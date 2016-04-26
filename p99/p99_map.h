/* This may look like nonsense, but it really is -*- mode: C -*-              */
/*                                                                            */
/* Except for parts copied from previous work and as explicitly stated below, */
/* the authors and copyright holders for this work are as follows:            */
/* (C) copyright  2010-2014 Jens Gustedt, INRIA, France                       */
/* (C) copyright  2012 William Morris                                         */
/*                                                                            */
/* This file is free software; it is part of the P99 project.                 */
/* You can redistribute it and/or modify it under the terms of the QPL as     */
/* given in the file LICENSE. It is distributed without any warranty;         */
/* without even the implied warranty of merchantability or fitness for a      */
/* particular purpose.                                                        */
/*                                                                            */
#ifndef     P99_MAP_H_
# define    P99_MAP_H_

/**
 ** @file
 ** @brief macros to produce lists of statements or declarations.
 ** @see statement_lists
 **/

#include "p99_for.h"

/** @addtogroup statement_lists Produce C99 statements or expression lists
 **
 ** This provides tools to produce a list of declarations (e.g @c
 ** typedef), list of initializers or perform a sequence of additions
 ** or other operations. The input usually is just a list of names, e.g.
 **
 ** @{
 **/


#define P00_ACCESSOR(NAME, X, I) P99_IF_EMPTY(NAME)([I])((NAME)[I])
#define P00_VASSIGN(NAME, X, I) X = P00_ACCESSOR(NAME, X, I)
#define P00_STRLEN(NAME, X, I) strlen(X)
#define P00_SIZEOF(NAME, X, I) sizeof(X)
#define P00_TYPD(NAME, X, I) typedef X P99_PASTE2(NAME, I)
#define P00_DESIGNATE(NAME, X, I) X = (NAME)X
#define P00_ADD(NAME, I, REC, RES) P99_ADD(RES, REC)

#define P00_STRLENS(N, ...) P99_FOR(,N, P00_SUM, P00_STRLEN, __VA_ARGS__)
#define P00_SIZEOFS(N, ...) P99_FOR(,N, P00_SUM, P00_SIZEOF, __VA_ARGS__)
#define P00_ADDS(N, ...) P99_FOR(, N, P00_ADD, P00_IDT, __VA_ARGS__)

#define P00_POW0(X, _1, _2) (X)
#define P00_POW(X, _1, REC, _3) (X) * REC

/**
 ** @brief Compute the @a N<sup>th</sup> multiplicative integer power of @a X.
 **
 ** @a N must be a decimal constant without suffixes. The value @c 0
 ** is special in that it evaluates to a @c 1 that is promoted to the
 ** promoted type of @a X.
 **/
P00_DOCUMENT_NUMBER_ARGUMENT(P99_IPOW, 0)
P00_DOCUMENT_MULTIPLE_ARGUMENT(P99_IPOW, 1)
#define P99_IPOW(N, X) P99_IF_EQ(N,0)(P99_SIGN_PROMOTE(1, X))((P99_FOR(X, N, P00_POW, P00_POW0, P99_REP(N,))))

/**
 ** @brief Return an expression that returns the sum of the lengths of
 ** all strings that are given as arguments.
 **/
#define P99_STRLENS(...) P00_STRLENS(P99_NARG(__VA_ARGS__),__VA_ARGS__)

/**
 ** @brief Return an expression that returns the sum of the size of
 ** all arguments.
 **/
#define P99_SIZEOFS(...) P00_SIZEOFS(P99_NARG(__VA_ARGS__),__VA_ARGS__)

/**
 ** @brief Return a token that is the sum of all arguments.
 **/
#define P99_ADDS(...) P00_ADDS(P99_NARG(__VA_ARGS__),__VA_ARGS__)

#ifndef P00_DOXYGEN
P99_DECLARE_STRUCT(p00_strcat_state);
#endif

struct p00_strcat_state {
  char*restrict p00_buf;
  char*restrict p00_pos;
};

#if _XOPEN_SOURCE >= 700 || _POSIX_C_SOURCE >= 200809L
p99_inline
char *p00_stpcpy(char *restrict p00_des, const char *restrict p00_src) {
  return stpcpy(p00_des, p00_src);
}
#else
p99_inline
char *p00_stpcpy(char *restrict p00_des, const char *restrict p00_src) {
  for (;;) {
    *p00_des = *p00_src;
    if (!*p00_src) break;
    ++p00_des; ++p00_src;
  }
  return p00_des;
}
#endif


p99_inline
p00_strcat_state* p00_strcat(p00_strcat_state *restrict p00_des, char const*restrict p00_src) {
  if (!p00_des->p00_pos) p00_des->p00_pos = strchr(p00_des->p00_buf, 0);
  p00_des->p00_pos = p00_stpcpy(p00_des->p00_pos, p00_src);
  return p00_des;
}

p99_inline
char* p00_strcat_terminate(p00_strcat_state *restrict p00_des) {
  return p00_des->p00_buf;
}

/**
 ** @brief Append all argument strings after @a TARG to @a TARG.
 **
 ** @a TARG should be compatible with @c char* and must provide enough
 ** space to hold the concatenation of all strings. The remaining
 ** arguments must be compatible with @c const char*.
 **
 ** This macro ensures linear complexity in the operation. In
 ** particular each position in the argument strings is accessed at
 ** most twice, once by a call to strlen and once by a call to
 ** memcpy.
 **
 ** This uses some small inlined helper functions, since the repeated
 ** use of bare @c strcat would have quadratic complexity.
 **
 ** The resulting replacement produced by this macro evaluates
 ** each of the arguments at most once.
 **/
#define P99_STRCATS(TARG, ...)                                 \
p00_strcat_terminate                                           \
(P99_BIGFUNC                                                   \
 (p00_strcat,                                                  \
  P99_NARG(TARG, __VA_ARGS__),                                 \
  (&(p00_strcat_state){ .p00_buf = (TARG), .p00_pos = 0  }),   \
   __VA_ARGS__))

/**
 ** @brief Concatenate all arguments.
 **
 ** All arguments must be strings for which the length can be computed
 ** at compile time.
 **
 ** @return a temporary string that is valid in the containing block
 ** of the expression holding the call to this macro.
 **
 ** @see P99_STRDUP for a variant that returns a @c malloc'ed string and
 ** thus can be called with any type of @c char* arguments.
 **/
P00_DOCUMENT_PERMITTED_ARGUMENT(P99_JOIN, 0)
P00_DOCUMENT_PERMITTED_ARGUMENT(P99_JOIN, 1)
P00_DOCUMENT_PERMITTED_ARGUMENT(P99_JOIN, 2)
#define P99_JOIN(...) P99_STRCATS((char[P99_SIZEOFS(__VA_ARGS__) + 1]){ 0 }, __VA_ARGS__)

/**
 ** @brief Concatenate all arguments.
 **
 ** @return a string that must be freed by @c free
 **
 ** The resulting replacement produced by this macro evaluates
 ** each of the arguments twice; once to compute the overall length of
 ** the new string and then again for the duplication operation.
 **/
P00_DOCUMENT_MULTIPLE_ARGUMENT(P99_STRDUP, 0)
P00_DOCUMENT_MULTIPLE_ARGUMENT(P99_STRDUP, 1)
P00_DOCUMENT_MULTIPLE_ARGUMENT(P99_STRDUP, 2)
#define P99_STRDUP(...) P99_STRCATS(calloc(P99_STRLENS(__VA_ARGS__) + 16, 1), __VA_ARGS__)

/**
 ** @brief Produce a list of length @a N that has the contents of 0,
 ** 1, , @a N-1
 **/
P00_DOCUMENT_NUMBER_ARGUMENT(P99_POSS, 0)
#define P99_POSS(N) P99_FOR(,N, P00_SEQ, P00_POS,)


#define P00_ACCESSORS(X, ...) P99_FOR(X, __VA_ARGS__, P00_SEQ, P00_ACCESSOR, )

/**
 ** Produce a list of length @a N that has the contents of @a X[0], @a
 ** X [1], ,
 ** @a X[@a N-1]
 **/
P00_DOCUMENT_MULTIPLE_ARGUMENT(P99_ACCESSORS, 0)
P00_DOCUMENT_NUMBER_ARGUMENT(P99_ACCESSORS, 1)
#define P99_ACCESSORS(X, N) P00_ACCESSORS(X, N)


/**
 ** @brief Vector-assign to a list
 **
 ** Produce a list of length @c N that has the contents of @c V0 = @a
 ** NAME[0], @c V1 = @a NAME[1], ..., @c VN-1 = @a NAME[@a N-1], where
 ** V0, etc are the remaining arguments.
 **/
P00_DOCUMENT_MULTIPLE_ARGUMENT(P99_VASSIGNS, 0)
#define P99_VASSIGNS(NAME, ...)                                            \
P99_IF_LT(P99_NARG(__VA_ARGS__),2)                                         \
(P99_IF_VOID(__VA_ARGS__)((void)0)(__VA_ARGS__ = (NAME)[0]))               \
  (P99_FOR(NAME, P00_NARG(__VA_ARGS__),P00_SEP, P00_VASSIGN, __VA_ARGS__))

#define P00_TYPEDEFS(NAME, N, ...)                             \
  P99_IF_VOID(__VA_ARGS__)                                     \
  (P99_MACRO_END(NAME, _eat_the_semicolon_, N))                \
  (P99_FOR(NAME, N, P00_SEP, P00_TYPD, __VA_ARGS__))

/**
 ** @brief Take each argument on the list and transform it into a
 ** @c typedef of name NAME_0, NAME_1, etc.
 **
 ** Due to syntax problems this can't be used for function or
 ** array type derivatives.
 **/
#define P99_TYPEDEFS(NAME, ...)                                \
P00_TYPEDEFS(NAME, P99_NARG(__VA_ARGS__), __VA_ARGS__)

#define P00_DESIGNATED(VAR, N, ...) P99_FOR(VAR, N, P00_SEQ, P00_DESIGNATE, __VA_ARGS__)

/**
 ** @brief Construct a designated initializer by copying fields of @a VAR.
 **
 ** The argument list must be composed of designators, something like
 ** @code
 ** struct toto { int a; int b; } A = { .a = 9, .b = 7 };
 ** struct toto B = P99_DESIGNATED(A, .b);
 ** double C[4] = { 1, 2, 3, 4 };
 ** double D[4] = P99_DESIGNATED(C, [0], [2]);
 ** @endcode
 **
 ** So here @c B.b is initialized with the value of @c A.b and @c B.a,
 ** since @c .a is not in the list, is initialized by 0. Likewise @c D
 ** gets copies of @c C[0] and @c C[2] and the other fields are
 ** initialized to @c 0.
 ** @see P99_LCOPY
 **/
P00_DOCUMENT_MULTIPLE_ARGUMENT(P99_DESIGNATED, 0)
P00_DOCUMENT_DESIGNATOR_ARGUMENT(P99_DESIGNATED, 1)
P00_DOCUMENT_DESIGNATOR_ARGUMENT(P99_DESIGNATED, 2)
P00_DOCUMENT_DESIGNATOR_ARGUMENT(P99_DESIGNATED, 3)
#define P99_DESIGNATED(VAR, ...) { P00_DESIGNATED(VAR, P99_NARG(__VA_ARGS__), __VA_ARGS__) }

/**
 ** @brief Expand to an array initializer copying array @a VAR for @a N positions.
 **
 ** This can be used to initialize an array with a designated
 ** initializer that is derived from another array.
 ** @code
 ** double B[] = P99_ADESIGNATED(A, 3);
 ** @endcode
 **
 ** Would initialize @c B to be an array of 3 @c double that are
 ** copies of the first three values of @c A.
 **/
#define P99_ADESIGNATED(VAR, N) P99_DESIGNATED(VAR, P99_ACCESSORS(, N))

/**
 ** @brief Construct a compound literal of type @a TYPE by copying fields of @a VAR.
 **
 ** The argument list must be composed of designators, something like
 ** @code
 ** struct toto { int a; int b; } A = { .a = 9, .b = 7 };
 ** struct toto B = P99_LCOPY(struct toto, A, .b);
 ** double C[4] = { 1, 2, 3, 4 };
 ** double *D = P99_LCOPY(double[4], C, [0], [2]);
 ** @endcode
 **
 ** So here @c B.b is initialized with the value of @c A.b and @c B.a,
 ** since @c .a is not in the list, is initialized by 0. Likewise @c D
 ** gets copies of @c C[0] and @c C[2] and the other fields are
 ** initialized to @c 0.
 **
 ** This is probably best used indirectly inside a type specific
 ** macro. E.g if you know that the copy operation for @c toto as
 ** above should always copy only @c .b and not @c .a you could do
 ** @code
 ** #define TOTO_LCOPY(A) P99_LCOPY(struct toto, A, .b);
 ** struct toto B = TOTO_LCOPY(A);
 ** @endcode
 ** @see P99_DESIGNATED
 **/
P00_DOCUMENT_MULTIPLE_ARGUMENT(P99_LCOPY, 1)
P00_DOCUMENT_TYPE_ARGUMENT(P99_LCOPY, 0)
P00_DOCUMENT_DESIGNATOR_ARGUMENT(P99_LCOPY, 2)
P00_DOCUMENT_DESIGNATOR_ARGUMENT(P99_LCOPY, 3)
P00_DOCUMENT_DESIGNATOR_ARGUMENT(P99_LCOPY, 4)
#define P99_LCOPY(TYPE, VAR, ...) ((TYPE)P99_DESIGNATED(VAR, __VA_ARGS__))


#define P00_ACOPY4(TYPE, N, VAR, ...) ((TYPE[N])P99_DESIGNATED(VAR, P00_ACCESSORS(, __VA_ARGS__)))

#define P00_ACOPY3(TYPE, N, VAR) P00_ACOPY4(TYPE, N, VAR, N)

#ifdef P00_DOXYGEN
/**
 ** @brief Expand to an array literal of type @a TYPE[@a N] copying
 ** from another array.
 **
 ** The third argument is the array @a VAR to be copied from. The
 ** optional forth argument @a M is the number of elements from @c VAR
 ** that are to be copied. It defaults to @a N if omitted. Obviously
 ** we must always have <code>M <= N</code> for this to work.
 **
 ** This can be used to call a function with a copy of
 ** of @a VAR.
 **
 ** @remark The base type of @a VAR must be assignment compatible with type @a TYPE.
 **/
#define P99_ACOPY(TYPE, N, VAR, M)
#else
P00_DOCUMENT_MULTIPLE_ARGUMENT(P99_ACOPY, 2)
P00_DOCUMENT_DECLARATION_ARGUMENT(P99_ACOPY, 4)
#define P99_ACOPY(TYPE, N, ...)                                \
P99_IF_LT(P99_NARG(__VA_ARGS__), 2)                            \
(P00_ACOPY3(TYPE, N, __VA_ARGS__))                             \
(P00_ACOPY4(TYPE, N, __VA_ARGS__))
#endif

#ifdef P00_DOXYGEN
/**
 ** @brief Assign the content of array @a SOURCE to @a TARGET.
 **
 ** Only the @a N first elements are copied. Use it as in
 ** @code
 ** size_t B[4] = { 2, 3, 4, 5 };
 ** double *A = malloc(sizeof(double[4]));
 ** P99_AASSIGN(A, B, 4);
 ** @endcode
 **
 ** @pre @a N must expand to a decimal integer constant.
 **
 ** @pre @a SOURCE and @a TARGET must be arrays with a size of at least @a N
 ** or pointers that point to such arrays.
 **
 ** @remark If @a TARGET has more than @a N elements the excess
 ** elements are left untouched.
 **
 ** @remark The base types must not necessarily be the same but that
 ** of @a SOURCE must be assignable to that for @a TARGET. In
 ** particular, the type of @a TARGET should be at least as wide as
 ** that for @a SOURCE.
 **/
#define P99_AASSIGN(TARGET, SOURCE, N)
#else
P00_DOCUMENT_MULTIPLE_ARGUMENT(P99_AASSIGN, 0)
P00_DOCUMENT_MULTIPLE_ARGUMENT(P99_AASSIGN, 1)
#define P99_AASSIGN(TARGET, SOURCE, N) P99_BLOCK(P99_VASSIGNS(SOURCE, P99_ACCESSORS(TARGET, N));)
#endif

/** @}
 **/

#endif      /* !P99_MAP_H_ */
