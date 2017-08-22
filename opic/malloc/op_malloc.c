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

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <errno.h>
#include "opic/op_malloc.h"
#include "opic/common/op_assert.h"
#include "opic/common/op_log.h"
#include "opic/common/op_utils.h"
#include "opic/malloc/objdef.h"

#ifdef __linux__
#define MINCORE_VEC unsigned char
#elif __APPLE__
#define MINCORE_VEC char
#else
#error "unknown platform for mincore"
#endif

OP_LOGGER_FACTORY(logger, "opic.malloc.op_malloc");

struct HeapFdEntry
{
  uintptr_t heap;
  int fd;
};

#define FDMAP_SIZE (1ULL<<12)
static struct HeapFdEntry heap_fd_map[FDMAP_SIZE];

int OPHeapGetFD(OPHeap* heap)
{
  uintptr_t uint_heap, idx_iter, idx, mask;
  uint_heap = (uintptr_t)heap;
  idx_iter = uint_heap >> HPAGE_BITS;
  mask = FDMAP_SIZE - 1;

  for (int i = 0; i < 2048; i++)
    {
      idx_iter++;
      idx = idx_iter & mask;
      if (heap_fd_map[idx].heap == 0)
        return -1;
      if (heap_fd_map[idx].heap == ~0ULL)
        continue;
      if (heap_fd_map[idx].heap == uint_heap)
        return heap_fd_map[idx].fd;
    }
  return -1;
}

void OPHeapPutFD(OPHeap* heap, int fd)
{
  uintptr_t uint_heap, idx_iter, idx, mask;
  uint_heap = (uintptr_t)heap;
  idx_iter = uint_heap >> HPAGE_BITS;
  mask = FDMAP_SIZE - 1;
  for (int i = 0; i < 2048; i++)
    {
      idx_iter++;
      idx = idx_iter & mask;
      if (heap_fd_map[idx].heap == 0 ||
          heap_fd_map[idx].heap == ~0ULL ||
          heap_fd_map[idx].heap == uint_heap)
        {
          OP_LOG_DEBUG(logger, "Storing heap to fd map: %p -> fd %d",
                       heap, fd);
          heap_fd_map[idx].heap = uint_heap;
          heap_fd_map[idx].fd = fd;
          return;
        }
    }
}

void OPHeapDelFD(OPHeap* heap)
{
  uintptr_t uint_heap, idx_iter, idx, mask;
  uint_heap = (uintptr_t)heap;
  idx_iter = uint_heap >> HPAGE_BITS;
  mask = FDMAP_SIZE - 1;

  for (int i = 0; i <= 2048; i++)
    {
      idx_iter++;
      idx = idx_iter & mask;
      if (heap_fd_map[idx].heap == 0 ||
          heap_fd_map[idx].heap == ~0ULL)
        return;
      if (heap_fd_map[idx].heap == uint_heap)
        {
          OP_LOG_DEBUG(logger, "Deleting heap to fd map: %p -> fd %d",
                       heap, fd);
          heap_fd_map[idx].heap = ~0ULL;
          close(heap_fd_map[idx].fd);
          return;
        }
    }
  return;
}

void OPHeapFSync(OPHeap* heap)
{
  int fd;
  fd = OPHeapGetFD(heap);
  op_assert(fd != -1,
            "All OPHeap should have a matching fd. (fd=0 means on swap)\n");
  if (fd)
    fsync(fd);
}

static off_t GetFDSize(int fd)
{
  struct stat heap_stat;
  int stat_ret;
  if (fstat(fd, &heap_stat) == -1)
    {
      OP_LOG_ERROR(logger, "Error on fstat: %s",
                   strerror(errno));
      return ~0ULL;
    }
  return heap_stat.st_size;
}

static inline
OPHeap* OPHeapOpenInternal(int fd)
{
  OPHeap* heap;
  void *addr, *map_addr;
  MINCORE_VEC page_check[1] = {0};
  int mincore_status;
  off_t heap_size;
  addr = NULL + OPHEAP_SIZE;
  map_addr = MAP_FAILED;

  heap_size = GetFDSize(fd);

  for (int i = 0; i < (1<<15); i++)
    {
      errno = 0;
      page_check[0] = 0;
      mincore_status = mincore(addr, SPAGE_SIZE, page_check);
      if (page_check[0] ||
          (mincore_status == -1 && errno != ENOMEM))
        {
          OP_LOG_DEBUG(logger,
                       "Addr %p not available for OPHeap: "
                       "mincore check %d, error %s",
                       addr, page_check[0], strerror(errno));
          goto next_heap;
        }

      map_addr = mmap(addr, OPHEAP_SIZE, PROT_NONE,
                      MAP_ANON | MAP_PRIVATE | MAP_FIXED,
                      -1, 0);
      if (map_addr == MAP_FAILED)
        {
          OP_LOG_WARN(logger,
                      "Addr %p failed to reserve 64GB for OPHeap, "
                      "trying next available addresses.",
                      addr);
        next_heap:
          addr += OPHEAP_SIZE;
          continue;
        }
      OP_LOG_DEBUG(logger, "Reserved heap space at %p", addr);

      if (heap_size == 0)  // Create file case
        {
          ftruncate(fd, HPAGE_SIZE);
          map_addr = mmap(addr, HPAGE_SIZE, PROT_READ | PROT_WRITE,
                          MAP_FILE | MAP_SHARED | MAP_FIXED,
                          fd, 0);
          if (map_addr == MAP_FAILED)
            {
              OP_LOG_DEBUG(logger, "Failed to mmap heap at %p",
                           addr);
              munmap(addr, OPHEAP_SIZE);
              return NULL;
            }
          heap = map_addr;
          heap->version = OPHEAP_VERSION;
        }
      else  // open existing file case
        {
          map_addr = mmap(addr, heap_size, PROT_READ | PROT_WRITE,
                          MAP_FILE | MAP_SHARED | MAP_FIXED,
                          fd, 0);
          if (map_addr == MAP_FAILED)
            {
              OP_LOG_DEBUG(logger, "Failed to mmap heap at %p, %s",
                           addr, strerror(errno));
              munmap(addr, OPHEAP_SIZE);
              return NULL;
            }
          heap = map_addr;
        }
      return heap;
    }
  return NULL;
}

OPHeap* OPHeapOpen(const char *path, int flags)
{
  OPHeap* heap;
  int fd;
  fd = open(path, flags);
  if (fd == -1)
    {
      OP_LOG_ERROR(logger, "Failed to open %s. %s",
                   path, strerror(errno));
      return NULL;
    }
  heap = OPHeapOpenInternal(fd);
  if (heap)
    OPHeapPutFD(heap, fd);
  return heap;
}

OPHeap* OPHeapOpenTmp()
{
  OPHeap* heap;
  int fd;
  FILE* pfile = tmpfile();
  if (pfile == NULL)
    {
      OP_LOG_ERROR(logger, "Failed to create tmp file: %s",
                   strerror(errno));
      return NULL;
    }
  fd = fileno(pfile);
  heap = OPHeapOpenInternal(fd);
  if (heap)
    OPHeapPutFD(heap, fd);
  return heap;
}

void OPHeapClose(OPHeap* heap)
{
  OPHeapFSync(heap);
  OPHeapDelFD(heap);
  munmap(heap, OPHEAP_SIZE);
}


void OPHeapStorePtr(OPHeap* heap, void* ptr, int pos)
{
  op_assert(heap == ObtainOPHeap(ptr), "Attempt to store ptr %p in OPHeap %p\n",
            ptr, heap);
  op_assert(pos < 8, "Can only store 8 root ptrs, but got pos = %d\n", pos);
  opref_t ptr_base;
  ptr_base = OPPtr2Ref(ptr);
  heap->root_ptrs[pos] = ptr_base;
}

void* OPHeapRestorePtr(OPHeap* heap, int pos)
{
  op_assert(pos < 8, "Can only store 8 root ptrs, but got pos = %d\n", pos);
  return OPRef2Ptr(heap, heap->root_ptrs[pos]);
}

/* op_malloc.c ends here */
