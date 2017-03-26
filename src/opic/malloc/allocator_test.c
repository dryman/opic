/* allocator_test.c ---
 *
 * Filename: allocator_test.c
 * Description:
 * Author: Felix Chern
 * Maintainer:
 * Copyright: (c) 2017 Felix Chern
 * Created: Sat Mar 11 20:42:45 2017 (-0800)
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

#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdint.h>
#include <sys/mman.h>
#include <string.h>
#include <cmocka.h>

#include "magic.h"
#include "inline_aux.h"
#include "lookup_helper.h"
#include "init_helper.h"
#include "allocator.h"


static void
test_OPHeapObtainHPage_FullSize(void** context)
{
  OPHeap* heap;
  uintptr_t heap_base, hpage_base;
  uint64_t test_bmap[HPAGE_BMAP_NUM] = {};
  OPHeapCtx ctx;

  assert_true(OPHeapNew(&heap));
  heap_base = (uintptr_t)heap;

  // first hpage
  test_bmap[0] = 0x01UL;
  assert_true(OPHeapObtainHPage(heap, &ctx));
  assert_ptr_equal(&heap->hpage, ctx.hspan.hpage);
  assert_memory_equal(test_bmap, heap->occupy_bmap, sizeof(test_bmap));
  assert_memory_equal(test_bmap, heap->header_bmap, sizeof(test_bmap));
  assert_int_equal(0, heap->pcard);

  // test if we can fill the hole
  heap->occupy_bmap[0] = 0xFFCFUL;
  heap->header_bmap[0] = 0xFFCFUL;
  test_bmap[0] = 0XFFDFUL;
  hpage_base = heap_base + 4 * HPAGE_SIZE;
  assert_true(OPHeapObtainHPage(heap, &ctx));
  assert_ptr_equal(hpage_base, ctx.hspan.hpage);
  assert_memory_equal(test_bmap, heap->occupy_bmap, sizeof(test_bmap));
  assert_memory_equal(test_bmap, heap->header_bmap, sizeof(test_bmap));
  assert_int_equal(0, heap->pcard);
  test_bmap[0] = 0XFFFFUL;
  hpage_base = heap_base + 5 * HPAGE_SIZE;
  assert_true(OPHeapObtainHPage(heap, &ctx));
  assert_ptr_equal(hpage_base, ctx.hspan.hpage);
  assert_memory_equal(test_bmap, heap->occupy_bmap, sizeof(test_bmap));
  assert_memory_equal(test_bmap, heap->header_bmap, sizeof(test_bmap));
  assert_int_equal(0, heap->pcard);

  memset(test_bmap, 0xFF, sizeof(test_bmap));

  heap->occupy_bmap[0] = ~0UL;
  heap->header_bmap[0] = ~0UL;

  for (int i = 0; i < (HPAGE_BMAP_NUM - 1) * 64; i++)
    {
      hpage_base = heap_base + (i + 64) * HPAGE_SIZE;
      assert_true(OPHeapObtainHPage(heap, &ctx));
      assert_ptr_equal(hpage_base, ctx.hspan.hpage);
      assert_int_equal(0, heap->pcard);
    }
  assert_memory_equal(test_bmap, heap->occupy_bmap, sizeof(test_bmap));
  assert_memory_equal(test_bmap, heap->header_bmap, sizeof(test_bmap));

  assert_false(OPHeapObtainHPage(heap, &ctx));
  assert_int_equal(0, heap->pcard);

  OPHeapDestroy(heap);
}

static void
test_OPHeapObtainHPage_SmallSize(void** context)
{
  OPHeap* heap;
  uintptr_t heap_base, hpage_base;
  uint64_t occupy_bmap[HPAGE_BMAP_NUM] = {};
  uint64_t header_bmap[HPAGE_BMAP_NUM] = {};
  OPHeapCtx ctx;

  assert_true(OPHeapNew(&heap));
  heap_base = (uintptr_t)heap;
  heap->hpage_num = 16;
  OPHeapEmptiedBMaps(heap, heap->occupy_bmap, heap->header_bmap);
  memset(occupy_bmap, 0xFF, sizeof(occupy_bmap));

  // first hpage
  //                 7654321076543210
  occupy_bmap[0] = 0xFFFFFFFFFFFF0001UL;
  header_bmap[0] = 0x01UL;
  assert_true(OPHeapObtainHPage(heap, &ctx));
  assert_ptr_equal(&heap->hpage, ctx.hspan.hpage);
  assert_memory_equal(occupy_bmap, heap->occupy_bmap, sizeof(occupy_bmap));
  assert_memory_equal(header_bmap, heap->header_bmap, sizeof(header_bmap));
  assert_int_equal(0, heap->pcard);

  // test if we can fill the hole
  OPHeapEmptiedBMaps(heap, heap->occupy_bmap, heap->header_bmap);
  heap->occupy_bmap[0] |= 0xFFCFUL;
  heap->header_bmap[0] |= 0xFFCFUL;
  //                 7654321076543210
  occupy_bmap[0] = 0xFFFFFFFFFFFFFFDFUL;
  header_bmap[0] = 0xFFDFUL;
  hpage_base = heap_base + 4 * HPAGE_SIZE;
  assert_true(OPHeapObtainHPage(heap, &ctx));
  assert_ptr_equal(hpage_base, ctx.hspan.hpage);
  assert_memory_equal(occupy_bmap, heap->occupy_bmap, sizeof(occupy_bmap));
  assert_memory_equal(header_bmap, heap->header_bmap, sizeof(header_bmap));
  assert_int_equal(0, heap->pcard);
  //                 7654321076543210
  occupy_bmap[0] = 0xFFFFFFFFFFFFFFFFUL;
  header_bmap[0] = 0xFFFFUL;
  hpage_base = heap_base + 5 * HPAGE_SIZE;
  assert_true(OPHeapObtainHPage(heap, &ctx));
  assert_ptr_equal(hpage_base, ctx.hspan.hpage);
  assert_memory_equal(occupy_bmap, heap->occupy_bmap, sizeof(occupy_bmap));
  assert_memory_equal(header_bmap, heap->header_bmap, sizeof(header_bmap));
  assert_int_equal(0, heap->pcard);

  assert_false(OPHeapObtainHPage(heap, &ctx));
  assert_int_equal(0, heap->pcard);

  OPHeapDestroy(heap);
}

static void
test_OPHeapObtainHBlob_Small(void** context)
{
  OPHeap* heap;
  uintptr_t heap_base, hblob_base;
  uint64_t occupy_bmap[HPAGE_BMAP_NUM] = {};
  uint64_t header_bmap[HPAGE_BMAP_NUM] = {};
  OPHeapCtx ctx;

  assert_true(OPHeapNew(&heap));
  heap_base = (uintptr_t)heap;

  // first hpage won't be alloc for hblob
  hblob_base = heap_base + HPAGE_SIZE;
  occupy_bmap[0] = 0x02UL;
  header_bmap[0] = 0x02UL;
  assert_true(OPHeapObtainHBlob(heap, &ctx, 1));
  assert_ptr_equal(hblob_base, ctx.hspan.hblob);
  assert_memory_equal(occupy_bmap, heap->occupy_bmap, sizeof(occupy_bmap));
  assert_memory_equal(header_bmap, heap->header_bmap, sizeof(header_bmap));
  assert_int_equal(0, heap->pcard);

  hblob_base = heap_base + 2 * HPAGE_SIZE;
  occupy_bmap[0] = 0xFFEUL;
  header_bmap[0] = 0x06UL;
  assert_true(OPHeapObtainHBlob(heap, &ctx, 10));
  assert_ptr_equal(hblob_base, ctx.hspan.hblob);
  assert_memory_equal(occupy_bmap, heap->occupy_bmap, sizeof(occupy_bmap));
  assert_memory_equal(header_bmap, heap->header_bmap, sizeof(header_bmap));
  assert_int_equal(0, heap->pcard);

  hblob_base = heap_base + 12 * HPAGE_SIZE;
  //                 7654321076543210
  occupy_bmap[0] = 0x00000FFFFFFFFFFEUL;
  header_bmap[0] = 0x0000000000001006UL;
  assert_true(OPHeapObtainHBlob(heap, &ctx, 32));
  assert_ptr_equal(hblob_base, ctx.hspan.hblob);
  assert_memory_equal(occupy_bmap, heap->occupy_bmap, sizeof(occupy_bmap));
  assert_memory_equal(header_bmap, heap->header_bmap, sizeof(header_bmap));
  assert_int_equal(0, heap->pcard);

  // Cross a bitmap
  hblob_base = heap_base + 64 * HPAGE_SIZE;
  //                 7654321076543210
  occupy_bmap[1] = 0x00000000FFFFFFFFUL;
  header_bmap[1] = 0x0000000000000001UL;
  assert_true(OPHeapObtainHBlob(heap, &ctx, 32));
  assert_ptr_equal(hblob_base, ctx.hspan.hblob);
  assert_memory_equal(occupy_bmap, heap->occupy_bmap, sizeof(occupy_bmap));
  assert_memory_equal(header_bmap, heap->header_bmap, sizeof(header_bmap));
  assert_int_equal(0, heap->pcard);

  // End at boundary
  hblob_base = heap_base + 96 * HPAGE_SIZE;
  //                 7654321076543210
  occupy_bmap[1] = 0xFFFFFFFFFFFFFFFFUL;
  header_bmap[1] = 0x0000000100000001UL;
  assert_true(OPHeapObtainHBlob(heap, &ctx, 32));
  assert_ptr_equal(hblob_base, ctx.hspan.hblob);
  assert_memory_equal(occupy_bmap, heap->occupy_bmap, sizeof(occupy_bmap));
  assert_memory_equal(header_bmap, heap->header_bmap, sizeof(header_bmap));
  assert_int_equal(0, heap->pcard);

  // Can fill in gap
  hblob_base = heap_base + 44 * HPAGE_SIZE;
  //                 7654321076543210
  occupy_bmap[0] = 0x8000FFFFFFFFFFFEUL;
  header_bmap[0] = 0x8000100000001006UL;
  heap->occupy_bmap[0] |= 1UL << 63;
  heap->header_bmap[0] |= 1UL << 63;
  assert_true(OPHeapObtainHBlob(heap, &ctx, 4));
  assert_ptr_equal(hblob_base, ctx.hspan.hblob);
  assert_memory_equal(occupy_bmap, heap->occupy_bmap, sizeof(occupy_bmap));
  assert_memory_equal(header_bmap, heap->header_bmap, sizeof(header_bmap));
  assert_int_equal(0, heap->pcard);

  // TODO need to test out of space case..
  OPHeapDestroy(heap);
}

static void
test_OPHeapObtainHBlob_Large(void** context)
{
  OPHeap* heap;
  uintptr_t heap_base, hblob_base;
  uint64_t occupy_bmap[HPAGE_BMAP_NUM] = {};
  uint64_t header_bmap[HPAGE_BMAP_NUM] = {};
  OPHeapCtx ctx;

  assert_true(OPHeapNew(&heap));
  heap_base = (uintptr_t)heap;

  // first hpage won't be alloc for hblob
  hblob_base = heap_base + HPAGE_SIZE;
  //                 7654321076543210
  occupy_bmap[0] = 0xFFFFFFFFFFFFFFFEUL;
  header_bmap[0] = 0x02UL;
  assert_true(OPHeapObtainHBlob(heap, &ctx, 63));
  assert_ptr_equal(hblob_base, ctx.hspan.hblob);
  assert_memory_equal(occupy_bmap, heap->occupy_bmap, sizeof(occupy_bmap));
  assert_memory_equal(header_bmap, heap->header_bmap, sizeof(header_bmap));
  assert_int_equal(0, heap->pcard);

  hblob_base = heap_base + 64 * HPAGE_SIZE;
  //                 7654321076543210
  occupy_bmap[1] = 0x0000000FFFFFFFFFUL;
  header_bmap[1] = 0x0000000000000001UL;
  assert_true(OPHeapObtainHBlob(heap, &ctx, 36));
  assert_ptr_equal(hblob_base, ctx.hspan.hblob);
  assert_memory_equal(occupy_bmap, heap->occupy_bmap, sizeof(occupy_bmap));
  assert_memory_equal(header_bmap, heap->header_bmap, sizeof(header_bmap));
  assert_int_equal(0, heap->pcard);

  hblob_base = heap_base + 100 * HPAGE_SIZE;
  //                 7654321076543210
  occupy_bmap[1] = 0xFFFFFFFFFFFFFFFFUL;
  header_bmap[1] = 0x0000001000000001UL;
  occupy_bmap[2] = 0xFFFFFFFFFFFFFFFFUL;
  occupy_bmap[3] = 0x0000000FFFFFFFFFUL;
  assert_true(OPHeapObtainHBlob(heap, &ctx, 128));
  assert_ptr_equal(hblob_base, ctx.hspan.hblob);
  assert_memory_equal(occupy_bmap, heap->occupy_bmap, sizeof(occupy_bmap));
  assert_memory_equal(header_bmap, heap->header_bmap, sizeof(header_bmap));
  assert_int_equal(0, heap->pcard);

  hblob_base = heap_base + 228 * HPAGE_SIZE;
  //                 7654321076543210
  occupy_bmap[3] = 0xFFFFFFFFFFFFFFFFUL;
  header_bmap[3] = 0x0000001000000000UL;
  occupy_bmap[4] = 0xFFFFFFFFFFFFFFFFUL;
  assert_true(OPHeapObtainHBlob(heap, &ctx, 92));
  assert_ptr_equal(hblob_base, ctx.hspan.hblob);
  assert_memory_equal(occupy_bmap, heap->occupy_bmap, sizeof(occupy_bmap));
  assert_memory_equal(header_bmap, heap->header_bmap, sizeof(header_bmap));
  assert_int_equal(0, heap->pcard);

  OPHeapDestroy(heap);
}

static void
test_HPageObtainUSpan(void** context)
{
  OPHeap* heap;
  OPHeapCtx ctx;
  HugePage* hpage;
  uintptr_t heap_base, uspan_addr;
  Magic magic = {};
  uint64_t occupy_bmap[8] = {0};
  uint64_t header_bmap[8] = {0};

  assert_true(OPHeapNew(&heap));
  heap_base = (uintptr_t)heap;

  assert_true(OPHeapObtainHPage(heap, &ctx));
  ctx.hqueue = &heap->raw_type.hpage_queue;
  magic.raw_hpage.pattern = RAW_HPAGE_PATTERN;
  hpage = ctx.hspan.hpage;
  HPageInit(hpage, magic);
  EnqueueHPage(ctx.hqueue, hpage);
  assert_ptr_equal(hpage, ctx.hqueue->hpage);
  assert_int_equal(SPAN_ENQUEUED, hpage->state);

  hpage->pcard = -1;
  assert_int_equal(QOP_CONTINUE, HPageObtainUSpan(&ctx, 1, false));
  hpage->pcard = 0;

  atomic_check_in(&ctx.hqueue->pcard);
  assert_int_equal(1, ctx.hqueue->pcard);

  /*
   * sizeof(OPHeap) = 391936
   * sizeof(HugePage) = 144
   * (391936 + 144) = 4096 * 95 + 2960
   * => 96 bit spaces to occupy
   * 96 = 64 + 32
   */
  //                 7654321076543210
  occupy_bmap[0] = 0xFFFFFFFFFFFFFFFFUL;
  occupy_bmap[1] = 0x00000000FFFFFFFFUL;
  assert_memory_equal(occupy_bmap, hpage->occupy_bmap, sizeof(occupy_bmap));
  assert_memory_equal(header_bmap, hpage->header_bmap, sizeof(header_bmap));

  //                 7654321076543210
  occupy_bmap[1] = 0x0000000FFFFFFFFFUL;
  header_bmap[1] = 0x0000000100000000UL;
  uspan_addr = heap_base + 96 * SPAGE_SIZE;
  assert_int_equal(QOP_SUCCESS, HPageObtainUSpan(&ctx, 4, false));
  assert_int_equal(uspan_addr, ctx.sspan.uintptr);
  assert_memory_equal(occupy_bmap, hpage->occupy_bmap, sizeof(occupy_bmap));
  assert_memory_equal(header_bmap, hpage->header_bmap, sizeof(header_bmap));

  //                 7654321076543210
  occupy_bmap[2] = 0x00000000FFFFFFFFUL;
  header_bmap[2] = 0x0000000000000001UL;
  uspan_addr = heap_base + 128 * SPAGE_SIZE;
  assert_int_equal(QOP_SUCCESS, HPageObtainUSpan(&ctx, 32, false));
  assert_int_equal(uspan_addr, ctx.sspan.uintptr);
  assert_memory_equal(occupy_bmap, hpage->occupy_bmap, sizeof(occupy_bmap));
  assert_memory_equal(header_bmap, hpage->header_bmap, sizeof(header_bmap));

  //                 7654321076543210
  occupy_bmap[1] = 0xFFFFFFFFFFFFFFFFUL;
  header_bmap[1] = 0x0000001100000000UL;
  uspan_addr = heap_base + 100 * SPAGE_SIZE;
  assert_int_equal(QOP_SUCCESS, HPageObtainUSpan(&ctx, 28, false));
  assert_int_equal(uspan_addr, ctx.sspan.uintptr);
  assert_memory_equal(occupy_bmap, hpage->occupy_bmap, sizeof(occupy_bmap));
  assert_memory_equal(header_bmap, hpage->header_bmap, sizeof(header_bmap));

  for (int i = 2; i < 8; i++)
    { //                 7654321076543210
      occupy_bmap[i] = 0xFFFFFFFFFFFFFFFFUL;
      header_bmap[i] = 0x0000000100000001UL;
    }
  for (uspan_addr = heap_base + 160 * SPAGE_SIZE;
       uspan_addr < heap_base + 512 * SPAGE_SIZE;
       uspan_addr += 32 * SPAGE_SIZE)
    {
      assert_int_equal(QOP_SUCCESS, HPageObtainUSpan(&ctx, 32, false));
      assert_int_equal(uspan_addr, ctx.sspan.uintptr);
    }
  assert_memory_equal(occupy_bmap, hpage->occupy_bmap, sizeof(occupy_bmap));
  assert_memory_equal(header_bmap, hpage->header_bmap, sizeof(header_bmap));

  assert_int_equal(QOP_RESTART, HPageObtainUSpan(&ctx, 1, false));
  assert_ptr_equal(NULL, ctx.hqueue->hpage);
  assert_int_equal(SPAN_DEQUEUED, hpage->state);

  atomic_check_out(&ctx.hqueue->pcard);
  assert_int_equal(0, ctx.hqueue->pcard);

  // get second hpage to test uspan offset
  // The offset should be sizeof(HugePage)
  assert_true(OPHeapObtainHPage(heap, &ctx));
  hpage = ctx.hspan.hpage;
  HPageInit(hpage, magic);
  EnqueueHPage(ctx.hqueue, hpage);
  assert_ptr_equal(hpage, ctx.hqueue->hpage);
  assert_int_equal(SPAN_ENQUEUED, hpage->state);

  memset(occupy_bmap, 0, sizeof(occupy_bmap));
  memset(header_bmap, 0, sizeof(header_bmap));
  occupy_bmap[0] = 0x01UL;
  header_bmap[0] = 0x01UL;
  uspan_addr = heap_base + 512 * SPAGE_SIZE + sizeof(HugePage);
  assert_int_equal(QOP_SUCCESS, HPageObtainUSpan(&ctx, 1, false));
  assert_int_equal(uspan_addr, ctx.sspan.uintptr);
  assert_memory_equal(occupy_bmap, hpage->occupy_bmap, sizeof(occupy_bmap));
  assert_memory_equal(header_bmap, hpage->header_bmap, sizeof(header_bmap));

  // get third hpage to test use_full_span logic
  assert_true(OPHeapObtainHPage(heap, &ctx));
  hpage = ctx.hspan.hpage;
  HPageInit(hpage, magic);
  EnqueueHPage(ctx.hqueue, hpage);
  assert_int_equal(SPAN_ENQUEUED, hpage->state);
  assert_ptr_equal(hpage, ctx.hqueue->hpage->next);

  occupy_bmap[0] = 0x02UL;
  header_bmap[0] = 0x02UL;
  uspan_addr = heap_base + 1025 * SPAGE_SIZE;
  assert_int_equal(QOP_SUCCESS, HPageObtainUSpan(&ctx, 1, true));
  assert_int_equal(uspan_addr, ctx.sspan.uintptr);
  assert_memory_equal(occupy_bmap, hpage->occupy_bmap, sizeof(occupy_bmap));
  assert_memory_equal(header_bmap, hpage->header_bmap, sizeof(header_bmap));

  OPHeapDestroy(heap);
}

static void
test_HPageObtainSSpan(void** context)
{
  OPHeap* heap;
  OPHeapCtx ctx;
  HugePage* hpage;
  uintptr_t heap_base, uspan_addr;
  Magic magic = {};
  uint64_t occupy_bmap[8] = {0};
  uint64_t header_bmap[8] = {0};

  assert_true(OPHeapNew(&heap));
  heap_base = (uintptr_t)heap;

  assert_true(OPHeapObtainHPage(heap, &ctx));
  ctx.hqueue = &heap->raw_type.hpage_queue;
  magic.raw_hpage.pattern = RAW_HPAGE_PATTERN;
  hpage = ctx.hspan.hpage;
  HPageInit(hpage, magic);
  EnqueueHPage(ctx.hqueue, hpage);
  assert_ptr_equal(hpage, ctx.hqueue->hpage);
  assert_int_equal(SPAN_ENQUEUED, hpage->state);

  hpage->pcard = -1;
  assert_int_equal(QOP_CONTINUE, HPageObtainSSpan(&ctx, 64, true));
  hpage->pcard = 0;

  atomic_check_in(&ctx.hqueue->pcard);
  assert_int_equal(1, ctx.hqueue->pcard);

  //                 7654321076543210
  occupy_bmap[0] = 0xFFFFFFFFFFFFFFFFUL;
  occupy_bmap[1] = 0x00000000FFFFFFFFUL;
  assert_memory_equal(occupy_bmap, hpage->occupy_bmap, sizeof(occupy_bmap));
  assert_memory_equal(header_bmap, hpage->header_bmap, sizeof(header_bmap));

  //                 7654321076543210
  occupy_bmap[1] = 0xFFFFFFFFFFFFFFFFUL;
  header_bmap[1] = 0x0000000100000000UL;
  occupy_bmap[2] = 0x00000000FFFFFFFFUL;
  uspan_addr = heap_base + 96 * SPAGE_SIZE;
  assert_int_equal(QOP_SUCCESS, HPageObtainSSpan(&ctx, 64, true));
  assert_int_equal(uspan_addr, ctx.sspan.uintptr);
  assert_memory_equal(occupy_bmap, hpage->occupy_bmap, sizeof(occupy_bmap));
  assert_memory_equal(header_bmap, hpage->header_bmap, sizeof(header_bmap));

  //                 7654321076543210
  header_bmap[2] = 0x0000000100000000UL;
  memset(occupy_bmap, 0xFF, sizeof(occupy_bmap));
  uspan_addr = heap_base + 160 * SPAGE_SIZE;
  assert_int_equal(QOP_SUCCESS, HPageObtainSSpan(&ctx, 352, true));
  assert_int_equal(uspan_addr, ctx.sspan.uintptr);
  assert_memory_equal(occupy_bmap, hpage->occupy_bmap, sizeof(occupy_bmap));
  assert_memory_equal(header_bmap, hpage->header_bmap, sizeof(header_bmap));

  assert_int_equal(QOP_RESTART, HPageObtainSSpan(&ctx, 64, true));
  assert_ptr_equal(NULL, ctx.hqueue->hpage);
  assert_int_equal(SPAN_DEQUEUED, hpage->state);

  // Second HPage
  assert_true(OPHeapObtainHPage(heap, &ctx));
  hpage = ctx.hspan.hpage;
  HPageInit(hpage, magic);
  EnqueueHPage(ctx.hqueue, hpage);
  assert_ptr_equal(hpage, ctx.hqueue->hpage);
  assert_int_equal(SPAN_ENQUEUED, hpage->state);
  assert_int_equal(1, ctx.hqueue->pcard);

  memset(occupy_bmap, 0, sizeof(occupy_bmap));
  memset(header_bmap, 0, sizeof(header_bmap));
  //                 7654321076543210
  occupy_bmap[0] = 0xFFFFFFFFFFFFFFFFUL;
  occupy_bmap[1] = 0xFFFFFFFFFFFFFFFFUL;
  header_bmap[0] = 1UL;
  uspan_addr = heap_base + 512 * SPAGE_SIZE + sizeof(HugePage);
  assert_int_equal(QOP_SUCCESS, HPageObtainSSpan(&ctx, 128, false));
  assert_int_equal(uspan_addr, ctx.sspan.uintptr);
  assert_memory_equal(occupy_bmap, hpage->occupy_bmap, sizeof(occupy_bmap));
  assert_memory_equal(header_bmap, hpage->header_bmap, sizeof(header_bmap));

  hpage->occupy_bmap[0] = 0;
  hpage->occupy_bmap[1] = 0;
  hpage->header_bmap[0] = 0;
  //                 7654321076543210
  occupy_bmap[0] = 0xFFFFFFFFFFFFFFFEUL;
  occupy_bmap[1] = 0x0000000000000001UL;
  header_bmap[0] = 2UL;
  uspan_addr = heap_base + 513 * SPAGE_SIZE;
  assert_int_equal(QOP_SUCCESS, HPageObtainSSpan(&ctx, 64, true));
  assert_int_equal(uspan_addr, ctx.sspan.uintptr);
  assert_memory_equal(occupy_bmap, hpage->occupy_bmap, sizeof(occupy_bmap));
  assert_memory_equal(header_bmap, hpage->header_bmap, sizeof(header_bmap));

  OPHeapDestroy(heap);
}

static void
test_USpanObtainAddr(void** context)
{
  OPHeap* heap;
  OPHeapCtx ctx;
  UnarySpan* uspan;
  uintptr_t heap_base, u_addr;
  void* addr;
  Magic umagic = {};
  int count;

  assert_true(OPHeapNew(&heap));
  heap_base = (uintptr_t)heap;

  /*
   * Object size: 16 bytes; (The smallest raw_type size we can alloc)
   * 1 Page count => 4096 bytes
   * Bitmap: 4096 / 16 = 256 bits to map the space = 4 bitmaps
   * 4 bitmaps takes 8 * 4 = 32 bytes
   * headroom size in bytes: sizeof(UnarySpan) + 32 = 24 + 32 = 56 bytes
   * headroom in object/bits: 56 = 16 * 3 + 8 => 4 bits
   * padding: 0 bytes
   * number of objects: 256 - 4 = 252
   */
  umagic.raw_uspan.pattern = RAW_USPAN_PATTERN;
  umagic.raw_uspan.obj_size = 16;
  umagic.raw_uspan.thread_id = 0;
  ctx.uqueue = &heap->raw_type.uspan_queue[0][0];
  ctx.sspan.uintptr = heap_base + HPAGE_SIZE + SPAGE_SIZE;
  uspan = ctx.sspan.uspan;
  USpanInit(uspan, umagic, 1);
  EnqueueUSpan(ctx.uqueue, uspan);
  assert_ptr_equal(uspan, ctx.uqueue->uspan);
  assert_int_equal(SPAN_ENQUEUED, uspan->state);
  atomic_check_in(&ctx.uqueue->pcard);
  for (count = 0, u_addr = heap_base + HPAGE_SIZE +
         SPAGE_SIZE + 16 * uspan->bitmap_headroom;
       u_addr < heap_base + HPAGE_SIZE + 2 * SPAGE_SIZE;
       u_addr += 16, count++)
    {
      assert_int_equal(QOP_SUCCESS, USpanObtainAddr(&ctx, &addr));
      assert_ptr_equal(u_addr, addr);
    }
  assert_int_equal(252, count);
  assert_int_equal(QOP_RESTART, USpanObtainAddr(&ctx, &addr));
  assert_int_equal(SPAN_DEQUEUED, uspan->state);
  assert_ptr_equal(NULL, ctx.uqueue->uspan);

  /*
   * Object size: 16 bytes
   * 1 Page count => 4096 bytes
   * Bitmap: 4096 / 16 = 256 bits to map the space = 4 bitmaps
   * 4 bitmaps takes 8 * 4 = 32 bytes
   * headroom size in bytes: sizeof(HugePage) + sizeof(UnarySpan) + 32
   *   = 144 + 24 + 32 = 200 bytes
   * headroom in object/bits: 200 = 16 * 12 + 8 => 13 bits
   * padding: 0 bytes
   * number of objects: 256 - 13 = 243
   */
  ctx.sspan.uintptr = heap_base + HPAGE_SIZE + sizeof(HugePage);
  uspan = ctx.sspan.uspan;
  USpanInit(uspan, umagic, 1);
  EnqueueUSpan(ctx.uqueue, uspan);
  assert_ptr_equal(uspan, ctx.uqueue->uspan);
  assert_int_equal(SPAN_ENQUEUED, uspan->state);
  for (count = 0, u_addr = heap_base + HPAGE_SIZE + 16 * uspan->bitmap_headroom;
       u_addr < heap_base + HPAGE_SIZE + SPAGE_SIZE;
       u_addr += 16, count++)
    {
      assert_int_equal(QOP_SUCCESS, USpanObtainAddr(&ctx, &addr));
      assert_ptr_equal(u_addr, addr);
    }
  assert_int_equal(243, count);
  assert_int_equal(QOP_RESTART, USpanObtainAddr(&ctx, &addr));
  assert_int_equal(SPAN_DEQUEUED, uspan->state);
  assert_ptr_equal(NULL, ctx.uqueue->uspan);

  /*
   * Object size: 24 bytes
   * 1 Page count => 4096 bytes
   * Bitmap: 4096 / 24 = 170.6 bits to map the space = 3 bitmaps
   * 3 bitmaps takes 8 * 3 = 24 bytes
   * headroom size in bytes: sizeof(UnarySpan) + 24 = 24 + 24 = 48 bytes
   * headroom in object/bits: 48 = 24 * 2 => 2 bits
   * padding size in bytes: 3 * 64 * 24 - 4096 = 512 bytes
   * padding in object/bits: 512 = 24 * 21 + 8 => 22 bits
   * number of objects: 3 * 64 - 2 - 22 = 168
   */
  umagic.raw_uspan.obj_size = 24;
  ctx.sspan.uintptr = heap_base + HPAGE_SIZE + 2 * SPAGE_SIZE;
  uspan = ctx.sspan.uspan;
  USpanInit(uspan, umagic, 1);
  EnqueueUSpan(ctx.uqueue, uspan);
  assert_ptr_equal(uspan, ctx.uqueue->uspan);
  assert_int_equal(SPAN_ENQUEUED, uspan->state);
  for (count = 0, u_addr = heap_base + HPAGE_SIZE +
         2 * SPAGE_SIZE + 24 * uspan->bitmap_headroom;
       u_addr < heap_base + HPAGE_SIZE + 2 * SPAGE_SIZE + 24 * 170;
       u_addr += 24, count++)
    {
      assert_int_equal(QOP_SUCCESS, USpanObtainAddr(&ctx, &addr));
      assert_ptr_equal(u_addr, addr);
    }
  assert_int_equal(168, count);
  assert_int_equal(QOP_RESTART, USpanObtainAddr(&ctx, &addr));
  assert_int_equal(SPAN_DEQUEUED, uspan->state);
  assert_ptr_equal(NULL, ctx.uqueue->uspan);


  /*
   * Object size: 2 bytes => align to 16
   * 1 Page count => 4096 bytes
   * Bitmap: 4096 / 16 = 256 bits to map the space = 4 bitmaps
   * headroom size in bytes: sizeof(UnarySpan) + 8 * 4 = 24 + 32 = 56 bytes
   * headroom in object/bits: 56 = 16 * 3 + 8 => 4 bits
   * padding: 0 bytes
   * number of objects: 256 - 4 = 252
   */
  umagic.typed_uspan.pattern = TYPED_USPAN_PATTERN;
  umagic.typed_uspan.obj_size = 2;
  umagic.typed_uspan.thread_id = 0;
  umagic.typed_uspan.type_alias = 0;
  ctx.uqueue = &heap->type_alias[0].uspan_queue[0];
  ctx.sspan.uintptr = heap_base + HPAGE_SIZE + 3 * SPAGE_SIZE;
  USpanInit(ctx.sspan.uspan, umagic, 1);

  uspan = ctx.sspan.uspan;
  EnqueueUSpan(ctx.uqueue, uspan);
  assert_ptr_equal(uspan, ctx.uqueue->uspan);
  assert_int_equal(SPAN_ENQUEUED, uspan->state);
  atomic_check_in(&ctx.uqueue->pcard);
  for (count = 0, u_addr = heap_base + HPAGE_SIZE +
         3 * SPAGE_SIZE + 16 * uspan->bitmap_headroom;
       u_addr < heap_base + HPAGE_SIZE + 4 * SPAGE_SIZE;
       u_addr += 16, count++)
    {
      assert_int_equal(QOP_SUCCESS, USpanObtainAddr(&ctx, &addr));
      assert_ptr_equal(u_addr, addr);
    }
  assert_int_equal(252, count);
  assert_int_equal(QOP_RESTART, USpanObtainAddr(&ctx, &addr));
  assert_int_equal(SPAN_DEQUEUED, uspan->state);
  assert_ptr_equal(NULL, ctx.uqueue->uspan);

  OPHeapDestroy(heap);
}

static void
test_USpanObtainAddr_Large(void** context)
{
  OPHeap* heap;
  OPHeapCtx ctx;
  UnarySpan* uspan;
  uintptr_t heap_base, u_addr;
  void* addr;
  Magic umagic = {};
  int count;

  assert_true(OPHeapNew(&heap));
  heap_base = (uintptr_t)heap;

  /*
   * Object size: 1024 bytes
   * 16 Page count => 65536 bytes
   * Bitmap: 65536 / 1024 = 64 bits to map the space = 1 bitmaps
   * headroom size in bytes: sizeof(UnarySpan) + 8 = 24 + 8 = 32 bytes
   * headroom in object/bits: 1
   * padding: 0 bytes
   * number of objects: 64 - 1 = 63
   */
  umagic.large_uspan.pattern = LARGE_USPAN_PATTERN;
  umagic.large_uspan.obj_size = 1024;
  ctx.uqueue = &heap->raw_type.large_uspan_queue[0];
  ctx.sspan.uintptr = heap_base + HPAGE_SIZE + SPAGE_SIZE;
  uspan = ctx.sspan.uspan;
  USpanInit(uspan, umagic, 16);
  EnqueueUSpan(ctx.uqueue, uspan);
  assert_ptr_equal(uspan, ctx.uqueue->uspan);
  assert_int_equal(SPAN_ENQUEUED, uspan->state);
  atomic_check_in(&ctx.uqueue->pcard);
  for (count = 0, u_addr = heap_base + HPAGE_SIZE +
         SPAGE_SIZE + 1024 * uspan->bitmap_headroom;
       u_addr < heap_base + HPAGE_SIZE + 17 * SPAGE_SIZE;
       u_addr += 1024, count++)
    {
      assert_int_equal(QOP_SUCCESS, USpanObtainAddr(&ctx, &addr));
      assert_ptr_equal(u_addr, addr);
    }
  assert_int_equal(63, count);
  assert_int_equal(QOP_RESTART, USpanObtainAddr(&ctx, &addr));
  assert_int_equal(SPAN_DEQUEUED, uspan->state);
  assert_ptr_equal(NULL, ctx.uqueue->uspan);

  /*
   * Object size: 2048 bytes
   * 32 Page count => 131072 bytes
   * Bitmap: 131072 / 2048 = 64 bits to map the space = 1 bitmaps
   * headroom size in bytes: sizeof(UnarySpan) + 8 = 24 + 8 = 32 bytes
   * headroom in object/bits: 1
   * padding: 0 bytes
   * number of objects: 64 - 1 = 63
   */
  umagic.large_uspan.obj_size = 2048;
  ctx.uqueue = &heap->raw_type.large_uspan_queue[0];
  ctx.sspan.uintptr = heap_base + HPAGE_SIZE + 32 * SPAGE_SIZE;
  uspan = ctx.sspan.uspan;
  USpanInit(uspan, umagic, 32);
  EnqueueUSpan(ctx.uqueue, uspan);
  assert_ptr_equal(uspan, ctx.uqueue->uspan);
  assert_int_equal(SPAN_ENQUEUED, uspan->state);
  for (count = 0, u_addr = heap_base + HPAGE_SIZE +
         32 * SPAGE_SIZE + 2048 * uspan->bitmap_headroom;
       u_addr < heap_base + HPAGE_SIZE + 64 * SPAGE_SIZE;
       u_addr += 2048, count++)
    {
      assert_int_equal(QOP_SUCCESS, USpanObtainAddr(&ctx, &addr));
      assert_ptr_equal(u_addr, addr);
    }
  assert_int_equal(63, count);
  assert_int_equal(QOP_RESTART, USpanObtainAddr(&ctx, &addr));
  assert_int_equal(SPAN_DEQUEUED, uspan->state);
  assert_ptr_equal(NULL, ctx.uqueue->uspan);

  OPHeapDestroy(heap);
}

static void
test_DispatchHPageForSSpan(void** context)
{
  OPHeap* heap;
  uintptr_t heap_base;

  assert_true(OPHeapNew(&heap));
  heap_base = (uintptr_t)heap;

  // TODO: configure different kind of init state
  // run dispatch and see if the end state is expected

  OPHeapDestroy(heap);
}

int
main (void)
{
  const struct CMUnitTest allocator_tests[] =
    {
      cmocka_unit_test(test_OPHeapObtainHPage_FullSize),
      cmocka_unit_test(test_OPHeapObtainHPage_SmallSize),
      cmocka_unit_test(test_OPHeapObtainHBlob_Small),
      cmocka_unit_test(test_OPHeapObtainHBlob_Large),
      cmocka_unit_test(test_HPageObtainUSpan),
      cmocka_unit_test(test_HPageObtainSSpan),
      cmocka_unit_test(test_USpanObtainAddr),
      cmocka_unit_test(test_USpanObtainAddr_Large),
      cmocka_unit_test(test_DispatchHPageForSSpan),
    };

  return cmocka_run_group_tests(allocator_tests, NULL, NULL);
}

/* allocator_test.c ends here */
