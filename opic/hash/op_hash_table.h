/**
 * @file op_hash_table.h
 * @brief A general hashmap/hashset/hashmultimap implemantation using
 * robin hood hashing.
 * @author Felix Chern
 * @date Sun Apr  2 07:09:50 2017 (-0700)
 * @copyright 2017 Felix Chern
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

#ifndef OPIC_HASH_HASH_TABLE_H
#define OPIC_HASH_HASH_TABLE_H 1

#include <stdbool.h>
#include "opic/common/op_macros.h"
#include "op_hash.h"
#include "opic/op_malloc.h"

OP_BEGIN_DECLS

/**
 * @ingroup hash
 * @struct OPHashTable
 * @brief An opaque object that manage associations of fixed length
 * key-value pairs.
 *
 * The size of key and value is configured at the construction time of
 * OPHashTable, and can not be changed later. This design is similar
 * to fixed length fields `CHAR(30)` in SQL which improve both space
 * and runtime efficiencies.
 *
 * Note that user can spcify size of value to 0 to make OPHashTable
 * as a hash set. Similarly, make value size `sizeof(opref_t)` and
 * store a opref_t referencing another container (binary serach tree
 * or whatever), can turn OPHashTable into a hash-multiset.
 *
 * This object is not thread safe.
 *
 */
typedef struct OPHashTable OPHashTable;

/**
 * @ingroup hash
 * @struct HTFunnel
 * @brief An opaque object for doing massive update or quries on
 * OPHashTable.
 *
 * This object is not thread safe.
 *
 */
typedef struct HTFunnel HTFunnel;

/**
 * @relates OPHashTable
 * @brief Constructor for OPHashTable.
 *
 * @param heap OPHeap instance.
 * @param num_objects number of objects we decided to put in.
 * @param load (0.0-1.0) how full the hash table could be
 * before expansion.
 * @param keysize length of key measured in bytes. Cannot be zero.
 * @param valsize length of value measured in bytes. This vlaue
 * can be zero and the hash table would work like a hash set.
 * @return OPHashTable instance if allocation succeeded, else return NULL.
 */
OPHashTable* HTNew(OPHeap* heap, uint64_t num_objects,
                   double load, size_t keysize, size_t valsize);

/**
 * @relates OPHashTable
 * @brief Destructor for OPHashTable.
 *
 * @param table the OPHashTable instance to destory.
 */
void HTDestroy(OPHashTable* table);

/**
 * @relates OPHashTable
 * @brief Associates the specified key with the specified value in
 * OPHashTable with specified hash function.
 *
 * @param table OPHashTable instance.
 * @param hasher hash function.
 * @param key pointer to the key.
 * @param val pointer to the value.
 * @return true if the operation succeeded, false otherwise.
 *
 * The content pointed by key and val will be copied into the hash table.
 * If the value size were 0, only the key get copied. When there's a
 * key collision, the coresponding value get replaced.
 *
 * If the inserted key-value pairs exceeded the original size user configured,
 * the hash table will resized with a larger capacity. If the resize failed,
 * false is returned.
 */
bool HTInsertCustom(OPHashTable* table, OPHash hasher, void* key, void* val);

/**
 * @relates OPHashTable
 * @brief Update or insert depends on whether the key already exists in
 * the hash table using custom hash function.
 *
 * @param table OPHashTable instance.
 * @param hasher hash function.
 * @param key pointer to the key.
 * @param val_ref reference of value pointer.
 * @param is_duplicate reference of duplication boolean variable.
 * @return true if the operation succeeded, false otherwise.
 *
 * This method does not insert the value automatically, instead it provides
 * the pointer to the address where value can be inserted or overriden.
 *
 * @code
 * int key;
 * int* value;
 * bool is_duplicate;
 * OPHashTable *table;
 * // create a robin hood hash where key and value are both integers.
 * HTNew(heap, &table, 30, 0.8, sizeof(int), sizeof(int));
 * key = 5;
 * HTUpsert(table, OPDefaultHash, &key, (void**)&val, &is_duplicate);
 * // different logic depends on is_duplicate.
 * // User can use this interface to create a hash multimap.
 * if (is_duplicate)
 *   *value = 7;
 * else
 *   *value = 8;
 * @endcode
 *
 * If the inserted key-value pairs exceeded the original size user configured,
 * the hash table will resized with a larger capacity. If the resize failed,
 * false is returned.
 */
bool HTUpsertCustom(OPHashTable* table, OPHash hasher,
                    void* key, void** val_ref, bool* is_duplicate);

/**
 * @relates OPHashTable
 * @brief Obtain the value associated with the specified key and hash
 * function. Returns NULL if the key was not found.
 *
 * @param table OPHashTable instance.
 * @param hasher hash function.
 * @param key pointer to the key.
 * @return pointer to the value if found, else NULL.
 *
 * If the value size were set to 0, HTGetCustom would still return a pointer
 * to where it would store the value. User can still use the returned value to
 * exam if the key were present in the hash table.
 */
void* HTGetCustom(OPHashTable* table, OPHash hasher, void* key);

/**
 * @relates OPHashTable
 * @brief Deletes the key-value entry in hash table with specified hasher.
 *
 * @param table OPHashTable instance.
 * @param hasher hash function.
 * @param key pointer to the key.
 * @return pointer to the value if it found, else NULL.
 *
 * The hash table may shrink if too many entries were deleted.
 */
void* HTDeleteCustom(OPHashTable* table, OPHash hasher, void* key);

/**
 * @relates OPHashTable
 * @brief Associates the specified key with the specified value in
 * OPHashTable using the default hash function.
 *
 * @param table OPHashTable instance.
 * @param key pointer to the key.
 * @param val pointer to the value.
 * @return true if the operation succeeded, false otherwise.
 *
 * The content pointed by key and val will be copied into the hash table.
 * If the value size were 0, only the key get copied. When there's a
 * key collision, the coresponding value get replaced.
 *
 * If the inserted key-value pairs exceeded the original size user configured,
 * the hash table will resized with a larger capacity. If the resize failed,
 * false is returned.
 */
static inline bool
HTInsert(OPHashTable* table, void* key, void* val)
{
  return HTInsertCustom(table, OPDefaultHash, key, val);
}

/**
 * @relates OPHashTable
 * @brief Update or insert depends on whether the key already exists in
 * the hash table.
 *
 * @param table OPHashTable instance.
 * @param key pointer to the key.
 * @param val_ref reference of value pointer.
 * @param is_duplicate reference of duplication boolean variable.
 * @return true if the operation succeeded, false otherwise.
 *
 * This method does not insert the value automatically, instead it provides
 * the pointer to the address where value can be inserted or overriden.
 *
 * @code
 * int key;
 * int* value;
 * bool is_duplicate;
 * OPHashTable *table;
 * // create a robin hood hash where key and value are both integers.
 * HTNew(heap, &table, 30, 0.8, sizeof(int), sizeof(int));
 * key = 5;
 * HTUpsert(table, &key, (void**)&val, &is_duplicate);
 * // different logic depends on is_duplicate.
 * // User can use this interface to create a hash multimap.
 * if (is_duplicate)
 *   *value = 7;
 * else
 *   *value = 8;
 * @endcode
 *
 * If the inserted key-value pairs exceeded the original size user configured,
 * the hash table will resized with a larger capacity. If the resize failed,
 * false is returned.
 */
static inline bool
HTUpsert(OPHashTable* table, void* key, void** val_ref, bool* is_duplicate)
{
  return HTUpsertCustom(table, OPDefaultHash, key, val_ref, is_duplicate);
}

/**
 * @relates OPHashTable
 * @brief Obtain the value associated with the specified key using
 * the default hash function. Returns NULL if the key was not found.
 *
 * @param table OPHashTable instance.
 * @param key pointer to the key.
 * @return pointer to the value if found, else NULL.
 *
 * If the value size were set to 0, HTGetCustom would still return a pointer
 * to where it would store the value. User can still use the returned value to
 * exam if the key were present in the hash table.
 */
static inline void*
HTGet(OPHashTable* table, void* key)
{
  return HTGetCustom(table, OPDefaultHash, key);
}

/**
 * @relates OPHashTable
 * @brief Deletes the key-value entry in hash table using the default
 * hash function.
 *
 * @param table OPHashTable instance.
 * @param key pointer to the key.
 * @return pointer to the value if it found, else NULL.
 *
 * The hash table may shrink if too many entries were deleted.
 */
static inline void*
HTDelete(OPHashTable* table, void* key)
{
  return HTDeleteCustom(table, OPDefaultHash, key);
}

/**
 * @relates OPHashTable
 * @brief Obtain the number of objects stored in this hash table.
 */
uint64_t HTObjcnt(OPHashTable* table);

/**
 * @relates OPHashTable
 * @brief Obtain the number of objects can be stored in this hash table.
 */
uint64_t HTCapacity(OPHashTable* table);

/**
 * @relates OPHashTable
 * @brief Obtain the size of the key configured for this hash table.
 */
size_t HTKeySize(OPHashTable* table);

/**
 * @relates OPHashTable
 * @brief Obtain the size of the value configured for this hash table.
 */
size_t HTValSize(OPHashTable* table);

/**
 * @relates OPHashTable
 * @brief Iterates over all key-value pairs in this hash table with
 * user specified context.
 *
 * @param table OPHashTable instance.
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
 * // HTIterate takes in a OPHashTable object, a fuction pointer
 * // OPHashIterator and a user defined context for iteration.
 * HTIterate(table, &my_iterator, &my_s);
 * @endcode
 */
void HTIterate(OPHashTable* table, OPHashIterator iterator, void* context);

/**
 * @relates OPHashTable
 * @brief Prints the accumulated count for each probing number.
 *
 * Deprecated. Use HTProbeStat instead.
 */
void HTPrintStat(OPHashTable* table);

uint32_t HTMaxProbe(OPHashTable* table);

uint32_t HTProbeStat(OPHashTable* table, uint32_t idx);

int HTGetProbeCustom(OPHashTable* table, OPHash hasher, void* key);

static inline
int HTGetProbe(OPHashTable* table, void* key)
{
  return HTGetProbeCustom(table, OPDefaultHash, key);
}

HTFunnel* HTFunnelNewCustom(OPHashTable* table,
                            OPHash hasher,
                            FunnelCB callback,
                            size_t slotsize,
                            size_t partition_size);

static inline
HTFunnel* HTFunnelNew(OPHashTable* table,
                      FunnelCB callback,
                      size_t slotsize,
                      size_t partition_size)
{
  return HTFunnelNewCustom(table, OPDefaultHash, callback,
                           slotsize, partition_size);
}

void HTFunnelDestroy(HTFunnel* funnel);

void HTFunnelPreHashInsert(HTFunnel* funnel,
                           uint64_t hashed_key,
                           void* key, void* value);

void HTFunnelInsert(HTFunnel* funnel, void* key, void* value);

void HTFunnelInsertFlush(HTFunnel* funnel);

void HTFunnelPreHashUpsert(HTFunnel* funnel,
                           uint64_t hashed_key,
                           void* key, void* value,
                           void* context, size_t ctxsize);

void HTFunnelUpsert(HTFunnel* funnel,
                    void* key, void* value,
                    void* context, size_t ctxsize);

void HTFunnelUpsertFlush(HTFunnel* funnel);

void HTFunnelPreHashGet(HTFunnel* funnel, uint64_t hashed_key,
                        void* key, void* context, size_t ctxsize);

void HTFunnelGet(HTFunnel* funnel, void* key, void* context, size_t ctxsize);

void HTFunnelGetFlush(HTFunnel* funnel);

void HTFunnelPreHashDelete(HTFunnel* funnel, uint64_t hashed_key,
                           void* key, void* context, size_t ctxsize);

void HTFunnelDelete(HTFunnel* funnel, void* key,
                    void* context, size_t ctxsize);

void HTFunnelDeleteFlush(HTFunnel* funnel);

OP_END_DECLS

#endif

/* op_hash_table.h ends here */
