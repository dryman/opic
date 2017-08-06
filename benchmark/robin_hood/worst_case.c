/* worst_case.c ---
 *
 * Filename: worst_case.c
 * Description:
 * Author: Felix Chern
 * Maintainer:
 * Copyright: (c) 2017 Felix Chern
 * Created: Sat Aug  5 16:50:17 2017 (-0700)
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <sys/types.h>
#include <stdbool.h>
#include <inttypes.h>
#include <unistd.h>
#include "opic/common/op_assert.h"
#include "opic/op_malloc.h"
#include "opic/hash/op_hash.h"
#include "opic/hash/robin_hood.h"

#include "murmurhash3.h"
#include "spookyhash-c/spookyhash.h"
#include "farmhash-c/farmhash.h"
#include "generic_table.h"

static uint64_t val_sum = 0;
static GenericTable* table;
static RobinHoodHash* rhh;
static OPHash hasher;

typedef uint64_t (*HashFunc)(void* key, void* context, OPHash hasher);
typedef void (*RunKey)(int size, HashFunc hash_func,
                       void* context, OPHash hasher);

static void run_short_keys(int size, HashFunc hash_func,
                           void* context, OPHash hasher);
static void run_mid_keys(int size, HashFunc hash_func,
                         void* context, OPHash hasher);
static void run_long_keys(int size, HashFunc hash_func,
                          void* context, OPHash hasher);
static void print_timediff(const char* info,
                           struct timeval start, struct timeval end);

uint64_t murmur3(void* key, size_t size)
{
  uint64_t hashed_val[2];
  MurmurHash3_x64_128(key, size, 421439783, hashed_val);
  return hashed_val[0];
}

uint64_t spooky(void* key, size_t size)
{
  return spookyhash64(key, size, 421439783);
}

uint64_t city(void* key, size_t size)
{
  return cityhash64(key, size);
}

uint64_t farm(void* key, size_t size)
{
  return farmhash64(key, size);
}

uint64_t RHHPutWrap(void* key, void* context, OPHash hash_impl)
{
  static uint64_t val = 0;
  RHHInsertCustom(context, hash_impl, key, &val);
  val++;
  return 0;
}

uint64_t QPInsertWrap(void* key, void* context, OPHash hash_impl)
{
  static uint64_t val = 0;
  QPInsertCustom(context, hash_impl, key, &val);
  val++;
  return 0;
}

int RHHProbeWrap(const void* akey, const void* bkey)
{
  return RHHGetProbeCustom(rhh, hasher, (void*)akey) -
    RHHGetProbeCustom(rhh, hasher, (void*)bkey);
}

int TableProbeWrap(const void* akey, const void* bkey)
{
  return QPGetProbeCustom(table, hasher, (void*)akey) -
    QPGetProbeCustom(table, hasher, (void*)bkey);
}

void RecordHashKey(void* key, void* value, size_t keysize, size_t valsize,
                   void* context)
{
  char** keyrecord = (char**)context;
  memcpy(key, *keyrecord, keysize);
  *keyrecord += keysize;
}

int main(int argc, char* argv[])
{
  int opt = 0;
  int repeat = 1;
  int num_power = 23;
  uint64_t num;
  float load = 0.8;
  float percent = 0.1;
  OPHeap* heap;
  RunKey key_func = run_short_keys;
  int k_len = 6;
  bool use_rhh = false;
  char* allkeys, *allkeys_iter;
  struct timeval
    q_start, q_end;

  hasher = city;

  while ((opt = getopt(argc, argv, "n:l:p:r:f:i:k:")) > -1)
    {
      switch (opt)
        {
        case 'n':
          num_power = atoi(optarg);
          break;
        case 'l':
          load = atof(optarg);
          break;
        case 'r':
          repeat = atoi(optarg);
          break;
        case 'p':
          percent = atof(optarg);
          op_assert(percent < 1.0 && percent > 0.0,
                    "-p <percent> must within 0.0 and 1.0\n");
          break;
        case 'i':
          if (!strcmp("rhh", optarg))
            {
              use_rhh = true;
            }
          break;
        case 'f':
          if (!strcmp("murmur3", optarg))
            {
              printf("using murmur3 hasher\n");
              hasher = murmur3;
            }
          else if (!strcmp("spooky", optarg))
            {
              printf("using spookyhash\n");
              hasher = spooky;
            }
          else if (!strcmp("city", optarg))
            {
              printf("using cityhash\n");
              hasher = city;
            }
          else if (!strcmp("farm", optarg))
            {
              printf("using farmhash\n");
              hasher = farm;
            }
          break;
        case 'k':
          if (!strcmp("s_string", optarg))
            {
              key_func = run_short_keys;
              k_len = 6;
            }
          else if (!strcmp("m_string", optarg))
            {
              key_func = run_mid_keys;
              k_len = 32;
            }
          else if (!strcmp("l_string", optarg))
            {
              key_func = run_long_keys;
              k_len = 256;
            }
          else break;
        }
    }

  num = 1ULL << num_power;
  printf("running elements %" PRIu64 " and measuring last %f get performance\n",
         num, percent);
  allkeys = malloc(k_len * num);

  OPHeapNew(&heap);

  if (use_rhh)
    {
      RHHNew(heap, &rhh, num, load, k_len, 8);
      key_func(num_power, RHHPutWrap, rhh, hasher);
      allkeys_iter = allkeys;
      RHHIterate(rhh, RecordHashKey, &allkeys_iter);
      qsort(allkeys, num, k_len, RHHProbeWrap);

      for (int i = 0; i < repeat; i++)
        {
          printf("attempt %d\n", i+1);
          gettimeofday(&q_start, NULL);
          for (char* key = &allkeys[k_len * (int)(num * (1.0 - percent))];
               key < allkeys + k_len * num;
               key += k_len)
            {
              uint64_t* intval = RHHGetCustom(rhh, hasher, key);
              val_sum += *intval;
            }
          gettimeofday(&q_end, NULL);
          print_timediff("Query time ", q_start, q_end);
        }
    }
  else
    {
      TableNew(heap, &table, num, load, k_len, 8, false);
      key_func(num_power, QPInsertWrap, table, hasher);
      allkeys_iter = allkeys;
      printf("inserting data to allkeys\n");
      TableIterate(table, RecordHashKey, &allkeys_iter);
      printf("got data inserted to allkeys\n");
      qsort(allkeys, num, k_len, TableProbeWrap);
      printf("sorted keys\n");

      for (int i = 0; i < repeat; i++)
        {
          printf("attempt %d\n", i+1);
          gettimeofday(&q_start, NULL);
          for (char* key = &allkeys[k_len * (int)(num * (1.0 - percent))];
               key < allkeys + k_len * num;
               key += k_len)
            {
              uint64_t* intval = QPGetCustom(table, hasher, key);
              val_sum += *intval;
            }
          gettimeofday(&q_end, NULL);
          print_timediff("Query time ", q_start, q_end);
        }
    }
  printf("val_sum: %" PRIu64 "\n",  val_sum);
  OPHeapDestroy(heap);
  free(allkeys);
}

void run_short_keys(int size, HashFunc hash_func,
                    void* context, OPHash hasher)
{
  op_assert(size >= 12, "iteration size must > 2^12\n");
  int i_bound = 1 << (size - 12);
  char uuid [] = "!!!!!!";
  uint64_t counter = 0;
  for (int i = 0; i < i_bound; i++)
    {
      for (int j = 2, val = counter >> 12; j < 6; j++, val>>=6)
        {
          uuid[j] = 0x21 + (val & 0x3F);
        }
      for (int j = 0; j < 64; j++)
        {
          uuid[1] = 0x21 + j;
          for (int k = 0; k < 64; k++)
            {
              uuid[0] = 0x21 + k;
              counter++;
              hash_func(uuid, context, hasher);
            }
        }
    }
}

void run_mid_keys(int size, HashFunc hash_func,
                  void* context, OPHash hasher)
{
  op_assert(size >= 12, "iteration size must > 2^12\n");
  int i_bound = 1 << (size - 12);
  char uuid [] = "!!!!!!--!!!!!!--!!!!!!--!!!!!!--";
  uint64_t counter = 0;
  for (int i = 0; i < i_bound; i++)
    {
      for (int j = 2, val = counter >> 12; j < 6; j++, val>>=6)
        {
          uuid[j] = 0x21 + (val & 0x3F);
          uuid[j+8] = 0x21 + (val & 0x3F);
          uuid[j+16] = 0x21 + (val & 0x3F);
          uuid[j+24] = 0x21 + (val & 0x3F);
        }
      for (int j = 0; j < 64; j++)
        {
          uuid[1] = 0x21 + j;
          uuid[1+8] = 0x21 + j;
          uuid[1+16] = 0x21 + j;
          uuid[1+24] = 0x21 + j;
          for (int k = 0; k < 64; k++)
            {
              uuid[0] = 0x21 + k;
              uuid[0+8] = 0x21 + k;
              uuid[0+16] = 0x21 + k;
              uuid[0+24] = 0x21 + k;
              counter++;
              hash_func(uuid, context, hasher);
            }
        }
    }
}

void run_long_keys(int size, HashFunc hash_func,
                   void* context, OPHash hasher)
{
  op_assert(size >= 12, "iteration size must > 2^12\n");
  int i_bound = 1 << (size - 12);
  char uuid [] =
    "!!!!!!--!!!!!!--!!!!!!--!!!!!!--"
    "!!!!!!--!!!!!!--!!!!!!--!!!!!!--"
    "!!!!!!--!!!!!!--!!!!!!--!!!!!!--"
    "!!!!!!--!!!!!!--!!!!!!--!!!!!!--"
    "!!!!!!--!!!!!!--!!!!!!--!!!!!!--"
    "!!!!!!--!!!!!!--!!!!!!--!!!!!!--"
    "!!!!!!--!!!!!!--!!!!!!--!!!!!!--"
    "!!!!!!--!!!!!!--!!!!!!--!!!!!!--";
  uint64_t counter = 0;
  for (int i = 0; i < i_bound; i++)
    {
      for (int j = 2, val = counter >> 12; j < 6; j++, val>>=6)
        {
          for (int k = 0; k < 256; k+=8)
            uuid[j+k] = 0x21 + (val & 0x3F);
        }
      for (int j = 0; j < 64; j++)
        {
          for (int h = 0; h < 256; h+=8)
            uuid[h+1] = 0x21 + j;
          for (int k = 0; k < 64; k++)
            {
              for (int h = 0; h < 256; h+=8)
                uuid[h] = 0x21 + k;
              counter++;
              hash_func(uuid, context, hasher);
            }
        }
    }
}

void print_timediff(const char* info, struct timeval start, struct timeval end)
{
  long int second = end.tv_sec - start.tv_sec;
  unsigned int usec;
  if (end.tv_usec < start.tv_usec)
    {
      second--;
      usec = end.tv_usec + 1000000 - start.tv_usec;
    }
  else
    usec = end.tv_usec - start.tv_usec;

  printf("%s%ld.%06u\n", info, second, usec);
}

/* worst_case.c ends here */
