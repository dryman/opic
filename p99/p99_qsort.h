/* This may look like nonsense, but it really is -*- mode: C -*-              */
/*                                                                            */
/* Except for parts copied from previous work and as explicitly stated below, */
/* the author and copyright holder for this work is                           */
/* (C) copyright  2012-2013 Jens Gustedt, INRIA, France                       */
/*                                                                            */
/* This file is free software; it is part of the P99 project.                 */
/* You can redistribute it and/or modify it under the terms of the QPL as     */
/* given in the file LICENSE. It is distributed without any warranty;         */
/* without even the implied warranty of merchantability or fitness for a      */
/* particular purpose.                                                        */
/*                                                                            */
#ifndef P99_QSORT_H_
#define P99_QSORT_H_
#include "p99_rand.h"
#include "p99_arith.h"

/** @file
 **
 ** @brief An implementation of a sorting routine
 **/

/**
 ** @addtogroup sorting
 ** @{
 **/

P99_DECLARE_STRUCT(p00_qsort);

struct p00_qsort {
  size_t bot;
  size_t top;
};

#define P00_QSWAP_MEMCPY(P, A, B)                              \
do {                                                           \
  void * p00Ma = (P)+(A);                                      \
  void * p00Mb = (P)+(B);                                      \
  /* if (p00Ma != p00Mb) */ {                                  \
    memcpy(&p00_tmp, p00Ma, p00_s);                            \
    memcpy(p00Ma, p00Mb, p00_s);                               \
    memcpy(p00Mb, &p00_tmp, p00_s);                            \
  }                                                            \
} while (false)

#define P00_QSWAP_VCPY_(A, B)                                  \
for (size_t p00Mi = 0; p00Mi < p00_vsize; ++p00Mi)             \
  (A)[p00Mi] = (B)[p00Mi]


#define P00_QSWAP_VCPY(P, A, B)                                \
do {                                                           \
  P00_QSWAP_VCPY_(p00_tmp, (P)[A]);                            \
  P00_QSWAP_VCPY_((P)[A], (P)[B]);                             \
  P00_QSWAP_VCPY_((P)[B], p00_tmp);                            \
} while (false)

#define P00_QSWAP_ASSIGN(P, A, B)                              \
do {                                                           \
  p00_tmp = (P)[A];                                            \
  (P)[A] = (P)[B];                                             \
  (P)[B] = p00_tmp;                                            \
 } while (false)

#define P00_QCOMP(A, B) p00_comp(&p00_B[A], &p00_B[B], p00_ctx)

#define P00_QPUSH(P, B, T)                                     \
do {                                                           \
  register p00_qsort *const p00Mp = ++(P);                     \
  p00Mp->bot = (B);                                            \
  p00Mp->top = (T);                                            \
 } while (false)

#define P00_QTOP(P, B, T)                                      \
  register size_t const B = (P)->bot;                          \
  register size_t const T = (P)->top

#define P00_QEMPTY(S, P) ((S) == (P))

#define P00_QSORT_BODY(SWAP)                                          \
if (p00_n > RSIZE_MAX || p00_s > RSIZE_MAX) return EDOM;              \
if (p00_n && (!p00_base || !p00_comp)) return EINVAL;                 \
do {                                                                  \
  register p99_seed *const seed = p99_seed_get();                     \
  /* Initialize a stack of states */                                  \
  P99_CONSTANT(int, p00_tail, 20);                                    \
  /* provide a reasonable stack of states */                          \
  p00_qsort p00_a[(p99_arith_log2(p00_n) + 1)*p00_tail];              \
  p00_qsort* p00_p = p00_a;                                           \
  P00_QPUSH(p00_p, 0, p00_n);                                         \
  while(!P00_QEMPTY(p00_a, p00_p)) {                                  \
    /* read the values from the stack */                              \
    P00_QTOP(p00_p, p00_bot, p00_top);                                \
    register size_t const p00_len = p00_top - p00_bot;                \
                                                                      \
    switch (p00_len) {                                                \
      /* special cases all fall through. */                           \
    case 2:                                                           \
      if (P00_QCOMP(p00_bot, p00_bot + 1) > 0)                        \
        SWAP(p00_B, p00_bot, p00_bot + 1);                            \
    case 1: ;                                                         \
    case 0:                                                           \
      --p00_p;                                                        \
      break;                                                          \
    default:                                                          \
      /* move the pivot to the bottom element */                      \
      {                                                               \
        size_t p00_c = p99_rand(seed) % p00_len;                      \
        if (p00_c) SWAP(p00_B, p00_bot, p00_bot + p00_c);             \
      }                                                               \
                                                                      \
      /* The running variables. The fact that p00_b is > p00_bot,     \
         guarantees progress. */                                      \
      register size_t p00_b = p00_bot + 1;                            \
      register size_t p00_t = p00_top;                                \
                                                                      \
      while (P99_LIKELY(p00_b < p00_t)) {                             \
        /* Try to find two misplaced elements. */                     \
        while (!(P00_QCOMP(p00_bot, p00_b) < 0)) {                    \
          ++p00_b;                                                    \
          if (P99_UNLIKELY(p00_b == p00_t)) goto P00_RECURSE;         \
        }                                                             \
        while (P00_QCOMP(p00_bot, p00_t - 1) < 0){                    \
          --p00_t;                                                    \
          if (P99_UNLIKELY(p00_b == p00_t)) goto P00_RECURSE;         \
        }                                                             \
                                                                      \
        /* Two distinct misplaced elements are found. */              \
        --p00_t;                                                      \
        SWAP(p00_B, p00_b, p00_t);                                    \
        ++p00_b;                                                      \
      }                                                               \
    P00_RECURSE:                                                      \
      if ((p00_b - p00_bot) > 1) {                                    \
        /* The pivot is always a maximal element in the lower part */ \
        --p00_b;                                                      \
        SWAP(p00_B, p00_bot, p00_b);                                  \
        /* Move all elements that compare equal adjacent */           \
        register size_t const p00_bb = p00_b;                         \
        for (register size_t p00_c = p00_bot;                         \
             p00_c < p00_b;) {                                        \
          if (P00_QCOMP(p00_bb, p00_c) <= 0) {                        \
            --p00_b;                                                  \
            if (p00_c == p00_b) break;                                \
            SWAP(p00_B, p00_c, p00_b);                                \
          } else ++p00_c;                                             \
        }                                                             \
      }                                                               \
      /* Register the "recursive" calls into the two halfs. Most */   \
      /* recursive calls are actually close to the bottom, so we */   \
      /* rarely have to do the check if they are small enough.   */   \
      if (P99_UNLIKELY(p00_len >= p00_tail)) {                        \
        size_t p00Mmax = p00_len*0.99;                                \
        /* If the split isn't good enough we just try again     */    \
        if (P99_UNLIKELY(((p00_b - p00_bot) >= p00Mmax)               \
                         ||                                           \
                         ((p00_top - p00_t) >= p00Mmax)))             \
          continue;                                                   \
      }                                                               \
      --p00_p;                                                        \
      if ((p00_b - p00_bot) > 1) P00_QPUSH(p00_p, p00_bot, p00_b);    \
      if ((p00_top - p00_t) > 1) P00_QPUSH(p00_p, p00_t, p00_top);    \
    }                                                                 \
  }                                                                   \
  return 0;                                                           \
 } while(false)


p99_inline
errno_t p00_qsort_generic16(void *p00_base,
                            rsize_t p00_n,
                            rsize_t p00_a,
                            rsize_t p00_s,
                            int (*p00_comp)(const void *, const void *, void *),
                            void *p00_ctx) {
  P99_UNUSED(p00_a);
  size_t const p00_vsize = p00_s / sizeof(uint16_t);
  typedef uint16_t p00_el[p00_vsize];
  register p00_el *const p00_B = p00_base;
  p00_el p00_tmp;
  P00_QSORT_BODY(P00_QSWAP_VCPY);
}


p99_inline
errno_t p00_qsort_generic32(void *p00_base,
                            rsize_t p00_n,
                            rsize_t p00_a,
                            rsize_t p00_s,
                            int (*p00_comp)(const void *, const void *, void *),
                            void *p00_ctx) {
  P99_UNUSED(p00_a);
  size_t const p00_vsize = p00_s / sizeof(uint32_t);
  typedef uint32_t p00_el[p00_vsize];
  register p00_el *const p00_B = p00_base;
  p00_el p00_tmp;
  P00_QSORT_BODY(P00_QSWAP_VCPY);
}


p99_inline
errno_t p00_qsort_generic64(void *p00_base,
                            rsize_t p00_n,
                            rsize_t p00_a,
                            rsize_t p00_s,
                            int (*p00_comp)(const void *, const void *, void *),
                            void *p00_ctx) {
  P99_UNUSED(p00_a);
  size_t const p00_vsize = p00_s / sizeof(uint64_t);
  typedef uint64_t p00_el[p00_vsize];
  register p00_el *const p00_B = p00_base;
  p00_el p00_tmp;
  P00_QSORT_BODY(P00_QSWAP_VCPY);
}


#ifdef UINT128_MAX
p99_inline
errno_t p00_qsort_generic128(void *p00_base,
                             rsize_t p00_n,
                             rsize_t p00_a,
                             rsize_t p00_s,
                             int (*p00_comp)(const void *, const void *, void *),
                             void *p00_ctx) {
  P99_UNUSED(p00_a);
  size_t const p00_vsize = p00_s / sizeof(uint128_t);
  typedef uint128_t p00_el[p00_vsize];
  register p00_el *const p00_B = p00_base;
  p00_el p00_tmp;
  P00_QSORT_BODY(P00_QSWAP_VCPY);
}
#else
# ifdef P99X_UINT128_MAX
p99_inline
errno_t p00_qsort_generic128(void *p00_base,
                             rsize_t p00_n,
                             rsize_t p00_a,
                             rsize_t p00_s,
                             int (*p00_comp)(const void *, const void *, void *),
                             void *p00_ctx) {
  P99_UNUSED(p00_a);
  size_t const p00_vsize = p00_s / sizeof(p99x_uint128);
  typedef p99x_uint128 p00_el[p00_vsize];
  register p00_el *const p00_B = p00_base;
  p00_el p00_tmp;
  P00_QSORT_BODY(P00_QSWAP_VCPY);
}
# endif
#endif


p99_inline
errno_t p00_qsort_generic(void *p00_base,
                          rsize_t p00_n,
                          rsize_t p00_a,
                          rsize_t p00_s,
                          int (*p00_comp)(const void *, const void *, void *),
                          void *p00_ctx) {
  P99_UNUSED(p00_a);
  typedef unsigned char p00_el[p00_s];
  register p00_el *const p00_B = p00_base;
  p00_el p00_tmp;
  P00_QSORT_BODY(P00_QSWAP_MEMCPY);
}


#define P00_QSORT_DECLARE(T)                                             \
p99_inline                                                               \
errno_t P99_PASTE2(p00_qsort_, T)(void *p00_base,                        \
                    rsize_t p00_n,                                       \
                    rsize_t p00_a,                                       \
                    rsize_t p00_s,                                       \
                    int (*p00_comp)(const void *, const void *, void *), \
                    void *p00_ctx) {                                     \
  P99_UNUSED(p00_a);                                                     \
  register T *const p00_B = p00_base;                                    \
  _Alignas(sizeof(max_align_t)) T p00_tmp;                               \
  P00_QSORT_BODY(P00_QSWAP_ASSIGN);                                      \
}                                                                        \
P99_MACRO_END(p00_qsort_, T)

P00_QSORT_DECLARE(_Bool);
P00_QSORT_DECLARE(schar);
P00_QSORT_DECLARE(uchar);
P00_QSORT_DECLARE(char);
P00_QSORT_DECLARE(short);
P00_QSORT_DECLARE(ushort);
P00_QSORT_DECLARE(signed);
P00_QSORT_DECLARE(unsigned);
P00_QSORT_DECLARE(long);
P00_QSORT_DECLARE(ulong);
P00_QSORT_DECLARE(llong);
P00_QSORT_DECLARE(ullong);
P00_QSORT_DECLARE(float);
P00_QSORT_DECLARE(double);
P00_QSORT_DECLARE(ldouble);
#ifndef __STDC_NO_COMPLEX__
P00_QSORT_DECLARE(cfloat);
P00_QSORT_DECLARE(cdouble);
P00_QSORT_DECLARE(cldouble);
#endif

P00_QSORT_DECLARE(void_ptr);

P00_QSORT_DECLARE(size_t);
P00_QSORT_DECLARE(ptrdiff_t);
P00_QSORT_DECLARE(intptr_t);
P00_QSORT_DECLARE(uintptr_t);

#ifdef UINT8_MAX
P00_QSORT_DECLARE(uint8_t);
P00_QSORT_DECLARE(int8_t);
#endif
#ifdef UINT16_MAX
P00_QSORT_DECLARE(uint16_t);
P00_QSORT_DECLARE(int16_t);
#endif
#ifdef UINT32_MAX
P00_QSORT_DECLARE(uint32_t);
P00_QSORT_DECLARE(int32_t);
#endif
#ifdef UINT64_MAX
P00_QSORT_DECLARE(uint64_t);
P00_QSORT_DECLARE(int64_t);
#endif
#ifdef UINT128_MAX
P00_QSORT_DECLARE(uint128_t);
P00_QSORT_DECLARE(int128_t);
#else
# ifdef P99X_UINT128_MAX
P00_QSORT_DECLARE(p99x_uint128);
P00_QSORT_DECLARE(p99x_int128);
# endif
#endif

p99_inline
errno_t p00_qsort_s(void *p00_base,
                    rsize_t p00_n,
                    rsize_t p00_a,
                    rsize_t p00_s,
                    int (*p00_comp)(const void *, const void *, void *),
                    void *p00_ctx) {
  switch (p00_a) {
#ifdef UINT16_MAX
  case sizeof(uint16_t):
    return p00_qsort_generic16(p00_base, p00_n, p00_a, p00_s, p00_comp, p00_ctx);
#endif
#ifdef UINT32_MAX
  case sizeof(uint32_t):
    return p00_qsort_generic32(p00_base, p00_n, p00_a, p00_s, p00_comp, p00_ctx);
#endif
#ifdef UINT64_MAX
  case sizeof(uint64_t):
    return p00_qsort_generic64(p00_base, p00_n, p00_a, p00_s, p00_comp, p00_ctx);
#endif
#ifdef UINT128_MAX
  case sizeof(uint128_t):
    return p00_qsort_generic128(p00_base, p00_n, p00_a, p00_s, p00_comp, p00_ctx);
#else
# ifdef P99X_UINT128_MAX
  case sizeof(p99x_uint128):
    return p00_qsort_generic128(p00_base, p00_n, p00_a, p00_s, p00_comp, p00_ctx);
# endif
#endif
  }
  return p00_qsort_generic(p00_base, p00_n, p00_a, p00_s, p00_comp, p00_ctx);
}


/**
 ** @brief A generic sorting routine.
 **
 ** This an implementation of the @c qsort variant as it is specified
 ** in Annex K of the C11 standard. Its particularity is that it
 ** additionally takes a "context" argument, which allows to program
 ** comparison functions more widely, without refering to global
 ** variables. Its prototype if it were not implemented as
 ** a type generic macro, would be:
 **
 ** @code
 ** errno_t qsort_s(void *base,
 **                 rsize_t nmemb,
 **                 rsize_t size,
 **                 int (*compar)(const void *x, const void *y, void *context),
 **                 void *context);
 ** @endcode
 **
 ** Because this is a type generic macro, the implementation can take
 ** care of the "real" base type of @c base, in particular about
 ** alignment. If it really only would receive a @c void* it would
 ** have to make the worst assumptions about that and always use
 ** @c memcpy to copy elements around. If it has more type information it
 ** can use more efficient means for that. So casting the first
 ** argument to @c void* wouldn't be a good idea.
 **/
#ifdef __STDC_NO_COMPLEX__
#define qsort_s(B, N, S, CMP, CTX)                             \
  P99_CONSTRAINT_TRIGGER(                                      \
  P99_GENERIC(&((B)[0]),                                       \
            p00_qsort_s,                                       \
            (void_ptr*, p00_qsort_void_ptr),                   \
            /* */                                              \
            (float*, p00_qsort_float),                         \
            (double*, p00_qsort_double),                       \
            (double*, p00_qsort_cdouble),                      \
            /* */                                              \
            (_Bool*, p00_qsort__Bool),                         \
            (char*, p00_qsort_char),                           \
            (uchar*, p00_qsort_uchar),                         \
            (schar*, p00_qsort_schar),                         \
            /* */                                              \
            (ushort*, p00_qsort_ushort),                       \
            (short*, p00_qsort_short),                         \
            /* */                                              \
            (unsigned*, p00_qsort_unsigned),                   \
            (signed*, p00_qsort_signed),                       \
            /* */                                              \
            (long*, p00_qsort_long),                           \
            (ulong*, p00_qsort_ulong),                         \
            /* */                                              \
            (llong*, p00_qsort_llong),                         \
            (ullong*, p00_qsort_ullong)                        \
              )((B), (N), alignof(*(B)), (S), (CMP), (CTX)),   \
  "qsort_s runtime constraint violation")
#else
#define qsort_s(B, N, S, CMP, CTX)                             \
  P99_CONSTRAINT_TRIGGER(                                      \
  P99_GENERIC(&((B)[0]),                                       \
            p00_qsort_s,                                       \
            (void_ptr*, p00_qsort_void_ptr),                   \
            /* */                                              \
            (float*, p00_qsort_float),                         \
            (double*, p00_qsort_double),                       \
            (ldouble*, p00_qsort_ldouble),                     \
            /* */                                              \
            (cfloat*, p00_qsort_cfloat),                       \
            (cdouble*, p00_qsort_cdouble),                     \
            (cldouble*, p00_qsort_cldouble),                   \
            /* */                                              \
            (_Bool*, p00_qsort__Bool),                         \
            (char*, p00_qsort_char),                           \
            (uchar*, p00_qsort_uchar),                         \
            (schar*, p00_qsort_schar),                         \
            /* */                                              \
            (ushort*, p00_qsort_ushort),                       \
            (short*, p00_qsort_short),                         \
            /* */                                              \
            (unsigned*, p00_qsort_unsigned),                   \
            (signed*, p00_qsort_signed),                       \
            /* */                                              \
            (long*, p00_qsort_long),                           \
            (ulong*, p00_qsort_ulong),                         \
            /* */                                              \
            (llong*, p00_qsort_llong),                         \
            (ullong*, p00_qsort_ullong)                        \
              )((B), (N), alignof(*(B)), (S), (CMP), (CTX)),   \
  "qsort_s runtime constraint violation")
#endif


/**
 ** @brief Check if the array passed in as @a p00_base is sorted and
 ** return the first mismatch if it is not.
 **
 ** A mismatch here is defined as the first position at which we
 ** detect that the array is not sorted. If the array is in fact
 ** sorted the return value is @a p00_n.
 **/
p99_inline
rsize_t p99_mismatch(void *p00_base,
                     rsize_t p00_n,
                     rsize_t p00_s,
                     int (*p00_comp)(const void *, const void *, void *),
                     void *p00_ctx) {
  typedef unsigned char p00_el[p00_s];
  p00_el *const p00_B = p00_base;
  for (register rsize_t p00_r = 1; p00_r < p00_n; ++p00_r) {
    if (p00_comp(&p00_B[p00_r - 1], &p00_B[p00_r], p00_ctx) > 0)
      return p00_r;
  }
  return p00_n;
}

/**
 ** @brief Check if the array passed in as @a p00_base is sorted
 **/
p99_inline
bool p99_is_sorted(void *p00_base,
                   rsize_t p00_n,
                   rsize_t p00_s,
                   int (*p00_comp)(const void *, const void *, void *),
                   void *p00_ctx) {
  return !(p99_mismatch(p00_base, p00_n, p00_s, p00_comp, p00_ctx) < p00_n);
}


/**
 ** @}
 **/

#endif
