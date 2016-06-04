#include <stdio.h>
#include <assert.h>
#include <execinfo.h>
#include <stdlib.h>
#include <stdarg.h>
#include "op_macros.h"

#ifndef OP_ASSERT_H
#define OP_ASSERT_H 1

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
#define OP_ASSERT_STACK_LIMIT 2048
#endif

#ifndef NDEBUG

#define op_assert(X, ...) \
 do{ \
   if (op_unlikely(!(X))) { \
     fprintf(stderr,"Assertion failed: %s (%s:%d)\n", __func__, __FILE__, __LINE__); \
     fprintf(stderr,"Error message: " __VA_ARGS__); \
     op_stacktrace(stderr); \
   } \
 } while(0)


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

