/* objdef.h ---
 *
 * Filename: objdef.h
 * Description:
 * Author: Felix Chern
 * Maintainer:
 * Copyright: (c) 2016 Felix Chern
 * Created: Fri Nov 11 2016
 * Version:
 * Package-Requires: ()
 * Last-Updated: 03/03/2017
 *           By: Felix Chern
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
 * Rename from malloc_internal.h to objdef.h
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


#ifndef OPIC_MALLOC_OBJDEF_H
#define OPIC_MALLOC_OBJDEF_H 1

#include <stdint.h>
#include <stdbool.h>
#include "opic/common/op_atomic.h"
#include "opic/common/op_macros.h"
#include "magic.h"
#include "opic/op_malloc.h"

OP_BEGIN_DECLS

typedef enum SpanState SpanState;
typedef enum QueueOperation QueueOperation;
typedef struct UnarySpan UnarySpan;
typedef struct HugePage HugePage;
typedef struct UnarySpanQueue UnarySpanQueue;
typedef struct HugePageQueue HugePageQueue;
typedef struct GenericContainer GenericContainer;
typedef struct SmallBlob SmallBlob;
typedef struct HugeBlob HugeBlob;
typedef union SmallSpanPtr SmallSpanPtr;
typedef union HugeSpanPtr HugeSpanPtr;
typedef struct RawType RawType;
typedef struct OPHeapCtx OPHeapCtx;

// TODO: change to enqueued/dequeued
// TODO: Rename to something more meaningful
// ENQUEUED, DEQUEUED, TOMBSTONE, NEW
enum SpanState
  {
    SPAN_ENQUEUED = 0,
    SPAN_DEQUEUED = 1,
  } __attribute__((packed));

// static_assert(sizeof(SpanState) == 1, "sizeof(SpanState)");

enum QueueOperation
  {
    QOP_SUCCESS = 0,
    QOP_CONTINUE = 1,
    QOP_RESTART = 2,
  };

struct UnarySpan
{
  Magic magic;
  uint8_t bitmap_cnt;
  uint8_t bitmap_headroom;
  uint8_t bitmap_padding;
  uint8_t bitmap_hint;  // TODO: Document how this hints to search avail space.
  a_int16_t pcard;
  a_uint16_t obj_cnt;
  _Atomic SpanState state;
  const uint32_t struct_padding: 24;
  UnarySpan* next;
  // TODO: Document how bitmap is stored after this header
};

// static_assert(sizeof(UnarySpan) == 24, "sizeof(UnarySpan)");


struct HugePage
{
  Magic magic;
  a_int16_t pcard;
  _Atomic SpanState state;
  const int8_t struct_padding;
  HugePage* next;
  a_uint64_t occupy_bmap[8];
  a_uint64_t header_bmap[8];
};

// static_assert(sizeof(HugePage) == 144, "sizeof(HugePage)");

struct UnarySpanQueue
{
  UnarySpan* uspan;
  a_int16_t pcard;
} __attribute__((packed));

// static_assert(sizeof(UnarySpanQueue) == 10, "sizeof(UnarySpanQueue)");

struct HugePageQueue
{
  HugePage* hpage;
  a_int16_t pcard;
} __attribute__((packed));

// static_assert(sizeof(HugePageQueue) == 10, "sizeof(HugePageQueue)");

// Blob contained by HPage
struct SmallBlob
{
  const Magic magic;
  // May have more info like size and offset.
};

// Blob contained by OPHeap
struct HugeBlob
{
  const Magic magic;
  // May have more info like size and offset.
};

union SmallSpanPtr
{
  uintptr_t uintptr;
  Magic* magic;
  UnarySpan* uspan;
  SmallBlob* sblob;
} __attribute__((__transparent_union__));

union HugeSpanPtr
{
  uintptr_t uintptr;
  Magic* magic;
  HugePage* hpage;
  HugeBlob* hblob;
} __attribute__((__transparent_union__));

/************** OPHeap Layout ******************/

// NOTE: bookmark may be a better name for XXQueue
struct RawType
{
  // Thread local physical spans. In total of 16 size classes to serve
  // objects of size from 16 bytes to 256 bytes. Each size class has
  // 16 thread local UnarySpanQueue
  UnarySpanQueue uspan_queue[16][16];
  // size class 512, 1024, 2048
  UnarySpanQueue large_uspan_queue[3];
  HugePageQueue hpage_queue;
} __attribute__((packed));

// static_assert(sizeof(RawType) == 2600, "sizeof(RawType)");

struct OPHeap
{
  uint32_t version;
  a_int16_t pcard;
  uint16_t hpage_num;
  opref_t root_ptrs[8];
  a_uint64_t occupy_bmap[HPAGE_BMAP_NUM];
  a_uint64_t header_bmap[HPAGE_BMAP_NUM];
  RawType raw_type;
  HugePage hpage;
} __attribute__((packed));

// static_assert(sizeof(OPHeap) == 11008, "sizeof(OPHeap)");

struct OPHeapCtx
{
  SmallSpanPtr sspan;
  HugeSpanPtr hspan;
  UnarySpanQueue* uqueue;
  HugePageQueue* hqueue;
};

OP_END_DECLS

#endif

/* objdef.h ends here */
