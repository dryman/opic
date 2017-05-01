/* rhh_bkv_v4qu.c ---
 *
 * Filename: rhh_bkv_v4qu.c
 * Description:
 * Author: Felix Chern
 * Maintainer:
 * Copyright: (c) 2017 Felix Chern
 * Created: Sun Apr 30 16:05:21 2017 (-0700)
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
#include "rhh_bkv_v4qu.h"

#define PROBE_STATS_SIZE 64

OP_LOGGER_FACTORY(logger, "benchmark.robin_hood.rhh_bkv_v4qu");

typedef uint64_t v4qu __attribute__ ((vector_size (32)));

struct RHH_bkv_v4qu
{
  uint64_t objcnt;
  uint64_t objcnt_high;
  uint8_t capacity_clz;    // leading zeros of capacity
  uint8_t capacity_ms4b;   // most significant 4 bits
  uint16_t longest_probes;
  size_t keysize;
  size_t valsize;
  uint32_t stats[PROBE_STATS_SIZE];
  uint8_t* bucket;
};

bool
RHH_bkv_v4qu_New(OPHeap* heap, RHH_bkv_v4qu ** rhh,
              uint64_t num_objects, double load,
              size_t keysize, size_t valsize)
{
  uint64_t capacity;
  uint32_t capacity_clz, capacity_ms4b, capacity_msb;
  size_t alloc_size, header_size;
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


  header_size = sizeof(RHH_bkv_v4qu);
  alloc_size = header_size + capacity * (1 + keysize + valsize);
  OP_LOG_INFO(logger, "alloc size %zu", alloc_size);

  *rhh = OPCalloc(heap, 1, alloc_size);
  if (!*rhh)
    return false;
  rhh_base = (uintptr_t)(*rhh);

  (*rhh)->bucket = (uint8_t*)(rhh_base + header_size);

  (*rhh)->capacity_clz = capacity_clz;
  (*rhh)->capacity_ms4b = capacity_ms4b;
  (*rhh)->objcnt_high = (uint64_t)(capacity * load);
  (*rhh)->keysize = keysize;
  (*rhh)->valsize = valsize;
  return true;
}

void
RHH_bkv_v4qu_Destroy(RHH_bkv_v4qu* rhh)
{
  OPDealloc(rhh);
}

static inline uintptr_t
hash_with_probe(RHH_bkv_v4qu* rhh, uint64_t key, int probe)
{
  uintptr_t mask = (1ULL << (64 - rhh->capacity_clz)) - 1;

  // quadratic probing
  uint64_t probed_hash = key + probe * probe * 2;

  // Fast mod and scale
  return (probed_hash & mask) * rhh->capacity_ms4b >> 4;
}

static inline v4qu
v4qu_hash_with_probe(RHH_bkv_v4qu* rhh, uint64_t key, int probe)
{
  v4qu vkey, vprobe, vmask, vprobed_hash, vms4b, vout;
  uint64_t mask, ms4b;
  mask = (1ULL << (64 - rhh->capacity_clz)) - 1;
  ms4b = rhh->capacity_ms4b;

  vkey = (v4qu){key, key, key, key};
  vprobe = (v4qu){probe, probe + 1, probe + 2, probe + 3};
  vmask = (v4qu){mask, mask, mask, mask};
  vms4b = (v4qu){ms4b, ms4b, ms4b, ms4b};

  vprobed_hash = vkey + ((vprobe * vprobe) << (v4qu){1, 1, 1, 1});
  vout = ((vprobed_hash & vmask) * vms4b) >> (v4qu){4, 4, 4, 4};

  return vout;
}

static inline int
findprobe(RHH_bkv_v4qu* rhh, OPHash hasher, uintptr_t idx)
{
  const size_t keysize = rhh->keysize;
  const size_t valsize = rhh->valsize;
  const size_t bucket_size = keysize + valsize + 1;
  uint64_t hashed_key;
  v4qu probed_idxes;

  hashed_key = hasher(&rhh->bucket[idx * bucket_size + 1], keysize);
  for (int i = 0; i <= rhh->longest_probes; i+=4)
    {
      probed_idxes = v4qu_hash_with_probe(rhh, hashed_key, i);
      if (probed_idxes[0] == idx)
        return i;
      if (probed_idxes[1] == idx)
        return i + 1;
      if (probed_idxes[2] == idx)
        return i + 2;
      if (probed_idxes[3] == idx)
        return i + 3;
    }
  OP_LOG_ERROR(logger, "Didn't find any match probe!\n");
  return -1;
}

bool RHH_bkv_v4qu_PutCustom(RHH_bkv_v4qu* rhh,
                         OPHash hasher, void* key, void* val)
{
  const size_t keysize = rhh->keysize;
  const size_t valsize = rhh->valsize;
  const size_t bucket_size = keysize + valsize + 1;
  uintptr_t idx;
  int probe, old_probe;
  uint8_t bucket_cpy[bucket_size];
  uint8_t bucket_tmp[bucket_size];
  uint64_t hashed_key;

  if (rhh->objcnt > rhh->objcnt_high)
    return false;

  bucket_cpy[0] = 1;
  memcpy(&bucket_cpy[1], key, keysize);
  memcpy(&bucket_cpy[keysize + 1], val, valsize);

  probe = 0;
  while (true)
    {
      hashed_key = hasher(&bucket_cpy[1], keysize);
      idx = hash_with_probe(rhh, hashed_key, probe);

      if (rhh->bucket[idx * bucket_size] != 1)
        {
          memcpy(&rhh->bucket[idx * bucket_size], bucket_cpy, bucket_size);
          rhh->longest_probes = probe > rhh->longest_probes ?
            probe : rhh->longest_probes;
          rhh->objcnt++;
          if (probe < PROBE_STATS_SIZE)
            rhh->stats[probe]++;
          else
            OP_LOG_WARN(logger, "Large probe: %d\n", probe);
          return true;
        }
      else if (!memcmp(&rhh->bucket[idx * bucket_size + 1],
                       &bucket_cpy[1], keysize))
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
RHHSearchIdx(RHH_bkv_v4qu* rhh, OPHash hasher, void* key, uintptr_t* idx)
{
  const size_t keysize = rhh->keysize;
  const size_t valsize = rhh->valsize;
  const size_t bucket_size = keysize + valsize + 1;
  uint64_t hashed_key;
  v4qu probed_idxes;

  hashed_key = hasher(key, keysize);

  for (int probe = 0; probe <= rhh->longest_probes; probe+=4)
    {
      probed_idxes = v4qu_hash_with_probe(rhh, hashed_key, probe);
      for (int i = 0; i < 4; i++)
        {
          *idx = probed_idxes[i];
          if (rhh->bucket[*idx * bucket_size] != 1)
            return false;
          if (!memcmp(key, &rhh->bucket[*idx * bucket_size + 1], keysize))
            return true;
        }
    }
  return false;
}

void* RHH_bkv_v4qu_GetCustom(RHH_bkv_v4qu* rhh, OPHash hasher, void* key)
{
  const size_t keysize = rhh->keysize;
  const size_t valsize = rhh->valsize;
  const size_t bucket_size = keysize + valsize + 1;
  uintptr_t idx;
  if (RHHSearchIdx(rhh, hasher, key, &idx))
    {
      return &rhh->bucket[idx * bucket_size + keysize + 1];
    }
  return NULL;
}

void RHH_bkv_v4qu_PrintStat(RHH_bkv_v4qu* rhh)
{
  for (int i = 0; i < PROBE_STATS_SIZE; i++)
    if (rhh->stats[i])
      printf("probe %02d: %d\n", i, rhh->stats[i]);
}

/* rhh_bkv_v4qu.c ends here */
