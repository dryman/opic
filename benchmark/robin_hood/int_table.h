/* int_table.h ---
 *
 * Filename: int_table.h
 * Description:
 * Author: Felix Chern
 * Maintainer:
 * Copyright: (c) 2017 Felix Chern
 * Created: Sun Jul  9 08:43:46 2017 (-0700)
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

#ifndef BENCHMARK_ROBIN_HOOD_INT_TABLE_H
#define BENCHMARK_ROBIN_HOOD_INT_TABLE_H

#include <stdbool.h>
#include "opic/common/op_macros.h"
#include "opic/hash/op_hash.h"
#include "opic/op_malloc.h"

OP_BEGIN_DECLS

typedef struct IntTable IntTable;

bool IntTableNew(OPHeap* heap, IntTable** table,
                 uint64_t num_objects, double load, size_t valsize,
                 uint64_t empty_key,
                 uint64_t delete_key);

void IntTableDestroy(IntTable* table);

uint32_t IntTableMaxProbe(IntTable* table);

uint32_t IntTableProbeStat(IntTable* table, uint32_t idx);

bool QPIntInsertCustom(IntTable* table, OPHash hasher,
                       uint64_t key, void* value);

void* QPIntGetCustom(IntTable* table, OPHash hasher, uint64_t key);

bool IntTableNew2(OPHeap* heap, IntTable** table,
                  uint64_t num_objects, double load,
                  size_t keysize, size_t valsize);

bool QPIntInsertCustom2(IntTable* table, OPHash hasher,
                        uint64_t key, void* value);

void* QPIntGetCustom2(IntTable* table, OPHash hasher, uint64_t key);


OP_END_DECLS

#endif
/* int_table.h ends here */
