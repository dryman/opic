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
#include "opic/common/op_assert.h"
#include "opic/common/op_atomic.h"
#include "opic/common/op_log.h"
#include "opic/common/op_utils.h"
#include "allocator.h"
#include "init_helper.h"
#include "lookup_helper.h"

#define DISPATCH_ATTEMPT 1024


static __thread int thread_id = -1;
static a_uint32_t round_robin = 0;

void*
OPMallocRaw(OPHeap* heap, size_t size)
{
  if (thread_id == -1)
    thread_id = atomic_fetch_add_explicit
      (&round_robin, 1, memory_order_acquire) % 16;

  return OPMallocRawAdviced(heap, size, thread_id);
}

void*
OPCallocRaw(OPHeap* heap, size_t size)
{
  if (thread_id == -1)
    thread_id = atomic_fetch_add_explicit
      (&round_robin, 1, memory_order_acquire) % 16;

  return OPCallocRawAdviced(heap, size, thread_id);
}

void*
OPMallocRawAdviced(OPHeap* heap, size_t size, int advice)
{
  OPHeapCtx ctx;
  void* addr;
  Magic magic;
  unsigned int size_class, page_cnt;

  op_assert(size > 0, "malloc size must greater than 0");

  advice %= 16;

  ctx.hqueue = &heap->raw_type.hpage_queue;
  if (size <= 256)
    {
      size_class = round_up_div(size, 16);
      magic.raw_uspan.pattern = RAW_USPAN_PATTERN;
      magic.raw_uspan.obj_size = size_class * 16;
      magic.raw_uspan.thread_id = advice;
      ctx.uqueue = &heap->raw_type.uspan_queue[size_class][advice];
      if (DispatchUSpanForAddr(&ctx, magic, &addr))
        return addr;
      else
        return NULL;
    }
  else if (size <= 2048)
    {
      magic.large_uspan.pattern = LARGE_USPAN_PATTERN;
      if (size <= 512)
        {
          ctx.uqueue = &heap->raw_type.large_uspan_queue[0];
          magic.large_uspan.obj_size = 512;
        }
      else if (size <= 1024)
        {
          ctx.uqueue = &heap->raw_type.large_uspan_queue[1];
          magic.large_uspan.obj_size = 1024;
        }
      else
        {
          ctx.uqueue = &heap->raw_type.large_uspan_queue[2];
          magic.large_uspan.obj_size = 2048;
        }
      if (DispatchUSpanForAddr(&ctx, magic, &addr))
        return addr;
      else
        return NULL;
    }
  else if (size <= HPAGE_SIZE - SPAGE_SIZE)
    {
      page_cnt = round_up_div(size + sizeof(Magic), SPAGE_SIZE);
      magic.raw_hpage.pattern = RAW_HPAGE_PATTERN;
      if (!DispatchHPageForSSpan(&ctx, magic, page_cnt, true))
        return NULL;
      ctx.sspan.magic->int_value = 0;
      ctx.sspan.magic->small_blob.pattern = SMALL_BLOB_PATTERN;
      ctx.sspan.magic->small_blob.pages = page_cnt;
      addr = (void*)(ctx.sspan.uintptr + sizeof(Magic));
      return addr;
    }
  else
    {
      page_cnt = round_up_div(size + sizeof(Magic), HPAGE_SIZE);
      if (!OPHeapObtainHBlob(heap, &ctx, page_cnt))
        return NULL;
      ctx.hspan.magic->int_value = 0;
      ctx.hspan.magic->huge_blob.pattern = HUGE_BLOB_PATTERN;
      ctx.hspan.magic->huge_blob.huge_pages = page_cnt;
      addr = (void*)(ctx.hspan.uintptr + sizeof(Magic));
      return addr;
    }
}

void*
OPCallocRawAdviced(OPHeap* heap, size_t size, int advice)
{
  void* addr;

  addr = OPMallocRawAdviced(heap, size, thread_id);
  if (addr)
    memset(addr, 0x00, size);

  return addr;
}

bool
DispatchUSpanForAddr(OPHeapCtx* ctx, Magic uspan_magic, void** addr)
{
  unsigned int spage_cnt;
  Magic hpage_magic = {};
  int attempt;
  attempt = 0;

 retry:
  if (attempt++ > DISPATCH_ATTEMPT)
    return false;
  while (!atomic_check_in(&ctx->uqueue->pcard))
    ;

  UnarySpan** it = &ctx->uqueue->uspan;
  while (*it)
    {
      switch(USpanObtainAddr(ctx, addr))
        {
        case QOP_SUCCESS:
          atomic_check_out(&ctx->uqueue->pcard);
          return true;
        case QOP_RESTART:
          atomic_check_out(&ctx->uqueue->pcard);
          goto retry;
        case QOP_CONTINUE:
          *it = (*it)->next;
        }
    }
  if (!atomic_book_critical(&ctx->uqueue->pcard))
    {
      atomic_check_out(&ctx->uqueue->pcard);
      goto retry;
    }
  atomic_enter_critical(&ctx->uqueue->pcard);

  switch (uspan_magic.generic.pattern)
    {
    case TYPED_USPAN_PATTERN:
      hpage_magic.typed_hpage.pattern = TYPED_HPAGE_PATTERN;
      hpage_magic.typed_hpage.type_alias = uspan_magic.typed_uspan.type_alias;
      break;
    case RAW_USPAN_PATTERN:
    case LARGE_USPAN_PATTERN:
      hpage_magic.raw_hpage.pattern = RAW_HPAGE_PATTERN;
      break;
    default:
      op_assert(false, "Unknown uspan pattern %d", uspan_magic.generic.pattern);
    }
  if (uspan_magic.uspan_generic.obj_size <= 32)
    spage_cnt = 1;
  else if (uspan_magic.uspan_generic.obj_size <= 64)
    spage_cnt = 4;
  else if (uspan_magic.uspan_generic.obj_size <= 256)
    spage_cnt = 8;
  else if (uspan_magic.uspan_generic.obj_size < 1024)
    spage_cnt = 16;
  else
    spage_cnt = 32;
  if (!DispatchHPageForSSpan(ctx, hpage_magic, spage_cnt, false))
    {
      atomic_exit_check_out(&ctx->uqueue->pcard);
      return false;
    }
  USpanInit(ctx->sspan.uspan, uspan_magic, spage_cnt);
  EnqueueUSpan(ctx->uqueue, ctx->sspan.uspan);
  atomic_exit_check_out(&ctx->uqueue->pcard);
  goto retry;
}

bool
DispatchHPageForSSpan(OPHeapCtx* ctx, Magic magic, unsigned int spage_cnt,
                      bool use_full_span)
{
  int attempt;
  attempt = 0;
 retry:
  if (attempt++ > DISPATCH_ATTEMPT)
    return false;
  while (!atomic_check_in(&ctx->hqueue->pcard))
    ;

  HugePage** it = &ctx->hqueue->hpage;
  while (*it)
    {
      switch(HPageObtainSSpan(ctx, spage_cnt, use_full_span))
        {
        case QOP_SUCCESS:
          atomic_check_out(&ctx->hqueue->pcard);
          return true;
        case QOP_RESTART:
          atomic_check_out(&ctx->hqueue->pcard);
          goto retry;
        case QOP_CONTINUE:
          *it = (*it)->next;
        }
    }
  if (!atomic_book_critical(&ctx->hqueue->pcard))
    {
      atomic_check_out(&ctx->hqueue->pcard);
      goto retry;
    }
  atomic_enter_critical(&ctx->hqueue->pcard);
  if (!OPHeapObtainHPage(ObtainOPHeap(ctx->hqueue), ctx))
    {
      atomic_exit_check_out(&ctx->hqueue->pcard);
      return false;
    }
  HPageInit(ctx->hspan.hpage, magic);
  EnqueueHPage(ctx->hqueue, ctx->hspan.hpage);
  atomic_exit_check_out(&ctx->hqueue->pcard);
  goto retry;
}

QueueOperation
USpanObtainAddr(OPHeapCtx* ctx, void** addr)
{
  UnarySpan* uspan;
  uintptr_t uspan_base;
  uint64_t old_bmap, new_bmap;
  uint16_t obj_size, obj_cnt_old, obj_cnt_new, obj_capacity;
  a_uint64_t *bmap;
  uint64_t bmidx, bmbit;

  uspan = ctx->sspan.uspan;
  uspan_base = ObtainSSpanBase(uspan);

  if (!atomic_check_in(&uspan->pcard))
    return QOP_CONTINUE;

  obj_capacity = uspan->bitmap_cnt * 64 -
    uspan->bitmap_headroom - uspan->bitmap_padding;
  obj_cnt_old = atomic_load_explicit(&uspan->obj_cnt,
                                     memory_order_relaxed);
  do
    {
      if (obj_cnt_old >= obj_capacity)
        goto uspan_full;
      obj_cnt_new = obj_cnt_old + 1;
    }
  while (!atomic_compare_exchange_weak_explicit
         (&uspan->obj_cnt, &obj_cnt_old, obj_cnt_new,
          memory_order_acq_rel,
          memory_order_relaxed));

  obj_size = uspan->magic.typed_uspan.obj_size < 16 ?
    16 : uspan->magic.typed_uspan.obj_size;
  bmap = (a_uint64_t *)((uintptr_t)uspan + sizeof(UnarySpan));
  bmidx = uspan->bitmap_hint;

  while (1)
    {
      old_bmap = atomic_load_explicit(&bmap[bmidx], memory_order_relaxed);
      do
        {
          if (old_bmap == ~0UL) goto next_bmap;
          new_bmap = (old_bmap + 1);
          bmbit = __builtin_ctzl(new_bmap);
          new_bmap |= old_bmap;
        }
      while(!atomic_compare_exchange_strong_explicit
            (&bmap[bmidx], &old_bmap, new_bmap,
             memory_order_relaxed,
             memory_order_relaxed));
      *addr = (void*)(uspan_base + (bmidx * 64UL + bmbit) * obj_size);
      uspan->bitmap_hint = bmidx;
      atomic_check_out(&uspan->pcard);
      return QOP_SUCCESS;

    next_bmap:
      bmidx++;
      bmidx %= uspan->bitmap_cnt;
    }

 uspan_full:
  if (atomic_load_explicit(&uspan->state,
                           memory_order_acquire) == SPAN_DEQUEUED)
    {
      atomic_check_out(&uspan->pcard);
      return QOP_RESTART;
    }
  if (!atomic_book_critical(&ctx->uqueue->pcard))
    {
      atomic_check_out(&uspan->pcard);
      return QOP_RESTART;
    }
  atomic_enter_critical(&ctx->uqueue->pcard);
  DequeueUSpan(ctx->uqueue, uspan);
  atomic_exit_critical(&ctx->uqueue->pcard);
  atomic_check_out(&uspan->pcard);
  return QOP_RESTART;
}

QueueOperation
HPageObtainSSpan(OPHeapCtx* ctx, unsigned int spage_cnt, bool use_full_span)
{
  HugePage* hpage;
  uintptr_t hpage_base;
  int sspan_bmidx, sspan_bmbit, bmidx, _spage_cnt;
  uint64_t* occupy_bmap;

  if (spage_cnt <= 32)
    return HPageObtainUSpan(ctx, spage_cnt, use_full_span);

  hpage = ctx->hspan.hpage;
  hpage_base = ObtainHSpanBase(hpage);

  if (!atomic_check_in_book(&hpage->pcard))
    return QOP_CONTINUE;
  atomic_enter_critical(&hpage->pcard);

  occupy_bmap = (uint64_t*)(hpage->occupy_bmap);
  sspan_bmidx = 0;

  while (1)
    {
      if (sspan_bmidx >= 8)
        goto check_full;
      if (occupy_bmap[sspan_bmidx] & (1UL << 63))
        {
          sspan_bmidx++;
          continue;
        }
      _spage_cnt = spage_cnt;
      bmidx = sspan_bmidx;
      sspan_bmbit = occupy_bmap[sspan_bmidx] == 0 ?
        0 : 64 - __builtin_clzl(occupy_bmap[sspan_bmidx]);
      if (use_full_span && sspan_bmidx == 0 && sspan_bmbit == 0)
        sspan_bmbit = 1;
      if (_spage_cnt <= 64 - sspan_bmbit)
        goto found;

      _spage_cnt -= 64 - sspan_bmbit;
      bmidx++;

      while (1)
        {
          if (bmidx >= 8)
            goto check_full;
          if (_spage_cnt > 64)
            {
              if (occupy_bmap[bmidx] != 0UL)
                {
                  sspan_bmidx++;
                  break;
                }
              bmidx++;
              _spage_cnt -= 64;
              continue;
            }
          else if (_spage_cnt == 64)
            {
              bmidx++;
              _spage_cnt -= 64;
              goto found;
            }
          else if (_spage_cnt < (occupy_bmap[bmidx] == 0 ?
                                 64 : __builtin_ctzl(occupy_bmap[bmidx])))
            {
              goto found;
            }
          sspan_bmidx++;
          break;
        }
    }

 found:
  ctx->sspan.uintptr = hpage_base +
    (64 * sspan_bmidx + sspan_bmbit) * SPAGE_SIZE;
  if (sspan_bmidx == 0 && sspan_bmbit == 0)
    ctx->sspan.uintptr += sizeof(HugePage);
  hpage->header_bmap[sspan_bmidx] |= 1UL << sspan_bmbit;
  if (bmidx == sspan_bmidx)
    {
      occupy_bmap[sspan_bmidx] = ((1UL << _spage_cnt) - 1) << sspan_bmbit;
    }
  else
    {
      occupy_bmap[sspan_bmidx] |=
        ~((1UL << sspan_bmbit) - 1) | (1UL << sspan_bmbit);
      if (_spage_cnt)
        occupy_bmap[bmidx] |= (1UL << _spage_cnt) - 1;
      for (int idx = sspan_bmidx + 1; idx < bmidx; idx++)
        occupy_bmap[idx] = ~0UL;
    }

  atomic_exit_check_out(&hpage->pcard);
  return QOP_SUCCESS;

 check_full:
  for (int idx = 0; idx < 8; idx++)
    {
      if (occupy_bmap[idx] != ~0UL)
        {
          atomic_exit_check_out(&hpage->pcard);
          return QOP_CONTINUE;
        }
    }
  while (1)
    {
      if (atomic_load_explicit(&hpage->state, memory_order_acquire)
          == SPAN_DEQUEUED)
        {
          atomic_exit_check_out(&hpage->pcard);
          return QOP_RESTART;
        }
      if (atomic_book_critical(&ctx->hqueue->pcard))
        break;
    }
  atomic_enter_critical(&ctx->hqueue->pcard);
  if (atomic_load_explicit(&hpage->state, memory_order_acquire)
      == SPAN_DEQUEUED)
    {
      atomic_exit_critical(&ctx->hqueue->pcard);
      atomic_exit_check_out(&hpage->pcard);
      return QOP_RESTART;
    }
  DequeueHPage(ctx->hqueue, hpage);
  atomic_exit_critical(&ctx->hqueue->pcard);
  atomic_exit_check_out(&hpage->pcard);
  return QOP_RESTART;
}

QueueOperation
HPageObtainUSpan(OPHeapCtx* ctx, unsigned int spage_cnt, bool use_full_span)
{
  HugePage* hpage;
  uintptr_t hpage_base;
  int sspan_bmidx, sspan_bmbit;
  uint64_t old_bmap, new_bmap;

  hpage = ctx->hspan.hpage;
  hpage_base = ObtainHSpanBase(hpage);

  if (!atomic_check_in(&hpage->pcard))
    return QOP_CONTINUE;
  for (sspan_bmidx = 0; sspan_bmidx < 8; sspan_bmidx++)
    {
      old_bmap = atomic_load_explicit(&hpage->occupy_bmap[sspan_bmidx],
                                      memory_order_relaxed);
      while (1)
        {
          if (old_bmap == ~0UL) break;
          new_bmap = sspan_bmidx == 0 && use_full_span ?
            old_bmap | 0x01 : old_bmap;
          sspan_bmbit = fftstr0l(new_bmap, spage_cnt);
          if (sspan_bmbit == -1) break;
          new_bmap = old_bmap | ((1UL<< spage_cnt) - 1) << sspan_bmbit;

          if (atomic_compare_exchange_weak_explicit
              (&hpage->occupy_bmap[sspan_bmidx], &old_bmap, new_bmap,
               memory_order_acquire,
               memory_order_relaxed))
            {
              atomic_fetch_or_explicit(&hpage->header_bmap[sspan_bmidx],
                                       1UL << sspan_bmbit,
                                       memory_order_relaxed);
              atomic_check_out(&hpage->pcard);
              ctx->sspan.uintptr = hpage_base +
                (64 * sspan_bmidx + sspan_bmbit) * SPAGE_SIZE;
              if (sspan_bmidx == 0 && sspan_bmbit == 0)
                ctx->sspan.uintptr += sizeof(HugePage);
              return QOP_SUCCESS;
            }
        }
    }
  if (!atomic_book_critical(&hpage->pcard))
    {
      atomic_check_out(&hpage->pcard);
      return QOP_CONTINUE;
    }
  atomic_enter_critical(&hpage->pcard);
  for (int bmidx = 0; bmidx < 8; bmidx++)
    {
      if (atomic_load_explicit(&hpage->occupy_bmap[bmidx],
                               memory_order_relaxed)
          != ~0UL)
        {
          atomic_exit_check_out(&hpage->pcard);
          return QOP_CONTINUE;
        }
    }
  if (!atomic_book_critical(&ctx->hqueue->pcard))
    {
      atomic_exit_check_out(&hpage->pcard);
      return QOP_RESTART;
    }
  atomic_enter_critical(&ctx->hqueue->pcard);
  DequeueHPage(ctx->hqueue, hpage);
  atomic_exit_critical(&ctx->hqueue->pcard);
  atomic_exit_check_out(&hpage->pcard);
  return QOP_RESTART;
}


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

bool
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

bool
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
      if (bmidx_head > HPAGE_BMAP_NUM)
        return false;
      if (occupy_bmap[bmidx_head] & (1UL << 63))
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

      _hpage_cnt -= 64 - bmbit_head;
      bmidx_iter++;

      while (1)
        {
          if (bmidx_iter > HPAGE_BMAP_NUM)
            return false;
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
          else if (_hpage_cnt < (occupy_bmap[bmidx_iter] == 0 ?
                                 64 : __builtin_ctzl(occupy_bmap[bmidx_iter])))
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
  if (bmidx_iter - bmidx_head == 0)
    {
      occupy_bmap[bmidx_head] = ((1UL << _hpage_cnt) - 1) << bmbit_head;
    }
  else
    {
      occupy_bmap[bmidx_head] |=
        ~((1UL << bmbit_head) - 1) | (1UL << bmbit_head);
      if (_hpage_cnt)
        occupy_bmap[bmidx_iter] |= (1UL << _hpage_cnt) - 1;
      for (int bmidx = bmidx_head + 1; bmidx < bmidx_iter; bmidx++)
        occupy_bmap[bmidx] = ~0UL;
    }
  return true;
}

/* op_pspan.c ends here */
