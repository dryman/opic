/* op_malloc.h ---
 *
 * Filename: op_malloc.h
 * Description:
 * Author: Felix Chern
 * Maintainer:
 * Created: Sat Oct  1 20:12:46 2016 (-0700)
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

/* This program is free software: you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation, either version 3 of
 * the License, or (at your option) any later version.
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


#ifndef OP_MALLOC_H
#define OP_MALLOC_H 1

#include <stdint.h>
#include "opic/common/op_macros.h"

OP_BEGIN_DECLS

#define OPHEAP_BITS 36
#define OPHEAP_SIZE (1UL << OPHEAP_BITS)

typedef struct OPHeap OPHeap;

bool OPHeapNew(OPHeap** heap_ref);

void OPHeapDestroy(OPHeap* heap);

static inline OPHeap*
ObtainOPHeap(void* addr)
{
  return (OPHeap*)((uintptr_t)addr & ~(OPHEAP_SIZE - 1));
}

static inline uintptr_t
OPPtr2Ref(void* addr)
{
  return (uintptr_t)addr & (OPHEAP_SIZE - 1);
}

static inline void*
OPRef2Ptr(void* ptr_in_heap, uintptr_t ref)
{
  return (void*)((uintptr_t)ObtainOPHeap(ptr_in_heap) + ref);
}

void*
OPMallocRaw(OPHeap* heap, size_t size)
  __attribute__ ((malloc));

void*
OPCallocRaw(OPHeap* heap, size_t num, size_t size)
  __attribute__ ((malloc));

void*
OPMallocRawAdviced(OPHeap* heap, size_t size, int advice)
  __attribute__ ((malloc));

void*
OPCallocRawAdviced(OPHeap* heap, size_t num, size_t size, int advice)
  __attribute__ ((malloc));

void
OPDealloc(void* addr);

OP_END_DECLS

#endif

/* op_malloc.h ends here */
