/* generic_table.h ---
 *
 * Filename: generic_table.h
 * Description:
 * Author: Felix Chern
 * Maintainer:
 * Copyright: (c) 2017 Felix Chern
 * Created: Mon Jun 26 22:26:09 2017 (-0700)
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


#ifndef BENCHMARK_ROBIN_HOOD_GENERIC_TABLE_H
#define BENCHMARK_ROBIN_HOOD_GENERIC_TABLE_H 1

#include <stdbool.h>
#include "opic/common/op_macros.h"
#include "opic/hash/op_hash.h"
#include "opic/op_malloc.h"

OP_BEGIN_DECLS

typedef struct GenericTable GenericTable;

bool TableNew(OPHeap* heap, GenericTable** table,
              uint64_t num_objects, double load,
              size_t keysize, size_t valsize, bool is_chain_table);

void TableDestroy(GenericTable* table);

void TablePrintStat(GenericTable* table);

uint32_t TableMaxProbe(GenericTable* table);

uint32_t TableProbeStat(GenericTable* table, uint32_t idx);

bool LPInsertCustom(GenericTable* table, OPHash hasher,
                    void* key, void* value);

bool ChainInsertCustom(GenericTable* table, OPHash hasher,
                       void* key, void* value);

void* LPGetCustom(GenericTable* table, OPHash hasher, void* key);

bool QPInsertCustom(GenericTable* table, OPHash hasher,
                    void* key, void* value);

void* QPGetCustom(GenericTable* table, OPHash hasher, void* key);

void* QPDelCustom(GenericTable* table, OPHash hasher, void* key);

bool DHInsertCustom(GenericTable* table, OPHash hasher,
                    void* key, void* value);

void* DHGetCustom(GenericTable* table, OPHash hasher, void* key);

void* ChainGetCustom(GenericTable* table, OPHash hasher, void* key);

OP_END_DECLS

#endif

/* generic_table.h ends here */
