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
#ifndef P99_COUNT_H
#define P99_COUNT_H

#include "p99_futex.h"

/**
 ** @addtogroup futex
 ** @{
 **/

/**
 ** @brief A counter that allows atomic increment and decrement and a
 ** wait for the value 0.
 **
 ** This is implemented more or less efficiently according to the
 ** features that the platform provides:
 ** - one that uses atomic operations and futexes for signaling
 ** - one that mutexes all access and uses a condition variable for
 **   signaling.
 **/
#ifdef P00_DOXYGEN
struct p99_count {};
#else
typedef p99_futex p99_count;
#endif

/**
 ** @brief Initialize an ::p99_count object.
 **/
# define P99_COUNT_INITIALIZER P99_FUTEX_INITIALIZER

/**
 ** @brief Initialize an ::p99_count object.
 **/
P99_DEFARG_DOCU(p99_count_init)
p99_inline
p99_count* p99_count_init(p99_count* p00_c, unsigned p00_v) {
  return p99_futex_init(p00_c, p00_v);
}

#define p99_count_init(...) P99_CALL_DEFARG(p99_count_init, 2, __VA_ARGS__)
#define p99_count_init_defarg_1() 0U

p99_inline
void p99_count_destroy(p99_count* p00_c) {
  p99_futex_destroy(p00_c);
}

/**
 ** @brief Account the ::p99_count @a COUNT during execution
 ** of a dependent block or statement.
 **/
P99_BLOCK_DOCUMENT
#define P99_ACCOUNT(COUNT)                                              \
P00_BLK_DECL(p99_count*, p00Mcount, &(COUNT))                           \
P99_PROTECTED_BLOCK(p99_count_inc(p00Mcount), p99_count_dec(p00Mcount))

/**
 ** @brief increment the counter @a counter atomically by @a p00_hm.
 ** @return the value of the counter before the increment.
 ** @remark @a p00_hm defaults to 1 if omitted.
 ** @related p99_count
 **/
P99_DEFARG_DOCU(p99_count_inc)
p99_inline unsigned p99_count_inc(p99_count volatile* p00_c, unsigned p00_hm) {
  return p99_futex_add(p00_c, p00_hm, 0U, 0U, 0U, 0U);
}

#define p99_count_inc(...) P99_CALL_DEFARG(p99_count_inc, 2, __VA_ARGS__)
#define p99_count_inc_defarg_1() (1U)

/**
 ** @brief increment the counter @a p00_c atomically by @a p00_hm but only if it is not zero before.
 ** @return the value of the counter before the increment.
 ** @remark @a p00_hm defaults to 1 if omitted.
 ** @related p99_count
 **/
P99_DEFARG_DOCU(p99_count_inc_conditionally)
P00_FUTEX_INLINE(p99_count_inc_conditionally)
unsigned p99_count_inc_conditionally(p99_count volatile* p00_c, unsigned p00_hm) {
  unsigned p00_ret = 0;
  P99_FUTEX_COMPARE_EXCHANGE(p00_c, p00_act,
                             /* never wait */
                             true,
                             /* only do something if positive */
                             (!p00_act ? 0U : p00_act + p00_hm),
                             /* capture the state for return, but
                                never wakeup and waiters */
                             ((p00_ret = p00_act), 0), 0);
  return p00_ret;
}

#define p99_count_inc_conditionally(...) P99_CALL_DEFARG(p99_count_inc_conditionally, 2, __VA_ARGS__)
#define p99_count_inc_conditionally_defarg_1() (1U)

/**
 ** @brief Obtain the value of counter @a p00_c atomically.
 ** @related p99_count
 **/
p99_inline unsigned p99_count_value(p99_count volatile* p00_c) {
  return p99_futex_load(p00_c);
}


/**
 ** @brief decrement the counter @a p00_c atomically by @a p00_hm.
 **
 ** Also signals eventual waiters if the counter falls to 0.
 ** @return the value of the counter after the decrement.
 ** @remark @a p00_hm defaults to 1 if omitted.
 ** @related p99_count
 **/
P99_DEFARG_DOCU(p99_count_dec)
p99_inline
unsigned p99_count_dec(p99_count volatile* p00_c, unsigned p00_hm) {
  unsigned ret = p99_futex_add(p00_c, -(signed)p00_hm, 0U, 1U, 0U, P99_FUTEX_MAX_WAITERS);
  return ret - p00_hm;
}

#define p99_count_dec(...) P99_CALL_DEFARG(p99_count_dec, 2, __VA_ARGS__)
#define p99_count_dec_defarg_1() (1U)

/**
 ** @brief wait until the p00_c @a counter falls to @c 0.
 **
 ** @remark p00_v defaults to @c 0U.
 ** @related p99_count
 **/
P00_FUTEX_INLINE(p99_count_wait)
void p99_count_wait(p99_count volatile* p00_c) {
  P99_FUTEX_COMPARE_EXCHANGE(p00_c, p00_act, !p00_act, p00_act, 0U, 0U);
}

/**
 ** @}
 **/


#endif
