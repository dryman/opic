/** @file op_malloc.h
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

#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include "opic/common/op_macros.h"

OP_BEGIN_DECLS

#define OPHEAP_BITS 36
#define OPHEAP_SIZE (1UL << OPHEAP_BITS)

/**
 * @struct OPHeap
 * @brief opaque object for memory allocation.
 */
typedef struct OPHeap OPHeap;

/**
 * @typedef opref_t
 * @brief pointer replacement for object allocated in OPHeap.
 * The conversions between opref_t and regular pointer
 * @see OPPtr2Ref
 * @see OPRef2Ptr
 */
typedef uintptr_t opref_t;

/**
 * @relates OPHeap
 * @brief OPHeap constructor.
 *
 * Example:
 *   OPHeap* heap;
 *   assert(OPHeapNew(&heap);
 *   // now the heap pointer is set.
 *
 * @param heap_ref reference to a OPHeap pointer. The pointer is set
 *        when the allocation succeeded.
 * @return true when allocation succeeded, false otherwise.
 */
bool OPHeapNew(OPHeap** heap_ref);

/**
 * @relates OPHeap
 * @brief Writes the heap data to a file.
 *
 * The file sizes would be multiple of 2MB. This is due to the internal
 * huge pages of OPHeap are 2MB, and OPHeap writes out file base on the
 * huge pages.
 *
 * @param heap pointer to OPHeap instance.
 * @param stream an opened FILE pointer.
 */
void OPHeapWrite(OPHeap* heap, FILE* stream);

/**
 * @relates OPHeap
 * @brief Memory map a file as an OPHeap instance. (read only)
 *
 * We only support read only access for now. The memory footprint of
 * the read OPHeap instance would have the same size as the file.
 * Write support and resizing the heap is on our roadmap.
 *
 * @param heap_ref reference to the heap pointer for assigning OPHeap
 *        instance.
 * @param stream an opened FILE pointer.
 * @return true when the read succeeded, false otherwise.
 */
bool OPHeapRead(OPHeap** heap_ref, FILE* stream);

/**
 * @relates OPHeap
 * @brief Destroy the OPHeap instance
 *
 * @param heap the OPHeap instance to destroy.
 */
void OPHeapDestroy(OPHeap* heap);

/**
 * @relates OPHeap
 * @brief Store a pointer to a root pointer slot in OPHeap.
 *
 * @param heap pointer to OPHeap instance.
 * @param ptr the pointer we want to store in root pointer slot.
 * @param pos index in the root pointer slot. 0 <= pos < 8.
 */
void OPHeapStorePtr(OPHeap* heap, void* ptr, int pos);

/**
 * @relates OPHeap
 * @brief Restore a pointer from specified root pointer slot.
 *
 * @param heap pointer to OPHeap instance.
 * @param pos index in the root pointer slot. 0 <= pos < 8.
 * @return The pointer we stored in the root pointer slot.
 */
void* OPHeapRestorePtr(OPHeap* heap, int pos);

/**
 * @relates OPHeap
 * @brief Given any pointer in the OPHeap, returns the pointer to OPHeap.
 *
 * @param addr A pointer allocated with OPHeap.
 * @return pointer to OPHeap.
 */
static inline OPHeap*
ObtainOPHeap(void* addr)
{
  return (OPHeap*)((uintptr_t)addr & ~(OPHEAP_SIZE - 1));
}

/**
 * @brief Converts a pointer allocated in OPHeap to an opref_t.
 *
 * @param addr Any pointer that is allocated with OPHeap.
 * @return An opref_t value.
 */
static inline opref_t
OPPtr2Ref(void* addr)
{
  return (opref_t)addr & (OPHEAP_SIZE - 1);
}

/**
 * @brief Converts an opref_t reference to a regular pointer.
 *
 * @param ptr_in_heap Any pointer in the heap, including OPHeap*.
 * @param ref A opref_t value.
 * @return A regular pointer.
 */
static inline void*
OPRef2Ptr(void* ptr_in_heap, opref_t ref)
{
  return (void*)((opref_t)ObtainOPHeap(ptr_in_heap) + ref);
}

/**
 * @relates OPHeap
 * @brief Allocate an object from OPHeap with given size
 *
 * @param heap pointer to OPHeap instance.
 * @param size the size of object.
 * @return pointer to the object allocated.
 */
void* OPMalloc(OPHeap* heap, size_t size)
  __attribute__ ((malloc));

/**
 * @relates OPHeap
 * @brief Allocate a chunk of memory filled with 0s.
 *
 * @param heap pointer to OPHeap instance.
 * @param num number of contiguous objects.
 * @param size the size of an object.
 * @return pointer to the memory allocated.
 */
void* OPCalloc(OPHeap* heap, size_t num, size_t size)
  __attribute__ ((malloc));

/**
 * @relates OPHeap
 * @brief Allocate an object of given size with an arena hint.
 *
 * @param heap pointer to OPHeap instance.
 * @param size the size of object.
 * @param advice hint to which arena slot to use.
 * @return pointer to the object allocated.
 */
void* OPMallocAdviced(OPHeap* heap, size_t size, int advice)
  __attribute__ ((malloc));

/**
 * @relates OPHeap
 * @brief Allocate a chunk of memory filled with 0s with an arena hint.
 *
 * @param heap pointer to OPHeap instance.
 * @param num number of contiguous objects.
 * @param size the size of an object.
 * @param advice hint to which arena slot to use.
 * @return pointer to the memory allocated.
 */
void* OPCallocAdviced(OPHeap* heap, size_t num, size_t size, int advice)
  __attribute__ ((malloc));

/**
 * @relates OPHeap
 * @brief Dealloc an object created with OPHeap.
 *
 * @param addr the address of the object to be dealloc.
 */
void
OPDealloc(void* addr);

OP_END_DECLS

#endif

/* op_malloc.h ends here */
