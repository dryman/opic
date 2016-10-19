/* op_vpage.c --- 
 * 
 * Filename: op_vpage.c
 * Description: 
 * Author: Felix Chern
 * Maintainer: 
 * Copyright: (c) 2016 Felix Chern
 * Created: Tue Oct 11 2016
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


#include <string.h>
#include <limits.h>
#include "op_vpage.h"
#include "opic/common/op_utils.h"

OP_LOGGER_FACTORY(logger, "opic.malloc.op_vpage");

OPVPage* OPVPageInit(void* addr)
{
  op_assert(addr, "address should not be null\n");
  op_assert(((size_t)addr & (1UL<<21)-1) == 0,
            "OPVPage address should align 2MB, but were %p\n", addr);
  memset(addr, 0, 16*8);
  memset(addr+16*8, CHAR_MIN, 512);
  OPVPage *self = addr;
  return self;
}


UnaryPSpan* OPVPageAllocPSpan(OPVPage* restrict self,
                              uint16_t ta_idx,
                              uint16_t obj_size,
                              unsigned int span_cnt)
{
  op_assert(self, "OPVPage cannot be NULL\n");
  op_assert(span_cnt <= 256, "span_cnt is limited to 256 pages, aka 1MB\n");

  uint64_t old_bmap, new_bmap;
  void* base = self;

  for (int i = 0; i < 8; i++)
    {
      old_bmap = atomic_load_explicit(&self->occupy_bmap[i],
                                      memory_order_relaxed);
      while(1)
        {
          if (old_bmap == ~0UL) break;
          int pos = fftstr0l(old_bmap, span_cnt);
          if (pos == -1) break;
          new_bmap = old_bmap | ((1UL << span_cnt)-1) << pos;

          if (atomic_compare_exchange_weak_explicit
              (&self->occupy_bmap[i], &old_bmap, new_bmap,
               memory_order_acquire,
               memory_order_relaxed))
            {
              // Write to UnaryPSpan should not be visible before
              // occupy_bmap is set. This is enforced by
              // memory_order_acquire on success. UnaryPSpan is
              // visible after we set the header_bmap.
              UnaryPSpan* span;

              if (i == 0 && pos == 0)
                {
                  span = UnaryPSpanInit(base + sizeof(OPVPage),
                                        ta_idx, obj_size,
                                        (span_cnt << 12) - sizeof(OPVPage));
                }
              else
                {
                  span = UnaryPSpanInit(base + (((i << 6) + pos) << 12),
                                        ta_idx, obj_size,
                                        span_cnt << 12);
                }

              // TODO setup linked list of TA
              atomic_fetch_or_explicit(&self->header_bmap[i], 1UL << pos,
                                       memory_order_relaxed);

              // As long as concurrent access < 127, our state is well defined
              int8_t expected_refcnt = CHAR_MIN;
              while (!atomic_compare_exchange_weak_explicit
                     (&self->refcnt[i*64+pos], &expected_refcnt, 0,
                      memory_order_release,
                      memory_order_relaxed))
                expected_refcnt = CHAR_MIN;
              
              return span;
            }
        }
    }
  return NULL;
}

bool OPVPageFree(OPVPage* restrict self, void* addr)
{
  void* base = (void*)self;
  ptrdiff_t diff = addr - base;
  UnaryPSpan* span;
  int page_idx = diff >> 12;
  int span_header_idx;
  uint64_t header_mask, occupy_mask;
  size_t span_size;

  // TODO: this implementation is assuming pspan can only be
  // UnaryPSpan, but we might have Varying PSpan (alloc multiple
  // element at same time), and Array PSpan (array of objects cross
  // multiple pages) in near future.
  
  if (page_idx == 0)
    {
      span = base + sizeof(OPVPage);
      header_mask = ~1UL;
      span_header_idx = 0;
    }
  else 
    {    
      uint64_t bitmap = atomic_load_explicit(&self->header_bmap[page_idx >> 6],
                                             memory_order_relaxed);
      uint64_t clear_low = bitmap & ~((1UL << page_idx % 64)-1);
      span_header_idx = ((page_idx >> 6) << 6) + __builtin_ctzl(clear_low);
      span = base + (span_header_idx << 12);
      header_mask = ~(clear_low & (~(clear_low) + 1));
    }

  if (!UnaryPSpanFree(span, addr))
    return false;

  /*** PSpan is freed. Start critical section ***/

  // First exclude access
  int8_t expected_refcnt = 0;
  while (!atomic_compare_exchange_weak_explicit
         (&self->refcnt[span_header_idx],
          &expected_refcnt, CHAR_MIN,
          memory_order_acquire,
          memory_order_relaxed))
    expected_refcnt = 0;
  
  atomic_fetch_and_explicit(&self->header_bmap[page_idx >> 6], header_mask,
                            memory_order_relaxed);

  span_size = span->obj_size*(64*span->bitmap_cnt - span->bitmap_padding);
  // first occupy bitmap is different
  if (page_idx == 0) span_size += sizeof(OPVPage);
  op_assert((span_size & (1UL<<12)-1)==0,
            "span size should align page, but were %zu", span_size);
  occupy_mask = ~(((1UL << (span_size >> 12))-1) << span_header_idx);

  // Release semantic to ensure header unmark happens before occupy unmark
  atomic_fetch_and_explicit(&self->occupy_bmap[page_idx >> 6], occupy_mask,
                            memory_order_release);
  
  if (atomic_load_explicit(&self->occupy_bmap[page_idx >> 6],
                           memory_order_relaxed))
    return false;


  uint64_t expected_empty = 0UL;
  int iter = 0;
  
  for (iter = 0; iter < 8; iter++)
    {
      expected_empty = 0UL;
      if (!atomic_compare_exchange_strong_explicit
          (&self->occupy_bmap[iter], &expected_empty, ~0UL,
           memory_order_acquire,
           memory_order_relaxed))
        goto catch_nonempty_exception;
    }

  return true;
  
 catch_nonempty_exception:

  for (int i = 0; i < iter; i++)
    atomic_store_explicit(&self->occupy_bmap[i], 0UL,
                          memory_order_release);
      
  return false;
}

/* op_vpage.c ends here */
