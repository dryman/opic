AUTOMAKE_OPTIONS = subdir-objects
AM_CPPFLAGS = -I$(top_srcdir)/src
AM_CFLAGS = @log4c_CFLAGS@ @cmocka_CFLAGS@

TESTS = lookup_helper_test
check_PROGRAMS = lookup_helper_test

lookup_helper_test_SOURCES = \
  lookup_helper_test.c \
  lookup_helper.c \
  init_helper.c \
  ../common/op_log.c

lookup_helper_test_LDADD = @log4c_LIBS@ @PTHREAD_LIBS@ \
  @cmocka_LIBS@ @atomic_LIBS@
lookup_helper_test_LDFLAGS = -static
