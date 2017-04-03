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
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include "opic/op_malloc.h"
#include "murmurhash3.h"
#include "robin_hood.h"

// for experiment and benchmark, let's define macro for now

struct FixWidthRobinHoodHash
{
  uint64_t capacity;
  uint64_t objcnt_limit;
  uint64_t objcnt;
  int32_t expected_probes;
  int32_t longest_probes;
  uint32_t seed;
  size_t keysize;
  uintptr_t* key;
  uintptr_t* value;
  // Use enum to choose hash function? (extra branch here..)
  // Need to benchmark to see the enum overhead
  // candidates: xxhash, highwayhash
};

static inline uint64_t
hash(FixWidthRobinHoodHash* fwrhh, void* key)
{
  uint64_t hashed_val[2];
  MurmurHash3_x64_128(key, fwrhh->keysize, fwrhh->seed, hashed_val);
  return hashed_val[1];
}

static inline uintptr_t
hash_with_probe(FixWidthRobinHoodHash* fwrhh, void* key, int probe)
{
  int probe_offset;
  probe = probe - fwrhh->expected_probes;
  probe_offset = probe < 0 ? -2 * probe - 1 : 2 * probe;
  return (hash(fwrhh, key) + probe_offset * probe_offset) % fwrhh->capacity;
}

static inline int
findprobe(FixWidthRobinHoodHash* fwrhh, uintptr_t idx)
{
  const size_t keysize = fwrhh->keysize;
  uintptr_t key_base_location, key_real_location;
  int probe_offset;

  key_real_location = idx * keysize;
  key_base_location = hash(fwrhh, &fwrhh->key[key_real_location])
    % fwrhh->capacity;
  if (key_real_location < key_base_location)
    key_real_location += fwrhh->capacity;
  probe_offset = key_real_location - key_base_location;
  if (probe_offset & 0x01)
    {
      return fwrhh->expected_probes - ((probe_offset + 1) / 2);
    }
  else
    {
      return fwrhh->expected_probes + (probe_offset / 2);
    }
}

bool insertKV(FixWidthRobinHoodHash* fwrhh, void* key, void* value)
{
  const size_t keysize = fwrhh->keysize;
  uintptr_t idx;
  int probe, old_probe;
  uint8_t key_cpy[keysize];
  uint8_t key_tmp[keysize];
  uint8_t empty_key[keysize];
  uintptr_t val_cpy;
  uintptr_t val_tmp;

  memset(empty_key, 0x00, keysize);
  memcpy(key_cpy, key, keysize);
  val_cpy = OPPtr2Ref(value);

  if (fwrhh->objcnt >= fwrhh->objcnt_limit)
    return false;

  probe = 0;
  while (true)
    {
      idx = hash_with_probe(fwrhh, key_cpy, probe);
      if (!memcmp(&fwrhh->key[idx * keysize], empty_key, keysize))
        {
          memcpy(&fwrhh->key[idx * keysize], key_cpy, keysize);
          fwrhh->value[idx] = val_cpy;
          fwrhh->longest_probes = probe > fwrhh->longest_probes ?
            probe : fwrhh->longest_probes;
          fwrhh->objcnt++;
          return true;
        }
      else if (!memcmp(&fwrhh->key[idx * keysize], key_cpy, keysize))
        {
          // TODO log duplicate key
          fwrhh->value[idx] = val_cpy;
          return true;
        }
      old_probe = findprobe(fwrhh, idx);
      if (probe > old_probe)
        {
          memcpy(key_tmp, &fwrhh->key[idx * keysize], keysize);
          memcpy(&fwrhh->key[idx * keysize], key_cpy, keysize);
          memcpy(key_cpy, key_tmp, keysize);
          val_tmp = fwrhh->value[idx];
          fwrhh->value[idx] = val_cpy;
          val_cpy = val_tmp;
          fwrhh->longest_probes = probe > fwrhh->longest_probes ?
            probe : fwrhh->longest_probes;
          probe = old_probe;
        }
      else
        probe++;
    }
}

bool search(FixWidthRobinHoodHash* fwrhh, void* key, uintptr_t* match_idx)
{
  size_t keysize;
  uint64_t key_raw_hash;
  uintptr_t idx;

  keysize = fwrhh->keysize;
  key_raw_hash = hash(fwrhh, key);
  for (int i = 0; i < fwrhh->longest_probes; i++)
    {
      idx = (key_raw_hash + i * i) % fwrhh->capacity;
      if (!memcmp(key, &fwrhh->key[idx * keysize], keysize))
        {
          *match_idx = idx;
          return true;
        }
    }
  return false;
}

void*
robin_hood_get(FixWidthRobinHoodHash* fwrhh, void* key)
{
  uintptr_t match_idx;
  if (search(fwrhh, key, &match_idx))
    return OPRef2Ptr(fwrhh, fwrhh->value[match_idx]);
  return NULL;
}

bool
RHH_new(OPHeap* heap, FixWidthRobinHoodHash** fwrhh,
        uint64_t size, double load, size_t keysize, uint32_t seed)
{
  uint64_t capacity;
  double capacity_d, expected_probes_d;
  size_t malloc_size;
  uintptr_t fwrhh_base;
  capacity = (uint64_t)(size / load);
  capacity_d = (double)capacity;
  expected_probes_d = log(capacity_d / (capacity_d - size)) * capacity_d / size;
  malloc_size = sizeof(FixWidthRobinHoodHash) +
    (keysize + sizeof(uintptr_t)) * capacity;
  *fwrhh = OPMallocRaw(heap, malloc_size);
  if (!*fwrhh)
    return false;

  fwrhh_base = (uintptr_t)(*fwrhh);
  memset(*fwrhh, 0x00, malloc_size);
  (*fwrhh)->capacity = capacity;
  (*fwrhh)->objcnt_limit = size;
  (*fwrhh)->expected_probes = (int32_t) expected_probes_d;
  (*fwrhh)->seed = seed;
  (*fwrhh)->keysize = keysize;
  (*fwrhh)->key = (uintptr_t*)(fwrhh_base + sizeof(FixWidthRobinHoodHash));
  (*fwrhh)->value = (uintptr_t*)(fwrhh_base + sizeof(FixWidthRobinHoodHash) +
                                 keysize * capacity);
  return true;
}

void
RHH_destroy(FixWidthRobinHoodHash* fwrhh)
{
  OPDealloc(fwrhh);
}

/* robin_hood.c ends here */
