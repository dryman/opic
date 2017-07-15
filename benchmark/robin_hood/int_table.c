/* int_table.c ---
 *
 * Filename: int_table.c
 * Description:
 * Author: Felix Chern
 * Maintainer:
 * Copyright: (c) 2017 Felix Chern
 * Created: Sun Jul  9 07:42:37 2017 (-0700)
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



#define PROBE_STATS_SIZE 2048


#include <stdio.h> // TODO use op_log instead
#include <inttypes.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include "opic/common/op_assert.h"
#include "opic/common/op_utils.h"
#include "opic/common/op_log.h"
#include "opic/op_malloc.h"
#include "int_table.h"

struct IntTable
{
  uint64_t objcnt;
  uint8_t capacity_clz;    // leading zeros of capacity
  uint8_t capacity_ms4b;   // most significant 4 bits
  uint16_t longest_probes;
  size_t keysize;
  size_t valsize;
  uint32_t stats[PROBE_STATS_SIZE];
  opref_t bucket_ref;
  uint64_t empty_key;
  uint64_t delete_key;
};


bool
IntTableNew(OPHeap* heap, IntTable** table,
            uint64_t num_objects, double load, size_t valsize,
            uint64_t empty_key,
            uint64_t delete_key)
{
  uint64_t capacity;
  uint32_t capacity_clz, capacity_ms4b, capacity_msb;
  size_t bucket_size;
  uint8_t* bucket_ptr;

  op_assert(load > 0.0 && load < 1.0,
            "load %lf must within close interval (0.0, 1.0)\n", load);
  capacity = (uint64_t)(num_objects / load);
  if (capacity < 8)
    capacity = 8;
  capacity_clz = __builtin_clzl(capacity);
  capacity_msb = 64 - capacity_clz;
  capacity_ms4b = round_up_div(capacity, 1UL << (capacity_msb - 4));
  capacity = (uint64_t)capacity_ms4b << (capacity_msb - 4);

  bucket_size = 8 + valsize;

  *table = OPCalloc(heap, 1, sizeof(IntTable));
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
  (*table)->valsize = valsize;
  (*table)->empty_key = empty_key;
  (*table)->delete_key = delete_key;

  uint64_t *keyref;
  for (uint64_t i = 0; i < capacity; i++)
    {
      keyref = (uint64_t*)&bucket_ptr[i * bucket_size];
      *keyref = empty_key;
    }
  return true;
}

// int table with meta, like other string impl
bool
IntTableNew2(OPHeap* heap, IntTable** table,
             uint64_t num_objects, double load,
             size_t keysize, size_t valsize)
{
  uint64_t capacity;
  uint32_t capacity_clz, capacity_ms4b, capacity_msb;
  size_t bucket_size;
  uint8_t* bucket_ptr;

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

  *table = OPCalloc(heap, 1, sizeof(IntTable));
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
IntTableDestroy(IntTable* table)
{
  OPDealloc(OPRef2Ptr(table, table->bucket_ref));
  OPDealloc(table);
}

uint32_t IntTableMaxProbe(IntTable* table)
{
  return table->longest_probes;
}

uint32_t IntTableProbeStat(IntTable* table, uint32_t idx)
{
  if (idx < PROBE_STATS_SIZE)
    return table->stats[idx];
  return 0;
}

static inline void
IncreaseProbeStat(IntTable* table, int probe)
{
  table->objcnt++;
  table->longest_probes = probe > table->longest_probes ?
    probe : table->longest_probes;
  table->stats[probe]++;
}

static inline uintptr_t
quadratic_probe(IntTable* table, uint64_t key, int probe)
{
  uint64_t mask = (1ULL << (64 - table->capacity_clz)) - 1;
  uint64_t probed_hash = key + probe * probe * 2;
  //uint64_t probed_hash = key + probe * (probe + 1);

  return (probed_hash & mask) * table->capacity_ms4b >> 4;
}

bool QPIntInsertCustom(IntTable* table, OPHash hasher,
                    uint64_t key, void* value)
{
  const size_t valsize = table->valsize;
  const size_t bucket_size = 8 + valsize;
  const uint64_t hashed_key = hasher(&key, 8);

  uint8_t* buckets;
  int probe;
  uintptr_t idx;
  uint64_t* keyref;

  buckets = OPRef2Ptr(table, table->bucket_ref);
  probe = 0;

  while (true)
    {
      idx = quadratic_probe(table, hashed_key, probe);
      keyref = (uint64_t*)&buckets[idx * bucket_size];
      if (*keyref == table->empty_key ||
          *keyref == table->delete_key)
        {
          IncreaseProbeStat(table, probe);
          *keyref = key;
          memcpy(&buckets[idx * bucket_size + 8],
                 value, valsize);
          return true;
        }
      if (key == *keyref)
        {
          // duplicate case
          memcpy(&buckets[idx * bucket_size + 8],
                 value, valsize);
          return true;
        }
      probe++;
    }
  return false;
}

void* QPIntGetCustom(IntTable* table, OPHash hasher, uint64_t key)
{
  const size_t valsize = table->valsize;
  const size_t bucket_size = 8 + valsize;
  const uint64_t hashed_key = hasher(&key, 8);
  const uint64_t mask = (1ULL << (64 - table->capacity_clz)) - 1;

  uint8_t* buckets;
  uint64_t* keyref;
  uintptr_t idx, idx_next;
  buckets = OPRef2Ptr(table, table->bucket_ref);

  for (int probe = 0; probe <= table->longest_probes; probe++)
    {
      idx = quadratic_probe(table, hashed_key, probe);
      keyref = (uint64_t*)&buckets[idx * bucket_size];
      if (*keyref == table->empty_key)
        return NULL;
      /* if (!memcmp(&key, keyref, 8)) */
      /*   return &buckets[idx * bucket_size + 8]; */
      /* if (memeq(&key, keyref, 8)) */
      /*   return &buckets[idx * bucket_size + 8]; */
      if (*keyref == key)
        return &buckets[idx * bucket_size + 8];
    }
  return NULL;
}

bool QPIntInsertCustom2(IntTable* table, OPHash hasher,
                        uint64_t key, void* value)
{
  const size_t valsize = table->valsize;
  const size_t bucket_size = 8 + valsize + 1;
  const uint64_t hashed_key = hasher(&key, 8);

  uint8_t* buckets;
  int probe;
  uintptr_t idx;
  uint64_t* keyref;

  buckets = OPRef2Ptr(table, table->bucket_ref);
  probe = 0;

  while (true)
    {
      idx = quadratic_probe(table, hashed_key, probe);
      keyref = (uint64_t*)&buckets[idx * bucket_size + 1];
      if (buckets[idx * bucket_size] != 1)
        {
          IncreaseProbeStat(table, probe);
          buckets[idx * bucket_size] = 1;
          *keyref = key;
          memcpy(&buckets[idx * bucket_size + 9],
                 value, valsize);
          return true;
        }
      if (key == *keyref)
        {
          // duplicate case
          memcpy(&buckets[idx * bucket_size + 9],
                 value, valsize);
          return true;
        }
      probe++;
    }
  return false;
}

void* QPIntGetCustom2(IntTable* table, OPHash hasher, uint64_t key)
{
  const size_t keysize = table->keysize;
  const size_t valsize = table->valsize;
  const size_t bucket_size = keysize + valsize + 1;
  const uint64_t hashed_key = hasher(&key, keysize);
  const uint64_t mask = (1ULL << (64 - table->capacity_clz)) - 1;

  uint8_t* buckets;
  uint64_t* keyref;
  uintptr_t idx, idx_next;
  buckets = OPRef2Ptr(table, table->bucket_ref);

  for (int probe = 0; probe <= table->longest_probes; probe++)
    {
      idx = quadratic_probe(table, hashed_key, probe);
      keyref = (uint64_t*)&buckets[idx * bucket_size + 1];
      switch(buckets[idx * bucket_size])
        {
        case 0: return NULL;
        case 2: continue;
        default: (void)0;
        }
      /* if (!memcmp(&key, keyref, 8)) */
      /*   return &buckets[idx * bucket_size + 8]; */
      if (memeq(&key, keyref, 8))
        return &buckets[idx * bucket_size + keysize + 1];
      /* if (*keyref == key) */
      /*   return &buckets[idx * bucket_size + 9]; */
    }
  return NULL;
}


/* int_table.c ends here */
