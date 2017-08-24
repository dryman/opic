/**
 * @file pascal_robin_hood.h
 * @brief A general hashmap/hashset/hashmultimap implementation
 * with support of multi-length keys.
 * @author: Felix Chern
 * @date Sat May 13 15:25:00 2017 (-0700)
 * @copyright 2017 Felix Chern
 */

/* This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
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

#ifndef OPIC_HASH_PASCAL_ROBIN_HOOD_HASH
#define OPIC_HASH_PASCAL_ROBIN_HOOD_HASH 1

#include <stdbool.h>
#include "opic/common/op_macros.h"
#include "opic/op_malloc.h"
#include "op_hash.h"

OP_BEGIN_DECLS

/**
 * @ingroup hash
 * @struct PascalHashTable
 * @brief An opaque object that manages associations of key-value pairs.
 *
 * This object is not thread safe.
 */
typedef struct PascalHashTable PascalHashTable;

/**
 * @relates PascalHashTable
 * @brief Constructor for PascalHashTable.
 *
 * @param heap OPHeap instance.
 * @param num_objects number of object we decided to put in.
 * @param load (0.0-1.0) how full the table could be before expansion.
 * @param key_inline_size Size to store the key inline. If the key size
 *   is larger than this value, the key would be copied to OPHeap and get
 *   referenced by a pointer. If key_inline_size is set to 0, pointer
 *   is always used.
 * @param valsize length of the value measured in bytes. This value
 * can be zero for hashset.
 * @return PascalHashTable instance if allocation succeeded, else return NULL.
 */
PascalHashTable* PHNew(OPHeap* heap, uint64_t num_objects, double load,
                       size_t key_inline_size, size_t valsize);

/**
 * @relates PascalHashTable
 * @brief Destructor for PascalHashTable
 *
 * @param rhh PascalHashTable instance to destroy.
 *
 * All the keys managed by this instance will get dealloc as well.
 * User need to manage the value deallocation prior calling this method.
 */
void PHDestroy(PascalHashTable* rhh);

/**
 * @relates PascalHashTable
 * @brief Associates the specified key and value with custom
 * hash function.
 *
 * @param rhh PascalHashTable instance.
 * @param hasher hash function.
 * @param key pointer the the key
 * @param keysize length of key data, measured in bytes.
 * @param val pointer to the value.
 * @return true if the operation succeeded, false otherwise.
 *
 * The content pointed by key and val will be copied into the hash
 * table.  If the value size were 0, only the key get copied. When
 * there's a key collision, the coresponding value get replaced.
 *
 * If the inserted key-value pairs exceeded the original size user
 * configured, the hash table will resized with a larger capacity. If
 * the resize failed, false is returned.
 */
bool PHInsertCustom(PascalHashTable* rhh, OPHash hasher,
                    void* key, size_t keysize, void* val);

/**
 * @relates PascalHashTable
 * @brief Update or insert depends on whether the key already exists in
 * the hash table using custom hash function.
 *
 * @param rhh RobinHoodHash instance.
 * @param hasher hash function.
 * @param key pointer to the key.
 * @param keysize length of the key data, measured in bytes.
 * @param val_ref reference of value pointer.
 * @param is_duplicate reference of duplication boolean variable.
 * @return true if the operation succeeded, false otherwise.
 *
 * This method does not insert the value automatically, instead it provides
 * the pointer to the address where value can be inserted or overriden.
 *
 * If the inserted key-value pairs exceeded the original size user configured,
 * the hash table will resized with a larger capacity. If the resize failed,
 * false is returned.
 */
bool PHUpsertCustom(PascalHashTable* rhh, OPHash hasher,
                    void* key, size_t keysize, void** val_ref,
                    bool* is_duplicate);

/**
 * @relates PascalHashTable
 * @brief Obtain the value associated with the key and hash function.
 * Returns NULL if the key was not found.
 *
 * @param rhh PascalHashTable instance.
 * @param hasher hash function.
 * @param key pointer to the key.
 * @param keysize length of the key data. measured in bytes.
 * @return pointer to the value if found, NULL otherwise.
 *
 * If the value size were set to 0, PHGetCustom would still return a
 * pointer to where it would store the value. User can still use the
 * returned value to exam if the key were present in the hash table.
 */
void* PHGetCustom(PascalHashTable* rhh, OPHash hasher,
                  void* key, size_t keysize);

/**
 * @relates PascalHashTable
 * @brief Deletes the key-value entry with specified hash function.
 *
 * @param rhh PascalHashTable instance.
 * @param hasher hash function.
 * @param key pointer to the key.
 * @param keysize length of the key data, measured in bytes.
 * @return pointer to the value if found, NULL otherwise.
 *
 * The key would get deallocated after deletion. Table will resize
 * when many entries are deleted.
 */
void* PHDeleteCustom(PascalHashTable* rhh, OPHash hasher,
                     void* key, size_t keysize);

/**
 * @relates PascalHashTable
 * @brief Associates the specified key and value using default hash
 * function.
 *
 * @param rhh PascalHashTable instance.
 * @param key pointer the the key
 * @param keysize length of key data, measured in bytes.
 * @param val pointer to the value.
 * @return true if the operation succeeded, false otherwise.
 *
 * The content pointed by key and val will be copied into the hash
 * table.  If the value size were 0, only the key get copied. When
 * there's a key collision, the coresponding value get replaced.
 *
 * If the inserted key-value pairs exceeded the original size user
 * configured, the hash table will resized with a larger capacity. If
 * the resize failed, false is returned.
 *
 */
static inline bool
PHInsert(PascalHashTable* rhh, void* key, size_t keysize, void* val)
{
  return PHInsertCustom(rhh, OPDefaultHash, key, keysize, val);
}

/**
 * @relates PascalHashTable
 * @brief Update or insert depends on whether the key already exists in
 * the hash table.
 *
 * @param rhh RobinHoodHash instance.
 * @param key pointer to the key.
 * @param keysize length of the key data, measured in bytes.
 * @param val_ref reference of value pointer.
 * @param is_duplicate reference of duplication boolean variable.
 * @return true if the operation succeeded, false otherwise.
 *
 * This method does not insert the value automatically, instead it provides
 * the pointer to the address where value can be inserted or overriden.
 *
 * If the inserted key-value pairs exceeded the original size user configured,
 * the hash table will resized with a larger capacity. If the resize failed,
 * false is returned.
 */
static inline bool
PHUpsert(PascalHashTable* rhh, void* key, size_t keysize,
         void** val_ref, bool* is_duplicate)
{
  return PHUpsertCustom(rhh, OPDefaultHash, key, keysize,
                        val_ref, is_duplicate);
}

/**
 * @relates PascalHashTable
 * @brief Obtain the value associated with the key using default hash
 * function. Returns NULL if the key was not found.
 *
 * @param rhh PascalHashTable instance.
 * @param key pointer to the key.
 * @param keysize length of the key data. measured in bytes.
 * @return pointer to the value if found, NULL otherwise.
 *
 * If the value size were set to 0, PHGetCustom would still return a
 * pointer to where it would store the value. User can still use the
 * returned value to exam if the key were present in the hash table.
 */
static inline void*
PHGet(PascalHashTable* rhh, void* key, size_t keysize)
{
  return PHGetCustom(rhh, OPDefaultHash, key, keysize);
}

/**
 * @relates PascalHashTable
 * @brief Deletes the key-value entry using default hash function.
 *
 * @param rhh PascalHashTable instance.
 * @param key pointer to the key.
 * @param keysize length of the key data, measured in bytes.
 * @return pointer to the value if found, NULL otherwise.
 *
 * The key would get deallocated after deletion. Table will resize
 * when many entries are deleted.
 */
static inline void*
PHDelete(PascalHashTable* rhh, void* key, size_t keysize)
{
  return PHDeleteCustom(rhh, OPDefaultHash, key, keysize);
}

/**
 * @relates PascalHashTable
 * @brief Obtain the number of objects stored in this hash table.
 */
uint64_t PHObjcnt(PascalHashTable* rhh);

/**
 * @relates PascalHashTable
 * @brief Obtain the number of objects can be stored in this hash table.
 */
uint64_t PHCapacity(PascalHashTable* rhh);

/**
 * @relates PascalHashTable
 * @brief Obtain the size of the key that can be stored inline in the
 * hash table. If the size of the key is larger than this size, the key
 * would not be inline but allocated somewhere in the OPHeap.
 */
size_t PHKeyInlineSize(PascalHashTable* rhh);

/**
 * @relates PascalHashTable
 * @brief Obtain the size of the value configured for this hash table.
 */
size_t PHValSize(PascalHashTable* rhh);

/**
 * @relates PascalHashTable
 * @brief Iterates over all key-value pairs in this hash table with
 * user specified context.
 *
 * @param rhh PascalHashTable instance.
 * @param iterator function pointer to user defined iterator function.
 * @param context user defined context.
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
 * // PHIterate takes in a PascalHashTable object, a fuction pointer
 * // OPHashIterator and a user defined context for iteration.
 * PHIterate(rhh, &my_iterator, &my_s);
 * @endcode
 */
void PHIterate(PascalHashTable* rhh,
               OPHashIterator iterator, void* context);

/**
 * @relates PascalHashTable
 * @brief Prints the accumulated count for each probing number.
 */
void PHPrintStat(PascalHashTable* rhh);

uint32_t PHMaxProbe(PascalHashTable* rhh);

uint32_t PHProbeStat(PascalHashTable* rhh, uint32_t idx);

OP_END_DECLS

#endif
/* pascal_robin_hood.h ends here */
