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

int
main (void)
{
  const struct CMUnitTest allocator_tests[] =
    {
      cmocka_unit_test(test_OPHeapObtainHPage_FullSize),
      cmocka_unit_test(test_OPHeapObtainHPage_SmallSize),
    };

  return cmocka_run_group_tests(allocator_tests, NULL, NULL);
}

/* allocator_test.c ends here */
