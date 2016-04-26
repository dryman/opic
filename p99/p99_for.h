/* This may look like nonsense, but it really is -*- mode: C -*-              */
/*                                                                            */
/* Except for parts copied from previous work and as explicitly stated below, */
/* the authors and copyright holders for this work are as follows:            */
/* (C) copyright  2010-2014 Jens Gustedt, INRIA, France                       */
/* (C) copyright  2012 William Morris                                         */
/*                                                                            */
/* This file is free software; it is part of the P99 project.                 */
/* You can redistribute it and/or modify it under the terms of the QPL as     */
/* given in the file LICENSE. It is distributed without any warranty;         */
/* without even the implied warranty of merchantability or fitness for a      */
/* particular purpose.                                                        */
/*                                                                            */
#ifndef     P99_FOR_H_
# define    P99_FOR_H_

/**
 ** @file
 ** @brief A preprocessor for loop implementation and some derived
 ** list handling macros.
 ** @see P99_FOR
 **/

#include "p99_block.h"



/** @addtogroup preprocessor_for Preprocessor FOR loops
 ** @{
 **/

#define P00_FOR0(NAME, OP, FUNC, ...)
#define P00_FOR1(NAME, OP, FUNC, ...) FUNC(NAME, P00_PRE1(__VA_ARGS__,), 0)

#ifdef P00_DOXYGEN
/**
 ** @brief A preprocessor pseudo iterator.
 **
 ** @param NAME a name or other data that is visible to all iterations
 ** @param N the number of times the iteration is to be done
 ** @param OP an operation that is performed to glue the different
 **        results of the individual iterations together
 ** @param FUNC a function that is applied in each iteration
 **
 ** In each iteration, @a FUNC will be called as @c FUNC(NAME, X, I).
 ** Here @a NAME is the same as the argument to ::P99_FOR. @c I is the
 ** ordinal number of this iteration step, starting from 0. @c X is
 ** the @c Ith argument from the remaining argument list of this
 ** invocation of ::P99_FOR.
 **
 ** @a OP is called for iterations 1 to @a N - 1 to glue the results
 ** of the @a N iterations together. It is called in the form @a
 ** OP(NAME, I, REC, RES), where @a NAME and @c I are as before. @c
 ** REC is the result of all iterations with index less than @c I, @c
 ** RES is the result of the current iteration.
 **
 ** @code
 ** #define P00_SEP(NAME, I, REC, RES) REC; RES
 ** #define P00_VASSIGN(NAME, X, I) X = (NAME)[I]
 **
 ** P99_FOR(A, 2, P00_SEP, P00_VASSIGN, toto, tutu);
 ** @endcode
 **
 ** Will result in
 ** @code
 ** toto = (A)[0]; tutu = (A)[1];
 ** @endcode
 **
 ** To understand the associativity of the @a OP argument
 ** @code
 ** #define P00_SUM(NAME, I, REC, RES) ((REC) + (RES))
 ** #define P00_IDT(NAME, X, I) X
 **
 ** P99_FOR(A, 2, P00_SUM, P00_IDT, a, b, c)
 ** @endcode
 ** Will result in
 ** @code
 ** ((((a) + (b))) + (c))
 ** @endcode
 **/
P00_DOCUMENT_MULTIPLE_ARGUMENT(P99_FOR, 0)
P00_DOCUMENT_NUMBER_ARGUMENT(P99_FOR, 1)
P00_DOCUMENT_MACRO_ARGUMENT(P99_FOR, 3)
#define P99_FOR(NAME, N, OP, FUNC, ...)
#else
P00_DOCUMENT_MULTIPLE_ARGUMENT(P99_FOR, 0)
P00_DOCUMENT_NUMBER_ARGUMENT(P99_FOR, 1)
P00_DOCUMENT_MACRO_ARGUMENT(P99_FOR, 3)
#define P99_FOR(NAME, N, OP, FUNC, ...) P99_PASTE2(P00_FOR, N)(NAME, OP, FUNC, __VA_ARGS__)
#endif

#define P00_IGN(NAME, X, I)
#define P00_IDT(NAME, X, I) X
#define P00_POS(NAME, X, I) I
#define P00_NAM(NAME, X, I) NAME
#define P00_NAME_I(NAME, X, I) P99_PASTE2(NAME, I)
#define P00_STR(NAME, X, I) P99_STRINGIFY(X)
#define P00_ISIT(WHAT, X, I) (X) WHAT

#define P00_SUM(NAME, I, X, Y) ((X) + (Y))
#define P00_PROD(NAME, I, X, Y) ((X) * (Y))
#define P00_QUOT(NAME, I, X, Y) ((X) / (Y))
#define P00_XOR(NAME, I, X, Y) ((X) ^ (Y))
#define P00_BOR(NAME, I, X, Y) ((X) | (Y))
#define P00_BAND(NAME, I, X, Y) ((X) & (Y))
#define P00_OR(NAME, I, X, Y) ((X) || (Y))
#define P00_AND(NAME, I, X, Y) ((X) && (Y))
#define P00_TOKJOIN(NAME, I, X, Y) X NAME Y

#define P00_SEQ(NAME, I, REC, X) REC, X
#define P00_SEP(NAME, I, REC, X) REC; X
#define P00_SER(NAME, I, REC, X) REC X
#define P00_REV(NAME, I, REC, X) X, REC
#define P00_PES(NAME, I, REC, X) X; REC
#define P00_RES(NAME, I, REC, X) X REC

/**
 ** @brief generate lists of names of the form <code>NAME0, NAME1, ...</code>
 **/
P00_DOCUMENT_NUMBER_ARGUMENT(P99_NAME, 0)
#define P99_NAME(N, NAME) P99_FOR(NAME, N, P00_SEQ, P00_NAME_I, P99_REP(N,))

#define P00_FUNC(NAME, I, REC, X) NAME(REC, X)

/**
 ** @brief Realize the right associative operation @a OP of all the arguments.
 **
 ** Here @a OP should receive four arguments <code>NAME, X, N,
 ** REC</code> out of which @c NAME and @c N are ignored and @c X and
 ** @c REC should be interpreted as the left and right hand of the
 ** operator action, respectively.
 **
 ** @a M is the length of the list that follows it.
 **/
P00_DOCUMENT_NUMBER_ARGUMENT(P99_BIGOP, 1)
#define P99_BIGOP(OP, M, ...) P99_FOR( , M, OP, P00_IDT, __VA_ARGS__)

/**
 ** @brief Realize the right associative call of binary function @a FUNC of all the arguments.
 **
 ** Here @a FUNC should be a function of two arguments.
 **
 ** @a M is the length of the list that follows it.
 **/
P00_DOCUMENT_NUMBER_ARGUMENT(P99_BIGFUNC, 1)
#define P99_BIGFUNC(FUNC, M, ...) P99_FOR(FUNC, M, P00_FUNC, P00_IDT, __VA_ARGS__)


#define P00_REPEAT(MACRO, X, I) MACRO(I)

/**
 ** @brief Apply the macro @a MACRO @a N times
 **
 ** The macro is called with the numbers <code>0, ..., N-1</code> and
 ** the @a N results are separated by a comma.
 **
 ** In the following example we define an adhoc macro that initializes
 ** an array element with a certain structure type. The array @c P is
 ** an array of 10 pairs, each containing their index in the @c index
 ** field and a different pointer in their @c aPos field.
 ** @code
 ** typedef struct pair pair;
 ** struct pair {
 **   size_t index;
 **   double* aPos;
 ** };
 ** #define ASIZE 10
 ** double A[] = { P99_DUPL(ASIZE, 1.7) };
 ** #define INIT_PAIR(I) [I] = {                               \
 **   .index = I,                                              \
 **   .aPos = &A[I],                                           \
 **   }
 ** pair P[] = { P99_REPEAT(INIT_PAIR, ASIZE) };
 ** @endcode
 ** @see P99_UNROLL for a macro that separates the parts by @c ;
 ** @see P99_SEQ for a similar macro that applies @a MACRO to a list of items
 ** @see P99_FOR for a more generic and flexible utility
 **/
P00_DOCUMENT_MACRO_ARGUMENT(P99_REPEAT, 0)
P00_DOCUMENT_NUMBER_ARGUMENT(P99_REPEAT, 1)
#define P99_REPEAT(MACRO, N) P99_FOR(MACRO, N, P00_SEQ, P00_REPEAT, P99_DUPL(N,))

/**
 ** @brief Apply the macro @a MACRO @a N times
 **
 ** The macro is called with the numbers <code>0, ..., N-1</code> and
 ** the @a N results are separated by a semicolon.
 **
 ** In the following example we define an adhoc macro that copies an array element
 ** of an array @c A to the elements of another array B.
 **
 ** @code
 ** #define ASIZE 3
 ** double A[] = { P99_DUPL(ASIZE, 1.7) };
 ** double B[] = { P99_DUPL(ASIZE, 371) };
 ** #define COPY_A2B(I) B[I] = A[I]
 ** P99_UNROLL(COPY_A2B, ASIZE);
 ** @endcode
 **
 ** This will expand to
 ** @code
 ** B[0] = A[0]; B[1] = A[1]; B[2] = A[2];
 ** @endcode
 **
 ** Observe that the first two @c ; are inserted automatically as
 ** separators by the ::P99_UNROLL macro.  The final one is inserted
 ** directly in the program, right after the macro invocation.
 **
 ** @see P99_REPEAT for a macro that separates the parts by @c ,
 ** @see P99_SEQ for a similar macro that applies @a MACRO to a list of items
 ** @see P99_FOR for a more generic and flexible utility
 **/
P00_DOCUMENT_MACRO_ARGUMENT(P99_UNROLL, 0)
P00_DOCUMENT_NUMBER_ARGUMENT(P99_UNROLL, 1)
#define P99_UNROLL(MACRO, N) P99_FOR(MACRO, N, P00_SEP, P00_REPEAT, P99_DUPL(N,))

#define P00_MAP(MACRO, X, I) MACRO(X)
/**
 ** @brief Apply the macro @a MACRO to the rest of the argument list.
 **
 ** The macro is called with each of the other arguments and
 ** the results are separated by commas.
 **
 ** Suppose you have an enumeration type with three values:
 ** @code
 ** enum { one, two, three } ;
 ** #define ENUM_INIT(X) [X] = P99_STRINGIFY(X)
 ** char const* names[] = { P99_SEQ(ENUM_INIT, one, two, three) };
 ** @endcode
 **
 ** This will result in the following expansion
 **
 ** @code
 ** char const* names[] = { [one] = "one", [two] = "two", [three] = "three" };
 ** @endcode
 ** @see P99_REPEAT for a similar macro that applies @a MACRO a fixed number of times
 ** @see P99_SEP for a similar macro that separates the different parts with a @c ;
 ** @see P99_SER for a similar macro that separates the different parts with a space token
 ** @see P99_FOR for a more generic and flexible utility
 **/
P00_DOCUMENT_MACRO_ARGUMENT(P99_SEQ, 0)
#define P99_SEQ(MACRO, ...) P00_MAP_(P99_NARG(__VA_ARGS__), MACRO, (,), __VA_ARGS__)

/**
 ** @brief Apply the macro @a MACRO to the rest of the argument list.
 **
 ** The macro is called with each of the other arguments and
 ** the results are separated by a space token.
 **
 ** @see P99_UNROLL for a similar macro that applies @a MACRO a fixed number of times
 ** @see P99_SEQ for a similar macro that separates the different parts with a @c ,
 ** @see P99_SER for a similar macro that separates the different parts with a space token
 ** @see P99_FOR for a more generic and flexible utility
 **/
P00_DOCUMENT_MACRO_ARGUMENT(P99_SER, 0)
#define P99_SER(MACRO, ...) P00_MAP_(P99_NARG(__VA_ARGS__), MACRO, ( ), __VA_ARGS__)

/**
 ** @brief Apply the macro @a MACRO to the rest of the argument list.
 **
 ** The macro is called with each of the other arguments and
 ** the results are separated by semicolon.
 **
 ** Suppose you want to create a @c struct that has several fields of
 ** similar name and type.
 **
 ** @code
 ** #define FIELD_DECL(X) P99_PASTE2(type_, X) P99_PASTE2(X, _flag)
 ** struct bits {
 **    P99_SEP(FIELD_DECL, chaos, sat, grey);
 ** };
 ** @endcode
 **
 ** This will result in the following expansion
 **
 ** @code
 ** struct bits {
 **    type_chaos chaos_flag;
 **    type_sat sat_flag;
 **    type_grey grey_flag;
 ** };
 ** @endcode
 ** @see P99_UNROLL for a similar macro that applies @a MACRO a fixed number of times
 ** @see P99_SEQ for a similar macro that separates the different parts with a @c ,
 ** @see P99_SER for a similar macro that separates the different parts with a space token
 ** @see P99_FOR for a more generic and flexible utility
 **/
P00_DOCUMENT_MACRO_ARGUMENT(P99_SEP, 0)
#define P99_SEP(MACRO, ...) P00_MAP_(P99_NARG(__VA_ARGS__), MACRO, (;), __VA_ARGS__)

/**
 ** @brief Apply the macro @a MACRO to the rest of the argument list.
 **
 ** The macro is called with each of the other arguments and
 ** the results are joined by a <code>+</code> token.
 **
 ** @see P99_UNROLL for a similar macro that applies @a MACRO a fixed number of times
 ** @see P99_SEQ for a similar macro that separates the different parts with a @c ,
 ** @see P99_SER for a similar macro that separates the different parts with a space token
 ** @see P99_FOR for a more generic and flexible utility
 **/
P00_DOCUMENT_MACRO_ARGUMENT(P99_SEA, 0)
#define P99_SEA(MACRO, ...) P00_MAP_(P99_NARG(__VA_ARGS__), MACRO, (+), __VA_ARGS__)

/**
 ** @brief Apply the macro @a MACRO to the rest of the argument list.
 **
 ** The macro is called with each of the other arguments and
 ** the results are joined by a <code>*</code> token.
 **
 ** @see P99_UNROLL for a similar macro that applies @a MACRO a fixed number of times
 ** @see P99_SEQ for a similar macro that separates the different parts with a @c ,
 ** @see P99_SER for a similar macro that separates the different parts with a space token
 ** @see P99_FOR for a more generic and flexible utility
 **/
P00_DOCUMENT_MACRO_ARGUMENT(P99_SEM, 0)
#define P99_SEM(MACRO, ...) P00_MAP_(P99_NARG(__VA_ARGS__), MACRO, (*), __VA_ARGS__)


/**
 ** @}
 **/



/** @addtogroup statement_lists
 ** @{
 **/

/**
 ** @brief Realize the right associative sum of all the arguments.
 **/
#define P99_SUMS(...) P99_BIGOP(P00_SUM, P99_NARG(__VA_ARGS__),__VA_ARGS__)
/**
 ** @brief Realize the right associative product of all the arguments.
 **/
#define P99_PRODS(...) P99_BIGOP(P00_PROD, P99_NARG(__VA_ARGS__),__VA_ARGS__)
/**
 ** @brief Realize the right associative quotient of all the arguments.
 **/
#define P99_QUOTS(...) P99_BIGOP(P00_QUOT, P99_NARG(__VA_ARGS__),__VA_ARGS__)
/**
 ** @brief Realize the right associative bitwise exclusive or of all the arguments.
 **/
#define P99_XORS(...) P99_BIGOP(P00_XOR, P99_NARG(__VA_ARGS__),__VA_ARGS__)
/**
 ** @brief Realize the right associative bitwise or of all the arguments.
 **/
#define P99_BORS(...) P99_BIGOP(P00_BOR, P99_NARG(__VA_ARGS__),__VA_ARGS__)
/**
 ** @brief Realize the right associative bitwise and of all the arguments.
 **/
#define P99_BANDS(...) P99_BIGOP(P00_BAND, P99_NARG(__VA_ARGS__),__VA_ARGS__)
/**
 ** @brief Realize the right associative logical or of all the arguments.
 **/
#define P99_ORS(...) P99_BIGOP(P00_OR, P99_NARG(__VA_ARGS__),__VA_ARGS__)
/**
 ** @brief Realize the right associative logical and of all the arguments.
 **/
#define P99_ANDS(...) P99_BIGOP(P00_AND, P99_NARG(__VA_ARGS__),__VA_ARGS__)


/**
 ** @brief Check if argument @a FIRST is equal to one of the other
 ** elements in the list
 **
 ** Use this as follows:
 ** @code
 ** if (P99_IS_ONE(23, b, c, d, e, f)) {
 **   // one of the guys is 23, do something special
 ** } else {
 **   // handle the base case
 ** }
 ** @endcode
 **/
P00_DOCUMENT_MULTIPLE_ARGUMENT(P99_IS_ONE, 0)
#define P99_IS_ONE(FIRST, ...) P99_FOR(== (FIRST), P99_NARG(__VA_ARGS__), P00_OR, P00_ISIT, __VA_ARGS__)

/**
 ** @brief Check if the arguments in the list are all equal
 **
 ** Use this as follows:
 ** @code
 ** if (P99_ARE_EQ(a, b, c, d, e, f)) {
 **   // all are equal, do something special
 ** } else {
 **   // handle the base case
 ** }
 ** @endcode
 **/
P00_DOCUMENT_MULTIPLE_ARGUMENT(P99_ARE_EQ, 0)
#define P99_ARE_EQ(FIRST, ...) P99_FOR(== (FIRST), P99_NARG(__VA_ARGS__), P00_AND, P00_ISIT, __VA_ARGS__)

/**
 ** @brief Check if argument @a FIRST is less than the other elements in the list
 **
 ** Use this as follows:
 ** @code
 ** if (P99_IS_MIN(a, b, c, d, e, f)) {
 **   // a is smallest, do something special
 ** } else {
 **   // handle the base case
 ** }
 ** @endcode
 **/
P00_DOCUMENT_MULTIPLE_ARGUMENT(P99_IS_MIN, 0)
#define P99_IS_MIN(FIRST, ...) P99_FOR(>= (FIRST), P99_NARG(__VA_ARGS__), P00_AND, P00_ISIT, __VA_ARGS__)

/**
 ** @brief Check if argument @a FIRST is less than or equal to the other
 ** elements in the list
 **
 ** Use this as follows:
 ** @code
 ** if (P99_IS_INF(a, b, c, d, e, f)) {
 **   // a is smallest, do something special
 ** } else {
 **   // handle the base case
 ** }
 ** @endcode
 **/
P00_DOCUMENT_MULTIPLE_ARGUMENT(P99_IS_INF, 0)
#define P99_IS_INF(FIRST, ...) P99_FOR(> (FIRST), P99_NARG(__VA_ARGS__), P00_AND, P00_ISIT, __VA_ARGS__)

/**
 ** @brief Check if argument @a FIRST is strictly greater than the other elements in the list
 **
 ** Use this as follows:
 ** @code
 ** if (P99_IS_MAX(a, b, c, d, e, f)) {
 **   // a is largest, do something special
 ** } else {
 **   // handle the base case
 ** }
 ** @endcode
 **/
P00_DOCUMENT_MULTIPLE_ARGUMENT(P99_IS_MAX, 0)
#define P99_IS_MAX(FIRST, ...) P99_FOR(<= (FIRST), P99_NARG(__VA_ARGS__), P00_AND, P00_ISIT, __VA_ARGS__)

/**
 ** @brief Check if argument @a FIRST is greater than or equal to the other
 ** elements in the list
 **
 ** Use this as follows:
 ** @code
 ** if (P99_IS_SUP(a, b, c, d, e, f)) {
 **   // a is largest, do something special
 ** } else {
 **   // handle the base case
 ** }
 ** @endcode
 **/
P00_DOCUMENT_MULTIPLE_ARGUMENT(P99_IS_SUP, 0)
#define P99_IS_SUP(FIRST, ...) P99_FOR(< (FIRST), P99_NARG(__VA_ARGS__), P00_AND, P00_ISIT, __VA_ARGS__)

/**
 ** @brief Check if the arguments in the list are ordered according to
 ** the operation @a OP.
 **
 ** Use this as follows:
 ** @code
 ** if (P99_ARE_ORDERED(<=, a, b, c, d, e, f)) {
 **   // all are in order, do something special
 ** } else {
 **   // handle the base case
 ** }
 ** @endcode
 **/
P00_DOCUMENT_MULTIPLE_ARGUMENT(P99_ARE_ORDERED, 0)
P00_DOCUMENT_MULTIPLE_ARGUMENT(P99_ARE_ORDERED, 1)
P00_DOCUMENT_MULTIPLE_ARGUMENT(P99_ARE_ORDERED, 2)
#define P99_ARE_ORDERED(OP, ...) P00_ARE_ORDERED(OP, P99_NARG(__VA_ARGS__), __VA_ARGS__)

#define P00_ARE_ORDERED(OP, N, ...)                            \
P99_IF_LT(N, 3)                                                \
(P00_ARE_ORDERED2(OP,__VA_ARGS__))                             \
(P00_ARE_ORDERED3(OP, P99_PRED(N), __VA_ARGS__))

#define P00_ARE_ORDERED2(OP, X, Y) (X) OP (Y)

#define P00_ARE_ORDERED3(OP, N, ...)                           \
((P99_SUB(0, 1, __VA_ARGS__))                                  \
 OP P00_ARE_ORDERED_MID(OP, P99_PRED(N), __VA_ARGS__)          \
 OP (P99_SUB(N, 1, __VA_ARGS__)))

#define P00_ARE_ORDERED_MID(OP, N, ...)                                             \
P99_FOR(OP, N, P00_ARE_ORDERED_OP, P00_ARE_ORDERED_AND, P99_SUB(1, N, __VA_ARGS__))

#define P00_ARE_ORDERED_AND(_0, X, _2) (X)) && ((X)
#define P00_ARE_ORDERED_OP(OP, _1, X, Y) X OP Y



/**
 ** @}
 **/

/**
 ** @brief join a list with a specific token given as the first argument
 **
 ** Examples
 ** @code
 ** P99_TOKJOIN(+, 1, 2, 3)  ->  1+2+3
 ** P99_TOKJOIN(., f(), a, length)  ->  f().a.length
 ** @endcode
 **/
P00_DOCUMENT_MULTIPLE_ARGUMENT(P99_TOKJOIN, 0)
#define P99_TOKJOIN(TOK, ...)                                            \
P99_IF_LT(P99_NARG(__VA_ARGS__), 2)                                      \
(__VA_ARGS__)                                                            \
(P99_FOR(TOK, P99_NARG(__VA_ARGS__), P00_TOKJOIN, P00_IDT, __VA_ARGS__))

/**
 ** @ingroup preprocessor_for
 ** @brief Revert the argument list
 **/
#define P99_REVS(...) P00_REVS(P99_NARG(__VA_ARGS__),__VA_ARGS__)

#define P00_REVS(N, ...) P99_PASTE2(P00_REVS_, P99_IS_LT(N, 2))(N, __VA_ARGS__)

#define P00_REVS_0(N, ...) P00_REVS_(N,__VA_ARGS__)
#define P00_REVS_1(N, ...) __VA_ARGS__

/* the general case for an argument list of at least two elements */
#define P00_REVS_(N, ...) P99_FOR(,N, P00_REV, P00_IDT, __VA_ARGS__)

/**
 ** @}
 **/

/**
 ** @ingroup preprocessor_arithmetic
 ** @brief Generate the quotient of non-negative decimal numbers @a A and @a B at
 ** preprocessing time.
 **
 ** @warning Both arguments must be less than the maximum argument list number that
 ** is supported, currently 64.
 **/
#define P99_DIV(A, B) P99_CHS(A, P99_FOR(B, 32, P00_SEQ, P00_IDI, P00_ALL_ONES()))

#define P00_IDI(B, X, I) P99_DUPL(B, I)


#define P00_CDIM_OP(NAME, I, REC, X) (X + ((NAME)[I] * REC))
#define P00_CDIM_FUNC(NAME, X, I) (X)
#define P00_CDIM(N, NAME, ...) P99_FOR(NAME, N, P00_CDIM_OP, P00_CDIM_FUNC, __VA_ARGS__)

/**
 ** @ingroup preprocessor_arithmetic
 ** @brief Compute an absolute index in a multidimensional array in
 ** the same way as C.
 **
 ** If we have @c N arguments after @a NAME, @a NAME must be an array
 ** of type
 ** @code
 ** size_t NAME[N];
 ** @endcode
 ** that hold the side lengths of an @c N dimensional cube. E.g
 ** @code
 ** size_t const D[] = { 3, 4, 7 };
 ** @endcode
 ** corresponds to a cube of side length 3 in dimension 0, 4 in
 ** dimension 1 and 7 in dimension 2, with in total 84 elements.
 ** With that, we get
 ** @code
 ** P99_CDIM(D, 1, 2, 3)  =>  ((3) + ((D)[2] * ((2) + ((D)[1] * (1)))))
 ** P99_CDIM(D, k0, k1, k2)  =>  ((k2) + ((D)[2] * ((k1) + ((D)[1] * (k0)))))
 ** @endcode
 **/
P00_DOCUMENT_MULTIPLE_ARGUMENT(P99_CDIM, 0)
#define P99_CDIM(NAME, ...) P00_CDIM(P99_NARG(__VA_ARGS__), NAME, __VA_ARGS__)


/**
 ** @addtogroup VLA Variable Length Arrays
 ** @{
 **/

#define P00_SUBSCRIPT(X) [X]

/**
 ** @brief Transform the list of arguments <code>x0, x1, ...</code> to array
 ** subscripts <code>[x0][x1]...</code>
 **/
#define P99_SUBSCRIPT(...) P99_SER(P00_SUBSCRIPT, __VA_ARGS__)

#define P99_ARRAY(ARR, ...) (ARR)P99_SUBSCRIPT(__VA_ARGS__)
#define P99_AREF(T, ARR, ...) T P99_ARRAY(*const ARR, __VA_ARGS__)
#define P99_AREF1(T, ARR, ...) T P99_ARRAY(ARR, static const 1, __VA_ARGS__)

#define P00_ALEN0(NAME)                                         \
  ((sizeof(NAME)/sizeof((NAME)[0]))                             \
   /sizeof(char[((!(sizeof(NAME) % sizeof((NAME)[0])))<<1)-1]))

#define P00_ALEN(NAME, _1, I) P99_IF_EQ_0(I)(P00_ALEN0(NAME))(P00_ALEN0((NAME)P99_REP(I,[0])))
#define P00_ALEN2_(NAME, I, ...) P00_ALEN(NAME,,I)
#define P00_ALEN2(NAME, ...) P00_ALEN2_(NAME, __VA_ARGS__,)

#define P00_ALENS0(NAME, I, REC, _3) REC, P00_ALEN(NAME,,I)
/**
 ** @brief Produce a list of the lengths of the argument array @a ARR in terms
 ** of the number of elements in the first @a N dimensions.
 **/
P00_DOCUMENT_PERMITTED_ARGUMENT(P99_ALENS, 0)
P00_DOCUMENT_NUMBER_ARGUMENT(P99_ALENS, 1)
#define P99_ALENS(ARR, N) P99_FOR(ARR, N, P00_ALENS0, P00_ALEN, P99_REP(N,))


/**
 ** @brief Declare a new matrix @a A of base type @a T and with @a N
 ** dimensions as given by @a B
 **/
#define P99_ATYPE(T, A, B, N) P99_AREF(T, A, P99_ALENS(*B, N))


#define P00_AALLOC(...) ((__VA_ARGS__)malloc(sizeof *(__VA_ARGS__){ 0 }))

/**
 ** @brief Allocate a new matrix of base type @a T and with @a N
 ** dimensions as given by @a VB
 **/
P00_DOCUMENT_TYPE_ARGUMENT(P99_AALLOC, 0)
P00_DOCUMENT_PERMITTED_ARGUMENT(P99_AALLOC, 1)
#define P99_AALLOC(T, VB, N) P00_AALLOC(P99_ATYPE(T, , VB, N))

#define P00_ACALL1(ARR) P99_ALENS(*ARR, 1), (ARR)
#define P00_ACALL2(ARR, N) P99_ALENS(*ARR, N), (ARR)
/* The three argument form asserts that pointers to the elements of
   the matrix are assignment compatible to pointers of the indicated type.
   Then we do the cast to the pointer to matrix type that would
   otherwise be dangerous and could hide incompatibilities. */
#define P00_ACALL3(ARR, N, TYPE) P99_ALENS(*ARR, N), ((TYPE (*const)P99_SUBSCRIPT(P99_ALENS(*ARR, N)))(TYPE*const){ &((*ARR)P99_REP(N,[0])) })

/* transform a list of names into size_t declarations */
#define P00_AARG_DECL(X) size_t const X
#define P00_AARG_LIST(N, ...) P99_SEQ(P00_AARG_DECL, __VA_ARGS__)

/* generate a list of size_t's and the declaration of the array
   pointer */
#define P00_AARG_0(T, ARR, DIM, ...) P00_AARG_LIST(DIM, __VA_ARGS__), P99_AREF1(T, ARR, __VA_ARGS__)
#define P00_AARG(T, ARR, DIM, INAME) P00_AARG_0(T, ARR, DIM, P99_NAME(DIM, INAME))

/* capture the special cases do implement default arguments */
#define P00_AARG_3(T, ARR, DIM) P00_AARG(T, ARR, DIM, P99_PASTE(p00_aarg_, ARR))
#define P00_AARG_2(T, ARR) P00_AARG_3(T, ARR, 1)

/* generate a list of size_t's and the declaration of the array
   pointer */
#define P00_ANAME_0(ARR, DIM, ...) __VA_ARGS__, ARR
#define P00_ANAME(ARR, DIM, INAME) P00_ANAME_0(ARR, DIM, P99_NAME(DIM, INAME))

/* capture the special cases do implement default arguments */
#define P00_ANAME_2(ARR, DIM) P00_ANAME(ARR, DIM, P99_PASTE(p00_aarg_, ARR))
#define P00_ANAME_1(ARR) P00_ANAME_2(ARR, 1)

#ifdef P00_DOXYGEN
/**
 ** @brief Produce the length of the argument array @a ARR in terms of number
 ** of elements.
 **
 ** If a second argument @a N is given, it refers to the size of the
 ** Nth dimension of the array.
 **
 ** If @a ARR is actually just a pointer to an array, P99_ALEN(ARR, 0)
 ** is meaningless.
 **/
P00_DOCUMENT_PERMITTED_ARGUMENT(P99_ALEN, 0)
P00_DOCUMENT_NUMBER_ARGUMENT(P99_ALEN, 1)
#define P99_ALEN(ARR, N)

/**
 ** @brief Pass a pointer to an @a N dimensional array @a ARR to a function.
 **
 ** This is not supposed to be used directly but instead is for defining a
 ** macro interface to a function:
 ** @code
 ** double dotproductFunc(P99_AARG(double const, A, 1),
 **                       P99_AARG(double const, B, 1));
 **
 ** #define dotproduct(VA, VB)                                 \
 **   dotproductFunc(P99_ACALL(VA, 1, double const),           \
 **                  P99_ACALL(VB, 1, double const))
 ** .
 ** double Ar[5];
 ** double Br[5];
 ** .
 ** double result = dotproduct(&Ar, &Br);
 ** @endcode
 ** Here the expression with @c dotproduct in the last line will
 ** first result in a macro expansion that will place the pointers as
 ** well as the array sizes to a call of the function @c
 ** dotproductFunc.
 **
 ** If the argument @a N is omitted it will default to 1, indicating
 ** that the array is just one dimensional. If N is greater than 1, a
 ** list of the @a N lengths in the first @a N dimensions of @a ARR is
 ** passed to the function call.
 **
 ** @a TYPE can be omitted in which case no attempt to conform types
 ** will be made. Specifying @a TYPE is particularly helpful if the
 ** type is qualified, that is it has a @c const or @c volatile
 ** qualification as in the example above. If you don't use this macro,
 ** ensuring <code>const</code>ness of multidimensional
 ** arrays is particularly tedious.
 **
 ** To be more precise, the three argument form asserts that pointers
 ** to the elements of the matrix are assignment compatible to
 ** pointers of the indicated type.  Then we do the cast to the
 ** pointer to matrix type that would otherwise be dangerous and could
 ** hide incompatibilities.
 ** @see P99_AARG
 **/
P00_DOCUMENT_PERMITTED_ARGUMENT(P99_ACALL, 0)
P00_DOCUMENT_NUMBER_ARGUMENT(P99_ACALL, 1)
P00_DOCUMENT_TYPE_ARGUMENT(P99_ACALL, 2)
#define P99_ACALL(ARR, N, TYPE)

/**
 ** @brief Declare a pointer to array function argument of basetype @a
 ** TYPE, with name @a NAME, dimension @a DIM and naming scheme for
 ** the length variables @a VAR{0}, ... @a VAR{@a DIM - 1}.
 **
 ** Parameter @a VAR may be omitted such that you will not have access
 ** to the length variables. But you most probably don't need them
 ** since you may use ::P99_ALEN to have these values.
 **
 ** @a DIM defaults to @c 1.
 **
 ** @warning A pointer so declared has the @c const attribute
 ** and thus may not be modified.
 **
 ** If @a TYPE has qualifiers (@c const, @c volatile, @c restrict or
 ** @c _Atomic), the corresponding call to ::P99_ACALL @em must
 ** contain the same qualifiers in the 3rd argument.
 **
 ** @see P99_ACALL
 ** @see P99_ALEN
 **/
P00_DOCUMENT_TYPE_ARGUMENT(P99_AARG, 0)
P00_DOCUMENT_NUMBER_ARGUMENT(P99_AARG, 2)
#define P99_AARG(TYPE, NAME, DIM, VAR)

/**
 ** @brief Declare list of variable names as produced by ::P99_AARG
 **
 ** Parameter @a VAR may be omitted as for :P99_AARG.
 **
 ** @a DIM defaults to @c 1.
 **
 ** @see P99_ACALL
 ** @see P99_ALEN
 **/
P00_DOCUMENT_TYPE_ARGUMENT(P99_ANAME, 0)
P00_DOCUMENT_NUMBER_ARGUMENT(P99_ANAME, 2)
#define P99_ANAME(NAME, DIM, VAR)

#else
P00_DOCUMENT_PERMITTED_ARGUMENT(P99_ALEN, 0)
P00_DOCUMENT_NUMBER_ARGUMENT(P99_ALEN, 1)
#define P99_ALEN(...) P99_IF_EQ_1(P99_NARG(__VA_ARGS__))(P00_ALEN(__VA_ARGS__, ,0))(P00_ALEN2(__VA_ARGS__))
P00_DOCUMENT_PERMITTED_ARGUMENT(P99_ACALL, 0)
P00_DOCUMENT_NUMBER_ARGUMENT(P99_ACALL, 1)
P00_DOCUMENT_TYPE_ARGUMENT(P99_ACALL, 2)
#define P99_ACALL(...)  P99_PASTE2(P00_ACALL, P99_NARG(__VA_ARGS__))(__VA_ARGS__)
P00_DOCUMENT_TYPE_ARGUMENT(P99_AARG, 0)
P00_DOCUMENT_NUMBER_ARGUMENT(P99_AARG, 2)
#define P99_AARG(...) P99_IF_GT(P99_NARG(__VA_ARGS__),3)(P00_AARG(__VA_ARGS__))(P99_PASTE2(P00_AARG_, P99_NARG(__VA_ARGS__))(__VA_ARGS__))
P00_DOCUMENT_TYPE_ARGUMENT(P99_ANAME, 0)
P00_DOCUMENT_NUMBER_ARGUMENT(P99_ANAME, 2)
#define P99_ANAME(...) P99_IF_GT(P99_NARG(__VA_ARGS__),2)(P00_ANAME(__VA_ARGS__))(P99_PASTE2(P00_ANAME_, P99_NARG(__VA_ARGS__))(__VA_ARGS__))

#endif

/**
 ** @example test-p99-pow.c
 ** @brief an example for computations with large matrices
 **
 ** This uses the VLA array passing macros, ::P99_DO and ::P99_PARALLEL_DO
 **/


/** @}
 **/


/**
 ** @ingroup preprocessor_blocks
 ** @brief Declare a @c for loop for which all iterations can be run
 ** independently and out of order.
 **
 ** This can be used syntactically exactly as the keyword @c for,
 ** except that the programmer asserts with this that the depending
 ** statement or block can be executed independently and out of order for all instances.
 **
 ** @code
 ** P99_PARALLEL_FOR (unsigned i = 0; i < limit; ++i) {
 **    unsigned sum = a[i] + b[i];
 **    a[i] *= sum;
 ** }
 ** @endcode
 **
 ** The resulting code may then be parallelized and (if the platform
 ** supports this) multiple threads may be used to speed up the
 ** execution.
 ** @see P99_PARALLEL_PRAGMA for the conditions under which this will
 ** result in a parallel execution.
 **/
#define P99_PARALLEL_FOR _Pragma(P99_PARALLEL_PRAGMA) for


#define P00_PRAGMA_DO(PRAG, TYPE, VAR, LOW, LEN, INCR)                           \
P00_BLK_START                                                                    \
P00_BLK_BEFORE(const TYPE                                                        \
               P99_PASTE2(p00_start_, VAR) = (LOW),                              \
               P99_PASTE2(p00_stop_, VAR) = P99_PASTE2(p00_start_, VAR) + (LEN), \
               P99_PASTE2(p00_incr_, VAR) = (INCR))                              \
P99_PRAGMA(PRAG)                                                                 \
     for (register TYPE P99_PASTE2(p00_i_, VAR) = P99_PASTE2(p00_start_, VAR);   \
          P99_PASTE2(p00_i_, VAR) < P99_PASTE2(p00_stop_, VAR);                  \
          P99_PASTE2(p00_i_, VAR) += P99_PASTE2(p00_incr_, VAR))                 \
       P00_BLK_START                                                             \
         P00_BLK_BEFORE(TYPE const VAR = P99_PASTE2(p00_i_, VAR))

#ifdef P00_DOXYGEN
/**
 ** @ingroup preprocessor_blocks
 ** @brief A fortran like do-loop with bounds that are fixed at the
 ** beginning
 **
 ** @param TYPE is the type of the control variable. It must be an
 ** arithmetic type.
 **
 ** @param VAR is the name of the control variable. It is not mutable
 ** inside the loop, as if it were declared <code>TYPE const
 ** VAR</code>.
 **
 ** @param LOW is the start value of VAR for the first iteration. Only
 ** evaluated once before all iterations. Must be assignment
 ** compatible to type @a TYPE.
 **
 ** @param LEN is the length of the iteration and is
 ** non-inclusive. Only evaluated once before all iterations. Must be
 ** assignment compatible to type @a TYPE.
 **
 ** @param INCR is the increment of VAR after each iteration. Only
 ** evaluated once before all iterations. @a INCR defaults to @c 1 if
 ** omitted. Must be assignment compatible to type @a TYPE.
 **
 ** @code
 ** P99_DO(size_t, i, a, n, inc) {
 **   A[i] *= B[i-1]
 ** }
 ** @endcode
 ** would expand to something similar to
 ** @code
 ** for (size_t i = a; i < (a + n); i += inc) {
 **   A[i] *= B[i-1]
 ** }
 ** @endcode
 **
 ** only that
 ** -  the bounds of the loop (involving @c a and @c n) and the
 ** increment @c inc are fixed once when entering this construct
 ** - the loop variable @c i is not modifiable within the block
 **
 ** @warning Placing a @c #pragma directive directly in front of
 ** ::P99_DO will not work because of syntactic restrictions. Use
 ** ::P99_PRAGMA_DO instead.
 ** @see P99_PARALLEL_DO for a parallel variant of this
 ** @see P99_PRAGMA_DO for a variant of this that can be controlled
 ** with an arbitrary @c #pragma directive.
 **/
#define P99_DO(TYPE, VAR, LOW, LEN, INCR) for(;;)
/**
 ** @ingroup preprocessor_blocks
 ** @brief as ::P99_DO but performs the iterations out of order
 ** @see P99_DO for an explanation of the arguments
 ** @see P99_FOR for a more general parallel iteration construct
 **/
#define P99_PARALLEL_DO(TYPE, VAR, LOW, LEN, INCR) for(;;)
/**
 ** @brief as ::P99_DO but allows you to additionally place a pragma
 ** directive in front of the generated @c for loop
 **
 ** @warning Just placing a @c #pragma directive directly in front of
 ** ::P99_DO will not work because of syntactic restrictions
 **/
#define P99_PRAGMA_DO(PRAG, TYPE, VAR, LOW, LEN, INCR) for(;;)
#else
P00_DOCUMENT_TYPE_ARGUMENT(P99_DO, 0)
#define P99_DO(TYPE, VAR, ...) P99_PRAGMA_DO(, TYPE, VAR, __VA_ARGS__)
P00_DOCUMENT_TYPE_ARGUMENT(P99_PARALLEL_DO, 0)
#define P99_PARALLEL_DO(TYPE, VAR, ...) P99_PRAGMA_DO(P99_PARALLEL_PRAGMA, TYPE, VAR, __VA_ARGS__)
P00_DOCUMENT_TYPE_ARGUMENT(P99_PRAGMA_DO, 1)
#define P99_PRAGMA_DO(PRAG, TYPE, VAR, ...)                    \
P99_IF_EQ(P99_NARG(__VA_ARGS__), 2)                            \
(P00_PRAGMA_DO(PRAG, TYPE, VAR, __VA_ARGS__, 1))               \
(P00_PRAGMA_DO(PRAG, TYPE, VAR, __VA_ARGS__))
#endif

#define P00_FORALL_OP(NAME, I, REC, X) REC X

#define P00_FORALL_FUNC(NAME, X, I) P99_DO(size_t, X, 0, (NAME)[I])

#define P00_FORALL(N, NAME, ...) P99_FOR(NAME, N, P00_FORALL_OP, P00_FORALL_FUNC, __VA_ARGS__)

/**
 ** @ingroup preprocessor_blocks
 ** @brief A multi-index @c for loop
 **
 ** Given the names of @c N identifiers after @a NAME, @a NAME must
 ** correspond to an array of lengths with dimension at least @c N.
 ** @code
 ** size_t NAME[N];
 ** @endcode
 ** For @c N = 3 this could e.g be
 ** @code
 ** size_t const D[] = { 3, 4, 7 };
 ** @endcode
 ** Then, the macro in the following
 ** @code
 ** P99_FORALL(D, i0, i1, i2) {
 **   A[i0][i1][i2] *= B[i0][i1][i2]
 ** }
 ** @endcode
 ** would expand to something similar to
 ** @code
 ** for (size_t i0 = 0; i0 < D[0]; ++i0)
 **   for (size_t i1 = 0; i1 < D[1]; ++i1)
 **     for (size_t i2 = 0; i2 < D[2]; ++i2) {
 **        A[i0][i1][i2] *= B[i0][i1][i2]
 **     }
 ** @endcode
 **
 ** only that
 ** - the bounds of the loops (involving @c D[0], @c D[1] and @c
 **    D[2]) are fixed once when entering this construct
 ** - the loop variables @c i0, @c i1 and @c i2 are not modifiable
 **    within the block
 **
 ** @see P99_PARALLEL_FORALL for a variant that uses OpenMp to parallelize the loop.
 ** @see P99_DO for a simple fortran like iteration
 ** @see P99_CDIM for a macro that computes the absolute position of an
 **   index N-tuple in a multi-dimensional array.
 **/
P00_DOCUMENT_MULTIPLE_ARGUMENT(P99_FORALL, 0)
#define P99_FORALL(NAME, ...) P00_FORALL(P99_NARG(__VA_ARGS__), NAME, __VA_ARGS__)

#define P00_PARALLEL_FORALL_FUNC(NAME, X, I)  P99_PARALLEL_DO(size_t, X, 0, (NAME)[I])
#define P00_PARALLEL_FORALL(N, NAME, ...) P99_FOR(NAME, N, P00_FORALL_OP, P00_PARALLEL_FORALL_FUNC, __VA_ARGS__)

/**
 ** @ingroup preprocessor_blocks
 ** @brief A multi-index @c for loop who's dependent statement or
 ** block may be executed out of order.
 **
 ** This has the same semantics as ::P99_FORALL except that it assumes
 ** the independence of each execution of the statement from every
 ** other.
 **
 ** @see P99_FORALL for a variant that doesn't need that assumption,
 ** i.e where the statements should be executed sequentially in order.
 ** @see P99_PARALLEL_DO for a simple fortran like parallel iteration
 ** @see P99_PARALLEL_FOR for a parallel replacement of @c for
 ** @see P99_CDIM for a macro that computes the absolute position of an
 **   index N-tuple in a multi-dimensional array.
 **/
P00_DOCUMENT_MULTIPLE_ARGUMENT(P99_PARALLEL_FORALL, 0)
#define P99_PARALLEL_FORALL(NAME, ...) P00_PARALLEL_FORALL(P99_NARG(__VA_ARGS__), NAME, __VA_ARGS__)


#define P00_CASERANGE0(NAME, X, I) case ((NAME)+I):
#define P00_CASERANGE3(START, LEN, LABEL)                          \
if (0) {                                                           \
  /* Execution will only go here if one of the cases is chosen. */ \
  P99_FOR(START, LEN, P00_SEP, P00_CASERANGE0, P99_REP(LEN,))      \
    /* Then it just continues with the else part */                \
    goto LABEL;                                                    \
 } else                                                            \
  /* execution will just fall through, here, if a previous case    \
     matched */                                                    \
  LABEL

#define P00_CASERANGE1(START, LEN, ...) P00_CASERANGE3(START, LEN, P99_UNIQ(__VA_ARGS__, caselabel))
#define P00_CASERANGE2(START, LEN) P00_CASERANGE3(START, LEN, P99_UNIQ(caselabel))


#ifdef P00_DOXYGEN
/**
 ** @ingroup preprocessor_blocks
 ** @brief implement a range syntax for case labels.
 **
 ** gcc has an analogous extension to the C syntax. Something like
 ** @code
 ** case '0'..'9': return 23;
 ** @endcode
 ** This implementation uses macros and consequently should
 ** be more portable.
 ** @code
 ** switch (argv[0][0]) {
 **   P99_CASERANGE('\0', 0): return -1;
 **   P99_CASERANGE('0', 10): return 0;
 **   P99_CASERANGE('A', 25): --argc;
 **   P99_CASERANGE('.', 0):  return -1;
 **   P99_CASERANGE('a', 25,  oioi): return 2;
 **   default: return 3;
 ** }
 ** @endcode
 **
 ** @param START must evaluate to an expression that can be used as a case label
 **
 ** @param LEN must evaluate to a decimal number. If this is 0 the
 ** depending statement will never be reached as a direct jump to the
 ** "label". Depending on the flow for the other cases the statement
 ** may or may not be reachable when falling through from a previous
 ** case.  In the example above, for the first range @c '\0' is not
 ** reachable. But the range for @c '.' is reachable after the
 ** execution of the range starting with @c 'A'.
 **
 ** The additional variable argument list is optional and is used to
 ** "name" the range. This is only necessary if you have more than one
 ** P99_CASERANGE on the same logical line of code.
 **
 ** This is intended to have the same flow control rules as if there
 ** were just @em one case label in front of @em one statement. In
 ** particular, the dependent statement may just be a @c break to
 ** break out of the enclosing @c switch.
 **/
#define P99_CASERANGE(START, LEN, ...)
#else
P00_DOCUMENT_PERMITTED_ARGUMENT(P99_CASERANGE, 0)
P00_DOCUMENT_NUMBER_ARGUMENT(P99_CASERANGE, 1)
#define P99_CASERANGE(START, ...)                              \
P99_IF_LT(P99_NARG(__VA_ARGS__), 2)                            \
(P00_CASERANGE2(START, __VA_ARGS__))                           \
(P00_CASERANGE1(START, __VA_ARGS__))
#endif


#define P00_STRUCT_TYPENAME(BASE, DECL) P99_PASTE3(DECL, _P99_typedef_of_, BASE)
#define P00_STRUCT_TYPEDEF(BASE, DECL, I) typedef P00_STRUCT_TYPENAME(BASE, DECL)
#define P00_STRUCT_TYPEDEFS(NAME, ...) P99_FOR(NAME, P99_NARG(__VA_ARGS__), P00_SEP, P00_STRUCT_TYPEDEF, __VA_ARGS__)


/**
 ** @ingroup types
 ** @brief Declare a structure of name @a NAME composed of the
 ** field declarations that are given in the remaining arguments.
 **
 ** For this to work the argument list must contain the declaration of
 ** the fields, one per argument.
 **
 ** @remark The declarations must be such that the name of the field
 ** is at the end of the declaration.
 **
 ** @see P99_STRUCT_USE to see how to lift all or parts of the fields
 ** that are defined here as local variables on the stack of the
 ** current function.
 **/
#define P99_DEFINE_STRUCT(NAME, ...)                           \
struct NAME {                                                  \
  P99_SEP(P00_IDENT, __VA_ARGS__);                             \
};                                                             \
P00_STRUCT_TYPEDEFS(NAME, __VA_ARGS__)


#define P00_STRUCT_USE3(TYPE, VAR, NAME) P00_STRUCT_TYPENAME(TYPE, NAME) NAME = (VAR)->NAME
#define P00_STRUCT_USE2(PAIR, NAME) P00_STRUCT_USE3(PAIR, NAME)
#define P00_STRUCT_USE(PAIR, NAME, I) P00_STRUCT_USE2(P00_ROBUST PAIR, NAME)

/**
 ** @ingroup types
 ** @brief Use the fields of variable @a VAR of type @a TYPE
 **
 ** This "lifts" the fields of @a VAR as local variables onto the
 ** local stack and copies their value into these local variables.
 **
 ** @see P99_STRUCT_UNUSE to restore changed values back into @a VAR.
 **/
P00_DOCUMENT_TYPE_IDENTIFIER_ARGUMENT(P99_STRUCT_USE, 0)
P00_DOCUMENT_IDENTIFIER_ARGUMENT(P99_STRUCT_USE, 1)
P00_DOCUMENT_IDENTIFIER_ARGUMENT(P99_STRUCT_USE, 2)
P00_DOCUMENT_IDENTIFIER_ARGUMENT(P99_STRUCT_USE, 3)
P00_DOCUMENT_IDENTIFIER_ARGUMENT(P99_STRUCT_USE, 4)
#define P99_STRUCT_USE(TYPE, VAR, ...) P99_FOR((TYPE, VAR), P99_NARG(__VA_ARGS__), P00_SEP, P00_STRUCT_USE, __VA_ARGS__)

#define P00_STRUCT_UNUSE3(TYPE, VAR, NAME) P00_STRUCT_TYPENAME(TYPE, NAME) (VAR)->NAME = NAME
#define P00_STRUCT_UNUSE2(PAIR, NAME) P00_STRUCT_UNUSE3(PAIR, NAME)
#define P00_STRUCT_UNUSE(PAIR, NAME, I) P00_STRUCT_UNUSE2(P00_ROBUST PAIR, NAME)

/**
 ** @ingroup types
 ** @brief Copy local variables back to the fields of variable @a VAR.
 **
 ** @see P99_STRUCT_USE
 **/
P00_DOCUMENT_TYPE_IDENTIFIER_ARGUMENT(P99_STRUCT_UNUSE, 0)
P00_DOCUMENT_IDENTIFIER_ARGUMENT(P99_STRUCT_UNUSE, 1)
P00_DOCUMENT_IDENTIFIER_ARGUMENT(P99_STRUCT_UNUSE, 2)
P00_DOCUMENT_IDENTIFIER_ARGUMENT(P99_STRUCT_UNUSE, 3)
P00_DOCUMENT_IDENTIFIER_ARGUMENT(P99_STRUCT_UNUSE, 4)
#define P99_STRUCT_UNUSE(TYPE, VAR, ...) P99_FOR((TYPE, VAR), P99_NARG(__VA_ARGS__), P00_SEP, P00_STRUCT_UNUSE, __VA_ARGS__)

#define P00_LITERAL(NAME) .NAME = NAME

/**
 ** @ingroup types
 ** @brief Copy local variables back to the fields of same name inside a literal.
 **
 ** @see P99_DEFINE_STRUCT
 **/
P00_DOCUMENT_IDENTIFIER_ARGUMENT(P99_LITERAL, 0)
P00_DOCUMENT_IDENTIFIER_ARGUMENT(P99_LITERAL, 1)
P00_DOCUMENT_IDENTIFIER_ARGUMENT(P99_LITERAL, 2)
P00_DOCUMENT_IDENTIFIER_ARGUMENT(P99_LITERAL, 3)
#define P99_LITERAL(...) P99_SEQ(P00_LITERAL, __VA_ARGS__)


/**
 ** @ingroup types
 ** @brief Copy local variables back to the fields of same name inside
 ** a compound literal of type @a TYPE.
 **
 ** @see P99_DEFINE_STRUCT
 **/
P00_DOCUMENT_IDENTIFIER_ARGUMENT(P99_STRUCT_LITERAL, 0)
P00_DOCUMENT_IDENTIFIER_ARGUMENT(P99_STRUCT_LITERAL, 1)
P00_DOCUMENT_IDENTIFIER_ARGUMENT(P99_STRUCT_LITERAL, 2)
P00_DOCUMENT_IDENTIFIER_ARGUMENT(P99_STRUCT_LITERAL, 3)
#define P99_STRUCT_LITERAL(TYPE, ...) (TYPE){ P99_SEQ(P00_LITERAL, __VA_ARGS__) }

#define P00_STRUCT_TYPES(TYPE, NAME, I) P00_STRUCT_TYPENAME(TYPE, NAME)

/**
 ** @ingroup types
 ** @brief Transform the argument list into a list of field types for
 ** type @a TYPE.
 **
 ** @see P99_DEFINE_STRUCT
 **/
P00_DOCUMENT_TYPE_IDENTIFIER_ARGUMENT(P99_STRUCT_TYPES, 0)
P00_DOCUMENT_IDENTIFIER_ARGUMENT(P99_STRUCT_TYPES, 1)
P00_DOCUMENT_IDENTIFIER_ARGUMENT(P99_STRUCT_TYPES, 2)
P00_DOCUMENT_IDENTIFIER_ARGUMENT(P99_STRUCT_TYPES, 3)
P00_DOCUMENT_IDENTIFIER_ARGUMENT(P99_STRUCT_TYPES, 4)
#define P99_STRUCT_TYPES(TYPE, ...) P99_FOR(TYPE, P99_NARG(__VA_ARGS__), P00_SEQ, P00_STRUCT_TYPES, __VA_ARGS__)

#define P00_STRUCT_TYPE0(TYPE, NAME, I) P99_0(P00_STRUCT_TYPENAME(TYPE, NAME))

/**
 ** @ingroup types
 ** @brief Transform the argument list into a list of lvalue for the
 ** fields of type @a TYPE.
 **
 ** @see P99_DEFINE_STRUCT
 **/
P00_DOCUMENT_TYPE_IDENTIFIER_ARGUMENT(P99_STRUCT_TYPE0, 0)
P00_DOCUMENT_IDENTIFIER_ARGUMENT(P99_STRUCT_TYPE0, 1)
P00_DOCUMENT_IDENTIFIER_ARGUMENT(P99_STRUCT_TYPE0, 2)
P00_DOCUMENT_IDENTIFIER_ARGUMENT(P99_STRUCT_TYPE0, 3)
P00_DOCUMENT_IDENTIFIER_ARGUMENT(P99_STRUCT_TYPE0, 4)
#define P99_STRUCT_TYPE0(TYPE, ...) P99_FOR(TYPE, P99_NARG(__VA_ARGS__), P00_SEQ, P00_STRUCT_TYPE0, __VA_ARGS__)


#define P00_MAC_ARGS_TYPE_(NAME, EXP, QUAL, ...) __typeof__(EXP)
#define P00_MAC_ARGS_EXP_(NAME, EXP, QUAL, ...) (EXP)
#define P00_MAC_ARGS_QUAL_(NAME, EXP, QUAL, ...) QUAL

#define P00_MAC_ARGS_NAME(NAME, ...) NAME
#define P00_MAC_ARGS_TYPE(...) P00_MAC_ARGS_TYPE_(__VA_ARGS__,)

#define P00_MAC_ARGS_EXP(...) P00_MAC_ARGS_EXP_(__VA_ARGS__,)

#define P00_MAC_ARGS_QUAL(...) P00_MAC_ARGS_QUAL_(__VA_ARGS__,)

#define P00_MAC_ARGS_REAL0(_0, PAIR, I)                        \
P00_MAC_ARGS_TYPE PAIR                                         \
P00_MAC_ARGS_QUAL PAIR                                         \
P99_PASTE2(p00_mac_arg_, I)                                    \
= P00_MAC_ARGS_EXP PAIR

#define P00_MAC_ARGS_REAL1(_0, PAIR, I)                        \
P00_MAC_ARGS_TYPE PAIR                                         \
P00_MAC_ARGS_QUAL PAIR                                         \
P00_MAC_ARGS_NAME PAIR                                         \
  = P99_PASTE2(p00_mac_arg_, I)

/**
 ** @ingroup preprocessor_initialization
 **
 ** @brief Declare macro parameters as local variables as if the macro
 ** were declared as a type generic @c inline function.
 **
 ** @remark This uses the @c __typeof__ extension implemented
 ** by gcc.
 **
 ** This receives parenthesized pairs of name and value that are to be
 ** promoted as local variables inside a macro expansion. Use this as
 ** follows:
 ** @code
 ** #define atomic_fetch_add_conditional(OBJP, OPERAND)        \
 ** ({                                                         \
 ** P99_MAC_ARGS((p00_objp, OBJP), (p00_op, OPERAND));         \
 ** ...                                                        \
 ** })
 ** @endcode
 **
 ** @remark The corresponding local variables have exactly the type of
 ** the expressions that are passed as the 2nd element in each pair.
 **
 ** This achieves several objectives
 ** - Each macro parameter is evaluated exactly once.
 **
 ** - The values of the macro parameters are accessible through an
 **   ordinary identifier.
 **
 ** - Even if a variable with one of the names is passed through a
 **   macro parameter (e.g by calling
 **   <code>atomic_fetch_add_conditional(p00_op->next, 23)</code>)
 **   there will be no conflict.
 **
 ** This is done by evaluating all macro arguments first, as it would
 ** be for a function call, and then assigning it to fresh variables.
 **/
P00_DOCUMENT_PERMITTED_ARGUMENT(P99_MAC_ARGS, 0)
P00_DOCUMENT_PERMITTED_ARGUMENT(P99_MAC_ARGS, 1)
P00_DOCUMENT_PERMITTED_ARGUMENT(P99_MAC_ARGS, 2)
#define P99_MAC_ARGS(...)                                                   \
P99_FOR(, P99_NARG(__VA_ARGS__), P00_SEP, P00_MAC_ARGS_REAL0, __VA_ARGS__); \
P99_FOR(, P99_NARG(__VA_ARGS__), P00_SEP, P00_MAC_ARGS_REAL1, __VA_ARGS__)

#define P00_MACRO_VAR(NAME, EXP, ...)                                 \
__typeof__(EXP) __VA_ARGS__ P99_PASTE2(p00_macro_var_, NAME) = (EXP), \
  NAME = P99_PASTE2(p00_macro_var_, NAME)

#define P00_MACRO_PVAR(NAME, EXP, ...)                                    \
__typeof__(*(EXP)) __VA_ARGS__* P99_PASTE2(p00_macro_var_, NAME) = (EXP), \
  * NAME = P99_PASTE2(p00_macro_var_, NAME)

#ifdef DOXYGEN
/**
 ** @brief Define a variable with @a NAME that has the type and value of
 ** @a EXPR.
 **
 ** If @a QUAL is given it must be a qualifier list that is added to
 ** the resulting type.
 **
 ** @remark Other than just redeclaring @a NAME this macro is safe
 ** even if @a EXPR contains the evaluation of a variable of the same
 ** name @a NAME.
 **
 ** This is achieved by declaring two variables, one with a dummy name
 ** that receives @a EXPR as an initializer (so there can't be a name
 ** conflict), and then @a NAME that is initialized with the
 ** first. Any normal optimizer should optimize that auxiliary
 ** variable out.
 **/
P00_DOCUMENT_IDENTIFIER_ARGUMENT(P99_MACRO_VAR, 0)
P00_DOCUMENT_PERMITTED_ARGUMENT(P99_MACRO_VAR, 1)
# define P99_MACRO_VAR(NAME, EXPR, QUAL)
/**
 ** @brief Define a variable with @a NAME that has the type and value of
 ** @a EXPR, where @a EXPR is of a pointer type.
 **
 ** If @a QUAL is given it must be a qualifier list that is
 ** added to the type @a EXPR is pointing to.
 **
 ** @remark Other than just redeclaring @a NAME this macro is safe
 ** even if @a EXPR contains the evaluation of a variable of the same
 ** name @a NAME.
 **
 ** This is achieved by declaring two variables, one with a dummy name
 ** that receives @a EXPR as an initializer (so there can't be a name
 ** conflict), and then @a NAME that is initialized with the
 ** first. Any normal optimizer should optimize that auxiliary
 ** variable out.
 **/
P00_DOCUMENT_IDENTIFIER_ARGUMENT(P99_MACRO_PVAR, 0)
P00_DOCUMENT_PERMITTED_ARGUMENT(P99_MACRO_PVAR, 1)
# define P99_MACRO_PVAR(NAME, EXPR, QUAL)
#else
P00_DOCUMENT_IDENTIFIER_ARGUMENT(P99_MACRO_VAR, 0)
P00_DOCUMENT_PERMITTED_ARGUMENT(P99_MACRO_VAR, 1)
# define P99_MACRO_VAR(NAME, ...)                              \
P99_IF_EQ_1(P99_NARG(__VA_ARGS__))                             \
(P00_MACRO_VAR(NAME, __VA_ARGS__,))                            \
(P00_MACRO_VAR(NAME, __VA_ARGS__))

P00_DOCUMENT_IDENTIFIER_ARGUMENT(P99_MACRO_PVAR, 0)
P00_DOCUMENT_PERMITTED_ARGUMENT(P99_MACRO_PVAR, 1)
# define P99_MACRO_PVAR(NAME, ...)                             \
P99_IF_EQ_1(P99_NARG(__VA_ARGS__))                             \
(P00_MACRO_PVAR(NAME, __VA_ARGS__,))                           \
(P00_MACRO_PVAR(NAME, __VA_ARGS__))
#endif

#endif      /* !P99_FOR_H_ */
