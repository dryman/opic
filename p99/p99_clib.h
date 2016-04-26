/* This may look like nonsense, but it really is -*- mode: C -*-              */
/*                                                                            */
/* Except for parts copied from previous work and as explicitly stated below, */
/* the authors and copyright holders for this work are as follows:            */
/* (C) copyright  2012, 2014 Jens Gustedt, INRIA, France                      */
/* (C) copyright  2012 William Morris                                         */
/*                                                                            */
/* This file is free software; it is part of the P99 project.                 */
/* You can redistribute it and/or modify it under the terms of the QPL as     */
/* given in the file LICENSE. It is distributed without any warranty;         */
/* without even the implied warranty of merchantability or fitness for a      */
/* particular purpose.                                                        */
/*                                                                            */
#ifndef P99_CLIB_H
#define P99_CLIB_H 1

#include "p99_compiler.h"
#include "p99_new.h"
#include "p99_callback.h"
#include "p99_tss.h"
#include <time.h>

/**
 ** @addtogroup C11_library C11 additions to the C library
 **
 ** @{
 **/

#if __STDC_VERSION__ >= 201112L
# define p00_has_feature_aligned_alloc 1
# define p00_has_extension_aligned_alloc 1
#elif (_XOPEN_SOURCE >= 600) || defined(P00_DOXYGEN)

# if !p99_has_feature(aligned_alloc)

#  define p00_has_feature_aligned_alloc 1
#  define p00_has_extension_aligned_alloc 1

/**
 ** @brief allocation with a chosen alignment
 **
 ** @remark this implementation relies on the presence of @c posix_memalign from POSIX
 **/
p99_inline
void *aligned_alloc(size_t p00_alignment, size_t p00_size) {
  void * p00_ret = 0;
  int err = posix_memalign(&p00_ret, p00_alignment, p00_size);
  /* If there was an error and a fake pointer has been returned, free
     this pointer and set it to 0. This is the only way to return an
     error for this C11 interface. */
  if (err && p00_ret) {
    free(p00_ret);
    p00_ret = 0;
  }
  return p00_ret;
}

#  endif

# endif /* XOPEN */


# define p00_has_feature_quick_exit 1
# define p00_has_extension_quick_exit 1

#if __STDC_VERSION__ < 201112L

/* In both cases this is guaranteed to do the correct
   initialization. */
P99_WEAK(p00_cb)
p99_callback_stack p00_at_quick_exit = P99_LIFO_INITIALIZER(0);

# ifdef __USE_GNU
#  if __GLIBC_PREREQ(2,13)
/* they seem to have implemented quick_exit */
#  else
/**
 ** @brief registers the function pointed to by @a p00_void_func, to be called
 ** without arguments should ::quick_exit be called.
 **/
p99_inline
int at_quick_exit(void (*p00_void_func)(void)) {
  return !P99_CALLBACK_PUSH(&p00_at_quick_exit, p00_void_func);
}

/**
 ** @brief causes normal program termination.
 **
 ** No functions registered by the @c atexit function or signal
 ** handlers registered by the signal function are called.
 **
 ** @see at_quick_exit
 **/
p99_inline
_Noreturn void quick_exit(int status) {
  p99_callback(&p00_at_quick_exit);
  _Exit(status);
}

#  endif
# endif /* USE_GNU */

#endif /* C < C11 */

P99_SETJMP_INLINE(p00_run_at_thrd_exit)
void p00_run_at_thrd_exit(void * li) {
  p99_callback(li);
}

P99_TSS_DECLARE_LOCAL(p99_callback_stack, p00_at_thrd_exit, p00_run_at_thrd_exit);
# define P00_AT_THRD_EXIT P99_TSS_LOCAL(p00_at_thrd_exit)

/**
 ** @brief Add @a p00_void_func to the functions that are called on exit of
 ** the current thread.
 **
 ** This is an extension of the C11 thread functions and works
 ** analogously to the functions ::at_exit and ::at_quick exit.
 **/
p99_inline
int at_thrd_exit(void (*p00_void_func)(void)) {
  return !P99_CALLBACK_PUSH(&P00_AT_THRD_EXIT, p00_void_func);
}

/* Add rudimentary support for the timespec data structure */

/* All this fuss is needed because TIME_UTC isn't allowed to be 0.
   And this is because timespec_get returns failure as 0, and success
   by returning the time base, oh well. */

/* A fallback version if all else fails */

p99_inline
int p00_timespec_get(struct timespec *p00_ts, int p00_base) {
  struct timeval t;
  if (gettimeofday(&t, P99_0(struct timezone*))) {
    errno = 0;
    return 0;
  } else {
    p00_ts->tv_sec = t.tv_sec;
    /* ensure that the usec value is first converted to a nsec
       value of the correct width ... */
    p00_ts->tv_nsec = t.tv_usec;
    /* ... and do the multiplication within that width. */
    p00_ts->tv_nsec *= 1000;
    return p00_base;
  }
}

#ifndef TIME_UTC

/**
 ** @brief The ::timespec_get function sets the interval pointed to by
 ** @a p00_ts to hold the current calendar time based on the specified
 ** time base.
 **
 ** If @a p00_base is ::TIME_UTC, the @c tv_sec member is set to the
 ** number of seconds since an implementation defined epoch, truncated
 ** to a whole value and the @c tv_nsec member is set to the integral
 ** number of nanoseconds, rounded to the resolution of the system
 ** clock.
 **
 ** @return If the ::timespec_get function is successful it returns
 ** the nonzero value @a p00_base; otherwise, it returns zero.
 **
 ** @ingroup C11_library
 **/
p99_inline
int timespec_get(struct timespec *p00_ts, int p00_base);

enum {
  p00_time_base,
  p00_time_utc,
  p00_time_monotonic,
# ifdef CLOCK_PROCESS_CPUTIME_ID
  p00_time_process_cputime_id,
# endif
# ifdef CLOCK_THREAD_CPUTIME_ID
  p00_time_thread_cputime_id,
# endif
  p00_time_base_max
};

/**
 ** @brief expands to an integer constant greater than 0 that
 ** designates the UTC time base since an implementation defined epoch
 **
 ** This is the only time base that is guaranteed to be available by C11.
 **
 ** @see TIME_MONOTONIC
 **/
# define TIME_UTC p00_time_utc

# if defined(CLOCK_REALTIME) || defined(P00_DOXYGEN)

# if defined(CLOCK_MONOTONIC) || defined(P00_DOXYGEN)
/**
 ** @brief expands to an integer constant greater than 0 that
 ** designates a real time clock who's base is usually the boot time
 ** of the processor
 **
 ** If this is available, this denotes a clock that should be a bit
 ** more efficient than ::TIME_UTC, since it usually doesn't have to
 ** perform a call into the OS kernel but may query the processor
 ** directly.
 **
 ** Use this if available and if you are only interested in times
 ** relative to your program execution, e.g for benchmarks.
 **/
#  define TIME_MONOTONIC p00_time_monotonic

# endif
# ifdef CLOCK_PROCESS_CPUTIME_ID
#  define TIME_PROCESS_CPUTIME_ID p00_time_process_cputime_id
# endif
# ifdef CLOCK_THREAD_CPUTIME_ID
#  define TIME_THREAD_CPUTIME_ID p00_time_thread_cputime_id,
# endif

P99_CONST_FUNCTION
p99_inline
clockid_t p00_getclockid(int base) {
  return (base >= p00_time_base_max)
         ? CLOCK_REALTIME
  : (clockid_t const[]) {
    [p00_time_base] = CLOCK_REALTIME,
                      [p00_time_utc] = CLOCK_REALTIME,
# ifdef CLOCK_MONOTONIC
                                       [p00_time_monotonic] = CLOCK_MONOTONIC,
# endif
# ifdef CLOCK_PROCESS_CPUTIME_ID
                                           [p00_time_process_cputime_id] = CLOCK_PROCESS_CPUTIME_ID,
# endif
# ifdef CLOCK_THREAD_CPUTIME_ID
                                               [p00_time_thread_cputime_id] = CLOCK_THREAD_CPUTIME_ID,
# endif
  }[base];
}

/**
 ** @brief The ::timespec_get function sets the interval pointed to by
 ** @a p00_ts to hold the current calendar time based on the specified
 ** time base.
 **
 ** If @a p00_base is ::TIME_UTC, the @c tv_sec member is set to the
 ** number of seconds since an implementation defined epoch, truncated
 ** to a whole value and the @c tv_nsec member is set to the integral
 ** number of nanoseconds, rounded to the resolution of the system
 ** clock.
 **
 ** @return If the ::timespec_get function is successful it returns
 ** the nonzero value @a p00_base; otherwise, it returns zero.
 **/
p99_inline
int timespec_get(struct timespec *p00_ts, int p00_base) {
  clockid_t p00_clkid = p00_getclockid(p00_base);
  if (clock_gettime(p00_clkid, p00_ts)) {
    errno = 0;
    return 0;
  } else
    return p00_base;
}

# elif defined(__ENVIRONMENT_MAC_OS_X_VERSION_MIN_REQUIRED__)
# include <mach/mach_time.h>

# define TIME_MONOTONIC p00_time_monotonic

P99_WEAK(p00_timebase)
double p00_timebase;

P99_WEAK(p00_timeoff_)
struct timespec p00_timeoff_;

P99_WEAK(p00_timeoff)
struct timespec const*const p00_timeoff = &p00_timeoff_;

P99_WEAK(p00_timeonce)
once_flag p00_timeonce = ONCE_FLAG_INIT;

p99_inline
void p00_timeonce_init(void) {
  /* Calibrate the monotonic time */
  mach_timebase_info_data_t p00_tb = P99_INIT;
  mach_timebase_info(&p00_tb);
  p00_timebase = p00_tb.numer;
  p00_timebase /= p00_tb.denom;
  /* Compute the offset of the monotonic time compared to UTC */
  /* Nanosec since system start, or something similar. */
  uint64_t p00_nsec = mach_absolute_time() * p00_timebase;
  p00_timespec_get(&p00_timeoff_, TIME_UTC);
  uint64_t const p00_giga = UINT64_C(1000000000);
  uint64_t p00_epoch = p00_timeoff_.tv_sec * p00_giga + p00_timeoff_.tv_nsec;
  p00_epoch -= p00_nsec;
  p00_timeoff_.tv_sec = p00_epoch / p00_giga;
  p00_timeoff_.tv_nsec = p00_epoch % p00_giga;
}

p99_inline
int timespec_get(struct timespec *p00_ts, int p00_base) {
  call_once(&p00_timeonce, p00_timeonce_init);
  uint64_t p00_nsec = mach_absolute_time() * p00_timebase;
  register uint64_t const p00_giga = UINT64_C(1000000000);
  p00_ts->tv_sec = p00_nsec / p00_giga;
  p00_ts->tv_nsec = p00_nsec % p00_giga;
  if (p00_base != TIME_MONOTONIC) {
    p00_ts->tv_sec += p00_timeoff->tv_sec;
    p00_ts->tv_nsec += p00_timeoff->tv_nsec;
    while (p00_ts->tv_nsec >= p00_giga) {
      p00_ts->tv_nsec -= p00_giga;
      ++p00_ts->tv_sec;
    }
  }
  return p00_base;
}
# else
# warning only low resolution gettimeofday found
# define timespec_get p00_timespec_get
# endif
#endif

/**
 ** @}
 **/

#endif
