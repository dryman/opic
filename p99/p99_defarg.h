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
#ifndef     P99_DEFARG_H_
# define    P99_DEFARG_H_

/**
 ** @file
 ** @brief Macros for default arguments to functions.
 ** @see default_arguments
 **/

#include "p99_map.h"
#include P99_ADVANCE_ID

/**
 ** @addtogroup code_augmenting C Programming facilities
 **
 ** Macros and functions in these groups are designed to ease
 ** everyday life. They concern initialization and heap allocation
 ** of variables, default arguments for functions (yes, this is C),
 ** "variadic" function that magically receive the length of their
 ** argument list...
 **
 ** Most of this is implemented with macros. But we might also define
 ** some helper functions. If so they are small and defined as @c
 ** static @c inline, @c negligible, say.
 ** @{
 **/

#define P00_code_augmenting


/**
 ** @addtogroup default_arguments Default arguments and types for functions
 **
 ** @brief As a C++ like feature, this series of macros can be used to
 ** provide default arguments to functions and also to improve type
 ** safety for variadic functions.
 **
 ** This goes in several parts.
 **
 **   - Use ::P99_PROTOTYPE to define a prototype for your function.
 **   - define a macro that just calls ::P99_CALL_DEFARG as a
 **       replacement for your function
 **   - declare the default arguments with ::P99_DECLARE_DEFARG
 **   - generate the necessary external symbols with
 **       ::P99_DEFINE_DEFARG
 **
 ** Another feature that is provided here is a macro that allows you
 ** to prescribe a certain type to the arguments of a variadic
 ** function. In plain C these are dangerous, since C cannot guess the
 ** type that the implementation of the function
 ** expects. ::P99_CALL_VA_ARG may be used to overcome this problem.
 ** @{
 **/


#ifdef P00_DOXYGEN
# define P99_CALL_DEFARG(NAME, M, ...) NAME(__VA_ARGS__)
# define P99_CALL_DEFARG_LIST(NAME, M, ...) __VA_ARGS__
#else
P00_DOCUMENT_NUMBER_ARGUMENT(P99_CALL_DEFARG, 1)
# define P99_CALL_DEFARG(NAME, M, ...) NAME(P99_CALL_DEFARG_LIST(NAME, M, __VA_ARGS__))

P00_DOCUMENT_NUMBER_ARGUMENT(P99_CALL_DEFARG_LIST, 1)
# define P99_CALL_DEFARG_LIST(NAME, M, ...)                    \
P99_IF_EQ(0,M)                                                 \
(__VA_ARGS__)                                                  \
(P99_IF_EMPTY(__VA_ARGS__)                                     \
 (P00_DEFARGS(NAME, M, P99_PASTE2(NAME,_defarg_0)()))          \
 (P00_DEFARGS(NAME, M, __VA_ARGS__))                           \
 )
#endif


/**
 ** @def P99_CALL_DEFARG
 ** @brief Define a replacement macro for functions that can provide
 ** default arguments to the underlying real function.
 **
 ** This macro may be used for `overloading' system functions or
 ** functions that you define yourself. It is easiest to explain
 ** this with an example. The system function @c pthread_mutex_init is
 ** defined as follows:
 **
 ** @code
 ** int pthread_mutex_init(pthread_mutex_t *mut, pthread_mutexattr_t* attr);
 ** @endcode
 **
 ** Here the second argument is used to specify an
 ** `attribute' to the mutex @c mut. Most people don't use that
 ** functionality and therefore @c pthread_mutex_init accepts a null
 ** pointer constant
 ** as a replacement for @c attr. This might be annoying since the
 ** focus of the syntax is on the exception rather than on the main use: the
 ** programmer always has to remember this particular special case and
 ** give explicit @c 0's.
 **
 ** The following lines heal this.
 **
 ** @code
 ** P99_PROTOTYPE(int, pthread_mutex_init, pthread_mutex_t*, pthread_mutexattr_t const*);
 ** #define pthread_mutex_init(...) P99_CALL_DEFARG(pthread_mutex_init, 2, __VA_ARGS__)
 ** P99_DECLARE_DEFARG(pthread_mutex_init, , (pthread_mutexattr_t*)0);
 ** @endcode
 **
 ** This declares a macro @c pthread_mutex_init that resolves to the call of
 ** a real function to initialize a @c pthread_mutexattr_t*. If invoked
 ** with two arguments or more, the macro expansion just results in
 ** the usual call to the function.
 **
 ** If the initialization value for argument 1 is omitted (arguments
 ** count from 0) the default value of a null pointer constant is used. Valid use is
 **
 ** @code
 ** static pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;
 ** static pthread_mutexattr_t attr;
 ** .
 ** pthread_mutex_init(&mut, &attr); // full specification with attributes
 ** pthread_mutex_init(&mut, 0);     // still a valid form
 **
 ** // easy variant for everyday use, equivalent to the previous one
 ** pthread_mutex_init(&mut);
 **
 ** // Also function pointers can still be taken.
 ** int (*myFunc)(pthread_mutex_t *, pthread_mutexattr_t*) = pthread_mutex_init;
 ** @endcode
 ** @param NAME is the function to provide with default argument features.
 ** @param M is the number of arguments that a full call to @a NAME takes.
 ** @see P99_DECLARE_DEFARG
 ** @see P99_PROTOTYPE
 **
 ** This macro is more flexible than the corresponding C++ feature of
 ** default arguments. It also lets you omit middle arguments.
 **
 ** More technically, for arguments that are omitted this just
 ** requires that NAME_defarg_M is defined for function @a NAME
 ** and @a M and that it is callable without arguments. This may just
 ** be a function (as implicitly defined by #P99_DECLARE_DEFARG) or a
 ** macro. For the first case everything the function refers to must
 ** be declared at the point of its definition. For the second case,
 ** the macro is evaluated at the place of the call and could refer to
 ** local variables or anything you like.
 **/

/**
 ** @def P99_CALL_DEFARG_LIST
 ** @brief Expand an argument list with default arguments.
 **
 ** @see P99_CALL_DEFARG for how this mechanism works. This macro
 ** just expands the argument list but doesn't add the function call
 ** itself.
 **/

/**
 ** @def P99_PROTOTYPE(RT, NAME, ...)
 ** @brief Define the prototype of function @a NAME.
 **
 ** @a RT is the return type of the function, and the remaining
 ** arguments list the types of the arguments. This is needed by
 ** #P99_DECLARE_DEFARG to determine the type of the functions that return
 ** default arguments.
 **
 ** @warning the list should only contain types and should not give
 ** names to the individual parameters.
 **
 ** @see P99_INSTANTIATE if your function is @c inline, in which case you
 ** also have to provide an external symbol for the function.
 **
 ** @remark This should be "macro-safe" that is if @a NAME is
 ** overloaded with a macro, ::P99_PROTOTYPE should still be able to
 ** instantiate the corresponding function.
 **/
P00_DOCUMENT_TYPE_ARGUMENT(P99_PROTOTYPE, 0)
P00_DOCUMENT_TYPE_ARGUMENT(P99_PROTOTYPE, 2)

#ifdef P00_DOXYGEN
#define P99_PROTOTYPE(...)
#else
#define P00_PROTOTYPE(RT, NAME, ...)                           \
  RT (NAME)(P99_IF_EMPTY(__VA_ARGS__)(void)(__VA_ARGS__));     \
  typedef RT P99_CAT2(NAME, _prototype_ret);                   \
  P99_TYPEDEFS(P99_CAT2(NAME, _prototype_), __VA_ARGS__)

#define P99_PROTOTYPE(...)                                     \
P99_IF_EQ_2(P99_NARG(__VA_ARGS__))                             \
(P00_PROTOTYPE(__VA_ARGS__, void))                             \
(P00_PROTOTYPE(__VA_ARGS__))
#endif

#if P99_COMPILER & P99_COMPILER_CLANG
#define P00_INSTANTIATE(RT, NAME, ...)                                                                   \
RT (*const P99_PASTE3(p00_, NAME, _pointer)[])(P99_IF_EMPTY(__VA_ARGS__)(void)(__VA_ARGS__)) = { NAME }; \
p00_instantiate RT (NAME)(P99_IF_EMPTY(__VA_ARGS__)(void)(__VA_ARGS__))
#else
#define P00_INSTANTIATE(RT, NAME, ...)                                  \
p00_instantiate RT (NAME)(P99_IF_EMPTY(__VA_ARGS__)(void)(__VA_ARGS__))
#endif

#ifdef P00_DOXYGEN
/**
 ** @brief Instantiate an inline function.
 **
 ** For functions that are declared inline in C99, the compiler doesn't generate an
 ** external symbol unless explicitly told to. But
 ** often you will need such an external symbol, e.g if you switch on
 ** debugging or if you pass a function pointer as a callback to
 ** another function.
 **
 ** The syntax for this feature is a bit crude and not all compilers
 ** agree upon the interpretation. Therefore we provide a wrapper that
 ** does just this.  Put such a call to ::P99_INSTANTIATE in exactly
 ** one .c file (compilation unit) of you liking. The external symbol
 ** will then be generated there.
 **
 ** @see P99_PROTOTYPE for the syntax of this macro.
 **
 ** @remark This should be "macro-safe" that is if @a NAME is
 ** overloaded with a macro, ::P99_INSTANTIATE should still be able to
 ** instantiate the corresponding function.
 **/
#define P99_INSTANTIATE(RT, NAME, ...) RT NAME(__VA_ARGS__)
#else
#define P99_INSTANTIATE(...)                                   \
P99_IF_EQ_2(P99_NARG(__VA_ARGS__))                             \
(P00_INSTANTIATE(__VA_ARGS__, void))                           \
(P00_INSTANTIATE(__VA_ARGS__))
#endif

#define P00_EXPR_FUNCTION(NAME, X, N)                                   \
P99_IF_EMPTY(X)                                                         \
()                                                                      \
(                                                                       \
 inline                                                                 \
 P99_PASTE3(NAME, _prototype_, N) P99_PASTE3(NAME, _defarg_, N)(void) { \
   P99_PASTE3(NAME, _prototype_, N) p00_ret = (X);                      \
   return p00_ret;                                                      \
 }                                                                      \
)

#define P00_DAFE(NAME, X, N)                                                       \
P99_IF_EMPTY(X)                                                                    \
(P99_MACRO_END(NAME, _boring_, N))                                                 \
(P99_INSTANTIATE(P99_PASTE3(NAME, _prototype_, N), P99_PASTE3(NAME, _defarg_, N)))

#define P00_DECLARE_DEFARG(NAME, N, ...)                       \
P99_FOR(NAME, N, P00_SER, P00_EXPR_FUNCTION, __VA_ARGS__)      \
P99_MACRO_END(NAME, _declare_defarg)

#ifdef P00_DOXYGEN
/**
 ** @brief Provide default arguments for macro @a NAME
 **
 ** Each element in the list must correspond to an expression that can
 ** be evaluated in the outer scope, just where this call is placed.
 ** In many cases they will be constant expressions such as @c 0, but they need not be so.
 **
 ** An empty argument, i.e nothing but an eventual comment, produces
 ** nothing. So no default argument will be provided for the
 ** corresponding position in the parameter list of @a NAME.
 **
 ** @see P99_PROTOTYPE on how to declare the prototype of a function
 ** @a NAME that can be used with this
 **
 ** @see P99_CALL_DEFARG on how to declare the macro @a NAME
 **
 ** @see rand48_t_init for a more sophisticated example with
 ** non-constant expressions.
 **/
#define P99_DECLARE_DEFARG(NAME, ...)
#else
#define P99_DECLARE_DEFARG(NAME, ...) P00_DECLARE_DEFARG(NAME, P99_NARG(__VA_ARGS__), __VA_ARGS__)
#endif

#define P00_DEFINE_DEFARG(NAME, N, ...)                        \
  P99_FOR(NAME, N, P00_SEP, P00_DAFE, __VA_ARGS__)

#ifdef P00_DOXYGEN
/**
 ** @brief Define the symbols that are declared through a
 ** corresponding call ::P99_DECLARE_DEFARG.
 **
 ** The argument list here should be exactly the same as for ::P99_DECLARE_DEFARG.
 **/
#define P99_DEFINE_DEFARG(NAME, ...)
#else
#define P99_DEFINE_DEFARG(NAME, ...) P00_DEFINE_DEFARG(NAME, P99_NARG(__VA_ARGS__), __VA_ARGS__)
#endif


#define P00_DARG(NAME, X, N) P99_IF_EMPTY(X)(P99_PASTE3(NAME, _defarg_, N)())(X)
#define P00__DEFARGS(NAME, N, ...) P99_FOR(NAME, N, P00_SEQ, P00_DARG, __VA_ARGS__)
#define P00_DEFARGS(NAME, N, ...) P00__DEFARGS(NAME, N, P99_IF_LT(P99_NARG(__VA_ARGS__),N) (__VA_ARGS__, P99_DUPL(P99_MINUS(N,P99_NARG(__VA_ARGS__)),)) (__VA_ARGS__))


/**
 ** @brief Provide a documentation section to a function defined with ::P99_CALL_DEFARG
 **/
#define P99_DEFARG_DOCU(NAME)                                                                                        \
/*! @remark NAME is actually implemented as a macro that helps to provide default arguments to the real function. */ \
/*! @see P99_CALL_DEFARG */                                                                                          \
/*! @see P99_DECLARE_DEFARG */


#define P00_VAARG_0(NAME, T) NAME
#define P00_VAARG_1(NAME, T) T

#define P00_VAARG(NAMET, X, I) P99_RVAL(P00_VAARG_1 NAMET, P99_IF_EMPTY(X)(P99_PASTE2(P00_VAARG_0 NAMET, _defarg)())(X))

#define P00_CALL_VA_ARG(NAME, T, ...) P99_FOR((NAME, T), P99_NARG(__VA_ARGS__), P00_SEQ, P00_VAARG, __VA_ARGS__)

#ifdef DOXYGEN
/**
 ** @brief Assure type safety for variadic functions
 **
 ** Variadic functions in C have a big loophole in that they don't
 ** enforce the types for parameters that are given to the ... list. This
 ** may have severe consequences when you pass constants as arguments
 ** to such functions and the resulting type differs from what is expected.
 **
 ** A classical example is @c NULL, which may be an integral 0 of any
 ** type @em or @c (void*)0. Suppose a function
 ** @code
 ** void toto_raw(size_t len, ...);
 ** @endcode
 **
 ** expects the
 ** parameter @c len, followed by a list of arguments expected to be @c
 ** void*. Consider the following three calls to @c toto_raw:
 ** @code
 ** toto_raw(2, NULL, malloc(23));
 ** toto_raw(2, 0, malloc(23));
 ** toto_raw(2, (void*)0, malloc(23));
 ** @endcode
 **
 ** Depending on the compiler, the first two might both result in an
 ** <code>(int)0</code> being put on the stack. @c sizeof(int) might
 ** for example be 4 and @c sizeof(void*) be 8, so the program would
 ** crash. C has no automatic way to detect that since the
 ** interface of @c toto_raw simply can't specify which types the function
 ** expects.
 **
 ** ::P99_CALL_VA_ARG allows you to "declare" the type of the ... arguments.
 ** @code
 ** #define toto(...) P99_CALL_VA_ARG(toto_raw, 1, void*, __VA_ARGS__)
 ** @endcode
 ** @param NAME is the name of the variadic function that is to be called
 ** @param M is the number of arguments of @a NAME before the ...
 ** @param T is the conversion type of the ... arguments
 **
 ** All the following calls of @c toto result in valid calls of @c
 ** toto_raw and only put @c void* values in the variadic list:
 ** @code
 ** toto(0);
 ** toto(1, NULL);
 ** toto(1, 0);
 ** toto(1, (void*)0);
 ** toto(2, NULL, malloc(23));
 ** toto(2, 0, malloc(23));
 ** toto(2, (void*)0, malloc(23));
 ** @endcode
 **
 ** The conversion of the arguments to type @a T is done with
 ** ::P99_RVAL. So all values passed in the variadic list must be
 ** assignment compatible with type @a T.
 **
 ** This macro also allows you to declare default values for the @a
 ** M first arguments. We could for example do
 ** @code
 ** #define toto_defarg_0() 0
 ** @endcode
 **
 ** Then calling @c toto without arguments would be valid:
 ** @code
 ** toto();
 ** @endcode
 **
 ** The convention for these symbols is that the number at the end
 ** corresponds to the position of the argument, starting from 0. This
 ** may be a macro, as above, or a function. We could have achieved
 ** the same effect by declaring
 ** @code
 ** inline size_t toto_defarg_0(void) { return 0; }
 ** @endcode
 **
 ** The arguments in the variadic list may have not only a
 ** default type but may have a default value, too.
 ** @code
 ** #define toto_defarg() ((void*)0)
 ** @endcode
 **
 ** By that
 ** @code
 ** toto(1,);
 ** @endcode
 ** would expand to something equivalent to
 ** @code
 ** toto(1, (void*)0);
 ** @endcode
 **
 ** The naming convention is similar to that stated above for the
 ** numbered arguments, only that the suffix "_N" is omitted from the
 ** name of the function or macro.
 **/
#define P99_CALL_VA_ARG(NAME, M, T, ...) NAME(__VA_ARGS__)
#else
P00_DOCUMENT_NUMBER_ARGUMENT(P99_CALL_VA_ARG, 1)
#define P99_CALL_VA_ARG(NAME, M, T, ...)                                                                   \
P99_IF_GT(P99_NARG(__VA_ARGS__), M)                                                                        \
(NAME(P00__DEFARGS(NAME, M, P99_SELS(M, __VA_ARGS__)), P00_CALL_VA_ARG(NAME, T, P99_SKP(M, __VA_ARGS__)))) \
(P99_CALL_DEFARG(NAME, M, __VA_ARGS__))
#endif

/** @}
 **/

/** @}
 **/

#endif      /* !P99_DEFARG_H_ */
