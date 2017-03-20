/* op_assert.h ---
 *
 * Filename: op_assert.h
 * Description:
 * Author: Felix Chern
 * Maintainer:
 * Copyright: (c) 2016-2017 Felix Chern
 * Created: May 2, 2016
 * Version:
 * Package-Requires: ()
 * Last-Updated:
 *           By:
 *     Update #: 0
 * URL:
 * Doc URL:
 * Keywords:
 * Compatibility:
 *
 */

/* Commentary:
 *
 *
 *
 */

/* Change Log:
 *
 *
 */

/* This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or (at
 * your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/* Code: */


#include <stdio.h>
#include <assert.h>
#include <execinfo.h>
#include <stdlib.h>
#include <stdarg.h>
#include "op_macros.h"

#ifndef OPIC_COMMON_OP_ASSERT_H
#define OPIC_COMMON_OP_ASSERT_H 1

#define op_stacktrace(stream)                           \
  do {                                                  \
    void* stack[OP_ASSERT_STACK_LIMIT];                 \
    size_t size;                                        \
    size = backtrace(stack, OP_ASSERT_STACK_LIMIT);     \
    backtrace_symbols_fd(stack,size,fileno(stream));    \
    abort();                                            \
  } while(0)

#endif /* OP_ASSERT_H */

/*
 * Unlike other ANSI header files, <op_assert.h> may usefully be included
 * multiple times, with and without NDEBUG defined.
 * TODO: test the overhead of assert (though should have minimized by unlikely)
 * TODO: Do we want to use log4c instead of stderr?
 * TODO: integrate with cmocka to test assersions.
 */

#ifndef OP_ASSERT_STACK_LIMIT
#define OP_ASSERT_STACK_LIMIT 2048
#endif

#ifndef NDEBUG

#define op_assert(X, ...)                               \
  do{                                                   \
    if (op_unlikely(!(X))) {                            \
      fprintf(stderr,"Assertion failed: %s (%s:%d)\n",  \
              __func__, __FILE__, __LINE__);            \
      fprintf(stderr,"Error message: " __VA_ARGS__);    \
      op_stacktrace(stderr);                            \
    }                                                   \
  } while(0)


#define op_assert_diagnose(X,cb, ...)                   \
  do {                                                  \
    if (op_unlikely(!(X))) {                            \
      fprintf(stderr,"Assertion failed: %s (%s:%d)\n",  \
              __func__, __FILE__, __LINE__);            \
      (cb)(__VA_ARGS__);                                \
      op_stacktrace(stderr);                            \
    }                                                   \
  } while(0)

#else /* NDEBUG = 1 */
#define op_assert(X, format,...) ((void)0)
#define op_assert_diagnose(X, cb, ...) ((void)0)
#endif /* NDEBUG */


/* op_assert.h ends here */
