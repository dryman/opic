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
#include <stdatomic.h>
#include "opic/common/op_macros.h"

OP_BEGIN_DECLS

#define ACQ_R_LOCK(RWLOCK, FW, FW_OFFSET)                       \
  do {                                                          \
  __auto_type rwlock_ptr = (RWLOCK);                            \
  __auto_type fw_ptr = (FW);                                    \
  __typeof__ (*fw_ptr) flag = 1 << (FW_OFFSET);                 \
  __typeof__ (*rwlock_ptr) oldlock = atomic_load_explicit       \
    (rwlock_ptr, memory_order_relaxed);                         \
  while (1)                                                     \
    {                                                           \
      if (!(atomic_load_explicit                                \
            ((favor_w),                                         \
             memory_order_relaxed) & flag))                     \
        break;                                                  \
      if (oldlock < 0)                                          \
        {                                                       \
          oldlock = atomic_load_explicit                        \
            (rwlock_ptr, memory_order_relaxed);                 \
        }                                                       \
      if (atomic_compare_exchange_weak_explicit                 \
          (rwlock_ptr, &oldlock, oldlock + 1,                   \
           memory_order_acquire,                                \
           memory_order_relaxed))                               \
        break;                                                  \
    }                                                           \
  } while(0)

#define REL_R_LOCK(RWLOCK)                                      \
  do {                                                          \
  __auto_type rwlock_ptr = (RWLOCK);                            \
  __typeof__ (*rwlock_ptr) oldlock = atomic_load_explicit       \
    (rwlock_ptr, memory_order_relaxed);                         \
  while (!atomic_compare_exchange_weak_explicit                 \
    (rwlock_ptr, &oldlock, oldlock - 1,                         \
     memory_order_release,                                      \
     memory_order_relaxed)) ;                                   \
  } while(0)

#define ACQ_W_LOCK(RWLOCK, FW, FW_OFFSET)                       \
  do {                                                          \
  __auto_type rwlock_ptr = (RWLOCK);                            \
  __typeof__ (*rwlock_ptr) expected_lock = 0;                   \
  while (!atomic_compare_exchange_weak_explicit                 \
    (rwlock_ptr, &expected_lock, -1,                            \
     memory_order_acquire,                                      \
     memory_order_relaxed))                                     \
    expected_lock = 0;                                          \
  atomic_store_explicit(fw_ptr, ~(1 << (FW_OFFSET)),            \
                        memory_order_relaxed);                  \
  } while(0)

OP_END_DECLS

#endif /* OP_LOCK_UTILS_H */
/* op_lock_utils.h ends here */
