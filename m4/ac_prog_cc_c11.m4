AC_DEFUN([_AC_PROG_CC_C11],
[_AC_C_STD_TRY([c11],
[[#include <stdalign.h>
#include <stdnoreturn.h>
#include <assert.h>
#include <stdatomic.h>
static_assert(1, "static assert in c11");
#ifndef noreturn
#error "noreturn should be part of C11"
#endif
#ifndef alignof
#error "alignof should be part of C11"
#endif
#if __STDC_VERSION__ != 201112L
#error "not c11"
#endif
#define my_func(X) _Generic((X),short: short_func, int: int_func)(X)
void short_func(short x){}
void int_func(int x){}
]],
[[
int x;
my_func(x);
]],
[[-std=gnu11 -std=c11 -c11]], [$1], [$2])[]dnl
])

AC_DEFUN([AC_PROG_CC_C11],
[ AC_REQUIRE([AC_PROG_CC])dnl
  _AC_PROG_CC_C11
])
