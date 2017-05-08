SUBDIRS = malloc hash

AUTOMAKE_OPTIONS = subdir-objects
AM_CPPFLAGS = -I$(top_srcdir)
AM_CFLAGS = @log4c_CFLAGS@


lib_LTLIBRARIES = libopic.la


libopic_la_SOURCES = \
  common/op_log.c \
  malloc/op_malloc.c \
  malloc/allocator.c \
  malloc/deallocator.c \
  malloc/init_helper.c \
  malloc/lookup_helper.c \
  hash/cityhash.c \
  hash/robin_hood.c
