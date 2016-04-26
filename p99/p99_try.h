/* This may look like nonsense, but it really is -*- mode: C -*-              */
/*                                                                            */
/* Except for parts copied from previous work and as explicitly stated below, */
/* the authors and copyright holders for this work are as follows:            */
/* (C) copyright  2012-2014 Jens Gustedt, INRIA, France                       */
/* (C) copyright  2012 Simon Peeters                                          */
/* (C) copyright  2012 William Morris                                         */
/*                                                                            */
/* This file is free software; it is part of the P99 project.                 */
/* You can redistribute it and/or modify it under the terms of the QPL as     */
/* given in the file LICENSE. It is distributed without any warranty;         */
/* without even the implied warranty of merchantability or fitness for a      */
/* particular purpose.                                                        */
/*                                                                            */
#ifndef P99_TRY_H
#define P99_TRY_H
#include "p99_constraint.h"
#include "p99_lifo.h"

P99_POINTER_TYPE(p00_jmp_buf0);
P99_LIFO_DECLARE(p00_jmp_buf0_ptr);

P99_DECLARE_THREAD_LOCAL(P99_LIFO(p00_jmp_buf0_ptr), p00_jmp_buf_top);

#define P00_JMP_BUF_TOP P99_THREAD_LOCAL(p00_jmp_buf_top)

p99_inline
void p00_jmp_skip(p00_jmp_buf0 * p00_des) {
  P99_LIFO(p00_jmp_buf0_ptr)* p00_head = &P00_JMP_BUF_TOP;
  p00_jmp_buf0 * p00_ret = 0;
  do {
    p00_ret = P99_LIFO_POP(p00_head);
  } while (p00_ret && (p00_ret != p00_des));
}

p99_inline
void p00_jmp_push(p00_jmp_buf0 * p00_des) {
  P99_LIFO_PUSH(&P00_JMP_BUF_TOP, p00_des);
}

/**
 ** @brief Report the origin and cause of an error
 **
 ** Use this if a catch clause needs another layer of try/catch blocks
 ** during the cleanup.
 **
 ** @code
 ** P99_TRY {
 **   // the real application code
 ** } P99_CATCH(int code) {
 **   if (code) p99_jmp_report(code);
 **   P99_TRY {
 **     // some complicated cleanup that might throw
 **     // errors by itself
 **   } P99_CATCH();
 ** }
 ** @endcode
 **
 ** Without the call to ::p99_jmp_report the origin of the error would
 ** be lost in the second :P99_CATCH.
 **/
p99_inline void p99_jmp_report(errno_t p00_cond) {
  p00_constraint_report(p00_cond, 0, 0, 0);
}

p99_inline
noreturn
void p00_jmp_abort(errno_t p00_cond, char const* p00_file, char const* p00_context, char const* p00_info) {
  p00_constraint_report(p00_cond, p00_file, p00_context, p00_info);
  constraint_handler_t p00_func = atomic_load(&p00_constraint_handler);
  if (p00_func == exit_handler_s) {
    /* Avoid looping in exit handlers. */
    set_constraint_handler_s(abort_handler_s);
    /* Give the application a chance to clean up. */
    exit(EXIT_FAILURE);
  }
  abort();
}

p99_inline
noreturn
void p00_jmp_throw(errno_t p00_cond, p00_jmp_buf0 * p00_top, char const* p00_file, char const* p00_context, char const* p00_info) {
  if (p00_file) P00_JMP_BUF_FILE = p00_file;
  if (p00_context) P00_JMP_BUF_CONTEXT = p00_context;
  if (p00_info) P00_JMP_BUF_INFO = p00_info;
  if (!p00_top) p00_top = P99_LIFO_TOP(&P00_JMP_BUF_TOP);
  if (P99_LIKELY(p00_top)) p00_longjmp(p00_top, p00_cond);
  else p00_jmp_abort(p00_cond, p00_file, p00_context, p00_info);
}


/**
 ** @addtogroup try Try, catch and finally blocks
 **
 ** @{
 **/


/**
 ** @brief Stop execution at the current point and signal an
 ** exception of value @a X to the next ::P99_TRY clause
 ** on the call stack, if any.
 **
 ** @remark If there is no such try clause on the call stack, @c abort
 ** is called.
 **
 ** @param X should be an integer value that fits into an @c int.
 **
 ** A good convention for the values to throw is to use system wide
 ** error numbers such as @c ERANGE. But any other convention that
 ** fits the needs of an application can be used.
 **
 ** @warning Be careful when throwing @c 0 as a value. This should be
 ** reserved for preliminary returns from deep recursion that is not
 ** considered being an error. In particular, throwing @c 0 will only
 ** unwind to the next ::P99_FINALLY and continue normal execution
 ** thereafter.
 **/
P00_UNWIND_DOCUMENT
#define P99_THROW(X) p00_jmp_throw((X), p00_unwind_top, P99_STRINGIFY(__LINE__), __func__, "throw")

p99_inline
noreturn
void p00_throw_errno(p00_jmp_buf0 * p00_top, errno_t p00_def, char const* p00_file, char const* p00_context, char const* p00_info) {
  errno_t p00_err = errno;
  if (!p00_err) p00_err = (p00_def ? p00_def : EINVAL);
  errno = 0;
  p00_jmp_throw(p00_err, p00_top, p00_file, p00_context, p00_info);
}

p99_inline
void p00_throw_call_range(p00_jmp_buf0 * p00_top, errno_t p00_sign, char const* p00_file, char const* p00_context, char const* p00_info) {
  errno_t p00_err = errno;
  if  (P99_LIKELY(!p00_err)) return;
  switch (p00_err) {
  case ERANGE: if (p00_sign) p00_err = p00_sign;
  }
  errno = 0;
  p00_jmp_throw(p00_err, p00_top, p00_file, p00_context, p00_info);
}

#define P00_ALMOST_ZERO(X)                                                \
P99_GENERIC((X),                                                          \
            ((X) > 0 ? (X) <= FLT_MIN : -(X) >= FLT_MIN),                 \
            (float, ((X) > 0 ? (X) <= LDBL_MIN : -(X) >= LDBL_MIN)),      \
            (long double, ((X) > 0 ? (X) <= LDBL_MIN : -(X) >= LDBL_MIN)) \
            )

/* Define a function for each of the standard real types, that runs
   p00_throw_call_range with the correct information of under- or
   overflow. We need this for compilers that don't support gcc's block
   expressions and @c typeof. */
#define P00_THROW_CALL_RANGE(T, F, ...)                           \
p99_inline                                                        \
T P99_PASTE2(p00_throw_call_range_, T)(p00_jmp_buf0 * p00_top,    \
                                     T p00_val,                   \
                                     char const* p00_file,        \
                                     char const* p00_context,     \
                                     char const* p00_info) {      \
  if (P99_UNLIKELY(P99_IS_ONE(p00_val, 0, __VA_ARGS__))           \
      P99_IF_EQ_1(F)(|| P99_UNLIKELY(P00_ALMOST_ZERO(p00_val)))() \
      )                                                           \
    p00_throw_call_range(p00_top,                                 \
                       /* also capture errors for floating        \
                          types, for integer types part of this   \
                          is redundant. */                        \
                       ((p00_val > 0)                             \
                        ? ((p00_val >= 1) ? INT_MAX : 0)          \
                        : (((T)-p00_val >= 1) ? INT_MIN : 0)),    \
                       p00_file, p00_context, p00_info);          \
  return p00_val;                                                 \
}                                                                 \
P99_MACRO_END(P00_THROW_CALL_RANGE, T)

P00_THROW_CALL_RANGE(_Bool, 0, 1);
P00_THROW_CALL_RANGE(char, 0, CHAR_MAX, CHAR_MIN);
P00_THROW_CALL_RANGE(schar, 0, SCHAR_MAX, SCHAR_MIN);
P00_THROW_CALL_RANGE(short, 0, SHRT_MAX, SHRT_MIN);
P00_THROW_CALL_RANGE(int, 0, INT_MAX, INT_MIN);
P00_THROW_CALL_RANGE(long, 0, LONG_MAX, LONG_MIN);
P00_THROW_CALL_RANGE(llong, 0, LLONG_MAX, LLONG_MIN);
P00_THROW_CALL_RANGE(uchar, 0, UCHAR_MAX);
P00_THROW_CALL_RANGE(ushort, 0, USHRT_MAX);
P00_THROW_CALL_RANGE(unsigned, 0, UINT_MAX);
P00_THROW_CALL_RANGE(ulong, 0, ULONG_MAX);
P00_THROW_CALL_RANGE(ullong, 0, ULLONG_MAX);
# ifdef HUGE_VALF
P00_THROW_CALL_RANGE(float, 1, HUGE_VALF, -HUGE_VALF);
# endif
# ifdef HUGE_VAL
P00_THROW_CALL_RANGE(double, 1, HUGE_VAL, -HUGE_VAL);
# endif
# ifdef HUGE_VALL
P00_THROW_CALL_RANGE(ldouble, 1, HUGE_VALL, -HUGE_VALL);
# endif

#define P00_THROW_CALL_RANGE_CASE(T) ,(T, P99_PASTE2(p00_throw_call_range_, T))

#define P00_THROW_CALL_RANGE_(F, CASES, ...)                                              \
P99_GENERIC((F)(__VA_ARGS__), P00_ROBUST CASES)                                           \
  (p00_unwind_top, F(__VA_ARGS__), P99_STRINGIFY(__LINE__), __func__, #F ", range check")

#define P99_THROW_CALL_RANGE_ARG_0 permitted
#define P99_THROW_CALL_RANGE_ARG_1 permitted
#define P99_THROW_CALL_RANGE_ARG_2 permitted
#define P99_THROW_CALL_RANGE_ARG_3 permitted
#define P99_THROW_CALL_RANGE_ARG_4 permitted

/**
 ** @brief Wrap a function call to @a F such that it throws an error
 ** on failure.
 **
 ** Many functions in the C and POSIX standards set @c errno to @c
 ** ERANGE to signal an under- or overflow. This wrapper makes this
 ** transparent such that it ensures that @c errno is always checked,
 ** and if an error occurs a value is thrown.
 **
 ** If the error is @c ERANGE the value of @c INT_MAX is thrown for an
 ** overflow and @c INT_MIN for a negative overflow. If the return
 ** type of @a F is a floating point type @c ERANGE could also be set
 ** for a value that is too close to 0. In that case @c ERANGE is
 ** thrown directly.
 **
 ** If @c errno has another non-zero value that value is thrown.
 **
 ** @return the value of the function call if the call was
 ** successful. Never returns if it wasn't.
 **
 ** @see P99_THROW_CALL_NEG for a similar macro that checks if the
 ** return value is negative
 **
 ** @see P99_THROW_CALL_VOIDP for a similar macro that checks a
 ** pointer return value
 **
 ** @remark This is only implemented for the real arithmetic types by
 ** means of a type generic macro.
 **/
P00_DOCUMENT_PERMITTED_ARGUMENT(P99_THROW_CALL_RANGE, 0)
P00_DOCUMENT_PERMITTED_ARGUMENT(P99_THROW_CALL_RANGE, 1)
P00_DOCUMENT_PERMITTED_ARGUMENT(P99_THROW_CALL_RANGE, 2)
P00_DOCUMENT_PERMITTED_ARGUMENT(P99_THROW_CALL_RANGE, 3)
P00_DOCUMENT_PERMITTED_ARGUMENT(P99_THROW_CALL_RANGE, 4)
#define P99_THROW_CALL_RANGE(F, ...)                           \
  P00_THROW_CALL_RANGE_                                        \
  (F,                                                          \
   (P99_SER(P00_THROW_CALL_RANGE_CASE, P99_STD_REAL_TYPES)),   \
   __VA_ARGS__)


/**
 ** @brief Capture, clean and throw the current value of @c errno
 **
 ** This is intended for a cleanup after system functions. A lot of
 ** them just return a @c -1 or so if an error occurred.
 ** @code
 ** FILE* f = fopen("bla.txt", "w");
 ** if (!f) P99_THROW_ERRNO;
 ** @endcode
 **
 ** @see P99_THROW
 **/
#if defined(noreturn) || defined(_Noreturn)
#define P99_THROW_ERRNO p00_throw_errno(p00_unwind_top, EINVAL, P99_STRINGIFY(__LINE__), __func__, "THROW_ERRNO")
#else
#define P99_THROW_ERRNO                                        \
do {                                                           \
  errno_t p00_err = errno;                                     \
  if (!p00_err) p00_err = EINVAL;                              \
  errno = 0;                                                   \
  P99_THROW(p00_err);                                          \
 } while(0)
#endif

p99_inline
int p00_throw_call_zero(int p00_err,
                        errno_t p00_def,
                        p00_jmp_buf0 * p00_top,
                        char const* p00_file,
                        char const* p00_context,
                        char const* p00_info) {
  if (P99_UNLIKELY(p00_err)) p00_throw_errno(p00_top, p00_def, p00_file, p00_context, p00_info);
  return 0;
}

/**
 ** @brief Wrap a function call to @a F such that it throws an error
 ** on failure.
 **
 ** Many functions in the C and POSIX standards return an @c int or @c errno_t only
 ** for the purpose of signaling an error and provide an error code in
 ** @c errno. This wrapper makes this transparent such that it ensures
 ** that the error code is always checked, and if an error occurs the
 ** value of @c errno is thrown.
 **
 ** @return @c 0 if the call was successful. Never returns if it
 ** wasn't.
 **
 ** @see P99_THROW_CALL_NEG for a similar macro that checks if the
 ** return value is negative
 **
 ** @see P99_THROW_CALL_VOIDP for a similar macro that checks a
 ** pointer return value
 **/
#define P99_THROW_CALL_ZERO(F, E, ...)                                                                            \
p00_throw_call_zero(F(__VA_ARGS__), E, p00_unwind_top, P99_STRINGIFY(__LINE__), __func__, #F ", non-zero return")

#ifndef NDEBUG
/**
 ** @brief Replacement for @c assert that throw a catchable exception
 **
 ** The first argument @a E is the error code that will be passed down
 ** the line.
 **
 ** @remark As for @c assert such an assertion is disabled at compile
 ** time if the macro @c NDEBUG is defined.
 **/
#define P99_THROW_ASSERT(E, ...)                                                                                                          \
(void)p00_throw_call_zero(!(__VA_ARGS__), E, p00_unwind_top, P99_STRINGIFY(__LINE__), __func__, "failed assertion: ``" #__VA_ARGS__ "''")
#else
#define P99_THROW_ASSERT(...) P99_NOP
#endif

/**
 ** @brief Wrap a function call to @a F such that it throws an error
 ** on failure.
 **
 ** Similar to ::P99_THROW_CALL_ZERO, only that the condition for
 ** failure is inverted, that is 0 is considered a failure and all
 ** other values are considered success.
 **/
#define P99_THROW_CALL_NOT_ZERO(F, E, ...)                                                                     \
p00_throw_call_zero(!F(__VA_ARGS__), E, p00_unwind_top, P99_STRINGIFY(__LINE__), __func__, #F ", zero return")

p99_inline
int p00_throw_call_thrd(int p00_err,
                        p00_jmp_buf0 * p00_top,
                        char const* p00_file,
                        char const* p00_context,
                        char const* p00_info) {
  if (P99_UNLIKELY(p00_err != thrd_success))
    p00_jmp_throw(p00_err, p00_top, p00_file, p00_context, p00_info);
  return 0;
}

/**
 ** @brief Wrap a "thread" function call to @a F such that it throws an error
 ** on failure.
 **
 ** In C thread interface functions return an @c int to signal success
 ** (::thrd_success) or an error. This wrapper makes this transparent
 ** such that it ensures that the error code is always checked, and if
 ** an error occurs the value is thrown.
 **
 ** @return ::thrd_success if the call was successful. Never returns
 ** if it wasn't.
 **
 ** @see P99_THROW_CALL_ZERO for a similar macro that checks if the
 ** return value is @c 0
 **
 ** @see P99_THROW_CALL_NEG for a similar macro that checks if the
 ** return value is negative
 **
 ** @see P99_THROW_CALL_VOIDP for a similar macro that checks a
 ** pointer return value
 **/
#define P99_THROW_CALL_THRD(F, ...)                                                                            \
p00_throw_call_thrd(F(__VA_ARGS__), p00_unwind_top, P99_STRINGIFY(__LINE__), __func__, #F ", no thrd_success")

p99_inline
int p00_throw_call_neg(int p00_neg,
                       errno_t p00_def,
                       p00_jmp_buf0 * p00_top,
                       char const* p00_file,
                       char const* p00_context,
                       char const* p00_info) {
  if (P99_UNLIKELY(p00_neg < 0)) p00_throw_errno(p00_top, p00_def, p00_file, p00_context, p00_info);
  return p00_neg;
}

#define P00_THROW_CALL_NEG(F, E, ...)                                                                       \
p00_throw_call_neg(F(__VA_ARGS__), E, p00_unwind_top, P99_STRINGIFY(__LINE__), __func__, #F ", neg return")

/**
 ** @brief Wrap a function call to @a F such that it throws an error
 ** on negative return.
 **
 ** Many functions in the C and POSIX standards return an @c int and
 ** signal an error with a negative value. They then provide an error
 ** code in @c errno. This wrapper makes this transparent such that it
 ** ensures that the error code is always checked, and if an error
 ** occurs the value of @c errno is thrown.
 **
 ** @return the value of the call to the function if that was
 ** successful. Never returns if it wasn't.
 **
 ** @see P99_THROW_CALL_ZERO for a similar macro that checks if the
 ** return value is @c 0
 **
 ** @see P99_THROW_CALL_VOIDP for a similar macro that checks a
 ** pointer return value
 **/
#define P99_THROW_CALL_NEG(F, E, ...) P00_THROW_CALL_NEG(F, E, __VA_ARGS__)

p99_inline
int p00_throw_call_negate(int p00_neg,
                          errno_t p00_def,
                          p00_jmp_buf0 * p00_top,
                          char const* p00_file,
                          char const* p00_context,
                          char const* p00_info) {
  P99_UNUSED(p00_def);
  if (P99_UNLIKELY(p00_neg < 0)) p00_jmp_throw(-p00_neg, p00_top, p00_file, p00_context, p00_info);
  return p00_neg;
}

#define P00_THROW_CALL_NEGATE(F, E, ...)                                                                       \
p00_throw_call_negate(F(__VA_ARGS__), E, p00_unwind_top, P99_STRINGIFY(__LINE__), __func__, #F ", neg return")

/**
 ** @brief Wrap a function call to @a F such that it throws an error
 ** on negative return.
 **
 ** A common strategy of libraries and also the Linux kernel is to
 ** return an @c int and signal an error with a negative value. The
 ** error code is then the negation of that return value. This wrapper
 ** makes this transparent such that it ensures that the error code is
 ** always checked, and if an error occurs the negated value is
 ** thrown.
 **
 ** @return the value of the call to the function if that was
 ** successful. Never returns if it wasn't.
 **
 ** @see P99_THROW_CALL_NEG for a similar macro that also checks if
 ** the return value is negative but that returns the value of @c
 ** errno, instead.
 **
 ** @see P99_THROW_CALL_ZERO for a similar macro that checks if the
 ** return value is @c 0
 **
 ** @see P99_THROW_CALL_VOIDP for a similar macro that checks a
 ** pointer return value
 **/
#define P99_THROW_CALL_NEGATE(F, E, ...) P00_THROW_CALL_NEGATE(F, E, __VA_ARGS__)

p99_inline
void* p00_throw_call_voidp(void* p00_p,
                           errno_t p00_def,
                           p00_jmp_buf0 * p00_top,
                           char const* p00_file,
                           char const* p00_context,
                           char const* p00_info) {
  if (P99_UNLIKELY(!p00_p || (p00_p == (void*)-1))) p00_throw_errno(p00_top, p00_def, p00_file, p00_context, p00_info);
  return p00_p;
}

#define P00_THROW_CALL_VOIDP(F, E, ...)                                                                           \
p00_throw_call_voidp(F(__VA_ARGS__), E, p00_unwind_top, P99_STRINGIFY(__LINE__), __func__, #F ", invalid return")


/**
 ** @brief Wrap a function call to @a F such that it throws an error
 ** on invalid return.
 **
 ** Many functions in the C and POSIX standards return a @c void* and
 ** signal an error with value that is @c 0 or
 ** <code>(void*)-1</code>. They then provide an error code in @c
 ** errno. This wrapper makes this transparent such that it ensures
 ** that the error code is always checked, and if an error occurs the
 ** value of @c errno is thrown.
 **
 ** @return the value of the call to the function if that was
 ** successful. Never returns if it wasn't.
 **
 ** @see P99_THROW_CALL_ZERO for a similar macro that checks if the
 ** return value is @c 0
 **
 ** @see P99_THROW_CALL_NEG for a similar macro that checks if the
 ** return value is negative
 **
 **/
#define P99_THROW_CALL_VOIDP(F, E, ...) P00_THROW_CALL_VOIDP(F, E, __VA_ARGS__)

/**
 ** @brief Stop execution at the current point inside a ::P99_FINALLY
 ** or ::P99_CATCH clause and propagate the same exception that led
 ** here to the next level.
 **/
P00_UNWIND_DOCUMENT
#define P99_RETHROW p00_jmp_throw(p00_code, p00_unwind_top, 0, 0, 0)


/**
 ** @brief Create a block that can catch exceptions
 **
 ** @remark This must be used with either ::P99_CATCH or ::P99_FINALLY
 ** following immediately after the depending block.
 **
 ** The simplest use of this feature is together with ::P99_FINALLY
 ** @code
 ** unsigned char*volatile buffer = 0;
 ** P99_TRY {
 **   buffer = malloc(bignumber);
 **   if (!buffer) P99_THROW(thrd_nomem);
 **   // do something complicated with buffer
 **   favorite_func(buffer);
 ** } P99_FINALLY {
 **   free(buffer);
 ** }
 ** @endcode
 **
 ** This will ensure that the buffer allocated in @c buffer will
 ** always be freed, regardless of any error conditions the code
 ** encounters. In particular this will work, even if an exception is
 ** thrown from below the call to @c favorite_func.
 **
 ** If no exception occurs, the ::P99_FINALLY clause is always executed.
 ** Execution then continues after the clause, just as for
 ** normal code.
 **
 ** If an exception occurs, the ::P99_FINALLY clause is executed (and in this case
 ** the call to @c free is issued). But afterwards, execution will not
 ** continue as normal but instead will jump to the next ::P99_FINALLY or
 ** ::P99_CATCH block on the call stack.
 **
 ** An alternative way is to use ::P99_CATCH and to handle different
 ** exceptions explicitly.
 **
 ** @code
 ** unsigned char*volatile buffer = 0;
 ** P99_TRY {
 **   buffer = malloc(bignumber);
 **   if (!buffer) P99_THROW(thrd_nomem);
 **   // do something complicated with buffer
 ** } P99_CATCH(int code) {
 **   switch(code) {
 **     case thrd_nomem: perror("we had an allocation error"); break;
 **     case thrd_timedout: perror("we were timed out"); break;
 **   }
 **   free(buffer);
 **   if (code) P99_RETHROW;
 ** }
 ** @endcode
 **
 ** The difference here is that we receive the error code through the
 ** variable @c code and we can thus take different action for
 ** different exceptional conditions. If it weren't for the
 ** ::P99_RETHROW, the unrolling of the call stack would stop at this
 ** point and execution would continue after the catch block. The
 ** exception would be considered caught.
 **
 ** Here, since there is a ::P99_RETHROW, execution will jump to the
 ** next ::P99_FINALLY or ::P99_CATCH block on the call stack. In fact
 ** a catch clause of
 **
 ** @code
 ** P99_CATCH(int code) {
 **   // do something here and then
 **   if (code) P99_RETHROW;
 ** }
 ** @endcode
 **
 ** Would be equivalent to
 **
 ** @code
 ** P99_FINALLY {
 **   // do something here
 ** }
 ** @endcode
 **
 ** except that this wouldn't give access to @c code.
 **
 ** Note that the code depending on ::P99_TRY must always be an entire
 ** block with <code>{ }</code> surrounding it. The code depending on
 ** ::P99_FINALLY or ::P99_CATCH doesn't have that restriction and could
 ** be just a single statement.
 **
 **/
P00_UNWIND_DOCUMENT
#define P99_TRY                                                \
P99_UNWIND_PROTECT                                             \
/* one phase for the try, one for the finally */               \
for (register unsigned p00_pha = 0; p00_pha < 2u; ++p00_pha)   \
  /* Restrict the first phase to the try */                    \
  if (!p00_pha)                                                \
    P00_BLK_START                                              \
      P00_BLK_BEFORE(p00_jmp_push(p00_unwind_top))             \
      do

#define P00_FINALLY                                                 \
while (0); else case 0:                                             \
P00_BLK_START                                                       \
P00_BLK_BEFORE(p00_code = p00_unwind_top[0].p00_code)               \
P00_BLK_BEFORE(p00_unw = !!p00_code)                                \
/* make sure that this phase is executed at most once */            \
P00_BLK_BEFORE(p00_pha = 2u)                                        \
/* unwind the lifo to the current point */                          \
P00_BLK_BEFORE(p00_jmp_skip(p00_unwind_top))                        \
/* Hide the top most jump buffer, such that throw or rethrow inside \
   the catch or finally blocks goes to the next level. */           \
P00_BLK_DECL(p00_jmp_buf0*, p00_unwind_top, p00_unwind_prev)


/**
 ** @brief Designate a block that is executed regardless of the
 ** exceptions that were encountered in the corresponding try block
 **
 ** @remark If the finally clause was reached via the catching of an exception,
 ** the unwind of ::P99_TRY and ::P99_UNWIND_PROTECT blocks
 ** will continue. Otherwise execution will resume normally after the
 ** ::P99_FINALLY clause.
 **
 ** A typical use pattern will be as follows:
 **
 ** @code
 ** P99_FINALLY {
 **  // do some cleanup
 ** }
 ** // continue only if no exception had been caught
 ** @endcode
 **
 ** @see P99_TRY
 ** @see P99_CATCH
 **/
P00_UNWIND_DOCUMENT
#define P99_FINALLY                                            \
P00_FINALLY                                                    \
P00_BLK_AFTER(p00_unw ? P99_RETHROW : P99_NOP)

/**
 ** @brief Designate a block that is executed regardless of the
 ** exceptions that were encountered in the corresponding try block
 **
 ** @remark The argument to ::P99_CATCH should be a declaration of an
 ** integer variable, most likely an @c int.
 **
 ** @remark With a ::P99_CATCH clause, an exception is considered to have
 ** been caught. If you want to unwind the call stack even further you
 ** have to use ::P99_RETHROW.
 **
 ** @remark The corresponding code will be @c 0 if and only if no
 ** exception occured.
 **
 ** The definition of the @c code variable can be omitted. Such a ::P99_CATCH
 ** without a variable can be
 ** used to catch any exception and to continue execution after the
 ** catch clause in any case:
 **
 ** @code
 ** P99_CATCH() {
 **  // do some cleanup
 ** }
 ** // continue here regardless of what happened
 ** @endcode
 **
 ** There is also a "catch all" dialect of all this
 ** @code
 ** P99_TRY {
 **   // do something complicated that may fail
 ** } P99_CATCH();
 ** @endcode
 **
 ** The ";" after the catch is just an empty statement. So this catch
 ** clause catches all exceptions, forgets the exception code and does
 ** nothing.
 **
 ** @see P99_TRY
 ** @see P99_THROW
 ** @see P99_RETHROW
 **/
P00_UNWIND_DOCUMENT
#define P99_CATCH(...)                                                                        \
P00_FINALLY                                                                                   \
P99_IF_EMPTY(__VA_ARGS__)()(P00_BLK_BEFORE(__VA_ARGS__ = p00_code))                           \
P00_BLK_BEFORE(p00_unw = 0)                                                                   \
P00_BLK_AFTER(p00_code ? (void)((P00_JMP_BUF_FILE = 0), (P00_JMP_BUF_CONTEXT = 0)) : P99_NOP)

/**
 ** @}
 **/


#endif
