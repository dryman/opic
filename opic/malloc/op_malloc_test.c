/* op_malloc_test.c ---
 *
 * Filename: op_malloc_test.c
 * Description:
 * Author: Felix Chern
 * Maintainer:
 * Copyright: (c) 2017 Felix Chern
 * Created: Fri Apr 14 20:10:11 2017 (-0700)
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

#include "opic/malloc/objdef.h"
#include "opic/op_malloc.h"

extern void OPHeapShrinkCopy(OPHeap* heap);

static void
test_OPHeapShrinkShadow(void** context)
{
  OPHeap heap, heap_control;

  heap.hpage_num = HPAGE_BMAP_NUM * 64;
  atomic_store(&heap.occupy_bmap[0], ~0ULL);
  OPHeapShrinkCopy(&heap);

  heap_control.hpage_num = 64;
  memset(heap_control.occupy_bmap, 0xff,
         sizeof(uint64_t) * HPAGE_BMAP_NUM);

  assert_int_equal(heap_control.hpage_num, heap.hpage_num);
  assert_memory_equal(&heap_control.occupy_bmap,
                      &heap.occupy_bmap,
                      sizeof(uint64_t) * HPAGE_BMAP_NUM);

  heap.hpage_num = 96;
  memset(heap.occupy_bmap, 0x00,
         sizeof(uint64_t) * HPAGE_BMAP_NUM);
  memset(heap.occupy_bmap, 0xff, sizeof(uint32_t));
  OPHeapShrinkCopy(&heap);

  heap_control.hpage_num = 32;
  assert_int_equal(heap_control.hpage_num, heap.hpage_num);
  assert_memory_equal(&heap_control.occupy_bmap,
                      &heap.occupy_bmap,
                      sizeof(uint64_t) * HPAGE_BMAP_NUM);

  heap.hpage_num = 96;
  memset(heap.occupy_bmap, 0x00,
         sizeof(uint64_t) * HPAGE_BMAP_NUM);
  atomic_store(&heap.occupy_bmap[0], 1);
  OPHeapShrinkCopy(&heap);

  heap_control.hpage_num = 1;
  assert_int_equal(heap_control.hpage_num, heap.hpage_num);
  assert_memory_equal(&heap_control.occupy_bmap,
                      &heap.occupy_bmap,
                      sizeof(uint64_t) * HPAGE_BMAP_NUM);
}

int
main (void)
{
  const struct CMUnitTest op_malloc_tests[] =
    {
      cmocka_unit_test(test_OPHeapShrinkShadow),
    };

  return cmocka_run_group_tests(op_malloc_tests, NULL, NULL);
}

/* op_malloc_test.c ends here */
