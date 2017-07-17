/* del_bench.c ---
 *
 * Filename: del_bench.c
 * Description:
 * Author: Felix Chern
 * Maintainer:
 * Copyright: (c) 2017 Felix Chern
 * Created: Sat Jul 15 18:50:40 2017 (-0700)
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


typedef uint64_t (*HashFunc)(void* key, void* context, OPHash hasher);

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

int main(int argc, char* argv[])
{
  char fname_base[1024] = "del_quadratic";
  char fname[1024];
  int opt = 0;
  int repeat = 1;
  uint64_t num = 1000000;
  float load = 0.8;
  OPHeap* heap;
  GenericTable* table;
  FILE* fd;
  OPHash hasher = city;
  bool use_rhh;

  while ((opt = getopt(argc, argv, "n:l:p:r:f:i:")) > -1)
    {
      switch (opt)
        {
        case 'n':
          num = atoll(optarg);
          break;
        case 'l':
          load = atof(optarg);
          break;
        case 'r':
          repeat = atoi(optarg);
          break;
        case 'p':
          strcpy(fname_base, optarg);
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
        }
    }
  OPHeapNew(&heap);
  if (use_rhh)
    {
      RobinHoodHash* rhh;
      RHHNew(heap, &rhh, num, load, 8, 8);

      printf("iteration %d\n", 0);
      sprintf(fname, "%s_%02d", fname_base, 0);
      fd = fopen(fname, "w+");
      for (uint64_t j = 0; j < num; j++)
        {
          op_assert(RHHInsertCustom(rhh, hasher, &j, &j),
                    "insert must succeed\n");
        }
      fprintf(fd, "%s\n", fname);
      for (uint32_t k = 0; k <= RHHMaxProbe(rhh); k++)
        {
          fprintf(fd, "%u\n", RHHProbeStat(rhh, k));
        }
      fclose(fd);

      for (int i = 1; i < repeat; i++)
        {
          printf("iteration %d\n", i);
          sprintf(fname, "%s_%02d", fname_base, i);
          fd = fopen(fname, "w+");
          for (uint64_t j = i * num; j < (i+1) * num; j++)
            {
              uint64_t k = j - num;
              op_assert(RHHDeleteCustom(rhh, hasher, &k),
                        "del item cannot be null\n");
              op_assert(RHHInsertCustom(rhh, hasher, &j, &j),
                        "insert mush succeed\n");
            }
          fprintf(fd, "%s\n", fname);
          for (uint32_t k = 0; k <= RHHMaxProbe(rhh); k++)
            {
              fprintf(fd, "%u\n", RHHProbeStat(rhh, k));
            }
          fclose(fd);
        }
      RHHDestroy(rhh);
    }
  else
    {
      TableNew(heap, &table, num, load, 8, 8, false);

      printf("iteration %d\n", 0);
      sprintf(fname, "%s_%02d", fname_base, 0);
      fd = fopen(fname, "w+");
      for (uint64_t j = 0; j < num; j++)
        {
          op_assert(QPInsertCustom(table, hasher, &j, &j),
                    "insert must succeed\n");
        }
      fprintf(fd, "%s\n", fname);
      for (uint32_t k = 0; k <= TableMaxProbe(table); k++)
        {
          fprintf(fd, "%u\n", TableProbeStat(table, k));
        }
      fclose(fd);

      for (int i = 1; i < repeat; i++)
        {
          printf("iteration %d\n", i);
          sprintf(fname, "%s_%02d", fname_base, i);
          fd = fopen(fname, "w+");
          for (uint64_t j = i * num; j < (i+1) * num; j++)
            {
              uint64_t k = j - num;
              op_assert(QPDelCustom(table, hasher, &k),
                        "del item cannot be null\n");
              op_assert(QPInsertCustom(table, hasher, &j, &j),
                        "insert mush succeed\n");
            }
          fprintf(fd, "%s\n", fname);
          for (uint32_t k = 0; k <= TableMaxProbe(table); k++)
            {
              fprintf(fd, "%u\n", TableProbeStat(table, k));
            }
          fclose(fd);
        }
      TableDestroy(table);
    }
  OPHeapDestroy(heap);
}


/* del_bench.c ends here */
