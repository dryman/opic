/* This may look like nonsense, but it really is -*- mode: C -*-              */
/*                                                                            */
/* Except for parts copied from previous work and as explicitly stated below, */
/* the authors and copyright holders for this work are as follows:            */
/* (C) copyright  2012-2014 Jens Gustedt, INRIA, France                       */
/* (C) copyright  2012 William Morris                                         */
/*                                                                            */
/* This file is free software; it is part of the P99 project.                 */
/* You can redistribute it and/or modify it under the terms of the QPL as     */
/* given in the file LICENSE. It is distributed without any warranty;         */
/* without even the implied warranty of merchantability or fitness for a      */
/* particular purpose.                                                        */
/*                                                                            */
#ifndef P99_TSS_H
#define P99_TSS_H 1

#include <unistd.h>
#include <sys/time.h>
#include <pthread.h>

#include "p99_defarg.h"
#include "p99_atomic.h"

#if !p99_has_feature(threads_h)

/**
 ** @addtogroup threads C11 thread emulation on top of POSIX threads
 **
 ** This is a relatively straightforward implementation of the C11
 ** thread model on top of POSIX threads. The main difficulty this presents
 ** is that the thread entry function signature differs between the
 ** two. C11 thread returns an <code>int</code> whereas POSIX returns
 ** a <code>void*</code>.
 **
 ** You can find the thread management interfaces through the
 ** documentation of the type ::thrd_t.
 **
 ** @remark In addition to POSIX threads this implementation needs
 ** some C11 atomic operations for initialization via ::call_once and
 ** status communication.
 **
 ** @{
 **/

/**
 ** @addtogroup thread_macros
 ** @{
 **/

#ifndef PTHREAD_DESTRUCTOR_ITERATIONS
# warning "definition of PTHREAD_DESTRUCTOR_ITERATIONS is missing"
/**
 ** @brief expands to an integer constant expression representing the
 ** maximum number of times that destructors will be called when a
 ** thread terminates
 ** @see tss_t
 **/
# define TSS_DTOR_ITERATIONS 1
#else
# define TSS_DTOR_ITERATIONS PTHREAD_DESTRUCTOR_ITERATIONS
#endif

/**
 ** @}
 **/


/**
 ** @addtogroup thread_types
 ** @{
 **/

/**
 ** @brief complete object type that holds an identifier for a
 ** thread-specific storage pointer
 **
 ** @remark This type is just a wrapper around a POSIX @c pthread_key_t.
 **
 ** @see P99_DECLARE_THREAD_LOCAL for a more comfortable interface to
 ** thread local variables
 **/
P99_ENC_DECLARE(pthread_key_t, tss_t);

/**
 ** @brief which is the function pointer type <code>void
 ** (*)(void*)</code>, used for a destructor for a thread-specific
 ** storage pointer
 ** @see tss_t
 **/
typedef void (*tss_dtor_t)(void*);

/**
 ** @}
 **/

/**
 ** @addtogroup thread_enum
 ** @{
 **/

/**
 ** @brief C11 thread function return values
 **/
enum thrd_status {
  /**
   ** @brief returned by a timed wait function to indicate that the time specified in the call was reached without acquiring the requested resource
   **/
  thrd_timedout = ETIMEDOUT,
  /**
   ** @brief returned by a function to indicate that the requested operation succeeded
   **/
  thrd_success = 0,
  /**
   ** @brief returned by a function to indicate that the requested
   ** operation failed because a resource requested by a test and
   ** return function is already in use
   **/
  thrd_busy = EBUSY,
  /**
   ** @brief returned by a function to indicate that the requested operation failed
   **/
  thrd_error = INT_MIN,
  /**
   ** @brief returned by a function to indicate that the requested
   ** operation failed because it was unable to allocate memory
   **/
  thrd_nomem = ENOMEM,
  /**
   ** @brief (extension) returned by ::thrd_sleep to indicate that the
   ** corresponding request has been interrupted by a signal
   **/
  thrd_intr = -1
};

/**
 ** @}
 **/

/**
 ** @related tss_t
 ** @return ::thrd_success on success, or ::thrd_error if the request
 ** could not be honored.
 **
 ** If successful, sets the thread-specific storage pointed to by key
 ** to a value that uniquely identifies the newly created
 ** pointer. Otherwise, the thread-specific storage pointed to by key
 ** is set to an undefined value.
 **/
P99_WARN_UNUSED_RESULT
p99_inline
int tss_create(tss_t *p00_key, tss_dtor_t dtor) {
  return pthread_key_create(&P99_ENCP(p00_key), dtor) ? thrd_error : thrd_success;
}

/**
 ** @related tss_t
 **/
p99_inline
void tss_delete(tss_t p00_key) {
  (void)pthread_key_delete(P99_ENC(p00_key));
}

/**
 ** @related tss_t
 **
 ** @return the value for the current thread if successful, or @c 0 if
 ** unsuccessful.
 **/
p99_inline
void *tss_get(tss_t p00_key) {
  return pthread_getspecific(P99_ENC(p00_key));
}

/**
 ** @related tss_t
 ** @return ::thrd_success on success, or ::thrd_error if the request
 ** could not be honored.
 **/
P99_WARN_UNUSED_RESULT
p99_inline
int tss_set(tss_t p00_key, void *p00_val) {
  return pthread_setspecific(P99_ENC(p00_key), p00_val) ? thrd_error : thrd_success;
}


#endif

/**
 ** @brief A stub structure to hold a thread local variable if
 ** ::thread_local is not available.
 **
 ** In most cases you wouldn't use this type directly but use
 ** ::P99_TSS_DECLARE_LOCAL to declare a variable and ::P99_TSS_LOCAL
 ** to access it. This should in particular be the case where you
 ** don't make explicit use of #p99_dtor to destroy particular
 ** instances of the variable.
 **
 ** The advantage of ::p99_tss over the C11 type ::tss_t is that it
 ** doesn't need an equivalent of ::tss_create. If they are properly
 ** initialized with the default initializer, variables of this type
 ** here will do the dynamic part of the initialization automatically
 ** at the first use. This could come with a tiny overhead of some
 ** instructions, which normally shouldn't even be measurable.
 **
 ** The dynamic initialization needs to know what the destructor
 ** function of the TSS should be. It can be provided through the
 ** field #p99_dtor. If #p99_dtor is @c 0 no destructor will be
 ** called.
 **
 ** The functions that are implemented follow the same line as those
 ** for ::tss_t, only that they always receive a pointer to a
 ** ::p99_tss such that they will be able to perform the
 ** initialization if necessary.
 **
 ** In addition to the ::tss_t interfaces we have #p99_tss_get_alloc
 ** to allocate a buffer if the TSS was not yet set for the executing
 ** thread before. Both need that the destructor value #p99_dtor and
 ** the one that has been passed to the call to ::tss_create are
 ** consistent. Don't mess around with that.
 **
 ** @see ::P99_TSS_DECLARE_LOCAL
 ** @see ::P99_DECLARE_THREAD_LOCAL
 **/
struct p99_tss {
  tss_t p00_val;
  /**
   ** @brief Destructor function that is automatically called at the
   ** termination of a thread.
   **/
  tss_dtor_t p99_dtor;
  bool volatile p00_done;
  atomic_flag p00_flg;
};

typedef struct p99_tss p99_tss;

p99_inline
p99_tss* p99_tss_init(p99_tss* p00_el, tss_dtor_t p00_f) {
  if (p00_el) {
    *p00_el = (p99_tss) { .p99_dtor = p00_f, };
    atomic_flag_clear_explicit(&p00_el->p00_flg, memory_order_release);
  }
  return p00_el;
}

/* This is an implementation to bootstrap the thread specific
   code. Once initialization functionalities that are better suited
   for application code are defined elsewhere. */
p99_inline
void p00_tss_init(p99_tss * p00_key) {
  if (P99_UNLIKELY(!p00_key->p00_done)) {
    P99_SPIN_EXCLUDE(&p00_key->p00_flg) {
      if (!p00_key->p00_done) {
        int p00_ret = tss_create(&P99_ENCP(p00_key), p00_key->p99_dtor);
        if (p00_ret) {
          errno = p00_ret;
          perror("can't create thread specific key");
          abort();
        }
        p00_key->p00_done = true;
      }
    }
  }
}

/**
 ** @related p99_tss
 **
 ** @brief Similar to ::tss_delete
 **/
p99_inline
void p99_tss_delete(p99_tss * p00_key) {
  p00_tss_init(p00_key);
  tss_delete(P99_ENCP(p00_key));
  memcpy(p00_key, &P99_LVAL(p99_tss const, .p00_done = false), sizeof *p00_key);
}

/**
 ** @related p99_tss
 **
 ** @brief Similar to ::tss_get
 **/
p99_inline
void* p99_tss_get(p99_tss * p00_key) {
  p00_tss_init(p00_key);
  return tss_get(P99_ENCP(p00_key));
}

/**
 ** @related p99_tss
 **
 ** @brief Similar to <code>tss_set(p00_key, p00_val)</code> but also
 ** calls the destructor on the previous value if necessary.
 **
 ** If old and new thread specific value are equal, nothing is done
 ** and ::thrd_success is returned.
 **
 ** If the underlying call to ::tss_set fails, nothing is changed and
 ** the destructor is not called.
 **
 ** @a p00_val defaults to @c 0 if not given, that is the TSS is
 ** deleted.
 **/
P99_DEFARG_DOCU(p99_tss_set)
p99_inline
P99_WARN_UNUSED_RESULT
int p99_tss_set(p99_tss * p00_key, void *p00_val) {
  int p00_ret = thrd_success;
  void * p00_vol = p99_tss_get(p00_key);
  if (p00_val != p00_vol) {
    p00_ret = tss_set(P99_ENCP(p00_key), p00_val);
    if (p00_ret == thrd_success && p00_vol && p00_key->p99_dtor) {
      p00_key->p99_dtor(p00_vol);
    }
  }
  return p00_ret;
}

#ifndef P00_DOXYGEN
inline
P99_PROTOTYPE(int, p99_tss_set, p99_tss*, void *);
#define p99_tss_set(...) P99_CALL_DEFARG(p99_tss_set, 2, __VA_ARGS__)
#endif

#define p99_tss_set_defarg_1() (0)


/**
 ** @def P99_TSS_DECLARE_LOCAL
 ** @see p99_tss
 ** @brief declare a thread local variable @a NAME of type @a T and
 ** with destructor @a DTOR.
 **
 ** @remark such a variable must be declared in global scope
 **
 ** A hypothetical example for the use of such a variable would be @c
 ** errno:
 **
 ** @code
 ** P99_TSS_DECLARE_LOCAL(int, errno_loc);
 ** #define errno P99_TSS_LOCAL(errno_loc)
 ** @endcode
 **
 ** With just these two lines @c errno always evaluates to an lvalue
 ** representing a thread local object. That is you can use it
 ** everywhere a normal variable of type @c int could be used:
 **
 ** @code
 ** if (errno == EINTR) ...
 ** errno = 0;
 ** my_func(&errno);
 ** @endcode
 **
 ** @a DTOR is optional and corresponds to the destructor function
 ** that is called when the thread finishes. If it is omitted, @c free
 ** is used. In that case you should better use
 ** ::P99_DECLARE_THREAD_LOCAL such that more efficient realizations
 ** than ::p99_tss could be used for the task.
 **
 ** @see P99_TSS_LOCAL to access the variable
 ** @see p99_tss
 **/
P00_DOCUMENT_IDENTIFIER_ARGUMENT(P99_TSS_DECLARE_LOCAL, 1)
#ifdef P00_DOXYGEN
# define P99_TSS_DECLARE_LOCAL(T, NAME, DTOR)                  \
/** @see P99_TSS_LOCAL to access the variable */               \
p99_tss NAME
#else
# define P99_TSS_DECLARE_LOCAL(...)                            \
P99_IF_LT(P99_NARG(__VA_ARGS__), 3)                            \
(P00_TSS_DECLARE_LOCAL(__VA_ARGS__, (free)))                   \
(P00_TSS_DECLARE_LOCAL(__VA_ARGS__))

#define P00_TSS_DECLARE_LOCAL(T, NAME, DTOR)                   \
P99_WEAK(NAME)                                                 \
P00_TSS_DECLARE_LOCAL3(NAME, T, DTOR);                         \
P00_TSS_DEFINE_LOCAL3(NAME, T, DTOR)

# define P99_TSS_DECLARE_LOCAL_EXTERN(...)                     \
P99_IF_LT(P99_NARG(__VA_ARGS__), 3)                            \
(P00_TSS_DECLARE_LOCAL_EXTERN(__VA_ARGS__, (free)))            \
(P00_TSS_DECLARE_LOCAL_EXTERN(__VA_ARGS__))

#define P00_TSS_DECLARE_LOCAL_EXTERN(T, NAME, DTOR)            \
extern                                                         \
P00_TSS_DECLARE_LOCAL3(NAME, T, DTOR)

# define P99_TSS_DEFINE_LOCAL(...)                             \
P99_IF_LT(P99_NARG(__VA_ARGS__), 3)                            \
(P00_TSS_DEFINE_LOCAL(__VA_ARGS__, (free)))                    \
(P00_TSS_DEFINE_LOCAL(__VA_ARGS__))

#define P00_TSS_DEFINE_LOCAL(T, NAME, DTOR)                    \
P00_TSS_DEFINE_LOCAL3(NAME, T, DTOR)


#endif


#define P00_TSS_DECLARE_LOCAL3(NAME, T, DTOR)                  \
/** @see P99_TSS_LOCAL to access the variable */               \
p99_tss NAME;                                                  \
typedef T P99_PASTE3(p00_, NAME, _type)

#define P00_TSS_DEFINE_LOCAL3(NAME, T, DTOR)                   \
p99_tss NAME = { .p99_dtor = (DTOR), }


/**
 ** @def P99_TSS_LOCAL
 ** @see p99_tss
 ** @brief an lvalue expression that returns the thread local instance
 ** of variable @a NAME
 **
 ** @see P99_TSS_DECLARE_LOCAL to declare the variable and for an
 ** example
 ** @see p99_tss
 **/
#define P99_TSS_LOCAL(NAME) (*(P99_PASTE3(p00_, NAME, _type)*)p99_tss_get_alloc(&(NAME), sizeof(P99_PASTE3(p00_, NAME, _type))))


/**
 ** @related p99_tss
 **
 ** @brief Similar to ::p99_tss_get, but also allocates a buffer of @a
 ** p00_size bytes for @a p00_key.
 **
 ** Under normal circumstances this should always return a valid
 ** thread specific buffer, so in some sense this can than be viewed
 ** as if this would be refering to a thread specific statically
 ** allocated variable.
 **/
p99_inline
void* p99_tss_get_alloc(p99_tss * p00_key, size_t p00_size) {
  void * p00_ret = p99_tss_get(p00_key);
  if (P99_UNLIKELY(!p00_ret))
    if (p00_size) {
      p00_ret = calloc(1, p00_size);
      if (p99_tss_set(p00_key, p00_ret) != thrd_success) {
        free(p00_ret);
        p00_ret = 0;
      }
    }
  return p00_ret;
}

#if defined(thread_local) && !defined(P99_EMULATE_THREAD_LOCAL) && !defined(P00_DOXYGEN)

#define P99_DECLARE_THREAD_LOCAL(T, NAME)                      \
P99_WEAK(NAME)                                                 \
thread_local T NAME

#define P99_DECLARE_THREAD_LOCAL_EXTERN(T, NAME)               \
extern                                                         \
thread_local T NAME

#define P99_DEFINE_THREAD_LOCAL(T, NAME)                       \
thread_local T NAME


#define P99_THREAD_LOCAL(NAME) (NAME)

#else
/**
 ** @def P99_DECLARE_THREAD_LOCAL
 ** @brief declare a thread local variable @a NAME of type @a T
 **
 ** @remark Such a variable must be declared in global scope.
 **
 ** @remark This is implemented with a ::thread_local variable if the
 ** platform supports this. Otherwise this uses ::p99_tss and
 ** ::P99_TSS_DECLARE_LOCAL etc underneath.
 **
 ** @see P99_THREAD_LOCAL to access the variable
 ** @see P99_TSS_DECLARE_LOCAL to see examples how this should work
 **/
#define P99_DECLARE_THREAD_LOCAL P99_TSS_DECLARE_LOCAL

#define P99_DECLARE_THREAD_LOCAL_EXTERN P99_TSS_DECLARE_LOCAL_EXTERN

#define P99_DEFINE_THREAD_LOCAL P99_TSS_DEFINE_LOCAL

/**
 ** @def P99_THREAD_LOCAL
 ** @brief an lvalue expression that returns the thread local instance
 ** of variable @a NAME
 **
 ** @see P99_DECLARE_THREAD_LOCAL to declare the variable and for an
 ** example
 **/
#define P99_THREAD_LOCAL P99_TSS_LOCAL
#endif


/**
 ** @}
 **/

#endif
