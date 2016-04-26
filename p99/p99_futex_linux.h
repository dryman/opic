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
#if !defined(P99_FUTEX_LINUX_H) && !defined(P00_DOXYGEN)
#define P99_FUTEX_LINUX_H

#include "p99_atomic.h"
#include "p99_threads.h"
#if !defined(ATOMIC_VAR_INIT) && defined(__GNUC__)
# include "p99_atomic.h"
#endif
#include "p99_posix_default.h"

/**
 ** @addtogroup library_support
 ** @{
 **/


#if (defined(__linux__) && !defined(NO_FUTEX)) || defined(DOXYGEN)
#define P00_FUTEX_LINUX 1

# if __GLIBC__
#  include <linux/futex.h>
# else
/* Other C libraries (e.g musl) do not provide values for futex
   operations. Only the first five operations are documented, so
   probably the occasional user of this will not expect more. */
#  define FUTEX_WAIT    0
#  define FUTEX_WAKE    1
#  define FUTEX_FD    2
#  define FUTEX_REQUEUE   3
#  define FUTEX_CMP_REQUEUE 4
# endif
# include <unistd.h>
# include <sys/syscall.h>

long syscall(long number, ...);

/**
 ** @brief Wrap the linux system call @c futex.
 **
 ** @c syscall is a va_arg function, so we would never be sure
 ** of the type conversions that could take place. Clearly specify the
 ** interface.
 **
 ** @warning This is probably nothing that should be called directly.
 ** @see P00_FUTEX_WAIT
 ** @see p00_futex_wake
 ** @see p00_futex_wait_once
 ** @see p00_futex_signal
 ** @see p00_futex_broadcast
 **/
P99_DEFARG_DOCU(p00_futex)
p99_inline
int p00_futex(int *uaddr, /*!< the base address to be used */
              int op,     /*!< the operation that is to be performed */
              int val,    /*!< the value that a wait operation
                             expects when going into wait, or the
                             number of tasks to wake up */
              const struct timespec
              *timeout, /*!< a time out for wait, unused by P99, defaults to
                            0. */
              int *uaddr2, /*!< unused by P99, defaults to 0 */
              int val3     /*!< unused by P99, defaults to 0 */
             ) {
  return syscall(SYS_futex, uaddr, op, val, timeout, uaddr2, val3);
}

#define p00_futex(...) P99_CALL_DEFARG(p00_futex, 6, __VA_ARGS__)
#define p00_futex_defarg_3() ((void*)0)
#define p00_futex_defarg_4() ((void*)0)
#define p00_futex_defarg_5() 0

/**
 ** @brief Wait until a wake up event is received on address @a uaddr.
 **
 ** This will return under three different circumstances:
 ** - the value @c (*uaddr) is initially not equal to @a val
 ** - a wake up event is triggered by some other task or process
 ** - an interrupt is received.
 **
 ** This later type of event is called a "spurious wakeup".
 **
 ** In any of these cases it is up to the application to check for the
 ** condition that it wanted to be satisfied while waiting.
 **
 ** @warning Generally this is not the function that you'd want to use
 ** directly in an application.
 ** @see P00_FUTEX_WAIT for a macro that is better suited for an
 ** application usage.
 ** @see p00_futex_wake
 ** @see p00_futex_signal
 ** @see p00_futex_broadcast
 **/
p99_inline
int p00_futex_wait_once(int* uaddr, int val) {
  int ret = p00_futex(uaddr, FUTEX_WAIT, val);
  if (P99_UNLIKELY(ret < 0)) {
    ret = errno;
    errno = 0;
  }
  return ret;
}

/**
 ** @brief Wait until the value to which @a ADDR points to fulfills
 ** expression @a EXPECTED.
 **
 ** @param ADDR is a valid address that is interpreted as pointing to
 ** an @c int object.
 **
 ** @param NAME must be an identifier. It serves to declare an
 ** internal variable
 ** that will hold @c (*ADDR) and which should be used in expression
 ** @a EXPECTED.
 **
 ** @param EXPECTED is a expression that evaluates @a NAME and that
 ** should not have side effects.
 **
 ** If it is not fulfilled initially, this macro blocks execution of
 ** the calling thread until the thread is woken up @em and @a
 ** EXPECTED is fulfilled. That is if each occurence of @a NAME in @a
 ** EXPECTED is replaced by the current value of @c (*ADDR) and then
 ** the evaluation of the resulting expression returns a truth value.
 **
 ** It is the responsibility of the application to issue the
 ** corresponding calls to wake up potential waiters whenever the
 ** value of @c (*ADDR) is changed.
 **
 ** Take the following example of a counter implementation:
 ** @code
 ** enum { why = 42 };
 ** int count = 0;
 **
 ** // some thread waiting for the count to become more than why.
 ** P00_FUTEX_WAIT(&count, x, x > why);
 **
 ** // some thread augmenting the count. wake up potential
 ** // waiters.
 ** atomic_fetch_add(&count, 1);
 ** p00_futex_broadcast(&count);
 **
 ** // some thread reducing the count. no need to wake up potential
 ** // waiters.
 ** atomic_fetch_sub(&count, 1);
 ** @endcode
 **
 ** @warning It is probably not a good idea to have the evaluation of
 ** a variable (other than @a NAME) inside expression @a EXPRESSION
 ** that is subject to changes.
 ** @see p00_futex_wake
 ** @see p00_futex_signal
 ** @see p00_futex_broadcast
 **/
#define P00_FUTEX_WAIT(ADDR, NAME, EXPECTED)                   \
do {                                                           \
  register int volatile*const p = (int volatile*)(ADDR);       \
  for (;;) {                                                   \
    register int NAME = *p;                                    \
    if (P99_LIKELY(EXPECTED)) break;                           \
    register int ret = p00_futex_wait_once((int*)p, NAME);     \
    if (P99_UNLIKELY(ret)) {                                   \
      assert(!ret);                                            \
    }                                                          \
  }                                                            \
 } while (false)

/**
 ** @brief Wakeup waiters for address @a uaddr.
 **
 ** If there are @a wakeup waiters, as much waiters are woke up. If
 ** there are less, all waiters are woken up.
 ** @return the number of processes that had effectively been woken up
 ** @see P00_FUTEX_WAIT
 ** @see p00_futex_signal
 ** @see p00_futex_broadcast
 **/
p99_inline
int p00_futex_wake(int* uaddr, int wakeup) {
  int ret = p00_futex(uaddr, FUTEX_WAKE, wakeup);
  return ret;
}

/**
 ** @brief Wakeup one waiter for address @a uaddr, if there is any.
 ** @see P00_FUTEX_WAIT
 ** @see p00_futex_wake
 ** @see p00_futex_broadcast
 **/
p99_inline
int p00_futex_signal(int* uaddr) {
  return p00_futex_wake(uaddr, 1);
}

/**
 ** @brief Wakeup all waiters for address @a uaddr, if there are
 ** any.
 ** @see P00_FUTEX_WAIT
 ** @see p00_futex_wake
 ** @see p00_futex_signal
 **/
p99_inline
int p00_futex_broadcast(int* uaddr) {
  return p00_futex_wake(uaddr, INT_MAX);
}

# ifndef P99_FUTEX_INITIALIZER
#  define P99_FUTEX_INITIALIZER(INITIAL) ATOMIC_VAR_INIT(INITIAL)
# endif

p99_inline
p99_futex* p99_futex_init(p99_futex* p00_c, unsigned p00_ini) {
  if (p00_c) {
    atomic_init(p00_c, p00_ini);
  }
  return p00_c;
}

p99_inline
void p99_futex_destroy(p99_futex* p00_c) {
  if (p00_c) {
    atomic_store(p00_c, UINT_MAX);
  }
}

p99_inline
unsigned p99_futex_load(p99_futex volatile* p00_fut) {
  return atomic_load(p00_fut);
}

p99_inline
void p99_futex_wakeup(p99_futex volatile* p00_cntp,
                      unsigned p00_wmin, unsigned p00_wmax) {
  if (p00_wmax < p00_wmin) p00_wmax = p00_wmin;
  if (p00_wmax) {
    unsigned volatile*const p00_cnt = (unsigned*)p00_cntp;
    static_assert(sizeof *p00_cntp == sizeof *p00_cnt,
                  "linux futex supposes that there is no hidden lock field");
    for (;;) {
      register signed p00_wok = p00_futex_wake((int*)p00_cnt, p00_wmax);
      assert(p00_wok >= 0);
      if (p00_wok >= p00_wmin) break;
      p00_wmax -= p00_wok;
      p00_wmin -= p00_wok;
    }
  }
}

p99_inline
void p99_futex_wait(p99_futex volatile* p00_cntp) {
  unsigned volatile*const p00_cnt = (unsigned*)p00_cntp;
  static_assert(sizeof *p00_cntp == sizeof *p00_cnt,
                "linux futex supposes that there is no hidden lock field");
  for (;;) {
    unsigned p00_act = *p00_cnt;
    register int p00_ret = p00_futex_wait_once((int*)p00_cnt, p00_act);
    switch (p00_ret) {
    default: assert(!p00_ret);
    case 0: return;
    // Allow for different val or spurious wake ups
    case EWOULDBLOCK: ;
    case EINTR: ;
    }
  }
}


p99_inline
unsigned p99_futex_add(p99_futex volatile* futex, unsigned p00_hmuch,
                       unsigned p00_cstart, unsigned p00_clen,
                       unsigned p00_wmin, unsigned p00_wmax) {
  unsigned p00_act = atomic_fetch_add(futex, p00_hmuch);
  register unsigned const ret = p00_act + p00_hmuch;
  if (p00_clen && P99_IN_RANGE(ret, p00_cstart, p00_clen))
    p99_futex_wakeup(futex, p00_wmin, p00_wmax);
  return p00_act;
}

p99_inline
unsigned p99_futex_exchange(p99_futex volatile* futex, unsigned p00_desired,
                            unsigned p00_cstart, unsigned p00_clen,
                            unsigned p00_wmin, unsigned p00_wmax) {
  unsigned p00_act = atomic_exchange(futex, p00_desired);
  if (p00_clen && P99_IN_RANGE(p00_desired, p00_cstart, p00_clen))
    p99_futex_wakeup(futex, p00_wmin, p00_wmax);
  return p00_act;
}

#ifndef P99_FUTEX_COMPARE_EXCHANGE
P00_DOCUMENT_IDENTIFIER_ARGUMENT(P99_FUTEX_COMPARE_EXCHANGE, 1)
# define P99_FUTEX_COMPARE_EXCHANGE(FUTEX, ACT, EXPECTED, DESIRED, WAKEMIN, WAKEMAX) \
do {                                                                                 \
  _Atomic(unsigned) volatile*const p00Mcntp = (FUTEX);                               \
  unsigned volatile*const p00Mcnt = (unsigned*)p00Mcntp;                             \
  static_assert(sizeof *p00Mcntp == sizeof *p00Mcnt,                                 \
                "linux futex stuff supposes that there is no hidden lock field");    \
  unsigned p00Mact = *p00Mcnt;                                                       \
  for (;;) {                                                                         \
    register unsigned const ACT = p00Mact;                                           \
    if (P99_LIKELY(EXPECTED)) {                                                      \
      register unsigned const p00Mdes = (DESIRED);                                   \
      /* This will only fail if there is contention on the futex, so we then try */  \
      /* again, immediately. */                                                      \
      if (ACT == p00Mdes) break;                                                     \
      if (atomic_compare_exchange_weak(p00Mcntp, &p00Mact, p00Mdes)) {               \
        register unsigned p00Mwmin = (WAKEMIN);                                      \
        register unsigned p00Mwmax = (WAKEMAX);                                      \
        p99_futex_wakeup(p00Mcntp, p00Mwmin, p00Mwmax);                              \
        break;                                                                       \
      }                                                                              \
    } else {                                                                         \
      register int p00Mret = p00_futex_wait_once((int*)p00Mcnt, ACT);                \
      switch (p00Mret) {                                                             \
      default: assert(!p00Mret);                                                     \
      case 0: ;                                                                      \
        /* Allow for different val or spurious wake ups */                           \
      case EWOULDBLOCK: ;                                                            \
      case EINTR: ;                                                                  \
      }                                                                              \
      p00Mact = *p00Mcnt;                                                            \
    }                                                                                \
  }                                                                                  \
 } while (false)
#endif

#endif

/**
 ** @}
 **/

#endif
