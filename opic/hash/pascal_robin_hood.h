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

typedef struct PascalRobinHoodHash PascalRobinHoodHash;

bool PRHHNew(OPHeap* heap, PascalRobinHoodHash** rhh_ref,
             uint64_t num_objects, double load, size_t valsize);

void PRHHDestroy(PascalRobinHoodHash* rhh);

bool PRHHPutCustom(PascalRobinHoodHash* rhh, OPHash hasher,
                   void* key, size_t keysize, void* val);

void* PRHHGetCustom(PascalRobinHoodHash* rhh, OPHash hasher,
                    void* key, size_t keysize);

void* PRHHDeleteCustom(PascalRobinHoodHash* rhh, OPHash hasher,
                       void* key, size_t keysize);

uint64_t PRHHObjcnt(PascalRobinHoodHash* rhh);

uint64_t PRHHCapacity(PascalRobinHoodHash* rhh);

size_t RHHValsize(PascalRobinHoodHash* rhh);

OP_END_DECLS

#endif
/* pascal_robin_hood.h ends here */
