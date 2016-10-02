AC_INIT([OPIC],[0.2])

AC_CONFIG_SRCDIR([src/opic.h])
AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_MACRO_DIR([m4])
AM_CONFIG_HEADER([src/config.h])

AM_INIT_AUTOMAKE([-Wall -Werror foreign])
AM_PROG_AR
LT_INIT

AC_PROG_CC
AC_PROG_CC_C99
AC_PROG_LIBTOOL
AC_C_INLINE

AX_PTHREAD

AC_HEADER_STDBOOL
AC_CHECK_HEADERS([limits.h inttypes.h])

# Checks for log4c
AC_PATH_PROG([LOG4C_CONFIG], [log4c-config])
if test x"$LOG4C_CONFIG" != x""; then
	log4c_CFLAGS=`$LOG4C_CONFIG --cflags`
	log4c_LIBS=`$LOG4C_CONFIG --libs`
	AC_SUBST([log4c_CFLAGS])
	AC_SUBST([log4c_LIBS])
	AC_DEFINE([HAS_LOG4C], [1], [Define to 1 if log4c is available.])
fi

AC_FUNC_MALLOC
AC_FUNC_MEMCMP
AC_FUNC_MMAP


AC_CONFIG_FILES([Makefile src/Makefile pm_serde_example/Makefile])

AC_OUTPUT
