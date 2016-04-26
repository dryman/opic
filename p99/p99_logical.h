/* This may look like nonsense, but it really is -*- mode: C -*-              */
/*                                                                            */
/* Except for parts copied from previous work and as explicitly stated below, */
/* the author and copyright holder for this work is                           */
/* (C) copyright  2010-2013 Jens Gustedt, INRIA, France                       */
/*                                                                            */
/* This file is free software; it is part of the P99 project.                 */
/* You can redistribute it and/or modify it under the terms of the QPL as     */
/* given in the file LICENSE. It is distributed without any warranty;         */
/* without even the implied warranty of merchantability or fitness for a      */
/* particular purpose.                                                        */
/*                                                                            */
#ifndef     P99_LOGICAL_H_
# define    P99_LOGICAL_H_

/**
 ** @file
 **
 ** @brief macros to handle Boolean conditions at compile time.
 **/

#include "p99_args.h"
#include "p99_list.h"

/**
 ** @addtogroup preprocessor_operators Preprocessor operations
 **
 ** @brief Preprocessor macros that perform simple operations on there
 ** arguments, such as Boolean, arithmetic or text.
 **/

/**
 ** @addtogroup preprocessor_logic Preprocessor Boolean operations
 **
 ** @brief Preprocessor macros that return tokens 0 or 1 according to
 ** the evaluation of their arguments.
 ** @{
 **/

/**
 ** @brief Determine if the two tokens @a _0 and @a _1 are equal
 **
 ** For a specific token X to work with this, a macro @c
 ** P00_IS_X_EQ_X must have been declared and expand to a comma.
 **/
#define P99_IS_EQ(_0, _1) P99_HAS_COMMA(P99_PASTE4(P00_IS_, _0, _EQ_, _1)())


/**
 ** @brief Do a evaluation of the argument.
 **
 ** The result is the token 0 (seen here as `false') if the argument
 ** was empty or if it evaluated to the token 0. Otherwise returns the
 ** token 1.
 **
 ** @return tokens 0 or 1
 **/
#define P99_LOGIC_EVAL(_0) P00_EVAL_0(P99_IS_EMPTY(_0), P99_IS_EQ_0(_0))

#define P00_EVAL_0(_0, _1) P99_PASTE3(P00_EVAL_, _0, _1)

#define P00_EVAL_00 1
#define P00_EVAL_10 0
#define P00_EVAL_01 0
/* should never happen */
#define P00_EVAL_11 WEIRD_EVALUATION_ERROR

/**
 ** @brief Do a logical negation of the argument.
 **
 ** The result is the token 1 (seen here as `true') if the argument
 ** was empty or if it evaluated to the token 0. Otherwise returns the
 ** token 0.
 **
 ** @return tokens 0 or 1
 **/
#define P99_LOGIC_NOT(A)  P00_NOT_0(P99_IS_EMPTY(_0), P99_IS_EQ_0(_0))

#define P00_NOT_0(_0, _1) P99_PASTE3(P00_NOT_, _0, _1)

#define P00_NOT_00 1
#define P00_NOT_10 0
#define P00_NOT_01 1
/* should never happen */
#define P00_NOT_11 WEIRD_NEGATION_ERROR

/**
 ** @brief Do a logical exclusive or of the arguments.
 **
 ** @see P99_LOGIC_EVAL for how the individual arguments are considered to
 ** be truth values.
 **
 ** @return tokens 0 or 1
 **/
#define P99_LOGIC_XOR(A, B) P99_IS_EQ(P99_LOGIC_NOT(A), P99_LOGIC_EVAL(B))


/**
 ** @brief Do a logical inclusive or of the arguments.
 **
 ** @see P99_LOGIC_EVAL for how the individual arguments are considered to
 ** be truth values.
 **
 ** @return tokens 0 or 1
 **/
#define P99_LOGIC_OR(A, B) P00_LOGIC_OR(P99_LOGIC_EVAL(A), P99_LOGIC_EVAL(B))


#define P00_LOGIC_OR(_0, _1) P99_PASTE3(P00_LOGIC_OR_, _0, _1)

#define P00_LOGIC_OR_00 0
#define P00_LOGIC_OR_10 1
#define P00_LOGIC_OR_01 1
#define P00_LOGIC_OR_11 1

/**
 ** @brief Do a logical and of the arguments.
 **
 ** @see P99_LOGIC_EVAL for how the individual arguments are considered to
 ** be truth values.
 **
 ** @return tokens 0 or 1
 **/
#define P99_LOGIC_AND(A, B) P00_LOGIC_AND(P99_LOGIC_EVAL(A), P99_LOGIC_EVAL(B))


#define P00_LOGIC_AND(_0, _1) P99_PASTE3(P00_LOGIC_AND_, _0, _1)

#define P00_LOGIC_AND_00 0
#define P00_LOGIC_AND_10 0
#define P00_LOGIC_AND_01 0
#define P00_LOGIC_AND_11 1



/**
 ** @def P99_IS_EQ_void(...)
 ** @see P99_IS_VOID for a macro that test whether or not its argument is
 ** empty @b or if it consists of the word @c void.
 **/


/**
 ** @brief Test whether or not its argument is empty @b or if it
 ** consists of the word @c void.
 **
 ** @see P99_IF_void for a macro that tests if the argument is exactly the
 ** word @c void.
 **/
#define P99_IS_VOID(...) P00_IS_VOID(P99_IS_EMPTY(__VA_ARGS__), P99_IS_EQ_void(__VA_ARGS__))

#define P00_IS_VOID(_0, _1) P99_PASTE3(P00_IS_VOID_, _0, _1)

#define P00_IS_VOID_00 0
#define P00_IS_VOID_01 1
#define P00_IS_VOID_10 1
/* should not happen */
#define P00_IS_VOID_11 WEIRD_VOID_ARG_ERROR

#define P99_IS_INT(...) P00_IS_INT(P99_IS_EQ_signed(__VA_ARGS__), P99_IS_EQ_int(__VA_ARGS__))

#define P00_IS_INT(_0, _1) P99_PASTE3(P00_IS_INT_, _0, _1)

#define P00_IS_INT_00 0
#define P00_IS_INT_01 1
#define P00_IS_INT_10 1
/* should not happen */
#define P00_IS_INT_11 WEIRD_INT_ARG_ERROR

#define P99_IF_INT(TOK) P99_IF_EQ_1(P99_IS_INT(TOK))

/** @brief a decimal less than operator **/
#define P99_IS_LT(_0, _1)  P00_LT( P99_IS_EQ_0(_1), P99_CHS(_0, P99_SELS(_1, P00_ALL_ONES()), P00_ALL_ZEROES()))
#define P00_LT(_0, _1)  P99_PASTE2(P00_LT_, _0)(_1)

#define P00_LT_0(_0) _0
#define P00_LT_1(_0) 0

/** @brief a decimal greater or equal operator **/
#define P99_IS_GE(_0, _1)  P00_GE( P99_IS_EQ_0(_1), P99_CHS(_0, P99_SELS(_1, P00_ALL_ZEROES()), P00_ALL_ONES()))
#define P00_GE(_0, _1)  P99_PASTE2(P00_GE_, _0)(_1)

#define P00_GE_0(_0) _0
#define P00_GE_1(_0) 1

/** @brief a decimal greater than operator **/
#define P99_IS_GT(_0, _1)  P99_IS_LT(_1, _0)
/** @brief a decimal less or equal operator **/
#define P99_IS_LE(_0, _1)  P99_IS_GE(_1, _0)

/**
 ** @}
 **/

/**
 ** @addtogroup preprocessor_arithmetic Preprocessor arithmetic operations
 **
 ** @brief Preprocessor macros that perform simple arithmetic on
 ** decimal arguments.
 **
 ** These are only implemented for small numbers, currently the limit
 ** is somewhere around ::P99_MAX_NUMBER
 ** @{
 **/

/**
 ** @brief add two decimal numbers
 **/
#define P99_ADD(_0, _1)                                        \
P00_ADD_(_0, _1,                                               \
         P99_IS_EQ_0(_0),                                      \
         P99_IS_EQ_0(_1),                                      \
         P99_NARG(                                             \
                  P99_SELS(_0, P00_ALL_ZEROES()),              \
                  P99_SELS(_1, P00_ALL_ZEROES())))


#define P00_ADD_(_0, _1, _2, _3, _4) P99_PASTE3(P00_ADD_, _2, _3)(_0, _1, _4)

#define P00_ADD_00(_0, _1, _2) _2
#define P00_ADD_01(_0, _1, _2) _0
#define P00_ADD_10(_0, _1, _2) _1
#define P00_ADD_11(_0, _1, _2) 0


/**
 ** @brief substract two decimal numbers
 **
 ** If the result is negative, a token of the form @c minus_NNN is
 ** returned where @c NNN would be the result of
 ** @code
 ** P99_MINUS(_1, _0)
 ** @endcode
 **/
#define P99_MINUS(_0, _1) P00_MINUS(_0, _1, P99_IS_EQ(_0, _1), P99_IS_EQ_0(_0), P99_IS_EQ_0(_1))
#define P00_MINUS(_0, _1, _2, _3, _4) P99_PASTE4(P00_MINUS_, _2, _3, _4)(_0, _1)

#define P00_MINUS_000(_0, _1) P00_MINUS_(_0, _1, P99_IS_LT(_0, _1))
/* if one of _0 or _1 is 0, there is not much to do */
#define P00_MINUS_001(_0, _1) _0
#define P00_MINUS_010(_0, _1) P99_PASTE2(minus_, _1)
/* should not occur */
#define P00_MINUS_011(_0, _1) P99_WEIRD_MINUS_ARG_ERROR
/* whenever _0 and _1 are equal there is nothing to do */
#define P00_MINUS_100(_0, _1) 0
#define P00_MINUS_101(_0, _1) 0
#define P00_MINUS_110(_0, _1) 0
#define P00_MINUS_111(_0, _1) 0

#define P00_MINUS_(_0, _1, _2) P99_PASTE2(P00_MINUS_, _2)(_0, _1)

#define P00_MINUS_0(_0, _1) P00_MINUS__(_0, _1)
#define P00_MINUS_1(_0, _1) P99_PASTE2(minus_, P00_MINUS__(_1, _0))



/* The general case both are non-zero and _0 is strictly greater than _1 */
#define P00_MINUS__(_0, _1) P99_NARG(P99_SKP(_1, P99_SELS(_0, P00_ALL_ZEROES())))


/**
 ** @brief Macro that expands to the predecessor of decimal constant
 ** @a N
 **/
#define P99_PRED(N) P00_PRED(N)
#define P00_PRED(N) P00__PRED(P00_PRED_ , N)
#define P00__PRED(P, N) P ## N

#define P00_PRED_0 minus_1

/**
 ** @brief evaluate the result of one of the arithmetic preprocessor
 **/
#define P99_EVAL(EDEC) P99_PASTE2(P00_dec_eval_, EDEC)


/**
 ** @brief Generate the product of non-negative decimal numbers @a A and @a B at
 ** preprocessing time.
 **
 ** @warning The result must be less than the maximum argument list number that
 ** is supported, currently 64.
 **/
#define P99_MUL(A, B) P99_PASTE3(P00_MUL_, P99_IS_EQ_0(A), P99_IS_EQ_0(B))(A, B)

#define P00_MUL_00(A, B) P99_NARG(P99_DUPL(A, P99_SELS(B, P00_ALL_ONES())))
#define P00_MUL_01(A, B) 0
#define P00_MUL_10(A, B) 0
#define P00_MUL_11(A, B) 0


/**
 ** @brief Generate the modulus of non-negative decimal numbers @a A and @a B at
 ** preprocessing time.
 **
 ** @warning Both arguments must be less than the maximum argument list number that
 ** is supported, currently 64.
 **/
#define P99_MOD(A, B) P00_MOD(A, P99_DUPL(32, P99_SELS(B, P00_ASCENDING())))
#define P00_MOD(A, ...) P99_CHS(A, __VA_ARGS__)

/**
 ** @}
 **/


/** @addtogroup basic_list_operations
 **
 ** @{
 **/


/**
 ** @brief Obtain the last element of a list.
 **/
#define P99_LAST(...) P99_CHS(P99_PRED(P00_NARG(__VA_ARGS__)), __VA_ARGS__,)

/**
 ** @brief Obtain all elements but the last of a list.
 **/
#define P99_ALLBUTLAST(...) P99_PASTE2(P00_PRE,P99_PRED(P00_NARG(__VA_ARGS__)))(__VA_ARGS__,)

#define P00__PASTE(F, N, ...) F ## N(__VA_ARGS__)
#define P00_PASTE(N, ...) P00__PASTE(P99_PASTE, N, __VA_ARGS__)


/**
 ** @ingroup list_processing preprocessor_text
 ** @brief A left-to-right associative paste operator.
 **
 ** This macro avoids the ambiguity of the @c ## preprocessor operator
 ** which has no well defined associativity. With this macro here
 ** something like
 ** @code
 ** P99_PASTE(0.1E, -, 1)
 ** @endcode
 ** is guaranteed to produce the token @c 0.1E-1, whereas the
 ** seemingly equivalent
 ** @code
 ** ETSAP(0.1E, -, 1)
 ** @endcode
 ** is not valid: the intermediate operation to paste tokens `-' and
 ** `1' would result in an invalid token and is thus rejected.
 **
 ** This macro does the evaluation of the arguments first and
 ** then proceeds at the concatenation of the results.
 ** @pre the argumentlist should not be empty.
 **/
#define P99_PASTE(...) P00_PASTE(P00_NARG(__VA_ARGS__), __VA_ARGS__)

#define P00_EAT_FIRST(SEQ) P00_EAT_ ## SEQ

#define P00_STARTS(TOK, SEQ) P99_IS_EQ(2, P99_NARG(P99_PASTE4(P00_TOK_, TOK, _STARTS_, SEQ)))


/** @}
 **/


#endif      /* !P99_LOGICAL_H_ */
