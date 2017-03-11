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
test_HPageInit(void** ctx)
{
  OPHeap* heap;
  HugePage* hpage;

  assert_true(OPHeapNew(&heap));

  OPHeapDestroy(heap);
}

static void
test_USpanInit(void** ctx)
{
}

static void
test_HPageEmptiedBMaps(void** ctx)
{
}

static void
test_USpanEmptiedBMap(void** ctx)
{
}

int
main (void)
{
  const struct CMUnitTest init_helper_tests[] =
    {
      cmocka_unit_test(test_HPageInit),
      cmocka_unit_test(test_USpanInit),
      cmocka_unit_test(test_HPageEmptiedBMaps),
      cmocka_unit_test(test_USpanEmptiedBMap),
    };

  return cmocka_run_group_tests(init_helper_tests, NULL, NULL);
}

/* init_helper_test.c ends here */
