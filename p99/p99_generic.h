/* This may look like nonsense, but it really is -*- mode: C -*-              */
/*                                                                            */
/* Except for parts copied from previous work and as explicitly stated below, */
/* the authors and copyright holders for this work are as follows:            */
/* (C) copyright  2012-2014 Jens Gustedt, INRIA, France                       */
/* (C) copyright  2012 William Morris                                         */
/*                                                                            */
/* This file is free software; it is part of the P99 project.                 */
/* You can redistribute it and/or modify it under the terms of the QPL as     */
/* given in the file LICENSE. It is distributed without any warranty;         */
/* without even the implied warranty of merchantability or fitness for a      */
/* particular purpose.                                                        */
/*                                                                            */
#ifndef     P99_GENERIC_H_
# define    P99_GENERIC_H_

#include "p99_for.h"
#include "p99_enum.h"
#include "p99_typenames.h"
#include "p99_c99.h"

/**
 ** @file
 **/

#ifndef P00_DOXYGEN

#define P00_GENERIC_TYPE(T, ...) T
#define P00_GENERIC_SIZE_(UI, ...) char(*)[UI]
#define P00_GENERIC_EXP_(T, ...) (__VA_ARGS__)
#define P00_GENERIC_LIT_(T, EXP) (EXP){ 0 }

#define P00_GENERIC_SIZE_LIT(EXP, PAIR, I) P00_GENERIC_EXPRESSION(P00_GENERIC_SIZE_, P00_GENERIC_LIT_, EXP, PAIR, I)
#define P00_GENERIC_SIZE(EXP, PAIR, I) P00_GENERIC_EXPRESSION(P00_GENERIC_SIZE_, P00_GENERIC_EXP_, EXP, PAIR, I)
#define P00_GENERIC_EXP(EXP, PAIR, I) P00_GENERIC_EXPRESSION(P00_GENERIC_TYPE, P00_GENERIC_EXP_, EXP, PAIR, I)
#define P00_GENERIC_LIT(EXP, PAIR, I) P00_GENERIC_EXPRESSION(P00_GENERIC_TYPE, P00_GENERIC_LIT_, EXP, PAIR, I)

#if p99_has_extension(c_generic_selections)

#define P00_GENERIC_EXPRESSION(TOP, EOP, EXP, PAIR, I)         \
TOP PAIR: EOP PAIR

#define P00_GENERIC_(N, MOP, EXP, DEF, ...)                    \
p99_extension                                                  \
_Generic                                                       \
((EXP),                                                        \
 P99_IF_EMPTY(DEF)()(default: (DEF),)                          \
 P99_FOR((EXP), N, P00_SEQ, MOP, __VA_ARGS__)                  \
 )

#elif defined(__GNUC__)

#define P00_GENERIC_CLOSE(A,B,C) )

#define P00_GENERIC_EXPRESSION(TOP, EOP, EXP, PAIR, I)         \
__builtin_choose_expr                                          \
(__builtin_types_compatible_p(__typeof__ EXP, TOP PAIR),       \
 EOP PAIR

/* If no default is given, the idea of _Generic is to abort
   compilation. To emulate this behavior we would have to produce an
   expression that is valid as such, but can't be used in any valid
   context. Such an expression doesn't exist, I think, since any valid
   expression can always be used in a void context.

   The idea for that case is to use an extern function that never will
   be defined and that bears a special attribute that inhibits this
   function to be called.  This function is then called through a
   sizeof expression for VLA with side effect, such that it only
   triggers when that particular branch is taken.

   Unfortunately gcc had this attribute only from about version 4.3,
   so for versions below that this only produces a link error, much
   later.
   */

#if p99_has_attribute(error)
__attribute__((__error__("Invalid choice in type generic expression")))
#endif
extern size_t p00_invalid_type_in_generic(char const*);

#define P00_INVALID_TYPE_IN_GENERIC(EXP, STR)                  \
p00_invalid_type_in_generic(__FILE__                           \
                            P99_STRINGIFY(:__LINE__)           \
                            ": invalid type generic choice `"  \
                            P99_STRINGIFY(EXP)                 \
                            "` for "                           \
                            STR)

#define P00_GENERIC_(N, MOP, EXP, DEF, ...)                                \
  P99_FOR((EXP), N, P00_SEQ, MOP, __VA_ARGS__),                            \
    P99_IF_EMPTY(DEF)(P00_INVALID_TYPE_IN_GENERIC(EXP, #__VA_ARGS__))(DEF) \
    P99_FOR(, N, P00_SER, P00_GENERIC_CLOSE, P99_DUPL(N, ))

#endif

#define P00_GENERIC0(MOP, EXP, DEF, ...)                       \
P00_GENERIC_                                                   \
(                                                              \
 P99_NARG(__VA_ARGS__),                                        \
 P00_ROBUST(MOP),                                              \
 P00_ROBUST(EXP),                                              \
 P00_ROBUST(DEF),                                              \
 __VA_ARGS__)

#define P00_GENERIC(N, ...) P99_IF_LT(N, 3)()(P00_GENERIC0(__VA_ARGS__))

P00_DOCUMENT_PERMITTED_ARGUMENT(P99_GENERIC, 0)
P00_DOCUMENT_PERMITTED_ARGUMENT(P99_GENERIC, 2)
#define P99_GENERIC(...) P00_GENERIC(P99_NARG(__VA_ARGS__), P00_GENERIC_EXP, __VA_ARGS__)

P00_DOCUMENT_PERMITTED_ARGUMENT(P99_GENERIC_LIT, 0)
P00_DOCUMENT_PERMITTED_ARGUMENT(P99_GENERIC_LIT, 2)
#define P99_GENERIC_LIT(...) P00_GENERIC(P99_NARG(__VA_ARGS__), P00_GENERIC_LIT, __VA_ARGS__)

#define P00_GENERIC_SIZE0(...) P00_GENERIC(P99_NARG(__VA_ARGS__), P00_GENERIC_SIZE, __VA_ARGS__)

P00_DOCUMENT_PERMITTED_ARGUMENT(P99_GENERIC_SIZE, 0)
P00_DOCUMENT_PERMITTED_ARGUMENT(P99_GENERIC_SIZE, 2)
P00_DOCUMENT_PERMITTED_ARGUMENT(P99_GENERIC_SIZE, 3)
#define P99_GENERIC_SIZE(UI, ...) P00_GENERIC_SIZE0((char(*)[(size_t)(UI)]){ 0 }, __VA_ARGS__)

#define P00_GENERIC_SIZE_LIT0(...) P00_GENERIC(P99_NARG(__VA_ARGS__), P00_GENERIC_SIZE_LIT, __VA_ARGS__)

P00_DOCUMENT_PERMITTED_ARGUMENT(P99_GENERIC_SIZE_LIT, 0)
P00_DOCUMENT_PERMITTED_ARGUMENT(P99_GENERIC_SIZE_LIT, 2)
P00_DOCUMENT_PERMITTED_ARGUMENT(P99_GENERIC_SIZE_LIT, 3)
#define P99_GENERIC_SIZE_LIT(UI, ...) P00_GENERIC_SIZE_LIT0((char(*)[(size_t)(UI)]){ 0 }, __VA_ARGS__)


#if p99_has_extension(c_generic_selections)

# define P99_TYPED_TERN(COND, YES, NO)                         \
(P99_GENERIC                                                   \
 ((char(*)[1 + !!(COND)]){ 0 },                                \
  (NO),                                                        \
  (char(*)[2], (YES))))

#elif defined(__GNUC__)

# define P99_TYPED_TERN __builtin_choose_expr

#else

#define P99_TYPED_TERN(COND, YES, NO) only_implemented_with_C11_or_gcc


#endif

/* A first example for the usefulness of type generic
   expressions. Implement creal and cimag type generic functions
   ourselves. */
#ifndef __STDC_NO_COMPLEX__
# ifdef creal
#  undef creal
# endif
# define creal(A)                                              \
P99_GENERIC((A)+0,                                             \
            p99_creall,                                        \
            (float _Complex, p99_crealf),                      \
            (double _Complex, p99_creal))                      \
 (A)

# ifdef cimag
#  undef cimag
# endif
# define cimag(A)                                              \
P99_GENERIC((A)+0,                                             \
            p99_cimagl,                                        \
            (float _Complex, p99_cimagf),                      \
            (double _Complex, p99_cimag))                      \
 (A)
#endif

#define P00_CHAR_SIGNED (CHAR_MAX < UCHAR_MAX)

#define P00_RVALUE(X) (1 ? (X) : (X))

#define P00_SVALUE(X) ((X)+0)

#define P00_SVALUE_SIG(T, X)                                   \
  (T, (T)(intmax_t)(X)),                                       \
  (T const, (T)(intmax_t)(X)),                                 \
  (T volatile, (T)(intmax_t)(X)),                              \
  (T const volatile, (T)(intmax_t)(X)),                        \
  (_Atomic(T), (T)(intmax_t)(X)),                              \
  (_Atomic(T) const, (T)(intmax_t)(X)),                        \
  (_Atomic(T) volatile, (T)(intmax_t)(X)),                     \
  (_Atomic(T) const volatile, (T)(intmax_t)(X))

#define P00_SVALUE_UNS(T, X)                                   \
  (T, (T)(uintmax_t)(X)),                                      \
  (T const, (T)(uintmax_t)(X)),                                \
  (T volatile, (T)(uintmax_t)(X)),                             \
  (T const volatile, (T)(uintmax_t)(X)),                       \
  (_Atomic(T), (T)(uintmax_t)(X)),                             \
  (_Atomic(T) const, (T)(uintmax_t)(X)),                       \
  (_Atomic(T) volatile, (T)(uintmax_t)(X)),                    \
  (_Atomic(T) const volatile, (T)(uintmax_t)(X))

#define P00_SVALUE_QUAL(X, Q)                                                                           \
(char Q, ((char)P99_TYPED_TERN(P00_CHAR_SIGNED, (schar)(intmax_t)(X), (uchar)(uintmax_t)(X)))),         \
(_Atomic(char) Q, ((char)P99_TYPED_TERN(P00_CHAR_SIGNED, (schar)(intmax_t)(X), (uchar)(uintmax_t)(X))))

#define P00_SVALUE_CHAR(X)                                     \
  P00_SVALUE_QUAL(X, ),                                        \
  P00_SVALUE_QUAL(X, const),                                   \
  P00_SVALUE_QUAL(X, volatile),                                \
  P00_SVALUE_QUAL(X, const volatile)

P00_DOCUMENT_PERMITTED_ARGUMENT(P99_SVALUE, 0)
#define P99_SVALUE(X)                                             \
P99_GENERIC((X),                                                  \
            P00_SVALUE(X),                                        \
            (void*, (X)),                                         \
            /*(void const*, (X)),                                 \
            (void volatile*, (X)),                                \
            (void const volatile*, (X)),                          \
            (void*const, (X)),                                    \
            (void const*const, (X)),                              \
            (void volatile*const, (X)),                           \
            (void const volatile*const, (X)),                     \
            (void*volatile, (X)),                                 \
            (void const*volatile, (X)),                           \
            (void volatile*volatile, (X)),                        \
            (void const volatile*volatile, (X)),                  \
            (void*const volatile, (X)),                           \
            (void const*const volatile, (X)),                     \
            (void volatile*const volatile, (X)),                  \
            (void const volatile*const volatile, (X)),*/          \
            /* currently clang crashes with restrict */           \
            /*(void* restrict, (X)),                              \
            (void const* restrict, (X)),                          \
            (void volatile* restrict, (X)),                       \
            (void const volatile* restrict, (X)),                 \
            (void*const restrict, (X)),                           \
            (void const*const restrict, (X)),                     \
            (void volatile*const restrict, (X)),                  \
            (void const volatile*const restrict, (X)),            \
            (void*volatile restrict, (X)),                        \
            (void const*volatile restrict, (X)),                  \
            (void volatile*volatile restrict, (X)),               \
            (void const volatile*volatile restrict, (X)),         \
            (void*const volatile restrict, (X)),                  \
            (void const*const volatile restrict, (X)),            \
            (void volatile*const volatile restrict, (X)),         \
            (void const volatile*const volatile restrict, (X)),*/ \
            P00_SVALUE_CHAR(X),                                   \
            P00_SVALUE_SIG(schar, X),                             \
            P00_SVALUE_SIG(sshort, X),                            \
            P00_SVALUE_UNS(_Bool, X),                             \
            P00_SVALUE_UNS(uchar, X),                             \
            P00_SVALUE_UNS(ushort, X))

#define P00_QVALUE_SIG(T, X)                                                  \
  (T, (T)(intmax_t)(X)),                                                      \
  (T const, (T const)(intmax_t const)(X)),                                    \
  (T volatile, (T volatile)(intmax_t volatile)(X)),                           \
  (T const volatile, (T const volatile)(intmax_t const volatile)(X)),         \
  (_Atomic(T), (T)(intmax_t)(X)),                                             \
  (_Atomic(T) const, (T const)(intmax_t const)(X)),                           \
  (_Atomic(T) volatile, (T volatile)(intmax_t volatile)(X)),                  \
  (_Atomic(T) const volatile, (T const volatile)(intmax_t const volatile)(X))

#define P00_QVALUE_UNS(T, X)                                                   \
  (T, (T)(uintmax_t)(X)),                                                      \
  (T const, (T const)(uintmax_t const)(X)),                                    \
  (T volatile, (T volatile)(uintmax_t volatile)(X)),                           \
  (T const volatile, (T const volatile)(uintmax_t const volatile)(X)),         \
  (_Atomic(T), (T)(uintmax_t)(X)),                                             \
  (_Atomic(T) const, (T const)(uintmax_t const)(X)),                           \
  (_Atomic(T) volatile, (T volatile)(uintmax_t volatile)(X)),                  \
  (_Atomic(T) const volatile, (T const volatile)(uintmax_t const volatile)(X))

#define P00_QVALUE_QUAL(X, Q)                                                                                     \
(char Q, ((char Q)P99_TYPED_TERN(P00_CHAR_SIGNED, (schar Q)(intmax_t Q)(X), (uchar Q)(uintmax_t Q)(X)))),         \
(_Atomic(char) Q, ((char Q)P99_TYPED_TERN(P00_CHAR_SIGNED, (schar Q)(intmax_t Q)(X), (uchar Q)(uintmax_t Q)(X))))

#define P00_QVALUE_CHAR(X)                                     \
  P00_QVALUE_QUAL(X, ),                                        \
  P00_QVALUE_QUAL(X, const),                                   \
  P00_QVALUE_QUAL(X, volatile),                                \
  P00_QVALUE_QUAL(X, const volatile)



P00_DOCUMENT_PERMITTED_ARGUMENT(P99_QVALUE, 0)
#define P99_QVALUE(X)                                          \
P99_GENERIC((X),                                               \
            P00_RVALUE(X),                                     \
            P00_QVALUE_CHAR(X),                                \
            P00_QVALUE_SIG(schar, X),                          \
            P00_QVALUE_SIG(sshort, X),                         \
            P00_QVALUE_UNS(_Bool, X),                          \
            P00_QVALUE_UNS(uchar, X),                          \
            P00_QVALUE_UNS(ushort, X))


#define P00_TYPE_CHOICE(YES, T, I) (T, YES)

P00_DOCUMENT_PERMITTED_ARGUMENT(P99_TYPE_CHOICE, 0)
P00_DOCUMENT_PERMITTED_ARGUMENT(P99_TYPE_CHOICE, 1)
P00_DOCUMENT_PERMITTED_ARGUMENT(P99_TYPE_CHOICE, 2)
#define P99_TYPE_CHOICE(EXP, YES, NO, ...)                                   \
P99_GENERIC                                                                  \
((EXP),                                                                      \
 NO,                                                                         \
 P99_FOR(YES, P99_NARG(__VA_ARGS__), P00_SEQ, P00_TYPE_CHOICE, __VA_ARGS__))

P00_DOCUMENT_PERMITTED_ARGUMENT(P99_TYPE_UNSIGNED, 0)
#define P99_TYPE_UNSIGNED(EXP)      P99_TYPE_CHOICE((EXP), 1, 0, P99_STD_UNSIGNED_TYPES)
P00_DOCUMENT_PERMITTED_ARGUMENT(P99_TYPE_SIGNED, 0)
#define P99_TYPE_SIGNED(EXP)        P99_TYPE_CHOICE((EXP), 1, 0, P99_STD_SIGNED_TYPES)
P00_DOCUMENT_PERMITTED_ARGUMENT(P99_TYPE_REAL_FLOATING, 0)
#define P99_TYPE_REAL_FLOATING(EXP) P99_TYPE_CHOICE((EXP), 1, 0, P99_STD_REAL_FLOATING_TYPES)
#ifndef __STDC_NO_COMPLEX__
P00_DOCUMENT_PERMITTED_ARGUMENT(P99_TYPE_COMPLEX, 0)
# define P99_TYPE_COMPLEX(EXP)       P99_TYPE_CHOICE((EXP), 1, 0, P99_STD_COMPLEX_TYPES)
#endif
P00_DOCUMENT_PERMITTED_ARGUMENT(P99_TYPE_FLOATING, 0)
#define P99_TYPE_FLOATING(EXP)      P99_TYPE_CHOICE((EXP), 1, 0, P99_STD_FLOATING_TYPES)
P00_DOCUMENT_PERMITTED_ARGUMENT(P99_TYPE_BASIC, 0)
#define P99_TYPE_BASIC(EXP)         P99_TYPE_CHOICE((EXP), 1, 0, P99_STD_BASIC_TYPES)
P00_DOCUMENT_PERMITTED_ARGUMENT(P99_TYPE_CHARACTER, 0)
#define P99_TYPE_CHARACTER(EXP)     P99_TYPE_CHOICE((EXP), 1, 0, P99_STD_CHARACTER_TYPES)
P00_DOCUMENT_PERMITTED_ARGUMENT(P99_TYPE_INTEGER, 0)
#define P99_TYPE_INTEGER(EXP)       P99_TYPE_CHOICE((EXP), 1, 0, P99_STD_INTEGER_TYPES)
P00_DOCUMENT_PERMITTED_ARGUMENT(P99_TYPE_REAL, 0)
#define P99_TYPE_REAL(EXP)          P99_TYPE_CHOICE((EXP), 1, 0, P99_STD_REAL_TYPES)
P00_DOCUMENT_PERMITTED_ARGUMENT(P99_TYPE_ARITHMETIC, 0)
#define P99_TYPE_ARITHMETIC(EXP)    P99_TYPE_CHOICE((EXP), 1, 0, P99_STD_ARITHMETIC_TYPES)

#define P00_SIZE_CHOICE(YES, UI, I) (char(*)[(size_t)(UI)], YES)

P00_DOCUMENT_PERMITTED_ARGUMENT(P99_SIZE_CHOICE, 0)
P00_DOCUMENT_PERMITTED_ARGUMENT(P99_SIZE_CHOICE, 1)
P00_DOCUMENT_PERMITTED_ARGUMENT(P99_SIZE_CHOICE, 2)
#define P99_SIZE_CHOICE(UI, YES, NO, ...)                                    \
P99_GENERIC                                                                  \
 ((char(*)[(size_t)(UI)])0,                                                  \
 NO,                                                                         \
 P99_FOR(YES, P99_NARG(__VA_ARGS__), P00_SEQ, P00_SIZE_CHOICE, __VA_ARGS__))


P00_DOCUMENT_PERMITTED_ARGUMENT(P99_SIZE_INDICATOR, 0)
#define P99_SIZE_INDICATOR(UI, ...) P99_SIZE_CHOICE(UI, 1, 0, __VA_ARGS__)


#define P00_DECLARE_INLINE_EXPRESSION1(EXT, BASE, EXP, A)      \
P99_CONST_FUNCTION                                             \
p99_inline                                                     \
P99_BUILTIN_TYPE(EXT) P99_PASTE3(p00_gen_, BASE, EXT)          \
(P99_BUILTIN_TYPE(EXT) A)                                      \
{                                                              \
  return (EXP);                                                \
}

#define P00_DECLARE_INLINE_EXPRESSION2(EXT, BASE, EXP, A, B)   \
P99_CONST_FUNCTION                                             \
p99_inline                                                     \
P99_BUILTIN_TYPE(EXT) P99_PASTE3(p00_gen_, BASE, EXT)          \
(P99_BUILTIN_TYPE(EXT) A, P99_BUILTIN_TYPE(EXT) B)             \
{                                                              \
  return (EXP);                                                \
}

#define P00_DECLARE_INLINE_EXPRESSION3(EXT, BASE, EXP, A, B, C) \
p99_inline                                                      \
P99_BUILTIN_TYPE(EXT) P99_PASTE3(p00_gen_, BASE, EXT)           \
(P99_BUILTIN_TYPE(EXT) A, P99_BUILTIN_TYPE(EXT) B,              \
 P99_BUILTIN_TYPE(EXT) C)                                       \
{                                                               \
  return (EXP);                                                 \
}

#define P00_DECLARE_INLINE_EXPRESSION4(EXT, BASE, EXP, A, B, C, D) \
p99_inline                                                         \
P99_BUILTIN_TYPE(EXT) P99_PASTE3(p00_gen_, BASE, EXT)              \
(P99_BUILTIN_TYPE(EXT) A, P99_BUILTIN_TYPE(EXT) B,                 \
 P99_BUILTIN_TYPE(EXT) C, P99_BUILTIN_TYPE(EXT) D)                 \
{                                                                  \
  return (EXP);                                                    \
}

#define P00_DECLARE_INLINE_EXPRESSION5(EXT, BASE, EXP, A, B, C, D, E) \
p99_inline                                                            \
P99_BUILTIN_TYPE(EXT) P99_PASTE3(p00_gen_, BASE, EXT)                 \
(P99_BUILTIN_TYPE(EXT) A, P99_BUILTIN_TYPE(EXT) B,                    \
 P99_BUILTIN_TYPE(EXT) C, P99_BUILTIN_TYPE(EXT) D,                    \
 P99_BUILTIN_TYPE(EXT) E)                                             \
{                                                                     \
  return (EXP);                                                       \
}

#define P00_DECLARE_INLINE_EXPRESSION6(EXT, BASE, EXP, A, B, C, D, E, F) \
p99_inline                                                               \
P99_BUILTIN_TYPE(EXT) P99_PASTE3(p00_gen_, BASE, EXT)                    \
(P99_BUILTIN_TYPE(EXT) A, P99_BUILTIN_TYPE(EXT) B,                       \
 P99_BUILTIN_TYPE(EXT) C, P99_BUILTIN_TYPE(EXT) D,                       \
 P99_BUILTIN_TYPE(EXT) E, P99_BUILTIN_TYPE(EXT) F)                       \
{                                                                        \
  return (EXP);                                                          \
}

P00_DOCUMENT_IDENTIFIER_ARGUMENT(P99_DECLARE_INLINE_EXPRESSION, 0)
P00_DOCUMENT_IDENTIFIER_ARGUMENT(P99_DECLARE_INLINE_EXPRESSION, 1)
P00_DOCUMENT_PERMITTED_ARGUMENT(P99_DECLARE_INLINE_EXPRESSION, 2)
#define P99_DECLARE_INLINE_EXPRESSION(...)                                                  \
P99_PASTE2(P00_DECLARE_INLINE_EXPRESSION, P99_MINUS(P99_NARG(__VA_ARGS__), 3))(__VA_ARGS__)

#define P00_DECLARE_INLINE_EXPRESSION_(...) P99_DECLARE_INLINE_EXPRESSION(__VA_ARGS__)
#define P00_DECLARE_INLINE_EXPRESSION(ARGS, EXT, I) P00_DECLARE_INLINE_EXPRESSION_(EXT, P00_ROBUST ARGS)

P00_DOCUMENT_PERMITTED_ARGUMENT(P99_DECLARE_INLINE_EXPRESSIONS, 0)
#define P99_DECLARE_INLINE_EXPRESSIONS(NEPL, ...)                                         \
P99_FOR(NEPL, P99_NARG(__VA_ARGS__), P00_SER, P00_DECLARE_INLINE_EXPRESSION, __VA_ARGS__) \
P99_MACRO_END(P99_DECLARE_INLINE_EXPRESSIONS, __VA_ARGS__)

extern void p00_invalid_function(void*, ...);

#define P00_GEN_EXPR(BASE, EXT, I) (P99_BUILTIN_TYPE(EXT), P99_PASTE3(p00_gen_, BASE, EXT))

P00_DOCUMENT_IDENTIFIER_ARGUMENT(P99_GEN_EXPR, 0)
P00_DOCUMENT_PERMITTED_ARGUMENT(P99_GEN_EXPR, 1)
#define P99_GEN_EXPR(BASE, EXPR, ...)                                                 \
P99_GENERIC(EXPR,                                                                     \
            p00_invalid_function,                                                     \
            P99_FOR(BASE, P99_NARG(__VA_ARGS__), P00_SEQ, P00_GEN_EXPR, __VA_ARGS__))




P99_DECLARE_INLINE_EXPRESSIONS((maximum,
                                (p00_a >= p00_b) ? p00_a : p00_b,
                                p00_a, p00_b),
                               P99_STD_REAL_EXTS
                              );

P00_DOCUMENT_PERMITTED_ARGUMENT(P99_GEN_MAX, 0)
P00_DOCUMENT_PERMITTED_ARGUMENT(P99_GEN_MAX, 1)
#define P99_GEN_MAX(A, B)                                      \
P99_GEN_EXPR(maximum, ((A) >= (B)) ? (A) : (B),                \
             P99_STD_REAL_EXTS                                 \
             )                                                 \
((A), (B))

P99_DECLARE_INLINE_EXPRESSIONS((minimum,
                                (p00_a <= p00_b) ? p00_a : p00_b,
                                p00_a, p00_b),
                               P99_STD_REAL_EXTS
                              );

P00_DOCUMENT_PERMITTED_ARGUMENT(P99_GEN_MIN, 0)
P00_DOCUMENT_PERMITTED_ARGUMENT(P99_GEN_MIN, 1)
#define P99_GEN_MIN(A, B)                                      \
P99_GEN_EXPR(minimum, ((A) <= (B)) ? (A) : (B),                \
             P99_STD_REAL_EXTS                                 \
             )                                                 \
((A), (B))


P99_DECLARE_INLINE_EXPRESSIONS((abs,
                                (p00_a >= 0) ? p00_a : -p00_a,
                                p00_a),
                               P99_STD_SIGNED_EXTS, P99_STD_REAL_FLOATING_EXTS
                              );

P99_DECLARE_INLINE_EXPRESSIONS((abs,
                                p00_a,
                                p00_a),
                               P99_STD_UNSIGNED_EXTS
                              );


P00_DOCUMENT_PERMITTED_ARGUMENT(P99_GEN_ABS, 0)
#define P99_GEN_ABS(A) P99_GEN_EXPR(abs, ((A) >= 0) ? (A) : -(A), P99_STD_REAL_EXTS)(A)

#define p00_gen_sind sin
#define p00_gen_sinf sinf
#define p00_gen_sinld sinl
#define p00_gen_sindc csin
#define p00_gen_sinfc csinf
#define p00_gen_sinldc csinl

P00_DOCUMENT_PERMITTED_ARGUMENT(P99_GEN_SIN, 0)
#define P99_GEN_SIN(A) P99_GEN_EXPR(sin, (A), P99_STD_FLOATING_EXTS)(A)

inline int* p00_generic_test(int * p00_a) {
  double *p00_x = 0;
  switch (P99_GEN_ABS(*p00_a % 3)) {
  case 0:
    return P99_GENERIC(&*p00_a,
                       /* empty default expression */,
                       (int*, p00_a),
                       (double*, p00_x+1),
                       (float*, p00_x+2));
#ifndef P99_CSIN_BUG
  case 1:
    return P99_GENERIC(&*p00_a,
                       /* another form of empty default */,
                       (double[7], P99_GEN_SIN(((p00_x+0)))),
                       (int*, p00_a),
                       (float*, p00_x+2));
#endif
  default:
    return P99_GENERIC(&*p00_a,
                       /* default expression: */ p00_x,
                       (double*, p00_x+0),
                       (float[7], p00_x+1),
                       (int*, p00_a));
  }
}

#else

/**
 ** @addtogroup generic Generic type expressions
 **
 ** C11 provides a new feature to write template-like expressions with
 ** the macro preprocessor, @c _Generic. Here we provide some tools
 ** that emulate this feature by means of gcc specific extensions.
 **
 ** @c _Generic is one single construct which could be seen as an
 ** analogue to a @c switch statement, only that the different choices
 ** are made with matching types and not values. A typical example is
 **
 ** @code
 ** #define sin(X) _Generic((X), default: sin, float: sinf, long double: sinld)(X)
 ** @endcode
 **
 ** In contrast to that single construct, in C++ there are a several
 ** of constructs that would be needed to implement similar
 ** functionalities: function overloading, templates, constexpr.
 **
 ** Type generic expressions have an important new feature that was
 ** difficult to implement before C11:
 **
 **  - the @b type of the result of such an expression depends on the
 **    type or value of the "choice" expression.
 **
 ** C++ has a construct that decides on the type of an expression, but
 ** which is less powerful: function overloading. The actual function
 ** that is called at any point depends on the types of its
 ** arguments. E.g in
 **
 ** @code
 ** b = abs(a);
 ** @endcode
 **
 ** the return type of the function call would depend on the type of
 ** @c a, for that simple example it should be the same type as @c a.
 **
 ** Such simple type generic functions can be implemented through
 ** macros in C11 without problems. They have the advantage that the
 ** result must not necessarily be a function call but can be any type
 ** of expression, in particular constants. This can be convenient in
 ** a context for which optimization is crucial, either for CPU
 ** efficiency or size of the code. To enforce similar optimizations
 ** as with C11 @c _Generic, you'd have to use the new @c constexpr
 ** feature in C++ in the declaration of the functions that is used.
 **
 ** But @c _Generic is more powerful than that. It also can take such
 ** "code" branches according to a value, examples:
 **
 ** @code
 ** #define TOTO_APPROX(X) P99_TYPED_TERN(sizeof(toto) > 4, toto_ld(X), toto_d(X))
 ** @endcode
 **
 ** Using @c _Generic underneath ::P99_TYPED_TERN, this defines a
 ** function-like macro @c TOTO_APPROX that chooses between to
 ** functions according to the size of a type @c toto. The result type
 ** is the type of any of the branches that is chosen. The two types
 ** need not be compatible.
 **
 ** The choice expression (@c sizeof ...) is not known during
 ** preprocessing phases, so an <code>#if/#else</code> preprocessor
 ** conditional could not be used for the same purpose.On the other
 ** hand a conventional ternary expression
 **
 ** @code
 ** #define TOTO_APPROX0(X) (sizeof(toto) > 4 ? toto_ld(X) : toto_d(X))
 ** @endcode
 **
 ** would impose that the return types of the two functions would have
 ** to be compatible (both arithmetic types or both pointer types,
 ** e.g). If both were arithmetic types the result of the whole would
 ** be the wider of the two types. If e.g @c toto_ld would return
 ** <code>long double</code> and @c toto_d only @c double, in any case
 ** the result of the whole would still be <code>long double</code>,
 **
 ** In C++, one would need a template class that would be parametrized
 ** with a @c bool to obtain the same effect.
 **
 ** < should I leave this in? sounds a bit complicated >
 **
 ** - if @c FLT_EVAL_METHOD is 2 (all floating point operations are
 **   performed in <code>long double<code>) cast the expression down
 **   to @c double
 **
 ** @code
 ** #define FLOATING_EVAL(X) P99_GENERIC_SIZE(10+FLT_EVAL_METHOD, (X), (12, (double)(X)))
 **
 ** printf("toto is %f\n", FLOATING_EVAL(x * y))
 ** @endcode
 **
 ** This would ensure that the @c printf call would never see a
 ** <code>long double<code>, even if the arguments are only @c float
 ** or @c double.
 **
 ** @see P99_GENERIC
 **
 ** @{
 **/

/**
 ** @brief Type generic expression in anticipation of C11 @c _Generic
 **
 ** This macro expects a syntax that is similar to that of C11's @c
 ** _Generic keyword. The syntax that we support is as follows
 **
 ** @code
 ** P99_GENERIC(a,
 **             , // empty default expression
 **             (int*, a),
 **             (double*, x));
 ** @endcode
 **
 ** That is an expression @a EXP, followed by a default value @a DEF,
 ** followed by a list of type value pairs. So here this is an
 ** expression that depending on the type of @c a will have a type of
 ** @c int* or @c double* that will be set to @c a or @c x,
 ** respectively.
 **
 ** In C11 syntax, the above would be coded with some kind of "label"
 ** syntax:
 **
 ** @code
 ** _Generic(a,
 **          int*: a,
 **          double*: x);
 ** @endcode
 **
 ** As you can see above, the default value can be omitted. If omitted, it
 ** is replaced with some appropriate expression that should usually
 ** give you a syntax error.
 **
 ** If there is a default expression, it is used when none of
 ** the types matches:
 **
 ** @code
 ** a = P99_GENERIC(a + b,
 **                 max_uintmax,
 **                 (int, max_int),
 **                 (long, max_long),
 **                 (long long, max_llong),
 **                 (float, max_float),
 **                 (double, max_double))(a, b);
 ** @endcode
 **
 ** In C11 syntax
 ** @code
 ** a = _Generic(a + b,
 **              default: max_uintmax,
 **              int: max_int,
 **              long: max_long,
 **              long long: max_llong,
 **              float: max_float,
 **              double: max_double)(a, b);
 ** @endcode
 **
 ** Here all of the expressions evaluate to a function specifier. If
 ** <code>a + b</code> is @c int, ... or @c double the
 ** appropriate maximum function is choosen for that type. If none of
 ** these matches, the one for @c uintmax_t is choosen. The
 ** corresponding function is then evaluated with @c a and @c b as
 ** arguments.
 **
 ** - because the choice expression is <code>a + b</code> its type is
 **   the promoted common type of @c a and @c b. E.g for all types
 **   that are narrower than @c int, e.g @c short, normally @c int
 **   will be the type of the expression and @c max_int will be the
 **   function. If @c a is @c unsigned and @c b is @c
 **   double the result is also @c double.
 **
 ** - the return type of the @c _Generic expression is a
 **   function to two arguments. If it is @c int, e.g, the
 **   type is <code>int ()(int, int)</code>. So the return type
 **   of the function call would be @c int in that case.
 **
 ** - the arguments are promoted and converted to the expected type of
 **   the choosen function
 **
 ** @remark If the compiler is C11 compliant, the ::P99_GENERIC
 ** expression will just be translated to the corresponding @c
 ** _Generic expression.
 **
 ** @remark Otherwise only gcc and compatible compilers are supported.
 **/
#define P99_GENERIC(...)

/**
 ** @brief For each generic choice return a compound literal of the chosen type
 **
 ** The resulting literal is default initialized with @c 0.
 **
 ** This is similar to ::P99_GENERIC except that the second entry in
 ** each pair should be a type.
 **
 ** @code
 ** P99_GENERIC_LIT(a + b,
 **                 uintmax_t,
 **                 (int, unsigned),
 **                 (long, unsigned long),
 **                 (float, double),
 **                 (double, double));
 ** @endcode
 **
 ** @see P99_GENERIC
 **/
#define P99_GENERIC_LIT(...)

/**
 ** @brief Similar to ::P99_GENERIC but the choice is not
 ** according to the type of the expression @a UI but to its unsigned
 ** value.
 **
 ** @param UI must be a compile time integer expression that is cast
 ** to @c size_t and that must not be of value @c 0.
 **
 ** @remark @a UI is only evaluated at compile time
 **
 ** @code
 ** a = P99_GENERIC_SIZE(sizeof(a),
 **                      func_fallback,
 **                      (1, func1),
 **                      (2, func2),
 **                      (4, func4),
 **                      (8, func8))
 **                ((void*)&a);
 ** @endcode
 **
 ** In this example one of the functions @c func1, ..., @c func8 is
 ** chosen according to the size of @c a. This function is then called
 ** with the address of @c a. In case the size of @c a is not
 ** appropriate, a function @c func_fallback is used.
 **
 ** @warning The range of allowed values for @a UI is platform
 ** dependent. The only known fixed guarantee is @c UINT16_MAX, but
 ** the result of a @c sizeof operator should always work.
 **
 ** @see P99_GENERIC
 **/
#define P99_GENERIC_SIZE(UI, ...)

/**
 ** @brief Similar to ::P99_GENERIC_SIZE but returns a compound
 ** literal of the chosen type
 **
 ** @see P99_GENERIC_SIZE
 ** @see P99_GENERIC_LIT
 ** @see P99_GENERIC
 **/
#define P99_GENERIC_SIZE_LIT(UI, ...)

/**
 ** @brief A compile time ternary operator that is analogous to
 ** <code>COND ? YES : NO</code> that keeps the type of the chosen
 ** expression.
 **
 ** When there is full @c _Generic support this is implemented using
 ** that feature. If not, the fallback from gcc for that purpose is
 ** used.
 **/
#define P99_TYPED_TERN(COND, YES, NO)

/**
 ** @addtogroup C11_types Generic identification of families of types or values
 **
 ** @{
 **/

#define P00_TYPE_CHOICE(YES, T, I) (T, YES)

/**
 ** @brief Classify expression @a EXP according to its type and return
 ** @a YES if the type is in the list and @a NO, otherwise.
 **
 ** @a EXP is evaluated only at compile time for its type. @a YES and @a
 ** NO are evaluated at most once.
 **/
#define P99_TYPE_CHOICE(EXP, YES, NO, ...)

/**
 ** @addtogroup type_generic Generic macros that classify expressions
 **
 ** @{
 **/

#define P99_TYPE_UNSIGNED(EXP)      P99_TYPE_CHOICE((EXP), 1, 0, P99_STD_UNSIGNED_TYPES)
#define P99_TYPE_SIGNED(EXP)        P99_TYPE_CHOICE((EXP), 1, 0, P99_STD_SIGNED_TYPES)
#define P99_TYPE_REAL_FLOATING(EXP) P99_TYPE_CHOICE((EXP), 1, 0, P99_STD_REAL_FLOATING_TYPES)
#define P99_TYPE_COMPLEX(EXP)       P99_TYPE_CHOICE((EXP), 1, 0, P99_STD_COMPLEX_TYPES)
#define P99_TYPE_FLOATING(EXP)      P99_TYPE_CHOICE((EXP), 1, 0, P99_STD_FLOATING_TYPES)
#define P99_TYPE_BASIC(EXP)         P99_TYPE_CHOICE((EXP), 1, 0, P99_STD_BASIC_TYPES)
#define P99_TYPE_CHARACTER(EXP)     P99_TYPE_CHOICE((EXP), 1, 0, P99_STD_CHARACTER_TYPES)
#define P99_TYPE_INTEGER(EXP)       P99_TYPE_CHOICE((EXP), 1, 0, P99_STD_INTEGER_TYPES)
#define P99_TYPE_REAL(EXP)          P99_TYPE_CHOICE((EXP), 1, 0, P99_STD_REAL_TYPES)
#define P99_TYPE_ARITHMETIC(EXP)    P99_TYPE_CHOICE((EXP), 1, 0, P99_STD_ARITHMETIC_TYPES)

/**
 ** @}
 **/

/**
 ** @brief Classify expression @a UI according to its value and
 ** return @a YES if the value is in the list and @a NO, otherwise.
 **
 ** @a UI is evaluated only at compile time and the resulting value is cast
 ** to @c size_t. It must not be @c 0.
 **
 ** @a YES and @a NO are evaluated at most once.
 **
 ** @warning The range of allowed values for @a UI is platform
 ** dependent. The only known fixed guarantee is @c UINT16_MAX, but
 ** the result of a @c sizeof operator should always work.
 **/
#define P99_SIZE_CHOICE(UI, YES, NO, ...)

/**
 ** @brief Classify expression @a UI according to its value and
 ** return @c 1 if the value is in the list and @c 0, otherwise.
 **
 ** @a UI is evaluated only at compile time and the resulting value is cast
 ** to @c size_t. It must not be @c 0.
 **
 ** @code
 ** if (P99_SIZE_INDICATOR(sizeof(toto), 1, 2, 4, 8)) {
 **   .. do something easy ..
 ** } else {
 **   .. have some fallback for weirdos ...
 ** }
 ** @endcode
 **
 ** @warning The range of allowed values for @a UI is platform
 ** dependent. The only known fixed guarantee is @c UINT16_MAX, but
 ** the result of a @c sizeof operator should always work.
 **/
#define P99_SIZE_INDICATOR(UI, ...)

/**
 ** @brief Declare an inline function of basename @a BASE for
 ** expression @a EXP, applied to the builtin type @a EXT.
 **
 ** The motivation for declaring such functions is for expressions that
 ** evaluate their arguments multiple times.
 **
 ** The argument list contains the names of the function parameters as they
 ** should appear inside @a EXP. The name of the declared function has
 ** @a EXT appended to @a BASE. E.g for a function operating on two @c
 ** unsigned values:
 **
 ** @code
 ** P99_DECLARE_INLINE_EXPRESSION(u, my_max, ((a >= b) ? a : b), a, b);
 ** @endcode
 **
 ** This declares an @c inline function with the following prototype:
 **
 ** @code
 ** unsigned p00_gen_my_maxu(unsigned, unsigned);
 ** @endcode
 **
 ** @remark For the moment, the number of arguments that can appear in
 ** the expression is limited to 6, but this could be augmented easily
 ** if there is need for it.
 **
 ** @see P99_BUILTIN_TYPE for the shorthands that can be used for the
 ** types
 **
 ** @see P99_DECLARE_INLINE_EXPRESSIONS to create this type of
 ** functions %for a whole list of %types
 **/
#define P99_DECLARE_INLINE_EXPRESSION(EXT, BASE, EXP, ...)

/**

 ** @brief Declare a whole bunch of @c inline functions of basename @c
 ** BASE for expression @c EXP, applied to the builtin types as given
 ** in the argument list.
 **
 ** The motivation for declaring such functions is for expressions that
 ** evaluate their arguments multiple times. You can use these
 ** functions in a generic expression such as ::P99_GEN_EXPR.
 **
 ** @a NEPL represents the argument list that is passed to
 ** ::P99_DECLARE_INLINE_EXPRESSION for defining the individual
 ** functions.
 **
 ** @code
 ** P99_DECLARE_INLINE_EXPRESSIONS((my_max, ((a >= b) ? a : b), a, b),
 **                                u, ul, i, c, uhh);
 ** @endcode
 **
 ** This declares @c inline functions with the following prototypes:
 **
 ** @code
 ** unsigned p00_gen_my_maxu(unsigned, unsigned);
 ** unsigned long p00_gen_my_maxul(unsigned long, unsigned long);
 ** signed p00_gen_my_maxi(signed, signed);
 ** char p00_gen_my_maxc(char, char);
 ** unsigned char p00_gen_my_maxuhh(unsigned char, unsigned char);
 ** @endcode
 **
 ** @see P99_BUILTIN_TYPE
 ** @see P99_GENERIC
 ** @see P99_GEN_EXPR
 ** @see P99_DECLARE_INLINE_EXPRESSION
 **/
#define P99_DECLARE_INLINE_EXPRESSIONS(NEPL, ...)

extern void p00_invalid_function(void*, ...);

/**
 ** @brief Produce a type generic expression that can be used as if it
 ** were an @c inline function.
 **
 ** The motivation for declaring a macro that uses this is for
 ** expressions that evaluate their arguments multiple times.
 **
 ** E.g to define a macro ::P99_GEN_MAX you can use the following
 **
 ** @code
 ** P99_DECLARE_INLINE_EXPRESSIONS((maximum,
 **                                 (p00_a >= p00_b) ? p00_a : p00_b,
 **                                 p00_a, p00_b),
 **                                b, c, hh, uhh, h, uh, i, u, l, ul, ll, ull,
 **                                d, f, ld
 **                                );
 **
 ** #define P99_GEN_MAX(A, B)                                  \
 ** P99_GEN_EXPR(maximum, ((A) >= (B)) ? (A) : (B),            \
 **              b, c, hh, uhh, h, uh, i, u, l, ul, ll, ull,   \
 **              d, f, ld                                      \
 **              )                                             \
 ** ((A), (B))
 ** @endcode
 **
 ** This first defines 15 inline functions for the different
 ** arithmetic types, you could also just use
 ** ::P99_STD_ARITHMETIC_EXTS to produce that long list. Then the
 ** definition of the macro expands to a type generic expression that
 ** has as @a EXPR as its selection expression (here <code>(A) >= (B)) ?
 ** (A) : (B)</code>).
 **
 ** @remark the sole effect of using exactly the target expression for @a EXPR
 ** is that the type of the selection expression undergoes
 ** exactly the promotion or conversion rules that would be applied to
 ** @a EXPR if it were to be evaluated directly.
 **
 ** So, staying with the example above, we would have
 **
 ** @code
 ** int f(toto t);
 ** double d;
 **
 ** double dd = P99_GEN_MAX(f(t), d);
 ** @endcode
 **
 ** the commonly used type of @c f and @c d for the evaluation of
 ** <code>P99_GEN_MAX(f(t), d)</code> would be @c double. Before
 ** computing the maximum value, the result of @c f(t) is converted to
 ** @c double and then the result of the operation is also @c double.
 **
 ** As you can already see from this simple example, for such an
 ** expression it is crucial that @c f(t) is only evaluated once,
 ** which is the principal goal of ::P99_GEN_EXPR.
 **
 ** Here is another example that shows how simple it is to produce the
 ** type generic math macros that should normally be provided by
 ** "tgmath.h".
 **
 ** @code
 ** #define p00_gen_sind sin
 ** #define p00_gen_sinf sinf
 ** #define p00_gen_sinld sinl
 ** #define p00_gen_sindc csin
 ** #define p00_gen_sinfc csinf
 ** #define p00_gen_sinldc csinl
 **
 ** #define P99_GEN_SIN(A) P99_GEN_EXPR(sin, (A), P99_STD_FLOATING_EXTS)(A)
 ** @endcode
 **/
#define P99_GEN_EXPR(BASE, EXPR, ...)

#define P99_GEN_MAX(A, B)                                      \
P99_GEN_EXPR(maximum, ((A) >= (B)) ? (A) : (B),                \
             P99_STD_REAL_EXTS                                 \
             )                                                 \
((A), (B))

#define P99_GEN_MIN(A, B)                                      \
P99_GEN_EXPR(minimum, ((A) <= (B)) ? (A) : (B),                \
             P99_STD_REAL_EXTS                                 \
             )                                                 \
((A), (B))


#define P99_GEN_ABS(A) P99_GEN_EXPR(abs, ((A) >= 0) ? (A) : -(A), P99_STD_REAL_EXTS)(A)

/**
 ** @brief Type generic macro to compute the sine of @a A.
 **
 ** This is just a little example showing how simply the type generic macros
 ** of "tgmath.h" can be implemented.
 **/
#define P99_GEN_SIN(A) P99_GEN_EXPR(sin, (A), P99_STD_FLOATING_EXTS)(A)

#endif

/**
 ** @}
 **/


/**
 ** @addtogroup qualifiers determine type related properties
 **
 ** @{
 **/


#define P00_OVALUES_(X, T, I) (T*, X[0])
#define P00_OVALUES(X, ...) P99_FOR(X, P99_NARG(__VA_ARGS__), P00_SEQ, P00_OVALUES_, __VA_ARGS__)
#define P00_OVALUE_(X, DEF, ...) P99_GENERIC(X, DEF, __VA_ARGS__)

#define P00_OVALUES1_(X, T, I) (T*, X)
#define P00_OVALUES1(X, ...) P99_FOR(X, P99_NARG(__VA_ARGS__), P00_SEQ, P00_OVALUES1_, __VA_ARGS__)
#define P00_OVALUE1_(X, ...) P99_GENERIC(&(X[0]), , P00_OVALUES1(X, __VA_ARGS__))

#define P00_AVALUES_(X, T, I) (T*, *(T(*)[1])X)
#define P00_AVALUES(X, ...) P99_FOR(X, P99_NARG(__VA_ARGS__), P00_SEQ, P00_AVALUES_, __VA_ARGS__)
#define P00_AVALUE_(X, DEF, ...) P99_GENERIC(X, DEF, __VA_ARGS__)


#ifdef P00_DOXYGEN
/**
 ** @brief For a pointer or array expression @a X return the
 ** underlying object.
 **
 ** @pre This requires that @a X is either a pointer or array, or in
 ** other words that <code>(X)[0]</code> is a valid expression.
 **
 ** @pre This requires that the base type of @a X is one of the types
 ** listed in the arguments.
 **
 ** @return If @a X is a pointer to of one of the types listed in the
 ** argument list, <code>X[0]</code> is returned, that is it
 ** is assumed that the pointer points to one element of the
 ** underlying base type. Otherwise @a X is an lvalue of array type
 ** and this object is returned.
 **/
P00_DOCUMENT_PERMITTED_ARGUMENT(P99_OVALUE, 0)
P00_DOCUMENT_TYPE_ARGUMENT(P99_OVALUE, 1)
P00_DOCUMENT_TYPE_ARGUMENT(P99_OVALUE, 2)
P00_DOCUMENT_TYPE_ARGUMENT(P99_OVALUE, 3)
#define P99_OVALUE(X, ...)

/**
 ** @brief For a pointer or array expression @a X return the
 ** underlying array.
 **
 ** @pre This requires that @a X is either a pointer or array, or in
 ** other words that <code>(X)[0]</code> is a valid expression.
 **
 ** @pre This requires that the base type of @a X is one of the types
 ** listed in the arguments.
 **
 ** @return If @a X is a pointer to of one of the types listed in the
 ** argument list, @c X[0] is reinterpreted as a one element array and
 ** that array is returned. Otherwise @a X is an lvalue of array type
 ** and this object is returned.
 **/
P00_DOCUMENT_PERMITTED_ARGUMENT(P99_AVALUE, 0)
P00_DOCUMENT_TYPE_ARGUMENT(P99_AVALUE, 1)
P00_DOCUMENT_TYPE_ARGUMENT(P99_AVALUE, 2)
P00_DOCUMENT_TYPE_ARGUMENT(P99_AVALUE, 3)
#define P99_AVALUE(X, ...)

/**
 ** @brief For a pointer or array expression @a X return the size of
 ** the underlying object.
 **
 ** @pre This requires that @a X is either a pointer or array, or in
 ** other words that <code>(X)[0]</code> is a valid expression.
 **
 ** @pre This requires that the base type of @a X is one of the types
 ** listed in the arguments.
 **
 ** @return If @a X is a pointer to of one of the types listed in the
 ** argument list, <code>sizeof (X)[0]</code> is returned, that is it
 ** is assumed that the pointer points to one element of the
 ** underlying base type. Otherwise @a X is an lvalue of array type
 ** and this corresponds to the total size of the array object.
 **/
P00_DOCUMENT_PERMITTED_ARGUMENT(P99_OBJSIZE, 0)
P00_DOCUMENT_TYPE_ARGUMENT(P99_OBJSIZE, 1)
P00_DOCUMENT_TYPE_ARGUMENT(P99_OBJSIZE, 2)
P00_DOCUMENT_TYPE_ARGUMENT(P99_OBJSIZE, 3)
#define P99_OBJSIZE(X, ...)

/**
 ** @brief For a pointer or array expression @a X return the length of
 ** the underlying array object.
 **
 ** @pre This requires that @a X is either a pointer or array, or in
 ** other words that <code>(X)[0]</code> is a valid expression.
 **
 ** @pre This requires that the base type of @a X is one of the types
 ** listed in the arguments.
 **
 ** @return If @a X is a pointer to of one of the types listed in the
 ** argument list, <code>1</code> is returned, that is it is assumed
 ** that the pointer points to one element of the underlying base
 ** type. Otherwise @a X is an lvalue of array type and this
 ** corresponds to the total number of elements of the array object.
 **/
P00_DOCUMENT_PERMITTED_ARGUMENT(P99_OBJLEN, 0)
P00_DOCUMENT_TYPE_ARGUMENT(P99_OBJLEN, 1)
P00_DOCUMENT_TYPE_ARGUMENT(P99_OBJLEN, 2)
P00_DOCUMENT_TYPE_ARGUMENT(P99_OBJLEN, 3)
#define P99_OBJLEN(X, ...)
#else
P00_DOCUMENT_PERMITTED_ARGUMENT(P99_OVALUE, 0)
P00_DOCUMENT_TYPE_ARGUMENT(P99_OVALUE, 1)
P00_DOCUMENT_TYPE_ARGUMENT(P99_OVALUE, 2)
P00_DOCUMENT_TYPE_ARGUMENT(P99_OVALUE, 3)
#define P99_OVALUE(X, ...) P00_OVALUE_((X), P00_OVALUE1_((X), __VA_ARGS__), P00_OVALUES((X), __VA_ARGS__))

P00_DOCUMENT_PERMITTED_ARGUMENT(P99_AVALUE, 0)
P00_DOCUMENT_TYPE_ARGUMENT(P99_AVALUE, 1)
P00_DOCUMENT_TYPE_ARGUMENT(P99_AVALUE, 2)
P00_DOCUMENT_TYPE_ARGUMENT(P99_AVALUE, 3)
#define P99_AVALUE(X, ...) P00_AVALUE_((X), P00_OVALUE1_((X), __VA_ARGS__), P00_AVALUES((X), __VA_ARGS__))

P00_DOCUMENT_PERMITTED_ARGUMENT(P99_OBJSIZE, 0)
P00_DOCUMENT_TYPE_ARGUMENT(P99_OBJSIZE, 1)
P00_DOCUMENT_TYPE_ARGUMENT(P99_OBJSIZE, 2)
P00_DOCUMENT_TYPE_ARGUMENT(P99_OBJSIZE, 3)
#define P99_OBJSIZE(X, ...) (sizeof P99_OVALUE(X, __VA_ARGS__))

P00_DOCUMENT_PERMITTED_ARGUMENT(P99_OBJLEN, 0)
P00_DOCUMENT_TYPE_ARGUMENT(P99_OBJLEN, 1)
P00_DOCUMENT_TYPE_ARGUMENT(P99_OBJLEN, 2)
P00_DOCUMENT_TYPE_ARGUMENT(P99_OBJLEN, 3)
#define P99_OBJLEN(X, ...) (P99_OBJSIZE(X, __VA_ARGS__)/(sizeof (X)[0]))
#endif

/**
 ** @}
 **/


/**
 ** @addtogroup tgprint type generic printing
 **
 ** @see P99_GENERIC
 **
 ** @{
 **/

#define P00_SPRINT_DEFINE(T, ...)                                                             \
p99_inline                                                                                    \
char const* P99_PASTE2(p00_sprint_, T)(T p00_val, char*restrict p00_str, unsigned p00_form) { \
  enum { p00_len = P99_NARG(__VA_ARGS__), };                                                  \
  static char const*const p00_format[p00_len] = { __VA_ARGS__ };                              \
  char const*const p00_f = (p00_form < p00_len)                                               \
    ? p00_format[p00_form]                                                                    \
    : p00_format[0];                                                                          \
  sprintf(p00_str, p00_f, p00_val);                                                           \
  return p00_str;                                                                             \
}                                                                                             \
P99_MACRO_END(P00_SPRINT_DEFINE, T)

P00_SPRINT_DEFINE(char, "%c");
P00_SPRINT_DEFINE(schar, "%hhd");
P00_SPRINT_DEFINE(uchar, "%hhu", "%#hhX", "%#hho");
P00_SPRINT_DEFINE(short, "%hd");
P00_SPRINT_DEFINE(ushort, "%hu", "%#hX", "%#ho");
P00_SPRINT_DEFINE(int, "%d");
P00_SPRINT_DEFINE(unsigned, "%u", "%#X", "%#o");
P00_SPRINT_DEFINE(long, "%ld");
P00_SPRINT_DEFINE(ulong, "%lu", "%#lX", "%#lo");
P00_SPRINT_DEFINE(llong, "%lld");
P00_SPRINT_DEFINE(ullong, "%llu", "%#llX", "%#llo");
P00_SPRINT_DEFINE(float, "%g", "%a");
P00_SPRINT_DEFINE(double, "%g", "%a");
P00_SPRINT_DEFINE(ldouble, "%Lg", "%La");

P99_CONST_FUNCTION
p99_inline
char const* p00_sprint__Bool(_Bool p00_val, char*restrict p00_str, unsigned p00_form) {
  P99_UNUSED(p00_str);
  P99_UNUSED(p00_form);
  char const*const p00_format[] = {
    "false", "true",
    "0", "1",
    "f", "t",
  };
  register unsigned const p00_len = P99_ALEN(p00_format) / 2;
  if (p00_form >= p00_len) p00_form = 0;
  return p00_format[p00_form * 2 + p00_val];
}

P99_CONST_FUNCTION
p99_inline
char const volatile* p00_sprint_charp(char const volatile* p00_val, char*restrict p00_str, unsigned p00_form) {
  P99_UNUSED(p00_str);
  P99_UNUSED(p00_form);
  return p00_val;
}

p99_inline
char const* p00_sprint_voidp(void const volatile* p00_val, char*restrict p00_str, unsigned p00_form) {
  P99_UNUSED(p00_form);
  sprintf(p00_str, "%p", p00_val);
  return p00_str;
}

#ifndef __STDC_NO_COMPLEX__
p99_inline
char const* p00_sprint_cfloat(cfloat p00_val, char*restrict p00_str, unsigned p00_form) {
  char const*const p00_format[] = { "(%g, %g)", "(%a, %a)", };
  register unsigned const p00_len = P99_ALEN(p00_format);
  char const*const p00_f = (p00_form < p00_len)
                           ? p00_format[p00_form]
                           : p00_format[0];
  sprintf(p00_str, p00_f, creal(p00_val), cimag(p00_val));
  return p00_str;
}

p99_inline
char const* p00_sprint_cdouble(cdouble p00_val, char*restrict p00_str, unsigned p00_form) {
  char const*const p00_format[] = { "(%g, %g)", "(%a, %a)", };
  register unsigned const p00_len = P99_ALEN(p00_format);
  char const*const p00_f = (p00_form < p00_len)
                           ? p00_format[p00_form]
                           : p00_format[0];
  sprintf(p00_str, p00_f, creal(p00_val), cimag(p00_val));
  return p00_str;
}

p99_inline
char const* p00_sprint_cldouble(cldouble p00_val, char*restrict p00_str, unsigned p00_form) {
  char const*const p00_format[] = { "(%Lg, %Lg)", "(%La, %La)", };
  register unsigned const p00_len = P99_ALEN(p00_format);
  char const*const p00_f = (p00_form < p00_len)
                           ? p00_format[p00_form]
                           : p00_format[0];
  sprintf(p00_str, p00_f, creal(p00_val), cimag(p00_val));
  return p00_str;
}
#endif


#ifdef p99x_uintmax
#define UINT64_D19 UINT64_C(10000000000000000000)
p99_inline
void p00_sprint_p99x_uintmax_u_ite(p99x_uintmax p00_val, char*restrict p00_str) {
  uint64_t p00_ar[2*sizeof(p99x_uintmax)/sizeof(uint64_t)];
  size_t p00_pos = 0;
  for (; p00_val >= UINT64_D19; ++p00_pos) {
    /* These operations are expensive, so avoid them whenever we
       can. */
    p00_ar[p00_pos] = (uint64_t)(p00_val % UINT64_D19);
    p00_val /= UINT64_D19;
  }
  p00_str += sprintf(p00_str, "%" PRIu64, (uint64_t)p00_val);
  while (p00_pos) {
    --p00_pos;
    p00_str += sprintf(p00_str, "%019" PRIu64, p00_ar[p00_pos]);
  }
}
p99_inline
char* p00_sprint_p99x_uintmax_u(p99x_uintmax p00_val, char*restrict p00_str) {
  p00_sprint_p99x_uintmax_u_ite(p00_val, p00_str);
  return p00_str;
}
#define UINT64_O21 (~(UINT64_C(1)<<63))
p99_inline
void p00_sprint_p99x_uintmax_o_ite(p99x_uintmax p00_val, char*restrict p00_str) {
  uint64_t p00_ar[3*sizeof(p99x_uintmax)/sizeof(uint64_t)];
  size_t p00_pos = 0;
  for (;;) {
    /* Mask and shift in that case are less expensive. */
    p00_ar[p00_pos] = ((uint64_t)p00_val) & UINT64_O21;
    p00_val >>= 63;
    if (!p00_val) break;
    ++p00_pos;
  }
  p00_str += sprintf(p00_str, "%#" PRIo64, p00_ar[p00_pos]);
  while (p00_pos) {
    --p00_pos;
    p00_str += sprintf(p00_str, "%021" PRIo64, p00_ar[p00_pos]);
  }
}
p99_inline
char* p00_sprint_p99x_uintmax_o(p99x_uintmax p00_val, char*restrict p00_str) {
  p00_sprint_p99x_uintmax_o_ite(p00_val, p00_str);
  return p00_str;
}
p99_inline
void p00_sprint_p99x_uintmax_X_ite(p99x_uintmax p00_val, char*restrict p00_str) {
  uint64_t p00_ar[2*sizeof(p99x_uintmax)/sizeof(uint64_t)];
  size_t p00_pos = 0;
  for (;;) {
    /* Mask and shift in that case are less expensive. */
    p00_ar[p00_pos] = (uint64_t)p00_val;
    p00_val >>= 64;
    if (!p00_val) break;
    ++p00_pos;
  }
  p00_str += sprintf(p00_str, "%#" PRIX64, p00_ar[p00_pos]);
  while (p00_pos) {
    --p00_pos;
    p00_str += sprintf(p00_str, "%016" PRIX64, p00_ar[p00_pos]);
  }
}
p99_inline
char const* p00_sprint_p99x_uintmax_X(p99x_uintmax p00_val, char*restrict p00_str) {
  p00_sprint_p99x_uintmax_X_ite(p00_val, p00_str);
  return p00_str;
}

p99_inline
char const* p00_sprint_p99x_intmax(p99x_intmax p00_val, char*restrict p00_str, unsigned p00_form) {
  P99_UNUSED(p00_form);
  if (p00_val < 0) {
    p00_str[0] = '-';
    p00_sprint_p99x_uintmax_u(-p00_val, p00_str + 1);
  } else {
    p00_sprint_p99x_uintmax_u(p00_val, p00_str);
  }
  return p00_str;
}

p99_inline
char const* p00_sprint_p99x_uintmax(p99x_uintmax p00_val, char*restrict p00_str, unsigned p00_form) {
  switch (p00_form) {
  default: return p00_sprint_p99x_uintmax_u(p00_val, p00_str);
  case 1: return p00_sprint_p99x_uintmax_X(p00_val, p00_str);
  case 2: return p00_sprint_p99x_uintmax_o(p00_val, p00_str);
  }
}
#endif

#define P00_SPRINT(NAME, T, I) (T, P99_PASTE2(p00_sprint_, T))

#define P00_SPRINT_LIST_(...)                                        \
  P99_FOR(, P99_NARG(__VA_ARGS__), P00_SEQ, P00_SPRINT, __VA_ARGS__)

#define P00_SPRINT_LIST() P00_SPRINT_LIST_(P99_EXT_ARITHMETIC_TYPES)

#define P00_SPRINT_FORMAT_(X, A, ...)                                                  \
P99_GENERIC((X)+0,                                                                     \
            p00_sprint_voidp,                                                          \
            (char*, p00_sprint_charp),                                                 \
            (char const*, p00_sprint_charp),                                           \
            __VA_ARGS__)((X),                                                          \
                         P99_GENERIC((X)+0,                                            \
                                     /* be sure not to have an array for the sizeof */ \
                                     /* times a rough estimate for octal conversion */ \
                                     /* plus a rough offset for floating points */     \
                                     (char[(sizeof(X+0)*22+64)/8]){ 0 },               \
                                     (char*, 0),                                       \
                                     (char const*, 0)                                  \
                                     ),                                                \
                         (A))

#define P00_SPRINT_FORMAT(...) P00_SPRINT_FORMAT_(__VA_ARGS__)

/**
 ** @return a string with a printable representation of the first
 ** argument. This string is local to the function and should not be
 ** exported from there.
 **
 ** Only use this with the @c printf family of functions as follows:
 **
 ** @code
 ** printf("My values are %s and %s\n", P99_FORMAT(a), P99_FORMAT(b));
 ** @endcode
 **
 ** that is the only @c printf format you should use yourself is "%s"
 ** for the position and then ::P99_FORMAT is doing the rest, namely
 ** prints the argument according to its type.
 **
 ** @remark This supports all scalar types, including @c _Bool and the
 ** complex types (if there are any).
 **
 ** @remark For many of the types there are alternate output formats
 ** that can be chosen by adding a second parameter (default 0). The
 ** alternate formats are hexadecimal (for unsigned and floating
 ** types) and additionally octal representations (for unsigned
 ** types).
 **
 ** @pre This uses ::P99_GENERIC, so obviously it will only work if
 ** the rudimentary support for type generic macros is available.
 **/
P00_DOCUMENT_PERMITTED_ARGUMENT(P99_FORMAT, 0)
P00_DOCUMENT_PERMITTED_ARGUMENT(P99_FORMAT, 2)
#define P99_FORMAT(...)                                        \
P00_SPRINT_FORMAT                                              \
 (P99_IF_LT(P99_NARG(__VA_ARGS__), 2)                          \
  (__VA_ARGS__, 0)                                             \
  (__VA_ARGS__),                                               \
  P00_SPRINT_LIST())

P00_DOCUMENT_PERMITTED_ARGUMENT(P99_FORMATS, 0)
P00_DOCUMENT_PERMITTED_ARGUMENT(P99_FORMATS, 1)
P00_DOCUMENT_PERMITTED_ARGUMENT(P99_FORMATS, 2)
#define P99_FORMATS(...) P99_SEQ(P99_FORMAT, __VA_ARGS__)
#define P00_PRINTF(...) printf(__VA_ARGS__)

P00_DOCUMENT_PERMITTED_ARGUMENT(P99_PRINTF, 1)
P00_DOCUMENT_PERMITTED_ARGUMENT(P99_PRINTF, 2)
P00_DOCUMENT_PERMITTED_ARGUMENT(P99_PRINTF, 3)
#define P99_PRINTF(FORMAT, ...) printf(FORMAT, P99_FORMATS(__VA_ARGS__))

#define P00_FPRINTF(...) fprintf(__VA_ARGS__)
P00_DOCUMENT_PERMITTED_ARGUMENT(P99_FPRINTF, 2)
P00_DOCUMENT_PERMITTED_ARGUMENT(P99_FPRINTF, 3)
P00_DOCUMENT_PERMITTED_ARGUMENT(P99_FPRINTF, 4)
#define P99_FPRINTF(F, FORMAT, ...) fprintf(F, FORMAT, P99_FORMATS(__VA_ARGS__))

#define P00_SPRINTF(...) sprintf(__VA_ARGS__)
P00_DOCUMENT_PERMITTED_ARGUMENT(P99_SPRINTF, 2)
P00_DOCUMENT_PERMITTED_ARGUMENT(P99_SPRINTF, 3)
P00_DOCUMENT_PERMITTED_ARGUMENT(P99_SPRINTF, 4)
#define P99_SPRINTF(S, FORMAT, ...) sprintf(S, FORMAT, P99_FORMATS(__VA_ARGS__))

#define P00_SNPRINTF(...) snprintf(__VA_ARGS__)
P00_DOCUMENT_PERMITTED_ARGUMENT(P99_SNPRINTF, 3)
P00_DOCUMENT_PERMITTED_ARGUMENT(P99_SNPRINTF, 4)
P00_DOCUMENT_PERMITTED_ARGUMENT(P99_SNPRINTF, 5)
#define P99_SNPRINTF(S, N, FORMAT, ...) snprintf(S, N, FORMAT, P99_FORMATS(__VA_ARGS__))

/**
 ** @}
 **/

#define P00_DEFINE_IN_RANGE(T)                                   \
P99_CONST_FUNCTION                                               \
p99_inline                                                       \
bool P99_PASTE2(p00_in_range_, T)(T p00_r, T p00_s, T p00_len) { \
  return (p00_r >= p00_s) && ((p00_r - p00_s) < p00_len);        \
}

P99_CONST_FUNCTION
p99_inline
bool p00_in_range_voidp(void* p00_r_, void* p00_s_, size_t p00_len) {
  unsigned char* p00_r = p00_r_;
  unsigned char* p00_s = p00_s_;
  return (p00_r >= p00_s) && ((size_t)(p00_r - p00_s) < p00_len);
}

#ifndef P00_DOXYGEN
P99_SER(P00_DEFINE_IN_RANGE, P99_EXT_REAL_TYPES)
#endif

#define P00_IN_RANGE_PART(NAME, T, I) (T, P99_PASTE2(p00_in_range_, T))


#define P00_IN_RANGE_LIST_(...)                                             \
  P99_FOR(, P99_NARG(__VA_ARGS__), P00_SEQ, P00_IN_RANGE_PART, __VA_ARGS__)

#define P00_IN_RANGE_LIST() P00_IN_RANGE_LIST_(P99_EXT_REAL_TYPES)

#define P00_IN_RANGE(R, S, L, ...)                                           \
P99_GENERIC((1 ? (R) : (S)), p00_in_range_voidp, __VA_ARGS__)((R), (S), (L))

/**
 ** @brief check if @a R is in the range [@a S, @a S + @a L)
 **
 ** This is a type generic function that should work with all real
 ** types and pointer types, though you may encounter some surprises
 ** with floating point types due to rounding errors.
 **
 ** @warning The length parameter @a L is to be taken in bytes and not
 ** in numbers of elements of the base type.
 **/
P00_DOCUMENT_PERMITTED_ARGUMENT(P99_IN_RANGE, 0)
P00_DOCUMENT_PERMITTED_ARGUMENT(P99_IN_RANGE, 1)
#define P99_IN_RANGE(R, S, L) P00_IN_RANGE((R), (S), (L), P00_IN_RANGE_LIST())

/**
 ** @addtogroup qualifiers
 **
 ** @{
 **/

#define P00_VOID_QUAL_(QUAL, ...) (void QUAL*, __VA_ARGS__)
#define P00_VOID_QUAL(LIST) P00_VOID_QUAL_ LIST

#define P00_VOIDIFY_LIST(...) P99_SEQ(P00_VOID_QUAL, __VA_ARGS__)

/**
 ** @brief Generic choice based on the qualification of the target of
 ** a pointer expression
 **
 ** This can be used to choose a different function to call if the
 ** target of a pointer expression is qualified or not. If we suppose
 ** that for a certain task we want to distinguish @c const or @c
 ** volatile qualified pointers and have already different functions
 ** @c myfunc_, @c myfunc_c, ... that handle these cases we can simply
 ** chose like this:
 **
 ** @code
 ** P99_GENERIC_PQUALIFIED((PEXP),
 **   (, myfunc_),
 **   (const, myfunc_c),
 **   (volatile, myfunc_v),
 **   (const volatile, myfunc_cv))
 ** (PEXP)
 ** @endcode
 **
 ** Or if we want the qualification of a return expression to match
 ** the qualification of the target of an input expression
 **
 ** @code
 ** P99_GENERIC_PQUALIFIED(toto,
 **   (, tutu),
 **   (const, (tutu_type const*)tutu),
 **   (volatile, (tutu_type volatile*)tutu),
 **   (const volatile, (tutu_type const volatile*)tutu)
 ** )
 ** @endcode
 **
 ** @see P99_GENERIC_PCONST
 ** @see P99_GENERIC_PVOLATILE
 ** @see P99_GENERIC_PCONSTVOLATILE
 ** @see P99_GENERIC_TQUALIFIED for a similar macro that works for
 **   type expressions instead of a pointer expression
 */
P00_DOCUMENT_PERMITTED_ARGUMENT(P99_GENERIC_PQUALIFIED, 0)
P00_DOCUMENT_PERMITTED_ARGUMENT(P99_GENERIC_PQUALIFIED, 1)
P00_DOCUMENT_PERMITTED_ARGUMENT(P99_GENERIC_PQUALIFIED, 2)
P00_DOCUMENT_PERMITTED_ARGUMENT(P99_GENERIC_PQUALIFIED, 3)
#define P99_GENERIC_PQUALIFIED(PEXP, ...)                               \
P99_GENERIC(                                                            \
            /* The second case is subtle. If we would chose (void*)0 */ \
            /* this would be a null pointer constant and the return  */ \
            /* type would be the type of PEXP. If it is another type */ \
            /* of void* expression the return is a qualified version */ \
            /* of void*.                                             */ \
(1 ? (PEXP) : (void*)1),,                                               \
  P00_VOIDIFY_LIST(__VA_ARGS__))

/**
 ** @brief Generic choice based on the qualification of the target of
 ** a pointer expression
 **
 ** This can be used to choose a different function to call if the
 ** target of a pointer expression is @c const qualified or not. If we
 ** suppose that for a certain task we want to distinguish @c const
 ** qualified pointers and have already two functions @c myfunc_ and
 ** @c myfunc_c that handle these two cases we can simply chose like
 ** this:
 **
 ** @code
 ** #define myfunc(PEXP) P99_GENERIC_PQUALIFIED((PEXP), myfunc_, myfunc_c)(PEXP)
 ** @endcode
 **
 ** @see P99_GENERIC_PQUALIFIED
 ** @see P99_GENERIC_PVOLATILE
 ** @see P99_GENERIC_PCONSTVOLATILE
 ** @see P99_GENERIC_TCONST for a similar macro that works for
 **   type expressions instead of a pointer expression
 */
P00_DOCUMENT_PERMITTED_ARGUMENT(P99_GENERIC_PCONST, 0)
#define P99_GENERIC_PCONST(PEXP, NCONST, CONST)                \
P99_GENERIC((1 ? (PEXP) : (void volatile*)1),,                 \
            P00_VOID_QUAL_(volatile, NCONST),                  \
            P00_VOID_QUAL_(volatile const, CONST)              \
            )

/**
 ** @brief Generic choice based on the qualification of the target of
 ** a pointer expression
 **
 ** Similar to ::P99_GENERIC_PCONST but ask for @c volatile
 ** qualification.
 **
 ** @see P99_GENERIC_PQUALIFIED
 ** @see P99_GENERIC_PCONST
 ** @see P99_GENERIC_PCONSTVOLATILE
 ** @see P99_GENERIC_TCONSTVOLATILE for a similar macro that works for
 **   type expressions instead of a pointer expression
 */
P00_DOCUMENT_PERMITTED_ARGUMENT(P99_GENERIC_PVOLATILE, 0)
#define P99_GENERIC_PVOLATILE(PEXP, NVOLATILE, VOLATILE)       \
P99_GENERIC((1 ? (PEXP) : (void const*)1),,                    \
            P00_VOID_QUAL_(const, NVOLATILE),                  \
            P00_VOID_QUAL_(const volatile, VOLATILE)           \
            )

/**
 ** @brief Generic choice based on the qualification of the target of
 ** a pointer expression
 **
 ** Similar to ::P99_GENERIC_PCONST but ask for @c const and @c volatile
 ** qualification.
 **
 ** @see P99_GENERIC_PQUALIFIED
 ** @see P99_GENERIC_PCONST
 ** @see P99_GENERIC_PVOLATILE
 ** @see P99_GENERIC_TVOLATILE for a similar macro that works for
 **   type expressions instead of a pointer expression
 */
P00_DOCUMENT_PERMITTED_ARGUMENT(P99_GENERIC_PCONSTVOLATILE, 0)
#define P99_GENERIC_PCONSTVOLATILE(PEXP, NON, FULL)            \
P99_GENERIC((1 ? (PEXP) : (void*)1),                           \
            NVOLATILE,                                         \
            P00_VOID_QUAL_(const volatile, VOLATILE)           \
            )


/**
 ** @brief Generic choice based on the qualification of a type
 ** expression
 **
 ** @see P99_GENERIC_PQUALIFIED
 **/
P00_DOCUMENT_TYPE_ARGUMENT(P99_GENERIC_TQUALIFIED, 0)
#define P99_GENERIC_TQUALIFIED(T, ...)                         \
P99_GENERIC_PQUALIFIED((&(T)P99_INIT), ...)

/**
 ** @brief Generic choice based on the qualification of a type
 ** expression
 **
 ** @see P99_GENERIC_PCONST
 **/
P00_DOCUMENT_TYPE_ARGUMENT(P99_GENERIC_TCONST, 0)
#define P99_GENERIC_TCONST(T, NCONST, CONST)                   \
P99_GENERIC_PCONST((&(T)P99_INIT), NCONST, CONST)

/**
 ** @brief Generic choice based on the qualification of a type
 ** expression
 **
 ** @see P99_GENERIC_PVOLATILE
 **/
P00_DOCUMENT_TYPE_ARGUMENT(P99_GENERIC_TVOLATILE, 0)
#define P99_GENERIC_TVOLATILE(T, NVOLATILE, VOLATILE)          \
P99_GENERIC_PVOLATILE((&(T)P99_INIT), NVOLATILE, VOLATILE)

/**
 ** @brief Generic choice based on the qualification of a type
 ** expression
 **
 ** @see P99_GENERIC_PCONSTVOLATILE
 **/
P00_DOCUMENT_TYPE_ARGUMENT(P99_GENERIC_TCONSTVOLATILE, 0)
#define P99_GENERIC_TCONSTVOLATILE(T, NON, FULL)               \
P99_GENERIC_PCONSTVOLATILE((&(T)P99_INIT), NON, FULL)


/**
 ** @}
 **/

/**
 ** @addtogroup constexpr Compile time constant expressions
 **
 ** @{
 **/

#define P00_GENERIC_VOIDPTR_OR_INTEGER(PEXP, TRUE, FALSE)      \
P99_GENERIC((1 ? (void*)0 : (PEXP)),                           \
            FALSE,                                             \
            (void*, TRUE)                                      \
            )

#define P00_IS_VOIDPTR_OR_INTEGER(PEXP) P00_GENERIC_VOIDPTR_OR_INTEGER(PEXP, true, false)

typedef struct p00_nullptr_test p00_nullptr_test;

#define P00_GENERIC_NULLPTR_CONSTANT(PEXP, TRUE, FALSE)        \
P99_GENERIC((1 ? (p00_nullptr_test*)0 : (PEXP)),               \
            FALSE,                                             \
            (p00_nullptr_test*, TRUE)                          \
            )

#define P00_IS_NULLPTR_CONSTANT(PEXP) P00_GENERIC_NULLPTR_CONSTANT(PEXP, true, false)

#define P99_GENERIC_NULLPTR_CONSTANT_(PEXP, TRUE, FALSE)       \
P00_GENERIC_NULLPTR_CONSTANT(PEXP,                             \
                             TRUE,                             \
                             FALSE)

#define P99_GENERIC_NULLPTR_CONSTANT(PEXP, TRUE, FALSE)                             \
P99_GENERIC_NULLPTR_CONSTANT_(P00_GENERIC_VOIDPTR_OR_INTEGER(PEXP, PEXP, (void*)1), \
                             TRUE,                                                  \
                             FALSE)


/**
 ** @brief Test if the expression @a PEXP is a null pointer constant
 ** in the sense of the C standard.
 **
 ** A null pointer constant is any compile time constant of integral
 ** type (that is of integer or enum type) eventually cast to @c
 ** void*.
 **
 ** @remark Passing other integral values than @c 0 should result in a
 ** compile time diagnostic about type mismatch.
 **
 ** @remark A compile time constant of value @c 0 that is of a
 ** qualified version of @c void, e.g <code>void const*</p> should
 ** result in the value false.
 **
 ** @remark A const qualified variable of value @c 0 that is of
 ** integral type or @c void* should also result in the value false.
 **
 ** @remark @a PEXP will only be evaluated for its type, not for its
 ** value.
 **
 ** @remark The evaluation of this macro by itself results in a
 ** compile time expression of value @c false or @c true.
 **
 ** @see P99_IS_NULLPTR
 ** @see P99_IS_INTEGRAL_CONSTANT
 **/
#define P99_IS_NULLPTR_CONSTANT(PEXP) P99_GENERIC_NULLPTR_CONSTANT((PEXP), true, false)

P00_DOCUMENT_PERMITTED_ARGUMENT(P99_GENERIC_INTEGRAL_CONSTANT, 0)
P00_DOCUMENT_PERMITTED_ARGUMENT(P99_GENERIC_INTEGRAL_CONSTANT, 2)
#define P99_GENERIC_INTEGRAL_CONSTANT(EXP, TRUE, FALSE)                                 \
P99_GENERIC((EXP),                                                                      \
            P99_GENERIC_NULLPTR_CONSTANT((void*)(ptrdiff_t)((EXP)-(EXP)), TRUE, FALSE), \
            /* avoid to test with arithmetic for void* expressions */                   \
            (void*, FALSE),                                                             \
            (void const*, FALSE),                                                       \
            (void volatile*, FALSE),                                                    \
            (void const volatile*, FALSE)                                               \
            )

/**
 ** @brief Test if the expression @a EXP is an integral constant
 ** in the sense of the C standard.
 **
 ** An integral constant is any compile time constant of integral type
 ** (that is of integer or enum type) that is the result of an
 ** expression containing only integer literals, integral enumeration
 ** constants and certain @c sizeof and @c _Alignof evaluations.
 **
 ** @warning Any expression of pointer type should result in @c false,
 ** even if the value of the pointer is a constant @c 0.
 **
 ** @warning A compile time constant of pointer value that is of an
 ** incomplete type (e.g a forward declared @c struct pointer) other
 ** than <code>void*</code> could result in a diagnostic or even
 ** error. This can be considered as restriction for this macro.
 **
 ** @remark A const qualified variable of value of integer type should
 ** result in @c false.
 **
 ** @remark A literal of type @c float or @c double even with value
 ** 0.0 should result in @c false. This will not change, even if such
 ** a literal is used to compute an integral value such as in
 ** <code>!!0.0</code>.
 **
 ** @remark @a EXP will only be evaluated for its type, not for its
 ** value.
 **
 ** @remark The evaluation of this macro by itself results in a
 ** compile time expression of value @c false or @c true.
 **
 ** @see P99_IS_NULLPTR_CONSTANT
 ** @see P99_IS_NULLPTR
 **/
P00_DOCUMENT_PERMITTED_ARGUMENT(P99_IS_INTEGRAL_CONSTANT, 0)
#define P99_IS_INTEGRAL_CONSTANT(EXP) P99_GENERIC_INTEGRAL_CONSTANT((EXP), true, false)

P00_DOCUMENT_PERMITTED_ARGUMENT(P99_GENERIC_NULLPTR, 0)
P00_DOCUMENT_PERMITTED_ARGUMENT(P99_GENERIC_NULLPTR, 1)
P00_DOCUMENT_PERMITTED_ARGUMENT(P99_GENERIC_NULLPTR, 2)
#define P99_GENERIC_NULLPTR(PEXP, TRUE, FALSE)                 \
(P99_GENERIC_NULLPTR_CONSTANT(PEXP, TRUE, FALSE)               \
 &&!P99_GENERIC_INTEGRAL_CONSTANT(PEXP, TRUE, FALSE))

/**
 ** @brief Test if the expression @a EXP is a null pointer in the
 ** sense of the C standard.
 **
 ** @warning Beware that there are "null pointer constants" that are
 ** of integral type and thus are not a null pointer in this sense. In
 ** fact, even @c NULL may have that property.
 **
 ** @see P99_IS_NULLPTR_CONSTANT
 ** @see P99_IS_INTEGRAL_CONSTANT
 **/
P00_DOCUMENT_PERMITTED_ARGUMENT(P99_IS_NULLPTR, 0)
#define P99_IS_NULLPTR(PEXP) P99_GENERIC_NULLPTR((PEXP), true, false)

/**
 ** @}
 **/

/**
 ** @}
 **/

#endif
