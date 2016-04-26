/* This may look like nonsense, but it really is -*- mode: C -*-              */
/*                                                                            */
/* Except for parts copied from previous work and as explicitly stated below, */
/* the author and copyright holder for this work is                           */
/* (C) copyright  2013-2014 Jens Gustedt, INRIA, France                       */
/*                                                                            */
/* This file is free software; it is part of the P99 project.                 */
/* You can redistribute it and/or modify it under the terms of the QPL as     */
/* given in the file LICENSE. It is distributed without any warranty;         */
/* without even the implied warranty of merchantability or fitness for a      */
/* particular purpose.                                                        */
/*                                                                            */
#ifndef     P99_INIT_H_
# define    P99_INIT_H_

# include "p99_if.h"
# include "p99_callback.h"
# include "p99_hook.h"

/**
 ** @file
 **
 ** @brief Implement initialization functions that are executed early.
 **
 ** This can emulate gcc's constructor attribute and call init
 ** functions for variables with static storage duration.
 **
 ** @deprecated This constructor code is too much system dependent and
 ** too fragile. Don't use it in regular code, this might be removed
 ** from P99, soon.
 **
 ** The only place that uses this in P99 itself is for threads. There
 ** is an optional feature to replace main.
 **/

/**
 ** @addtogroup startup_hooks Hooks executed at startup
 ** @{
 **/

# define P00_INIT_1
# define P00_INIT_2
# define P00_INIT_3

# define P00_INIT_NR P99_PASTE3(P00_INIT_3, P00_INIT_2, P00_INIT_1)

# define P00_INIT_FUNCTION(NR)  P99_IF_EMPTY(NR)(P99_PASTE2(p00_init_function_, P00_INIT_NR))(P99_PASTE2(p00_init_function_, NR))

# define P00_HAVE_INIT_FUNCTION(NR)  P99_IF_EMPTY(NR)(P99_PASTE2(p00_have_init_function_, P00_INIT_NR))(P99_PASTE2(p00_have_init_function_, NR))

# define P00_INIT_FUNC_VAR_S(_0, _1, I)                        \
P99_TENTATIVE_DEC(bool const, P00_HAVE_INIT_FUNCTION(I));      \
P99_TENTATIVE_DEC(p99_callback_el const, P00_INIT_FUNCTION(I))

P99_FOR(, P99_MAX_NUMBER, P00_SEP, P00_INIT_FUNC_VAR_S, P99_REP(P99_MAX_NUMBER,));

# define P00_INIT_TRIGGER_FUNCTION_1(_0, _1, I)                              \
do {                                                                         \
  if (P00_HAVE_INIT_FUNCTION(I)) p99_callback_el_call(P00_INIT_FUNCTION(I)); \
 } while (false)

# define P00_INIT_FUNCTION_(NAME, NR)                                                                         \
void NAME(void);                                                                                              \
P99_TENTATIVE_DEF(bool const, P00_HAVE_INIT_FUNCTION(NR)) = true;                                             \
P99_TENTATIVE_DEF(p99_callback_el const, P00_INIT_FUNCTION(NR)) = { .p00_void = { .p00_void_func = NAME, }, }

# ifdef P00_DOXYGEN
/**
 ** @brief Request that @a FUNC is to be called at initialization time
 ** with priority @a NR
 **
 ** @param FUNC must be compatible to a function pointer of type
 ** <code>void (*)(void)</code>
 **
 ** @param NR must be chosen uniquely in the range 0
 ** .. ::P99_MAX_NUMBER. It can be omitted, in which case a low valued
 ** number is provided.
 **
 ** @warning To ensure that @a NR is unique the file "p99_init.h" must
 ** be included before any usage of ::P99_INIT_FUNCTION_DECLARE
 **
 ** The mechanism that ensures this feature is relatively fragile. You
 ** should in particular ensure that the compilation unit that
 ** contains ::p99_init_main (or @c main if you intercept @c main) see
 ** all such calls to ::P99_INIT_FUNCTION_DECLARE that are used by the
 ** program.
 **
 ** This works by initializing a bunch of @c static @c const variables
 ** with function and data pointers. The order in which these then are
 ** processed depends on the file inclusion order. So if you do not
 ** use the @a NR you should not rely on a particular order. If you
 ** need initialization dependencies between "modules" (= compilation
 ** units) you should use
 **
 ** @code
 ** // ***** file module1.h
 ** P99_DECLARE_ONCE_CHAIN(module1);
 ** // always include this immediately before, even several times
 ** #include "p99_init.h"
 ** P99_INIT_FUNCTION_DECLARE(module1_trigger);
 **
 ** // ***** file module2.c
 ** P99_DEFINE_ONCE_CHAIN(module1) {
 **   // here initialize some global variables e.g
 ** }
 ** // always include this immediately before, even several times
 ** #include "p99_init.h"
 ** void module1_trigger(void) {
 **   P99_INIT_CHAIN(module1);
 ** }
 **
 **
 ** // ***** file module2.h
 ** P99_DECLARE_ONCE_CHAIN(module2);
 ** // always include this immediately before, even several times
 ** #include "p99_init.h"
 ** P99_INIT_FUNCTION_DECLARE(module2_trigger);
 **
 ** // ***** file module2.c
 ** // module2 depends upon module1 being properly initialized
 ** P99_DEFINE_ONCE_CHAIN(module2, module1) {
 **   // here initialize some global variables e.g
 ** }
 ** // always include this immediately before, even several times
 ** #include "p99_init.h"
 ** void module2_trigger(void) {
 **   P99_INIT_CHAIN(module2);
 ** }
 ** @endcode
 **
 ** @see P99_INIT_VARIABLE for a similar mechanism with that receive a
 ** pointer argument and are compatible with
 ** <code>void (*)(void*)</code>.
 **/
#  define P99_INIT_FUNCTION_DECLARE(FUNC, NR)
# else
#  define P99_INIT_FUNCTION_DECLARE(...) P99_IF_EQ(P99_NARG(__VA_ARGS__), 2)(P00_INIT_FUNCTION_(__VA_ARGS__))(P00_INIT_FUNCTION_(__VA_ARGS__,))
# endif

# define P00_INIT_VARIABLE(NAME, FUNC, NR)                      \
P99_TENTATIVE_DEF(p99_callback_el const, P00_INIT_FUNCTION(NR)) \
= {                                                             \
  .p00_voidptr_func = (FUNC),                                   \
  .p00_void = {                                                 \
    .p00_arg = &(NAME),                                         \
  },                                                            \
}

# ifdef P00_DOXYGEN
/**
 ** @brief Request that @a FUNC is to be called with argument
 ** <code>&(NAME)</code> at initialization time with priority @a NR
 **
 ** @param NAME must be an object with static storage duration. Its
 ** address is taken as a compile time constant expression.
 **
 ** @param FUNC must be compatible to a function pointer of type
 ** <code>void (*)(void*)</code> and will be called equivalent to
 ** <code>FUNC(&(NAME))</code>.
 **
 ** @param NR must be chosen uniquely in the range 0
 ** .. ::P99_MAX_NUMBER. It can be omitted, in which case a low valued
 ** number is provided.
 **
 ** @warning To ensure that @a NR is unique the file "p99_init.h" must
 ** be included before any usage of ::P99_INIT_FUNCTION_DECLARE
 **
 ** @see P99_INIT_FUNCTION_DECLARE for the mechanism that is used to
 ** implement this feature.
 **/
#  define P99_INIT_VARIABLE(NAME, FUNC, NR)
# else
#  define P99_INIT_VARIABLE(...) P99_IF_EQ(P99_NARG(__VA_ARGS__), 3)(P00_INIT_VARIABLE(__VA_ARGS__))(P00_INIT_VARIABLE(__VA_ARGS__,))
# endif

# if defined(P00_DOXYGEN)
/**
 ** @brief Macro to control compilation of initialization features
 **
 ** @see P99_MAIN_INTERCEPT
 **/
#  define P99_INTERCEPT_MAIN
# endif

# if defined(P99_INTERCEPT_MAIN) || defined(P00_DOXYGEN)

/**
 ** @brief Intercept the @c main function before it is called and run
 ** some startup code
 **
 ** This is a fragile method to intercept @c main, e.g to act on @c
 ** argc and @c argv before the program run enters user code. This is
 ** only fully active when the program is compiled with the macro
 ** ::P99_INTERCEPT_MAIN enabled. If it is not enabled you can still
 ** call your defined function through the use of the macro
 ** ::P99_INIT_TRIGGER.
 **
 ** A complete example would like the one defined here in this file:
 **
 ** @code
 ** P99_MAIN_INTERCEPT(p99_init_main) {
 **   // here do something reasonable
 ** }
 **
 ** # if defined(P99_INTERCEPT_MAIN)
 ** #  undef main
 ** #  define main p99_init_main
 ** # endif
 **
 ** int main(int argc, char *argv[]) {
 **  ...
 **  P99_INIT_TRIGGER(NAME, &argc, &argv);
 **  ...
 **  return EXIT_SUCCESS;
 ** }
 ** @endcode
 **
 ** This has three different parts. First comes the declaration of the
 ** function body that is to be executed when @c main is intercepted.
 ** Then comes a @b re-definition of @c main. As you can guess, this
 ** will rename the user function to @c p99_init_main in this example.
 **
 ** @remark The call to the ::P99_INIT_TRIGGER function is optional if
 ** compiled with ::P99_INTERCEPT_MAIN.
 **
 ** @warning If the program is compiled ::P99_INTERCEPT_MAIN the @c
 ** return is mandatory: for the compiler the user @c main is not a @c
 ** main in the sense of the C standard anymore.
 **/
#  define P99_MAIN_INTERCEPT(NAME)                                         \
int NAME(int, char*[]);                                                    \
P99_WEAK(P99_PASTE2(p00_init_func_, NAME))                                 \
 void P99_PASTE2(p00_init_func_, NAME)(int*, char***);                     \
P99_WEAK(main)                                                             \
int main(int p00_argc, char**p00_argv) {                                   \
  fprintf(stderr, "%s: intercepting " P99_STRINGIFY(NAME) "\n", __func__); \
  P99_PASTE2(p00_init_func_, NAME)(&p00_argc, &p00_argv);                  \
  return NAME(p00_argc, p00_argv);                                         \
}                                                                          \
P99_WEAK(P99_PASTE2(p00_init_func_, NAME))                                 \
void P99_PASTE2(p00_init_func_, NAME)(int * p00_argc, char***p00_argv)

#  define P99_INIT_TRIGGER(NAME, ARGC, ARGV) P99_NOP

# else

#  define P99_MAIN_INTERCEPT(NAME)                                     \
P99_WEAK(P99_PASTE2(p00_init_func_, NAME))                             \
void P99_PASTE2(p00_init_func_, NAME)(int * p00_argc, char***p00_argv)

#  define P99_INIT_TRIGGER(NAME, ARGC, ARGV) P99_PASTE2(p00_init_func_, NAME)((ARGC), (ARGV))

# endif

# if defined(P99_AT_LOAD_DECLARE)

P99_WEAK(p99_init_main)
P99_AT_LOAD_DECLARE(p99_init_main);

P99_WEAK(p99_init_main)
P99_CONST_FUNCTION
P99_AT_LOAD_DEFINE(p99_init_main) {
  P99_FOR(, P99_MAX_NUMBER, P00_SEP, P00_INIT_TRIGGER_FUNCTION_1, P99_REP(P99_MAX_NUMBER,));
}

P99_CONST_FUNCTION
p99_inline
void p00_init_func_p99_init_main(int * p00_argc, char***p00_argv) {
  P99_UNUSED(p00_argc);
  P99_UNUSED(p00_argv);
}

# else

#  warning "no native load time launcher found, trying to intercept main"

P99_MAIN_INTERCEPT(p99_init_main) {
  P99_FOR(, P99_MAX_NUMBER, P00_SEP, P00_INIT_TRIGGER_FUNCTION_1, P99_REP(P99_MAX_NUMBER,));
  P99_FOR(, P99_MAX_NUMBER, P00_SEP, P00_INIT_TRIGGER_FUNCTION_2, P99_REP(P99_MAX_NUMBER,));
}

#  if defined(P99_INTERCEPT_MAIN)
#   undef main
#   define main p99_init_main
#  endif
# endif


/**
 ** @}
 **/

#endif

#if P99_PASTE2(P00_INIT_1, 0) == 0
# undef P00_INIT_1
# define P00_INIT_1 1
#elif P00_INIT_1 == 1
# undef P00_INIT_1
# define P00_INIT_1 2
#elif P00_INIT_1 == 2
# undef P00_INIT_1
# define P00_INIT_1 3
#elif P00_INIT_1 == 3
# undef P00_INIT_1
# define P00_INIT_1 4
#elif P00_INIT_1 == 4
# undef P00_INIT_1
# define P00_INIT_1 5
#elif P00_INIT_1 == 5
# undef P00_INIT_1
# define P00_INIT_1 6
#elif P00_INIT_1 == 6
# undef P00_INIT_1
# define P00_INIT_1 7
#elif P00_INIT_1 == 7
# undef P00_INIT_1
# define P00_INIT_1 8
#elif P00_INIT_1 == 8
# undef P00_INIT_1
# define P00_INIT_1 9
#elif P00_INIT_1 == 9
# undef P00_INIT_1
# define P00_INIT_1 0
# if P99_PASTE2(P00_INIT_2, 0) == 0
#  undef P00_INIT_2
#  define P00_INIT_2 1
# elif P00_INIT_2 == 1
#  undef P00_INIT_2
#  define P00_INIT_2 2
# elif P00_INIT_2 == 2
#  undef P00_INIT_2
#  define P00_INIT_2 3
# elif P00_INIT_2 == 3
#  undef P00_INIT_2
#  define P00_INIT_2 4
# elif P00_INIT_2 == 4
#  undef P00_INIT_2
#  define P00_INIT_2 5
# elif P00_INIT_2 == 5
#  undef P00_INIT_2
#  define P00_INIT_2 6
# elif P00_INIT_2 == 6
#  undef P00_INIT_2
#  define P00_INIT_2 7
# elif P00_INIT_2 == 7
#  undef P00_INIT_2
#  define P00_INIT_2 8
# elif P00_INIT_2 == 8
#  undef P00_INIT_2
#  define P00_INIT_2 9
# elif P00_INIT_2 == 9
#  undef P00_INIT_2
#  define P00_INIT_2 0
#  if P99_PASTE2(P00_INIT_3, 0) == 0
#   undef P00_INIT_3
#   define P00_INIT_3 1
#  elif P00_INIT_3 == 1
#   undef P00_INIT_3
#   define P00_INIT_3 2
#  elif P00_INIT_3 == 2
#   undef P00_INIT_3
#   define P00_INIT_3 3
#  elif P00_INIT_3 == 3
#   undef P00_INIT_3
#   define P00_INIT_3 4
#  elif P00_INIT_3 == 4
#   undef P00_INIT_3
#   define P00_INIT_3 5
#  elif P00_INIT_3 == 5
#   undef P00_INIT_3
#   define P00_INIT_3 6
#  elif P00_INIT_3 == 6
#   undef P00_INIT_3
#   define P00_INIT_3 7
#  elif P00_INIT_3 == 7
#   undef P00_INIT_3
#   define P00_INIT_3 8
#  elif P00_INIT_3 == 8
#   undef P00_INIT_3
#   define P00_INIT_3 9
#  elif P00_INIT_3 == 9
#   error "more than 999 init functions, compilation aborted"
#  endif
# endif
#endif

#if P00_INIT_NR > P99_MAX_NUMBER
# error "more init functions than supported through P99_MAX_NUMBER, compilation aborted"
#endif
