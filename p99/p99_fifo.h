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
#ifndef P99_FIFO_H
#define P99_FIFO_H 1

#include "p99_enum.h"
#include "p99_generic.h"

/* Additions by C11 */
# if __STDC_VERSION__ < 201100L
#  include "p99_atomic.h"
# endif


/**
 ** @addtogroup atomic C11 atomic operations
 ** @{
 **/

#if defined(P99_DECLARE_ATOMIC) || P00_DOXYGEN
# define P99_FIFO(T) P99_PASTE2(p00_fifo_, T)
# define P99_FIFO_DECLARE(T)                                     \
typedef T P99_PASTE2(p00_fifo_base_, T);                         \
P99_DECLARE_ATOMIC(P99_PASTE2(p00_fifo_base_, T));               \
 struct P99_PASTE2(p00_fifo_, T) {                               \
 _Atomic(P99_PASTE2(p00_fifo_base_, T)) p00_head;                \
 _Atomic(P99_PASTE2(p00_fifo_base_, T)) p00_tail;                \
 };                                                              \
typedef struct P99_PASTE2(p00_fifo_, T) P99_PASTE2(p00_fifo_, T)
# define P99_FIFO_INITIALIZER(HEAD, TAIL) {                    \
  .p00_head = ATOMIC_VAR_INIT(HEAD),                           \
  .p00_tail = ATOMIC_VAR_INIT(TAIL),                           \
}

/**
 ** @brief Append element @a EL to an atomic FIFO @a L
 ** @see P99_FIFO_CLEAR
 ** @see P99_FIFO_POP
 ** @see P00_FIFO_EL
 **/
P00_DOCUMENT_PERMITTED_ARGUMENT(P99_FIFO_APPEND, 0)
P00_DOCUMENT_PERMITTED_ARGUMENT(P99_FIFO_APPEND, 1)
#define P99_FIFO_APPEND(L, EL)                                                                                              \
do {                                                                                                                        \
  /* first evaluate the macro arguments such that there can't be */                                                         \
  /* name conflicts */                                                                                                      \
  register const P99_MACRO_VAR(p00_l, (L));                                                                                 \
  register const P99_MACRO_VAR(p00_el, (EL));                                                                               \
  register const P99_MACRO_VAR(p00_h, &p00_l->p00_head);                                                                    \
  register const P99_MACRO_VAR(p00_t, &p00_l->p00_tail);                                                                    \
  p00_el->p99_lifo = 0;                                                                                                     \
  P99_MACRO_VAR(p00_head, atomic_load_explicit(p00_h, memory_order_relaxed));                                               \
  for (;;) {                                                                                                                \
    if (p00_head) {                                                                                                         \
      /* spin lock the whole fifo */                                                                                        \
      if (atomic_compare_exchange_weak_explicit(p00_h, &p00_head, 0, memory_order_acq_rel, memory_order_relaxed)) {         \
        /* make p00_el the last element */                                                                                  \
        atomic_exchange_explicit(p00_t, p00_el, memory_order_acq_rel)->p99_lifo = p00_el;                                   \
        /* unlock the fifo */                                                                                               \
        atomic_store_explicit(p00_h, p00_head, memory_order_release);                                                       \
        break;                                                                                                              \
      }                                                                                                                     \
    } else {                                                                                                                \
      P99_MACRO_VAR(p00_tail, atomic_load_explicit(p00_t, memory_order_relaxed));                                           \
      if (!p00_tail                                                                                                         \
          && atomic_compare_exchange_weak_explicit(p00_t, &p00_tail, p00_el, memory_order_acq_rel, memory_order_relaxed)) { \
        /* the fifo was empty, our element is inserted, update the head */                                                  \
        atomic_store_explicit(p00_h, p00_el, memory_order_release);                                                         \
        break;                                                                                                              \
      }                                                                                                                     \
      /* we were in the middle of an update of another thread */                                                            \
      p00_head = atomic_load_explicit(p00_h, memory_order_consume);                                                         \
    }                                                                                                                       \
  }                                                                                                                         \
} while (false)

/**
 ** @brief Pop the front element from an atomic FIFO @a L
 **
 ** This implements a generic interface to an atomic FIFO (First In -
 ** First Out) data structure. To use it you just have do some
 ** preparatory declarations and add a @c p99_lifo field to your data
 ** structure:
 **
 ** @code
 ** P99_DECLARE_STRUCT(myData);
 ** P99_POINTER_TYPE(myData);
 ** P99_FIFO_DECLARE(myData_ptr);
 **
 ** struct myData {
 **   ...
 **   myData_ptr p99_lifo;
 **   ...
 ** };
 ** extern P99_FIFO(myData_ptr) head;
 ** @endcode
 **
 ** Now @c head can be used as the head of a FIFO:
 **
 ** @code
 ** myData_ptr el = P99_NEW(myData, \/\* your initializer arguments \*\/);
 ** P99_FIFO_APPEND(&head, el);
 ** ...
 ** for (myData_ptr el = P99_FIFO_POP(&head);
 **      el;
 **      el = P99_FIFO_POP(&head)) {
 **        // do something with el and then
 **        free(el);
 ** }
 ** @endcode
 **
 ** @see P99_FIFO_CLEAR
 ** @see P99_FIFO
 ** @see P99_FIFO_DECLARE
 ** @see P99_FIFO_APPEND
 **/
P00_DOCUMENT_PERMITTED_ARGUMENT(P99_FIFO_POP, 0)
#define P99_FIFO_POP(L)                                                                                             \
p99_extension                                                                                                       \
({                                                                                                                  \
  /* first evaluate the macro argument such that there can't be */                                                  \
  /* a name conflict */                                                                                             \
  register const P99_MACRO_VAR(p00_l, (L));                                                                         \
  register const P99_MACRO_VAR(p00_h, &p00_l->p00_head);                                                            \
  register const P99_MACRO_VAR(p00_t, &p00_l->p00_tail);                                                            \
  P99_MACRO_VAR(p00_head, atomic_load_explicit(p00_h, memory_order_relaxed));                                       \
  for (;;) {                                                                                                        \
    if (p00_head) {                                                                                                 \
      /* spin lock the whole fifo */                                                                                \
      if (atomic_compare_exchange_weak_explicit(p00_h, &p00_head, 0, memory_order_acq_rel, memory_order_consume)) { \
        if (p00_head->p99_lifo)                                                                                     \
          /* there is still another element to come in the fifo, make it                                            \
             the head */                                                                                            \
          atomic_store_explicit(p00_h, p00_head->p99_lifo, memory_order_release);                                   \
        else                                                                                                        \
          /* this was the last element in the fifo, set the tail to 0,                                              \
             too */                                                                                                 \
          atomic_store_explicit(p00_t, 0, memory_order_release);                                                    \
        p00_head->p99_lifo = 0;                                                                                     \
        break;                                                                                                      \
      }                                                                                                             \
    } else {                                                                                                        \
      register P99_MACRO_VAR(p00_tail, atomic_load_explicit(p00_t, memory_order_consume));                          \
      if (!p00_tail) break;                                                                                         \
      p00_head = atomic_load_explicit(p00_h, memory_order_relaxed);                                                 \
    }                                                                                                               \
  }                                                                                                                 \
  /* make sure that the result can not be used as an lvalue */                                                      \
  register const __typeof__(p00_head = p00_head) p00_r = p00_head;                                                  \
  p00_r;                                                                                                            \
})

/**
 ** @brief Atomically clear an atomic FIFO @a L and return a pointer
 ** to the start of the list that it previously contained
 **
 ** @see P99_FIFO
 ** @see P99_FIFO_DECLARE
 ** @see P99_FIFO_APPEND
 ** @see P00_FIFO_EL
 **/
P00_DOCUMENT_PERMITTED_ARGUMENT(P99_FIFO_CLEAR, 0)
#define P99_FIFO_CLEAR(L)                                                                                           \
p99_extension                                                                                                       \
({                                                                                                                  \
  /* first evaluate the macro argument such that there can't be */                                                  \
  /* a name conflict */                                                                                             \
  register const P99_MACRO_VAR(p00_l, (L));                                                                         \
  register const P99_MACRO_VAR(p00_h, &p00_l->p00_head);                                                            \
  register const P99_MACRO_VAR(p00_t, &p00_l->p00_tail);                                                            \
  P99_MACRO_VAR(p00_head, atomic_load_explicit(p00_h, memory_order_relaxed));                                       \
  for (;;) {                                                                                                        \
    if (p00_head) {                                                                                                 \
      /* spin lock the whole fifo */                                                                                \
      if (atomic_compare_exchange_weak_explicit(p00_h, &p00_head, 0, memory_order_acq_rel, memory_order_consume)) { \
        atomic_store_explicit(p00_t, 0, memory_order_release);                                                      \
        break;                                                                                                      \
      }                                                                                                             \
    } else {                                                                                                        \
      register const P99_MACRO_VAR(p00_tail, atomic_load_explicit(p00_t, memory_order_consume));                    \
      if (!p00_tail) break;                                                                                         \
      p00_head = atomic_load_explicit(p00_h, memory_order_relaxed);                                                 \
    }                                                                                                               \
  }                                                                                                                 \
  /* make sure that the result can not be used as an lvalue */                                                      \
  register const __typeof__(p00_head = p00_head) p00_r = p00_head;                                                  \
  p00_r;                                                                                                            \
})

#else

/* A fall back implementation for the case that there are no atomic
   operations available */

# define P99_FIFO(T) P99_PASTE2(p00_fifo_, T)
# define P99_FIFO_DECLARE(T) typedef T P99_PASTE2(p00_fifo_, T)[2]
# define P99_FIFO_INITIALIZER(HEAD, TAIL) { [0] = (HEAD), [1] = (TAIL) }

#define P99_FIFO_APPEND(L, EL)                                 \
p99_extension                                                  \
({                                                             \
  P99_MACRO_VAR(p00_l, (L));                                   \
  P99_MACRO_VAR(p00_el, (EL));                                 \
  p00_el->p99_lifo = (*p00_l)[1];                              \
  (*p00_l)[1] = p00_el;                                        \
  if (!(*p00_l)[0]) (*p00_l)[0] = p00_el;                      \
})

#define P99_FIFO_POP(L)                                        \
p99_extension                                                  \
({                                                             \
  P99_MACRO_VAR(p00_l, (L));                                   \
  P99_MACRO_VAR(p00_el, (*p00_l)[0]);                          \
  (*p00_l)[0] = p00_el->p99_lifo;                              \
  if (!(*p00_l)[0]) = (*p00_l)[0] = 0;                         \
  if (p00_el) p00_el->p99_lifo = 0;                            \
  /* be sure that the result can not be used as an lvalue */   \
  register const __typeof__(p00_el = p00_el) p00_r = p00_el;   \
  p00_r;                                                       \
})

P00_DOCUMENT_PERMITTED_ARGUMENT(P99_FIFO_CLEAR, 0)
#define P99_FIFO_CLEAR(L)                                      \
({                                                             \
  P99_MACRO_VAR(p00_l, (L));                                   \
  register P99_MACRO_VAR(p00_ret, (*p00_l)[0]);                \
  (*p00_l)[0] = 0;                                             \
  (*p00_l)[1] = 0;                                             \
  p00_ret;                                                     \
})

#endif

P00_DOCUMENT_TYPE_ARGUMENT(P99_FIFO_TABULATE, 0)
P00_DOCUMENT_IDENTIFIER_ARGUMENT(P99_FIFO_TABULATE, 1)
P00_DOCUMENT_PERMITTED_ARGUMENT(P99_FIFO_TABULATE, 2)
#define P99_FIFO_TABULATE(TYPE, TAB, L) P00_FIFO_TABULATE(TYPE, TAB, P99_UNIQ(TAB), L)

#define P00_FIFO_TABULATE(TYPE, TAB, ID, L)                    \
size_t P99_PASTE2(ID, _cnt) = 0;                               \
TYPE * P99_PASTE2(ID, _head) = P99_FIFO_CLEAR(L);              \
for (TYPE * p00_e = P99_PASTE2(ID, _head);                     \
     p00_e;                                                    \
     p00_e = p00_e->p99_lifo)                                  \
  ++P99_PASTE2(ID, _cnt);                                      \
TYPE * TAB[P99_PASTE2(ID, _cnt)];                              \
for (TYPE ** p00_t = &(TAB[0]),                                \
       * p00_e = P99_PASTE2(ID, _head);                        \
     p00_e;                                                    \
     p00_e = p00_e->p99_lifo,                                  \
       ++p00_t)                                                \
  *p00_t = p00_e

/**
 ** @}
 **/

#endif
