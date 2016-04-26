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
#ifndef P99_ATOMIC_GCC_SYNC_H
#define P99_ATOMIC_GCC_SYNC_H 1

#ifndef P99_ATOMIC_H
# warning "never include this file directly, use p99_atomic.h, instead"
#endif

#include "p99_args.h"

/**
 ** @file
 **
 ** @brief Implement some of the atomic operations as fallback to gcc'
 ** @c __sync builtins.
 **/

#define p00_atomic_exchange_n_(PTR, DES, ORD, ...)                                                  \
p99_extension ({                                                                                    \
    P99_MACRO_PVAR(p00_ptr, (PTR), volatile);                                                       \
    P99_MACRO_VAR(p00_des, (DES));                                                                  \
    register __typeof__(*(PTR)) p00_ret = p00_des;                                                  \
    for (;;) {                                                                                      \
      register __typeof__(*(PTR)) p00_val = __sync_val_compare_and_swap(p00_ptr, p00_ret, p00_des); \
      if (P99_LIKELY(p00_val == p00_ret)) break;                                                    \
      p00_ret = p00_val;                                                                            \
    }                                                                                               \
    p00_ret = p00_ret;                                                                              \
  })

#define p00_atomic_exchange_n(...) p00_atomic_exchange_n_(__VA_ARGS__,,)

#define p00_mfence(...) __sync_synchronize()

#define p00_sync_lock_release_(OBJ, ORD, ...)                        \
p99_extension ({                                                     \
  P99_MACRO_PVAR(p00_obj, (OBJ), volatile);                          \
  /* __sync_lock_release only has release consistency */             \
  /* the fence must come before so nothing can be reordered after */ \
  switch (ORD) {                                                     \
  case memory_order_consume: ;                                       \
  case memory_order_acquire: ;                                       \
  case memory_order_acq_rel: ;                                       \
  case memory_order_seq_cst: ;                                       \
    p00_mfence();                                                    \
  }                                                                  \
  __sync_lock_release(p00_obj);                                      \
 })

#define p00_sync_lock_test_and_set_(OBJ, ORD, ...)                   \
p99_extension ({                                                     \
  P99_MACRO_PVAR(p00_obj, (OBJ), volatile);                          \
  /* __sync_lock_test_and_set only has acquire consistency */        \
  int ret = __sync_lock_test_and_set(p00_obj, 1);                    \
  /* the fence must come after so nothing can be reordered before */ \
  switch (ORD) {                                                     \
  case memory_order_consume: ;                                       \
  case memory_order_release: ;                                       \
  case memory_order_acq_rel: ;                                       \
  case memory_order_seq_cst: ;                                       \
    p00_mfence();                                                    \
  }                                                                  \
  ret = ret;                                                         \
 })

#define p00_sync_lock_release(...) p00_sync_lock_release_(__VA_ARGS__, memory_order_seq_cst, )
#define p00_sync_lock_test_and_set(...) p00_sync_lock_test_and_set_(__VA_ARGS__, memory_order_seq_cst, )

#define p00_atomic_compare_exchange_n_(PTR, EXP, DES, WEAK, SUC, FAI, ...)              \
p99_extension ({                                                                        \
    P99_MACRO_PVAR(p00_ptr, (PTR), volatile);                                           \
    P99_MACRO_VAR(p00_exp, (EXP));                                                      \
    P99_MACRO_VAR(p00_des, (DES), const);                                               \
    __typeof__(*PTR) p00_val = __sync_val_compare_and_swap(p00_ptr, *p00_exp, p00_des); \
    _Bool p00_ret = (*p00_exp == p00_val);                                              \
    if (!p00_ret) *p00_exp = p00_val;                                                   \
    p00_ret = p00_ret;                                                                  \
  })

#define p00_atomic_compare_exchange_n(...)                                                     \
  P99_IF_EQ(P99_NARG(__VA_ARGS__), 3)                                                          \
  (p00_atomic_compare_exchange_n_(__VA_ARGS__, 0, memory_order_seq_cst, memory_order_seq_cst)) \
  (p00_atomic_compare_exchange_n_(__VA_ARGS__, memory_order_seq_cst, memory_order_seq_cst, ))

#define p00_atomic_load_n_(PTR, ORD, ...)                      \
p99_extension ({                                               \
    P99_MACRO_PVAR(p00_ptr, (PTR), volatile);                  \
    /* Ensure synchronization with all stores before */        \
    switch (ORD) {                                             \
    case memory_order_consume:;                                \
    case memory_order_acquire:;                                \
    case memory_order_acq_rel:;                                \
      (void)__sync_bool_compare_and_swap(p00_ptr, 0, 0);       \
      break;                                                   \
    case memory_order_seq_cst:;                                \
      p00_mfence();                                            \
    }                                                          \
    /* now ensure the load of the correct value */             \
    register __typeof__(*(PTR)) const p00_ret = *p00_ptr;      \
    /* Inhibit reordering with all code after */               \
    P99_MARK("load boundary for " P99_STRINGIFY(PTR));         \
    p00_ret;                                                   \
  })

#define p00_atomic_load_n(...) p00_atomic_load_n_(__VA_ARGS__,,)

#define p00_atomic_store_n_(PTR, DES, ORD, ...)                      \
p99_extension ({                                                     \
    P99_MACRO_PVAR(p00_ptr, (PTR), volatile);                        \
    P99_MACRO_VAR(p00_des, (DES), const);                            \
    /* Inhibit reordering with all code before */                    \
    P99_MARK("store boundary for " P99_STRINGIFY(PTR));              \
    /* now ensure the store of the correct value */                  \
    *p00_ptr = p00_des;                                              \
    /* Ensure that store is visible for all code hereafter */        \
    switch (ORD) {                                                   \
    case memory_order_consume:;                                      \
    case memory_order_release:;                                      \
    case memory_order_acq_rel:;                                      \
      (void)__sync_bool_compare_and_swap(p00_ptr, p00_des, p00_des); \
      break;                                                         \
    case memory_order_seq_cst:;                                      \
      p00_mfence();                                                  \
    }                                                                \
  })

#define p00_atomic_store_n(...) p00_atomic_store_n_(__VA_ARGS__, memory_order_seq_cst,)


#define p00_atomic_fetch_add_(PTR, VAL, ORD, ...) __sync_fetch_and_add((PTR), (VAL))
#define p00_atomic_fetch_add(...) p00_atomic_fetch_add_(__VA_ARGS__, ,)
#define p00_atomic_fetch_and_(PTR, VAL, ORD, ...) __sync_fetch_and_and((PTR), (VAL))
#define p00_atomic_fetch_and(...) p00_atomic_fetch_and_(__VA_ARGS__, ,)
#define p00_atomic_fetch_or_(PTR, VAL, ORD, ...) __sync_fetch_and_or((PTR), (VAL))
#define p00_atomic_fetch_or(...) p00_atomic_fetch_or_(__VA_ARGS__, ,)
#define p00_atomic_fetch_sub_(PTR, VAL, ORD, ...) __sync_fetch_and_sub((PTR), (VAL))
#define p00_atomic_fetch_sub(...) p00_atomic_fetch_sub_(__VA_ARGS__, ,)
#define p00_atomic_fetch_xor_(PTR, VAL, ORD, ...) __sync_fetch_and_xor((PTR), (VAL))
#define p00_atomic_fetch_xor(...) p00_atomic_fetch_xor_(__VA_ARGS__, ,)


#endif
