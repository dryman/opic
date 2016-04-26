/* This may look like nonsense, but it really is -*- mode: C -*-              */
/*                                                                            */
/* Except for parts copied from previous work and as explicitly stated below, */
/* the author and copyright holder for this work is                           */
/* (C) copyright  2012 Jens Gustedt, INRIA, France                            */
/*                                                                            */
/* This file is free software; it is part of the P99 project.                 */
/* You can redistribute it and/or modify it under the terms of the QPL as     */
/* given in the file LICENSE. It is distributed without any warranty;         */
/* without even the implied warranty of merchantability or fitness for a      */
/* particular purpose.                                                        */
/*                                                                            */
#ifndef     P99_C99_THROW_H_
# define    P99_C99_THROW_H_

#include "p99_try.h"

/**
 ** @file
 **
 ** This file is an optional component of P99. The macros that are
 ** defined here provide wrappers to C library functions and throw
 ** errors if the function call fails.
 **/

/**
 ** @addtogroup library_wrappers Wrappers for C library functions
 **
 ** @brief Wrap library functions such that they throw an exception on error
 **
 ** All macros here have the form of @c NAME_throw, where @c NAME is a
 ** C library function. All these macros are classified according to
 ** one of the conventions that are present in the C library on the
 ** strategies how errors are returned.
 **
 ** Eg. to have a @c malloc that always checks the return do
 ** @code
 ** double (*A)[n] = malloc_throw(sizeof *A);
 ** @endcode
 **
 ** In case you want just blend the names of the system calls you
 ** could do yourself for the ones that you want something like
 ** @code
 ** #define malloc malloc_throw
 **
 ** ...
 ** double (*A)[n] = malloc(sizeof *A);
 ** @endcode
 **
 **
 ** @warning Since these are just too many different calls only few of
 ** them have been tested. If you find a classification error please
 ** let us know.
 **
 ** @{
 **/

#define P00_LIB_WRAP_DOC(NAME) /** @brief A wrapper arround NAME that throws an exception on error */

/* fenv.h */
P00_LIB_WRAP_DOC(feclearexcept)
#define feclearexcept_throw(...) P99_THROW_CALL_ZERO(feclearexcept, EINVAL, __VA_ARGS__)
P00_LIB_WRAP_DOC(fegetexceptflag)
#define fegetexceptflag_throw(...) P99_THROW_CALL_ZERO(fegetexceptflag, EINVAL, __VA_ARGS__)
P00_LIB_WRAP_DOC(feraiseexcept)
#define feraiseexcept_throw(...) P99_THROW_CALL_ZERO(feraiseexcept, EINVAL, __VA_ARGS__)
P00_LIB_WRAP_DOC(fesetexceptflag)
#define fesetexceptflag_throw(...) P99_THROW_CALL_ZERO(fesetexceptflag, EINVAL, __VA_ARGS__)
P00_LIB_WRAP_DOC(fetestexcept)
#define fetestexcept_throw(...) P99_THROW_CALL_ZERO(fetestexcept, EINVAL, __VA_ARGS__)
P00_LIB_WRAP_DOC(fegetround)
#define fegetround_throw(...) P99_THROW_CALL_ZERO(fegetround, EINVAL, __VA_ARGS__)
P00_LIB_WRAP_DOC(fesetround)
#define fesetround_throw(...) P99_THROW_CALL_ZERO(fesetround, EINVAL, __VA_ARGS__)
P00_LIB_WRAP_DOC(fegetenv)
#define fegetenv_throw(...) P99_THROW_CALL_ZERO(fegetenv, EINVAL, __VA_ARGS__)
P00_LIB_WRAP_DOC(feholdexcept)
#define feholdexcept_throw(...) P99_THROW_CALL_ZERO(feholdexcept, EINVAL, __VA_ARGS__)
P00_LIB_WRAP_DOC(fesetenv)
#define fesetenv_throw(...) P99_THROW_CALL_ZERO(fesetenv, EINVAL, __VA_ARGS__)
P00_LIB_WRAP_DOC(feupdateenv)
#define feupdateenv_throw(...) P99_THROW_CALL_ZERO(feupdateenv, EINVAL, __VA_ARGS__)

/* inttypes.h */
P00_LIB_WRAP_DOC(strtoimax)
#define strtoimax_throw(...) P99_THROW_CALL_RANGE(strtoimax, __VA_ARGS__)
P00_LIB_WRAP_DOC(strtoumax)
#define strtoumax_throw(...) P99_THROW_CALL_RANGE(strtoumax, __VA_ARGS__)
P00_LIB_WRAP_DOC(wcstoimax)
#define wcstoimax_throw(...) P99_THROW_CALL_RANGE(wcstoimax, __VA_ARGS__)
P00_LIB_WRAP_DOC(wcstoumax)
#define wcstoumax_throw(...) P99_THROW_CALL_RANGE(wcstoumax, __VA_ARGS__)
//#define imaxabs_throw(...) P99_THROW_CALL_NEG(imaxabs, EINVAL, __VA_ARGS__)
//#define imaxdiv_throw(...) P99_THROW_CALL_NEG(imaxdiv, EINVAL, __VA_ARGS__)

/* math.h has nothing that can be caught */

/* signal.h */
// void (*signal(int sig, void (*func)(int)))(int);
P00_LIB_WRAP_DOC(raise)
#define raise_throw(...) P99_THROW_CALL_ZERO(raise, EINVAL, __VA_ARGS__)

/* stdarg.h has nothing that can be caught */

/* stdio.h */
P00_LIB_WRAP_DOC(fclose)
#define fclose_throw(...) P99_THROW_CALL_ZERO(fclose, EINVAL, __VA_ARGS__)
P00_LIB_WRAP_DOC(fflush)
#define fflush_throw(...) P99_THROW_CALL_ZERO(fflush, EINVAL, __VA_ARGS__)
P00_LIB_WRAP_DOC(fgetc)
#define fgetc_throw(...) P99_THROW_CALL_NEG(fgetc, EINVAL, __VA_ARGS__)
P00_LIB_WRAP_DOC(fgetpos)
#define fgetpos_throw(...) P99_THROW_CALL_ZERO(fgetpos, EINVAL, __VA_ARGS__)
P00_LIB_WRAP_DOC(fgets)
#define fgets_throw(...) P99_THROW_CALL_VOIDP(fgets, EINVAL, __VA_ARGS__)
P00_LIB_WRAP_DOC(fopen)
#define fopen_throw(...) P99_THROW_CALL_VOIDP(fopen, EINVAL, __VA_ARGS__)
P00_LIB_WRAP_DOC(fprintf)
#define fprintf_throw(...) P99_THROW_CALL_NEG(fprintf, EINVAL, __VA_ARGS__)
P00_LIB_WRAP_DOC(fputc)
#define fputc_throw(...) P99_THROW_CALL_NEG(fputc, EINVAL, __VA_ARGS__)
P00_LIB_WRAP_DOC(fputs)
#define fputs_throw(...) P99_THROW_CALL_NEG(fputs, EINVAL, __VA_ARGS__)
P00_LIB_WRAP_DOC(freopen)
#define freopen_throw(...) P99_THROW_CALL_VOIDP(freopen, EINVAL, __VA_ARGS__)
P00_LIB_WRAP_DOC(fscanf)
#define fscanf_throw(...) P99_THROW_CALL_NEG(fscanf, EINVAL, __VA_ARGS__)
P00_LIB_WRAP_DOC(fseek)
#define fseek_throw(...) P99_THROW_CALL_ZERO(fseek, EINVAL, __VA_ARGS__)
P00_LIB_WRAP_DOC(fsetpos)
#define fsetpos_throw(...) P99_THROW_CALL_ZERO(fsetpos, EINVAL, __VA_ARGS__)
P00_LIB_WRAP_DOC(ftell)
#define ftell_throw(...) P99_THROW_CALL_NEG(ftell, EINVAL, __VA_ARGS__)
P00_LIB_WRAP_DOC(getc)
#define getc_throw(...) P99_THROW_CALL_NEG(getc, EINVAL, __VA_ARGS__)
P00_LIB_WRAP_DOC(getchar)
#define getchar_throw(...) P99_THROW_CALL_NEG(getchar, EINVAL, __VA_ARGS__)
P00_LIB_WRAP_DOC(printf)
#define printf_throw(...) P99_THROW_CALL_NEG(printf, EINVAL, __VA_ARGS__)
P00_LIB_WRAP_DOC(putc)
#define putc_throw(...) P99_THROW_CALL_NEG(putc, EINVAL, __VA_ARGS__)
P00_LIB_WRAP_DOC(putchar)
#define putchar_throw(...) P99_THROW_CALL_NEG(putchar, EINVAL, __VA_ARGS__)
P00_LIB_WRAP_DOC(puts)
#define puts_throw(...) P99_THROW_CALL_NEG(puts, EINVAL, __VA_ARGS__)
P00_LIB_WRAP_DOC(remove)
#define remove_throw(...) P99_THROW_CALL_NEG(remove, EINVAL, __VA_ARGS__)
P00_LIB_WRAP_DOC(rename)
#define rename_throw(...) P99_THROW_CALL_NEG(rename, EINVAL, __VA_ARGS__)
P00_LIB_WRAP_DOC(scanf)
#define scanf_throw(...) P99_THROW_CALL_NEG(scanf, EINVAL, __VA_ARGS__)
P00_LIB_WRAP_DOC(setvbuf)
#define setvbuf_throw(...) P99_THROW_CALL_ZERO(setvbuf, EINVAL, __VA_ARGS__)
P00_LIB_WRAP_DOC(snprintf)
#define snprintf_throw(...) P99_THROW_CALL_NEG(snprintf, EINVAL, __VA_ARGS__)
P00_LIB_WRAP_DOC(sprintf)
#define sprintf_throw(...) P99_THROW_CALL_NEG(sprintf, EINVAL, __VA_ARGS__)
P00_LIB_WRAP_DOC(sscanf)
#define sscanf_throw(...) P99_THROW_CALL_NEG(sscanf, EINVAL, __VA_ARGS__)
P00_LIB_WRAP_DOC(tmpfile)
#define tmpfile_throw(...) P99_THROW_CALL_VOIDP(tmpfile, EINVAL, __VA_ARGS__)
P00_LIB_WRAP_DOC(tmpnam)
#define tmpnam_throw(...) P99_THROW_CALL_VOIDP(tmpnam, EINVAL, __VA_ARGS__)
P00_LIB_WRAP_DOC(ungetc)
#define ungetc_throw(...) P99_THROW_CALL_NEG(ungetc, EINVAL, __VA_ARGS__)
P00_LIB_WRAP_DOC(vfprintf)
#define vfprintf_throw(...) P99_THROW_CALL_NEG(vfprintf, EINVAL, __VA_ARGS__)
P00_LIB_WRAP_DOC(vfscanf)
#define vfscanf_throw(...) P99_THROW_CALL_NEG(vfscanf, EINVAL, __VA_ARGS__)
P00_LIB_WRAP_DOC(vprintf)
#define vprintf_throw(...) P99_THROW_CALL_NEG(vprintf, EINVAL, __VA_ARGS__)
P00_LIB_WRAP_DOC(vscanf)
#define vscanf_throw(...) P99_THROW_CALL_NEG(vscanf, EINVAL, __VA_ARGS__)
P00_LIB_WRAP_DOC(vsnprintf)
#define vsnprintf_throw(...) P99_THROW_CALL_NEG(vsnprintf, EINVAL, __VA_ARGS__)
P00_LIB_WRAP_DOC(vsprintf)
#define vsprintf_throw(...) P99_THROW_CALL_NEG(vsprintf, EINVAL, __VA_ARGS__)
P00_LIB_WRAP_DOC(vsscanf)
#define vsscanf_throw(...) P99_THROW_CALL_NEG(vsscanf, EINVAL, __VA_ARGS__)
/* the following are void functions or the capture of the return value
   makes no sense, here. */
//#define clearerr_throw(...) P99_THROW_CALL_NEG(clearerr, EINVAL, __VA_ARGS__)
//#define feof_throw(...) P99_THROW_CALL_NEG(feof, EINVAL, __VA_ARGS__)
//#define ferror_throw(...) P99_THROW_CALL_NEG(ferror, EINVAL, __VA_ARGS__)
//#define fread_throw(...) P99_THROW_CALL_NEG(fread, EINVAL, __VA_ARGS__)
//#define fwrite_throw(...) P99_THROW_CALL_NEG(fwrite, EINVAL, __VA_ARGS__)
//#define perror_throw(...) P99_THROW_CALL_NEG(perror, EINVAL, __VA_ARGS__)
//#define rewind_throw(...) P99_THROW_CALL_NEG(rewind, EINVAL, __VA_ARGS__)
//#define setbuf_throw(...) P99_THROW_CALL_NEG(setbuf, EINVAL, __VA_ARGS__)


/* stdlib.h */
P00_LIB_WRAP_DOC(aligned_alloc)
#define aligned_alloc_throw(...) P99_THROW_CALL_VOIDP(aligned_alloc, thrd_nomem, __VA_ARGS__)
P00_LIB_WRAP_DOC(at_quick_exit)
#define at_quick_exit_throw(...) P99_THROW_CALL_ZERO(at_quick_exit, EINVAL, __VA_ARGS__)
P00_LIB_WRAP_DOC(atexit)
#define atexit_throw(...) P99_THROW_CALL_ZERO(atexit, EINVAL, __VA_ARGS__)
P00_LIB_WRAP_DOC(calloc)
#define calloc_throw(...) P99_THROW_CALL_VOIDP(calloc, thrd_nomem, __VA_ARGS__)
P00_LIB_WRAP_DOC(getenv)
#define getenv_throw(...) P99_THROW_CALL_NEG(getenv, EINVAL, __VA_ARGS__)
P00_LIB_WRAP_DOC(malloc)
#define malloc_throw(...) P99_THROW_CALL_VOIDP(malloc, thrd_nomem, __VA_ARGS__)
P00_LIB_WRAP_DOC(mblen)
#define mblen_throw(...) P99_THROW_CALL_NEG(mblen, EINVAL, __VA_ARGS__)
P00_LIB_WRAP_DOC(mbtowc)
#define mbtowc_throw(...) P99_THROW_CALL_NEG(mbtowc, EINVAL, __VA_ARGS__)
P00_LIB_WRAP_DOC(realloc)
#define realloc_throw(...) P99_THROW_CALL_VOIDP(realloc, thrd_nomem, __VA_ARGS__)
P00_LIB_WRAP_DOC(strtod)
#define strtod_throw(...) P99_THROW_CALL_RANGE(strtod, __VA_ARGS__)
P00_LIB_WRAP_DOC(strtof)
#define strtof_throw(...) P99_THROW_CALL_RANGE(strtof, __VA_ARGS__)
P00_LIB_WRAP_DOC(strtol)
#define strtol_throw(...) P99_THROW_CALL_RANGE(strtol, __VA_ARGS__)
P00_LIB_WRAP_DOC(strtold)
#define strtold_throw(...) P99_THROW_CALL_RANGE(strtold, __VA_ARGS__)
P00_LIB_WRAP_DOC(strtoll)
#define strtoll_throw(...) P99_THROW_CALL_RANGE(strtoll, __VA_ARGS__)
P00_LIB_WRAP_DOC(strtoul)
#define strtoul_throw(...) P99_THROW_CALL_RANGE(strtoul, __VA_ARGS__)
P00_LIB_WRAP_DOC(strtoull)
#define strtoull_throw(...) P99_THROW_CALL_RANGE(strtoull, __VA_ARGS__)
P00_LIB_WRAP_DOC(system)
#define system_throw(...) P99_THROW_CALL_NEG(system, EINVAL, __VA_ARGS__)
P00_LIB_WRAP_DOC(wctomb)
#define wctomb_throw(...) P99_THROW_CALL_NEG(wctomb, EINVAL, __VA_ARGS__)

/* the following are void functions or the capture of the return value
   makes no sense, here. */
//#define _Exit_throw(...) P99_THROW_CALL_NEG(_Exit, EINVAL, __VA_ARGS__)
//#define abort_throw(...) P99_THROW_CALL_NEG(abort, EINVAL, __VA_ARGS__)
//#define abs_throw(...) P99_THROW_CALL_NEG(abs, EINVAL, __VA_ARGS__)
//#define bsearch_throw(...) P99_THROW_CALL_NEG(bsearch, EINVAL, __VA_ARGS__)
//#define div_throw(...) P99_THROW_CALL_NEG(div, EINVAL, __VA_ARGS__)
//#define exit_throw(...) P99_THROW_CALL_NEG(exit, EINVAL, __VA_ARGS__)
//#define free_throw(...) P99_THROW_CALL_NEG(free, EINVAL, __VA_ARGS__)
//#define labs_throw(...) P99_THROW_CALL_NEG(labs, EINVAL, __VA_ARGS__)
//#define ldiv_throw(...) P99_THROW_CALL_NEG(ldiv, EINVAL, __VA_ARGS__)
//#define llabs_throw(...) P99_THROW_CALL_NEG(llabs, EINVAL, __VA_ARGS__)
//#define lldiv_throw(...) P99_THROW_CALL_NEG(lldiv, EINVAL, __VA_ARGS__)
//#define qsort_throw(...) P99_THROW_CALL_NEG(qsort, EINVAL, __VA_ARGS__)
//#define quick_exit_throw(...) P99_THROW_CALL_NEG(quick_exit, EINVAL, __VA_ARGS__)
//#define rand_throw(...) P99_THROW_CALL_NEG(rand, EINVAL, __VA_ARGS__)
//#define srand_throw(...) P99_THROW_CALL_NEG(srand, EINVAL, __VA_ARGS__)

/* the following are functions that return SIZE_MAX on error. We are
   not yet able to handle that special convention. */
//#define wcstombs_throw(...) P99_THROW_CALL_NEG(wcstombs, EINVAL, __VA_ARGS__)
//#define mbstowcs_throw(...) P99_THROW_CALL_NEG(mbstowcs, EINVAL, __VA_ARGS__)

/* string.h has nothing that can be caught */
//#define memchr_throw(...) P99_THROW_CALL_NEG(memchr, EINVAL, __VA_ARGS__)
//#define memcmp_throw(...) P99_THROW_CALL_NEG(memcmp, EINVAL, __VA_ARGS__)
//#define memcpy_throw(...) P99_THROW_CALL_NEG(memcpy, EINVAL, __VA_ARGS__)
//#define memmove_throw(...) P99_THROW_CALL_NEG(memmove, EINVAL, __VA_ARGS__)
//#define memset_throw(...) P99_THROW_CALL_NEG(memset, EINVAL, __VA_ARGS__)
//#define strcat_throw(...) P99_THROW_CALL_NEG(strcat, EINVAL, __VA_ARGS__)
//#define strchr_throw(...) P99_THROW_CALL_NEG(strchr, EINVAL, __VA_ARGS__)
//#define strcmp_throw(...) P99_THROW_CALL_NEG(strcmp, EINVAL, __VA_ARGS__)
//#define strcoll_throw(...) P99_THROW_CALL_NEG(strcoll, EINVAL, __VA_ARGS__)
//#define strcpy_throw(...) P99_THROW_CALL_NEG(strcpy, EINVAL, __VA_ARGS__)
//#define strcspn_throw(...) P99_THROW_CALL_NEG(strcspn, EINVAL, __VA_ARGS__)
//#define strerror_throw(...) P99_THROW_CALL_NEG(strerror, EINVAL, __VA_ARGS__)
//#define strlen_throw(...) P99_THROW_CALL_NEG(strlen, EINVAL, __VA_ARGS__)
//#define strncat_throw(...) P99_THROW_CALL_NEG(strncat, EINVAL, __VA_ARGS__)
//#define strncmp_throw(...) P99_THROW_CALL_NEG(strncmp, EINVAL, __VA_ARGS__)
//#define strncpy_throw(...) P99_THROW_CALL_NEG(strncpy, EINVAL, __VA_ARGS__)
//#define strpbrk_throw(...) P99_THROW_CALL_NEG(strpbrk, EINVAL, __VA_ARGS__)
//#define strrchr_throw(...) P99_THROW_CALL_NEG(strrchr, EINVAL, __VA_ARGS__)
//#define strspn_throw(...) P99_THROW_CALL_NEG(strspn, EINVAL, __VA_ARGS__)
//#define strstr_throw(...) P99_THROW_CALL_NEG(strstr, EINVAL, __VA_ARGS__)
//#define strtok_throw(...) P99_THROW_CALL_NEG(strtok, EINVAL, __VA_ARGS__)
//#define strxfrm_throw(...) P99_THROW_CALL_NEG(strxfrm, EINVAL, __VA_ARGS__)


/* threads.h */
P00_LIB_WRAP_DOC(cnd_broadcast)
#define cnd_broadcast_throw(...) P99_THROW_CALL_THRD(cnd_broadcast, __VA_ARGS__)
P00_LIB_WRAP_DOC(cnd_init)
#define cnd_init_throw(...) P99_THROW_CALL_THRD(cnd_init, __VA_ARGS__)
P00_LIB_WRAP_DOC(cnd_signal)
#define cnd_signal_throw(...) P99_THROW_CALL_THRD(cnd_signal, __VA_ARGS__)
P00_LIB_WRAP_DOC(cnd_timedwait)
#define cnd_timedwait_throw(...) P99_THROW_CALL_THRD(cnd_timedwait, __VA_ARGS__)
P00_LIB_WRAP_DOC(cnd_wait)
#define cnd_wait_throw(...) P99_THROW_CALL_THRD(cnd_wait, __VA_ARGS__)
P00_LIB_WRAP_DOC(mtx_init)
#define mtx_init_throw(...) P99_THROW_CALL_THRD(mtx_init, __VA_ARGS__)
P00_LIB_WRAP_DOC(mtx_lock)
#define mtx_lock_throw(...) P99_THROW_CALL_THRD(mtx_lock, __VA_ARGS__)
P00_LIB_WRAP_DOC(mtx_timedlock)
#define mtx_timedlock_throw(...) P99_THROW_CALL_THRD(mtx_timedlock, __VA_ARGS__)
P00_LIB_WRAP_DOC(mtx_unlock)
#define mtx_unlock_throw(...) P99_THROW_CALL_THRD(mtx_unlock, __VA_ARGS__)
P00_LIB_WRAP_DOC(thrd_create)
#define thrd_create_throw(...) P99_THROW_CALL_THRD(thrd_create, __VA_ARGS__)
P00_LIB_WRAP_DOC(thrd_detach)
#define thrd_detach_throw(...) P99_THROW_CALL_THRD(thrd_detach, __VA_ARGS__)
P00_LIB_WRAP_DOC(thrd_equal)
#define thrd_equal_throw(...) P99_THROW_CALL_THRD(thrd_equal, __VA_ARGS__)
P00_LIB_WRAP_DOC(thrd_join)
#define thrd_join_throw(...) P99_THROW_CALL_THRD(thrd_join, __VA_ARGS__)
P00_LIB_WRAP_DOC(thrd_sleep)
#define thrd_sleep_throw(...) P99_THROW_CALL_THRD(thrd_sleep, __VA_ARGS__)
P00_LIB_WRAP_DOC(tss_create)
#define tss_create_throw(...) P99_THROW_CALL_THRD(tss_create, __VA_ARGS__)
P00_LIB_WRAP_DOC(tss_set)
#define tss_set_throw(...) P99_THROW_CALL_THRD(tss_set, __VA_ARGS__)

/* the following are void functions or the capture of the return value
   makes no sense, here. */
//#define cnd_destroy_throw(...) P99_THROW_CALL_NEG(cnd_destroy, EINVAL, __VA_ARGS__)
//#define mtx_destroy_throw(...) P99_THROW_CALL_NEG(mtx_destroy, EINVAL, __VA_ARGS__)
//#define mtx_trylock_throw(...) P99_THROW_CALL_THRD(mtx_trylock, __VA_ARGS__)
//#define thrd_current_throw(...) P99_THROW_CALL_NEG(thrd_current, EINVAL, __VA_ARGS__)
//#define thrd_exit_throw(...) P99_THROW_CALL_NEG(thrd_exit, EINVAL, __VA_ARGS__)
//#define thrd_yield_throw(...) P99_THROW_CALL_NEG(thrd_yield, EINVAL, __VA_ARGS__)
//#define tss_delete_throw(...) P99_THROW_CALL_NEG(tss_delete, EINVAL, __VA_ARGS__)
//#define tss_get_throw(...) P99_THROW_CALL_NEG(tss_get, EINVAL, __VA_ARGS__)
//void call_once(once_flag *flag, void (*func)(void));

/* wchar.h */
P00_LIB_WRAP_DOC(btowc)
#define btowc_throw(...) P99_THROW_CALL_NEG(btowc, EINVAL, __VA_ARGS__)
P00_LIB_WRAP_DOC(fgetwc)
#define fgetwc_throw(...) P99_THROW_CALL_NEG(fgetwc, EINVAL, __VA_ARGS__)
P00_LIB_WRAP_DOC(fgetws)
#define fgetws_throw(...) P99_THROW_CALL_NEG(fgetws, EINVAL, __VA_ARGS__)
P00_LIB_WRAP_DOC(fputwc)
#define fputwc_throw(...) P99_THROW_CALL_NEG(fputwc, EINVAL, __VA_ARGS__)
P00_LIB_WRAP_DOC(fputws)
#define fputws_throw(...) P99_THROW_CALL_NEG(fputws, EINVAL, __VA_ARGS__)
P00_LIB_WRAP_DOC(fwprintf)
#define fwprintf_throw(...) P99_THROW_CALL_NEG(fwprintf, EINVAL, __VA_ARGS__)
P00_LIB_WRAP_DOC(fwscanf)
#define fwscanf_throw(...) P99_THROW_CALL_NEG(fwscanf, EINVAL, __VA_ARGS__)
P00_LIB_WRAP_DOC(getwc)
#define getwc_throw(...) P99_THROW_CALL_NEG(getwc, EINVAL, __VA_ARGS__)
P00_LIB_WRAP_DOC(getwchar)
#define getwchar_throw(...) P99_THROW_CALL_NEG(getwchar, EINVAL, __VA_ARGS__)
P00_LIB_WRAP_DOC(putwc)
#define putwc_throw(...) P99_THROW_CALL_NEG(putwc, EINVAL, __VA_ARGS__)
P00_LIB_WRAP_DOC(putwchar)
#define putwchar_throw(...) P99_THROW_CALL_NEG(putwchar, EINVAL, __VA_ARGS__)
P00_LIB_WRAP_DOC(swprintf)
#define swprintf_throw(...) P99_THROW_CALL_NEG(swprintf, EINVAL, __VA_ARGS__)
P00_LIB_WRAP_DOC(swscanf)
#define swscanf_throw(...) P99_THROW_CALL_NEG(swscanf, EINVAL, __VA_ARGS__)
P00_LIB_WRAP_DOC(ungetwc)
#define ungetwc_throw(...) P99_THROW_CALL_NEG(ungetwc, EINVAL, __VA_ARGS__)
P00_LIB_WRAP_DOC(vfwprintf)
#define vfwprintf_throw(...) P99_THROW_CALL_NEG(vfwprintf, EINVAL, __VA_ARGS__)
P00_LIB_WRAP_DOC(vfwscanf)
#define vfwscanf_throw(...) P99_THROW_CALL_NEG(vfwscanf, EINVAL, __VA_ARGS__)
P00_LIB_WRAP_DOC(vswprintf)
#define vswprintf_throw(...) P99_THROW_CALL_NEG(vswprintf, EINVAL, __VA_ARGS__)
P00_LIB_WRAP_DOC(vswscanf)
#define vswscanf_throw(...) P99_THROW_CALL_NEG(vswscanf, EINVAL, __VA_ARGS__)
P00_LIB_WRAP_DOC(vwprintf)
#define vwprintf_throw(...) P99_THROW_CALL_NEG(vwprintf, EINVAL, __VA_ARGS__)
P00_LIB_WRAP_DOC(vwscanf)
#define vwscanf_throw(...) P99_THROW_CALL_NEG(vwscanf, EINVAL, __VA_ARGS__)
P00_LIB_WRAP_DOC(wcstod)
#define wcstod_throw(...) P99_THROW_CALL_RANGE(wcstod, __VA_ARGS__)
P00_LIB_WRAP_DOC(wcstof)
#define wcstof_throw(...) P99_THROW_CALL_RANGE(wcstof, __VA_ARGS__)
P00_LIB_WRAP_DOC(wcstok)
#define wcstok_throw(...) P99_THROW_CALL_RANGE(wcstok, __VA_ARGS__)
P00_LIB_WRAP_DOC(wcstol)
#define wcstol_throw(...) P99_THROW_CALL_RANGE(wcstol, __VA_ARGS__)
P00_LIB_WRAP_DOC(wcstold)
#define wcstold_throw(...) P99_THROW_CALL_RANGE(wcstold, __VA_ARGS__)
P00_LIB_WRAP_DOC(wcstoll)
#define wcstoll_throw(...) P99_THROW_CALL_RANGE(wcstoll, __VA_ARGS__)
P00_LIB_WRAP_DOC(wcstoul)
#define wcstoul_throw(...) P99_THROW_CALL_RANGE(wcstoul, __VA_ARGS__)
P00_LIB_WRAP_DOC(wcstoull)
#define wcstoull_throw(...) P99_THROW_CALL_RANGE(wcstoull, __VA_ARGS__)
P00_LIB_WRAP_DOC(wprintf)
#define wprintf_throw(...) P99_THROW_CALL_NEG(wprintf, EINVAL, __VA_ARGS__)
P00_LIB_WRAP_DOC(wscanf)
#define wscanf_throw(...) P99_THROW_CALL_NEG(wscanf, EINVAL, __VA_ARGS__)

/* the following are void functions or the capture of the return value
   makes no sense, here. */
//#define fwide_throw(...) P99_THROW_CALL_NEG(fwide, EINVAL, __VA_ARGS__)
//#define mbsinit_throw(...) P99_THROW_CALL_NEG(mbsinit, EINVAL, __VA_ARGS__)
//#define wcscat_throw(...) P99_THROW_CALL_NEG(wcscat, EINVAL, __VA_ARGS__)
//#define wcschr_throw(...) P99_THROW_CALL_NEG(wcschr, EINVAL, __VA_ARGS__)
//#define wcscmp_throw(...) P99_THROW_CALL_NEG(wcscmp, EINVAL, __VA_ARGS__)
//#define wcscoll_throw(...) P99_THROW_CALL_NEG(wcscoll, EINVAL, __VA_ARGS__)
//#define wcscpy_throw(...) P99_THROW_CALL_NEG(wcscpy, EINVAL, __VA_ARGS__)
//#define wcscspn_throw(...) P99_THROW_CALL_NEG(wcscspn, EINVAL, __VA_ARGS__)
//#define wcsftime_throw(...) P99_THROW_CALL_NEG(wcsftime, EINVAL, __VA_ARGS__)
//#define wcslen_throw(...) P99_THROW_CALL_NEG(wcslen, EINVAL, __VA_ARGS__)
//#define wcsncat_throw(...) P99_THROW_CALL_NEG(wcsncat, EINVAL, __VA_ARGS__)
//#define wcsncmp_throw(...) P99_THROW_CALL_NEG(wcsncmp, EINVAL, __VA_ARGS__)
//#define wcsncpy_throw(...) P99_THROW_CALL_NEG(wcsncpy, EINVAL, __VA_ARGS__)
//#define wcspbrk_throw(...) P99_THROW_CALL_NEG(wcspbrk, EINVAL, __VA_ARGS__)
//#define wcsrchr_throw(...) P99_THROW_CALL_NEG(wcsrchr, EINVAL, __VA_ARGS__)
//#define wcsspn_throw(...) P99_THROW_CALL_NEG(wcsspn, EINVAL, __VA_ARGS__)
//#define wcsstr_throw(...) P99_THROW_CALL_NEG(wcsstr, EINVAL, __VA_ARGS__)
//#define wcsxfrm_throw(...) P99_THROW_CALL_NEG(wcsxfrm, EINVAL, __VA_ARGS__)
//#define wctob_throw(...) P99_THROW_CALL_NEG(wctob, EINVAL, __VA_ARGS__)
//#define wmemchr_throw(...) P99_THROW_CALL_NEG(wmemchr, EINVAL, __VA_ARGS__)
//#define wmemcmp_throw(...) P99_THROW_CALL_NEG(wmemcmp, EINVAL, __VA_ARGS__)
//#define wmemcpy_throw(...) P99_THROW_CALL_NEG(wmemcpy, EINVAL, __VA_ARGS__)
//#define wmemmove_throw(...) P99_THROW_CALL_NEG(wmemmove, EINVAL, __VA_ARGS__)
//#define wmemset_throw(...) P99_THROW_CALL_NEG(wmemset, EINVAL, __VA_ARGS__)

/* the following are functions that return SIZE_MAX or similar on
   error. We are not yet able to handle that special convention. */
//-#define mbrlen_throw(...) P99_THROW_CALL_NEG(mbrlen, EINVAL, __VA_ARGS__)
//-#define mbrtowc_throw(...) P99_THROW_CALL_NEG(mbrtowc, EINVAL, __VA_ARGS__)
//-#define mbsrtowcs_throw(...) P99_THROW_CALL_NEG(mbsrtowcs, EINVAL, __VA_ARGS__)
//-#define wcrtomb_throw(...) P99_THROW_CALL_NEG(wcrtomb, EINVAL, __VA_ARGS__)
//-#define wcsrtombs_throw(...) P99_THROW_CALL_NEG(wcsrtombs, EINVAL, __VA_ARGS__)

/**
 ** @}
 **/


#endif
