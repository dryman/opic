SUBDIRS = malloc

AUTOMAKE_OPTIONS = subdir-objects
AM_CPPFLAGS = -I$(top_srcdir)

lib_LTLIBRARIES = libdemomalloc.la

libdemomalloc_la_SOURCES = \
  demomalloc.c \
  malloc/allocator.c \
  malloc/deallocator.c \
  malloc/init_helper.c \
  malloc/lookup_helper.c

libdemomalloc_la_LIBADD = @atomic_LIBS@
