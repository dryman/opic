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

OP_LOGGER_FACTORY(logger, "opic.hash.robin_hood");

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
  uintptr_t mask = (1ULL << (64 - rhh->capacity_clz)) - 1;

  // linear probing
  // uint64_t probed_hash = key + probe * 2;

  // quadratic probing
  uint64_t probed_hash = key + probe * probe * 2;

  // Fast mod and scale
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
  if (probe < PROBE_STATS_SIZE)
    rhh->stats[probe]++;
  else
    OP_LOG_WARN(logger, "Large probe: %d\n", probe);
}

static inline void
RHHUpsertInternal(RobinHoodHash* rhh, OPHash hasher,
                  void* key, uint8_t** matched_bucket)
{
  const size_t keysize = rhh->keysize;
  const size_t valsize = rhh->valsize;
  const size_t bucket_size = keysize + valsize + 1;
  uint8_t* buckets;
  int probe, old_probe;
  uint8_t bucket_cpy[bucket_size];
  uint8_t bucket_tmp[bucket_size];
  uintptr_t idx, _idx;
  uint64_t hashed_key;

  buckets = OPRef2Ptr(rhh, rhh->bucket_ref);
  //memcpy(bucket_cpy, bucket, bucket_size);
  probe = 0;
  hashed_key = hasher(key, keysize);

  // first round: find matched bucket
  while (true)
    {
      idx = hash_with_probe(rhh, hashed_key, probe);
      if (buckets[idx * bucket_size] == 0)
        {
          IncreaseProbeStat(rhh, probe);
          *matched_bucket = &buckets[idx * bucket_size];
          return;
        }
      else if (buckets[idx * bucket_size] == 2)
        {
          for (int p = probe+1; p <= rhh->longest_probes; p++)
            {
              _idx = hash_with_probe(rhh, hashed_key, p);
              if (buckets[_idx * bucket_size] != 1)
                continue;
              if (!memcmp(key, &buckets[_idx * bucket_size], bucket_size))
                {
                  *matched_bucket = &buckets[_idx * bucket_size];
                  return;
                }
            }
          IncreaseProbeStat(rhh, probe);
          *matched_bucket = &buckets[idx * bucket_size];
          return;
        }
      if (!memcmp(key, &buckets[idx * bucket_size], keysize))
        {
          *matched_bucket = &buckets[idx * bucket_size];
          return;
        }
      old_probe = findprobe(rhh, hasher, idx);
      if (probe > old_probe)
        {
          rhh->longest_probes = probe > rhh->longest_probes ?
            probe : rhh->longest_probes;
          if (old_probe < PROBE_STATS_SIZE)
            rhh->stats[old_probe]--;
          if (probe < PROBE_STATS_SIZE)
            rhh->stats[probe]++;
          else
            OP_LOG_WARN(logger, "Large probe: %d\n", probe);
          *matched_bucket = &buckets[idx * bucket_size];
          memcpy(bucket_cpy, &buckets[idx * bucket_size], bucket_size);
          buckets[idx * bucket_size] = 0;
          probe = old_probe+1;
          break;
        }
      probe++;
    }

  // second round: move existing records around
  // Now we should not have any duplicate value, so no need to
  // compare the keys.
  hashed_key = hasher(&bucket_cpy[1], keysize);
  while (true)
    {
      idx = hash_with_probe(rhh, hashed_key, probe);

      // If the one we're swaping out is the matched bucket,
      // we're in a cycle. Break the cycle by skipping the
      // matched_bucket.
      if ((void*)&buckets[idx * bucket_size] == matched_bucket)
        {
          probe++;
          continue;
        }

      // empty bucket and tombstone bucket
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
          if (old_probe < PROBE_STATS_SIZE)
            rhh->stats[old_probe]--;
          if (probe < PROBE_STATS_SIZE)
            rhh->stats[probe]++;
          else
            OP_LOG_WARN(logger, "Large probe: %d\n", probe);
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
  uint8_t *matched_bucket;

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
          RHHUpsertInternal(rhh, hasher,
                            &old_buckets[idx * bucket_size + 1],
                            &matched_bucket);
          memcpy(matched_bucket, &old_buckets[idx * bucket_size], bucket_size);
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
  uint8_t* matched_bucket;

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
          RHHUpsertInternal(rhh, hasher,
                            &old_buckets[idx * bucket_size + 1],
                            &matched_bucket);
          memcpy(matched_bucket, &old_buckets[idx * bucket_size], bucket_size);
        }
    }
  OPDealloc(old_buckets);
  return true;
}

bool RHHInsertCustom(RobinHoodHash* rhh, OPHash hasher, void* key, void* val)
{
  const size_t keysize = rhh->keysize;
  const size_t valsize = rhh->valsize;
  uint8_t* matched_bucket;

  RHHUpsertInternal(rhh, hasher, key, &matched_bucket);
  *matched_bucket = 1;
  memcpy(&matched_bucket[1], key, keysize);
  memcpy(&matched_bucket[1 + keysize], val, valsize);

  if (rhh->objcnt > rhh->objcnt_high)
    {
      return RHHSizeUp(rhh, hasher);
    }
  return true;
}

bool RHHUpsertCustom(RobinHoodHash* rhh, OPHash hasher,
                     void* key, void** val_ref)
{
  const size_t keysize = rhh->keysize;
  uint8_t* matched_bucket;
  RHHUpsertInternal(rhh, hasher, key, &matched_bucket);
  *val_ref = &matched_bucket[keysize + 1];

  // duplicate key case
  if (*matched_bucket == 1)
    return true;
  memcpy(&matched_bucket[1], key, keysize);
  return false;
}

static inline bool
RHHSearchIdx(RobinHoodHash* rhh, OPHash hasher, void* key, uintptr_t* idx)
{
  const size_t keysize = rhh->keysize;
  const size_t valsize = rhh->valsize;
  const size_t bucket_size = keysize + valsize + 1;
  uint8_t* const buckets = OPRef2Ptr(rhh, rhh->bucket_ref);
  uint64_t hashed_key;

  hashed_key = hasher(key, keysize);

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

void* RHHDeleteCustom(RobinHoodHash* rhh, OPHash hasher, void* key)
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

  if (!RHHSearchIdx(rhh, hasher, key, &idx))
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
        iterator(&buckets[idx*bucket_size + 1],
                 &buckets[idx*bucket_size + 1 + keysize],
                 keysize, valsize, context);
    }
}

void RHHPrintStat(RobinHoodHash* rhh)
{
  for (int i = 0; i < PROBE_STATS_SIZE; i++)
    if (rhh->stats[i])
      printf("probe %02d: %d\n", i, rhh->stats[i]);
}

/* robin_hood.c ends here */
