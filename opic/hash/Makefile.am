AM_CPPFLAGS = -I$(top_srcdir)
AUTOMAKE_OPTIONS = subdir-objects

TESTS = op_hash_table_test pascal_robin_hood_test
check_PROGRAMS = op_hash_table_test pascal_robin_hood_test

op_hash_table_test_SOURCES = \
  op_hash_table_test.c \
  op_hash_table.c \
  cityhash.c \
  ../common/op_log.c \
  ../malloc/op_malloc.c \
  ../malloc/allocator.c \
  ../malloc/deallocator.c \
  ../malloc/init_helper.c \
  ../malloc/lookup_helper.c

op_hash_table_test_CFLAGS = @cmocka_CFLAGS@ @log4c_CFLAGS@
op_hash_table_test_LDADD = @log4c_LIBS@ @cmocka_LIBS@ @atomic_LIBS@
op_hash_table_test_LDFLAGS = -static

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
