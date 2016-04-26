/* This may look like nonsense, but it really is -*- mode: C -*-              */
/*                                                                            */
/* Except for parts copied from previous work and as explicitly stated below, */
/* the authors and copyright holders for this work are as follows:            */
/* (C) copyright  2010-2012 Jens Gustedt, INRIA, France                       */
/* (C) copyright  2012 William Morris                                         */
/*                                                                            */
/* This file is free software; it is part of the P99 project.                 */
/* You can redistribute it and/or modify it under the terms of the QPL as     */
/* given in the file LICENSE. It is distributed without any warranty;         */
/* without even the implied warranty of merchantability or fitness for a      */
/* particular purpose.                                                        */
/*                                                                            */
/*
** p99_swap.h
**
** Made by Jens Gustedt
** Login   <gustedt@damogran.loria.fr>
**
** Started on  Thu Oct 21 11:40:09 2010 Jens Gustedt
** Last update Thu Oct 21 11:40:09 2010 Jens Gustedt
*/

#ifndef     P99_SWAP_H_
# define    P99_SWAP_H_

#include "p99_int.h"

p99_inline
void p00_swap2(void* p00_p0, void* p00_p1, size_t p00_size, void*restrict p00_t0, void*restrict p00_t1) {
  if (p00_p0 != p00_p1) {
    memcpy(p00_t0, p00_p0, p00_size);
    memcpy(p00_t1, p00_p1, p00_size);
    memcpy(p00_p1, p00_t0, p00_size);
    memcpy(p00_p0, p00_t1, p00_size);
  }
}

/**
 ** @brief Swap the contents of the arguments.
 **
 ** This uses two temporary objects, allocated on the heap.
 ** @see P99_SWAP for a macro that is generally better adapted, since
 ** all allocation is done on the stack.
 ** @see p99_swap1
 **/
p99_inline
void p99_swap2(void* p00_p0, void* p00_p1, size_t p00_size) {
  if (p00_p0 != p00_p1) {
    char* p00_t0 = malloc(2 * p00_size);
    char* p00_t1 = p00_t0 + p00_size;
    p00_swap2(p00_p0, p00_p1, p00_size, p00_t0, p00_t1);
    free(p00_t0);
  }
}

p99_inline
void p00_swap1(void* p00_p0, void* p00_p1, size_t p00_size, void*restrict p00_t0) {
  if (p00_p0 != p00_p1) {
    memcpy(p00_t0, p00_p0, p00_size);
    memcpy(p00_p0, p00_p1, p00_size);
    memcpy(p00_p1, p00_t0, p00_size);
  }
}

/**
 ** @brief Swap the contents of the arguments.
 **
 ** This uses one temporary object, allocated on the heap.
 ** @see P99_SWAP for a macro that is generally better adapted, since
 ** all allocation is done on the stack.
 ** @see p99_swap2
 **/
p99_inline
void p99_swap1(void* p00_p0, void* p00_p1, size_t p00_size) {
  if (p00_p0 != p00_p1) {
    void* p00_t0 = malloc(p00_size);
    p00_swap1(p00_p0, p00_p1, p00_size, p00_t0);
    free(p00_t0);
  }
}

#define P00_SWAP2(_0, _1)                                      \
p00_swap2(                                                     \
          /* check if the two are assignment compatible */     \
          P99_SIGN_PROMOTE(&(_0), ((_0) = (_1), (void*)0)),    \
          P99_SIGN_PROMOTE(&(_1), ((_1) = (_0), (void*)0)),    \
          sizeof(_0),                                          \
          /* only works if sizeof(_0) >= sizeof(_1) */         \
          (char[sizeof(_0)]){                                  \
            [(intmax_t)sizeof(_0) - sizeof(_1)] = 0,           \
              },                                               \
          /* only works if sizeof(_0) <= sizeof(_1) */         \
          (char[sizeof(_0)]){                                  \
            [(intmax_t)sizeof(_1) - sizeof(_0)] = 0,           \
              })

#define P00_SWAP1(_0, _1)                                      \
p00_swap1(                                                     \
          /* check if the two are assignment compatible */     \
          P99_SIGN_PROMOTE(&(_0), ((_0) = (_1), (void*)0)),    \
          P99_SIGN_PROMOTE(&(_1), ((_1) = (_0), (void*)0)),    \
          sizeof(_0),                                          \
          /* only works if sizeof(_0) <= sizeof(_1) */         \
          (char[sizeof(_0)]){                                  \
            [(intmax_t)sizeof(_1) - sizeof(_0)] = 0,           \
              })


/**
 ** @brief Swap the contents of the arguments.
 **
 ** This macro has the following properties:
 **  - It evaluates each of @a _0 and @a _1 only once.
 **  - It has a compile time check for the correct sizes.
 **  - It checks if the two expressions are assignment compatible in
 **    both ways
 **  - It has no naming issues with a hidden variable.
 **  - The size of the temporary variable is computed at compile
 **    time. So we may use a compound literal and not a dynamic array.
 **
 ** @remark This implementation is a follow up of a <a
 ** href="http://stackoverflow.com/questions/3982348/implement-generic-swap-macro-in-c/3983089#3983089">
 ** discussion on stackoverflow</a>.
 **
 ** @remark The concrete implementation separates into two different
 ** cases: @c P00_SWAP2(_0, _1), for small sizes, uses two
 ** temporaries in the hope that the loads into registers can be done
 ** simultaneously. The other one, @c P00_SWAP1(_0, _1), uses only one
 ** temporary but is then forced to serialize copy operations.
 **
 ** @warning For both arguments
 ** - each must be an lvalue expression
 ** - it must be permitted to take their addresses.
 **
 ** So variables that have the @c register storage class will not work
 ** with this macro.
 **
 ** @warning The types of the arguments are only checked to confirm that they
 ** have the same size @em and that the two lvalues are assignment
 ** compatible. If both are
 ** - of the same size,
 ** - are assignment compatible,
 ** - have different semantics,
 **
 ** you are in trouble. This may happen in the following cases:
 ** - A signed and unsigned type of same size, e.g <code>signed int</code> and
 **   <code>unsigned int</code>
 ** - Two integer types that by coincidence have the same size, e.g on
 **   a platform <code>long</code> and <code>long long</code> may
 **   both be 8 byte. This may work ok for a long time and then fail when
 **   you move to another platform.
 ** - If one type is a floating point type and the other an integral
 **   type, e.g @c double and a @c uint64_t may be of the same size.
 ** - Two types that have the same size but not the same width. A @c
 **   bool will usually be stored in one byte, but memcpy from a @c
 **   char is not equivalent to assigning it with @c =. Padding bits
 **   may have the effect that the value stored in a @c bool is a trap
 **   representation.
 **
 **/
P00_DOCUMENT_PERMITTED_ARGUMENT(P99_SWAP, 0)
P00_DOCUMENT_PERMITTED_ARGUMENT(P99_SWAP, 1)
#define P99_SWAP(_0, _1) ((sizeof(_0) > sizeof(uintmax_t)) ? P00_SWAP1(_0, _1) : P00_SWAP2(_0, _1))


P00_DOCUMENT_PERMITTED_ARGUMENT(P99_QSORT, 0)
#define P99_QSORT(TAB, NB, ...)                                \
P99_IF_LT(P99_NARG(__VA_ARGS__), 2)                            \
(qsort((TAB), (NB), sizeof (TAB)[0], __VA_ARGS__))             \
(qsort_s((TAB), (NB), sizeof (TAB)[0], __VA_ARGS__))

P00_DOCUMENT_PERMITTED_ARGUMENT(P99_ASORT, 0)
#define P99_ASORT(TAB, ...)                                    \
P99_IF_LT(P99_NARG(__VA_ARGS__), 2)                            \
(qsort((TAB), P99_ALEN(TAB), sizeof (TAB)[0], __VA_ARGS__))    \
(qsort_s((TAB), P99_ALEN(TAB), sizeof (TAB)[0], __VA_ARGS__))

#endif      /* !P99_SWAP_H_ */
