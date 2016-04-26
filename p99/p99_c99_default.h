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
#ifndef     P99_C99_DEFAULT_H_
# define    P99_C99_DEFAULT_H_

#include "p99_defarg.h"

#define P00_C99_DEFARG_DOCU(NAME, RET, ...)                               \
/*! @brief Default arguments for C99 function NAME */                     \
/*! This macro hides the function @code RET NAME(__VA_ARGS__) @endcode */ \
/*! @see P99_CALL_DEFARG */
P99_MACRO_END(C99_DEFARG_DOCU);

P00_C99_DEFARG_DOCU(strerror, char*, int errnum)
/*! @param errnum defaults to errno */
#define strerror(...) P99_CALL_DEFARG(strerror, 1, __VA_ARGS__)
#define strerror_defarg_0() 0

P00_C99_DEFARG_DOCU(calloc, void*, size_t rec_num, size_t rec_size)
/** @param rec_num is required
 ** @param rec_size defaults to 1, thus @c calloc(rec_num) is
 ** equivalent to @c malloc(rec_num) only that it also initializes the
 ** allocated space to all zeros
 **/
#define calloc(...) P99_CALL_DEFARG(calloc, 2, __VA_ARGS__)
#define calloc_defarg_1() 1u

P00_C99_DEFARG_DOCU(longjmp, void, jmp_buf env, int val)
/** @param jmp_buf is required
 ** @param val defaults to 1
 **/
#ifdef longjmp
# pragma message "warning longjmp defined as a macro, overwriting"
# undef longjmp
#endif
# define longjmp(...) P99_CALL_DEFARG(longjmp, 2, __VA_ARGS__)
# define longjmp_defarg_1() 1


/**
 ** @addtogroup stringconversion Conversion of strings to integer types
 ** @brief Extensions of the @c strto and @c wcsto families of functions
 **
 ** This generally adds default behavior and type safety to these
 ** standard C99 functions. The standard defines them only for the
 ** types @c long (::strtol), @c long @c long (::strtoll), @c
 ** intmax_t (::strtoimax) and their unsigned
 ** variants. This here adds support for the other standard integer
 ** types and @c typedef. This provides
 **  - precise overflow and underflow handling according to the type
 **  - flexible base, namely octal, decimal or hexadecimal conversion
 **
 ** In addition, to provide default arguments for the standard
 ** functions, these have names starting with @c p99_str... and macros that
 ** expand to these starting with @c str..., instead. The later might
 ** be reserved or provided in later version of the C standard. If we
 ** receive knowledge of such new interfaces we will bracket the
 ** definitions given here with appropriate defines.
 **
 ** We provide interfaces for the standard types @c char (strtoc), @c
 ** signed (strtohh) and @c unsigned @c char (strtouhh), @c signed
 ** (strtoh) and @c unsigned @c short (strtouh), and @c signed (strto)
 ** and @c unsigned @c int (strtou).  For the standard typedefs we
 ** provide strtouz for @c size_t and strtot for @c ptrdiff_t. Here
 ** the endings of the names are taken in analogy from the @c printf
 ** formats.
 **
 ** The type specific upper an lower bounds for all these are the @c
 ** MIN and @c MAX values of the corresponding types.
 **
 ** For the types @c {u}int_least[N]_t with N = 8, 16, 32 or 64 we
 ** provide functions and macros strto{u|i}[N] that have the bounds
 ** INT[N]_MIN, INT[N]_MAX and UINT[N]_MAX, respectively. So e.g for
 ** strtou16 the bound is not the bound of the type @c uint_least16_t
 ** (which might be much wider than 16 bit) but the value @c
 ** UINT16_MAX, i.e 2<sup>16</sup>-1.
 **
 **
 ** @{
 **/

P00_C99_DEFARG_DOCU(wcstol, long, wchar_t const *p00_nptr, wchar_t **p00_eptr, int p00_base)
/*! @param p00_nptr is required */
/*! @param p00_eptr defaults to 0, meaning that the successfully parsed string is not kept track */
/*! @param p00_base is 0, numbers are hex if they start with 0x, octal if they start with 0 and decimal otherwise */
#define wcstol(...) P99_CALL_DEFARG(wcstol, 3, __VA_ARGS__)
#define wcstol_defarg_1() 0
#define wcstol_defarg_2() 0

P00_C99_DEFARG_DOCU(wcstoll, long long, wchar_t const *p00_nptr, wchar_t **p00_eptr, int p00_base)

/*! @param p00_nptr is required */
/*! @param p00_eptr defaults to 0, meaning that the successfully parsed string is not kept track */
/*! @param p00_base is 0, numbers are hex if they start with 0x, octal if they start with 0 and decimal otherwise */
#define wcstoll(...) P99_CALL_DEFARG(wcstoll, 3, __VA_ARGS__)
#define wcstoll_defarg_1() 0
#define wcstoll_defarg_2() 0

P00_C99_DEFARG_DOCU(wcstoimax, intmax_t, wchar_t const *p00_nptr, wchar_t **p00_eptr, int p00_base)
/*! @param p00_nptr is required */
/*! @param p00_eptr defaults to 0, meaning that the successfully parsed string is not kept track */
/*! @param p00_base is 0, numbers are hex if they start with 0x, octal if they start with 0 and decimal otherwise */
#define wcstoimax(...) P99_CALL_DEFARG(wcstoimax, 3, __VA_ARGS__)
#define wcstoimax_defarg_1() 0
#define wcstoimax_defarg_2() 0

P00_C99_DEFARG_DOCU(wcstoul, unsigned long, wchar_t const *p00_nptr, wchar_t **p00_eptr, int p00_base)
/*! @param p00_nptr is required */
/*! @param p00_eptr defaults to 0, meaning that the successfully parsed string is not kept track */
/*! @param p00_base is 0, numbers are hex if they start with 0x, octal if they start with 0 and decimal otherwise */
#define wcstoul(...) P99_CALL_DEFARG(wcstoul, 3, __VA_ARGS__)
#define wcstoul_defarg_1() 0
#define wcstoul_defarg_2() 0

P00_C99_DEFARG_DOCU(wcstoull, unsigned long long, wchar_t const *p00_nptr, wchar_t **p00_eptr, int p00_base)
/*! @param p00_nptr is required */
/*! @param p00_eptr defaults to 0, meaning that the successfully parsed string is not kept track */
/*! @param p00_base is 0, numbers are hex if they start with 0x, octal if they start with 0 and decimal otherwise */
#define wcstoull(...) P99_CALL_DEFARG(wcstoull, 3, __VA_ARGS__)
#define wcstoull_defarg_1() 0
#define wcstoull_defarg_2() 0

P00_C99_DEFARG_DOCU(wcstoumax, uintmax_t, wchar_t const *p00_nptr, wchar_t **p00_eptr, int p00_base)
/*! @param p00_nptr is required */
/*! @param p00_eptr defaults to 0, meaning that the successfully parsed string is not kept track */
/*! @param p00_base is 0, numbers are hex if they start with 0x, octal if they start with 0 and decimal otherwise */
#define wcstoumax(...) P99_CALL_DEFARG(wcstoumax, 3, __VA_ARGS__)
#define wcstoumax_defarg_1() 0
#define wcstoumax_defarg_2() 0

P00_C99_DEFARG_DOCU(wcstof, float, wchar_t const *p00_nptr, wchar_t **p00_eptr)
/*! @param p00_nptr is required */
/*! @param p00_eptr defaults to 0, meaning that the successfully parsed string is not kept track */
#define wcstof(...) P99_CALL_DEFARG(wcstof, 2, __VA_ARGS__)
#define wcstof_defarg_1() 0

P00_C99_DEFARG_DOCU(wcstod, double, wchar_t const *p00_nptr, wchar_t **p00_eptr)
/*! @param p00_nptr is required */
/*! @param p00_eptr defaults to 0, meaning that the successfully parsed string is not kept track */
#define wcstod(...) P99_CALL_DEFARG(wcstod, 2, __VA_ARGS__)
#define wcstod_defarg_1() 0

P00_C99_DEFARG_DOCU(wcstold, long double, wchar_t const *p00_nptr, wchar_t **p00_eptr)
/*! @param p00_nptr is required */
/*! @param p00_eptr defaults to 0, meaning that the successfully parsed string is not kept track */
#define wcstold(...) P99_CALL_DEFARG(wcstold, 2, __VA_ARGS__)
#define wcstold_defarg_1() 0

P00_C99_DEFARG_DOCU(strtol, long, char const *p00_nptr, char **p00_eptr, int p00_base)
/** This macro is preferable to the @c atol function. The default
 ** arguments make it functionally equivalent but add two features:
 **  - overflow and underflow handling
 **  - flexible p00_base, namely octal, decimal or hexadecimal conversion
 **/
/*! @param p00_nptr is required */
/*! @param p00_eptr defaults to 0, meaning that the successfully parsed string is not kept track */
/*! @param p00_base is 0, numbers are hex if they start with 0x, octal if they start with 0 and decimal otherwise */
#define strtol(...) P99_CALL_DEFARG(strtol, 3, __VA_ARGS__)
#define strtol_defarg_1() 0
#define strtol_defarg_2() 0

P00_C99_DEFARG_DOCU(strtoll, long long, char const *p00_nptr, char **p00_eptr, int p00_base)
/** This macro is preferable to the @c atoll function. The default
 ** arguments make it functionally equivalent but add two features:
 **  - overflow and underflow handling
 **  - flexible p00_base, namely octal, decimal or hexadecimal conversion
 **/
/*! @param p00_nptr is required */
/*! @param p00_eptr defaults to 0, meaning that the successfully parsed string is not kept track */
/*! @param p00_base is 0, numbers are hex if they start with 0x, octal if they start with 0 and decimal otherwise */
#define strtoll(...) P99_CALL_DEFARG(strtoll, 3, __VA_ARGS__)
#define strtoll_defarg_1() 0
#define strtoll_defarg_2() 0

P00_C99_DEFARG_DOCU(strtoimax, intmax_t, char const *p00_nptr, char **p00_eptr, int p00_base)
/*! @param p00_nptr is required */
/*! @param p00_eptr defaults to 0, meaning that the successfully parsed string is not kept track */
/*! @param p00_base is 0, numbers are hex if they start with 0x, octal if they start with 0 and decimal otherwise */
#define strtoimax(...) P99_CALL_DEFARG(strtoimax, 3, __VA_ARGS__)
#define strtoimax_defarg_1() 0
#define strtoimax_defarg_2() 0

P00_C99_DEFARG_DOCU(strtoul, unsigned long, char const *p00_nptr, char **p00_eptr, int p00_base)
/*! @param p00_nptr is required */
/*! @param p00_eptr defaults to 0, meaning that the successfully parsed string is not kept track */
/*! @param p00_base is 0, numbers are hex if they start with 0x, octal if they start with 0 and decimal otherwise */
#define strtoul(...) P99_CALL_DEFARG(strtoul, 3, __VA_ARGS__)
#define strtoul_defarg_1() 0
#define strtoul_defarg_2() 0

P00_C99_DEFARG_DOCU(strtoull, unsigned long long, char const *p00_nptr, char **p00_eptr, int p00_base)
/*! @param p00_nptr is required */
/*! @param p00_eptr defaults to 0, meaning that the successfully parsed string is not kept track */
/*! @param p00_base is 0, numbers are hex if they start with 0x, octal if they start with 0 and decimal otherwise */
#define strtoull(...) P99_CALL_DEFARG(strtoull, 3, __VA_ARGS__)
#define strtoull_defarg_1() 0
#define strtoull_defarg_2() 0

P00_C99_DEFARG_DOCU(strtoumax, uintmax_t, char const *p00_nptr, char **p00_eptr, int p00_base)
/*! @param p00_nptr is required */
/*! @param p00_eptr defaults to 0, meaning that the successfully parsed string is not kept track */
/*! @param p00_base is 0, numbers are hex if they start with 0x, octal if they start with 0 and decimal otherwise */
#define strtoumax(...) P99_CALL_DEFARG(strtoumax, 3, __VA_ARGS__)
#define strtoumax_defarg_1() 0
#define strtoumax_defarg_2() 0

P00_C99_DEFARG_DOCU(strtof, float, char const *p00_nptr, char **p00_eptr)
/*! @param p00_nptr is required */
/*! @param p00_eptr defaults to 0, meaning that the successfully parsed string is not kept track */
#define strtof(...) P99_CALL_DEFARG(strtof, 2, __VA_ARGS__)
#define strtof_defarg_1() 0

P00_C99_DEFARG_DOCU(strtod, double, char const *p00_nptr, char **p00_eptr)
/*! @param p00_nptr is required */
/*! @param p00_eptr defaults to 0, meaning that the successfully parsed string is not kept track */
#define strtod(...) P99_CALL_DEFARG(strtod, 2, __VA_ARGS__)
#define strtod_defarg_1() 0

P00_C99_DEFARG_DOCU(strtold, long double, char const *p00_nptr, char **p00_eptr)
/*! @param p00_nptr is required */
/*! @param p00_eptr defaults to 0, meaning that the successfully parsed string is not kept track */
#define strtold(...) P99_CALL_DEFARG(strtold, 2, __VA_ARGS__)
#define strtold_defarg_1() 0

#define P00_DECLARE_STRTO(SUFF)                                                    \
/*! @brief A type safe wrapper for string to RET conversion */                     \
/*! @see stringconversion */                                                       \
p99_inline                                                                         \
P99_BUILTIN_TYPE(SUFF)                                                             \
P99_PASTE2(p99_strto, SUFF)(char const *p00_nptr, char **p00_eptr, int p00_base) { \
  long long p00_ret = (strtoll)(p00_nptr, p00_eptr, p00_base);                     \
  if ((p00_ret > P99_BUILTIN_MAX(SUFF) || p00_ret < P99_BUILTIN_MIN(SUFF))         \
      && (!errno)) errno = ERANGE;                                                 \
  if (p00_ret > P99_BUILTIN_MAX(SUFF)) p00_ret = P99_BUILTIN_MAX(SUFF);            \
  if (p00_ret < P99_BUILTIN_MIN(SUFF)) p00_ret = P99_BUILTIN_MIN(SUFF);            \
  return p00_ret;                                                                  \
}                                                                                  \
P99_MACRO_END(p99_strto, SUFF)


#define P00_DECLARE_STRTOU(SUFF)                                                   \
/*! @brief A type safe wrapper for string to RET conversion */                     \
/*! @see stringconversion */                                                       \
p99_inline                                                                         \
P99_BUILTIN_TYPE(SUFF)                                                             \
P99_PASTE2(p99_strto, SUFF)(char const *p00_nptr, char **p00_eptr, int p00_base) { \
  unsigned long long p00_ret = (strtoull)(p00_nptr, p00_eptr, p00_base);           \
  if (p00_ret > P99_BUILTIN_MAX(SUFF)) {                                           \
    if (!errno) errno = ERANGE;                                                    \
    p00_ret = P99_BUILTIN_MAX(SUFF);                                               \
  }                                                                                \
  return p00_ret;                                                                  \
}                                                                                  \
P99_MACRO_END(p99_strto, SUFF)

#define P00_I_LIST c, hh, , h, t, j, i8, i16, i32, i64

P99_SEP(P00_DECLARE_STRTO, P00_I_LIST);

#define P00_U_LIST uhh, u, uh, uz, uj, u8, u16, u32, u64
P99_SEP(P00_DECLARE_STRTOU, P00_U_LIST);

/** This macro is preferable to the @c atoi function. The default
 ** arguments make it functionally equivalent but add two features:
 **  - overflow and underflow handling
 **  - flexible p00_base, namely octal, decimal or hexadecimal conversion
 **/
P00_C99_DEFARG_DOCU(p99_strto, signed, char const *p00_nptr, char **p00_eptr, int p00_base)
/*! @param p00_nptr is required */
/*! @param p00_eptr defaults to 0, meaning that the successfully parsed string is not kept track */
/*! @param p00_base is 0, numbers are hex if they start with 0x, octal if they start with 0 and decimal otherwise */
#define p99_strto(...) P99_CALL_DEFARG(p99_strto, 3, __VA_ARGS__)
#define p99_strto_defarg_1() 0
#define p99_strto_defarg_2() 0


P00_C99_DEFARG_DOCU(p99_strtoc, char, char const *p00_nptr, char **p00_eptr, int p00_base)
/*! @param p00_nptr is required */
/*! @param p00_eptr defaults to 0, meaning that the successfully parsed string is not kept track */
/*! @param p00_base is 0, numbers are hex if they start with 0x, octal if they start with 0 and decimal otherwise */
#define p99_strtoc(...) P99_CALL_DEFARG(p99_strtoc, 3, __VA_ARGS__)
#define p99_strtoc_defarg_1() 0
#define p99_strtoc_defarg_2() 0

P00_C99_DEFARG_DOCU(p99_strtohh, signed char, char const *p00_nptr, char **p00_eptr, int p00_base)
/*! @param p00_nptr is required */
/*! @param p00_eptr defaults to 0, meaning that the successfully parsed string is not kept track */
/*! @param p00_base is 0, numbers are hex if they start with 0x, octal if they start with 0 and decimal otherwise */
#define p99_strtohh(...) P99_CALL_DEFARG(p99_strtohh, 3, __VA_ARGS__)
#define p99_strtohh_defarg_1() 0
#define p99_strtohh_defarg_2() 0

P00_C99_DEFARG_DOCU(p99_strtouhh, unsigned char, char const *p00_nptr, char **p00_eptr, int p00_base)
/*! @param p00_nptr is required */
/*! @param p00_eptr defaults to 0, meaning that the successfully parsed string is not kept track */
/*! @param p00_base is 0, numbers are hex if they start with 0x, octal if they start with 0 and decimal otherwise */
#define p99_strtouhh(...) P99_CALL_DEFARG(p99_strtouhh, 3, __VA_ARGS__)
#define p99_strtouhh_defarg_1() 0
#define p99_strtouhh_defarg_2() 0


P00_C99_DEFARG_DOCU(p99_strtoh, signed short, char const *p00_nptr, char **p00_eptr, int p00_base)
/*! @param p00_nptr is required */
/*! @param p00_eptr defaults to 0, meaning that the successfully parsed string is not kept track */
/*! @param p00_base is 0, numbers are hex if they start with 0x, octal if they start with 0 and decimal otherwise */
#define p99_strtoh(...) P99_CALL_DEFARG(p99_strtoh, 3, __VA_ARGS__)
#define p99_strtoh_defarg_1() 0
#define p99_strtoh_defarg_2() 0

P00_C99_DEFARG_DOCU(p99_strtouh, unsigned short, char const *p00_nptr, char **p00_eptr, int p00_base)
/*! @param p00_nptr is required */
/*! @param p00_eptr defaults to 0, meaning that the successfully parsed string is not kept track */
/*! @param p00_base is 0, numbers are hex if they start with 0x, octal if they start with 0 and decimal otherwise */
#define p99_strtouh(...) P99_CALL_DEFARG(p99_strtouh, 3, __VA_ARGS__)
#define p99_strtouh_defarg_1() 0
#define p99_strtouh_defarg_2() 0


/** This macro is preferable to the @c atoi function. First, it is
 ** specific to @c unsigned and will return values in the correct
 ** range. Then, the default arguments make it functionally equivalent
 ** but add two features:
 **  - overflow handling
 **  - flexible p00_base, namely octal, decimal or hexadecimal conversion
 **/
P00_C99_DEFARG_DOCU(p99_strtou, unsinged, char const *p00_nptr, char **p00_eptr, int p00_base)
/*! @param p00_nptr is required */
/*! @param p00_eptr defaults to 0, meaning that the successfully parsed string is not kept track */
/*! @param p00_base is 0, numbers are hex if they start with 0x, octal if they start with 0 and decimal otherwise */
#define p99_strtou(...) P99_CALL_DEFARG(p99_strtou, 3, __VA_ARGS__)
#define p99_strtou_defarg_1() 0
#define p99_strtou_defarg_2() 0

P00_C99_DEFARG_DOCU(p99_strtoi8, int_least8_t, char const *p00_nptr, char **p00_eptr, int p00_base)
/*! @param p00_nptr is required */
/*! @param p00_eptr defaults to 0, meaning that the successfully parsed string is not kept track */
/*! @param p00_base is 0, numbers are hex if they start with 0x, octal if they start with 0 and decimal otherwise */
#define p99_strtoi8(...) P99_CALL_DEFARG(p99_strtoi8, 3, __VA_ARGS__)
#define p99_strtoi8_defarg_1() 0
#define p99_strtoi8_defarg_2() 0

P00_C99_DEFARG_DOCU(p99_strtot, ptrdiff_t, char const *p00_nptr, char **p00_eptr, int p00_base)
/*! @param p00_nptr is required */
/*! @param p00_eptr defaults to 0, meaning that the successfully parsed string is not kept track */
/*! @param p00_base is 0, numbers are hex if they start with 0x, octal if they start with 0 and decimal otherwise */
#define p99_strtot(...) P99_CALL_DEFARG(p99_strtot, 3, __VA_ARGS__)
#define p99_strtot_defarg_1() 0
#define p99_strtot_defarg_2() 0

P00_C99_DEFARG_DOCU(p99_strtouz, size_t, char const *p00_nptr, char **p00_eptr, int p00_base)
/*! @param p00_nptr is required */
/*! @param p00_eptr defaults to 0, meaning that the successfully parsed string is not kept track */
/*! @param p00_base is 0, numbers are hex if they start with 0x, octal if they start with 0 and decimal otherwise */
#define p99_strtouz(...) P99_CALL_DEFARG(p99_strtouz, 3, __VA_ARGS__)
#define p99_strtouz_defarg_1() 0
#define p99_strtouz_defarg_2() 0


P00_C99_DEFARG_DOCU(p99_strtou8, uint_least8_t, char const *p00_nptr, char **p00_eptr, int p00_base)
/*! @param p00_nptr is required */
/*! @param p00_eptr defaults to 0, meaning that the successfully parsed string is not kept track */
/*! @param p00_base is 0, numbers are hex if they start with 0x, octal if they start with 0 and decimal otherwise */
#define p99_strtou8(...) P99_CALL_DEFARG(p99_strtou8, 3, __VA_ARGS__)
#define p99_strtou8_defarg_1() 0
#define p99_strtou8_defarg_2() 0

P00_C99_DEFARG_DOCU(p99_strtoi16, int_least16_t, char const *p00_nptr, char **p00_eptr, int p00_base)
/*! @param p00_nptr is required */
/*! @param p00_eptr defaults to 0, meaning that the successfully parsed string is not kept track */
/*! @param p00_base is 0, numbers are hex if they start with 0x, octal if they start with 0 and decimal otherwise */
#define p99_strtoi16(...) P99_CALL_DEFARG(p99_strtoi16, 3, __VA_ARGS__)
#define p99_strtoi16_defarg_1() 0
#define p99_strtoi16_defarg_2() 0


P00_C99_DEFARG_DOCU(p99_strtou16, uint_least16_t, char const *p00_nptr, char **p00_eptr, int p00_base)
/*! @param p00_nptr is required */
/*! @param p00_eptr defaults to 0, meaning that the successfully parsed string is not kept track */
/*! @param p00_base is 0, numbers are hex if they start with 0x, octal if they start with 0 and decimal otherwise */
#define p99_strtou16(...) P99_CALL_DEFARG(p99_strtou16, 3, __VA_ARGS__)
#define p99_strtou16_defarg_1() 0
#define p99_strtou16_defarg_2() 0

P00_C99_DEFARG_DOCU(p99_strtoi32, int_least32_t, char const *p00_nptr, char **p00_eptr, int p00_base)
/*! @param p00_nptr is required */
/*! @param p00_eptr defaults to 0, meaning that the successfully parsed string is not kept track */
/*! @param p00_base is 0, numbers are hex if they start with 0x, octal if they start with 0 and decimal otherwise */
#define p99_strtoi32(...) P99_CALL_DEFARG(p99_strtoi32, 3, __VA_ARGS__)
#define p99_strtoi32_defarg_1() 0
#define p99_strtoi32_defarg_2() 0


P00_C99_DEFARG_DOCU(p99_strtou32, uint_least32_t, char const *p00_nptr, char **p00_eptr, int p00_base)
/*! @param p00_nptr is required */
/*! @param p00_eptr defaults to 0, meaning that the successfully parsed string is not kept track */
/*! @param p00_base is 0, numbers are hex if they start with 0x, octal if they start with 0 and decimal otherwise */
#define p99_strtou32(...) P99_CALL_DEFARG(p99_strtou32, 3, __VA_ARGS__)
#define p99_strtou32_defarg_1() 0
#define p99_strtou32_defarg_2() 0


P00_C99_DEFARG_DOCU(p99_strtoi64, int_least64_t, char const *p00_nptr, char **p00_eptr, int p00_base)
/*! @param p00_nptr is required */
/*! @param p00_eptr defaults to 0, meaning that the successfully parsed string is not kept track */
/*! @param p00_base is 0, numbers are hex if they start with 0x, octal if they start with 0 and decimal otherwise */
#define p99_strtoi64(...) P99_CALL_DEFARG(p99_strtoi64, 3, __VA_ARGS__)
#define p99_strtoi64_defarg_1() 0
#define p99_strtoi64_defarg_2() 0


P00_C99_DEFARG_DOCU(p99_strtou64, uint_least64_t, char const *p00_nptr, char **p00_eptr, int p00_base)
/*! @param p00_nptr is required */
/*! @param p00_eptr defaults to 0, meaning that the successfully parsed string is not kept track */
/*! @param p00_base is 0, numbers are hex if they start with 0x, octal if they start with 0 and decimal otherwise */
#define p99_strtou64(...) P99_CALL_DEFARG(p99_strtou64, 3, __VA_ARGS__)
#define p99_strtou64_defarg_1() 0
#define p99_strtou64_defarg_2() 0

#ifndef strtoc
# define strtoc p99_strtoc
#endif

#ifndef strtohh
# define strtohh p99_strtohh
#endif
#ifndef strtoh
# define strtoh p99_strtoh
#endif
#ifndef strto
# define strto p99_strto
#endif
#ifndef strtot
# define strtot p99_strtot
#endif
#ifndef strtoj
# define strtoj p99_strtoj
#endif

#ifndef strtouhh
# define strtouhh p99_strtouhh
#endif
#ifndef strtouh
# define strtouh p99_strtouh
#endif
#ifndef strtou
# define strtou p99_strtou
#endif
#ifndef strtouz
# define strtouz p99_strtouz
#endif
#ifndef strtouj
# define strtouj p99_strtouj
#endif

#ifndef strtoi8
# define strtoi8 p99_strtoi8
#endif
#ifndef strtoi16
# define strtoi16 p99_strtoi16
#endif
#ifndef strtoi32
# define strtoi32 p99_strtoi32
#endif
#ifndef strtoi64
# define strtoi64 p99_strtoi64
#endif

#ifndef strtou8
# define strtou8 p99_strtou8
#endif
#ifndef strtou16
# define strtou16 p99_strtou16
#endif
#ifndef strtou32
# define strtou32 p99_strtou32
#endif
#ifndef strtou64
# define strtou64 p99_strtou64
#endif


/**
 ** @}
 **/

#endif      /* !P99_C99_DEFAULT_H_ */
