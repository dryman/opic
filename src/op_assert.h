#include <stdio.h>
#include <assert.h>
#include <execinfo.h>
#include <stdlib.h>
#include <stdarg.h>
#include "op_macros.h"

#ifndef OP_ASSERT_H
#define OP_ASSERT_H 1

/** @file */

/** Print stack trace to specified stream. The printed stack length is configured
 * by OP_ASSERT_STACK_LIMIT macro, which defaults to 2048.
 * @param stream pointer to FILE object that specifies an output stream
 */
#define op_stacktrace(stream) \
  do {\
    void* stack[OP_ASSERT_STACK_LIMIT]; \
    size_t size; \
    size = backtrace(stack, OP_ASSERT_STACK_LIMIT); \
    backtrace_symbols_fd(stack,size,fileno(stream)); \
    abort(); \
  } while(0)

#endif /* OP_ASSERT_H */

/*
 * Unlike other ANSI header files, <op_assert.h> may usefully be included
 * multiple times, with and without NDEBUG defined.
 * TODO: test the overhead of assert (though should have minimized by unlikely)
 */

#ifndef OP_ASSERT_STACK_LIMIT
/** maximum stack trace length */
#define OP_ASSERT_STACK_LIMIT 2048
#endif

#ifndef NDEBUG

/** Assert with formatted output to stderr.
 * @param X assertion statement.
 * @param ... (additional arguments) additional arguments passed to printf.
 */
#define op_assert(X, ...) \
 do{ \
   if (op_unlikely(!(X))) { \
     fprintf(stderr,"Assertion failed: %s (%s:%d)\n", __func__, __FILE__, __LINE__); \
     fprintf(stderr,"Error message: " __VA_ARGS__); \
     op_stacktrace(stderr); \
   } \
 } while(0)

/** Assert with callback function
 * @param X assertion statement.
 * @param cb callback function.
 * @param ... (additional arguments) arguments passed to cb when assertion
 * failed.
 */
#define op_assert_diagnose(X,cb, ...) \
  do { \
   if (op_unlikely(!(X))) { \
     fprintf(stderr,"Assertion failed: %s (%s:%d)\n", __func__, __FILE__, __LINE__); \
     (cb)(__VA_ARGS__); \
     op_stacktrace(stderr); \
   } \
  } while(0)

#else /* NDEBUG = 1 */
#define op_assert(X, format,...) ((void)0)
#define op_assert_diagnose(X, cb, ...) ((void)0)
#endif /* NDEBUG */

