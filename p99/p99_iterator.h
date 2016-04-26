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
#ifndef P99_ITERATOR_H
#define P99_ITERATOR_H

#include "p99_futex.h"

/**
 ** @addtogroup futex
 ** @{
 **/

P99_DECLARE_STRUCT(p99_iterator);

/**
 ** @brief Iterate over a series events that are signaled by other
 ** threads.
 **
 ** A @c for-loop like the following
 ** @code
 ** p99_iterator it;
 ** p99_iterator_init(&it);
 ** .
 ** .
 ** for (unsigned i = p99_iterator_next(&it);
 **      i < n;
 **      i = p99_iterator_next(&it))
 **      do_something_with(A[i]);
 ** @endcode
 **
 ** will step through @n calls to @c do_something_with as other
 ** threads signal events through ::p99_iterator_signal.
 **
 ** @see p99_iterator_next
 ** @see p99_iterator_signal
 **/
struct p99_iterator {
  unsigned p00_act;
  p99_futex p00_seen;
};

/**
 ** @brief Initialize an iterator
 ** @related p99_iterator
 **/
P99_DEFARG_DOCU(p99_iterator_init)
p99_inline
p99_iterator* p99_iterator_init(p99_iterator* p00_i) {
  if (p00_i) {
    p00_i->p00_act = 0;
    p99_futex_init(&p00_i->p00_seen, 0);
  }
  return p00_i;
}

/**
 ** @brief destroy a iterator
 ** @related p99_iterator
 **/
p99_inline
void p99_iterator_destroy(p99_iterator* p00_i) {
  if (p00_i) {
    p99_futex_destroy(&p00_i->p00_seen);
  }
}

/**
 ** @brief Block until an event has been signaled that has not yet
 ** been accounted for
 **
 ** Non blocking if enough events already have been signaled.
 **
 ** @related p99_iterator
 **/
P99_DEFARG_DOCU(p99_iterator_next)
P00_FUTEX_INLINE(p99_iterator_next)
unsigned p99_iterator_next(p99_iterator volatile* p00_i) {
  register unsigned const p00_act = p00_i->p00_act;
  P99_FUTEX_COMPARE_EXCHANGE(&p00_i->p00_seen, p00_seen,
                             /* wait for more events than we have
                                already processed */
                             (p00_act < p00_seen),
                             /* never update */
                             p00_seen,
                             /* never wakeup others */
                             0u, 0u);
  p00_i->p00_act = p00_act + 1;
  return p00_act;
}

/**
 ** @brief Signal an event.
 **
 ** @related p99_iterator
 **/
P99_DEFARG_DOCU(p99_iterator_signal)
p99_inline
unsigned p99_iterator_signal(p99_iterator volatile* p00_i) {
  return p99_futex_add(&p00_i->p00_seen, 1u, 0u, UINT_MAX, 0u, P99_FUTEX_MAX_WAITERS);
}


P99_DECLARE_STRUCT(p99_event);

struct p99_event {
  p99_iterator p00_it;
  unsigned p00_n;
  void ** p00_event;
};

/**
 ** @brief Initialize an event
 ** @related p99_event
 **/
P99_DEFARG_DOCU(p99_event_init)
p99_inline
p99_event* p99_event_init(p99_event* p00_e, unsigned p00_n) {
  if (p00_e) {
    (*p00_e) = (p99_event) {
      .p00_n = p00_n,
       .p00_event = P99_MEMZERO(void_ptr, P99_MALLOC(void_ptr[p00_n]), p00_n),
    };
    p99_iterator_init(&p00_e->p00_it);
  }
  return p00_e;
}

/**
 ** @brief destroy an event
 ** @related p99_event
 **/
p99_inline
void p99_event_destroy(p99_event* p00_e) {
  if (p00_e) {
    free(p00_e->p00_event);
    p99_iterator_destroy(&p00_e->p00_it);
  }
}

/**
 ** @brief Block until an event has been signaled that has not yet
 ** been accounted for
 **
 ** Non blocking if enough events already have been signaled.
 **
 ** @related p99_event
 **/
P99_DEFARG_DOCU(p99_event_next)
P00_FUTEX_INLINE(p99_event_next)
void* p99_event_next(p99_event volatile* p00_e) {
  P99_FPRINTF(stderr, "next event on %s\n", (void*)p00_e);
  unsigned p00_pos = p99_iterator_next(&p00_e->p00_it);
  void* p00_ret = 0;
  if (p00_pos < p00_e->p00_n)
    while (!(p00_ret = p00_e->p00_event[p00_pos]));
  P99_FPRINTF(stderr, "next event on %s, returns %s pos %s\n", (void*)p00_e, p00_ret, p00_pos);
  return p00_ret;
}

/**
 ** @brief Signal the event. @a p00_w
 **
 ** @related p99_event
 **/
P99_DEFARG_DOCU(p99_event_signal)
p99_inline
void p99_event_signal(p99_event volatile* p00_e, void * p00_w) {
  if (p00_e) {
    unsigned p00_ret = p99_iterator_signal(&p00_e->p00_it);
    p00_e->p00_event[p00_ret] = p00_w;
  }
}


/**
 ** @}
 **/


#endif
