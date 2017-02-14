/* malloc_internal.h ---
 *
 * Filename: malloc_internal.h
 * Description:
 * Author: Felix Chern
 * Maintainer:
 * Copyright: (c) 2016 Felix Chern
 * Created: Fri Nov 11 2016
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


#ifndef MALLOC_INTERNAL_H
#define MALLOC_INTERNAL_H

#include <stdint.h>
#include <stdbool.h>
#include "magic.h"
#include "opic/common/op_atomic.h"
#include "opic/common/op_macros.h"

OP_BEGIN_DECLS

#define round_up_div(X, Y) ((X) + (Y) - 1)/(Y)

typedef struct UnarySpan UnarySpan;
typedef struct BolbSpan BlobSpan;
typedef struct HugePage HugePage;

typedef enum __attribute__((packed)) BitMapState
  {
    BM_NORMAL = 0,
    BM_NEW = 1,
    BM_FULL = 2,
    BM_TOMBSTONE = 3,
  }
BitMapState;

static_assert(sizeof(BitMapState) == 1, "BitMapState should be 1 byte\n");

struct UnarySpan
{
  const Magic magic;             // 32 bits
  const uint8_t bitmap_cnt;
  const uint8_t bitmap_headroom;
  const uint8_t bitmap_padding;
  uint8_t bitmap_hint;
  a_in16_t pcard;
  a_uint16_t obj_cnt;
  _Atomic BitMapState state;
  const uint32_t struct_padding: 24;
  UnarySpan* next;
};

static_assert(sizeof(UnarySpan) == 24, "UnaryPSpan size should be 24 bytes\n");

struct BlobSpan
{
  const Magic magic;
};

struct HugePage
{
  const Magic magic;
  a_int16_t pcard;
  _Atomic BitMapState state;
  //const uint64_t padding : 48;
  HugePage* next;
  a_uint64_t occupy_bmap[8];
  a_uint64_t header_bmap[8];
};

static_assert(sizeof(HugePage) == 144, "HugePage size should be 144\n");


OP_END_DECLS

#endif

/* malloc_internal.h ends here */
