AC_INIT([OPIC],[0.1])

AC_CONFIG_SRCDIR([src/op_trait.h])
AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_MACRO_DIR([m4])

AM_INIT_AUTOMAKE([-Wall -Werror foreign])
AM_PROG_AR
LT_INIT

AC_PROG_CC
AC_PROG_CC_C99
AC_PROG_LIBTOOL

AC_HEADER_STDBOOL
AC_CHECK_HEADERS([limits.h inttypes.h])

AC_FUNC_MALLOC
AC_FUNC_MEMCMP
AC_FUNC_MMAP

AC_CONFIG_FILES([Makefile src/Makefile monad_example/Makefile pm_serde_example/Makefile])

AC_OUTPUT
