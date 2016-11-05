/* op_pspan_test.c --- 
 * 
 * Filename: op_pspan_test.c
 * Description: 
 * Author: Felix Chern
 * Maintainer: 
 * Copyright: (c) 2016 Felix Chern
 * Created: Sun Oct  9 2016
 * Version: 0.3
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
#include "opic/malloc/op_pspan.h"
#include <sys/mman.h>


static void invalid_address_test(void **state)
{
  assert_null(USpanInit(NULL, 0, 1, 2));
}

static void invalid_object_size(void **state)
{
  void* addr = malloc(1<<12);
  assert_null(USpanInit(addr, 0, 0, 1));
  free(addr);
}

static void invalid_page_cnt(void **state)
{
  void* addr = malloc(1<<12);
  assert_null(USpanInit(addr, 0, 1, 0));
  free(addr);
}

static void obj_size_4byte(void **state)
{
  void* addr = malloc(1<<12);
  UnarySpan* span;
  span = USpanInit(addr, 0, 4, 1<<12);
  assert_int_equal(span->bitmap_cnt, 16);
  assert_int_equal(span->bitmap_headroom, 38);
  assert_int_equal(span->bitmap_padding, 0);
  uint64_t bitmaps [16] = { (1UL << 38)-1 };
  assert_memory_equal(span+1, &bitmaps, sizeof(bitmaps));
  
  free(addr);
}

// TODO(fchern): Use parameterized test or macro
static void obj_size_8byte(void **state)
{
  void* addr = malloc(1<<12);
  UnarySpan* span;
  span = USpanInit(addr, 0, 8, 1<<12);
  assert_int_equal(span->bitmap_cnt, 8);
  assert_int_equal(span->bitmap_headroom, 11);
  assert_int_equal(span->bitmap_padding, 0);
  uint64_t bitmaps_1p [8] = { (1UL << 11)-1 };
  assert_memory_equal(span+1, &bitmaps_1p, sizeof(bitmaps_1p));
  free(addr);
  
  addr = malloc(2<<12);
  span = USpanInit(addr, 0, 8, 2<<12);
  assert_int_equal(span->bitmap_cnt, 16);
  assert_int_equal(span->bitmap_headroom, 19);
  assert_int_equal(span->bitmap_padding, 0);
  uint64_t bitmaps_2p [16] = { (1UL << 19)-1 };
  assert_memory_equal(span+1, &bitmaps_2p, sizeof(bitmaps_2p));
  free(addr);

  addr = malloc(3<<12);
  span = USpanInit(addr, 0, 8, 3<<12);
  assert_int_equal(span->bitmap_cnt, 24);
  assert_int_equal(span->bitmap_headroom, 27);
  assert_int_equal(span->bitmap_padding, 0);
  uint64_t bitmaps_3p [24] = { (1UL << 27)-1 };
  assert_memory_equal(span+1, &bitmaps_3p, sizeof(bitmaps_3p));
  free(addr);

  addr = malloc(4<<12);
  span = USpanInit(addr, 0, 8, 4<<12);
  assert_int_equal(span->bitmap_cnt, 32);
  assert_int_equal(span->bitmap_headroom, 35);
  assert_int_equal(span->bitmap_padding, 0);
  uint64_t bitmaps_4p [32] = { (1UL << 35)-1 };
  assert_memory_equal(span+1, &bitmaps_4p, sizeof(bitmaps_4p));
  free(addr);
}

// TODO: test malloc that has padding

static void malloc_4byte(void **state)
{
  void* const addr = malloc(1<<12);
  UnarySpan* span;
  span = USpanInit(addr, 0, 4, 1<<12);
  uint64_t bitmaps [16] = { (1UL << 38)-1 };
  assert_memory_equal(span+1, bitmaps, sizeof(bitmaps));

  for (int i = 0; i<1024-38; i++)
    {
      assert_non_null(USpanMalloc(span));
    }
  assert_null(USpanMalloc(span));

  void* item = addr + 38*4;
  
  for (int i = 0; i<1024-38-1; i++)
    {
      assert_false(USpanFree(span, item));
      item+=4;
    }
  assert_ptr_equal(addr+(1<<12)-4, item);
  assert_true(USpanFree(span, item));

  for (int i = 0; i<16; i++)
    bitmaps[i]=~0UL;

  assert_memory_equal(span+1, bitmaps, sizeof(bitmaps));
  
  free(addr);
}

// TODO: test free headroom and padding


int main(void)
{
  const struct CMUnitTest init_tests[] =
    {
      cmocka_unit_test(invalid_address_test),
      cmocka_unit_test(invalid_object_size),
      cmocka_unit_test(invalid_page_cnt),
      cmocka_unit_test(obj_size_4byte),
      cmocka_unit_test(obj_size_8byte),
      cmocka_unit_test(malloc_4byte),
    };
  
  return cmocka_run_group_tests(init_tests, NULL, NULL);
}


/* op_pspan_test.c ends here */
