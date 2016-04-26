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
/*
** p99_str.h
**
** Made by Jens Gustedt
** Login   <gustedt@damogran.loria.fr>
**
** Started on  Thu Oct  7 14:57:47 2010 Jens Gustedt
** Last update Thu Oct  7 14:57:47 2010 Jens Gustedt
*/

#ifndef     P99_STR_H_
# define    P99_STR_H_

/**
 ** @file
 ** @brief Provide a family of functions @c str2XX that provide a
 ** safer end-check with a position in the string instead of the
 ** bogus @c char pointer.
 **/

#include "p99_classification.h"

#define P00_DEFINE_STR3(CODE)                                                                             \
p99_inline                                                                                                \
P99_BUILTIN_TYPE(CODE) P99_PASTE2(str2, CODE)(char const* p00_nptr, size_t* p00_pos, unsigned p00_base) { \
  char *p00_eptr;                                                                                         \
  P99_BUILTIN_TYPE(CODE) p00_ret = (strto ## CODE)(p00_nptr, (p00_pos ? &p00_eptr : 0), p00_base);        \
  if (p00_pos) *p00_pos = p00_eptr - p00_nptr;                                                            \
  return p00_ret;                                                                                         \
}                                                                                                         \
P99_MACRO_END(P00_DEFINE_STR3, CODE)

#define P00_STR3_0(X) P00_DEFINE_STR3(X)
#define P00_STR3_1(...) P99_SEP(P00_STR3_0, __VA_ARGS__)

#ifndef P00_DOXYGEN
P00_STR3_1(l, ll, ul, ull, uz, t, j, uj);
#endif

P00_C99_DEFARG_DOCU(str2l, long, char const *p00_nptr, size_t *p00_pos, unsigned p00_base)
/*! @param p00_nptr is required */
/*! @param p00_pos defaults to 0, meaning that the successfully parsed string is not kept track */
/*! @param p00_base is 0, numbers are hex if they start with 0x, octal if they start with 0 and decimal otherwise */
#define str2l(...) P99_CALL_DEFARG(str2l, 3, __VA_ARGS__)
#define str2l_defarg_1() 0
#define str2l_defarg_2() 0

P00_C99_DEFARG_DOCU(str2ll, long long, char const *p00_nptr, size_t *p00_pos, unsigned p00_base)
/*! @param p00_nptr is required */
/*! @param p00_pos defaults to 0, meaning that the successfully parsed string is not kept track */
/*! @param p00_base is 0, numbers are hex if they start with 0x, octal if they start with 0 and decimal otherwise */
#define str2ll(...) P99_CALL_DEFARG(str2ll, 3, __VA_ARGS__)
#define str2ll_defarg_1() 0
#define str2ll_defarg_2() 0

P00_C99_DEFARG_DOCU(str2ul, unsigned long, char const *p00_nptr, size_t *p00_pos, unsigned p00_base)
/*! @param p00_nptr is required */
/*! @param p00_pos defaults to 0, meaning that the successfully parsed string is not kept track */
/*! @param p00_base is 0, numbers are hex if they start with 0x, octal if they start with 0 and decimal otherwise */
#define str2ul(...) P99_CALL_DEFARG(str2ul, 3, __VA_ARGS__)
#define str2ul_defarg_1() 0
#define str2ul_defarg_2() 0

P00_C99_DEFARG_DOCU(str2ull, unsigned long long, char const *p00_nptr, size_t *p00_pos, unsigned p00_base)
/*! @param p00_nptr is required */
/*! @param p00_pos defaults to 0, meaning that the successfully parsed string is not kept track */
/*! @param p00_base is 0, numbers are hex if they start with 0x, octal if they start with 0 and decimal otherwise */
#define str2ull(...) P99_CALL_DEFARG(str2ull, 3, __VA_ARGS__)
#define str2ull_defarg_1() 0
#define str2ull_defarg_2() 0

P00_C99_DEFARG_DOCU(str2uz, size_t, char const *p00_nptr, size_t *p00_pos, unsigned p00_base)
/*! @param p00_nptr is required */
/*! @param p00_pos defaults to 0, meaning that the successfully parsed string is not kept track */
/*! @param p00_base is 0, numbers are hex if they start with 0x, octal if they start with 0 and decimal otherwise */
#define str2uz(...) P99_CALL_DEFARG(str2uz, 3, __VA_ARGS__)
#define str2uz_defarg_1() 0
#define str2uz_defarg_2() 0

P00_C99_DEFARG_DOCU(str2t, ptrdiff_t, char const *p00_nptr, size_t *p00_pos, unsigned p00_base)
/*! @param p00_nptr is required */
/*! @param p00_pos defaults to 0, meaning that the successfully parsed string is not kept track */
/*! @param p00_base is 0, numbers are hex if they start with 0x, octal if they start with 0 and decimal otherwise */
#define str2t(...) P99_CALL_DEFARG(str2t, 3, __VA_ARGS__)
#define str2t_defarg_1() 0
#define str2t_defarg_2() 0

P00_C99_DEFARG_DOCU(str2j, intmax_t, char const *p00_nptr, size_t *p00_pos, unsigned p00_base)
/*! @param p00_nptr is required */
/*! @param p00_pos defaults to 0, meaning that the successfully parsed string is not kept track */
/*! @param p00_base is 0, numbers are hex if they start with 0x, octal if they start with 0 and decimal otherwise */
#define str2j(...) P99_CALL_DEFARG(str2j, 3, __VA_ARGS__)
#define str2j_defarg_1() 0
#define str2j_defarg_2() 0

P00_C99_DEFARG_DOCU(str2uj, uintmax_t, char const *p00_nptr, size_t *p00_pos, unsigned p00_base)
/*! @param p00_nptr is required */
/*! @param p00_pos defaults to 0, meaning that the successfully parsed string is not kept track */
/*! @param p00_base is 0, numbers are hex if they start with 0x, octal if they start with 0 and decimal otherwise */
#define str2uj(...) P99_CALL_DEFARG(str2uj, 3, __VA_ARGS__)
#define str2uj_defarg_1() 0
#define str2uj_defarg_2() 0

#define P00_DEFINE_STR2(CODE)                                                            \
p99_inline                                                                               \
P99_BUILTIN_TYPE(CODE) P99_PASTE2(str2, CODE)(char const* p00_nptr, size_t* p00_pos) {   \
  char *p00_eptr;                                                                        \
  P99_BUILTIN_TYPE(CODE) p00_ret = (strto ## CODE)(p00_nptr, (p00_pos ? &p00_eptr : 0)); \
  if (p00_pos) *p00_pos = p00_eptr - p00_nptr;                                           \
  return p00_ret;                                                                        \
}                                                                                        \
P99_MACRO_END(P00_DEFINE_STR2, CODE)

#define P00_STR2_0(X) P00_DEFINE_STR2(X)
#define P00_STR2_1(...) P99_SEP(P00_STR2_0, __VA_ARGS__)

P00_STR2_1(f, d, ld);

P00_C99_DEFARG_DOCU(str2f, float, char const *p00_nptr, size_t *p00_pos)
/*! @param p00_nptr is required */
/*! @param p00_pos defaults to 0, meaning that the successfully parsed string is not kept track */
#define str2f(...) P99_CALL_DEFARG(str2f, 2, __VA_ARGS__)
#define str2f_defarg_1() 0

P00_C99_DEFARG_DOCU(str2d, double, char const *p00_nptr, size_t *p00_pos)
/*! @param p00_nptr is required */
/*! @param p00_pos defaults to 0, meaning that the successfully parsed string is not kept track */
#define str2d(...) P99_CALL_DEFARG(str2d, 2, __VA_ARGS__)
#define str2d_defarg_1() 0

P00_C99_DEFARG_DOCU(str2ld, long double, char const *p00_nptr, size_t *p00_pos)
/*! @param p00_nptr is required */
/*! @param p00_pos defaults to 0, meaning that the successfully parsed string is not kept track */
#define str2ld(...) P99_CALL_DEFARG(str2ld, 2, __VA_ARGS__)
#define str2ld_defarg_1() 0



#endif      /* !P99_STR_H_ */
