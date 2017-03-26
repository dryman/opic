/* init_helper.h ---
 *
 * Filename: init_helper.h
 * Description:
 * Author: Felix Chern
 * Maintainer:
 * Copyright: (c) 2016 Felix Chern
 * Created: Sun Mar  5 16:41:20 2017 (-0800)
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

#ifndef OPIC_MALLOC_INIT_HELPER_H
#define OPIC_MALLOC_INIT_HELPER_H 1

#include "objdef.h"
#include "inline_aux.h"

OP_BEGIN_DECLS

typedef union BmapPtr BmapPtr;

union BmapPtr
{
  uint64_t* uint64;
  a_uint64_t* a_uint64;
} __attribute__ ((__transparent_union__));

void HPageInit(HugePage* hpage, Magic magic)
  __attribute__ ((visibility ("internal")));

void USpanInit(UnarySpan* uspan, Magic magic, unsigned int spage_cnt)
  __attribute__ ((visibility ("internal")));

void OPHeapEmptiedBMaps(OPHeap* heap, BmapPtr occupy_bmap, BmapPtr header_bmap)
  __attribute__ ((visibility ("internal")));

void HPageEmptiedBMaps(HugePage* hpage, BmapPtr occupy_bmap,
                       BmapPtr header_bmap)
  __attribute__ ((visibility ("internal")));

void USpanEmptiedBMap(UnarySpan* uspan, BmapPtr bmap)
  __attribute__ ((visibility ("internal")));

OP_END_DECLS

#endif

/* init_helper.h ends here */
