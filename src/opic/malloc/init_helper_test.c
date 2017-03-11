/* init_helper_test.c ---
 *
 * Filename: init_helper_test.c
 * Description:
 * Author: Felix Chern
 * Maintainer:
 * Copyright: (c) 2016 Felix Chern
 * Created: Wed Mar  8 20:07:16 2017 (-0800)
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
test_HPageInit(void** context)
{
  OPHeap* heap;
  uintptr_t heap_base;
  OPHeapCtx ctx;
  HugePage* hpage;
  Magic magic = {};
  uint64_t occupy_bmap[8] = {0};
  uint64_t header_bmap[8] = {0};

  assert_true(OPHeapNew(&heap));
  heap_base = (uintptr_t)heap;
  magic.raw_hpage.pattern = RAW_HPAGE_PATTERN;
  ctx.hspan.hpage = &heap->hpage;

  HPageInit(&ctx, magic);
  hpage = ctx.hspan.hpage;

  assert_memory_equal(&magic, &hpage->magic, sizeof(Magic));
  assert_int_equal(0, hpage->pcard);
  // TODO: skip state test for now

  /*
   * sizeof(OPHeap) = 391864;
   * sizeof(HugePage) = 144;
   * (391864 + 144) = 4096 * 95 + 2888
   * => 96 bit spaces to occupy
   * 96 = 64 + 32
   */
  occupy_bmap[0] = ~0UL;
  occupy_bmap[1] = (1UL << 32) - 1;
  assert_memory_equal(occupy_bmap, hpage->occupy_bmap, 8 * sizeof(uint64_t));
  assert_memory_equal(header_bmap, hpage->header_bmap, 8 * sizeof(uint64_t));

  ctx.hspan.uintptr = heap_base + HPAGE_SIZE;
  HPageInit(&ctx, magic);
  hpage = ctx.hspan.hpage;
  assert_memory_equal(&magic, &hpage->magic, sizeof(Magic));
  assert_int_equal(0, hpage->pcard);

  occupy_bmap[0] = occupy_bmap[1] = 0UL;
  assert_memory_equal(occupy_bmap, hpage->occupy_bmap, 8 * sizeof(uint64_t));
  assert_memory_equal(header_bmap, hpage->header_bmap, 8 * sizeof(uint64_t));

  OPHeapDestroy(heap);
}

static void
test_USpanInit(void** context)
{
}

int
main (void)
{
  const struct CMUnitTest init_helper_tests[] =
    {
      cmocka_unit_test(test_HPageInit),
      cmocka_unit_test(test_USpanInit),
    };

  return cmocka_run_group_tests(init_helper_tests, NULL, NULL);
}

/* init_helper_test.c ends here */
