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
 * @brief Size of OPHeap represented in bits.
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
 * @brief Another "pointer type" used within objects created in OPHeap.
 *
 * oplenref_t can encode an object created in OPHeap *and* the size of
 * such object. User can query the size of the object by OPLenRef2Szie.
 * The size of the object must smaller than OPLENREF_MAX_LEN, which is
 * 256MB and suppose to be sufficient for regular use.
 *
 * When oplenref_t is used in a container, oplenref_t can be used to encode
 * the inline data in the container. The container holding oplenref_t can
 * provide additional space next to oplenref_t to hold the inline data.
 * When encoding or decoding oplenref_t the addtional space information
 * must present so we know if the data is next to oplenref_t, or it is
 * somewhere else in OPHeap.
 *
 * @see
 *   - OPLenRef2Ptr
 *   - OPLenRef2Size
 *   - OPLenRefCreate
 *   - OPLenRefDelete
 *   - OPLenRefReplace
 */
typedef uintptr_t oplenref_t;

/**
 * @ingroup malloc
 * @brief Maximum size oplenref_t can hold.
 *
 * The size is roughly 256MB, which should be sufficient for most applications.
 */
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

#ifndef DOXYGEN_SKIP
/*
 * Internal use only.  Extracts opref_t part from oplenref_t. This
 * value could be 0 if the size portion of oplenref_t is smaller than
 * the container size.
 *
 * In most cases, user should use OPLenRef2Ptr instead of this
 * function.
 *
 */
static inline opref_t
OPLenRef2Ref(oplenref_t ref)
{
  return ref & (OPHEAP_SIZE - 1);
}

/*
 * Internal use only.  It encodes if a reference is an empty key in
 * container.
 */
static inline bool
OPLenRefIsEmpty(oplenref_t ref)
{
  return ref == 0;
}

/*
 * Internal use only.  It encodes if a reference is a deleted key in
 * container.
 */
static inline bool
OPLenRefIsDeleted(oplenref_t ref)
{
  return ref == ~0ULL;
}
#endif

/**
 * @ingroup malloc
 * @brief Converts an oplenref_t reference to a regular pointer.
 *
 * @param ref Pointer to oplenref_t.
 * @param container_size Size of the container that holds oplenref_t.
 *   If used without a container, set this parameter to 0.
 * @return A regular pointer.
 */
static inline void*
OPLenRef2Ptr(oplenref_t* ref, size_t container_size)
{
  uintptr_t uintref = (uintptr_t)ref;
  if (OPLenRefIsEmpty(*ref) || OPLenRefIsDeleted(*ref))
    return NULL;
  if (OPLenRef2Size(*ref) > container_size)
    return OPRef2Ptr(ObtainOPHeap(ref), OPLenRef2Ref(*ref));
  return (void*)(uintref + sizeof(oplenref_t));
}

/**
 * @ingroup malloc
 * @brief Converts an oplenref_t reference to a regular pointer on
 * specified heap.
 *
 * This method is useful when oplenref_t is not on OPHeap, therefore
 * we need to assist with a specific heap.
 *
 * @param ref Pointer to oplenref_t.
 * @param container_size Size of the container that holds oplenref_t.
 *   If used without a container, set this parameter to 0.
 * @param heap Address to OPHeap where the data pointer may locate at.
 * @return A regular pointer.
 */
static inline void*
OPLenRef2PtrOnHeap(oplenref_t* ref, size_t container_size, OPHeap* heap)
{
  uintptr_t uintref = (uintptr_t)ref;
  if (OPLenRefIsEmpty(*ref) || OPLenRefIsDeleted(*ref))
    return NULL;
  if (OPLenRef2Size(*ref) > container_size)
    return OPRef2Ptr(heap, OPLenRef2Ref(*ref));
  return (void*)(uintref + sizeof(oplenref_t));
}

/**
 * @ingroup malloc
 * @brief A constructor for oplenref_t to hold the input data.
 *
 * When oplenref_t used in a container, there would be some spaces
 * next to the oplenref_t address that can hold inline data. The
 * inline space is specified by the container_size. Data get copied to
 * the inline space if the data_size is smaller than the
 * container_size; otherwise the data would get copied to a newly
 * allocated object in OPHeap. In either case, oplenref_t would store
 * the information of which scheme was used.
 *
 * @param ref Pointer to oplenref_t.
 * @param data The data to copy over to OPHeap.
 * @param data_size Size of the data. This size must smaller than
 *   OPLENREF_MAX_LEN.
 * @param container_size Size of the container that holds oplenref_t.
 *   If used without a container, set this paramter to 0.
 *
 */
static inline void
OPLenRefCreate(oplenref_t* ref, void* data, size_t data_size,
               size_t container_size)
{
  uintptr_t uintref = (uintptr_t)ref;
  if (data_size > OPLENREF_MAX_LEN)
    {
      *ref = 0;
      return;
    }
  if (data_size > container_size)
    {
      void* ptr;
      ptr = OPCalloc(ObtainOPHeap(ref), 1, data_size);
      if (!ptr)
        {
          *ref = 0;
          return;
        }
      memcpy(ptr, data, data_size);
      *ref = (oplenref_t)OPPtr2Ref(ptr);
    }
  else
    {
      memcpy((void*)(uintref + sizeof(oplenref_t)), data, data_size);
      *ref = 0;
    }
  *ref |= data_size << OPHEAP_BITS;
}

/**
 * @ingroup malloc
 * @brief A destructor for oplenref_t.
 *
 * Deallocates the data stored in oplenref_t.
 *
 * @param ref Pointer to oplenref_t.
 * @param container_size Size of the container that holds oplenref_t.
 *   If used without a container, set this paramter to 0.
 *
 */
static inline void
OPLenRefDelete(oplenref_t* ref, size_t container_size)
{
  if (OPLenRefIsEmpty(*ref) || OPLenRefIsDeleted(*ref))
    return;
  if (OPLenRef2Size(*ref) > container_size)
    {
      OPDealloc(OPLenRef2Ptr(ref, container_size));
    }
  *ref = ~0ULL;
}

/**
 * @ingroup malloc
 * @brief Relace the data stored in oplenref_t.
 *
 * Will deallocate the original data stored in oplenref_t if it exists.
 *
 * @param ref Pointer to oplenref_t.
 * @param data The data to copy over to OPHeap.
 * @param data_size Size of the data.
 * @param container_size Size of the container that holds oplenref_t.
 *   If used without a container, set this paramter to 0.
 *
 */
static inline void
OPLenRefRelpace(oplenref_t* ref, void* data, size_t data_size,
                size_t container_size)
{
  if (OPLenRefIsEmpty(*ref) || OPLenRefIsDeleted(*ref))
    {
      OPLenRefCreate(ref, data, data_size, container_size);
      return;
    }
  if (data == OPLenRef2Ptr(ref, container_size))
    return;
  if (OPLenRef2Size(*ref) > container_size)
    {
      OPDealloc(OPLenRef2Ptr(ref, container_size));
    }
  OPLenRefCreate(ref, data, data_size, container_size);
}

OP_END_DECLS

#endif

/* op_malloc.h ends here */
