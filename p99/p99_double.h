/* This may look like nonsense, but it really is -*- mode: C -*-              */
/*                                                                            */
/* Except for parts copied from previous work and as explicitly stated below, */
/* the authors and copyright holders for this work are as follows:            */
/* (C) copyright  2010-2011 Jens Gustedt, INRIA, France                       */
/* (C) copyright  2012 William Morris                                         */
/*                                                                            */
/* This file is free software; it is part of the P99 project.                 */
/* You can redistribute it and/or modify it under the terms of the QPL as     */
/* given in the file LICENSE. It is distributed without any warranty;         */
/* without even the implied warranty of merchantability or fitness for a      */
/* particular purpose.                                                        */
/*                                                                            */
#ifndef     P99_DOUBLE_H_
# define    P99_DOUBLE_H_

#include "p99_if.h"

/**
 ** @file
 ** @brief Build decimal or hexadecimal @c double constants with macros
 **/

/**
 ** @addtogroup double_constants  Decimal or hexadecimal double constants
 **
 ** Since not all substrings of a double constant form a valid
 ** preprocessor token, construction of @c double constants must be
 ** done carefully when macros are used. The macros here guarantee
 ** that this is done in a portable way.
 ** @{
 */

#define P00_DEC_DOUBLE(SIGN, INT, FRAC, ESIGN, EXP, ...)       \
  P99_IF_EMPTY(SIGN)(+)(SIGN)P00_SKIP_ P99_PASTE(              \
  P99_IF_EMPTY(INT)(0)(INT),                                   \
  .,                                                           \
  P99_IF_EMPTY(FRAC)(0)(FRAC),                                 \
  E,                                                           \
  P99_IF_EMPTY(ESIGN)(+)(ESIGN),                               \
  P99_IF_EMPTY(EXP)(0)(EXP),                                   \
  __VA_ARGS__)

#ifdef P00_DOXYGEN
/**
 ** @brief construct a @c double constant in decimal representation.
 **
 ** @param SIGN the sign of the constant, (+)
 ** @param INT the integer part, (0)
 ** @param FRAC the fractional part, (0)
 ** @param ESIGN sign of the exponent, (+)
 ** @param EXP exponent in decimal, (0)
 **
 ** So if all parameters are empty such as
 ** @code
 ** P99_DEC_DOUBLE()
 ** P99_DEC_DOUBLE(,,,,)
 ** @endcode
 ** this produces @c +0.0E+0
 **/
#define P99_DEC_DOUBLE(SIGN, INT, FRAC, ESIGN, EXP)
#else
P00_DOCUMENT_NUMBER_ARGUMENT(P99_DEC_DOUBLE, 1)
P00_DOCUMENT_NUMBER_ARGUMENT(P99_DEC_DOUBLE, 2)
P00_DOCUMENT_NUMBER_ARGUMENT(P99_DEC_DOUBLE, 4)
#define P99_DEC_DOUBLE(...)                                    \
  P99_IF_GE(P99_NARG(__VA_ARGS__), 6)                          \
  (P00_DEC_DOUBLE(__VA_ARGS__))                                \
  (P00_DEC_DOUBLE(__VA_ARGS__,,,,,))
#endif


#define P00_HEX_DOUBLE(SIGN, HEXINT, HEXFRAC, ESIGN, BINEXP, ...) \
  P99_IF_EMPTY(SIGN)(+)(SIGN)P00_SKIP_ P99_PASTE(                 \
  0x,                                                             \
  P99_IF_EMPTY(HEXINT)(0)(HEXINT),                                \
  .,                                                              \
  P99_IF_EMPTY(HEXFRAC)(0)(HEXFRAC),                              \
  P,                                                              \
  P99_IF_EMPTY(ESIGN)(+)(ESIGN),                                  \
  P99_IF_EMPTY(BINEXP)(0)(BINEXP),                                \
  __VA_ARGS__)

#ifdef P00_DOXYGEN
/**
 ** @brief construct a @c double constant in hexadecimal representation.
 **
 ** @see P99_DEC_DOUBLE for the analog with decimal representation
 **/
#define P99_HEX_DOUBLE(SIGN, HEXINT, HEXFRAC, ESIGN, BINEXP)
#else
P00_DOCUMENT_NUMBER_ARGUMENT(P99_HEX_DOUBLE, 1)
P00_DOCUMENT_NUMBER_ARGUMENT(P99_HEX_DOUBLE, 2)
P00_DOCUMENT_NUMBER_ARGUMENT(P99_HEX_DOUBLE, 4)
#define P99_HEX_DOUBLE(...)                                    \
  P99_IF_GE(P99_NARG(__VA_ARGS__), 6)                          \
  (P00_HEX_DOUBLE(__VA_ARGS__))                                \
  (P00_HEX_DOUBLE(__VA_ARGS__,,,,,))
#endif

/**
 ** @}
 */


#endif      /* !P99_DOUBLE_H_ */
