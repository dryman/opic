/* op_heap.c --- 
 * 
 * Filename: op_heap.c
 * Description: 
 * Author: Felix Chern
 * Maintainer: 
 * Copyright: (c) 2016 Felix Chern
 * Created: Sat Oct 22, 2016
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


#include "op_heap.h"
#include "op_pspan.h"
#include "op_vpage.h"

#define VSPAN_NUM (1 << 15)
#define VSPAN_BMAP_NUM (1 << 9)

typedef struct RawType RawType;
typedef struct TypeAlias TypeAlias;
typedef struct UnarySizeClass UnarySizeClass;
typedef struct PolyadicSizeClass PolyadicSizeClass;

static __thread int tid = -1;
static atomic_uint round_robin = 0;

struct UnarySizeClass
{
  UnaryPSpan* _Atomic uspan[16];
  UnaryPSpan* candidate;
  atomic_uint_fast16_t uspan_bmap;
  atomic_bool candidate_lock;
};

struct PolyadicSizeClass
{
  PolyadicPSpan* _Atomic plspan;
  PolyadicPSpan* candidate;
  atomic_bool plspan_lock;
  atomic_bool candidate_lock;
};

struct RawType
{
  struct UnarySizeClass size_class_8;
  struct UnarySizeClass size_class_16_256[16];
  struct PolyadicSizeClass size_class_256_2048[4];
};

struct TypeAlias
{
  // TODO: change to Class* when we merge with object
  void *klass;
  char *type_name;
  struct UnarySizeClass size_class_1;
  struct PolyadicSizeClass size_class_2_16;
  struct PolyadicSizeClass size_class_16_128;
};

struct OPHeap
{
  atomic_uint_fast64_t occupy_bmap[VSPAN_BMAP_NUM];
  atomic_uint_fast64_t header_bmap[VSPAN_BMAP_NUM];
  atomic_int_fast16_t refcnt[VSPAN_NUM];
  struct RawType raw_type;
  struct TypeAlias type_alias[2048];
};

/* op_heap.c ends here */
