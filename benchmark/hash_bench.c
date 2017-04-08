/* hash_bench.c ---
 *
 * Filename: hash_bench.c
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

typedef void (*HashFunc)(char* key, void* context);
static void run_short_keys(int size, HashFunc hash_func, void* context);
static void run_long_keys(int size, HashFunc hash_func, void* context);
static void run_long_int(int size, HashFunc hash_func, void* context);


void rhh_put(char* key, void* context)
{
  RobinHoodHash* rhh = (RobinHoodHash*)context;
  RHHPut(rhh, key, 0);
}

void rhh_get(char* key, void* context)
{
  static int counter;
  RobinHoodHash* rhh = (RobinHoodHash*)context;
  //op_assert((size_t)RHHGet(rhh, key) == 0, "val is 0");
  RHHGet(rhh,key);
  //opref_t val;
  //printf("counter: %d key %s\n", counter++, key);
  //op_assert(RHHSearch(rhh, key, &val), "can find key\n");
}

void print_timediff(struct timeval start, struct timeval end)
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

  printf("%ld.%06u\n", second, usec);
}

int main(int argc, char* argv[])
{
  OPHeap* heap;
  RobinHoodHash* rhh;
  int num_power, opt;
  uint64_t num;

  num_power = 20;

  while ((opt = getopt(argc, argv, "n:h")) > -1)
    {
      switch (opt)
        {
        case 'n':
          num_power = atoi(optarg);
          break;
        case 'h':
        case '?':
        default:
          printf("usage: %s [options]\n"
                 "  -n num     Number of elements measured in power of 2.\n"
                 "             -n 20 => run 2^20 = 1 million elements.\n"
                 "             defaults to 20\n", argv[0]);
          exit(1);
        }
    }

  num = 1UL << num_power;
  printf("running elements 2^%d = %" PRIu64 "\n", num_power, num);

  op_assert(OPHeapNew(&heap), "Create OPHeap\n");
  op_assert(RHHNew(heap, &rhh, num,
                   0.80, 6, 421439783), "Create RobinHoodHash\n");

  struct timeval start, mid, end;
  gettimeofday(&start, NULL);
  run_short_keys(num_power, rhh_put, rhh);
  //run_long_int(num_power, rhh_put, rhh);
  printf("insert finished\n");
  gettimeofday(&mid, NULL);
  //run_long_int(num_power, rhh_get, rhh);
  run_short_keys(num_power, rhh_get, rhh);
  gettimeofday(&end, NULL);

  print_timediff(start, mid);
  print_timediff(mid, end);
  RHHPrintStat(rhh);
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

void run_long_keys(int size, HashFunc hash_func, void* context)
{
  op_assert(size >= 12, "iteration size must > 2^12\n");
  int i_bound = 1 << (size - 12);
  char uuid [] = "!!!!!!--!!!!!!--!!!!!!";
  uint64_t counter = 0;
  for (int i = 0; i < i_bound; i++)
    {
      for (int j = 2, val = counter >> 12; j < 6; j++, val>>=6)
        {
          uuid[j] = 0x21 + (val & 0x3F);
          uuid[j+8] = 0x21 + (val & 0x3F);
          uuid[j+16] = 0x21 + (val & 0x3F);
        }
      for (int j = 0; j < 64; j++)
        {
          uuid[1] = 0x21 + j;
          uuid[1+8] = 0x21 + j;
          uuid[1+16] = 0x21 + j;
          for (int k = 0; k < 64; k++)
            {
              uuid[0] = 0x21 + k;
              uuid[0+8] = 0x21 + k;
              uuid[0+16] = 0x21 + k;
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
      hash_func(&i, context);
    }
}

/* hash_bench.c ends here */
