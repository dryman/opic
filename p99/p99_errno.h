/* This may look like nonsense, but it really is -*- mode: C -*-              */
/*                                                                            */
/* Except for parts copied from previous work and as explicitly stated below, */
/* the author and copyright holder for this work is                           */
/* (C) copyright  2012-2013 Jens Gustedt, INRIA, France                       */
/*                                                                            */
/* This file is free software; it is part of the P99 project.                 */
/* You can redistribute it and/or modify it under the terms of the QPL as     */
/* given in the file LICENSE. It is distributed without any warranty;         */
/* without even the implied warranty of merchantability or fitness for a      */
/* particular purpose.                                                        */
/*                                                                            */
#ifndef     P99_ERRNO_H_
# define    P99_ERRNO_H_

#include "p99_for.h"

#define P00_IF_XEQ_(A, B) P99_IF_EQ(A, B)
#define P00_IF_XEQ(A, B) P00_IF_XEQ(A, B)


/* A long list of error numbers. C11 only has EDOM, EILSEQ, ERANGE but
   usually systems declare their own values:

   Additional macro definitions, beginning with E and a digit or E and
   an uppercase letter,203) may also be specified by the
   implementation.

   For the moment this list is from what Linux has to offer. This
   includes the macros that are defined by POSIX.
   */
#define P00_ERRNO_LIST                                              \
       2BIG,                                                        \
       ACCES,                                                       \
       ADDRINUSE,                                                   \
       ADDRNOTAVAIL,                                                \
       AFNOSUPPORT,                                                 \
         /* POSIX allows these two to be equal */                   \
       P99_IF_EQ(EAGAIN, EWOULDBLOCK)(AGAIN,)(AGAIN, WOULDBLOCK,)   \
       ALREADY,                                                     \
       BADE,                                                        \
       BADF,                                                        \
       BADFD,                                                       \
       BADMSG,                                                      \
       BADR,                                                        \
       BADRQC,                                                      \
       BADSLT,                                                      \
       BUSY,                                                        \
       CANCELED,                                                    \
       CHILD,                                                       \
       CHRNG,                                                       \
       COMM,                                                        \
       CONNABORTED,                                                 \
       CONNREFUSED,                                                 \
       CONNRESET,                                                   \
         /* POSIX has only EDEADLK, Linux also has EDEADLOCK */     \
       P99_IF_EQ(EDEADLK, EDEADLOCK)(DEADLK,)(DEADLK, DEADLOCK,)    \
       DESTADDRREQ,                                                 \
       DOM,                                                         \
       DQUOT,                                                       \
       EXIST,                                                       \
       FAULT,                                                       \
       FBIG,                                                        \
       HOSTDOWN,                                                    \
       HOSTUNREACH,                                                 \
       IDRM,                                                        \
       ILSEQ,                                                       \
       INPROGRESS,                                                  \
       INTR,                                                        \
       INVAL,                                                       \
       IO,                                                          \
       ISCONN,                                                      \
       ISDIR,                                                       \
       ISNAM,                                                       \
       KEYEXPIRED,                                                  \
       KEYREJECTED,                                                 \
       KEYREVOKED,                                                  \
       L2HLT,                                                       \
       L2NSYNC,                                                     \
       L3HLT,                                                       \
       L3RST,                                                       \
       LIBACC,                                                      \
       LIBBAD,                                                      \
       LIBEXEC,                                                     \
       LIBMAX,                                                      \
       LIBSCN,                                                      \
       LOOP,                                                        \
       MEDIUMTYPE,                                                  \
       MFILE,                                                       \
       MLINK,                                                       \
       MSGSIZE,                                                     \
       MULTIHOP,                                                    \
       NAMETOOLONG,                                                 \
       NETDOWN,                                                     \
       NETRESET,                                                    \
       NETUNREACH,                                                  \
       NFILE,                                                       \
       NOBUFS,                                                      \
       NODATA,                                                      \
       NODEV,                                                       \
       NOENT,                                                       \
       NOEXEC,                                                      \
       NOKEY,                                                       \
       NOLCK,                                                       \
       NOLINK,                                                      \
       NOMEDIUM,                                                    \
       NOMEM,                                                       \
       NOMSG,                                                       \
       NONET,                                                       \
       NOPKG,                                                       \
       NOPROTOOPT,                                                  \
       NOSPC,                                                       \
       NOSR,                                                        \
       NOSTR,                                                       \
       NOSYS,                                                       \
       NOTBLK,                                                      \
       NOTCONN,                                                     \
       NOTDIR,                                                      \
       NOTEMPTY,                                                    \
       NOTSOCK,                                                     \
       NOTTY,                                                       \
       NOTUNIQ,                                                     \
       NXIO,                                                        \
         /* should be distinct for POSIX, but are equal on Linux */ \
       P99_IF_EQ(ENOTSUP, EOPNOTSUPP)(NOTSUP,)(NOTSUP, OPNOTSUPP,)  \
         /* is defined by SVID as such: OVERFLOW, */                \
       PERM,                                                        \
       PFNOSUPPORT,                                                 \
       PIPE,                                                        \
       PROTO,                                                       \
       PROTONOSUPPORT,                                              \
       PROTOTYPE,                                                   \
       RANGE,                                                       \
       REMCHG,                                                      \
       REMOTE,                                                      \
       REMOTEIO,                                                    \
       RESTART,                                                     \
       ROFS,                                                        \
       SHUTDOWN,                                                    \
       SOCKTNOSUPPORT,                                              \
       SPIPE,                                                       \
       SRCH,                                                        \
       STALE,                                                       \
       STRPIPE,                                                     \
       TIME,                                                        \
       TIMEDOUT,                                                    \
       TXTBSY,                                                      \
       UCLEAN,                                                      \
       UNATCH,                                                      \
       USERS,                                                       \
       XDEV,                                                        \
       XFULL,                                                       \
       XXX

#define P00_ERRNO_ELEM_(ERR, STR) P99_IF_GT(ERR, 0)([ERR] = 0,)()
#define P00_ERRNO_ELEM(ERR) P00_ERRNO_ELEM_(E ## ERR, "E" #ERR)

#define P00_ERRNO_ENUM_(ERR, NAME) P99_IF_GT(ERR, 0)(NAME)(ERR)
#define P00_ERRNO_ENUM(ERR) P00_ERRNO_ENUM_(E ## ERR, p00_E ## ERR)

enum {
  /**
   ** @brief The maximum predefined error code that we found on this system
   **/
  p00_errno_max = sizeof((char[]) { P99_SER(P00_ERRNO_ELEM, P00_ERRNO_LIST) P00_ERRNO_ELEM(OVERFLOW) }),
  /* Add all other codes as enumeration constants */
  P99_SEQ(P00_ERRNO_ENUM, P00_ERRNO_LIST), P00_ERRNO_ENUM(OVERFLOW),
  /**
   ** @brief The maximum error code that we found or defined on this system
   **/
  p99_errno_max
};

#define P00_ERRNO_CASE_(ERR, STR) case ERR: return STR
#define P00_ERRNO_CASE(ERR) P00_ERRNO_CASE_(E ## ERR, "E" #ERR)

/**
 ** @brief Return the name of an error condition
 **
 ** This uses a long list of error condition names to detect potential
 ** candidates for such error conditions. This uses the fact that all
 ** identifiers starting with "E" and consisting only of uppercase
 ** letters or decimals are reserved for error conditions.
 **
 ** If an error condition is not found in the list of known values, a
 ** null pointer is returned.
 **/
P99_CONST_FUNCTION
p99_inline
char const* p99_errno_getname(errno_t p00_err) {
  switch (p00_err) {
    P99_SEP(P00_ERRNO_CASE, P00_ERRNO_LIST);
    P00_ERRNO_CASE(OVERFLOW);
  default: return 0;
  }
}

#endif
