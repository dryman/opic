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
#include "opic/common/op_macros.h"
#include "opic/common/op_assert.h"
#include "opic/common/op_log.h"
#include "magic.h"

OP_BEGIN_DECLS

typedef struct UnarySpan UnarySpan;
typedef struct PolyadicSpan PolyadicSpan;

// we probably need to define a magic header

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

struct PolyadicSpan
{
  const Magic magic;
  const uint8_t bitmap_cnt;
  const uint8_t bitmap_headroom;
  const uint8_t bitmap_padding;
  uint8_t bitmap_hint;
  PolyadicSpan* prev;
  PolyadicSpan* next;
};

static_assert(sizeof(UnarySpan) == 24, "UnaryPSpan size should be 24\n");
static_assert(sizeof(PolyadicSpan) == 24,
              "PolyadicPSpan size should be 24\n");

UnarySpan* USpanInit(void* addr, Magic magic, size_t span_size);

void* USpanMalloc(UnarySpan* self);

bool USpanFree(UnarySpan* self, void* addr);

OP_END_DECLS

#endif
/* op_pspan.h ends here */
