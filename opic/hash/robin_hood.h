/* robin_hood.h ---
 *
 * Filename: robin_hood.h
 * Description:
 * Author: Felix Chern
 * Maintainer:
 * Copyright: (c) 2017 Felix Chern
 * Created: Sun Apr  2 07:09:50 2017 (-0700)
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

#ifndef OPIC_HASH_ROBIN_HOOD_H
#define OPIC_HASH_ROBIN_HOOD_H 1

#include <stdbool.h>
#include "opic/common/op_macros.h"

OP_BEGIN_DECLS

typedef struct RobinHoodHash RobinHoodHash;
typedef uint64_t(*OPHash)(void* key, size_t size);

bool RHHNew(OPHeap* heap, RobinHoodHash** rhh, uint64_t num_objects,
            double load, size_t keysize, size_t valsize);
void RHHDestroy(RobinHoodHash* rhh);
bool RHHPut(RobinHoodHash* rhh, OPHash hasher, void* key, void* val);
void* RHHGet(RobinHoodHash* rhh, OPHash hasher, void* key);
void* RHHDelete(RobinHoodHash* rhh, OPHash hasher, void* key);
void RHHPrintStat(RobinHoodHash* rhh);
uint64_t RHHKeysize(RobinHoodHash* rhh);
uint64_t RHHValsize(RobinHoodHash* rhh);
uint64_t RHHFixkey(void* key, size_t size);
uint64_t RHHPascal(void* key, size_t size);

static inline bool
RHHFixkeyPut(RobinHoodHash* rhh, void* key, void* val)
{
  return RHHPut(rhh, RHHFixkey, key, val);
}

static inline void*
RHHFixkeyGet(RobinHoodHash* rhh, void* key)
{
  return RHHGet(rhh, RHHFixkey, key);
}

static inline bool
RHHPascalPut(RobinHoodHash* rhh, void* key, void* val)
{
  return RHHPut(rhh, RHHPascal, key, val);
}

static inline void*
RHHPascalGet(RobinHoodHash* rhh, void* key)
{
  return RHHGet(rhh, RHHPascal, key);
}

OP_END_DECLS

#endif
/* robin_hood.h ends here */
