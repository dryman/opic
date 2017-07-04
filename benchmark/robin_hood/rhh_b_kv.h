/* rhh_b_kv.h ---
 *
 * Filename: rhh_b_kv.h
 * Description:
 * Author: Felix Chern
 * Maintainer:
 * Copyright: (c) 2017 Felix Chern
 * Created: Sun Apr 30 15:35:42 2017 (-0700)
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

#ifndef BENCHMARK_ROBIN_HOOD_RHH_B_KV_H
#define BENCHMARK_ROBIN_HOOD_RHH_B_KV_H 1

#include <stdbool.h>
#include "opic/common/op_macros.h"
#include "opic/hash/op_hash.h"
#include "opic/op_malloc.h"

OP_BEGIN_DECLS

typedef struct RHH_b_kv RHH_b_kv;

bool
RHH_b_kv_New(OPHeap* heap, RHH_b_kv ** rhh,
              uint64_t num_objects, double load,
              size_t keysize, size_t valsize);

void
RHH_b_kv_Destroy(RHH_b_kv* rhh);

bool RHH_b_kv_PutCustom(RHH_b_kv* rhh,
                        OPHash hasher, void* key, void* val);

void* RHH_b_kv_GetCustom(RHH_b_kv* rhh, OPHash hasher, void* key);

static inline bool
RHH_b_kv_Put(RHH_b_kv* rhh, void* key, void* val)
{
  return RHH_b_kv_PutCustom(rhh, OPDefaultHash, key, val);
}

static inline uint64_t
RHH_b_kv_PutWrap(void* key, void* context, OPHash hash_impl)
{
  uint64_t val = 0;
  RHH_b_kv_PutCustom(context, hash_impl, key, &val);
  return 0;
}

static inline void*
RHH_b_kv_Get(RHH_b_kv* rhh, void* key)
{
  return RHH_b_kv_GetCustom(rhh, OPDefaultHash, key);
}

static inline uint64_t
RHH_b_kv_GetWrap(void* key, void* context, OPHash hash_impl)
{
  return *(uint64_t*)RHH_b_kv_GetCustom(context, hash_impl, key);
}

void RHH_b_kv_PrintStat(RHH_b_kv* rhh);

uint32_t RHH_b_kv_MaxProbe(RHH_b_kv* rhh);

uint32_t RHH_b_kv_ProbeStat(RHH_b_kv* rhh, uint32_t idx);

OP_END_DECLS

#endif

/* rhh_b_kv.h ends here */
