# TODO: Can we put Makefile.am in subdir?
# https://www.gnu.org/software/automake/manual/html_node/Libtool-Convenience-Libraries.html
AUTOMAKE_OPTIONS = subdir-objects

AM_CPPFLAGS = -I$(top_srcdir)/src

lib_LTLIBRARIES = libopic.la
libopic_la_SOURCES = \
  opic/common/op_assert.h \
  opic/common/op_log.c \
  opic/common/op_log.h \
  opic/common/op_macros.h \
  opic/object/op_serializable.c \
  opic/object/op_serializable.h \
  opic/object/op_trait.c \
  opic/object/op_trait.h \
  opic/object/op_object.h \
  opic/object/op_object.c \
  opic/object/op_object_def.h \
  opic/object/op_malloc_manager.c \
  opic/object/class_map.c \
  opic/object/class_map.h \
  opic/object/ptr_range_map_splay.c \
  opic/object/ptr_range_map.h \
  opic.h \
  op_collection.h \
  op_functional.h \
  op_iterator.h \
  op_linked_list.h \
  op_list.h \
  op_collection.c \
  op_iterator.c \
  op_linked_list.c \
  op_list.c
libopic_la_CFLAGS = @log4c_CFLAGS@ @PTHREAD_CFLAGS@
libopic_la_LDFLAGS = @log4c_LIBS@

include_HEADERS = \
  opic.h \
  op_collection.h \
  op_functional.h \
  op_iterator.h \
  op_linked_list.h \
  op_list.h

nobase_include_HEADERS = \
  opic/common/op_assert.h \
  opic/common/op_log.h \
  opic/common/op_macros.h \
  opic/object/op_serializable.h \
  opic/object/op_trait.h \
  opic/object/op_object_def.h \
  opic/object/op_object.h
