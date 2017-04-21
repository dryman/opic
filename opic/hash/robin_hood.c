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

#include <math.h>
#include <stdio.h> // TODO use op_log instead
#include <inttypes.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include "opic/common/op_assert.h"
#include "opic/common/op_utils.h"
#include "opic/common/op_log.h"
#include "opic/op_malloc.h"
#include "murmurhash3.h"
#include "robin_hood.h"

#define VISIT_IDX_CACHE 16

OP_LOGGER_FACTORY(logger, "opic.hash.robin_hood");

struct RobinHoodHash
{
  uint64_t capacity;
  uint64_t objcnt_limit;
  uint64_t objcnt;
  uint8_t capacity_clz;    // leading zeros of capacity
  uint8_t capacity_ms4b;   // most significant 4 bits
  int16_t longest_probes;
  size_t keysize;
  size_t valsize;
  uint8_t* data; // TODO might be better to use data[0]
  uint32_t stats[30];

  uint64_t reserved[8];
};

bool
RHHNew(OPHeap* heap, RobinHoodHash** rhh,
       uint64_t num_objects, double load, size_t keysize, size_t valsize)
{
  uint64_t capacity;
  uint32_t capacity_clz, capacity_ms4b, capacity_msb;
  size_t malloc_total_size, malloc_header_size, bucket_size;
  uintptr_t rhh_base;

  capacity = (uint64_t)(num_objects / load);
  capacity_clz = __builtin_clzl(capacity);
  capacity_msb = 64 - capacity_clz;
  capacity_ms4b = round_up_div(capacity, 1UL << (capacity_msb - 4));
  capacity_ms4b |= 1;
  capacity = (uint64_t)capacity_ms4b << (capacity_msb - 4);

  bucket_size = keysize + valsize + 1;
  malloc_header_size = sizeof(RobinHoodHash);
  malloc_total_size = malloc_header_size + bucket_size * capacity;

  *rhh = OPMallocRaw(heap, malloc_total_size);
  if (!*rhh)
    return false;

  rhh_base = (uintptr_t)(*rhh);
  memset(*rhh, 0x00, malloc_total_size);
  (*rhh)->capacity = capacity;
  (*rhh)->capacity_clz = capacity_clz;
  (*rhh)->capacity_ms4b = capacity_ms4b;
  (*rhh)->objcnt_limit = num_objects;
  (*rhh)->keysize = keysize;
  (*rhh)->valsize = valsize;
  (*rhh)->data = (uint8_t*)(rhh_base + malloc_header_size);
  return true;
}

void
RHHDestroy(RobinHoodHash* rhh)
{
  OPDealloc(rhh);
}

uint64_t RHHKeysize(RobinHoodHash* rhh)
{
  return rhh->keysize;
}

uint64_t RHHValsize(RobinHoodHash* rhh)
{
  return rhh->valsize;
}

uint64_t RHHFixkey(void* key, size_t size)
{
  uint64_t hashed_val[2];
  MurmurHash3_x64_128(key, size, 421439783, hashed_val);
  return hashed_val[0];
}

uint64_t RHHPascal(void* key, size_t size)
{
  uint64_t hashed_val[2];
  opref_t packed_key, opref_key;
  size_t real_keysize;
  void* real_key;
  packed_key = *(opref_t*)key;
  opref_key = packed_key & ((1ULL << OPHEAP_BITS) - 1);
  real_keysize = (size_t)packed_key >> OPHEAP_BITS;
  real_key = OPRef2Ptr(key, opref_key);
  MurmurHash3_x64_128(real_key, real_keysize, 421439783, hashed_val);
  return hashed_val[0];
}

static inline uintptr_t
hash_with_probe(RobinHoodHash* rhh, uint64_t key, int probe)
{
  uintptr_t mask = (1ULL << (64 - rhh->capacity_clz)) - 1;

  // linear probing
  // Best cache performance, but terrible on key collision.
  // uint64_t probed_hash = key + probe * 2;

  // quadratic probing
  // Still good on cache performance, but not good enough to resolve
  // key collisions under high load.
  uint64_t probed_hash = key + probe * probe * 2;

  // Felix's probing 1: perfect hashing based on probes.
  // Best key collision resolver. Generates unifomly distributed
  // probe result. However, it has bad cache performance.
  // uint64_t probed_hash = (key >> probe) | (key << (64 - probe));

  // Felix's probing 2
  // Use the last 3,4 digits to shuffle the probe position.
  // Makes good balance on cache performance and key collision
  // int probe_mod = probe % 4;
  // int probe_div = probe / 4;
  // uint64_t probed_hash = (key << probe_div) + probe_mod * probe_mod;

  // Fast mod and scale
  return (probed_hash & mask) * rhh->capacity_ms4b >> 4;
}

static inline int
findprobe(RobinHoodHash* rhh, OPHash hasher, uintptr_t idx)
{
  const size_t keysize = rhh->keysize;
  const size_t valsize = rhh->valsize;
  const size_t bucket_size = keysize + valsize + 1;
  uint64_t hashed_key;

  for (int i = 0; i <= rhh->longest_probes; i++)
    {
      hashed_key = hasher(&rhh->data[idx*bucket_size + 1], keysize);
      if (hash_with_probe(rhh, hashed_key, i) == idx)
        return i;
    }
  OP_LOG_ERROR(logger, "Didn't find any match probe!\n");
  return -1;
}

bool RHHPut(RobinHoodHash* rhh, OPHash hasher, void* key, void* val)
{
  const size_t keysize = rhh->keysize;
  const size_t valsize = rhh->valsize;
  const size_t bucket_size = keysize + valsize + 1;
  uintptr_t idx;
  int probe, old_probe, visit;
  uint8_t bucket_cpy[bucket_size];
  uint8_t bucket_tmp[bucket_size];
  uint64_t hashed_key;

  bucket_cpy[0] = 1;
  memcpy(&bucket_cpy[1], key, keysize);
  memcpy(&bucket_cpy[1 + keysize], val, valsize);

  if (rhh->objcnt >= rhh->objcnt_limit)
    return false;

  probe = 0;
  visit = 0;
  while (true)
    {
      hashed_key = hasher(&bucket_cpy[1], keysize);
      idx = hash_with_probe(rhh, hashed_key, probe);
      if (!rhh->data[idx*bucket_size])
        {
          memcpy(&rhh->data[idx*bucket_size], bucket_cpy, bucket_size);
          rhh->longest_probes = probe > rhh->longest_probes ?
            probe : rhh->longest_probes;
          rhh->objcnt++;
          if (probe < 30)
            rhh->stats[probe]++;
          else
            OP_LOG_WARN(logger, "Large probe: %d\n", probe);
          return true;
        }
      else if (!memcmp(&rhh->data[idx*bucket_size + 1],
                       &bucket_cpy[1], keysize))
        {
          memcpy(&rhh->data[idx*bucket_size], bucket_cpy, bucket_size);
          return true;
        }
      old_probe = findprobe(rhh, hasher, idx);

      if (probe > old_probe)
        {
          if (old_probe < 30)
            rhh->stats[old_probe]--;
          if (probe < 30)
            rhh->stats[probe]++;
          else
            OP_LOG_WARN(logger, "Large probe: %d\n", probe);
          memcpy(bucket_tmp, &rhh->data[idx*bucket_size], bucket_size);
          memcpy(&rhh->data[idx*bucket_size], bucket_cpy, bucket_size);
          memcpy(bucket_cpy, bucket_tmp, bucket_size);
          rhh->longest_probes = probe > rhh->longest_probes ?
            probe : rhh->longest_probes;
          probe = old_probe;
        }
        probe++;
    }
}

static inline bool
RHHSearchIdx(RobinHoodHash* rhh, OPHash hasher, void* key, uintptr_t* idx)
{
  const size_t keysize = rhh->keysize;
  const size_t valsize = rhh->valsize;
  const size_t bucket_size = keysize + valsize + 1;
  uint64_t hashed_key;

  hashed_key = hasher(key, keysize);

  for (int probe = 0; probe <= rhh->longest_probes; probe++)
    {
      *idx = hash_with_probe(rhh, hashed_key, probe);
      if (!rhh->data[*idx*bucket_size])
        return false;
      if (!memcmp(key, &rhh->data[*idx*bucket_size + 1], keysize))
        return true;
    }
  return false;
}

void* RHHDelete(RobinHoodHash* rhh, OPHash hasher, void* key)
{
  const size_t keysize = rhh->keysize;
  const size_t valsize = rhh->valsize;
  const size_t bucket_size = keysize + valsize + 1;
  uintptr_t idx, premod_idx, candidate_idx;
  uintptr_t mask = (1ULL << (64 - rhh->capacity_clz)) - 1;
  int candidates;

  if (!RHHSearchIdx(rhh, hasher, key, &idx))
    return NULL;

  rhh->objcnt--;
  while (true)
    {
    next_iter:
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
          for (int extra = 0; extra < candidates; extra++)
            {
              candidate_idx =
                ((premod_idx + extra + (probe + 1)*(probe + 1)*2
                  - probe*probe*2) & mask) * rhh->capacity_ms4b >> 4;
              if (rhh->data[candidate_idx * bucket_size] &&
                  hash_with_probe(rhh,
                                  hasher(&rhh->data[candidate_idx
                                                    * bucket_size + 1],
                                         keysize),
                                  probe + 1) == candidate_idx)
                {
                  rhh->stats[probe+1]--;
                  rhh->stats[probe]++;
                  if (probe+1 == rhh->longest_probes &&
                      rhh->stats[probe+1] == 0)
                    rhh->longest_probes--;
                  memcpy(&rhh->data[idx*bucket_size],
                         &rhh->data[candidate_idx*bucket_size],
                         bucket_size);
                  idx = candidate_idx;
                  goto next_iter;
                }
            }
        }
      // TODO: use 2 as tombstone
      // TODO: only iterate deleted.probe times. That's what it can
      // contributes
      rhh->data[idx*bucket_size] = 0;
      return &rhh->data[idx*bucket_size + 1 + keysize];
    }
}

void RHHPrintStat(RobinHoodHash* rhh)
{
  for (int i = 0; i < 30; i++)
    printf("probe %02d: %d\n", i, rhh->stats[i]);
}

void* RHHGet(RobinHoodHash* rhh, OPHash hasher, void* key)
{
  const size_t keysize = rhh->keysize;
  const size_t valsize = rhh->valsize;
  const size_t bucket_size = keysize + valsize + 1;
  uintptr_t idx;
  if (RHHSearchIdx(rhh, hasher, key, &idx))
    return &rhh->data[idx*bucket_size + keysize + 1];
  return NULL;
}
/* robin_hood.c ends here */
