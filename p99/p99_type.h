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
/**
 ** @file p99_type.h
 */

#ifndef     P99_TYPE_H_
# define    P99_TYPE_H_

#include "p99_paste.h"


/* This is defined in some header file since C11. Since C11 allows to
   repeat typedefs as long as they resolve to the same type, this can
   be done at any place. */
/**
 ** @ingroup C11_library
 **/
typedef int errno_t;

/**
 ** @addtogroup types Type facilities
 ** @brief Macros that help in the handling of different kinds of types,
 ** forward declaring @c struct or @c union, and in handling @c enum.
 ** @{
 **/


/**
 ** @brief forward declaration of a @c struct @a NAME
 **
 ** This combines a @c struct forward declaration and a @c typedef
 ** that should allow you to use @c struct @a NAME and just @a NAME
 ** interchangeably.
 **
 ** This declaration should also be suitable for inclusion into a C++
 ** source.
 **/
P00_DOCUMENT_IDENTIFIER_ARGUMENT(P99_DECLARE_STRUCT, 0)
#define P99_DECLARE_STRUCT(NAME)                               \
typedef struct NAME NAME


/**
 ** @brief forward declaration of a @c union @a NAME
 **
 ** This combines a @c union forward declaration and a @c typedef
 ** that should allow you to use @c union @a NAME and just @a NAME
 ** interchangeably.
 **
 ** This declaration should also be suitable for inclusion into a C++
 ** source.
 **/
P00_DOCUMENT_IDENTIFIER_ARGUMENT(P99_DECLARE_UNION, 0)
#define P99_DECLARE_UNION(NAME)                                \
typedef union NAME NAME

/**
 ** @def P99_DEFINE_UNION
 ** @brief definition of a @c union @a NAME
 **
 ** The member declaration(s) should be given as the variable argument
 ** list.
 **
 ** The difference between this and a straightforward @c union declaration
 ** is that here we introduce a hidden first member that consists of a
 ** byte array with just the appropriate length to cover the whole
 ** union. The only purpose of this hidden member is to ensure that
 ** the default initializer <code>{ 0 }</code> initializes the whole
 ** @c union.
 **
 ** Otherwise in C99 padding bytes could be omitted from such an
 ** initialization, which can lead to surprising results. C1x
 ** explicitly states that padding bytes must be initialized to @c
 ** 0. So from then on we can use a straight @c union definition.
 **
 ** @warning Don't assume anything about the ordering of the members
 ** of this @c union. Use designated initializers such as <code>{
 ** .toto = { .a = 1, }, }</code>, instead.
 **/

#if  __STDC_VERSION__ < 201101L
P00_DOCUMENT_IDENTIFIER_ARGUMENT(P99_DEFINE_UNION, 0)
P00_DOCUMENT_DECLARATION_ARGUMENT(P99_DEFINE_UNION, 1)
P00_DOCUMENT_DECLARATION_ARGUMENT(P99_DEFINE_UNION, 2)
P00_DOCUMENT_DECLARATION_ARGUMENT(P99_DEFINE_UNION, 3)
#define P99_DEFINE_UNION(NAME, ...)                                                                                                                                                                                                                                                                           \
  /** \remark This union has a hidden first member that is just a byte array to ensure that the default initializer <code>{ 0 }</code> will zero out the whole structure. To initialize a particular member, you should always use a designated initializer such as <code>{ .toto = { .a = 1, }, }</code> **/ \
union NAME {                                                                                                                                                                                                                                                                                                  \
  uint8_t p00_allbytes[sizeof(union { __VA_ARGS__ })];                                                                                                                                                                                                                                                        \
  __VA_ARGS__                                                                                                                                                                                                                                                                                                 \
}
#else
P00_DOCUMENT_IDENTIFIER_ARGUMENT(P99_DEFINE_UNION, 0)
P00_DOCUMENT_DECLARATION_ARGUMENT(P99_DEFINE_UNION, 1)
P00_DOCUMENT_DECLARATION_ARGUMENT(P99_DEFINE_UNION, 2)
P00_DOCUMENT_DECLARATION_ARGUMENT(P99_DEFINE_UNION, 3)
#define P99_DEFINE_UNION(NAME, ...)                                                                                                                                                                                                                                                                           \
  /** \remark This union has a hidden first member that is just a byte array to ensure that the default initializer <code>{ 0 }</code> will zero out the whole structure. To initialize a particular member, you should always use a designated initializer such as <code>{ .toto = { .a = 1, }, }</code> **/ \
union NAME { __VA_ARGS__ }
#endif

/* For each one word integer type have a signed and unsigned variant. */
#define P00_ONE_TOK(T, NAME)                                                    \
/*! @brief a `one token' abreviation for <code>T</code> */                      \
/*! These type names are needed to have a valid naming scheme for functions. */ \
typedef T NAME

/**
 ** @brief Declare derived pointer types with endings "_ptr" and "_cptr"
 **/
P00_DOCUMENT_TYPE_IDENTIFIER_ARGUMENT(P99_POINTER_TYPE, 0)
#define P99_POINTER_TYPE(T)                                    \
/*! @brief a pointer to @c T */                                \
typedef T *P99_PASTE2(T, _ptr);                                \
/*! @brief a @c const pointer to @c T */                       \
typedef T const*P99_PASTE2(T, _cptr)

/**
 ** @brief Declare trivial init and destroy functions for type @a T.
 **/
P00_DOCUMENT_TYPE_IDENTIFIER_ARGUMENT(P99_PLAIN_TYPE, 0)
#define P99_PLAIN_TYPE(T)                                          \
/*! @brief initialize the object that @a p00_id points to by 0. */ \
p99_inline T* P99_PASTE2(T, _init)(T *p00_id) {                    \
  if (p00_id) *p00_id = 0;                                         \
  return p00_id;                                                   \
}                                                                  \
/*! @brief destroy the object that @a p00_id points to. */         \
P99_CONST_FUNCTION                                                 \
p99_inline void P99_PASTE2(T, _destroy)(T*  p00_id) {              \
  /* empty */                                                      \
  (void)p00_id;                                                    \
}                                                                  \
P99_MACRO_END(P99_PLAIN_TYPE, T)

/**
 ** @brief Declare trivial init and destroy functions for type @a T
 ** and its pointer derivatives.
 **/
P00_DOCUMENT_TYPE_IDENTIFIER_ARGUMENT(P99_DERIVED_TYPES, 0)
#define P99_DERIVED_TYPES(T)                                   \
P99_PLAIN_TYPE(T);                                             \
P99_PLAIN_TYPE(P99_PASTE2(T, _cptr));                          \
P99_PLAIN_TYPE(P99_PASTE2(T, _ptr))


/**
 ** @brief Encapsulate an object of type @a T in a new type called @a NAME
 **
 ** This hides type @a T inside the new structure type such that the
 ** original type is only accessible if asked accessed explicitly.
 **
 ** @see P99_ENC to access the hidden type of an object of type @a NAME
 ** @see P99_ENCP to access the hidden type of a pointer to object of type @a NAME
 ** @see P99_ENC_INIT to initialize a variable of type @a NAME
 **/
P00_DOCUMENT_TYPE_ARGUMENT(P99_ENC_DECLARE, 0)
P00_DOCUMENT_IDENTIFIER_ARGUMENT(P99_ENC_DECLARE, 1)
#define P99_ENC_DECLARE(T, NAME)                                                                                                 \
/** @remark encapsulates an object of type T @see P99_ENC for access through object @see P99_ENCP for access through pointer **/ \
struct NAME {                                                                                                                    \
  /** @private */                                                                                                                \
  T p00_val;                                                                                                                     \
};                                                                                                                               \
P99_DECLARE_STRUCT(NAME)

/**
 ** @brief Access an encapsulated object
 ** @see P99_ENC_DECLARE
 **/
#define P99_ENC(OBJ) ((OBJ).p00_val)

/**
 ** @brief Access an encapsulated object through a pointer
 ** @see P99_ENC_DECLARE
 **/
#define P99_ENCP(OBJP) ((OBJP)->p00_val)

/**
 ** @brief Initialize an encapsulated object
 **
 ** @param V must be an expression that is assignment compatible with
 ** the base type of the encapsulated object type
 **
 ** @see P99_ENC_DECLARE
 **/
#define P99_ENC_INIT(V) { .p00_val = (V), }

#if CHAR_MAX == UCHAR_MAX
# define P99_STD_UNSIGNED_TYPES                                \
 _Bool,                                                        \
 char,                                                         \
 uchar,                                                        \
 ushort,                                                       \
 unsigned,                                                     \
 ulong,                                                        \
 ullong
# define P99_STD_UNSIGNED_EXTS b, c, uhh, uh, u, ul, ull
# define P99_STD_SIGNED_TYPES                                  \
  schar,                                                       \
  short,                                                       \
  int,                                                         \
  long,                                                        \
  llong
# define P99_STD_SIGNED_EXTS hh, h, i, l, ll
# define P99_STD_REAL_FLOATING_TYPES                           \
 float,                                                        \
 double,                                                       \
 ldouble
#else
# define P99_STD_UNSIGNED_TYPES                                \
 _Bool,                                                        \
 uchar,                                                        \
 ushort,                                                       \
 unsigned,                                                     \
 ulong,                                                        \
 ullong
# define P99_STD_UNSIGNED_EXTS b, uhh, uh, u, ul, ull
# define P99_STD_SIGNED_TYPES                                  \
  char,                                                        \
  schar,                                                       \
  short,                                                       \
  int,                                                         \
  long,                                                        \
  llong
# define P99_STD_SIGNED_EXTS c, hh, h, i, l, ll
# define P99_STD_REAL_FLOATING_TYPES                           \
 float,                                                        \
 double,                                                       \
 ldouble
#endif

#define P99_STD_REAL_FLOATING_EXTS f, d, ld

#ifndef __STDC_NO_COMPLEX__
# define P99_STD_COMPLEX_TYPES                                 \
  cfloat,                                                      \
  cdouble,                                                     \
  cldouble
# define P99_STD_COMPLEX_EXTS fc, dc, ldc
# define P99_STD_FLOATING_TYPES P99_STD_REAL_FLOATING_TYPES, P99_STD_COMPLEX_TYPES
# define P99_STD_FLOATING_EXTS P99_STD_REAL_FLOATING_EXTS, P99_STD_COMPLEX_EXTS
#else
# define P99_STD_FLOATING_TYPES P99_STD_REAL_FLOATING_TYPES
# define P99_STD_FLOATING_EXTS P99_STD_REAL_FLOATING_EXTS
#endif

#define P99_STD_BASIC_TYPES                                    \
 P99_STD_INTEGER_TYPES,                                        \
 P99_STD_FLOATING_TYPES

#define P99_STD_BASIC_EXTS                                     \
 P99_STD_INTEGER_EXTS,                                         \
 P99_STD_FLOATING_EXTS

#define P99_STD_CHARACTER_TYPES                                \
  char,                                                        \
  schar,                                                       \
  uchar

#define P99_STD_CHARACTER_EXTS c, hh, uhh

#define P99_STD_INTEGER_TYPES                                  \
  P99_STD_SIGNED_TYPES,                                        \
  P99_STD_UNSIGNED_TYPES

#define P99_STD_INTEGER_EXTS                                   \
  P99_STD_SIGNED_EXTS,                                         \
  P99_STD_UNSIGNED_EXTS

#define P99_STD_REAL_TYPES                                     \
  P99_STD_INTEGER_TYPES,                                       \
  P99_STD_REAL_FLOATING_TYPES

#define P99_STD_REAL_EXTS                                      \
  P99_STD_INTEGER_EXTS,                                        \
  P99_STD_REAL_FLOATING_EXTS

#define P99_STD_ARITHMETIC_TYPES                               \
  P99_STD_INTEGER_TYPES,                                       \
  P99_STD_FLOATING_TYPES

#define P99_STD_ARITHMETIC_EXTS                                \
  P99_STD_INTEGER_EXTS,                                        \
  P99_STD_FLOATING_EXTS

#ifdef p99x_uint128
# define P99_EXT_INTEGER_TYPES p99x_uintmax, p99x_intmax
# define P99_EXT_ARITHMETIC_TYPES P99_STD_ARITHMETIC_TYPES, P99_EXT_INTEGER_TYPES
# define P99_EXT_REAL_TYPES P99_STD_REAL_TYPES, P99_EXT_INTEGER_TYPES
#else
# define P99_EXT_INTEGER_TYPES
# define P99_EXT_ARITHMETIC_TYPES P99_STD_ARITHMETIC_TYPES
# define P99_EXT_REAL_TYPES P99_STD_REAL_TYPES
#endif

/** @}
 **/

#endif      /* !P99_TYPE_H_ */
