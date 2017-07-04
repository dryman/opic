/* rhh_b_k_v.h ---
 *
 * Filename: rhh_b_k_v.h
 * Description:
 * Author: Felix Chern
 * Maintainer:
 * Copyright: (c) 2017 Felix Chern
 * Created: Sun Apr 30 14:35:19 2017 (-0700)
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

#ifndef BENCHMARK_ROBIN_HOOD_RHH_B_K_V_H
#define BENCHMARK_ROBIN_HOOD_RHH_B_K_V_H 1

#include <stdbool.h>
#include "opic/common/op_macros.h"
#include "opic/hash/op_hash.h"
#include "opic/op_malloc.h"

OP_BEGIN_DECLS

typedef struct RHH_b_k_v RHH_b_k_v;

bool
RHH_b_k_v_New(OPHeap* heap, RHH_b_k_v ** rhh,
              uint64_t num_objects, double load,
              size_t keysize, size_t valsize);

void
RHH_b_k_v_Destroy(RHH_b_k_v* rhh);

bool RHH_b_k_v_PutCustom(RHH_b_k_v* rhh,
                         OPHash hasher, void* key, void* val);

void* RHH_b_k_v_GetCustom(RHH_b_k_v* rhh, OPHash hasher, void* key);

static inline bool
RHH_b_k_v_Put(RHH_b_k_v* rhh, void* key, void* val)
{
  return RHH_b_k_v_PutCustom(rhh, OPDefaultHash, key, val);
}

static inline uint64_t
RHH_b_k_v_PutWrap(void* key, void* context, OPHash hash_impl)
{
  uint64_t val = 0;
  RHH_b_k_v_PutCustom(context, hash_impl, key, &val);
  return 0;
}

static inline void*
RHH_b_k_v_Get(RHH_b_k_v* rhh, void* key)
{
  return RHH_b_k_v_GetCustom(rhh, OPDefaultHash, key);
}

static inline uint64_t
RHH_b_k_v_GetWrap(void* key, void* context, OPHash hash_impl)
{
  return *(uint64_t*)RHH_b_k_v_GetCustom(context, hash_impl, key);
}

void RHH_b_k_v_PrintStat(RHH_b_k_v* rhh);

uint32_t RHH_b_k_v_MaxProbe(RHH_b_k_v* rhh);

uint32_t RHH_b_k_v_ProbeStat(RHH_b_k_v* rhh, uint32_t idx);

OP_END_DECLS

#endif

/* rhh_b_k_v.h ends here */
