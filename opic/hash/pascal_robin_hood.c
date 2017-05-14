/* pascal_robin_hood.c ---
 *
 * Filename: pascal_robin_hood.c
 * Description:
 * Author: Felix Chern
 * Maintainer:
 * Created: Sat May 13 15:57:42 2017 (-0700)
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
 * it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this program.  If not, see
 * <http://www.gnu.org/licenses/>.
 */

/* Code: */

#define PROBE_STATS_SIZE 64
#define DEFAULT_LARGE_DATA_THRESHOLD (1UL << 30)

OP_LOGGER_FACTORY(logger, "opic.hash.pascal_robin_hood");

struct PascalRobinHoodHash
{
  uint64_t objcnt;
  uint64_t objcnt_high;
  uint64_t objcnt_low;
  uint64_t large_data_threshold;
  uint8_t capacity_clz;    // leading zeros of capacity
  uint8_t capacity_ms4b;   // most significant 4 bits
  uint16_t longest_probes;
  size_t valsize;
  uint32_t stats[PROBE_STATS_SIZE];
  opref_t bucket_ref;
};

static inline uintptr_t
hash_with_probe(PascalRobinHoodHash* rhh, uint64_t key, int probe)
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
findprobe(PascalRobinHoodHash* rhh, OPHash hasher, uintptr_t idx)
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

bool PRHHNew(OPHeap* heap, PascalRobinHoodHash** rhh_ref,
             uint64_t num_objects, double load, size_t valsize);

static inline
uint64_t PRHHCapacityInternal(uint8_t capacity_clz, uint8_t capacity_ms4b)
{
  return (1UL << (64 - capacity_clz - 4)) * capacity_ms4b;
}

uint64_t PRHHCapacity(PascalRobinHoodHash* rhh)
{
  return PRHHCapacityInternal(rhh->capacity_clz, rhh->capacity_ms4b);
}

static bool
PRHHSizeUp(PascalRobinHoodHash* rhh, OPHash hasher)
{
  const size_t keysize = sizeof(oplenref_t);
  const size_t valsize = rhh->valsize;
  const size_t bucket_size = keysize + valsize + 1;
  const size_t large_data_threshold = rhh->large_data_threshold;
  uint8_t* old_buckets;
  uint8_t* new_buckets;
  uint8_t new_capacity_ms4b, new_capacity_clz;
  uint64_t old_capacity, new_capacity;
  uintptr_t bucket_base;
  void* oldkey;
  void* oldval;

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
          bucket_base = (uintptr_t)&old_buckets[idx*bucket_size];
          oldkey = (void*)(bucket_base + 1);
          oldval = (void*)(bucket_base + 1 + keysize);
          op_assert(RHHPutCustom(rhh, hasher, oldkey, oldval),
                    "Resize and insert with idx: %" PRIu64 "\n", idx);
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
  uintptr_t bucket_base;
  void* oldkey;
  void* oldval;

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
          bucket_base = (uintptr_t)&old_buckets[idx*bucket_size];
          oldkey = (void*)(bucket_base + 1);
          oldval = (void*)(bucket_base + 1 + keysize);
          op_assert(RHHPutCustom(rhh, hasher, oldkey, oldval),
                    "Resize and insert with idx: %" PRIu64 "\n", idx);
        }
    }
  OPDealloc(old_buckets);
  return true;
}
bool PRHHPutCustom(PascalRobinHoodHash* rhh, OPHash hasher,
                   void* key, size_t keysize, void* val)
{
  const size_t refsize = sizeof(oplenref_t);
  const size_t valsize = rhh->valsize;
  const size_t bucket_size = refsize + valsize + 1;
  void* keyptr;
  oplenref_t keyref, recordref;
  size_t record_keysize;
  uint8_t* buckets;
  OPHeap* heap;
  uintptr_t idx;
  int probe, old_probe;
  uint8_t bucket_cpy[bucket_size];
  uint8_t bucket_tmp[bucket_size];
  uint64_t hashed_key;

  heap = ObtainOPHeap(rhh);
  buckets = OPRef2Ptr(rhh, rhh->bucket_ref);
  bucket_cpy[0] = 1;
  keyptr = OPCalloc(heap, 1, keysize);
  keyref = OPPtr2LenRef(keyptr);
  memcpy(keyptr, key, keysize);
  memcpy(&bucket_cpy[1], keyref, refsize);
  memcpy(&bucket_cpy[1 + refsize], val, valsize);

  probe = 0;
  while (true)
    {
      hashed_key = hasher(&bucket_cpy[1], refsize);
      idx = hash_with_probe(rhh, hashed_key, probe);
      if (buckets[idx*bucket_size] != 1)
        {
          memcpy(&buckets[idx*bucket_size], bucket_cpy, bucket_size);
          rhh->longest_probes = probe > rhh->longest_probes ?
            probe : rhh->longest_probes;
          rhh->objcnt++;
          if (probe < PROBE_STATS_SIZE)
            rhh->stats[probe]++;
          else
            OP_LOG_WARN(logger, "Large probe: %d\n", probe);
          goto size_check;
        }
      else
        {
          keyref = *(oplenref_t*)&buckets[idx*bucket_size + 1];
          recordref = *(oplenref_t*)&bucket_cpy[1];
          record_keysize = OPLenRef2Size(recordref);
          if (OPLenRef2Size(keyref) == record_keysize &&
              !memcmp(OPLenRef2Ptr(heap, keyref),
                      OPLenRef2Ptr(heap, recordref),
                      record_keysize))
            {
              OPDealloc(OPLenRef2Ptr(heap, keyref));
              memcpy(&buckets[idx*bucket_size], bucket_cpy, bucket_size);
              goto size_check;
            }
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
          memcpy(bucket_tmp, &buckets[idx*bucket_size], bucket_size);
          memcpy(&buckets[idx*bucket_size], bucket_cpy, bucket_size);
          memcpy(bucket_cpy, bucket_tmp, bucket_size);
          rhh->longest_probes = probe > rhh->longest_probes ?
            probe : rhh->longest_probes;
          probe = old_probe;
        }
        probe++;
    }
 size_check:
  if (rhh->objcnt > rhh->objcnt_high)
    {
      return RHHSizeUp(rhh, hasher);
    }
  return true;
}

void* PRHHGetCustom(PascalRobinHoodHash* rhh, OPHash hasher,
                    void* key, size_t keysize);


/* pascal_robin_hood.c ends here */
