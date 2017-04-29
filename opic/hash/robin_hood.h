/**
 * @file robin_hood.h
 * @brief A general hashmap/hashset/hashmultimap implemantation using
 * robin hood hashing.
 * @author Felix Chern
 * @date Sun Apr  2 07:09:50 2017 (-0700)
 * Copyright: (c) 2017 Felix Chern
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

#ifndef OPIC_HASH_ROBIN_HOOD_H
#define OPIC_HASH_ROBIN_HOOD_H 1

#include <stdbool.h>
#include "opic/common/op_macros.h"
#include "opic/op_malloc.h"

OP_BEGIN_DECLS

/**
 * @struct RobinHoodHash　
 * @brief Opaque object for fixed length key hashmap/hashset/hashmultimap.
 *
 * @todo there is a wide space character "　" appended after
 * "RobinHoodHash" in this document. Somehow doxygen (1.8.13) cannot
 * process "RobinHoodHash" as a struct name. Any character edit to the
 * string works, except the form "RobinHoodHash". As a workaround, I use
 * a wide space character to finish up the document first. The real struct
 * in code does not use the wide space character.
 */
typedef struct RobinHoodHash RobinHoodHash;

/**
 * @typedef OPHash
 * @brief Hash function interface.
 *
 * @param key pointer to the key
 * @param size size of the key
 */
typedef uint64_t(*OPHash)(void* key, size_t size);

/**
 * @relates RobinHoodHash　
 * @brief HashTable iterator interface.
 *
 * @param key pointer to key
 * @param value pointer to value
 * @param keysize length of the key
 * @param valsize length of the value
 * @param context user defined context
 *
 * Usage example:
 *
 * @code
 * // Function interface matches OPHashIterator
 * void my_iterator(void* key, void* value,
 *                  size_t keysize, size_t valsize,
 *                  void* context)
 * {
 *   // Obtain the object we passed in.
 *   struct MyStruct* my_s = (struct MyStruct*) context;
 *
 *   // assumes both key and value were null terminated string
 *   printf("key: %s, value: %s\n", key, value);
 * }
 *
 * // User defined context
 * struct MyStruct my_s;
 *
 * // RHHIterate takes in a RobinHoodHash object, a fuction pointer
 * // OPHashIterator and a user defined context for iteration.
 * RHHIterate(rhh, &my_iterator, &my_s);
 * @endcode
 *
 */
typedef void(*OPHashIterator)(void* key, void* value,
                              size_t keysize, size_t valsize,
                              void* context);

/**
 * @relates RobinHoodHash　
 * @brief Default hash function for RobinHoodHash.
 *
 * This is the implementation of OPHash.
 */
uint64_t RHHFixkey(void* key, size_t size);


/**
 * @relates RobinHoodHash　
 * @brief Constructor for RobinHoodHash.
 *
 * @param heap OPHeap instance.
 * @param rhh_ref reference to the RobinHoodHash pointer for assigining
 * RobinHoodHash instance.
 * @param uint64_t num_objects number of objects we decided to put in.
 * @param double load (0.0-1.0) how full the hash table could be
 * before expansion.
 * @param size_t keysize length of key measured in bytes. Cannot be zero.
 * @param size_t valsize length of value measured in bytes. This vlaue
 * can be zero and the hash table would work like a hash set.
 * @return true when the allocation succeeded, false otherwise.
 */
bool RHHNew(OPHeap* heap, RobinHoodHash** rhh_ref, uint64_t num_objects,
            double load, size_t keysize, size_t valsize);
void RHHDestroy(RobinHoodHash* rhh);

bool RHHPutCustom(RobinHoodHash* rhh, OPHash hasher, void* key, void* val);
void* RHHGetCustom(RobinHoodHash* rhh, OPHash hasher, void* key);
void* RHHDeleteCustom(RobinHoodHash* rhh, OPHash hasher, void* key);

uint64_t RHHObjcnt(RobinHoodHash* rhh);
uint64_t RHHCapacity(RobinHoodHash* rhh);
size_t RHHKeysize(RobinHoodHash* rhh);
size_t RHHValsize(RobinHoodHash* rhh);
void RHHIterate(RobinHoodHash* rhh, OPHashIterator iterator, void* context);
void RHHPrintStat(RobinHoodHash* rhh);

static inline bool
RHHPut(RobinHoodHash* rhh, void* key, void* val)
{
  return RHHPutCustom(rhh, RHHFixkey, key, val);
}

static inline void*
RHHGet(RobinHoodHash* rhh, void* key)
{
  return RHHGetCustom(rhh, RHHFixkey, key);
}

static inline void*
RHHDelete(RobinHoodHash* rhh, void* key)
{
  return RHHDeleteCustom(rhh, RHHFixkey, key);
}

OP_END_DECLS

#endif
/* robin_hood.h ends here */
