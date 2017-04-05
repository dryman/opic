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
#include <string.h>
#include "opic/common/op_assert.h"
#include "opic/op_malloc.h"
#include "opic/hash/robin_hood.h"

typedef void (*HashFunc)(char* key, void* context);
static void run_short_keys(int size, HashFunc hash_func, void* context);
static void run_long_keys(int size, HashFunc hash_func, void* context);

#define SIZE 20

void rhh_put(char* key, void* context)
{
  static int rhh_counter;
  RobinHoodHash* rhh = (RobinHoodHash*)context;
  printf("%04d key: '%s'\n", rhh_counter++, key);
  RHHPut(rhh, key, 0);
}

int main(int argc, char** argv)
{
  OPHeap* heap;
  RobinHoodHash* rhh;
  op_assert(OPHeapNew(&heap), "Create OPHeap\n");
  op_assert(RHHNew(heap, &rhh, 1 << SIZE,
                   0.8, 44, 421439783), "Create RobinHoodHash\n");
  run_long_keys(SIZE, rhh_put, rhh);
  return 0;
}

void run_short_keys(int size, HashFunc hash_func, void* context)
{
  op_assert(size >= 12, "iteration size must > 2^12\n");
  int i_bound = 1 << (size - 12);
  char uuid [] = "      ";
  uint64_t counter = 0;
  for (int i = 0; i < i_bound; i++)
    {
      for (int j = 2, val = counter >> 12; j < 6; j++, val>>=6)
        {
          uuid[j] = 0x20 + (val & 0x3F);
        }
      for (int j = 0; j < 64; j++)
        {
          uuid[1] = 0x20 + j;
          for (int k = 0; k < 64; k++)
            {
              uuid[0] = 0x20 + k;
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
  char uuid [] = "      --      --      ";
  uint64_t counter = 0;
  for (int i = 0; i < i_bound; i++)
    {
      for (int j = 2, val = counter >> 12; j < 6; j++, val>>=6)
        {
          uuid[j] = 0x20 + (val & 0x3F);
          uuid[j+8] = 0x20 + (val & 0x3F);
          uuid[j+16] = 0x20 + (val & 0x3F);
        }
      for (int j = 0; j < 64; j++)
        {
          uuid[1] = 0x20 + j;
          uuid[1+8] = 0x20 + j;
          uuid[1+16] = 0x20 + j;
          for (int k = 0; k < 64; k++)
            {
              uuid[0] = 0x20 + k;
              uuid[0+8] = 0x20 + k;
              uuid[0+16] = 0x20 + k;
              counter++;
              hash_func(uuid, context);
            }
        }
    }
}

/* hash_bench.c ends here */
