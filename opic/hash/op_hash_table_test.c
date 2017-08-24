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

#include "opic/common/op_log.h"
#include "op_hash_table.h"

OP_LOGGER_FACTORY(logger, "opic.hash.robin_hood_test");

#define TEST_OBJECTS (1<<15)
#define SMALL_TEST_OBJECTS 20

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

void CountObjects(void* key, void* val,
                  size_t keysize, size_t valsize, void* ctx)
{
  objcnt++;
}

void CheckObjects(void* key, void* val,
                  size_t keysize, size_t valsize, void* ctx)
{
  int* intkey = key;
  objmap[*intkey] = 1;
}

static void
test_HTNew(void** context)
{
  OPHeap* heap;
  OPHashTable* table;
  heap = OPHeapOpenTmp();
  table = HTNew(heap, TEST_OBJECTS, 0.95, sizeof(int), 0);
  HTDestroy(table);
  OPHeapClose(heap);
}

static void
test_BasicInsert(void** context)
{
  OPHeap* heap;
  OPHashTable* table;

  OP_LOG_INFO(logger, "Starting basic insert");
  heap = OPHeapOpenTmp();
  table = HTNew(heap, 20, 0.80, sizeof(int), 0);
  OP_LOG_DEBUG(logger, "HT addr %p", table);
  for (int i = 0; i < TEST_OBJECTS; i++)
    {
      HTInsert(table, &i, NULL);
    }
  HTPrintStat(table);
  assert_int_equal(TEST_OBJECTS, HTObjcnt(table));
  ResetObjcnt();
  HTIterate(table, CountObjects, NULL);
  assert_int_equal(TEST_OBJECTS, objcnt);
  ResetObjmap();
  HTIterate(table, CheckObjects, NULL);
  for (int i = 0; i < TEST_OBJECTS; i++)
    {
      assert_int_equal(1, objmap[i]);
    }

  // test mismatch objects
  for (int i = TEST_OBJECTS; i < TEST_OBJECTS*2; i++)
    {
      assert_null(HTGet(table, &i));
    }

  HTDestroy(table);
  OPHeapClose(heap);
}

static void
test_BasicDelete(void** context)
{
  OPHeap* heap;
  OPHashTable* table;
  int i;

  heap = OPHeapOpenTmp();
  table = HTNew(heap,TEST_OBJECTS, 0.95, sizeof(int), 0);
  for (i = 0; i < TEST_OBJECTS; i++)
    {
      HTInsert(table, &i, NULL);
    }
  assert_int_equal(TEST_OBJECTS, HTObjcnt(table));

  for (i = 0; i < TEST_OBJECTS; i++)
    {
      assert_non_null(HTGet(table, &i));
    }

  for (i = 0; i < TEST_OBJECTS; i++)
    {
      assert_non_null(HTDelete(table, &i));
    }
  assert_int_equal(0, HTObjcnt(table));
  ResetObjcnt();
  HTIterate(table, CountObjects, NULL);
  assert_int_equal(0, objcnt);
  HTDestroy(table);
  OPHeapClose(heap);
}

static void
test_DistributionForUpdate(void** context)
{
  OPHeap* heap;
  OPHashTable* table;
  int key;

  heap = OPHeapOpenTmp();
  table = HTNew(heap, TEST_OBJECTS, 0.70, sizeof(int), 0);

  for (int i = 0; i < TEST_OBJECTS; i++)
    {
      HTInsert(table, &i, NULL);
    }
  assert_int_equal(TEST_OBJECTS, HTObjcnt(table));
  // TODO Change API to test the highest probe
  HTPrintStat(table);

  for (int i = TEST_OBJECTS; i < TEST_OBJECTS*10; i++)
    {
      key = i - TEST_OBJECTS;
      HTDelete(table, &key);
      HTInsert(table, &i, NULL);
    }
  HTPrintStat(table);
  HTDestroy(table);
  OPHeapClose(heap);
}

static void
test_Upsert(void** context)
{
  OPHeap* heap;
  OPHashTable* table;
  int* val;
  bool is_duplicate;

  heap = OPHeapOpenTmp();
  table = HTNew(heap, 20, 0.7, sizeof(int), sizeof(int));

  for (int i = 0; i < TEST_OBJECTS; i++)
    {
      assert_true(HTUpsert(table, &i, (void**)&val, &is_duplicate));
      assert_false(is_duplicate);
      *val = i;
    }

  for (int i = 0; i < TEST_OBJECTS; i++)
    {
      assert_true(HTUpsert(table, &i, (void**)&val, &is_duplicate));
      assert_true(is_duplicate);
      assert_int_equal(i, *val);
    }
  HTDestroy(table);
  OPHeapClose(heap);
}

static void
test_BasicInsertSmall(void** context)
{
  OPHeap* heap;
  OPHashTable* table;

  OP_LOG_INFO(logger, "Starting basic insert");
  heap = OPHeapOpenTmp();
  table = HTNew(heap, 20, 0.80, sizeof(int), 0);
  OP_LOG_DEBUG(logger, "HT addr %p", table);
  for (int i = 0; i < SMALL_TEST_OBJECTS; i++)
    {
      HTInsert(table, &i, NULL);
    }
  HTPrintStat(table);
  assert_int_equal(SMALL_TEST_OBJECTS, HTObjcnt(table));
  ResetObjcnt();
  HTIterate(table, CountObjects, NULL);
  assert_int_equal(SMALL_TEST_OBJECTS, objcnt);

  // test mismatch objects
  for (int i = SMALL_TEST_OBJECTS; i < SMALL_TEST_OBJECTS*2; i++)
    {
      assert_null(HTGet(table, &i));
    }
  HTDestroy(table);
  OPHeapClose(heap);
}

static void
test_BasicDeleteSmall(void** context)
{
  OPHeap* heap;
  OPHashTable* table;
  int i;

  heap = OPHeapOpenTmp();
  table = HTNew(heap, SMALL_TEST_OBJECTS, 0.95, sizeof(int), 0);
  for (i = 0; i < SMALL_TEST_OBJECTS; i++)
    {
      HTInsert(table, &i, NULL);
    }
  assert_int_equal(SMALL_TEST_OBJECTS, HTObjcnt(table));

  for (i = 0; i < SMALL_TEST_OBJECTS; i++)
    {
      assert_non_null(HTGet(table, &i));
    }

  for (i = 0; i < SMALL_TEST_OBJECTS; i++)
    {
      assert_non_null(HTDelete(table, &i));
    }
  assert_int_equal(0, HTObjcnt(table));
  ResetObjcnt();
  HTIterate(table, CountObjects, NULL);
  assert_int_equal(0, objcnt);
  HTDestroy(table);
  OPHeapClose(heap);
}

static void
test_DistributionForUpdateSmall(void** context)
{
  OPHeap* heap;
  OPHashTable* table;
  int key;

  heap = OPHeapOpenTmp();
  table = HTNew(heap, SMALL_TEST_OBJECTS, 0.70, sizeof(int), 0);

  for (int i = 0; i < SMALL_TEST_OBJECTS; i++)
    {
      HTInsert(table, &i, NULL);
    }
  assert_int_equal(SMALL_TEST_OBJECTS, HTObjcnt(table));
  // TODO Change API to test the highest probe
  HTPrintStat(table);

  for (int i = SMALL_TEST_OBJECTS; i < SMALL_TEST_OBJECTS*10; i++)
    {
      key = i - SMALL_TEST_OBJECTS;
      HTDelete(table, &key);
      HTInsert(table, &i, NULL);
    }
  HTPrintStat(table);
  HTDestroy(table);
  OPHeapClose(heap);
}

static void
test_UpsertSmall(void** context)
{
  OPHeap* heap;
  OPHashTable* table;
  int* val;
  bool is_duplicate;

  heap = OPHeapOpenTmp();
  table = HTNew(heap, 20, 0.7, sizeof(int), sizeof(int));

  for (int i = 0; i < SMALL_TEST_OBJECTS; i++)
    {
      assert_true(HTUpsert(table, &i, (void**)&val, &is_duplicate));
      assert_false(is_duplicate);
      *val = i;
    }

  for (int i = 0; i < SMALL_TEST_OBJECTS; i++)
    {
      assert_true(HTUpsert(table, &i, (void**)&val, &is_duplicate));
      assert_true(is_duplicate);
      assert_int_equal(i, *val);
    }
}

static void
test_FunnelInsert(void** context)
{
  OPHeap* heap;
  OPHashTable* table;
  HTFunnel* funnel;

  OP_LOG_INFO(logger, "Starting funnel insert");
  heap = OPHeapOpenTmp();
  table = HTNew(heap, TEST_OBJECTS, 0.80, sizeof(int), 0);
  funnel = HTFunnelNew(table, NULL, 2048, 2048);
  for (int i = 0; i < TEST_OBJECTS; i++)
    {
      HTFunnelInsert(funnel, &i, NULL);
    }
  HTFunnelInsertFlush(funnel);
  HTFunnelDestroy(funnel);
  HTPrintStat(table);
  assert_int_equal(TEST_OBJECTS, HTObjcnt(table));
  ResetObjcnt();
  HTIterate(table, CountObjects, NULL);
  assert_int_equal(TEST_OBJECTS, objcnt);
  ResetObjmap();
  HTIterate(table, CheckObjects, NULL);
  for (int i = 0; i < TEST_OBJECTS; i++)
    {
      assert_int_equal(1, objmap[i]);
    }
  HTDestroy(table);
  OPHeapClose(heap);
}

void upsert_empty_bucket(void* key,
                         void* table_value,
                         void* funnel_value,
                         void* ctx,
                         size_t keysize, size_t valsize,
                         size_t ctxsize, bool is_duplicate)
{
  int* f_val, *ctx_val;
  f_val = (int*)funnel_value;
  ctx_val = (int*)ctx;
  memcpy(table_value, funnel_value, valsize);
  assert_false(is_duplicate);
  assert_int_equal(*f_val, *ctx_val);
}

void upsert_dup_bucket(void* key,
                       void* table_value,
                       void* funnel_value,
                       void* ctx,
                       size_t keysize, size_t valsize,
                       size_t ctxsize, bool is_duplicate)
{
  int* t_val, *f_val;
  assert_true(is_duplicate);
  t_val = (int*)table_value;
  f_val = (int*)funnel_value;
  assert_int_equal(*t_val, *f_val);
  assert_int_equal(0, ctxsize);
}

static void
test_FunnelUpsert(void** context)
{
  OPHeap* heap;
  OPHashTable* table;
  HTFunnel* funnel;

  heap = OPHeapOpenTmp();
  table = HTNew(heap, TEST_OBJECTS, 0.8, sizeof(int), sizeof(int));
  funnel = HTFunnelNew(table, upsert_empty_bucket, 2048, 2048);

  for (int i = 0; i < TEST_OBJECTS; i++)
    {
      HTFunnelUpsert(funnel, &i, &i, &i, sizeof(int));
    }
  HTFunnelUpsertFlush(funnel);
  HTFunnelDestroy(funnel);

  HTPrintStat(table);
  assert_int_equal(TEST_OBJECTS, HTObjcnt(table));
  ResetObjcnt();
  HTIterate(table, CountObjects, NULL);
  assert_int_equal(TEST_OBJECTS, objcnt);
  ResetObjmap();
  HTIterate(table, CheckObjects, NULL);
  for (int i = 0; i < TEST_OBJECTS; i++)
    {
      assert_int_equal(1, objmap[i]);
    }

  funnel = HTFunnelNew(table, upsert_dup_bucket, 2048, 2048);
  for (int i = 0; i < TEST_OBJECTS; i++)
    {
      HTFunnelUpsert(funnel, &i, &i, NULL, 0);
    }
  HTFunnelUpsertFlush(funnel);
  HTFunnelDestroy(funnel);
  HTDestroy(table);
  OPHeapClose(heap);
}

void funnel_count_objects(void* key, void* value, void* ctx,
                          size_t keysize, size_t valsize,
                          size_t ctxsize)
{
  if (!value)
    return;

  objcnt++;
  int* intval = (int*)value;
  int* intctx = (int*)ctx;
  assert_int_equal(*intval, *intctx);
}

void funnel_check_objects(void* key, void* value, void* ctx,
                          size_t keysize, size_t valsize,
                          size_t ctxsize)
{
  if (!value)
    return;

  int* intkey = key;
  objmap[*intkey] = 1;
}

static void
test_FunnelGet(void** context)
{
  OPHeap* heap;
  OPHashTable* table;
  HTFunnel* funnel;

  heap = OPHeapOpenTmp();
  table = HTNew(heap, TEST_OBJECTS, 0.8, sizeof(int), sizeof(int));

  for (int i = 0; i < TEST_OBJECTS; i++)
    {
      HTInsert(table, &i, &i);
    }

  ResetObjcnt();
  funnel = HTFunnelNew(table, funnel_count_objects, 2048, 2048);
  for (int i = 0; i < TEST_OBJECTS; i++)
    {
      HTFunnelGet(funnel, &i, &i, sizeof(int));
    }
  HTFunnelGetFlush(funnel);
  HTFunnelDestroy(funnel);
  assert_int_equal(TEST_OBJECTS, objcnt);

  ResetObjmap();
  funnel = HTFunnelNew(table, funnel_check_objects, 2048, 2048);
  for (int i = 0; i < TEST_OBJECTS; i++)
    {
      HTFunnelGet(funnel, &i, NULL, 0);
    }
  HTFunnelGetFlush(funnel);
  HTFunnelDestroy(funnel);
  for (int i = 0; i < TEST_OBJECTS; i++)
    {
      assert_int_equal(1, objmap[i]);
    }

  // test mismatch object case
  ResetObjcnt();
  funnel = HTFunnelNew(table, funnel_count_objects, 2048, 2048);
  for (int i = TEST_OBJECTS; i < TEST_OBJECTS*2; i++)
    {
      HTFunnelGet(funnel, &i, &i, sizeof(int));
    }
  HTFunnelGetFlush(funnel);
  HTFunnelDestroy(funnel);
  assert_int_equal(0, objcnt);

  ResetObjmap();
  funnel = HTFunnelNew(table, funnel_check_objects, 2048, 2048);
  for (int i = TEST_OBJECTS; i < TEST_OBJECTS*2; i++)
    {
      HTFunnelGet(funnel, &i, NULL, 0);
    }
  HTFunnelGetFlush(funnel);
  HTFunnelDestroy(funnel);
  for (int i = 0; i < TEST_OBJECTS; i++)
    {
      assert_int_equal(0, objmap[i]);
    }

  HTDestroy(table);
  OPHeapClose(heap);
}

static void
test_FunnelDelete(void** context)
{
  OPHeap* heap;
  OPHashTable* table;
  HTFunnel* funnel;

  heap = OPHeapOpenTmp();
  table = HTNew(heap, TEST_OBJECTS, 0.8, sizeof(int), sizeof(int));

  for (int i = 0; i < TEST_OBJECTS; i++)
    {
      HTInsert(table, &i, &i);
    }

  ResetObjmap();
  funnel = HTFunnelNew(table, funnel_check_objects, 2048, 2048);
  for (int i = 0; i < TEST_OBJECTS; i++)
    {
      HTFunnelDelete(funnel, &i, NULL, 0);
    }
  HTFunnelDeleteFlush(funnel);
  HTFunnelDestroy(funnel);
  for (int i = 0; i < TEST_OBJECTS; i++)
    {
      assert_int_equal(1, objmap[i]);
    }
  assert_int_equal(0, HTObjcnt(table));
  ResetObjcnt();
  HTIterate(table, CountObjects, NULL);
  assert_int_equal(0, objcnt);

  HTDestroy(table);
  OPHeapClose(heap);
}

int
main (void)
{
  const struct CMUnitTest table_tests[] =
    {
      cmocka_unit_test(test_HTNew),
      cmocka_unit_test(test_BasicInsert),
      cmocka_unit_test(test_BasicDelete),
      cmocka_unit_test(test_DistributionForUpdate),
      cmocka_unit_test(test_Upsert),
      cmocka_unit_test(test_BasicInsertSmall),
      cmocka_unit_test(test_BasicDeleteSmall),
      cmocka_unit_test(test_DistributionForUpdateSmall),
      cmocka_unit_test(test_UpsertSmall),
      cmocka_unit_test(test_FunnelInsert),
      cmocka_unit_test(test_FunnelUpsert),
      cmocka_unit_test(test_FunnelGet),
      cmocka_unit_test(test_FunnelDelete),
    };

  return cmocka_run_group_tests(table_tests, NULL, NULL);
}

/* robin_hood_test.c ends here */
