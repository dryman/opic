/* robin_hood.c ---
 *
 * Filename: robin_hood.c
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
#include "robin_hood.h"

#define PROBE_STATS_SIZE 64
#define DEFAULT_LARGE_DATA_THRESHOLD (1UL << 30)
#define VISIT_IDX_CACHE 8

OP_LOGGER_FACTORY(logger, "opic.hash.robin_hood");

enum upsert_result_t
  {
    UPSERT_EMPTY,
    UPSERT_DUP,
    UPSERT_PUSHDOWN,
  };

static inline enum upsert_result_t
RHHUpsertNewKey(RobinHoodHash* rhh, OPHash hasher,
                uint64_t hashed_key,
                void* key,
                uint8_t** matched_bucket,
                int* probe_state);

static inline void
RHHUpsertPushDown(RobinHoodHash* rhh, OPHash hasher,
                  uint8_t* bucket_cpy, int probe,
                  uint8_t* avoid_bucket, bool* resize);

static bool RHHSizeUp(RobinHoodHash* rhh, OPHash hasher);

struct RobinHoodHash
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

struct RHHFunnel
{
  RobinHoodHash* rhh;
  OPHash hasher;
  FunnelCB callback;
  size_t slotsize;
  uint8_t capacity_clz;
  uint8_t partition_clz;
  uint8_t* tubes;
  ptrdiff_t* flowheads;
};

bool
RHHNew(OPHeap* heap, RobinHoodHash** rhh,
       uint64_t num_objects, double load, size_t keysize, size_t valsize)
{
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
  capacity = (uint64_t)capacity_ms4b << (capacity_msb - 4);

  bucket_size = keysize + valsize + 1;

  *rhh = OPCalloc(heap, 1, sizeof(RobinHoodHash));
  if (!*rhh)
    return false;
  bucket_ptr = OPCalloc(heap, 1, bucket_size * capacity);
  if (!bucket_ptr)
    {
      OPDealloc(rhh);
      return false;
    }
  (*rhh)->bucket_ref = OPPtr2Ref(bucket_ptr);
  (*rhh)->large_data_threshold = DEFAULT_LARGE_DATA_THRESHOLD;
  (*rhh)->capacity_clz = capacity_clz;
  (*rhh)->capacity_ms4b = capacity_ms4b;
  (*rhh)->objcnt_high = (uint64_t)(capacity * load);
  (*rhh)->objcnt_low = capacity * 2 / 10;
  (*rhh)->keysize = keysize;
  (*rhh)->valsize = valsize;
  return true;
}

void
RHHDestroy(RobinHoodHash* rhh)
{
  OPDealloc(OPRef2Ptr(rhh, rhh->bucket_ref));
  OPDealloc(rhh);
}

uint64_t RHHObjcnt(RobinHoodHash* rhh)
{
  return rhh->objcnt;
}

static inline
uint64_t RHHCapacityInternal(uint8_t capacity_clz, uint8_t capacity_ms4b)
{
  return (1UL << (64 - capacity_clz - 4)) * capacity_ms4b;
}

uint64_t RHHCapacity(RobinHoodHash* rhh)
{
  return RHHCapacityInternal(rhh->capacity_clz, rhh->capacity_ms4b);
}

size_t RHHKeysize(RobinHoodHash* rhh)
{
  return rhh->keysize;
}

size_t RHHValsize(RobinHoodHash* rhh)
{
  return rhh->valsize;
}

static inline uintptr_t
hash_with_probe(RobinHoodHash* rhh, uint64_t key, int probe)
{
  uint64_t mask = (1ULL << (64 - rhh->capacity_clz)) - 1;

  // These probing methods are just for experiments.
  // They work on insertion and querying, but not deletion.
  // Only the quadratic probing is supported for all operation.
  // It is also the fastest probing strategry I find so far.

  // Linear probing
  // Under high load, linear probe can increase up to 50.
  // The high probe number makes both insert and query slow.
  // uint64_t probed_hash = key + probe * 2;

  // Quadratic probing
  uint64_t probed_hash = key + probe * probe * 2;

  // Double hashing
  // double hashing gives good probe distribution, but lacking
  // the cache locality makes it slower than both quadratic probing
  // and linear probing.
  // uint64_t up32key = key >> 32;
  // uint64_t probed_hash = key + up32key * probe;

  // Fast mod and scale
  // This is mod next power of two, times a number between 8 and 15
  // then devide by 16. This gives us fast division on non power of
  // two table size.
  // Both linear probing and quadratic probing needs to double the
  // probe sequence because the scaling part of this algorithm has
  // some probability to trim off the last bit in the probed hash.
  return (probed_hash & mask) * rhh->capacity_ms4b >> 4;
}

static inline int
findprobe(RobinHoodHash* rhh, OPHash hasher, uintptr_t idx)
{
  const size_t keysize = rhh->keysize;
  const size_t valsize = rhh->valsize;
  const size_t bucket_size = keysize + valsize + 1;
  uint8_t* const buckets = OPRef2Ptr(rhh, rhh->bucket_ref);
  uint64_t hashed_key;

  hashed_key = hasher(&buckets[idx*bucket_size + 1], keysize);
  for (int i = 0; i <= rhh->longest_probes; i++)
    {
      if (hash_with_probe(rhh, hashed_key, i) == idx)
        return i;
    }
  OP_LOG_ERROR(logger, "Didn't find any match probe!\n");
  return -1;
}

static inline void
IncreaseProbeStat(RobinHoodHash* rhh, int probe)
{
  rhh->objcnt++;
  rhh->longest_probes = probe > rhh->longest_probes ?
    probe : rhh->longest_probes;
  rhh->stats[probe]++;
}

static inline enum upsert_result_t
RHHUpsertNewKey(RobinHoodHash* rhh, OPHash hasher,
                uint64_t hashed_key,
                void* key,
                uint8_t** matched_bucket, int* probe_state)
{
  const size_t keysize = rhh->keysize;
  const size_t valsize = rhh->valsize;
  const size_t bucket_size = keysize + valsize + 1;
  uint8_t* buckets;
  int probe, old_probe;
  uintptr_t idx, _idx;

  buckets = OPRef2Ptr(rhh, rhh->bucket_ref);
  probe = 0;

  while (true)
    {
      idx = hash_with_probe(rhh, hashed_key, probe);
      if (probe > PROBE_STATS_SIZE)
        {
          RHHSizeUp(rhh, hasher);
          probe = 0;
          buckets = OPRef2Ptr(rhh, rhh->bucket_ref);
          continue;
        }
      if (buckets[idx * bucket_size] == 0)
        {
          IncreaseProbeStat(rhh, probe);
          *matched_bucket = &buckets[idx * bucket_size];
          return UPSERT_EMPTY;
        }
      else if (buckets[idx * bucket_size] == 2)
        {
          for (int p = probe+1; p <= rhh->longest_probes; p++)
            {
              _idx = hash_with_probe(rhh, hashed_key, p);
              if (buckets[_idx * bucket_size] != 1)
                continue;
              if (!memcmp(key, &buckets[_idx * bucket_size + 1], bucket_size))
                {
                  *matched_bucket = &buckets[_idx * bucket_size];
                  return UPSERT_DUP;
                }
            }
          IncreaseProbeStat(rhh, probe);
          *matched_bucket = &buckets[idx * bucket_size];
          return UPSERT_EMPTY;
        }
      if (!memcmp(key, &buckets[idx * bucket_size + 1], keysize))
        {
          *matched_bucket = &buckets[idx * bucket_size];
          return UPSERT_DUP;
        }
      old_probe = findprobe(rhh, hasher, idx);
      if (probe > old_probe)
        {
          rhh->longest_probes = probe > rhh->longest_probes ?
            probe : rhh->longest_probes;
          rhh->stats[old_probe]--;
          rhh->stats[probe]++;
          *matched_bucket = &buckets[idx * bucket_size];
          *probe_state = old_probe+1;
          return UPSERT_PUSHDOWN;
        }
      probe++;
    }
}

static inline void
RHHUpsertPushDown(RobinHoodHash* rhh, OPHash hasher,
                  uint8_t* bucket_cpy, int probe, uint8_t* avoid_bucket,
                  bool* resized)
{
  const size_t keysize = rhh->keysize;
  const size_t valsize = rhh->valsize;
  const size_t bucket_size = keysize + valsize + 1;
  uint8_t* buckets;
  int old_probe;
  uint8_t bucket_tmp[bucket_size];
  uintptr_t idx;
  uint64_t hashed_key, iter, capacity;
  int visit;
  uintptr_t visited_idx[VISIT_IDX_CACHE];

  visit = 0;
  *resized = false;
  hashed_key = hasher(&bucket_cpy[1], keysize);
  buckets = OPRef2Ptr(rhh, rhh->bucket_ref);
  capacity = RHHCapacity(rhh);
  iter = 0;

  while (true)
    {
    next_iter:
      iter++;
      idx = hash_with_probe(rhh, hashed_key, probe);

      if (iter > capacity)
        {
          RHHSizeUp(rhh, hasher);
          capacity = RHHCapacity(rhh);
          iter = 0;
          probe = 0;
          buckets = OPRef2Ptr(rhh, rhh->bucket_ref);
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
          IncreaseProbeStat(rhh, probe);
          memcpy(&buckets[idx * bucket_size], bucket_cpy, bucket_size);
          return;
        }

      old_probe = findprobe(rhh, hasher, idx);
      if (probe > old_probe)
        {
          rhh->longest_probes = probe > rhh->longest_probes ?
            probe : rhh->longest_probes;
          rhh->stats[old_probe]--;
          rhh->stats[probe]++;
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
RHHSizeUp(RobinHoodHash* rhh, OPHash hasher)
{
  const size_t keysize = rhh->keysize;
  const size_t valsize = rhh->valsize;
  const size_t bucket_size = keysize + valsize + 1;
  const size_t large_data_threshold = rhh->large_data_threshold;
  uint8_t* old_buckets;
  uint8_t* new_buckets;
  uint8_t new_capacity_ms4b, new_capacity_clz;
  uint64_t old_capacity, new_capacity;
  bool resized;

  old_capacity = RHHCapacity(rhh);
  old_buckets = OPRef2Ptr(rhh, rhh->bucket_ref);

  if (old_capacity * bucket_size >= large_data_threshold)
    {
      // increase size by 20% ~ 33%
      switch(rhh->capacity_ms4b)
        {
        case 8:
          new_capacity_ms4b = 10;
          new_capacity_clz = rhh->capacity_clz;
          break;
        case 9:
        case 10:
          new_capacity_ms4b = 12;
          new_capacity_clz = rhh->capacity_clz;
          break;
        case 11:
        case 12:
          new_capacity_ms4b = 14;
          new_capacity_clz = rhh->capacity_clz;
          break;
        case 13:
        case 14:
          new_capacity_ms4b = 8;
          new_capacity_clz = rhh->capacity_clz - 1;
          break;
        case 15:
          new_capacity_ms4b = 10;
          new_capacity_clz = rhh->capacity_clz - 1;
          break;
        default: op_assert(false, "Unknown capacity_ms4b %d\n",
                           rhh->capacity_ms4b);
        }
    }
  else
    {
      new_capacity_ms4b = 8;
      new_capacity_clz = rhh->capacity_ms4b == 8 ?
        rhh->capacity_clz - 1 : rhh->capacity_clz - 2;
    }
  new_capacity = RHHCapacityInternal(new_capacity_clz, new_capacity_ms4b);
  OP_LOG_INFO(logger, "Resize from %" PRIu64 " to %" PRIu64,
              old_capacity, new_capacity);

  new_buckets = OPCalloc(ObtainOPHeap(rhh), 1, bucket_size * new_capacity);
  if (!new_buckets)
    {
      OP_LOG_ERROR(logger, "Cannot obtain new bucket for size %" PRIu64,
                   new_capacity);
      return false;
    }

  rhh->objcnt = 0;
  rhh->objcnt_high = new_capacity * 8 / 10;
  rhh->objcnt_low = new_capacity * 2 / 10;
  rhh->capacity_clz = new_capacity_clz;
  rhh->capacity_ms4b = new_capacity_ms4b;
  rhh->longest_probes = 0;
  memset(rhh->stats, 0x00, sizeof(uint32_t) * PROBE_STATS_SIZE);
  rhh->bucket_ref = OPPtr2Ref(new_buckets);

  for (uint64_t idx = 0; idx < old_capacity; idx++)
    {
      if (old_buckets[idx*bucket_size] == 1)
        {
          RHHUpsertPushDown(rhh, hasher, &old_buckets[idx * bucket_size],
                            0, NULL, &resized);
        }
    }
  OPDealloc(old_buckets);
  return true;
}

static bool
RHHSizeDown(RobinHoodHash* rhh, OPHash hasher)
{
  const size_t keysize = rhh->keysize;
  const size_t valsize = rhh->valsize;
  const size_t bucket_size = keysize + valsize + 1;
  uint8_t* old_buckets;
  uint8_t* new_buckets;
  uint8_t new_capacity_ms4b, new_capacity_clz;
  uint64_t old_capacity, new_capacity;
  bool resized;

  old_capacity = RHHCapacity(rhh);
  old_buckets = OPRef2Ptr(rhh, rhh->bucket_ref);
  op_assert(old_capacity > 16,
            "Can not resize smaller than 16, but got old_capacity %"
            PRIu64 "\n", old_capacity);

  switch(rhh->capacity_ms4b)
    {
    case 8:  // new load 0.45
    case 9:  // new load 0.50
    case 10: // new load 0.55
    case 11: // new load 0.60
      new_capacity_ms4b = 8;
      new_capacity_clz = rhh->capacity_clz + 1;
      break;
    case 12: // new load 0.40
    case 13: // new load 0.43
    case 14: // new load 0.46
    case 15: // new load 0.50
      new_capacity_ms4b = 12;
      new_capacity_clz = rhh->capacity_clz + 1;
      break;
    default: op_assert(false, "Unknown capacity_ms4b %d\n",
                       rhh->capacity_ms4b);
    }

  new_capacity = RHHCapacityInternal(new_capacity_clz, new_capacity_ms4b);
  OP_LOG_INFO(logger, "Resize from %" PRIu64 " to %" PRIu64,
              old_capacity, new_capacity);
  new_buckets = OPCalloc(ObtainOPHeap(rhh), 1, bucket_size * new_capacity);
  if (!new_buckets)
    {
      OP_LOG_ERROR(logger, "Cannot obtain new bucket for size %" PRIu64,
                   new_capacity);
      return false;
    }

  rhh->objcnt = 0;
  rhh->objcnt_high = new_capacity * 8 / 10;
  rhh->objcnt_low = new_capacity * 2 / 10;
  rhh->capacity_clz = new_capacity_clz;
  rhh->capacity_ms4b = new_capacity_ms4b;
  rhh->longest_probes = 0;
  memset(rhh->stats, 0x00, sizeof(uint32_t) * PROBE_STATS_SIZE);
  rhh->bucket_ref = OPPtr2Ref(new_buckets);

  for (uint64_t idx = 0; idx < old_capacity; idx++)
    {
      if (old_buckets[idx*bucket_size] == 1)
        {
          RHHUpsertPushDown(rhh, hasher, &old_buckets[idx * bucket_size],
                            0, NULL, &resized);
        }
    }
  OPDealloc(old_buckets);
  return true;
}

static inline
bool RHHPreHashInsertCustom(RobinHoodHash* rhh, OPHash hasher,
                            uint64_t hashed_key, void* key, void* val)
{
  const size_t keysize = rhh->keysize;
  const size_t valsize = rhh->valsize;
  const size_t bucket_size = keysize + valsize + 1;
  enum upsert_result_t upsert_result;
  uint8_t* matched_bucket;
  int probe;
  uint8_t bucket_cpy[bucket_size];
  bool resized;

  if (rhh->objcnt > rhh->objcnt_high)
    {
      if(!RHHSizeUp(rhh, hasher))
        return false;
    }

  upsert_result = RHHUpsertNewKey(rhh, hasher, hashed_key, key,
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
      RHHUpsertPushDown(rhh, hasher, bucket_cpy, probe,
                        matched_bucket, &resized);
    }
  return true;
}

bool RHHInsertCustom(RobinHoodHash* rhh, OPHash hasher, void* key, void* val)
{
  uint64_t hashed_key;
  hashed_key = hasher(key, rhh->keysize);
  return RHHPreHashInsertCustom(rhh, hasher, hashed_key, key, val);
}

bool RHHUpsertCustom(RobinHoodHash* rhh, OPHash hasher,
                     void* key, void** val_ref, bool* is_duplicate)
{
  const size_t keysize = rhh->keysize;
  const size_t valsize = rhh->valsize;
  const size_t bucket_size = keysize + valsize + 1;
  enum upsert_result_t upsert_result;
  uint64_t hashed_key;
  uint8_t* matched_bucket;
  int probe;
  uint8_t bucket_cpy[bucket_size];
  bool resized;

  if (rhh->objcnt > rhh->objcnt_high)
    {
      if (!RHHSizeUp(rhh, hasher))
        return false;
    }

  hashed_key = hasher(key, keysize);
  upsert_result = RHHUpsertNewKey(rhh, hasher, hashed_key, key,
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
      RHHUpsertPushDown(rhh, hasher, bucket_cpy, probe,
                        matched_bucket, &resized);
      if (resized)
        {
          *val_ref = RHHGetCustom(rhh, hasher, key);
        }
    }
  return true;
}

static inline bool
RHHPreHashSearchIdx(RobinHoodHash* rhh, uint64_t hashed_key,
                    void* key, uintptr_t* idx)
{
  const size_t keysize = rhh->keysize;
  const size_t valsize = rhh->valsize;
  const size_t bucket_size = keysize + valsize + 1;
  uint8_t* const buckets = OPRef2Ptr(rhh, rhh->bucket_ref);

  for (int probe = 0; probe <= rhh->longest_probes; probe++)
    {
      *idx = hash_with_probe(rhh, hashed_key, probe);
      switch(buckets[*idx*bucket_size])
        {
        case 0: return false;
        case 2: continue;
        default: (void)0;
        }
      if (!memcmp(key, &buckets[*idx*bucket_size + 1], keysize))
        return true;
    }
  return false;
}

static inline bool
RHHSearchIdx(RobinHoodHash* rhh, OPHash hasher, void* key, uintptr_t* idx)
{
  const size_t keysize = rhh->keysize;
  uint64_t hashed_key;
  hashed_key = hasher(key, keysize);
  return RHHPreHashSearchIdx(rhh, hashed_key, key, idx);
}

void* RHHGetCustom(RobinHoodHash* rhh, OPHash hasher, void* key)
{
  const size_t keysize = rhh->keysize;
  const size_t valsize = rhh->valsize;
  const size_t bucket_size = keysize + valsize + 1;
  uint8_t* const buckets = OPRef2Ptr(rhh, rhh->bucket_ref);
  uintptr_t idx;
  if (RHHSearchIdx(rhh, hasher, key, &idx))
    {
      return &buckets[idx*bucket_size + keysize + 1];
    }
  return NULL;
}

static inline void*
RHHPreHashDeleteCustom(RobinHoodHash* rhh, OPHash hasher,
                       uint64_t hashed_key, void* key)
{
  /*
   * This works for load that is not super high, i.e. < 0.9.
   * It slows down the growth for both E[psl] and Var[psl], but only
   * slows down, not bounding it.
   */
  const size_t keysize = rhh->keysize;
  const size_t valsize = rhh->valsize;
  const size_t bucket_size = keysize + valsize + 1;
  uint8_t* buckets;
  uintptr_t idx, premod_idx, candidate_idx;
  uintptr_t mask;
  int candidates;
  int record_probe;
  uint8_t bucket_tmp[bucket_size];

  if (rhh->objcnt < rhh->objcnt_low &&
      rhh->objcnt > 16)
    {
      if (!RHHSizeDown(rhh, hasher))
        return NULL;
    }

  if (!RHHPreHashSearchIdx(rhh, hashed_key, key, &idx))
    return NULL;

  buckets = OPRef2Ptr(rhh, rhh->bucket_ref);
  mask = (1ULL << (64 - rhh->capacity_clz)) - 1;

  rhh->objcnt--;
  record_probe = findprobe(rhh, hasher, idx);
  if (record_probe < PROBE_STATS_SIZE)
    rhh->stats[record_probe]--;
  else
    OP_LOG_WARN(logger, "Large probe: %d\n", record_probe);

  if (record_probe == rhh->longest_probes &&
      rhh->stats[record_probe] == 0)
    {
      rhh->longest_probes--;
    }

  while (true)
    {
    next_iter:
      if (record_probe == 0)
        goto end_iter;
      switch (rhh->capacity_ms4b)
        {
        case 8: premod_idx =  round_up_div(16*idx, 8); break;
        case 9: premod_idx =  round_up_div(16*idx, 9); break;
        case 10: premod_idx = round_up_div(16*idx, 10); break;
        case 11: premod_idx = round_up_div(16*idx, 11); break;
        case 12: premod_idx = round_up_div(16*idx, 12); break;
        case 13: premod_idx = round_up_div(16*idx, 13); break;
        case 14: premod_idx = round_up_div(16*idx, 14); break;
        case 15: premod_idx = round_up_div(16*idx, 15); break;
        default: op_assert(false, "Unknown capacity_ms4b %d\n",
                           rhh->capacity_ms4b);
        }
      candidates = (((premod_idx + 1) & mask) * rhh->capacity_ms4b >> 4)
        == idx ? 2 : 1;
      for (int probe = rhh->longest_probes - 1;
           probe > 0; probe--)
        {
          for (int candidate = 0; candidate < candidates; candidate++)
            {
              candidate_idx =
                ((premod_idx + candidate + (probe + 1)*(probe + 1)*2
                  - probe*probe*2) & mask) * rhh->capacity_ms4b >> 4;
              if (buckets[candidate_idx * bucket_size] == 1 &&
                  hash_with_probe(rhh,
                                  hasher(&buckets[candidate_idx*bucket_size+1],
                                         keysize),
                                  probe + 1) == candidate_idx &&
                  hash_with_probe(rhh,
                                  hasher(&buckets[candidate_idx*bucket_size+1],
                                         keysize),
                                  probe) == idx)
                {
                  if (probe + 1 < PROBE_STATS_SIZE)
                    rhh->stats[probe + 1]--;
                  if (probe < PROBE_STATS_SIZE)
                    rhh->stats[probe]++;
                  else
                    OP_LOG_WARN(logger, "Large probe: %d\n", probe);
                  if (probe + 1 == rhh->longest_probes &&
                      rhh->stats[probe+1] == 0)
                    {
                      rhh->longest_probes--;
                    }
                  memcpy(bucket_tmp, &buckets[idx * bucket_size], bucket_size);
                  memcpy(&buckets[idx*bucket_size],
                         &buckets[candidate_idx*bucket_size],
                         bucket_size);
                  memcpy(&buckets[candidate_idx * bucket_size],
                         bucket_tmp, bucket_size);
                  idx = candidate_idx;
                  record_probe--;
                  goto next_iter;
                }
            }
        }
      goto end_iter;
    }

 end_iter:
  buckets[idx*bucket_size] = 2;
  return &buckets[idx*bucket_size + 1 + keysize];
}

void* RHHDeleteCustom(RobinHoodHash* rhh, OPHash hasher, void* key)
{
  uint64_t hashed_key;
  hashed_key = hasher(key, rhh->keysize);
  return RHHPreHashDeleteCustom(rhh, hasher, hashed_key, key);
}

void RHHIterate(RobinHoodHash* rhh, OPHashIterator iterator, void* context)
{
  const size_t keysize = rhh->keysize;
  const size_t valsize = rhh->valsize;
  const size_t bucket_size = keysize + valsize + 1;
  uint8_t* const buckets = OPRef2Ptr(rhh, rhh->bucket_ref);
  uint64_t capacity = RHHCapacity(rhh);

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

void RHHPrintStat(RobinHoodHash* rhh)
{
  for (int i = 0; i < PROBE_STATS_SIZE; i++)
    if (rhh->stats[i])
      printf("probe %02d: %d\n", i, rhh->stats[i]);
}

RHHFunnel* RHHFunnelNewCustom(RobinHoodHash* rhh, OPHash hasher,
                              FunnelCB callback,
                              size_t slotsize, size_t partition_size)
{
  RHHFunnel* funnel;
  size_t bucketsize;
  int tube_num;

  funnel = malloc(sizeof(RHHFunnel));
  bucketsize = rhh->keysize + rhh->valsize + 1;
  funnel->rhh = rhh;
  funnel->hasher = hasher;
  funnel->callback = callback;
  funnel->slotsize = slotsize;
  funnel->partition_clz = __builtin_clzll(partition_size / bucketsize);
  funnel->capacity_clz = 0;
  funnel->tubes = NULL;
  funnel->flowheads = NULL;
  if (funnel->partition_clz > rhh->capacity_clz)
    {
      funnel->capacity_clz = rhh->capacity_clz;
      tube_num = 1 << (funnel->partition_clz - funnel->capacity_clz);
      funnel->tubes = malloc(tube_num * slotsize);
      funnel->flowheads = malloc(tube_num * sizeof(ptrdiff_t*));
      for (int i = 0; i < tube_num; i++)
        funnel->flowheads[i] = i * funnel->slotsize;
    }
  return funnel;
}

void RHHFunnelDestroy(RHHFunnel* funnel)
{
  if (!funnel)
    return;

  if (funnel->tubes)
    free(funnel->tubes);
  if (funnel->flowheads)
    free(funnel->flowheads);
  free(funnel);
}

void RHHFunnelPreHashInsert(RHHFunnel* funnel,
                            uint64_t hashed_key,
                            void* key, void* value)
{
  const size_t keysize = funnel->rhh->keysize;
  const size_t valsize = funnel->rhh->valsize;
  const size_t bucket_size = keysize + valsize + 1;
  const size_t trip_bundle_size = sizeof(hashed_key) + keysize + valsize;

  RobinHoodHash* rhh;
  int tube_num, old_tube_num, row_idx, probe;
  uint64_t mask;
  ptrdiff_t flowhead, flowbase, tubeidx;
  ptrdiff_t* old_flowheads;
  uint8_t *old_tubes, *tube_key, *tube_val, *matched_bucket;
  uint64_t* tube_hashed_key;
  bool resized;
  enum upsert_result_t upsert_result;
  uint8_t bucket_cpy[bucket_size];

  rhh = funnel->rhh;

  if (funnel->capacity_clz != rhh->capacity_clz)
    {
      if (funnel->capacity_clz == 0)
        {
          // If the capacity of the hash table is smaller than
          // partitions, simply insert the items into the hash table.
          // Otherwise, initialize the funnels.
          if (funnel->partition_clz > rhh->capacity_clz)
            {
              funnel->capacity_clz = rhh->capacity_clz;
              tube_num = 1 << (funnel->partition_clz - funnel->capacity_clz);
              funnel->tubes = malloc(tube_num * funnel->slotsize);
              funnel->flowheads = malloc(tube_num * sizeof(ptrdiff_t*));
              for (row_idx = 0; row_idx < tube_num; row_idx++)
                funnel->flowheads[row_idx] = row_idx * funnel->slotsize;
            }
          else
            {
              RHHPreHashInsertCustom(rhh, funnel->hasher,
                                     hashed_key, key, value);
              return;
            }
        }
      else
        {
          old_tube_num = 1 << (funnel->partition_clz - funnel->capacity_clz);
          old_tubes = funnel->tubes;
          old_flowheads = funnel->flowheads;

          funnel->capacity_clz = rhh->capacity_clz;
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
                  RHHFunnelPreHashInsert(funnel,
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

          upsert_result = RHHUpsertNewKey(rhh, funnel->hasher,
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
              RHHUpsertPushDown(rhh, funnel->hasher, bucket_cpy, probe,
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

void RHHFunnelInsert(RHHFunnel* funnel,
                     void* key, void* value)
{
  uint64_t hashed_key;
  hashed_key = funnel->hasher(key, funnel->rhh->keysize);
  RHHFunnelPreHashInsert(funnel, hashed_key, key, value);
}

void RHHFunnelInsertFlush(RHHFunnel* funnel)
{
  const size_t keysize = funnel->rhh->keysize;
  const size_t valsize = funnel->rhh->valsize;
  const size_t bucket_size = keysize + valsize + 1;

  RobinHoodHash* rhh;
  int tube_num, row_idx, probe;
  ptrdiff_t flowhead, tubeidx;
  uint8_t *tube_key, *tube_val, *matched_bucket;
  uint64_t* tube_hashed_key;
  bool resized;
  enum upsert_result_t upsert_result;
  uint8_t bucket_cpy[bucket_size];

  if (!funnel->tubes || !funnel->rhh)
    return;

  rhh = funnel->rhh;
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

          upsert_result = RHHUpsertNewKey(rhh, funnel->hasher,
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
              RHHUpsertPushDown(rhh, funnel->hasher, bucket_cpy, probe,
                                matched_bucket, &resized);
            }
        }
      funnel->flowheads[row_idx] = row_idx * funnel->slotsize;
    }
}

void RHHFunnelPreHashUpsert(RHHFunnel* funnel,
                            uint64_t hashed_key,
                            void* key, void* value,
                            void* context, size_t ctxsize_st)
{
  const size_t keysize = funnel->rhh->keysize;
  const size_t valsize = funnel->rhh->valsize;
  const size_t bucket_size = keysize + valsize + 1;

  size_t trip_bundle_size;
  RobinHoodHash* rhh;
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

  rhh = funnel->rhh;
  upsertcb = funnel->callback.upsertcb;
  ctxsize = (uint32_t)ctxsize_st;

  if (funnel->capacity_clz != rhh->capacity_clz)
    {
      if (funnel->capacity_clz == 0)
        {
          // If the capacity of the hash table is smaller than
          // partitions, simply insert the items into the hash table.
          // Otherwise, initialize the funnels.
          if (funnel->partition_clz > rhh->capacity_clz)
            {
              funnel->capacity_clz = rhh->capacity_clz;
              tube_num = 1 << (funnel->partition_clz - funnel->capacity_clz);
              funnel->tubes = malloc(tube_num * funnel->slotsize);
              funnel->flowheads = malloc(tube_num * sizeof(ptrdiff_t*));
              for (row_idx = 0; row_idx < tube_num; row_idx++)
                funnel->flowheads[row_idx] = row_idx * funnel->slotsize;
            }
          else
            {
              RHHInsertCustom(rhh, funnel->hasher, key, value);
              upsert_result = RHHUpsertNewKey(rhh, funnel->hasher,
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
                  RHHUpsertPushDown(rhh, funnel->hasher, bucket_cpy, probe,
                                    matched_bucket, &resized);
                  // if resized, the matched bucket no longer point to correct
                  // address of the inserted bucket, we need to search for it
                  // again.
                  if (resized)
                    {
                      // reference to value
                      matched_bucket = RHHGetCustom(rhh, funnel->hasher, key);
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

          funnel->capacity_clz = rhh->capacity_clz;
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
                  upsert_result = RHHUpsertNewKey(rhh, funnel->hasher,
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
                      RHHUpsertPushDown(rhh, funnel->hasher, bucket_cpy, probe,
                                        matched_bucket, &resized);
                      if (resized)
                        {
                          // reference to value
                          matched_bucket = RHHGetCustom(rhh, funnel->hasher,
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
          upsert_result = RHHUpsertNewKey(rhh, funnel->hasher,
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
              RHHUpsertPushDown(rhh, funnel->hasher, bucket_cpy, probe,
                                matched_bucket, &resized);
              // if resized, the matched bucket no longer point to correct
              // address of the inserted bucket, we need to search for it again.
              if (resized)
                {
                  // reference to value
                  matched_bucket = RHHGetCustom(rhh, funnel->hasher, tube_key);
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

void RHHFunnelUpsert(RHHFunnel* funnel,
                     void* key, void* value, void* context, size_t ctxsize)
{
  uint64_t hashed_key;
  hashed_key = funnel->hasher(key, funnel->rhh->keysize);
  RHHFunnelPreHashUpsert(funnel, hashed_key, key, value, context, ctxsize);
}

void RHHFunnelUpsertFlush(RHHFunnel* funnel)
{
  const size_t keysize = funnel->rhh->keysize;
  const size_t valsize = funnel->rhh->valsize;
  const size_t bucket_size = keysize + valsize + 1;

  RobinHoodHash* rhh;
  OPFunnelUpsertCB upsertcb;
  int tube_num, row_idx, probe;
  ptrdiff_t flowhead, tubeidx;
  uint8_t *tube_key, *tube_val, *tube_ctx, *matched_bucket;
  uint32_t* tube_ctxsize;
  uint64_t* tube_hashed_key;
  bool resized;
  enum upsert_result_t upsert_result;
  uint8_t bucket_cpy[bucket_size];

  if (!funnel->tubes || !funnel->rhh)
    return;

  rhh = funnel->rhh;
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

          upsert_result = RHHUpsertNewKey(rhh, funnel->hasher,
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
              RHHUpsertPushDown(rhh, funnel->hasher, bucket_cpy, probe,
                                matched_bucket, &resized);
              // if resized, the matched bucket no longer point to correct
              // address of the inserted bucket, we need to search for it again.
              if (resized)
                {
                  // reference to value
                  matched_bucket = RHHGetCustom(rhh, funnel->hasher, tube_key);
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

void RHHFunnelGet(RHHFunnel* funnel, void* key, void* context, size_t ctxsize)
{
  uint64_t hashed_key;
  hashed_key = funnel->hasher(key, funnel->rhh->keysize);
  RHHFunnelPreHashGet(funnel, hashed_key, key, context, ctxsize);
}

void RHHFunnelPreHashGet(RHHFunnel* funnel, uint64_t hashed_key,
                         void* key, void* context, size_t ctxsize_st)
{
  const size_t keysize = funnel->rhh->keysize;
  const size_t valsize = funnel->rhh->valsize;
  const size_t bucket_size = keysize + valsize + 1;

  RobinHoodHash* rhh;
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
  uint8_t* buckets;

  rhh = funnel->rhh;
  buckets = OPRef2Ptr(rhh, rhh->bucket_ref);
  getcb = funnel->callback.getcb;

  // hash table is too small for using funnel
  if (!funnel->tubes)
    {
      if (RHHPreHashSearchIdx(rhh,
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
          if (RHHPreHashSearchIdx(rhh,
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

void RHHFunnelGetFlush(RHHFunnel* funnel)
{
  const size_t keysize = funnel->rhh->keysize;
  const size_t valsize = funnel->rhh->valsize;
  const size_t bucket_size = keysize + valsize + 1;

  RobinHoodHash* rhh;
  OPFunnelGetCB getcb;
  int tube_num, row_idx;
  ptrdiff_t flowhead, tubeidx;
  uintptr_t bucket_idx;
  uint8_t *tube_key, *tube_ctx;
  uint32_t* tube_ctxsize;
  uint64_t* tube_hashed_key;
  uint8_t* buckets;

  if (!funnel->tubes || !funnel->rhh)
    return;

  rhh = funnel->rhh;
  buckets = OPRef2Ptr(rhh, rhh->bucket_ref);
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
          if (RHHPreHashSearchIdx(rhh,
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

void RHHFunnelDelete(RHHFunnel* funnel, void* key,
                     void* context, size_t ctxsize)
{
  uint64_t hashed_key;
  hashed_key = funnel->hasher(key, funnel->rhh->keysize);
  RHHFunnelPreHashDelete(funnel, hashed_key, key, context, ctxsize);
}

void RHHFunnelPreHashDelete(RHHFunnel* funnel, uint64_t hashed_key,
                            void* key, void* context, size_t ctxsize_st)
{
  const size_t keysize = funnel->rhh->keysize;
  const size_t valsize = funnel->rhh->valsize;

  RobinHoodHash* rhh;
  OPFunnelDeleteCB deletecb;
  int row_idx;
  uint64_t mask;
  size_t trip_bundle_size;
  ptrdiff_t flowhead, flowbase, tubeidx;
  uint8_t *tube_key, *tube_ctx, *deleted_key, *deleted_val;
  uint32_t* tube_ctxsize;
  uint32_t ctxsize;
  uint64_t* tube_hashed_key;

  rhh = funnel->rhh;
  deletecb = funnel->callback.deletecb;

  // hash table is too small for using funnel
  if (!funnel->tubes)
    {
      deleted_val = RHHPreHashDeleteCustom(rhh,
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
          deleted_val = RHHPreHashDeleteCustom(rhh,
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

void RHHFunnelDeleteFlush(RHHFunnel* funnel)
{
  const size_t keysize = funnel->rhh->keysize;
  const size_t valsize = funnel->rhh->valsize;

  RobinHoodHash* rhh;
  OPFunnelDeleteCB deletecb;
  int tube_num, row_idx;
  ptrdiff_t flowhead, tubeidx;
  uint8_t *tube_key, *tube_ctx, *deleted_key, *deleted_val;
  uint32_t* tube_ctxsize;
  uint64_t* tube_hashed_key;

  if (!funnel->tubes || !funnel->rhh)
    return;

  rhh = funnel->rhh;
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
          deleted_val = RHHPreHashDeleteCustom(rhh,
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

/* robin_hood.c ends here */
