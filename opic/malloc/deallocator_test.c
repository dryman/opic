/* deallocator_test.c ---
 *
 * Filename: deallocator_test.c
 * Description:
 * Author: Felix Chern
 * Maintainer:
 * Copyright: (c) 2017 Felix Chern
 * Created: Fri Mar 17 23:38:38 2017 (-0700)
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
#include "deallocator.h"

extern void
OPHeapCheckExpandSize(OPHeap* heap, size_t size);

static void
test_OPHeapReleaseHSpan_1Page(void** context)
{
  OPHeap* heap;
  uintptr_t heap_base;
  uint64_t occupy_bmap[HPAGE_BMAP_NUM] = {};
  uint64_t header_bmap[HPAGE_BMAP_NUM] = {};
  HugeSpanPtr hspan[8];
  Magic raw_hpage_magic = {}, hblob_magic = {};

  heap = OPHeapOpenTmp();
  OPHeapCheckExpandSize(heap, 68 * HPAGE_SIZE);

  heap_base = (uintptr_t)heap;

  occupy_bmap[0] = 0x0F;
  occupy_bmap[1] = 0x0F;
  header_bmap[0] = 0x0F;
  header_bmap[1] = 0x0F;
  atomic_store(&heap->occupy_bmap[0], 0x0F);
  atomic_store(&heap->header_bmap[0], 0x0F);
  atomic_store(&heap->occupy_bmap[1], 0x0F);
  atomic_store(&heap->header_bmap[1], 0x0F);

  raw_hpage_magic.raw_hpage.pattern = RAW_HPAGE_PATTERN;
  hblob_magic.huge_blob.pattern = HUGE_BLOB_PATTERN;
  hblob_magic.huge_blob.huge_pages = 1;

  hspan[0].hpage = &heap->hpage;
  hspan[1].uintptr = heap_base + HPAGE_SIZE;
  hspan[2].uintptr = heap_base + 2 * HPAGE_SIZE;
  hspan[3].uintptr = heap_base + 3 * HPAGE_SIZE;
  hspan[4].uintptr = heap_base + 64 * HPAGE_SIZE;
  hspan[5].uintptr = heap_base + 65 * HPAGE_SIZE;
  hspan[6].uintptr = heap_base + 66 * HPAGE_SIZE;
  hspan[7].uintptr = heap_base + 67 * HPAGE_SIZE;
  HPageInit(hspan[0].hpage, raw_hpage_magic);
  HPageInit(hspan[1].hpage, raw_hpage_magic);
  HPageInit(hspan[2].hpage, raw_hpage_magic);
  HPageInit(hspan[3].hpage, raw_hpage_magic);
  *hspan[4].magic = hblob_magic;
  *hspan[5].magic = hblob_magic;
  *hspan[6].magic = hblob_magic;
  *hspan[7].magic = hblob_magic;

  occupy_bmap[0] = 0x0E;
  header_bmap[0] = 0x0E;
  OPHeapReleaseHSpan(hspan[0]);
  assert_memory_equal(occupy_bmap, heap->occupy_bmap, sizeof(occupy_bmap));
  assert_memory_equal(header_bmap, heap->header_bmap, sizeof(header_bmap));
  assert_int_equal(0, heap->pcard);

  occupy_bmap[1] = 0x0E;
  header_bmap[1] = 0x0E;
  OPHeapReleaseHSpan(hspan[4]);
  assert_memory_equal(occupy_bmap, heap->occupy_bmap, sizeof(occupy_bmap));
  assert_memory_equal(header_bmap, heap->header_bmap, sizeof(header_bmap));
  assert_int_equal(0, heap->pcard);

  occupy_bmap[0] = 0x06;
  header_bmap[0] = 0x06;
  OPHeapReleaseHSpan(hspan[3]);
  assert_memory_equal(occupy_bmap, heap->occupy_bmap, sizeof(occupy_bmap));
  assert_memory_equal(header_bmap, heap->header_bmap, sizeof(header_bmap));
  assert_int_equal(0, heap->pcard);

  occupy_bmap[0] = 0x04;
  header_bmap[0] = 0x04;
  OPHeapReleaseHSpan(hspan[1]);
  assert_memory_equal(occupy_bmap, heap->occupy_bmap, sizeof(occupy_bmap));
  assert_memory_equal(header_bmap, heap->header_bmap, sizeof(header_bmap));
  assert_int_equal(0, heap->pcard);

  occupy_bmap[0] = 0x00;
  header_bmap[0] = 0x00;
  OPHeapReleaseHSpan(hspan[2]);
  assert_memory_equal(occupy_bmap, heap->occupy_bmap, sizeof(occupy_bmap));
  assert_memory_equal(header_bmap, heap->header_bmap, sizeof(header_bmap));
  assert_int_equal(0, heap->pcard);

  occupy_bmap[1] = 0x0C;
  header_bmap[1] = 0x0C;
  OPHeapReleaseHSpan(hspan[5]);
  assert_memory_equal(occupy_bmap, heap->occupy_bmap, sizeof(occupy_bmap));
  assert_memory_equal(header_bmap, heap->header_bmap, sizeof(header_bmap));
  assert_int_equal(0, heap->pcard);

  occupy_bmap[1] = 0x08;
  header_bmap[1] = 0x08;
  OPHeapReleaseHSpan(hspan[6]);
  assert_memory_equal(occupy_bmap, heap->occupy_bmap, sizeof(occupy_bmap));
  assert_memory_equal(header_bmap, heap->header_bmap, sizeof(header_bmap));
  assert_int_equal(0, heap->pcard);

  occupy_bmap[1] = 0x00;
  header_bmap[1] = 0x00;
  OPHeapReleaseHSpan(hspan[7]);
  assert_memory_equal(occupy_bmap, heap->occupy_bmap, sizeof(occupy_bmap));
  assert_memory_equal(header_bmap, heap->header_bmap, sizeof(header_bmap));
  assert_int_equal(0, heap->pcard);

  OPHeapClose(heap);
}

static void
test_OPHeapReleaseHSpan_smallHBlob(void** context)
{
  OPHeap* heap;
  uintptr_t heap_base;
  uint64_t occupy_bmap[HPAGE_BMAP_NUM] = {};
  uint64_t header_bmap[HPAGE_BMAP_NUM] = {};
  HugeSpanPtr hspan[4];

  heap = OPHeapOpenTmp();
  OPHeapCheckExpandSize(heap, 97 * HPAGE_SIZE);
  heap_base = (uintptr_t)heap;

  //                                    7654321076543210
  atomic_store(&heap->occupy_bmap[0], 0x0000000FFFFFFFFFUL);
  atomic_store(&heap->header_bmap[0], 0x0000000000000103UL);
  atomic_store(&heap->occupy_bmap[1], 0xFFFFFFFFFFFFFFFFUL);
  atomic_store(&heap->header_bmap[1], 0x0000000100000001UL);
  occupy_bmap[0] = heap->occupy_bmap[0];
  header_bmap[0] = heap->header_bmap[0];
  occupy_bmap[1] = heap->occupy_bmap[1];
  header_bmap[1] = heap->header_bmap[1];

  hspan[0].uintptr = heap_base + HPAGE_SIZE;
  hspan[1].uintptr = heap_base + 8 * HPAGE_SIZE;
  hspan[2].uintptr = heap_base + 64 * HPAGE_SIZE;
  hspan[3].uintptr = heap_base + 96 * HPAGE_SIZE;
  hspan[0].magic->huge_blob.pattern = HUGE_BLOB_PATTERN;
  hspan[1].magic->huge_blob.pattern = HUGE_BLOB_PATTERN;
  hspan[2].magic->huge_blob.pattern = HUGE_BLOB_PATTERN;
  hspan[3].magic->huge_blob.pattern = HUGE_BLOB_PATTERN;
  hspan[0].magic->huge_blob.huge_pages = 7;
  hspan[1].magic->huge_blob.huge_pages = 28;
  hspan[2].magic->huge_blob.huge_pages = 32;
  hspan[3].magic->huge_blob.huge_pages = 32;

  //                 7654321076543210
  occupy_bmap[0] = 0x0000000FFFFFFF01UL;
  header_bmap[0] = 0x0000000000000101UL;
  OPHeapReleaseHSpan(hspan[0]);
  assert_memory_equal(occupy_bmap, heap->occupy_bmap, sizeof(occupy_bmap));
  assert_memory_equal(header_bmap, heap->header_bmap, sizeof(header_bmap));
  assert_int_equal(0, heap->pcard);

  //                 7654321076543210
  occupy_bmap[0] = 0x0000000000000001UL;
  header_bmap[0] = 0x0000000000000001UL;
  OPHeapReleaseHSpan(hspan[1]);
  assert_memory_equal(occupy_bmap, heap->occupy_bmap, sizeof(occupy_bmap));
  assert_memory_equal(header_bmap, heap->header_bmap, sizeof(header_bmap));
  assert_int_equal(0, heap->pcard);

  //                 7654321076543210
  occupy_bmap[1] = 0x00000000FFFFFFFFUL;
  header_bmap[1] = 0x0000000000000001UL;
  OPHeapReleaseHSpan(hspan[3]);
  assert_memory_equal(occupy_bmap, heap->occupy_bmap, sizeof(occupy_bmap));
  assert_memory_equal(header_bmap, heap->header_bmap, sizeof(header_bmap));
  assert_int_equal(0, heap->pcard);

  //                 7654321076543210
  occupy_bmap[1] = 0x0000000000000000UL;
  header_bmap[1] = 0x0000000000000000UL;
  OPHeapReleaseHSpan(hspan[2]);
  assert_memory_equal(occupy_bmap, heap->occupy_bmap, sizeof(occupy_bmap));
  assert_memory_equal(header_bmap, heap->header_bmap, sizeof(header_bmap));
  assert_int_equal(0, heap->pcard);

  OPHeapClose(heap);
}

static void
test_OPHeapReleaseHSpan_lageHBlob(void** context)
{
  OPHeap* heap;
  uintptr_t heap_base;
  uint64_t occupy_bmap[HPAGE_BMAP_NUM] = {};
  uint64_t header_bmap[HPAGE_BMAP_NUM] = {};
  HugeSpanPtr hspan[4];

  heap = OPHeapOpenTmp();
  OPHeapCheckExpandSize(heap, 256 * HPAGE_SIZE);
  heap_base = (uintptr_t)heap;

  //                                    7654321076543210
  atomic_store(&heap->occupy_bmap[0], 0xFFFFFFFF00000000UL);
  atomic_store(&heap->header_bmap[0], 0x0000000100000000UL);
  atomic_store(&heap->occupy_bmap[1], 0xFFFFFFFFFFFFFFFFUL);
  atomic_store(&heap->header_bmap[1], 0x0000000100000000UL);
  atomic_store(&heap->occupy_bmap[2], 0xFFFFFFFFFFFFFFFFUL);
  atomic_store(&heap->header_bmap[2], 0x0000000000000000UL);
  atomic_store(&heap->occupy_bmap[3], 0xFFFFFFFFFFFFFFF0UL);
  atomic_store(&heap->header_bmap[3], 0x8000000000000010UL);
  atomic_store(&heap->occupy_bmap[4], 0xFFFFFFFFFFFFFFFFUL);
  atomic_store(&heap->occupy_bmap[5], 0xFFFFFFFFFFFFFFFFUL);
  atomic_store(&heap->occupy_bmap[6], 0x0000000000000001UL);
  occupy_bmap[0] = heap->occupy_bmap[0];
  header_bmap[0] = heap->header_bmap[0];
  occupy_bmap[1] = heap->occupy_bmap[1];
  header_bmap[1] = heap->header_bmap[1];
  occupy_bmap[2] = heap->occupy_bmap[2];
  header_bmap[2] = heap->header_bmap[2];
  occupy_bmap[3] = heap->occupy_bmap[3];
  header_bmap[3] = heap->header_bmap[3];
  occupy_bmap[4] = heap->occupy_bmap[4];
  occupy_bmap[5] = heap->occupy_bmap[5];
  occupy_bmap[6] = heap->occupy_bmap[6];

  hspan[0].uintptr = heap_base + 32 * HPAGE_SIZE;
  hspan[1].uintptr = heap_base + 96 * HPAGE_SIZE;
  hspan[2].uintptr = heap_base + 196 * HPAGE_SIZE;
  hspan[3].uintptr = heap_base + 255 * HPAGE_SIZE;
  hspan[0].magic->huge_blob.pattern = HUGE_BLOB_PATTERN;
  hspan[1].magic->huge_blob.pattern = HUGE_BLOB_PATTERN;
  hspan[2].magic->huge_blob.pattern = HUGE_BLOB_PATTERN;
  hspan[3].magic->huge_blob.pattern = HUGE_BLOB_PATTERN;
  hspan[0].magic->huge_blob.huge_pages = 64;
  hspan[1].magic->huge_blob.huge_pages = 96;
  hspan[2].magic->huge_blob.huge_pages = 59;
  hspan[3].magic->huge_blob.huge_pages = 130;

  //                 7654321076543210
  occupy_bmap[0] = 0x0000000000000000UL;
  header_bmap[0] = 0x0000000000000000UL;
  occupy_bmap[1] = 0xFFFFFFFF00000000UL;
  header_bmap[1] = 0x0000000100000000UL;
  OPHeapReleaseHSpan(hspan[0]);
  assert_memory_equal(occupy_bmap, heap->occupy_bmap, sizeof(occupy_bmap));
  assert_memory_equal(header_bmap, heap->header_bmap, sizeof(header_bmap));
  assert_int_equal(0, heap->pcard);

  //                 7654321076543210
  occupy_bmap[1] = 0x0000000000000000UL;
  header_bmap[1] = 0x0000000000000000UL;
  occupy_bmap[2] = 0x0000000000000000UL;
  OPHeapReleaseHSpan(hspan[1]);
  assert_memory_equal(occupy_bmap, heap->occupy_bmap, sizeof(occupy_bmap));
  assert_memory_equal(header_bmap, heap->header_bmap, sizeof(header_bmap));
  assert_int_equal(0, heap->pcard);

  //                 7654321076543210
  occupy_bmap[3] = 0x8000000000000000UL;
  header_bmap[3] = 0x8000000000000000UL;
  OPHeapReleaseHSpan(hspan[2]);
  assert_memory_equal(occupy_bmap, heap->occupy_bmap, sizeof(occupy_bmap));
  assert_memory_equal(header_bmap, heap->header_bmap, sizeof(header_bmap));
  assert_int_equal(0, heap->pcard);

  //                 7654321076543210
  occupy_bmap[3] = 0x0000000000000000UL;
  header_bmap[3] = 0x0000000000000000UL;
  occupy_bmap[4] = 0x0000000000000000UL;
  occupy_bmap[5] = 0x0000000000000000UL;
  occupy_bmap[6] = 0x0000000000000000UL;
  OPHeapReleaseHSpan(hspan[3]);
  assert_memory_equal(occupy_bmap, heap->occupy_bmap, sizeof(occupy_bmap));
  assert_memory_equal(header_bmap, heap->header_bmap, sizeof(header_bmap));
  assert_int_equal(0, heap->pcard);

  OPHeapClose(heap);
}

static void
test_HPageReleaseSSpan(void** context)
{
  OPHeap* heap;
  HugePage *hpage1, *hpage2, *hpage3;
  UnarySpan* uspan;
  HugePageQueue* hqueue;
  uintptr_t heap_base;
  OPHeapCtx ctx;
  Magic hmagic = {};
  Magic umagic = {};
  uint64_t occupy_bmap[8] = {0};
  uint64_t header_bmap[8] = {0};

  heap = OPHeapOpenTmp();
  OPHeapCheckExpandSize(heap, 4 * HPAGE_SIZE);
  heap_base = (uintptr_t)heap;
  atomic_store(&heap->occupy_bmap[0], 0x07);
  atomic_store(&heap->header_bmap[0], 0x07);
  hmagic.raw_hpage.pattern = RAW_HPAGE_PATTERN;
  ctx.hqueue = &heap->raw_type.hpage_queue;
  ctx.hspan.uintptr = heap_base + HPAGE_SIZE;
  hpage2 = ctx.hspan.hpage;
  HPageInit(hpage2, hmagic);
  hqueue = ctx.hqueue;

  memset(hpage2->occupy_bmap, 0xFF, 8 * sizeof(uint64_t));
  memset(hpage2->header_bmap, 0xFF, 8 * sizeof(uint64_t));
  hpage2->state = SPAN_DEQUEUED;

  umagic.raw_uspan.pattern = RAW_USPAN_PATTERN;
  umagic.raw_uspan.obj_size = 24;
  umagic.raw_uspan.thread_id = 0;
  ctx.sspan.uintptr = heap_base + HPAGE_SIZE + sizeof(HugePage);
  uspan = ctx.sspan.uspan;
  USpanInit(uspan, umagic, 1);

  // Enqueue hpage if it were dequeued
  memset(occupy_bmap, 0xFF, sizeof(occupy_bmap));
  memset(header_bmap, 0xFF, sizeof(header_bmap));
  //                 7654321076543210
  occupy_bmap[0] = 0xFFFFFFFFFFFFFFFE;
  header_bmap[0] = 0xFFFFFFFFFFFFFFFE;
  HPageReleaseSSpan(hpage2, uspan);
  assert_int_equal(0, hpage2->pcard);
  assert_int_equal(0, hqueue->pcard);
  assert_int_equal(SPAN_ENQUEUED, hpage2->state);
  assert_ptr_equal(hpage2, hqueue->hpage);
  assert_memory_equal(occupy_bmap, hpage2->occupy_bmap, sizeof(occupy_bmap));
  assert_memory_equal(header_bmap, hpage2->header_bmap, sizeof(header_bmap));

  // Enqueue another hpage which precedes previous one.
  ctx.hspan.hpage = &heap->hpage;
  hpage1 = ctx.hspan.hpage;
  HPageInit(hpage1, hmagic);
  hpage1->state = SPAN_DEQUEUED;
  atomic_store(&hpage1->occupy_bmap[2], 0x01UL);
  atomic_store(&hpage1->header_bmap[2], 0x01UL);
  HPageObtainUSpan(&ctx, 1, false);
  ctx.sspan.magic->small_blob.pattern = SMALL_BLOB_PATTERN;
  ctx.sspan.magic->small_blob.pages = 1;
  HPageReleaseSSpan(hpage1, ctx.sspan);
  memset(occupy_bmap, 0x00, sizeof(occupy_bmap));
  memset(header_bmap, 0x00, sizeof(header_bmap));
  occupy_bmap[0] = 0x07UL;
  occupy_bmap[1] = 0x00UL;
  occupy_bmap[2] = 0x01UL;
  header_bmap[2] = 0x01UL;
  assert_int_equal(0, hpage1->pcard);
  assert_int_equal(0, hqueue->pcard);
  assert_int_equal(SPAN_ENQUEUED, hpage1->state);
  assert_ptr_equal(hpage1, hqueue->hpage);
  assert_ptr_equal(hpage2, hqueue->hpage->next);
  assert_memory_equal(occupy_bmap, hpage1->occupy_bmap, sizeof(occupy_bmap));
  assert_memory_equal(header_bmap, hpage1->header_bmap, sizeof(header_bmap));

  // Setup third hpage and test releasing it
  ctx.hspan.uintptr = heap_base + 2 * HPAGE_SIZE;
  hpage3 = ctx.hspan.hpage;
  HPageInit(hpage3, hmagic);
  EnqueueHPage(ctx.hqueue, hpage3);
  assert_ptr_equal(hpage1, hqueue->hpage);
  assert_ptr_equal(hpage2, hqueue->hpage->next);
  assert_ptr_equal(hpage3, hqueue->hpage->next->next);
  umagic.large_uspan.pattern = LARGE_USPAN_PATTERN;
  umagic.large_uspan.obj_size = 2048;
  ctx.sspan.uintptr = heap_base + 2 * HPAGE_SIZE + sizeof(HugePage);
  uspan = ctx.sspan.uspan;
  USpanInit(uspan, umagic, 128);
  atomic_store(&hpage3->occupy_bmap[0], ~0UL);
  atomic_store(&hpage3->occupy_bmap[1], ~0UL);
  atomic_store(&hpage3->header_bmap[0], 1UL);
  HPageReleaseSSpan(hpage3, uspan);
  assert_ptr_equal(hpage1, hqueue->hpage);
  assert_ptr_equal(hpage2, hqueue->hpage->next);
  assert_ptr_equal(NULL, hqueue->hpage->next->next);
  assert_int_equal(0x03UL, heap->occupy_bmap[0]);
  assert_int_equal(0x03UL, heap->header_bmap[0]);

  // Even if the hpage were dequeued, we can still release it
  // This part also covers the testcase for the first hpage.
  DequeueHPage(ctx.hqueue, hpage1);
  assert_ptr_equal(hpage2, hqueue->hpage);
  assert_ptr_equal(NULL, hqueue->hpage->next);
  umagic.raw_uspan.pattern = RAW_USPAN_PATTERN;
  umagic.raw_uspan.obj_size = 2;
  ctx.sspan.uintptr = heap_base + 128 * SPAGE_SIZE;
  uspan = ctx.sspan.uspan;
  USpanInit(uspan, umagic, 1);
  HPageReleaseSSpan(hpage1, uspan);
  assert_int_equal(0x02UL, heap->occupy_bmap[0]);
  assert_int_equal(0x02UL, heap->header_bmap[0]);

  OPHeapClose(heap);
}

static void
test_USpanReleaseAddr(void** context)
{
  OPHeap* heap;
  SmallSpanPtr sspan1, sspan2;
  UnarySpanQueue* uqueue1;
  UnarySpanQueue* uqueue2;
  HugePage *hpage;
  uintptr_t heap_base;
  Magic hmagic = {};
  Magic umagic1 = {};
  Magic umagic2 = {};
  void* addr1;
  void* addr2;
  OPHeapCtx ctx;

  heap = OPHeapOpenTmp();
  OPHeapCheckExpandSize(heap, 4 * HPAGE_SIZE);
  heap_base = (uintptr_t)heap;
  atomic_store(&heap->occupy_bmap[0], 0x02UL);
  atomic_store(&heap->header_bmap[0], 0x02UL);

  hmagic.raw_hpage.pattern = RAW_HPAGE_PATTERN;
  hpage = (HugePage*)(heap_base + HPAGE_SIZE);
  HPageInit(hpage, hmagic);
  atomic_store(&hpage->occupy_bmap[0], ~0UL);
  atomic_store(&hpage->header_bmap[0], 0x07);
  atomic_store(&hpage->occupy_bmap[1], 0x07);
  atomic_store(&hpage->header_bmap[1], 0x04);

  sspan1.uintptr = heap_base + HPAGE_SIZE + sizeof(HugePage);
  sspan2.uintptr = heap_base + HPAGE_SIZE + 2 * SPAGE_SIZE;
  umagic1.raw_uspan.pattern = RAW_USPAN_PATTERN;
  umagic2.large_uspan.pattern = LARGE_USPAN_PATTERN;
  umagic1.raw_uspan.obj_size = 48;
  umagic2.large_uspan.obj_size = 2048;
  USpanInit(sspan1.uspan, umagic1, 1);
  USpanInit(sspan2.uspan, umagic2, 64);

  uqueue1 = &heap->raw_type.uspan_queue[2][0];
  uqueue2 = &heap->raw_type.large_uspan_queue[2];

  ctx.uqueue = uqueue1;
  ctx.sspan = sspan1;
  assert_int_equal(QOP_SUCCESS, USpanObtainAddr(&ctx, &addr1));
  assert_int_equal(QOP_SUCCESS, USpanObtainAddr(&ctx, &addr2));
  sspan1.uspan->state = SPAN_DEQUEUED;
  USpanReleaseAddr(sspan1.uspan, addr1);
  assert_ptr_equal(sspan1.uspan, uqueue1->uspan);
  assert_int_equal(SPAN_ENQUEUED, sspan1.uspan->state);
  USpanReleaseAddr(sspan1.uspan, addr2);
  assert_ptr_equal(NULL, uqueue1->uspan);
  //                 7654321076543210
  assert_int_equal(0xFFFFFFFFFFFFFFFEUL, hpage->occupy_bmap[0]);
  assert_int_equal(0x06UL, hpage->header_bmap[0]);

  ctx.uqueue = uqueue2;
  ctx.sspan = sspan2;
  assert_int_equal(QOP_SUCCESS, USpanObtainAddr(&ctx, &addr1));
  assert_int_equal(QOP_SUCCESS, USpanObtainAddr(&ctx, &addr2));
  sspan2.uspan->state = SPAN_DEQUEUED;
  USpanReleaseAddr(sspan2.uspan, addr1);
  assert_ptr_equal(sspan2.uspan, uqueue2->uspan);
  assert_int_equal(SPAN_ENQUEUED, sspan2.uspan->state);
  USpanReleaseAddr(sspan2.uspan, addr2);
  assert_ptr_equal(NULL, uqueue2->uspan);
  assert_int_equal(2UL, hpage->occupy_bmap[0]);
  assert_int_equal(2UL, hpage->header_bmap[0]);
  assert_int_equal(0x04UL, hpage->occupy_bmap[1]);
  assert_int_equal(0x04UL, hpage->header_bmap[1]);

  OPHeapClose(heap);
}

int
main (void)
{
  const struct CMUnitTest deallocator_tests[] =
    {
      cmocka_unit_test(test_OPHeapReleaseHSpan_1Page),
      cmocka_unit_test(test_OPHeapReleaseHSpan_smallHBlob),
      cmocka_unit_test(test_OPHeapReleaseHSpan_lageHBlob),
      cmocka_unit_test(test_HPageReleaseSSpan),
      cmocka_unit_test(test_USpanReleaseAddr),
    };

  return cmocka_run_group_tests(deallocator_tests, NULL, NULL);
}

/* deallocator_test.c ends here */
