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
#ifndef     P99_ARGS_H_
# define    P99_ARGS_H_

/**
 ** @file
 ** @brief Providing macros that handle variadic macro argument lists.
 **/

#include "p99_paste.h"

/**
 ** @addtogroup basic_list_operations
 **
 ** @{
 **/

/**
 ** @brief Return the length of the variate argument list.
 **
 ** This supposes that the length is less than ::P99_MAX_NUMBER.
 **
 ** Idea is due to Laurent Deniau, CERN, and taken from a discussion
 ** in comp.lang.c.
 **
 ** @warning this also counts an empty argument list as having one (=
 ** the empty) argument
 ** @see P99_NARG for a macro that returns 0 if the list is empty
 **/
#define P00_NARG(...) P00_NARG_1(__VA_ARGS__)

#define P00_IS__EQ__(...) ,

/**
 ** @brief Test if the argument list is empty.
 **
 ** This expands to token 1 if the list was empty and to token 0 if
 ** there was anything other than a comment in the list.
 **
 ** The implementation of this macro is kind of tricky and relies heavily
 ** on the fact that a function macro (@c P00_IS__EQ__ in this case) is
 ** left untouched if it is not followed by a parenthesis. See
 ** http://gustedt.wordpress.com/2010/06/08/detect-empty-macro-arguments/
 **
 ** @return tokens 0 or 1
 **
 ** @warning This macro should work for most reasonable invocations
 ** (balanced parenthesis and stuff like that). The only case that
 ** definitely does not work is when called with another macro @c X
 ** at the end of its argument list, where X itself expects more than one
 ** argument.
 ** The particular cases where X receives @c 0, @c 1 or a
 ** variable number of arguments should be fine.
 **/
#define P99_IS_EMPTY(...)                                                 \
P00_ISEMPTY(                                                              \
            /* test if there is just one argument, that might be empty */ \
             P99_HAS_COMMA(__VA_ARGS__),                                  \
             /* test if P99_IS__EQ__ together with the argument           \
                adds a comma */                                           \
             P99_HAS_COMMA(P00_IS__EQ__ __VA_ARGS__),                     \
             /* test if the argument together with a parenthesis          \
                adds a comma */                                           \
             P99_HAS_COMMA(__VA_ARGS__ (/*empty*/)),                      \
             /* test if placing it between P99_IS__EQ__ and the           \
                parenthesis adds a comma */                               \
             P99_HAS_COMMA(P00_IS__EQ__ __VA_ARGS__ (/*empty*/))          \
             )

#define P00_ISEMPTY(_0, _1, _2, _3) P99_HAS_COMMA(P99_PASTE5(P00_IS_EMPTY_CASE_, _0, _1, _2, _3))
#define P00_IS_EMPTY_CASE_0000 P00_IS_EMPTY_CASE_0000
#define P00_IS_EMPTY_CASE_0001 ,
#define P00_IS_EMPTY_CASE_0010 P00_IS_EMPTY_CASE_0010
#define P00_IS_EMPTY_CASE_0011 P00_IS_EMPTY_CASE_0011
#define P00_IS_EMPTY_CASE_0100 P00_IS_EMPTY_CASE_0100
#define P00_IS_EMPTY_CASE_0101 P00_IS_EMPTY_CASE_0101
#define P00_IS_EMPTY_CASE_0110 P00_IS_EMPTY_CASE_0110
#define P00_IS_EMPTY_CASE_0111 P00_IS_EMPTY_CASE_0111
#define P00_IS_EMPTY_CASE_1000 P00_IS_EMPTY_CASE_1000
#define P00_IS_EMPTY_CASE_1001 P00_IS_EMPTY_CASE_1001
#define P00_IS_EMPTY_CASE_1010 P00_IS_EMPTY_CASE_1010
#define P00_IS_EMPTY_CASE_1011 P00_IS_EMPTY_CASE_1011
#define P00_IS_EMPTY_CASE_1100 P00_IS_EMPTY_CASE_1100
#define P00_IS_EMPTY_CASE_1101 P00_IS_EMPTY_CASE_1101
#define P00_IS_EMPTY_CASE_1110 P00_IS_EMPTY_CASE_1110
#define P00_IS_EMPTY_CASE_1111 P00_IS_EMPTY_CASE_1111


#define P00_NARG_EMPTY_1(VAL) 0
#define P00_NARG_EMPTY_0(VAL) VAL

/**
 ** @brief Return the length of the variable length argument list, where an empty
 ** argument list is considered to have 0 arguments.
 **
 ** This supposes that the length of the list is less than ::P99_MAX_NUMBER.
 **
 ** @see P00_NARG for a macro in which an empty list is considered to have 1 argument.
 **/
#define P99_NARG(...) P00_NARG__1(P99_IS_EMPTY(__VA_ARGS__), P00_NARG(__VA_ARGS__))
#define P00_NARG__1(B, VAL) P00_NARG__2(P99_PASTE2(P00_NARG_EMPTY_, B), VAL)
#define P00_NARG__2(B, VAL) B(VAL)


/**
 ** @}
 **/


/**
 ** @addtogroup preprocessor_text
 **
 ** @{
 **/

/**
 ** @brief Detect if two tokens are equal.
 **
 ** The tokens must be alphanumeric, composed of [_a-zA-Z0-9]. To
 ** be able to test for equality of token @c X the macro @c
 ** P00_IS_X_EQ_X(...) must be defined to expand to a comma.
 **
 ** For a list of predefined tokens for which this is implemented see @ref preprocessor_text
 **/
#define P99_TOK_EQ(TOK, ...)  P00_TOK_EQ_(P99_PASTE3(P00_IS_, TOK, _EQ_), __VA_ARGS__)
#define P00_TOK_EQ_(MAC, ...)  P00_TOK_EQ__(MAC, __VA_ARGS__)
#define P00_TOK_EQ__(MAC, ...) P99_HAS_COMMA(P99_PASTE2(P00_TOK_EQ_, P00_NARG(MAC ## __VA_ARGS__ (~) MAC ## __VA_ARGS__))(~))

#define P00_TOK_EQ_0(...) ~
#define P00_TOK_EQ_1(...) ~
#define P00_TOK_EQ_2(...) ,
#define P00_TOK_EQ_3(...) ~
#define P00_TOK_EQ_4(...) ~


/**
 ** @}
 **/

/**
 ** @addtogroup variadic Macros to ease programming of variadic functions
 **
 ** @{
 **/

/**
 ** @brief Helper macro to declare a variable length parameter list.
 **
 ** Inside the declared function @a X will be of type @c size_t and should
 ** hold the actual length of the list. It can be used as the argument
 ** to @c va_start.
 **
 ** Wrap your function in a macro that uses P99_LENGTH_VA_ARG. If used through
 ** that macro, the correct value for @a X will always be provided at
 ** compile time. Declare such a function as follows:
 ** @code
 ** unsigned P99_FSYMB(toto)(unsigned a, P99_VA_ARGS(number));
 ** #define toto(A, ...) P99_FSYMB(toto)(A, P99_LENGTH_VA_ARG(__VA_ARGS__))
 ** @endcode
 **
 ** In the definition of the function you may then use the @c va_start
 ** etc from stdarg.h to traverse the argument list.
 ** @code
 ** unsigned P99_FSYMB(toto)(unsigned a, P99_VA_ARGS(number)) {
 **     unsigned ret = 0;
 **     va_list ap;
 **     va_start(ap, number);
 **     for (size_t i = 0; i < number; ++i) {
 **       ret += va_arg(ap, unsigned);
 **     }
 **     va_end(ap);
 **     return ret % a;
 ** }
 ** @endcode
 ** In this toy example @c toto can be used as
 ** @code
 ** unsigned magic = toto(3, 1, 3, 5, 7);
 ** @endcode
 ** which will result in converting 1, 3, 5, 7 (the variable
 ** arguments) to @c unsigned, computing their sum, i.e 16u, and
 ** compute that value mod 3u (the fixed argument @a a). So @a magic
 ** should hold the value 1u thereafter. (But beware of implicit
 ** integer promotion rules for integers of small width.)
 **
 ** @param X is the name of the `length' parameter that you want to
 ** use in the definition of the function. As in the example above it
 ** should then be used as the second argument to @c va_start and as a
 ** loop boundary when you actual handle the argument list. @a X is
 ** implicitly declared to have type @c size_t.
 **
 ** @see P99_LENGTH_ARR_ARG for a way that is generally more efficient
 **      than using @c va_list
 ** @see P99_LENGTH_VA_ARG
 ** @see P99_FSYMB
 **/
#define P99_VA_ARGS(X) size_t X /*!< the number of arguments that follow */, ...

#define P00_FSYMB(NAME) P99_PASTE5(NAME, _f, sy, mb, _)

/**
 ** @brief Mangle @a NAME
 **
 ** This should only be used in declaration and definition of the
 ** function that is hidden behind the macro @a NAME.
 **/
#define P99_FSYMB(NAME) P00_FSYMB(NAME)

/**
 ** @brief Meta-macro to generate calls to functions with variable
 ** argument lists.
 **
 ** This supposes that the length is less than ::P99_MAX_NUMBER. It prefixes the
 ** list of arguments by an integer constant containing the length of
 ** the list.
 ** @see P99_VA_ARGS
 **/
#define P99_LENGTH_VA_ARG(...) ((size_t)P99_NARG(__VA_ARGS__)), __VA_ARGS__


/**
 ** @brief Helper macro to declare a variable length parameter list.
 **
 ** Wrap your function in a macro that uses P99_LENGTH_ARR_ARG. If used through
 ** that macro, the correct value for @c number for the length of the
 ** array @c arr as in the following
 ** example will always be provided at
 ** compile time:
 ** @code
 ** unsigned P99_FSYMB(tutu)(unsigned a, size_t number, unsigned const*arr);
 ** #define tutu(A, ...) P99_FSYMB(tutu)(A, P99_LENGTH_ARR_ARG(unsigned const, __VA_ARGS__))
 ** @endcode
 **
 ** In the definition of the function you then may use an array of the
 ** arguments in the obvious way.
 ** @code
 ** unsigned P99_FSYMB(tutu)(unsigned a, size_t number, unsigned const*arr) {
 **   unsigned ret = 0;
 **   for (size_t i = 0; i < number; ++i) {
 **     ret += arr[i];
 **   }
 **   return ret % a;
 ** }
 ** @endcode
 ** In this toy example @c tutu can be used as
 ** @code
 ** unsigned magic = tutu(3, 1, 3, 5, 7);
 ** @endcode
 ** which will result in converting 1, 3, 5, 7 (the variable
 ** arguments) to @c unsigned, computing their sum, i.e 16u, and
 ** compute that value mod 3u (the fixed argument @a a). So @a magic
 ** should hold the value 1u thereafter.
 **
 ** In the example @c number is the name of the `length' parameter
 ** that you want to use in the definition of the function.
 **
 ** The method here is generally more efficient than using
 ** ::P99_VA_ARGS since it results in code that can be inlined more easily
 ** by the compiler. In  particular, if a function such as @c tutu above is
 ** called with compile time constants for all parameters, the call
 ** may be optimized away completely.
 **
 ** @see P99_VA_ARGS
 ** @see P99_FSYMB
 **/
#define P99_LENGTH_ARR_ARG(T, ...) ((size_t)P99_NARG(__VA_ARGS__)), (T[]){ __VA_ARGS__ }


/**
 ** @}
 **/



#endif      /* !P99_ARGS_H_ */
