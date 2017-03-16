AUTOMAKE_OPTIONS = subdir-objects
AM_CPPFLAGS = -I$(top_srcdir)/src
AM_CFLAGS = @log4c_CFLAGS@ @cmocka_CFLAGS@

TESTS = lookup_helper_test init_helper_test allocator_test
check_PROGRAMS = lookup_helper_test init_helper_test allocator_test

lookup_helper_test_SOURCES = \
  lookup_helper_test.c \
  lookup_helper.c \
  init_helper.c \
  ../common/op_log.c

lookup_helper_test_LDADD = @log4c_LIBS@ @PTHREAD_LIBS@ \
  @cmocka_LIBS@ @atomic_LIBS@
lookup_helper_test_LDFLAGS = -static

init_helper_test_SOURCES = \
  init_helper.c \
  init_helper_test.c \
  lookup_helper.c \
  ../common/op_log.c

init_helper_test_LDADD = @log4c_LIBS@ @PTHREAD_LIBS@ \
  @cmocka_LIBS@ @atomic_LIBS@
init_helper_test_LDFLAGS = -static

allocator_test_SOURCES = \
  allocator.c \
  allocator_test.c \
  init_helper.c \
  lookup_helper.c \
  ../common/op_log.c

allocator_test_LDADD = @log4c_LIBS@ @PTHREAD_LIBS@ \
  @cmocka_LIBS@ @atomic_LIBS@
allocator_test_LDFLAGS = -static
