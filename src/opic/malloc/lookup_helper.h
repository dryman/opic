/* lookup_helper.h ---
 *
 * Filename: lookup_helper.h
 * Description:
 * Author: Felix Chern
 * Maintainer:
 * Copyright: (c) 2016 Felix Chern
 * Created: Sun Mar  5 15:40:03 2017 (-0800)
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

#ifndef OPIC_MALLOC_LOOKUP_HELPER_H
#define OPIC_MALLOC_LOOKUP_HELPER_H 1

#include "objdef.h"

OP_BEGIN_DECLS

static inline HugePage*
ObtainHPage(void* addr)
{
  OPHeap* heap;
  uintptr_t heap_base, addr_base;

  heap = ObtainOPHeap(addr);
  heap_base = (uintptr_t)heap;
  addr_base = (uintptr_t)addr;

  if (addr_base - heap_base < HPAGE_SIZE)
    return &heap->hpage;

  return (HugePage*)(addr_base & ~(HPAGE_SIZE - 1));
}

static inline uintptr_t
ObtainHSpanBase(HugeSpanPtr header)
{
  return header.uintptr & ~(HPAGE_SIZE - 1);
}

static inline uintptr_t
ObtainSSpanBase(SmallSpanPtr header)
{
  return header.uintptr & ~(SPAGE_SIZE - 1);
}

HugeSpanPtr ObtainHugeSpanPtr(void* addr)
  __attribute__ ((visibility ("internal")));

SmallSpanPtr HPageObtainSmallSpanPtr(HugePage* hpage, void* addr)
  __attribute__ ((visibility ("internal")));

UnarySpanQueue* ObtainUSpanQueue(UnarySpan* uspan)
  __attribute__ ((visibility ("internal")));

HugePageQueue* ObtainHPageQueue(HugePage* hpage)
  __attribute__ ((visibility ("internal")));

OP_END_DECLS

#endif

/* lookup_helper.h ends here */
