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
  uint32_t seed;
  size_t keysize;
  uint8_t* key;
  //opref_t* value;
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
  size_t malloc_total_size, malloc_header_size,
    malloc_key_size, malloc_val_size;
  uintptr_t rhh_base;

  capacity = (uint64_t)(num_objects / load);
  capacity_clz = __builtin_clzl(capacity);
  capacity_msb = 64 - capacity_clz;
  capacity_ms4b = round_up_div(capacity, 1UL << (capacity_msb - 4));
  capacity_ms4b |= 1;
  capacity = (uint64_t)capacity_ms4b << (capacity_msb - 4);

  malloc_header_size = sizeof(RobinHoodHash);
  malloc_key_size = (keysize + 4 + 8) * capacity;
  //malloc_val_size = sizeof(opref_t) * capacity;
  malloc_total_size = malloc_header_size + malloc_key_size;
  //+ malloc_val_size;

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
  (*rhh)->key = (uint8_t*)(rhh_base + malloc_header_size);
  //(*rhh)->value = (opref_t*)(rhh_base + malloc_header_size + malloc_key_size);
  return true;
}

void
RHHDestroy(RobinHoodHash* rhh)
{
  OPDealloc(rhh);
}


static inline uint64_t
hash(RobinHoodHash* rhh, void* key, uint32_t* crc)
{
  uint64_t hashed_val[2];
  MurmurHash3_crc_x64_128(key, rhh->keysize, rhh->seed, hashed_val, crc);
  return hashed_val[0];
}

static inline uintptr_t
hash_with_probe(RobinHoodHash* rhh, uint64_t key, int probe)
{
  uintptr_t mask = (1ULL << (64 - rhh->capacity_clz)) - 1;
  // linear
  //uint64_t probed_hash = key + probe;
  // quadratic
  uint64_t probed_hash = key + probe * probe;
  //uint64_t probed_hash = (key >> probe) | (key << (64 - probe));
  return (probed_hash & mask) * rhh->capacity_ms4b >> 4;
  //return (hash(rhh, rhh->seed + probe * probe, key) % rhh->capacity);
}

static inline int
findprobe(RobinHoodHash* rhh, uintptr_t idx)
{
  const size_t keysize = rhh->keysize;
  uint32_t unused_crc;

  for (int i = 0; i <= rhh->longest_probes; i++)
    {
      if (hash_with_probe(rhh,
                          hash(rhh, &rhh->key[idx * (keysize + 4 + 8) + 4],
                               &unused_crc),
                          i) == idx)
        {
          return i;
        }
    }
  printf("Didn't find any match probe!\n");
  return -1;
}

bool RHHPut(RobinHoodHash* rhh, void* key, opref_t val_ref)
{
  const size_t keysize = rhh->keysize;
  uintptr_t idx;
  uintptr_t visited_idx[VISIT_IDX_CACHE];
  int probe, old_probe, visit;
  uint8_t key_cpy[keysize];
  uint8_t key_tmp[keysize];
  opref_t val_cpy, val_tmp;
  uint32_t crc, crc_tmp;
  uint64_t hashed_key;

  memcpy(key_cpy, key, keysize);
  val_cpy = val_ref;

  if (rhh->objcnt >= rhh->objcnt_limit)
    return false;

  probe = 0;
  visit = 0;
  while (true)
    {
      hashed_key = hash(rhh, key_cpy, &crc);
      crc |= 1;
    next_iter:
      idx = hash_with_probe(rhh, hashed_key, probe);
      if (!(uint32_t)rhh->key[idx * (keysize + 4 + 8)])
        {
          memcpy(&rhh->key[idx * (keysize + 4 + 8) + 4], key_cpy, keysize);
          *(uint32_t*)&rhh->key[idx * (keysize + 4 + 8)] = crc;
          *(opref_t*)&rhh->key[idx * (keysize + 4 + 8)
                               + 4 + keysize] = val_cpy;
          rhh->longest_probes = probe > rhh->longest_probes ?
            probe : rhh->longest_probes;
          rhh->objcnt++;
          if (probe < 30)
            rhh->stats[probe]++;
          else
            OP_LOG_WARN(logger, "Large probe: %d\n", probe);
          return true;
        }
      else if (((uint32_t)rhh->key[idx * (keysize + 4 + 8)] == crc) &&
               !memcmp(&rhh->key[idx * (keysize + 4 + 8) + 4],
                       key_cpy, keysize))
        {
          // TODO log duplicate key
          //rhh->value[idx] = val_cpy;
          *(opref_t*)&rhh->key[idx * (keysize + 4 + 8)
                               + 4 + keysize] = val_cpy;
          return true;
        }
      old_probe = findprobe(rhh, idx);

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
            if (idx == visited_idx[i % VISIT_IDX_CACHE])
              {
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
          *(uint32_t*)&rhh->key[idx * (keysize + 4 + 8)] = crc;
          memcpy(key_tmp, &rhh->key[idx * (keysize + 4 + 8) + 4], keysize);
          memcpy(&rhh->key[idx * (keysize + 4 + 8) + 4], key_cpy, keysize);
          memcpy(key_cpy, key_tmp, keysize);
          val_tmp = (opref_t)rhh->key[idx * (keysize + 4 + 8)
                                      + 4 + keysize];
          *(opref_t*)&rhh->key[idx * (keysize + 4 + 8)
                               + 4 + keysize] = val_cpy;
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

bool RHHSearch(RobinHoodHash* rhh, void* key, opref_t* val)
{
  size_t keysize;
  uint64_t hashed_key;
  uintptr_t idx;
  uint32_t record_crc, crc;

  keysize = rhh->keysize;
  hashed_key = hash(rhh, key, &crc);
  crc |= 1;

  for (int probe = 0; probe <= rhh->longest_probes; probe++)
    {
      idx = hash_with_probe(rhh, hashed_key, probe);
      record_crc = (uint32_t)rhh->key[idx * (keysize + 4 + 8)];
      if (!record_crc)
        return false;
      if (record_crc == crc &&
          !memcmp(key, &rhh->key[idx * (keysize + 4 + 8) + 4], keysize))
        {
          *val = (opref_t)rhh->key[idx * (keysize + 4 + 8)
                                   + 4 + keysize];
          return true;
        }
    }
  return false;
}


void* RHHGet(RobinHoodHash* rhh, void* key)
{
  opref_t val;
  if (RHHSearch(rhh, key, &val))
    return OPRef2Ptr(rhh, val);
  return NULL;
}
/* robin_hood.c ends here */
