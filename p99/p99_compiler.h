/* This may look like nonsense, but it really is -*- mode: C -*-              */
/*                                                                            */
/* Except for parts copied from previous work and as explicitly stated below, */
/* the authors and copyright holders for this work are as follows:            */
/* (C) copyright  2013 Bobby                                                  */
/* (C) copyright  2010-2015 Jens Gustedt, INRIA, France                       */
/* (C) copyright  2013 Pierre-Nicolas Clauss                                  */
/* (C) copyright  2012 William Morris                                         */
/*                                                                            */
/* This file is free software; it is part of the P99 project.                 */
/* You can redistribute it and/or modify it under the terms of the QPL as     */
/* given in the file LICENSE. It is distributed without any warranty;         */
/* without even the implied warranty of merchantability or fitness for a      */
/* particular purpose.                                                        */
/*                                                                            */
#ifndef P99_COMPILER_H
#define P99_COMPILER_H

#include "p99_args.h"

/**
 ** @file
 ** @brief Group compiler dependencies together in one file
 **
 ** This has been tested with different versions of gcc (GNU, versions 4.0
 ** to 4.4), clang, opencc (OPEN64) and icc (INTEL).
 **/


/**
 ** @def P99_COMPILER
 **
 ** @brief Identify the compiler
 **
 ** All compilers have some specific macro that identifies them but it
 ** is difficult for user code to track all of them. This macro here
 ** can be used to identify the compiler in a portable way. E.g by
 ** something like
 **
 ** @code
 ** #if P99_COMPILER & (P99_COMPILER_CLANG | P99_COMPILER_GNU | P99_COMPILER_OPEN64)
 ** ...
 ** #endif
 ** @endcode
 **
 ** See @link p99_generated.h @endlink for a list of the compilers
 ** that are known to P99.
 **/

/**
 ** @addtogroup compiler Compiler Specific Tuning and Extensions
 **
 ** Many compilers provide extensions that could be
 ** useful. Unfortunately similar extension are often presented
 ** differently with different compilers. Here we try to give macros
 ** that abstract from these compiler specifics.
 **
 ** As I personally mainly have compilers that all claim themselves to
 ** be compatible with gcc, this collection is strongly biased towards
 ** gcc extensions. Please don't hesitate to point me to documentation
 ** of other compilers that could be useful here.
 **
 ** @see P99_COMPILER
 ** @see P99_IF_COMPILER
 ** @{
 **/

/**
 ** @addtogroup compiler_utilities A small collection of utilities
 **
 ** @{
 **/

/**
 ** @example test-p99-conformance.c
 ** @brief A file that provides a test for C99 conformance.
 **
 ** It only tests the "compiler" part of C, that is without any
 ** include files. Any C implementation, whether hosted or
 ** freestanding should comply with this.
 **
 ** To convince your compiler to compile this you might have to
 ** provide some additional parameters on the command line. E.g for
 ** the gcc family of compilers (including third party pretenders) you
 ** usually have to give "-std=c99" to switch to C99 mode. But other
 ** parameters may be in order, consult your compiler documentation.
 **
 ** This file is split into several parts that hopefully are
 ** self explanatory. Each of the parts has a macro @c SKIP_... that
 ** lets you skip a test.
 **/

#define P00_PREFIX0(N) P00_PREFIX0_(N)
#define P00_PREFIX0_(N) 0 ## N
#define P00_STRINGIFY(...) #__VA_ARGS__
#define P00_VERSION_NO(A, B, C) (((A)*10000UL)+(B)*100UL+(C))

/**
 ** @brief Transform the argument list into one string.
 **/
#define P99_STRINGIFY(...) P00_STRINGIFY(__VA_ARGS__)

/* be sure to put all compilers that are faking gcc before gcc itself */
#if P99_COMPILER & P99_COMPILER_APPLE
# undef P00_COMPILER_PRAGMA_APPLE
# define P00_COMPILER_PRAGMA_APPLE(STR) _Pragma(STR)
# undef P99_COMPILER_VERSION
# define P99_COMPILER_VERSION                                  \
 "Apple/clang "                                                \
 __apple_build_version__                                       \
 "pretending clang version "                                   \
 __clang_version__                                             \
 "; gnu "                                                      \
 P99_STRINGIFY(__GNUC__) "."                                   \
 P99_STRINGIFY(__GNUC_MINOR__) "."                             \
 P99_STRINGIFY(__GNUC_PATCHLEVEL__)
# define P99_VERSION_NO __apple_build_version__

#elif P99_COMPILER & P99_COMPILER_CLANG
# undef P00_COMPILER_PRAGMA_CLANG
# define P00_COMPILER_PRAGMA_CLANG(STR) _Pragma(STR)
# undef P99_COMPILER_VERSION
# define P99_COMPILER_VERSION                                  \
 "clang "                                                      \
 __clang_version__                                             \
 "; gnu "                                                      \
 P99_STRINGIFY(__GNUC__) "."                                   \
 P99_STRINGIFY(__GNUC_MINOR__) "."                             \
 P99_STRINGIFY(__GNUC_PATCHLEVEL__)
# define P99_VERSION_NO P00_VERSION_NO(__clang_major__, __clang_minor__, __clang_patchlevel__)

#elif P99_COMPILER & P99_COMPILER_INTEL
# undef P99_COMPILER_VERSION
# define P99_COMPILER_VERSION                                  \
 "intel " P99_STRINGIFY(__INTEL_COMPILER)                      \
 "; gnu "                                                      \
 P99_STRINGIFY(__GNUC__) "."                                   \
 P99_STRINGIFY(__GNUC_MINOR__) "."                             \
 P99_STRINGIFY(__GNUC_PATCHLEVEL__)
# define P99_VERSION_NO P00_VERSION_NO(__INTEL_COMPILER, 0, 0)

#elif P99_COMPILER & P99_COMPILER_PCC
# undef P99_COMPILER_VERSION
# define P99_COMPILER_VERSION                                  \
"pcc "                                                         \
 P99_STRINGIFY(__PCC__)                                        \
 "." P99_STRINGIFY(__PCC_MINOR__)                              \
 "." P99_STRINGIFY(__PCC_MINORMINOR__)                         \
 "; gnu "                                                      \
 P99_STRINGIFY(__GNUC__) "."                                   \
 P99_STRINGIFY(__GNUC_MINOR__) "."                             \
 P99_STRINGIFY(__GNUC_PATCHLEVEL__)
# define P99_VERSION_NO P00_VERSION_NO(__PCC__, __PCC_MINOR__, __PCC_MINORMINOR__)

#elif P99_COMPILER & P99_COMPILER_TINYC
# undef P99_COMPILER_VERSION
# define P99_COMPILER_VERSION                                  \
  "tinyc "                                                     \
  P99_STRINGIFY(__TINYC__)
# define P99_VERSION_NO P00_VERSION_NO(__TINYC__, 0, 0)

#elif P99_COMPILER & P99_COMPILER_OPEN64
# undef P99_COMPILER_VERSION
# define P99_COMPILER_VERSION                                  \
 "open64 " __OPEN64__                                          \
 "; gnu "                                                      \
 P99_STRINGIFY(__GNUC__) "."                                   \
 P99_STRINGIFY(__GNUC_MINOR__) "."                             \
 P99_STRINGIFY(__GNUC_PATCHLEVEL__)
# define P99_VERSION_NO P00_VERSION_NO(__TINYC__, 0, 0)

#elif P99_COMPILER & P99_COMPILER_GNU
# undef P99_COMPILER_VERSION
# define P99_COMPILER_VERSION                                  \
 "gnu "                                                        \
 P99_STRINGIFY(__GNUC__) "."                                   \
 P99_STRINGIFY(__GNUC_MINOR__) "."                             \
 P99_STRINGIFY(__GNUC_PATCHLEVEL__)
# define P99_VERSION_NO P00_VERSION_NO(__GNUC__, __GNUC_MINOR__, __GNUC_PATCHLEVEL__)
#endif

/* intel is cheating about the gcc abi they support */
#if P99_COMPILER & P99_COMPILER_INTEL
# if (__ICC < 1400) && (__GNUC__ == 4) && (__GNUC_MINOR__ > 2)
#  undef __GNUC_MINOR__
#  define __GNUC_MINOR__ 2
#  undef __GNUC_PATCHLEVEL__
#  define __GNUC_PATCHLEVEL__ 0
# endif
#endif


# ifdef __GNUC__
#  define p99_extension __extension__
#  define P99_GCC_VERSION P00_VERSION_NO(__GNUC__, __GNUC_MINOR__, __GNUC_PATCHLEVEL__)
# endif

#ifndef p99_extension
/**
 ** @brief Mark an expression as using a compiler extension.
 **/
# define p99_extension
#endif


#ifndef P00_DOXYGEN
#ifdef __cplusplus
/* C++ as of 1998 is currently not compatible with the macros here. It
   is missing:
   - variate macros
   - compound literals
   - trailing commas in initializers
   - trailing commas in enum declarations
   we test for some of this to see if we have any chance to pass this
   through. Otherwise this should error out early.
 */
# define P00_VA_ARGS__(...) __VA_ARGS__
enum { p00_trailing_comma_in_enum__ = -1, };
inline
signed p00_trailing_comma_in_initializer__(void) {
  signed a[] = { p00_trailing_comma_in_enum__ , };
  return a[0];
}
#else
# if !defined(__STDC_VERSION__) ||  (__STDC_VERSION__ < 199901L)
/* If you come here your compiler is not conforming to C99, since
   this requires the macro __STDC_VERSION__ to be set to the
   indicated value (or larger).

   You still might be able to use P99, but you would have to cheat on
   that value. You are on your own. */
#  error "The P99 preprocessor files need a C99 compliant compiler"
# endif
# if  (!P99_TOK_EQ(1, 1) || P99_TOK_EQ(1, 0))
/* If you come here your preprocessor is not able to expand P99 macros
   correctly. Most probably this is a bug in your preprocessor
   implementation, but it could also be that your implementation just
   interprets the standard different. In any case, we can't
   proceed. */
#  error "The preprocessor is not P99 compatible"
# endif
#endif
#endif

#if !(P99_COMPILER & (P99_COMPILER_CLANG | P99_COMPILER_APPLE))
# ifndef __has_builtin
#  define __has_builtin(X) p00_has_builtin_ ## X  // Compatibility with non-clang compilers.
# endif
# ifndef __has_feature
#  define __has_feature(X) p00_has_feature_ ## X  // Compatibility with non-clang compilers.
# endif
# ifndef __has_extension
#  define __has_extension __has_feature  // Compatibility with non-clang compilers.
# endif
# ifndef __has_attribute
#  define __has_attribute(X) p00_has_attribute_ ## X  // Compatibility with non-clang compilers.
# endif
#endif

#ifndef p99_has_builtin
# define p99_has_builtin(X) (__has_builtin(X) || p00_has_builtin_ ## X)  // Compatibility with non-clang compilers.
# define p99_has_feature(X) (__has_feature(X) || p00_has_feature_ ## X)  // Compatibility with non-clang compilers.
# define p99_has_extension(X) (__has_extension(X) || p00_has_extension_ ## X)  // Compatibility with non-clang compilers.
# define p99_has_attribute(X) (__has_attribute(X) || p00_has_attribute_ ## X)  // Compatibility with non-clang compilers.
#endif

#if P99_COMPILER & P99_COMPILER_OPEN64
# define __GCC_HAVE_SYNC_COMPARE_AND_SWAP_1 1
# define __GCC_HAVE_SYNC_COMPARE_AND_SWAP_2 1
# define __GCC_HAVE_SYNC_COMPARE_AND_SWAP_4 1
# define __GCC_HAVE_SYNC_COMPARE_AND_SWAP_8 1
# define __GNUC_NO_TLS__ 1
#endif

#ifdef _OPENMP
# define p00_has_feature_openmp 1
#endif

#if __GNUC__
# define p00_has_attribute_always_inline 1
# define p00_has_attribute_weak 1
# define p00_has_attribute_weakref 1
# define p00_has_attribute_constructor 1
# define p00_has_attribute_destructor 1
# define p00_has_attribute_vector_size 1
# define p00_has_attribute_warn_unused_result 1
# define p00_has_extension_attribute_const 1
# define p00_has_attribute_pure 1
# if defined(__GNUC_GNU_INLINE__) || (P99_GCC_VERSION < 40300UL)
#  define p00_has_attribute_gnu_inline 1
# endif
# define p00_has_attribute_aligned 1
# define p00_has_attribute_noreturn 1
# define p00_has_attribute___noreturn__ 1
# define p00_has_attribute_deprecated 1
# define p00_has_attribute_unused 1
# ifdef __GCC_HAVE_SYNC_COMPARE_AND_SWAP_4
#  define p00_has_builtin___sync_val_compare_and_swap 1
#  define p00_has_builtin___sync_lock_test_and_set 1
#  define p00_has_builtin___sync_lock_release 1
#  define p00_has_builtin___sync_synchronize 1
#  define p00_has_builtin___sync_fetch_and_add 1
#  define p00_has_builtin___sync_fetch_and_sub 1
#  define p00_has_builtin___sync_fetch_and_or 1
#  define p00_has_builtin___sync_fetch_and_and 1
#  define p00_has_builtin___sync_fetch_and_xor 1
# endif
# if P99_GCC_VERSION >= 30000UL
#  define p00_has_builtin___builtin_expect 1
# endif
//# if P99_GCC_VERSION >= UNKNOWN
//#  define p00_has_feature_c_alignas 1
//# endif
# if P99_GCC_VERSION >= 40300UL
#  define p00_has_attribute_error 1
# endif
# if P99_GCC_VERSION >= 40600UL
#  define p00_has_feature_c_static_assert 1
#  define p00_has_attribute_externally_visible 1
# endif
# if defined(__GNUC_STDC_INLINE__) || P99_GCC_VERSION >= 40300UL
#  define p00_has_feature_c_inline 1
# endif
# define p00_has_feature_gnu_thread_local 1
# define p00_has_feature_gnu_alignof 1
# define p00_has_feature_statement_expression 1
# define p00_has_feature_tgmath_h 1
# define P99_TYPEOF(X) __typeof__(X)
# if (P99_GCC_VERSION >= 40700UL) && (P99_GCC_VERSION < 40900UL)
#  define p00_has_feature_stdnoreturn_h 1
#  define p00_has_feature_stdalign_h 1
#  if __STDC_VERSION__ > 201100L
#   define p00_has_feature_c_max_align_t 1
#   define __STDC_NO_ATOMICS__ 1
#   define p00_has_feature_c_generic_selections 0
#  endif
# endif
# if (P99_GCC_VERSION >= 40900UL) && (P99_GCC_VERSION < 41000UL)
#  define p00_has_feature_stdnoreturn_h 1
#  define p00_has_feature_stdalign_h 1
#  if __STDC_VERSION__ > 201100L
#   define p00_has_feature_c_max_align_t 1
#   define p00_has_feature_c_generic_selections 1
#  endif
# endif
#endif

#if P99_COMPILER & P99_COMPILER_ARMCC
# define p00_has_attribute_always_inline 1
# define p00_has_attribute_weak 1
# define p00_has_attribute_weakref 1
# define p00_has_attribute_deprecated 1
# define p00_has_attribute_aligned 1
# define p00_has_attribute_noreturn 1
# define p00_has_attribute___noreturn__ 1
#endif

#if p99_has_builtin(__sync_val_compare_and_swap)
# ifndef __GCC_HAVE_SYNC_COMPARE_AND_SWAP_1
#  define __GCC_HAVE_SYNC_COMPARE_AND_SWAP_1 1
# endif
# ifndef __GCC_HAVE_SYNC_COMPARE_AND_SWAP_2
#  define __GCC_HAVE_SYNC_COMPARE_AND_SWAP_2 1
# endif
# ifndef __GCC_HAVE_SYNC_COMPARE_AND_SWAP_4
#  define __GCC_HAVE_SYNC_COMPARE_AND_SWAP_4 1
#  if !defined(__GCC_HAVE_SYNC_COMPARE_AND_SWAP_8) && (UINTPTR_MAX >= UINT64_MAX)
#   define __GCC_HAVE_SYNC_COMPARE_AND_SWAP_8 1
#  endif
# endif
#endif


/* Since for the moment C11 support is only very partial, we have to
   introduce some feature test macros. If a compiler claims to be C11
   but doesn't implement a required feature, you have to define the
   corresponding macro to 0 before this point. */
#if __STDC_VERSION__ > 201100L
# ifndef p00_has_feature_stdnoreturn_h
#   define p00_has_feature_stdnoreturn_h 1
# endif
# ifndef p00_has_feature_c_max_align_t
#   define p00_has_feature_c_max_align_t 1
# endif
# ifndef p00_has_feature_c_generic_selections
#  define p00_has_feature_c_generic_selections 1
# endif
#endif

#if P99_COMPILER & (P99_COMPILER_IBM | P99_COMPILER_SUN)
# define p00_has_feature_gnu_thread 1
#elif P99_COMPILER & (P99_COMPILER_MICROSOFT | P99_COMPILER_BORLAND)
# define p00_has_feature_declspec_thread 1
#endif

#if P99_COMPILER & P99_COMPILER_INTEL
# define p99_inline __attribute__((__weak__,__always_inline__))
# if __INTEL_COMPILER < 1310
#  if defined(__GNUC__) && defined(p00_has_feature_tgmath_h)
#   undef p00_has_feature_tgmath_h
#  endif
# else
/* Intel now has a file stdatomic.h, but this is still quite
   incomplete and not yet worth it. */
//#  define p00_has_feature_stdatomic_h 1
# endif

#elif P99_COMPILER & P99_COMPILER_PCC
/* # error "The P99 preprocessor files can't work with the pcc compiler, yet" */

#elif P99_COMPILER & P99_COMPILER_APPLE
/* For a start the properties for the apple clang fake are just copied
   from clang. Adjust once we know more details. */
# if p99_has_attribute(always_inline)
#  define p99_inline __attribute__((__always_inline__)) inline
# endif
/* clang can't nail a variable to a register, yet */
# define P99_FIXED_REGISTER(REG)
/* clang has no stdatomic.h, yet */
# define __STDC_NO_ATOMICS__ 1

#elif P99_COMPILER & P99_COMPILER_CLANG
# if p99_has_attribute(always_inline)
#  define p99_inline __attribute__((__always_inline__)) inline
# endif
/* clang can't nail a variable to a register, yet */
# define P99_FIXED_REGISTER(REG)
/* clang has no stdatomic.h, yet. It can't use the one from gcc, since
   that (gratuously) uses __auto_type. */
# if P99_VERSION_NO < 100000UL
#  define __STDC_NO_ATOMICS__ 1
# endif
# if P99_VERSION_NO > 30200UL
#  define p00_has_feature_stdnoreturn_h 1
# endif
/* stdalign.h exists but is not usable, at least up to 3.2 */
//# if P99_VERSION_NO >= 30000UL
//#  define p00_has_feature_stdalign_h 1
//# endif

#elif P99_COMPILER & (P99_COMPILER_GNU | P99_COMPILER_OPEN64)
# define P99_ATLEAST
/* gcc prior to version 4.2.1 has the inline keyword but with slightly
   different semantics.
   Be sure to always inline functions in this cases.
   */
# if !p99_has_feature(c_inline)
#  ifdef inline
#   undef inline
#  endif
#  if p99_has_attribute(gnu_inline)
#   define inline __attribute__((__gnu_inline__,__weak__)) __inline__
#   define p99_inline __attribute__((__always_inline__,__gnu_inline__,__weak__)) __inline__
#  else
#   define inline __attribute__((__weak__)) __inline__
#   define p99_inline __attribute__((__always_inline__,__weak__)) __inline__
#  endif
#  define static_inline static __inline__
#  if p99_has_attribute(externally_visible)
#   define p00_instantiate __attribute__((__externally_visible__))
#  else
#   define p00_instantiate
#  endif
# else
#  define inline __inline__
#  if p99_has_attribute(externally_visible)
#   define p00_instantiate __attribute__((__externally_visible__)) extern __inline__
#  else
#   define p00_instantiate extern __inline__
#  endif
#  define p99_inline __attribute__((__always_inline__)) __inline__
# endif
#endif

# if !defined(static_inline) || defined(P00_DOXYGEN)
#  define static_inline static inline
# endif
# if !defined(p99_inline) || defined(P00_DOXYGEN)
/**
 ** @brief Try to force a function always to be inlined
 **
 ** Since there is no default language construct to ensure this, this
 ** will always only be an approximation depending on the compiler.
 **
 ** The functions that are defined by P99 itself are declared/defined
 ** with this.
 **/
#  define p99_inline static inline
# endif

#ifdef P00_FORCE_NOINLINE
# undef p99_inline
# define p99_inline
#endif


# ifndef p00_instantiate
/**
 ** @brief Force a function symbol to be emitted.
 **
 ** The default that is used for this is to add the keywords
 ** <code>extern inline</code>. By that the definition that has been
 ** seen in this unit is not an @c inline definition and thus the
 ** function is generated and a symbol is emitted.
 **/
#  if p99_has_attribute(externally_visible)
#   define p00_instantiate __attribute__((__externally_visible__)) extern __inline__
#  else
#   define p00_instantiate extern __inline__
#  endif
# endif

#if p99_has_attribute(weak)
# define P00_WEAK1(ID) __attribute__((__weak__))
#elif P99_COMPILER & P99_COMPILER_MICROSOFT
# define P00_WEAK1(ID) __declspec(selectany)
#else
# define P00_WEAK1(ID) _Pragma(P99_STRINGIFY(weak ID))
#endif

#if p99_has_attribute(weakref)
# define P00_WEAK2(ID, ...) __attribute__((__weakref__(#__VA_ARGS__)))
#else
# define P00_WEAK2(ID, ...) _Pragma(P99_STRINGIFY(weak ID=__VA_ARGS__))
#endif

/**
 ** @brief Declare a symbol to be weak such that it can be provided
 ** several times without error.
 **
 ** This should be placed before the corresponding declaration and
 ** receive the name of the symbol as an argument. Such as
 **
 ** @code
 ** P99_WEAK(toto)
 ** unsigned toto;
 ** @endcode
 **
 ** To have maximum portability this should immediately precede the
 ** definition. Another form would be
 **
 ** @code
 ** P99_WEAK(func, _func)
 ** unsigned func(void);
 ** @endcode
 **
 ** By that all references to @c func would use @c _func, instead.
 **
 ** @remark This feature seems to be widely supported. We have seen
 ** it mentioned for gcc and relatives, IBM, SGI, HP, SUN, Diab,
 ** Microsoft
 **/
# define P99_WEAK(...) P99_IF_LT(P99_NARG(__VA_ARGS__), 2)(P00_WEAK1(__VA_ARGS__))(P00_WEAK2(__VA_ARGS__))

#ifndef P99_TENTATIVE_CAUTION
# define P00_TENTATIVE_DEC(NAME) static
# define P00_TENTATIVE_DEF(NAME) static
#else
# define P00_TENTATIVE_DEC(NAME) P99_WEAK(NAME)
# define P00_TENTATIVE_DEF(NAME)
#endif

/**
 ** @brief A tentative declaration of an object @a NAME of type @a T
 **
 ** On most platforms this should just result in
 ** @code
 ** static T NAME
 ** @endcode
 **
 ** so a declaration of @a NAME that is also a tentative
 ** definition. Such a beast is suitable to provide a default value of
 ** @c 0 for @a NAME, that can at any point in the same compilation
 ** unit be overwritten by a user specified value.
 **
 ** @see P99_TENTATIVE_DEF for the corresponding definition that
 ** should provide a value through initialization.
 **/
# define P99_TENTATIVE_DEC(T, NAME)                            \
P00_TENTATIVE_DEC(NAME) T NAME

# define P99_TENTATIVE_DEF(T, NAME)                            \
P00_TENTATIVE_DEF(NAME) T NAME

/**
 ** @brief On architectures that support this, warn if the result of a
 ** function is not used.
 **/
#if p99_has_attribute(warn_unused_result) && defined(P99_WARN_UNUSED_RESULT)
# undef P99_WARN_UNUSED_RESULT
# define P99_WARN_UNUSED_RESULT __attribute__((__warn_unused_result__))
#else
# undef P99_WARN_UNUSED_RESULT
# define P99_WARN_UNUSED_RESULT
#endif

/**
 ** @brief On architectures that support this, assert that a function
 ** is "pure", i.e only depends on parameters and global variables.
 **/
#if p99_has_attribute(pure)
# define P99_PURE_FUNCTION __attribute__((__pure__))
#else
# define P99_PURE_FUNCTION
#endif

/**
 ** @brief On architectures that support this, assert that a function
 ** is "const", i.e only depends on parameters and global variables.
 **/
#if p99_has_extension(attribute_const)
# define P99_CONST_FUNCTION __attribute__((__const__))
#else
# define P99_CONST_FUNCTION
#endif

#if p99_has_feature(setjmp_inline)
# define P99_SETJMP_INLINE(NAME) p99_inline
#else
# define P99_SETJMP_INLINE(NAME) P99_WEAK(NAME)
#endif


#ifndef P99_FIXED_REGISTER
# ifdef __GNUC__
#  define P99_FIXED_REGISTER(REG) __asm__(P99_STRINGIFY(REG))
# else
/**
 ** @brief Fix a variable to a specific register, if the platform
 ** supports this.
 **
 **/
#  define P99_FIXED_REGISTER(REG)
# endif
#endif


/**
 ** @}
 **/

/* Now that feature test macros are set up we may check for the
   library support. */
#include "p99_libc.h"


/**
 ** @addtogroup C11 Emulating features of C11
 **
 ** The new C standard C11 (published in December 2011) introduces
 ** some new features that are already present in many compilers or
 ** OS, but sometimes with different syntax or interfaces. We provide
 ** interfaces to some of them with the intention that once compilers
 ** that implement C11 are released, these interfaces can directly relate
 ** to the C11 feature.
 **
 ** @{
 **/

/**
 ** @addtogroup C11_keywords Some new C11 keywords
 **
 ** @{
 **/


#ifndef static_assert
/**
 ** @brief Evaluate expression @a EXPR at compile time and ensure that
 ** it is fulfilled.
 **
 ** The expression must be given as the first argument. The second
 ** argument is a diagnostic string that should be part of the
 ** diagnostic message when the assertion fails.
 **
 ** Not all compilers give a useful message when an assertion is not
 ** fulfilled, but all should give at least the line number and stop
 ** compilation.
 **
 ** @remark This functionality will be directly supported in C11 and
 ** the macro ::static_assert must be provided by assert.h, which we
 ** include.
 **/
# if p99_has_feature(c_static_assert)
#  define static_assert _Static_assert
# else
#  define static_assert(EXPR, DIAGSTR)                            \
extern char const p00_compiletime_assert[                         \
 sizeof((void const*[3*(!!(EXPR)) - 1]){                          \
    &p00_compiletime_assert,                                      \
   "static assertion failed: " P99_STRINGIFY(EXPR) ", " DIAGSTR}) \
]
extern char const p00_compiletime_assert[sizeof(void const*[2])];
# endif
#endif

#if P99_COMPILER & (P99_COMPILER_CLANG | P99_COMPILER_GNU | P99_COMPILER_OPEN64)
# if defined(__LONG_MAX__) && defined(__LONG_LONG_MAX__) && (P99_GCC_VERSION >= 30000UL)
#  if defined(__SIZEOF_INT128__)
#   define p99x_uintmax p99x_uintmax
#   define p99x_intmax p99x_intmax
#   define p99x_uint128 p99x_uint128
#   define p99x_int128 p99x_int128
typedef __uint128_t p99x_uintmax;
typedef __int128_t p99x_intmax;
typedef __uint128_t p99x_uint128;
typedef __int128_t p99x_int128;
#  endif
# endif
#endif

/**
 ** @brief Return the alignment requirement for type @a T
 **
 ** @remark If this is not provided a gcc extension is used. If no such extension
 ** is provided, a hack through the @c offsetof
 ** macro is used. For the later, @a T is restricted to simple type names.
 ** Arrays or function pointers can only be used through @c typedef.
 **/
#ifndef __alignof_is_defined
# define alignof _Alignof
# if !p99_has_feature(c_alignof)
#  if p99_has_feature(gnu_alignof)
#   ifndef _Alignof
#    define _Alignof(T) __alignof__(T)
#   endif
#  else
#   define _Alignof(T) offsetof(struct { char p00_c; T p00_t; }, p00_t)
#  endif
# endif
#endif

/**
 ** @brief Align an object according to @a X
 **
 ** @remark If this is not provided by the compiler implementation
 ** a gcc extension is used. Other than required by C11, this
 ** extension only accepts numerical values for @a X.
 **/
#ifndef __alignas_is_defined
# define alignas _Alignas
# if !p99_has_feature(c_alignas)
#  if p99_has_attribute(aligned)
#   ifndef _Alignas
#    define _Alignas(X) __attribute__((__aligned__(X)))
#   endif
#  endif
# endif
#endif

/**
 ** @brief A type with the maximum alignment among the standard types.
 **
 ** This type is required for C11. We achieve this feature by simply
 ** producing a @c union of all the standard types, object
 ** and function pointer types, @a struct and @a union.
 **
 ** If it is provided, we additionally use a gcc extension to
 ** determine such a maximal alignment.
 **
 ** @remark The actual declaration of this type should never be used
 ** for any other purpose than to ensure alignment. The field names
 ** are obfuscated to make such abuses really difficult.
 **/
#if !p99_has_feature(c_max_align_t) && !p99_has_extension(c_max_align_t)
typedef union max_align_t max_align_t;
# ifndef P00_DOXYGEN
union max_align_t {
  struct P99_PASTE2(p00_, __LINE__) {
    unsigned P99_PASTE2(p00_, __LINE__);
  } P99_PASTE2(p00_, __LINE__);
  union max_align_t* P99_PASTE2(p00_, __LINE__);
  void* P99_PASTE2(p00_, __LINE__);
  void (*P99_PASTE2(p00_, __LINE__))(void);
  _Bool P99_PASTE2(p00_, __LINE__);
  char P99_PASTE2(p00_, __LINE__);
  signed char P99_PASTE2(p00_, __LINE__);
  unsigned char P99_PASTE2(p00_, __LINE__);
  short int P99_PASTE2(p00_, __LINE__);
  unsigned short int P99_PASTE2(p00_, __LINE__);
  int P99_PASTE2(p00_, __LINE__);
  unsigned int P99_PASTE2(p00_, __LINE__);
  long int P99_PASTE2(p00_, __LINE__);
  unsigned long int P99_PASTE2(p00_, __LINE__);
  long long int P99_PASTE2(p00_, __LINE__);
  unsigned long long int P99_PASTE2(p00_, __LINE__);
  float P99_PASTE2(p00_, __LINE__);
  double P99_PASTE2(p00_, __LINE__);
  long double P99_PASTE2(p00_, __LINE__);
#  ifndef __STDC_NO_COMPLEX__
  float _Complex P99_PASTE2(p00_, __LINE__);
  double _Complex P99_PASTE2(p00_, __LINE__);
  long double _Complex P99_PASTE2(p00_, __LINE__);
#  endif
#  ifdef p99x_uint128
  p99x_uint128 P99_PASTE2(p00_, __LINE__);
#  endif
#  ifdef UINT128_MAX
  uint128_t P99_PASTE2(p00_, __LINE__);
#  endif
}
#  if p99_has_attribute(aligned)
__attribute__((__aligned__))
#  endif
;
# endif
#endif

#undef p00_has_feature_c_max_align_t
#define p00_has_feature_c_max_align_t 1
#undef p00_has_extension_c_max_align_t
#define p00_has_extension_c_max_align_t 1

#ifdef P00_DOXYGEN
/**
 ** @def _Noreturn
 ** @brief Declare a function that doesn't return to the caller.
 **
 ** You'd probably use this rarely, and only for functions that use
 ** something like @c longjmp, @c exit, @c abort, ::quick_exit or
 ** ::thrd_exit under the hood.
 **
 ** @remark Uses a gcc attribute for the implementation or defers to a
 ** @c #pragma if that is not available.
 ** @see noreturn
 **/
#define _Noreturn
/**
 ** @def noreturn
 ** @brief Declare a function that doesn't return to the caller.
 **
 ** @see _Noreturn
 **/
#define noreturn

noreturn void p00_f(void);
static_assert(1);

#elif !defined(noreturn)
# define noreturn _Noreturn
#endif

#ifdef P00_DOXYGEN
#elif !p99_has_feature(c_noreturn)
# if p99_has_attribute(__noreturn__)
#  ifndef _Noreturn
#   define _Noreturn __attribute__((__noreturn__))
#  endif
# elif p99_has_feature(pragma_noreturn)
#  define _Noreturn _Pragma(NORETURN)
# else
#  define _Noreturn /* noreturn feature is not implemented */
# endif
#endif

/* Patch a flaw in OS X. They use __attribute__((noreturn)) which
   explodes if noreturn is defined. */
#ifdef __APPLE__
# undef __dead2
# define __dead2 __attribute__((__noreturn__))
#endif

#ifdef P00_DOXYGEN
/**
 ** @def _Thread_local
 ** @brief The C11 keyword for declaring a thread-local variable.
 **
 ** @see P99_DECLARE_THREAD_LOCAL for a method that is also usable for non-C11 compilers
 ** @see thread_local
 **/
# define _Thread_local
/**
 ** @def thread_local
 ** @brief Declare a thread-local variable.
 **
 ** @see P99_DECLARE_THREAD_LOCAL for a method that is also usable for non-C11 compilers
 ** @see _Thread_local
 **/
# define thread_local
#elif !defined(thread_local)
# define thread_local _Thread_local
# if p99_has_feature(gnu_thread_local)
#  define _Thread_local __thread
# elif p99_has_feature(declspec_thread)
#  define _Thread_local __declspec(thread)
# endif
#endif

static_assert(1, "test of static assertions");

/**
 ** @}
 **/

/**
 ** @}
 **/

/**
 ** @addtogroup compiler_utilities A small collection of utilities
 **
 ** @{
 **/

#define P00_HARMLESS_SIZEOF(ID) sizeof(sizeof(ID))

#if p99_has_attribute(unused)
# define P00_UNUSED(EXPR)                                      \
  extern char const p00_harmless_declaration                   \
  [P00_HARMLESS_SIZEOF(EXPR)] __attribute__((__unused__))
#else
# define P00_UNUSED(EXPR)                                      \
  extern char const p00_harmless_declaration                   \
  [P00_HARMLESS_SIZEOF(EXPR)]
#endif

/* Used inside P99_MACRO_END. The idea that this is an extern
   declaration, so it doesn't result in any code. On the other hand it
   uses the address of itself in its own declaration, so the compiler
   shouldn't issue a warning about an unused variable. */
#define P00_HARMLESS_DECLARATION P00_UNUSED(p00_harmless_declaration)

/* To be able to refer to it in a sizeof expression this must be
   forward declared. */
P00_UNUSED(1);

/**
 ** @brief A meta macro that forces the addition of a semicolon after
 ** a call to the macro that it terminates.
 **
 ** This should only be used for macros that replace declarations.
 **/
#define P99_MACRO_END(...)                                          \
extern void P99_PASTE(p00_harmless_declaration_, __VA_ARGS__)(void)


/**
 ** @brief A token sequence that can be used in a @c #pragma directive
 ** to indicate a parallel for-loop.
 **
 ** When using this in a @c #pragma, the resulting code may then be
 ** parallelized and (if the platform
 ** supports this) multiple threads may be used to speed up
 ** execution. This will only be effective if your compiler supports
 ** the <a href="http://openmp.org/wp/">Open Multi-Processing</a>
 ** extension (OpenMP for short, or OMP even shorter) and you enabled its
 ** use.
 **/
#if p99_has_feature(openmp)
#define P99_PARALLEL_PRAGMA omp parallel for
#else
#define P99_PARALLEL_PRAGMA
#endif

/**
 ** @def P99_EXPECT
 ** @brief Provide a compiler hint concerning the likelihood of a
 ** certain value in an expression @a EXP.
 **
 ** With this you indicate that in the overwhelming number of cases
 ** the integer expression @a EXP will evaluate to @a VAL.
 **
 ** Currently this is only implemented for gcc and related.
 **/
#if p99_has_builtin(__builtin_expect)
# define P99_EXPECT(EXP, VAL) __builtin_expect((EXP), (VAL))
#else
# define P99_EXPECT(EXP, VAL) (EXP)
#endif

/**
 ** @brief Mark the conditional expression as being unlikely
 **
 ** This can be useful e.g to test returns of system functions. Many
 ** of these return @c 0 if everything goes well and something else
 ** otherwise.
 **
 ** Use with care, as humans are particularly bad at branch
 ** prediction. If unsure, first test your conditional for some time
 **
 ** to see that the case is really as unlikely as you think.
 ** @see P99_EXPECT
 ** @see P99_LIKELY
 **/
#ifndef P99_UNLIKELY
# define P99_UNLIKELY(...) P99_EXPECT(!!(__VA_ARGS__), 0)
#endif

/**
 ** @brief Mark the conditional expression as being likely
 **
 ** This can be useful e.g to test the return value of @c printf.
 **
 ** Use with care, as humans are particularly bad at branch
 ** prediction. If unsure, first test your conditional for some time
 ** to see that the case is really as likely as you think.
 **
 ** @see P99_EXPECT
 ** @see P99_UNLIKELY
 **/
#ifndef P99_LIKELY
# define P99_LIKELY(...) P99_EXPECT(!!(__VA_ARGS__), 1)
#endif


/**
 ** @def P99_DEPRECATED
 ** @brief Deprecate a declaration that is given as the argument list.
 **/
#if p99_has_attribute(deprecated)
# define P99_DEPRECATED(...) /*! \deprecated __VA_ARGS__ */ __attribute__((__deprecated__))
#else
# define P99_DEPRECATED(...) /*! \deprecated __VA_ARGS__ */
#endif

/**
 ** @def P99_ATLEAST
 ** @brief Specify for array parameters that they have a least a given number of elements.
 **
 ** This is an addition through an abuse of the @c static keyword that
 ** older compilers might not support.
 **/
#ifndef P99_ATLEAST
# define P99_ATLEAST static
#endif


/**
 ** @brief A wrapper for vector type extensions
 **
 ** This implements a vector of @a N elements of type @a T. On
 ** platforms that support this directly such vectors then can be used
 ** twofold. They can be accessed as arrays through indexing with @c
 ** [] and they can be used with the standard operators such as @c +,
 ** @c * etc.
 **
 ** On platforms that don't support this type of extension this
 ** expands to an array declaration with special alignment
 ** properties. On such platforms such a "vector" can only be used for
 ** declarations of variables or function parameters, but not as
 ** types.
 **/
P00_DOCUMENT_TYPE_ARGUMENT(P99_VECTOR, 0)
P00_DOCUMENT_IDENTIFIER_ARGUMENT(P99_VECTOR, 1)
P00_DOCUMENT_NUMBER_ARGUMENT(P99_VECTOR, 2)
#if p99_has_attribute(vector_size)
# define P99_VECTOR(T, NAME, N) T NAME __attribute__((vector_size(sizeof(T)*(N))))
#else
# define P99_VECTOR(T, NAME, N) _Alignas(sizeof(T)*(N)) T NAME[N]
#endif

/**
 ** @brief Issue the pragma that is given as a supplementary argument
 ** iff the actual compiler is @a COMP.
 ** @see P99_COMPILER
 **/
#define P99_IF_COMPILER(COMP, ...) P00_COMPILER_PRAGMA_ ## COMP(P99_STRINGIFY(__VA_ARGS__))

#ifndef P00_DOXYGEN

/* Disable bogus warnings that are provoked by the code in this file. */

P99_IF_COMPILER(INTEL, warning(disable: 1418)) /* external function definition with no prior declaration */
P99_IF_COMPILER(INTEL, warning(disable: 1419)) /* external declaration in primary source file */
P99_IF_COMPILER(INTEL, warning(disable: 557))  /* pointless comparison of unsigned integer with a negative constant */
P99_IF_COMPILER(INTEL, warning(disable: 283))  /* duplicate specifier in declaration */

/* Warnings on initializers are a plague. They are responsible for the
   fact that many people don't use default initializers where they
   could and should. Shame on gcc and Co that they enable this with
   -Wall. */

P99_IF_COMPILER(GNU, GCC diagnostic ignored "-Wmissing-braces")
P99_IF_COMPILER(GNU, GCC diagnostic ignored "-Wmissing-field-initializers")

P99_IF_COMPILER(OPEN64, GCC diagnostic ignored "-Wmissing-braces")
P99_IF_COMPILER(OPEN64, GCC diagnostic ignored "-Wmissing-field-initializers")

/* clang warns about features that are completely ok. */
P99_IF_COMPILER(CLANG, GCC diagnostic ignored "-Wnon-literal-null-conversion")
P99_IF_COMPILER(CLANG, GCC diagnostic ignored "-Wswitch-bool")

/**
 ** @def P99_WARN_INIT_PUSH
 ** @brief Switch bogus warnings about initializers off.
 ** @remark If available this uses compiler specific
 ** features. Otherwise this just ignored
 **/

/**
 ** @def P99_WARN_INIT_POP
 ** @brief Switch bogus warnings about initializers on again.
 ** @remark If available this uses compiler specific
 ** features. Otherwise this just ignored
 **/

#if P99_COMPILER & P99_COMPILER_CLANG
#define P99_WARN_INIT_PUSH                                        \
P99_PRAGMA(GCC diagnostic push)                                   \
P99_PRAGMA(GCC diagnostic ignored "-Wmissing-braces")             \
P99_PRAGMA(GCC diagnostic ignored "-Wmissing-field-initializers") \
P99_PRAGMA(GCC diagnostic ignored "-Winitializer-overrides")
#define P99_WARN_INIT_POP P99_PRAGMA(GCC diagnostic pop)
#endif

#ifndef P99_WARN_INIT_PUSH
# define P99_WARN_INIT_PUSH
#endif

#ifndef P99_WARN_INIT_POP
# define P99_WARN_INIT_POP
#endif

/**
 ** @def P99_WARN_REDUNDANT_DECLS_PUSH
 ** @brief Switch bogus warnings about redundant declarations off.
 ** @remark If available this uses compiler specific
 ** features. Otherwise this just ignored
 **/

/**
 ** @def P99_WARN_REDUNDANT_DECLS_POP
 ** @brief Switch bogus warnings about redundant declarations on again.
 ** @remark If available this uses compiler specific
 ** features. Otherwise this just ignored
 **/

#if P99_COMPILER & (P99_COMPILER_GNU | P99_COMPILER_CLANG)
#define P99_WARN_REDUNDANT_DECLS_PUSH                          \
P99_PRAGMA(GCC diagnostic push)                                \
P99_PRAGMA(GCC diagnostic ignored "-Wredundant-decls")
#define P99_WARN_REDUNDANT_DECLS_POP P99_PRAGMA(GCC diagnostic pop)
#endif

#ifndef P99_WARN_REDUNDANT_DECLS_PUSH
# define P99_WARN_REDUNDANT_DECLS_PUSH
#endif

#ifndef P99_WARN_REDUNDANT_DECLS_POP
# define P99_WARN_REDUNDANT_DECLS_POP
#endif

#endif

/** @}
 **/


/** @}
 **/

#endif
