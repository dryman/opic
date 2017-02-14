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


#include <stddef.h>
#include <string.h>
#include <limits.h>
#include "span.h"
#include "huge_page.h"
#include "opic/common/op_utils.h"

OP_LOGGER_FACTORY(logger, "opic.malloc.huge_page");

void HugePageInit(HugePage* self, Magic magic)
{
  /*
  op_assert(((size_t)addr & ((1UL<<21)-1)) == 0,
            "HugePage address should align 2MB, but were %p\n", addr);
  */
  OPHeap* heap = get_opheap(self);

  memset(&self->occupy_bmap, 0, sizeof(self->occupy_bmap));
  memset(&self->header_bmap, 0, sizeof(self->header_bmap));
  self->magic = magic;
  self->next = NULL;

  if (self == heap->first_hpage)
    {
      int occupied = round_up_div(sizeof(OPHeap), (1UL << 12));
      int i;
      for (i = 0; i < occupied/64; i++)
        self->occupy_bmap[i] = ~0UL;
      self->occupy_bmap[i] |= (1UL << (occupied % 64)) - 1;
    }
}


bool ObtainUSpan(HugePage* self,
                 UnarySpan** uspan,
                 Magic magic,
                 unsigned int span_cnt)
{
  // In current logic, we can get at most 64 spans..
  op_assert(span_cnt <= 64,
            "span_cnt is limited to 64 pages, aka 512KB\n");

  uint64_t old_bmap, new_bmap;
  uintptr_t base;
  Magic magic = self->magic;
  OPHeap* heap = get_opheap(self);
  a_int16_t* hpage_queue_pcard;
  HugePage** hpage_queue;

  while (1)
    {
      base = self == heap->first_hpage ? (uintptr_t)heap : (uintptr_t)self;
      if (!atomic_check_in(&self->pcard))
        return false;
      for (int i = 0; i < 8; i++)
        {
          old_bmap = atomic_load_explicit(&self->occupy_bmap[i],
                                          memory_order_relaxed);
          /* Unlike uspan, we don't capture the item count in
           * huge span.  In uspan we can use the count to show
           * if the span is available for allocation, because
           * the empty spot is guaranteed to present.  In huge page,
           * however, even if the required space is less than the
           * count, we may not have enough contiguous space to allocate.
           */
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
                  *uspan = (UnarySpan*)(base + ((i*64 + pos) << 12));
                  if (i == 0 && pos == 0)
                    USpanInit(*uspan, magic,
                              (span_cnt << 12) - sizeof(HugePage));
                  else
                    USpanInit(*uspan, magic, span_cnt << 12);
                  atomic_fetch_or_explicit(&self->header_bmap[i], 1UL << pos,
                                           memory_order_release);
                  atomic_check_out(&self->pcard);
                  return true;
                }
            }
        }
      atomic_check_out(&self->pcard);

      if (magic.generic.pattern == RAW_HPAGE_PATTERN)
        {
          hpage_queue_pcard = &heap->raw_type.hpage_pcard;
          hpage_queue = &heap->raw_type.hpage;
        }
      else
        {
          TypeAlias* ta = &heap->type_alias[magic.typed_hpage.type_alias];
          hpage_queue_pcard = &ta->hpage_pcard;
          hpage_queue = &ta->hpage;
        }
      if (!atomic_book_critical(hpage_queue_pcard))
        return false;
      atomic_enter_critical(hpage_queue_pcard);
      dequeue_hpage(hpage_queue, self);

      // If the next page is available, use it
      if (*hpage_queue)
        {
          self = *hpage_queue;
          atomic_exit_critical(hpage_queue_pcard);
          continue;
        }
      // else insert a new hpage
      for (int i = 0; i < 10; i++)
        {
          if (ObtainHPage(heap, &self, magic))
            goto obtain_hpage_success;
        }
      return false;

    obtain_hpage_success:
      enqueue_hpage(hpage_queue, self);
      atomic_exit_critical(hpage_queue_pcard);
      // continue with new self
    }
}

BitMapState HPageFree(HugePage* self, void* addr)
{
  OPHeap* heap = get_opheap(self);
  bool is_first_hpage = self == heap->first_hpage;
  uintptr_t base = is_first_hpage ? (uintptr_t)heap : (uintptr_t)self;
  ptrdiff_t diff = (uintptr_t)addr - base;
  UnarySpan* span;
  int page_idx = diff >> 12;
  int span_header_idx;
  uint64_t header_mask, occupy_mask;
  size_t span_size;

  // TODO: this implementation is assuming pspan can only be
  // UnaryPSpan, but we might have Varying PSpan (alloc multiple
  // element at same time), and Array PSpan (array of objects cross
  // multiple pages) in near future.

  // Do we really need to check in?
  while (!atomic_check_in(&self->punch_card))
    ;


  if (page_idx == 0)
    {
      span = base + sizeof(HugePage);
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

  if (USpanFree(span, addr) == BM_NORMAL)
    return BM_NORMAL;


  /*** PSpan is freed. Start critical section ***/

  // First exclude access
  /* int8_t expected_refcnt = 0; */
  /* while (!atomic_compare_exchange_weak_explicit */
  /*        (&self->refcnt[span_header_idx], */
  /*         &expected_refcnt, CHAR_MIN, */
  /*         memory_order_acquire, */
  /*         memory_order_relaxed)) */
  /*   expected_refcnt = 0; */

  atomic_fetch_and_explicit(&self->header_bmap[page_idx >> 6], header_mask,
                            memory_order_relaxed);

  // need to determine span type..
  span_size = span->magic.typed_uspan.obj_size*
    (64*span->bitmap_cnt - span->bitmap_padding);
  // first occupy bitmap is different
  if (page_idx == 0) span_size += sizeof(HugePage);
  op_assert((span_size & ((1UL<<12)-1))==0,
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

void HPageFreeUSpan(HugePage* self, void* addr)
{
}

/* op_vpage.c ends here */
