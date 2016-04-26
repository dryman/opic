/* This may look like nonsense, but it really is -*- mode: C -*-              */
/*                                                                            */
/* Except for parts copied from previous work and as explicitly stated below, */
/* the author and copyright holder for this work is                           */
/* (C) copyright  2014 Jens Gustedt, INRIA, France                            */
/*                                                                            */
/* This file is free software; it is part of the P99 project.                 */
/* You can redistribute it and/or modify it under the terms of the QPL as     */
/* given in the file LICENSE. It is distributed without any warranty;         */
/* without even the implied warranty of merchantability or fitness for a      */
/* particular purpose.                                                        */
/*                                                                            */
#ifndef P99_RWL_H
#define P99_RWL_H

#include "p99_futex.h"

/**
 ** @addtogroup futex
 ** @{
 **/

/**
 ** @brief A simple rwlock implementation.
 **
 ** This is implemented more or less efficiently according to the
 ** features that the platform provides:
 ** - one that uses atomic operations and futexes for signaling
 ** - one that mutexes all access and uses a condition variable for
 **   signaling.
 **
 ** It has the following properties:
 **
 ** - A lock that is obtained is not bound to a specific thread, any
 **   thread may unlock it.
 **
 ** - If there is a rdlock that is hold, any thread may call
 **   ::p99_rwl_rdlock, again, on the same object. It is the
 **   responsibility of the application to ensure that
 **   ::p99_rwl_unlock is called as many times as it has been locked.
 **
 ** - If a wrlock is hold, nobody, the holding thread including, will
 **   be blocked when calling ::p99_rwl_rdlock or ::p99_rwl_wrlock.
 **
 ** As a consequence, this form of lock can be easily cleaned up if a
 ** thread has left it locked and then walked away:
 ** @code
 ** p99_rwl rwl = P99_RWL_INITIALIZER;
 **
 ** while (p99_rwl_islocked(&rwl))
 **       p99_rwl_unlock(&rwl);
 ** @endcode
 **
 ** This takes care of all situations where no other thread actively
 ** is trying to achieve the lock.
 **/
#ifdef P00_DOXYGEN
struct p99_rwl {};
#else
typedef struct p99_rwl p99_rwl;
struct p99_rwl {
  p99_futex p00_f;
  _Atomic(unsigned) p00_w;
};
#endif

#define P00_RWL_EXCL UINT_MAX

#ifndef P00_RWL_DIAG
# define P00_RWL_DIAG(...) P99_NOP
#endif

/**
 ** @brief Initialize an ::p99_rwl object.
 **/
# define P99_RWL_INITIALIZER                                   \
{                                                              \
  .p00_f = P99_FUTEX_INITIALIZER,                              \
  .p00_w = ATOMIC_VAR_INIT(0),                                 \
}

/**
 ** @brief Initialize an ::p99_rwl object.
 **/
p99_inline
p99_rwl* p99_rwl_init(p99_rwl* p00_r) {
  if (p00_r) {
    p99_futex_init(&p00_r->p00_f, 0u);
    atomic_init(&p00_r->p00_w, 0u);
  }
  return p00_r;
}

p99_inline
void p99_rwl_destroy(p99_rwl* p00_r) {
  if (p00_r) {
    p99_futex_destroy(&p00_r->p00_f);
  }
}

/**
 ** @brief establish a shared lock for rwlock @a p00_c.
 **
 ** This will inhibit to take an exclusive lock for anybody.
 **
 ** @remark blocks until the lock can be achieved or until an error is
 ** detected.
 **
 ** @return EAGAIN if there are already too many lockers, 0 in all
 ** other cases
 ** @related p99_rwl
 **/
P00_FUTEX_INLINE(p99_rwl_rdlock)
int p99_rwl_rdlock(p99_rwl volatile* p00_r) {
  uint p00_res = 0;
  atomic_fetch_add_explicit(&(p00_r->p00_w), 1u, memory_order_acq_rel);
  P99_FUTEX_COMPARE_EXCHANGE(&(p00_r->p00_f), p00_act,
                             /* block if there is an exclusive lock or
                                already too many readers */
                             (P00_RWL_DIAG(stderr, "rdlock found %u\n", p00_act),
                              (p00_act < P00_RWL_EXCL-1)),
                             /* as soon as there is no exclusive lock
                                and the number of waiters is not too
                                big add us to the count */
                             (p00_res = ((p00_act < P00_RWL_EXCL-1) ? p00_act + 1U : p00_act)),
                             /* never wakeup anybody */
                             0U, 0U);
  atomic_fetch_add_explicit(&(p00_r->p00_w), -1u, memory_order_acq_rel);
  P00_RWL_DIAG(stderr, "rdlock set to %u\n", p00_res);
  /* Return EAGAIN if we couldn't increment because there were too
     many waiters. */
  return (p00_res <= P00_RWL_EXCL-1)
         ? 0
         : EAGAIN;
}

/**
 ** @brief establish an exclusive lock for rwlock @a p00_r.
 **
 ** This will inhibit anybody else, this thread including, to take a
 ** lock on @a p00_r.
 **
 ** @remark blocks until the lock can be achieved
 **
 ** @return 0
 ** @related p99_rwl
 **/
P00_FUTEX_INLINE(p99_rwl_wrlock)
int p99_rwl_wrlock(p99_rwl volatile* p00_r) {
  uint p00_res = 0;
  atomic_fetch_add_explicit(&(p00_r->p00_w), 1u, memory_order_acq_rel);
  P99_FUTEX_COMPARE_EXCHANGE(&(p00_r->p00_f), p00_act,
                             /* block if there is any lock */
                             (P00_RWL_DIAG(stderr, "wrlock found %u\n", p00_act), !p00_act),
                             /* as soon as there is no lock, reserve exclusively */
                             (p00_res = P00_RWL_EXCL),
                             /* never wakeup anybody */
                             0U, 0U);
  atomic_fetch_add_explicit(&(p00_r->p00_w), -1u, memory_order_acq_rel);
  P00_RWL_DIAG(stderr, "wrlock set to %u\n", p00_res);
  return 0;
}

/**
 ** @brief release a lock on rwlock @a p00_r.
 **
 ** @return 0
 ** @related p99_rwl
 **/
P00_FUTEX_INLINE(p99_rwl_inc_conditionally)
int p99_rwl_unlock(p99_rwl volatile* p00_r) {
  uint p00_res = 0;
  P99_FUTEX_COMPARE_EXCHANGE(&(p00_r->p00_f), p00_act,
                             /* never block */
                             (P00_RWL_DIAG(stderr, "unlock found %u\n", p00_act), true),
                             /* decrement for shared locks, force to 0 for exclusives */
                             (p00_res = ((p00_act == P00_RWL_EXCL) ? 0U : p00_act - 1U)),
                             /* wakeup potential waiters if any and
                                the count fell to 0 */
                             0U, (p00_res ? 0U : atomic_load(&p00_r->p00_w)));
  P00_RWL_DIAG(stderr, "unlock set to %u\n", p00_res);
  return 0;
}

/**
 ** @brief Tell if @a is locked.
 **
 ** @remark this gives only a temporary picture of the lock state
 **
 ** @related p99_rwl
 **/
p99_inline bool p99_rwl_islocked(p99_rwl volatile* p00_r) {
  return p99_futex_load(&(p00_r->p00_f));
}

/**
 ** @brief Tell if @a has waiters.
 **
 ** @remark this gives only a temporary picture of the lock state
 **
 ** @related p99_rwl
 **/
p99_inline bool p99_rwl_haswaiters(p99_rwl volatile* p00_r) {
  return atomic_load(&(p00_r->p00_w));
}

# ifndef P99_SIMPLE_BLOCKS
/**
 ** @brief protect the depending statement or block by a shared lock
 **
 ** @see p99_rwl
 **/
#  define P99_RDLOCK(RWLOCK)                                                          \
P00_BLK_START                                                                         \
P00_BLK_DECL(int, p00_errNo, 0)                                                       \
P99_GUARDED_BLOCK(p99_rwl*,                                                           \
                  P99_FILEID(rwlock),                                                 \
                  &(RWLOCK),                                                          \
                  (void)(P99_UNLIKELY(p00_errNo = p99_rwl_rdlock(P99_FILEID(rwlock))) \
                         && (fprintf(stderr,                                          \
                                     __FILE__ ":"                                     \
                                     P99_STRINGIFY(__LINE__) ": read lock error for " \
                                     P99_STRINGIFY(RWLOCK) ", %s",                    \
                                     strerror(p00_errNo)), 1)                         \
                         && (P99_FILEID(rwlock) = 0, 1)                               \
                         && (P99_UNWIND(-1), 1)                                       \
                         ),                                                           \
                  (void)(P99_FILEID(rwlock)                                           \
                         && p99_rwl_unlock(P99_FILEID(rwlock))))


/**
 ** @brief protect the depending statement or block by an exclusive lock
 **
 ** @see p99_rwl
 **/
#  define P99_WRLOCK(RWLOCK)                                                           \
P00_BLK_START                                                                          \
P00_BLK_DECL(int, p00_errNo, 0)                                                        \
P99_GUARDED_BLOCK(p99_rwl*,                                                            \
                  P99_FILEID(rwlock),                                                  \
                  &(RWLOCK),                                                           \
                  (void)(P99_UNLIKELY(p00_errNo = p99_rwl_wrlock(P99_FILEID(rwlock)))  \
                         && (fprintf(stderr,                                           \
                                     __FILE__ ":"                                      \
                                     P99_STRINGIFY(__LINE__) ": write lock error for " \
                                     P99_STRINGIFY(RWLOCK) ", %s",                     \
                                     strerror(p00_errNo)), 1)                          \
                         && (P99_FILEID(rwlock) = 0, 1)                                \
                         && (P99_UNWIND(-1), 1)                                        \
                         ),                                                            \
                  (void)(P99_FILEID(rwlock)                                            \
                         && p99_rwl_unlock(P99_FILEID(rwlock))))
# else
#  define P99_RDLOCK(RWLOCK)                                   \
P99_GUARDED_BLOCK(p99_rwl*,                                    \
                  P99_FILEID(rwlock),                          \
                  &(RWLOCK),                                   \
                  p99_rwl_rdlock(P99_FILEID(rwlock)),          \
                  p99_rwl_unlock(P99_FILEID(rwlock)))


#  define P99_WRLOCK(RWLOCK)                                   \
P99_GUARDED_BLOCK(p99_rwl*,                                    \
                  P99_FILEID(rwlock),                          \
                  &(RWLOCK),                                   \
                  p99_rwl_wrlock(P99_FILEID(rwlock)),          \
                  p99_rwl_unlock(P99_FILEID(rwlock)))
# endif


/**
 ** @}
 **/


#endif
