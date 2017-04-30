/* robin_bench.c ---
 *
 * Filename: robin_bench.c
 * Description:
 * Author: Felix Chern
 * Maintainer:
 * Copyright: (c) 2017 Felix Chern
 * Created: Mon Apr  3 22:07:32 2017 (-0700)
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
#include <inttypes.h>
#include <unistd.h>
#include "opic/common/op_assert.h"
#include "opic/op_malloc.h"
#include "opic/hash/robin_hood.h"

typedef uint64_t (*HashFunc)(char* key, void* context);
typedef void (*RunKey)(int size, HashFunc hash_func, void* context);
static void run_short_keys(int size, HashFunc hash_func, void* context);
static void run_mid_keys(int size, HashFunc hash_func, void* context);
static void run_long_keys(int size, HashFunc hash_func, void* context);
static void run_long_int(int size, HashFunc hash_func, void* context);
static void print_timediff(const char* info,
                           struct timeval start, struct timeval end);

enum HASH_IMPL
  {
    ROBIN_HOOD,
    DENSE_HASH_MAP,
    SPARSE_HASH_MAP,
    STD_UNORDERED_MAP,
    CUCKOO,
    KHASH,
  };

enum BENCHMARK_MODE
  {
    IN_MEMORY,
    SERIALIZE,
    DESERIALIZE,
    DE_NO_CACHE,
  };

uint64_t rhh_put(char* key, void* context)
{
  RobinHoodHash* rhh = (RobinHoodHash*)context;
  uint64_t val = 0;
  RHHPut(rhh, key, &val);
  return 0;
}

uint64_t rhh_get(char* key, void* context)
{
  RobinHoodHash* rhh = (RobinHoodHash*)context;
  return *(uint64_t*)RHHGet(rhh, key);
}

void rhh_in_memory(int num_power, uint64_t num, RunKey key_func, int keysize)
{
  OPHeap* heap;
  RobinHoodHash* rhh;
  struct timeval start, mid, end;

  printf("RobinHoodHash in memory\n");
  op_assert(OPHeapNew(&heap), "Create OPHeap\n");
  op_assert(RHHNew(heap, &rhh, num,
                   0.95, keysize, 8), "Create RobinHoodHash\n");

  gettimeofday(&start, NULL);
  key_func(num_power, rhh_put, rhh);
  printf("insert finished\n");
  gettimeofday(&mid, NULL);
  key_func(num_power, rhh_get, rhh);
  gettimeofday(&end, NULL);

  print_timediff("Insert time: ", start, mid);
  print_timediff("Query time: ", mid, end);
  RHHPrintStat(rhh);
  RHHDestroy(rhh);
  OPHeapDestroy(heap);
}

void help(char* program)
{
  printf
    ("usage: %s [-n power_of_2] [-r repeat] [-k keytype] [-i impl]\n"
     "Options:\n"
     "  -n num     Number of elements measured in power of 2.\n"
     "             -n 20 => run 2^20 = 1 million elements.\n"
     "             defaults to 20\n"
     "  -r repeat  Repeat the benchmar for `repeat` times.\n"
     "  -k keytype keytype = short_string, mid_string, long_string or\n"
     "             long_int\n"
     "             short_string: 6 bytes, mid_string: 32 bytes,\n"
     "             long_string: 256 bytes, long_int: 8 bytes\n"
     "             For now only robin_hood hash supports long_int benchmark\n"
     "  -i impl    impl = rhh\n"
     "  -h         print help.\n"
     ,program);
  exit(1);
}

int main(int argc, char* argv[])
{
  int num_power, opt;
  int repeat = 1;
  enum HASH_IMPL hash_impl = ROBIN_HOOD;
  enum BENCHMARK_MODE b_mode = IN_MEMORY;
  RunKey key_func = run_short_keys;
  int k_len = 6;
  char* file_name = NULL;
  uint64_t num;

  num_power = 20;

  while ((opt = getopt(argc, argv, "n:r:k:i:h")) > -1)
    {
      switch (opt)
        {
        case 'n':
          num_power = atoi(optarg);
          break;
        case 'r':
          repeat = atoi(optarg);
          break;
        case 'k':
          if (!strcmp("short_string", optarg))
            {
              key_func = run_short_keys;
              k_len = 6;
            }
          else if (!strcmp("mid_string", optarg))
            {
              key_func = run_mid_keys;
              k_len = 32;
            }
          else if (!strcmp("long_string", optarg))
            {
              key_func = run_long_keys;
              k_len = 256;
            }
          else if (!strcmp("long_int", optarg))
            {
              key_func = run_long_int;
              k_len = 8;
            }
          else
            help(argv[0]);
          break;
        case 'i':
          if (!strcmp("rhh", optarg))
            hash_impl = ROBIN_HOOD;
          else
            help(argv[0]);
          break;
        case 'h':
        case '?':
        default:
            help(argv[0]);
        }
    }

  num = 1UL << num_power;
  printf("running elements %" PRIu64 "\n", num);

  for (int i = 0; i < repeat; i++)
    {
      printf("attempt %d\n", i + 1);
      rhh_in_memory(num_power, num, key_func, k_len);
    }

  return 0;
}

void run_short_keys(int size, HashFunc hash_func, void* context)
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
              hash_func(uuid, context);
            }
        }
    }
}

void run_mid_keys(int size, HashFunc hash_func, void* context)
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
              hash_func(uuid, context);
            }
        }
    }
}

void run_long_keys(int size, HashFunc hash_func, void* context)
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
              hash_func(uuid, context);
            }
        }
    }
}

void run_long_int(int size, HashFunc hash_func, void* context)
{
  op_assert(size >= 12, "iteration size must > 2^12\n");
  uint64_t i_bound = 1 << size;
  uint64_t counter = 0;
  for (uint64_t i = 0; i < i_bound; i++)
    {
      hash_func((char*)&i, context);
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


/* robin_bench.c ends here */
