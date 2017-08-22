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
#include <string.h>
#include <cmocka.h>

#include "magic.h"
#include "inline_aux.h"
#include "lookup_helper.h"
#include "init_helper.h"

static void
test_Sizes(void** context)
{
  assert_int_equal(4, sizeof(Magic));
  assert_int_equal(24, sizeof(UnarySpan));
  assert_int_equal(144, sizeof(HugePage));
  assert_int_equal(10, sizeof(UnarySpanQueue));
  assert_int_equal(10, sizeof(HugePageQueue));
  assert_int_equal(2600, sizeof(RawType));
  assert_int_equal(11008, sizeof(OPHeap));
}

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

  heap = OPHeapOpenTmp();
  heap_base = (uintptr_t)heap;
  magic.raw_hpage.pattern = RAW_HPAGE_PATTERN;
  ctx.hspan.hpage = &heap->hpage;

  hpage = ctx.hspan.hpage;
  HPageInit(hpage, magic);

  assert_int_equal(magic.int_value, hpage->magic.int_value);
  assert_int_equal(0, hpage->pcard);

  /*
   * sizeof(OPHeap) = 11008 = 4096 * 2 + 2816
   * => 3 bit spaces to occupy
   */
  //                 7654321076543210
  occupy_bmap[0] = 0x07UL;
  assert_memory_equal(occupy_bmap, hpage->occupy_bmap, 8 * sizeof(uint64_t));
  assert_memory_equal(header_bmap, hpage->header_bmap, 8 * sizeof(uint64_t));

  ctx.hspan.uintptr = heap_base + HPAGE_SIZE;
  hpage = ctx.hspan.hpage;
  HPageInit(hpage, magic);
  assert_int_equal(magic.int_value, hpage->magic.int_value);
  assert_int_equal(0, hpage->pcard);

  occupy_bmap[0] = 0UL;
  assert_memory_equal(occupy_bmap, hpage->occupy_bmap, 8 * sizeof(uint64_t));
  assert_memory_equal(header_bmap, hpage->header_bmap, 8 * sizeof(uint64_t));

  OPHeapClose(heap);
}

static void
test_USpanInit_RawTypeSmall(void** context)
{
  OPHeap* heap;
  uintptr_t heap_base;
  OPHeapCtx ctx;
  UnarySpan* uspan;
  Magic magic = {};
  uint64_t* bmap;
  uint64_t test_bmap[4] = {0};

  heap = OPHeapOpenTmp();
  heap_base = (uintptr_t)heap;
  ctx.sspan.uintptr = heap_base + HPAGE_SIZE + SPAGE_SIZE;
  uspan = ctx.sspan.uspan;
  bmap = (uint64_t*)(ctx.sspan.uintptr + sizeof(UnarySpan));

  /*
   * Object size: 16 bytes; (The smallest raw_type size we can alloc)
   * 1 Page count => 4096 bytes
   * Bitmap: 4096 / 16 = 256 bits to map the space = 4 bitmaps
   * 4 bitmaps takes 8 * 4 = 32 bytes
   * headroom size in bytes: sizeof(UnarySpan) + 32 = 24 + 32 = 56 bytes
   * headroom in object/bits: 56 = 16 * 3 + 8 => 4 bits
   * padding: 0 bytes;
   */
  magic.raw_uspan.pattern = RAW_USPAN_PATTERN;
  magic.raw_uspan.obj_size = 16;
  USpanInit(uspan, magic, 1);
  assert_int_equal(magic.int_value, uspan->magic.int_value);
  assert_int_equal(4, uspan->bitmap_cnt);
  assert_int_equal(4, uspan->bitmap_headroom);
  assert_int_equal(0, uspan->bitmap_padding);
  assert_int_equal(0, uspan->bitmap_hint);
  assert_int_equal(0, uspan->pcard);
  assert_int_equal(0, uspan->obj_cnt);
  assert_null(uspan->next);
  memset(test_bmap, 0, 4 * sizeof(uint64_t));
  test_bmap[0] = 0x0F;
  assert_memory_equal(test_bmap, bmap, 4 * sizeof(uint64_t));

  /*
   * Object size: 24 bytes
   * 1 Page count => 4096 bytes
   * Bitmap: 4096 / 24 = 170.6 bits to map the space = 3 bitmaps
   * 3 bitmaps takes 8 * 3 = 24 bytes
   * headroom size in bytes: sizeof(UnarySpan) + 24 = 24 + 24 = 48 bytes
   * headroom in object/bits: 48 = 24 * 2 => 2 bits
   * padding size in bytes: 3 * 64 * 24 - 4096 = 512 bytes
   * padding in object/bits: 512 = 24 * 21 + 8 => 22 bits
   */
  magic.raw_uspan.pattern = RAW_USPAN_PATTERN;
  magic.raw_uspan.obj_size = 24;
  USpanInit(uspan, magic, 1);
  assert_int_equal(magic.int_value, uspan->magic.int_value);
  assert_int_equal(3, uspan->bitmap_cnt);
  assert_int_equal(2, uspan->bitmap_headroom);
  assert_int_equal(22, uspan->bitmap_padding);
  assert_int_equal(0, uspan->bitmap_hint);
  assert_int_equal(0, uspan->pcard);
  assert_int_equal(0, uspan->obj_cnt);
  assert_null(uspan->next);
  memset(test_bmap, 0, 3 * sizeof(uint64_t));
  test_bmap[0] = 0x03;
  //               7654321076543210
  test_bmap[2] = 0xFFFFFC0000000000UL;
  assert_memory_equal(test_bmap, bmap, 3 * sizeof(uint64_t));
  OPHeapClose(heap);
}

static void
test_USpanInit_RawTypeSmall_FstPage(void** context)
{
  OPHeap* heap;
  uintptr_t heap_base;
  OPHeapCtx ctx;
  UnarySpan* uspan;
  Magic magic = {};
  uint64_t* bmap;
  uint64_t test_bmap[8] = {0};

  heap = OPHeapOpenTmp();
  heap_base = (uintptr_t)heap;
  ctx.sspan.uintptr = heap_base + HPAGE_SIZE + sizeof(HugePage);
  uspan = ctx.sspan.uspan;
  bmap = (uint64_t*)(ctx.sspan.uintptr + sizeof(UnarySpan));

  /*
   * Object size: 16 bytes
   * 1 Page count => 4096 bytes
   * Bitmap: 4096 / 16 = 256 bits to map the space = 4 bitmaps
   * 4 bitmaps takes 8 * 4 = 32 bytes
   * headroom size in bytes: sizeof(HugePage) + sizeof(UnarySpan) + 32
   *   = 144 + 24 + 32 = 200 bytes
   * headroom in object/bits: 200 = 16 * 12 + 8 => 13 bits
   * padding: 0 bytes;
   */
  magic.raw_uspan.pattern = RAW_USPAN_PATTERN;
  magic.raw_uspan.obj_size = 16;
  USpanInit(uspan, magic, 1);
  assert_int_equal(magic.int_value, uspan->magic.int_value);
  assert_int_equal(4, uspan->bitmap_cnt);
  assert_int_equal(13, uspan->bitmap_headroom);
  assert_int_equal(0, uspan->bitmap_padding);
  assert_int_equal(0, uspan->bitmap_hint);
  assert_int_equal(0, uspan->pcard);
  assert_int_equal(0, uspan->obj_cnt);
  assert_null(uspan->next);
  memset(test_bmap, 0, 4 * sizeof(uint64_t));
  test_bmap[0] = 0x1FFF;
  assert_memory_equal(test_bmap, bmap, 4 * sizeof(uint64_t));

  /*
   * Object size: 24 bytes
   * 1 Page count => 4096 bytes
   * Bitmap: 4096 / 24 = 170.6 bits to map the space = 3 bitmaps
   * 3 bitmaps takes 8 * 3 = 24 bytes
   * headroom size in bytes: sizeof(HugePage) + sizeof(UnarySpan) + 24
   *   = 144 + 24 + 24 = 192 bytes
   * headroom in object/bits: 192 = 24 * 8 => 8 bits
   * padding size in bytes: 3 * 64 * 24 - 4096 = 512 bytes
   * padding in object/bits: 512 = 24 * 21 + 8 => 22 bits
   */
  magic.raw_uspan.pattern = RAW_USPAN_PATTERN;
  magic.raw_uspan.obj_size = 24;
  USpanInit(uspan, magic, 1);
  assert_int_equal(magic.int_value, uspan->magic.int_value);
  assert_int_equal(3, uspan->bitmap_cnt);
  assert_int_equal(8, uspan->bitmap_headroom);
  assert_int_equal(22, uspan->bitmap_padding);
  assert_int_equal(0, uspan->bitmap_hint);
  assert_int_equal(0, uspan->pcard);
  assert_int_equal(0, uspan->obj_cnt);
  assert_null(uspan->next);
  memset(test_bmap, 0, 3 * sizeof(uint64_t));
  test_bmap[0] = 0xFF;
  //               7654321076543210
  test_bmap[2] = 0xFFFFFC0000000000UL;
  assert_memory_equal(test_bmap, bmap, 3 * sizeof(uint64_t));
  OPHeapClose(heap);
}


static void
test_USpanInit_RawTypeLarge(void** context)
{
  OPHeap* heap;
  uintptr_t heap_base;
  OPHeapCtx ctx;
  UnarySpan* uspan;
  Magic magic = {};
  uint64_t* bmap;
  uint64_t test_bmap[8] = {0};

  heap = OPHeapOpenTmp();
  heap_base = (uintptr_t)heap;
  ctx.sspan.uintptr = heap_base + HPAGE_SIZE + SPAGE_SIZE;
  uspan = ctx.sspan.uspan;
  bmap = (uint64_t*)(ctx.sspan.uintptr + sizeof(UnarySpan));

  /*
   * Object size: 1024 bytes
   * 16 Page count => 65536 bytes
   * Bitmap: 65536 / 1024 = 64 bits to map the space = 1 bitmaps
   * headroom size in bytes: sizeof(UnarySpan) + 8 = 24 + 8 = 32 bytes
   * headroom in object/bits: 1
   * padding: 0 bytes
   */
  magic.raw_uspan.pattern = RAW_USPAN_PATTERN;
  magic.raw_uspan.obj_size = 1024;
  USpanInit(uspan, magic, 16);
  assert_int_equal(magic.int_value, uspan->magic.int_value);
  assert_int_equal(1, uspan->bitmap_cnt);
  assert_int_equal(1, uspan->bitmap_headroom);
  assert_int_equal(0, uspan->bitmap_padding);
  assert_int_equal(0, uspan->bitmap_hint);
  assert_int_equal(0, uspan->pcard);
  assert_int_equal(0, uspan->obj_cnt);
  assert_null(uspan->next);
  memset(test_bmap, 0, 1 * sizeof(uint64_t));
  test_bmap[0] = 0x01;
  assert_memory_equal(test_bmap, bmap, 1 * sizeof(uint64_t));

  /*
   * In actual setup we use 32 pages instead of 16.
   * Here we want to test the initializer robustness for bitmap
   * that is half full.
   * Object size: 2048 bytes
   * 16 Page count => 65536 bytes
   * Bitmap: 65536 / 2048 = 32 bits to map the space = 1 bitmaps
   * headroom size in bytes: sizeof(UnarySpan) + 8 = 24 + 8 = 32 bytes
   * headroom in object/bits: 1
   * padding size in bytes: 2048 * 64 - 65536 = 65536
   * padding in object/bits: 65536 = 2048 * 32 => 32 bits
   */
  magic.raw_uspan.pattern = RAW_USPAN_PATTERN;
  magic.raw_uspan.obj_size = 2048;
  USpanInit(uspan, magic, 16);
  assert_int_equal(magic.int_value, uspan->magic.int_value);
  assert_int_equal(1, uspan->bitmap_cnt);
  assert_int_equal(1, uspan->bitmap_headroom);
  assert_int_equal(32, uspan->bitmap_padding);
  assert_int_equal(0, uspan->bitmap_hint);
  assert_int_equal(0, uspan->pcard);
  assert_int_equal(0, uspan->obj_cnt);
  assert_null(uspan->next);
  memset(test_bmap, 0, 1 * sizeof(uint64_t));
  //               7654321076543210
  test_bmap[0] = 0xFFFFFFFF00000001UL;
  assert_memory_equal(test_bmap, bmap, 1 * sizeof(uint64_t));

  OPHeapClose(heap);
}

static void
test_OPHeapEmptiedBMaps(void** context)
{
  OPHeap* heap;
  uint64_t test_bmap[HPAGE_BMAP_NUM] = {0};

  heap = OPHeapOpenTmp();
  OPHeapEmptiedBMaps(heap, heap->occupy_bmap, heap->header_bmap);
  assert_memory_equal(test_bmap, heap->occupy_bmap,
                      HPAGE_BMAP_NUM * sizeof(uint64_t));
  assert_memory_equal(test_bmap, heap->header_bmap,
                      HPAGE_BMAP_NUM * sizeof(uint64_t));

  heap->hpage_num = 1;
  OPHeapEmptiedBMaps(heap, heap->occupy_bmap, heap->header_bmap);
  //               7654321076543210
  test_bmap[0] = 0xFFFFFFFFFFFFFFFEUL;
  memset(&test_bmap[1], 0xFF, (HPAGE_BMAP_NUM - 1) * sizeof(uint64_t));
  assert_memory_equal(test_bmap, heap->occupy_bmap,
                      HPAGE_BMAP_NUM * sizeof(uint64_t));

  heap->hpage_num = 64;
  OPHeapEmptiedBMaps(heap, heap->occupy_bmap, heap->header_bmap);
  test_bmap[0] = 0UL;
  assert_memory_equal(test_bmap, heap->occupy_bmap,
                      HPAGE_BMAP_NUM * sizeof(uint64_t));
  heap->hpage_num = HPAGE_BMAP_NUM * 64;
  OPHeapClose(heap);
}

int
main (void)
{
  const struct CMUnitTest init_helper_tests[] =
    {
      cmocka_unit_test(test_Sizes),
      cmocka_unit_test(test_HPageInit),
      cmocka_unit_test(test_USpanInit_RawTypeSmall),
      cmocka_unit_test(test_USpanInit_RawTypeSmall_FstPage),
      cmocka_unit_test(test_USpanInit_RawTypeLarge),
      cmocka_unit_test(test_OPHeapEmptiedBMaps),
    };

  return cmocka_run_group_tests(init_helper_tests, NULL, NULL);
}

/* init_helper_test.c ends here */
