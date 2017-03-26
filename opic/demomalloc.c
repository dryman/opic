/* demomalloc.c ---
 *
 * Filename: demomalloc.c
 * Description:
 * Author: Felix Chern
 * Maintainer:
 * Copyright: (c) 2017 Felix Chern
 * Created: Sun Mar 26 11:43:56 2017 (-0700)
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

#include <stdatomic.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include "opic/op_malloc.h"
#include "opic/demomalloc.h"

static atomic_flag lock = ATOMIC_FLAG_INIT;
static OPHeap* heap;

static
OPHeap* GetOPHeap()
{
  while (true)
    {
      if (heap)
        return heap;
      if (atomic_flag_test_and_set_explicit(&lock, memory_order_acquire))
        continue;
      OPHeapNew(&heap);
      atomic_flag_clear_explicit(&lock, memory_order_release);
    }
}

void*
OPDemoMalloc(size_t size)
{
  OPHeap* heap = GetOPHeap();
  return OPMallocRaw(heap, size);
}

void*
OPDemoCalloc(size_t num, size_t size)
{
  OPHeap* heap = GetOPHeap();
  return OPCallocRaw(heap, num, size);
}

void*
OPDemoRealloc(void* addr, size_t size)
{
  OPHeap* heap;
  void* new_addr;
  heap = ObtainOPHeap(addr);
  // NOTE: for sblob/hblob we might find the new size still fits in the blob.
  // We can do this optimization later.
  new_addr = OPMallocRaw(heap, size);
  if (new_addr)
    {
      memcpy(new_addr, addr, size);
      OPDealloc(addr);
    }
  return new_addr;
}

void
OPDemoFree(void* addr)
{
  OPDealloc(addr);
}

/* demomalloc.c ends here */
