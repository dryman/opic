AM_CPPFLAGS = -I$(top_srcdir)
AUTOMAKE_OPTIONS = subdir-objects

TESTS = robin_hood_test pascal_robin_hood_test
check_PROGRAMS = robin_hood_test pascal_robin_hood_test

robin_hood_test_SOURCES = \
  robin_hood_test.c \
  robin_hood.c \
  cityhash.c \
  ../common/op_log.c \
  ../malloc/op_malloc.c \
  ../malloc/allocator.c \
  ../malloc/deallocator.c \
  ../malloc/init_helper.c \
  ../malloc/lookup_helper.c

robin_hood_test_CFLAGS = @cmocka_CFLAGS@ @log4c_CFLAGS@
robin_hood_test_LDADD = @log4c_LIBS@ @cmocka_LIBS@ @atomic_LIBS@
robin_hood_test_LDFLAGS = -static

pascal_robin_hood_test_SOURCES = \
  pascal_robin_hood_test.c \
  pascal_robin_hood.c \
  cityhash.c \
  ../common/op_log.c \
  ../malloc/op_malloc.c \
  ../malloc/allocator.c \
  ../malloc/deallocator.c \
  ../malloc/init_helper.c \
  ../malloc/lookup_helper.c

pascal_robin_hood_test_CFLAGS = @cmocka_CFLAGS@ @log4c_CFLAGS@
pascal_robin_hood_test_LDADD = @log4c_LIBS@ @cmocka_LIBS@ @atomic_LIBS@
pascal_robin_hood_test_LDFLAGS = -static
