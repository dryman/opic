#include <assert.h>
#include <execinfo.h>
#include <stdio.h>
#include <stdlib.h>
#include "common_macro.h"

#define tc_assert(X, ...) \
  if(unlikely(!(X))) { \
    printf("Assertion failed at function %s, file %s, line %d.\n", \
      __func__, __FILE__, __LINE__); \
    printf("Error message: " __VA_ARGS__); \
    puts(""); \
    const int stack_limit = 2048; \
    void* stack[stack_limit]; \
    size_t size; \
    char **strings; \
    size_t i; \
    size = backtrace(stack, stack_limit); \
    strings = backtrace_symbols(stack, size); \
    for(i=0;i<size;i++){ \
      printf("%s\n",strings[i]); \
    } \
    free(strings); \
    abort(); \
  }

