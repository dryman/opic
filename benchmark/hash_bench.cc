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
#include "khash.h"

#include <fstream>
#include <string>
#include <unordered_map>
#include <google/dense_hash_map>
#include <google/sparse_hash_map>
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/unordered_map.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <libcuckoo/cuckoohash_map.hh>


typedef uint64_t (*HashFunc)(char* key, void* context);
typedef void (*RunKey)(int size, HashFunc hash_func, void* context);
static void run_short_keys(int size, HashFunc hash_func, void* context);
static void run_mid_keys(int size, HashFunc hash_func, void* context);
static void run_long_keys(int size, HashFunc hash_func, void* context);
static void run_long_int(int size, HashFunc hash_func, void* context);
static void print_timediff(const char* info,
                           struct timeval start, struct timeval end);

KHASH_MAP_INIT_STR(str, uint64_t)

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

uint64_t um_put(char* key, void* context)
{
  auto um = static_cast<std::unordered_map<std::string, uint64_t>*>(context);
  um->insert(std::make_pair(key, 0));
  return 0;
}

uint64_t um_get(char* key, void* context)
{
  auto um = static_cast<std::unordered_map<std::string, uint64_t>*>(context);
  return um->at(key);
}

uint64_t dhm_put(char* key, void* context)
{
  auto dhm = static_cast<google::dense_hash_map
                         <std::string, uint64_t>*>(context);
  dhm->insert(std::make_pair(key, 0));
  return 0;
}

uint64_t dhm_get(char* key, void* context)
{
  auto dhm = static_cast<google::dense_hash_map
                         <std::string, uint64_t>*>(context);
  auto search = dhm->find(key);
  return search->second;
}

uint64_t shm_put(char* key, void* context)
{
  auto shm = static_cast<google::sparse_hash_map
                         <std::string, uint64_t>*>(context);
  shm->insert(std::make_pair(key, 0));
  return 0;
}

uint64_t shm_get(char* key, void* context)
{
  auto shm = static_cast<google::sparse_hash_map
                         <std::string, uint64_t>*>(context);
  auto search = shm->find(key);
  return search->second;
}

uint64_t ckoo_put(char* key, void* context)
{
  auto ckoo = static_cast<cuckoohash_map<std::string, uint64_t>*>(context);
  ckoo->insert(key, 0);
  return 0;
}

uint64_t ckoo_get(char* key, void* context)
{
  auto ckoo = static_cast<cuckoohash_map<std::string, uint64_t>*>(context);
  return ckoo->find(key);
}

uint64_t khash_put(char* key, void* context)
{
  khash_t(str) *kh;
  int absent;
  khint_t khint;
  kh = (khash_t(str)*)context;
  khint = kh_put(str, kh, key, &absent);
  if (absent)
    {
      kh_key(kh, khint) = strdup(key);
      kh_value(kh, khint) = 0;
    }
  return 0;
}

uint64_t khash_get(char* key, void* context)
{
  khash_t(str) *kh;
  khint_t khint;
  kh = (khash_t(str)*)context;
  khint = kh_get(str, kh, key);
  return (uint64_t)kh_value(kh, khint);
  //printf("%s\n", (char*)kh_key(kh, khint));
}

void rhh_in_memory(int num_power, uint64_t num, RunKey key_func, int keysize)
{
  OPHeap* heap;
  RobinHoodHash* rhh;
  struct timeval start, mid, end;

  printf("RobinHoodHash in memory\n");
  op_assert(OPHeapNew(&heap), "Create OPHeap\n");
  op_assert(RHHNew(heap, &rhh, num,
                   0.90, keysize, 8), "Create RobinHoodHash\n");

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

void rhh_serialize(int num_power, uint64_t num, RunKey key_func, int keysize,
                   char* file)
{
  OPHeap* heap;
  RobinHoodHash* rhh;
  struct timeval start, mid, end;
  FILE* stream;
  printf("RobinHoodHash serialization\n");

  op_assert(OPHeapNew(&heap), "Create OPHeap\n");
  op_assert(RHHNew(heap, &rhh, num,
                   0.80, keysize, 8), "Create RobinHoodHash\n");
  gettimeofday(&start, NULL);
  key_func(num_power, rhh_put, rhh);
  gettimeofday(&mid, NULL);
  stream = fopen(file, "w");
  OPHeapStorePtr(heap, rhh, 0);
  OPHeapWrite(heap, stream);
  fclose(stream);
  gettimeofday(&end, NULL);
  printf("serialized to %s\n", file);

  print_timediff("Insert time: ", start, mid);
  print_timediff("Serialization time: ", mid, end);
  RHHDestroy(rhh);
  OPHeapDestroy(heap);
}

void rhh_deserialize(int num_power, RunKey key_func, char* file)
{
  OPHeap* heap;
  RobinHoodHash* rhh;
  struct timeval start, mid, end;
  FILE* stream;

  printf("RobinHoodHash deserialization\n");

  gettimeofday(&start, NULL);
  stream = fopen(file, "r");
  op_assert(OPHeapRead(&heap, stream));
  fclose(stream);
  rhh = (RobinHoodHash*)OPHeapRestorePtr(heap, 0);
  printf("deserialized\n");

  gettimeofday(&mid, NULL);
  key_func(num_power, rhh_get, rhh);
  gettimeofday(&end, NULL);

  print_timediff("Deserialization time: ", start, mid);
  print_timediff("Query time: ", mid, end);
  OPHeapDestroy(heap);
}

void rhh_deserialize2(int num_power, RunKey key_func, char* file)
{
  OPHeap* heap;
  RobinHoodHash* rhh;
  struct timeval start, end;
  FILE* stream;
  char key [] = "!!!!!!";

  printf("RobinHoodHash deserialization2\n");

  gettimeofday(&start, NULL);

  for (int i = 0; i< 64; i++)
    {
      stream = fopen(file, "r");
      OPHeapRead(&heap, stream);
      fclose(stream);
      rhh = (RobinHoodHash*)OPHeapRestorePtr(heap, 0);
      RHHGet(rhh, key);
      key[0]++;
      OPHeapDestroy(heap);
    }

  gettimeofday(&end, NULL);

  print_timediff("Deserialization time for 64 short keys: ", start, end);
}

void um_in_memory(int num_power, uint64_t num, RunKey key_func)
{
  struct timeval start, mid, end;
  auto um = new std::unordered_map<std::string, uint64_t>(num);

  printf("std::unordered_map in memory\n");
  gettimeofday(&start, NULL);
  key_func(num_power, um_put, static_cast<void*>(um));
  gettimeofday(&mid, NULL);
  key_func(num_power, um_get, static_cast<void*>(um));
  gettimeofday(&end, NULL);

  delete um;

  print_timediff("Insert time: ", start, mid);
  print_timediff("Query time: ", mid, end);
}

void um_serialize(int num_power, uint64_t num, RunKey key_func, char* file_name)
{
  struct timeval start, mid, end;
  auto um = new std::unordered_map<std::string, uint64_t>(num);

  printf("std::unordered_map serialization\n");
  gettimeofday(&start, NULL);
  key_func(num_power, um_put, static_cast<void*>(um));
  gettimeofday(&mid, NULL);
  std::ofstream ofs(file_name);
  boost::archive::binary_oarchive oa(ofs);
  oa << um;
  ofs.close();
  gettimeofday(&end, NULL);
  delete um;
  print_timediff("Insert time: ", start, mid);
  print_timediff("Serialization time: ", mid, end);
}

void um_deserialize(int num_power, RunKey key_func, char* file_name)
{
  struct timeval start, mid, end;
  auto um = new std::unordered_map<std::string, uint64_t>();

  printf("std::unordered_map deserialization\n");

  gettimeofday(&start, NULL);
  std::ifstream ifs(file_name);
  boost::archive::binary_iarchive ia(ifs);
  ia >> um;
  ifs.close();
  gettimeofday(&mid, NULL);

  printf("std:unordered_map deserialized\n");
  key_func(num_power, um_get, static_cast<void*>(um));
  gettimeofday(&end, NULL);
  delete um;
  print_timediff("Deserialization time: ", start, mid);
  print_timediff("Query time: ", mid, end);
}

void dhm_in_memory(int num_power, uint64_t num, RunKey key_func)
{
  struct timeval start, mid, end;
  auto dhm = new google::dense_hash_map<std::string, uint64_t>(num);
  //dhm->max_load_factor(0.80);
  //dhm->resize(num);
  dhm->set_empty_key("\x00");
  dhm->set_deleted_key("\xff");

  printf("google::dense_hash_map in memory\n");

  gettimeofday(&start, NULL);
  key_func(num_power, dhm_put, static_cast<void*>(dhm));
  gettimeofday(&mid, NULL);
  key_func(num_power, dhm_get, static_cast<void*>(dhm));
  gettimeofday(&end, NULL);

  delete dhm;

  print_timediff("Insert time: ", start, mid);
  print_timediff("Query time: ", mid, end);
}

void shm_in_memory(int num_power, uint64_t num, RunKey key_func)
{
  struct timeval start, mid, end;
  auto shm = new google::sparse_hash_map<std::string, uint64_t>(num);
  shm->set_deleted_key("\xff");

  printf("google::sparse_hash_map in memory\n");

  gettimeofday(&start, NULL);
  key_func(num_power, shm_put, static_cast<void*>(shm));
  gettimeofday(&mid, NULL);
  key_func(num_power, shm_get, static_cast<void*>(shm));
  gettimeofday(&end, NULL);

  delete shm;

  print_timediff("Insert time: ", start, mid);
  print_timediff("Query time: ", mid, end);
}

void shm_serialize(int num_power, uint64_t num, RunKey key_func,
                   char* file_name)
{
  struct timeval start, mid, end;
  FILE* stream;
  auto shm = new google::sparse_hash_map<std::string, uint64_t>(num);
  shm->set_deleted_key("\xff");

  printf("google::sparse_hash_map serialization\n");

  gettimeofday(&start, NULL);
  key_func(num_power, shm_put, static_cast<void*>(shm));

  gettimeofday(&mid, NULL);

  stream = fopen(file_name, "w");
  shm->write_metadata(stream);
  shm->write_nopointer_data(stream);
  fclose(stream);
  gettimeofday(&end, NULL);

  delete shm;

  print_timediff("Insert time: ", start, mid);
  print_timediff("Serialization time: ", mid, end);
}

void shm_deserialize(int num_power, RunKey key_func, char* file_name)
{
  struct timeval start, mid, end;
  FILE* stream;
  auto shm = new google::sparse_hash_map<std::string, uint64_t>();

  printf("google::sparse_hash_map deserialization\n");

  gettimeofday(&start, NULL);
  stream = fopen(file_name, "r");
  shm->read_metadata(stream);
  shm->read_nopointer_data(stream);
  fclose(stream);

  gettimeofday(&mid, NULL);

  printf("gooogle::sparse_hash_map deserialized\n");
  key_func(num_power, shm_get, static_cast<void*>(shm));
  gettimeofday(&end, NULL);

  delete shm;

  print_timediff("Deserialization time: ", start, mid);
  print_timediff("Query time: ", mid, end);
}

void ckoo_in_memory(int num_power, uint64_t num, RunKey key_func)
{
  struct timeval start, mid, end;
  auto ckoo = new cuckoohash_map<std::string, uint64_t>
    ((size_t)(num * 1.25)); // 0.8 load factor

  printf("cuckoohash_map in memory\n");
  gettimeofday(&start, NULL);
  key_func(num_power, ckoo_put, static_cast<void*>(ckoo));
  gettimeofday(&mid, NULL);
  key_func(num_power, ckoo_get, static_cast<void*>(ckoo));
  gettimeofday(&end, NULL);

  delete ckoo;

  print_timediff("Insert time: ", start, mid);
  print_timediff("Query time: ", mid, end);
}

void khash_in_memory(int num_power, uint64_t num, RunKey key_func)
{
  struct timeval start, mid, end;
  khash_t(str) *kh;
  kh = kh_init(str);

  printf("khash in memory\n");
  gettimeofday(&start, NULL);
  key_func(num_power, khash_put, kh);
  gettimeofday(&mid, NULL);
  key_func(num_power, khash_get, kh);
  gettimeofday(&end, NULL);

  khint_t khint;
  for (khint = 0; khint < kh_end(kh); ++khint)
    if (kh_exist(kh, khint))
      free((char*)kh_key(kh, khint));

  kh_destroy(str, kh);

  print_timediff("Insert time: ", start, mid);
  print_timediff("Query time: ", mid, end);
}

void help(char* program)
{
  printf
    ("usage: %s [-n power_of_2] [-r repeat] [-k keytype]\n"
     "  [-i impl] [-m mode] [-f file] [-h]\n"
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
     "  -i impl    impl = robin_hood, dense_hash_map, sparse_hash_map,\n"
     "                    std_unordered_map, cuckoo, khash\n"
     "  -m mode    mode = in_memory, serialize, deserialize, or de_no_cache\n"
     "             in_memory: benchmark hash map creation time and query time\n"
     "               supported impl: all\n"
     "             serialize: hash_map creation time and serialization time\n"
     "               supported impl: robin_hood, sparse_hash_map\n"
     "                               std_unordered_map\n"
     "             deserialize: deserialize hash map then query for 2^n times\n"
     "               supported impl: robin_hood, sparse_hash_map\n"
     "                               std_unordered_map\n"
     "             de_no_cache: measures bare deserialization performance\n"
     "               supported impl: robin_hood\n"
     "  -f file    file used in serialize, deserialize and deserialize_cached\n"
     "             mode.\n"
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

  while ((opt = getopt(argc, argv, "n:r:k:i:f:m:h")) > -1)
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
          if (!strcmp("robin_hood", optarg))
            hash_impl = ROBIN_HOOD;
          else if (!strcmp("dense_hash_map", optarg))
            hash_impl = DENSE_HASH_MAP;
          else if (!strcmp("sparse_hash_map", optarg))
            hash_impl = SPARSE_HASH_MAP;
          else if (!strcmp("std_unordered_map", optarg))
            hash_impl = STD_UNORDERED_MAP;
          else if (!strcmp("cuckoo", optarg))
            hash_impl = CUCKOO;
          else if (!strcmp("khash", optarg))
            hash_impl = KHASH;
          else
            help(argv[0]);
          break;
        case 'm':
          if (!strcmp("in_memory", optarg))
            b_mode = IN_MEMORY;
          else if (!strcmp("serialize", optarg))
            b_mode = SERIALIZE;
          else if (!strcmp("deserialize", optarg))
            b_mode = DESERIALIZE;
          else if (!strcmp("de_no_cache", optarg))
            b_mode = DE_NO_CACHE;
          else
            help(argv[0]);
          break;
        case 'f':
          file_name = optarg;
          break;
        case 'h':
        case '?':
        default:
            help(argv[0]);
        }
    }

  if (key_func == run_long_int &&
      hash_impl != ROBIN_HOOD)
    {
      printf("We don't support integer key benchmark on "
             "hash map other than robin_hood yet.\n"
             "Feel free to contribute to add it in.\n");
      exit(1);
    }

  num = 1UL << num_power;
  printf("running elements %" PRIu64 "\n", num);

  for (int i = 0; i < repeat; i++)
    {
      printf("attempt %d\n", i + 1);
      switch (b_mode)
        {
        case IN_MEMORY:
          switch(hash_impl)
            {
            case ROBIN_HOOD:
              rhh_in_memory(num_power, num, key_func, k_len);
              break;
            case STD_UNORDERED_MAP:
              um_in_memory(num_power, num, key_func);
              break;
            case DENSE_HASH_MAP:
              dhm_in_memory(num_power, num, key_func);
              break;
            case SPARSE_HASH_MAP:
              shm_in_memory(num_power, num, key_func);
              break;
            case CUCKOO:
              ckoo_in_memory(num_power, num, key_func);
              break;
            case KHASH:
              khash_in_memory(num_power, num, key_func);
              break;
            }
          break;
        case SERIALIZE:
          op_assert(file_name, "Need to specify file name via -f option\n");
          switch (hash_impl)
            {
            case ROBIN_HOOD:
              rhh_serialize(num_power, num, key_func, k_len, file_name);
              break;
            case STD_UNORDERED_MAP:
              um_serialize(num_power, num, key_func, file_name);
              break;
            case SPARSE_HASH_MAP:
              shm_serialize(num_power, num, key_func, file_name);
              break;
            default:
              printf("not implemented yet\n");
              exit(1);
            }
          break;
        case DESERIALIZE:
          op_assert(file_name, "Need to specify file name via -f option\n");
          switch (hash_impl)
            {
            case ROBIN_HOOD:
              rhh_deserialize(num_power, key_func, file_name);
              break;
            case STD_UNORDERED_MAP:
              um_deserialize(num_power, key_func, file_name);
              break;
            case SPARSE_HASH_MAP:
              shm_deserialize(num_power, key_func, file_name);
              break;
            default:
              printf("not implemented yet\n");
              exit(1);
            }
          break;
        case DE_NO_CACHE:
          op_assert(file_name, "Need to specify file name via -f option\n");
          if (hash_impl != ROBIN_HOOD)
            {
              printf("not implemented yet\n");
              exit(1);
            }
          rhh_deserialize2(num_power, key_func, file_name);
        }
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


/* hash_bench.c ends here */
