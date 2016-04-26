/* This may look like nonsense, but it really is -*- mode: C -*-              */
/*                                                                            */
/* Except for parts copied from previous work and as explicitly stated below, */
/* the authors and copyright holders for this work are as follows:            */
/* (C) copyright  2011-2014 Jens Gustedt, INRIA, France                       */
/* (C) copyright  2012 William Morris                                         */
/*                                                                            */
/* This file is free software; it is part of the P99 project.                 */
/* You can redistribute it and/or modify it under the terms of the QPL as     */
/* given in the file LICENSE. It is distributed without any warranty;         */
/* without even the implied warranty of merchantability or fitness for a      */
/* particular purpose.                                                        */
/*                                                                            */
#ifndef P99_THREADS_H
#define P99_THREADS_H 1

#include "p99_try.h"
#include "p99_tss.h"

#if p99_has_feature(threads_h)
# include <threads.h>
#elif defined(_XOPEN_SOURCE) || defined(_POSIX_C_SOURCE)
# include "p99_threads_posix.h"
#else
# error "no suitable thread implementation found"
#endif

#ifndef ONCE_FLAG_INIT
typedef struct p99_once_flag once_flag;
#define ONCE_FLAG_INIT P99_ONCE_FLAG_INIT
#define call_once p99_call_once
#endif

typedef struct p99_once_flag p99_once_flag;

enum p00_once {
  p00_once_uninit = 0,
  p00_once_started,
  p00_once_finished,
};

/**
 ** @brief complete object type that holds a flag for use by
 ** ::p99_call_once
 **
 ** From the wording of the standard it is not clear whether a variable of
 ** this type @b must be initialized by means of ::P99_ONCE_FLAG_INIT. The
 ** corresponding POSIX structure requires the analog.
 **
 ** Therefore we don't use the POSIX structure, here, but cook this
 ** ourselves with atomic variables. In this way we can guarantee that a
 ** ::p99_once_flag that is initialized by the default initializer always
 ** has the correct state.
 */
struct p99_once_flag {
  union {
    enum p00_once p00_done;
    enum p00_once volatile p00_vdone;
  } p00_done;
  thrd_t p00_id;
  void (*const p00_init)(void);
  atomic_flag p00_flg;
};

P00_DOCUMENT_TYPE_ARGUMENT(P99_DECLARE_INIT_ONCE, 0)
P00_DOCUMENT_IDENTIFIER_ARGUMENT(P99_DECLARE_INIT_ONCE, 1)
P00_DOCUMENT_IDENTIFIER_ARGUMENT(P99_DECLARE_INIT_ONCE, 2)
#define P99_DECLARE_INIT_ONCE(T, NAME, ARG)                     \
/** @remark wrapper type around a T that is initialized once */ \
struct NAME {                                                   \
  p99_once_flag p00_once;                                       \
  T p00_val;                                                    \
};                                                              \
P99_DECLARE_STRUCT(NAME);                                       \
p99_inline                                                      \
void P99_PASTE3(p00_, NAME, _init_func)(T* ARG);                \
p99_inline                                                      \
void P99_PASTE3(p00_, NAME, _init_once)(NAME* ARG) {            \
  if (P99_UNLIKELY(!ARG->p00_once.p00_done.p00_done))           \
    do {                                                        \
      P99_SPIN_EXCLUDE(&ARG->p00_once.p00_flg) {                \
        if (!ARG->p00_once.p00_done.p00_vdone) {                \
          P99_PASTE3(p00_, NAME, _init_func)(&ARG->p00_val);    \
          ARG->p00_once.p00_done.p00_vdone = true;              \
        }                                                       \
      }                                                         \
    } while (!ARG->p00_once.p00_done.p00_vdone);                \
}                                                               \
p99_inline                                                      \
void P99_PASTE3(p00_, NAME, _init_func)(T* ARG)

#define P99_INIT_ONCE(NAME, VARP) P99_PASTE3(p00_, NAME, _init_once)(VARP)

#define p00_call_once_2(FLAG, FUNC)                                          \
do {                                                                         \
  p99_once_flag *p00Mflag = (FLAG);                                          \
  if (P99_UNLIKELY(p00Mflag->p00_done.p00_done != p00_once_finished))        \
    do {                                                                     \
      atomic_flag_lock(&p00Mflag->p00_flg);                                  \
      switch (p00Mflag->p00_done.p00_vdone) {                                \
        /* we are doing the initialization */                                \
      case p00_once_uninit:                                                  \
        p00Mflag->p00_done.p00_done = 1;                                     \
        p00Mflag->p00_id = thrd_current();                                   \
        atomic_flag_unlock(&p00Mflag->p00_flg);                              \
        FUNC();                                                              \
        p00Mflag->p00_done.p00_done = 2;                                     \
        break;                                                               \
      case p00_once_started:                                                 \
        if (thrd_equal(p00Mflag->p00_id, thrd_current())) {                  \
          /* we are called recursively, abandon and return */                \
          atomic_flag_unlock(&p00Mflag->p00_flg);                            \
          p00Mflag = 0;                                                      \
          break;                                                             \
        }                                                                    \
        /* otherwise fall through */                                         \
      case p00_once_finished:                                                \
        atomic_flag_unlock(&p00Mflag->p00_flg);                              \
        break;                                                               \
      }                                                                      \
    } while (p00Mflag && p00Mflag->p00_done.p00_vdone != p00_once_finished); \
 } while (false)

p99_inline
void p00_call_once_1(p99_once_flag *p00_flag) {
  p00_call_once_2(p00_flag, p00_flag->p00_init);
}

#define p00_call_once_3(FLAG, FUNC, ...)                                     \
do {                                                                         \
  p99_once_flag *p00Mflag = (FLAG);                                          \
  if (P99_UNLIKELY(p00Mflag->p00_done.p00_done != p00_once_finished))        \
    do {                                                                     \
      atomic_flag_lock(&p00Mflag->p00_flg);                                  \
      switch (p00Mflag->p00_done.p00_vdone) {                                \
        /* we are doing the initialization */                                \
      case p00_once_uninit:                                                  \
        p00Mflag->p00_done.p00_done = 1;                                     \
        p00Mflag->p00_id = thrd_current();                                   \
        atomic_flag_unlock(&p00Mflag->p00_flg);                              \
        FUNC(__VA_ARGS__);                                                   \
        p00Mflag->p00_done.p00_done = 2;                                     \
        break;                                                               \
      case p00_once_started:                                                 \
        if (thrd_equal(p00Mflag->p00_id, thrd_current())) {                  \
          /* we are called recursively, abandon and return */                \
          atomic_flag_unlock(&p00Mflag->p00_flg);                            \
          p00Mflag = 0;                                                      \
          break;                                                             \
        }                                                                    \
        /* otherwise fall through */                                         \
      case p00_once_finished:                                                \
        atomic_flag_unlock(&p00Mflag->p00_flg);                              \
        break;                                                               \
      }                                                                      \
    } while (p00Mflag && p00Mflag->p00_done.p00_vdone != p00_once_finished); \
 } while (false)

#define p00_call_once(N, ...)                                  \
P99_IF_EQ_1(N)                                                 \
(p00_call_once_1(__VA_ARGS__))                                 \
(P99_IF_EQ_2(N)                                                \
 (p00_call_once_2(__VA_ARGS__))                                \
 (p00_call_once_3(__VA_ARGS__)))

/**
 ** @brief Call a function @a FUNC exactly once, optionally
 ** providing it with argument @a ARG
 **
 ** This is an extension of the standard function ::call_once.
 **
 ** - If @a ARG is given, it must be compatible with type @c void* and is
 **   passed to @a FUNC as an argument. In this case @a FUNC must have
 **   the prototype <code>void FUNC(void*)</code>.
 **
 ** - If @a ARG is omitted @a FUNC should have the prototype
 **   <code>void FUNC(void)</code>, i.e not take any argument.
 **
 ** - If the field @c p00_init is initialized with an appropriate
 **   function, the @a FUNC can also be omitted and @c p00_init is then
 **   called instead.
 **
 ** @remark The @a FLAG is only protected by an
 ** ::atomic_flag. Therefore the functions that are passed to this
 ** should be nice and short.
 **
 ** @remark These functions are protected against recursion and should
 ** not deadlock when they are confronted with cyclic
 ** dependencies. But obviously, the order in which such a cycle is
 ** taken is not predictable.
 **
 ** @see p99_once_flag
 **/
#ifdef P00_DOXYGEN
#define p99_call_once(FLAG, FUNC, ARG)
#else
#define p99_call_once(...) p00_call_once(P99_NARG(__VA_ARGS__), __VA_ARGS__)
#endif

#ifdef P00_DOXYGEN
/**
 ** @brief Define a function that will be called exactly once by
 ** <code>P99_INIT_CHAIN(T)</code>.
 **
 ** The function has a prototype of <code>void someFunctionName(void)</code>.
 **
 ** @a T can be any valid identifier, the real function name will
 ** be mangled such that it will not clash with an existing name.
 **
 ** The ... list (optional) can be used to give a list of dependencies
 ** from other ::P99_INIT_CHAIN functions.
 ** @code
 ** P99_DEFINE_ONCE_CHAIN(toto) {
 **  // initialize some shared ressource
 ** }
 **
 ** P99_DEFINE_ONCE_CHAIN(tutu, toto) {
 **   // empty
 ** }
 ** @endcode
 **
 ** This will ensure that <code>P99_INIT_CHAIN(toto)</code> is always
 ** triggered by <code>P99_INIT_CHAIN(tutu)</code> and is run before we run
 ** the function @c tutu itself. As shown above in the example, many functions
 ** will be empty, serving just to ensure that all dynamic
 ** dependencies are initialized in the right order.
 ** @see P99_DECLARE_ONCE_CHAIN
 ** @see P99_INIT_CHAIN
 **/
#define P99_DEFINE_ONCE_CHAIN(T, ...)                          \
p99_once_flag p99_ ## T ## _once;                              \
void p00_ ## T ## _once_init(void)
#else
#define P99_DEFINE_ONCE_CHAIN(...)                             \
P99_IF_ELSE(P99_HAS_COMMA(__VA_ARGS__))                        \
 (P00_P99_DEFINE_ONCE_CHAIN_1(__VA_ARGS__))                    \
 (P00_P99_DEFINE_ONCE_CHAIN_0(__VA_ARGS__))
#endif

#define P00_P99_DEFINE_ONCE_CHAIN_0(T)                         \
static void P99_PASTE3(p00_, T, _once_init)(void);             \
p99_once_flag P99_PASTE3(p99_, T, _once) = {                   \
  .p00_init = P99_PASTE3(p00_, T, _once_init),                 \
};                                                             \
static void P99_PASTE3(p00_, T, _once_init)(void)

#define P00_ONCE_INIT(_0, T, _2) P99_INIT_CHAIN(T)

#define P00_P99_DEFINE_ONCE_CHAIN_1(T, ...)                              \
static void P99_PASTE3(p00_, T, _once_init0)(void);                      \
static void P99_PASTE3(p00_, T, _once_init)(void) {                      \
  P99_FOR(, P99_NARG(__VA_ARGS__), P00_SEP, P00_ONCE_INIT, __VA_ARGS__); \
  /* fprintf(stderr, "Initializing " #T "\n");*/                         \
  P99_PASTE3(p00_, T, _once_init0)();                                    \
 }                                                                       \
struct p99_once_flag P99_PASTE3(p99_, T, _once) = {                      \
  .p00_init = P99_PASTE3(p00_, T, _once_init),                           \
};                                                                       \
static void P99_PASTE3(p00_, T, _once_init0)(void)

/**
 ** @brief Declare the symbols that are needed for the macro
 ** ::P99_INIT_CHAIN().
 **
 ** @param T should be unique for each use of this macro.
 ** @see P99_INIT_CHAIN
 ** @see P99_DEFINE_ONCE_CHAIN
 **/
#define P99_DECLARE_ONCE_CHAIN(T)                              \
extern p99_once_flag P99_PASTE3(p99_, T, _once)

/**
 ** @brief Ensure that the function that was defined with
 ** ::P99_DEFINE_ONCE_CHAIN has been called exactly once before proceeding.
 **
 ** Such a call could be placed at the beginning of a user function to
 ** ensure that a shared resource is always initialized before its
 ** use. A better strategy though would be to call ::P99_INIT_CHAIN
 ** from @c main, e.g., before any threads of the application are
 ** started, or through the mechanism provided by :::P99_INIT_FUNCTION.
 ** @see P99_DECLARE_ONCE_CHAIN
 ** @see P99_DEFINE_ONCE_CHAIN
 **/
#define P99_INIT_CHAIN(T)                                                       \
p99_call_once(&P99_PASTE3(p99_, T, _once), P99_PASTE3(p99_, T, _once).p00_init)

/**
 ** @brief Protect the following block or statement with @c
 ** mtx_t @a MUT.
 **
 ** @see P99_CRITICAL for a tool that uses a spinlock that is
 ** allocated behind the scene.
 **
 ** This does some rudimentary error checking for the result of
 ** locking. If an error occurs the whole block and any other
 ** enclosing blocks that are protected with P99_UNWIND_PROTECT are
 ** aborted.
 **/
P99_BLOCK_DOCUMENT
P00_DOCUMENT_PERMITTED_ARGUMENT(P99_MUTUAL_EXCLUDE, 0)
#define P99_MUTUAL_EXCLUDE(MUT) P00_MUTUAL_EXCLUDE(MUT, P99_UNIQ(mut))

# if !P99_SIMPLE_BLOCKS
#  define P00_MUTUAL_EXCLUDE(MUT, UNIQ)                                          \
P00_BLK_START                                                                    \
P00_BLK_DECL(int, p00_errNo, 0)                                                  \
P99_GUARDED_BLOCK(mtx_t*,                                                        \
                  UNIQ,                                                          \
                  &(MUT),                                                        \
                  (void)(P99_UNLIKELY(p00_errNo = mtx_lock(UNIQ))                \
                         && (fprintf(stderr,                                     \
                                     __FILE__ ":"                                \
                                     P99_STRINGIFY(__LINE__) ": lock error for " \
                                     P99_STRINGIFY(MUT) ", %s\n",                \
                                     strerror(p00_errNo)), 1)                    \
                         && (UNIQ = 0, 1)                                        \
                         && (P99_UNWIND(-1), 1)                                  \
                         ),                                                      \
                  (void)(UNIQ                                                    \
                         && mtx_unlock(UNIQ)))
# else
#  define P00_MUTUAL_EXCLUDE(MUT, UNIQ)                        \
P00_BLK_START                                                  \
P00_BLK_DECL(mtx_t*, UNIQ, &(MUT))                             \
P00_BLK_BEFAFT(mtx_lock(UNIQ), mtx_unlock(UNIQ))
# endif

p99_inline thrd_t* thrd_t_init(thrd_t *p00_id) {
  if (p00_id) {
    *p00_id = P99_LVAL(thrd_t const);
  }
  return p00_id;
}

P99_CONST_FUNCTION
p99_inline void thrd_t_destroy(thrd_t *p00_id) {
  /* special care for bogus warning given by icc */
  (void)p00_id;
}

p99_inline
char const* thrd2str(char *p00_buf, thrd_t p00_id) {
  unsigned char *p00_p = (unsigned char*)&p00_id;
  for (size_t p00_i = 0; p00_i < sizeof(thrd_t); ++p00_i) {
    snprintf(p00_buf + 2*p00_i, 3, "%02X", p00_p[p00_i]);
  }
  return p00_buf;
}

#define THRD2STR(ID) thrd2str((char[1 + sizeof(thrd_t) * 2]){0}, (ID))


#endif
