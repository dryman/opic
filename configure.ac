AC_INIT([OPIC],[0.3])

AC_CONFIG_SRCDIR([README.md])
AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_MACRO_DIR([m4])
AM_CONFIG_HEADER([config.h])

AM_INIT_AUTOMAKE([-Wall -Werror foreign])
AM_PROG_AR
LT_INIT

AC_PROG_CC_C11
AC_PROG_CXX
AX_CXX_COMPILE_STDCXX_11
AC_PROG_LIBTOOL
AC_C_INLINE
AC_HEADER_STDBOOL
AC_CHECK_HEADERS([limits.h inttypes.h])
AC_FUNC_MALLOC
AC_FUNC_MEMCMP
AC_FUNC_MMAP

AX_CFLAGS_WARN_ALL
AX_PTHREAD

# TODO(fchern):
# check cmocka

# Checks for log4c
AC_PATH_PROG([LOG4C_CONFIG], [log4c-config])
AS_IF([test "x$LOG4C_CONFIG" != "x"], [
  log4c_CFLAGS=`$LOG4C_CONFIG --cflags`
  log4c_LIBS=`$LOG4C_CONFIG --libs`
  AC_SUBST([log4c_CFLAGS])
  AC_SUBST([log4c_LIBS])
  AC_DEFINE([HAS_LOG4C], [1], [Define to 1 if log4c is available.])
])

# ugly test to detect gcc and clang that pretends to be gcc
AS_IF([test "x$GCC" = "xyes"],
  [AS_IF([$CC --version | grep "clang"],
   [atomic_LIBS=""],
   [atomic_LIBS="-latomic"])],
  [atomic_LIBS=""])
AC_SUBST([atomic_LIBS])

PKG_CHECK_MODULES([cmocka], [cmocka >= 1.0.1])

AC_CONFIG_FILES([
  Makefile
  opic/Makefile
  opic/malloc/Makefile
  opic/hash/Makefile
  benchmark/Makefile
])

AC_OUTPUT
