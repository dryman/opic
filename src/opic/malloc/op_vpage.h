/* op_vpage.h --- 
 * 
 * Filename: op_vpage.h
 * Description: 
 * Author: Felix Chern
 * Maintainer: 
 * Copyright: (c) 2016 Felix Chern
 * Created: Tue Oct 11 2016
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

#ifndef OP_VPAGE_H
#define OP_VPAGE_H 1

#include <stdint.h>
#include <stdbool.h>
#include <stdatomic.h>
#include "opic/common/op_macros.h"
#include "opic/common/op_assert.h"
#include "opic/common/op_log.h"
#include "opic/malloc/op_pspan.h"

OP_BEGIN_DECLS

typedef struct OPVPage OPVPage;

struct OPVPage 
{
  _Atomic uint64_t occupy_bmap[512];
  _Atomic uint64_t header_bmap[512];
};

OPVPage* OPVPageInit(void* addr);

OPSingularPSpan* OPVPageAllocPSpan(OPVPage* restrict self,
                                   uint16_t ta_idx,
                                   uint16_t obj_size,
                                   unsigned int span_cnt);

bool OPVPageFree(OPVPage* restrict self, void* addr);



OP_END_DECLS

#endif
/* op_vpage.h ends here */
