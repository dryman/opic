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
#ifndef P99_ATOMIC_GCC_ATOMIC_H
#define P99_ATOMIC_GCC_ATOMIC_H 1

#ifndef P99_ATOMIC_H
# warning "never include this file directly, use p99_atomic.h, instead"
#endif

#include "p99_args.h"

/**
 ** @file
 **
 ** @brief Implement some of the atomic operations as fallback to gcc'
 ** @c __atomic builtins.
 **
 ** All call to the __atomic builtins should have the corresponding
 ** ::memory_order arguments as compile time constants.
 **/


#define p00_atomic_clear(OBJ, ORD)                             \
p99_extension ({                                               \
  p00_atomic_flag volatile* p00_obj = (OBJ);                   \
  __atomic_clear(p00_obj, (ORD));                              \
 })

#define p00_atomic_test_and_set(OBJ, ORD)                      \
p99_extension ({                                               \
  p00_atomic_flag volatile* p00_obj = (OBJ);                   \
  __atomic_test_and_set(p00_obj, (ORD));                       \
 })

#define p00_mfence(...)                                        \
 P99_IF_EMPTY(__VA_ARGS__)                                     \
 (__atomic_thread_fence(__ATOMIC_SEQ_CST))                     \
 (__atomic_thread_fence(__VA_ARGS__))

#define p00_sync_lock_release(...)                             \
  P99_IF_LT(P99_NARG(__VA_ARGS__), 2)                          \
  (p00_atomic_clear(__VA_ARGS__, __ATOMIC_SEQ_CST))            \
  (p00_atomic_clear(__VA_ARGS__))

#define p00_sync_lock_test_and_set(...)                        \
  P99_IF_LT(P99_NARG(__VA_ARGS__), 2)                          \
  (p00_atomic_test_and_set(__VA_ARGS__, __ATOMIC_SEQ_CST))     \
  (p00_atomic_test_and_set(__VA_ARGS__))

#define p00_atomic_compare_exchange_n_(PTR, EXP, DES, WEAK, SUC, FAI, ...)               \
p99_extension ({                                                                         \
    P99_MACRO_PVAR(p00_ptr, (PTR), volatile);                                            \
    P99_MACRO_PVAR(p00_exp, (EXP), volatile);                                            \
    P99_MACRO_VAR(p00_desp, (DES));                                                      \
    __typeof__(*(PTR)) p00_des = p00_desp;                                               \
    __atomic_compare_exchange_n(p00_ptr, (void*)p00_exp, p00_des, (WEAK), (SUC), (FAI)); \
  })

#define p00_atomic_compare_exchange_n(...)                                                     \
  P99_IF_EQ(P99_NARG(__VA_ARGS__), 3)                                                          \
  (p00_atomic_compare_exchange_n_(__VA_ARGS__, 0, memory_order_seq_cst, memory_order_seq_cst)) \
  (p00_atomic_compare_exchange_n_(__VA_ARGS__, memory_order_seq_cst, memory_order_seq_cst, ))

#define p00_atomic_exchange_n_(PTR, DES, ORD, ...)                       \
p99_extension ({                                                         \
    P99_MACRO_PVAR(p00_ptr, (PTR), volatile);                            \
    P99_MACRO_VAR(p00_des, (DES));                                       \
    P99_MACRO_VAR(p00_ord, (ORD), const);                                \
    __typeof__(*p00_ptr) p00_ret;                                        \
    switch (p00_ord) {                                                   \
    case __ATOMIC_RELAXED:;                                              \
      p00_ret = __atomic_exchange_n(p00_ptr, p00_des, __ATOMIC_RELAXED); \
      break;                                                             \
    case __ATOMIC_ACQUIRE:;                                              \
      p00_ret = __atomic_exchange_n(p00_ptr, p00_des, __ATOMIC_ACQUIRE); \
      break;                                                             \
    case __ATOMIC_RELEASE:;                                              \
      p00_ret = __atomic_exchange_n(p00_ptr, p00_des, __ATOMIC_RELEASE); \
      break;                                                             \
    case __ATOMIC_ACQ_REL:;                                              \
      p00_ret = __atomic_exchange_n(p00_ptr, p00_des, __ATOMIC_ACQ_REL); \
      break;                                                             \
    default:                                                             \
      p00_ret = __atomic_exchange_n(p00_ptr, p00_des, __ATOMIC_SEQ_CST); \
    }                                                                    \
    p00_ret = p00_ret;                                                   \
  })

#define p00_atomic_exchange_n(...) p00_atomic_exchange_n_(__VA_ARGS__, __ATOMIC_SEQ_CST,)

#define p00_atomic_load_n_(PTR, ORD, ...)                      \
p99_extension ({                                               \
    P99_MACRO_PVAR(p00_ptr, (PTR), volatile);                  \
    P99_MACRO_VAR(p00_ord, (ORD), const);                      \
    __typeof__(*p00_ptr) p00_ret;                              \
    switch (p00_ord) {                                         \
    case __ATOMIC_RELAXED:;                                    \
      p00_ret = __atomic_load_n(p00_ptr, __ATOMIC_RELAXED);    \
      break;                                                   \
    case __ATOMIC_ACQUIRE:;                                    \
      p00_ret = __atomic_load_n(p00_ptr, __ATOMIC_ACQUIRE);    \
      break;                                                   \
    case __ATOMIC_CONSUME:;                                    \
      p00_ret = __atomic_load_n(p00_ptr, __ATOMIC_CONSUME);    \
      break;                                                   \
    default:                                                   \
      p00_ret =__atomic_load_n(p00_ptr, __ATOMIC_SEQ_CST);     \
    }                                                          \
    p00_ret = p00_ret;                                         \
  })

#define p00_atomic_load_n(...) p00_atomic_load_n_(__VA_ARGS__, __ATOMIC_SEQ_CST,)

#define p00_atomic_store_n_(PTR, DES, ORD, ...)                \
p99_extension ({                                               \
    P99_MACRO_PVAR(p00_ptr, (PTR), volatile);                  \
    P99_MACRO_VAR(p00_des, (DES));                             \
    P99_MACRO_VAR(p00_ord, (ORD), const);                      \
    switch (p00_ord) {                                         \
    case __ATOMIC_RELAXED:;                                    \
      __atomic_store_n(p00_ptr, p00_des, __ATOMIC_RELAXED);    \
      break;                                                   \
    case __ATOMIC_RELEASE:;                                    \
      __atomic_store_n(p00_ptr, p00_des, __ATOMIC_RELEASE);    \
      break;                                                   \
    default:                                                   \
      __atomic_store_n(p00_ptr, p00_des, __ATOMIC_SEQ_CST);    \
    }                                                          \
  })

#define p00_atomic_store_n(...) p00_atomic_store_n_(__VA_ARGS__, __ATOMIC_SEQ_CST,)

#define p00_atomic_fetch_add_(PTR, VAL, ORD, ...) __atomic_fetch_add((PTR), (VAL), (ORD))
#define p00_atomic_fetch_add(...) p00_atomic_fetch_add_(__VA_ARGS__, __ATOMIC_SEQ_CST,)
#define p00_atomic_fetch_and_(PTR, VAL, ORD, ...) __atomic_fetch_and((PTR), (VAL), (ORD))
#define p00_atomic_fetch_and(...) p00_atomic_fetch_and_(__VA_ARGS__, __ATOMIC_SEQ_CST,)
#define p00_atomic_fetch_or_(PTR, VAL, ORD, ...) __atomic_fetch_or((PTR), (VAL), (ORD))
#define p00_atomic_fetch_or(...) p00_atomic_fetch_or_(__VA_ARGS__, __ATOMIC_SEQ_CST,)
#define p00_atomic_fetch_sub_(PTR, VAL, ORD, ...) __atomic_fetch_sub((PTR), (VAL), (ORD))
#define p00_atomic_fetch_sub(...) p00_atomic_fetch_sub_(__VA_ARGS__, __ATOMIC_SEQ_CST,)
#define p00_atomic_fetch_xor_(PTR, VAL, ORD, ...) __atomic_fetch_xor((PTR), (VAL), (ORD))
#define p00_atomic_fetch_xor(...) p00_atomic_fetch_xor_(__VA_ARGS__, __ATOMIC_SEQ_CST,)

#endif
