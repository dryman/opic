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

#include <string>
#include <unordered_map>
#include <google/dense_hash_map>
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/unordered_map.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>


typedef void (*HashFunc)(char* key, void* context);
typedef void (*RunKey)(int size, HashFunc hash_func, void* context);
static void run_short_keys(int size, HashFunc hash_func, void* context);
static void run_mid_keys(int size, HashFunc hash_func, void* context);
static void run_long_keys(int size, HashFunc hash_func, void* context);
static void run_long_int(int size, HashFunc hash_func, void* context);
static void print_timediff(struct timeval start, struct timeval end);

enum HASH_IMPL
  {
    ROBIN_HOOD,
    DENSE_HASH_MAP,
    STD_UNORDERED_MAP,
  };

enum BENCHMARK_MODE
  {
    IN_MEMORY,
    SERIALIZE,
    DESERIALIZE,
    DE_NO_CACHE,
  };

void rhh_put(char* key, void* context)
{
  RobinHoodHash* rhh = (RobinHoodHash*)context;
  RHHPut(rhh, key, 0);
}

void rhh_get(char* key, void* context)
{
  static int counter;
  RobinHoodHash* rhh = (RobinHoodHash*)context;
  RHHGet(rhh,key);
}

void um_put(char* key, void* context)
{
  auto um = static_cast<std::unordered_map<std::string, uint64_t>*>(context);
  um->insert(std::make_pair(key, 0));
}

void um_get(char* key, void* context)
{
  auto um = static_cast<std::unordered_map<std::string, uint64_t>*>(context);
  um->at(key);
}

void dhm_put(char* key, void* context)
{
  auto dhm = static_cast<google::dense_hash_map
                         <std::string, uint64_t>*>(context);
  dhm->insert(std::make_pair(key, 0));
}

void dhm_get(char* key, void* context)
{
  auto dhm = static_cast<google::dense_hash_map
                         <std::string, uint64_t>*>(context);
  auto search = dhm->find(key);
  search->first;
}

void rhh_in_memory(int num_power, uint64_t num, RunKey key_func, int keysize)
{
  OPHeap* heap;
  RobinHoodHash* rhh;
  struct timeval start, mid, end;

  printf("RobinHoodHash in memory\n");
  op_assert(OPHeapNew(&heap), "Create OPHeap\n");
  op_assert(RHHNew(heap, &rhh, num,
                   0.80, keysize, 421439783), "Create RobinHoodHash\n");

  gettimeofday(&start, NULL);
  key_func(num_power, rhh_put, rhh);
  printf("insert finished\n");
  gettimeofday(&mid, NULL);
  key_func(num_power, rhh_get, rhh);
  gettimeofday(&end, NULL);

  print_timediff(start, mid);
  print_timediff(mid, end);
//RHHPrintStat(rhh);
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
                   0.80, keysize, 421439783), "Create RobinHoodHash\n");
  gettimeofday(&start, NULL);
  key_func(num_power, rhh_put, rhh);
  printf("insert finished\n");
  gettimeofday(&mid, NULL);
  stream = fopen(file, "w");
  printf("heap %p rhh %p\n", heap, rhh);
  OPHeapStorePtr(heap, rhh, 0);
  OPHeapWrite(heap, stream);
  fclose(stream);
  gettimeofday(&end, NULL);
  printf("serialized to %s\n", file);

  print_timediff(start, mid);
  print_timediff(mid, end);
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
  printf("heap %p rhh %p\n", heap, rhh);
  printf("deserialized\n");

  gettimeofday(&mid, NULL);
  key_func(num_power, rhh_get, rhh);
  gettimeofday(&end, NULL);

  print_timediff(start, mid);
  print_timediff(mid, end);
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

  print_timediff(start, end);
}

void um_in_memory(int num_power, uint64_t num, RunKey key_func)
{
  struct timeval start, mid, end;
  auto um = new std::unordered_map<std::string, uint64_t>(num);

  printf("std::unordered_map in memory\n");
  gettimeofday(&start, NULL);
  key_func(num_power, um_put, static_cast<void*>(um));
  printf("insert finished\n");
  gettimeofday(&mid, NULL);
  key_func(num_power, um_get, static_cast<void*>(um));
  gettimeofday(&end, NULL);

  delete um;

  print_timediff(start, mid);
  print_timediff(mid, end);
}

void um_serialize(int num_power, uint64_t num, RunKey key_func)
{
  struct timeval start, mid, end;
  auto um = new std::unordered_map<std::string, uint64_t>(num);

  printf("std::unordered_map in memory\n");
  gettimeofday(&start, NULL);
  key_func(num_power, um_put, static_cast<void*>(um));
  printf("insert finished\n");
  gettimeofday(&mid, NULL);
}

void dhm_in_memory(int num_power, uint64_t num, RunKey key_func)
{
  struct timeval start, mid, end;
  auto dhm = new google::dense_hash_map<std::string, uint64_t>(num);
  dhm->set_empty_key("\x00");
  dhm->set_deleted_key("\xff");

  printf("google::dense_hash_map in memory\n");

  gettimeofday(&start, NULL);
  key_func(num_power, dhm_put, static_cast<void*>(dhm));
  printf("insert finished\n");
  gettimeofday(&mid, NULL);
  key_func(num_power, dhm_get, static_cast<void*>(dhm));
  gettimeofday(&end, NULL);

  delete dhm;

  print_timediff(start, mid);
  print_timediff(mid, end);
}

/*
struct StringSerializer {
  bool operator()(FILE* fp, const std::string& value) const {
    assert(value.length() <= 255);   // we only support writing small strings
    const unsigned char size = value.length();
    if (fwrite(&size, 1, 1, fp) != 1)
      return false;
    if (fwrite(value.data(), size, 1, fp) != 1)
      return false;
    return true;
  }
  bool operator()(FILE* fp, std::string* value) const {
    unsigned char size;    // all strings are <= 255 chars long
    if (fread(&size, 1, 1, fp) != 1)
      return false;
    char* buf = new char[size];
    if (fread(buf, size, 1, fp) != 1) {
      delete[] buf;
      return false;
    }
    value->assign(buf, size);
    delete[] buf;
    return true;
  }
};

void dhm_serialize(int num_power, uint64_t num, RunKey key_func, char* file)
{
  struct timeval start, mid, end;
  FILE* stream;
  auto dhm = new google::dense_hash_map<std::string, uint64_t>(num);
  dhm->set_empty_key("\x00");
  dhm->set_deleted_key("\xff");

  printf("google::dense_hash_map serialization\n");

  gettimeofday(&start, NULL);
  key_func(num_power, dhm_put, static_cast<void*>(dhm));
  printf("insert finished\n");
  gettimeofday(&mid, NULL);

  stream = fopen(file, "w");
  dhm->serialize (StringSerializer(), stream);
  fclose(stream);
  gettimeofday(&end, NULL);
  print_timediff(start, mid);
  print_timediff(mid, end);
}
*/

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
     "  -i impl    impl = robin_hood, dense_hash_map, or std_unordered_map\n"
     "  -m mode    mode = in_memory, serialize, deserialize, or de_no_cache\n"
     "             in_memory: benchmark hash map creation time and query time\n"
     "             serialize: hash_map creation time and serialization time\n"
     "             deserialize: deserialize hash map then query for 2^n times\n"
     "             de_no_cache: measures bare deserialization performance\n"
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
          else if (!strcmp("std_unordered_map", optarg))
            hash_impl = STD_UNORDERED_MAP;
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

  num = 1UL << num_power;
  printf("running elements 2^%d = %" PRIu64 "\n", num_power, num);

  for (int i = 0; i < repeat; i++)
    {
      printf("attempt %d\n", i + 1);
      switch(b_mode)
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
            }
          break;
        case SERIALIZE:
          op_assert(file_name, "Need to specify file name via -f option\n");
          if (hash_impl != ROBIN_HOOD)
            {
              printf("not implemented yet\n");
              exit(1);
            }
          rhh_serialize(num_power, num, key_func, k_len, file_name);
          break;
        case DESERIALIZE:
          op_assert(file_name, "Need to specify file name via -f option\n");
          if (hash_impl != ROBIN_HOOD)
            {
              printf("not implemented yet\n");
              exit(1);
            }
          rhh_deserialize(num_power, key_func, file_name);
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
          for (int k = 0; k < 32; k++)
            uuid[j+k] = 0x21 + (val & 0x3F);
        }
      for (int j = 0; j < 64; j++)
        {
          for (int h = 0; h < 32; h++)
            uuid[h+1] = 0x21 + j;
          for (int k = 0; k < 64; k++)
            {
              for (int h = 0; h < 32; h++)
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


/* hash_bench.c ends here */
