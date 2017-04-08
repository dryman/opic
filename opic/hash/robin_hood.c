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
#include <stdio.h> // TODO remove this
#include <inttypes.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include "opic/common/op_utils.h"
#include "opic/op_malloc.h"
#include "xxHash/xxhash.h"
#include "murmurhash3.h"
#include "robin_hood.h"

#define VISIT_IDX_CACHE 16

struct RobinHoodHash
{
  uint64_t capacity;
  uint64_t objcnt_limit;
  uint64_t objcnt;
  uint8_t capacity_clz;    // leading zeros of capacity
  uint8_t capacity_ms4b;   // most significant 4 bits
  int16_t longest_probes;
  uint32_t seed;
  size_t keysize;
  uint64_t* bmap;
  uint8_t* key;
  opref_t* value;
  uint32_t stats[30];

  uint64_t reserved[8];
  // Use enum to choose hash function? (extra branch here..)
  // Need to benchmark to see the enum overhead
  // candidates: xxhash, highwayhash
};

bool
RHHNew(OPHeap* heap, RobinHoodHash** rhh,
       uint64_t num_objects, double load, size_t keysize, uint32_t seed)
{
  uint64_t capacity;
  uint32_t capacity_clz, capacity_ms4b, capacity_msb;
  size_t malloc_total_size, malloc_header_size, malloc_bmap_size,
    malloc_key_size, malloc_val_size;
  uintptr_t rhh_base;

  capacity = (uint64_t)(num_objects / load);
  capacity_clz = __builtin_clzl(capacity);
  capacity_msb = 64 - capacity_clz;
  capacity_ms4b = round_up_div(capacity, 1UL << (capacity_msb - 4));
  capacity_ms4b |= 1;
  capacity = (uint64_t)capacity_ms4b << (capacity_msb - 4);

  malloc_header_size = sizeof(RobinHoodHash);
  malloc_bmap_size = capacity / 8;
  malloc_key_size = keysize * capacity;
  malloc_val_size = sizeof(opref_t) * capacity;
  malloc_total_size = malloc_header_size + malloc_bmap_size +
    malloc_key_size + malloc_val_size;

  *rhh = OPMallocRaw(heap, malloc_total_size);
  if (!*rhh)
    return false;

  rhh_base = (uintptr_t)(*rhh);
  memset(*rhh, 0x00, malloc_total_size);
  (*rhh)->capacity = capacity;
  (*rhh)->capacity_clz = capacity_clz;
  (*rhh)->capacity_ms4b = capacity_ms4b;
  (*rhh)->objcnt_limit = num_objects;
  (*rhh)->seed = seed;
  (*rhh)->keysize = keysize;
  (*rhh)->bmap = (uint64_t*)(rhh_base + malloc_header_size);
  (*rhh)->key = (uint8_t*)(rhh_base + malloc_header_size + malloc_bmap_size);
  (*rhh)->value = (opref_t*)(rhh_base + malloc_header_size + malloc_bmap_size +
                             malloc_key_size);
  printf("clz: %d\n", (*rhh)->capacity_clz);
  return true;
}

void
RHHDestroy(RobinHoodHash* rhh)
{
  OPDealloc(rhh);
}


static inline uint64_t
hash(RobinHoodHash* rhh, void* key)
{
  //return XXH64(key, rhh->keysize, seed);
  uint64_t hashed_val[2];
  MurmurHash3_x64_128(key, rhh->keysize, rhh->seed, hashed_val);
  return hashed_val[0];

  //MurmurHash3_x86_32(key, rhh->keysize, seed, hashed_val);
  //uint64_t kk = *(uint64_t*)key;
  // return (((((((17 * kk) % 163307llu + kk) * 1597llu
  //             + kk) * 2074129llu) % 110477914016779llu
  //           + kk) * 25717llu) + 4027llu * kk)
  //   % 905035071625626043llu;
}

static inline uintptr_t
hash_with_probe(RobinHoodHash* rhh, uint64_t key, int probe)
{
  /*
  int probe_offset;
  probe = probe - rhh->expected_probes;
  probe_offset = probe > 2 * rhh->expected_probes ?
    probe : probe < 0 ?
    -2 * probe - 1 :
    2 * probe;
  return (hash(rhh, key) + probe_offset * probe_offset) % rhh->capacity;
  */
  uintptr_t mask = (1ULL << (64 - rhh->capacity_clz)) - 1;
  return ((key >> (probe * probe)) & mask) * rhh->capacity_ms4b >> 4;
  /*
  printf("clz: %d, mask %" PRIxPTR " hashed %"
         PRIxPTR " masked %" PRIxPTR "\n",
         clz, mask, hashed, masked);
  */
  //return (hash(rhh, rhh->seed + probe * probe, key) % rhh->capacity);
}

static inline int
findprobe(RobinHoodHash* rhh, uintptr_t idx)
{
  const size_t keysize = rhh->keysize;

  for (int i = 0; i <= rhh->longest_probes; i++)
    {
      if (hash_with_probe(rhh,
                          hash(rhh, &rhh->key[idx * keysize]),
                          i) == idx)
        {
          return i;
        }
    }
  printf("Didn't find any match probe!\n");
  return -1;
  /*
  key_base_location = hash(rhh, rhh->seed, &rhh->key[key_real_location])
    % rhh->capacity;
  if (key_real_location < key_base_location)
    key_real_location += rhh->capacity;
  probe_offset = (int)sqrt(key_real_location - key_base_location);
  printf("probe offset: %d\n", probe_offset);
  return probe_offset;
  */
  /*
  if (probe_offset > 2 * rhh->expected_probes)
    {
      return probe_offset;
    }
  else if (probe_offset & 0x01)
    {
      return rhh->expected_probes - ((probe_offset + 1) / 2);
    }
  else
    {
      return rhh->expected_probes + (probe_offset / 2);
    }
  */
}

bool RHHPut(RobinHoodHash* rhh, void* key, opref_t val_ref)
{
  const size_t keysize = rhh->keysize;
  uintptr_t idx, bmidx, bmbit;
  uintptr_t visited_idx[VISIT_IDX_CACHE];
  int probe, old_probe, visit;
  uint8_t key_cpy[keysize];
  uint8_t key_tmp[keysize];
  opref_t val_cpy, val_tmp;

  memcpy(key_cpy, key, keysize);
  val_cpy = val_ref;

  if (rhh->objcnt >= rhh->objcnt_limit)
    return false;

  probe = 0;
  visit = 0;
  while (true)
    {
    next_iter:
      idx = hash_with_probe(rhh, hash(rhh, key_cpy), probe);
      bmidx = idx / 64;
      bmbit = idx % 64;
      if (!(rhh->bmap[bmidx] & (1UL << bmbit)))
        {
          memcpy(&rhh->key[idx * keysize], key_cpy, keysize);
          rhh->bmap[bmidx] |= 1UL << bmbit;
          rhh->value[idx] = val_cpy;
          rhh->longest_probes = probe > rhh->longest_probes ?
            probe : rhh->longest_probes;
          rhh->objcnt++;
          if (probe < 30)
            rhh->stats[probe]++;
          else
            printf("large probe: %d\n", probe);
          return true;
        }
      else if (!memcmp(&rhh->key[idx * keysize], key_cpy, keysize))
        {
          // TODO log duplicate key
          rhh->value[idx] = val_cpy;
          return true;
        }
      old_probe = findprobe(rhh, idx);
      /*
      printf("idx: %" PRIuPTR "  key: %.6s with probe %d,"
             "old key: %.6s with probe: %d\n",
             idx,
             (char*)key_cpy, (int)probe,
             (char*)&rhh->key[idx * keysize], old_probe);
      */

      if (visit < VISIT_IDX_CACHE)
        {
          for (int i = 0; i < visit; i++)
            {
              if (idx == visited_idx[i])
                {
                  printf("found visited idx!\n");
                  probe++;
                  goto next_iter;
                }
            }
        }
      else
        {
          for (int i = visit + 1; i < visit + VISIT_IDX_CACHE; i++)
            if (idx == visited_idx[i % VISIT_IDX_CACHE])
              {
                printf("found visited idx!\n");
                probe++;
                goto next_iter;
              }
        }
      visited_idx[visit % VISIT_IDX_CACHE] = idx;
      visit++;

      if (probe > old_probe)
        {
          if (old_probe < 30)
            rhh->stats[old_probe]--;
          if (probe < 30)
            rhh->stats[probe]++;
          else
            printf("large probe: %d\n", probe);
          memcpy(key_tmp, &rhh->key[idx * keysize], keysize);
          memcpy(&rhh->key[idx * keysize], key_cpy, keysize);
          memcpy(key_cpy, key_tmp, keysize);
          val_tmp = rhh->value[idx];
          rhh->value[idx] = val_cpy;
          val_cpy = val_tmp;
          rhh->longest_probes = probe > rhh->longest_probes ?
            probe : rhh->longest_probes;
          probe = old_probe;
        }
        probe++;
    }
}

void RHHPrintStat(RobinHoodHash* rhh)
{
  for (int i = 0; i < 30; i++)
    printf("probe %02d: %d\n", i, rhh->stats[i]);
}

static inline
bool RHHSearchInternal(RobinHoodHash* rhh, void* key, uintptr_t* match_idx)
{
  size_t keysize;
  uint64_t hashed_key;
  uintptr_t idx, bmidx, bmbit;

  keysize = rhh->keysize;
  hashed_key = hash(rhh, key);

  for (int probe = 0; probe <= rhh->longest_probes; probe++)
    {
      idx = hash_with_probe(rhh, hashed_key, probe);
      bmidx = idx / 64;
      bmbit = idx % 64;
      if (!(rhh->bmap[bmidx] & (1UL << bmbit)))
        return false;
      if (!memcmp(key, &rhh->key[idx * keysize], keysize))
        {
          *match_idx = idx;
          return true;
        }
    }
  return false;
}

bool RHHSearch(RobinHoodHash* rhh, void* key, opref_t* val)
{
  uintptr_t match_idx;
  if (RHHSearchInternal(rhh, key, &match_idx))
    {
      *val = rhh->value[match_idx];
      return true;
    }
  return false;
}

void* RHHGet(RobinHoodHash* rhh, void* key)
{
  uintptr_t match_idx;
  if (RHHSearchInternal(rhh, key, &match_idx))
    return OPRef2Ptr(rhh, rhh->value[match_idx]);
  return NULL;
}
/* robin_hood.c ends here */
