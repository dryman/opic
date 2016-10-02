/* op_malloc.c --- 
 * 
 * Filename: op_malloc.c
 * Description: 
 * Author: Felix Chern
 * Maintainer: Felix Chern
 * Created: Sat Oct  1 16:25:47 2016
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
 * it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "op_malloc.h"
#include "../common/op_utils.h"
//#include "../common/op_log.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/mman.h>
#include <stdatomic.h>

#define OP_MEMORY_MANAGER_SIZE (1L << 36)
#define OP_VPAGE_SIZE (1L << 21)

//OP_LOGGER_FACTORY(logger, "opic.malloc.op_malloc")

struct OPMemoryManager
{
  atomic_uint_fast64_t vspan_avail_bmap[512];
  atomic_uint_fast64_t vspan_header_bmap[512];
};


int OPMemoryManagerCreate(OPMemoryManager** ref)
{
  *ref = mmap(NULL, OP_MEMORY_MANAGER_SIZE,
              PROT_READ | PROT_WRITE,
              MAP_ANON | MAP_PRIVATE, -1, 0);
  if (*ref == MAP_FAILED)
    {
      // should use logger
      printf("mmap failed %s\n", strerror(errno));
      return -1;
    }

  OPMemoryManager* self = *ref;

  for (int i = 0; i < 512; i++)
    {
      atomic_store(&self->vspan_avail_bmap[i], ~0L);
    }
  // turn off lsb as we uses it
  atomic_fetch_sub(&self->vspan_avail_bmap[0], 1L);

  return 0;
}

void OPMemoryManagerDestory(OPMemoryManager* self)
{
  munmap(self, OP_MEMORY_MANAGER_SIZE);
}

void* OPMallocVSpan(OPMemoryManager* self, int pages)
{
  // assert pages < 64
  uint64_t mask, new_mask;
  if (pages == 1)
    {
      // TODO should avoid linear scan
      for (int i = 0; i < 512; i++)
        {
          while (1)
            {
              mask = atomic_load_explicit(&self->vspan_avail_bmap[i],
                                          memory_order_acquire);
              if (mask == 0) break;
              uint64_t isolate_bit = ~mask & (mask+1);
              new_mask = mask & (~isolate_bit);
              if (atomic_compare_exchange_weak(&self->vspan_avail_bmap[i],
                                               &mask, new_mask))
                {
                  // we should really set the header, then set the header
                  // bit
                  atomic_fetch_or_explicit(&self->vspan_header_bmap[i],
                                           isolate_bit,
                                           memory_order_release);
                  return self + (64*i + __builtin_ctzl(isolate_bit))
                         * OP_VPAGE_SIZE;
                }
            }
        }
      // TODO: error, running out of vpages
    }
  else
    {
      for (int i = 0; i < 512; i++)
        {
          while (1)
            {
              mask = atomic_load_explicit(&self->vspan_avail_bmap[i],
                                          memory_order_acquire);
              if (mask == 0) break;
              int pos = fftstr1l(mask, pages);
              if (pos == -1) break;
              new_mask = mask & ((1L << (pos + 1)) -1);
              if (atomic_compare_exchange_weak(&self->vspan_avail_bmap[i],
                                               &mask, new_mask))
                {
                  atomic_fetch_or_explicit(&self->vspan_header_bmap[i],
                                           1L << pos,
                                           memory_order_release);
                  return self + (64*i + pos) * OP_VPAGE_SIZE;
                }
            }
        }
      // TODO: error, running out of vpages
    }
}

void OPFreeVSpan(OPMemoryManager* self, void* addr, int pages)
{
}

int main(int argc, char** argv)
{
  OPMemoryManager* mm;
  if (OPMemoryManagerCreate(&mm))
    {
      exit(1);
    }

  printf("Hello world\n");
  void* p1 = OPMallocVSpan(mm, 1);
  void* p2 = OPMallocVSpan(mm, 5);
  void* p3 = OPMallocVSpan(mm, 40);
  void* p4 = OPMallocVSpan(mm, 35);

  printf("mm: %p\n"
         "p1: %p\n"
         "p2: %p\n"
         "p3: %p\n"
         "p4: %p\n", mm, p1, p2, p3, p4);
  
  OPMemoryManagerDestory(mm);
  return 0;
}

/* op_malloc.c ends here */
