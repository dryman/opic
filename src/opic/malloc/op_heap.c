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

#include "op_lock_utils.h"
#include "op_heap.h"
#include "op_pspan.h"
#include "op_vpage.h"
#include <string.h>
#include <sys/mman.h>
#include <stdlib.h>

#define OPHEAP_SIZE (1L << 36)
#define VPAGE_MASK (~((1L << 21) - 1))
#define PPAGE_MASK (~((1L << 12) - 1))
#define VSPAN_NUM (1 << 15)
#define VSPAN_BMAP_NUM (1 << 9)

typedef struct RawType RawType;
typedef struct TypeAlias TypeAlias;

static __thread int thread_id = -1;
static atomic_uint round_robin = 0;

OP_LOGGER_FACTORY(logger, "opic.malloc.op_heap");


struct RawType
{
  // Thread local physical spans. In total of 16 size classes to serve
  // objects of size from 16 bytes to 256 bytes. Each size class has
  // 16 thread local UnaryPSpan pointers.
  UnarySpan* uspan[16][16];
  // Thread local read write lock
  atomic_int_fast8_t uspan_rwlock[16][16];
  // 16 favor wirte flags, each bit coresponds to a thread local lock.
  atomic_uint_fast16_t uspan_favor[16];
  PolyadicSpan* sc_512;
  PolyadicSpan* sc_1024;
  PolyadicSpan* sc_2048;
  HugePage* vpage;
  atomic_int_fast16_t sc_512_rwlock;  
  atomic_int_fast16_t sc_1024_rwlock;
  atomic_int_fast16_t sc_2048_rwlock;
  atomic_int_fast16_t vpage_rwlock;
  // favor flag for sc_512, sc_1024, sc_2048, and vpage
  atomic_uint_fast8_t remain_favor;
};

struct TypeAlias
{
  // TODO: change to Class* when we merge with object
  void *klass;
  char *type_name;
  UnarySpan* uspan[16];
  atomic_int_fast8_t uspan_rwlock[16];
  atomic_uint_fast16_t uspan_favor;
  PolyadicSpan* polyspan;
  atomic_int_fast16_t polyspan_rwlock;
  HugePage* vpage;
  atomic_int_fast16_t vpage_rwlock;
  atomic_uint_fast8_t remain_favor;
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
  // TODO assign first hugepage to raw
  atomic_store_explicit(&self->occupy_bmap[0], 1, memory_order_relaxed);
  atomic_store_explicit(&self->header_bmap[0], 1, memory_order_relaxed);
  return 0;
}

void* OPAllocRaw(OPHeap* self, size_t size)
{
  if (thread_id == -1)
    thread_id = atomic_fetch_add_explicit
      (&round_robin, 1, memory_order_acquire) % 16;

  int tid = thread_id;
  void* addr;
  
  if (size <= 256)
    {
      int size_class = (int)(size >> 4);
      size_class += (int)size - (size_class << 4) == 0 ? 0 : 1;

      UnarySpan* uspan;

      while (1)
        {
          acq_rlock(&self->raw_type.uspan_rwlock[size_class][tid],
                    &self->raw_type.uspan_favor[size_class],
                    tid);
          uspan = self->raw_type.uspan[size_class][tid];
          if (uspan == NULL)
            {
              favor_write(&self->raw_type.uspan_favor[size_class],
                          tid);
              rel_rlock(&self->raw_type.uspan_rwlock[size_class][tid]);
              insert_new_uspan(0, // span magic, we need a magic processor...
                               size_class,
                               &self->raw_type.uspan[size_class][tid],
                               &self->raw_type.uspan_rwlock[size_class][tid],
                               &self->raw_type.uspan_favor[size_class],
                               tid,
                               &self->raw_type.vpage,
                               &self->raw_type.vpage_rwlock,
                               &self->raw_type.remain_favor,
                               3, // TODO use enum?
                               self);
            }
          else 
            {
              addr = USpanMalloc(uspan);
              if (addr)
                goto small_addr_obtained;

              // TODO mark span as full
              favor_write(&self->raw_type.uspan_favor[size_class],
                          tid);
              rel_rlock(&self->raw_type.uspan_rwlock[size_class][tid]);
              remove_uspan(&self->raw_type.uspan[size_class][tid],
                           &self->raw_type.uspan_rwlock[size_class][tid],
                           &self->raw_type.uspan_favor[size_class],
                           tid,
                           uspan);
            }
        }
    small_addr_obtained:
      rel_rlock(&self->raw_type.uspan_rwlock[size_class][tid]);
      return addr;      
    }
  else if (size < 4096)
    {
      op_assert(0, "not implemented yet\n");

    }
  else
    {
      op_assert(0, "not implemented yet\n");
    }
  
  return NULL;
}

HugePage* ObtainHPage(OPHeap* self)
{
  uint64_t old_bmap, new_bmap;
  ptrdiff_t item_offset;

  for (int i = 0; i < VSPAN_BMAP_NUM;)
    {
      old_bmap = atomic_load_explicit(&self->occupy_bmap[i],
                                      memory_order_relaxed);
      do
        {
          if (old_bmap == ~0UL) goto next_bmap;
          new_bmap = (old_bmap + 1);
          item_offset = __builtin_ctzl(new_bmap);
          new_bmap |= old_bmap;
        } while (!atomic_compare_exchange_weak_explicit
                 (&self->occupy_bmap[i], &old_bmap, new_bmap,
                  memory_order_acquire,
                  memory_order_relaxed));
      
      HugePage* hpage = HugePageInit((void*)self + ((i << 6) + item_offset));
      atomic_fetch_or_explicit(&self->header_bmap[i], 1UL << item_offset,
                               memory_order_release);
      return hpage;

    next_bmap:
      i++;
    }
  op_assert(0, "Running out of hpage\n");
}
      
          
/* op_heap.c ends here */
