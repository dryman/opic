/* pascal_robin_hood_test.c ---
 *
 * Filename: pascal_robin_hood_test.c
 * Description:
 * Author: Felix Chern
 * Maintainer:
 * Created: Sun May 21 15:56:43 2017 (-0700)
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
 * it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this program.  If not, see
 * <http://www.gnu.org/licenses/>.
 */

/* Code: */


#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdint.h>
#include <sys/mman.h>
#include <string.h>
#include <cmocka.h>

#include "opic/common/op_log.h"
#include "pascal_robin_hood.h"

OP_LOGGER_FACTORY(logger, "opic.hash.pascal_robin_hood_test");

// On very small table size, we may have cycles
// for example TEST_OBJECTS = 12 we get into infinite loop..
// I had one work around that is having a small cache that
// record past certain number of elements, and check if the
// current element exists in the cache. But this seems to be
// costy.
#define TEST_OBJECTS (1<<15)

static char uuid [] = "!!!!!!--!!!!!!--!!!!!!--!!!!!!--";

static int objcnt = 0;

size_t MutateUUID(int idx)
{
  size_t keylen;
  for (int j = 0; j < 6; j++)
    {
      int k = idx >> j*6;
      k %= 64;
      uuid[j] = 0x21 + k;
      uuid[j+8] = 0x21 + k;
      uuid[j+16] = 0x21 + k;
      uuid[j+24] = 0x21 + k;
    }
  keylen = 8 + idx % 24;
  return keylen;
}

void ResetObjcnt(void)
{
  objcnt = 0;
}

void CountObjects(void* key, void* val,
                  size_t keysize, size_t valsize, void* ctx)
{
  objcnt++;
}

static void
test_RHHNew(void** context)
{
  OPHeap* heap;
  PascalRobinHoodHash* rhh;
  assert_true(OPHeapNew(&heap));
  assert_true(PRHHNew(heap, &rhh, TEST_OBJECTS,
                      0.95, 0, 0));
  PRHHDestroy(rhh);
  assert_true(PRHHNew(heap, &rhh, TEST_OBJECTS,
                      0.95, 10, 0));
  PRHHDestroy(rhh);
  OPHeapDestroy(heap);
}

static void
test_BasicInsert(void** context)
{
  OPHeap* heap;
  PascalRobinHoodHash* rhh;
  size_t keylen;

  OP_LOG_INFO(logger, "Starting basic insert");
  assert_true(OPHeapNew(&heap));
  assert_true(PRHHNew(heap, &rhh, 20, 0.80, 0, 0));
  OP_LOG_DEBUG(logger, "PRHH addr %p", rhh);

  for (int i = 0; i < TEST_OBJECTS; i++)
    {
      keylen = MutateUUID(i);
      //OP_LOG_DEBUG(logger, "Inserting %s with len %zu", uuid, keylen);
      PRHHInsert(rhh, uuid, keylen, NULL);
    }
  PRHHPrintStat(rhh);
  assert_int_equal(TEST_OBJECTS, PRHHObjcnt(rhh));
  ResetObjcnt();
  PRHHIterate(rhh, CountObjects, NULL);
  assert_int_equal(TEST_OBJECTS, objcnt);
  for (int i = 0; i < TEST_OBJECTS; i++)
    {
      keylen = MutateUUID(i);
      //OP_LOG_DEBUG(logger, "Querying %s with len %zu", uuid, keylen);
      assert_non_null(PRHHGet(rhh, uuid, keylen));
    }
  PRHHDestroy(rhh);
  OPHeapDestroy(heap);
}

static void
test_BasicInsertWithKeyInline(void** context)
{
  OPHeap* heap;
  PascalRobinHoodHash* rhh;
  size_t keylen;

  OP_LOG_INFO(logger, "Starting basic insert");
  assert_true(OPHeapNew(&heap));
  assert_true(PRHHNew(heap, &rhh, 20, 0.80, 8, 0));
  OP_LOG_DEBUG(logger, "PRHH addr %p", rhh);

  for (int i = 0; i < TEST_OBJECTS; i++)
    {
      keylen = MutateUUID(i);
      //OP_LOG_DEBUG(logger, "Inserting %s with len %zu", uuid, keylen);
      PRHHInsert(rhh, uuid, keylen, NULL);
    }
  PRHHPrintStat(rhh);
  assert_int_equal(TEST_OBJECTS, PRHHObjcnt(rhh));
  ResetObjcnt();
  PRHHIterate(rhh, CountObjects, NULL);
  assert_int_equal(TEST_OBJECTS, objcnt);
  for (int i = 0; i < TEST_OBJECTS; i++)
    {
      keylen = MutateUUID(i);
      //OP_LOG_DEBUG(logger, "Querying %s with len %zu", uuid, keylen);
      assert_non_null(PRHHGet(rhh, uuid, keylen));
    }
  PRHHDestroy(rhh);
  OPHeapDestroy(heap);
}

static void
test_BasicDelete(void** context)
{
  OPHeap* heap;
  PascalRobinHoodHash* rhh;
  size_t keylen;

  assert_true(OPHeapNew(&heap));
  assert_true(PRHHNew(heap, &rhh, TEST_OBJECTS, 0.95, 0, 0));
  for (int i = 0; i < TEST_OBJECTS; i++)
    {
      keylen = MutateUUID(i);
      PRHHInsert(rhh, uuid, keylen, NULL);
    }
  assert_int_equal(TEST_OBJECTS, PRHHObjcnt(rhh));

  for (int i = 0; i < TEST_OBJECTS; i++)
    {
      keylen = MutateUUID(i);
      //OP_LOG_DEBUG(logger, "Deleting %s with len %zu", uuid, keylen);
      assert_non_null(PRHHDelete(rhh, uuid, keylen));
    }
  assert_int_equal(0, PRHHObjcnt(rhh));
  ResetObjcnt();
  PRHHIterate(rhh, CountObjects, NULL);
  assert_int_equal(0, objcnt);
  PRHHDestroy(rhh);
  OPHeapDestroy(heap);
}

static void
test_BasicDeleteWithKeyInline(void** context)
{
  OPHeap* heap;
  PascalRobinHoodHash* rhh;
  size_t keylen;

  assert_true(OPHeapNew(&heap));
  assert_true(PRHHNew(heap, &rhh, TEST_OBJECTS, 0.95, 8, 0));
  for (int i = 0; i < TEST_OBJECTS; i++)
    {
      keylen = MutateUUID(i);
      PRHHInsert(rhh, uuid, keylen, NULL);
    }
  assert_int_equal(TEST_OBJECTS, PRHHObjcnt(rhh));

  for (int i = 0; i < TEST_OBJECTS; i++)
    {
      keylen = MutateUUID(i);
      //OP_LOG_DEBUG(logger, "Deleting %s with len %zu", uuid, keylen);
      assert_non_null(PRHHDelete(rhh, uuid, keylen));
    }
  assert_int_equal(0, PRHHObjcnt(rhh));
  ResetObjcnt();
  PRHHIterate(rhh, CountObjects, NULL);
  assert_int_equal(0, objcnt);
  PRHHDestroy(rhh);
  OPHeapDestroy(heap);
}

static void
test_DistributionForUpdate(void** context)
{
  OPHeap* heap;
  PascalRobinHoodHash* rhh;
  size_t keylen;

  assert_true(OPHeapNew(&heap));
  assert_true(PRHHNew(heap, &rhh, TEST_OBJECTS,
                      0.70, 0, 0));

  for (int i = 0; i < TEST_OBJECTS; i++)
    {
      keylen = MutateUUID(i);
      PRHHInsert(rhh, uuid, keylen, NULL);
    }
  assert_int_equal(TEST_OBJECTS, PRHHObjcnt(rhh));
  // TODO Change API to test the highest probe
  PRHHPrintStat(rhh);

  for (int i = 0; i < TEST_OBJECTS*9; i++)
    {
      keylen = MutateUUID(i);
      // OP_LOG_DEBUG(logger, "Deleting %s with len %zu", uuid, keylen);
      PRHHDelete(rhh, uuid, keylen);
      keylen = MutateUUID(i+TEST_OBJECTS);
      // OP_LOG_DEBUG(logger, "Inserting %s with len %zu", uuid, keylen);
      PRHHInsert(rhh, uuid, keylen, NULL);
    }
  PRHHPrintStat(rhh);
  PRHHDestroy(rhh);
  OPHeapDestroy(heap);
}

static void
test_Upsert(void** context)
{
  OPHeap* heap;
  PascalRobinHoodHash* rhh;
  size_t keylen;
  int* val;
  bool is_duplicate;

  OP_LOG_INFO(logger, "Starting basic insert");
  assert_true(OPHeapNew(&heap));
  assert_true(PRHHNew(heap, &rhh, 20, 0.80, 0, sizeof(int)));
  OP_LOG_DEBUG(logger, "PRHH addr %p", rhh);

  for (int i = 0; i < TEST_OBJECTS; i++)
    {
      keylen = MutateUUID(i);
      assert_true(PRHHUpsert(rhh, uuid, keylen, (void**)&val, &is_duplicate));
      assert_false(is_duplicate);
      *val = i;
    }

  for (int i = 0; i < TEST_OBJECTS; i++)
    {
      keylen = MutateUUID(i);
      assert_true(PRHHUpsert(rhh, uuid, keylen, (void**)&val, &is_duplicate));
      assert_true(is_duplicate);
      assert_int_equal(i, *val);
    }
  PRHHDestroy(rhh);
  OPHeapDestroy(heap);
}

int
main (void)
{
  const struct CMUnitTest prhh_tests[] =
    {
      cmocka_unit_test(test_RHHNew),
      cmocka_unit_test(test_BasicInsert),
      cmocka_unit_test(test_BasicDelete),
      cmocka_unit_test(test_BasicInsertWithKeyInline),
      cmocka_unit_test(test_BasicDeleteWithKeyInline),
      cmocka_unit_test(test_DistributionForUpdate),
      cmocka_unit_test(test_Upsert),
    };

  return cmocka_run_group_tests(prhh_tests, NULL, NULL);
}

/* pascal_robin_hood_test.c ends here */
