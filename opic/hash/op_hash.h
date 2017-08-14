/**
 * @file op_hash.h
 * @author Felix Chern
 * @date Sat Apr 29 16:28:18 2017 (-0700)
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

#ifndef OPIC_HASH_OP_HASH_H
#define OPIC_HASH_OP_HASH_H 1

#include "opic/common/op_macros.h"
#include "cityhash.h"

OP_BEGIN_DECLS

/**
 * @defgroup hash
 */

/**
 * @ingroup hash
 * @typedef OPHash
 * @brief Hash function interface.
 *
 * @param key pointer to the key
 * @param size size of the key
 */
typedef uint64_t(*OPHash)(void* key, size_t size);

/**
 * @ingroup hash
 * @brief HashTable iterator interface.
 *
 * @param key pointer to key
 * @param value pointer to value
 * @param keysize length of the key
 * @param valsize length of the value
 * @param context user defined context
 *
 * @see RHHIterate for example usage.
 */
typedef void(*OPHashIterator)(void* key, void* value,
                              size_t keysize, size_t valsize,
                              void* context);

/**
 * @ingroup hash
 * @brief Default hash function.
 *
 * This is the implementation of OPHash.
 */
static inline
uint64_t OPDefaultHash(void* key, size_t size)
{
  return cityhash64((const uint8_t*)key, size);
}

/**
 * @ingroup hash
 * @brief Callback type for doing upsert operation with funnel.
 *
 * @param key The key upserting to hash table
 * @param table_value The value in table (old value).
 * @param funnel_value The value in funnel (new value).
 * @param ctx User defined context.
 * @param keysize Size of the key.
 * @param valsize Both table_value and funnel_value has same size valsize.
 * @param ctxsize Size of the context.
 * @param is_duplicate True when this upsert operation is on a duplicate
 * key (update case). False when this key is newly inserted.
 */
typedef void(*OPFunnelUpsertCB)(void* key,
                                void* table_value,
                                void* funnel_value,
                                void* ctx,
                                size_t keysize, size_t valsize,
                                size_t ctxsize, bool is_duplicate);

/**
 * @ingroup hash
 * @brief Callback type for doing get operation with funnel.
 *
 * @param key The key upserting to hash table
 * @param value The value in table.
 * @param ctx User defined context.
 * @param keysize Size of the key.
 * @param valsize Size of the value.
 * @param ctxsize Size of the context.
 */
typedef void(*OPFunnelGetCB)(void* key, void* value, void* ctx,
                             size_t keysize, size_t valsize,
                             size_t ctxsize);

/**
 * @ingroup hash
 * @brief Callback type for doing delete operation with funnel.
 *
 * @param key The key upserting to hash table
 * @param value The value in table.
 * @param ctx User defined context.
 * @param keysize Size of the key.
 * @param valsize Size of the value.
 * @param ctxsize Size of the context.
 */
typedef void(*OPFunnelDeleteCB)(void* key, void* value, void* ctx,
                                size_t keysize, size_t valsize,
                                size_t ctxsize);

#ifndef DOXYGEN_SKIP

typedef union FunnelCB
{
  OPFunnelUpsertCB upsertcb;
  OPFunnelGetCB getcb;
  OPFunnelDeleteCB deletecb;
} FunnelCB __attribute__((__transparent_union__));

#endif

OP_END_DECLS

#endif
/* op_hash.h ends here */
