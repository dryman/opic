/**
 * @file op_malloc.h
 * @author Felix Chern
 * @date Sat Oct  1 20:12:46 2016 (-0700)
 * @copyright 2016-2017 Felix Chern
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
#include <inttypes.h>
#include <string.h>
#include "opic/common/op_assert.h"
#include "opic/common/op_macros.h"

OP_BEGIN_DECLS

/**
 * @defgroup malloc
 */

/**
 * @ingroup malloc
 * @brief Size of OPHeap represented in bits offset.
 */
#define OPHEAP_BITS 36

/**
 * @ingroup malloc
 * @brief Size of OPHeap.
 */
#define OPHEAP_SIZE (1UL << OPHEAP_BITS)

/**
 * @ingroup malloc
 * @struct OPHeap
 * @brief Opaque object for memory allocation.
 */
typedef struct OPHeap OPHeap;

/**
 * @ingroup malloc
 * @typedef opref_t
 * @brief The "pointer type" used within objects created by OPHeap.
 *
 * For all the objects relationship in OPHeap, user must use opref_t
 * or oplenref_t instead of regular pointer. Regular pointers would be
 * invalid when OPHeap is written to disk. To access the object
 * referenced by opref_t, first dereference opref_t to regular
 * pointer, then dereference the pointer.
 *
 * Unfortunately, C type system is quite weak. It would be better
 * if we have the following features:
 *   -# preserve the type information of the address we points to.
 *   -# operator overload, or makes every symbol posible to be used as
 *      an operator like what Haskell does. Common operation like
 *      dereferencing should have its own operator.
 *
 * Here is an example of how to reference other objects using opref_t:
 *
 * @code
 * struct A {
 *   opref_t ref_b;
 * };
 *
 * struct B {
 *   int x;
 * };
 *
 * OPHeap* heap;
 * OPHeapNew(&heap);
 *
 * struct A* a = OPMalloc(heap, sizeof(struct A));
 * struct B* b = OPMalloc(heap, sizeof(struct B));
 * struct B* b2;
 *
 * // We store the pointer as opref_t
 * a->ref_b = OPPtr2Ref(b);
 *
 * // When accessing the memory, dereference it as a pointer
 * b2 = OPRef2Ptr(a, a->ref_b);
 * @endcode
 *
 * @see
 *   - OPPtr2Ref
 *   - OPRef2Ptr.
 */
typedef uintptr_t opref_t;

/**
 * @ingroup malloc
 * @typedef oplenref_t
 * @brief Another "pointer type" used within objects created by OPHeap,
 *
 * oplenref_t not only served as opref_t, but also encodes length of
 * the object it pointed to. The length oplenref_t encodes must be
 * smaller than OPLENREF_MAX_LEN.
 *
 * @see
 *   - OPPtr2LenRef
 *   - OPLenRef2Ptr
 *   - OPLenRef2Size
 *   - OPLenRef2Ref
 *   - OPLenRefCreate
 */
typedef uintptr_t oplenref_t;

#define OPLENREF_MAX_LEN (1ULL << (64 - OPHEAP_BITS))

/**
 * @relates OPHeap
 * @brief OPHeap constructor.
 * @param heap_ref reference to a OPHeap pointer. The pointer is set
 *        when the allocation succeeded.
 * @return true when allocation succeeded, false otherwise.
 *
 * @code
 *   OPHeap* heap;
 *   assert(OPHeapNew(&heap));
 *   // now the heap pointer is set.
 * @endcode
 *
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
 * @param heap OPHeap instance.
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
 * @param heap OPHeap instance.
 * @param ptr the pointer we want to store in root pointer slot.
 * @param pos index in the root pointer slot. 0 <= pos < 8.
 */
void OPHeapStorePtr(OPHeap* heap, void* ptr, int pos);

/**
 * @relates OPHeap
 * @brief Restore a pointer from specified root pointer slot.
 *
 * @param heap OPHeap instance.
 * @param pos index in the root pointer slot. 0 <= pos < 8.
 * @return The pointer we stored in the root pointer slot.
 */
void* OPHeapRestorePtr(OPHeap* heap, int pos);

/**
 * @relates OPHeap
 * @brief Allocate an object from OPHeap with given size
 *
 * @param heap OPHeap instance.
 * @param size the size of object.
 * @return pointer to the object allocated.
 */
void* OPMalloc(OPHeap* heap, size_t size)
  __attribute__ ((malloc));

/**
 * @relates OPHeap
 * @brief Allocate a chunk of memory filled with 0s.
 *
 * @param heap OPHeap instance.
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
 * @param heap OPHeap instance.
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
 * @param heap OPHeap instance.
 * @param num number of contiguous objects.
 * @param size the size of an object.
 * @param advice hint to which arena slot to use.
 * @return pointer to the memory allocated.
 */
void* OPCallocAdviced(OPHeap* heap, size_t num, size_t size, int advice)
  __attribute__ ((malloc));

/**
 * @relates OPHeap
 * @brief Dealloc an object created by OPHeap.
 *
 * @param addr the address of the object to be dealloc.
 */
void
OPDealloc(void* addr);

/**
 * @relates OPHeap
 * @brief Given any pointer in the OPHeap, returns the pointer to OPHeap.
 *
 * @param addr A pointer allocated by OPHeap.
 * @return pointer to OPHeap.
 */
static inline OPHeap*
ObtainOPHeap(void* addr)
{
  return (OPHeap*)((uintptr_t)addr & ~(OPHEAP_SIZE - 1));
}

/**
 * @ingroup malloc
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
 * @ingroup malloc
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
 * @ingroup malloc
 * @brief Converts a pointer allocated in OPHeap and the size
 * of the object it pointed to to an oplenref_t.
 *
 * @param addr Any pointer that is allocated with OPHeap.
 * @param size The size of the object allocated with OPHeap.
 * @return An oplenref_t value.
 */
static inline oplenref_t
OPPtr2LenRef(void* addr, size_t size)
{
  oplenref_t ref;

  op_assert(size < OPLENREF_MAX_LEN,
            "Size for oplenref_t must smaller than %" PRIu64
            ", but was %zu\n", OPLENREF_MAX_LEN, size);
  ref = (oplenref_t)addr & (OPHEAP_SIZE - 1);
  ref |= size << OPHEAP_BITS;
  return ref;
}

/**
 * @ingroup malloc
 * @brief Obtain the size encoded in oplenref_t
 *
 * @param ref A oplenref_t value.
 * @return The size of the object it pointed to.
 */
static inline size_t
OPLenRef2Size(oplenref_t ref)
{
  return (size_t)(ref >> OPHEAP_BITS);
}

/**
 * @ingroup malloc
 * @brief Convert oplenref_t to opref_t.
 *
 * @param ref A oplenref_t value.
 * @return An opref_t value.
 */
static inline opref_t
OPLenRef2Ref(oplenref_t ref)
{
  return ref & (OPHEAP_SIZE - 1);
}

/**
 * @ingroup malloc
 * @brief Converts an oplenref_t reference to a regular pointer.
 *
 * @param ptr_in_heap Any pointer in the heap, including OPHeap*.
 * @param ref A oplenref_t value.
 * @return A regular pointer.
 */
static inline void*
OPLenRef2Ptr(void* ptr_in_heap, oplenref_t ref)
{
  return OPRef2Ptr(ptr_in_heap, OPLenRef2Ref(ref));
}

/**
 * @ingroup malloc
 * @brief A constructor that copies the data to OPHeap,
 * and returns the oplenref_t referencing the data in OPHeap.
 *
 * @param heap OPHeap reference.
 * @param data The data to copy over to OPHeap.
 * @param size Size of the data.
 * @return An oplenref_t value. If the allocation failed, the
 * value would be 0.
 */
static inline oplenref_t
OPLenRefCreate(OPHeap* heap, void* data, size_t size)
{
  void* ptr;
  ptr = OPCalloc(heap, 1, size);
  if (!ptr)
    return 0;
  memcpy(ptr, data, size);
  return OPPtr2LenRef(ptr, size);
}

OP_END_DECLS

#endif

/* op_malloc.h ends here */
