/* This may look like nonsense, but it really is -*- mode: C -*-              */
/*                                                                            */
/* Except for parts copied from previous work and as explicitly stated below, */
/* the author and copyright holder for this work is                           */
/* (C) copyright  2012, 2014 Jens Gustedt, INRIA, France                      */
/*                                                                            */
/* This file is free software; it is part of the P99 project.                 */
/* You can redistribute it and/or modify it under the terms of the QPL as     */
/* given in the file LICENSE. It is distributed without any warranty;         */
/* without even the implied warranty of merchantability or fitness for a      */
/* particular purpose.                                                        */
/*                                                                            */
#ifndef P99_FUTEX_C11_H
#define P99_FUTEX_C11_H

/**
 ** @brief The structure that is used in the fallback implementation
 ** of ::p99_futex on non-linux systems
 **/
struct p99_futex_c11 {
  /** @brief An @c unsigned that makes up the counter itself.
   **/
  unsigned p99_cnt;
  /** @brief Holds the number of waiters on the condition.
   **/
  unsigned p99_waiting;
  /** @brief Holds the number of waiters on the condition that are to be woken up.
   **/
  unsigned p99_awaking;
  /** @brief A mutex that locks the access to the data structure */
  mtx_t p99_mut;
  /** @brief A conditional variable to wait and signal changes to the value.
   **/
  cnd_t p99_cnd;
};

#ifndef P00_DOXYGEN

#ifndef P99_FUTEX_INITIALIZER
# define P99_FUTEX_INITIALIZER(INITIAL) { .p99_cnt = (INITIAL), }
#endif

p99_inline
p99_futex* p99_futex_init(p99_futex* p00_fut, unsigned p00_ini) {
  if (p00_fut) {
    *p00_fut = (p99_futex)P99_FUTEX_INITIALIZER(p00_ini);
    mtx_init(&p00_fut->p99_mut, mtx_plain);
    cnd_init(&p00_fut->p99_cnd);
  }
  return p00_fut;
}

p99_inline
void p99_futex_destroy(p99_futex* p00_fut) {
  if (p00_fut) {
    p00_fut->p99_cnt = UINT_MAX;
    mtx_destroy(&p00_fut->p99_mut);
    cnd_destroy(&p00_fut->p99_cnd);
  }
}

P99_WEAK(p99_futex_load)
unsigned p99_futex_load(p99_futex volatile* p00_fut) {
  unsigned p00_ret = 0;
  P99_MUTUAL_EXCLUDE(*(mtx_t*)&p00_fut->p99_mut) {
    p00_ret = p00_fut->p99_cnt;
  }
  return p00_ret;
}

/* Supposes that the lock on the mutex is already taken and that
 * p00_wmin <= p00_wmax. Returns min(p00_win, p00_wok) where p00_wok
 * is the number of threads that have been woken up. */
p99_inline
unsigned p00_futex_wakeup(p99_futex volatile* p00_fut,
                          unsigned p00_wmin, unsigned p00_wmax) {
  assert(p00_wmin <= p00_wmax);
  if (p00_wmax && p00_fut->p99_waiting) {
    if (p00_wmax > p00_fut->p99_waiting) p00_wmax = p00_fut->p99_waiting;
    if (p00_wmax > 1u) cnd_broadcast((cnd_t*)&p00_fut->p99_cnd);
    else cnd_signal((cnd_t*)&p00_fut->p99_cnd);
    p00_fut->p99_waiting -= p00_wmax;
    p00_fut->p99_awaking += p00_wmax;
    return p00_wmin;
  } else {
    return 0;
  }
}

#define P00_FUTEX_WAKEUP(FUT, WMIN, WMAX)                      \
  do {                                                         \
  unsigned p00Wok = p00_futex_wakeup((FUT), WMIN, WMAX);       \
  WMIN -= p00Wok;                                              \
  WMAX -= p00Wok;                                              \
 } while(false)

P99_WEAK(p99_futex_wakeup)
void p99_futex_wakeup(p99_futex volatile* p00_fut,
                      unsigned p00_wmin, unsigned p00_wmax) {
  if (p00_wmax < p00_wmin) p00_wmax = p00_wmin;
  if (p00_wmax) do {
      unsigned p00_wok = 0;
      P99_MUTUAL_EXCLUDE(*(mtx_t*)&p00_fut->p99_mut) {
        p00_wok = p00_futex_wakeup(p00_fut, p00_wmin, p00_wmax);
      }
      p00_wmax -= p00_wok;
      p00_wmin -= p00_wok;
    } while (p00_wmin);
}

p99_inline
void p00_futex_wait(p99_futex volatile* p00_fut) {
  ++p00_fut->p99_waiting;
  /* This loop captures spurious wakeups as they may happen for
     cnd_wait. */
  do {
    cnd_wait((cnd_t*)&p00_fut->p99_cnd, (mtx_t*)&p00_fut->p99_mut);
  } while (!p00_fut->p99_awaking);
  --p00_fut->p99_awaking;
}

P99_WEAK(p99_futex_wait)
void p99_futex_wait(p99_futex volatile* p00_fut) {
  P99_MUTUAL_EXCLUDE(*(mtx_t*)&p00_fut->p99_mut)
  p00_futex_wait(p00_fut);
}

P99_WEAK(p99_futex_add)
unsigned p99_futex_add(p99_futex volatile* p00_fut, unsigned p00_hmuch,
                       unsigned p00_cstart, unsigned p00_clen,
                       unsigned p00_wmin, unsigned p00_wmax) {
  unsigned p00_ret = 0;
  if (p00_wmax < p00_wmin) p00_wmax = p00_wmin;
  P99_MUTUAL_EXCLUDE(*(mtx_t*)&p00_fut->p99_mut) {
    p00_ret = p00_fut->p99_cnt;
    register unsigned const p00_des = p00_ret + p00_hmuch;
    p00_fut->p99_cnt = p00_des;
    if (p00_clen && P99_IN_RANGE(p00_des, p00_cstart, p00_clen)) {
      P00_FUTEX_WAKEUP(p00_fut, p00_wmin, p00_wmax);
    } else {
      p00_wmin = 0;
    }
  }
  /* If we haven't woken enough threads, we have to re-acquire the
     mutex and loop until enough threads will enter the futex wait. */
  if (p00_wmin) p99_futex_wakeup(p00_fut, p00_wmin, p00_wmax);
  return p00_ret;
}

P99_WEAK(p99_futex_exchange)
unsigned p99_futex_exchange(p99_futex volatile* p00_fut, unsigned p00_desired,
                            unsigned p00_cstart, unsigned p00_clen,
                            unsigned p00_wmin, unsigned p00_wmax) {
  volatile unsigned p00_act = 0;
  if (p00_wmax < p00_wmin) p00_wmax = p00_wmin;
  P99_MUTUAL_EXCLUDE(*(mtx_t*)&p00_fut->p99_mut) {
    p00_act = p00_fut->p99_cnt;
    p00_fut->p99_cnt = p00_desired;
    if (p00_clen && P99_IN_RANGE(p00_desired, p00_cstart, p00_clen)) {
      P00_FUTEX_WAKEUP(p00_fut, p00_wmin, p00_wmax);
    } else {
      p00_wmin = 0;
    }
  }
  /* If we haven't woken enough threads, we have to re-acquire the
     mutex and loop until enough threads will enter the futex wait. */
  if (p00_wmin) p99_futex_wakeup(p00_fut, p00_wmin, p00_wmax);
  return p00_act;
}

#ifndef P99_FUTEX_COMPARE_EXCHANGE
P00_DOCUMENT_IDENTIFIER_ARGUMENT(P99_FUTEX_COMPARE_EXCHANGE, 1)
# define P99_FUTEX_COMPARE_EXCHANGE(FUTEX, ACT, EXPECTED, DESIRED, WAKEMIN, WAKEMAX) \
do {                                                                                 \
  p99_futex volatile*const p00Mfut = (FUTEX);                                        \
  unsigned volatile p00Mwmin = 0;                                                    \
  unsigned volatile p00Mwmax = 0;                                                    \
  P99_MUTUAL_EXCLUDE(*(mtx_t*)&p00Mfut->p99_mut) {                                   \
    for (;;) {                                                                       \
      register unsigned const ACT = p00Mfut->p99_cnt;                                \
      P99_UNUSED(ACT);                            /* Don't warn if ACT is unused. */ \
      if (P99_LIKELY(EXPECTED)) {                                                    \
        p00Mfut->p99_cnt = (DESIRED);                                                \
        p00Mwmin = (WAKEMIN);                                                        \
        p00Mwmax = (WAKEMAX);                                                        \
        if (p00Mwmax < p00Mwmin) p00Mwmax = p00Mwmin;                                \
        P00_FUTEX_WAKEUP(p00Mfut, p00Mwmin, p00Mwmax);                               \
        break;                                                                       \
      }                                                                              \
      p00_futex_wait(p00Mfut);                                                       \
    }                                                                                \
  }                                                                                  \
  /* If we haven't woken enough threads, we have to re-acquire the                   \
     mutex and loop until enough threads will enter the futex wait. */               \
  if (p00Mwmin) p99_futex_wakeup(p00Mfut, p00Mwmin, p00Mwmax);                       \
 } while (false)
#endif

#endif /* P00_DOXYGEN */
#endif
