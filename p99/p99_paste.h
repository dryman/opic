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
#ifndef     P99_PASTE_H_
# define    P99_PASTE_H_

/**
 ** @file
 ** @brief macros that paste tokens in a predictable way
 ** @see P99_PASTE
 **/

#include "p99_generated.h"

/** @addtogroup preprocessor_text Preprocessor text and token manipulation
 ** @{
 **/


/* This was inspired by BOOST's PP_CAT macro. Using such a thing avoids
   to define multiple levels of expansion for each macro. */
#define P99_PASTE0()
#define P99_PASTE1(_1) _1

/**
 ** @brief Paste two token sequences at their junction.
 **
 ** This macro does the paste operation first, and then an evaluation
 ** of the result. Thus
 ** @code
 ** #define B(x) toto(x)
 ** P99_CAT2(A, B(6));
 ** @endcode
 ** will result in
 ** @code
 ** AB(6);
 ** @endcode
 ** and not in
 ** @code
 ** Atoto(6)
 ** @endcode
 **/
#define P99_CAT2(_1, _2) _1 ## _2

/**
 ** @brief Paste two token sequences at their junction.
 **
 ** This macro does the evaluation of the arguments first and then
 ** proceeds with the concatenation
 ** of the results. Thus
 ** @code
 ** #define B(x) toto(x)
 ** P99_CAT2(A, B(6));
 ** @endcode
 ** will result in
 ** @code
 ** Atoto(6)
 ** @endcode
 ** and not in
 ** @code
 ** AB(6);
 ** @endcode
 **/
#define P99_PASTE2(_1, _2) P99_CAT2(_1, _2)
#define P99_PASTE3(_1,  _2, _3)                                \
  P99_PASTE2(P99_PASTE2(_1, _2), _3)
#define P99_PASTE4(_1,  _2, _3, _4)                            \
  P99_PASTE2(P99_PASTE3(_1, _2, _3), _4)
#define P99_PASTE5(_1,  _2, _3, _4, _5)                        \
  P99_PASTE2(P99_PASTE4(_1, _2, _3, _4), _5)
#define P99_PASTE6(_1,  _2, _3, _4, _5, _6)                    \
  P99_PASTE2(P99_PASTE5(_1, _2, _3, _4, _5), _6)

#define P99_PASTID0()
#define P99_PASTID1(ID) ID
#define P00_PASTID2(ID0, ID1) ID0 ## _ ## ID1
#define P99_PASTID2(ID0, ID1) P99_IF_EMPTY(ID1)(P00_PASTID2(ID0, p007))(P00_PASTID2(ID0, ID1))

#define P99_PASTID(...) P99_PASTE2(P99_PASTID, P99_NARG(__VA_ARGS__))(__VA_ARGS__)

#ifndef P00_DOCUMENT_MULTIPLE_ARGUMENT
#define P00_DOCUMENT_TYPE_ARGUMENT(MACRO, N) /*! @remark argument N should correspond to a type that is not a VLA. */
#define P00_DOCUMENT_TYPE_IDENTIFIER_ARGUMENT(MACRO, N) /*! @remark argument N should correspond to a type name (one token) that is not a VLA. */
#define P00_DOCUMENT_MULTIPLE_ARGUMENT(MACRO, N) /*! @warning argument N may be evaluated multiple times */
#define P00_DOCUMENT_WARN_VLA_ARGUMENT(MACRO, N) /*! @warning argument N may be evaluated multiple times if it is a VLA */
#define P00_DOCUMENT_IDENTIFIER_ARGUMENT(MACRO, N) /*! @remark argument N must be an identifier */
#define P00_DOCUMENT_PERMITTED_ARGUMENT(MACRO, N) /*! @remark argument N maybe evaluated several times for its type but only once for its value */
#define P00_DOCUMENT_STATEMENT_ARGUMENT(MACRO, N)  /*! @remark argument N is a statement that will be emitted multiple times in the resulting macro expansion */
#define P00_DOCUMENT_DECLARATION_ARGUMENT(MACRO, N)
#define P00_DOCUMENT_MACRO_ARGUMENT(MACRO, N) /*! @remark argument N should correspond to a macro name */
#define P00_DOCUMENT_NUMBER_ARGUMENT(MACRO, N) /*! @remark argument N must expand to a decimal number */
#define P00_DOCUMENT_DESIGNATOR_ARGUMENT(MACRO, N) /*! @remark argument N must be a field designator */
#endif

/**
 ** @}
 **/


#endif      /* !P99_PASTE_H_ */
