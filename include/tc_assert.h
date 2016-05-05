#include <stdio.h>
#include <assert.h>
#include <execinfo.h>
#include <stdlib.h>
#include <stdarg.h>
#include "common_macros.h"

#ifndef TC_ASSERT_H
#define TC_ASSERT_H 1
#define tc_stacktrace(stream) \
  do {\
    void* stack[TC_ASSERT_STACK_LIMIT]; \
    size_t size; \
    char **strings; \
    size = backtrace(stack, TC_ASSERT_STACK_LIMIT); \
    backtrace_symbols_fd(stack,size,fileno(stream)); \
    abort(); \
  } while(0)

#endif /* TC_ASSERT_H */

/*
 * Unlike other ANSI header files, <tc_assert.h> may usefully be included
 * multiple times, with and without NDEBUG defined.
 * TODO: test the overhead of assert (though should have minimized by unlikely)
 */

#ifndef TC_ASSERT_STACK_LIMIT
#define TC_ASSERT_STACK_LIMIT 2048
#endif

#ifndef NDEBUG

#define tc_assert(X, ...) \
 do{ \
   if (unlikely(!(X))) { \
     fprintf(stderr,"Assertion failed: %s (%s:%d)\n", __func__, __FILE__, __LINE__); \
     fprintf(stderr,"Error message: " __VA_ARGS__); \
     tc_stacktrace(stderr); \
   } \
 } while(0)


#define tc_assert_diagnose(X,cb, ...) \
  do { \
   if (unlikely(!(X))) { \
     fprintf(stderr,"Assertion failed: %s (%s:%d)\n", __func__, __FILE__, __LINE__); \
     (cb)(__VA_ARGS__); \
     tc_stacktrace(stderr); \
   } \
  } while(0)

#else /* NDEBUG = 1 */
#define tc_assert(X, format,...) ((void)0)
#define tc_assert_diagnose(X, cb, ...) ((void)0)
#endif /* NDEBUG */

