/* rhh_bkv.h ---
 *
 * Filename: rhh_bkv.h
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


#ifndef BENCHMARK_ROBIN_HOOD_RHH_BKV_H
#define BENCHMARK_ROBIN_HOOD_RHH_BKV_H 1

#include <stdbool.h>
#include "opic/common/op_macros.h"
#include "opic/hash/op_hash.h"
#include "opic/op_malloc.h"

OP_BEGIN_DECLS

typedef struct RHH_bkv RHH_bkv;

uint64_t CCityHash64(const char *buf, size_t len);

bool
RHH_bkv_New(OPHeap* heap, RHH_bkv ** rhh,
              uint64_t num_objects, double load,
              size_t keysize, size_t valsize);

void
RHH_bkv_Destroy(RHH_bkv* rhh);

bool RHH_bkv_PutCustom(RHH_bkv* rhh,
                        OPHash hasher, void* key, void* val);

void* RHH_bkv_GetCustom(RHH_bkv* rhh, OPHash hasher, void* key);

static inline uint64_t
OPCityHash(void* key, size_t size)
{
  return CCityHash64(key, size);
}

static inline bool
RHH_bkv_Put(RHH_bkv* rhh, void* key, void* val)
{
  return RHH_bkv_PutCustom(rhh, OPCityHash, key, val);
}

static inline uint64_t
RHH_bkv_PutWrap(void* key, void* context)
{
  uint64_t val = 0;
  RHH_bkv_Put(context, key, &val);
  return 0;
}

static inline void*
RHH_bkv_Get(RHH_bkv* rhh, void* key)
{
  return RHH_bkv_GetCustom(rhh, OPCityHash, key);
}

static inline uint64_t
RHH_bkv_GetWrap(void* key, void* context)
{
  return *(uint64_t*)RHH_bkv_Get(context, key);
}

void RHH_bkv_PrintStat(RHH_bkv* rhh);

OP_END_DECLS

#endif

/* rhh_bkv.h ends here */
