/* op_pspan.h --- 
 * 
 * Filename: op_pspan.h
 * Description: 
 * Author: Felix Chern
 * Maintainer: 
 * Copyright: (c) 2016 Felix Chern
 * Created: Sat Oct 8, 2016
 * Version: 0.3.0
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

#ifndef OP_PSPAN_H
#define OP_PSPAN_H 1

#include <stdint.h>
#include <stdbool.h>
#include "../common/op_macros.h"
#include "../common/op_assert.h"
#include "../common/op_log.h"

OP_BEGIN_DECLS

typedef struct OPSingularPSpan OPSingularPSpan;

struct OPSingularPSpan
{
  const uint16_t ta_idx;
  const uint16_t obj_size;
  const uint8_t bitmap_cnt;
  const uint8_t bitmap_headroom;
  const uint8_t bitmap_padding;
  uint8_t bitmap_hint;
  // TODO: squeeze some bits for varying pspan
  OPSingularPSpan* prev;
  OPSingularPSpan* next;
};

OPSingularPSpan* OPSingularPSpanInit(void* restrict addr, uint16_t ta_idx,
                                     uint16_t obj_size, size_t span_size);

void* OPSingularPSpanMalloc(OPSingularPSpan* self);

bool OPSingularPSpanFree(OPSingularPSpan* self, void* addr);

OP_END_DECLS

#endif
/* op_pspan.h ends here */
