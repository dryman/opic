/* This may look like nonsense, but it really is -*- mode: C -*-              */
/*                                                                            */
/* Except for parts copied from previous work and as explicitly stated below, */
/* the authors and copyright holders for this work are as follows:            */
/* (C) copyright  2012, 2014 Jens Gustedt, INRIA, France                      */
/* (C) copyright  2012 William Morris                                         */
/*                                                                            */
/* This file is free software; it is part of the P99 project.                 */
/* You can redistribute it and/or modify it under the terms of the QPL as     */
/* given in the file LICENSE. It is distributed without any warranty;         */
/* without even the implied warranty of merchantability or fitness for a      */
/* particular purpose.                                                        */
/*                                                                            */
#ifndef P99_ATOMIC_ARM_H
#define P99_ATOMIC_ARM_H 1

#ifndef P99_ATOMIC_H
# warning "never include this file directly, use p99_atomic.h, instead"
#endif

#if !defined(__thumb__) && !defined(__thumb2__)
/* When in arm mode we can't do addressing with offset, here, so use
   direct addressing. */
p99_inline
uint8_t p00_arm_ldrexb(uint8_t volatile*p00_ptr) {
  uint8_t p00_ret;
  __asm__ volatile ("ldrexb %0,[%1]\t@ load exclusive\n"
                    : "=&r" (p00_ret)
                    : "r" (p00_ptr)
                    : "cc", "memory"
                   );
  return p00_ret;
}

p99_inline
_Bool p00_arm_strexb(uint8_t volatile*p00_ptr, uint8_t p00_val) {
  uint32_t p00_ret;
  __asm__ volatile ("strexb %0,%1,[%2]\t@ store exclusive\n"
                    : "=&r" (p00_ret)
                    : "r" (p00_val), "r" (p00_ptr)
                    : "cc", "memory"
                   );
  return p00_ret;
}
p99_inline
uint16_t p00_arm_ldrexh(uint16_t volatile*p00_ptr) {
  uint16_t p00_ret;
  __asm__ volatile ("ldrexh %0,[%1]\t@ load exclusive\n"
                    : "=&r" (p00_ret)
                    : "r" (p00_ptr)
                    : "cc", "memory"
                   );
  return p00_ret;
}

p99_inline
_Bool p00_arm_strexh(uint16_t volatile*p00_ptr, uint16_t p00_val) {
  uint32_t p00_ret;
  __asm__ volatile ("strexh %0,%1,[%2]\t@ store exclusive\n"
                    : "=&r" (p00_ret)
                    : "r" (p00_val), "r" (p00_ptr)
                    : "cc", "memory"
                   );
  return p00_ret;
}
p99_inline
uint32_t p00_arm_ldrex(uint32_t volatile*p00_ptr) {
  uint32_t p00_ret;
  __asm__ volatile ("ldrex %0,[%1]\t@ load exclusive\n"
                    : "=&r" (p00_ret)
                    : "r" (p00_ptr)
                    : "cc", "memory"
                   );
  return p00_ret;
}

p99_inline
_Bool p00_arm_strex(uint32_t volatile*p00_ptr, uint32_t p00_val) {
  uint32_t p00_ret;
  __asm__ volatile ("strex %0,%1,[%2]\t@ store exclusive\n"
                    : "=&r" (p00_ret)
                    : "r" (p00_val), "r" (p00_ptr)
                    : "cc", "memory"
                   );
  return p00_ret;
}
# if defined(__GCC_HAVE_SYNC_COMPARE_AND_SWAP_8)
p99_inline
uint64_t p00_arm_ldrexd(uint64_t volatile*p00_ptr) {
  uint64_t p00_ret;
  __asm__ volatile ("ldrexd %0, %H0, [%1]\t@ load exclusive\n"
                    : "=&r" (p00_ret)
                    : "r" (p00_ptr)
                    : "cc", "memory"
                   );
  return p00_ret;
}

p99_inline
_Bool p00_arm_strex(uint64_t volatile*p00_ptr, uint64_t p00_val) {
  uint32_t p00_ret;
  __asm__ volatile ("strex %0, %1, %H1, [%2]\t@ store exclusive\n"
                    : "=&r" (p00_ret)
                    : "r" (p00_val), "r" (p00_ptr)
                    : "cc", "memory"
                   );
  return p00_ret;
}
# endif
#else
/* When in thumb mode we can do addressing with offset, here, so use
   the "m" constraint to the assembler. */
p99_inline
uint8_t p00_arm_ldrexb(uint8_t volatile*p00_ptr) {
  uint8_t p00_ret;
  __asm__ volatile ("ldrexb %0,%1\t@ load exclusive\n"
                    : "=&r" (p00_ret)
                    : "m" (p00_ptr)
                    : "cc", "memory"
                   );
  return p00_ret;
}

p99_inline
_Bool p00_arm_strexb(uint8_t volatile*p00_ptr, uint8_t p00_val) {
  uint32_t p00_ret;
  __asm__ volatile ("strexb %0,%1,%2\t@ store exclusive\n"
                    : "=&r" (p00_ret)
                    : "r" (p00_val), "m" (p00_ptr)
                    : "cc", "memory"
                   );
  return p00_ret;
}
p99_inline
uint16_t p00_arm_ldrexh(uint16_t volatile*p00_ptr) {
  uint16_t p00_ret;
  __asm__ volatile ("ldrexh %0,%1\t@ load exclusive\n"
                    : "=&r" (p00_ret)
                    : "m" (p00_ptr)
                    : "cc", "memory"
                   );
  return p00_ret;
}

p99_inline
_Bool p00_arm_strexh(uint16_t volatile*p00_ptr, uint16_t p00_val) {
  uint32_t p00_ret;
  __asm__ volatile ("strexh %0,%1,%2\t@ store exclusive\n"
                    : "=&r" (p00_ret)
                    : "r" (p00_val), "m" (p00_ptr)
                    : "cc", "memory"
                   );
  return p00_ret;
}
p99_inline
uint32_t p00_arm_ldrex(uint32_t volatile*p00_ptr) {
  uint32_t p00_ret;
  __asm__ volatile ("ldrex %0,%1\t@ load exclusive\n"
                    : "=&r" (p00_ret)
                    : "m" (p00_ptr)
                    : "cc", "memory"
                   );
  return p00_ret;
}

p99_inline
_Bool p00_arm_strex(uint32_t volatile*p00_ptr, uint32_t p00_val) {
  uint32_t p00_ret;
  __asm__ volatile ("strex %0,%1,%2\t@ store exclusive\n"
                    : "=&r" (p00_ret)
                    : "r" (p00_val), "m" (p00_ptr)
                    : "cc", "memory"
                   );
  return p00_ret;
}
# if defined(__GCC_HAVE_SYNC_COMPARE_AND_SWAP_8)
p99_inline
uint64_t p00_arm_ldrexd(uint64_t volatile*p00_ptr) {
  uint64_t p00_ret;
  __asm__ volatile ("ldrexd %0, %H0, %1\t@ load exclusive\n"
                    : "=&r" (p00_ret)
                    : "m" (p00_ptr)
                    : "cc", "memory"
                   );
  return p00_ret;
}

p99_inline
_Bool p00_arm_strexd(uint64_t volatile*p00_ptr, uint64_t p00_val) {
  uint32_t p00_ret;
  __asm__ volatile ("strexd %0, %1, %H1, %2\t@ store exclusive\n"
                    : "=&r" (p00_ret)
                    : "r" (p00_val), "m" (p00_ptr)
                    : "cc", "memory"
                   );
  return p00_ret;
}
# endif
#endif

p99_inline
uint8_t p00_atomic_exchange_1(uint8_t volatile* p00_objp, uint8_t p00_des) {
  for (;;) {
    uint8_t p00_ret = p00_arm_ldrexb(object);
    if (!p00_arm_strexb(object, p00_des)) return p00_ret;
  }
}

p99_inline
uint16_t p00_atomic_exchange_2(uint16_t volatile* p00_objp, uint16_t p00_des) {
  for (;;) {
    uint16_t p00_ret = p00_arm_ldrexh(object);
    if (!p00_arm_strexh(object, p00_des)) return p00_ret;
  }
}

p99_inline
uint32_t p00_atomic_exchange_4(uint32_t volatile* p00_objp, uint32_t p00_des) {
  for (;;) {
    uint32_t p00_ret = p00_arm_ldrex(object);
    if (!p00_arm_strex(object, p00_des)) return p00_ret;
  }
}

#if defined(__GCC_HAVE_SYNC_COMPARE_AND_SWAP_8) || defined(P00_DOXYGEN)
p99_inline
uint64_t p00_atomic_exchange_8(uint64_t volatile* p00_objp, uint64_t p00_des) {
  for (;;) {
    uint64_t p00_ret = p00_arm_ldrexd(object);
    if (!p00_arm_strexd(object, p00_des)) return p00_ret;
  }
}
#endif

#if defined(__GCC_HAVE_SYNC_COMPARE_AND_SWAP_4) && !defined(P00_DOXYGEN)

p99_inline
uint32_t p00_sync_lock_test_and_set(uint32_t volatile *p00_objp) {
  return __sync_lock_test_and_set(p00_objp, 1);
}

p99_inline
void p00_sync_lock_release(uint32_t volatile *p00_objp) {
  __sync_lock_release(p00_objp);
}

p99_inline
void p00_mfence(void) {
  __sync_synchronize();
}


#else
/**
 ** @addtogroup atomic_arm Atomic operations on ARM
 **
 ** This implementation uses the @c ldrex/strex instruction pair that has been
 ** implemented since arm v6.
 **
 ** @c ldrex/strex is a load-link and store instruction pair. This means
 ** a strex will only succeed if nobody else has touched "object"
 ** since the load.
 **
 ** This operation is not lock-free by itself, so it doesn't guarantee
 ** the requirements of the standard for operations on ::atomic_flag
 ** when used on its own. The OS must support this operation by
 ** canceling all pending @c ldrex operations when (de)scheduling a
 ** thread or entering or leaving a signal handler.
 **
 ** @remark This is only used if the gcc extensions for atomic lock
 ** free operations is not implemented directly by the compiler.
 **
 ** @remark Uses the @c __asm__ extension of gcc for inline assembler.
 **
 ** @ingroup atomic_stub
 **
 ** @{
 **/


p99_inline
uint32_t p00_sync_lock_test_and_set_internal(uint32_t volatile *object, memory_order p00_ord) {
  for (;;) {
    uint32_t p00_ret = p00_arm_ldrex(object);
    /* Even if the result has been a 1 in p00_ret, We must imperatively
       put a strex after the ldex since otherwise we would block other
       threads when they try to access this. On the other hand even if
       the strex doesn't succeed but p00_ret is already set, we are also
       done. */
    if (!p00_arm_strex(object, 1) || p00_ret) return p00_ret;
  }
}

p99_inline
void p00_sync_lock_release_internal(uint32_t volatile *object, memory_order p00_ord) {
  __sync_lock_release(object);
}

p99_inline
void p00_mfence_internal(memory_order p00_ord) {
  __asm__ __volatile__("dmb":::"memory");
}

#define p00_mfence(...)                                        \
P99_IF_EMPTY(__VA_ARGS__)                                      \
 (p00_mfence_internal(memory_order_seq_cst))                   \
 (p00_mfence_internal(__VA_ARGS__))

#define p00_sync_lock_release(...)                              \
  P99_IF_LT(P99_NARG(__VA_ARGS__), 2)                           \
  (p00_sync_lock_release_internal(__VA_ARGS__))                 \
  (p00_sync_lock_release_internal(P99_ALLBUTLAST(__VA_ARGS__)))
#define p00_sync_lock_test_and_set(...)                              \
  P99_IF_LT(P99_NARG(__VA_ARGS__), 2)                                \
  (p00_sync_lock_test_and_set_internal(__VA_ARGS__))                 \
  (p00_sync_lock_test_and_set_internal(P99_ALLBUTLAST(__VA_ARGS__)))

p99_inline
uint32_t __sync_val_compare_and_swap_4(uint32_t volatile *object, uint32_t p00_pre, uint32_t p00_des) {
  uint32_t p00_ret = 0;
  for (;;) {
    p00_ret = p00_arm_ldrex(object);
    if (p00_pre != p00_ret) {
      /* wrong value, cancel */
      p00_arm_strex(object, p00_ret);
      break;
    } else {
      if (!p00_arm_strex(object, p00_des)) break;
      /* somebody else touched it, continue */
    }
  }
  return p00_ret;
}

p99_inline
uint32_t __sync_fetch_and_add_4(uint32_t volatile *object, uint32_t p00_val) {
  uint32_t p00_ret = 0;
  for (;;) {
    p00_ret = p00_arm_ldrex(object);
    uint32_t p00_des = p00_ret + p00_val;
    if (!p00_arm_strex(object, p00_des)) break;
    /* somebody else touched it, continue */
  }
  return p00_ret;
}

p99_inline
uint32_t __sync_fetch_and_sub_4(uint32_t volatile *object, uint32_t p00_val) {
  uint32_t p00_ret = 0;
  for (;;) {
    p00_ret = p00_arm_ldrex(object);
    uint32_t p00_des = p00_ret - p00_val;
    if (!p00_arm_strex(object, p00_des)) break;
    /* somebody else touched it, continue */
  }
  return p00_ret;
}

p99_inline
uint32_t __sync_fetch_and_or_4(uint32_t volatile *object, uint32_t p00_val) {
  uint32_t p00_ret = 0;
  for (;;) {
    p00_ret = p00_arm_ldrex(object);
    uint32_t p00_des = p00_ret | p00_val;
    if (!p00_arm_strex(object, p00_des)) break;
    /* somebody else touched it, continue */
  }
  return p00_ret;
}

p99_inline
uint32_t __sync_fetch_and_and_4(uint32_t volatile *object, uint32_t p00_val) {
  uint32_t p00_ret = 0;
  for (;;) {
    p00_ret = p00_arm_ldrex(object);
    uint32_t p00_des = p00_ret & p00_val;
    if (!p00_arm_strex(object, p00_des)) break;
    /* somebody else touched it, continue */
  }
  return p00_ret;
}

p99_inline
uint32_t __sync_fetch_and_xor_4(uint32_t volatile *object, uint32_t p00_val) {
  uint32_t p00_ret = 0;
  for (;;) {
    p00_ret = p00_arm_ldrex(object);
    uint32_t p00_des = p00_ret ^ p00_val;
    if (!p00_arm_strex(object, p00_des)) break;
    /* somebody else touched it, continue */
  }
  return p00_ret;
}

#undef __GCC_HAVE_SYNC_COMPARE_AND_SWAP_4
#define __GCC_HAVE_SYNC_COMPARE_AND_SWAP_4 1


/**
 ** @}
 **/

# endif

#endif
