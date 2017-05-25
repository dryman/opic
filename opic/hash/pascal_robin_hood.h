/**
 * @file pascal_robin_hood.h
 * @brief A general hashmap/hashset/hashmultimap implementation
 * with support of multi-length keys.
 * @authorr: Felix Chern
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
 * @struct PascalRobinHoodHash
 * @brief An opaque object that manages associations of key-value pairs.
 *
 * PascalRobinHoodHash uses pointers to manage keys that has different
 * sizes.  This doesn't make PascalRobinHoodHash harder to serialize,
 * but does create some overhead: allocations and deallocations
 * are invoked during insert and delete. Pointers may also make cache
 * efficiancy worse compare to RobinHoodHash　.
 *
 * This object is not thread safe.
 */
typedef struct PascalRobinHoodHash PascalRobinHoodHash;

/**
 * @relates PascalRobinHoodHash
 * @brief Constructor for PascalRobinHoodHash.
 *
 * @param heap OPHeap instance.
 * @param rhh_ref reference to the PascalRobinHoodHash pointer for
 * assignging PascalRobinHoodHash instance.
 * @param num_objects number of object we decided to put in.
 * @param load (0.0-1.0) how full the table could be before expansion.
 * @param valsize length of the value measured in bytes. This value
 * can be zero for hashset.
 * @return true when the allocation succeeded, false otherwise.
 */
bool PRHHNew(OPHeap* heap, PascalRobinHoodHash** rhh_ref,
             uint64_t num_objects, double load, size_t valsize);

/**
 * @relates PascalRobinHoodHash
 * @brief Destructor for PascalRobinHoodHash
 *
 * @param rhh PascalRobinHoodHash instance to destroy.
 *
 * All the keys managed by this instance will get dealloc as well.
 * User need to manage the values by themselves.
 */
void PRHHDestroy(PascalRobinHoodHash* rhh);

/**
 * @relates PascalRobinHoodHash
 * @brief Associates the specified key and value with custom
 * hash function.
 *
 * @param rhh PascalRobinHoodHash instance.
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
bool PRHHInsertCustom(PascalRobinHoodHash* rhh, OPHash hasher,
                      void* key, size_t keysize, void* val);

bool PRHHUpsertCustom(PascalRobinHoodHash* rhh, OPHash hasher,
                      void* key, size_t keysize, void** val_ref,
                      bool* is_duplicate);

/**
 * @relates PascalRobinHoodHash
 * @brief Obtain the value associated with the key and hash function.
 * Returns NULL if the key was not found.
 *
 * @param rhh PascalRobinHoodHash instance.
 * @param hasher hash function.
 * @param key pointer to the key.
 * @param keysize length of the key data. measured in bytes.
 * @return pointer to the value if found, NULL otherwise.
 *
 * If the value size were set to 0, PRHHGetCustom would still return a
 * pointer to where it would store the value. User can still use the
 * returned value to exam if the key were present in the hash table.
 */
void* PRHHGetCustom(PascalRobinHoodHash* rhh, OPHash hasher,
                    void* key, size_t keysize);

/**
 * @relates PascalRobinHoodHash
 * @brief Deletes the key-value entry with specified hash function.
 *
 * @param rhh PascalRobinHoodHash instance.
 * @param hasher hash function.
 * @param key pointer to the key.
 * @param keysize length of the key data, measured in bytes.
 * @return pointer to the value if found, NULL otherwise.
 *
 * The key would get deallocated after deletion. Table will resize
 * when many entries are deleted.
 */
void* PRHHDeleteCustom(PascalRobinHoodHash* rhh, OPHash hasher,
                       void* key, size_t keysize);

/**
 * @relates PascalRobinHoodHash
 * @brief Associates the specified key and value using default hash
 * function.
 *
 * @param rhh PascalRobinHoodHash instance.
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
PRHHInsert(PascalRobinHoodHash* rhh, void* key, size_t keysize, void* val)
{
  return PRHHInsertCustom(rhh, OPDefaultHash, key, keysize, val);
}

static inline bool
PRHHUpsert(PascalRobinHoodHash* rhh, void* key, size_t keysize,
           void** val_ref, bool* is_duplicate)
{
  return PRHHUpsertCustom(rhh, OPDefaultHash, key, keysize,
                          val_ref, is_duplicate);
}

/**
 * @relates PascalRobinHoodHash
 * @brief Obtain the value associated with the key using default hash
 * function. Returns NULL if the key was not found.
 *
 * @param rhh PascalRobinHoodHash instance.
 * @param key pointer to the key.
 * @param keysize length of the key data. measured in bytes.
 * @return pointer to the value if found, NULL otherwise.
 *
 * If the value size were set to 0, PRHHGetCustom would still return a
 * pointer to where it would store the value. User can still use the
 * returned value to exam if the key were present in the hash table.
 */
static inline void*
PRHHGet(PascalRobinHoodHash* rhh, void* key, size_t keysize)
{
  return PRHHGetCustom(rhh, OPDefaultHash, key, keysize);
}

/**
 * @relates PascalRobinHoodHash
 * @brief Deletes the key-value entry using default hash function.
 *
 * @param rhh PascalRobinHoodHash instance.
 * @param key pointer to the key.
 * @param keysize length of the key data, measured in bytes.
 * @return pointer to the value if found, NULL otherwise.
 *
 * The key would get deallocated after deletion. Table will resize
 * when many entries are deleted.
 */
static inline void*
PRHHDelete(PascalRobinHoodHash* rhh, void* key, size_t keysize)
{
  return PRHHDeleteCustom(rhh, OPDefaultHash, key, keysize);
}

/**
 * @relates PascalRobinHoodHash
 * @brief Obtain the number of objects stored in this hash table.
 */
uint64_t PRHHObjcnt(PascalRobinHoodHash* rhh);

/**
 * @relates PascalRobinHoodHash
 * @brief Obtain the number of objects can be stored in this hash table.
 */
uint64_t PRHHCapacity(PascalRobinHoodHash* rhh);

/**
 * @relates PascalRobinHoodHash
 * @brief Obtain the size of the value configured for this hash table.
 */
size_t RHHValsize(PascalRobinHoodHash* rhh);

/**
 * @relates PascalRobinHoodHash
 * @brief Iterates over all key-value pairs in this hash table with
 * user specified context.
 *
 * @param rhh PascalRobinHoodHash instance.
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
 * // PRHHIterate takes in a PascalRobinHoodHash object, a fuction pointer
 * // OPHashIterator and a user defined context for iteration.
 * PRHHIterate(rhh, &my_iterator, &my_s);
 * @endcode
 */
void PRHHIterate(PascalRobinHoodHash* rhh,
                 OPHashIterator iterator, void* context);

/**
 * @relates PascalRobinHoodHash
 * @brief Prints the accumulated count for each probing number.
 */
void PRHHPrintStat(PascalRobinHoodHash* rhh);

OP_END_DECLS

#endif
/* pascal_robin_hood.h ends here */
