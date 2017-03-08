/* lookup_helper_test.c ---
 *
 * Filename: lookup_helper_test.c
 * Description:
 * Author: Felix Chern
 * Maintainer:
 * Copyright: (c) 2016 Felix Chern
 * Created: Sun Mar  5 16:04:06 2017 (-0800)
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
#include <cmocka.h>

#include "magic.h"
#include "inline_aux.h"
#include "lookup_helper.h"
#include "init_helper.h"

static void
test_ObtainOPHeap(void** state)
{
  uintptr_t base, header, inner, boundary, out_of_reach;
  OPHeap* heap;

  assert_true(OPHeapNew(&heap));

  base = (uintptr_t)heap;
  header = (uintptr_t)&heap->hpage;
  inner = base + HPAGE_SIZE * 100;
  boundary = base + OPHEAP_SIZE - 1;
  out_of_reach = base + OPHEAP_SIZE;

  assert_ptr_equal(heap, ObtainOPHeap((void*)base));
  assert_ptr_equal(heap, ObtainOPHeap((void*)header));
  assert_ptr_equal(heap, ObtainOPHeap((void*)inner));
  assert_ptr_equal(heap, ObtainOPHeap((void*)boundary));
  assert_ptr_not_equal(heap, ObtainOPHeap((void*)out_of_reach));

  OPHeapDestroy(heap);
}

static void
test_ObtainHPage(void** state)
{
  uintptr_t heap_base, first_hpage, second_hpage;
  OPHeap* heap;

  assert_true(OPHeapNew(&heap));

  heap_base = (uintptr_t)heap;
  first_hpage = (uintptr_t)&heap->hpage;
  second_hpage = heap_base + HPAGE_SIZE;

  assert_ptr_equal
    (first_hpage, ObtainHPage((void*)heap_base));
  assert_ptr_equal
    (first_hpage, ObtainHPage((void*)(heap_base + 10)));
  assert_ptr_equal
    (first_hpage, ObtainHPage((void*)(heap_base + 4096)));
  assert_ptr_equal
    (first_hpage, ObtainHPage((void*)(heap_base + HPAGE_SIZE - 1)));
  assert_ptr_equal
    (first_hpage, ObtainHPage((void*)(first_hpage)));

  assert_ptr_equal
    (second_hpage,
     ObtainHPage(((void*)heap_base + HPAGE_SIZE)));
  assert_ptr_equal
    (second_hpage,
     ObtainHPage((void*)(heap_base + HPAGE_SIZE + 10)));
  assert_ptr_equal
    (second_hpage,
     ObtainHPage((void*)(heap_base + HPAGE_SIZE + 4096)));
  assert_ptr_equal
    (second_hpage,
     ObtainHPage((void*)(heap_base + HPAGE_SIZE*2 - 1)));
  assert_ptr_equal(second_hpage, ObtainHPage((void*)second_hpage));

  OPHeapDestroy(heap);
}

static void
test_ObtainHugeSpanPtr_fristBMap(void** state)
{
  OPHeap* heap;
  uintptr_t heap_base, first_hpage, second_hpage, isolated_hpage, hblob;

  assert_true(OPHeapNew(&heap));

  // test first hpage
  first_hpage = (uintptr_t)&heap->hpage;
  heap_base = (uintptr_t)heap;
  heap->occupy_bmap[0] = 0x01;
  heap->header_bmap[0] = 0x01;

  assert_ptr_equal
    (first_hpage,
     ObtainHugeSpanPtr((void*)(heap_base))
     .hpage);
  assert_ptr_equal
    (first_hpage,
     ObtainHugeSpanPtr((void*)(heap_base + 10))
     .hpage);
  assert_ptr_equal
    (first_hpage,
     ObtainHugeSpanPtr((void*)(heap_base + 4096))
     .hpage);
  assert_ptr_equal
    (first_hpage,
     ObtainHugeSpanPtr((void*)(heap_base + HPAGE_SIZE - 1))
     .hpage);

  heap->occupy_bmap[0] = 0x03;
  heap->header_bmap[0] = 0x03;
  second_hpage = heap_base + HPAGE_SIZE;
  assert_ptr_equal
    (first_hpage,
     ObtainHugeSpanPtr((void*)(heap_base + HPAGE_SIZE - 1))
     .hpage);
  assert_ptr_equal
    (second_hpage,
     ObtainHugeSpanPtr((void*)(heap_base + HPAGE_SIZE))
     .hpage);
  assert_ptr_equal
    (second_hpage,
     ObtainHugeSpanPtr((void*)(heap_base + HPAGE_SIZE + 10))
     .hpage);
  assert_ptr_equal
    (second_hpage,
     ObtainHugeSpanPtr((void*)(heap_base + HPAGE_SIZE + 4096))
     .hpage);
  assert_ptr_equal
    (second_hpage,
     ObtainHugeSpanPtr((void*)(heap_base + 2 * HPAGE_SIZE - 1))
     .hpage);

  heap->occupy_bmap[0] = 0x13;
  heap->header_bmap[0] = 0x13;
  isolated_hpage = heap_base + 4 * HPAGE_SIZE;
  assert_ptr_equal
    (isolated_hpage,
     ObtainHugeSpanPtr((void*)(heap_base + 4 * HPAGE_SIZE))
     .hpage);
  assert_ptr_equal
    (isolated_hpage,
     ObtainHugeSpanPtr((void*)(heap_base + 5 * HPAGE_SIZE - 1))
     .hpage);

  heap->occupy_bmap[0] = 0xFFFF3;
  heap->header_bmap[0] = 0x13;
  hblob = heap_base + 4 * HPAGE_SIZE;
  assert_ptr_equal
    (hblob,
     ObtainHugeSpanPtr((void*)(heap_base + 4 * HPAGE_SIZE))
     .hpage);
  assert_ptr_equal
    (hblob,
     ObtainHugeSpanPtr((void*)(heap_base + 8 * HPAGE_SIZE))
     .hpage);
  assert_ptr_equal
    (hblob,
     ObtainHugeSpanPtr((void*)(heap_base + 20 * HPAGE_SIZE - 1))
     .hpage);

  OPHeapDestroy(heap);
}

static void
test_ObtainHugeSpanPtr_crossBMap(void** state)
{
  OPHeap* heap;
  uintptr_t heap_base, hblob;

  assert_true(OPHeapNew(&heap));

  heap_base = (uintptr_t)heap;
  hblob = heap_base + 4 * HPAGE_SIZE;
  heap->occupy_bmap[0] = ~0UL;
  heap->occupy_bmap[1] = 0x01;
  heap->header_bmap[0] = 0x1F;
  assert_ptr_equal
    (hblob,
     ObtainHugeSpanPtr((void*)(heap_base + 4 * HPAGE_SIZE))
     .hpage);
  assert_ptr_equal
    (hblob,
     ObtainHugeSpanPtr((void*)(heap_base + 64 * HPAGE_SIZE - 1))
     .hpage);
  assert_ptr_equal
    (hblob,
     ObtainHugeSpanPtr((void*)(heap_base + 64 * HPAGE_SIZE))
     .hpage);
  assert_ptr_equal
    (hblob,
     ObtainHugeSpanPtr((void*)(heap_base + 65 * HPAGE_SIZE - 1))
     .hpage);

  heap->occupy_bmap[1] = ~0UL;
  heap->occupy_bmap[2] = ~0UL;
  heap->occupy_bmap[3] = ~0UL;
  heap->occupy_bmap[4] = 0x01;
  assert_ptr_equal
    (hblob,
     ObtainHugeSpanPtr((void*)(heap_base + 4 * 64 * HPAGE_SIZE))
     .hpage);
  OPHeapDestroy(heap);
}

static void
test_HPageObtainSmallSpanPtr(void** context)
{
  OPHeap* heap;
  HugePage* hpage;
  uintptr_t heap_base, hpage_base,
    first_uspan, isolated_uspan, cross_bmap_uspan;

  assert_true(OPHeapNew(&heap));
  heap_base = (uintptr_t)heap;
  hpage_base = heap_base + HPAGE_SIZE;
  hpage = (HugePage*)hpage_base;

  hpage->occupy_bmap[0] = 0x10FF;
  hpage->header_bmap[0] = 0x1001;
  hpage->occupy_bmap[1] = ~0UL;
  hpage->header_bmap[1] = 0x1F;
  hpage->occupy_bmap[2] = ~0UL;

  first_uspan = hpage_base + sizeof(HugePage);
  isolated_uspan = hpage_base + 12 * SPAGE_SIZE;
  cross_bmap_uspan = hpage_base + 68 * SPAGE_SIZE;

  assert_ptr_equal
    (first_uspan,
     HPageObtainSmallSpanPtr
     (hpage,
      (void*)(hpage_base))
     .uspan);
  assert_ptr_equal
    (first_uspan,
     HPageObtainSmallSpanPtr
     (hpage,
      (void*)(hpage_base + SPAGE_SIZE))
     .uspan);
  assert_ptr_equal
    (first_uspan,
     HPageObtainSmallSpanPtr
     (hpage,
      (void*)(hpage_base + SPAGE_SIZE * 8 - 1))
     .uspan);

  assert_ptr_equal
    (isolated_uspan,
     HPageObtainSmallSpanPtr
     (hpage,
      (void*)(hpage_base + SPAGE_SIZE * 12))
     .uspan);
  assert_ptr_equal
    (isolated_uspan,
     HPageObtainSmallSpanPtr
     (hpage,
      (void*)(hpage_base + SPAGE_SIZE * 13 - 1))
     .uspan);

  assert_ptr_equal
    (cross_bmap_uspan,
     HPageObtainSmallSpanPtr
     (hpage,
      (void*)(hpage_base + SPAGE_SIZE * 68))
     .uspan);
  assert_ptr_equal
    (cross_bmap_uspan,
     HPageObtainSmallSpanPtr
     (hpage,
      (void*)(hpage_base + SPAGE_SIZE * 127))
     .uspan);
  assert_ptr_equal
    (cross_bmap_uspan,
     HPageObtainSmallSpanPtr
     (hpage,
      (void*)(hpage_base + SPAGE_SIZE * 128))
     .uspan);
  assert_ptr_equal
    (cross_bmap_uspan,
     HPageObtainSmallSpanPtr
     (hpage,
      (void*)(hpage_base + SPAGE_SIZE * 64 * 3 - 1))
     .uspan);

  OPHeapDestroy(heap);
}

int
main (void)
{
  const struct CMUnitTest lookup_helper_tests[] =
    {
      cmocka_unit_test(test_ObtainOPHeap),
      cmocka_unit_test(test_ObtainHPage),
      cmocka_unit_test(test_ObtainHugeSpanPtr_fristBMap),
      cmocka_unit_test(test_ObtainHugeSpanPtr_crossBMap),
      cmocka_unit_test(test_HPageObtainSmallSpanPtr),
    };

  return cmocka_run_group_tests(lookup_helper_tests, NULL, NULL);
}
/* lookup_helper_test.c ends here */
