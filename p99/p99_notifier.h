/* This may look like nonsense, but it really is -*- mode: C -*-              */
/*                                                                            */
/* Except for parts copied from previous work and as explicitly stated below, */
/* the author and copyright holder for this work is                           */
/* (C) copyright  2012-2014 Jens Gustedt, INRIA, France                       */
/*                                                                            */
/* This file is free software; it is part of the P99 project.                 */
/* You can redistribute it and/or modify it under the terms of the QPL as     */
/* given in the file LICENSE. It is distributed without any warranty;         */
/* without even the implied warranty of merchantability or fitness for a      */
/* particular purpose.                                                        */
/*                                                                            */
#ifndef P99_NOTIFIER_H
#define P99_NOTIFIER_H

#include "p99_futex.h"

/**
 ** @addtogroup futex
 ** @{
 **/

/**
 ** @brief Set a flag and notify other threads that an event has
 ** occurred.
 **
 ** Such a variable stores a state and enables threads to wait for a
 ** certain value of that state.
 **
 ** Per default, the state space that is used are just the values @c 0
 ** and @c 1 but other values that are compatible with @c unsigned or
 ** @c int, e.g enumeration types, could be used as well.
 **
 ** The state with value @c 0 is special and should not be waited for.
 **
 ** A typical example could be a herd of threads. Let us suppose that
 ** we have a main thread that launches such a herd:
 **
 ** @code
 ** p99_notifier all_started = P99_NOTIFIER_INITIALIZER;
 **
 ** for (size_t i = 0; i < n; ++i)
 **   start_my_threads(i, &all_started);
 **
 ** p99_notifier_set(&all_started);
 ** // ... do something clever ...
 **
 ** // ... join all the threads ...
 ** @endcode
 **
 ** Then every thread should just block on that notifier at the
 ** beginning of its function
 **
 ** @code
 ** int my_thread_function(void* arg) {
 **   p99_notifier* all = arg;
 **   p99_notifier_block(all);
 **   ...
 ** }
 ** @endcode
 **
 ** @see p99_notifier_set
 ** @see p99_notifier_block
 ** @see p99_notifier_load
 ** @see p99_notifier_unset
 **/
#ifdef P00_DOXYGEN
struct p99_notifier { };
#else
typedef p99_futex p99_notifier;
#endif

/**
 ** @brief Initialize a notifier to value @a p00_v
 ** @related p99_notifier
 **/
P99_DEFARG_DOCU(p99_notifier_init)
p99_inline
p99_notifier* p99_notifier_init(p99_notifier* p00_n, unsigned p00_v) {
  return p99_futex_init(p00_n, p00_v);
}

#ifndef DOXYGEN
#define p99_notifier_init(...) P99_CALL_DEFARG(p99_notifier_init, 2, __VA_ARGS__)
#define p99_notifier_init_defarg_1() 0U
#endif


/**
 ** @brief destroy a notifier
 ** @related p99_notifier
 **/
p99_inline
void p99_notifier_destroy(p99_notifier* p00_n) {
  p99_futex_destroy(p00_n);
}

/**
 ** @brief Block until the notification flag has been set to the
 ** indicated value.
 **
 ** Non blocking if the flag is already set to @a p00_v.
 **
 ** @remark @a p00_v defaults to @c 1.
 ** @related p99_notifier
 **/
P99_DEFARG_DOCU(p99_notifier_block)
P00_FUTEX_INLINE(p99_notifier_block)
void p99_notifier_block(p99_notifier volatile* p00_n, unsigned p00_v) {
  P99_FUTEX_COMPARE_EXCHANGE(p00_n, p00_act,
                             /* wait for p00_v */
                             (p00_act == p00_v),
                             /* never update */
                             p00_act,
                             /* never wakeup others */
                             0u, 0u);
}

#ifndef DOXYGEN
#define p99_notifier_block(...) P99_CALL_DEFARG(p99_notifier_block, 2, __VA_ARGS__)
#define p99_notifier_block_defarg_1() 1U
#endif

/**
 ** @brief Initialize an ::p99_notifier object.
 **/
# define P99_NOTIFIER_INITIALIZER P99_FUTEX_INITIALIZER(0u)

/**
 ** @brief Return the value of the notifier. Non blocking.
 ** @related p99_notifier
 **/
p99_inline
unsigned p99_notifier_load(p99_notifier volatile* p00_n) {
  return p99_futex_load(p00_n);
}

/**
 ** @brief Set the notifier flag to @a p00_v and wake up all potential
 ** waiters.
 **
 ** @remark @a p00_v defaults to @c 1.
 ** @related p99_notifier
 **/
P99_DEFARG_DOCU(p99_notifier_set)
P99_SETJMP_INLINE(p99_notifier_set)
void p99_notifier_set(p99_notifier volatile* p00_n, unsigned p00_v) {
  if (p00_v)
    P99_FUTEX_COMPARE_EXCHANGE(p00_n,
                               // name of the local variable
                               p00_l,
                               // never wait
                               true,
                               // the new value
                               p00_v,
                               // no enforced wake up
                               0u,
                               // wake up all waiters only if there was a change
                               ((p00_l != p00_v) ? P99_FUTEX_MAX_WAITERS : 0u));
  else
    P99_FUTEX_COMPARE_EXCHANGE(p00_n,
                               // name of the local variable
                               p00_l,
                               // never wait
                               true,
                               // the new value
                               p00_v,
                               // never wake up anybody
                               0u, 0u);
}

#ifndef DOXYGEN
#define p99_notifier_set(...) P99_CALL_DEFARG(p99_notifier_set, 2, __VA_ARGS__)
#define p99_notifier_set_defarg_1() 1U
#endif

/**
 ** @brief Unconditionally reset the notifier to value @c 0.
 **
 ** This should only be used when it is known that there is no waiter
 ** for the notifier.
 **
 ** @related p99_notifier
 **/
p99_inline
void p99_notifier_unset(p99_notifier volatile* p00_n) {
  p99_futex_exchange(p00_n, 0u, 1u, 0u, 0u, 0u);
}

/**
 ** @}
 **/


#endif
