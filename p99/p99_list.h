/* This may look like nonsense, but it really is -*- mode: C -*-              */
/*                                                                            */
/* Except for parts copied from previous work and as explicitly stated below, */
/* the author and copyright holder for this work is                           */
/* (C) copyright  2010-2012 Jens Gustedt, INRIA, France                       */
/*                                                                            */
/* This file is free software; it is part of the P99 project.                 */
/* You can redistribute it and/or modify it under the terms of the QPL as     */
/* given in the file LICENSE. It is distributed without any warranty;         */
/* without even the implied warranty of merchantability or fitness for a      */
/* particular purpose.                                                        */
/*                                                                            */
#ifndef     P99_LIST_H_
# define    P99_LIST_H_

/**
 ** @file
 ** @brief Basis macros to process the parameter list of a variadic
 ** macro.
 ** @see basic_list_operations
 **/

#include "p99_generated.h"

#define P00_PRE0(...)
#define P00_PRE1(_0, ...) _0

/** @addtogroup list_processing List processing macros
 ** @brief We provide here a series of macros that take a list of
 ** arguments of arbitrary length and that transform each element in
 ** that list in some way.
 **/

/** @addtogroup basic_list_operations Basic list processing macros
 **
 ** @{
 **/

/**
 ** Cut the argument list at position @a N
 **/
#define P99_SELS(N, ...) P99_PASTE2(P00_PRE, N)(__VA_ARGS__)

#define P00_SKP0(...) __VA_ARGS__
#define P00_SKP1(_0, ...) __VA_ARGS__


/**
 ** @brief Skip @a N elements in the remaining argument list.
 **/
#define P99_SKP(N, ...) P99_PASTE2(P00_SKP, N)(__VA_ARGS__)

/**
 ** @brief Get the sublist of length @a L starting at the @a
 ** N<sup>th</sup> element in the remaining argument list.
 **
 ** Counting of elements starts at 0.
 **/
#define P99_SUB(N, L, ...) P00_SUB(L, P99_SKP(N, __VA_ARGS__))
#define P00_SUB(L, ...) P99_SELS(L, __VA_ARGS__)

/**
 ** @brief Choose the @a N<sup>th</sup> element in the remaining argument
 ** list.
 **
 ** Counting of elements starts at 0.
 **/
#define P99_CHS(N, ...) P00_CHS(P99_SKP(N, __VA_ARGS__))
#define P00_CHS(...) P00_CHS_(__VA_ARGS__,)
#define P00_CHS_(X, ...) X


/**
 ** @brief Construct a list that repeats the argument list @a N times
 **
 ** The corner cases should work as expected:
 ** - If @a N is 0 the empty list is produced.
 ** - If the argument list is empty, the empty list is produced.
 ** - If the argument list has just one element which is empty, the
 **   result will just be a sequence of @a N - 1 commas.
 **/
#define P99_DUPL(...) P99_PASTE2(P00_DUPL_0_, P99_IS_LT(P99_NARG(__VA_ARGS__), 2))(__VA_ARGS__)

#define P00_DUPL_0_0(...) P00_DUPL(__VA_ARGS__)
#define P00_DUPL_0_1(...)

#define P00_DUPL_1(...) __VA_ARGS__

#define P00_DUPL(N, ...) P00_DUPL_ ## N(__VA_ARGS__)

/**
 ** @brief Construct a space separated sequence that repeats the argument list @a N times
 **
 ** The corner cases should work as expected:
 ** - If @a N is 0 the empty token is produced.
 ** - If the argument list is empty, the empty token is produced.
 ** - If the argument list has just one element which is empty, the
 **    token is produced.
 **/
P00_DOCUMENT_NUMBER_ARGUMENT(P99_REP, 0)
P00_DOCUMENT_MULTIPLE_ARGUMENT(P99_REP, 1)
P00_DOCUMENT_MULTIPLE_ARGUMENT(P99_REP, 2)
#define P99_REP(...) P99_PASTE2(P00_REP_0_, P99_IS_LT(P99_NARG(__VA_ARGS__), 2))(__VA_ARGS__)

#define P00_REP_0_0(...) P00_REP(__VA_ARGS__)
#define P00_REP_0_1(...)

#define P00_REP_1(...) __VA_ARGS__

#define P00_REP(N, ...) P00_REP_ ## N(__VA_ARGS__)

#define P99_BRACKETS(...) P99_PASTE2(P00_BRACKETS_, P99_IS_LT(P99_NARG(__VA_ARGS__), 1))(P99_NARG(__VA_ARGS__), __VA_ARGS__)

#define P00_BRACKETS_0(...) P00_BRACKET(__VA_ARGS__)
#define P00_BRACKETS_1(...)

#define P00_BRACKET_1(...) [__VA_ARGS__]

#define P00_BRACKET(N, ...) P00_BRACKET_ ## N(__VA_ARGS__)

#define P99_PARENS(...) P99_PASTE2(P00_PARENS_, P99_IS_LT(P99_NARG(__VA_ARGS__), 1))(P99_NARG(__VA_ARGS__), __VA_ARGS__)

#define P00_PARENS_0(...) P00_PAREN(__VA_ARGS__)
#define P00_PARENS_1(...)

#define P00_PAREN_1(...) [__VA_ARGS__]

#define P00_PAREN(N, ...) P00_PAREN_ ## N(__VA_ARGS__)

#define P99_BRACES(...) P99_PASTE2(P00_BRACES_, P99_IS_LT(P99_NARG(__VA_ARGS__), 1))(P99_NARG(__VA_ARGS__), __VA_ARGS__)

#define P00_BRACES_0(...) P00_BRACE(__VA_ARGS__)
#define P00_BRACES_1(...)

#define P00_BRACE_1(...) [__VA_ARGS__]

#define P00_BRACE(N, ...) P00_BRACE_ ## N(__VA_ARGS__)

#define P00_MAP_1(MAC, SEP, ...) MAC(__VA_ARGS__)
#define P00_MAP_0(...)

#define P00_MAP_0_(N, MAC, SEP, ...) P00_MAP_ ## N(MAC, SEP, __VA_ARGS__)

#define P00_MAP_(...) P00_MAP_0_(__VA_ARGS__)


/** @}
 **/


#endif      /* !P99_LIST_H_ */
