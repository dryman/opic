/* This may look like nonsense, but it really is -*- mode: C -*-              */
/*                                                                            */
/* Except for parts copied from previous work and as explicitly stated below, */
/* the authors and copyright holders for this work are as follows:            */
/* (C) copyright  2010-2013 Jens Gustedt, INRIA, France                       */
/* (C) copyright  2013 Pierre-Nicolas Clauss                                  */
/* (C) copyright  2012 William Morris                                         */
/*                                                                            */
/* This file is free software; it is part of the P99 project.                 */
/* You can redistribute it and/or modify it under the terms of the QPL as     */
/* given in the file LICENSE. It is distributed without any warranty;         */
/* without even the implied warranty of merchantability or fitness for a      */
/* particular purpose.                                                        */
/*                                                                            */
#ifndef     P99_INT_H_
# define    P99_INT_H_

/**
 ** @file
 ** @brief Macros handling integer types and initialization.
 **
 ** The initialization features in this file might produce many
 ** compiler warnings, such as "missing braces in initializer" or
 ** something similar. This is because we have to use a
 ** catch all initializer of the form <code>{ 0 }</code>. Such a
 ** flattened initializer is explicitly covered by the standard but
 ** seems to be considered bad style by some people.
 **
 ** If you use the features of this file and switch all warnings
 ** on for such a compiler you will probably have a hard time
 ** detecting real and interesting warning for all these initializer
 ** warnings. Therefore we switch off such warnings for compilers that
 ** we know cause such a problem.
 **/

#include "p99_c99.h"
#include "p99_id.h"
#include "p99_type.h"

#if P99_COMPILER & (P99_COMPILER_GNU | P99_COMPILER_OPEN64)
# if P99_GCC_VERSION >= 40200UL
#   pragma GCC diagnostic ignored "-Wmissing-braces"
# endif
#endif

/**
 ** @addtogroup integers Macros to handle integer type expressions
 **
 ** The macros here help with integer handling, e.g to detect if a
 ** type or expression is signed, what the maximum and minimum values
 ** are etc.
 **
 ** @{
 */

#define P00_DOCUMENT_C2(WIDTH) /*! @brief Combine two integer expressions of half the width into one of width WIDTH*/

#ifdef UINT16_MAX
P00_DOCUMENT_C2(16)
#define P99X_UINT16_C2(H, L) ((((uint16_t)(uint8_t)H) << 8u) | (uint16_t)(uint8_t)L)
#endif
#ifdef INT16_MAX
P00_DOCUMENT_C2(16)
#define P99X_INT16_C2(H, L) ((((int16_t)(int8_t)H) << 8u) | (int16_t)(int8_t)L)
#endif
#ifdef UINT32_MAX
P00_DOCUMENT_C2(32)
#define P99X_UINT32_C2(H, L) ((((uint32_t)(uint16_t)H) << 16u) | (uint32_t)(uint16_t)L)
#endif
#ifdef INT32_MAX
P00_DOCUMENT_C2(32)
#define P99X_INT32_C2(H, L) ((((int32_t)(int16_t)H) << 16u) | (int32_t)(int16_t)L)
#endif
#ifdef UINT64_MAX
P00_DOCUMENT_C2(64)
#define P99X_UINT64_C2(H, L) ((((uint64_t)(uint32_t)H) << 32u) | (uint64_t)(uint32_t)L)
#endif
#ifdef INT64_MAX
P00_DOCUMENT_C2(64)
#define P99X_INT64_C2(H, L) ((((int64_t)(int32_t)H) << 32u) | (int64_t)(int32_t)L)
#endif

#ifdef p99x_uint128
P00_DOCUMENT_C2(128)
#define P99X_UINT128_C2(H, L) ((((p99x_uint128)H) << 64u) | (p99x_uint128)L)
#define P99X_UINT128_0 P99X_UINT128_C2(0x0000000000000000, 0x0000000000000000)
#define P99X_UINT128_MAX P99X_UINT128_C2(0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF)
#endif

#ifdef p99x_int128
P00_DOCUMENT_C2(128)
#define P99X_INT128_C2(H, L) ((((p99x_int128)H) << 64u) | (p99x_int128)L)
#define P99X_INT128_MAX P99X_INT128_C2(0x7FFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF)
#define P99X_INT128_MIN P99X_INT128_C2(0x8000000000000000, 0x0000000000000000)
#endif

/**
 ** @brief An unsigned integer type of maximal width that exceeds the
 ** C99 specifications.
 **
 ** Typically this might be of width 128 where the whole tool chain,
 ** in particular the preprocessor, only supports 64.
 **
 ** This @c typedef is always defined.  In the best case, it
 ** coincides with @c uintmax_t - this can be
 ** checked with a macro of the same name.
 ** @see p99x_uint128
 **/
#ifndef p99x_uint128
typedef uintmax_t p99x_uintmax;
#endif

/**
 ** @brief A signed integer type of maximal width that exceeds the
 ** C99 specifications.
 **
 ** Typically this might be of width 128 where the whole tool chain,
 ** in particular the preprocessor, only supports 64.
 **
 ** This @c typedef is always defined.  In the bestcase, it
 ** coincides with @c intmax_t - this can be
 ** checked for with a macro of the same name.
 ** @see p99x_int128
 **/
#ifndef p99x_int128
typedef intmax_t p99x_intmax;
#endif

#ifdef P00_DOXYGEN
/**
 ** @brief An unsigned integer type of width 128 that exceeds the
 ** C99 specifications.
 **
 ** Typically this might be defined when the whole tool chain,
 ** in particular the preprocessor, only supports 64 bits.
 **
 ** This @c typedef does not necessary exist. It can be checked for with a
 ** macro of the same name.
 ** @see p99x_uintmax
 **/
typedef extendedInt p99x_uint128;

/**
 ** @brief A signed integer type of width 128 that exceeds the
 ** C99 specifications.
 **
 ** Typically this might be defined when the whole tool chain,
 ** in particular the preprocessor, only supports 64 bits.
 **
 ** This @c typedef does not necessary exist. It can be checked for with a
 ** macro of the same name.
 ** @see p99x_intmax
 **/
typedef extendedInt p99x_int128;
#endif

#ifdef p99x_uintmax

#define P99X__SIGN_PROMOTE(EXPR)                                                \
((p99x_uintmax)+P99_SIGN_PROMOTE(P99_UE_MAX(EXPR), (p99x_uintmax)+UINTMAX_MAX))

#define P99X__SHIFT(EXPR)                                                       \
((P99_SIGN_PROMOTE(P99_UE_MAX(EXPR), UINTMAX_MAX) > (p99x_uintmax)+UINTMAX_MAX) \
 ? 64u                                                                          \
 : 0u)
#endif

#ifndef P99_HIGH2
# if P99_UINTMAX_WIDTH == 64
#  define P99_HIGH2(X)                                         \
((((X) & P00_B0) ? P00_S0 : 0u)                                \
 | (((X) & P00_B1) ? P00_S1 : 0u)                              \
 | (((X) & P00_B2) ? P00_S2 : 0u)                              \
 | (((X) & P00_B3) ? P00_S3 : 0u)                              \
 | (((X) & P00_B4) ? P00_S4 : 0u)                              \
 | (((X) & P00_B5) ? P00_S5 : 0u))
# endif
#endif
#ifndef P99_HIGH2
# if P99_UINTMAX_WIDTH <= 128
#  define P99_HIGH2(X)                                         \
((((X) & P00_B0) ? P00_S0 : 0u)                                \
 | (((X) & P00_B1) ? P00_S1 : 0u)                              \
 | (((X) & P00_B2) ? P00_S2 : 0u)                              \
 | (((X) & P00_B3) ? P00_S3 : 0u)                              \
 | (((X) & P00_B4) ? P00_S4 : 0u)                              \
 | (((X) & P00_B5) ? P00_S5 : 0u)                              \
 | (((X) & P00_B6) ? P00_S6 : 0u))
# endif
#endif

#ifndef P99X__SHIFT
#define P99X__SHIFT(EXPR) 0
#endif

#ifndef P99X__SIGN_PROMOTE
#define P99X__SIGN_PROMOTE(EXPR) 0
#endif

#define P99_HIGH2_1(X) ((X) == P99_UINTMAX_MAX ? P99_UINTMAX_WIDTH : (P99_HIGH2((X) + UINTMAX_C(1))))

/**
 ** @brief Apply the type macro @a MACRO to an unsigned type that is
 ** compatible with type @a T.
 **
 ** The returned expression is of type @c uintmax_t
 **/
P00_DOCUMENT_TYPE_ARGUMENT(P99_TO_UNSIGNED, 0)
P00_DOCUMENT_MACRO_ARGUMENT(P99_TO_UNSIGNED, 1)
#define P99_TO_UNSIGNED(T, MACRO)                              \
((uintmax_t)                                                   \
 (sizeof(T) < sizeof(signed)                                   \
  ? (sizeof(T) == 1u                                           \
     ? MACRO(unsigned char)                                    \
     : MACRO(unsigned short))                                  \
  : (sizeof(T) < sizeof(unsigned long)                         \
     ? MACRO(unsigned)                                         \
     : (sizeof(T) < sizeof(unsigned long long)                 \
        ? MACRO(unsigned long)                                 \
        : MACRO(unsigned long long)))))

P00_DOCUMENT_TYPE_ARGUMENT(P99_TO_UNSIGN, 0)
P00_DOCUMENT_MACRO_ARGUMENT(P99_TO_UNSIGN, 1)
#define P99_TO_UNSIGN(T, VAL)                                  \
((uintmax_t)                                                   \
 (sizeof(T) < sizeof(signed)                                   \
  ? (sizeof(T) == 1u                                           \
     ? (unsigned char)+(VAL)                                   \
     : (unsigned short)+(VAL))                                 \
  : (sizeof(T) < sizeof(unsigned long)                         \
     ? (unsigned)+(VAL)                                        \
     : (sizeof(T) < sizeof(unsigned long long)                 \
        ? (unsigned long)+(VAL)                                \
        : (unsigned long long)+(VAL)))))



/**
 ** @brief Convert -1 to type @a T
 **
 ** If @a T is a signed type, a representation of the value -1 should
 ** always exist, since the value 1 also exists.
 **
 ** If @a T is an unsigned type, the converted value is guaranteed to
 ** hold the maximum value that is representable in this type. This is
 ** guaranteed to work regardless of the platform's representation of
 ** negative values: integer conversion @b to an unsigned type is
 ** always defined to be modulo 2^N where N is the precision of the
 ** target type.
 **/
#define P99_M1(T) ((T)-1)

/**
 ** @brief Return an unsigned version of P99_M1.
 **
 ** The returned expression is of type @c uintmax_t
 **/
#define P99_M1U(T) (P99_ISSIGNED(T) ? P99_TO_UNSIGN(T, -1) : P99_C(uintmax_t, P99_M1(T)))

#define P00_DOCUMENT_SIGNED(X) /*! @brief Cast the @c int value @c X to type @a T */
#define P00_DOCUMENT_UNSIGNED(X) /*! @brief Cast the @c int value @c X to the unsigned type corresponding to @a T */


/**
 ** @brief Generate an integer expression of type @a T and value @a X.
 **
 ** This macro is suitable for use in preprocessor conditionals,
 ** provided X evaluates to an integer constant.
 **
 ** @warning Beware that the type information @a T is simply ignored
 ** by the preprocessor because its arithmetic is done with types @c
 ** intmax_t or @c uintmax_t. If you want to be sure that it is used
 ** as @c uintmax_t suffix the constant @a X with an "u" or "U".
 **
 ** @warning Don't use this to perform bit-complement arithmetic in the
 ** preprocessor, since @c uintmax_t might have more bits than @a T, the
 ** result might not be what you expect.
 **
 ** @param T must be a type identifier, just one word that represents a type.
 **
 ** @param X could be any integer expression that is allowed in the
 ** same context. It is an error for @a X to evaluate to a pointer value.
 **
 ** The macro itself uses a dirty trick. In preprocessor context of
 ** conditional evaluation the @a T in the expansion is just an
 ** identifier that is unknown to the preprocessor and it is thus
 ** replaced by @c 0. The <code>+</code> sign is thus a binary plus.
 **
 ** In program context @c (T) is interpreted as a cast.  The
 ** <code>+</code> sign is thus a prefix to the integer
 ** expression. This results in an error when an attempt is made to
 ** use this with a pointer value.
 **/
#define P99_C(T, X) ((T)+(X))

#define P00_DOCUMENT_CONSTANT(T) /*! @brief Cast the integer value @c X to type @a T, compatible with the preprocessor @see P99_C */

/* Constants macros for the required typedefs */

#if !defined(SIZE_C)
P00_DOCUMENT_CONSTANT(size_t)
# define SIZE_C(X) P99_C(size_t, X)
#endif

#if !defined(PTRDIFF_C)
P00_DOCUMENT_CONSTANT(ptrdiff_t)
# define PTRDIFF_C(X) P99_C(ptrdiff_t, X)
#endif

#if !defined(WCHAR_C)
P00_DOCUMENT_CONSTANT(wchar_t)
# define WCHAR_C(X) P99_C(wchar_t, X)
#endif

#if !defined(WINT_C)
P00_DOCUMENT_CONSTANT(wint_t)
# define WINT_C(X) P99_C(wint_t, X)
#endif

/* Constants macros for the optional typedefs */

#if defined(SIG_ATOMIC_MAX) && !defined(SIG_ATOMIC_C)
P00_DOCUMENT_CONSTANT(sig_atomic_t)
# define SIG_ATOMIC_C(X) P99_C(sig_atomic_t, X)
#endif

#if defined(UINTPTR_MAX) && !defined(UINTPTR_C)
P00_DOCUMENT_CONSTANT(uintptr_t)
# define UINTPTR_C(X) P99_C(uintptr_t, X)
#endif

#if defined(UINTPTR_MAX) && !defined(INTPTR_C)
P00_DOCUMENT_CONSTANT(intptr_t)
# define INTPTR_C(X) P99_C(intptr_t, X)
#endif




P00_DOCUMENT_SIGNED(0)
#define P99_0(T) P99_C(T, 0)

P00_DOCUMENT_UNSIGNED(0)
#define P99_0U(T) P99_TO_UNSIGN(T, 0)

P00_DOCUMENT_SIGNED(1)
#define P99_1(T) P99_C(T, 1)

P00_DOCUMENT_UNSIGNED(1)
#define P99_1U(T)  P99_TO_UNSIGN(T, 1)

P00_DOCUMENT_SIGNED(2)
#define P99_2(T) P99_C(T, 2)

P00_DOCUMENT_UNSIGNED(2)
#define P99_2U(T)  P99_TO_UNSIGN(T, 2)

P00_DOCUMENT_SIGNED(3)
#define P99_3(T) P99_C(T, 3)

P00_DOCUMENT_UNSIGNED(3)
#define P99_3U(T)  P99_TO_UNSIGN(T, 3)

/**
 ** @brief The maximum representable value of the unsigned type
 ** corresponding to @a T
 **
 ** The returned expression is of type @c uintmax_t
 **/
P00_DOCUMENT_TYPE_ARGUMENT(P99_UT_MAX, 0)
#define P99_UT_MAX(T) (P99_M1U(T))

/**
 ** @brief Half of the maximum representable value of the unsigned type
 ** corresponding to @a T
 **
 ** This is the maximum representable value of the signed type
 ** corresponding to @a T.
 **
 ** The returned expression is of type @c uintmax_t.
 **
 ** @see P99_TMAX
 **/
#define P99_UT_MAX1(T) (P99_UT_MAX(T)/2u)

/**
 ** @brief The negative of half the maximum representable value
 ** of the unsigned type corresponding to @a T
 **
 ** This is generally not the minimum representable value of the signed type
 ** corresponding to @a T, it might deviate by one from that value.
 **
 ** The returned expression is of type @a T.
 **
 ** @see P99_TMIN
 **/
#define P00_ST_MIN1(T) (-(T)P99_UT_MAX1(T))

/**
 ** @brief Determine if @a T is an unsigned or signed integral type
 **
 ** This works as follows:
 ** - If @a T is signed then -1 in that type is always less than 0 in
 **    that type
 ** - If @a T is unsigned then conversion of -1 to that type gives the
 **    maximally encodable value for that type. This is always greater
 **    than 0 in that type,
 ** - If @a T is @c _Bool or equivalent, -1 converted to it results in
 **    1 and 0 is also mapped to 0. Thus it is detected as unsigned.
 **
 ** @see P99_SIGNED for a similar macro that takes an expression as an
 ** argument
 **/
P00_DOCUMENT_TYPE_ARGUMENT(P99_ISSIGNED, 0)
#define P99_ISSIGNED(T) (P99_M1(T) < P99_1(T))

/**
 ** @brief Compute expression @a A and apply integer promotion rules
 ** under the constraint of expression @a B.
 **
 ** Expression @a A is evaluated exactly once. Expression @a B is only
 ** used for its type and never evaluated.
 **
 ** The result can always be determined at compile time, if @a A can
 ** be determined then, regardless of the actual value of @a B.  But
 ** it is only a constant expression in the strict sense of C99 if
 ** both @a A and @a B are so.
 **
 ** @warning Due to the integer promotion rules the resulting
 ** expression has a width that is at least that of @c int, even if @a
 ** A and @a B have smaller width than that.
 **/
#define P99_SIGN_PROMOTE(A, B) (1 ? (A) : (B))


#define P00_SEE_PROMOTE /*! @see P99_SIGN_PROMOTE for rules about integer sign promotion */

#define P00_DOCUMENT_PROMOTE(X) /*! @brief Promote the integer value @c X under the constraint of expression @a EXPR */

P00_DOCUMENT_PROMOTE(0)
P00_SEE_PROMOTE
#define P99_PROMOTE_0(EXPR) P99_SIGN_PROMOTE(0, (EXPR))

P00_DOCUMENT_PROMOTE(1)
P00_SEE_PROMOTE
#define P99_PROMOTE_1(EXPR) P99_SIGN_PROMOTE(1, (EXPR))

P00_DOCUMENT_PROMOTE(2)
P00_SEE_PROMOTE
#define P99_PROMOTE_2(EXPR) P99_SIGN_PROMOTE(2, (EXPR))

P00_DOCUMENT_PROMOTE(3)
P00_SEE_PROMOTE
#define P99_PROMOTE_3(EXPR) P99_SIGN_PROMOTE(3, (EXPR))

P00_DOCUMENT_PROMOTE(0U)
P00_SEE_PROMOTE
#define P99_PROMOTE_0U(EXPR) P99_SIGN_PROMOTE(0U, (EXPR))

P00_DOCUMENT_PROMOTE(1u)
P00_SEE_PROMOTE
#define P99_PROMOTE_1U(EXPR) P99_SIGN_PROMOTE(1U, (EXPR))

P00_DOCUMENT_PROMOTE(2u)
P00_SEE_PROMOTE
#define P99_PROMOTE_2U(EXPR) P99_SIGN_PROMOTE(2U, (EXPR))


P00_DOCUMENT_PROMOTE(-1)
P00_SEE_PROMOTE
#define P99_PROMOTE_M1(EXPR) P99_SIGN_PROMOTE(-1, (EXPR))

/**
 ** @brief Promote the integer value @c -1 under the constraint of the
 ** unsigned promoted expression @a EXPR
 ** */
P00_SEE_PROMOTE
#define P99_PROMOTE_M1U(EXPR) P99_SIGN_PROMOTE(P99_PROMOTE_M1(EXPR), P99_PROMOTE_0U(EXPR))

/**
 ** @brief The maximum representable value of the unsigned type
 ** promoted with respect to expression @a EXPR.
 **
 ** The returned expression is of unsigned integer type.
 **/
P00_SEE_PROMOTE
#define P99_UE_MAX(EXPR) (P99_PROMOTE_M1U(EXPR))

/**
 ** @brief Half of the maximum representable value of the unsigned type
 ** promoted with respect to expression @a EXPR
 **
 ** This is the maximum representable value of the signed type
 ** promoted with respect to @a EXPR
 **
 ** The returned expression is of unsigned integer type.
 **
 ** @see P99_TMAX
 **/
P00_SEE_PROMOTE
#define P99_UE_MAX1(EXPR) (P99_UE_MAX(EXPR)/P99_PROMOTE_2U(EXPR))


#ifdef DOXYGEN
/**
 ** @brief The width of the integral type of expression @a EXPR.
 **
 ** This is the precision, plus a sign bit if the type is
 ** signed.
 **
 ** The resulting expression is evaluated at compile time and may be
 ** used in constant expressions.
 ** @warning These are not necessarily all bits that are @em used by
 ** the type, there might be padding bits.
 ** @see P99_TWIDTH
 ** @see P99_EPREC
 ** @see P99_EPADDING
 **/
P00_SEE_PROMOTE
#define P99_EWIDTH(EXPR)

/**
 ** @brief Give the maximum representable value of type @a T
 **/
P00_DOCUMENT_TYPE_ARGUMENT(P99_TMAX, 0)
#define P99_TMAX(T)

/**
 ** @brief Give the minimum representable value of type @a T
 **/
P00_DOCUMENT_TYPE_ARGUMENT(P99_TMIN, 0)
#define P99_TMIN(T)

#endif

#ifdef p99x_uintmax
#define P99_EWIDTH(EXPR)                                                                \
  (P99X__SHIFT(EXPR)                                                                    \
 ? (P99_HIGH2_1((uintmax_t)+(P99_UE_MAX(EXPR)>>P99X__SHIFT(EXPR))) + P99X__SHIFT(EXPR)) \
 : P99_HIGH2_1(P99_UE_MAX(EXPR))                                                        \
 )
#else
#define P99_EWIDTH(EXPR) P99_HIGH2_1(P99_UE_MAX(EXPR))
#endif

/**
 ** @brief The precision, i.e the number of significant bits in the
 ** integral type of expression @a EXPR.
 **
 ** The resulting expression is evaluated at compile time and may be
 ** used in constant expressions.
 ** @warning this is not necessarily the width of @a T
 ** @see P99_TPREC
 ** @see P99_EWIDTH
 ** @see P99_EPADDING
 **/
P00_SEE_PROMOTE
#define P99_EPREC(EXPR) (P99_EWIDTH(EXPR) - P99_SIGNED(EXPR))

/**
 ** @brief The padding bits of the integral type of expression @a EXPR.
 **
 ** These are the bits that are not used for the numerical
 ** representation of the values. On most architectures and for most
 ** types this will be 0. But for e.g for @c _Bool this will be at
 ** least 7.
 **
 ** The resulting expression is evaluated at compile time and may be
 ** used in constant expressions.
 ** @see P99_TPADDING
 ** @see P99_EWIDTH
 ** @see P99_EPREC
 **/
P00_SEE_PROMOTE
#define P99_EPADDING(EXPR) (sizeof(P99_PROMOTE_0(EXPR))*CHAR_BIT - P99_EWIDTH(EXPR))

#define P99_SE_MAX(EXPR)                                       \
((((P99_PROMOTE_1(EXPR)                                        \
    << (P99_EWIDTH(EXPR) - 2U))                                \
   - P99_PROMOTE_1(EXPR))                                      \
  << 1U)                                                       \
 + P99_PROMOTE_1(EXPR))


/**
 ** @brief The negative of half the maximum representable value
 ** of the promoted integral type of expression @a EXPR
 **
 ** This is generally not the minimum representable value of the signed type
 ** corresponding to @a EXPR, it might deviate by one from that value.
 **
 ** The returning expression is of type @a T.
 **
 ** @see P99_TMIN
 **/
#define P00_SE_MIN1(EXPR) (-P99_SE_MAX(EXPR))

/**
 ** @brief Determine if @a EXPR has an unsigned or signed integral type
 **
 ** Note that this macro does not evaluate @a EXPR but uses it only to
 ** determine its signedness. There are no side effects.
 **
 ** The result can always be determined at compile time, but it is not
 ** a constant expression in the strict sense of C99 if @a EXPR is not
 ** so.
 **
 ** Beware, the result of this expression is not the sign of @a EXPR,
 ** but whether or not the type of it could hold a signed value.
 **
 ** @see P99_ISSIGNED for a similar macro that takes a type as an argument
 **/
P00_SEE_PROMOTE
#define P99_SIGNED(EXPR) (P99_PROMOTE_M1(EXPR) < P99_PROMOTE_1(EXPR))


P99_CONST_FUNCTION
p99_inline
uintmax_t p00_abs_signed(intmax_t p00_a) {
  uintmax_t p00_aa = p00_a;
  /* The minus is taken on the unsigned value, so it gives the
     correct result with -INTMAX_MAX, namely INTMAX_MAX, which might
     not be representable for two's complement representation. */
  return (p00_a < INTMAX_C(0)) ? -p00_aa : p00_a;
}

/**
 ** @brief Compute the absolute value of an integral expression.
 **
 ** @return The return type of this macro is @c uintmax_t. It must be
 ** so, since if we have a two's complement representation the value
 ** @c -INTMAX_MIN is not representable in @c intmax_t.
 **
 ** @a EXPR is guaranteed to be evaluated exactly once.
 **
 ** This macro is preferable to the C99 function @c imaxabs. That
 ** function forcibly returns a value of type @c intmax_t, and might
 ** thus fail for @c INTMAX_MIN.
 **/
#define P99_ABS(EXPR) (P99_SIGNED(EXPR) ? p00_abs_signed(EXPR) : P99_C(uintmax_t, EXPR))

#if defined(p99x_uintmax) && defined(p99x_intmax)
P99_CONST_FUNCTION
p99_inline
p99x_uintmax p99x__abs_signed(p99x_intmax p00_a) {
  p99x_uintmax p00_aa = p00_a;
  /* The minus is taken on the unsigned value, so it gives the
     correct result with -INTMAX_MAX, namely INTMAX_MAX, which might
     not be representable for two's complement representation. */
  return (p00_a < (p99x_intmax)0) ? -p00_aa : p00_a;
}
#define P99X_ABS(EXPR) (P99_SIGNED(EXPR) ? p99x__abs_signed(EXPR) : (EXPR))
#endif

#ifndef P99X_ABS
/**
 ** @brief Compute the absolute value of an integral expression, using
 ** integers with extended width.
 **
 ** @return The return type of this macro is p99x_uintmax. It must be
 ** so, since if we have a two's complement representation the minimum
 ** signed value of p99x_intmax is not representable in p99x_intmax.
 **
 ** @a EXPR is guaranteed to be evaluated exactly once.
 **/
# define P99X_ABS P00_ABS
#endif

/**
 ** @brief C99 allows exactly three different possibilities for the
 ** encoding of negative values of integer types.
 **
 ** @see ::P99_SIGNED_REPRESENTATION
 **/
typedef enum {
  p99_signed_representation_invalid = 0,
  p99_signed_representation_magnitude = 1,
  p99_signed_representation_ones = 2,
  p99_signed_representation_twos = 3,
} p99_signed_representation;

/**
 ** @brief C99 allows exactly three different possibilities for the
 ** encoding of negative values of integer types.
 **
 ** The representation can be found by looking at the two least
 ** significant bits of -1 represented in @a T.
 ** @see ::p99_signed_representation
 **/
P00_DOCUMENT_TYPE_ARGUMENT(P99_SIGNED_REPRESENTATION, 0)
#define P99_SIGNED_REPRESENTATION(T) P99_C(p99_signed_representation, (P99_M1(T) & P99_3(T)))


/**
 ** @brief If the sign representation of a type is two's complement
 ** the type has no @em negative zero and can thus represent one more
 ** value.
 **/
#define P99_2COMPLEMENT(T) (P99_SIGNED_REPRESENTATION(T) == p99_signed_representation_twos)

#ifdef p99x_uintmax
P00_DOCUMENT_TYPE_ARGUMENT(P99_TMAX, 0)
#define P99_TMAX(T)                                                     \
((T)                                                                    \
 (P99X__SHIFT((T)0)                                                     \
  ? (P99_ISSIGNED(T) ? P99X__SIGN_PROMOTE((T)-1)/2u : P99_UE_MAX((T)0)) \
  : (P99_ISSIGNED(T) ? P99_UT_MAX1(T) : P99_UT_MAX(T))))

P00_DOCUMENT_TYPE_ARGUMENT(P99_TMIN, 0)
#define P99_TMIN(T)                                                                   \
((T)                                                                                  \
 (P99X__SHIFT((T)0)                                                                   \
  ? (P99_ISSIGNED(T) ? (-(P99X__SIGN_PROMOTE((T)-1)/2u)) - P99_2COMPLEMENT(T) : (T)0) \
  : (P99_ISSIGNED(T) ? (P00_ST_MIN1(T) - P99_2COMPLEMENT(T)) : P99_0(T))))
#else
P00_DOCUMENT_TYPE_ARGUMENT(P99_TMAX, 0)
#define P99_TMAX(T) P99_C(T, P99_ISSIGNED(T) ? P99_UT_MAX1(T) : P99_UT_MAX(T))
P00_DOCUMENT_TYPE_ARGUMENT(P99_TMIN, 0)
#define P99_TMIN(T) P99_C(T, P99_ISSIGNED(T) ? (P00_ST_MIN1(T) - P99_2COMPLEMENT(T)) : P99_0(T))
#endif


/**
 ** @brief C99 allows for exactly three different possibilities for the
 ** encoding of negative values of integer types.
 **
 ** The representation can be found by looking at the two least
 ** significant bits of -1 represented in the type of the expression.
 ** @see ::p99_signed_representation
 **/
#define P99_E_REPRESENTATION(EXPR) ((p99_signed_representation)(P99_PROMOTE_M1(EXPR) & P99_PROMOTE_3(EXPR)))


/**
 ** @brief If the sign representation of a type is two's complement
 ** the type has no @em negative zero and can thus represent one more
 ** value.
 **/
#define P99_E_2COMPLEMENT(EXPR)                                                        \
P99_SIGN_PROMOTE(P99_E_REPRESENTATION(EXPR) == p99_signed_representation_twos, (EXPR))

/**
 ** @brief Give the maximum representable value of the type of the
 ** expression @a EXPR
 **/
#define P99_EMAX(EXPR) (P99_SIGNED(EXPR) ? P99_SE_MAX(EXPR) : P99_PROMOTE_M1(EXPR))

/**
 ** @brief Give the minimum representable value of the type of the
 ** expression @a EXPR
 **/
#define P99_EMIN(EXPR) (P99_SIGNED(EXPR) ? (P00_SE_MIN1(EXPR) - P99_E_2COMPLEMENT(EXPR)) : P99_PROMOTE_0(EXPR))

/**
 ** @brief The precision, i.e the number of significant bits of integral type
 ** @a T.
 **
 ** The resulting expression is evaluated at compile time and may be
 ** used in constant expressions.
 ** @warning this is not necessarily the width of @a T
 ** @see P99_TWIDTH
 ** @see P99_TPADDING
 **/
#define P99_TPREC(T)                                           \
(P99X__SHIFT((T)-1)                                            \
 ? P99_EPREC((T)-1)                                            \
 : P99_HIGH2_1(P99_TMAX(T)))

/**
 ** @brief The width of integral type @a T.
 **
 ** This is the precision, plus a sign bit if @a T is signed.
 **
 ** The resulting expression is evaluated at compile time and may be
 ** used in constant expressions.
 ** @warning These are not necessarily all bits that are @em used by
 ** the type, there might be padding bits.
 ** @see P99_TPREC
 ** @see P99_TPADDING
 **/
#define P99_TWIDTH(T) (P99_TPREC(T) + P99_ISSIGNED(T))

/**
 ** @brief The padding bits of integral type @a T.
 **
 ** These are the bits that are not used for the numerical
 ** representation of the values. On most architectures and for most
 ** types this will be 0. But for e.g for @c _Bool this will be at
 ** least 7.
 **
 ** The resulting expression is evaluated at compile time and may be
 ** used in constant expressions.
 ** @see P99_TWIDTH
 ** @see P99_TPREC
 **/
#define P99_TPADDING(T) ((sizeof(T)*CHAR_BIT) - P99_TWIDTH(T))

#ifdef P00_DOXYGEN
#define P00_DECLARE_OVERFLOW(SUFF)                                                                                                            \
/*! @brief Cast an unsigned type into a signed one as would do a two's complement representation of the signed type. */                       \
/*! If the signed type is in usual two's complement this should be the identity. For other cases this is supposed to do the best possible. */ \
/*! @warning For bizarrely encoded cases this might result in a negative zero or so. */                                                       \
p99_inline                                                                                                                                    \
P99_BUILTIN_TYPE(SUFF,)                                                                                                                       \
P99_PASTE2(p99_twos, SUFF)(P99_BUILTIN_TYPE(u, SUFF) p00_a);                                                                                  \
p99_inline                                                                                                                                    \
P99_BUILTIN_TYPE(SUFF,)                                                                                                                       \
P99_PASTE2(p99_add, SUFF)(P99_BUILTIN_TYPE(SUFF,) p00_a, P99_BUILTIN_TYPE(SUFF,) p00_b, int* p00_err)
#else
#define P00_DECLARE_OVERFLOW(SUFF)                             \
  P00_DECLARE_TWOS(SUFF)                                       \
  P00_DECLARE_UNSIG(SUFF)                                      \
  P00_DECLARE_ADD0(SUFF)                                       \
  P00_DECLARE_ADD1(SUFF)                                       \
  P00_DECLARE_ADD2(SUFF)                                       \
  P00_DECLARE_ADD(SUFF)                                        \
  P00_DECLARE_SUB0(SUFF)                                       \
  P00_DECLARE_SUB1(SUFF)                                       \
  P00_DECLARE_SUB2(SUFF)                                       \
  P00_DECLARE_SUB(SUFF)                                        \
P99_MACRO_END(p99_overflow_, SUFF)


#define P00_DECLARE_TWOS(SUFF)                                                                        \
P99_CONST_FUNCTION                                                                                    \
p99_inline                                                                                            \
P99_BUILTIN_TYPE(SUFF)                                                                                \
P99_PASTE2(p99_twos, SUFF)(P99_BUILTIN_TYPE(u, SUFF) p00_a) {                                         \
  P99_BUILTIN_TYPE(u, SUFF) const type_max = P99_BUILTIN_MAX(SUFF);                                   \
  P99_BUILTIN_TYPE(u, SUFF) const type_max1 = (P99_BUILTIN_TYPE(u, SUFF))(type_max + 1);              \
  /* the unsigned max, as if it had just one value bit more */                                        \
  P99_BUILTIN_TYPE(u, SUFF) const utype_max = (P99_BUILTIN_TYPE(u, SUFF))((2 * type_max) + 1);        \
  return                                                                                              \
    /* for positive values there is nothing to do, this includes the                                  \
       case where the unsigned type has the same number of value bits                                 \
       as the signed type */                                                                          \
    (p00_a <= type_max)                                                                               \
    ? p00_a                                                                                           \
    /* Capture the special case where type_max1 is a trap                                             \
       representation for the signed type */                                                          \
    : (((P99_BUILTIN_MIN(SUFF) == -P99_BUILTIN_MAX(SUFF)) && (p00_a == type_max1))                    \
       ? (P99_BUILTIN_TYPE(SUFF))(-0)                                                                 \
       /* otherwise compute the negative modulo utype_max + 1. for                                    \
          the case that the unsigned type is much wider than the                                      \
          signed type we mask the higher order bits away. */                                          \
       : (P99_BUILTIN_TYPE(SUFF))((-(P99_BUILTIN_TYPE(SUFF))(utype_max - (utype_max & p00_a))) - 1)); \
}

#define P00_DECLARE_UNSIG(SUFF)                                                                         \
P99_CONST_FUNCTION                                                                                      \
p99_inline                                                                                              \
P99_BUILTIN_TYPE(u, SUFF)                                                                               \
P99_PASTE2(p99_unsig, SUFF)(P99_BUILTIN_TYPE(SUFF) p00_a) {                                             \
  /* needed to avoid spurious compiler warnings */                                                      \
  register P99_BUILTIN_TYPE(SUFF) const type_null = 0;                                                  \
  register P99_BUILTIN_TYPE(u, SUFF) const type_max = P99_BUILTIN_MAX(SUFF);                            \
  register P99_BUILTIN_TYPE(u, SUFF) const type_max1 = (P99_BUILTIN_TYPE(u, SUFF))(type_max + 1);       \
  /* the unsigned max, as if it had just one value bit more */                                          \
  register P99_BUILTIN_TYPE(u, SUFF) const utype_max = (P99_BUILTIN_TYPE(u, SUFF))((2 * type_max) + 1); \
  return                                                                                                \
    p00_a >= type_null                                                                                  \
    ? p00_a                                                                                             \
    /* Capture the special case where -INTMAX_MIN can not represented                                   \
       in the signed type */                                                                            \
    : (((P99_BUILTIN_MIN(SUFF) == -P99_BUILTIN_MAX(SUFF)) && (p00_a == P99_BUILTIN_MIN(SUFF)))          \
       ? type_max1                                                                                      \
       /* otherwise compute the negative modulo utype_max + 1. */                                       \
       : (P99_BUILTIN_TYPE(u, SUFF))((utype_max - (P99_BUILTIN_TYPE(u, SUFF))-p00_a) + 1));             \
}

#define P00_DECLARE_ADD0(SUFF)                                                               \
P99_CONST_FUNCTION                                                                           \
p99_inline                                                                                   \
P99_BUILTIN_TYPE(u, SUFF)                                                                    \
P99_PASTE2(p00_add0, SUFF)(P99_BUILTIN_TYPE(SUFF) p00_a, P99_BUILTIN_TYPE(SUFF) p00_b) {     \
  register P99_BUILTIN_TYPE(u, SUFF) p00_ua = P99_PASTE2(p99_unsig, SUFF)(p00_a);            \
  register P99_BUILTIN_TYPE(u, SUFF) p00_ub = P99_PASTE2(p99_unsig, SUFF)(p00_b);            \
  register P99_BUILTIN_TYPE(u, SUFF) p00_res = (P99_BUILTIN_TYPE(u, SUFF))(p00_ua + p00_ub); \
  return p00_res;                                                                            \
}

#define P00_DECLARE_SUB0(SUFF)                                                               \
P99_CONST_FUNCTION                                                                           \
p99_inline                                                                                   \
P99_BUILTIN_TYPE(u, SUFF)                                                                    \
P99_PASTE2(p00_sub0, SUFF)(P99_BUILTIN_TYPE(SUFF) p00_a, P99_BUILTIN_TYPE(SUFF) p00_b) {     \
  register P99_BUILTIN_TYPE(u, SUFF) p00_ua = P99_PASTE2(p99_unsig, SUFF)(p00_a);            \
  register P99_BUILTIN_TYPE(u, SUFF) p00_ub = P99_PASTE2(p99_unsig, SUFF)(p00_b);            \
  register P99_BUILTIN_TYPE(u, SUFF) p00_res = (P99_BUILTIN_TYPE(u, SUFF))(p00_ua - p00_ub); \
  return p00_res;                                                                            \
}

#define P00_DECLARE_ADD2(SUFF)                                                                    \
P99_CONST_FUNCTION                                                                                \
p99_inline                                                                                        \
P99_BUILTIN_TYPE(SUFF)                                                                            \
     P99_PASTE2(p00_add2, SUFF)(P99_BUILTIN_TYPE(SUFF) p00_a,                                     \
                                P99_BUILTIN_TYPE(SUFF) p00_b,                                     \
                                int p00_err[P99_ATLEAST 1]) {                                     \
  /* needed to avoid spurious compiler warnings */                                                \
  register P99_BUILTIN_TYPE(SUFF) const type_null = 0;                                            \
  register P99_BUILTIN_TYPE(u, SUFF) const type_max = P99_BUILTIN_MAX(SUFF);                      \
  register P99_BUILTIN_TYPE(u, SUFF) const type_max1 = (P99_BUILTIN_TYPE(u, SUFF))(type_max + 1); \
  register P99_BUILTIN_TYPE(u, SUFF) p00_uc                                                       \
    = P99_PASTE2(p00_add0, SUFF)(p00_a, p00_b);                                                   \
  register P99_BUILTIN_TYPE(SUFF) p00_c                                                           \
    = P99_PASTE2(p99_twos, SUFF)(p00_uc);                                                         \
  /* (x ^ y) < 0 iff x and y have different signs */                                              \
  if (P99_UNLIKELY(((p00_a ^ p00_b) >= type_null) && ((p00_b ^ p00_c) < type_null))               \
      /* capture the case of the trap value */                                                    \
      || ((P99_BUILTIN_MIN(SUFF) == -P99_BUILTIN_MAX(SUFF))                                       \
          && (p00_uc == type_max1)))                                                              \
    p00_err[0] = ERANGE;                                                                          \
  return p00_c;                                                                                   \
}

#define P00_DECLARE_SUB2(SUFF)                                                                    \
P99_CONST_FUNCTION                                                                                \
p99_inline                                                                                        \
P99_BUILTIN_TYPE(SUFF)                                                                            \
     P99_PASTE2(p00_sub2, SUFF)(P99_BUILTIN_TYPE(SUFF) p00_a,                                     \
                                P99_BUILTIN_TYPE(SUFF) p00_b,                                     \
                                int p00_err[P99_ATLEAST 1]) {                                     \
  /* needed to avoid spurious compiler warnings */                                                \
  register P99_BUILTIN_TYPE(SUFF) const type_null = 0;                                            \
  register P99_BUILTIN_TYPE(u, SUFF) const type_max = P99_BUILTIN_MAX(SUFF);                      \
  register P99_BUILTIN_TYPE(u, SUFF) const type_max1 = (P99_BUILTIN_TYPE(u, SUFF))(type_max + 1); \
  register P99_BUILTIN_TYPE(u, SUFF) p00_uc                                                       \
    = P99_PASTE2(p00_sub0, SUFF)(p00_a, p00_b);                                                   \
  register P99_BUILTIN_TYPE(SUFF) p00_c                                                           \
    = P99_PASTE2(p99_twos, SUFF)(p00_uc);                                                         \
  /* (x ^ y) < 0 iff x and y have different signs */                                              \
  if (P99_UNLIKELY(((p00_a ^ p00_b) < type_null) && ((p00_b ^ p00_c) >= type_null))               \
      /* capture the case of the trap value */                                                    \
      || ((P99_BUILTIN_MIN(SUFF) == -P99_BUILTIN_MAX(SUFF))                                       \
          && (p00_uc == type_max1)))                                                              \
    p00_err[0] = ERANGE;                                                                          \
  return p00_c;                                                                                   \
}

#define P00_DECLARE_ADD1(SUFF)                                 \
P99_CONST_FUNCTION                                             \
p99_inline                                                     \
P99_BUILTIN_TYPE(SUFF)                                         \
     P99_PASTE2(p00_add1, SUFF)(P99_BUILTIN_TYPE(SUFF) p00_a,  \
                                P99_BUILTIN_TYPE(SUFF) p00_b,  \
                                int p00_err[P99_ATLEAST 1]) {  \
  /* needed to avoid spurious compiler warnings */             \
  register P99_BUILTIN_TYPE(SUFF) const type_null = 0;         \
  register P99_BUILTIN_TYPE(SUFF) p00_ret;                     \
  if (p00_b >= type_null) {                                    \
    if (P99_LIKELY(P99_BUILTIN_MAX(SUFF) - p00_b >= p00_a)) {  \
      p00_ret = p00_a + p00_b;                                 \
    } else {                                                   \
      p00_ret = ((p00_b - P99_BUILTIN_MAX(SUFF)) + p00_a) - 1; \
      p00_err[0] = ERANGE;                                     \
    }                                                          \
  } else {                                                     \
    if (P99_LIKELY(P99_BUILTIN_MIN(SUFF) - p00_b <= p00_a)) {  \
      p00_ret = p00_a + p00_b;                                 \
    } else {                                                   \
      p00_ret = ((p00_b + P99_BUILTIN_MAX(SUFF)) + p00_a) + 1; \
      p00_err[0] = ERANGE;                                     \
    }                                                          \
  }                                                            \
  return p00_ret;                                              \
}

#define P00_DECLARE_SUB1(SUFF)                                 \
P99_CONST_FUNCTION                                             \
p99_inline                                                     \
P99_BUILTIN_TYPE(SUFF)                                         \
     P99_PASTE2(p00_sub1, SUFF)(P99_BUILTIN_TYPE(SUFF) p00_a,  \
                                P99_BUILTIN_TYPE(SUFF) p00_b,  \
                                int p00_err[P99_ATLEAST 1]) {  \
  /* needed to avoid spurious compiler warnings */             \
  register P99_BUILTIN_TYPE(SUFF) const type_null = 0;         \
  register P99_BUILTIN_TYPE(SUFF) p00_ret;                     \
  if (p00_b <= type_null) {                                    \
    if (P99_LIKELY(P99_BUILTIN_MAX(SUFF) + p00_b >= p00_a)) {  \
      p00_ret = p00_a - p00_b;                                 \
    } else {                                                   \
      p00_ret = (p00_a - (p00_b + P99_BUILTIN_MAX(SUFF))) + 1; \
      p00_err[0] = ERANGE;                                     \
    }                                                          \
  } else {                                                     \
    if (P99_LIKELY(P99_BUILTIN_MIN(SUFF) + p00_b <= p00_a)) {  \
      p00_ret = p00_a - p00_b;                                 \
    } else {                                                   \
      p00_ret = (p00_a - (p00_b - P99_BUILTIN_MAX(SUFF))) - 1; \
      p00_err[0] = ERANGE;                                     \
    }                                                          \
  }                                                            \
  return p00_ret;                                              \
}

#define P00_DECLARE_ADD(SUFF)                                  \
P99_CONST_FUNCTION                                             \
p99_inline                                                     \
P99_BUILTIN_TYPE(SUFF)                                         \
     P99_PASTE2(p99_add, SUFF)(P99_BUILTIN_TYPE(SUFF) p00_a,   \
                               P99_BUILTIN_TYPE(SUFF) p00_b,   \
                               int p00_err[P99_ATLEAST 1]) {   \
  return                                                       \
    (P99_BUILTIN_MAX(SUFF) < P99_BUILTIN_MAX(u, SUFF))         \
    ? P99_PASTE2(p00_add2, SUFF)(p00_a, p00_b, p00_err)        \
    : P99_PASTE2(p00_add1, SUFF)(p00_a, p00_b, p00_err);       \
}

#define P00_DECLARE_SUB(SUFF)                                  \
P99_CONST_FUNCTION                                             \
p99_inline                                                     \
P99_BUILTIN_TYPE(SUFF)                                         \
     P99_PASTE2(p99_sub, SUFF)(P99_BUILTIN_TYPE(SUFF) p00_a,   \
                               P99_BUILTIN_TYPE(SUFF) p00_b,   \
                               int p00_err[P99_ATLEAST 1]) {   \
  return                                                       \
    (P99_BUILTIN_MAX(SUFF) < P99_BUILTIN_MAX(u, SUFF))         \
    ? P99_PASTE2(p00_sub2, SUFF)(p00_a, p00_b, p00_err)        \
    : P99_PASTE2(p00_sub1, SUFF)(p00_a, p00_b, p00_err);       \
}
#endif

P00_DECLARE_OVERFLOW(c);
P00_DECLARE_OVERFLOW(hh);
P00_DECLARE_OVERFLOW(h);
P00_DECLARE_OVERFLOW();
P00_DECLARE_OVERFLOW(l);
P00_DECLARE_OVERFLOW(ll);

/**
 ** @brief A catch all 0-initializer
 **
 ** Variables of static storage are initialized as if all
 ** components are initialized recursively from 0. Use this macro
 ** to achieve the same effect for @c auto or @c register variables.
 ** All the following declarations are legal:
 ** @code
 ** unsigned a        = P99_INIT;
 ** unsigned b[2]     = P99_INIT;
 ** unsigned *c       = P99_INIT;
 ** unsigned (*)d[3]  = P99_INIT;
 ** unsigned e[4][5]  = P99_INIT;
 ** @endcode
 ** Here, depending on your compiler, the last expression for @c e (and other
 ** deeply nested types) may produce spurious "missing braces"
 ** warnings. These can safely be ignored.
 ** @see P99_LVAL
 ** @see p99_int.h
 **/
#if P99_COMPILER & P99_COMPILER_CLANG
# define P99_INIT                                              \
P99_WARN_INIT_PUSH                                             \
  { 0 }                                                        \
P99_WARN_INIT_POP
#else
# define P99_INIT { 0 }
#endif

#define P00_LVAL1(T) ((T)P99_INIT)
#define P00_LVAL(T, ...) ((T){ __VA_ARGS__ })

/**
 ** @brief Define an lvalue of type @c T, where @c T is the first
 ** parameter in the variable parameter list.
 **
 ** If only @c T is given as a parameter, @c { 0 } is used to
 ** initialize the lvalue. Otherwise the remaining parameters are used
 ** for initialization.
 **
 ** @see P99_AVAL for an array type with unknown base type.
 **
 ** @see P99_RVAL for a macro that returns an rvalue of a certain type
 ** and value.
 **/
#define P99_LVAL(...)                                                              \
P99_WARN_INIT_PUSH                                                                 \
 P99_IF_LE(P99_NARG(__VA_ARGS__),1)(P00_LVAL1(__VA_ARGS__))(P00_LVAL(__VA_ARGS__)) \
P99_WARN_INIT_POP

#ifdef DOXYGEN
/**
 ** @brief Define an rvalue of type @a T and (if given)
 ** value @a VAL
 **
 ** @param T must be a type that can serve as an rvalue, but see below.
 ** @param VAL can be omitted. If given it must be assignment compatible to @a T.
 ** If omitted, an rvalue of type @a T with default initialization is produced.
 **
 ** In a way this is a "safer" cast operation. E.g
 ** @code
 ** void f(double* x);
 ** void f(double x);
 ** int a = 32;
 **
 ** g((double)a);
 ** g(P99_RVAL(double, a));   // essentially the same as previous
 **
 ** f((double*)&a);           // no warning is produced
 ** f(P99_RVAL(double*, &a)); // warning: assignment from incompatible pointer type
 ** @endcode
 **
 ** @pre @a T must be a type to which a value can be assigned. This excludes
 ** function types and array types. It does not exclude pointers to
 ** function types or array types, but unfortunately for syntactic
 ** reasons these two only work if @a T is a @c typedef to that
 ** pointer type.
 **
 ** @see P99_AVAL for an array type with unknown base type.
 **
 ** @see P99_LVAL for a macro that returns an lvalue.
 **/
# define P99_RVAL(T, VAL)
#else
# define P99_RVAL(...)                                         \
P99_WARN_INIT_PUSH                                             \
  P99_IF_EQ_1(P99_NARG(__VA_ARGS__))                           \
  (P00_RVAL1(__VA_ARGS__))                                     \
  (P00_RVAL2(__VA_ARGS__))                                     \
P99_WARN_INIT_PUSH
#endif

#define P00_RVAL1_(T) (((const struct { int p00_bla1; T p00_T1; }){ .p00_bla1 = 0 }).p00_T1)
#define P00_RVAL2_(T) (((      struct { int p00_bla2; T p00_T2; }){ .p00_bla2 = 0 }).p00_T2)

#define P00_RVAL2(T, ...) (P00_RVAL2_(T) = (__VA_ARGS__))
#define P00_RVAL1(T) P00_RVAL2(T, P00_RVAL1_(T))

/**
 ** @brief Define an lvalue of array type @c T with unknown base type.
 **
 ** This should be used for @c typedef array types for which you don't
 ** have control over the base type. It should only be rarely needed.
 **
 ** @remark Even though the result is an lvalue it can't be assigned,
 ** since it is an array type. But @c sizeof such an object will
 ** return the size of the array and the address of the array object
 ** can be taken.
 **
 ** @remark In all contexts other than the two given above (@c sizeof
 ** and addressof operator) this will decay to a pointer to the
 ** unknown base class.
 **
 ** @see P99_LVAL for a macro that returns an lvalue.
 ** @see P99_RVAL for a macro that returns an rvalue of a certain type
 ** and value.
 **/
#define P99_AVAL(T) P00_RVAL2_(T)


P00_DOCUMENT_PERMITTED_ARGUMENT(P99_CHOOSE5, 0)
#define P99_CHOOSE5(xT, cc, cs, ci, cl, cll)                   \
((sizeof(xT) < sizeof(int))                                    \
 ? ((sizeof(xT) < sizeof(short))                               \
    ? cc                                                       \
    : cs)                                                      \
 : ((sizeof(xT) <= sizeof(long))                               \
    ? ((sizeof(xT) == sizeof(int))                             \
       ? ci                                                    \
       : cl)                                                   \
    : cll))


P00_DOCUMENT_PERMITTED_ARGUMENT(P99_PRI, 0)
#define P99_PRI(xT, F, LEN)                                    \
P99_CHOOSE5(xT,                                                \
            "%" #LEN "hh" #F,                                  \
            "%" #LEN "h" #F,                                   \
            "%" #LEN "" #F,                                    \
            "%" #LEN "l" #F,                                   \
            "%" #LEN "ll" #F)

/**
 ** @brief Promote integer expression @a x to the width of @c
 ** uintmax_t but keep signedness if possible.
 **/
#define P00_J(X) (0 ? P99_0(uintmax_t) : (X))


/**
 ** @brief A mask for the higher @a M bits in an N bit word.
 **
 ** This is a generic implementation that should also work for
 ** the case that @a N is less than the width of @c unsigned, or in
 ** other words if the conversion rank of @c uintN_t is less than that
 ** for @c unsigned.
 **
 ** @pre @a N and @a M must evaluate to decimal constants by the preprocessor
 ** @pre @a N must be larger or equal than @a M
 ** @remark this is only implemented for values @a N and @a M less
 ** than the width of @c uintmax_t.
 **/
#define P99_HMASK(N,M) (P99_PASTE2(P00_MASK_, N)^P99_PASTE2(P00_MASK_, P99_MINUS(N, M)))

/**
 ** @addtogroup bitfiddling
 ** @brief Bit fiddling of low order bits
 **
 ** The smart expression used in this group are taken as
 ** summarized in <a
 ** href="http://realtimecollisiondetection.net/blog/?p=78"> Christer
 ** Ericson's blog</a>.
 **
 ** They work because of the special features of unsigned integer
 ** arithmetic that it is arithmetic modulo a power of @c 2.
 **
 ** The notation of the macro and function names has some menomics:
 **
 ** - @c low2 stands for the least significant bit resulting in the
 **   corresponding power of 2, something like <code>1 <<
 **   bitposition</code>
 ** - @c mask stands for a mask that is constructed from this, that is
 **   a sequence of bits that are all one. When @c mask comes after @c
 **   low as in @c low2mask it means that the bit mask follows that
 **   least significant bit. When @c mask comes before @c low as in @c
 **   mask2low it means that the bit mask precedes that least
 **   significant bit.
 ** - The last digit of @c 0 or @c 1 indicates whether that least significant
 **   bit is cleared or left untouched.
 **
 ** Be careful when using the macros in this group:
 ** - they may evaluate their arguments several times
 ** - they @b must be only used with expressions that can be
 **   guaranteed to be unsigned
 **
 ** On the other hand prefer the macro when you known that you have
 ** compile time expressions. Then you may even use them as part of an
 ** <code>#</code><code>if</code> preprocessing conditional.
 **
 ** @{
 **/

/**
 ** @brief extract the least significant bit that is non zero
 **
 ** Example: 01001110 ->  00000010
 **/
#define P99_LOW2(X) ((X) & -(X))

/**
 ** @brief function equivalent to ::P99_LOW2
 **/
P99_CONST_FUNCTION
p99_inline
uintmax_t p99_low2(uintmax_t p00_x) { return P99_LOW2(p00_x); }

/**
 ** @brief mask consisting of bits strictly below the least
 ** significant bit that is non zero
 **
 ** Example: 10011100 ->  00000011
 **/
#define P99_LOW2MASK1(X) ((X) ^ ((X) - 1))

/**
 ** @brief function equivalent to ::P99_LOW2MASK1
 **/
P99_CONST_FUNCTION
p99_inline
uintmax_t p99_low2mask1(uintmax_t p00_x) { return P99_LOW2MASK1(p00_x); }

/**
 ** @brief mask consisting of bits below and including the least
 ** significant bit that is non zero
 **
 ** Example: 10011100 ->  00000111
 **/
#define P99_LOW2MASK0(X) (~(X) & ((X) - 1))

/**
 ** @brief function equivalent to ::P99_LOW2MASK0
 **/
P99_CONST_FUNCTION
p99_inline
uintmax_t p99_low2mask0(uintmax_t p00_x) { return P99_LOW2MASK0(p00_x); }

/**
 ** @brief mask consisting of bits above and including the least
 ** significant bit that is non zero
 **
 ** Example: 10011100 ->  11111100
 **/
#define P99_MASK2LOW1(X) ((X) | -(X))

/**
 ** @brief function equivalent to ::P99_MASK2LOW1
 **/
P99_CONST_FUNCTION
p99_inline
uintmax_t p99_mask2low1(uintmax_t p00_x) { return P99_MASK2LOW1(p00_x); }

/**
 ** @brief mask consisting of bits strictly above the least
 ** significant bit that is non zero
 **
 ** Example: 10011100 ->  11111000
 **/
#define P99_MASK2LOW0(X) ((X) ^ -(X))

/**
 ** @brief function equivalent to ::P99_MASK2LOW0
 **/
P99_CONST_FUNCTION
p99_inline
uintmax_t p99_mask2low0(uintmax_t p00_x) { return P99_MASK2LOW0(p00_x); }

/**
 ** @brief clear the least significant bit that is non zero
 **
 ** Example: 01001110 ->  01001100
 **/
#define P99_LOW2CLEAR(X) ((X) & ((X) - 1))

/**
 ** @brief function equivalent to ::P99_LOW2CLEAR
 **/
P99_CONST_FUNCTION
p99_inline
uintmax_t p99_low2clear(uintmax_t p00_x) { return P99_LOW2CLEAR(p00_x); }

/**
 ** @brief fill all bits below least significant bit that is non zero
 **
 ** Example: 01001100 ->  01001111
 **/
#define P99_LOW2FILL(X) ((X) | ((X) - 1))

/**
 ** @brief function equivalent to ::P99_LOW2FILL
 **/
P99_CONST_FUNCTION
p99_inline
uintmax_t p99_low2fill(uintmax_t p00_x) { return P99_LOW2FILL(p00_x); }

/**
 ** @brief set least significant zero bit
 **
 ** Example: 01001011 ->  01001111
 **/
#define P99_LOW0SET(X) ((X) | ((X) + 1))

/**
 ** @brief function equivalent to ::P99_LOW0SET
 **/
P99_CONST_FUNCTION
p99_inline
uintmax_t p99_low0set(uintmax_t p00_x) { return P99_LOW0SET(p00_x); }

/**
 ** @brief shift number right such that the least significant bit
 ** that is non zero ends up at bit position 0
 **
 ** Example: 10011100 ->  00100111
 **/
#define P99_LOW2SHIFT(X) (P99_LIKELY(!!(X)) ? ((X) / ((X) & -(X))) : 0u)

/**
 ** @brief function equivalent to ::P99_LOW2SHIFT
 **/
P99_CONST_FUNCTION
p99_inline
uintmax_t p99_low2shift(uintmax_t p00_x) { return P99_LOW2SHIFT(p00_x); }

/**
 ** @brief function that returns the next higher value that has
 ** exactly the same popcount as @a x.
 **
 ** That is if @a x has @c K bits set in total, the result will be the
 ** smallest number that also has @c K bits set and that is greater
 ** than @a x.
 **/
P99_CONST_FUNCTION
p99_inline
uintmax_t p99_next_popcount(uintmax_t p00_x) {
  uintmax_t p00_ret = 0;
  if (p00_x) {
    uintmax_t p00_b = P99_LOW2(p00_x);
    uintmax_t p00_t = p00_x + p00_b;
    uintmax_t p00_c = p00_x ^ p00_t;
    uintmax_t p00_m = (p00_c >> 2) / p00_b;
    p00_ret = p00_t | p00_m;
  }
  return p00_ret;
}

/**
 ** @}
 **/

/**
 ** @addtogroup endianess
 ** @brief Help to handle endianess problems of different kind.
 ** @{
 **/

/** @brief an overlay of 2 byte integer and an uint8_array of 2 elements **/
P99_DECLARE_UNION(p00_endian_2);
/** @brief an overlay of 4 byte integer and an uint8_array of 4 elements **/
P99_DECLARE_UNION(p00_endian_4);
/** @brief an overlay of 8 byte integer and an uint8_array of 8 elements **/
P99_DECLARE_UNION(p00_endian_8);
/** @brief an overlay of 16 byte integer and an uint8_array of 16 elements **/
P99_DECLARE_UNION(p00_endian_16);

typedef uint16_t p00_uint_byte_2;
typedef uint32_t p00_uint_byte_4;
typedef uint64_t p00_uint_byte_8;

union p00_endian_2 {
  uint8_t p00_c[2];
  uint16_t p00_i;
};

union p00_endian_4 {
  uint8_t p00_c[4];
  uint32_t p00_i;
};

union p00_endian_8 {
  uint8_t p00_c[8];
  uint64_t p00_i;
};


#ifdef UINT128_MAX
typedef uint128_t p00_uint_byte_16;

union p00_endian_16 {
  uint8_t p00_c[16];
  uint128_t p00_i;
};
#else
# ifdef p99x_uint128
typedef p99x_uint128 p00_uint_byte_16;

union p00_endian_16 {
  uint8_t p00_c[16];
  p99x_uint128 p00_i;
};
# endif
#endif


#define P00_HTON0(N, X, I) [I] = (0xFF & ((X)>>((N - (I + 1))*CHAR_BIT)))
#define P00_HTON(N, X) P99_FOR(N, N, P00_SEQ, P00_HTON0, P99_DUPL(N, X))
#define P99_HTON_INITIALIZER(N, X) { .p00_c = { P00_HTON(N, X) } }

/**
 ** @brief host to network transformation of integers according to the endianness of the platform
 ** @param N is the number of bytes of the type
 ** @param X is the value that is to be transformed
 **/
#define P99_HTON(N, X) (((P99_PASTE2(p00_endian_, N) const)P99_HTON_INITIALIZER(N, X)).p00_i)

/**
 ** @brief host to network transformation of integers according to the endianness of the platform
 ** @param X is the value that is to be transformed
 ** @remark the "S" for @c short in the name refers to a base type of @c uint16_t
 ** @see P99_HTON
 **/
P00_DOCUMENT_NUMBER_ARGUMENT(P99_HTONS, 0)
P00_DOCUMENT_PERMITTED_ARGUMENT(P99_HTONS, 1)
#define P99_HTONS(X) P99_HTON(2, X)

/**
 ** @brief host to network transformation of integers according to the endianness of the platform
 ** @param X is the value that is to be transformed
 ** @remark the "L" for @c long in the name refers to a base type of @c uint32_t
 ** @see P99_HTON
 **/
P00_DOCUMENT_NUMBER_ARGUMENT(P99_HTONL, 0)
P00_DOCUMENT_PERMITTED_ARGUMENT(P99_HTONL, 1)
#define P99_HTONL(X) P99_HTON(4, X)


#define P00_NTOH0(N, X, I) (((P99_PASTE2(p00_uint_byte_, N))((X).p00_c[I]))<<((N - (I + 1))*CHAR_BIT))
#define P00_NTOH(N, X, XX) P99_FOR(N, N, P00_BOR, P00_NTOH0, P99_DUPL(N, XX))
#define P99_NTOH_INITIALIZER(N, X) { .p00_i = (X) }

/**
 ** @brief network to host transformation of integers according to the endianness of the platform
 ** @param N is the number of bytes of the type
 ** @param X is the value that is to be transformed
 **/
#define P99_NTOH(N, X) (P99_PASTE2(p00_uint_byte_, N) const)P00_NTOH(N, X, ((P99_PASTE2(p00_endian_, N) const)P99_NTOH_INITIALIZER(N, X)))

/**
 ** @brief network to host transformation of integers according to the endianness of the platform
 ** @param X is the value that is to be transformed
 ** @remark the "S" for @c short in the name refers to a base type of @c uint16_t
 ** @see P99_NTOH
 **/
P00_DOCUMENT_NUMBER_ARGUMENT(P99_NTOHS, 0)
#define P99_NTOHS(X) P99_NTOH(2, X)

/**
 ** @brief network to host transformation of integers according to the endianness of the platform
 ** @param X is the value that is to be transformed
 ** @remark the "L" for @c long in the name refers to a base type of @c uint32_t
 ** @see P99_NTOH
 **/
P00_DOCUMENT_NUMBER_ARGUMENT(P99_NTOHL, 0)
#define P99_NTOHL(X) P99_NTOH(4, X)



/**
 ** @}
 **/

/**
 ** @}
 **/


#endif      /* !P99_INT_H_ */
