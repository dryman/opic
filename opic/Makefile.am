SUBDIRS = malloc

AUTOMAKE_OPTIONS = subdir-objects
AM_CPPFLAGS = -I$(top_srcdir)

lib_LTLIBRARIES = libdemomalloc.la

libdemomalloc_la_SOURCES = \
  demomalloc.c \
  malloc/allocator.c \
  malloc/deallocator.c \
  malloc/init_helper.c \
  malloc/lookup_helper.c \
  hash/robin_hood.c \
  hash/murmurhash3.c \
  hash/xxHash/xxhash.c
