/* deallocator.c ---
 *
 * Filename: deallocator.c
 * Description:
 * Author: Felix Chern
 * Maintainer:
 * Copyright: (c) 2017 Felix Chern
 * Created: Thu Mar 16 22:04:56 2017 (-0700)
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
#include "opic/common/op_assert.h"
#include "opic/common/op_atomic.h"
#include "deallocator.h"
#include "inline_aux.h"
#include "init_helper.h"
#include "lookup_helper.h"


void
OPDealloc(void* addr)
{
  HugeSpanPtr hspan;
  SmallSpanPtr sspan;

  hspan = ObtainHugeSpanPtr(addr);
  if (hspan.magic->generic.pattern == HUGE_BLOB_PATTERN)
    {
      OPHeapReleaseHSpan(hspan);
      return;
    }
  sspan = HPageObtainSmallSpanPtr(hspan.hpage, addr);
  if (sspan.magic->generic.pattern == SMALL_BLOB_PATTERN)
    {
      HPageReleaseSSpan(hspan.hpage, sspan);
      return;
    }
  USpanReleaseAddr(sspan.uspan, addr);
}

void
USpanReleaseAddr(UnarySpan* uspan, void* addr)
{
  uint16_t obj_size, obj_capacity;
  uintptr_t uspan_base, addr_base, _addr, _addr_obj_size,
    _addr_bmidx, _addr_bmbit;
  uint64_t mask, old_bmap;
  a_uint64_t* bmap;
  UnarySpanQueue* uqueue;
  HugePage* hpage;

  while (!atomic_check_in(&uspan->pcard))
    ;
  uspan_base = ObtainSSpanBase(uspan);
  addr_base = (uintptr_t)addr;
  uqueue = ObtainUSpanQueue(uspan);
  hpage = ObtainHugeSpanPtr(uspan).hpage;
  bmap = (a_uint64_t*)((uintptr_t)uspan + sizeof(UnarySpan));

  _addr = addr_base - uspan_base;
  obj_size = uspan->magic.uspan_generic.obj_size;
  _addr_obj_size = _addr / obj_size;
  op_assert(_addr_obj_size >= uspan->bitmap_headroom,
            "Address %p mapped to bitmap_headroom\n", addr);
  op_assert(_addr_obj_size < uspan->bitmap_cnt * 64UL - uspan->bitmap_padding,
            "Address %p mapped to bitmap_padding\n", addr);
  _addr_bmidx = _addr_obj_size / 64;
  _addr_bmbit = _addr_obj_size % 64;
  obj_capacity = uspan->bitmap_cnt * 64L -
    uspan->bitmap_headroom - uspan->bitmap_padding;

  mask = ~(1UL << _addr_bmbit);
  old_bmap = atomic_fetch_and_explicit(&bmap[_addr_bmidx],
                                       mask, memory_order_release);
  op_assert(old_bmap & (1UL << _addr_bmbit),
            "Double free address %p\n", addr);
  if (atomic_fetch_sub_explicit(&uspan->obj_cnt, 1,
                                memory_order_acq_rel) == 1)
    {
      if (!atomic_book_critical(&uspan->pcard))
        {
          atomic_check_out(&uspan->pcard);
          return;
        }
      atomic_enter_critical(&uspan->pcard);
      if (atomic_load_explicit(&uspan->obj_cnt, memory_order_acquire) != 0)
        {
          atomic_exit_check_out(&uspan->pcard);
          return;
        }
      while (1)
        {
          if (atomic_load_explicit(&uspan->state, memory_order_acquire)
              == SPAN_DEQUEUED)
            {
              atomic_exit_check_out(&uspan->pcard);
              HPageReleaseSSpan(hpage, uspan);
              return;
            }
          if (atomic_check_in_book(&uqueue->pcard))
            break;
        }
      atomic_enter_critical(&uqueue->pcard);
      if (atomic_load_explicit(&uspan->state, memory_order_acquire)
          == SPAN_DEQUEUED)
        {
          atomic_exit_check_out(&uqueue->pcard);
          atomic_check_out(&uspan->pcard);
          HPageReleaseSSpan(hpage, uspan);
          return;
        }
      DequeueUSpan(uqueue, uspan);
      atomic_exit_check_out(&uqueue->pcard);
      HPageReleaseSSpan(hpage, uspan);
      return;
    }

  while (1)
    {
      if (atomic_load_explicit(&uspan->obj_cnt, memory_order_acquire)
          > obj_capacity / 2 ||
          atomic_load_explicit(&uspan->state, memory_order_acquire)
          == SPAN_ENQUEUED)
        {
          atomic_check_out(&uspan->pcard);
          return;
        }
      if (atomic_is_booked(&uspan->pcard))
        {
          atomic_check_out(&uspan->pcard);
          return;
        }
      if (!atomic_check_in_book(&uqueue->pcard))
        continue;
      atomic_enter_critical(&uqueue->pcard);
      if (atomic_load_explicit(&uspan->state, memory_order_acquire)
          == SPAN_ENQUEUED)
        {
          atomic_exit_check_out(&uqueue->pcard);
          atomic_check_out(&uspan->pcard);
          return;
        }
      EnqueueUSpan(uqueue, uspan);
      atomic_exit_check_out(&uqueue->pcard);
      atomic_check_out(&uspan->pcard);
      return;
    }
}

void
HPageReleaseSSpan(HugePage* hpage, SmallSpanPtr sspan)
{
  uintptr_t hpage_base, _addr, _addr_spage, _addr_bmidx, _addr_bmbit, spages,
    obj_size, bitmap_cnt, bitmap_padding;
  HugePageQueue* hqueue;
  uint64_t mask, old_bmap;
  uint64_t occupy_bmap[8], header_bmap[8];

  hpage_base = ObtainHSpanBase(hpage);
  hqueue = ObtainHPageQueue(hpage);
  HPageEmptiedBMaps(hpage, occupy_bmap, header_bmap);

  _addr = ObtainSSpanBase(sspan) - hpage_base;
  _addr_spage = _addr / SPAGE_SIZE;
  _addr_bmidx = _addr_spage / 64;
  _addr_bmbit = _addr_spage % 64;

  switch (sspan.magic->generic.pattern)
    {
    case RAW_USPAN_PATTERN:
    case LARGE_USPAN_PATTERN:
      obj_size = sspan.magic->uspan_generic.obj_size;
      if (obj_size < 16)
        obj_size = 16;
      bitmap_cnt = sspan.uspan->bitmap_cnt;
      bitmap_padding = sspan.uspan->bitmap_padding;
      spages = round_up_div(obj_size * (64 * bitmap_cnt - bitmap_padding),
                            SPAGE_SIZE);
      break;
    case SMALL_BLOB_PATTERN:
      spages = sspan.magic->small_blob.pages;
      break;
    default:
      op_assert(0, "unknown small span pattern %d",
                sspan.magic->generic.pattern);
    }

  if (_addr_bmbit + spages <= 64)
    {
      while (!atomic_check_in(&hpage->pcard))
        ;
      old_bmap = atomic_fetch_and_explicit(&hpage->header_bmap[_addr_bmidx],
                                           ~(1UL << _addr_bmbit),
                                           memory_order_release);
      op_assert((old_bmap & (1UL << _addr_bmbit)) != 0,
                "header bit didn't match");
      mask = ~(((1UL << spages) - 1) << _addr_bmbit);
      atomic_fetch_and_explicit(&hpage->occupy_bmap[_addr_bmidx],
                                mask, memory_order_release);

      if (memcmp(occupy_bmap, hpage->occupy_bmap, sizeof(occupy_bmap)) == 0)
        {
          if (!atomic_book_critical(&hpage->pcard))
            {
              atomic_check_out(&hpage->pcard);
              return;
            }
          atomic_enter_critical(&hpage->pcard);
          if (memcmp(occupy_bmap, hpage->occupy_bmap, sizeof(occupy_bmap)) != 0)
            {
              atomic_exit_check_out(&hpage->pcard);
              return;
            }
          while (1)
            {
              if (atomic_load_explicit(&hpage->state, memory_order_acquire)
                  == SPAN_DEQUEUED)
                {
                  atomic_exit_check_out(&hpage->pcard);
                  OPHeapReleaseHSpan(hpage);
                  return;
                }
              if (atomic_check_in_book(&hqueue->pcard))
                break;
            }
          atomic_enter_critical(&hqueue->pcard);
          if (atomic_load_explicit(&hpage->state, memory_order_acquire)
              == SPAN_DEQUEUED)
            {
              atomic_exit_check_out(&hqueue->pcard);
              atomic_check_out(&hpage->pcard);
              OPHeapReleaseHSpan(hpage);
              return;
            }
          DequeueHPage(hqueue, hpage);
          atomic_exit_check_out(&hqueue->pcard);
          OPHeapReleaseHSpan(hpage);
          return;
        }
      else
        {
          while (1)
            {
              if (atomic_is_booked(&hpage->pcard))
                {
                  atomic_check_out(&hpage->pcard);
                  return;
                }
              if (atomic_load_explicit(&hpage->state, memory_order_acquire)
                  == SPAN_ENQUEUED)
                {
                  atomic_check_out(&hpage->pcard);
                  return;
                }
              if (atomic_check_in_book(&hqueue->pcard))
                break;
            }
          atomic_enter_critical(&hqueue->pcard);
          if (atomic_load_explicit(&hpage->state, memory_order_acquire)
              == SPAN_ENQUEUED)
            {
              atomic_exit_check_out(&hqueue->pcard);
              atomic_check_out(&hpage->pcard);
              return;
            }
          EnqueueHPage(hqueue, hpage);
          atomic_exit_check_out(&hqueue->pcard);
          atomic_check_out(&hpage->pcard);
        }
    }
  else
    {
      while (!atomic_check_in_book(&hpage->pcard))
        ;
      atomic_enter_critical(&hpage->pcard);
      atomic_fetch_and_explicit(&hpage->header_bmap[_addr_bmidx],
                                ~(1UL << _addr_bmbit),
                                memory_order_relaxed);
      atomic_fetch_and_explicit(&hpage->occupy_bmap[_addr_bmidx],
                                (1UL << _addr_bmbit) - 1,
                                memory_order_relaxed);
      spages -= (64 - _addr_bmbit);
      _addr_bmidx++;
      while (spages >= 64)
        {
          atomic_store_explicit(&hpage->occupy_bmap[_addr_bmidx++],
                                0UL, memory_order_relaxed);
          spages -= 64;
        }
      if (spages)
        {
          atomic_fetch_and_explicit(&hpage->occupy_bmap[_addr_bmidx],
                                    ~((1UL << spages) - 1),
                                    memory_order_relaxed);
        }

      if (memcmp(occupy_bmap, hpage->occupy_bmap, sizeof(occupy_bmap)) == 0)
        {
          while (1)
            {
              if (atomic_load_explicit(&hpage->state, memory_order_acquire)
                  == SPAN_DEQUEUED)
                {
                  atomic_exit_check_out(&hpage->pcard);
                  OPHeapReleaseHSpan(hpage);
                  return;
                }
              if (atomic_check_in_book(&hqueue->pcard))
                break;
            }
          atomic_enter_critical(&hqueue->pcard);
          if (atomic_load_explicit(&hpage->state, memory_order_acquire)
              == SPAN_DEQUEUED)
            {
              atomic_exit_check_out(&hqueue->pcard);
              atomic_check_out(&hpage->pcard);
              OPHeapReleaseHSpan(hpage);
              return;
            }
          DequeueHPage(hqueue, hpage);
          atomic_exit_check_out(&hqueue->pcard);
          OPHeapReleaseHSpan(hpage);
          return;
        }
      else
        {
          while (1)
            {
              if (atomic_load_explicit(&hpage->state, memory_order_acquire)
                  == SPAN_ENQUEUED)
                {
                  atomic_exit_check_out(&hpage->pcard);
                  return;
                }
              if (atomic_check_in_book(&hqueue->pcard))
                break;
            }
          atomic_enter_critical(&hqueue->pcard);
          if (atomic_load_explicit(&hpage->state, memory_order_acquire)
              == SPAN_ENQUEUED)
            {
              atomic_exit_check_out(&hqueue->pcard);
              atomic_exit_check_out(&hpage->pcard);
              return;
            }
          EnqueueHPage(hqueue, hpage);
          atomic_exit_check_out(&hqueue->pcard);
          atomic_exit_check_out(&hpage->pcard);
        }
    }
}

void
OPHeapReleaseHSpan(HugeSpanPtr hspan)
{
  OPHeap* heap;
  uintptr_t heap_base, _addr, _addr_hpage, _addr_bmidx, _addr_bmbit, hpages;
  uint64_t mask;
  MagicPattern pattern;
  heap = ObtainOPHeap(hspan.hpage);
  heap_base = (uintptr_t)heap;

  if (&heap->hpage == hspan.hpage)
    _addr_bmidx = _addr_bmbit = 0;
  else
    {
      _addr = hspan.uintptr - heap_base;
      _addr_hpage = _addr / HPAGE_SIZE;
      _addr_bmidx = _addr_hpage / 64;
      _addr_bmbit = _addr_hpage % 64;
    }

  pattern = hspan.magic->generic.pattern;
  if (pattern == RAW_HPAGE_PATTERN ||
      hspan.magic->huge_blob.huge_pages == 1)
    {
      while (!atomic_check_in(&heap->pcard))
        ;
      atomic_fetch_and_explicit(&heap->header_bmap[_addr_bmidx],
                                ~(1UL << _addr_bmbit),
                                memory_order_relaxed);
      atomic_fetch_and_explicit(&heap->occupy_bmap[_addr_bmidx],
                                ~(1UL << _addr_bmbit),
                                memory_order_release);
      atomic_check_out(&heap->pcard);
      return;
    }
  hpages = hspan.magic->huge_blob.huge_pages;
  if (_addr_bmbit + hpages <= 64)
    {
      while (!atomic_check_in(&heap->pcard))
        ;
      mask = ~(((1UL << hpages) - 1) << _addr_bmbit);
      atomic_fetch_and_explicit(&heap->header_bmap[_addr_bmidx],
                                ~(1UL << _addr_bmbit),
                                memory_order_relaxed);
      atomic_fetch_and_explicit(&heap->occupy_bmap[_addr_bmidx],
                                mask,
                                memory_order_release);
      atomic_check_out(&heap->pcard);
      return;
    }

  while (!atomic_check_in_book(&heap->pcard))
    ;
  atomic_enter_critical(&heap->pcard);
  atomic_fetch_and_explicit(&heap->header_bmap[_addr_bmidx],
                            ~(1UL << _addr_bmbit),
                            memory_order_relaxed);
  atomic_fetch_and_explicit(&heap->occupy_bmap[_addr_bmidx],
                            (1UL << _addr_bmbit) - 1,
                            memory_order_relaxed);
  hpages -= (64 - _addr_bmbit);
  _addr_bmidx++;
  while (hpages >= 64)
    {
      atomic_store_explicit(&heap->occupy_bmap[_addr_bmidx++],
                            0UL, memory_order_relaxed);
      hpages -= 64;
    }
  if (hpages)
    {
      atomic_fetch_and_explicit(&heap->occupy_bmap[_addr_bmidx],
                                ~((1UL << hpages) - 1),
                                memory_order_relaxed);
    }
  atomic_exit_check_out(&heap->pcard);
  return;
}


/* deallocator.c ends here */
