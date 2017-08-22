AM_CPPFLAGS = -I$(top_srcdir)
AM_CFLAGS = @cmocka_CFLAGS@ @log4c_CFLAGS@
AUTOMAKE_OPTIONS = subdir-objects

TESTS = lookup_helper_test init_helper_test allocator_test \
  deallocator_test op_malloc_test
check_PROGRAMS = lookup_helper_test init_helper_test allocator_test \
  deallocator_test op_malloc_test

lookup_helper_test_SOURCES = \
  ../common/op_log.c \
  allocator.c \
  lookup_helper_test.c \
  lookup_helper.c \
  init_helper.c \
  op_malloc.c

lookup_helper_test_LDADD = @log4c_LIBS@ @PTHREAD_LIBS@ \
  @cmocka_LIBS@ @atomic_LIBS@
lookup_helper_test_LDFLAGS = -static

init_helper_test_SOURCES = \
  ../common/op_log.c \
  allocator.c \
  init_helper.c \
  init_helper_test.c \
  lookup_helper.c \
  op_malloc.c

init_helper_test_LDADD = @log4c_LIBS@ @PTHREAD_LIBS@ \
  @cmocka_LIBS@ @atomic_LIBS@
init_helper_test_LDFLAGS = -static

allocator_test_SOURCES = \
  ../common/op_log.c \
  allocator.c \
  allocator_test.c \
  deallocator.c \
  init_helper.c \
  lookup_helper.c \
  op_malloc.c

allocator_test_LDADD = @log4c_LIBS@ @PTHREAD_LIBS@ \
  @cmocka_LIBS@ @atomic_LIBS@
allocator_test_LDFLAGS = -static

deallocator_test_SOURCES = \
  ../common/op_log.c \
  allocator.c \
  deallocator.c \
  deallocator_test.c \
  init_helper.c \
  lookup_helper.c \
  op_malloc.c

deallocator_test_LDADD = @log4c_LIBS@ @PTHREAD_LIBS@ \
  @cmocka_LIBS@ @atomic_LIBS@
deallocator_test_LDFLAGS = -static

op_malloc_test_SOURCES = \
  ../common/op_log.c \
  op_malloc_test.c \
  init_helper.c \
  lookup_helper.c \
  op_malloc.c

op_malloc_test_LDADD = @log4c_LIBS@ @PTHREAD_LIBS@ \
  @cmocka_LIBS@ @atomic_LIBS@
op_malloc_test_LDFLAGS = -static
