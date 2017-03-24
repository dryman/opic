/* op_malloc.h ---
 *
 * Filename: op_malloc.h
 * Description:
 * Author: Felix Chern
 * Maintainer:
 * Created: Sat Oct  1 20:12:46 2016 (-0700)
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

/* This program is free software: you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation, either version 3 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this program.  If not, see
 * <http://www.gnu.org/licenses/>.
 */

/* Code: */


#ifndef OP_MALLOC_H
#define OP_MALLOC_H 1

typedef struct OPHeap OPHeap;

void*
OPMallocRaw(OPHeap* heap, size_t size)
  __attribute__ ((malloc));

void*
OPMallocRawAdviced(OPHeap* heap, size_t size, int hint)
  __attribute__ ((malloc));

void
OPDealloc(void* addr);

#endif /* OP_MALLOC_H */

/* op_malloc.h ends here */
