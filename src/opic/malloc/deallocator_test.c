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

int
main (void)
{
  const struct CMUnitTest deallocator_tests[] =
    {
      cmocka_unit_test(test_OPHeapReleaseHSpan_1Page),
    };

  return cmocka_run_group_tests(deallocator_tests, NULL, NULL);
}

/* deallocator_test.c ends here */
