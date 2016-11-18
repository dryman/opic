/* op_lock_utils.h --- 
 * 
 * Filename: op_lock_utils.h
 * Description: 
 * Author: Felix Chern
 * Maintainer: 
 * Copyright: (c) 2016 Felix Chern
 * Created: Thu Nov  3 2016
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

#ifndef OP_HEAP_INTERNAL_H
#define OP_HEAP_INTERNAL_H 1

#include <stdint.h>
#include <stdbool.h>
#include <stdatomic.h>
#include "opic/common/op_macros.h"
#include "opic/malloc/huge_page.h"
#include "opic/malloc/op_heap.h"

OP_BEGIN_DECLS

#define FAVOR_HPAGE 0
#define FAVOR_512 1
#define FAVOR_1024 2
#define FAVOR_2048 3

typedef struct RawType RawType;
typedef struct TypeAlias TypeAlias;

struct RawType
{
  // Thread local physical spans. In total of 16 size classes to serve
  // objects of size from 16 bytes to 256 bytes. Each size class has
  // 16 thread local UnaryPSpan pointers.
  UnarySpan* uspan[16][16];
  // Thread local read write lock
  atomic_int_fast8_t uspan_rwlock[16][16];
  // 16 favor wirte flags, each bit coresponds to a thread local lock.
  atomic_uint_fast16_t uspan_favor[16];
  // size class 512, 1024, 2048
  UnarySpan* large_uspan[3];
  atomic_int_fast16_t large_uspan_rwlock[3];
  HugePage* hpage;
  atomic_int_fast16_t hpage_rwlock;
  // favor flag for hpage, size class 512, 1024, and 2048
  atomic_uint_fast8_t remain_favor;
};

struct TypeAlias
{
  // TODO: change to Class* when we merge with object
  void *klass;
  char *type_name;
  UnarySpan* uspan[16];
  atomic_int_fast8_t uspan_rwlock[16];
  atomic_uint_fast16_t uspan_favor;
  HugePage* hpage;
  atomic_int_fast16_t hpage_rwlock;
  atomic_uint_fast8_t remain_favor;
};

HugePage* ObtainHPage(OPHeap* self, Magic magic);

#define acq_rlock(RWLOCK, FAVOR, OFFSET)           \
  _Generic((RWLOCK),                               \
           atomic_int_fast8_t*: acq_rlock_int8,    \
           atomic_int_fast16_t*: acq_rlock_int16)  \
  (RWLOCK, FAVOR, OFFSET)

#define rel_rlock(RWLOCK)                          \
  _Generic((RWLOCK),                               \
           atomic_int_fast8_t*: rel_rlock_int8,    \
           atomic_int_fast16_t*: rel_rlock_int16)  \
  (RWLOCK)

#define favor_write(FAVOR, OFFSET)                      \
  _Generic((FAVOR),                                     \
           atomic_uint_fast8_t*: favor_write_int8,      \
           atomic_uint_fast16_t*: favor_write_int16)    \
  (FAVOR, OFFSET)

#define acq_wlock(RWLOCK, FAVOR, OFFSET)           \
  _Generic((RWLOCK),                               \
           atomic_int_fast8_t*: acq_wlock_int8,    \
           atomic_int_fast16_t*: acq_wlock_int16)  \
  (RWLOCK, FAVOR, OFFSET)

#define rel_wlock(RWLOCK)                          \
  _Generic((RWLOCK),                               \
           atomic_int_fast8_t*: rel_wlock_int8,    \
           atomic_int_fast16_t*: rel_wlock_int16)  \
  (RWLOCK)


static inline bool
acq_rlock_int8(atomic_int_fast8_t* rwlock,
               atomic_uint_fast16_t* favor,
               int favor_offset)
{
  uint16_t mask = 1u << favor_offset;
  if (atomic_load_explicit(favor, memory_order_relaxed) & mask)
    return false;

  int8_t oldlock = atomic_load_explicit(rwlock, memory_order_relaxed);
  if (oldlock < 0)
    return false;

  while (!atomic_compare_exchange_weak_explicit
         (rwlock, &oldlock, oldlock + 1,
          memory_order_acquire,
          memory_order_relaxed))
    {
      if (oldlock < 0)
        return false;
      if (atomic_load_explicit(favor, memory_order_relaxed) & mask)
        return false;
    }
  return true;
}

static inline bool
acq_rlock_int16(atomic_int_fast16_t* rwlock,
                atomic_uint_fast8_t* favor,
                int favor_offset)
{
  uint8_t mask = 1u << favor_offset;
  
  if (atomic_load_explicit(favor, memory_order_relaxed) & mask)
    return false;

  int16_t oldlock = atomic_load_explicit(rwlock, memory_order_relaxed);
  if (oldlock < 0)
    return false;
  
  while (!atomic_compare_exchange_weak_explicit
         (rwlock, &oldlock, oldlock + 1,
          memory_order_acquire,
          memory_order_relaxed))
    {
      if (oldlock < 0)
        return false;
      if (atomic_load_explicit(favor, memory_order_relaxed) & mask)
        return false;
    }
  return true;
}

static inline void
rel_rlock_int8(atomic_int_fast8_t* rwlock)
{
  atomic_fetch_sub_explicit(rwlock, 1,
                            memory_order_release);
}

static inline void
rel_rlock_int16(atomic_int_fast16_t* rwlock)
{
  atomic_fetch_sub_explicit(rwlock, 1,
                            memory_order_release);
}

static inline void
favor_write_int8(atomic_uint_fast8_t* favor, int offset)
{
  atomic_fetch_or_explicit(favor, 1 << offset,
                           memory_order_relaxed);
}

static inline void
favor_write_int16(atomic_uint_fast16_t* favor, int offset)
{
  atomic_fetch_or_explicit(favor, 1 << offset,
                           memory_order_relaxed);
}

static inline bool
acq_wlock_int8(atomic_int_fast8_t* rwlock,
               atomic_uint_fast16_t* favor,
               int favor_offset)
{
  int8_t expected_lock = 0;
  while (!atomic_compare_exchange_strong_explicit
         (rwlock, &expected_lock, -1,
          memory_order_acquire,
          memory_order_relaxed))
    {
      if (expected_lock < 0)
        return false;
      else
        expected_lock = 0;
    }
  uint16_t mask = ~(1 << favor_offset);
  atomic_fetch_and_explicit(favor, mask, memory_order_relaxed);
  return true;
}

static inline bool
acq_wlock_int16(atomic_int_fast16_t* rwlock,
                atomic_uint_fast8_t* favor,
                int favor_offset)
{
  int16_t expected_lock = 0;
  while (!atomic_compare_exchange_strong_explicit
         (rwlock, &expected_lock, -1,
          memory_order_acquire,
          memory_order_relaxed))
    {
      if (expected_lock < 0)
        return false;
      else
        expected_lock = 0;
    }
  uint8_t mask = ~(1 << favor_offset);
  atomic_fetch_and_explicit(favor, mask, memory_order_relaxed);
  return true;
}

static inline void
rel_wlock_int8(atomic_int_fast8_t* rwlock)
{
  atomic_store_explicit(rwlock, 0, memory_order_release);
}

static inline void
rel_wlock_int16(atomic_int_fast16_t* rwlock)
{
  atomic_store_explicit(rwlock, 0, memory_order_release);
}

static inline void
insert_hpage_internal(HugePage** hpage_ref, HugePage* hpage)
{
  HugePage** it = hpage_ref;
  while (*it && (*it) < hpage)
    it = &(*it)->next;

  if (*it == NULL)
    {
      *it = hpage;
      return;
    }
  // TODO maybe we should assert *it > hpage
  // because equal case should not happen because we always
  // use try wlock.
  else if (*it > hpage)
    {
      hpage->next = (*it);
      *it = hpage;
      return;
    }
}

static inline void
insert_new_raw_hpage(HugePage** hpage_ref,
                     atomic_int_fast16_t* h_rwlock,
                     atomic_uint_fast8_t* h_favor,
                     OPHeap* heap)
{
  if (!acq_wlock(h_rwlock, h_favor, FAVOR_HPAGE))
    return;

  Magic magic = 
    {
      .raw_hpage = 
      {
        .pattern = RAW_HPAGE_PATTERN
      }
    };
  HugePage* hpage = ObtainHPage(heap, magic);
  insert_hpage_internal(hpage_ref, hpage);

  rel_wlock(h_rwlock);
}

static inline void
insert_new_typed_hpage(uint16_t type_alias_id,
                       HugePage** hpage_ref,
                       atomic_int_fast16_t* h_rwlock,
                       atomic_uint_fast8_t* h_favor,
                       OPHeap* heap)
{
  if (!acq_wlock(h_rwlock, h_favor, FAVOR_HPAGE))
    return;

  Magic magic = 
    {
      .typed_hpage = 
      {
        .pattern = TYPED_HPAGE_PATTERN,
        .type_alias = type_alias_id
      }
    };
  HugePage* hpage = ObtainHPage(heap, magic);
  insert_hpage_internal(hpage_ref, hpage);

  rel_wlock(h_rwlock);
}

static inline void
insert_hpage(HugePage** hpage_ref,
             atomic_int_fast16_t* h_rwlock,
             atomic_uint_fast8_t* h_favor,
             HugePage* hpage)
{
  if (!acq_wlock(h_rwlock, h_favor, FAVOR_HPAGE))
    return;

  insert_hpage_internal(hpage_ref, hpage);
  rel_wlock(h_rwlock);
}

static inline void
remove_hpage(HugePage** hpage_ref,
             atomic_int_fast16_t* h_rwlock,
             atomic_uint_fast8_t* h_favor,
             HugePage* hpage)
{
  if (!acq_wlock(h_rwlock, h_favor, FAVOR_HPAGE))
    return;

  HugePage** it = hpage_ref;
  while (*it != hpage)
    it = &(*it)->next;

  *it = (*it)->next;

  rel_wlock(h_rwlock);
}

static inline void
insert_uspan_internal(UnarySpan** uspan_ref, UnarySpan* uspan)
{
  UnarySpan** it = uspan_ref;
  while (*it && (*it) < uspan)
    it = &(*it)->next;

  if (*it == NULL)
    {
      *it = uspan;
      return;
    }
  else if (*it > uspan)
    {
      uspan->next = (*it);
      *it = uspan;
      return;
    }
}


static inline void
insert_new_raw_uspan(RawType* raw_type,
                     uint16_t size_class,
                     uint8_t tid,
                     OPHeap* heap)
{
  if (!acq_wlock(&raw_type->uspan_rwlock[size_class][tid],
                 &raw_type->uspan_favor[size_class],
                 tid))
    return;

  HugePage* hpage = NULL;
  UnarySpan* uspan = NULL;
  Magic magic = 
    {
      .raw_uspan = 
      {
        .pattern = RAW_USPAN_PATTERN,
        .obj_size = size_class,
        .thread_id = tid
      }
    };

  while (1)
    {
      if(!acq_rlock(&raw_type->hpage_rwlock,
                    &raw_type->remain_favor,
                    FAVOR_HPAGE))
        continue;
      hpage = raw_type->hpage;
      if (hpage == NULL)
        {
          favor_write(&raw_type->remain_favor,
                      FAVOR_HPAGE);
          rel_rlock(&raw_type->hpage_rwlock);
          insert_new_raw_hpage(&raw_type->hpage,
                               &raw_type->hpage_rwlock,
                               &raw_type->remain_favor,
                               heap);
          continue;
        }

      uspan = ObtainUSpan(hpage, magic, 1);
      if (uspan == NULL) 
        {
          favor_write(&raw_type->remain_favor,
                      FAVOR_HPAGE);
          rel_rlock(&raw_type->hpage_rwlock);
          // TODO maybe we should optimize it as
          // remove and try insert new hpage...
          remove_hpage(&raw_type->hpage,
                       &raw_type->hpage_rwlock,
                       &raw_type->remain_favor,
                       hpage);
          continue;
        }
      break;
    }

  rel_rlock(&raw_type->hpage_rwlock);
  insert_uspan_internal(&raw_type->uspan[size_class][tid], uspan);
  rel_wlock(&raw_type->uspan_rwlock[size_class][tid]);
}


static inline void
insert_new_typed_uspan(TypeAlias* type_alias,
                       uint16_t obj_size,
                       uint8_t tid,
                       uint16_t type_alias_id,
                       OPHeap* heap)
{
  if (!acq_wlock(&type_alias->uspan_rwlock[tid],
                 &type_alias->uspan_favor,
                 tid))
    return;
  
  HugePage* hpage = NULL;
  UnarySpan* uspan = NULL;
  Magic magic = 
    {
      .typed_uspan = 
      {
        .pattern = TYPED_USPAN_PATTERN,
        .obj_size = obj_size,
        .thread_id = tid,
        .type_alias = type_alias_id
      }
    };

  while (1)
    {
      if(!acq_rlock(&type_alias->hpage_rwlock,
                    &type_alias->remain_favor,
                    FAVOR_HPAGE))
        continue;
      hpage = type_alias->hpage;
      if (hpage == NULL)
        {
          favor_write(&type_alias->remain_favor,
                      FAVOR_HPAGE);
          rel_rlock(&type_alias->hpage_rwlock);
          insert_new_typed_hpage(type_alias_id,
                                 &type_alias->hpage,
                                 &type_alias->hpage_rwlock,
                                 &type_alias->remain_favor,
                                 heap);
          continue;
        }
      // TODO we may optimize to use larger span
      uspan = ObtainUSpan(hpage, magic, 1);
      if (uspan == NULL)
        {
          favor_write(&type_alias->remain_favor,
                      FAVOR_HPAGE);
          rel_rlock(&type_alias->hpage_rwlock);
          remove_hpage(&type_alias->hpage,
                       &type_alias->hpage_rwlock,
                       &type_alias->remain_favor,
                       hpage);
          continue;
        }
      break;
    }
  rel_rlock(&type_alias->hpage_rwlock);
  insert_uspan_internal(&type_alias->uspan[tid], uspan);
  rel_wlock(&type_alias->uspan_rwlock[tid]);
}

static inline void
insert_new_large_uspan(RawType* raw_type,
                       int large_uspan_id,
                       int size_class,
                       int favor,
                       OPHeap* heap)
{
  if (!acq_wlock(&raw_type->large_uspan_rwlock[large_uspan_id],
                 &raw_type->remain_favor,
                 favor))
    return;
  HugePage* hpage = NULL;
  UnarySpan* uspan = NULL;
  Magic magic = 
    {
      .large_uspan = 
      {
        .pattern = LARGE_USPAN_PATTERN,
        .obj_size = size_class,
      }
    };

  while (1)
    {
      if(!acq_rlock(&raw_type->hpage_rwlock,
                    &raw_type->remain_favor,
                    FAVOR_HPAGE))
        continue;
      hpage = raw_type->hpage;
      if (hpage == NULL)
        {
          favor_write(&raw_type->remain_favor,
                      FAVOR_HPAGE);
          rel_rlock(&raw_type->hpage_rwlock);
          insert_new_raw_hpage(&raw_type->hpage,
                               &raw_type->hpage_rwlock,
                               &raw_type->remain_favor,
                               heap);
          continue;
        }

      uspan = ObtainUSpan(hpage, magic, 4);
      if (uspan == NULL) 
        {
          favor_write(&raw_type->remain_favor,
                      FAVOR_HPAGE);
          rel_rlock(&raw_type->hpage_rwlock);
          // TODO maybe we should optimize it as
          // remove and try insert new hpage...
          remove_hpage(&raw_type->hpage,
                       &raw_type->hpage_rwlock,
                       &raw_type->remain_favor,
                       hpage);
          continue;
        }
      break;
    }

  rel_rlock(&raw_type->hpage_rwlock);
  insert_uspan_internal(&raw_type->large_uspan[large_uspan_id], uspan);
  rel_wlock(&raw_type->large_uspan_rwlock[large_uspan_id]);
}


static inline void
remove_uspan(UnarySpan** uspan_ref,
             atomic_int_fast8_t* u_rwlock,
             atomic_uint_fast16_t* u_favor,
             int tid,
             UnarySpan* uspan)
{
  if (!acq_wlock(u_rwlock, u_favor, tid))
    return;

  UnarySpan** it = uspan_ref;
  while (*it != uspan)
    it = &(*it)->next;

  *it = (*it)->next;
  rel_wlock(u_rwlock);
}


static inline void
remove_large_uspan(UnarySpan** uspan_ref,
                   atomic_int_fast16_t* u_rwlock,
                   atomic_uint_fast8_t* u_favor,
                   int favor,
                   UnarySpan* uspan)
{
  if (!acq_wlock(u_rwlock, u_favor, favor))
    return;

  UnarySpan** it = uspan_ref;
  while (*it != uspan)
    it = &(*it)->next;

  *it = (*it)->next;
  rel_wlock(u_rwlock);
}

OP_END_DECLS

#endif /* OP_HEAP_INTERNAL_H */
/* op_lock_utils.h ends here */
