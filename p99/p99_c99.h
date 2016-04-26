/* This may look like nonsense, but it really is -*- mode: C -*-              */
/*                                                                            */
/* Except for parts copied from previous work and as explicitly stated below, */
/* the authors and copyright holders for this work are as follows:            */
/* (C) copyright  2011 Emmanuel Jeanvoine, INRIA, France                      */
/* (C) copyright  2010-2014 Jens Gustedt, INRIA, France                       */
/*                                                                            */
/* This file is free software; it is part of the P99 project.                 */
/* You can redistribute it and/or modify it under the terms of the QPL as     */
/* given in the file LICENSE. It is distributed without any warranty;         */
/* without even the implied warranty of merchantability or fitness for a      */
/* particular purpose.                                                        */
/*                                                                            */
#ifndef     P99_C99_H_
# define    P99_C99_H_

/**
 ** @file
 ** @brief C99 specific include files that are required by the standard.
 **
 ** Using this file adds some restrictions about keywords on your
 ** code. Most prominent are probably @c bool, @c true, @c false and
 ** @c I, but there a lot more such as
 ** @c and @c and_eq @c bitand @c bitor @c compl @c not @c not_eq @c or @c or_eq @c xor @c xor_eq
 **/

#ifndef __STDC_WANT_LIB_EXT1__
# define __STDC_WANT_LIB_EXT1__ 1
#endif

#include "p99_compiler.h"

#if p99_has_feature(complex_h)
# include <complex.h>
#endif
#if p99_has_feature(ctype_h)
# include <ctype.h>
#endif
#if p99_has_feature(errno_h)
# include <errno.h>
#endif
#if p99_has_feature(fenv_h)
# include <fenv.h>
#endif
#if p99_has_feature(inttypes_h)
# include <inttypes.h>
#endif
#if p99_has_feature(locale_h)
# include <locale.h>
#endif
#if p99_has_feature(math_h)
# include <math.h>
#endif
#if p99_has_feature(setjmp_h)
# include <setjmp.h>
#endif
#if p99_has_feature(signal_h)
# include <signal.h>
#endif
#if p99_has_feature(stdio_h)
# include <stdio.h>
#endif
#if p99_has_feature(stdlib_h)
# include <stdlib.h>
#endif
#if p99_has_feature(string_h)
# include <string.h>
#endif
#if p99_has_feature(tgmath_h)
# include <tgmath.h>
#endif
#if p99_has_feature(time_h)
# include <time.h>
#endif

/* Additions by C11 */
#if p99_has_feature(stdatomic_h)
# include <stdatomic.h>
#endif
#if p99_has_feature(threads_h)
# include <threads.h>
#endif
#ifndef __STDC_NO_COMPLEX__
/* The CMPLX macros expand to an expression of the specified complex
 * type, with the real part having the (converted) value of x and the
 * imaginary part having the (converted) value of y. The resulting
 * expression shall be suitable for use as an initializer for an
 * object with static or thread storage duration, provided both
 * arguments are likewise suitable.
 */
# ifndef CMPLXF
#  define CMPLXF(A, B) ((float _Complex)((float)(A) + _Complex_I * (float)(B)))
# endif
# ifndef CMPLX
#  define CMPLX(A, B) ((double _Complex)((double)(A) + _Complex_I * (double)(B)))
# endif
# ifndef CMPLXL
#  define CMPLXL(A, B) ((long double _Complex)((long double)(A) + _Complex_I * (long double)(B)))
# endif
# if __STDC_VERSION__ > 201100L
#  define p99_creall creall
#  define p99_crealf crealf
#  define p99_creal creal
#  define p99_cimagl cimagl
#  define p99_cimagf cimagf
#  define p99_cimag cimag
# else
/* Each complex type has the same representation and alignment
 * requirements as an array type containing exactly two elements of
 * the corresponding real type; the first element is equal to the real
 * part, and the second element to the imaginary part, of the complex
 * number. */
#   define P00_COMPLEX_PARTIAL(T, A, I)                        \
  (((const union {                                             \
        T _Complex p00_c;                                      \
        T p00_r[2];                                            \
  }){ .p00_c = (A) }).p00_r[I])

P99_CONST_FUNCTION p99_inline float p99_crealf(float _Complex p00_c) { return P00_COMPLEX_PARTIAL(float, p00_c, 0); }
P99_CONST_FUNCTION p99_inline double p99_creal(double _Complex p00_c) { return P00_COMPLEX_PARTIAL(double, p00_c, 0); }
P99_CONST_FUNCTION p99_inline long double p99_creall(long double _Complex p00_c) { return P00_COMPLEX_PARTIAL(long double, p00_c, 0); }
P99_CONST_FUNCTION p99_inline float p99_cimagf(float _Complex p00_c) { return P00_COMPLEX_PARTIAL(float, p00_c, 1); }
P99_CONST_FUNCTION p99_inline double p99_cimag(double _Complex p00_c) { return P00_COMPLEX_PARTIAL(double, p00_c, 1); }
P99_CONST_FUNCTION p99_inline long double p99_cimagl(long double _Complex p00_c) { return P00_COMPLEX_PARTIAL(long double, p00_c, 1); }
#   undef P00_COMPLEX_PARTIAL
#  endif
# endif
#endif      /* !P99_C99_H_ */
