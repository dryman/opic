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

OP_BEGIN_DECLS

#define acq_rlock(RWLOCK, FAVOR, OFFSET)                \
  _Generic((RWLOCK),                                    \
           atomic_int_fast8_t: acq_rlock_int8,          \
           atomic_int_fast16_t: acq_rlock_int16)        \
  (RWLOCK, FAVOR, OFFSET)

#define rel_rlock(RWLOCK)                               \
  _Generic((RWLOCK),                                    \
           atomic_int_fast8_t: rel_rlock_int8,          \
           atomic_int_fast16_t: rel_rlock_int16)        \
  (RWLOCK)

#define favor_write(FAVOR, OFFSET)                      \
  _Generic((FAVOR),                                     \
           atomic_int_fast8_t: favor_write_int8,        \
           atomic_int_fast16_t: favor_write_int16)      \
  (FAVOR, OFFSET)

#define acq_wlock(RWLOCK, FAVOR, OFFSET)                \
  _Generic((RWLOCK),                                    \
           atomic_int_fast8_t: acq_wlock_int8,          \
           atomic_int_fast16_t: acq_wlock_int16)        \
  (RWLOCK, FAVOR, OFFSET)

#define rel_wlock(RWLOCK)                               \
  _Generic((RWLOCK),                                    \
           atomic_int_fast8_t: rel_wlock_int8,          \
           atomic_int_fast16_t: rel_wlock_int16)        \
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
favor_write_int8(atomic_int_fast8_t* favor, int offset)
{
  atomic_fetch_or_explicit(favor, 1 << offset,
                           memory_order_relaxed);
}

static inline void
favor_write_int16(atomic_int_fast16_t* favor, int offset)
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

/* static inline void */
/* insert_uspan(UnaryPSpan** uspan_ref, */
/*              atomic_int_fast8_t* u_rwlock, */
/*              atomic_uint_fast16_t* u_favor, */
/*              int tid, */
/*              VPage** vpage_ref, */
/*              atomic_int_fast16_t* v_rwlock, */
/*              atomic_int_fast8_t* v_favor, */
/*              int v_favor_idx, */
/*              OPHeap* heap) */
/* { */
/*   acq_wlock(u_rwlock, u_favor, tid); */
/*   UnaryPSpan** it = uspan_ref; */
/*   while (1) */
/*     { */
/*       if (*it == NULL) */
/*         { */
          
/* } */


OP_END_DECLS

#endif /* OP_LOCK_UTILS_H */
/* op_lock_utils.h ends here */
