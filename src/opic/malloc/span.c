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

#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include "span.h"
#include "opic/common/op_atomic.h"

#define round_up_div(X, Y) ((X) + (Y) - 1)/(Y)

extern void enqueue_uspan(UnarySpan** uspan_queue, UnarySpan* uspan);
extern void dequeue_uspan(UnarySpan** uspan_queue, UnarySpan* uspan);

static void select_uspan_queue(OPHeap* heap,
                               UnarySpan*** uspan_queue,
                               a_int16_t** uspan_queue_pcard);

UnarySpan* USpanInit(void* addr, Magic magic, size_t span_size)
{
  /* Unit test as of Oct 9, 2016 doesn't support op_assert
     Our workaround is return NULL instead. But this should be fixed.
  op_assert(addr, "address cannot be NULL");
  op_assert(obj_size, "object size in bytes should be greater than 0\n");
  op_assert(page_size, "allocated physical pages should be greater than 0\n");
  */
  if (op_unlikely(!magic.typed_uspan.obj_size)) return NULL;
  if (op_unlikely(!span_size)) return NULL;

  unsigned int obj_size, obj_cnt, bitmap_cnt, padding, headroom;
  uintptr_t iaddr;
  uint64_t* bmap;

  obj_size = magic.typed_uspan.obj_size;
  /* Number of objects fits into the span, regardless of header.  Note
   * this is different to the capcity of object that can stored in this
   * span.  The capacity should be calculated as
   * bitmap_cnt * 64 - headroom - padding.
   */
  obj_cnt = span_size / obj_size;
  bitmap_cnt = round_up_div(obj_cnt, 64);
  padding = (bitmap_cnt << 6) - obj_cnt;
  headroom = (sizeof(UnarySpan) + bitmap_cnt*8 + obj_size - 1)/obj_size;

  op_assert(headroom < 64,
            "headroom should be less equal to 64, but were %d\n", headroom);

  UnarySpan span =
    {
      .magic = magic,
      .bitmap_cnt = (uint8_t)bitmap_cnt,
      .bitmap_headroom = (uint8_t)headroom,
      .bitmap_padding = (uint8_t)padding,
      .bitmap_hint = 0,
      .pcard = 0,
      .obj_cnt = 0,
      .state = BM_NEW,
      .next = NULL
    };

  memcpy(addr, &span, sizeof(span));

  // Point to the first bitmap
  iaddr = (uintptr_t)addr + sizeof(UnarySpan);
  // Set all bitmap to 0
  memset((void*)iaddr, 0, bitmap_cnt << 3);
  // Mark the headroom bits
  bmap = (uint64_t*)iaddr;
  *bmap |= (1UL << headroom) - 1;

  // Mark the padding bits
  if (padding)
    {
      bmap = (uint64_t*)(iaddr + (bitmap_cnt - 1) * 8);
      *bmap |=  ~((1UL << (64-padding))-1);
    }

  atomic_thread_fence(memory_order_release);
  return (UnarySpan*) addr;
}

bool USpanMalloc(UnarySpan* self, void** addr)
{
  if (!atomic_check_in(&self->pcard))
    return false;

  BitMapState state;
  a_uint64_t *bitmap_base, *bitmap;
  uintptr_t base;
  ptrdiff_t bitmap_offset, item_offset;
  uint64_t old_bmap, new_bmap;
  uint16_t obj_size, obj_cnt, obj_capacity;
  UnarySpan** uspan_queue;
  a_int16_t* uspan_queue_pcard;

  state = atomic_load_explicit(&self->state,
                               memory_order_relaxed);

  // TODO: document the state machine.
  // When state == BM_NEW, obj_cnt can change from 0 to 1;
  // but when state is BM_NORMAL, obj_cnt == 0 is same as BM_TOMBSTONE
  if (state == BM_NORMAL &&
      atomic_load_explicit(&self->obj_cnt,
                           memory_order_relaxed) == 0)
    {
      atomic_check_out(&self->pcard);
      return false;
    }

  if (state == BM_NEW)
    atomic_store_explicit(&self->state, BM_NORMAL);

  obj_cnt = atomic_fetch_add_explicit(&self->obj_cnt, 1,
                                      memory_order_acquire);
  obj_capacity = ((uint16_t)self->bitmap_cnt)*64 -
    self->bitmap_headroom - self->bitmap_padding;

  /*
   * Say the capacity is N, and the object count is n.  When n = N, we
   * still insert the object into uspan, and since the insertion
   * succeeded, we return true.  When n > N (n > N+1 when accessed by
   * more than one thread), this uspan need to be removed from the
   * queue and allocates a new uspan to hold the object. This uspan
   * wasn't able to hold a new object, thus return false.
   *
   * Note that obj_cnt is (self->obj_cnt - 1). The logic below is
   * equivalent to
   * if (self->obj_cnt > obj_capacity) {...}
   */
  if (obj_cnt >= obj_capacity)
    {
      goto uspan_full;
    }

  base = (uintptr_t)self;
  obj_size = self->magic.typed_uspan.obj_size;
  bitmap_base = (a_uint64_t *)(base + sizeof(UnarySpan));
  bitmap_offset = (ptrdiff_t)self->bitmap_hint;
  bitmap = bitmap_base + bitmap_offset;

  while (1)
    {
      old_bmap = atomic_load_explicit(bitmap, memory_order_relaxed);
      do
        {
          if (old_bmap == ~0UL) goto next_bmap;
          new_bmap = (old_bmap + 1);
          item_offset = __builtin_ctzl(new_bmap);
          new_bmap |= old_bmap;
        }
      while(!atomic_compare_exchange_strong_explicit
            (bitmap, &old_bmap, new_bmap,
             memory_order_relaxed,
             memory_order_relaxed));
      *addr = (void*)(base + (bitmap_offset * 64 + item_offset) * obj_size);
      self->bitmap_hint = (uint8_t)bitmap_offset;
      atomic_check_out(&self->pcard);
      return true;

    next_bmap:
      bitmap_offset++;
      bitmap_offset %= self->bitmap_cnt;
      bitmap = bitmap_base + bitmap_offset;
    }

 uspan_full:
  /* If we couldn't book, there were some other thread booked the critical
     section.  Retry and start over again. */
  if (!atomic_book_critical(&self->pcard))
    {
      atomic_fetch_sub_explicit(&self->obj_cnt, 1, memory_order_relaxed);
      atomic_check_out(&self->pcard);
      return false;
    }
  atomic_enter_critical(&self->pcard);

  atomic_store_explicit(&self->state, BM_FULL, memory_order_relaxed);
  atomic_fetch_sub_explicit(&self->obj_cnt, 1, memory_order_relaxed);

  select_uspan_queue(get_opheap(self), &uspan_queue, &uspan_queue_pcard);
  atomic_check_out(uspan_queue_pcard);
  // Need to check out then check in to avoid dead lock.
  while (1)
    {
      if (!atomic_check_in(uspan_queue_pcard))
        continue;
      if (atomic_book_critical(uspan_queue_pcard))
        break;
      atomic_check_out(uspan_queue_pcard);
    }
  atomic_enter_critical(uspan_queue_pcard);
  dequeue_uspan(uspan_queue, self);
  atomic_exit_critical(uspan_queue_pcard);
  // do not checkout uspan_queue, the caller will do
  atomic_check_out(&self->pcard);
  return false;
}

BitMapState USpanFree(UnarySpan* self, void* addr)
{
  uintptr_t base, iaddr, bound;
  int obj_size, addr_idx, bmap_idx, item_idx;
  a_uint64_t* bitmap;
  OPHeap* heap;
  uint16_t obj_cnt;
  BitMapState state;
  UnarySpan** uspan_queue;
  a_int16_t* uspan_queue_pcard;

  // Locate the bitmap and item index, and validate its correctness
  base = (uintptr_t)self;
  iaddr = (uintptr_t)addr;
  obj_size = self->magic.uspan_generic->obj_size;
  bound = base + obj_size * (64 * self->bitmap_cnt - self->bitmap_padding);
  bitmap = (a_uint64_t *)(base + sizeof(UnarySpan));
  addr_idx = (iaddr - base) / obj_size;
  bmap_idx = addr_idx / 64;
  item_idx = addr_idx - bmap_idx * 64;
  heap = get_opheap(self);

  op_assert(iaddr > base && iaddr < bound,
            "Free address %p should within span from %p and %p",
            addr, (void*)base, (void*)bound);

  op_assert(addr_idx * obj_size + base == iaddr,
            "Free address %p should align with obj_size %d\n",
            addr, obj_size);

  if (bmap_idx == 0)
    {
      op_assert(item_idx >= self->bitmap_headroom,
                "Free address %p cannot overlap span %p headroom\n",
                addr, self);
    }

 retry:
  if (!atomic_check_in(&self->pcard))
    goto retry;

  state = atomic_load_explicit(&self->state, memory_order_acquire);
  if (state == BM_NORMAL)
    goto free_bm_normal;

  // free on full state
  op_assert(state == BM_FULL,
            "free should not operate on BM_NEW or BM_TOMEBSTONE\n");
  if (!atomic_book_critical(&self->pcard))
    {
      atomic_check_out(&self->pcard);
      goto retry;
    }
  atomic_enter_critical(&self->pcard);

  atomic_fetch_sub_explicit(&self->obj_cnt, 1, memory_order_relaxed);
  atomic_store_explicit(&self->state, BM_NORMAL, memory_order_relaxed);
  atomic_fetch_and_explicit(&bitmap[bmap_idx],
                            ~(1UL << item_idx),
                            memory_order_relaxed);

  select_uspan_queue(heap, &uspan_queue, &uspan_queue_pcard);
  while (1)
    {
      if (!atomic_check_in(uspan_queue_pcard))
        continue;
      if (atomic_book_critical(uspan_queue_pcard))
        break;
      atomic_check_out(uspan_queue_pcard);
    }
  atomic_enter_critical(uspan_queue_pcard);
  enqueue_uspan(uspan_queue, self);
  atomic_exit_critical(&self->pcard);
  atomic_check_out(uspan_queue_pcard);
  atomic_check_out(&self->pcard);
  return BM_NORMAL;

 free_bm_normal:

  obj_cnt = atomic_fetch_sub_explicit(&self->obj_cnt, 1,
                                      memory_order_acq_rel);
  atomic_fetch_and_explicit(&bitmap[bmap_idx],
                            ~(1UL << item_idx),
                            memory_order_relaxed);
  // Normal case
  if (obj_cnt > 1)
    {
      atomic_check_out(&self->pcard);
      return BM_NORMAL;
    }

  // Bury uspan
  op_assert(atomic_book_critical(&self->pcard),
            "only one thread can book critical to bury uspan");
  atomic_enter_critical(&self->pcard);
  atomic_store_explicit(&self->state, BM_TOMBSTONE, memory_order_relaxed);

  select_uspan_queue(heap, &uspan_queue, &uspan_queue_pcard);
  while (1)
    {
      if (!atomic_check_in(uspan_queue_pcard))
        continue;
      if (atomic_book_critical(uspan_queue_pcard))
        break;
      atomic_check_out(uspan_queue_pcard);
    }
  atomic_enter_critical(uspan_queue_pcard);
  dequeue_uspan(uspan_queue, self);
  atomic_exit_critical(uspan_queue_pcard);
  atomic_check_out(uspan_queue_pcard);
  atomic_check_out(&self->pcard);
  return BM_TOMBSTONE;
}

static inline void select_uspan_queue(OPHeap* heap,
                                      UnarySpan*** uspan_queue,
                                      a_int16_t** uspan_queue_pcard)
{
  switch (self->magic.uspan_generic.pattern)
    {
    case TYPED_USPAN_PATTERN:
      {
        TypeAlias* ta = &heap->type_alias[self->magic.typed_uspan.type_alias];
        int tid = self->magic.typed_uspan.thread_id;
        &uspan_queue_pcard = &ta->uspan_pcard[tid];
        &uspan_queue = &ta->uspan[tid];
        break;
      }
    case RAW_USPAN_PATTERN:
      {
        uint16_t size_class = self->magic.raw_uspan.obj_size / 16;
        int tid = self->magic.raw_uspan.thread_id;
        &uspan_queue_pcard = &heap->raw_type.uspan_pcard[size_class][tid];
        &uspan_queue = &heap->raw_type.uspan[size_class][tid];
        break;
      }
    case LARGE_USPAN_PATTERN:
      {
        uint16_t obj_size = self->magic.large_uspan.obj_size;
        int uid =
          obj_size == 512 ? 0 :
          obj_size == 1024 ? 1 : 2;
        &uspan_queue_pcard = &heap->raw_type.large_uspan_pcard[uid];
        &uspan_queue = &heap->raw_type.large_uspan[uid];
        break;
      }
    }
}

/* op_pspan.c ends here */
