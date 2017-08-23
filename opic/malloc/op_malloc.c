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
#include <pthread.h>
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

static pthread_mutex_t op_mutex = PTHREAD_MUTEX_INITIALIZER;

struct HeapFdEntry
{
  uintptr_t heap;
  int fd;
};

#define FDMAP_SIZE (1ULL<<12)
static struct HeapFdEntry heap_fd_map[FDMAP_SIZE];

static int OPHeapGetFD(OPHeap* heap)
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

static void OPHeapPutFD(OPHeap* heap, int fd)
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

static void OPHeapDelFD(OPHeap* heap)
{
  uintptr_t uint_heap, idx_iter, idx, mask;
  int fd;
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
          fd = heap_fd_map[idx].fd;
          OP_LOG_DEBUG(logger, "Deleting heap to fd map: %p -> fd %d",
                       heap, fd);
          heap_fd_map[idx].heap = ~0ULL;
          close(heap_fd_map[idx].fd);
          return;
        }
    }
  return;
}

static off_t GetFDSize(int fd)
{
  struct stat heap_stat;
  if (fstat(fd, &heap_stat) == -1)
    {
      OP_LOG_ERROR(logger, "Error on fstat: %s",
                   strerror(errno));
      return ~0ULL;
    }
  return heap_stat.st_size;
}

void OPHeapMSync(OPHeap* heap)
{
  int fd;
  off_t heap_size;
  pthread_mutex_lock(&op_mutex);

  fd = OPHeapGetFD(heap);
  op_assert(fd != -1,
            "All OPHeap should have a matching fd.\n");
  heap_size = GetFDSize(fd);
  if (!msync(heap, (size_t)heap_size, MS_SYNC))
    {
      OP_LOG_ERROR(logger, "msync on %p failed: %s",
                   heap, strerror(errno));
    }

  pthread_mutex_unlock(&op_mutex);
}


void OPHeapCheckExpandSize(OPHeap* heap, size_t size)
{
  int heap_fd;
  off_t heap_size, expand_boundary;
  uintptr_t heap_base;

  pthread_mutex_lock(&op_mutex);

  heap_fd = OPHeapGetFD(heap);
  heap_size = GetFDSize(heap_fd);
  expand_boundary = (off_t)size;
  heap_base = (uintptr_t)heap;

  if (heap_size < expand_boundary)
    {
      OP_LOG_DEBUG(logger,
                   "Expanding OPHeap %p size to %" PRIx64,
                   heap, (uint64_t)expand_boundary);
      if (ftruncate(heap_fd, expand_boundary) == -1)
        {
          OP_LOG_FATAL(logger, "Expanding fd %d failed. %s",
                       heap_fd, strerror(errno));
          op_assert(0, "Fatal error");
        }
      if (mmap((void*)(heap_base + heap_size),
               expand_boundary - heap_size,
               PROT_READ | PROT_WRITE,
               MAP_FILE | MAP_SHARED | MAP_FIXED,
               heap_fd, heap_size) == MAP_FAILED)
        {
          OP_LOG_FATAL(logger, "Expand OPHeap %p failed. %s",
                       heap, strerror(errno));
          op_assert(0, "Fatal error");
        }
    }
  pthread_mutex_unlock(&op_mutex);
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
  pthread_mutex_lock(&op_mutex);

  fd = open(path, flags);
  if (fd == -1)
    {
      OP_LOG_ERROR(logger, "Failed to open %s. %s",
                   path, strerror(errno));
      pthread_mutex_unlock(&op_mutex);
      return NULL;
    }
  heap = OPHeapOpenInternal(fd);
  if (heap)
    OPHeapPutFD(heap, fd);
  pthread_mutex_unlock(&op_mutex);
  return heap;
}

OPHeap* OPHeapOpenTmp()
{
  OPHeap* heap;
  int fd;
  FILE* pfile;
  pthread_mutex_lock(&op_mutex);

  pfile = tmpfile();
  if (pfile == NULL)
    {
      OP_LOG_ERROR(logger, "Failed to create tmp file: %s",
                   strerror(errno));
      pthread_mutex_unlock(&op_mutex);
      return NULL;
    }
  fd = fileno(pfile);
  heap = OPHeapOpenInternal(fd);
  if (heap)
    OPHeapPutFD(heap, fd);
  pthread_mutex_unlock(&op_mutex);
  return heap;
}

void OPHeapClose(OPHeap* heap)
{
  OPHeapMSync(heap);

  pthread_mutex_lock(&op_mutex);
  OPHeapDelFD(heap);
  munmap(heap, OPHEAP_SIZE);
  pthread_mutex_unlock(&op_mutex);
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
