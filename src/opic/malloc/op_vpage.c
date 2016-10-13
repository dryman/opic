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
#include "op_vpage.h"
#include "opic/common/op_utils.h"

OPVPage* OPVPageInit(void* addr)
{
  // use function attribute to check addr not null
  memset(addr, 0, sizeof(OPVPage));
  OPVPage *self = addr;
  return self;
}

OPSingularPSpan* OPVPageAllocPSpan(OPVPage* restrict self,
                                   uint16_t ta_idx,
                                   uint16_t obj_size,
                                   unsigned int span_cnt)
{
  op_assert(span_cnt <= 256, "span_cnt is limited to 256 pages, aka 1MB\n");

  uint64_t old_bmap, new_bmap;
  void* base = self;

  for (int i = 0; i < 512; i++)
    {
      while(1)
        {
          old_bmap = atomic_load_explicit(&self->occupy_bmap[i],
                                          memory_order_consume);
          if (old_bmap == ~0UL) break;
          int pos = fftstr0l(old_bmap, span_cnt);
          if (pos == -1) break;
          new_bmap = old_bmap | ((1UL << span_cnt)-1) << pos;

          if (atomic_compare_exchange_weak(&self->occupy_bmap[i],
                                           &old_bmap, new_bmap))
            {
              OPSingularPSpan* span;
              
              if (i == 0 && pos == 0)
                {
                  span = OPSingularPSpanInit
                    (base + sizeof(OPVPage),
                     ta_idx, obj_size,
                     (span_cnt << 12) - sizeof(OPVPage));
                }
              else
                {
                  span = OPSingularPSpanInit
                    (base + (((i << 6) + pos) << 12),
                     ta_idx, obj_size,
                     span_cnt << 12);
                }
              // TODO setup linked list of TA
              atomic_fetch_or_explicit(&self->header_bmap[i], 1UL << pos,
                                       memory_order_release);
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
  OPSingularPSpan* span;
  int page_idx = diff >> 12;
  uint64_t mask = ~0UL;
  
  if (page_idx == 0)
    {
      span = base + sizeof(OPVPage);
      mask = ~1UL;
    }
  else 
    {    
      uint64_t bitmap = atomic_load_explicit(&self->header_bmap[page_idx >> 6],
                                             memory_order_consume);
      uint64_t clear_low = bitmap & ~((1UL << page_idx % 64)-1);
      int span_header_idx = ((page_idx >> 6) << 6) + __builtin_ctzl(clear_low);
      span = base + (span_header_idx << 12);
      mask = ~(clear_low & (~(clear_low) + 1));
    }

  if (!OPSingularPSpanFree(span, addr))
    return false;
  
  atomic_fetch_and_explicit(&self->header_bmap[page_idx >> 6], mask,
                            memory_order_relaxed);

  if (atomic_load_explicit(&self->header_bmap[page_idx >> 6],
                           memory_order_consume))
    return false;

  uint64_t expected_empty = 0UL;
  int iter = 0;

  for (iter = 0; iter < 512; iter++)
    if (!atomic_compare_exchange_strong(&self->header_bmap[iter],
                                        &expected_empty,
                                        ~0UL))
      goto catch_nonempty_exception;

  return true;
  
 catch_nonempty_exception:

  for (int i = 0; i < iter; i++)
    atomic_store(&self->header_bmap[i], 0UL);
      
  return false;
}

  

/* op_vpage.c ends here */
