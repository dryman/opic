/* op_pspan.c --- 
 * 
 * Filename: op_pspan.c
 * Description: 
 * Author: Felix Chern
 * Maintainer: 
 * Copyright: (c) 2016 Felix Chern
 * Created: Sat Oct 8, 2016
 * Version: 0.3.0
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

#include "op_pspan.h"
#include <stdatomic.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>


OPSingularPSpan* OPSingularPSpanInit(void* restrict addr, uint16_t ta_idx,
                                     uint16_t obj_size, size_t span_size)
{
  /* Unit test as of Oct 9, 2016 doesn't support op_assert
     Our workaround is return NULL instead. But this should be fixed.
  op_assert(addr, "address cannot be NULL");
  op_assert(obj_size, "object size in bytes should be greater than 0\n");
  op_assert(page_size, "allocated physical pages should be greater than 0\n");
  */
  if (op_unlikely(!addr)) return NULL;
  if (op_unlikely(!obj_size)) return NULL;
  if (op_unlikely(!span_size)) return NULL;
  
  unsigned int obj_cnt, bitmap_cnt, padding, headroom;
  obj_cnt = span_size / obj_size;
  bitmap_cnt = (obj_cnt + 64 - 1) >> 6;
  padding = (bitmap_cnt << 6) - obj_cnt;
  headroom = (sizeof(OPSingularPSpan) + bitmap_cnt*8 + obj_size - 1)/obj_size;

  op_assert(headroom < 64,
            "headroom should be less equal to 64, but it is %d\n", headroom);
  
  OPSingularPSpan span = 
    {
      .ta_idx = ta_idx,
      .obj_size = obj_size,
      .bitmap_cnt = (uint8_t)bitmap_cnt,
      .bitmap_headroom = (uint8_t)headroom,
      .bitmap_padding = (uint8_t)padding,
      .bitmap_hint = 0,
      .prev = NULL,
      .next = NULL
    };

  memcpy(addr, &span, sizeof(span));
  OPSingularPSpan* self = addr;

  addr += sizeof(OPSingularPSpan);

  memset(addr, 0, bitmap_cnt << 3);
  atomic_fetch_or((_Atomic uint64_t *) addr, (1UL << headroom)-1);
  if (padding)
    atomic_fetch_or((_Atomic uint64_t *) (addr + ((bitmap_cnt-1) << 3)),
                    ~((1UL << (64-padding))-1));

  return self;
}

void* OPSingularPSpanMalloc(OPSingularPSpan* restrict self)
{
  op_assert(self, "Address cannot be NULL");
  _Atomic uint64_t *bitmap_base, *bitmap;
  ptrdiff_t bitmap_offset, item_offset;
  uint64_t old_bmap, new_bmap;
  
  bitmap_base = (_Atomic uint64_t *)(self+1);
  bitmap_offset = (ptrdiff_t)self->bitmap_hint;
  bitmap = bitmap_base + bitmap_offset;

  void* addr;
  for (int i = 0; i < self->bitmap_cnt; i++)
    {
      old_bmap = atomic_load_explicit(bitmap, memory_order_relaxed);
      do
        {
          if (old_bmap == ~0UL) goto next_bmap;
          new_bmap = (old_bmap + 1);
          item_offset = __builtin_ctzl(new_bmap);
          new_bmap |= old_bmap;
        } while(!atomic_compare_exchange_weak_explicit
                (bitmap, &old_bmap, new_bmap,
                 memory_order_relaxed,
                 memory_order_relaxed));
      
      addr = (void*)self +
        (((bitmap_offset % self->bitmap_cnt) << 6) + item_offset)
        * self->obj_size;

      self->bitmap_hint = (uint8_t)(bitmap_offset % self->bitmap_cnt);

      // ta_idx == 0 is for primitives
      if (self->ta_idx)
        *(uint16_t*)addr = self->ta_idx;
      return addr;
      
    next_bmap:
      bitmap_offset++;
      bitmap = bitmap_base + (bitmap_offset % self->bitmap_cnt);
      continue;
    }
  return NULL;
}

bool OPSingularPSpanFree(OPSingularPSpan* restrict self, void* restrict addr)
{
  op_assert(self, "Address cannot be NULL");
  ptrdiff_t diff = (addr - (void*)self) / self->obj_size;
  // assert diff*obj_size + self == addr
  // assert attempt to free is not freed

  _Atomic uint64_t *bitmap = (_Atomic uint64_t *)(self+1);
  const int bmap_idx = diff >> 6;
  const int remainder = diff - (bmap_idx << 6);
  
  atomic_fetch_and(&bitmap[bmap_idx], ~(1UL<<remainder));

  if (self->bitmap_cnt == 1)
    {
      uint64_t expected_empty_bmap =
        ((1UL << self->bitmap_headroom)-1) |
        ~((1UL << (64-self->bitmap_padding))-1);
      if (atomic_compare_exchange_strong_explicit
          (bitmap, &expected_empty_bmap, ~0UL,
           memory_order_release,
           memory_order_relaxed))
      return true;
    }
  else if (bmap_idx == 0 &&
           atomic_load_explicit(bitmap, memory_order_relaxed)==
           (1UL << self->bitmap_headroom)-1)
    {
      goto try_fullfree;
    }
  else if (bmap_idx == self->bitmap_cnt - 1)
    {
      if (atomic_load_explicit(&bitmap[bmap_idx], memory_order_relaxed) ==
          (self->bitmap_padding ?
           ~((1UL << (64 - self->bitmap_padding))-1) :
           0UL))
        goto try_fullfree;
    }
  else if (!atomic_load(&bitmap[bmap_idx]))
    {
      goto try_fullfree;
    }
  else
    return false;

  int iter;
  uint64_t expected_headroom, expected_body, expected_padding;
  
 try_fullfree:
  
  iter = 0;
  expected_headroom = (1UL << self->bitmap_headroom)-1;
  expected_body = 0UL;
  expected_padding = self->bitmap_padding ?
    ~((1UL << (64 - self->bitmap_padding))-1) : 0UL;

  // headroom
  if (!atomic_compare_exchange_strong_explicit
      (&bitmap[0], &expected_headroom, ~0UL,
       memory_order_relaxed,
       memory_order_relaxed))
    return false;

  // body
  for (iter = 1; iter < self->bitmap_cnt - 1; iter++)
    {
      expected_body = 0UL;
    if (!atomic_compare_exchange_strong_explicit
        (&bitmap[iter], &expected_body, ~0UL,
         memory_order_relaxed,
         memory_order_relaxed))
      goto catch_nonempty_exception;
    }

  // padding
  if (atomic_compare_exchange_strong_explicit
      (&bitmap[iter], &expected_padding, ~0UL,
       memory_order_relaxed,
       memory_order_relaxed))
    return true;

 catch_nonempty_exception:

  // headroom
  expected_headroom = (1UL << self->bitmap_headroom)-1;
  atomic_store_explicit(&bitmap[0], expected_headroom, memory_order_relaxed);

  // body
  for (int i = 1; i < iter; i++)
    {
      atomic_store_explicit(&bitmap[i], 0UL, memory_order_relaxed);
    }
  
  return false;
}


/* op_pspan.c ends here */
