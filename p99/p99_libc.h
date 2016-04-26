/* This may look like nonsense, but it really is -*- mode: C -*-              */
/*                                                                            */
/* Except for parts copied from previous work and as explicitly stated below, */
/* the authors and copyright holders for this work are as follows:            */
/* (C) copyright  2013 Bobby                                                  */
/* (C) copyright  2013-2014 Jens Gustedt, INRIA, France                       */
/*                                                                            */
/* This file is free software; it is part of the P99 project.                 */
/* You can redistribute it and/or modify it under the terms of the QPL as     */
/* given in the file LICENSE. It is distributed without any warranty;         */
/* without even the implied warranty of merchantability or fitness for a      */
/* particular purpose.                                                        */
/*                                                                            */
#ifndef P99_LIBC_H
#define P99_LIBC_H

/**
 ** @file
 ** @brief Group C library dependencies together in one file
 **
 ** The idea of this file is that different implementations of the C
 ** library may have particular features that are missing. If you have
 ** such a C library let me know and I will try to add it here.
 **
 ** Libraries that are conforming should be captured by the "#else"
 ** part, that is by the fallback. Libraries that are known to fall
 ** under this are
 **  - glibc, identifiable by __GLIBC__
 **  - musl, that doesn't set a special macro to identify itself
 **
 ** The only library that we currently know off that misses parts of
 ** the C library is avrlibc.
 **/

#if defined(__WITH_AVRLIBC__) || defined(__AVR_LIBC_VERSION__)
# ifndef __AVR_LIBC_VERSION__
#  include <avr/version.h>
# endif
/* Please drop me a line if avr libc one day supports one of the
   features.that are protected by __AVR_LIBC_VERSION__ */
# define P99_AVR_LIBC_SOMEDAY (-2U)
# define p00_has_feature_assert_h 1
# define p00_has_feature_float_h 1
# define p00_has_feature_iso646_h 1
# define p00_has_feature_limits_h 1
# define p00_has_feature_stdarg_h 1
# define p00_has_feature_stdbool_h 1
# define p00_has_feature_stddef_h 1
# define p00_has_feature_stdint_h 1
# define p00_has_feature_ctype_h 1
# define p00_has_feature_errno_h 1
# define p00_has_feature_stdio_h 1
# define p00_has_feature_stdlib_h 1
# define p00_has_feature_string_h 1
# define p00_has_feature_math_h 1
# define p00_has_feature_setjmp_h 1
# define P99_CSIN_BUG
/* tgmath.h broken in avr-gcc, tries to include unavailable complex.h. */
# if (__AVR_LIBC_VERSION__ > P99_AVR_LIBC_SOMEDAY)
#  undef p00_has_feature_tgmath_h
# endif
# if __STDC_HOSTED__
/* C99 requires this C11 has this conditionally */
#  if (__AVR_LIBC_VERSION__ > P99_AVR_LIBC_SOMEDAY)
#   ifndef __STDC_NO_COMPLEX__
#    define p00_has_feature_complex_h 1
#    undef P99_CSIN_BUG
#   endif
#  endif
#  if (__AVR_LIBC_VERSION__ > P99_AVR_LIBC_SOMEDAY)
#   define p00_has_feature_fenv_h 1
#  endif
#  define p00_has_feature_inttypes_h 1
#  if (__AVR_LIBC_VERSION__ > P99_AVR_LIBC_SOMEDAY)
#   define p00_has_feature_locale_h 1
#  endif
#  if (__AVR_LIBC_VERSION__ > P99_AVR_LIBC_SOMEDAY)
#   define p00_has_feature_signal_h 1
#  endif
/* tgmath.h should be given on the compiler level */
#  if (__AVR_LIBC_VERSION__ > P99_AVR_LIBC_SOMEDAY)
#   define p00_has_feature_time_h 1
#  endif
#  if (__AVR_LIBC_VERSION__ > P99_AVR_LIBC_SOMEDAY)
#   define p00_has_feature_wchar_h 1
#  endif
#  if (__AVR_LIBC_VERSION__ > P99_AVR_LIBC_SOMEDAY)
#   define p00_has_feature_wctype_h 1
#  endif
# endif

#else
/* This is what a standard conforming C library must provide. */
# define p00_has_feature_float_h 1
# define p00_has_feature_iso646_h 1
# define p00_has_feature_limits_h 1
# define p00_has_feature_stdarg_h 1
# define p00_has_feature_stdbool_h 1
# define p00_has_feature_stddef_h 1
# define p00_has_feature_stdint_h 1
# if __STDC_HOSTED__
#  define p00_has_feature_assert_h 1
/* C99 requires this C11 has this conditionally */
#  ifndef __STDC_NO_COMPLEX__
#   define p00_has_feature_complex_h 1
#  endif
#  define p00_has_feature_ctype_h 1
#  define p00_has_feature_errno_h 1
#  define p00_has_feature_fenv_h 1
#  define p00_has_feature_inttypes_h 1
#  define p00_has_feature_locale_h 1
#  define p00_has_feature_math_h 1
#  define p00_has_feature_setjmp_h 1
#  define p00_has_feature_signal_h 1
#  define p00_has_feature_stdio_h 1
#  define p00_has_feature_stdlib_h 1
#  define p00_has_feature_string_h 1
/* tgmath.h should be given on the compiler level */
#  define p00_has_feature_time_h 1
#  define p00_has_feature_wchar_h 1
#  define p00_has_feature_wctype_h 1
# endif
#endif


#if p99_has_feature(float_h)
# include <float.h>
#endif
/* For a conforming compiler, this should now have been defined. Set
   it to "indeterminable" otherwise. */
#ifndef FLT_EVAL_METHOD
# define FLT_EVAL_METHOD (-1)
#endif
#if p99_has_feature(iso646_h)
# include <iso646.h>
#endif
#if p99_has_feature(limits_h)
# include <limits.h>
#endif
#if p99_has_feature(stdarg_h)
# include <stdarg.h>
#endif
#if p99_has_feature(stdbool_h)
# include <stdbool.h>
#endif
#if p99_has_feature(stddef_h)
# include <stddef.h>
#endif
#if p99_has_feature(stdint_h)
# include <stdint.h>
#endif

/* This is defined in some header file since C11. Since C11 allows to
   repeat typedefs as long as they resolve to the same type, this can
   be done at any place. */
typedef size_t rsize_t;

#ifndef RSIZE_MAX
/* This is the recommended practice if there is no other value
   available. */
# define RSIZE_MAX (SIZE_MAX >> 1)
#endif

#if p99_has_feature(assert_h)
# include <assert.h>
#endif
#if p99_has_feature(wchar_h)
# include <wchar.h>
#endif
#if p99_has_feature(wctype_h)
# include <wctype.h>
#endif

/* Look for C11 features that are typically provided by a C library
   and not by the compiler itself */
#ifdef __GLIBC__
# if __GLIBC_PREREQ(2, 19)
#  define p00_has_feature_aligned_alloc 1
#  define p00_has_extension_aligned_alloc 1
#  define p00_has_feature_uchar_h 1
# else
#  define p00_has_feature_uchar_h 0
#  define __STDC_NO_THREADS__ 1
# endif
#endif

#if __STDC_VERSION__ > 201100L
# define p00_has_feature_stdalign_h 1
# define p00_has_feature_stdnoreturn_h 1
# ifndef  __STDC_NO_ATOMICS__
#  define p00_has_feature_stdatomic_h 1
# endif
/*
# ifndef __STDC_NO_THREADS__
#  define p00_has_feature_threads_h 1
# endif
*/
#endif


/* implement emulation of some C11 features */
#if p99_has_feature(stdalign_h)
# include <stdalign.h>
#endif
#if p99_has_feature(stdnoreturn_h)
# include <stdnoreturn.h>
#endif
/* end C11 emulation support */

#if p99_has_feature(uchar_h)
# include <uchar.h>
#else
/* Define the unicode character types directly. */
typedef uint_least16_t char16_t;
typedef uint_least32_t char32_t;
#endif /* uchar */


#endif
