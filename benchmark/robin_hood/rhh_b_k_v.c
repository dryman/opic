/* rhh_b_k_v.c ---
 *
 * Filename: rhh_b_k_v.c
 * Description:
 * Author: Felix Chern
 * Maintainer:
 * Copyright: (c) 2017 Felix Chern
 * Created: Sun Apr 30 13:44:27 2017 (-0700)
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
#include "rhh_b_k_v.h"

#define PROBE_STATS_SIZE 64
// 128MB
#define DEFAULT_LARGE_DATA_THRESHOLD (1UL << 30)

OP_LOGGER_FACTORY(logger, "benchmark.robin_hood.rhh_b_k_v");

struct RHH_b_k_v
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
  uint8_t* key;
  uint8_t* val;
};

bool
RHH_b_k_v_New(OPHeap* heap, RHH_b_k_v ** rhh,
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


  header_size = sizeof(RHH_b_k_v);
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
  (*rhh)->key = (uint8_t*)(rhh_base + header_size + bmap_size);
  (*rhh)->val = (uint8_t*)(rhh_base + header_size + bmap_size + key_size);

  (*rhh)->capacity_clz = capacity_clz;
  (*rhh)->capacity_ms4b = capacity_ms4b;
  (*rhh)->objcnt_high = (uint64_t)(capacity * load);
  (*rhh)->keysize = keysize;
  (*rhh)->valsize = valsize;
  return true;
}

void
RHH_b_k_v_Destroy(RHH_b_k_v* rhh)
{
  OPDealloc(rhh);
}

static inline uintptr_t
hash_with_probe(RHH_b_k_v* rhh, uint64_t key, int probe)
{
  uintptr_t mask = (1ULL << (64 - rhh->capacity_clz)) - 1;

  // quadratic probing
  uint64_t probed_hash = key + probe * probe * 2;

  // Fast mod and scale
  return (probed_hash & mask) * rhh->capacity_ms4b >> 4;
}

static inline int
findprobe(RHH_b_k_v* rhh, OPHash hasher, uintptr_t idx)
{
  const size_t keysize = rhh->keysize;
  uint64_t hashed_key;

  hashed_key = hasher(&rhh->key[idx * keysize], keysize);
  for (int i = 0; i <= rhh->longest_probes; i++)
    {
      if (hash_with_probe(rhh, hashed_key, i) == idx)
        return i;
    }
  OP_LOG_ERROR(logger, "Didn't find any match probe!\n");
  return -1;
}

bool RHH_b_k_v_PutCustom(RHH_b_k_v* rhh,
                         OPHash hasher, void* key, void* val)
{
  const size_t keysize = rhh->keysize;
  const size_t valsize = rhh->valsize;
  uintptr_t idx;
  int probe, old_probe;
  uint8_t key_cpy[keysize];
  uint8_t key_tmp[keysize];
  uint8_t val_cpy[valsize];
  uint8_t val_tmp[valsize];
  uint64_t hashed_key;
  int bm_idx, bm_bit;

  if (rhh->objcnt > rhh->objcnt_high)
    return false;

  memcpy(key_cpy, key, keysize);
  memcpy(val_cpy, val, valsize);

  probe = 0;
  while (true)
    {
      hashed_key = hasher(key_cpy, keysize);
      idx = hash_with_probe(rhh, hashed_key, probe);
      bm_idx = idx / 64;
      bm_bit = idx % 64;
      if ((rhh->bmap[bm_idx] & (1ULL << bm_bit)) == 0)
        {
          memcpy(&rhh->key[idx * keysize], key_cpy, keysize);
          memcpy(&rhh->val[idx * valsize], val_cpy, valsize);
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
      else if (!memcmp(&rhh->key[idx * keysize], key_cpy, keysize))
        {
          memcpy(&rhh->val[idx * valsize], val_cpy, valsize);
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

          memcpy(key_tmp, &rhh->key[idx * keysize], keysize);
          memcpy(val_tmp, &rhh->val[idx * valsize], valsize);
          memcpy(&rhh->key[idx * keysize], key_cpy, keysize);
          memcpy(&rhh->val[idx * valsize], val_cpy, valsize);
          memcpy(key_cpy, key_tmp, keysize);
          memcpy(val_cpy, val_tmp, valsize);

          rhh->longest_probes = probe > rhh->longest_probes ?
            probe : rhh->longest_probes;
          probe = old_probe;
        }
        probe++;
    }
}

static inline bool
RHHSearchIdx(RHH_b_k_v* rhh, OPHash hasher, void* key, uintptr_t* idx)
{
  const size_t keysize = rhh->keysize;
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
      if (!memcmp(key, &rhh->key[*idx*keysize], keysize))
        return true;
    }
  return false;
}

void* RHH_b_k_v_GetCustom(RHH_b_k_v* rhh, OPHash hasher, void* key)
{
  uintptr_t idx;
  if (RHHSearchIdx(rhh, hasher, key, &idx))
    {
      return &rhh->val[idx];
    }
  return NULL;
}

void RHH_b_k_v_PrintStat(RHH_b_k_v* rhh)
{
  for (int i = 0; i < PROBE_STATS_SIZE; i++)
    if (rhh->stats[i])
      printf("probe %02d: %d\n", i, rhh->stats[i]);
}

/* rhh_b_k_v.c ends here */
