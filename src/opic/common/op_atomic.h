/* op_atomic.h --- 
 * 
 * Filename: op_atomic.h
 * Description: 
 * Author: Felix Chern
 * Maintainer: 
 * Created: Fri Nov 25 12:25:48 2016 (-0800)
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
 * You should have received a copy of the GNU Lesser General Public
 * License along with this program.  If not, see
 * <http://www.gnu.org/licenses/>.
 */

/* Code: */

#ifndef OP_ATOMIC_H
#define OP_ATOMIC_H 1

#include "op_macros.h"
#include "stdatomic.h"
#include "stdint.h"
#include "stdbool.h"

OP_BEGIN_DECLS

typedef _Atomic int8_t a_int8_t;
typedef _Atomic int16_t a_int16_t;
typedef _Atomic int32_t a_int32_t;
typedef _Atomic int64_t a_int64_t;
typedef _Atomic uint8_t a_uint8_t;
typedef _Atomic uint16_t a_uint16_t;
typedef _Atomic uint32_t a_uint32_t;
typedef _Atomic uint64_t a_uint64_t;

#define atomic_check_in(PUNCH_CARD)             \
  _Generic((PUNCH_CARD),                        \
           a_int8_t*: atomic_check_in_8,        \
           a_int16_t*: atomic_check_in_16,      \
           a_int32_t*: atomic_check_in_32,      \
           a_int64_t*: atomic_check_in_64)      \
  (PUNCH_CARD)

#define atomic_check_out(PUNCH_CARD)            \
  _Generic((PUNCH_CARD),                        \
           a_int8_t*: atomic_check_out_8,       \
           a_int16_t*: atomic_check_out_16,     \
           a_int32_t*: atomic_check_out_32,     \
           a_int64_t*: atomic_check_out_64)     \
  (PUNCH_CARD)

#define atomic_book_critical(PUNCH_CARD)        \
  _Generic((PUNCH_CARD),                        \
           a_int8_t*: atomic_book_critical_8,   \
           a_int16_t*: atomic_book_critical_16, \
           a_int32_t*: atomic_book_critical_32, \
           a_int64_t*: atomic_book_critical_64) \
  (PUNCH_CARD)

#define atomic_enter_critical(PUNCH_CARD)               \
  _Generic((PUNCH_CARD),                                \
           a_int8_t*: atomic_enter_critical_8,          \
           a_int16_t*: atomic_enter_critical_16,        \
           a_int32_t*: atomic_enter_critical_32,        \
           a_int64_t*: atomic_enter_critical_64)        \
  (PUNCH_CARD)

#define atomic_exit_critical(PUNCH_CARD)        \
  _Generic((PUNCH_CARD),                        \
           a_int8_t*: atomic_exit_critical_8,   \
           a_int16_t*: atomic_exit_critical_16, \
           a_int32_t*: atomic_exit_critical_32, \
           a_int64_t*: atomic_exit_critical_64) \
  (PUNCH_CARD)


static inline bool
atomic_check_in_8(a_int8_t* punch_card)
{
  int8_t val;
  do
    {
      val = atomic_load_explicit(punch_card,
                                 memory_order_relaxed);
      if (val < 0)
        return false;
    }
  while (!atomic_compare_exchange_weak_explicit
         (punch_card, &val, val + 1,
          memory_order_acquire,
          memory_order_relaxed));
  return true;
}

static inline bool
atomic_check_in_16(a_int16_t* punch_card)
{
  int16_t val;
  do
    {
      val = atomic_load_explicit(punch_card,
                                 memory_order_relaxed);
      if (val < 0)
        return false;
    }
  while (!atomic_compare_exchange_weak_explicit
         (punch_card, &val, val + 1,
          memory_order_acquire,
          memory_order_relaxed));
  return true;
}

static inline bool
atomic_check_in_32(a_int32_t* punch_card)
{
  int32_t val;
  do
    {
      val = atomic_load_explicit(punch_card,
                                 memory_order_relaxed);
      if (val < 0)
        return false;
    }
  while (!atomic_compare_exchange_weak_explicit
         (punch_card, &val, val + 1,
          memory_order_acquire,
          memory_order_relaxed));
  return true;
}

static inline bool
atomic_check_in_64(a_int64_t* punch_card)
{
  int64_t val;
  do
    {
      val = atomic_load_explicit(punch_card,
                                 memory_order_relaxed);
      if (val < 0)
        return false;
    }
  while (!atomic_compare_exchange_weak_explicit
         (punch_card, &val, val + 1,
          memory_order_acquire,
          memory_order_relaxed));
  return true;
}

static inline void
atomic_check_out_8(a_int8_t* punch_card)
{
  atomic_fetch_sub_explicit(punch_card,
                            1,
                            memory_order_relaxed);
}

static inline void
atomic_check_out_16(a_int16_t* punch_card)
{
  atomic_fetch_sub_explicit(punch_card,
                            1,
                            memory_order_relaxed);
}

static inline void
atomic_check_out_32(a_int32_t* punch_card)
{
  atomic_fetch_sub_explicit(punch_card,
                            1,
                            memory_order_relaxed);
}

static inline void
atomic_check_out_64(a_int64_t* punch_card)
{
  atomic_fetch_sub_explicit(punch_card,
                            1,
                            memory_order_relaxed);
}

static inline bool
atomic_book_critical_8(a_int8_t* punch_card)
{
  int8_t val = atomic_load_explicit(punch_card, memory_order_relaxed);
  do
    {
      if (val < 0)
        return false;
    }
  while (!atomic_compare_exchange_strong_explicit
         (punch_card, &val, val | (1<<7),
          memory_order_acq_rel,
          memory_order_relaxed));
  return true;
}

static inline bool
atomic_book_critical_16(a_int16_t* punch_card)
{
  int16_t val = atomic_load_explicit(punch_card, memory_order_relaxed);
  do
    {
      if (val < 0)
        return false;
    }
  while (!atomic_compare_exchange_strong_explicit
         (punch_card, &val, val | (1<<15),
          memory_order_acq_rel,
          memory_order_relaxed));
  return true;
}

static inline bool
atomic_book_critical_32(a_int32_t* punch_card)
{
  int32_t val = atomic_load_explicit(punch_card, memory_order_relaxed);
  do
    {
      if (val < 0)
        return false;
    }
  while (!atomic_compare_exchange_strong_explicit
         (punch_card, &val, val | (1<<31),
          memory_order_acq_rel,
          memory_order_relaxed));
  return true;
}

static inline bool
atomic_book_critical_64(a_int64_t* punch_card)
{
  int64_t val = atomic_load_explicit(punch_card, memory_order_relaxed);
  do
    {
      if (val < 0)
        return false;
    }
  while (!atomic_compare_exchange_strong_explicit
         (punch_card, &val, val | (1L<<63),
          memory_order_acq_rel,
          memory_order_relaxed));
  return true;
}

static inline bool
atomic_enter_critical_8(a_int8_t* punch_card)
{
  int8_t val = INT8_MIN + 1;
  if (atomic_compare_exchange_strong_explicit
      (punch_card, &val, val - 1,
       memory_order_acquire,
       memory_order_relaxed))
    return true;
  return false;
}

static inline bool
atomic_enter_critical_16(a_int16_t* punch_card)
{
  int16_t val = INT16_MIN + 1;
  if (atomic_compare_exchange_strong_explicit
      (punch_card, &val, val - 1,
       memory_order_acquire,
       memory_order_relaxed))
    return true;
  return false;
}

static inline bool
atomic_enter_critical_32(a_int32_t* punch_card)
{
  int32_t val = INT32_MIN + 1;
  if (atomic_compare_exchange_strong_explicit
      (punch_card, &val, val - 1,
       memory_order_acquire,
       memory_order_relaxed))
    return true;
  return false;
}

static inline bool
atomic_enter_critical_64(a_int64_t* punch_card)
{
  int64_t val = INT64_MIN + 1;
  if (atomic_compare_exchange_strong_explicit
      (punch_card, &val, val - 1,
       memory_order_acquire,
       memory_order_relaxed))
    return true;
  return false;
}

static inline void
atomic_exit_critical_8(a_int8_t* punch_card)
{
  atomic_store_explicit(punch_card, 1, memory_order_relaxed);
}

static inline void
atomic_exit_critical_16(a_int16_t* punch_card)
{
  atomic_store_explicit(punch_card, 1, memory_order_relaxed);
}

static inline void
atomic_exit_critical_32(a_int32_t* punch_card)
{
  atomic_store_explicit(punch_card, 1, memory_order_relaxed);
}

static inline void
atomic_exit_critical_64(a_int64_t* punch_card)
{
  atomic_store_explicit(punch_card, 1, memory_order_relaxed);
}


OP_END_DECLS
#endif
/* op_atomic.h ends here */
