/* generic_table.c ---
 *
 * Filename: generic_table.c
 * Description:
 * Author: Felix Chern
 * Maintainer:
 * Copyright: (c) 2017 Felix Chern
 * Created: Mon Jun 26 20:02:56 2017 (-0700)
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

#define PROBE_STATS_SIZE 256


#include <stdio.h> // TODO use op_log instead
#include <inttypes.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include "opic/common/op_assert.h"
#include "opic/common/op_utils.h"
#include "opic/common/op_log.h"
#include "opic/op_malloc.h"
#include "generic_table.h"

struct GenericTable
{
  uint64_t objcnt;
  uint8_t capacity_clz;    // leading zeros of capacity
  uint8_t capacity_ms4b;   // most significant 4 bits
  uint16_t longest_probes;
  size_t keysize;
  size_t valsize;
  uint32_t stats[PROBE_STATS_SIZE];
  opref_t bucket_ref;
};


bool
TableNew(OPHeap* heap, GenericTable** table,
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

  *table = OPCalloc(heap, 1, sizeof(GenericTable));
  if (!*table)
    return false;
  bucket_ptr = OPCalloc(heap, 1, bucket_size * capacity);
  if (!bucket_ptr)
    {
      OPDealloc(table);
      return false;
    }
  (*table)->bucket_ref = OPPtr2Ref(bucket_ptr);
  (*table)->capacity_clz = capacity_clz;
  (*table)->capacity_ms4b = capacity_ms4b;
  (*table)->keysize = keysize;
  (*table)->valsize = valsize;
  return true;
}

void
TableDestroy(GenericTable* table)
{
  OPDealloc(OPRef2Ptr(table, table->bucket_ref));
  OPDealloc(table);
}

void TablePrintStat(GenericTable* table)
{
  for (int i = 0; i < PROBE_STATS_SIZE; i++)
    if (table->stats[i])
      printf("probe %02d: %d\n", i, table->stats[i]);
}


static inline uintptr_t
linear_probe(GenericTable* table, uint64_t key, int probe)
{
  uint64_t mask = (1ULL << (64 - table->capacity_clz)) - 1;
  uint64_t probed_hash = key + probe * 2;

  return (probed_hash & mask) * table->capacity_ms4b >> 4;
}

static inline uintptr_t
quadratic_probe(GenericTable* table, uint64_t key, int probe)
{
  uint64_t mask = (1ULL << (64 - table->capacity_clz)) - 1;
  uint64_t probed_hash = key + probe * probe * 2;

  return (probed_hash & mask) * table->capacity_ms4b >> 4;
}

static inline uintptr_t
double_hashing_probe(GenericTable* table, uint64_t key, int probe)
{
  uint64_t mask = (1ULL << (64 - table->capacity_clz)) - 1;
  uint64_t up32key = key >> 32;
  uint64_t probed_hash = key + up32key * probe;

  return (probed_hash & mask) * table->capacity_ms4b >> 4;
}

static inline void
IncreaseProbeStat(GenericTable* table, int probe)
{
  table->objcnt++;
  table->longest_probes = probe > table->longest_probes ?
    probe : table->longest_probes;
  table->stats[probe]++;
}

bool LPInsertCustom(GenericTable* table, OPHash hasher,
                    void* key, void* value)
{
  const size_t keysize = table->keysize;
  const size_t valsize = table->valsize;
  const size_t bucket_size = keysize + valsize + 1;
  const uint64_t hashed_key = hasher(key, keysize);

  uint8_t* buckets;
  int probe;
  uintptr_t idx;

  buckets = OPRef2Ptr(table, table->bucket_ref);
  probe = 0;

  while (true)
    {
      idx = linear_probe(table, hashed_key, probe);
      if (buckets[idx * bucket_size] != 1)
        {
          IncreaseProbeStat(table, probe);
          buckets[idx * bucket_size] = 1;
          memcpy(&buckets[idx * bucket_size + 1], key, keysize);
          memcpy(&buckets[idx * bucket_size + 1 + keysize],
                 value, valsize);
          return true;
        }
      if (!memcmp(key, &buckets[idx * bucket_size + 1], keysize))
        {
          // duplicate case
          memcpy(&buckets[idx * bucket_size + 1 + keysize],
                 value, valsize);
          return true;
        }
      probe++;
    }
  return true;
}

void* LPGetCustom(GenericTable* table, OPHash hasher, void* key)
{
  const size_t keysize = table->keysize;
  const size_t valsize = table->valsize;
  const size_t bucket_size = keysize + valsize + 1;
  const uint64_t hashed_key = hasher(key, keysize);

  uint8_t* buckets;
  uintptr_t idx;
  buckets = OPRef2Ptr(table, table->bucket_ref);

  for (int probe = 0; probe <= table->longest_probes; probe++)
    {
      idx = linear_probe(table, hashed_key, probe);
      switch(buckets[idx * bucket_size])
        {
        case 0: return NULL;
        case 2: continue;
        default: (void)0;
        }
      if (!memcmp(key, &buckets[idx * bucket_size + 1], keysize))
        return &buckets[idx * bucket_size + 1 + keysize];
    }
  return NULL;
}

bool QPInsertCustom(GenericTable* table, OPHash hasher,
                    void* key, void* value)
{
  const size_t keysize = table->keysize;
  const size_t valsize = table->valsize;
  const size_t bucket_size = keysize + valsize + 1;
  const uint64_t hashed_key = hasher(key, keysize);

  uint8_t* buckets;
  int probe;
  uintptr_t idx;

  buckets = OPRef2Ptr(table, table->bucket_ref);
  probe = 0;

  while (true)
    {
      idx = quadratic_probe(table, hashed_key, probe);
      if (buckets[idx * bucket_size] != 1)
        {
          IncreaseProbeStat(table, probe);
          buckets[idx * bucket_size] = 1;
          memcpy(&buckets[idx * bucket_size + 1], key, keysize);
          memcpy(&buckets[idx * bucket_size + 1 + keysize],
                 value, valsize);
          return true;
        }
      if (!memcmp(key, &buckets[idx * bucket_size + 1], keysize))
        {
          // duplicate case
          memcpy(&buckets[idx * bucket_size + 1 + keysize],
                 value, valsize);
          return true;
        }
      probe++;
    }
  return true;
}

void* QPGetCustom(GenericTable* table, OPHash hasher, void* key)
{
  const size_t keysize = table->keysize;
  const size_t valsize = table->valsize;
  const size_t bucket_size = keysize + valsize + 1;
  const uint64_t hashed_key = hasher(key, keysize);

  uint8_t* buckets;
  uintptr_t idx;
  buckets = OPRef2Ptr(table, table->bucket_ref);

  for (int probe = 0; probe <= table->longest_probes; probe++)
    {
      idx = quadratic_probe(table, hashed_key, probe);
      switch(buckets[idx * bucket_size])
        {
        case 0: return NULL;
        case 2: continue;
        default: (void)0;
        }
      if (!memcmp(key, &buckets[idx * bucket_size + 1], keysize))
        return &buckets[idx * bucket_size + 1 + keysize];
    }
  return NULL;
}

bool DHInsertCustom(GenericTable* table, OPHash hasher,
                    void* key, void* value)
{
  const size_t keysize = table->keysize;
  const size_t valsize = table->valsize;
  const size_t bucket_size = keysize + valsize + 1;
  const uint64_t hashed_key = hasher(key, keysize);

  uint8_t* buckets;
  int probe;
  uintptr_t idx;

  buckets = OPRef2Ptr(table, table->bucket_ref);
  probe = 0;

  while (true)
    {
      idx = double_hashing_probe(table, hashed_key, probe);
      if (buckets[idx * bucket_size] != 1)
        {
          IncreaseProbeStat(table, probe);
          buckets[idx * bucket_size] = 1;
          memcpy(&buckets[idx * bucket_size + 1], key, keysize);
          memcpy(&buckets[idx * bucket_size + 1 + keysize],
                 value, valsize);
          return true;
        }
      if (!memcmp(key, &buckets[idx * bucket_size + 1], keysize))
        {
          // duplicate case
          memcpy(&buckets[idx * bucket_size + 1 + keysize],
                 value, valsize);
          return true;
        }
      probe++;
    }
  return true;
}

void* DHGetCustom(GenericTable* table, OPHash hasher, void* key)
{
  const size_t keysize = table->keysize;
  const size_t valsize = table->valsize;
  const size_t bucket_size = keysize + valsize + 1;
  const uint64_t hashed_key = hasher(key, keysize);

  uint8_t* buckets;
  uintptr_t idx;
  buckets = OPRef2Ptr(table, table->bucket_ref);

  for (int probe = 0; probe <= table->longest_probes; probe++)
    {
      idx = double_hashing_probe(table, hashed_key, probe);
      switch(buckets[idx * bucket_size])
        {
        case 0: return NULL;
        case 2: continue;
        default: (void)0;
        }
      if (!memcmp(key, &buckets[idx * bucket_size + 1], keysize))
        return &buckets[idx * bucket_size + 1 + keysize];
    }
  return NULL;
}
/* generic_table.c ends here */
