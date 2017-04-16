SUBDIRS = malloc

AUTOMAKE_OPTIONS = subdir-objects
AM_CPPFLAGS = -I$(top_srcdir)

lib_LTLIBRARIES = libopic.la

libopic_la_SOURCES = \
  demomalloc.c \
  common/op_log.c \
  malloc/op_malloc.c \
  malloc/allocator.c \
  malloc/deallocator.c \
  malloc/init_helper.c \
  malloc/lookup_helper.c \
  hash/robin_hood.c \
  hash/murmurhash3.c

libopic_la_CFLAGS = @log4c_CFLAGS@
