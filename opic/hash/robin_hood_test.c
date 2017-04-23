/* robin_hood_test.c ---
 *
 * Filename: robin_hood_test.c
 * Description:
 * Author: Felix Chern
 * Maintainer:
 * Copyright: (c) 2017 Felix Chern
 * Created: Sat Apr 22 16:53:56 2017 (-0700)
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

#include "robin_hood.h"

#define TEST_OBJECTS (1 << 15)

static int objcnt = 0;
static uint8_t objmap[TEST_OBJECTS];

void ResetObjcnt(void)
{
  objcnt = 0;
}

void ResetObjmap(void)
{
  memset(objmap, 0x00, sizeof(objmap));
}

void CountObjects(void* keyval, size_t keysize, size_t valsize, void* ctx)
{
  objcnt++;
}

void CheckObjects(void* keyval, size_t keysize, size_t valsize, void* ctx)
{
  int* key = (int*)keyval;
  objmap[*key] = 1;
}

static void
test_RHHNew(void** context)
{
}

static void
test_BasicInsert(void** context)
{
  OPHeap* heap;
  RobinHoodHash* rhh;

  assert_true(OPHeapNew(&heap));
  assert_true(RHHNew(heap, &rhh, TEST_OBJECTS,
                     0.95, sizeof(int), 0));
  for (int i = 0; i < TEST_OBJECTS; i++)
    {
      RHHPut(rhh, &i, NULL);
    }
  RHHPrintStat(rhh);
  assert_int_equal(TEST_OBJECTS, RHHObjcnt(rhh));
  ResetObjcnt();
  RHHIterate(rhh, CountObjects, NULL);
  assert_int_equal(TEST_OBJECTS, objcnt);
  ResetObjmap();
  RHHIterate(rhh, CheckObjects, NULL);
  for (int i = 0; i < TEST_OBJECTS; i++)
    {
      // printf("checking i = %d\n", i);
      assert_int_equal(1, objmap[i]);
    }
  RHHDestroy(rhh);
  OPHeapDestroy(heap);
}

static void
test_BasicDelete(void** context)
{
  OPHeap* heap;
  RobinHoodHash* rhh;

  assert_true(OPHeapNew(&heap));
  assert_true(RHHNew(heap, &rhh, TEST_OBJECTS,
                     0.95, sizeof(int), 0));
  for (int i = 0; i < TEST_OBJECTS; i++)
    {
      RHHPut(rhh, &i, NULL);
    }
  assert_int_equal(TEST_OBJECTS, RHHObjcnt(rhh));

  for (int i = 0; i < TEST_OBJECTS; i++)
    {
      assert_non_null(RHHDelete(rhh, &i));
    }
  assert_int_equal(0, RHHObjcnt(rhh));
  RHHDestroy(rhh);
  OPHeapDestroy(heap);
}

static void
test_DistributionForUpdate(void** context)
{
  OPHeap* heap;
  RobinHoodHash* rhh;
  int key;

  assert_true(OPHeapNew(&heap));
  assert_true(RHHNew(heap, &rhh, TEST_OBJECTS,
                     0.80, sizeof(int), 0));

  for (int i = 0; i < TEST_OBJECTS; i++)
    {
      RHHPut(rhh, &i, NULL);
    }
  assert_int_equal(TEST_OBJECTS, RHHObjcnt(rhh));
  // TODO Change API to test the highest probe
  RHHPrintStat(rhh);

  for (int i = TEST_OBJECTS; i < TEST_OBJECTS*40; i++)
    {
      key = i - TEST_OBJECTS;
      RHHDelete(rhh, &key);
      RHHPut(rhh, &i, NULL);
    }
  RHHPrintStat(rhh);
  RHHDestroy(rhh);
  OPHeapDestroy(heap);
}

int
main (void)
{
  const struct CMUnitTest rhh_tests[] =
    {
      cmocka_unit_test(test_RHHNew),
      cmocka_unit_test(test_BasicInsert),
      cmocka_unit_test(test_BasicDelete),
      cmocka_unit_test(test_DistributionForUpdate),
    };

  return cmocka_run_group_tests(rhh_tests, NULL, NULL);
}

/* robin_hood_test.c ends here */
