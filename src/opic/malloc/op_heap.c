/* op_heap.c --- 
 * 
 * Filename: op_heap.c
 * Description: 
 * Author: Felix Chern
 * Maintainer: 
 * Copyright: (c) 2016 Felix Chern
 * Created: Sat Oct 22, 2016
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


#include "op_heap.h"
#include "op_pspan.h"
#include "op_vpage.h"
#include <stddef.h>
#include <string.h>
#include <sys/mman.h>

#define OPHEAP_SIZE (1L << 36)
#define VPAGE_MASK (~((1L << 21) - 1))
#define PPAGE_MASK (~((1L << 12) - 1))
#define VSPAN_NUM (1 << 15)
#define VSPAN_BMAP_NUM (1 << 9)

typedef struct RawType RawType;
typedef struct TypeAlias TypeAlias;
typedef struct UnarySizeClass UnarySizeClass;
typedef struct PolyadicSizeClass PolyadicSizeClass;

static __thread int tid = -1;
static atomic_uint round_robin = 0;

OP_LOGGER_FACTORY(logger, "opic.malloc.op_heap");


struct RawType
{
  // Thread local physical spans. In total of 16 size classes to serve
  // objects of size from 16 bytes to 256 bytes. Each size class has
  // 16 thread local UnaryPSpan pointers.
  UnaryPSpan* tlspan[16][16];
  // Thread local read write lock
  atomic_int_fast8_t tlrwlock[16][16];
  // 16 favor wirte flags, each bit coresponds to a thread local lock.
  atomic_uint_fast16_t tlfavor_w[16];
  PolyadicPSpan* sc_512;
  PolyadicPSpan* sc_1024;
  PolyadicPSpan* sc_2048;
  OPVPage* vpage;
  atomic_int_fast16_t rwlock_512;
  atomic_int_fast16_t rwlock_1024;
  atomic_int_fast16_t rwlock_2048;
  atomic_int_fast16_t rwlock_vpage;
  // favor write flag for sc_512, sc_1024, sc_2048
  atomic_uint_fast8_t favor_w;
  char reserved;
};

struct TypeAlias
{
  // TODO: change to Class* when we merge with object
  void *klass;
  char *type_name;
  UnaryPSpan* tlspan[16];
  atomic_int_fast8_t tlrwlock[16];
  atomic_uint_fast32_t favor_w;
  PolyadicPSpan* ppspan;
  atomic_int_fast16_t ppspan_rwlock;
  OPVPage* vpage;
  atomic_int_fast16_t vpage_rwlock;
};

struct OPHeap
{
  // TODO: add a magic in the very front so UNIX
  // can recognize us?
  atomic_uint_fast64_t occupy_bmap[VSPAN_BMAP_NUM];
  atomic_uint_fast64_t header_bmap[VSPAN_BMAP_NUM];
  struct RawType raw_type;
  struct TypeAlias type_alias[2048];
};

int OPHeapCreate(OPHeap** heap_ref)
{
  ptrdiff_t offset = OPHEAP_SIZE;
  void* addr = NULL + offset;
  void* map_addr = MAP_FAILED;
  OPHeap* self;
  for (int i = 0; i < (1<<15); i++)
    {
      OP_LOG_INFO(logger,
                  "Attempt to create OPHeap on %p",
                  addr);
      map_addr = mmap(addr, OPHEAP_SIZE,
                      PROT_READ | PROT_WRITE,
                      MAP_ANON | MAP_PRIVATE | MAP_FIXED,
                      -1, 0);
      if (map_addr != MAP_FAILED)
        {
          OP_LOG_INFO(logger,
                      "Successfully created OPHeap on %p",
                      map_addr);
          *heap_ref = map_addr;
          self = *heap_ref;
          goto init_opheap;
        }
      else
        addr += OPHEAP_SIZE;
    }
  OP_LOG_ERROR(logger,
               "Cannot allocate OPHeap, reached address limit");
  return -1;

 init_opheap:
  memset(self, 0, sizeof(OPHeap));
  atomic_store_explicit(&self->occupy_bmap[0], 1, memory_order_relaxed);
  atomic_store_explicit(&self->header_bmap[0], 1, memory_order_relaxed);
  return 0;
}

void* OPAllocRaw(OPHeap* self, size_t size)
{
  if (tid == -1)
    tid = atomic_fetch_add_explicit(&round_robin, 1, memory_order_acquire) % 16;

  
  return NULL;
}

      
/* op_heap.c ends here */
