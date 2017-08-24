/* op_hash_table.c ---
 *
 * Filename: op_hash_table.c
 * Description:
 * Author: Felix Chern
 * Maintainer:
 * Copyright: (c) 2017 Felix Chern
 * Created: Sun Apr  2 07:16:17 2017 (-0700)
 * Version:
 * Package-Requires: ()
 * Last-Updated:
 *           By:
 *     Update #: 0
 * URL:
 * Doc URL:
 * Keywords:
 * Compatibility:
 *
 */

/* Commentary:
 *
 *
 *
 */

/* Change Log:
 *
 *
 */

/* This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or (at
 * your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/* Code: */

#include <stdio.h> // TODO use op_log instead
#include <stdlib.h>
#include <inttypes.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include "opic/common/op_assert.h"
#include "opic/common/op_utils.h"
#include "opic/common/op_log.h"
#include "opic/op_malloc.h"
#include "op_hash_table.h"

#define PROBE_STATS_SIZE 64
#define DEFAULT_LARGE_DATA_THRESHOLD (1UL << 30)
#define VISIT_IDX_CACHE 8

OP_LOGGER_FACTORY(logger, "opic.hash.op_hash_table");

enum upsert_result_t
  {
    UPSERT_EMPTY,
    UPSERT_DUP,
    UPSERT_PUSHDOWN,
  };

static inline enum upsert_result_t
HTUpsertNewKey(OPHashTable* table, OPHash hasher,
               uint64_t hashed_key,
               void* key,
               uint8_t** matched_bucket,
               int* probe_state);

static inline void
HTUpsertPushDown(OPHashTable* table, OPHash hasher,
                 uint8_t* bucket_cpy, int probe,
                 uint8_t* avoid_bucket, bool* resize);

static bool HTSizeUp(OPHashTable* table, OPHash hasher);

struct OPHashTable
{
  uint64_t objcnt;
  uint64_t objcnt_high;
  uint64_t objcnt_low;
  uint64_t large_data_threshold;
  uint8_t capacity_clz;    // leading zeros of capacity
  uint8_t capacity_ms4b;   // most significant 4 bits
  uint16_t longest_probes;
  size_t keysize;
  size_t valsize;
  uint32_t stats[PROBE_STATS_SIZE];
  opref_t bucket_ref;
};

struct HTFunnel
{
  OPHashTable* restrict table;
  OPHash hasher;
  FunnelCB callback;
  size_t slotsize;
  uint8_t capacity_clz;
  uint8_t partition_clz;
  uint8_t* restrict tubes;
  ptrdiff_t* restrict flowheads;
};

static inline
uint64_t HTCapacityInternal(uint8_t capacity_clz, uint8_t capacity_ms4b);

OPHashTable*
HTNew(OPHeap* heap, uint64_t num_objects, double load,
      size_t keysize, size_t valsize)
{
  OPHashTable* table;
  uint64_t capacity;
  uint32_t capacity_clz, capacity_ms4b, capacity_msb;
  size_t bucket_size;
  void* bucket_ptr;

  op_assert(load > 0.0 && load < 1.0,
            "load %lf must within close interval (0.0, 1.0)\n", load);
  capacity = (uint64_t)(num_objects / load);
  if (capacity < 8)
    capacity = 8;
  capacity_clz = __builtin_clzl(capacity);
  capacity_msb = 64 - capacity_clz;
  capacity_ms4b = round_up_div(capacity, 1UL << (capacity_msb - 4));
  capacity = HTCapacityInternal((uint8_t)capacity_clz, (uint8_t)capacity_ms4b);

  bucket_size = keysize + valsize + 1;

  table = OPCalloc(heap, 1, sizeof(OPHashTable));
  if (!table)
    return NULL;
  bucket_ptr = OPCalloc(heap, 1, bucket_size * capacity);
  if (!bucket_ptr)
    {
      OPDealloc(table);
      return NULL;
    }
  table->bucket_ref = OPPtr2Ref(bucket_ptr);
  table->large_data_threshold = DEFAULT_LARGE_DATA_THRESHOLD;
  table->capacity_clz = capacity_clz;
  table->capacity_ms4b = capacity_ms4b;
  table->objcnt_high = (uint64_t)(capacity * load);
  table->objcnt_low = capacity * 2 / 10;
  table->keysize = keysize;
  table->valsize = valsize;
  return table;
}

void
HTDestroy(OPHashTable* table)
{
  OPDealloc(OPRef2Ptr(table, table->bucket_ref));
  OPDealloc(table);
}

uint64_t HTObjcnt(OPHashTable* table)
{
  return table->objcnt;
}

uint64_t HTCapacity(OPHashTable* table)
{
  return HTCapacityInternal(table->capacity_clz, table->capacity_ms4b);
}

size_t HTKeySize(OPHashTable* table)
{
  return table->keysize;
}

size_t HTValSize(OPHashTable* table)
{
  return table->valsize;
}

uint64_t HTCapacityInternal(uint8_t capacity_clz, uint8_t capacity_ms4b)
{
  return (1UL << (64 - capacity_clz - 4)) * capacity_ms4b;
}

static inline uint64_t
quadratic_exact(uint64_t hashed_key, int probe)
{
  return hashed_key + probe * (probe + 1);
}

static inline uint64_t
quadratic_partial(uint64_t probing_key, int probe)
{
  return probing_key + probe * 2;
}

// Fast mod and scale
// This is mod next power of two, times a number between 8 and 15
// then devide by 16. This gives us fast division on non power of
// two table size.
// Both linear probing and quadratic probing needs to double the
// probe sequence because the scaling part of this algorithm has
// some probability to trim off the last bit in the probed hash.
static inline uint64_t
fast_mod_scale(uint64_t probed_hash, uint64_t mask, uint64_t scale)
{
  return (probed_hash & mask) * scale >> 4;
}

static inline uintptr_t
hash_with_probe(OPHashTable* table, uint64_t key, int probe)
{
  uint64_t mask = (1ULL << (64 - table->capacity_clz)) - 1;

  // These probing methods are just for experiments.
  // They work on insertion and querying, but not deletion.
  // Only the quadratic probing is supported for all operation.
  // It is also the fastest probing strategry I find so far.

  // Linear probing
  // Under high load, linear probe can increase up to 50.
  // The high probe number makes both insert and query slow.
  // uint64_t probed_hash = key + probe * 2;

  // Quadratic probing
  uint64_t probed_hash = quadratic_exact(key, probe);

  // Double hashing
  // double hashing gives good probe distribution, but lacking
  // the cache locality makes it slower than both quadratic probing
  // and linear probing.
  // uint64_t up32key = key >> 32;
  // uint64_t probed_hash = key + up32key * probe;

  return fast_mod_scale(probed_hash, mask, table->capacity_ms4b);
}

static inline int
findprobe(OPHashTable* table, OPHash hasher, uintptr_t idx)
{
  const size_t keysize = table->keysize;
  const size_t valsize = table->valsize;
  const size_t bucket_size = keysize + valsize + 1;
  uint8_t* buckets = OPRef2Ptr(table, table->bucket_ref);
  uint64_t hashed_key, probing_key, probing_idx;
  uint64_t mask = (1ULL << (64 - table->capacity_clz)) - 1;

  hashed_key = hasher(&buckets[idx*bucket_size + 1], keysize);
  probing_key = hashed_key;

  for (int i = 0; i <= table->longest_probes; i++)
    {
      probing_key = quadratic_partial(probing_key, i);
      probing_idx = fast_mod_scale(probing_key, mask, table->capacity_ms4b);
      if (probing_idx == idx)
        return i;
    }
  OP_LOG_ERROR(logger, "Didn't find any match probe!\n");
  return -1;
}

static inline void
IncreaseProbeStat(OPHashTable* table, int probe)
{
  table->objcnt++;
  table->longest_probes = probe > table->longest_probes ?
    probe : table->longest_probes;
  table->stats[probe]++;
}

static inline enum upsert_result_t
HTUpsertNewKey(OPHashTable* table, OPHash hasher,
               uint64_t hashed_key,
               void* key,
               uint8_t** matched_bucket, int* probe_state)
{
  const size_t keysize = table->keysize;
  const size_t valsize = table->valsize;
  const size_t bucket_size = keysize + valsize + 1;
  uint8_t* restrict buckets;
  int probe, old_probe;
  uintptr_t idx, _idx;

  buckets = OPRef2Ptr(table, table->bucket_ref);
  probe = 0;

  while (true)
    {
      idx = hash_with_probe(table, hashed_key, probe);
      if (probe > PROBE_STATS_SIZE)
        {
          HTSizeUp(table, hasher);
          probe = 0;
          buckets = OPRef2Ptr(table, table->bucket_ref);
          continue;
        }
      // empty bucket
      if (buckets[idx * bucket_size] == 0)
        {
          IncreaseProbeStat(table, probe);
          *matched_bucket = &buckets[idx * bucket_size];
          return UPSERT_EMPTY;
        }
      // deleted bucket
      else if (buckets[idx * bucket_size] == 2)
        {
          for (int p = probe+1; p <= table->longest_probes; p++)
            {
              _idx = hash_with_probe(table, hashed_key, p);
              // if is empty or deleted, skip and look for next one
              if (buckets[_idx * bucket_size] == 1)
                continue;
              if (memeq(key, &buckets[_idx * bucket_size + 1], bucket_size))
                {
                  *matched_bucket = &buckets[_idx * bucket_size];
                  return UPSERT_DUP;
                }
            }
          IncreaseProbeStat(table, probe);
          *matched_bucket = &buckets[idx * bucket_size];
          return UPSERT_EMPTY;
        }
      if (memeq(key, &buckets[idx * bucket_size + 1], keysize))
        {
          *matched_bucket = &buckets[idx * bucket_size];
          return UPSERT_DUP;
        }
      old_probe = findprobe(table, hasher, idx);
      if (probe > old_probe)
        {
          table->longest_probes = probe > table->longest_probes ?
            probe : table->longest_probes;
          table->stats[old_probe]--;
          table->stats[probe]++;
          *matched_bucket = &buckets[idx * bucket_size];
          *probe_state = old_probe+1;
          return UPSERT_PUSHDOWN;
        }
      probe++;
    }
}

static inline void
HTUpsertPushDown(OPHashTable* table, OPHash hasher,
                 uint8_t* bucket_cpy, int probe, uint8_t* avoid_bucket,
                 bool* resized)
{
  const size_t keysize = table->keysize;
  const size_t valsize = table->valsize;
  const size_t bucket_size = keysize + valsize + 1;
  uint8_t* restrict buckets;
  int old_probe;
  uint8_t bucket_tmp[bucket_size];
  uintptr_t idx;
  uint64_t hashed_key, iter, capacity;
  int visit;
  uintptr_t visited_idx[VISIT_IDX_CACHE];

  visit = 0;
  *resized = false;
  hashed_key = hasher(&bucket_cpy[1], keysize);
  buckets = OPRef2Ptr(table, table->bucket_ref);
  capacity = HTCapacity(table);
  iter = 0;

  while (true)
    {
    next_iter:
      iter++;
      idx = hash_with_probe(table, hashed_key, probe);

      if (iter > capacity)
        {
          HTSizeUp(table, hasher);
          capacity = HTCapacity(table);
          iter = 0;
          probe = 0;
          buckets = OPRef2Ptr(table, table->bucket_ref);
          *resized = true;
          continue;
        }
      if (&buckets[idx * bucket_size] == avoid_bucket)
        {
          probe++;
          continue;
        }
      if (visit > 2)  // cycle can happen only after two visit
        {
          if (visit < VISIT_IDX_CACHE)
            {
              for (int i = 0; i < visit; i++)
                {
                  if (idx == visited_idx[i])
                    {
                      probe++;
                      goto next_iter;
                    }
                }
            }
          else
            {
              for (int i = visit + 1; i < visit + VISIT_IDX_CACHE; i++)
                {
                  if (idx == visited_idx[i % VISIT_IDX_CACHE])
                    {
                      probe++;
                      goto next_iter;
                    }
                }
            }
        }
      visited_idx[visit % VISIT_IDX_CACHE] = idx;
      visit++;

      // empty bucket or tombstone bucket
      if (buckets[idx * bucket_size] != 1)
        {
          IncreaseProbeStat(table, probe);
          memcpy(&buckets[idx * bucket_size], bucket_cpy, bucket_size);
          return;
        }

      old_probe = findprobe(table, hasher, idx);
      if (probe > old_probe)
        {
          table->longest_probes = probe > table->longest_probes ?
            probe : table->longest_probes;
          table->stats[old_probe]--;
          table->stats[probe]++;
          memcpy(bucket_tmp, &buckets[idx * bucket_size], bucket_size);
          memcpy(&buckets[idx * bucket_size], bucket_cpy, bucket_size);
          memcpy(bucket_cpy, bucket_tmp, bucket_size);
          probe = old_probe + 1;
          hashed_key = hasher(&bucket_cpy[1], keysize);
          continue;
        }
      probe++;
    }
}

static bool
HTSizeUp(OPHashTable* table, OPHash hasher)
{
  const size_t keysize = table->keysize;
  const size_t valsize = table->valsize;
  const size_t bucket_size = keysize + valsize + 1;
  const size_t large_data_threshold = table->large_data_threshold;
  uint8_t* old_buckets;
  uint8_t* new_buckets;
  uint8_t new_capacity_ms4b, new_capacity_clz;
  uint64_t old_capacity, new_capacity;
  bool resized;

  old_capacity = HTCapacity(table);
  old_buckets = OPRef2Ptr(table, table->bucket_ref);

  if (old_capacity * bucket_size >= large_data_threshold)
    {
      // increase size by 20% ~ 33%
      switch(table->capacity_ms4b)
        {
        case 8:
          new_capacity_ms4b = 10;
          new_capacity_clz = table->capacity_clz;
          break;
        case 9:
        case 10:
          new_capacity_ms4b = 12;
          new_capacity_clz = table->capacity_clz;
          break;
        case 11:
        case 12:
          new_capacity_ms4b = 14;
          new_capacity_clz = table->capacity_clz;
          break;
        case 13:
        case 14:
          new_capacity_ms4b = 8;
          new_capacity_clz = table->capacity_clz - 1;
          break;
        case 15:
          new_capacity_ms4b = 10;
          new_capacity_clz = table->capacity_clz - 1;
          break;
        default: op_assert(false, "Unknown capacity_ms4b %d\n",
                           table->capacity_ms4b);
        }
    }
  else
    {
      new_capacity_ms4b = 8;
      new_capacity_clz = table->capacity_ms4b == 8 ?
        table->capacity_clz - 1 : table->capacity_clz - 2;
    }
  new_capacity = HTCapacityInternal(new_capacity_clz, new_capacity_ms4b);
  OP_LOG_INFO(logger, "Resize from %" PRIu64 " to %" PRIu64,
              old_capacity, new_capacity);

  new_buckets = OPCalloc(ObtainOPHeap(table), 1, bucket_size * new_capacity);
  if (!new_buckets)
    {
      OP_LOG_ERROR(logger, "Cannot obtain new bucket for size %" PRIu64,
                   new_capacity);
      return false;
    }

  table->objcnt = 0;
  table->objcnt_high = new_capacity * 8 / 10;
  table->objcnt_low = new_capacity * 2 / 10;
  table->capacity_clz = new_capacity_clz;
  table->capacity_ms4b = new_capacity_ms4b;
  table->longest_probes = 0;
  memset(table->stats, 0x00, sizeof(uint32_t) * PROBE_STATS_SIZE);
  table->bucket_ref = OPPtr2Ref(new_buckets);

  for (uint64_t idx = 0; idx < old_capacity; idx++)
    {
      if (old_buckets[idx*bucket_size] == 1)
        {
          HTUpsertPushDown(table, hasher, &old_buckets[idx * bucket_size],
                           0, NULL, &resized);
        }
    }
  OPDealloc(old_buckets);
  return true;
}

static bool
HTSizeDown(OPHashTable* table, OPHash hasher)
{
  const size_t keysize = table->keysize;
  const size_t valsize = table->valsize;
  const size_t bucket_size = keysize + valsize + 1;
  uint8_t* old_buckets;
  uint8_t* new_buckets;
  uint8_t new_capacity_ms4b, new_capacity_clz;
  uint64_t old_capacity, new_capacity;
  bool resized;

  old_capacity = HTCapacity(table);
  old_buckets = OPRef2Ptr(table, table->bucket_ref);
  op_assert(old_capacity > 16,
            "Can not resize smaller than 16, but got old_capacity %"
            PRIu64 "\n", old_capacity);

  switch(table->capacity_ms4b)
    {
    case 8:  // new load 0.45
    case 9:  // new load 0.50
    case 10: // new load 0.55
    case 11: // new load 0.60
      new_capacity_ms4b = 8;
      new_capacity_clz = table->capacity_clz + 1;
      break;
    case 12: // new load 0.40
    case 13: // new load 0.43
    case 14: // new load 0.46
    case 15: // new load 0.50
      new_capacity_ms4b = 12;
      new_capacity_clz = table->capacity_clz + 1;
      break;
    default: op_assert(false, "Unknown capacity_ms4b %d\n",
                       table->capacity_ms4b);
    }

  new_capacity = HTCapacityInternal(new_capacity_clz, new_capacity_ms4b);
  OP_LOG_INFO(logger, "Resize from %" PRIu64 " to %" PRIu64,
              old_capacity, new_capacity);
  new_buckets = OPCalloc(ObtainOPHeap(table), 1, bucket_size * new_capacity);
  if (!new_buckets)
    {
      OP_LOG_ERROR(logger, "Cannot obtain new bucket for size %" PRIu64,
                   new_capacity);
      return false;
    }

  table->objcnt = 0;
  table->objcnt_high = new_capacity * 8 / 10;
  table->objcnt_low = new_capacity * 2 / 10;
  table->capacity_clz = new_capacity_clz;
  table->capacity_ms4b = new_capacity_ms4b;
  table->longest_probes = 0;
  memset(table->stats, 0x00, sizeof(uint32_t) * PROBE_STATS_SIZE);
  table->bucket_ref = OPPtr2Ref(new_buckets);

  for (uint64_t idx = 0; idx < old_capacity; idx++)
    {
      if (old_buckets[idx*bucket_size] == 1)
        {
          HTUpsertPushDown(table, hasher, &old_buckets[idx * bucket_size],
                           0, NULL, &resized);
        }
    }
  OPDealloc(old_buckets);
  return true;
}

static inline
bool HTPreHashInsertCustom(OPHashTable* table, OPHash hasher,
                           uint64_t hashed_key, void* key, void* val)
{
  const size_t keysize = table->keysize;
  const size_t valsize = table->valsize;
  const size_t bucket_size = keysize + valsize + 1;
  enum upsert_result_t upsert_result;
  uint8_t* matched_bucket;
  int probe;
  uint8_t bucket_cpy[bucket_size];
  bool resized;

  if (table->objcnt > table->objcnt_high)
    {
      if(!HTSizeUp(table, hasher))
        return false;
    }

  upsert_result = HTUpsertNewKey(table, hasher, hashed_key, key,
                                 &matched_bucket, &probe);

  switch (upsert_result)
    {
    case UPSERT_EMPTY:
      *matched_bucket = 1;
      memcpy(&matched_bucket[1], key, keysize);
    case UPSERT_DUP:
      memcpy(&matched_bucket[1 + keysize], val, valsize);
      break;
    case UPSERT_PUSHDOWN:
      memcpy(bucket_cpy, matched_bucket, bucket_size);
      memcpy(&matched_bucket[1], key, keysize);
      memcpy(&matched_bucket[1 + keysize], val, valsize);
      HTUpsertPushDown(table, hasher, bucket_cpy, probe,
                       matched_bucket, &resized);
    }
  return true;
}

bool HTInsertCustom(OPHashTable* table, OPHash hasher, void* key, void* val)
{
  uint64_t hashed_key;
  hashed_key = hasher(key, table->keysize);
  return HTPreHashInsertCustom(table, hasher, hashed_key, key, val);
}

bool HTUpsertCustom(OPHashTable* table, OPHash hasher,
                    void* key, void** val_ref, bool* is_duplicate)
{
  const size_t keysize = table->keysize;
  const size_t valsize = table->valsize;
  const size_t bucket_size = keysize + valsize + 1;
  enum upsert_result_t upsert_result;
  uint64_t hashed_key;
  uint8_t* matched_bucket;
  int probe;
  uint8_t bucket_cpy[bucket_size];
  bool resized;

  if (table->objcnt > table->objcnt_high)
    {
      if (!HTSizeUp(table, hasher))
        return false;
    }

  hashed_key = hasher(key, keysize);
  upsert_result = HTUpsertNewKey(table, hasher, hashed_key, key,
                                 &matched_bucket, &probe);
  *val_ref = &matched_bucket[keysize + 1];
  switch (upsert_result)
    {
    case UPSERT_EMPTY:
      *is_duplicate = false;
      *matched_bucket = 1;
      memcpy(&matched_bucket[1], key, keysize);
      break;
    case UPSERT_DUP:
      *is_duplicate = true;
      break;
    case UPSERT_PUSHDOWN:
      *is_duplicate = false;
      memcpy(bucket_cpy, matched_bucket, bucket_size);
      memcpy(&matched_bucket[1], key, keysize);
      HTUpsertPushDown(table, hasher, bucket_cpy, probe,
                       matched_bucket, &resized);
      if (resized)
        {
          *val_ref = HTGetCustom(table, hasher, key);
        }
    }
  return true;
}

static inline bool
HTPreHashSearchIdx(OPHashTable* table, uint64_t hashed_key,
                   void* key, uintptr_t* idx)
{
  const size_t keysize = table->keysize;
  const size_t valsize = table->valsize;
  const size_t bucket_size = keysize + valsize + 1;
  uint8_t* buckets = OPRef2Ptr(table, table->bucket_ref);
  uintptr_t idx_next;
  uint64_t mask = (1ULL << (64 - table->capacity_clz)) - 1;
  uint64_t probing_key;

  probing_key = hashed_key;
  *idx = fast_mod_scale(probing_key, mask, table->capacity_ms4b);
  probing_key = quadratic_partial(probing_key, 1);
  idx_next = fast_mod_scale(probing_key, mask, table->capacity_ms4b);
  for (int probe = 2; probe <= table->longest_probes+2; probe++)
    {
      __builtin_prefetch(&buckets[idx_next * bucket_size], 0, 0);
      if (buckets[*idx * bucket_size] == 0)
        return false;
      if (buckets[*idx * bucket_size] == 2)
        goto next_iter;
      if (memeq(key, &buckets[*idx*bucket_size + 1], keysize))
        return true;
    next_iter:
      *idx = idx_next;
      probing_key = quadratic_partial(probing_key, probe);
      idx_next = fast_mod_scale(probing_key, mask, table->capacity_ms4b);
    }
  return false;
}

static inline bool
HTSearchIdx(OPHashTable* table, OPHash hasher, void* key, uintptr_t* idx)
{
  const size_t keysize = table->keysize;
  uint64_t hashed_key;
  hashed_key = hasher(key, keysize);
  return HTPreHashSearchIdx(table, hashed_key, key, idx);
}

void* HTGetCustom(OPHashTable* table, OPHash hasher, void* key)
{
  const size_t keysize = table->keysize;
  const size_t valsize = table->valsize;
  const size_t bucket_size = keysize + valsize + 1;
  uint8_t* buckets = OPRef2Ptr(table, table->bucket_ref);
  uintptr_t idx;
  if (HTSearchIdx(table, hasher, key, &idx))
    {
      return &buckets[idx*bucket_size + keysize + 1];
    }
  return NULL;
}

int HTGetProbeCustom(OPHashTable* table, OPHash hasher, void* key)
{
  uintptr_t idx;
  if (HTSearchIdx(table, hasher, key, &idx))
    {
      return findprobe(table, hasher, idx);
    }
  return -1;
}

static inline void*
HTPreHashDeleteCustom(OPHashTable* table, OPHash hasher,
                      uint64_t hashed_key, void* key)
{
  /*
   * This works for load that is not super high, i.e. < 0.9.
   * It slows down the growth for both E[psl] and Var[psl], but only
   * slows down, not bounding it.
   */
  const size_t keysize = table->keysize;
  const size_t valsize = table->valsize;
  const size_t bucket_size = keysize + valsize + 1;
  uint8_t* restrict buckets;
  uintptr_t idx;
  int record_probe;

  if (table->objcnt < table->objcnt_low &&
      table->objcnt > 16)
    {
      if (!HTSizeDown(table, hasher))
        return NULL;
    }

  if (!HTPreHashSearchIdx(table, hashed_key, key, &idx))
    return NULL;

  buckets = OPRef2Ptr(table, table->bucket_ref);

  table->objcnt--;
  record_probe = findprobe(table, hasher, idx);
  if (record_probe < PROBE_STATS_SIZE)
    table->stats[record_probe]--;
  else
    OP_LOG_WARN(logger, "Large probe: %d\n", record_probe);

  if (record_probe == table->longest_probes &&
      table->stats[record_probe] == 0)
    {
      for (int i = table->longest_probes; i >= 0; i--)
        {
          if (table->stats[i])
            {
              table->longest_probes = i;
              break;
            }
        }
    }
  // Turns out marking tombstone is good enough.
  // I used a have a implementation which lookup candidates
  // with high probing count that can fullfill the deleted spot, and
  // thought this would reduce both the mean and variance of the probe
  // counts like robin hood insertion does.
  // After some experiments I found this strategy gives similar probe
  // distribution like the one without the rebalancing strategy.
  buckets[idx * bucket_size] = 2;
  return &buckets[idx * bucket_size + 1 + keysize];
}

void* HTDeleteCustom(OPHashTable* table, OPHash hasher, void* key)
{
  uint64_t hashed_key;
  hashed_key = hasher(key, table->keysize);
  return HTPreHashDeleteCustom(table, hasher, hashed_key, key);
}

void HTIterate(OPHashTable* table, OPHashIterator iterator, void* context)
{
  const size_t keysize = table->keysize;
  const size_t valsize = table->valsize;
  const size_t bucket_size = keysize + valsize + 1;
  uint8_t* buckets = OPRef2Ptr(table, table->bucket_ref);
  uint64_t capacity = HTCapacity(table);

  for (uint64_t idx = 0; idx < capacity; idx++)
    {
      if (buckets[idx*bucket_size] == 1)
        {
          iterator(&buckets[idx*bucket_size + 1],
                   &buckets[idx*bucket_size + 1 + keysize],
                   keysize, valsize, context);
        }
    }
}

void HTPrintStat(OPHashTable* table)
{
  for (int i = 0; i < PROBE_STATS_SIZE; i++)
    if (table->stats[i])
      printf("probe %02d: %d\n", i, table->stats[i]);
}

uint32_t HTMaxProbe(OPHashTable* table)
{
  return table->longest_probes;
}

uint32_t HTProbeStat(OPHashTable* table, uint32_t idx)
{
  if (idx < PROBE_STATS_SIZE)
    return table->stats[idx];
  return 0;
}

HTFunnel* HTFunnelNewCustom(OPHashTable* table, OPHash hasher,
                            FunnelCB callback,
                            size_t slotsize, size_t partition_size)
{
  HTFunnel* funnel;
  size_t bucketsize;
  int tube_num;

  funnel = malloc(sizeof(HTFunnel));
  bucketsize = table->keysize + table->valsize + 1;
  funnel->table = table;
  funnel->hasher = hasher;
  funnel->callback = callback;
  funnel->slotsize = slotsize;
  funnel->partition_clz = __builtin_clzll(partition_size / bucketsize);
  funnel->capacity_clz = 0;
  funnel->tubes = NULL;
  funnel->flowheads = NULL;
  if (funnel->partition_clz > table->capacity_clz)
    {
      funnel->capacity_clz = table->capacity_clz;
      tube_num = 1 << (funnel->partition_clz - funnel->capacity_clz);
      funnel->tubes = malloc(tube_num * slotsize);
      funnel->flowheads = malloc(tube_num * sizeof(ptrdiff_t*));
      for (int i = 0; i < tube_num; i++)
        funnel->flowheads[i] = i * funnel->slotsize;
    }
  return funnel;
}

void HTFunnelDestroy(HTFunnel* funnel)
{
  if (!funnel)
    return;

  if (funnel->tubes)
    free(funnel->tubes);
  if (funnel->flowheads)
    free(funnel->flowheads);
  free(funnel);
}

void HTFunnelPreHashInsert(HTFunnel* funnel,
                           uint64_t hashed_key,
                           void* key, void* value)
{
  const size_t keysize = funnel->table->keysize;
  const size_t valsize = funnel->table->valsize;
  const size_t bucket_size = keysize + valsize + 1;
  const size_t trip_bundle_size = sizeof(hashed_key) + keysize + valsize;

  OPHashTable* table;
  int tube_num, old_tube_num, row_idx, probe;
  uint64_t mask;
  ptrdiff_t flowhead, flowbase, tubeidx;
  ptrdiff_t* old_flowheads;
  uint8_t *old_tubes, *tube_key, *tube_val, *matched_bucket;
  uint64_t* tube_hashed_key;
  bool resized;
  enum upsert_result_t upsert_result;
  uint8_t bucket_cpy[bucket_size];

  table = funnel->table;

  if (funnel->capacity_clz != table->capacity_clz)
    {
      if (funnel->capacity_clz == 0)
        {
          // If the capacity of the hash table is smaller than
          // partitions, simply insert the items into the hash table.
          // Otherwise, initialize the funnels.
          if (funnel->partition_clz > table->capacity_clz)
            {
              funnel->capacity_clz = table->capacity_clz;
              tube_num = 1 << (funnel->partition_clz - funnel->capacity_clz);
              funnel->tubes = malloc(tube_num * funnel->slotsize);
              funnel->flowheads = malloc(tube_num * sizeof(ptrdiff_t*));
              for (row_idx = 0; row_idx < tube_num; row_idx++)
                funnel->flowheads[row_idx] = row_idx * funnel->slotsize;
            }
          else
            {
              HTPreHashInsertCustom(table, funnel->hasher,
                                    hashed_key, key, value);
              return;
            }
        }
      else
        {
          old_tube_num = 1 << (funnel->partition_clz - funnel->capacity_clz);
          old_tubes = funnel->tubes;
          old_flowheads = funnel->flowheads;

          funnel->capacity_clz = table->capacity_clz;
          tube_num = 1 << (funnel->partition_clz - funnel->capacity_clz);
          funnel->tubes = malloc(tube_num * funnel->slotsize);
          funnel->flowheads = malloc(tube_num * sizeof(ptrdiff_t*));
          for (row_idx = 0; row_idx < tube_num; row_idx++)
            funnel->flowheads[row_idx] = row_idx * funnel->slotsize;

          for (row_idx = 0; row_idx < old_tube_num; row_idx++)
            {
              tubeidx = row_idx * funnel->slotsize;
              flowhead = old_flowheads[row_idx];
              while (tubeidx < flowhead)
                {
                  tube_hashed_key = (uint64_t*)&old_tubes[tubeidx];
                  tubeidx += sizeof(uint64_t);
                  tube_key = &old_tubes[tubeidx];
                  tubeidx += keysize;
                  tube_val = &old_tubes[tubeidx];
                  tubeidx += valsize;
                  HTFunnelPreHashInsert(funnel,
                                        *tube_hashed_key,
                                        tube_key, tube_val);
                }
            }
          free(old_flowheads);
          free(old_tubes);
        }
    }

  mask = (1ULL << (64 - funnel->capacity_clz)) - 1;
  row_idx = (hashed_key & mask) >> funnel->partition_clz;
  flowhead = funnel->flowheads[row_idx];
  flowbase = row_idx * funnel->slotsize;

  // flush funnel into hash table
  if (trip_bundle_size + flowhead - flowbase > funnel->slotsize)
    {
      tubeidx = flowbase;
      while (tubeidx < flowhead)
        {
          tube_hashed_key = (uint64_t*)&funnel->tubes[tubeidx];
          tubeidx += sizeof(uint64_t);
          tube_key = &funnel->tubes[tubeidx];
          tubeidx += keysize;
          tube_val = &funnel->tubes[tubeidx];
          tubeidx += valsize;

          upsert_result = HTUpsertNewKey(table, funnel->hasher,
                                         *tube_hashed_key,
                                         tube_key,
                                         &matched_bucket,
                                         &probe);
          switch (upsert_result)
            {
            case UPSERT_EMPTY:
              *matched_bucket = 1;
              memcpy(&matched_bucket[1], tube_key, keysize);
            case UPSERT_DUP:
              memcpy(&matched_bucket[1 + keysize], tube_val, valsize);
              break;
            case UPSERT_PUSHDOWN:
              memcpy(bucket_cpy, matched_bucket, bucket_size);
              memcpy(&matched_bucket[1], tube_key, keysize);
              memcpy(&matched_bucket[1 + keysize], tube_val, valsize);
              HTUpsertPushDown(table, funnel->hasher, bucket_cpy, probe,
                               matched_bucket, &resized);
            }
        }
      funnel->flowheads[row_idx] = flowbase;
      flowhead = flowbase;
    }

  tubeidx = flowhead;
  memcpy(&funnel->tubes[tubeidx], &hashed_key, sizeof(uint64_t));
  tubeidx += sizeof(hashed_key);
  memcpy(&funnel->tubes[tubeidx], key, keysize);
  tubeidx += keysize;
  memcpy(&funnel->tubes[tubeidx], value, valsize);
  tubeidx += valsize;
  funnel->flowheads[row_idx] = tubeidx;
}

void HTFunnelInsert(HTFunnel* funnel,
                    void* key, void* value)
{
  uint64_t hashed_key;
  hashed_key = funnel->hasher(key, funnel->table->keysize);
  HTFunnelPreHashInsert(funnel, hashed_key, key, value);
}

void HTFunnelInsertFlush(HTFunnel* funnel)
{
  const size_t keysize = funnel->table->keysize;
  const size_t valsize = funnel->table->valsize;
  const size_t bucket_size = keysize + valsize + 1;

  OPHashTable* table;
  int tube_num, row_idx, probe;
  ptrdiff_t flowhead, tubeidx;
  uint8_t *tube_key, *tube_val, *matched_bucket;
  uint64_t* tube_hashed_key;
  bool resized;
  enum upsert_result_t upsert_result;
  uint8_t bucket_cpy[bucket_size];

  if (!funnel->tubes || !funnel->table)
    return;

  table = funnel->table;
  tube_num = 1 << (funnel->partition_clz - funnel->capacity_clz);

  for (row_idx = 0; row_idx < tube_num; row_idx++)
    {
      tubeidx = row_idx * funnel->slotsize;
      flowhead = funnel->flowheads[row_idx];
      while (tubeidx < flowhead)
        {
          tube_hashed_key = (uint64_t*)&funnel->tubes[tubeidx];
          tubeidx += sizeof(uint64_t);
          tube_key = &funnel->tubes[tubeidx];
          tubeidx += keysize;
          tube_val = &funnel->tubes[tubeidx];
          tubeidx += valsize;

          upsert_result = HTUpsertNewKey(table, funnel->hasher,
                                         *tube_hashed_key,
                                         tube_key,
                                         &matched_bucket,
                                         &probe);
          switch (upsert_result)
            {
            case UPSERT_EMPTY:
              *matched_bucket = 1;
              memcpy(&matched_bucket[1], tube_key, keysize);
            case UPSERT_DUP:
              memcpy(&matched_bucket[1 + keysize], tube_val, valsize);
              break;
            case UPSERT_PUSHDOWN:
              memcpy(bucket_cpy, matched_bucket, bucket_size);
              memcpy(&matched_bucket[1], tube_key, keysize);
              memcpy(&matched_bucket[1 + keysize], tube_val, valsize);
              HTUpsertPushDown(table, funnel->hasher, bucket_cpy, probe,
                               matched_bucket, &resized);
            }
        }
      funnel->flowheads[row_idx] = row_idx * funnel->slotsize;
    }
}

void HTFunnelPreHashUpsert(HTFunnel* funnel,
                           uint64_t hashed_key,
                           void* key, void* value,
                           void* context, size_t ctxsize_st)
{
  const size_t keysize = funnel->table->keysize;
  const size_t valsize = funnel->table->valsize;
  const size_t bucket_size = keysize + valsize + 1;

  size_t trip_bundle_size;
  OPHashTable* table;
  OPFunnelUpsertCB upsertcb;
  int tube_num, old_tube_num, row_idx, probe;
  uint64_t mask;
  ptrdiff_t flowhead, flowbase, tubeidx;
  ptrdiff_t* old_flowheads;
  uint8_t *old_tubes, *tube_key, *tube_val, *tube_ctx, *matched_bucket;
  uint32_t* tube_ctxsize;
  uint32_t ctxsize;
  uint64_t* tube_hashed_key;
  bool resized;
  enum upsert_result_t upsert_result;
  uint8_t bucket_cpy[bucket_size];

  table = funnel->table;
  upsertcb = funnel->callback.upsertcb;
  ctxsize = (uint32_t)ctxsize_st;

  if (funnel->capacity_clz != table->capacity_clz)
    {
      if (funnel->capacity_clz == 0)
        {
          // If the capacity of the hash table is smaller than
          // partitions, simply insert the items into the hash table.
          // Otherwise, initialize the funnels.
          if (funnel->partition_clz > table->capacity_clz)
            {
              funnel->capacity_clz = table->capacity_clz;
              tube_num = 1 << (funnel->partition_clz - funnel->capacity_clz);
              funnel->tubes = malloc(tube_num * funnel->slotsize);
              funnel->flowheads = malloc(tube_num * sizeof(ptrdiff_t*));
              for (row_idx = 0; row_idx < tube_num; row_idx++)
                funnel->flowheads[row_idx] = row_idx * funnel->slotsize;
            }
          else
            {
              HTInsertCustom(table, funnel->hasher, key, value);
              upsert_result = HTUpsertNewKey(table, funnel->hasher,
                                             hashed_key,
                                             key,
                                             &matched_bucket,
                                             &probe);
              switch (upsert_result)
                {
                case UPSERT_EMPTY:
                  *matched_bucket = 1;
                  memcpy(&matched_bucket[1], key, keysize);
                  if (upsertcb)
                    upsertcb(&matched_bucket[1],           // key
                             &matched_bucket[1 + keysize], // table_value
                             value,                        // upsert_value
                             context,                      // context
                             keysize, valsize, ctxsize,
                             false);  // is_duplicate = false
                  break;
                case UPSERT_DUP:
                  if (upsertcb)
                    upsertcb(&matched_bucket[1],           // key
                             &matched_bucket[1 + keysize], // table_value
                             value,                        // upsert_value
                             context,                      // context
                             keysize, valsize, ctxsize,
                             true);  // is_duplicate = true
                  break;
                case UPSERT_PUSHDOWN:
                  memcpy(bucket_cpy, matched_bucket, bucket_size);
                  memcpy(&matched_bucket[1], key, keysize);
                  HTUpsertPushDown(table, funnel->hasher, bucket_cpy, probe,
                                   matched_bucket, &resized);
                  // if resized, the matched bucket no longer point to correct
                  // address of the inserted bucket, we need to search for it
                  // again.
                  if (resized)
                    {
                      // reference to value
                      matched_bucket = HTGetCustom(table, funnel->hasher, key);
                      // change it to regular matched bucket
                      matched_bucket -= 1 + keysize;
                    }
                  if (upsertcb)
                    upsertcb(&matched_bucket[1],           // key
                             &matched_bucket[1 + keysize], // table_value
                             value,                        // upsert_value
                             context,                      // context
                             keysize, valsize, ctxsize,
                             false);  // is_duplicate = false
                }
              return;
            }
        }
      else
        {
          old_tube_num = 1 << (funnel->partition_clz - funnel->capacity_clz);
          old_tubes = funnel->tubes;
          old_flowheads = funnel->flowheads;

          funnel->capacity_clz = table->capacity_clz;
          tube_num = 1 << (funnel->partition_clz - funnel->capacity_clz);
          funnel->tubes = malloc(tube_num * funnel->slotsize);
          funnel->flowheads = malloc(tube_num * sizeof(ptrdiff_t*));
          for (row_idx = 0; row_idx < tube_num; row_idx++)
            funnel->flowheads[row_idx] = row_idx * funnel->slotsize;

          for (row_idx = 0; row_idx < old_tube_num; row_idx++)
            {
              tubeidx = row_idx * funnel->slotsize;
              flowhead = old_flowheads[row_idx];
              while (tubeidx < flowhead)
                {
                  tube_hashed_key = (uint64_t*)&old_tubes[tubeidx];
                  tubeidx += sizeof(uint64_t);
                  tube_ctxsize = (uint32_t*)&funnel->tubes[tubeidx];
                  tubeidx += sizeof(uint32_t);
                  tube_key = &old_tubes[tubeidx];
                  tubeidx += keysize;
                  tube_val = &old_tubes[tubeidx];
                  tubeidx += valsize;
                  tube_ctx = &funnel->tubes[tubeidx];
                  tubeidx += *tube_ctxsize;
                  upsert_result = HTUpsertNewKey(table, funnel->hasher,
                                                 *tube_hashed_key,
                                                 tube_key,
                                                 &matched_bucket,
                                                 &probe);
                  switch (upsert_result)
                    {
                    case UPSERT_EMPTY:
                      *matched_bucket = 1;
                      memcpy(&matched_bucket[1], tube_key, keysize);
                      if (upsertcb)
                        upsertcb(&matched_bucket[1],           // key
                                 &matched_bucket[1 + keysize], // table_value
                                 tube_val,                     // funnel_value
                                 tube_ctx,                     // context
                                 keysize, valsize, *tube_ctxsize,
                                 false);  // is_duplicate = false
                      break;
                    case UPSERT_DUP:
                      if (upsertcb)
                        upsertcb(&matched_bucket[1],           // key
                                 &matched_bucket[1 + keysize], // table_value
                                 tube_val,                     // funnel_value
                                 tube_ctx,                     // context
                                 keysize, valsize, *tube_ctxsize,
                                 true);  // is_duplicate = true
                      break;
                    case UPSERT_PUSHDOWN:
                      memcpy(bucket_cpy, matched_bucket, bucket_size);
                      memcpy(&matched_bucket[1], tube_key, keysize);
                      HTUpsertPushDown(table, funnel->hasher, bucket_cpy, probe,
                                       matched_bucket, &resized);
                      if (resized)
                        {
                          // reference to value
                          matched_bucket = HTGetCustom(table, funnel->hasher,
                                                       tube_key);
                          // change it to regular matched bucket
                          matched_bucket -= 1 + keysize;
                        }
                      if (upsertcb)
                        upsertcb(&matched_bucket[1],           // key
                                 &matched_bucket[1 + keysize], // table_value
                                 tube_val,                     // funnel_value
                                 tube_ctx,                     // context
                                 keysize, valsize, *tube_ctxsize,
                                 false);  // is_duplicate = false
                    }
                }
            }
          free(old_flowheads);
          free(old_tubes);
        }
    }

  mask = (1ULL << (64 - funnel->capacity_clz)) - 1;
  row_idx = (hashed_key & mask) >> funnel->partition_clz;
  flowhead = funnel->flowheads[row_idx];
  flowbase = row_idx * funnel->slotsize;
  trip_bundle_size = sizeof(hashed_key) + sizeof(uint32_t)
    + keysize + valsize + ctxsize;
  op_assert(trip_bundle_size < funnel->slotsize);

  // flush funnel into hash table
  if (trip_bundle_size + flowhead - flowbase > funnel->slotsize)
    {
      tubeidx = flowbase;
      while (tubeidx < flowhead)
        {
          tube_hashed_key = (uint64_t*)&funnel->tubes[tubeidx];
          tubeidx += sizeof(uint64_t);
          tube_ctxsize = (uint32_t*)&funnel->tubes[tubeidx];
          tubeidx += sizeof(uint32_t);
          tube_key = &funnel->tubes[tubeidx];
          tubeidx += keysize;
          tube_val = &funnel->tubes[tubeidx];
          tubeidx += valsize;
          tube_ctx = &funnel->tubes[tubeidx];
          tubeidx += *tube_ctxsize;
          upsert_result = HTUpsertNewKey(table, funnel->hasher,
                                         *tube_hashed_key,
                                         tube_key,
                                         &matched_bucket,
                                         &probe);
          switch (upsert_result)
            {
            case UPSERT_EMPTY:
              *matched_bucket = 1;
              memcpy(&matched_bucket[1], tube_key, keysize);
              if (upsertcb)
                upsertcb(&matched_bucket[1],           // key
                         &matched_bucket[1 + keysize], // table_value
                         tube_val,                     // funnel_value
                         tube_ctx,                     // context
                         keysize, valsize, *tube_ctxsize,
                         false);  // is_duplicate = false
              break;
            case UPSERT_DUP:
              if (upsertcb)
                upsertcb(&matched_bucket[1],           // key
                         &matched_bucket[1 + keysize], // table_value
                         tube_val,                     // funnel_value
                         tube_ctx,                     // context
                         keysize, valsize, *tube_ctxsize,
                         true);  // is_duplicate = true
              break;
            case UPSERT_PUSHDOWN:
              memcpy(bucket_cpy, matched_bucket, bucket_size);
              memcpy(&matched_bucket[1], tube_key, keysize);
              HTUpsertPushDown(table, funnel->hasher, bucket_cpy, probe,
                               matched_bucket, &resized);
              // if resized, the matched bucket no longer point to correct
              // address of the inserted bucket, we need to search for it again.
              if (resized)
                {
                  // reference to value
                  matched_bucket = HTGetCustom(table, funnel->hasher, tube_key);
                  // change it to regular matched bucket
                  matched_bucket -= 1 + keysize;
                }
              if (upsertcb)
                upsertcb(&matched_bucket[1],           // key
                         &matched_bucket[1 + keysize], // table_value
                         tube_val,                     // funnel_value
                         tube_ctx,                     // context
                         keysize, valsize, *tube_ctxsize,
                         false);  // is_duplicate = false
            }
        }
      funnel->flowheads[row_idx] = flowbase;
      flowhead = flowbase;
    }

  tubeidx = flowhead;
  memcpy(&funnel->tubes[tubeidx], &hashed_key, sizeof(uint64_t));
  tubeidx += sizeof(hashed_key);
  memcpy(&funnel->tubes[tubeidx], &ctxsize, sizeof(uint32_t));
  tubeidx += sizeof(uint32_t);
  memcpy(&funnel->tubes[tubeidx], key, keysize);
  tubeidx += keysize;
  memcpy(&funnel->tubes[tubeidx], value, valsize);
  tubeidx += valsize;
  memcpy(&funnel->tubes[tubeidx], context, ctxsize);
  tubeidx += ctxsize;
  funnel->flowheads[row_idx] = tubeidx;
}

void HTFunnelUpsert(HTFunnel* funnel,
                    void* key, void* value, void* context, size_t ctxsize)
{
  uint64_t hashed_key;
  hashed_key = funnel->hasher(key, funnel->table->keysize);
  HTFunnelPreHashUpsert(funnel, hashed_key, key, value, context, ctxsize);
}

void HTFunnelUpsertFlush(HTFunnel* funnel)
{
  const size_t keysize = funnel->table->keysize;
  const size_t valsize = funnel->table->valsize;
  const size_t bucket_size = keysize + valsize + 1;

  OPHashTable* table;
  OPFunnelUpsertCB upsertcb;
  int tube_num, row_idx, probe;
  ptrdiff_t flowhead, tubeidx;
  uint8_t *tube_key, *tube_val, *tube_ctx, *matched_bucket;
  uint32_t* tube_ctxsize;
  uint64_t* tube_hashed_key;
  bool resized;
  enum upsert_result_t upsert_result;
  uint8_t bucket_cpy[bucket_size];

  if (!funnel->tubes || !funnel->table)
    return;

  table = funnel->table;
  upsertcb = funnel->callback.upsertcb;
  tube_num = 1 << (funnel->partition_clz - funnel->capacity_clz);

  for (row_idx = 0; row_idx < tube_num; row_idx++)
    {
      tubeidx = row_idx * funnel->slotsize;
      flowhead = funnel->flowheads[row_idx];
      while (tubeidx < flowhead)
        {
          tube_hashed_key = (uint64_t*)&funnel->tubes[tubeidx];
          tubeidx += sizeof(uint64_t);
          tube_ctxsize = (uint32_t*)&funnel->tubes[tubeidx];
          tubeidx += sizeof(uint32_t);
          tube_key = &funnel->tubes[tubeidx];
          tubeidx += keysize;
          tube_val = &funnel->tubes[tubeidx];
          tubeidx += valsize;
          tube_ctx = &funnel->tubes[tubeidx];
          tubeidx += *tube_ctxsize;

          upsert_result = HTUpsertNewKey(table, funnel->hasher,
                                         *tube_hashed_key,
                                         tube_key,
                                         &matched_bucket,
                                         &probe);
          switch (upsert_result)
            {
            case UPSERT_EMPTY:
              *matched_bucket = 1;
              memcpy(&matched_bucket[1], tube_key, keysize);
              if (upsertcb)
                upsertcb(&matched_bucket[1],           // key
                         &matched_bucket[1 + keysize], // table_value
                         tube_val,                     // funnel_value
                         tube_ctx,                     // context
                         keysize, valsize, *tube_ctxsize,
                         false);  // is_duplicate = false
              break;
            case UPSERT_DUP:
              if (upsertcb)
                upsertcb(&matched_bucket[1],           // key
                         &matched_bucket[1 + keysize], // table_value
                         tube_val,                     // funnel_value
                         tube_ctx,                     // context
                         keysize, valsize, *tube_ctxsize,
                         true);  // is_duplicate = true
              break;
            case UPSERT_PUSHDOWN:
              memcpy(bucket_cpy, matched_bucket, bucket_size);
              memcpy(&matched_bucket[1], tube_key, keysize);
              HTUpsertPushDown(table, funnel->hasher, bucket_cpy, probe,
                               matched_bucket, &resized);
              // if resized, the matched bucket no longer point to correct
              // address of the inserted bucket, we need to search for it again.
              if (resized)
                {
                  // reference to value
                  matched_bucket = HTGetCustom(table, funnel->hasher, tube_key);
                  // change it to regular matched bucket
                  matched_bucket -= 1 + keysize;
                }
              if (upsertcb)
                upsertcb(&matched_bucket[1],           // key
                         &matched_bucket[1 + keysize], // table_value
                         tube_val,                     // funnel_value
                         tube_ctx,                     // context
                         keysize, valsize, *tube_ctxsize,
                         false);  // is_duplicate = false
            }
        }
      funnel->flowheads[row_idx] = row_idx * funnel->slotsize;
    }
}

void HTFunnelGet(HTFunnel* funnel, void* key, void* context, size_t ctxsize)
{
  uint64_t hashed_key;
  hashed_key = funnel->hasher(key, funnel->table->keysize);
  HTFunnelPreHashGet(funnel, hashed_key, key, context, ctxsize);
}

void HTFunnelPreHashGet(HTFunnel* funnel, uint64_t hashed_key,
                        void* key, void* context, size_t ctxsize_st)
{
  const size_t keysize = funnel->table->keysize;
  const size_t valsize = funnel->table->valsize;
  const size_t bucket_size = keysize + valsize + 1;

  OPHashTable* table;
  OPFunnelGetCB getcb;
  int row_idx;
  uint64_t mask;
  size_t trip_bundle_size;
  ptrdiff_t flowhead, flowbase, tubeidx;
  uintptr_t bucket_idx;
  uint8_t *tube_key, *tube_ctx;
  uint32_t* tube_ctxsize;
  uint32_t ctxsize;
  uint64_t* tube_hashed_key;
  uint8_t* restrict buckets;

  table = funnel->table;
  buckets = OPRef2Ptr(table, table->bucket_ref);
  getcb = funnel->callback.getcb;

  // hash table is too small for using funnel
  if (!funnel->tubes)
    {
      if (HTPreHashSearchIdx(table,
                             hashed_key,
                             key,
                             &bucket_idx))
        {
          if (getcb)
            getcb(&buckets[bucket_idx * bucket_size + 1],
                  &buckets[bucket_idx * bucket_size + 1 + keysize],
                  context, keysize, valsize, ctxsize_st);
        }
      else
        {
          if (getcb)
            getcb(key, NULL, context, keysize, valsize, ctxsize_st);
        }
      return;
    }

  ctxsize = (uint32_t)ctxsize_st;
  mask = (1ULL << (64 - funnel->capacity_clz)) - 1;
  row_idx = (hashed_key & mask) >> funnel->partition_clz;
  flowhead = funnel->flowheads[row_idx];
  flowbase = row_idx * funnel->slotsize;
  trip_bundle_size = sizeof(hashed_key) + sizeof(uint32_t) + keysize + ctxsize;

  // flush funnel and call callback
  if (trip_bundle_size + flowhead - flowbase > funnel->slotsize)
    {
      tubeidx = flowbase;
      while (tubeidx < flowhead)
        {
          tube_hashed_key = (uint64_t*)&funnel->tubes[tubeidx];
          tubeidx += sizeof(uint64_t);
          tube_ctxsize = (uint32_t*)&funnel->tubes[tubeidx];
          tubeidx += sizeof(uint32_t);
          tube_key = &funnel->tubes[tubeidx];
          tubeidx += keysize;
          tube_ctx = &funnel->tubes[tubeidx];
          tubeidx += *tube_ctxsize;
          if (HTPreHashSearchIdx(table,
                                 *tube_hashed_key,
                                 tube_key,
                                 &bucket_idx))
            {
              if (getcb)
                getcb(&buckets[bucket_idx * bucket_size + 1],
                      &buckets[bucket_idx * bucket_size + 1 + keysize],
                      tube_ctx, keysize, valsize, *tube_ctxsize);
            }
          else
            {
              if (getcb)
                getcb(tube_key, NULL,
                      tube_ctx, keysize, valsize, *tube_ctxsize);
            }
        }
      funnel->flowheads[row_idx] = flowbase;
      flowhead = flowbase;
    }

  tubeidx = flowhead;
  memcpy(&funnel->tubes[tubeidx], &hashed_key, sizeof(uint64_t));
  tubeidx += sizeof(hashed_key);
  memcpy(&funnel->tubes[tubeidx], &ctxsize, sizeof(uint32_t));
  tubeidx += sizeof(uint32_t);
  memcpy(&funnel->tubes[tubeidx], key, keysize);
  tubeidx += keysize;
  memcpy(&funnel->tubes[tubeidx], context, ctxsize);
  tubeidx += ctxsize;
  funnel->flowheads[row_idx] = tubeidx;
}

void HTFunnelGetFlush(HTFunnel* funnel)
{
  const size_t keysize = funnel->table->keysize;
  const size_t valsize = funnel->table->valsize;
  const size_t bucket_size = keysize + valsize + 1;

  OPHashTable* table;
  OPFunnelGetCB getcb;
  int tube_num, row_idx;
  ptrdiff_t flowhead, tubeidx;
  uintptr_t bucket_idx;
  uint8_t *tube_key, *tube_ctx;
  uint32_t* tube_ctxsize;
  uint64_t* tube_hashed_key;
  uint8_t* restrict buckets;

  if (!funnel->tubes || !funnel->table)
    return;

  table = funnel->table;
  buckets = OPRef2Ptr(table, table->bucket_ref);
  getcb = funnel->callback.getcb;
  tube_num = 1 << (funnel->partition_clz - funnel->capacity_clz);

  for (row_idx = 0; row_idx < tube_num; row_idx++)
    {
      tubeidx = row_idx * funnel->slotsize;
      flowhead = funnel->flowheads[row_idx];
      while (tubeidx < flowhead)
        {
          tube_hashed_key = (uint64_t*)&funnel->tubes[tubeidx];
          tubeidx += sizeof(uint64_t);
          tube_ctxsize = (uint32_t*)&funnel->tubes[tubeidx];
          tubeidx += sizeof(uint32_t);
          tube_key = &funnel->tubes[tubeidx];
          tubeidx += keysize;
          tube_ctx = &funnel->tubes[tubeidx];
          tubeidx += *tube_ctxsize;
          if (HTPreHashSearchIdx(table,
                                 *tube_hashed_key,
                                 tube_key,
                                 &bucket_idx))
            {
              if (getcb)
                getcb(&buckets[bucket_idx * bucket_size + 1],
                      &buckets[bucket_idx * bucket_size + 1 + keysize],
                      tube_ctx, keysize, valsize, *tube_ctxsize);
            }
          else
            {
              if (getcb)
                getcb(tube_key, NULL,
                      tube_ctx, keysize, valsize, *tube_ctxsize);
            }
        }
      funnel->flowheads[row_idx] = row_idx * funnel->slotsize;
    }
}

void HTFunnelDelete(HTFunnel* funnel, void* key,
                    void* context, size_t ctxsize)
{
  uint64_t hashed_key;
  hashed_key = funnel->hasher(key, funnel->table->keysize);
  HTFunnelPreHashDelete(funnel, hashed_key, key, context, ctxsize);
}

void HTFunnelPreHashDelete(HTFunnel* funnel, uint64_t hashed_key,
                           void* key, void* context, size_t ctxsize_st)
{
  const size_t keysize = funnel->table->keysize;
  const size_t valsize = funnel->table->valsize;

  OPHashTable* table;
  OPFunnelDeleteCB deletecb;
  int row_idx;
  uint64_t mask;
  size_t trip_bundle_size;
  ptrdiff_t flowhead, flowbase, tubeidx;
  uint8_t *tube_key, *tube_ctx, *deleted_key, *deleted_val;
  uint32_t* tube_ctxsize;
  uint32_t ctxsize;
  uint64_t* tube_hashed_key;

  table = funnel->table;
  deletecb = funnel->callback.deletecb;

  // hash table is too small for using funnel
  if (!funnel->tubes)
    {
      deleted_val = HTPreHashDeleteCustom(table,
                                          funnel->hasher,
                                          hashed_key, key);
      if (deleted_val)
        {
          deleted_key = deleted_val - keysize;
          if (deletecb)
            deletecb(deleted_key, deleted_val,
                     context, keysize, valsize, ctxsize_st);
        }
      else
        {
          if (deletecb)
            deletecb(key, NULL, context, keysize, valsize, ctxsize_st);
        }
      return;
    }

  ctxsize = (uint32_t)ctxsize_st;
  mask = (1ULL << (64 - funnel->capacity_clz)) - 1;
  row_idx = (hashed_key & mask) >> funnel->partition_clz;
  flowhead = funnel->flowheads[row_idx];
  flowbase = row_idx * funnel->slotsize;
  trip_bundle_size = sizeof(hashed_key) + sizeof(uint32_t) + keysize + ctxsize;

  // flush funnel and call callback
  if (trip_bundle_size + flowhead - flowbase > funnel->slotsize)
    {
      tubeidx = flowbase;
      while (tubeidx < flowhead)
        {
          tube_hashed_key = (uint64_t*)&funnel->tubes[tubeidx];
          tubeidx += sizeof(uint64_t);
          tube_ctxsize = (uint32_t*)&funnel->tubes[tubeidx];
          tubeidx += sizeof(uint32_t);
          tube_key = &funnel->tubes[tubeidx];
          tubeidx += keysize;
          tube_ctx = &funnel->tubes[tubeidx];
          tubeidx += *tube_ctxsize;
          deleted_val = HTPreHashDeleteCustom(table,
                                              funnel->hasher,
                                              *tube_hashed_key, tube_key);
          if (deleted_val)
            {
              deleted_key = deleted_val - keysize;
              if (deletecb)
                deletecb(deleted_key, deleted_val,
                         tube_ctx, keysize, valsize, *tube_ctxsize);
            }
          else
            {
              if (deletecb)
                deletecb(tube_key, NULL,
                         tube_ctx, keysize, valsize, *tube_ctxsize);
            }
        }
      funnel->flowheads[row_idx] = flowbase;
      flowhead = flowbase;
    }

  tubeidx = flowhead;
  memcpy(&funnel->tubes[tubeidx], &hashed_key, sizeof(uint64_t));
  tubeidx += sizeof(hashed_key);
  memcpy(&funnel->tubes[tubeidx], &ctxsize, sizeof(uint32_t));
  tubeidx += sizeof(uint32_t);
  memcpy(&funnel->tubes[tubeidx], key, keysize);
  tubeidx += keysize;
  memcpy(&funnel->tubes[tubeidx], context, ctxsize);
  tubeidx += ctxsize;
  funnel->flowheads[row_idx] = tubeidx;
}

void HTFunnelDeleteFlush(HTFunnel* funnel)
{
  const size_t keysize = funnel->table->keysize;
  const size_t valsize = funnel->table->valsize;

  OPHashTable* table;
  OPFunnelDeleteCB deletecb;
  int tube_num, row_idx;
  ptrdiff_t flowhead, tubeidx;
  uint8_t *tube_key, *tube_ctx, *deleted_key, *deleted_val;
  uint32_t* tube_ctxsize;
  uint64_t* tube_hashed_key;

  if (!funnel->tubes || !funnel->table)
    return;

  table = funnel->table;
  deletecb = funnel->callback.deletecb;
  tube_num = 1 << (funnel->partition_clz - funnel->capacity_clz);

  for (row_idx = 0; row_idx < tube_num; row_idx++)
    {
      tubeidx = row_idx * funnel->slotsize;
      flowhead = funnel->flowheads[row_idx];
      while (tubeidx < flowhead)
        {
          tube_hashed_key = (uint64_t*)&funnel->tubes[tubeidx];
          tubeidx += sizeof(uint64_t);
          tube_ctxsize = (uint32_t*)&funnel->tubes[tubeidx];
          tubeidx += sizeof(uint32_t);
          tube_key = &funnel->tubes[tubeidx];
          tubeidx += keysize;
          tube_ctx = &funnel->tubes[tubeidx];
          tubeidx += *tube_ctxsize;
          deleted_val = HTPreHashDeleteCustom(table,
                                              funnel->hasher,
                                              *tube_hashed_key, tube_key);
          if (deleted_val)
            {
              deleted_key = deleted_val - keysize;
              if (deletecb)
                deletecb(deleted_key, deleted_val,
                         tube_ctx, keysize, valsize, *tube_ctxsize);
            }
          else
            {
              if (deletecb)
                deletecb(tube_key, NULL,
                         tube_ctx, keysize, valsize, *tube_ctxsize);
            }
        }
      funnel->flowheads[row_idx] = row_idx * funnel->slotsize;
    }
}

/* op_hash_table.c ends here */
