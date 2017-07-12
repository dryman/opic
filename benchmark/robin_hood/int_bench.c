/* int_bench.c ---
 *
 * Filename: int_bench.c
 * Description:
 * Author: Felix Chern
 * Maintainer:
 * Copyright: (c) 2017 Felix Chern
 * Created: Sun Jul  9 10:46:32 2017 (-0700)
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
#include "int_table.h"

#include "murmurhash3.h"
#include "spookyhash-c/spookyhash.h"
#include "farmhash-c/farmhash.h"

static uint64_t val_sum = 0;

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

void help(char* program)
{
  printf
    ("usage: %s [-n power_of_2] [-r repeat] [-k keytype] [-i impl]\n"
     "       [-l load] [-p file]\n"
     "Options:\n"
     "  -n num     Number of elements measured in power of 2.\n"
     "             -n 20 => run 2^20 = 1 million elements.\n"
     "             defaults to 20\n"
     "  -r repeat  Repeat the benchmar for `repeat` times.\n"
     "  -k keytype keytype = s_string, m_string, l_string l_int\n"
     "             s_string: 6 bytes, m_string: 32 bytes,\n"
     "             l_string: 256 bytes, l_int: 8 bytes\n"
     "             For now only robin_hood hash supports long_int benchmark\n"
     //"  -i impl    impl = linear, quadratic, double_hashing, chain\n"
     "  -l load    load number range from 0.0 to 1.0.\n"
     "  -p file    print probing stats of hash table to file\n"
     "  -h         print help.\n"
     ,program);
  exit(1);
}

int main(int argc, char* argv[])
{
  OPHeap* heap;
  IntTable* table;
  struct timeval
    i_start, i_end,
    q_start, q_end;

  int opt;
  int repeat = 1;
  uint64_t num = 1000000;
  double load = 0.8;
  FILE *stat_stream = NULL;
  char* stat_header = "int quadratic probing";

  OPHash hasher = city;

  while ((opt = getopt(argc, argv, "n:r:l:f:p:h")) > -1)
    {
      switch (opt)
        {
        case 'n':
          num = atol(optarg);
          break;
        case 'r':
          repeat = atoi(optarg);
          break;
        /* case 'i': */
        /*   if (!strcmp("linear", optarg)) */
        /*     { */
        /*       printf("linear probing\n"); */
        /*       stat_header = "linear probing"; */
        /*     } */
        /*   else if (!strcmp("quadratic", optarg)) */
        /*     { */
        /*       put_func = QPInsertWrap; */
        /*       get_func = QPGetWrap; */
        /*       printf("quadratic probing\n"); */
        /*       stat_header = "quadratic probing"; */
        /*     } */
        /*   else if (!strcmp("double_hashing", optarg)) */
        /*     { */
        /*       put_func = DHInsertWrap; */
        /*       get_func = DHGetWrap; */
        /*       printf("double hashing\n"); */
        /*       stat_header = "double hashing"; */
        /*     } */
        /*   else if (!strcmp("chain", optarg)) */
        /*     { */
        /*       is_chain = true; */
        /*       put_func = ChainInsertWrap; */
        /*       get_func = ChainGetWrap; */
        /*       printf("chaining\n"); */
        /*       stat_header = "chaining"; */
        /*     } */
        /*   else */
        /*     help(argv[0]); */
        /*   break; */
        case 'l':
          load = atof(optarg);
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
          else
            help(argv[0]);
          break;
        case 'p':
          stat_stream = fopen(optarg, "w");
          break;
        case 'h':
        case '?':
        default:
            help(argv[0]);
        }
    }

  printf("running elements %" PRIu64 "\n", num);

  op_assert(OPHeapNew(&heap), "Create OPHeap\n");

  for (int i = 0; i < repeat; i++)
    {
      printf("attempt %d\n", i + 1);
      op_assert(IntTableNew(heap, &table, num, load,
                            7, ~(0ULL), ~(0ULL)-1), "Create Table\n");
      /* op_assert(IntTableNew2(heap, &table, num, load, 8, 8), "Create Table\n"); */

      gettimeofday(&i_start, NULL);
      for (uint64_t i = 0; i < num; i++)
        {
          /* QPIntInsertCustom2(table, hasher, i, &i); */
          QPIntInsertCustom(table, hasher, i, &i);
        }
      gettimeofday(&i_end, NULL);

      printf("insert finished\n");

      gettimeofday(&q_start, NULL);
      for (uint64_t i = 0; i < num; i++)
        {
          /* uint64_t *vptr = QPIntGetCustom2(table, hasher, i); */
          uint64_t *vptr = QPIntGetCustom(table, hasher, i);
          val_sum += *vptr;
        }
      gettimeofday(&q_end, NULL);

      print_timediff("int Insert time: ", i_start, i_end);
      print_timediff("int Query time: ", q_start, q_end);

      if (stat_stream)
        {
          fprintf(stat_stream, "%s load %1.2f\n", stat_header, load);
          for (uint32_t i = 0; i <= IntTableMaxProbe(table); i++)
            fprintf(stat_stream, "%u\n", IntTableProbeStat(table, i));
        }
      IntTableDestroy(table);
    }
  if (stat_stream)
    fclose(stat_stream);

  return 0;
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

/* int_bench.c ends here */
