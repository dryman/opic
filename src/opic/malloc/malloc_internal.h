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
#include <stdatomic.h>
#include "magic.h"
#include "opic/common/op_macros.h"

OP_BEGIN_DECLS

typedef struct UnarySpan UnarySpan;
typedef struct BolbSpan BlobSpan;
typedef struct HugePage HugePage;
typedef enum FreeStatus FreeStatus;

struct UnarySpan
{
  const Magic magic;
  const uint8_t bitmap_cnt;
  const uint8_t bitmap_headroom;
  const uint8_t bitmap_padding;
  uint8_t bitmap_hint;
  UnarySpan* prev;
  UnarySpan* next;
};

static_assert(sizeof(UnarySpan) == 24, "UnaryPSpan size should be 24\n");

struct BlobSpan
{
  const Magic magic;
};

struct HugePage 
{
  const Magic magic;
  int32_t padding;
  HugePage* next;
  atomic_uint_fast64_t occupy_bmap[8];
  atomic_uint_fast64_t header_bmap[8];
};

static_assert(sizeof(HugePage) == 144, "HugePage size should be 144\n");

enum FreeStatus
  {
    FREE_NORMAL,
    FREE_FROM_FULL,
    FREE_REACHED_EMPTY
  };

OP_END_DECLS

#endif

/* malloc_internal.h ends here */
