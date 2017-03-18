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

int
main (void)
{
  /*
  const struct CMUnitTest allocator_tests[] =
    {
      cmocka_unit_test(test_OPHeapObtainHPage_FullSize),
      cmocka_unit_test(test_OPHeapObtainHPage_SmallSize),
      cmocka_unit_test(test_OPHeapObtainHBlob_Small),
      cmocka_unit_test(test_OPHeapObtainHBlob_Large),
    };

  return cmocka_run_group_tests(allocator_tests, NULL, NULL);
  */
}

/* deallocator_test.c ends here */
