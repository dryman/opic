/* lookup_helper.c ---
 *
 * Filename: lookup_helper.c
 * Description:
 * Author: Felix Chern
 * Maintainer:
 * Copyright: (c) 2016 Felix Chern
 * Created: Sun Mar  5 15:49:29 2017 (-0800)
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

#include <inttypes.h>
#include "opic/common/op_assert.h"
#include "opic/common/op_utils.h"
#include "magic.h"
#include "inline_aux.h"
#include "lookup_helper.h"

HugeSpanPtr
ObtainHugeSpanPtr(void* addr)
{
  OPHeap* heap;
  HugeSpanPtr hspan_ptr;
  uintptr_t heap_base, addr_base,
    _addr, _addr_hpage, _addr_bmidx, _addr_bmbit;
  uint64_t bmap, mask, bmap_masked;
  int leading_zeros;

  heap = ObtainOPHeap(addr);
  heap_base = (uintptr_t)heap;
  addr_base = (uintptr_t)addr;
  _addr = addr_base - heap_base;

  _addr_hpage = _addr >> HPAGE_BITS;
  _addr_bmidx = _addr_hpage / 64;
  _addr_bmbit = _addr_hpage % 64;

  // Not informative enough
  op_assert(atomic_load_explicit(&heap->occupy_bmap[_addr_bmidx],
                                 memory_order_relaxed) &
            (1UL << _addr_bmbit),
            "Addr %p located in %" PRIuPTR " OPHeap bitmap "
            "has value 0x%" PRIx64 "\n",
            addr, _addr_bmidx, heap->occupy_bmap[_addr_bmidx]);

  if (_addr < HPAGE_SIZE)
    {
      hspan_ptr.hpage = &heap->hpage;
      return hspan_ptr;
    }

  if (atomic_load_explicit(&heap->header_bmap[_addr_bmidx],
                           memory_order_relaxed) &
      (1UL << _addr_bmbit))
    {
      hspan_ptr.uintptr = heap_base + _addr_hpage * HPAGE_SIZE;
      return hspan_ptr;
    }

  mask = (1UL << _addr_bmbit) - 1;
  bmap_masked = atomic_load_explicit(&heap->header_bmap[_addr_bmidx],
                                     memory_order_relaxed) & mask;
  leading_zeros = __builtin_clzl(bmap_masked);

  if (bmap_masked && leading_zeros)
    {
      hspan_ptr.uintptr = heap_base +
        (_addr_bmidx * 64 + (64 - leading_zeros - 1)) * HPAGE_SIZE;
      return hspan_ptr;
    }

  for (int bmidx = (int)_addr_bmidx - 1; bmidx >= 0; bmidx--)
    {
      bmap = atomic_load_explicit(&heap->header_bmap[bmidx],
                                  memory_order_relaxed);
      if (bmap)
        {
          leading_zeros = __builtin_clzl(bmap);
          hspan_ptr.uintptr = heap_base +
            (bmidx * 64 + (64 - leading_zeros - 1)) * HPAGE_SIZE;
          return hspan_ptr;
        }
    }
  op_assert(0, "Could not find valid HSpan for addr %p", addr);
  hspan_ptr.uintptr = 0;
  return hspan_ptr;
}

SmallSpanPtr
HPageObtainSmallSpanPtr(HugePage* hpage, void* addr)
{
  SmallSpanPtr sspan_ptr;
  uintptr_t hpage_base, addr_base,
    _addr, _addr_spage, _addr_bmidx, _addr_bmbit;
  uint64_t bmap, mask, bmap_masked;
  int leading_zeros;

  hpage_base = ObtainHSpanBase(hpage);
  addr_base = (uintptr_t)addr;
  _addr = addr_base - hpage_base;
  op_assert(_addr >= 0 && _addr < HPAGE_SIZE,
            "Addr %p should be in hpage %p 2MB boundary\n",
            addr, hpage);

  _addr_spage = _addr >> SPAGE_BITS;
  _addr_bmidx = _addr_spage / 64;
  _addr_bmbit = _addr_spage % 64;

  // Not informative enough
  op_assert(atomic_load_explicit(&hpage->occupy_bmap[_addr_bmidx],
                                 memory_order_relaxed) &
            (1UL << _addr_bmbit),
            "Addr %p located in %" PRIuPTR " HPage bitmap "
            "has value %" PRIx64 "\n",
            addr, _addr_bmidx, hpage->occupy_bmap[_addr_bmidx]);

  if (atomic_load_explicit(&hpage->header_bmap[_addr_bmidx],
                           memory_order_relaxed) &
      (1UL << _addr_bmbit))
    {
      sspan_ptr.uintptr = hpage_base + _addr_spage * SPAGE_SIZE;
      goto first_sspan_adjustment;
    }

  mask = (1UL << _addr_bmbit) - 1;
  bmap_masked = atomic_load_explicit(&hpage->header_bmap[_addr_bmidx],
                                     memory_order_relaxed) & mask;
  leading_zeros = __builtin_clzl(bmap_masked);

  if (bmap_masked && leading_zeros)
    {
      sspan_ptr.uintptr = hpage_base +
        (_addr_bmidx * 64 + (64 - leading_zeros - 1)) * SPAGE_SIZE;
      goto first_sspan_adjustment;
    }

  for (int bmidx = (int)_addr_bmidx - 1; bmidx >= 0; bmidx--)
    {
      bmap = atomic_load_explicit(&hpage->header_bmap[bmidx],
                                  memory_order_relaxed);
      if (bmap)
        {
          leading_zeros = __builtin_clzl(bmap);
          sspan_ptr.uintptr = hpage_base +
            (bmidx * 64 + (64 - leading_zeros - 1)) * SPAGE_SIZE;
          goto first_sspan_adjustment;
        }
    }
  op_assert(0, "Could not find valid SSpan for addr %p in HPage %p\n",
            addr, hpage);
  sspan_ptr.uintptr = 0;
  return sspan_ptr;

 first_sspan_adjustment:
  if (sspan_ptr.uintptr == hpage_base)
    sspan_ptr.uintptr = hpage_base + sizeof(HugePage);

  return sspan_ptr;
}

UnarySpanQueue*
ObtainUSpanQueue(UnarySpan* uspan)
{
  OPHeap* heap;
  int tid, size_class, obj_size, uspan_id;

  heap = ObtainOPHeap(uspan);
  switch (uspan->magic.generic.pattern)
    {
    case RAW_USPAN_PATTERN:
      size_class = round_up_div(uspan->magic.raw_uspan.obj_size, 16) - 1;
      tid = uspan->magic.raw_uspan.thread_id;
      return &heap->raw_type.uspan_queue[size_class][tid];
    case LARGE_USPAN_PATTERN:
      obj_size = uspan->magic.large_uspan.obj_size;
      uspan_id =
        obj_size == 512 ? 0 :
        obj_size == 1024 ? 1 : 2;
      return &heap->raw_type.large_uspan_queue[uspan_id];
    default:
      op_assert(0, "Unknown USpan pattern %d\n",
                uspan->magic.generic.pattern);
      return NULL;
    }
}

HugePageQueue*
ObtainHPageQueue(HugePage* hpage)
{
  OPHeap* heap;
  heap = ObtainOPHeap(hpage);
  op_assert(hpage->magic.generic.pattern == RAW_HPAGE_PATTERN,
            "Unknown magic pattern %d\n", hpage->magic.generic.pattern);
  return &heap->raw_type.hpage_queue;
}

/* lookup_helper.c ends here */
