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

#ifndef OP_LOCK_UTILS_H
#define OP_LOCK_UTILS_H 1

#include <stdint.h>
#include <stdbool.h>
#include <stdatomic.h>
#include "opic/common/op_macros.h"
#include "opic/malloc/op_heap.h"
#include "opic/malloc/op_vpage.h"

OP_BEGIN_DECLS

HugePage* ObtainHPage(OPHeap* self);

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
insert_new_hpage(HugePage** hpage_ref,
                 atomic_int_fast16_t* h_rwlock,
                 atomic_uint_fast8_t* h_favor,
                 int h_favor_idx,
                 OPHeap* heap)
{
  if (!acq_wlock(h_rwlock, h_favor, h_favor_idx))
    return;

  HugePage* hpage = ObtainHPage(heap);
  insert_hpage_internal(hpage_ref, hpage);

  rel_wlock(h_rwlock);
}

static inline void
insert_hpage(HugePage** hpage_ref,
             atomic_int_fast16_t* h_rwlock,
             atomic_uint_fast8_t* h_favor,
             int h_favor_idx,
             HugePage* hpage)
{
  if (!acq_wlock(h_rwlock, h_favor, h_favor_idx))
    return;

  insert_hpage_internal(hpage_ref, hpage);
  rel_wlock(h_rwlock);
}

static inline void
remove_hpage(HugePage** hpage_ref,
             atomic_int_fast16_t* h_rwlock,
             atomic_uint_fast8_t* h_favor,
             int h_favor_idx,
             HugePage* hpage)
{
  if (!acq_wlock(h_rwlock, h_favor, h_favor_idx))
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
insert_new_uspan(Magic magic,
                 UnarySpan** uspan_ref,
                 atomic_int_fast8_t* u_rwlock,
                 atomic_uint_fast16_t* u_favor,
                 int tid,
                 HugePage** hpage_ref,
                 atomic_int_fast16_t* h_rwlock,
                 atomic_uint_fast8_t* h_favor,
                 int h_favor_idx,
                 OPHeap* heap)
{
  if (!acq_wlock(u_rwlock, u_favor, tid))
    return;

  HugePage* hpage;
  UnarySpan* uspan;

  // TODO: we may use a maximum retry, or a counter
  // to count how many retry occorred.
  while (1)
    {      
      acq_rlock(h_rwlock, h_favor, h_favor_idx);
      hpage = *hpage_ref;
      while (hpage != NULL)
        {
          // TODO: how do we determine span_cnt?
          // TODO: for now stick with 1 page.
          uspan = ObtainUSpan(hpage, magic, 1);

          if (uspan) goto uspan_created;
          // TODO: bug, how do we dicomission hpage?
          hpage = hpage->next;
        }
      // Didn't find any suitable hpage, insert a new hpage and start over
      favor_write(h_favor, h_favor_idx);
      rel_rlock(h_rwlock);
      insert_new_hpage(hpage_ref, h_rwlock, h_favor, h_favor_idx, heap);
    }
 uspan_created:
  rel_rlock(h_rwlock);
  insert_uspan_internal(uspan_ref, uspan);
  rel_wlock(u_rwlock);
}

static inline void
insert_uspan(UnarySpan** uspan_ref,
             atomic_int_fast8_t* u_rwlock,
             atomic_uint_fast16_t* u_favor,
             int tid,
             UnarySpan* uspan)
{
  if (!acq_wlock(u_rwlock, u_favor, tid))
    return;
  insert_uspan_internal(uspan_ref, uspan);
  rel_wlock(u_rwlock);
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

OP_END_DECLS

#endif /* OP_LOCK_UTILS_H */
/* op_lock_utils.h ends here */
