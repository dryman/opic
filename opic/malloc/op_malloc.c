/* op_malloc.c ---
 *
 * Filename: op_malloc.c
 * Description:
 * Author: Felix Chern
 * Maintainer: Felix Chern
 * Created: Sat Oct  1 16:25:47 2016
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
 * it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include "opic/op_malloc.h"
#include "opic/malloc/objdef.h"

bool
OPHeapNew(OPHeap** heap_ref)
{
  void *addr, *map_addr;
  addr = NULL + OPHEAP_SIZE;
  map_addr = MAP_FAILED;
  for (int i = 0; i < (1<<15); i++)
    {
      map_addr = mmap(addr, OPHEAP_SIZE,
                      PROT_READ | PROT_WRITE,
                      MAP_ANON | MAP_PRIVATE | MAP_FIXED,
                      -1, 0);
      if (map_addr != MAP_FAILED)
        {
          *heap_ref = map_addr;
          memset(*heap_ref, 0, sizeof(OPHeap));
          (*heap_ref)->version = OPHEAP_VERSION;
          (*heap_ref)->hpage_num = HPAGE_BMAP_NUM * 64;
          return true;
        }
      else
        addr += OPHEAP_SIZE;
    }
  return false;
}

bool
OPHeapNewFromFile(OPHeap** heap_ref, FILE fd)
{
  return false;
}

void
OPHeapDestroy(OPHeap* heap)
{
  munmap(heap, heap->hpage_num * HPAGE_SIZE);
}

/* op_malloc.c ends here */
