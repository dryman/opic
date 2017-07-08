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

#include "rhh_b_k_v.h"
#include "rhh_b_kv.h"
#include "rhh_bkv.h"
#include "rhh_bkv_v4qu.h"
#include "rhh_b16kv.h"
#include "rhh_b16kv2.h"

static int objcnt = 0;
static uint64_t val_sum = 0;

typedef uint64_t (*HashFunc)(void* key, void* context, OPHash hasher);
typedef void (*RunKey)(int size, HashFunc hash_func,
                       void* context, OPHash hasher);

typedef bool (*RHHNew_t)(OPHeap* heap, void* rhh,
                         uint64_t num_objects, double load,
                         size_t keysize, size_t valsize);
typedef void (*RHHDestroy_t)(void* rhh);
typedef uint32_t (*RHHMaxProbe_t)(void* rhh);
typedef uint32_t (*RHHProbeStat_t)(void* rhh, uint32_t idx);

static void run_short_keys(int size, HashFunc hash_func,
                           void* context, OPHash hasher);
static void run_mid_keys(int size, HashFunc hash_func,
                         void* context, OPHash hasher);
static void run_long_keys(int size, HashFunc hash_func,
                          void* context, OPHash hasher);
static void run_long_int(int size, HashFunc hash_func,
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

uint64_t RHHGetWrap(void* key, void* context, OPHash hash_impl)
{
  return *(uint64_t*)RHHGetCustom(context, hash_impl, key);
}


void CountObjects(void* key, void* val,
                  size_t keysize, size_t valsize, void* ctx)
{
  objcnt++;
  uint64_t *val_ptr = val;
  val_sum += *val_ptr;
}

struct SequentialCtx
{
  void* rhh;
  HashFunc rhh_func;
  OPHash hasher;
};

void SequentialOp(void* key, void* val,
                      size_t keysize, size_t valsize, void* ctx)
{
  struct SequentialCtx *sictx = (struct SequentialCtx*) ctx;
  sictx->rhh_func(key, sictx->rhh, sictx->hasher);
}

void help(char* program)
{
  printf
    ("usage: %s [-n power_of_2] [-r repeat] [-k keytype] [-i impl]\n"
     "       [-l load] [-p]\n"
     "Options:\n"
     "  -n num     Number of elements measured in power of 2.\n"
     "             -n 20 => run 2^20 = 1 million elements.\n"
     "             defaults to 20\n"
     "  -r repeat  Repeat the benchmar for `repeat` times.\n"
     "  -k keytype keytype = s_string, m_string, l_string l_int\n"
     "             s_string: 6 bytes, m_string: 32 bytes,\n"
     "             l_string: 256 bytes, l_int: 8 bytes\n"
     "             For now only robin_hood hash supports long_int benchmark\n"
     "  -i impl    impl = rhh, rhh_b_k_v, rhh_b_kv, rhh_bkv,\n"
     "             rhh_b16kv, rhh_bkv_v4qu\n"
     "  -l load    load number for rhh range from 0.0 to 1.0.\n"
     "  -p         print probing stats of RHH\n"
     "  -h         print help.\n"
     ,program);
  exit(1);
}

int main(int argc, char* argv[])
{
  OPHeap* heap;
  void *rhh, *rhh2;
  struct timeval
    i_start, i_end,
    q_start, q_end,
    s_start, s_end,
    si_start, si_end,
    sg_start, sg_end;

  int num_power, opt;
  int repeat = 1;
  RunKey key_func = run_short_keys;
  int k_len = 6;
  uint64_t num;
  double load = 0.8;
  char* stat_header = "RHH";
  FILE* stat_stream = NULL;

  RHHNew_t rhh_new = (RHHNew_t)RHHNew;
  RHHDestroy_t rhh_destroy = (RHHDestroy_t)RHHDestroy;
  HashFunc rhh_put = RHHPutWrap;
  HashFunc rhh_get = RHHGetWrap;
  RHHMaxProbe_t rhh_maxprobe = (RHHMaxProbe_t)RHHMaxProbe;
  RHHProbeStat_t rhh_probestat = (RHHProbeStat_t)RHHProbeStat;
  OPHash hasher = city;

  num_power = 20;

  while ((opt = getopt(argc, argv, "n:r:k:i:l:f:p:h")) > -1)
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
          else if (!strcmp("l_int", optarg))
            {
              key_func = run_long_int;
              k_len = 8;
            }
          else
            help(argv[0]);
          break;
        case 'i':
          if (!strcmp("rhh", optarg))
            {
              printf("Using official robin_hood\n");
            }
          else if (!strcmp("rhh_b_k_v", optarg))
            {
              printf("Using rhh_b_k_v\n");
              rhh_new = (RHHNew_t)RHH_b_k_v_New;
              rhh_destroy = (RHHDestroy_t)RHH_b_k_v_Destroy;
              rhh_put = RHH_b_k_v_PutWrap;
              rhh_get = RHH_b_k_v_GetWrap;
              stat_header = "RHH_b_k_v";
              rhh_maxprobe = (RHHMaxProbe_t)RHH_b_k_v_MaxProbe;
              rhh_probestat = (RHHProbeStat_t)RHH_b_k_v_ProbeStat;
            }
          else if (!strcmp("rhh_b_kv", optarg))
            {
              printf("Using rhh_b_kv\n");
              rhh_new = (RHHNew_t)RHH_b_kv_New;
              rhh_destroy = (RHHDestroy_t)RHH_b_kv_Destroy;
              rhh_put = RHH_b_kv_PutWrap;
              rhh_get = RHH_b_kv_GetWrap;
              stat_header = "RHH_b_kv";
              rhh_maxprobe = (RHHMaxProbe_t)RHH_b_kv_MaxProbe;
              rhh_probestat = (RHHProbeStat_t)RHH_b_kv_ProbeStat;
            }
          else if (!strcmp("rhh_bkv", optarg))
            {
              printf("Using rhh_bkv\n");
              rhh_new = (RHHNew_t)RHH_bkv_New;
              rhh_destroy = (RHHDestroy_t)RHH_bkv_Destroy;
              rhh_put = RHH_bkv_PutWrap;
              rhh_get = RHH_bkv_GetWrap;
              stat_header = "RHH_bkv";
              rhh_maxprobe = (RHHMaxProbe_t)RHH_bkv_MaxProbe;
              rhh_probestat = (RHHProbeStat_t)RHH_bkv_ProbeStat;
            }
          else if (!strcmp("rhh_bkv_v4qu", optarg))
            {
              printf("Using rhh_bkv_v4qu\n");
              rhh_new = (RHHNew_t)RHH_bkv_v4qu_New;
              rhh_destroy = (RHHDestroy_t)RHH_bkv_v4qu_Destroy;
              rhh_put = RHH_bkv_v4qu_PutWrap;
              rhh_get = RHH_bkv_v4qu_GetWrap;
              stat_header = "RHH_bkv_v4qu";
              rhh_maxprobe = (RHHMaxProbe_t)RHH_bkv_v4qu_MaxProbe;
              rhh_probestat = (RHHProbeStat_t)RHH_bkv_v4qu_ProbeStat;
            }
          else if (!strcmp("rhh_b16kv", optarg))
            {
              printf("Using rhh_b16kv\n");
              rhh_new = (RHHNew_t)RHH_b16kv_New;
              rhh_destroy = (RHHDestroy_t)RHH_b16kv_Destroy;
              rhh_put = RHH_b16kv_PutWrap;
              rhh_get = RHH_b16kv_GetWrap;
              stat_header = "RHH_b16kv";
              rhh_maxprobe = (RHHMaxProbe_t)RHH_b16kv_MaxProbe;
              rhh_probestat = (RHHProbeStat_t)RHH_b16kv_ProbeStat;
            }
          else if (!strcmp("rhh_b16kv2", optarg))
            {
              printf("Using rhh_b16kv2\n");
              rhh_new = (RHHNew_t)RHH_b16kv2_New;
              rhh_destroy = (RHHDestroy_t)RHH_b16kv2_Destroy;
              rhh_put = RHH_b16kv2_PutWrap;
              rhh_get = RHH_b16kv2_GetWrap;
              stat_header = "RHH_b16kv2";
              rhh_maxprobe = (RHHMaxProbe_t)RHH_b16kv2_MaxProbe;
              rhh_probestat = (RHHProbeStat_t)RHH_b16kv2_ProbeStat;
            }
          else
            help(argv[0]);
          break;
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

  num = 1UL << num_power;
  printf("running elements %" PRIu64 "\n", num);

  op_assert(OPHeapNew(&heap), "Create OPHeap\n");

  for (int i = 0; i < repeat; i++)
    {
      printf("attempt %d\n", i + 1);
      op_assert(rhh_new(heap, &rhh, num,
                        load, k_len, 8), "Create RobinHoodHash\n");
      op_assert(rhh_new(heap, &rhh2, num,
                        load, k_len, 8), "Create RobinHoodHash\n");
      gettimeofday(&i_start, NULL);
      key_func(num_power, rhh_put, rhh, hasher);
      gettimeofday(&i_end, NULL);
      printf("insert finished\n");
      gettimeofday(&q_start, NULL);
      key_func(num_power, rhh_get, rhh, hasher);
      gettimeofday(&q_end, NULL);

      /*
      gettimeofday(&s_start, NULL);
      RHHIterate(rhh, CountObjects, NULL);
      gettimeofday(&s_end, NULL);

      struct SequentialCtx sictx =
        {
          .rhh = rhh2,
          .rhh_func = rhh_put,
          .hasher = hasher,
        };
      gettimeofday(&si_start, NULL);
      RHHIterate(rhh, SequentialOp, &sictx);
      gettimeofday(&si_end, NULL);

      sictx.rhh_func = rhh_get;
      gettimeofday(&sg_start, NULL);
      RHHIterate(rhh, SequentialOp, &sictx);
      gettimeofday(&sg_end, NULL);
      */

      print_timediff("Insert time: ", i_start, i_end);
      print_timediff("Query time: ", q_start, q_end);
      /*
      print_timediff("Sequential read time: ", s_start, s_end);
      print_timediff("Sequential insert time: ", si_start, si_end);
      print_timediff("Sequential get time: ", sg_start, sg_end);
      */

      if (stat_stream)
        {
          fprintf(stat_stream, "%s load %1.2f\n", stat_header, load);
          for (uint32_t i = 0; i <= rhh_maxprobe(rhh); i++)
            fprintf(stat_stream, "%u\n", rhh_probestat(rhh, i));
        }
      rhh_destroy(rhh);
      rhh_destroy(rhh2);
    }
  printf("objcnt: %d val_sum: %" PRIu64 "\n", objcnt, val_sum);
  if (stat_stream)
    fclose(stat_stream);

  return 0;
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

void run_long_int(int size, HashFunc hash_func,
                  void* context, OPHash hasher)
{
  op_assert(size >= 12, "iteration size must > 2^12\n");
  uint64_t i_bound = 1 << size;
  for (uint64_t i = 0; i < i_bound; i++)
    {
      hash_func(&i, context, hasher);
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
