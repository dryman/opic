/* allocator.c ---
 *
 * Filename: allocator.c
 * Description:
 * Author: Felix Chern
 * Maintainer:
 * Copyright: (c) 2016-2017 Felix Chern
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

#include <string.h>
#include "opic/common/op_atomic.h"
#include "opic/common/op_log.h"
#include "opic/common/op_utils.h"
#include "allocator.h"
#include "init_helper.h"
#include "lookup_helper.h"

OP_LOGGER_FACTORY(logger, "opic.malloc.allocator");

static bool
OPHeapObtainSmallHBlob(OPHeap* heap, OPHeapCtx* ctx, unsigned int hpage_cnt);
static bool
OPHeapObtainLargeHBlob(OPHeap* heap, OPHeapCtx* ctx, unsigned int hpage_cnt);

bool
OPHeapObtainHPage(OPHeap* heap, OPHeapCtx* ctx)
{
  int hpage_bmidx, hpage_bmbit, cmp_result;
  uint64_t old_bmap, new_bmap;
  uintptr_t heap_base;

  uint64_t empty_occupy_bmap[HPAGE_BMAP_NUM];

  heap_base = (uintptr_t)heap;

 retry:
  while (!atomic_check_in(&heap->pcard))
    ;

  for (hpage_bmidx = 0; hpage_bmidx < HPAGE_BMAP_NUM; hpage_bmidx++)
    {
      old_bmap = atomic_load_explicit(&heap->occupy_bmap[hpage_bmidx],
                                      memory_order_relaxed);
      while (1)
        {
          if (old_bmap == ~0UL) break;
          new_bmap = old_bmap + 1;
          hpage_bmbit = __builtin_ctzl(new_bmap);
          new_bmap |= old_bmap;

          if (atomic_compare_exchange_weak_explicit
              (&heap->occupy_bmap[hpage_bmidx], &old_bmap, new_bmap,
               memory_order_acquire,
               memory_order_relaxed))
            {
              atomic_fetch_or_explicit(&heap->header_bmap[hpage_bmidx],
                                       1UL << hpage_bmbit,
                                       memory_order_relaxed);
              atomic_check_out(&heap->pcard);

              if (hpage_bmidx == 0 && hpage_bmbit == 0)
                ctx->hspan.hpage = &heap->hpage;
              else
                ctx->hspan.uintptr = heap_base +
                  (64 * hpage_bmidx + hpage_bmbit) * HPAGE_SIZE;
              return true;
            }
        }
    }

  OP_LOG_WARN(logger,
              "Running out of available hpages. Lock to check remaining");

  if (!atomic_book_critical(&heap->pcard))
    {
      atomic_check_out(&heap->pcard);
      goto retry;
    }

  atomic_enter_critical(&heap->pcard);
  memset(empty_occupy_bmap, 0xFF, sizeof(empty_occupy_bmap));
  cmp_result = memcmp(heap->occupy_bmap, empty_occupy_bmap,
                      sizeof(empty_occupy_bmap));
  atomic_exit_check_out(&heap->pcard);

  if (cmp_result)
    goto retry;

  OP_LOG_ERROR(logger, "No available hpage.");
  return false;
}

bool
OPHeapObtainHBlob(OPHeap* heap, OPHeapCtx* ctx, unsigned int hpage_cnt)
{
  bool result;

  if (hpage_cnt <= 32)
    return OPHeapObtainSmallHBlob(heap, ctx, hpage_cnt);

  while (!atomic_check_in_book(&heap->pcard))
    ;
  result = OPHeapObtainLargeHBlob(heap, ctx, hpage_cnt);
  atomic_exit_check_out(&heap->pcard);
  return result;
}

static bool
OPHeapObtainSmallHBlob(OPHeap* heap, OPHeapCtx* ctx, unsigned int hpage_cnt)
{
  int hblob_bmidx, hblob_bmbit;
  uint64_t old_bmap, new_bmap;
  uintptr_t heap_base;
  bool result;

  heap_base = (uintptr_t)heap;

 retry:
  while (!atomic_check_in(&heap->pcard))
    ;

  for (hblob_bmidx = 0; hblob_bmidx < HPAGE_BMAP_NUM; hblob_bmidx++)
    {
      old_bmap = atomic_load_explicit(&heap->occupy_bmap[hblob_bmidx],
                                      memory_order_relaxed);
      while (1)
        {
          if (old_bmap == ~0UL) break;
          new_bmap = hblob_bmidx == 0 ? old_bmap | 0x01 : old_bmap;
          hblob_bmbit = fftstr0l(new_bmap, hpage_cnt);
          if (hblob_bmbit == -1) break;
          new_bmap = old_bmap | ((1UL<< hpage_cnt) - 1) << hblob_bmbit;

          if (atomic_compare_exchange_weak_explicit
              (&heap->occupy_bmap[hblob_bmidx], &old_bmap, new_bmap,
               memory_order_acquire,
               memory_order_relaxed))
            {
              atomic_fetch_or_explicit(&heap->header_bmap[hblob_bmidx],
                                       1UL << hblob_bmbit,
                                       memory_order_relaxed);
              atomic_check_out(&heap->pcard);
              ctx->hspan.uintptr = heap_base +
                (64 * hblob_bmidx + hblob_bmbit) * HPAGE_SIZE;
              return true;
            }
        }
    }

  OP_LOG_WARN(logger,
              "Running out of available hpages. Lock to check remaining");

  if (!atomic_book_critical(&heap->pcard))
    {
      atomic_check_out(&heap->pcard);
      goto retry;
    }

  atomic_enter_critical(&heap->pcard);
  result = OPHeapObtainLargeHBlob(heap, ctx, hpage_cnt);
  atomic_exit_check_out(&heap->pcard);
  return result;
}

static bool
OPHeapObtainLargeHBlob(OPHeap* heap, OPHeapCtx* ctx, unsigned int hpage_cnt)
{
  int bmidx_head, bmidx_iter, _hpage_cnt, bmbit_head;
  uintptr_t heap_base;
  uint64_t* occupy_bmap;

  heap_base = (uintptr_t)heap;
  occupy_bmap = (uint64_t*)(heap->occupy_bmap);
  bmidx_head = 0;

  while (1)
    {
      if (bmidx_head > HPAGE_BMAP_NUM) goto fail;
      if (occupy_bmap[bmidx_head] && 1UL << 63)
        {
          bmidx_head++;
          continue;
        }
      _hpage_cnt = hpage_cnt;
      bmidx_iter = bmidx_head;
      bmbit_head = occupy_bmap[bmidx_head] == 0 ?
        0 : 64 - __builtin_clzl(occupy_bmap[bmidx_head]);
      if (bmidx_head == 0 && bmbit_head == 0)
        bmbit_head = 1;
      if (_hpage_cnt <= 64 - bmbit_head)
        goto found;

      while (1)
        {
          if (bmidx_iter > HPAGE_BMAP_NUM)
            goto fail;
          if (_hpage_cnt > 64)
            {
              if (occupy_bmap[bmidx_iter] != 0UL)
                {
                  bmidx_head++;
                  break;
                }
              bmidx_iter++;
              _hpage_cnt -= 64;
              continue;
            }
          else if (_hpage_cnt == 64)
            {
              bmidx_iter++;
              _hpage_cnt -= 64;
              goto found;
            }
          else if (_hpage_cnt < __builtin_ctzl(occupy_bmap[bmidx_iter]))
            {
              goto found;
            }
          bmidx_head++;
          break;
        }
    }
 found:
  ctx->hspan.uintptr = heap_base +
    (64 * bmidx_head + bmbit_head) * HPAGE_SIZE;
  heap->header_bmap[bmidx_head] |= 1UL << bmbit_head;
  if (bmidx_iter == 0)
    {
      occupy_bmap[0] = ((1UL << _hpage_cnt) - 1) << bmbit_head;
    }
  else
    {
      occupy_bmap[bmidx_head] |=
        ~((1UL << bmbit_head) - 1) &
        ~(1UL << bmbit_head);
      occupy_bmap[bmidx_iter] |= (1UL << _hpage_cnt) - 1;
      for (int bmidx = bmidx_head + 1; bmidx < bmidx_iter; bmidx++)
        occupy_bmap[bmidx] = ~0UL;
    }
  return true;

 fail:
  OP_LOG_ERROR(logger,
               "No available contiguous hpages for huge page count %d",
               hpage_cnt);
  return false;
}
/*

extern void enqueue_uspan(UnarySpan** uspan_queue, UnarySpan* uspan);
extern void dequeue_uspan(UnarySpan** uspan_queue, UnarySpan* uspan);

static void select_uspan_queue(uint8_t pattern,
                               OPHeap* heap,
                               UnarySpan*** uspan_queue,
                               a_int16_t** uspan_queue_pcard);

void USpanInit(UnarySpan* self, Magic magic, size_t span_size)
{
  op_assert(magic.uspan_generic.obj_size, "uspan object size cannot be 0\n");
  op_assert(span_size, "span_size must greater than 0\n");

  unsigned int obj_size, obj_cnt, bitmap_cnt, padding, headroom;
  uintptr_t bitmap_base;
  uint64_t* bmap;

  obj_size = magic.typed_uspan.obj_size;
  // Number of objects fits into the span, regardless of header.  Note
  // this is different to the capcity of object that can stored in this
  // span.  The capacity should be calculated as
  // bitmap_cnt * 64 - headroom - padding.
  ///
  obj_cnt = span_size / obj_size;
  bitmap_cnt = round_up_div(obj_cnt, 64);
  padding = (bitmap_cnt << 6) - obj_cnt;
  headroom = (sizeof(UnarySpan) + bitmap_cnt*8 + obj_size - 1)/obj_size;

  op_assert(headroom < 64,
            "headroom should be less equal to 64, but were %d\n", headroom);

  self->magic = magic;
  self->bitmap_cnt = bitmap_cnt;
  self->bitmap_headroom = headroom;
  self->bitmap_padding = padding;
  self->bitmap_hint = 0;
  self->pcard = 0;
  self->obj_cnt = 0;
  self->state = BM_NEW;
  self->struct_padding = 0;
  self->next = NULL;

  bitmap_base = (uintptr_t)self + sizeof(UnarySpan);
  // Set all bitmap to 0
  memset((void*)bitmap_base, 0, bitmap_cnt << 3);
  // Mark the headroom bits
  bmap = (uint64_t*)bitmap_base;
  *bmap |= (1UL << headroom) - 1;

  // Mark the padding bits
  if (padding)
    {
      bmap = (uint64_t*)(bitmap_base + (bitmap_cnt - 1) * 8);
      *bmap |=  ~((1UL << (64-padding))-1);
    }
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

  //
  // Say the capacity is N, and the object count is n.  When n = N, we
  // still insert the object into uspan, and since the insertion
  // succeeded, we return true.  When n > N (n > N+1 when accessed by
  // more than one thread), this uspan need to be removed from the
  // queue and allocates a new uspan to hold the object. This uspan
  // wasn't able to hold a new object, thus return false.
  //
  // Note that obj_cnt is (self->obj_cnt - 1). The logic below is
  // equivalent to
  // if (self->obj_cnt > obj_capacity) {...}
  ///
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
  // If we couldn't book, there were some other thread booked the critical
  // section.  Retry and start over again.
  if (!atomic_book_critical(&self->pcard))
    {
      atomic_fetch_sub_explicit(&self->obj_cnt, 1, memory_order_relaxed);
      atomic_check_out(&self->pcard);
      return false;
    }
  atomic_enter_critical(&self->pcard);

  atomic_store_explicit(&self->state, BM_FULL, memory_order_relaxed);
  atomic_fetch_sub_explicit(&self->obj_cnt, 1, memory_order_relaxed);

  select_uspan_queue(self->magic.uspan_generic.pattern,
                     get_opheap(self), &uspan_queue, &uspan_queue_pcard);
  if (!atomic_book_critical(uspan_queue_pcard))
    {
      atomic_exit_critical(&self->pcard);
      atomic_check_out(&self->pcard);
      return false;
    }
  atomic_enter_critical(uspan_queue_pcard);
  dequeue_uspan(uspan_queue, self);
  atomic_exit_critical(uspan_queue_pcard);
  atomic_exit_critical(&self->pcard);
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

  atomic_fetch_and_explicit(&bitmap[bmap_idx],
                            ~(1UL << item_idx),
                            memory_order_relaxed);
  atomic_fetch_sub_explicit(&self->obj_cnt, 1, memory_order_relaxed);

  while (atomic_load_explicit(&self->state, memory_order_acquire) == BM_FULL)
    {
      if (!atomic_check_in_book(&self->pcard))
        continue;
      atomic_enter_critical(&self->pcard);
      select_uspan_queue(self->magic.uspan_generic.pattern,
                         heap, &uspan_queue, &uspan_queue_pcard);
      if (!atomic_check_in_book(uspan_queue_pcard))
        {
          atomic_exit_critical(&self->pcard);
          atomic_check_out(&self->pcard);
          continue;
        }
      atomic_enter_critical(uspan_queue_pcard);
      enqueue_uspan(uspan_queue, self);
      atomic_store_explicit(&self->state, BM_NORMAL, memory_order_relaxed);
      atomic_exit_critical(&self->pcard);
      atomic_check_out(uspan_queue_pcard);
      atomic_check_out(&self->pcard);
      return BM_NORMAL;
    }


  if (atomic_load_explicit(&self->obj_cnt) != 0)
    return BM_NORMAL;
  if (!atomic_check_in_book(&self->pcard))
    return BM_NORMAL;
  atomic_enter_critical(&self->pcard);
  if (atomic_load_explicit(&self->obj_cnt) != 0)
    {
      atomic_exit_critical(&self->pcard);
      atomic_check_out(&self->pcard);
      return BM_NORMAL;
    }
  select_uspan_queue(self->magic.uspan_generic.pattern,
                     heap, &uspan_queue, &uspan_queue_pcard);
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
  // TODO why not delete the span here?
  atomic_exit_critical(&self->pcard);
  atomic_check_out(&self->pcard);
  return BM_TOMBSTONE;
}

static inline void select_uspan_queue(uint8_t pattern,
                                      OPHeap* heap,
                                      UnarySpan*** uspan_queue,
                                      a_int16_t** uspan_queue_pcard)
{
  switch (pattern)
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

*/

/* op_pspan.c ends here */
