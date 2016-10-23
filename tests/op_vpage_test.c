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
#include <limits.h>
#include "opic/common/op_log.h"
#include "opic/malloc/op_vpage.h"
#include "opic/malloc/op_pspan.h"
#include <sys/mman.h>

OP_LOGGER_FACTORY(logger, "opic.test.op_vpage_test");

static void* mmap_align_2MB()
{
  // Let's start from 1GB
  ptrdiff_t offset = 1L << 36;
  void* addr = NULL + offset;
  void* map_addr;
  for (int i = 0; i<128; i++)
    {
      map_addr = mmap(addr, 1UL<<21,
                      PROT_READ | PROT_WRITE,
                      MAP_ANON | MAP_PRIVATE | MAP_FIXED,
                      -1, 0);
      if (map_addr == MAP_FAILED)
        {
          OP_LOG_ERROR(logger, "mmap failed on %p\n", addr);
          addr += 1UL<<21;
        }
      else
        return map_addr;
    }
  return NULL;
}

static void vpage_init_test(void **state)
{
  void* addr = mmap_align_2MB();
  assert_non_null(addr);
  assert_non_null(OPVPageInit(addr));
  munmap(addr, 1UL<<21);
}

static void get_pspans_test(void **state)
{
  OPVPage* vpage = OPVPageInit(mmap_align_2MB());
  UnaryPSpan* span = OPVPageAllocPSpan(vpage, 0, 8, 1);
  assert_int_equal(span->bitmap_cnt, 7);
  assert_int_equal(span->bitmap_headroom, 10);
  assert_int_equal(span->bitmap_padding, 18);
  uint64_t bitmaps [7] =
    {
      [0] = (1UL << 10)-1,
      [6] = ~((1UL << (64-18))-1)
    };
  assert_memory_equal(span+1, &bitmaps, sizeof(bitmaps));

  uint64_t occupy_bmap[8] = {1};
  uint64_t header_bmap[8] = {1};
  int8_t refcnt[512];
  refcnt[0] = 0;
  for (int i = 1; i < 512; i++)
    refcnt[i] = CHAR_MIN;
  assert_memory_equal(&vpage->occupy_bmap, occupy_bmap, sizeof(occupy_bmap));
  assert_memory_equal(&vpage->header_bmap, header_bmap, sizeof(header_bmap));
  assert_memory_equal(&vpage->refcnt, refcnt, sizeof(refcnt));

  UnaryPSpan* span2 = OPVPageAllocPSpan(vpage, 0, 8, 1);
  assert_int_equal(span2->bitmap_cnt, 8);
  assert_int_equal(span2->bitmap_headroom, 11);
  assert_int_equal(span2->bitmap_padding, 0);

  occupy_bmap[0] = 3;
  header_bmap[0] = 3;
  refcnt[1] = 0;
  assert_memory_equal(&vpage->occupy_bmap, occupy_bmap, sizeof(occupy_bmap));
  assert_memory_equal(&vpage->header_bmap, header_bmap, sizeof(header_bmap));
  assert_memory_equal(&vpage->refcnt, refcnt, sizeof(refcnt));

  munmap(vpage, 1UL<<21);
}

static void simple_free_test(void **state)
{
  OPVPage* vpage = OPVPageInit(mmap_align_2MB());
  UnaryPSpan* span1 = OPVPageAllocPSpan(vpage, 0, 8, 1);
  UnaryPSpan* span2 = OPVPageAllocPSpan(vpage, 0, 8, 1);
  void* addr1 = UnaryPSpanMalloc(span1);
  void* addr2 = UnaryPSpanMalloc(span2);
  assert_non_null(addr1);
  assert_non_null(addr2);

  uint64_t occupy_bmap[8] = {0};
  uint64_t header_bmap[8] = {0};
  int8_t refcnt[512];

  for (int i = 0; i < 512; i++)
    refcnt[i] = CHAR_MIN;
  
  assert_false(OPVPageFree(vpage, addr1));
  occupy_bmap[0] = 2;
  header_bmap[0] = 2;
  refcnt[1] = 0;
  assert_memory_equal(&vpage->occupy_bmap, occupy_bmap, sizeof(occupy_bmap));
  assert_memory_equal(&vpage->header_bmap, header_bmap, sizeof(header_bmap));
  assert_memory_equal(&vpage->refcnt, refcnt, sizeof(refcnt));
  
  assert_true(OPVPageFree(vpage, addr2));

  for (int i = 0; i < 8; i++)
    occupy_bmap[i] = ~0UL;
  header_bmap[0] = 0;
  refcnt[1] = CHAR_MIN;

  assert_memory_equal(&vpage->occupy_bmap, occupy_bmap, sizeof(occupy_bmap));
  assert_memory_equal(&vpage->header_bmap, header_bmap, sizeof(header_bmap));
  assert_memory_equal(&vpage->refcnt, refcnt, sizeof(refcnt));
  
  munmap(vpage, 1UL<<21);
}

int main(void)
{
  const struct CMUnitTest vpage_tests[] =
    {
      cmocka_unit_test(vpage_init_test),
      cmocka_unit_test(get_pspans_test),
      cmocka_unit_test(simple_free_test),
    };
  
  return cmocka_run_group_tests(vpage_tests, NULL, NULL);
}

/* op_vpage_test.c ends here */
