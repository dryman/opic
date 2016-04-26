/* This may look like nonsense, but it really is -*- mode: C -*-              */
/*                                                                            */
/* Except for parts copied from previous work and as explicitly stated below, */
/* the authors and copyright holders for this work are as follows:            */
/* (C) copyright  2010-2013 Jens Gustedt, INRIA, France                       */
/* (C) copyright  2012 William Morris                                         */
/*                                                                            */
/* This file is free software; it is part of the P99 project.                 */
/* You can redistribute it and/or modify it under the terms of the QPL as     */
/* given in the file LICENSE. It is distributed without any warranty;         */
/* without even the implied warranty of merchantability or fitness for a      */
/* particular purpose.                                                        */
/*                                                                            */
#ifndef     P99_ID_H_
# define    P99_ID_H_

#include "p99_if.h"

/**
 ** @file
 **
 ** @brief Implement a simple FILEID that changes each time this file
 ** is included somewhere
 **
 ** The FILEID here is a hexadecimal number with 4 digits. 34320
 ** different such numbers are produced by the algorithm until it
 ** wraps around.
 **/

#define P00_DOCUMENT_ID(X) /*! @brief counting the number of inclusions of "p99_id.h" mod X */

P00_DOCUMENT_ID(11)
#define P99_ID_11 0

P00_DOCUMENT_ID(13)
#define P99_ID_13 0

P00_DOCUMENT_ID(15)
#define P99_ID_15 0

P00_DOCUMENT_ID(16)
#define P99_ID_16 0

#define P00_ALPH_0 0
#define P00_ALPH_1 1
#define P00_ALPH_2 2
#define P00_ALPH_3 3
#define P00_ALPH_4 4
#define P00_ALPH_5 5
#define P00_ALPH_6 6
#define P00_ALPH_7 7
#define P00_ALPH_8 8
#define P00_ALPH_9 9
#define P00_ALPH_10 A
#define P00_ALPH_11 B
#define P00_ALPH_12 C
#define P00_ALPH_13 D
#define P00_ALPH_14 E
#define P00_ALPH_15 F
#define P00_ALPH_16 G
#define P00_ALPH_17 H
#define P00_ALPH_18 I
#define P00_ALPH_19 J
#define P00_ALPH_20 K
#define P00_ALPH_21 L
#define P00_ALPH_22 M
#define P00_ALPH_23 N
#define P00_ALPH_24 O
#define P00_ALPH_25 P
#define P00_ALPH_26 Q
#define P00_ALPH_27 R
#define P00_ALPH_28 S
#define P00_ALPH_29 T
#define P00_ALPH_30 U
#define P00_ALPH_31 V
#define P00_ALPH_32 W
#define P00_ALPH_33 X
#define P00_ALPH_34 Y
#define P00_ALPH_35 Z



#define P00_ALPH_(A, X) P99_PASTE2(A, X)
#define P00_ALPH(X) P00_ALPH_(P00_ALPH_, X)

#define P99_ID_11_ P00_ALPH(P99_ID_11)
#define P99_ID_13_ P00_ALPH(P99_ID_13)
#define P99_ID_15_ P00_ALPH(P99_ID_15)
#define P99_ID_16_ P00_ALPH(P99_ID_16)

#define P99_ID() P99_PASTE4(P99_ID_11_, P99_ID_13_, P99_ID_15_, P99_ID_16_)

/**
 ** @brief A number that identifies different times of inclusion of
 ** the file "p99_id.h"
 **
 ** This is an unsigned hexadecimal constant of at most 4 significant digits.
 **/
#define P99_FILENO() P99_PASTE2(0x, P99_ID(), U)

/**
 ** @brief An identifier token that identifies different times of
 ** inclusion of the file "p99_id.h"
 **
 ** The argument may contain a list of partial identifier tokens that
 ** are appended to the id.
 **/
#define P99_FILEID(...) P99_PASTID(p00_fileid, P99_ID(), __VA_ARGS__)

/**
 ** @brief A number that identifies different lines in an include
 ** hierarchy.
 **
 ** This is a hexadecimal constant of type @c unsigned long long.
 ** @see P99_LINEID
 **/
#define P99_LINENO() P99_PASTE4(0x, __LINE__, P99_ID(), ULL)
/**
 ** @brief An identifier token that identifies different lines in an include
 ** hierarchy.
 **
 ** The argument may contain a token that is appended to the id.
 **
 ** If during an individual compilation there is a conflict because
 ** this macro is used in lines with exactly the same __LINE__ number,
 ** you'd have to include the file "p99_id.h" once more in one of the
 ** corresponding header files.
 **
 ** If such a conflict only occurs when linking different object files
 ** to your executable you should reconsider the offending lines that
 ** use this macro more thoroughly.
 **/
#define P99_LINEID(...) P99_PASTID(p00_lineid, __LINE__, P99_ID(), __VA_ARGS__)

#ifndef P00_UNIQ
# if __COUNTER__ || __COUNTER__
#  define P00_UNIQ __COUNTER__
# else
#  define P00_UNIQ p00_no_counter_feature
# endif
#endif

/**
 ** @brief An identifier token that is intended to be unique in this
 ** compilation unit
 **
 ** This uses different line numbers in an include hierarchy to
 ** disambiguate, and, if available, the non-standard macro
 ** <code>__COUNTER__</code>.
 **
 ** The argument may contain a token that is appended to the id.
 **
 ** If during an individual compilation there is a conflict because
 ** this macro is used in lines with exactly the same __LINE__ number,
 ** and <code>__COUNTER__</code> is not available you'd have to
 ** include the file "p99_id.h" once more in one of the corresponding
 ** header files.
 **
 ** If you need the same unique identifier at several places in the
 ** same macro you'd have to cascade as in the following example:
 **
 ** @code
 ** #define MY_DO(ID, START, STOP, INC) MY_DO_(ID, P99_UNIQ(n), P99_UNIQ(p), (START), (STOP), (INC))
 ** #define MY_DO_(ID, NU, PU, START, STOP, INC) for (unsigned ID = START, NU = STOP, PU = INC; ID < NU; ID += PU)
 **
 ** MY_DO(i, 0, strlen(filename), 1)
 **   printf("%c-", filename[i]);
 ** @endcode
 **
 ** This would expand to
 **
 ** @code
 ** for (unsigned ID = 0, crude_n = strlen(filename), crude_p = 1; i < crude_n; i += crude_p)
 **    printf("%c-", filename[i]);
 ** @endcode
 **
 ** Here, in the top most expansion of <code>MY_DO</code> two
 ** identifiers are generated and passed along as arguments of
 ** <code>MY_DO_</code>. (The "names" @c crude_n or @c crude_p only
 ** stand for some crude unique identifier you don't really want to
 ** know.)
 **
 ** The effect here is that the generated <code>for</code> loop has
 ** three local variables, that are initialized to the three arguments
 ** of <code>MY_DO</code>. By this, this macro can guarantee that the
 ** loop bounds are only evaluated once and that the number of
 ** iterations that is performed is known on entry to the loop.
 **/
#define P99_UNIQ(...)  P99_IF_EMPTY(__VA_ARGS__)(P99_LINEID(P00_UNIQ, uniq))(P99_LINEID(P00_UNIQ, uniq, __VA_ARGS__))

#ifdef P00_DOXYGEN
/**
 ** @brief Advance the unique ID generated by P99
 **
 ** Use this as
 ** @code
 ** #include P99_ADVANCE_ID
 ** @endcode
 **/
# define P99_ADVANCE_ID P99_ADVANCE_ID
#else
# define P99_ADVANCE_ID "p99_id.h"
#endif

#endif


#if P99_ID_11 >= 10
# undef P99_ID_11
# define P99_ID_11 0
#elif P99_ID_11 == 0
# undef P99_ID_11
# define P99_ID_11 1
#elif P99_ID_11 == 1
# undef P99_ID_11
# define P99_ID_11 2
#elif P99_ID_11 == 2
# undef P99_ID_11
# define P99_ID_11 3
#elif P99_ID_11 == 3
# undef P99_ID_11
# define P99_ID_11 4
#elif P99_ID_11 == 4
# undef P99_ID_11
# define P99_ID_11 5
#elif P99_ID_11 == 5
# undef P99_ID_11
# define P99_ID_11 6
#elif P99_ID_11 == 6
# undef P99_ID_11
# define P99_ID_11 7
#elif P99_ID_11 == 7
# undef P99_ID_11
# define P99_ID_11 8
#elif P99_ID_11 == 8
# undef P99_ID_11
# define P99_ID_11 9
#elif P99_ID_11 == 9
# undef P99_ID_11
# define P99_ID_11 10
#elif P99_ID_11 == 10
# undef P99_ID_11
# define P99_ID_11 11
#elif P99_ID_11 == 11
# undef P99_ID_11
# define P99_ID_11 12
#elif P99_ID_11 == 12
# undef P99_ID_11
# define P99_ID_11 13
#elif P99_ID_11 == 13
# undef P99_ID_11
# define P99_ID_11 14
#elif P99_ID_11 == 14
# undef P99_ID_11
# define P99_ID_11 15
#elif P99_ID_11 == 15
# undef P99_ID_11
# define P99_ID_11 16
#elif P99_ID_11 == 16
# undef P99_ID_11
# define P99_ID_11 17
#elif P99_ID_11 == 17
# undef P99_ID_11
# define P99_ID_11 18
#elif P99_ID_11 == 18
# undef P99_ID_11
# define P99_ID_11 19
#elif P99_ID_11 == 19
# undef P99_ID_11
# define P99_ID_11 20
#endif

#if P99_ID_13 >= 12
# undef P99_ID_13
# define P99_ID_13 0
#elif P99_ID_13 == 0
# undef P99_ID_13
# define P99_ID_13 1
#elif P99_ID_13 == 1
# undef P99_ID_13
# define P99_ID_13 2
#elif P99_ID_13 == 2
# undef P99_ID_13
# define P99_ID_13 3
#elif P99_ID_13 == 3
# undef P99_ID_13
# define P99_ID_13 4
#elif P99_ID_13 == 4
# undef P99_ID_13
# define P99_ID_13 5
#elif P99_ID_13 == 5
# undef P99_ID_13
# define P99_ID_13 6
#elif P99_ID_13 == 6
# undef P99_ID_13
# define P99_ID_13 7
#elif P99_ID_13 == 7
# undef P99_ID_13
# define P99_ID_13 8
#elif P99_ID_13 == 8
# undef P99_ID_13
# define P99_ID_13 9
#elif P99_ID_13 == 9
# undef P99_ID_13
# define P99_ID_13 10
#elif P99_ID_13 == 10
# undef P99_ID_13
# define P99_ID_13 11
#elif P99_ID_13 == 11
# undef P99_ID_13
# define P99_ID_13 12
#elif P99_ID_13 == 12
# undef P99_ID_13
# define P99_ID_13 13
#elif P99_ID_13 == 13
# undef P99_ID_13
# define P99_ID_13 14
#elif P99_ID_13 == 14
# undef P99_ID_13
# define P99_ID_13 15
#elif P99_ID_13 == 15
# undef P99_ID_13
# define P99_ID_13 16
#elif P99_ID_13 == 16
# undef P99_ID_13
# define P99_ID_13 17
#elif P99_ID_13 == 17
# undef P99_ID_13
# define P99_ID_13 18
#elif P99_ID_13 == 18
# undef P99_ID_13
# define P99_ID_13 19
#elif P99_ID_13 == 19
# undef P99_ID_13
# define P99_ID_13 20
#endif

#if P99_ID_15 >= 14
# undef P99_ID_15
# define P99_ID_15 0
#elif P99_ID_15 == 0
# undef P99_ID_15
# define P99_ID_15 1
#elif P99_ID_15 == 1
# undef P99_ID_15
# define P99_ID_15 2
#elif P99_ID_15 == 2
# undef P99_ID_15
# define P99_ID_15 3
#elif P99_ID_15 == 3
# undef P99_ID_15
# define P99_ID_15 4
#elif P99_ID_15 == 4
# undef P99_ID_15
# define P99_ID_15 5
#elif P99_ID_15 == 5
# undef P99_ID_15
# define P99_ID_15 6
#elif P99_ID_15 == 6
# undef P99_ID_15
# define P99_ID_15 7
#elif P99_ID_15 == 7
# undef P99_ID_15
# define P99_ID_15 8
#elif P99_ID_15 == 8
# undef P99_ID_15
# define P99_ID_15 9
#elif P99_ID_15 == 9
# undef P99_ID_15
# define P99_ID_15 10
#elif P99_ID_15 == 10
# undef P99_ID_15
# define P99_ID_15 11
#elif P99_ID_15 == 11
# undef P99_ID_15
# define P99_ID_15 12
#elif P99_ID_15 == 12
# undef P99_ID_15
# define P99_ID_15 13
#elif P99_ID_15 == 13
# undef P99_ID_15
# define P99_ID_15 14
#elif P99_ID_15 == 14
# undef P99_ID_15
# define P99_ID_15 15
#elif P99_ID_15 == 15
# undef P99_ID_15
# define P99_ID_15 16
#elif P99_ID_15 == 16
# undef P99_ID_15
# define P99_ID_15 17
#elif P99_ID_15 == 17
# undef P99_ID_15
# define P99_ID_15 18
#elif P99_ID_15 == 18
# undef P99_ID_15
# define P99_ID_15 19
#elif P99_ID_15 == 19
# undef P99_ID_15
# define P99_ID_15 20
#endif

#if P99_ID_16 >= 15
# undef P99_ID_16
# define P99_ID_16 0
#elif P99_ID_16 == 0
# undef P99_ID_16
# define P99_ID_16 1
#elif P99_ID_16 == 1
# undef P99_ID_16
# define P99_ID_16 2
#elif P99_ID_16 == 2
# undef P99_ID_16
# define P99_ID_16 3
#elif P99_ID_16 == 3
# undef P99_ID_16
# define P99_ID_16 4
#elif P99_ID_16 == 4
# undef P99_ID_16
# define P99_ID_16 5
#elif P99_ID_16 == 5
# undef P99_ID_16
# define P99_ID_16 6
#elif P99_ID_16 == 6
# undef P99_ID_16
# define P99_ID_16 7
#elif P99_ID_16 == 7
# undef P99_ID_16
# define P99_ID_16 8
#elif P99_ID_16 == 8
# undef P99_ID_16
# define P99_ID_16 9
#elif P99_ID_16 == 9
# undef P99_ID_16
# define P99_ID_16 10
#elif P99_ID_16 == 10
# undef P99_ID_16
# define P99_ID_16 11
#elif P99_ID_16 == 11
# undef P99_ID_16
# define P99_ID_16 12
#elif P99_ID_16 == 12
# undef P99_ID_16
# define P99_ID_16 13
#elif P99_ID_16 == 13
# undef P99_ID_16
# define P99_ID_16 14
#elif P99_ID_16 == 14
# undef P99_ID_16
# define P99_ID_16 15
#elif P99_ID_16 == 15
# undef P99_ID_16
# define P99_ID_16 16
#elif P99_ID_16 == 16
# undef P99_ID_16
# define P99_ID_16 17
#elif P99_ID_16 == 17
# undef P99_ID_16
# define P99_ID_16 18
#elif P99_ID_16 == 18
# undef P99_ID_16
# define P99_ID_16 19
#elif P99_ID_16 == 19
# undef P99_ID_16
# define P99_ID_16 20
#endif
