/* This may look like nonsense, but it really is -*- mode: C -*-              */
/*                                                                            */
/* Except for parts copied from previous work and as explicitly stated below, */
/* the authors and copyright holders for this work are as follows:            */
/* (C) copyright  2011-2014 Jens Gustedt, INRIA, France                       */
/* (C) copyright  2012 William Morris                                         */
/*                                                                            */
/* This file is free software; it is part of the P99 project.                 */
/* You can redistribute it and/or modify it under the terms of the QPL as     */
/* given in the file LICENSE. It is distributed without any warranty;         */
/* without even the implied warranty of merchantability or fitness for a      */
/* particular purpose.                                                        */
/*                                                                            */
#ifndef P99_THREADS_POSIX_H
#define P99_THREADS_POSIX_H 1

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

/**
 ** @brief expands to a value that can be used to initialize an object
 ** of type ::p99_once_flag
 **
 ** A characteristic of this implementation is that initialization is
 ** equivalent to the default initialization by @c 0, meaning in
 ** particular that a ::p99_once_flag that is of static or
 ** thread-local storage duration is by default correctly initialized.
 ** This property is subsequently used in the fallback
 ** implementation of thread local storage.
 **
 ** @see p99_once_flag
 **/
#define P99_ONCE_FLAG_INIT { { 0 } }

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
 ** condition variable
 **
 ** @remark This type is just a wrapper around a POSIX @c pthread_cond_t.
 **/
P99_ENC_DECLARE(pthread_cond_t, cnd_t);

typedef struct p00_thrd p00_thrd;
/**
 ** @brief complete object type that holds an identifier for a thread
 **
 ** @remark Although this implementation of threads is based on
 ** POSIX, this thread id type is not compatible with POSIX @c
 ** pthread_t.
 **
 ** The use of the P99 implementation will result in all threads, even those
 ** not created through ::thrd_create, having a distinct
 ** object of type ::thrd_t as their ID. This ID is accessible through
 ** ::thrd_current.
 **/
P99_ENC_DECLARE(struct p00_thrd*, thrd_t);

/**
 ** @brief complete object type that holds an identifier for a mutex
 **
 ** @remark This type is just a wrapper around a POSIX @c pthread_mutex_t.
 **/
P99_ENC_DECLARE(pthread_mutex_t, mtx_t);

/**
 ** @brief function pointer type <code>int (*)(void*)</code> that is
 ** passed to ::thrd_create to create a new thread
 ** @see thrd_t
 */
typedef int (*thrd_start_t)(void*);



/**
 ** @}
 **/

struct p00_thrd {
  atomic_flag p00_detached;
  unsigned p00_foreign;
  int p00_ret;
  pthread_t p00_id;
  union {
    struct {
      thrd_start_t p00_func;
      void *p00_arg;
    } p00_init;
    jmp_buf p00_jmp;
  } p00_ovrl;
};

/**
 ** @addtogroup thread_enum
 ** @{
 **/

/**
 ** @brief C11 mutex types
 **/
enum mtx_type {
  /**
   ** @brief passed to ::mtx_init to create a mutex object that supports
   ** neither timeout nor test and return
   **/
  mtx_plain = 0,

  /**
   ** @brief passed to ::mtx_init to create a mutex object that
   ** supports recursive locking
   **/
  mtx_recursive = 1,

  /**
   ** @brief passed to ::mtx_init to create a mutex object that supports timeout
   **
   ** In this implementation this feature is always provided.
   **/
  mtx_timed = 2,

  /**
   ** @brief passed to ::mtx_init to create a mutex object that
   ** deadlocks when locked twice
   **
   ** Consider a deadlock as a feature, here. Without this locking a
   ** mutex again is just undefined behavior, so anything could
   ** happen.
   **
   ** @remark This is an extension that comes with POSIX. Don't use it
   ** if you want your code to be portable outside POSIX.
   **/
  mtx_normal = 4,

  /**
   ** @brief passed to ::mtx_init to create a mutex object that
   ** returns an error when locked twice
   **
   ** @remark This is an extension that comes with POSIX. Don't use it
   ** if you want your code to be portable outside POSIX.
   **/
  mtx_errorcheck = 8,

  /**
   ** @brief used internally
   **
   ** This is meant to accumulate all extra flags that could be
   ** distinguished with POSIX mutex. This is not a valid flag to pass
   ** to ::mtx_init.
   **/
  mtx_extras = (mtx_normal | mtx_errorcheck | mtx_recursive),
};


/**
 ** @}
 **/

// 7.26.2 Initialization functions

/**
 ** @related thrd_t
 **/
p99_inline
void thrd_yield(void) {
  if (P99_UNLIKELY(sched_yield())) errno = 0;
}

/* Tentative definitions for global variables. This has the advantage
   that this defines weak symbols and we avoid to have to create a
   specific library. */
P99_DECLARE_THREAD_LOCAL(p00_thrd *, p00_thrd_local);

#define P00_THRD_LOCAL P99_THREAD_LOCAL(p00_thrd_local)

P99_WEAK(p00_foreign_nb)
_Atomic(size_t) p00_foreign_nb;

P99_WEAK(p00_foreign_tab)
p00_thrd ** p00_foreign_tab;

P99_WEAK(p00_foreign_cleanup)
void p00_foreign_cleanup(void) {
  size_t p00_foreign = atomic_load_explicit(&p00_foreign_nb, memory_order_consume);
  p00_thrd ** p00_thrd = p00_foreign_tab;
  p00_foreign_tab = 0;
  if (p00_foreign) {
    /* Ensure that all data is synchronized with all threads, not only
       with the last one that changed p00_foreign_nb. */
    atomic_thread_fence(memory_order_seq_cst);
    for (size_t p00_i = 0; p00_i < p00_foreign; ++p00_i) {
      if (!pthread_equal(p00_thrd[p00_i]->p00_id, pthread_self()))
        fputs("found foreign thread\n", stderr);
      free(p00_thrd[p00_i]);
    }
  }
  free(p00_thrd);
}

/**
 ** @related thrd_t
 **
 ** @return identifier of the thread that called it
 **/
p99_inline
thrd_t thrd_current(void) {
  p00_thrd * p00_loc = P00_THRD_LOCAL;
  if (P99_UNLIKELY(!p00_loc)) {
    size_t p00_nb = atomic_fetch_add_explicit(&p00_foreign_nb, 1, memory_order_acq_rel);
    if (!p00_nb) atexit(p00_foreign_cleanup);
    if ((p00_nb^(p00_nb-1)) == (p00_nb+(p00_nb-1))) {
      p00_foreign_tab = realloc(p00_foreign_tab, sizeof(p00_thrd*[2*(p00_nb+1)]));
    }
    p00_loc = malloc(sizeof *p00_loc);
    p00_foreign_tab[p00_nb] = p00_loc;
    *p00_loc = (p00_thrd) {
      .p00_id = pthread_self(),
       .p00_foreign = p00_nb + 1,
    };
    P00_THRD_LOCAL = p00_loc;
    if (p00_nb) {
      union {
        unsigned char raw[16];
        pthread_t thrd;
        unsigned long long ull;
      } id = { .raw = { 0 } };
      id.thrd = p00_loc->p00_id;
      fprintf(stderr, "foreign thread %llu is %zu\n", id.ull, p00_nb + 1);
    }
  }
  return (thrd_t)P99_ENC_INIT(p00_loc);
}

/**
 ** @related thrd_t
 **
 ** @return @c 0 if the thread @a p00_thr0 and the thread @a p00_thr1 refer to
 ** different threads. Otherwise a nonzero value is returned.
 **/
P99_CONST_FUNCTION
p99_inline
int thrd_equal(thrd_t p00_thr0, thrd_t p00_thr1) {
  return P99_ENC(p00_thr0) ==  P99_ENC(p00_thr1);
}


// 7.26.3 Condition variable functions

/**
 ** @related cnd_t
 **
 ** @return ::thrd_success on success, or ::thrd_error if the request
 ** could not be honored.
 **/
P99_WARN_UNUSED_RESULT
p99_inline
int cnd_broadcast(cnd_t *p00_cond) {
  return pthread_cond_broadcast(&P99_ENCP(p00_cond)) ? thrd_error : thrd_success;
}

/**
 ** @related cnd_t
 **/
p99_inline
void cnd_destroy(cnd_t *p00_cond) {
  (void)pthread_cond_destroy(&P99_ENCP(p00_cond));
}

/**
 ** @related cnd_t
 **
 ** @return The ::cnd_init function returns ::thrd_success on success,
 ** or ::thrd_nomem if no memory could be allocated for the newly
 ** created condition, or ::thrd_error if the request could not be
 ** honored.
 **/
P99_WARN_UNUSED_RESULT
p99_inline
int cnd_init(cnd_t *p00_cond) {
  int p00_ret = pthread_cond_init(&P99_ENCP(p00_cond), 0);
  switch (p00_ret) {
  case 0:         return thrd_success;
  case ENOMEM:    return thrd_nomem;
  default:        return thrd_error;
  }
}

/**
 ** @related cnd_t
 **
 ** @return ::thrd_success on success, or ::thrd_error if the request
 ** could not be honored.
 **/
P99_WARN_UNUSED_RESULT
p99_inline
int cnd_signal(cnd_t *p00_cond) {
  return pthread_cond_signal(&P99_ENCP(p00_cond)) ? thrd_error : thrd_success;
}

#if (POSIX_TIMEOUTS > 0) || !defined(POSIX_TIMEOUTS)

/**
 ** @related cnd_t
 **
 ** @return ::thrd_success upon success, or ::thrd_timedout if the
 ** time specified in the call was reached without acquiring the
 ** requested resource, or ::thrd_error if the request could not be
 ** honored.
 **/
P99_WARN_UNUSED_RESULT
p99_inline
int cnd_timedwait(cnd_t *restrict p00_cond, mtx_t *restrict p00_mtx, const struct timespec *restrict p00_ts) {
  int p00_ret = pthread_cond_timedwait(&P99_ENCP(p00_cond), &P99_ENCP(p00_mtx), p00_ts);
  switch (p00_ret) {
  case 0:         return thrd_success;
  case ETIMEDOUT: return thrd_timedout;
  default:        return thrd_error;
  };
}

#endif

/**
 ** @related cnd_t
 **
 ** @return ::thrd_success on success, or ::thrd_error if the request
 ** could not be honored.
 **/
P99_WARN_UNUSED_RESULT
p99_inline
int cnd_wait(cnd_t *p00_cond, mtx_t *p00_mtx) {
  return pthread_cond_wait(&P99_ENCP(p00_cond), &P99_ENCP(p00_mtx)) ? thrd_error : thrd_success;
}

// 7.26.4 Mutex functions

/**
 ** @related mtx_t
 **/
p99_inline
void mtx_destroy(mtx_t *p00_mtx) {
  (void)pthread_mutex_destroy(&P99_ENCP(p00_mtx));
}

/**
 ** @related mtx_t
 **
 ** @param p00_mtx A pointer to an unitialized mutex object
 ** @param p00_type One of the constants in ::mtx_type
 **
 ** @return ::thrd_success on success, or ::thrd_error if the request
 ** could not be honored.
 **/
P99_WARN_UNUSED_RESULT
p99_inline
int mtx_init(mtx_t *p00_mtx, int p00_type) {
  if (p00_type & mtx_extras) {
    pthread_mutexattr_t p00_attr;
    int p00_ret = pthread_mutexattr_init(&p00_attr);
    if (P99_UNLIKELY(p00_ret)) return thrd_error;
    switch (p00_type & mtx_extras) {
    case mtx_normal: p00_ret = PTHREAD_MUTEX_NORMAL; break;
    case mtx_errorcheck: p00_ret = PTHREAD_MUTEX_ERRORCHECK; break;
    case mtx_recursive: p00_ret = PTHREAD_MUTEX_RECURSIVE; break;
    default: return thrd_error;
    }
    p00_ret = pthread_mutexattr_settype(&p00_attr, p00_ret);
    if (P99_UNLIKELY(p00_ret)) return thrd_error;
    p00_ret = pthread_mutex_init(&P99_ENCP(p00_mtx), &p00_attr);
    if (P99_UNLIKELY(p00_ret)) return thrd_error;
  } else {
    int p00_ret = pthread_mutex_init(&P99_ENCP(p00_mtx), 0);
    if (P99_UNLIKELY(p00_ret)) return thrd_error;
  }
  return thrd_success;
}

/**
 ** @related mtx_t
 ** @return ::thrd_success on success, or ::thrd_error if the request
 ** could not be honored.
 **/
P99_WARN_UNUSED_RESULT
p99_inline
int mtx_lock(mtx_t *p00_mtx) {
  return pthread_mutex_lock(&P99_ENCP(p00_mtx)) ? thrd_error : thrd_success;
}

#if (POSIX_TIMEOUTS > 0) || !defined(POSIX_TIMEOUTS)

/**
 ** @related mtx_t
 **
 ** @return ::thrd_success upon success, or ::thrd_timedout if the
 ** time specified in the call was reached without acquiring the
 ** requested resource, or ::thrd_error if the request could not be
 ** honored.
 **/
P99_WARN_UNUSED_RESULT
p99_inline
int mtx_timedlock(mtx_t *restrict p00_mtx, const struct timespec *restrict p00_ts) {
  int p00_ret = pthread_mutex_timedlock(&P99_ENCP(p00_mtx), p00_ts);
  switch (p00_ret) {
  case 0:         return thrd_success;
  case ETIMEDOUT: return thrd_timedout;
  default:        return thrd_error;
  };
}

#endif

/**
 ** @related mtx_t
 **
 ** @return ::thrd_success on success, or ::thrd_busy if the resource
 ** requested is already in use, or ::thrd_error if the request could
 ** not be honored.
 **/
p99_inline
int mtx_trylock(mtx_t *p00_mtx) {
  int p00_ret = pthread_mutex_trylock(&P99_ENCP(p00_mtx));
  switch (p00_ret) {
  case 0:         return thrd_success;
  case EBUSY:     return thrd_busy;
  default:        return thrd_error;
  };
}

/**
 ** @related mtx_t
 ** @return ::thrd_success on success, or ::thrd_error if the request
 ** could not be honored.
 **/
P99_WARN_UNUSED_RESULT
p99_inline
int mtx_unlock(mtx_t *p00_mtx) {
  return pthread_mutex_unlock(&P99_ENCP(p00_mtx)) ? thrd_error : thrd_success;
}


P99_SETJMP_INLINE(p00_thrd_create)
void * p00_thrd_create(void* p00_context);

/**
 ** @related thrd_t
 **
 ** @return ::thrd_success on success, or ::thrd_nomem if no memory
 ** could be allocated for the thread requested, or ::thrd_error if
 ** the request could not be honored.
 **/
P99_WARN_UNUSED_RESULT
p99_inline
int thrd_create(thrd_t *p00_thr, thrd_start_t p00_func, void *p00_arg) {
  p00_thrd * p00_cntxt = malloc(sizeof *p00_cntxt);
  if (!p00_cntxt) return thrd_nomem;
  *p00_cntxt = (p00_thrd const) {
    .p00_ovrl = {
      .p00_init = {
        .p00_func = p00_func,
        .p00_arg = p00_arg,
      },
    },
    .p00_detached = ATOMIC_FLAG_INIT,
  };
  int p00_ret = pthread_create(&p00_cntxt->p00_id, 0, p00_thrd_create, p00_cntxt);
  if (P99_UNLIKELY(p00_ret)) {
    free(p00_cntxt);
    switch (p00_ret) {
    case ENOMEM:    return thrd_nomem;
    default:        return thrd_error;
    };
  } else {
    P99_ENCP(p00_thr) = p00_cntxt;
    return thrd_success;
  }
}

/**
 ** @related thrd_t
 **
 ** @return ::thrd_success on success, or ::thrd_error if the request
 ** could not be honored.
 **/
P99_WARN_UNUSED_RESULT
p99_inline
int thrd_detach(thrd_t p00_thr) {
  /* The thread is not yet detached so its pthread id is still
     valid. If it already has finished, this will just free the
     resources that pthread holds for it. */
  int p00_ret = pthread_detach(P99_ENC(p00_thr)->p00_id) ? thrd_error : thrd_success;
  if (atomic_flag_test_and_set_explicit(&P99_ENC(p00_thr)->p00_detached, memory_order_acq_rel)) {
    /* The thread has already finished. Free the state, since nobody
       will join it, anyhow. */
    free(P99_ENC(p00_thr));
    return thrd_success;
  } else {
    return p00_ret;
  }
}

#ifdef P00_DOXYGEN
/**
 ** @related thrd_t
 **/
p99_inline void thrd_exit(int p00_res);
#else
p99_inline
_Noreturn
void thrd_exit(int p00_res) {
  p00_thrd * p00_cntxt = P00_THRD_LOCAL;
  if (P99_LIKELY(p00_cntxt)) {
    if (!p00_cntxt->p00_foreign) {
      p00_cntxt->p00_ret = p00_res;
      longjmp(p00_cntxt->p00_ovrl.p00_jmp, 1);
    } else {
      free(p00_cntxt);
      P00_THRD_LOCAL = 0;
    }
  }
  /* should only be reached by threads that where created directly
     with pthreads, e.g main */
  fprintf(stderr,
          "P99: We are exiting a foreign thread (main?) with error code %d\n"
          "P99: There is no consistent way we can transmit that code to the environment\n",
          p00_res);
  pthread_exit(0);
}
#endif

#if defined(P99_INTERCEPT_MAIN) || defined(P00_DOXYGEN)

/**
 ** @brief A replacement name for the users @c main function,
 ** experimental
 **
 ** @remark compile with @c -DP99_INTERCEPT_MAIN to enable this
 ** feature
 **
 ** If compiled with the above macro definition, the users @c main
 ** function is silently renamed to ::p99_threads_main and a stub @c main is
 ** provided. That stub function will not do much more than creating a
 ** separate thread running ::p99_threads_main as the user would expect it,
 ** and then exit the thread of that stub @c main function.
 **
 ** The purpose is to ensure that all threads are C11 threads, and not
 ** only POSIX threads.
 **
 ** @deprecated The mechanism to launch this is fragile, avoid it if
 ** possible.
 **/
int p99_threads_main(int, char*[]);

struct p00_threads_main_arg {
  int p00_argc;
  char**p00_argv;
};

P99_WEAK(p00_threads_main)
int p00_threads_main(void* p00_arg) {
  struct p00_threads_main_arg *p00_a = p00_arg;
  int p00_argc = p00_a->p00_argc;
  char**p00_argv = p00_a->p00_argv;
  free(p00_arg);
  /* To have the same behavior as prescribed by the standard, we have
     to exit the whole process if main returns. The only thing that we
     wouldn't be able to emulate is the fact that leaving main without
     return statement is permitted. But the compiler should warn the
     user about that. */
  int p00_ret = p99_threads_main(p00_argc, p00_argv);
  fprintf(stderr, "exiting main thread with code %d", p00_ret);
  fflush(0);
  exit(p00_ret);
}

P99_MAIN_INTERCEPT(p99_threads_main) {
  thrd_t id = P99_INIT;
  struct p00_threads_main_arg * p00_arg = malloc(sizeof *p00_arg);
  *p00_arg = (struct p00_threads_main_arg) {
    .p00_argc = *p00_argc,
     .p00_argv = *p00_argv,
  };
  thrd_create(&id, p00_threads_main, p00_arg);
  thrd_detach(id);
  pthread_exit(0);
}

#undef main
#define main p99_threads_main
#endif



/**
 ** @related thrd_t
 ** @return ::thrd_success on success, or ::thrd_error if the request
 ** could not be honored.
 **/
P99_WARN_UNUSED_RESULT
p99_inline
int thrd_join(thrd_t p00_thr, int *p00_res) {
  void *p00_res0;
  if (P99_UNLIKELY(pthread_join(P99_ENC(p00_thr)->p00_id, &p00_res0))) return thrd_error;
  if (p00_res) *p00_res = P99_ENC(p00_thr)->p00_ret;
  free(P99_ENC(p00_thr));
  return thrd_success;
}

/**
 ** @related thrd_t
 **
 ** @return @c 0 if the requested time has elapsed, @c -1 if it has
 ** been interrupted by a signal, or another negative value if it fails.
 ** Consistent with that, this implementation uses ::thrd_success,
 ** ::thrd_intr and ::thrd_error as return values.
 **/
P99_WARN_UNUSED_RESULT
p99_inline
int thrd_sleep(const struct timespec *p00_duration, struct timespec *p00_remaining) {
  errno = 0;
  int p00_ret = nanosleep(p00_duration, p00_remaining);
  if (p00_ret) {
    p00_ret = (errno == EINTR) ? thrd_intr : thrd_error;
    errno = 0;
    return p00_ret;
  } else return thrd_success;
}

/*
  This is static inline because of the following message from gcc:

   sorry, unimplemented: function ‘p00_thrd_create’ can never be inlined because it uses setjmp
*/
P99_WARN_UNUSED_RESULT
P99_SETJMP_INLINE(p00_thrd_create)
void * p00_thrd_create(void* p00_context) {
  p00_thrd * p00_cntxt = p00_context;
  P00_THRD_LOCAL = p00_cntxt;
  {
    thrd_start_t p00_func = p00_cntxt->p00_ovrl.p00_init.p00_func;
    void * p00_arg = p00_cntxt->p00_ovrl.p00_init.p00_arg;
    if (!setjmp(p00_cntxt->p00_ovrl.p00_jmp)) {
      p00_cntxt->p00_ret = p00_func(p00_arg);
    }
    if (atomic_flag_test_and_set_explicit(&p00_cntxt->p00_detached, memory_order_acq_rel)) {
      free(p00_cntxt);
    }
  }
  P00_THRD_LOCAL = 0;
  return 0;
}


/**
 ** @}
 **/


#endif /* P99_THREADS_POSIX_H */
