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

static void
test_OPHeapReleaseHSpan_1Page(void** context)
{
  OPHeap* heap;
  uintptr_t heap_base;
  uint64_t occupy_bmap[HPAGE_BMAP_NUM] = {};
  uint64_t header_bmap[HPAGE_BMAP_NUM] = {};
  HugeSpanPtr hspan[8];
  OPHeapCtx ctx;
  Magic raw_hpage_magic = {}, typed_hpage_magic = {}, hblob_magic = {};

  assert_true(OPHeapNew(&heap));
  heap_base = (uintptr_t)heap;

  occupy_bmap[0] = 0x0F;
  occupy_bmap[1] = 0x0F;
  header_bmap[0] = 0x0F;
  header_bmap[1] = 0x0F;
  heap->occupy_bmap[0] = 0x0F;
  heap->header_bmap[0] = 0x0F;
  heap->occupy_bmap[1] = 0x0F;
  heap->header_bmap[1] = 0x0F;

  raw_hpage_magic.raw_hpage.pattern = RAW_HPAGE_PATTERN;
  typed_hpage_magic.typed_hpage.pattern = TYPED_HPAGE_PATTERN;
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
  ctx.hspan = hspan[0];
  HPageInit(&ctx, raw_hpage_magic);
  ctx.hspan = hspan[1];
  HPageInit(&ctx, raw_hpage_magic);
  ctx.hspan = hspan[2];
  HPageInit(&ctx, typed_hpage_magic);
  ctx.hspan = hspan[3];
  HPageInit(&ctx, typed_hpage_magic);
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

  OPHeapDestroy(heap);
}

static void
test_OPHeapReleaseHSpan_smallHBlob(void** context)
{
  OPHeap* heap;
  uintptr_t heap_base;
  uint64_t occupy_bmap[HPAGE_BMAP_NUM] = {};
  uint64_t header_bmap[HPAGE_BMAP_NUM] = {};
  HugeSpanPtr hspan[4];

  assert_true(OPHeapNew(&heap));
  heap_base = (uintptr_t)heap;

  //                       7654321076543210
  heap->occupy_bmap[0] = 0x0000000FFFFFFFFFUL;
  heap->header_bmap[0] = 0x0000000000000103UL;
  heap->occupy_bmap[1] = 0xFFFFFFFFFFFFFFFFUL;
  heap->header_bmap[1] = 0x0000000100000001UL;
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

  OPHeapDestroy(heap);
}

static void
test_OPHeapReleaseHSpan_lageHBlob(void** context)
{
  OPHeap* heap;
  uintptr_t heap_base;
  uint64_t occupy_bmap[HPAGE_BMAP_NUM] = {};
  uint64_t header_bmap[HPAGE_BMAP_NUM] = {};
  HugeSpanPtr hspan[4];

  assert_true(OPHeapNew(&heap));
  heap_base = (uintptr_t)heap;

  //                       7654321076543210
  heap->occupy_bmap[0] = 0xFFFFFFFF00000000UL;
  heap->header_bmap[0] = 0x0000000100000000UL;
  heap->occupy_bmap[1] = 0xFFFFFFFFFFFFFFFFUL;
  heap->header_bmap[1] = 0x0000000100000000UL;
  heap->occupy_bmap[2] = 0xFFFFFFFFFFFFFFFFUL;
  heap->header_bmap[2] = 0x0000000000000000UL;
  heap->occupy_bmap[3] = 0xFFFFFFFFFFFFFFF0UL;
  heap->header_bmap[3] = 0x8000000000000010UL;
  heap->occupy_bmap[4] = 0xFFFFFFFFFFFFFFFFUL;
  heap->occupy_bmap[5] = 0xFFFFFFFFFFFFFFFFUL;
  heap->occupy_bmap[6] = 0x0000000000000001UL;
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

  OPHeapDestroy(heap);
}

static void
test_HPageReleaseSSpan(void** context)
{
  OPHeap* heap;
  HugePage* hpage;
  HugePageQueue* hqueue;
  uintptr_t heap_base;
  OPHeapCtx ctx;
  Magic hmagic = {};
  Magic umagic = {};
  uint64_t occupy_bmap[8] = {0};
  uint64_t header_bmap[8] = {0};

  assert_true(OPHeapNew(&heap));
  heap_base = (uintptr_t)heap;
  heap->occupy_bmap[0] = 0x02;
  heap->header_bmap[0] = 0x02;
  hmagic.raw_hpage.pattern = RAW_HPAGE_PATTERN;
  ctx.hqueue = &heap->raw_type.hpage_queue;
  ctx.hspan.uintptr = heap_base + HPAGE_SIZE;
  HPageInit(&ctx, hmagic);
  hpage = ctx.hspan.hpage;

  OPHeapDestroy(heap);
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
    };

  return cmocka_run_group_tests(deallocator_tests, NULL, NULL);
}

/* deallocator_test.c ends here */
