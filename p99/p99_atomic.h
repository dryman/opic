/* This may look like nonsense, but it really is -*- mode: C -*-              */
/*                                                                            */
/* Except for parts copied from previous work and as explicitly stated below, */
/* the authors and copyright holders for this work are as follows:            */
/* (C) copyright  2011-2014 Jens Gustedt, INRIA, France                       */
/* (C) copyright  2012 William Morris                                         */
/*                                                                            */
/* This file is free software; it is part of the P99 project.                 */
/* You can redistribute it and/or modify it under the terms of the QPL as     */
/* given in the file LICENSE. It is distributed without any warranty;         */
/* without even the implied warranty of merchantability or fitness for a      */
/* particular purpose.                                                        */
/*                                                                            */
#ifndef P99_ATOMIC_H
#define P99_ATOMIC_H 1

#include "p99_enum.h"
#include "p99_generic.h"
#include P99_ADVANCE_ID

/**
 ** @addtogroup atomic C11 atomic operations
 **
 ** This is a stub implementation of C11 atomic types and operations.
 **
 ** This uses gcc extensions
 ** - all those that are needed for ::P99_GENERIC
 ** - @c __typeof__ to declare @c typedef or local variables of a specific type
 ** - block expressions with <code>({ ... })</code>
 **
 ** We also use @c __sync_lock_test_and_set and other similar built-ins
 ** if they are available. If not, @c __sync_lock_test_and_set and @c
 ** __sync_lock_release are implemented in assembler (for 4 byte
 ** integers) and all other operations are synthesized with an
 ** ::atomic_flag that is used as a spinlock.
 **
 ** @see _Atomic
 ** @see P99_DECLARE_ATOMIC
 **
 ** @{
 **/

#if p99_has_feature(stdatomic_h)
# include <stdatomic.h>
# include "p99_atomic_flag.h"

#define P00_DECLARE_ATOMIC2(T, ...) typedef _Atomic(T) __VA_ARGS__

#define P99_DECLARE_ATOMIC(...)                                                                                        \
/** @brief Atomic access to a value of type <code>T</code> @see atomic_int for the possible operations on this type */ \
P99_IF_EQ_1(P99_NARG(__VA_ARGS__))                                                                                     \
(P00_DECLARE_ATOMIC2(__VA_ARGS__, P99_PASTE2(atomic_, __VA_ARGS__)))                                                   \
(P00_DECLARE_ATOMIC2(__VA_ARGS__))

P99_DECLARE_ATOMIC(float);
P99_DECLARE_ATOMIC(double);

#else
/**
 ** @addtogroup atomic_stub Stub replacements of C11 atomic operations
 **
 ** This is a collection stub implementation of C11 atomic types and
 ** operations for the case that gcc doesn't implement them.
 **
 ** These use the @c __asm__ gcc extension.
 **
 ** The only operations that are implemented by these stubs are @c
 ** lock_test_and_set and @c lock_release operations. These are the
 ** minimal set of operations that are needed to comply with the
 ** standard.
 **
 ** @{
 **/

#ifdef P99_TEST_ATOMIC
# undef __GCC_HAVE_SYNC_COMPARE_AND_SWAP_1
# undef __GCC_HAVE_SYNC_COMPARE_AND_SWAP_2
# undef __GCC_HAVE_SYNC_COMPARE_AND_SWAP_4
# undef __GCC_HAVE_SYNC_COMPARE_AND_SWAP_8
#endif

/**
 ** @addtogroup atomic_enum
 ** @{
 **/

#if defined(P00_DOXYGEN) || !defined(__ATOMIC_RELAXED)
P99_DECLARE_ENUM(memory_order,
                 memory_order_relaxed,
                 memory_order_consume,
                 memory_order_acquire,
                 memory_order_release,
                 memory_order_acq_rel,
                 memory_order_seq_cst
                );
#else
enum memory_order {
  memory_order_relaxed = __ATOMIC_RELAXED,
  memory_order_consume = __ATOMIC_CONSUME,
  memory_order_acquire = __ATOMIC_ACQUIRE,
  memory_order_release = __ATOMIC_RELEASE,
  memory_order_acq_rel = __ATOMIC_ACQ_REL,
  memory_order_seq_cst = __ATOMIC_SEQ_CST,
};
typedef enum memory_order memory_order;
#endif

/**
 ** @}
 **/

#if defined(__GNUC__) && !defined(P00_ATOMIC_NO_GCC)
# include "p99_atomic_gcc.h"
#elif defined(__arm__)
# include "p99_atomic_arm.h"
#elif defined(__x86_64__) || defined(__i386__)
# include "p99_atomic_x86.h"
#else
# warning "no support for atomic operations detected for this platform"
# define P00_NO_ATOMICS
#endif

/**
 ** @}
 **/

#if !defined(P00_NO_ATOMICS) || defined(P00_DOXYGEN)

/**
 ** @addtogroup atomic_macros
 **
 ** Most of the macros defined here just serve the purpose of
 ** detecting the lock-free property for specific integer data
 ** types. Names are used as they are foreseen in the standard, e.g
 ** ::ATOMIC_INT_LOCK_FREE that handles the case for @c int and @c
 ** unsigned types.
 **
 ** This information can be provided externally. If it isn't, some
 ** heuristic is used to detect these features. Currently the only
 ** mechanism that is implemented is the one provided by gcc.
 **
 ** From this information a list of atomic integer types is constructed,
 ** ::P99_ATOMIC_LOCK_FREE_TYPES.  This list is used inside the macros for
 ** type generic programming.
 **
 ** The only type/function that is always necessary is ::atomic_flag
 ** that is used for all other atomic types.
 **
 ** @{
 **/


#ifndef ATOMIC_INT8_LOCK_FREE
#  if defined(__GCC_HAVE_SYNC_COMPARE_AND_SWAP_1)
#   define ATOMIC_INT8_LOCK_FREE 2
#  else
#   define ATOMIC_INT8_LOCK_FREE 0
#  endif
#endif
#if ATOMIC_INT8_LOCK_FREE == 2
# define P00_TYPE_LIST_ELEM1 , (1, uint8_t)
#else
# define P00_TYPE_LIST_ELEM1
#endif

#ifndef ATOMIC_INT16_LOCK_FREE
#  if defined(__GCC_HAVE_SYNC_COMPARE_AND_SWAP_2)
#   define ATOMIC_INT16_LOCK_FREE 2
#  else
#   define ATOMIC_INT16_LOCK_FREE 0
#  endif
#endif
#if ATOMIC_INT16_LOCK_FREE == 2
# define P00_TYPE_LIST_ELEM2 , (2, uint16_t)
#else
# define P00_TYPE_LIST_ELEM2
#endif

#ifndef ATOMIC_INT32_LOCK_FREE
#  if defined(__GCC_HAVE_SYNC_COMPARE_AND_SWAP_4)
#   define ATOMIC_INT32_LOCK_FREE 2
#  else
#   define ATOMIC_INT32_LOCK_FREE 0
#  endif
#endif
#if ATOMIC_INT32_LOCK_FREE == 2
# define P00_TYPE_LIST_ELEM4 , (4, uint32_t)
#else
# define P00_TYPE_LIST_ELEM4
#endif

#ifndef ATOMIC_INT64_LOCK_FREE
#  if defined(__GCC_HAVE_SYNC_COMPARE_AND_SWAP_8)
#   define ATOMIC_INT64_LOCK_FREE 2
#  else
#   define ATOMIC_INT64_LOCK_FREE 0
#  endif
#endif
#if ATOMIC_INT64_LOCK_FREE == 2
# define P00_TYPE_LIST_ELEM8 , (8, uint64_t)
#else
# define P00_TYPE_LIST_ELEM8
#endif

#ifndef ATOMIC_INT128_LOCK_FREE
#  if defined(__GCC_HAVE_SYNC_COMPARE_AND_SWAP_16) && (defined(UINT128_MAX) || defined(p99x_uint128))
#   define ATOMIC_INT128_LOCK_FREE 2
#  else
#   define ATOMIC_INT128_LOCK_FREE 0
#  endif
#endif
#if ATOMIC_INT128_LOCK_FREE == 2
# if defined(UINT128_MAX)
#  define P00_TYPE_LIST_ELEM16 , (16, uint128_t)
# else
#  define P00_TYPE_LIST_ELEM16 , (16, p99x_uint128)
# endif
#else
# define P00_TYPE_LIST_ELEM16
#endif


#ifndef ATOMIC_BOOL_LOCK_FREE
# if defined(__GCC_HAVE_SYNC_COMPARE_AND_SWAP_4) && (UINT_MAX <= UINT32_MAX)
#define ATOMIC_BOOL_LOCK_FREE 2
# else
#define ATOMIC_BOOL_LOCK_FREE 0
# endif
#endif
#ifndef ATOMIC_CHAR_LOCK_FREE
# define ATOMIC_CHAR_LOCK_FREE ATOMIC_INT8_LOCK_FREE
#endif
#if USHRT_MAX == UINT8_MAX
# define ATOMIC_SHORT_LOCK_FREE ATOMIC_INT8_LOCK_FREE
#elif USHRT_MAX == UINT16_MAX
# define ATOMIC_SHORT_LOCK_FREE ATOMIC_INT16_LOCK_FREE
#elif USHRT_MAX == UINT32_MAX
# define ATOMIC_SHORT_LOCK_FREE ATOMIC_INT32_LOCK_FREE
#elif USHRT_MAX == UINT64_MAX
# define ATOMIC_SHORT_LOCK_FREE ATOMIC_INT64_LOCK_FREE
#elif USHRT_MAX == UINT128_MAX
# define ATOMIC_SHORT_LOCK_FREE ATOMIC_INT128_LOCK_FREE
#else
# define ATOMIC_SHORT_LOCK_FREE 0
#endif
#if UINT_MAX == UINT8_MAX
# define ATOMIC_INT_LOCK_FREE ATOMIC_INT8_LOCK_FREE
#elif UINT_MAX == UINT16_MAX
# define ATOMIC_INT_LOCK_FREE ATOMIC_INT16_LOCK_FREE
#elif UINT_MAX == UINT32_MAX
# define ATOMIC_INT_LOCK_FREE ATOMIC_INT32_LOCK_FREE
#elif UINT_MAX == UINT64_MAX
# define ATOMIC_INT_LOCK_FREE ATOMIC_INT64_LOCK_FREE
#elif UINT_MAX == UINT128_MAX
# define ATOMIC_INT_LOCK_FREE ATOMIC_INT128_LOCK_FREE
#else
# define ATOMIC_INT_LOCK_FREE 0
#endif
#if ULONG_MAX == UINT8_MAX
# define ATOMIC_LONG_LOCK_FREE ATOMIC_INT8_LOCK_FREE
#elif ULONG_MAX == UINT16_MAX
# define ATOMIC_LONG_LOCK_FREE ATOMIC_INT16_LOCK_FREE
#elif ULONG_MAX == UINT32_MAX
# define ATOMIC_LONG_LOCK_FREE ATOMIC_INT32_LOCK_FREE
#elif ULONG_MAX == UINT64_MAX
# define ATOMIC_LONG_LOCK_FREE ATOMIC_INT64_LOCK_FREE
#elif ULONG_MAX == UINT128_MAX
# define ATOMIC_LONG_LOCK_FREE ATOMIC_INT128_LOCK_FREE
#else
# define ATOMIC_LONG_LOCK_FREE 0
#endif
#if ULLONG_MAX == UINT8_MAX
# define ATOMIC_LLONG_LOCK_FREE ATOMIC_INT8_LOCK_FREE
#elif ULLONG_MAX == UINT16_MAX
# define ATOMIC_LLONG_LOCK_FREE ATOMIC_INT16_LOCK_FREE
#elif ULLONG_MAX == UINT32_MAX
# define ATOMIC_LLONG_LOCK_FREE ATOMIC_INT32_LOCK_FREE
#elif ULLONG_MAX == UINT64_MAX
# define ATOMIC_LLONG_LOCK_FREE ATOMIC_INT64_LOCK_FREE
#elif ULLONG_MAX == UINT128_MAX
# define ATOMIC_LLONG_LOCK_FREE ATOMIC_INT128_LOCK_FREE
#else
# define ATOMIC_LLONG_LOCK_FREE 0
#endif
#if UINTPTR_MAX == UINT8_MAX
# define ATOMIC_INTPTR_LOCK_FREE ATOMIC_INT8_LOCK_FREE
#elif UINTPTR_MAX == UINT16_MAX
# define ATOMIC_INTPTR_LOCK_FREE ATOMIC_INT16_LOCK_FREE
#elif UINTPTR_MAX == UINT32_MAX
# define ATOMIC_INTPTR_LOCK_FREE ATOMIC_INT32_LOCK_FREE
#elif UINTPTR_MAX == UINT64_MAX
# define ATOMIC_INTPTR_LOCK_FREE ATOMIC_INT64_LOCK_FREE
#elif UINTPTR_MAX == UINT128_MAX
# define ATOMIC_INTPTR_LOCK_FREE ATOMIC_INT128_LOCK_FREE
#else
# define ATOMIC_INTPTR_LOCK_FREE 0
#endif
#ifndef ATOMIC_POINTER_LOCK_FREE
#define ATOMIC_POINTER_LOCK_FREE ATOMIC_INTPTR_LOCK_FREE
#endif
#if ATOMIC_INTPTR_LOCK_FREE == 2
#if UINTPTR_MAX == UINT8_MAX
# define P00_UINT_TYPE_LIST                                    \
  (1, uintptr_t)                                               \
  P00_TYPE_LIST_ELEM2                                          \
  P00_TYPE_LIST_ELEM4                                          \
  P00_TYPE_LIST_ELEM8                                          \
  P00_TYPE_LIST_ELEM16
#elif UINTPTR_MAX == UINT16_MAX
# define P00_UINT_TYPE_LIST                                    \
  (2, uintptr_t)                                               \
  P00_TYPE_LIST_ELEM1                                          \
  P00_TYPE_LIST_ELEM4                                          \
  P00_TYPE_LIST_ELEM8                                          \
  P00_TYPE_LIST_ELEM16
#elif UINTPTR_MAX == UINT32_MAX
# define P00_UINT_TYPE_LIST                                    \
  (4, uintptr_t)                                               \
  P00_TYPE_LIST_ELEM1                                          \
  P00_TYPE_LIST_ELEM2                                          \
  P00_TYPE_LIST_ELEM8                                          \
  P00_TYPE_LIST_ELEM16
#elif UINTPTR_MAX == UINT64_MAX
# define P00_UINT_TYPE_LIST                                    \
  (8, uintptr_t)                                               \
  P00_TYPE_LIST_ELEM1                                          \
  P00_TYPE_LIST_ELEM2                                          \
  P00_TYPE_LIST_ELEM4                                          \
  P00_TYPE_LIST_ELEM16
#elif UINTPTR_MAX == UINT128_MAX
# define P00_UINT_TYPE_LIST                                    \
  (16, uintptr_t)                                              \
  P00_TYPE_LIST_ELEM1                                          \
  P00_TYPE_LIST_ELEM2                                          \
  P00_TYPE_LIST_ELEM4                                          \
  P00_TYPE_LIST_ELEM8
#else
# define P00_UINT_TYPE_LIST                                    \
  (1, uint8_t)                                                 \
  P00_TYPE_LIST_ELEM2                                          \
  P00_TYPE_LIST_ELEM4                                          \
  P00_TYPE_LIST_ELEM8                                          \
  P00_TYPE_LIST_ELEM16
#endif
#endif
#if UINT_LEAST16_MAX == UINT16_MAX
# define ATOMIC_CHAR16_T_LOCK_FREE ATOMIC_INT16_LOCK_FREE
#elif UINT_LEAST16_MAX == UINT32_MAX
# define ATOMIC_CHAR16_T_LOCK_FREE ATOMIC_INT32_LOCK_FREE
#elif UINT_LEAST16_MAX == UINT64_MAX
# define ATOMIC_CHAR16_T_LOCK_FREE ATOMIC_INT64_LOCK_FREE
#elif UINT_LEAST16_MAX == UINT128_MAX
# define ATOMIC_CHAR16_T_LOCK_FREE ATOMIC_INT128_LOCK_FREE
#else
# define ATOMIC_CHAR16_T_LOCK_FREE 0
#endif
#if UINT_LEAST32_MAX == UINT32_MAX
# define ATOMIC_CHAR32_T_LOCK_FREE ATOMIC_INT32_LOCK_FREE
#elif UINT_LEAST32_MAX == UINT64_MAX
# define ATOMIC_CHAR32_T_LOCK_FREE ATOMIC_INT64_LOCK_FREE
#elif UINT_LEAST32_MAX == UINT128_MAX
# define ATOMIC_CHAR32_T_LOCK_FREE ATOMIC_INT128_LOCK_FREE
#else
# define ATOMIC_CHAR32_T_LOCK_FREE 0
#endif
#if WCHAR_MAX == UINT8_MAX || (!WCHAR_MIN && (WCHAR_MAX == INT8_MAX))
# define ATOMIC_WCHAR_LOCK_FREE ATOMIC_INT8_LOCK_FREE
#elif WCHAR_MAX == UINT16_MAX || (!WCHAR_MIN && (WCHAR_MAX == INT16_MAX))
# define ATOMIC_WCHAR_LOCK_FREE ATOMIC_INT16_LOCK_FREE
#elif WCHAR_MAX == UINT32_MAX || (!WCHAR_MIN && (WCHAR_MAX == INT32_MAX))
# define ATOMIC_WCHAR_LOCK_FREE ATOMIC_INT32_LOCK_FREE
#elif WCHAR_MAX == UINT64_MAX || (!WCHAR_MIN && (WCHAR_MAX == INT64_MAX))
# define ATOMIC_WCHAR_LOCK_FREE ATOMIC_INT64_LOCK_FREE
#elif WCHAR_MAX == UINT128_MAX || (!WCHAR_MIN && (WCHAR_MAX == INT128_MAX))
# define ATOMIC_WCHAR_LOCK_FREE ATOMIC_INT128_LOCK_FREE
#else
# define ATOMIC_WCHAR_LOCK_FREE 0
#endif

/**
 ** @brief A default unsigned integer type for type @a T
 **
 ** @return The result is an unsigned integer type of the same width
 ** as @a T, if such an integer type exists. Otherwise, the type is @c
 ** uintptr_t, an unsigned integer type that should be
 ** compatible with address arithmetic.
 **
 ** If @a T has the same width the result is @c uintptr_t. Otherwise,
 ** the result type is chosen from @c uint8_t, @c uint16_t, @c
 ** uint32_t and @c uint64_t.  If none fits the width, we fall back on @c uintptr_t.
 **
 ** As a consequence, if @a T is an integer type and the
 ** implementation has another integer type of the same width, this is
 ** not necessarily the integer type "corresponding" to @a T. E.g if
 ** @a T is <code>long long</code> and has the same width as @c long,
 ** the result type could well be <code>unsigned long</code> instead
 ** of <code>unsigned long long</code>.
 **
 ** @remark Uses the @c __typeof__ extension of the gcc-family of
 ** compilers.
 **/
P00_DOCUMENT_TYPE_ARGUMENT(P99_UINT_DEFAULT, 0)
#if defined(P00_UINT_TYPE_LIST) || defined(P00_DOXYGEN)
# define P99_UINT_DEFAULT(T)                                                      \
__typeof__(P99_GENERIC_SIZE_LIT(sizeof(T), (uintptr_t){ 0 }, P00_UINT_TYPE_LIST))
#else
# define P00_UINT_TYPE_LIST
# define P99_UINT_DEFAULT(T) uintptr_t
#endif

/**
 ** @brief Initialize a variable of type ::atomic_flag
 ** @see atomic_flag
 **/
#define ATOMIC_FLAG_INIT P99_ENC_INIT(0)

/**
 ** @brief Initialize a variable of an atomic type.
 ** @see atomic_int
 **/
#define ATOMIC_VAR_INIT(...) { .p00_xval = { .p00_t = __VA_ARGS__, }, }

/**
 ** @brief A list of types that are supposed to have lock-free atomic
 ** operations.
 **
 ** This list is constructed from knowledge given via the
 ** lock-free macros for the standard types.
 **
 ** @see ATOMIC_BOOL_LOCK_FREE
 ** @see ATOMIC_CHAR_LOCK_FREE
 ** @see ATOMIC_SHORT_LOCK_FREE
 ** @see ATOMIC_INT_LOCK_FREE
 ** @see ATOMIC_LONG_LOCK_FREE
 ** @see ATOMIC_LLONG_LOCK_FREE
 **/
#ifndef P99_ATOMIC_LOCK_FREE_TYPES
# define P99_ATOMIC_LOCK_FREE_TYPES P00_ATOMIC_LOCK_FREE_TYPES6_

#if ATOMIC_BOOL_LOCK_FREE == 2
# define P00_ATOMIC_LOCK_FREE_TYPES0 _Bool
#endif
#if ATOMIC_CHAR_LOCK_FREE == 2
# define P00_ATOMIC_LOCK_FREE_TYPES1 char, signed char, unsigned char
#endif
#if ATOMIC_SHORT_LOCK_FREE == 2
# define P00_ATOMIC_LOCK_FREE_TYPES2 short, unsigned short
#endif
#if ATOMIC_INT_LOCK_FREE == 2
# define P00_ATOMIC_LOCK_FREE_TYPES3 int, unsigned int
#endif
#if ATOMIC_LONG_LOCK_FREE == 2
# define P00_ATOMIC_LOCK_FREE_TYPES4 long, unsigned long
#endif
#if ATOMIC_LLONG_LOCK_FREE == 2
# define P00_ATOMIC_LOCK_FREE_TYPES5 long long, unsigned long long
#endif
#if ATOMIC_POINTER_LOCK_FREE == 2
# define P00_ATOMIC_LOCK_FREE_TYPES6 char*, signed char*, unsigned char*
#endif

#ifdef P00_ATOMIC_LOCK_FREE_TYPES0
# ifdef P00_ATOMIC_LOCK_FREE_TYPES1
#  define P00_ATOMIC_LOCK_FREE_TYPES1_ P00_ATOMIC_LOCK_FREE_TYPES0, P00_ATOMIC_LOCK_FREE_TYPES1
# else
#  define P00_ATOMIC_LOCK_FREE_TYPES1_ P00_ATOMIC_LOCK_FREE_TYPES0
# endif
#else
# ifdef P00_ATOMIC_LOCK_FREE_TYPES1
#  define P00_ATOMIC_LOCK_FREE_TYPES1_ P00_ATOMIC_LOCK_FREE_TYPES1
# endif
#endif

#ifdef P00_ATOMIC_LOCK_FREE_TYPES1_
# ifdef P00_ATOMIC_LOCK_FREE_TYPES2
#  define P00_ATOMIC_LOCK_FREE_TYPES2_ P00_ATOMIC_LOCK_FREE_TYPES1_, P00_ATOMIC_LOCK_FREE_TYPES2
# else
#  define P00_ATOMIC_LOCK_FREE_TYPES2_ P00_ATOMIC_LOCK_FREE_TYPES1_
# endif
#else
# ifdef P00_ATOMIC_LOCK_FREE_TYPES2
#  define P00_ATOMIC_LOCK_FREE_TYPES2_ P00_ATOMIC_LOCK_FREE_TYPES2
# endif
#endif

#ifdef P00_ATOMIC_LOCK_FREE_TYPES2_
# ifdef P00_ATOMIC_LOCK_FREE_TYPES3
#  define P00_ATOMIC_LOCK_FREE_TYPES3_ P00_ATOMIC_LOCK_FREE_TYPES2_, P00_ATOMIC_LOCK_FREE_TYPES3
# else
#  define P00_ATOMIC_LOCK_FREE_TYPES3_ P00_ATOMIC_LOCK_FREE_TYPES2_
# endif
#else
# ifdef P00_ATOMIC_LOCK_FREE_TYPES3
#  define P00_ATOMIC_LOCK_FREE_TYPES3_ P00_ATOMIC_LOCK_FREE_TYPES3
# endif
#endif

#ifdef P00_ATOMIC_LOCK_FREE_TYPES3_
# ifdef P00_ATOMIC_LOCK_FREE_TYPES4
#  define P00_ATOMIC_LOCK_FREE_TYPES4_ P00_ATOMIC_LOCK_FREE_TYPES3_, P00_ATOMIC_LOCK_FREE_TYPES4
# else
#  define P00_ATOMIC_LOCK_FREE_TYPES4_ P00_ATOMIC_LOCK_FREE_TYPES3_
# endif
#else
# ifdef P00_ATOMIC_LOCK_FREE_TYPES4
#  define P00_ATOMIC_LOCK_FREE_TYPES4_ P00_ATOMIC_LOCK_FREE_TYPES4
# endif
#endif

#ifdef P00_ATOMIC_LOCK_FREE_TYPES4_
# ifdef P00_ATOMIC_LOCK_FREE_TYPES5
#  define P00_ATOMIC_LOCK_FREE_TYPES5_ P00_ATOMIC_LOCK_FREE_TYPES4_, P00_ATOMIC_LOCK_FREE_TYPES5
# else
#  define P00_ATOMIC_LOCK_FREE_TYPES5_ P00_ATOMIC_LOCK_FREE_TYPES4_
# endif
#else
# ifdef P00_ATOMIC_LOCK_FREE_TYPES5
#  define P00_ATOMIC_LOCK_FREE_TYPES5_ P00_ATOMIC_LOCK_FREE_TYPES5
# endif
#endif

#ifdef P00_ATOMIC_LOCK_FREE_TYPES5_
# ifdef P00_ATOMIC_LOCK_FREE_TYPES6
#  define P00_ATOMIC_LOCK_FREE_TYPES6_ P00_ATOMIC_LOCK_FREE_TYPES5_, P00_ATOMIC_LOCK_FREE_TYPES6
# else
#  define P00_ATOMIC_LOCK_FREE_TYPES6_ P00_ATOMIC_LOCK_FREE_TYPES5_
# endif
#else
# ifdef P00_ATOMIC_LOCK_FREE_TYPES6
#  define P00_ATOMIC_LOCK_FREE_TYPES6_ P00_ATOMIC_LOCK_FREE_TYPES6
# endif
#endif
#endif

#ifndef P00_ATOMIC_LOCK_FREE_TYPES6_
# define P00_ATOMIC_LOCK_FREE_TYPES6_
#endif

/**
 ** @}
 **/

/**
 ** @addtogroup atomic_types
 ** @{
 **/

typedef uint32_t volatile p00_atomic_flag;

/**
 ** @brief The "minimal" type for which atomic operations must be
 ** defined.
 **
 ** This only has very basic operations that can set and clear the
 ** flag. In particular it has no operation that returns the state of
 ** the flag and that would not modify it eventually. So this is a
 ** kind of Heisenberg flag, you can't measure it without modifying
 ** it. This can be used as a spinlock to force the flag to be set,
 ** perform a desired operation and then clear the flag again.
 **
 ** There are extensions ::atomic_flag_lock, ::atomic_flag_trylock and
 ** ::atomic_flag_unlock that perform these spinlock type operations
 ** with only the necessary memory consistency.
 **/
P99_ENC_DECLARE(p00_atomic_flag, atomic_flag);

#define P00_AX(OBJP) ((OBJP)->p00_xval)
#define P00_AT(OBJP) (P00_AX(OBJP).p00_t)
#define P00_AO(OBJP) (P00_AX(OBJP).p00_o)
#define P00_AM(OBJP) (P00_AX(OBJP).p00_m)

P00_DOCUMENT_IDENTIFIER_ARGUMENT(P00_DECLARE_ATOMIC_TYPE, 0)
P00_DOCUMENT_TYPE_ARGUMENT(P00_DECLARE_ATOMIC_TYPE, 1)
P00_DOCUMENT_IDENTIFIER_ARGUMENT(P00_DECLARE_ATOMIC_TYPE, 2)
#define P00_DECLARE_ATOMIC_TYPE(TAGGER, TI, T, NAME)                   \
TAGGER P99_PASTE3(NAME, _, TAGGER) {                                   \
  atomic_flag p00_lock;                                                \
  union {                                                              \
    TI p00_o;                                                          \
    P99_UINT_DEFAULT(T) p00_m;                                         \
    T p00_t;                                                           \
  } p00_xval;                                                          \
};                                                                     \
typedef TAGGER P99_PASTE3(NAME, _, TAGGER) P99_PASTE3(NAME, _, TAGGER)


/**
 ** @brief declare an atomic type that will have lock-free operations
 **
 ** Normally it shouldn't be necessary to use this macro in user code
 ** for integral data types; the lock-free types should be detected
 ** automatically.
 **/
P00_DOCUMENT_TYPE_ARGUMENT(P99_DECLARE_ATOMIC_LOCK_FREE, 0)
P00_DOCUMENT_IDENTIFIER_ARGUMENT(P99_DECLARE_ATOMIC_LOCK_FREE, 1)
#ifdef P00_DOXYGEN
# define P99_DECLARE_ATOMIC_LOCK_FREE(T, NAME)                                                                         \
/** @brief Atomic access to a value of type <code>T</code> @see atomic_int for the possible operations on this type */ \
typedef P99_PASTE3(p99_, NAME, _union) NAME
#else
#define P99_DECLARE_ATOMIC_LOCK_FREE(T, NAME)                          \
P00_DECLARE_ATOMIC_TYPE(union, T, T, P99_PASTE2(p99_, NAME));          \
P00_DECLARE_ATOMIC_TYPE(struct, uintptr_t, T, P99_PASTE2(p99_, NAME)); \
typedef P99_PASTE3(p99_, NAME, _union) NAME
#endif


#define P00_DECLARE_ATOMIC2(T, ...)                                                                                    \
P00_DECLARE_ATOMIC_TYPE(union, T, T, P99_PASTE(p99_, __VA_ARGS__));                                                    \
P00_DECLARE_ATOMIC_TYPE(struct, uintptr_t, T, P99_PASTE(p99_, __VA_ARGS__));                                           \
/** @brief Atomic access to a value of type <code>T</code> @see atomic_int for the possible operations on this type */ \
typedef P99_PASTE(p99_, __VA_ARGS__, _struct) __VA_ARGS__

/**
 ** @brief declare an atomic type that will use lock operations to
 ** guarantee atomicity
 **
 ** Normally it shouldn't be necessary to use this macro in user code
 ** for integral data types; the lock-free types should be detected
 ** automatically.
 **
 ** This is used per default for integral types that are detected not
 ** to support atomic operations directly and for floating point
 ** types.
 **
 ** Use this macro to protect your own particular data type.
 **
 ** @param T base type for the atomic type
 **
 ** @param NAME the name of the newly derived type. Usually for type
 ** @c foo you should use something like atomic_foo.
 **/
P00_DOCUMENT_TYPE_ARGUMENT(P99_DECLARE_ATOMIC, 0)
P00_DOCUMENT_IDENTIFIER_ARGUMENT(P99_DECLARE_ATOMIC, 1)
#ifdef P00_DOXYGEN
#define P99_DECLARE_ATOMIC(T, NAME)
#else
#define P99_DECLARE_ATOMIC(...)                                                                                        \
/** @brief Atomic access to a value of type <code>T</code> @see atomic_int for the possible operations on this type */ \
P99_IF_EQ_1(P99_NARG(__VA_ARGS__))                                                                                     \
(P00_DECLARE_ATOMIC2(__VA_ARGS__, P99_PASTE2(atomic_, __VA_ARGS__)))                                                   \
(P00_DECLARE_ATOMIC2(__VA_ARGS__))
#endif

#define P00_DECLARE_ATOMIC(T, ...)                                                                                     \
/** @brief Atomic access to a value of type <code>T</code> @see atomic_int for the possible operations on this type */ \
typedef P00_ATOMIC_STRUCT(T, __VA_ARGS__) __VA_ARGS__

#define P00_DECLARE_ATOMIC_CHOICE(MAC, T, NAME)                \
P99_IF_EQ_2(MAC)                                               \
(P99_DECLARE_ATOMIC_LOCK_FREE(T, NAME))                        \
(P99_DECLARE_ATOMIC(T, NAME))


/**
 ** @brief Atomic access to a value of type <code>int</code>
 **
 ** See the "public member function" section of this description for
 ** the operations that support this type
 **/
P00_DECLARE_ATOMIC_CHOICE(ATOMIC_INT_LOCK_FREE, int, atomic_int);

/**
 ** @brief Atomic access to a value of type <code>bool</code>
 ** @see atomic_load
 ** @see atomic_store
 ** @see atomic_compare_exchange_weak
 ** @see ATOMIC_VAR_INIT
 ** @see atomic_init
 **
 **/
P00_DECLARE_ATOMIC_CHOICE(ATOMIC_BOOL_LOCK_FREE, _Bool, atomic_bool);


P00_DECLARE_ATOMIC_CHOICE(ATOMIC_CHAR_LOCK_FREE, char, atomic_char);
P00_DECLARE_ATOMIC_CHOICE(ATOMIC_CHAR_LOCK_FREE, signed char, atomic_schar);
P00_DECLARE_ATOMIC_CHOICE(ATOMIC_CHAR_LOCK_FREE, unsigned char, atomic_uchar);
P00_DECLARE_ATOMIC_CHOICE(ATOMIC_SHORT_LOCK_FREE, short, atomic_short);
P00_DECLARE_ATOMIC_CHOICE(ATOMIC_SHORT_LOCK_FREE, unsigned short, atomic_ushort);
P00_DECLARE_ATOMIC_CHOICE(ATOMIC_INT_LOCK_FREE, unsigned int, atomic_uint);
P00_DECLARE_ATOMIC_CHOICE(ATOMIC_LONG_LOCK_FREE, long, atomic_long);
P00_DECLARE_ATOMIC_CHOICE(ATOMIC_LONG_LOCK_FREE, unsigned long, atomic_ulong);
P00_DECLARE_ATOMIC_CHOICE(ATOMIC_LLONG_LOCK_FREE, long long, atomic_llong);
P00_DECLARE_ATOMIC_CHOICE(ATOMIC_LONG_LOCK_FREE, unsigned long long, atomic_ullong);

P00_DECLARE_ATOMIC_CHOICE(ATOMIC_POINTER_LOCK_FREE, void*, atomic_void_ptr);
P00_DECLARE_ATOMIC_CHOICE(ATOMIC_POINTER_LOCK_FREE, char*, atomic_char_ptr);
P00_DECLARE_ATOMIC_CHOICE(ATOMIC_POINTER_LOCK_FREE, signed char*, atomic_schar_ptr);
P00_DECLARE_ATOMIC_CHOICE(ATOMIC_POINTER_LOCK_FREE, unsigned char*, atomic_uchar_ptr);

P99_DECLARE_ATOMIC(float, atomic_float);
P99_DECLARE_ATOMIC(double, atomic_double);
P99_DECLARE_ATOMIC(long double, atomic_ldouble);

#ifndef __STDC_NO_COMPLEX__
P99_DECLARE_ATOMIC(float _Complex, atomic_cfloat);
P99_DECLARE_ATOMIC(double _Complex, atomic_cdouble);
P99_DECLARE_ATOMIC(long double _Complex, atomic_cldouble);
#define P00_ATOMIC_TYPES                                       \
  (_Bool, atomic_bool*),                                       \
  (char, atomic_char*),                                        \
  (signed char, atomic_schar*),                                \
  (unsigned char, atomic_uchar*),                              \
  (short int, atomic_short*),                                  \
  (unsigned short int, atomic_ushort*),                        \
  (int, atomic_int*),                                          \
  (unsigned int, atomic_uint*),                                \
  (long int, atomic_long*),                                    \
  (unsigned long int, atomic_ulong*),                          \
  (long long int, atomic_llong*),                              \
  (unsigned long long int, atomic_ullong*),                    \
  (float, atomic_float*),                                      \
  (double, atomic_double*),                                    \
  (long double, atomic_ldouble*),                              \
  (float _Complex, atomic_cfloat*),                            \
  (double _Complex, atomic_cdouble*),                          \
  (long double _Complex, atomic_cldouble*)
#else
#define P00_ATOMIC_TYPES                                       \
  (_Bool, atomic_bool*),                                       \
  (char, atomic_char*),                                        \
  (signed char, atomic_schar*),                                \
  (unsigned char, atomic_uchar*),                              \
  (short int, atomic_short*),                                  \
  (unsigned short int, atomic_ushort*),                        \
  (int, atomic_int*),                                          \
  (unsigned int, atomic_uint*),                                \
  (long int, atomic_long*),                                    \
  (unsigned long int, atomic_ulong*),                          \
  (long long int, atomic_llong*),                              \
  (unsigned long long int, atomic_ullong*),                    \
  (float, atomic_float*),                                      \
  (double, atomic_double*),                                    \
  (long double, atomic_ldouble*)
#endif


P00_DOCUMENT_TYPE_ARGUMENT(P99_ATOMIC_INHERIT, 0)
#define P99_ATOMIC_INHERIT(T)                                                               \
(*P99_GENERIC_LIT                                                                           \
 ((T){ 0 },                                                                                 \
  P99_GENERIC_SIZE_LIT                                                                      \
  (sizeof(T)+1,                                                                             \
   (struct P99_PASTE3(p99_atomic_, T, _struct)*){ 0 },                                      \
   (1, union P99_PASTE3(p99_atomic_, T, _union)*)                                           \
   P99_IF_EQ_2(ATOMIC_INT8_LOCK_FREE)(,(2, union P99_PASTE3(p99_atomic_, T, _union)*))()    \
   P99_IF_EQ_2(ATOMIC_INT16_LOCK_FREE)(,(3, union P99_PASTE3(p99_atomic_, T, _union)*))()   \
   P99_IF_EQ_2(ATOMIC_INT32_LOCK_FREE)(,(5, union P99_PASTE3(p99_atomic_, T, _union)*))()   \
   P99_IF_EQ_2(ATOMIC_INT64_LOCK_FREE)(,(9, union P99_PASTE3(p99_atomic_, T, _union)*))()   \
   P99_IF_EQ_2(ATOMIC_INT128_LOCK_FREE)(,(17, union P99_PASTE3(p99_atomic_, T, _union)*))() \
   ),                                                                                       \
  P00_ATOMIC_TYPES))

p99_inline
P99_CONST_FUNCTION uintptr_t p00_exchange_ignore(void* p00_x, ...) { P99_UNUSED(p00_x); return 0; }

#define P00_EXCHANGE(X)                                                 \
P99_GENERIC_SIZE                                                        \
 (sizeof(X),                                                            \
  p00_exchange_ignore,                                                  \
  (1, p00_atomic_exchange_1),                                           \
  (2, p00_atomic_exchange_2),                                           \
  (4, p00_atomic_exchange_4)                                            \
  P99_IF_EQ_2(ATOMIC_INT64_LOCK_FREE)(,(8, p00_atomic_exchange_8))()    \
  P99_IF_EQ_2(ATOMIC_INT128_LOCK_FREE)(,(16, p00_atomic_exchange_16))() \
  )

/**
 ** @brief refer to an atomic type of base type T
 **
 ** @param T a @b type name
 **
 ** This implements only part of the @c _Atomic keyword of C11. First
 ** it implements only the part described in 6.7.2.4, atomic type
 ** specifiers. I does not cover type qualifiers.
 **
 ** Second for data types that are not predefined integer or
 ** floating point types, the underlying realization of the atomic type
 ** must have been previously declared with ::P99_DECLARE_ATOMIC.
 **
 ** Besides the atomic integer types that are listed in the standard
 ** we provide 6 atomic types for all real and complex floating point
 ** types, as long as they exist.
 **
 ** For the standard predefined integer types there are different
 ** atomic types as they are listed in the standard. The atomic types
 ** for the floating point types (as there are no names listed in the
 ** standard) are chosen arbitrarily with an @c atomic_ prefix. Don't
 ** rely on a particular naming. Whenever ::_Atomic is called with a
 ** typename @a T that resolves to one of the predefined arithmetic
 ** types (without @c enum and pointers) the same type as for the
 ** original type results: e.g if @c unsigned is 32 bit wide (and @c
 ** long is 64)
 **
 ** @code
 ** _Atomic(uint32_t) a;
 ** _Atomic(unsigned) b;
 ** @endcode
 **
 ** is equivalent to
 **
 ** @code
 ** atomic_uint a;
 ** atomic_uint b;
 ** @endcode
 **
 ** @remark These types don't work with the usual operators such as @c
 ** +=, and a variable of such an atomic type doesn't evaluate to an
 ** rvalue of the base type.
 **
 ** @remark These variables are guaranteed to be in a valid state when
 ** they are @c 0 initialized by the default initializer, either
 ** explicitly or when declared with static storage location. The
 ** initial value of the base type corresponds to its @c 0 initialized
 ** value.
 **
 ** @see ATOMIC_VAR_INIT for an initializer macro
 ** @see atomic_init for a initializer function
 ** @see atomic_load to return an rvalue of the underlying base type @a T
 ** @see atomic_store to store a value that is compatible with @a T
 ** @see atomic_compare_exchange_weak to store a value conditionally
 **
 ** With the exception of the floating point types, these latter three
 ** operations are lock-free if a lock-free low-level function is
 ** implemented for an unsigned integer type with the same
 ** width. This should usually be the case for all integer types,
 ** including @c enum, and pointer types.
 **
 ** If the underlying operations are defined for @a T the following
 ** generic functions (macros) can be used with an atomic type:
 **
 ** @see atomic_fetch_add to add a value to the object as @c += would on @a T. This should be
 ** lock-free for all integer %types (see above) and is @em not
 ** lock-free for floating point %types.
 **
 ** @see atomic_fetch_sub to subtract a value as @c -= would on @a T. See ::atomic_fetch_add
 ** for constraints.
 **
 ** @see atomic_fetch_or "or" a value in place as @c |= would on @a T
 **
 ** @see atomic_fetch_and "and" a value in place as @c &= would on @a T
 **
 ** @see atomic_fetch_xor "exclusive or" a value in place as @c ^= would on @a T
 **
 ** @warning Don't assign atomic variables through the @c =
 ** operator. This will most probably not do what you expect:
 ** - This would copy state information from the right side to the
 **   left side.
 ** - Neither the read access on the right side nor the write access
 **   on the left side would be atomic.
 **
 ** @warning Don't use atomic variables as function arguments.
 ** - If you are only interested in the value evaluate by ::atomic_load.
 ** - Otherwise pass it through a pointer to atomic type.
 **
 ** @ingroup C11_keywords
 **/
#ifdef P00_DOXYGEN
# define _Atomic(T) P99_PASTE2(atomic_, T)
#else
# define _Atomic(T) __typeof__(P99_ATOMIC_INHERIT(T))
#endif

typedef _Atomic(char16_t) atomic_char16_t;
typedef _Atomic(char32_t) atomic_char32_t;
typedef _Atomic(wchar_t) atomic_wchar_t;
typedef _Atomic(int_least8_t) atomic_int_least8_t;
typedef _Atomic(uint_least8_t) atomic_uint_least8_t;
typedef _Atomic(int_least16_t) atomic_int_least16_t;
typedef _Atomic(uint_least16_t) atomic_uint_least16_t;
typedef _Atomic(int_least32_t) atomic_int_least32_t;
typedef _Atomic(uint_least32_t) atomic_uint_least32_t;
typedef _Atomic(int_least64_t) atomic_int_least64_t;
typedef _Atomic(uint_least64_t) atomic_uint_least64_t;
typedef _Atomic(int_fast8_t) atomic_int_fast8_t;
typedef _Atomic(uint_fast8_t) atomic_uint_fast8_t;
typedef _Atomic(int_fast16_t) atomic_int_fast16_t;
typedef _Atomic(uint_fast16_t) atomic_uint_fast16_t;
typedef _Atomic(int_fast32_t) atomic_int_fast32_t;
typedef _Atomic(uint_fast32_t) atomic_uint_fast32_t;
typedef _Atomic(int_fast64_t) atomic_int_fast64_t;
typedef _Atomic(uint_fast64_t) atomic_uint_fast64_t;
typedef _Atomic(intptr_t) atomic_intptr_t;
typedef _Atomic(uintptr_t) atomic_uintptr_t;
typedef _Atomic(size_t) atomic_size_t;
typedef _Atomic(ptrdiff_t) atomic_ptrdiff_t;
typedef _Atomic(intmax_t) atomic_intmax_t;
typedef _Atomic(uintmax_t) atomic_uintmax_t;

/**
 ** @}
 **/

/**
 ** @addtogroup fences Memory Fences
 **
 ** This is only rudimentary support for fences. Basically, all fences perform
 ** a full memory barrier except where the argument ::memory_order_relaxed is
 ** passed.
 ** @{
 **/

#define atomic_thread_fence p00_mfence

/**
 ** @remark In the current implementation a signal fence and a thread
 ** fence are the same full memory barrier.
 **/
#define atomic_signal_fence atomic_thread_fence

/**
 ** @}
 **/

/**
 ** @brief Unconditionally set @a *object to @c true and return the
 ** previous value
 **
 ** @related atomic_flag
 **
 ** @param OBJ the object that will be set
 **
 ** @param ORD fine tune the set operation for a specific memory order
 ** if the platform supports it. Otherwise the memory order is the
 ** most restrictive, namely ::memory_order_seq_cst.
 **/
#define atomic_flag_test_and_set_explicit(OBJ, ORD) p00_sync_lock_test_and_set(&P99_ENCP(OBJ), (ORD))

/**
 ** @brief Unconditionally set @a OBJ to @c true and return the
 ** previous value
 **
 ** @related atomic_flag
 **
 ** This implementation has the additional feature that a second
 ** optional argument can be given. The call is then equivalent to one
 ** to ::atomic_flag_test_and_set_explicit.
 **/
#define atomic_flag_test_and_set(OBJ) p00_sync_lock_test_and_set(&P99_ENCP(OBJ))

/**
 ** @brief Unconditionally set @a *p00_objp to @c false
 **
 ** @related atomic_flag
 **
 ** @param p00_objp the object that will be set
 **
 ** @param p00_ord fine tune the set operation for a specific memory
 ** order. The current implementation only uses this to enforce a
 ** complete memory barrier where necessary.
 **/
#define atomic_flag_clear_explicit(OBJ, ORD) p00_sync_lock_release(&P99_ENCP(OBJ), (ORD))

/**
 ** @brief Unconditionally set @a *p00_objp to @c false
 **
 ** @related atomic_flag
 **/
#define atomic_flag_clear(OBJ)  p00_sync_lock_release(&P99_ENCP(OBJ))

#include "p99_atomic_flag.h"

/**
 ** @brief return true if @a OBJP points to a lock-free object
 **
 ** @remark in this implementation this is a compile time expression,
 ** but it should not be built upon for future
 ** implementations of the C11 standard. For us this property is
 ** important such that two different versions of the atomic
 ** operations can be chosen at compile time.
 **
 ** @remark Uses the @c __typeof__ extension of the gcc-compiler
 ** family.
 **
 ** @see atomic_int
 **/
#define atomic_is_lock_free(OBJP) (!offsetof(__typeof__(*OBJP), p00_xval))

#define P00_ATOMIC_TERN(OBJP, VAL, ALT) P99_TYPED_TERN(atomic_is_lock_free(OBJP), (VAL), (ALT))

/**
 ** @brief Initialize the object behind @a OBJP with value @a VAL
 **
 ** @a VAL and the base type of @a OBJP must be assignment compatible.
 **
 ** @warning this should only be used in a context that is known to
 ** have no race condition
 **
 ** @see atomic_int
 **/
#define atomic_init(OBJP, VAL)                                 \
p99_extension                                                  \
(void)({                                                       \
    P99_MAC_ARGS((p00_objp, OBJP), (p00_val, VAL));            \
    /* To take care of the atomic_flag and padding bytes. */   \
    memset((void*)p00_objp, 0, sizeof *p00_objp);              \
    P00_AT(p00_objp) = p00_val;                                \
  })

#ifdef P00_DOXYGEN
/**
 ** @brief Store @a DESIRED into the object behind @a OBJP and return its previous value.
 **
 ** @a DESIRED and the base type of @a OBJP must be assignment compatible.
 **
 ** @a ORD is the value for the memory consistency. Currently this
 ** argument will not be taken into account for structure types.
 **
 ** @remark this can be used in a context that is known to have a race
 ** condition
 **
 ** @see atomic_int
 **/
#define atomic_exchange_explicit(OBJP, DESIRED, ORD)
#else
#define atomic_exchange_explicit(OBJP, DESIRED, ORD)                                     \
p99_extension                                                                            \
({                                                                                       \
  P99_MACRO_PVAR(p00_objp, (OBJP), volatile);                                            \
  typedef __typeof__(P00_AT(p00_objp)) p00_base_t;                                       \
  typedef __typeof__(P00_AX(p00_objp)) p00_ubase_t;                                      \
  register p00_base_t const p00_des = (DESIRED);                                         \
  register p00_ubase_t p00_ret = P99_INIT;                                               \
  if (!atomic_is_lock_free(p00_objp)) {                                                  \
    P99_SPIN_EXCLUDE(&p00_objp->p00_lock) {                                              \
      p00_ret.p00_t = P00_AT(p00_objp);                                                  \
      P00_AT(p00_objp) = p00_des;                                                        \
    }                                                                                    \
  } else {                                                                               \
    P99_IF_EMPTY(P99_ATOMIC_LOCK_FREE_TYPES)                                             \
      ()                                                                                 \
      (register p00_ubase_t const p00_desm = { .p00_t = p00_des };                       \
       p00_ret.p00_m = p00_atomic_exchange_n(&P00_AM(p00_objp), p00_desm.p00_m, (ORD))); \
  }                                                                                      \
  p00_ret.p00_t;                                                                         \
 })
#endif

/**
 ** @brief Store @a DESIRED into the object behind @a OBJP and return its previous value.
 **
 ** @a DESIRED and the base type of @a OBJP must be assignment compatible.
 **
 ** @remark this can be used in a context that is known to have a race
 ** condition
 **
 ** @see atomic_int
 ** @see atomic_exchange_explicit
 **/
#define atomic_exchange(OBJP, DESIRED)                            \
atomic_exchange_explicit((OBJP), (DESIRED), memory_order_seq_cst)


/**
 ** @brief Return the value of the object behind @a OBJP.
 **
 ** @a ORD is the value for the memory consistency. Currently this
 ** argument will not be taken into account for structure types.
 **
 ** @remark this can be used in a context that is known to have a race
 ** condition
 **
 ** @see atomic_int
 **/
#define atomic_load_explicit(OBJP, ORD)                              \
p99_extension                                                        \
({                                                                   \
  P99_MACRO_PVAR(p00_objp, (OBJP), volatile);                        \
  typedef __typeof__(P00_AX(p00_objp)) p00_ubase_t;                  \
  register p00_ubase_t p00_ret = P99_INIT;                           \
  if (!atomic_is_lock_free(p00_objp)) {                              \
    P99_SPIN_EXCLUDE(&p00_objp->p00_lock)                            \
      p00_ret.p00_t = P00_AT(p00_objp);                              \
  } else {                                                           \
    P99_IF_EMPTY(P99_ATOMIC_LOCK_FREE_TYPES)                         \
      (P00_AT(p00_objp))                                             \
      (p00_ret.p00_m = p00_atomic_load_n(&P00_AM(p00_objp), (ORD))); \
  }                                                                  \
  p00_ret.p00_t = p00_ret.p00_t;                                     \
 })

/**
 ** @see atomic_load_explicit
 **/
#define atomic_load(OBJP) atomic_load_explicit((OBJP), memory_order_seq_cst)


#define P00_CVT(EXP) ((void const*)(((struct { void const volatile* a; }){ .a = (EXP) }).a))

/**
 ** @brief Atomically compare @a *OBJP to @a *EXPECTED and set it to
 ** @a DESIRED if they are equal.
 **
 ** @return true if both values agree and @c false otherwise.  If the
 ** two values are not the same, the current value is also returned in @a
 ** *EXPECTED.
 **
 ** The base type of @a OBJP and @a *EXPECTED must be compatible, that
 ** is they must be the same if all qualifiers are taken out.
 **
 ** @a DESIRED must be assignment compatible with the base type of @a
 ** OBJP.
 **
 ** @a ORD is the value for the memory consistency. Currently this
 ** argument will not be taken into account for structure types.
 **
 ** @see atomic_int
 **/
#define atomic_compare_exchange_weak_explicit(OBJP, EXPECTED, DESIRED, SUCC, FAIL) \
  p00_atomic_compare_exchange(true, OBJP, EXPECTED, DESIRED, SUCC, FAIL,)

#define atomic_compare_exchange_weak(OBJP, EXPECTED, DESIRED)                                              \
atomic_compare_exchange_weak_explicit(OBJP, EXPECTED, DESIRED, memory_order_seq_cst, memory_order_seq_cst)

#define atomic_compare_exchange_strong_explicit(OBJP, EXPECTED, DESIRED, SUCC, FAIL) \
  p00_atomic_compare_exchange(false, OBJP, EXPECTED, DESIRED, SUCC, FAIL,)

#define atomic_compare_exchange_strong(OBJP, EXPECTED, DESIRED)                                              \
atomic_compare_exchange_strong_explicit(OBJP, EXPECTED, DESIRED, memory_order_seq_cst, memory_order_seq_cst)

#define p00_atomic_compare_exchange(WEAK, OBJP, EXPECTED, DESIRED, SUCC, FAIL, ...)                          \
p99_extension                                                                                                \
({                                                                                                           \
  P99_MACRO_PVAR(p00_objp, (OBJP), volatile);                                                                \
  typedef __typeof__(P00_AT(p00_objp)) p00_base_t;                                                           \
  typedef __typeof__(P00_AX(p00_objp)) p00_ubase_t;                                                          \
  typedef __typeof__(P00_AM(p00_objp)) p00_mbase_t;                                                          \
  /* Both, *EXPECTED and DESIRED must be assignment compatible with the base type */                         \
  register p00_base_t volatile* const p00_exp = (EXPECTED);                                                  \
  register p00_ubase_t const p00_des =  { .p00_t = (DESIRED) };                                              \
  register _Bool p00_ret = false;                                                                            \
  if (!atomic_is_lock_free(p00_objp)) {                                                                      \
    P99_SPIN_EXCLUDE(&p00_objp->p00_lock) {                                                                  \
      p00_ret = !memcmp(P00_CVT(p00_exp), P00_CVT(&P00_AT(p00_objp)), sizeof *p00_exp);                      \
      if (p00_ret) P00_AT(p00_objp) = p00_des.p00_t;                                                         \
      else *p00_exp = P00_AT(p00_objp);                                                                      \
    }                                                                                                        \
  }                                                                                                          \
  P99_IF_EMPTY(P99_ATOMIC_LOCK_FREE_TYPES)                                                                   \
    (else p00_ret = false;)                                                                                  \
    (else p00_ret = p00_atomic_compare_exchange_n(&P00_AM(p00_objp), ((p00_mbase_t*)p00_exp), p00_des.p00_m, \
                                                  (WEAK), memory_order_seq_cst, memory_order_seq_cst);       \
     )                                                                                                       \
    p00_ret;                                                                                                 \
 })

#ifdef P00_DOXYGEN
/**
 ** @brief Store @a DESIRED into the object behind @a OBJP.
 **
 ** @a DESIRED and the base type of @a OBJP must be assignment compatible.
 **
 ** @remark this can be used in a context that is known to have a race
 ** condition
 **
 ** @a ORD is the value for the memory consistency. Currently this
 ** argument will not be taken into account for structure types.
 **
 ** @see atomic_int
 **/
#define atomic_store_explicit(OBJP, DES, ORD)
#else
#define atomic_store_explicit(OBJP, DES, ORD)                        \
p99_extension                                                        \
({                                                                   \
  P99_MACRO_PVAR(p00_objp, (OBJP), volatile);                        \
  P99_MACRO_VAR(p00_desp, (DES));                                    \
  typedef __typeof__(P00_AX(p00_objp)) p00_ubase_t;                  \
  register p00_ubase_t const p00_des =  { .p00_t = (p00_desp) };     \
  if (!atomic_is_lock_free(p00_objp)) {                              \
    P99_SPIN_EXCLUDE(&p00_objp->p00_lock)                            \
      P00_AT(p00_objp) = p00_des.p00_t;                              \
  } else {                                                           \
    P99_IF_EMPTY(P99_ATOMIC_LOCK_FREE_TYPES)                         \
      (P00_AT(p00_objp))                                             \
      (p00_atomic_store_n(&P00_AM(p00_objp), p00_des.p00_m, (ORD))); \
  }                                                                  \
 })
#endif

/**
 ** @see atomic_store_explicit
 **/
#define atomic_store(OBJP, DES) atomic_store_explicit(OBJP, DES, memory_order_seq_cst)


#define P00_FETCH_OP(OBJP, OPERAND, BUILTIN, OPERATOR, ORD)          \
p99_extension                                                        \
({                                                                   \
  P99_MACRO_PVAR(p00_objp, (OBJP), volatile);                        \
  P99_MACRO_VAR(p00_op, OPERAND);                                    \
  ((!atomic_is_lock_free(p00_objp))                                  \
   ? ({                                                              \
       register __typeof__(P00_AT(p00_objp)) p00_ret = P99_INIT;     \
       P99_SPIN_EXCLUDE(&p00_objp->p00_lock) {                       \
         p00_ret = P00_AT(p00_objp);                                 \
         P00_AT(p00_objp) OPERATOR p00_op;                           \
       }                                                             \
       p00_ret;                                                      \
     })                                                              \
   : (P99_IF_EMPTY(P99_ATOMIC_LOCK_FREE_TYPES)                       \
      (P00_AT(p00_objp))                                             \
      (P00_ATOMIC_TERN(p00_objp,                                     \
                       BUILTIN(&P00_AO(p00_objp),                    \
                               P00_ATOMIC_TERN(p00_objp, p00_op, 0), \
                               (ORD)),                               \
                       P00_AT(p00_objp)))));                         \
 })

/**
 ** @brief Atomically add @a OPERAND to @a *OBJP.
 **
 ** @return the current value hidden in @a OBJP before the operation.
 **
 ** @a OPERAND must be assignment compatible with the base type of @a
 ** OBJP.
 **
 ** The base type of @a OBJP must have an operator @c +=.
 **
 ** @a ORD is the value for the memory consistency. Currently this
 ** argument will not be taken into account for types that aren't
 ** natively supported with atomic operations.
 **
 ** @see atomic_fetch_add for a simpler version without @a ORD parameter
 ** @see atomic_int
 **/
#define atomic_fetch_add_explicit(OBJP, OPERAND, ORD)            \
P00_FETCH_OP((OBJP), (OPERAND), p00_atomic_fetch_add, +=, (ORD))

#define atomic_fetch_add(OBJP, OPERAND) atomic_fetch_add_explicit((OBJP), (OPERAND), memory_order_seq_cst)

/**
 ** @brief Atomically subtract @a OPERAND from @a *OBJP.
 **
 ** @return the current value hidden in @a OBJP before the operation.
 **
 ** @a OPERAND must be assignment compatible with the base type of @a
 ** OBJP.
 **
 ** The base type of @a OBJP must have an operator @c -=.
 **
 ** @a ORD is the value for the memory consistency. Currently this
 ** argument will not be taken into account for types that aren't
 ** natively supported with atomic operations.
 **
 ** @see atomic_fetch_sub for a simpler version without @a ORD parameter
 ** @see atomic_int
 **/
#define atomic_fetch_sub_explicit(OBJP, OPERAND, ORD)          \
P00_FETCH_OP((OBJP), (OPERAND), p00_atomic_fetch_sub, -=, ORD)

#define atomic_fetch_sub(OBJP, OPERAND) atomic_fetch_sub_explicit((OBJP), (OPERAND), memory_order_seq_cst)

/**
 ** @brief Atomically do a bitwise OR operation between @a OPERAND and
 ** @a *OBJP.
 **
 ** @return the current value hidden in @a OBJP before the operation.
 **
 ** @a OPERAND must be assignment compatible with the base type of @a
 ** OBJP.
 **
 ** The base type of @a OBJP must have an operator @c |=.
 **
 ** @a ORD is the value for the memory consistency. Currently this
 ** argument will not be taken into account for types that aren't
 ** natively supported with atomic operations.
 **
 ** @see atomic_fetch_or for a simpler version without @a ORD parameter
 ** @see atomic_int
 **/
#define atomic_fetch_or_explicit(OBJP, OPERAND, ORD)            \
P00_FETCH_OP((OBJP), (OPERAND), p00_atomic_fetch_or, |=, (ORD))

#define atomic_fetch_or(OBJP, OPERAND) atomic_fetch_or_explicit((OBJP), (OPERAND), memory_order_seq_cst)

/**
 ** @brief Atomically do a bitwise AND operation between @a OPERAND
 ** and @a *OBJP.
 **
 ** @return the current value hidden in @a OBJP before the operation.
 **
 ** @a OPERAND must be assignment compatible with the base type of @a
 ** OBJP.
 **
 ** The base type of @a OBJP must have an operator @c &=.
 **
 ** @a ORD is the value for the memory consistency. Currently this
 ** argument will not be taken into account for types that aren't
 ** natively supported with atomic operations.
 **
 ** @see atomic_fetch_and for a simpler version without @a ORD parameter
 ** @see atomic_int
 **/
#define atomic_fetch_and_explicit(OBJP, OPERAND, ORD)            \
P00_FETCH_OP((OBJP), (OPERAND), p00_atomic_fetch_and, &=, (ORD))

#define atomic_fetch_and(OBJP, OPERAND) atomic_fetch_and_explicit((OBJP), (OPERAND), memory_order_seq_cst)

/**
 ** @brief Atomically do a bitwise XOR operation between @a OPERAND
 ** and @a *OBJP.
 **
 ** @return the current value hidden in @a OBJP before the operation.
 **
 ** @a OPERAND must be assignment compatible with the base type of @a
 ** OBJP.
 **
 ** The base type of @a OBJP must have an operator @c ^=.
 **
 ** @a ORD is the value for the memory consistency. Currently this
 ** argument will not be taken into account for types that aren't
 ** natively supported with atomic operations.
 **
 ** @see atomic_fetch_xor for a simpler version without @a ORD parameter
 ** @see atomic_int
 ** @see _Atomic
 **/
#define atomic_fetch_xor_explicit(OBJP, OPERAND, ORD)            \
P00_FETCH_OP((OBJP), (OPERAND), p00_atomic_fetch_xor, ^=, (ORD))

#define atomic_fetch_xor(OBJP, OPERAND) atomic_fetch_xor_explicit((OBJP), (OPERAND), memory_order_seq_cst)

#define atomic_fetch_add_conditional(OBJP, OPERAND)                       \
p99_extension                                                             \
({                                                                        \
  P99_MACRO_VAR(p00_objp, (OBJP));                                        \
  P99_MACRO_VAR(p00_op, (OPERAND));                                       \
  __typeof__(P00_AT(p00_objp)) p00_ret;                                   \
  /* be sure that the result can not be used as an lvalue */              \
  register __typeof__(p00_ret = p00_ret) p00_r = atomic_load(p00_objp);   \
  p00_ret = p00_r;                                                        \
  while (p00_r) {                                                         \
    P99_MACRO_VAR(p00_des, p00_ret + p00_op);                             \
    if (atomic_compare_exchange_weak(p00_objp, &p00_ret, p00_des)) break; \
    else p00_r = p00_ret;                                                 \
  }                                                                       \
  p00_r = p00_ret;                                                        \
 })

/**
 ** @}
 **/


# endif /* P00_NO_ATOMICS */
#undef P00_NO_ATOMICS

#endif /* no stdatomic.h*/

/**
 ** @addtogroup atomic_types
 ** @{
 **/
#define atomic_fetch_max(OBJP, OPERAND) atomic_fetch_max_explicit((OBJP), (OPERAND), memory_order_seq_cst)

/**
 ** @brief Atomically do a max operation between @a OPERAND
 ** and @a *OBJP.
 **
 ** @return the current value hidden in @a OBJP before the operation.
 **
 ** @a OPERAND must be assignment compatible with the base type of @a
 ** OBJP.
 **
 ** @a ORD is the value for the memory consistency. Currently this
 ** argument will not be taken into account for types that aren't
 ** natively supported with atomic operations.
 **
 ** @see atomic_fetch_max for a simpler version without @a ORD parameter
 ** @see atomic_int
 ** @see _Atomic
 **/
#define atomic_fetch_max_explicit(OBJP, OPERAND, ORD)                    \
p99_extension                                                            \
({                                                                       \
  P99_MACRO_VAR(p00_objp, (OBJP));                                       \
  P99_MACRO_VAR(p00_op, (OPERAND));                                      \
  __typeof__(atomic_load(p00_objp)) p00_ret;                             \
  /* be sure that the result can not be used as an lvalue */             \
  register __typeof__(p00_ret = p00_ret) p00_r = atomic_load(p00_objp);  \
  p00_ret = p00_r;                                                       \
  while (p00_r <= p00_op) {                                              \
    if (atomic_compare_exchange_weak(p00_objp, &p00_ret, p00_op)) break; \
    else p00_r = p00_ret;                                                \
  }                                                                      \
  p00_r = p00_ret;                                                       \
 })

/**
 ** @brief Protect the following block or statement as a critical
 ** section of the program.
 **
 ** Internally this uses a <code>static</code> ::atomic_flag as a
 ** spinlock, so this is an active wait.
 **
 ** @warning Such a section should only contain a handful of
 ** statements.
 **
 ** @warning Such a section should not contain preliminary exits such
 ** as @c goto, @c break, @c return, @c longjmp, or ::P99_UNWIND etc.
 **
 ** @code
 ** P99_CRITICAL {
 **    // do some operations on a fragile resource here
 ** }
 ** @endcode
 **
 ** Such a critical section is only protected against threads that try
 ** to enter this same critical section. Threads may well
 ** simultaneously be in different critical sections.
 **
 ** @remark Don't use this if you just want to protect e.g a counter
 ** that is shared between different threads. ::_Atomic and the
 ** operations on atomic variables are more appropriate for that.
 **
 ** @see P99_SPIN_EXCLUDE to protect several critical sections against
 ** each other.
 **
 ** @see P99_MUTUAL_EXCLUDE that is more suited for larger sections.
 **/
P99_BLOCK_DOCUMENT
#define P99_CRITICAL P00_CRITICAL(P99_UNIQ(crit))

#define P00_CRITICAL(ID)                                       \
P00_BLK_START                                                  \
P00_BLK_DECL_STATIC(atomic_flag, ID, ATOMIC_FLAG_INIT)         \
P99_SPIN_EXCLUDE(ID)

/**
 ** @}
 **/


#endif
