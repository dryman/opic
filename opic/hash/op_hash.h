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
  uint64_t hashed_val[2];
  MurmurHash3_x64_128(key, size, 421439783, hashed_val);
  return hashed_val[0];
}

#OP_END_DECLS
#endif
/* op_hash.h ends here */
