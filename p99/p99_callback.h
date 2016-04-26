/* This may look like nonsense, but it really is -*- mode: C -*-              */
/*                                                                            */
/* Except for parts copied from previous work and as explicitly stated below, */
/* the authors and copyright holders for this work are as follows:            */
/* (C) copyright  2012-2014 Jens Gustedt, INRIA, France                       */
/* (C) copyright  2012 William Morris                                         */
/*                                                                            */
/* This file is free software; it is part of the P99 project.                 */
/* You can redistribute it and/or modify it under the terms of the QPL as     */
/* given in the file LICENSE. It is distributed without any warranty;         */
/* without even the implied warranty of merchantability or fitness for a      */
/* particular purpose.                                                        */
/*                                                                            */
#ifndef P99_CALLBACK_H
#define P99_CALLBACK_H 1

# include "p99_lifo.h"

/**
 ** @addtogroup callbacks simple callbacks with or without void* argument
 **
 ** @{
 **/

P99_DECLARE_STRUCT(p99_callback_el);
P99_POINTER_TYPE(p99_callback_el);
#ifndef P00_DOXYGEN
P99_LIFO_DECLARE(p99_callback_el_ptr);
typedef P99_LIFO(p99_callback_el_ptr) p99_callback_stack;
#else
int p00_doxygen_is_confused(void) {}
/**
 ** @brief A data structure to register callbacks
 **/
struct p99_callback_stack { };
typedef struct p99_callback_stack p99_callback_stack;
#endif

/**
 ** @brief Function type for a callback without arguments
 ** @related p99_callback_stack
 **/
typedef void p99_callback_void_func(void);

/**
 ** @brief Function type for a callback with @c void* argument
 ** @related p99_callback_stack
 **/
typedef void p99_callback_voidptr_func(void*);

struct p99_callback_el {
  p99_callback_el_ptr p99_lifo;
  p99_callback_voidptr_func * p00_voidptr_func;
  union {
    p99_callback_void_func * p00_void_func;
    void* p00_arg;
  } p00_void;
};


p99_inline
p99_callback_el* p99_callback_el_init(p99_callback_el * p00_obj,
                                      p99_callback_voidptr_func* p00_voidptr_func,
                                      p99_callback_void_func* p00_void_func,
                                      void* p00_arg
                                     ) {
  if (p00_obj) {
    if (p00_voidptr_func)
      *p00_obj = (p99_callback_el) {
      .p00_voidptr_func = p00_voidptr_func,
      .p00_void = {
        .p00_arg = p00_arg,
      },
    };
    else
      *p00_obj = (p99_callback_el) { .p00_void = { .p00_void_func = p00_void_func, }, };
  }
  return p00_obj;
}

#define p99_callback_el_init_1(FUNC)                                          \
P99_GENERIC((&*FUNC),                                                         \
            ,                                                                 \
            (p99_callback_voidptr_func*, (p99_callback_voidptr_func*)(FUNC)), \
            (p99_callback_void_func*, (p99_callback_voidptr_func*)0)          \
            )


#define p99_callback_el_init_2(FUNC)                                    \
P99_GENERIC((&*FUNC),                                                   \
            ,                                                           \
            (p99_callback_void_func*, (p99_callback_void_func*)(FUNC)), \
            (p99_callback_voidptr_func*, (p99_callback_void_func*)0)    \
            )

#define p99_callback_el_init_(OBJ, FUNC, ARG)                                                \
p99_callback_el_init((OBJ), p99_callback_el_init_1(FUNC), p99_callback_el_init_2(FUNC), ARG)


#define p99_callback_el_init(...)                              \
P99_IF_LT(P99_NARG(__VA_ARGS__), 3)                            \
(p99_callback_el_init_(__VA_ARGS__, 0))                        \
(p99_callback_el_init_(__VA_ARGS__))


p99_inline
void p99_callback_el_call(p99_callback_el const p00_el) {
  if (p00_el.p00_voidptr_func) p00_el.p00_voidptr_func(p00_el.p00_void.p00_arg);
  else if (p00_el.p00_void.p00_void_func) p00_el.p00_void.p00_void_func();
}

p99_inline
p99_callback_el* p00_callback_push(p99_callback_stack* p00_l, p99_callback_el* p00_el) {
  if (p00_el) {
    P99_LIFO_PUSH(p00_l, p00_el);
  }
  return p00_el;
}

/**
 ** @brief Register a function as a callback on @a STCK
 **
 ** @param STCK should be of type ::p99_callback_stack*
 **
 ** The first of the arguments in the variable argument list should be
 ** a function pointer, either of type ::p99_callback_voidptr_func or
 ** ::p99_callback_void_func. In the first case a following argument,
 ** if any, should be a data pointer (i.e compatible to @c void*),
 ** which will be passed as parameter to the function. If no such
 ** argument is given the function is called with parameter @c 0.
 **
 ** This is as if there'd be two overloaded functions as
 ** @code
 ** p99_callback_push(p99_callback_stack*, p99_callback_voidptr_func*, void* = 0);
 ** p99_callback_push(p99_callback_stack*, p99_callback_void_func*);
 ** @endcode
 **
 ** @related p99_callback_stack
 ** @see p99_callback
 **/
#define P99_CALLBACK_PUSH(STCK, ...) p00_callback_push((STCK), P99_NEW(p99_callback_el, __VA_ARGS__))


/**
 ** @brief Call all functions that have been registered with @a
 ** p00_stck in reverse order of their registration and remove them
 ** from the stack
 **
 ** Functions of type ::p99_callback_voidptr_func will be called with
 ** the parameter that has been registered along with it. Functions of
 ** type ::p99_callback_void_func will be called without parameters.
 **
 ** All functions that have been registered with @a p00_stck are taken
 ** from the stack atomically and are executed in one batch by the
 ** same thread that runs ::p99_callback. Another function that would
 ** be registered with @a p00_stck by one of the callbacks would not
 ** be executed in the same batch.
 **
 ** @related p99_callback_stack
 ** @see P99_CALLBACK_PUSH to register a callback function
 **/
p99_inline
void p99_callback(p99_callback_stack* p00_stck) {
  for (p99_callback_el *head = P99_LIFO_CLEAR(p00_stck), *p00_el = head; p00_el; p00_el = head) {
    head = p00_el->p99_lifo;
    p99_callback_el const p00_cb = *p00_el;
    free(p00_el);
    p99_callback_el_call(p00_cb);
  }
}


/**
 ** @}
 **/

#endif
