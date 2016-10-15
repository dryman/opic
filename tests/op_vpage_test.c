/* op_vpage_test.c --- 
 * 
 * Filename: op_vpage_test.c
 * Description: 
 * Author: Felix Chern
 * Maintainer: 
 * Copyright: (c) 2016 Felix Chern
 * Created: Wed Oct 12 21:39:56 2016 (-0700)
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
#include <cmocka.h>
#include <stdint.h>
#include "opic/malloc/op_vpage.h"
#include <sys/mman.h>

static void vpage_init_test(void **state)
{
  //OPVPageInit(NULL);
  
}


int main(void)
{
  const struct CMUnitTest vpage_tests[] =
    {
      cmocka_unit_test(vpage_init_test),
    };
  
  return cmocka_run_group_tests(vpage_tests, NULL, NULL);
}

/* op_vpage_test.c ends here */
