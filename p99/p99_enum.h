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
#ifndef     P99_ENUM_H_
# define    P99_ENUM_H_

#include "p99_for.h"

/**
 ** @addtogroup types Type facilities
 ** @{
 **/


#define P00_ENUM_CASE(X) case X: return P99_STRINGIFY(X)

#define P00_ENUM_PARSE(C)                                      \
if (!memcmp(P99_STRINGIFY(C), p00_s, p00_len)) {               \
  ++p00_c;                                                     \
  p00_ret = C;                                                 \
 }



#ifdef P00_DOXYGEN
/**
 ** @brief Declare a simple inline function to return strings
 ** containing the names of enumeration constants.
 **/
#define P99_DECLARE_ENUM_GETNAME(T, ...)                                  \
/*! @brief Get a string with the name of constant @a p00_x of type ::T */ \
inline char const* P99_PASTE2(T, _getname)(T p00_x)
/**
 ** @brief Declare a simple inline function to return the longest
 ** enumeration constants of type @a T found in a string.
 **/
#define P99_DECLARE_ENUM_PARSE(T, ...)                                              \
/*! @brief Parse a string @a p00_s for the longest matching constant of type ::T */ \
inline T P99_PASTE2(T, _parse)(char const* p00_s)
#else
P00_DOCUMENT_TYPE_ARGUMENT(P99_DECLARE_ENUM_GETNAME, 0)
P00_DOCUMENT_DECLARATION_ARGUMENT(P99_DECLARE_ENUM_GETNAME, 1)
P00_DOCUMENT_DECLARATION_ARGUMENT(P99_DECLARE_ENUM_GETNAME, 2)
P00_DOCUMENT_DECLARATION_ARGUMENT(P99_DECLARE_ENUM_GETNAME, 3)
#define P99_DECLARE_ENUM_GETNAME(T, ...)                       \
P99_CONST_FUNCTION                                             \
p99_inline                                                     \
char const* P99_PASTE2(T, _getname)(T p00_x) {                 \
  switch ((uintmax_t)p00_x) {                                  \
    P99_SEP(P00_ENUM_CASE, __VA_ARGS__);                       \
  default: return "((" #T ")unknown value)";                   \
  }                                                            \
}                                                              \
P99_MACRO_END(declare_enum_getname, T)

P00_DOCUMENT_TYPE_ARGUMENT(P99_DECLARE_ENUM_PARSE, 0)
P00_DOCUMENT_DECLARATION_ARGUMENT(P99_DECLARE_ENUM_PARSE, 1)
P00_DOCUMENT_DECLARATION_ARGUMENT(P99_DECLARE_ENUM_PARSE, 2)
P00_DOCUMENT_DECLARATION_ARGUMENT(P99_DECLARE_ENUM_PARSE, 3)
#define P99_DECLARE_ENUM_PARSE(T, ...)                         \
P99_PURE_FUNCTION                                              \
p99_inline                                                     \
T P99_PASTE2(T, _parse)(char const p00_s[]) {                  \
  T p00_ret = P99_PASTE2(T, _amount);                          \
  if (p00_s) {                                                 \
    size_t p00_c = 0;                                          \
    size_t const p00_len = strlen(p00_s);                      \
    P99_SEP(P00_ENUM_PARSE, __VA_ARGS__);                      \
    if (p00_c > 1) p00_ret = P99_PASTE2(T, _amount);           \
  }                                                            \
  return p00_ret;                                              \
}                                                              \
P99_MACRO_END(declare_enum_parse, T)
#endif

#ifdef DOXYGEN
/**
 ** @brief Declare a simple enumeration type.
 **
 ** This macro only works for enumeration types that have no
 ** assignments to the constants. To define an enumeration type @c
 ** color use the macro in something like
 ** @code
 ** P99_DECLARE_ENUM(color, red, green, blue);
 ** @endcode
 **
 ** As additional benefits you obtain:
 **
 ** - constants @c color_min and @c color_max that in the example
 **   here would correspond to @c red and @c blue, respectively
 ** - constant @c color_amount that in the example
 **   here would correspond to @c 3
 ** - a function @c color_getname that returns a string containing the
 **   name of its argument.
 ** - a function @c color_parse that returns the color with the longest prefix in a string.
 **
 ** To have this work, you have to put a line
 ** @code
 ** P99_DEFINE_ENUM(color);
 ** @endcode
 **
 ** in one of your object files.
 **
 ** Unfortunately you can't use doxygen like comments inside the
 ** argument list to document the enumeration constants. You have to
 ** document the constants separately. For the example above you would
 ** do
 ** @code
 **   /// @var color red
 **   /// the most reddish color of all colors
 ** @endcode
 ** Observe the bizarre naming convention, here. Although in C (and
 ** C++) `red' is declared in the same scope as `enum color' you have
 ** to prefix it with `color' such that the documentation ends up inside
 ** the one for `color'.
 **/
P00_DOCUMENT_IDENTIFIER_ARGUMENT(P99_DECLARE_ENUM, 0)
P00_DOCUMENT_DECLARATION_ARGUMENT(P99_DECLARE_ENUM, 1)
P00_DOCUMENT_DECLARATION_ARGUMENT(P99_DECLARE_ENUM, 2)
P00_DOCUMENT_DECLARATION_ARGUMENT(P99_DECLARE_ENUM, 3)
#define P99_DECLARE_ENUM(T, ...)                                              \
/*! \see T ## _getname for access to the names of the constants as strings */ \
enum T { __VA_ARGS__ ,                                                        \
               /*! upper bound of the @ref T constants */                     \
               P99_PASTE2(T, _amount),                                        \
               /*! the largest @ref T constant */                             \
               P99_PASTE2(T, _max) = ((size_t)(P99_PASTE2(T, _amount)) - 1u), \
               /*! the smallest @ref T constant */                            \
               P99_PASTE2(T, _min) = 0                                        \
};                                                                            \
/*! \brief Enumeration type @c enum T and @c typedef T. */                    \
/*! \see T ## _getname for access to the names of the constants as strings */ \
typedef enum T T;                                                             \
 P99_DECLARE_ENUM_GETNAME(T, __VA_ARGS__);                                    \
P99_DECLARE_ENUM_PARSE(T, __VA_ARGS__)
#else
P00_DOCUMENT_IDENTIFIER_ARGUMENT(P99_DECLARE_ENUM, 0)
P00_DOCUMENT_DECLARATION_ARGUMENT(P99_DECLARE_ENUM, 1)
P00_DOCUMENT_DECLARATION_ARGUMENT(P99_DECLARE_ENUM, 2)
P00_DOCUMENT_DECLARATION_ARGUMENT(P99_DECLARE_ENUM, 3)
#define P99_DECLARE_ENUM(T, ...)                                              \
typedef enum T { __VA_ARGS__ ,                                                \
               /*! upper bound of the @ref T constants */                     \
               P99_PASTE2(T, _amount),                                        \
               /*! the largest @ref T constant */                             \
               P99_PASTE2(T, _max) = ((size_t)(P99_PASTE2(T, _amount)) - 1u), \
               /*! the smallest @ref T constant */                            \
               P99_PASTE2(T, _min) = 0                                        \
} T;                                                                          \
P99_DECLARE_ENUM_GETNAME(T, __VA_ARGS__);                                     \
P99_DECLARE_ENUM_PARSE(T, __VA_ARGS__)
#endif

/**
 ** @brief Define the necessary symbols for a simple enumeration type.
 **
 ** @see P99_DECLARE_ENUM
 **/
P00_DOCUMENT_TYPE_ARGUMENT(P99_DEFINE_ENUM, 0)
#define P99_DEFINE_ENUM(T)                                     \
P99_INSTANTIATE(char const*, P99_PASTE2(T, _getname), T);      \
P99_INSTANTIATE(T, P99_PASTE2(T, _parse), char const*)

P99_CONST_FUNCTION
p99_inline
char const* bool_getname(bool p00_x) {
  switch ((uintmax_t)p00_x) {
  case 0: return "false";
  case 1: return "true";
  default: return "((bool)unknown value)";
  }
}


/**
 ** @brief check if the list of expressions is syntactically valid but
 ** don't evaluate it
 **
 ** This can be used to mark an identifier as unused to avoid bogus
 ** compiler warnings.
 ** @code
 ** bool myTruth(bool t) {
 **   P99_UNUSED(t);
 **   return true;
 ** }
 ** @endcode
 **
 ** @remark this must be in a place where the expression could
 ** successfully evaluate and where a declaration of any sort is
 ** suitable
 **
 ** @remark this is preferable over the trick <code>(void)EXPR;</code>
 ** since it guarantees that @a EXPR is never evaluated, even if it
 ** contains references to @c volatile objects, and since it can also
 ** be placed in file scope.
 **/
#define P99_UNUSED(...) P99_SEP(P00_UNUSED, __VA_ARGS__)

#define P00_CONSTANT_STATIC_3(T, NAME, ...)  static T const NAME = __VA_ARGS__; P99_UNUSED(NAME)
#define P00_CONSTANT_ENUM_1(NAME) enum { NAME }
#define P00_CONSTANT_ENUM_2(NAME, ...) enum { NAME = (__VA_ARGS__) }

#define P00_CONSTANT_2(T, NAME)                                \
P99_IF_INT(T)                                                  \
(P00_CONSTANT_ENUM_1(NAME))                                    \
(P00_CONSTANT_STATIC_3(T, NAME, P99_INIT))

#define P00_CONSTANT_3(T, NAME, ...)                           \
P99_IF_INT(T)                                                  \
 (P00_CONSTANT_ENUM_2(NAME, __VA_ARGS__))                      \
 (P00_CONSTANT_STATIC_3(T, NAME, __VA_ARGS__))

#ifdef P00_DOXYGEN
/**
 ** @brief define a compile time constant @a NAME of type @a T with
 ** value @a INIT
 **
 ** @a INIT can be omitted, resulting in a zero initialized constant.
 **
 ** @remark if @a T is one of the special values @c int or @c signed,
 ** enumeration constants are defined.
 **
 ** Use this as in the following:
 ** @code
 ** P99_CONSTANT(struct tutu, tutu0);
 ** inline
 ** struct tutu * tutu_init(struct tutu* x) {
 **   if (x) *x = tutu0;
 **   return x;
 ** }
 ** @endcode
 **
 ** Here @c tutu0 is defined a the zero initialized value of type
 ** <code>struct tutu</code>.
 **
 ** @remark This is thought to use the proposed extension of @c
 ** register variables in file scope but we are not yet there.
 **/
P00_DOCUMENT_IDENTIFIER_ARGUMENT(P99_CONSTANT, 1)
#define P99_CONSTANT(T, NAME, INIT) register T const NAME = INIT
#else
P00_DOCUMENT_IDENTIFIER_ARGUMENT(P99_CONSTANT, 1)
#define P99_CONSTANT(...)                                      \
P99_IF_LT(P99_NARG(__VA_ARGS__), 3)                            \
(P00_CONSTANT_2(__VA_ARGS__))                                  \
(P00_CONSTANT_3(__VA_ARGS__))
#endif

/**
 ** @}
 **/

/**
** @addtogroup endianess
** @{
**/

/**
 ** @brief Classify platforms according to their endianness
 ** @see P99_ENDIANNESS
 **/
typedef enum p99_endianness {
  p99_big_endian = 0x01020304u,
  p99_little_endian = 0x04030201u,
  p99_pdp_endian = 0x02010403u
} p99_endianness;

P99_DECLARE_ENUM_GETNAME(
  p99_endianness,
  p99_big_endian,
  p99_little_endian,
  p99_pdp_endian
);

/**
 ** @brief Return the platform endianness
 ** in terms of a value of type ::p99_endianness.
 **/
#define P99_ENDIANNESS ((p99_endianness)P99_HTON(4, UINT32_C(0x01020304)))

/** @}
 **/


#endif      /* !P99_ENUM_H_ */
