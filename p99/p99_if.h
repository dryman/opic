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
#ifndef     P99_IF_H_
# define    P99_IF_H_

/**
 ** @file
 ** @brief preprocessor conditionals to use inside macros
 **/

#include "p99_logical.h"

/**
 ** @addtogroup preprocessor_conditionals Preprocessor conditionals
 **
 ** @brief This provides different types of if-else clause for the preprocessor.
 **
 ** The macros in this group are analogous to ::P99_IF_EQ
 ** @code
 ** P99_IF_EQ(INT_MAX, 10000)(short)(long) a;
 ** P99_IF_EQ(8, CHAR_BIT)(uint8_t)(uint_least8_t) c;
 ** @endcode
 **
 ** which would normally@fntm 5@efntm be textually replaced by
 ** @code
 ** long a;
 ** uint8_t c;
 ** @endcode
 **
 ** That is, all these macros expect @em three pairs of parentheses
 ** after their keyword token:
 **  -# containing the condition
 **  -# containing the if-clause
 **  -# containing the else-clause
 **
 ** For the underlying logical and arithmetical operations
 ** @see preprocessor_logic
 ** @see preprocessor_arithmetic
 **
 ** @fnt 5 @efnt
 ** @c INT_MAX can never be 10000, because is it at least
 ** 2<sup>15</sup>-1. @c CHAR_BIT isn't 8 only on special hardware
 ** such as DSP, and if is is 8, the typedef @c uint8_t must exist.
 ** @{
 **/

#define P00_IGNORE(...)
#define P00_IDENT(...) __VA_ARGS__
#define P00_SKIP_
#define P00_CLAUSE1(...) __VA_ARGS__ P00_IGNORE
#define P00_CLAUSE2(...) P00_IDENT

#define P00__IF_CLAUSE(A,B,C,...) C
#define P00_IF_CLAUSE(EXP) P00__IF_CLAUSE(EXP, P00_CLAUSE1, P00_CLAUSE2, ~)
#define P00_IF_NOT_CLAUSE(EXP) P00__IF_CLAUSE(EXP, P00_CLAUSE2, P00_CLAUSE1, ~)

/**
 ** @brief Test if two words @a A and @a B are equal.
 **
 ** @a A and @a B must be just one word, i.e composed of
 ** alpha-numerical characters and underscores.
 **
 ** For such a test to work properly a corresponding macro @c P00_IS_A_EQ_A
 ** must exist for all @a A such that @a B may be the same word as @a
 ** A. E.g for the test
 **
 ** @code
 ** P99_IF_EQ(0, X)(expand_when_equal)(expand_when_unequal)
 ** @endcode
 **
 ** the macro ::P00_IF_0_EQ_0 must exist. (Which it does in this case).
 **/
#define P99_IF_EQ(A, B) P00_IF_CLAUSE(P99_PASTE4(P00_IS_,A,_EQ_,B)())

/**
 ** @brief Test if two words @a A and @a B are unequal.
 **
 ** @see P99_IF_EQ
 **/
#define P99_IF_NE(A, B) P00_IF_NOT_CLAUSE(P99_PASTE4(P00_IS_,A,_EQ_,B)())

#define P99_IF_GE_0(A) P00_IF_CLAUSE(P99_PASTE4(P00_IS_,A,_GE_,0)())
#define P99_IF_LT_0(A) P00_IF_NOT_CLAUSE(P99_PASTE4(P00_IS_,A,_GE_,0)())

/**
 ** @brief Test two decimal numbers @a A and @a B for whether @a A is greater
 ** than or equal to @a B.
 **/
#define P99_IF_GE(A, B) P99_IF_EQ_1(P99_IS_GE(A, B))

/**
 ** @brief Test two decimal numbers @a A and @a B for whether @a A is less
 ** than or equal to @a B.
 **/
#define P99_IF_LE(A, B) P99_IF_EQ_1(P99_IS_LE(A, B))

/**
 ** @brief Test two decimal numbers @a A and @a B for whether @a A is strictly
 ** less than @a B.
 **/
#define P99_IF_LT(A, B) P99_IF_EQ_1(P99_IS_LT(A, B))

/**
 ** @brief Test two decimal numbers @a A and @a B for whether @a A is strictly
 ** greater than @a B.
 **/
#define P99_IF_GT(A, B) P99_IF_EQ_1(P99_IS_GT(A, B))

/**
 ** @brief Test if token N is the token 0.
 **/
#define P99_IF_EQ_0(N) P99_IF_EQ(0, N)

/**
 ** @brief Test if token N is the token 1.
 **/
#define P99_IF_EQ_1(N) P99_IF_EQ(1, N)

/**
 ** @brief Test if token N is the token 2.
 **/
#define P99_IF_EQ_2(N) P99_IF_EQ(2, N)

/**
 ** @brief Test if token N is the token 3.
 **/
#define P99_IF_EQ_3(N) P99_IF_EQ(3, N)

/**
 ** @brief Test if token N is the token 4.
 **/
#define P99_IF_EQ_4(N) P99_IF_EQ(4, N)

#define P99_IF_EMPTY(...) P99_IF_EQ_1(P99_IS_EMPTY(__VA_ARGS__))

/**
 ** @brief A preprocessor control structure
 **
 ** Use this as follows
 ** @code
 ** P99_IF_ELSE(some_expression)(tokens_A)(tokens_B)
 ** @endcode
 ** This expands to tokens_B if the list expanded to the token 0 and
 ** to tokens_A in any other case.
 **
 ** Observe the parenthesis around tokens_A and tokens_B.
 **/
#define P99_IF_ELSE(...) P99_IF_EQ_0(P99_IS_EQ_0(__VA_ARGS__))

#define P99_IF_void(...) P99_IF_EQ_1(P99_IS_EQ_void(__VA_ARGS__))

#define P99_IF_VOID(...) P99_IF_EQ_1(P99_IS_VOID(__VA_ARGS__))


#define P00_PRAGMA_(STR) _Pragma(STR)
#define P00_PRAGMA(...) P00_PRAGMA_(#__VA_ARGS__)

/**
 ** @brief An wrapper of the _Pragma keyword
 **
 ** All arguments are wrapped into a string that is passed as one
 ** argument to @c _Pragma. If the argument list is empty, this
 ** evaporates and is ignored.
 **/
#define P99_PRAGMA(...) P99_IF_EMPTY(__VA_ARGS__)()(P00_PRAGMA(__VA_ARGS__))

/**
 ** @}
 **/

# undef p99_has_builtin
# undef p99_has_feature
# undef p99_has_extension
# undef p99_has_attribute

# define p99_has_builtin(X) (P99_IF_EQ_1(__has_builtin(X))(1)(0) || P99_IF_EQ_1(p00_has_builtin_ ## X)(1)(0))  // Compatibility with non-clang compilers.
# define p99_has_feature(X) (P99_IF_EQ_1(__has_feature(X))(1)(0) || P99_IF_EQ_1(p00_has_feature_ ## X)(1)(0))  // Compatibility with non-clang compilers.
# define p99_has_extension(X) (P99_IF_EQ_1(__has_extension(X))(1)(0) || P99_IF_EQ_1(p00_has_extension_ ## X)(1)(0)) // Compatibility with non-clang compilers.
# define p99_has_attribute(X) (P99_IF_EQ_1(__has_attribute(X))(1)(0) || P99_IF_EQ_1(p00_has_attribute_ ## X)(1)(0))  // Compatibility with non-clang compilers.


#endif      /* !P99_IF_H_ */
