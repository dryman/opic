/* This may look like nonsense, but it really is -*- mode: C -*-              */
/*                                                                            */
/* Except for parts copied from previous work and as explicitly stated below, */
/* the author and copyright holder for this work is                           */
/* (C) copyright  2012 Jens Gustedt, INRIA, France                            */
/*                                                                            */
/* This file is free software; it is part of the P99 project.                 */
/* You can redistribute it and/or modify it under the terms of the QPL as     */
/* given in the file LICENSE. It is distributed without any warranty;         */
/* without even the implied warranty of merchantability or fitness for a      */
/* particular purpose.                                                        */
/*                                                                            */
#ifndef P99_FUTEX_H
#define P99_FUTEX_H

#include "p99_type.h"
#include "p99_threads.h"
#include "p99_posix_default.h"

P99_DECLARE_STRUCT(p99_futex_c11);

#if defined(DOXYGEN)
#define P00_FUTEX_INLINE(NAME) p99_inline

#elif (defined(__linux__) && !defined(NO_FUTEX)) || defined(DOXYGEN)
typedef _Atomic(unsigned) p99_futex;
#define P00_FUTEX_INLINE(NAME) p99_inline

#else
typedef p99_futex_c11 p99_futex;
/* The C11 implementation needs setjmp in its internals so the
   functions must be implemented as weak symbols. */
#define P00_FUTEX_INLINE(NAME) P99_WEAK(NAME)
#endif

/**
 ** @addtogroup library_support Compiler and system support features
 ** @{
 **/

/**
 ** @}
 **/


/**
 ** @addtogroup futex Fast User space locking and signaling
 **
 ** @brief A simple to use integer valued conditional for user code
 **
 ** Most C11 or POSIX lock-and-wait structures have the disadvantage
 ** that they may have so-called spurious wakeups. These are wakeups
 ** that are not related to the application code signaling changes,
 ** but wakeups that are related to some internal OS events in which
 ** the programmer (that is not a system programmer) usually is not
 ** interested.
 **
 ** Starting from a brilliant idea in the Linux kernel, this
 ** implements a feature that can be seen as a primitive for locks and
 ** wakeup control structure. In fact it could be used to build up all
 ** other usual control structures (mutexes, conditional variables,
 ** read-write locks, barriers, semaphores ...)
 **
 ** There is only one feature that is yet missing, here, which is wait
 ** calls that would time out, such as ::mtx_timedlock or
 ** ::cnd_timedwait provide it, e.g. There is no principal hurdle to
 ** overcome for the addition of such a feature, I just don't use
 ** these often, and so I am not yet sure about what interface I would
 ** provide for this.
 **
 ** @{
 **/

#ifdef P00_DOXYGEN
/**
 ** @brief A counter similar to a conditional variable that allows
 ** atomic increment and decrement and to wait for the atomic compare
 ** and exchange for a specific value.
 **
 ** This data structure is inspired by the linux system call @c futex,
 ** thus the name. Linux futex (Fast User muTEX) allows to have a full
 ** fledged control structure on just one @c int. The contents of the
 ** @c int is taken to reflect the state of the structure and its
 ** address and value can be used to block the calling thread until a
 ** certain value is reached. That feature transparently uses the
 ** kernel address of the @c int, so the waiting can be organized even
 ** between different processes that don't share their address space.
 **
 ** ::p99_futex are build around this only that for ideological
 ** reasons the base type is an @c unsigned, instead of an @c int.
 **
 **  - a ::p99_futex represents an unsigned value
 **    - the access to the value is atomic
 **
 **  - a ::p99_futex represents a lock and wait utility
 **    - the entrance into the OS wait queue is atomic, a thread only
 **      enters the OS wait if the state is what the thread expects
 **    - it will only wake up threads when the unsigned value has
 **      changed, or another thread signals the futex explicitly
 **    - there are no <em>spurious wakeups</em>, state changes of threads
 **      only depend on state changes of the value of the futex
 **      or user space actions
 **    - the number of threads that are woken up can be controlled:
 **      - a minimal number may be used to block (actively!) a thread
 **        until enough others are woken up
 **      - a maximum number may also be given
 **
 ** There are several operations that work on that value similar to
 ** their atomic analogues:
 **  - ::p99_futex_load returns the value
 **  - ::p99_futex_exchange atomically exchanges the value with
 **    a new one and returns the old one
 **  - ::p99_futex_add atomically adds a quantity to the value
 **  - ::P99_FUTEX_COMPARE_EXCHANGE atomically compares the existing
 **    value and conditionally exchanges it.
 **
 ** The last three may also be used to wakeup threads that are waiting
 ** on the futex, the very last, a macro, may also put the calling
 ** thread to a blocking or waiting state.
 **
 ** There is only ::p99_futex_add operation and no subtraction. That
 ** operation is simply not needed, because adding a negative value in
 ** @c unsigned arithmetic will magically do the right thing, here.
 **
 ** If the value of the futex isn't as expected, a thread may wait
 ** (::p99_futex_wait) until another thread notifies it
 ** (::p99_futex_wakeup) about a change of the value. That wait is not
 ** (or scarcely) using resources. Such a waiting thread will only be
 ** awoken if another thread wants so. Either by calling an explicit
 ** ::p99_futex_wakeup, or implicitly by changing the value through
 ** ::p99_futex_exchange, ::p99_futex_add or
 ** ::P99_FUTEX_COMPARE_EXCHANGE.
 **
 ** :p99_futex_exchange and ::p99_futex_add wake up waiters if
 ** the value reaches a certain interval. Therefore they have
 ** additional arguments @c p00_cstart, @c p00_clen and @c p00_wmin @c
 ** p00_wmax that give two ranges. One of the conditional values and
 ** one of a range of waiters that should be woken up.
 **
 ** ::P99_FUTEX_COMPARE_EXCHANGE is the most generic tool to operate
 ** on a ::p99_futex, since it is able to wait until the value is as
 ** expected, change it and then notify other threads about the
 ** change.
 **
 ** ::p99_futex is implemented more or less efficiently according to the
 ** features that the platform provides:
 ** - one, for Linux, that uses atomic operations and futexes for signaling
 ** - a fall back that mutexes all access and uses a condition variable for
 **   signaling.
 **
 ** @see P99_FUTEX_COMPARE_EXCHANGE for some examples
 ** @see p99_notifier for a derived data structure to have a group of threads wait for an event
 ** @see p99_count for a resource counter
 **/
struct p99_futex { };
#endif



/**
 ** @def P99_FUTEX_INITIALIZER(INITIAL)
 ** @brief Initialize an ::p99_futex object.
 ** @related p99_futex
 **/

/**
 ** @brief the maximum number of waiters that an ::p99_futex may have
 ** @related p99_futex
 **/
# define P99_FUTEX_MAX_WAITERS (INT_MAX+0U)


/**
 ** @brief Initialize an ::p99_futex object.
 ** @related p99_futex
 **/
p99_inline p99_futex* p99_futex_init(p99_futex* p00_c, unsigned p00_ini);

/**
 ** @brief Destroy an ::p99_futex object.
 ** @related p99_futex
 **/
p99_inline void p99_futex_destroy(p99_futex* p00_c);

/**
 ** @brief increment the counter of @a p00_fut atomically by @a p00_hmuch.
 **
 ** @return the previous value of the counter
 **
 ** After effecting the operation atomically, some waiters on this
 ** ::p99_futex will be woken up if the new value of the futex is in
 ** the range that is specified by the arguments @a p00_cstart and @a
 ** p00_clen. See ::P99_FUTEX_COMPARE_EXCHANGE for more details on the
 ** rules for the @a p00_wmin and @a p00_wmax counts.
 **
 ** If @a p00_hmuch is @c 0, nothing is added so ::p99_futex_add is
 ** equivalent to ::p99_futex_load but with the additional effect
 ** that waiters might be woken up.
 **
 ** @remark to decrement the counter, just pass a negative argument to
 ** @a p00_hmuch. The modulo arithmetic for @c unsigned will do the rest
 ** for you.
 ** @remark Waiters that wait for a value in the @a p00_clen element
 ** range starting at @a p00_cstart will be woken up if the counter
 ** reaches that value with this operation.
 ** @remark @a p00_clen defaults to @c 1u
 ** @remark @a p00_wmin defaults to @c 0u
 ** @remark @a p00_wmax defaults to ::P99_FUTEX_MAX_WAITERS
 ** @related p99_futex
 **/
P99_DEFARG_DOCU(p99_futex_add)
P00_FUTEX_INLINE(p99_futex_add) unsigned p99_futex_add(p99_futex volatile* p00_fut, unsigned p00_hmuch,
    unsigned p00_cstart, unsigned p00_clen,
    unsigned p00_wmin, unsigned p00_wmax);

#ifndef DOXYGEN
#define p99_futex_add(...) P99_CALL_DEFARG(p99_futex_add, 6, __VA_ARGS__)
#define p99_futex_add_defarg_3() 1u
#define p99_futex_add_defarg_4() 0u
#define p99_futex_add_defarg_5() P99_FUTEX_MAX_WAITERS
#endif


/**
 ** @brief Obtain the value of futex @a p00_fut atomically.
 ** @related p99_futex
 **/
P00_FUTEX_INLINE(p99_futex_load) unsigned p99_futex_load(p99_futex volatile* p00_fut);

/**
 ** @brief Unconditionally and atomically set the futex @a p00_fut to
 ** value @a p00_desired.
 **
 ** After effecting the operation atomically, some waiters on this
 ** ::p99_futex will be woken up if the new value of the futex is in
 ** the range that is specified by the arguments @a p00_cstart and @a
 ** p00_clen. See ::P99_FUTEX_COMPARE_EXCHANGE for more details on the
 ** rules for the @a p00_wmin and @a p00_wmax counts.
 **
 ** Also signals eventual waiters if the futex falls within the given range.
 ** @return the previous value of the futex
 ** @remark Waiters that wait for a value in the @a p00_clen element
 ** range starting at @a p00_cstart will be woken up if the counter
 ** reaches that value with this operation.
 ** @remark This signaling of waiters might not be performed if the
 ** counter reached @a p00_cstart because it wrapped around.
 ** @remark @a p00_clen defaults to @c 1u
 ** @remark @a p00_wmin defaults to @c 0u
 ** @remark @a p00_wmax defaults to ::P99_FUTEX_MAX_WAITERS
 ** @related p99_futex
 **/
P99_DEFARG_DOCU(p99_futex_exchange)
P00_FUTEX_INLINE(p99_futex_exchange) unsigned p99_futex_exchange(p99_futex volatile* p00_fut, unsigned p00_desired,
    unsigned p00_cstart, unsigned p00_clen,
    unsigned p00_wmin, unsigned p00_wmax);

#ifndef DOXYGEN
#define p99_futex_exchange(...) P99_CALL_DEFARG(p99_futex_exchange, 6, __VA_ARGS__)
#define p99_futex_exchange_defarg_3() 1u
#define p99_futex_exchange_defarg_4() 0u
#define p99_futex_exchange_defarg_5() P99_FUTEX_MAX_WAITERS
#endif

/**
 ** @brief Wake up threads that are waiting for a futex
 ** @related p99_futex
 **
 ** Most other ::p99_futex functions or macros also fulfill this
 ** functionality conditionally as a side effect when they change the
 ** value of the futex.
 **
 ** @see P99_FUTEX_COMPARE_EXCHANGE for more detailed explanations
 **/
P00_FUTEX_INLINE(p99_futex_wakeup)
void p99_futex_wakeup(p99_futex volatile* p00_fut,
                      unsigned p00_wmin, unsigned p00_wmax);


/**
 ** @brief Unconditionally wait for futex @a p00_fut
 ** @related p99_futex
 **
 ** This deschedules the calling thread until it is woken up by
 ** another thread through ::p99_futex_wakeup or equivalent.
 **
 ** @remark Such a waiting thread will not be subject to spurious wake
 ** ups when receiving signals.
 **/
P00_FUTEX_INLINE(p99_futex_wait)
void p99_futex_wait(p99_futex volatile* p00_fut);



#ifdef DOXYGEN
/**
 ** @brief a catch all macro to operate on ::p99_futex
 ** @related p99_futex
 **
 ** @param FUTEX a pointer that is compatible to <code>p99_futex
 ** volatile*</code>
 **
 ** @param ACT an identifier that can be used in the following
 ** parameters. If used there it will correspond to local @c register
 ** variable of type <code>unsigned const</code> holding the actual
 ** value of the futex. That variable cannot be modified and its
 ** address cannot be taken.
 **
 ** The other parameters are expressions that may contain arbitrary
 ** code that is valid at the point of calling this macro.  The
 ** evaluation may include the local variable @a ACT. Here is a pseudo
 ** code of what this macro actually does:
 **
 ** @code
 ** for (;;) {
 **   register unsigned const ACT = <load value from FUTEX>;
 **   if (EXPECTED) {
 **     if (ACT != (DESIRED)) {
 **       <try to change value of FUTEX to DESIRED>;
 **       if (<not successful>) continue;
 **     }
 **     unsigned wmin = (WAKEMIN);
 **     unsigned wmax = (WAKEMAX);
 **     if (wmin < wmax) wmax = wmin;
 **     <wakeup at least wmin and at most wmax waiters>
 **   } else {
 **     <block and wait until a change is signaled on FUTEX>
 **   }
 ** }
 ** @endcode
 **
 ** Only that each of the macro parameters is expanded exactly once
 ** for the C code. As this is a loop structure the code resulting
 ** from that argument expansion of @a EXPECTED and @a DESIRED may
 ** effectively be evaluated multiple times at run time, in particular
 ** when there is congestion on the futex.
 **
 ** @param EXPECTED is an expression that is interpreted as a Boolean
 ** condition. The calling thread will be blocked until this
 ** expression evaluates to @c true.
 **
 ** @remark @a EXPECTED should never be set to the constant @c false,
 ** since will result in the thread being blocked in the @c for loop.
 **
 ** @param DESIRED is an expression that is interpreted as an @c
 ** unsigned. Once the futex fulfills the condition @a EXPECTED the
 ** futex is atomically set to that value if necessary.
 **
 ** @warning @a EXPECTED and @a DESIRED may be evaluated several times
 ** if the underlying atomic compare exchange operations fails
 ** temporarily. So you should not have destructive side effects in
 ** these expressions.
 **
 ** After the futex value has been set atomically to the desired
 ** value, waiters may be woken up.
 **
 ** @param WAKEMIN is an expression that is interpreted as an @c
 ** unsigned that should not exceed ::P99_FUTEX_MAX_WAITERS. The
 ** calling thread will block until it has woken up at least that
 ** number of waiters.
 **
 ** @warning blocking on the @a WAKEMIN condition can be an active
 ** wait and should be avoided whenever possible.
 **
 ** @param WAKEMAX is an expression that is interpreted as an @c
 ** unsigned that should not exceed ::P99_FUTEX_MAX_WAITERS. @a
 ** WAKEMAX is adjusted to be at least as large as @a WAKEMIN.
 **
 ** <h3>Example 1: a semaphore implementation</h3>
 **
 ** To see how to use this, let us look into an implementation of a
 ** semaphore, starting with a "post" operation.
 **
 **  - Such a post operation on a semaphore should not place any
 **    condition to perform the post action so @a EXPECTED should
 **    always be true.
 **
 ** - The operation should increment the value by one, so @a DESIRED
 **   should be <code>ACT + 1</code>.
 **
 ** - It should always wake up potential waiters, so @a WAKEMAX
 **   shouldn't be @c 0.
 **
 ** - It should not wake up more than one waiters to avoid the waiters
 **   racing for one little token that had been placed. So @a WAKEMAX
 **   should be 1.
 **
 ** @code
 ** inline
 ** int my_sem_post(p99_futex volatile* f) {
 **   P99_FUTEX_COMPARE_EXCHANGE(f,
 **                              // name of the local variable
 **                              val,
 **                              // never wait
 **                              true,
 **                              // increment the value
 **                              val + 1u,
 **                              // wake up at most one waiter
 **                              0u, 1u);
 **   return 0;
 ** }
 ** @endcode
 **
 ** So effectively, such a post operation is just incrementing the
 ** value by one and then it up wakes some waiters. In a real world
 ** implementation this would better be done by using
 ** ::p99_futex_add.
 **
 ** A semaphore <em>wait operation</em> should block if the value is
 ** @c 0, and then, once the value is positive, decrement that value
 ** by @c 1 and never wake up any other waiters:
 **
 ** @code
 ** inline
 ** void my_sem_wait(p99_futex volatile* f) {
 **   P99_FUTEX_COMPARE_EXCHANGE(f,
 **                              // name of the local variable
 **                              val,
 **                              // block if val is 0 and retry
 **                              val > 0,
 **                              // once there is val, decrement it, if possible
 **                              val - 1u,
 **                              // never wake up anybody
 **                              0u, 0u);
 **   return 0;
 ** }
 ** @endcode
 **
 ** A semaphore trywait operation should never block, but only
 ** decrement the value if it is not @c 0, and never wake up any
 ** waiters. A trywait operation must be able to return a value that
 ** indicates success or failure of the operation. We set the return
 ** value by side effect in the @a WAKEMIN expression, where we know
 ** that it is evaluated only once.
 **
 ** @code
 ** inline
 ** int my_sem_trywait(p99_futex volatile* f) {
 **   int ret;
 **   P99_FUTEX_COMPARE_EXCHANGE(f,
 **                              // name of the local variable
 **                              val,
 **                              // never wait
 **                              true,
 **                              // if there is val decrement by one
 **                              (val ? 0u : val - 1u),
 **                              // capture the error by side effect
 **                              (ret = -!val, 0u),
 **                              // never wake up anybody
 **                              0u, 0u);
 **   if (ret) errno = EAGAIN;
 **   return ret;
 ** }
 ** @endcode
 **
 ** <h3>Example 2: reference counting</h3>
 **
 ** Another example of the use of an ::p99_futex could be a reference
 ** counter. Such a counter can e.g be useful to launch a number of
 ** threads, and then wait for all the threads to have finished.
 **
 ** @code
 ** int launch_my_threads_detached(void *arg) {
 **  p99_futex* fut = arg;
 **  ...
 **  my_counter_unlock(fut);
 **  return 0;
 ** }
 **
 ** p99_futex fut;
 ** p99_futex_init(&fut);
 ** for (size_t i = 0; i < large_number; ++i) {
 **   my_counter_lock(&fut);
 **   thrd_t id;
 **   thrd_create(&id, launch_my_threads_detached, &fut);
 **   thrd_detach(id);
 ** }
 ** ...
 ** my_counter_wait(&fut);
 ** @endcode
 **
 ** For that scheme to work we just need three "counter" functions.
 ** The first just silently piles up references:
 **
 ** @code
 ** inline
 ** void my_counter_lock(p99_futex volatile* f) {
 **   P99_FUTEX_COMPARE_EXCHANGE(f, val, true, val + 1u, 0u, 0u);
 ** }
 ** @endcode
 **
 ** So effectively, such an operation is just incrementing the value
 ** by one. In a real world implementation this would better be done
 ** by using ::atomic_fetch_add.
 **
 ** An unlock operation should decrement the value and, if the value
 ** falls to @c 0, wake up all waiters:
 **
 ** @code
 ** inline
 ** void my_counter_unlock_unsafe(p99_futex volatile* f) {
 **   P99_FUTEX_COMPARE_EXCHANGE(f,
 **                              // name of the local variable
 **                              val,
 **                              // never wait
 **                              true,
 **                              // decrement by one
 **                              val - 1u,
 **                              // no enforced wake up
 **                              0u,
 **                              // wake up all waiters iff the value falls to 0
 **                              ((val == 1u) ? P99_FUTEX_MAX_WAITERS : 0u));
 ** }
 ** @endcode
 **
 ** This unsafe version makes no provision for underflow of the
 ** counter in case these functions are used erroneously. A safer
 ** variant would look like this:
 **
 ** @code
 ** inline
 ** void my_counter_unlock(p99_futex volatile* f) {
 **   P99_FUTEX_COMPARE_EXCHANGE(f, val,
 **                              // name of the local variable
 **                              val,
 **                              // never wait
 **                              true,
 **                              // decrement by one, but only if wouldn't be underflow
 **                              (val ? val - 1u : 0u),
 **                              // no enforced wake up
 **                              0u,
 **                              // wake up all waiters iff the new value is 0
 **                              ((val <= 1u) ? P99_FUTEX_MAX_WAITERS : 0u));
 ** }
 ** @endcode
 **
 ** A wait operation should just expect the counter to fall to @c 0
 ** and do not much else.
 **
 ** @code
 ** inline
 ** void my_counter_wait(p99_futex volatile* f) {
 **   P99_FUTEX_COMPARE_EXCHANGE(f, val, 0u, 0u, 0u);
 **                              // name of the local variable
 **                              val,
 **                              // wait until the value is 0
 **                              !val,
 **                              // don't do anything else, no update
 **                              0u,
 **                              // and no wake up
 **                              0u, 0u);
 ** }
 ** @endcode
 **/
P00_DOCUMENT_IDENTIFIER_ARGUMENT(P99_FUTEX_COMPARE_EXCHANGE, 1)
#define P99_FUTEX_COMPARE_EXCHANGE(FUTEX, ACT, EXPECTED, DESIRED, WAKEMIN, WAKEMAX)
#endif

/**
 ** @}
 **/

#if (defined(__linux__) && !defined(NO_FUTEX)) || defined(DOXYGEN)
#include "p99_futex_linux.h"
#else
#include "p99_futex_c11.h"
#endif


#endif
