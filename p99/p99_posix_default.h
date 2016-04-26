/* This may look like nonsense, but it really is -*- mode: C -*-              */
/*                                                                            */
/* Except for parts copied from previous work and as explicitly stated below, */
/* the authors and copyright holders for this work are as follows:            */
/* (C) copyright  2010-2013 Jens Gustedt, INRIA, France                       */
/* (C) copyright  2012 William Morris                                         */
/*                                                                            */
/* This file is free software; it is part of the P99 project.                 */
/* You can redistribute it and/or modify it under the terms of the QPL as     */
/* given in the file LICENSE. It is distributed without any warranty;         */
/* without even the implied warranty of merchantability or fitness for a      */
/* particular purpose.                                                        */
/*                                                                            */
#ifndef     P99_POSIX_DEFAULT_H_
# define    P99_POSIX_DEFAULT_H_

#include "p99_defarg.h"
#include P99_ADVANCE_ID

/**
 ** @addtogroup posix_default Provide default arguments for some POSIX functions
 **
 ** @{
 **/

#define P00_POSIX_DEFARG_DOCU(NAME, RET, ...)                             \
/*! @brief Default arguments for POSIX function NAME */                   \
/*! This macro hides the function @code RET NAME(__VA_ARGS__) @endcode */ \
/*! @see P99_CALL_DEFARG */
P99_MACRO_END(POSIX_DEFARG_DOCU);


P00_POSIX_DEFARG_DOCU(pthread_barrier_init, int, pthread_barrier_t *restrict objp, const pthread_barrierattr_t *restrict attr, unsigned count)
/*! @param objp is required */
/*! @param attr defaults to 0, such that is @a objp is initialized with default velues */
/*! @param count is required */
#define pthread_barrier_init(...) P99_CALL_DEFARG(pthread_barrier_init, 3, __VA_ARGS__)
#define pthread_barrier_init_defarg_1() 0
#define pthread_barrier_init_defarg_2() (pthread_barrier_init must have a count argument)

P00_POSIX_DEFARG_DOCU(pthread_cond_init, int, pthread_cond_t* objp, pthread_condattr_t const* attr)
/*! @param objp is required */
/*! @param attr defaults to 0, such that is @a objp is initialized with default velues */
#define pthread_cond_init(...) P99_CALL_DEFARG(pthread_cond_init, 2, __VA_ARGS__)
#define pthread_cond_init_defarg_1() 0

P00_POSIX_DEFARG_DOCU(pthread_mutex_init, int, pthread_mutex_t* objp, pthread_mutexattr_t const* attr)
/*! @param objp is required */
/*! @param attr defaults to 0, such that is @a objp is initialized with default velues */
#define pthread_mutex_init(...) P99_CALL_DEFARG(pthread_mutex_init, 2, __VA_ARGS__)
#define pthread_mutex_init_defarg_1() 0

P00_POSIX_DEFARG_DOCU(pthread_rwlock_init, int, pthread_rwlock_t* objp, pthread_rwlockattr_t const* attr)
/*! @param objp is required */
/*! @param attr defaults to 0, such that is @a objp is initialized with default velues */
#define pthread_rwlock_init(...) P99_CALL_DEFARG(pthread_rwlock_init, 2, __VA_ARGS__)
#define pthread_rwlock_init_defarg_1() 0

P00_POSIX_DEFARG_DOCU(pthread_spin_init, int, pthread_spinlock_t* objp, int pshared)
/*! @param objp is required */
/*! @param pshared defaults to PTHREAD_PROCESS_PRIVATE, such that @a objp is not shared between different processes  */
#define pthread_spin_init(...) P99_CALL_DEFARG(pthread_spin_init, 2, __VA_ARGS__)
#define pthread_spin_init_defarg_1() PTHREAD_PROCESS_PRIVATE

P00_POSIX_DEFARG_DOCU(pthread_key_create, int, pthread_key_t *key, void (*destr_function) (void *))
/*! @param objp is required */
/*! @param destr_function defaults to 0 */
#define pthread_key_create(...) P99_CALL_DEFARG(pthread_key_create, 2, __VA_ARGS__)
#define pthread_key_create_defarg_1() 0

#define SOCKADDR_IN_INIIALIZER { .sin_family = AF_INET }

#define IN_ADDR_INITIALIZER  P99_INIT

P00_POSIX_DEFARG_DOCU(accept, int, int sockfd, struct sockaddr *addr, socklen_t *addrlen)
/**
 ** @param  sockfd must be provided
 ** @param  addr defaults to 0
 ** @param  addrlen defaults to the address of a temporary of type @c socklen_t
 **/
#define accept(...) P99_CALL_DEFARG(accept, 3, __VA_ARGS__)
#define accept_defarg_1() 0
#define accept_defarg_2() &P99_LVAL(socklen_t)

P00_POSIX_DEFARG_DOCU(socket, int, int domain, int type, int protocol)
/**
 ** @param  domain is required
 ** @param  type defaults to SOCK_STREAM
 ** @param  protocol defaults to 0
 **/
#define socket(...) P99_CALL_DEFARG(socket, 3, __VA_ARGS__)
#define socket_defarg_1() SOCK_STREAM
#define socket_defarg_2() 0

P00_POSIX_DEFARG_DOCU(inet_ntop, char const*, int af, const void *src, char *dst, socklen_t size)
/**
 ** @param  af is required
 ** @param  src is required
 ** @param  dst defaults to the address of a temporary that is then returned
 ** @param  size defaults to INET6_ADDRSTRLEN
 **/
#define inet_ntop(...) P99_CALL_DEFARG(inet_ntop, 4, __VA_ARGS__)
#define inet_ntop_defarg_2() P99_LVAL(char[INET6_ADDRSTRLEN])
#define inet_ntop_defarg_3() INET6_ADDRSTRLEN


P00_POSIX_DEFARG_DOCU(realpath, char*, char const *path, char *resolved_path)
/**
 ** @param  path is required
 ** @param  resolved_path defaults to the address of a temporary that is returned in case of success
 ** @note to have realpath allocate its return value with @c malloc, @a resolved_path should be set to 0
 **/
#define realpath(...) P99_CALL_DEFARG(realpath, 2, __VA_ARGS__)
#define realpath_defarg_1() P99_LVAL(char[PATH_MAX])


P00_POSIX_DEFARG_DOCU(getsockopt, int, int sockfd, int level, int optname, void* optval, socklen_t*optlen)
/**
 ** @a optlen is optional and defaults to a temporary containing the length of the argument @a optval
 **/
#define getsockopt(...) P99_IF_GE(P99_NARG(__VA_ARGS__),5)(getsockopt(__VA_ARGS__))(p00_getsockopt(__VA_ARGS__))

#define p00_getsockopt(FD, LEV, OPTNAME, OPTVAL)                         \
getsockopt(FD, LEV, OPTNAME, OPTVAL, (socklen_t[1]){ sizeof *(OPTVAL) })

P00_POSIX_DEFARG_DOCU(setsockopt, int, int sockfd, int level, int optname, void* optval, socklen_t optlen)
/**
 ** @a optlen is optional and defaults to the length of the argument @a optval
 **/
#define setsockopt(...) P99_IF_GE(P99_NARG(__VA_ARGS__),5)(setsockopt(__VA_ARGS__))(p00_setsockopt(__VA_ARGS__))

#define p00_setsockopt(FD, LEV, OPTNAME, OPTVAL) (setsockopt)(FD, LEV, OPTNAME, OPTVAL, sizeof *(OPTVAL))

/**
 ** @}
 **/

#endif      /* !P99_POSIX_DEFAULT_H_ */
