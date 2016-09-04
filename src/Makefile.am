# should removed and recursively define subdir
AUTOMAKE_OPTIONS = subdir-objects

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
  opic/object/pm_memory_manager.c \
  opic/object/pm_memory_manager.h \
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
libopic_la_CFLAGS = @log4c_CFLAGS@
libopic_la_LDFLAGS = @log4c_LIBS@

include_HEADERS = \
  opic.h \
  op_collection.h \
  op_functional.h \
  op_iterator.h \
  op_linked_list.h \
  op_list.h

pkginclude_HEADERS = \
  opic/common/op_assert.h \
  opic/common/op_log.h \
  opic/common/op_macros.h \
  opic/object/op_serializable.h \
  opic/object/op_trait.h \
  opic/object/pm_memory_manager.h
