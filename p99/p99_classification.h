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
#ifndef     P99_CLASSIFICATION_H_
# define    P99_CLASSIFICATION_H_

#include "p99_map.h"

/**
 ** @file
 ** @brief classification of different types of token sequences
 **
 ** @warning this will not be handling imaginary types with the
 ** _Imaginary keyword since the handling of those has been revised by
 ** a <a
 ** href="http://www.open-std.org/jtc1/sc22/wg14/www/docs/dr_207.htm">defect report>/a>
 **/

/**
 ** @addtogroup classification
 ** @brief The macros in this group help to classify different token
 ** sequences, in particular type specifiers that are composed of
 ** several tokens.
 ** @{
 **/



#define P00_BUILTIN_TYPE_V  P00_BUILTIN_TYPE_v
#define P00_BUILTIN_TYPE_B  P00_BUILTIN_TYPE_b
#define P00_BUILTIN_TYPE_C  P00_BUILTIN_TYPE_c
#define P00_BUILTIN_TYPE_D  P00_BUILTIN_TYPE_d
#define P00_BUILTIN_TYPE_DC P00_BUILTIN_TYPE_dc
#define P00_BUILTIN_TYPE_DI P00_BUILTIN_TYPE_di
#define P00_BUILTIN_TYPE_Dc P00_BUILTIN_TYPE_dc
/* #define P00_BUILTIN_TYPE_Di  P00_BUILTIN_TYPE_di */
#define P00_BUILTIN_TYPE_F  P00_BUILTIN_TYPE_f
#define P00_BUILTIN_TYPE_FC P00_BUILTIN_TYPE_fc
#define P00_BUILTIN_TYPE_FI P00_BUILTIN_TYPE_fi
#define P00_BUILTIN_TYPE_Fc P00_BUILTIN_TYPE_fc
/* #define P00_BUILTIN_TYPE_Fi  P00_BUILTIN_TYPE_fi */
#define P00_BUILTIN_TYPE_H  P00_BUILTIN_TYPE_h
#define P00_BUILTIN_TYPE_HH P00_BUILTIN_TYPE_hh
#define P00_BUILTIN_TYPE_Hh P00_BUILTIN_TYPE_hh
#define P00_BUILTIN_TYPE_I  P00_BUILTIN_TYPE_i
#define P00_BUILTIN_TYPE_L  P00_BUILTIN_TYPE_l
#define P00_BUILTIN_TYPE_LD P00_BUILTIN_TYPE_ld
#define P00_BUILTIN_TYPE_LDC  P00_BUILTIN_TYPE_ldc
#define P00_BUILTIN_TYPE_LDI  P00_BUILTIN_TYPE_ldi
#define P00_BUILTIN_TYPE_LDc  P00_BUILTIN_TYPE_ldc
/* #define P00_BUILTIN_TYPE_LDi P00_BUILTIN_TYPE_ldi */
#define P00_BUILTIN_TYPE_LL P00_BUILTIN_TYPE_ll
#define P00_BUILTIN_TYPE_Ld P00_BUILTIN_TYPE_ld
#define P00_BUILTIN_TYPE_LdC  P00_BUILTIN_TYPE_ldc
/* #define P00_BUILTIN_TYPE_LdI P00_BUILTIN_TYPE_ldi */
#define P00_BUILTIN_TYPE_Ldc  P00_BUILTIN_TYPE_ldc
/* #define P00_BUILTIN_TYPE_Ldi P00_BUILTIN_TYPE_ldi */
#define P00_BUILTIN_TYPE_Ll P00_BUILTIN_TYPE_ll
#define P00_BUILTIN_TYPE_U  P00_BUILTIN_TYPE_u
#define P00_BUILTIN_TYPE_UH P00_BUILTIN_TYPE_uh
#define P00_BUILTIN_TYPE_UHH  P00_BUILTIN_TYPE_uhh
#define P00_BUILTIN_TYPE_UHh  P00_BUILTIN_TYPE_uhh
#define P00_BUILTIN_TYPE_UL P00_BUILTIN_TYPE_ul
#define P00_BUILTIN_TYPE_ULL  P00_BUILTIN_TYPE_ull
#define P00_BUILTIN_TYPE_ULl  P00_BUILTIN_TYPE_ull
#define P00_BUILTIN_TYPE_Uh P00_BUILTIN_TYPE_uh
#define P00_BUILTIN_TYPE_UhH  P00_BUILTIN_TYPE_uhh
#define P00_BUILTIN_TYPE_Uhh  P00_BUILTIN_TYPE_uhh
#define P00_BUILTIN_TYPE_Ul P00_BUILTIN_TYPE_ul
#define P00_BUILTIN_TYPE_UlL  P00_BUILTIN_TYPE_ull
#define P00_BUILTIN_TYPE_Ull  P00_BUILTIN_TYPE_ull
#define P00_BUILTIN_TYPE_dC P00_BUILTIN_TYPE_dc
/* #define P00_BUILTIN_TYPE_dI  P00_BUILTIN_TYPE_di */
#define P00_BUILTIN_TYPE_fC P00_BUILTIN_TYPE_fc
/* #define P00_BUILTIN_TYPE_fI  P00_BUILTIN_TYPE_fi */
#define P00_BUILTIN_TYPE_hH P00_BUILTIN_TYPE_hh
#define P00_BUILTIN_TYPE_lD P00_BUILTIN_TYPE_ld
#define P00_BUILTIN_TYPE_lDC  P00_BUILTIN_TYPE_ldc
/* #define P00_BUILTIN_TYPE_lDI P00_BUILTIN_TYPE_ldi */
#define P00_BUILTIN_TYPE_lDc  P00_BUILTIN_TYPE_ldc
/* #define P00_BUILTIN_TYPE_lDi P00_BUILTIN_TYPE_ldi */
#define P00_BUILTIN_TYPE_lL P00_BUILTIN_TYPE_ll
#define P00_BUILTIN_TYPE_ldC  P00_BUILTIN_TYPE_ldc
/* #define P00_BUILTIN_TYPE_ldI P00_BUILTIN_TYPE_ldi */
#define P00_BUILTIN_TYPE_uH P00_BUILTIN_TYPE_uh
#define P00_BUILTIN_TYPE_uHH  P00_BUILTIN_TYPE_uhh
#define P00_BUILTIN_TYPE_uHh  P00_BUILTIN_TYPE_uhh
#define P00_BUILTIN_TYPE_uL P00_BUILTIN_TYPE_ul
#define P00_BUILTIN_TYPE_uLL  P00_BUILTIN_TYPE_ull
#define P00_BUILTIN_TYPE_uLl  P00_BUILTIN_TYPE_ull
#define P00_BUILTIN_TYPE_uhH  P00_BUILTIN_TYPE_uhh
#define P00_BUILTIN_TYPE_ulL  P00_BUILTIN_TYPE_ull


#define P00_DETECT_PAREN(...) ,

/**
 ** @brief Detect if the argument list is surrounded by an extra pair of ().
 **/
#define P99_HAS_NO_PAREN(...)                                                         \
  /* Use of P00_NARG is important to avoid false trigger when __VA_ARGS__ is empty */ \
P99_IS_EQ(P00_NARG(__VA_ARGS__), P00_NARG(P00_DETECT_PAREN __VA_ARGS__))
#define P00_REMOVE_PAREN_(...) __VA_ARGS__

#define P00_REMOVE_PAREN(ARG) P00_REMOVE_PAREN_ ARG

/**
 ** @brief Remove an extra pair of () around the argument, if any.
 **/
#define P99_REMOVE_PAREN(...)                                                            \
  P99_IF_ELSE(P99_HAS_NO_PAREN(__VA_ARGS__))(__VA_ARGS__)(P00_REMOVE_PAREN(__VA_ARGS__))

#define P00_TYPE_NORMALIZE_(CODE, CONS, VOLA, SEQ)             \
P99_IF_EMPTY(CODE)                                             \
  (P99_IF_EMPTY(SEQ)(void)(SEQ))                               \
  (P99_BUILTIN_TYPE(CODE)                                      \
   CONS                                                        \
   VOLA                                                        \
  )

#define P00_TYPE_NORMALIZE(N, CODE, SEQ)                       \
P00_TYPE_NORMALIZE_(CODE,                                      \
                     P00_CONST_CLASSIFY_(N, SEQ),              \
                     P00_VOLATILE_CLASSIFY_(N, SEQ),           \
                     SEQ                                       \
                     )
/**
 ** @brief Normalize a @c void type expression.
 **
 ** @param SEQ is a sequence of keywords that should form a qualified
 ** void type expression
 ** @return @c void, followed by the qualifiers
 **/
#define P99_VOID_NORMALIZE(SEQ)                                           \
  P00_TYPE_NORMALIZE(P99_VOID_QUAL_LEN(SEQ), P00_VOID_CLASSIFY(SEQ), SEQ)

/**
 ** @brief Normalize a Boolean type expression.
 **
 ** @param SEQ is a sequence of keywords that should form a qualified
 ** Boolean type expression
 ** @return @c _Bool followed by the qualifiers
 **/
#define P99_BOOL_NORMALIZE(SEQ)                                           \
  P00_TYPE_NORMALIZE(P99_BOOL_QUAL_LEN(SEQ), P00_BOOL_CLASSIFY(SEQ), SEQ)

/**
 ** @brief Normalize an integer type expression.
 **
 ** @param SEQ is a sequence of keywords that should form a qualified
 ** integer type expression.
 **
 ** This normalizes the type by removing redundancy, such as @c int.
 **
 ** @return the normalized unqualified type, followed by the qualifiers
 **/
#define P99_INTEGER_NORMALIZE(SEQ)                                              \
  P00_TYPE_NORMALIZE(P99_INTEGER_QUAL_LEN(SEQ), P00_INTEGER_CLASSIFY(SEQ), SEQ)

/**
 ** @brief Normalize an floating type expression, including @c
 ** _Complex types.
 **
 ** @param SEQ is a sequence of keywords that should form a qualified
 ** floating type expression.
 **
 ** This normalizes the type by reordering the keywords.
 **
 ** @return the normalized unqualified type, followed by the qualifiers
 **/
#define P99_FLOAT_NORMALIZE(SEQ)                                            \
  P00_TYPE_NORMALIZE(P99_FLOAT_QUAL_LEN(SEQ), P00_FLOAT_CLASSIFY(SEQ), SEQ)


/**
 ** @}
 **/



#endif      /* !P99_CLASSIFICATION_H_ */
