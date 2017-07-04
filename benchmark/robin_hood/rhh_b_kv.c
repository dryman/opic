/* rhh_b_kv.c ---
 *
 * Filename: rhh_b_kv.c
 * Description:
 * Author: Felix Chern
 * Maintainer:
 * Copyright: (c) 2017 Felix Chern
 * Created: Sun Apr 30 15:35:42 2017 (-0700)
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
#include "rhh_b_kv.h"

#define PROBE_STATS_SIZE 64

OP_LOGGER_FACTORY(logger, "benchmark.robin_hood.rhh_b_kv");

struct RHH_b_kv
{
  uint64_t objcnt;
  uint64_t objcnt_high;
  uint8_t capacity_clz;    // leading zeros of capacity
  uint8_t capacity_ms4b;   // most significant 4 bits
  uint16_t longest_probes;
  size_t keysize;
  size_t valsize;
  uint32_t stats[PROBE_STATS_SIZE];
  uint64_t* bmap;
  uint8_t* bucket;
};

bool
RHH_b_kv_New(OPHeap* heap, RHH_b_kv ** rhh,
              uint64_t num_objects, double load,
              size_t keysize, size_t valsize)
{
  uint64_t capacity;
  uint32_t capacity_clz, capacity_ms4b, capacity_msb;
  size_t alloc_size, header_size, bmap_size, key_size, val_size;
  uintptr_t rhh_base;

  op_assert(load > 0.0 && load < 1.0,
            "load %lf must within close interval (0.0, 1.0)\n", load);
  capacity = (uint64_t)(num_objects / load);
  if (capacity < 8)
    capacity = 8;
  capacity_clz = __builtin_clzl(capacity);
  capacity_msb = 64 - capacity_clz;
  capacity_ms4b = round_up_div(capacity, 1UL << (capacity_msb - 4));
  capacity = (uint64_t)capacity_ms4b << (capacity_msb - 4);


  header_size = sizeof(RHH_b_kv);
  bmap_size = round_up_div(capacity, 64) * sizeof(uint64_t);
  key_size = capacity * keysize;
  val_size = capacity * valsize;
  alloc_size = header_size + bmap_size + key_size + val_size;
  OP_LOG_INFO(logger, "alloc size %zu", alloc_size);

  *rhh = OPCalloc(heap, 1, alloc_size);
  if (!*rhh)
    return false;
  rhh_base = (uintptr_t)(*rhh);

  (*rhh)->bmap = (uint64_t*)(rhh_base + header_size);
  (*rhh)->bucket = (uint8_t*)(rhh_base + header_size + bmap_size);

  (*rhh)->capacity_clz = capacity_clz;
  (*rhh)->capacity_ms4b = capacity_ms4b;
  (*rhh)->objcnt_high = (uint64_t)(capacity * load);
  (*rhh)->keysize = keysize;
  (*rhh)->valsize = valsize;
  return true;
}

void
RHH_b_kv_Destroy(RHH_b_kv* rhh)
{
  OPDealloc(rhh);
}

static inline uintptr_t
hash_with_probe(RHH_b_kv* rhh, uint64_t key, int probe)
{
  uintptr_t mask = (1ULL << (64 - rhh->capacity_clz)) - 1;

  // quadratic probing
  uint64_t probed_hash = key + probe * probe * 2;

  // Fast mod and scale
  return (probed_hash & mask) * rhh->capacity_ms4b >> 4;
}

static inline int
findprobe(RHH_b_kv* rhh, OPHash hasher, uintptr_t idx)
{
  const size_t keysize = rhh->keysize;
  const size_t valsize = rhh->valsize;
  const size_t bucket_size = keysize + valsize;
  uint64_t hashed_key;

  hashed_key = hasher(&rhh->bucket[idx * bucket_size], keysize);
  for (int i = 0; i <= rhh->longest_probes; i++)
    {
      if (hash_with_probe(rhh, hashed_key, i) == idx)
        return i;
    }
  OP_LOG_ERROR(logger, "Didn't find any match probe!\n");
  return -1;
}

bool RHH_b_kv_PutCustom(RHH_b_kv* rhh,
                         OPHash hasher, void* key, void* val)
{
  const size_t keysize = rhh->keysize;
  const size_t valsize = rhh->valsize;
  const size_t bucket_size = keysize + valsize;
  uintptr_t idx;
  int probe, old_probe;
  uint8_t bucket_cpy[bucket_size];
  uint8_t bucket_tmp[bucket_size];
  uint64_t hashed_key;
  int bm_idx, bm_bit;

  if (rhh->objcnt > rhh->objcnt_high)
    return false;

  memcpy(bucket_cpy, key, keysize);
  memcpy(&bucket_cpy[keysize], val, valsize);

  probe = 0;
  while (true)
    {
      hashed_key = hasher(bucket_cpy, keysize);
      idx = hash_with_probe(rhh, hashed_key, probe);
      bm_idx = idx / 64;
      bm_bit = idx % 64;
      if ((rhh->bmap[bm_idx] & (1ULL << bm_bit)) == 0)
        {
          memcpy(&rhh->bucket[idx * bucket_size], bucket_cpy, bucket_size);
          rhh->bmap[bm_idx] |= (1ULL << bm_bit);
          rhh->longest_probes = probe > rhh->longest_probes ?
            probe : rhh->longest_probes;
          rhh->objcnt++;
          if (probe < PROBE_STATS_SIZE)
            rhh->stats[probe]++;
          else
            OP_LOG_WARN(logger, "Large probe: %d\n", probe);
          return true;
        }
      else if (!memcmp(&rhh->bucket[idx * bucket_size],
                       bucket_cpy, keysize))
        {
          memcpy(&rhh->bucket[idx*bucket_size], bucket_cpy, bucket_size);
          return true;
        }
      old_probe = findprobe(rhh, hasher, idx);

      if (probe > old_probe)
        {
          if (old_probe < PROBE_STATS_SIZE)
            rhh->stats[old_probe]--;
          if (probe < PROBE_STATS_SIZE)
            rhh->stats[probe]++;
          else
            OP_LOG_WARN(logger, "Large probe: %d\n", probe);

          memcpy(bucket_tmp, &rhh->bucket[idx*bucket_size], bucket_size);
          memcpy(&rhh->bucket[idx*bucket_size], bucket_cpy, bucket_size);
          memcpy(bucket_cpy, bucket_tmp, bucket_size);

          rhh->longest_probes = probe > rhh->longest_probes ?
            probe : rhh->longest_probes;
          probe = old_probe;
        }
        probe++;
    }
}

static inline bool
RHHSearchIdx(RHH_b_kv* rhh, OPHash hasher, void* key, uintptr_t* idx)
{
  const size_t keysize = rhh->keysize;
  const size_t valsize = rhh->valsize;
  const size_t bucket_size = keysize + valsize;
  uint64_t hashed_key;
  int bm_idx, bm_bit;

  hashed_key = hasher(key, keysize);

  for (int probe = 0; probe <= rhh->longest_probes; probe++)
    {
      *idx = hash_with_probe(rhh, hashed_key, probe);
      bm_idx = *idx / 64;
      bm_bit = *idx % 64;
      if ((rhh->bmap[bm_idx] & (1ULL << bm_bit)) == 0)
        return false;
      if (!memcmp(key, &rhh->bucket[*idx * bucket_size], keysize))
        return true;
    }
  return false;
}

void* RHH_b_kv_GetCustom(RHH_b_kv* rhh, OPHash hasher, void* key)
{
  const size_t keysize = rhh->keysize;
  const size_t valsize = rhh->valsize;
  const size_t bucket_size = keysize + valsize;
  uintptr_t idx;
  if (RHHSearchIdx(rhh, hasher, key, &idx))
    {
      return &rhh->bucket[idx * bucket_size + keysize];
    }
  return NULL;
}

void RHH_b_kv_PrintStat(RHH_b_kv* rhh)
{
  for (int i = 0; i < PROBE_STATS_SIZE; i++)
    if (rhh->stats[i])
      printf("probe %02d: %d\n", i, rhh->stats[i]);
}

uint32_t RHH_b_kv_MaxProbe(RHH_b_kv* rhh)
{
  return rhh->longest_probes;
}

uint32_t RHH_b_kv_ProbeStat(RHH_b_kv* rhh, uint32_t idx)
{
  if (idx < PROBE_STATS_SIZE)
    return rhh->stats[idx];
  return 0;
}

/* rhh_b_kv.c ends here */
