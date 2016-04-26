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
#ifndef P99_LIFO_H
#define P99_LIFO_H 1

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

#include "p99_tp.h"

# define P99_LIFO(T) P99_TP(T)

P00_DOCUMENT_TYPE_ARGUMENT(P99_LIFO_DECLARE, 0)
# define P99_LIFO_DECLARE(T) P99_TP_DECLARE(T)
# define P99_LIFO_INITIALIZER(VAL) P99_TP_INITIALIZER(VAL)

# define p99_lifo_init(EL, VAL) p99_tp_init((EL), (VAL))

/**
 ** @brief Return a pointer to the top element of an atomic LIFO @a L
 ** @see P99_LIFO_CLEAR
 ** @see P99_LIFO_POP
 ** @see P99_LIFO_PUSH
 **/
P00_DOCUMENT_PERMITTED_ARGUMENT(P99_LIFO_TOP, 0)
#define P99_LIFO_TOP(L) P99_TP_GET(L)


/**
 ** @brief Push element @a EL into an atomic LIFO @a L
 ** @see P99_LIFO_CLEAR
 ** @see P99_LIFO_POP
 ** @see P99_LIFO_TOP
 **/
P00_DOCUMENT_PERMITTED_ARGUMENT(P99_LIFO_PUSH, 0)
P00_DOCUMENT_PERMITTED_ARGUMENT(P99_LIFO_PUSH, 1)
#define P99_LIFO_PUSH(L, EL)                                                    \
p99_extension                                                                   \
({                                                                              \
  register const P99_MACRO_VAR(p00_l, (L));                                     \
  register P99_TP_TYPE(p00_l)*const p00_rr = (EL);                              \
  P99_TP_TYPE_STATE(p00_l) p00_state = P99_TP_STATE_INITIALIZER(p00_l, p00_rr); \
  do {                                                                          \
    p00_rr->p99_lifo = P99_TP_STATE_GET(&p00_state);                            \
  } while (!P99_TP_STATE_COMMIT(&p00_state));                                   \
})

/**
 ** @brief Pop the top element from an atomic LIFO @a L
 **
 ** This implements a generic interface to an atomic LIFO (Last In -
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
 ** extern P99_LIFO(myData_ptr) head;
 ** @endcode
 **
 ** Now @c head can be used as the head of a LIFO:
 **
 ** @code
 ** myData_ptr el = P99_NEW(myData, \/\* your initializer arguments \*\/);
 ** P99_LIFO_PUSH(&head, el);
 ** ...
 ** for (myData_ptr el = P99_LIFO_POP(&head);
 **      el;
 **      el = P99_LIFO_POP(&head)) {
 **        // do something with el and then
 **        free(el);
 ** }
 ** @endcode
 **
 ** @see P99_LIFO_CLEAR
 ** @see P99_LIFO
 ** @see P99_LIFO_DECLARE
 ** @see P99_LIFO_PUSH
 **/
P00_DOCUMENT_PERMITTED_ARGUMENT(P99_LIFO_POP, 0)
#define P99_LIFO_POP(L)                                                    \
p99_extension                                                              \
({                                                                         \
  register const P99_MACRO_VAR(p00_l, (L));                                \
  P99_TP_TYPE_STATE(p00_l) p00_state = P99_TP_STATE_INITIALIZER(p00_l, 0); \
  /* be sure that the result can not be used as an lvalue */               \
  register P99_TP_TYPE(p00_l)* p00_r = P99_TP_STATE_GET(&p00_state);       \
  for (; p00_r; p00_r = P99_TP_STATE_GET(&p00_state)) {                    \
    P99_TP_STATE_SET(&p00_state, p00_r->p99_lifo);                         \
    if (P99_TP_STATE_COMMIT(&p00_state))                                   \
      break;                                                               \
  }                                                                        \
  if (p00_r) p00_r->p99_lifo = 0;                                          \
  p00_r;                                                                   \
})

#define P00_LIFO_REVERT(L)                                     \
p99_extension                                                  \
({                                                             \
  register P99_MACRO_VAR(p00_h, (L));                          \
  register P99_MACRO_VAR(p00_t, P99_PROMOTE_0(p00_h));         \
  while (p00_h) {                                              \
    register P99_MACRO_VAR(p00_n, p00_h->p99_lifo);            \
    p00_h->p99_lifo = p00_t;                                   \
    p00_h = p00_n;                                             \
  }                                                            \
  /* make sure that the result can not be used as an lvalue */ \
  register const __typeof__(p00_t = p00_t) p00_r = p00_t;      \
  p00_r;                                                       \
})

/**
 ** @brief Atomically clear an atomic LIFO @a L and return a pointer
 ** to the start of the list that it previously contained
 **
 ** @see P99_LIFO
 ** @see P99_LIFO_DECLARE
 ** @see P99_LIFO_PUSH
 ** @see P99_LIFO_TOP
 **/
P00_DOCUMENT_PERMITTED_ARGUMENT(P99_LIFO_CLEAR, 0)
#define P99_LIFO_CLEAR(L)                                                  \
p99_extension                                                              \
({                                                                         \
  register const P99_MACRO_VAR(p00_l, (L));                                \
  P99_TP_TYPE_STATE(p00_l) p00_state = P99_TP_STATE_INITIALIZER(p00_l, 0); \
  /* be sure that the result can not be used as an lvalue */               \
  register P99_TP_TYPE(p00_l)* p00_r = P99_TP_STATE_GET(&p00_state);       \
  for (; p00_r; p00_r = P99_TP_STATE_GET(&p00_state)) {                    \
    if (P99_TP_STATE_COMMIT(&p00_state))                                   \
      break;                                                               \
  }                                                                        \
  p00_r;                                                                   \
})

#else

/* A fall back implementation for the case that there are no atomic
   operations available */

# define P99_LIFO(T) P99_PASTE2(p00_lifo_, T)
# define P99_LIFO_DECLARE(T) typedef T P99_LIFO(T)
# define P99_LIFO_INITIALIZER(VAL) ((void*)VAL)

#define P99_LIFO_TOP(L)  (*(L))

#define P99_LIFO_PUSH(L, EL)                                   \
p99_extension                                                  \
({                                                             \
  P99_MACRO_VAR(p00_l, (L));                                   \
  P99_MACRO_VAR(p00_el, (EL));                                 \
  p00_el->p99_lifo = *p00_l;                                   \
  *p00_l = p00_el;                                             \
})

#define P99_LIFO_POP(L)                                        \
p99_extension                                                  \
({                                                             \
  P99_MACRO_VAR(p00_l, (L));                                   \
  P99_MACRO_VAR(p00_el, *p00_l);                               \
  *p00_l = p00_el->p99_lifo;                                   \
  if (p00_el) p00_el->p99_lifo = 0;                            \
  /* be sure that the result can not be used as an lvalue */   \
  register __typeof__(p00_el = p00_el) p00_r = p00_el;         \
  p00_r;                                                       \
})

/**
 ** @brief Atomically clear an atomic LIFO @a L and return a pointer
 ** to the start of the list that it previously contained
 **
 ** @see P99_LIFO_POP
 ** @see P99_LIFO_PUSH
 ** @see P99_LIFO_TOP
 **/
P00_DOCUMENT_PERMITTED_ARGUMENT(P99_LIFO_CLEAR, 0)
#define P99_LIFO_CLEAR(L)                                      \
({                                                             \
  P99_MACRO_VAR(p00_l, (L));                                   \
  register P99_MACRO_VAR(p00_ret, *p00_l);                     \
  *p00_l = 0;                                                  \
  p00_ret;                                                     \
})

#endif

P00_DOCUMENT_TYPE_ARGUMENT(P99_LIFO_TABULATE, 0)
P00_DOCUMENT_IDENTIFIER_ARGUMENT(P99_LIFO_TABULATE, 1)
P00_DOCUMENT_PERMITTED_ARGUMENT(P99_LIFO_TABULATE, 2)
#define P99_LIFO_TABULATE(TYPE, TAB, L) P00_LIFO_TABULATE(TYPE, TAB, P99_UNIQ(TAB), L)

#define P00_LIFO_TABULATE(TYPE, TAB, ID, L)                    \
size_t P99_PASTE2(ID, _cnt) = 0;                               \
TYPE * P99_PASTE2(ID, _head) = P99_LIFO_CLEAR(L);              \
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
