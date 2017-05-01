/* rhh_bkv_v4qu.h ---
 *
 * Filename: rhh_bkv_v4qu.h
 * Description:
 * Author: Felix Chern
 * Maintainer:
 * Copyright: (c) 2017 Felix Chern
 * Created: Sun Apr 30 16:05:50 2017 (-0700)
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


#ifndef BENCHMARK_ROBIN_HOOD_RHH_BKV_V4QU_H
#define BENCHMARK_ROBIN_HOOD_RHH_BKV_V4QU_H 1

#include <stdbool.h>
#include "opic/common/op_macros.h"
#include "opic/hash/op_hash.h"
#include "opic/op_malloc.h"

OP_BEGIN_DECLS

typedef struct RHH_bkv_v4qu RHH_bkv_v4qu;

bool
RHH_bkv_v4qu_New(OPHeap* heap, RHH_bkv_v4qu ** rhh,
              uint64_t num_objects, double load,
              size_t keysize, size_t valsize);

void
RHH_bkv_v4qu_Destroy(RHH_bkv_v4qu* rhh);

bool RHH_bkv_v4qu_PutCustom(RHH_bkv_v4qu* rhh,
                        OPHash hasher, void* key, void* val);

void* RHH_bkv_v4qu_GetCustom(RHH_bkv_v4qu* rhh, OPHash hasher, void* key);

static inline bool
RHH_bkv_v4qu_Put(RHH_bkv_v4qu* rhh, void* key, void* val)
{
  return RHH_bkv_v4qu_PutCustom(rhh, OPDefaultHash, key, val);
}

static inline uint64_t
RHH_bkv_v4qu_PutWrap(void* key, void* context)
{
  uint64_t val = 0;
  RHH_bkv_v4qu_Put(context, key, &val);
  return 0;
}

static inline void*
RHH_bkv_v4qu_Get(RHH_bkv_v4qu* rhh, void* key)
{
  return RHH_bkv_v4qu_GetCustom(rhh, OPDefaultHash, key);
}

static inline uint64_t
RHH_bkv_v4qu_GetWrap(void* key, void* context)
{
  return *(uint64_t*)RHH_bkv_v4qu_Get(context, key);
}

void RHH_bkv_v4qu_PrintStat(RHH_bkv_v4qu* rhh);

OP_END_DECLS

#endif

/* rhh_bkv_v4qu.h ends here */
