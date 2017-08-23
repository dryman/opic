/* pascal_hash_table.c ---
 *
 * Filename: pascal_hash_table.c
 * Description:
 * Author: Felix Chern
 * Maintainer:
 * Created: Sat May 13 15:57:42 2017 (-0700)
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
 * it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this program.  If not, see
 * <http://www.gnu.org/licenses/>.
 */

/* Code: */

#include <inttypes.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include "opic/common/op_assert.h"
#include "opic/common/op_utils.h"
#include "opic/common/op_log.h"
#include "opic/op_malloc.h"
#include "pascal_hash_table.h"

#define PROBE_STATS_SIZE 64
#define DEFAULT_LARGE_DATA_THRESHOLD (1UL << 30)
#define VISIT_IDX_CACHE 8

OP_LOGGER_FACTORY(logger, "opic.hash.pascal_hash_table");

enum upsert_result_t
  {
    UPSERT_EMPTY,
    UPSERT_DUP,
    UPSERT_PUSHDOWN,
  };

static inline enum upsert_result_t
PHUpsertNewKey(PascalHashTable* table, OPHash hasher,
               void* key, size_t keylen, uint64_t hashed_key,
               uint8_t** matched_bucket, int* probe_state);

static inline void
PHUpsertPushDown(PascalHashTable* table, OPHash hasher,
                 uint8_t* bucket_cpy, int probe,
                 uint8_t* avoid_bucket, bool* resize);

static bool
PHSizeUp(PascalHashTable* table, OPHash hasher);

struct PascalHashTable
{
  uint64_t objcnt;
  uint64_t objcnt_high;
  uint64_t objcnt_low;
  uint64_t large_data_threshold;
  uint8_t capacity_clz;    // leading zeros of capacity
  uint8_t capacity_ms4b;   // most significant 4 bits
  uint16_t longest_probes;
  size_t key_inline_size;
  size_t valsize;
  uint32_t stats[PROBE_STATS_SIZE];
  opref_t bucket_ref;
};

PascalHashTable*
PHNew(OPHeap* heap, uint64_t num_objects, double load,
      size_t key_inline_size, size_t valsize)
{
  PascalHashTable* table;
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

  bucket_size = sizeof(oplenref_t) + key_inline_size + valsize;

  table = OPCalloc(heap, 1, sizeof(PascalHashTable));
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
  table->key_inline_size = key_inline_size;
  table->valsize = valsize;
  return table;
}

void PHDestroy(PascalHashTable* table)
{
  const size_t key_inline_size = table->key_inline_size;
  const size_t valsize = table->valsize;
  const size_t bucket_size = sizeof(oplenref_t) + key_inline_size + valsize;
  uint8_t* const buckets = OPRef2Ptr(table, table->bucket_ref);
  oplenref_t* recref;
  uint64_t capacity = PHCapacity(table);

  for (uint64_t idx = 0; idx < capacity; idx++)
    {
      recref = (oplenref_t*)&buckets[idx * bucket_size];
      OPLenRefDelete(recref, key_inline_size);
    }
  OPDealloc(OPRef2Ptr(table, table->bucket_ref));
  OPDealloc(table);
}

uint64_t PHObjcnt(PascalHashTable* table)
{
  return table->objcnt;
}

static inline
uint64_t PHCapacityInternal(uint8_t capacity_clz, uint8_t capacity_ms4b)
{
  return (1UL << (64 - capacity_clz - 4)) * capacity_ms4b;
}

uint64_t PHCapacity(PascalHashTable* table)
{
  return PHCapacityInternal(table->capacity_clz, table->capacity_ms4b);
}

size_t PHValsize(PascalHashTable* table)
{
  return table->valsize;
}


static inline void
IncreaseProbeStat(PascalHashTable* table, int probe)
{
  table->objcnt++;
  table->longest_probes = probe > table->longest_probes ?
    probe : table->longest_probes;
  if (probe < PROBE_STATS_SIZE)
    table->stats[probe]++;
  else
    OP_LOG_WARN(logger, "Large probe: %d\n", probe);
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
hash_with_probe(PascalHashTable* table, uint64_t key, int probe)
{
  uintptr_t mask = (1ULL << (64 - table->capacity_clz)) - 1;

  uint64_t probed_hash = quadratic_exact(key, probe);
  return (probed_hash & mask) * table->capacity_ms4b >> 4;
}

static inline int
findprobe(PascalHashTable* table, OPHash hasher, uintptr_t idx)
{
  const size_t key_inline_size = table->key_inline_size;
  const size_t valsize = table->valsize;
  const size_t bucket_size = sizeof(oplenref_t) + key_inline_size + valsize;
  uint8_t* const buckets = OPRef2Ptr(table, table->bucket_ref);
  uint64_t mask = (1ULL << (64 - table->capacity_clz)) - 1;
  uint64_t hashed_key, probing_key, probing_idx;
  oplenref_t *keyref;
  void* keyptr;
  size_t keysize;

  keyref = (oplenref_t*)&buckets[idx * bucket_size];
  keyptr = OPLenRef2Ptr(keyref, key_inline_size);
  keysize = OPLenRef2Size(*keyref);
  hashed_key = hasher(keyptr, keysize);
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

static inline enum upsert_result_t
PHUpsertNewKey(PascalHashTable* table, OPHash hasher,
               void* key, size_t keysize, uint64_t hashed_key,
               uint8_t** matched_bucket, int* probe_state)
{
  const size_t key_inline_size = table->key_inline_size;
  const size_t valsize = table->valsize;
  const size_t bucket_size = sizeof(oplenref_t) + key_inline_size + valsize;
  uint8_t* buckets;
  int probe, old_probe;
  uintptr_t idx, _idx;
  oplenref_t *recref, *_recref;
  void *recptr, *_recptr;
  size_t recsize, _recsize;

  buckets = OPRef2Ptr(table, table->bucket_ref);
  probe = 0;

  while (true)
    {
      idx = hash_with_probe(table, hashed_key, probe);
      if (probe > PROBE_STATS_SIZE)
        {
          PHSizeUp(table, hasher);
          probe = 0;
          buckets = OPRef2Ptr(table, table->bucket_ref);
          continue;
        }
      recref = (oplenref_t*)&buckets[idx * bucket_size];
      if (OPLenRefIsEmpty(*recref))
        {
          IncreaseProbeStat(table, probe);
          *matched_bucket = &buckets[idx * bucket_size];
          return UPSERT_EMPTY;
        }
      else if (OPLenRefIsDeleted(*recref))
        {
          for (int p = probe+1; p <= table->longest_probes; p++)
            {
              _idx = hash_with_probe(table, hashed_key, p);
              _recref = (oplenref_t*)&buckets[_idx * bucket_size];
              if (OPLenRefIsEmpty(*_recref) ||
                  OPLenRefIsDeleted(*_recref))
                continue;
              _recptr = OPLenRef2Ptr(_recref, key_inline_size);
              _recsize = OPLenRef2Size(*_recref);
              if (_recsize == keysize &&
                  memeq(key, _recptr, keysize))
                {
                  *matched_bucket = &buckets[_idx * bucket_size];
                  return UPSERT_DUP;
                }
            }
          IncreaseProbeStat(table, probe);
          *matched_bucket = &buckets[idx * bucket_size];
          return UPSERT_EMPTY;
        }
      recptr = OPLenRef2Ptr(recref, key_inline_size);
      recsize = OPLenRef2Size(*recref);
      if (keysize == recsize &&
          memeq(key, recptr, keysize))
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
          *probe_state = old_probe + 1;
          return UPSERT_PUSHDOWN;
        }
      probe++;
    }
}

static inline void
PHUpsertPushDown(PascalHashTable* table, OPHash hasher,
                 uint8_t* bucket_cpy, int probe, uint8_t* avoid_bucket,
                 bool* resized)
{
  const size_t key_inline_size = table->key_inline_size;
  const size_t valsize = table->valsize;
  const size_t bucket_size = sizeof(oplenref_t) + key_inline_size + valsize;
  OPHeap* heap;
  oplenref_t *recref, *_recref;
  void *recptr;
  size_t recsize;
  uint8_t* buckets;
  int old_probe;
  uint8_t bucket_tmp[bucket_size];
  uintptr_t idx;
  uint64_t hashed_key;
  int visit;
  uintptr_t visited_idx[VISIT_IDX_CACHE];

  heap = ObtainOPHeap(table);
  visit = 0;
  *resized = false;
  buckets = OPRef2Ptr(table, table->bucket_ref);
  recref = (oplenref_t*)&bucket_cpy[0];
  recptr = OPLenRef2PtrOnHeap(recref, key_inline_size, heap);
  recsize = OPLenRef2Size(*recref);
  hashed_key = hasher(recptr, recsize);
  while (true)
    {
    next_iter:
      idx = hash_with_probe(table, hashed_key, probe);

      if (probe > PROBE_STATS_SIZE)
        {
          PHSizeUp(table, hasher);
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

      _recref = (oplenref_t*)&buckets[idx * bucket_size];
      if (OPLenRefIsEmpty(*_recref) ||
          OPLenRefIsDeleted(*_recref))
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
          recref = (oplenref_t*)&bucket_cpy[0];
          recptr = OPLenRef2PtrOnHeap(recref, key_inline_size, heap);
          recsize = OPLenRef2Size(*recref);
          hashed_key = hasher(recptr, recsize);
          continue;
        }
      probe++;
    }
}

static bool
PHSizeUp(PascalHashTable* table, OPHash hasher)
{
  const size_t key_inline_size = table->key_inline_size;
  const size_t valsize = table->valsize;
  const size_t bucket_size = sizeof(oplenref_t) + key_inline_size + valsize;
  const size_t large_data_threshold = table->large_data_threshold;
  uint8_t* old_buckets;
  uint8_t* new_buckets;
  oplenref_t *recref;
  bool resized;
  uint8_t new_capacity_ms4b, new_capacity_clz;
  uint64_t old_capacity, new_capacity;

  old_capacity = PHCapacity(table);
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
  new_capacity = PHCapacityInternal(new_capacity_clz, new_capacity_ms4b);
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
      recref = (oplenref_t*)&old_buckets[idx * bucket_size];
      if (!OPLenRefIsEmpty(*recref) &&
          !OPLenRefIsDeleted(*recref))
        {
          PHUpsertPushDown(table, hasher, &old_buckets[idx * bucket_size],
                           0, NULL, &resized);
        }
    }
  OPDealloc(old_buckets);
  return true;
}

static bool
PHSizeDown(PascalHashTable* table, OPHash hasher)
{
  const size_t key_inline_size = table->key_inline_size;
  const size_t valsize = table->valsize;
  const size_t bucket_size = sizeof(oplenref_t) + key_inline_size + valsize;
  uint8_t* old_buckets;
  uint8_t* new_buckets;
  uint8_t new_capacity_ms4b, new_capacity_clz;
  uint64_t old_capacity, new_capacity;
  oplenref_t *recref;
  bool resized;

  old_capacity = PHCapacity(table);
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

  new_capacity = PHCapacityInternal(new_capacity_clz, new_capacity_ms4b);
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
      recref = (oplenref_t*)&old_buckets[idx * bucket_size];
      if (!OPLenRefIsEmpty(*recref) &&
          !OPLenRefIsDeleted(*recref))
        {
          PHUpsertPushDown(table, hasher, &old_buckets[idx * bucket_size],
                           0, NULL, &resized);
        }
    }
  OPDealloc(old_buckets);
  return true;
}

bool PHInsertCustom(PascalHashTable* table, OPHash hasher,
                    void* key, size_t keysize, void* val)
{
  const size_t key_inline_size = table->key_inline_size;
  const size_t valsize = table->valsize;
  const size_t bucket_size = sizeof(oplenref_t) + key_inline_size + valsize;
  enum upsert_result_t upsert_result;
  uint64_t hashed_key;
  uint8_t* matched_bucket;
  uint8_t bucket_cpy[bucket_size];
  int probe;
  bool resized;

  if (table->objcnt > table->objcnt_high)
    {
      if(!PHSizeUp(table, hasher))
        return false;
    }

  hashed_key = hasher(key, keysize);
  upsert_result = PHUpsertNewKey(table, hasher,
                                 key, keysize, hashed_key,
                                 &matched_bucket, &probe);

  switch (upsert_result)
    {
    case UPSERT_EMPTY:
      OPLenRefCreate((oplenref_t*)matched_bucket,
                     key, keysize, key_inline_size);
      memcpy(&matched_bucket[sizeof(oplenref_t)+key_inline_size],
             val, valsize);
      break;
    case UPSERT_DUP:
      memcpy(&matched_bucket[sizeof(oplenref_t)+key_inline_size],
             val, valsize);
      break;
    case UPSERT_PUSHDOWN:
      memcpy(bucket_cpy, matched_bucket, bucket_size);
      OPLenRefCreate((oplenref_t*)matched_bucket,
                     key, keysize, key_inline_size);
      memcpy(&matched_bucket[sizeof(oplenref_t)+key_inline_size],
             val, valsize);
      PHUpsertPushDown(table, hasher, bucket_cpy, probe,
                       matched_bucket, &resized);
    }
  return true;
}

bool PHUpsertCustom(PascalHashTable* table, OPHash hasher,
                    void* key, size_t keysize, void** val_ref,
                    bool* is_duplicate)
{
  const size_t key_inline_size = table->key_inline_size;
  const size_t valsize = table->valsize;
  const size_t bucket_size = sizeof(oplenref_t) + key_inline_size + valsize;
  enum upsert_result_t upsert_result;
  uint8_t* matched_bucket;
  uint64_t hashed_key;
  int probe;
  uint8_t bucket_cpy[bucket_size];
  bool resized;

  if (table->objcnt > table->objcnt_high)
    {
      if(!PHSizeUp(table, hasher))
        return false;
    }

  hashed_key = hasher(key, keysize);
  upsert_result = PHUpsertNewKey(table, hasher,
                                 key, keysize, hashed_key,
                                 &matched_bucket, &probe);
  *val_ref = &matched_bucket[sizeof(oplenref_t) + key_inline_size];

  switch (upsert_result)
    {
    case UPSERT_DUP:
      *is_duplicate = true;
      break;
    case UPSERT_EMPTY:
      *is_duplicate = false;
      OPLenRefCreate((oplenref_t*)matched_bucket,
                     key, keysize, key_inline_size);
      break;
    case UPSERT_PUSHDOWN:
      *is_duplicate = false;
      memcpy(bucket_cpy, matched_bucket, bucket_size);
      OPLenRefCreate((oplenref_t*)matched_bucket,
                     key, keysize, key_inline_size);
      PHUpsertPushDown(table, hasher, bucket_cpy, probe,
                       matched_bucket, &resized);
      if (resized)
        {
          *val_ref = PHGetCustom(table, hasher, key, keysize);
        }
    }
  return true;
}

static inline bool
PHSearchIdx(PascalHashTable* table, OPHash hasher,
            void* key, size_t keysize, uintptr_t* idx)
{
  const size_t key_inline_size = table->key_inline_size;
  const size_t valsize = table->valsize;
  const size_t bucket_size = sizeof(oplenref_t) + key_inline_size + valsize;
  uint8_t* const buckets = OPRef2Ptr(table, table->bucket_ref);
  uint64_t hashed_key, mask, probing_key;
  uintptr_t idx_next;
  oplenref_t *recref;
  void* recptr;
  size_t recsize;

  hashed_key = hasher(key, keysize);
  mask = (1ULL << (64 - table->capacity_clz)) - 1;

  probing_key = hashed_key;
  *idx = fast_mod_scale(probing_key, mask, table->capacity_ms4b);
  probing_key = quadratic_partial(probing_key, 1);
  idx_next = fast_mod_scale(probing_key, mask, table->capacity_ms4b);

  for (int probe = 2; probe <= table->longest_probes + 2; probe++)
    {
      __builtin_prefetch(&buckets[idx_next * bucket_size], 0, 0);
      recref = (oplenref_t*)&buckets[*idx * bucket_size];
      if (OPLenRefIsEmpty(*recref))
        return false;
      if (OPLenRefIsDeleted(*recref))
        goto next_iter;
      recptr = OPLenRef2Ptr(recref, key_inline_size);
      recsize = OPLenRef2Size(*recref);
      if (keysize == recsize &&
          memeq(key, recptr, keysize))
        return true;
    next_iter:
      *idx = idx_next;
      probing_key = quadratic_partial(probing_key, probe);
      idx_next = fast_mod_scale(probing_key, mask, table->capacity_ms4b);
    }
  return false;
}

void* PHGetCustom(PascalHashTable* table, OPHash hasher,
                  void* key, size_t keysize)
{
  const size_t key_inline_size = table->key_inline_size;
  const size_t valsize = table->valsize;
  const size_t bucket_size = sizeof(oplenref_t) + key_inline_size + valsize;
  uint8_t* const buckets = OPRef2Ptr(table, table->bucket_ref);
  uintptr_t idx;
  if (PHSearchIdx(table, hasher, key, keysize, &idx))
    {
      return &buckets[idx * bucket_size +
                      sizeof(oplenref_t) + key_inline_size];
    }
  return NULL;
}

void* PHDeleteCustom(PascalHashTable* table, OPHash hasher,
                     void* key, size_t keysize)
{
  const size_t key_inline_size = table->key_inline_size;
  const size_t valsize = table->valsize;
  const size_t bucket_size = sizeof(oplenref_t) + key_inline_size + valsize;
  uint8_t* buckets;
  uintptr_t idx;
  int record_probe;
  oplenref_t* recref;

  if (table->objcnt < table->objcnt_low &&
      table->objcnt > 16)
    {
      if (!PHSizeDown(table, hasher))
        return NULL;
    }

  if (!PHSearchIdx(table, hasher, key, keysize, &idx))
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

  recref = (oplenref_t*)&buckets[idx * bucket_size];
  OPLenRefDelete(recref, key_inline_size);
  return &buckets[idx * bucket_size +
                  sizeof(oplenref_t) + key_inline_size];
}

void PHIterate(PascalHashTable* table,
               OPHashIterator iterator, void* context)
{
  const size_t key_inline_size = table->key_inline_size;
  const size_t valsize = table->valsize;
  const size_t bucket_size = sizeof(oplenref_t) + key_inline_size + valsize;
  uint8_t* const buckets = OPRef2Ptr(table, table->bucket_ref);
  uint64_t capacity = PHCapacity(table);
  oplenref_t* recref;
  void* recptr;
  size_t recsize;

  for (uint64_t idx = 0; idx < capacity; idx++)
    {
      recref = (oplenref_t*)&buckets[idx * bucket_size];
      if (!OPLenRefIsEmpty(*recref) &&
          !OPLenRefIsDeleted(*recref))
        {
          recptr = OPLenRef2Ptr(recref, key_inline_size);
          recsize = OPLenRef2Size(*recref);
          iterator(recptr, &buckets[idx * bucket_size +
                                    sizeof(oplenref_t) +
                                    key_inline_size],
                   recsize, valsize, context);
        }
    }
}

void PHPrintStat(PascalHashTable* table)
{
  for (int i = 0; i < PROBE_STATS_SIZE; i++)
    if (table->stats[i])
      printf("probe %02d: %d\n", i, table->stats[i]);
}

uint32_t PHMaxProbe(PascalHashTable* table)
{
  return table->longest_probes;
}

uint32_t PHProbeStat(PascalHashTable* table, uint32_t idx)
{
  if (idx < PROBE_STATS_SIZE)
    return table->stats[idx];
  return 0;
}

/* pascal_robin_hood.c ends here */
