AUTOMAKE_OPTIONS = subdir-objects
bin_PROGRAMS = pm_test pm_read
pm_test_SOURCES = \
 pm_test.c \
 ../src/op_trait.h \
 ../src/pm_memory_manager.h \
 ../src/op_serializable.h \
 ../src/op_collection.h \
 ../src/op_list.h \
 ../src/op_linked_list.h
pm_test_CFLAGS = -std=c11 @log4c_CFLAGS@
pm_test_LDADD = ../src/libopic.la @log4c_LIBS@
pm_test_LDFLAGS = -latomic

pm_read_SOURCES = \
 pm_read.c \
 ../src/op_trait.h \
 ../src/pm_memory_manager.h \
 ../src/op_serializable.h \
 ../src/op_collection.h \
 ../src/op_list.h \
 ../src/op_linked_list.h
pm_read_CFLAGS = -std=c11 @log4c_CFLAGS@
pm_read_LDADD = ../src/libopic.la @log4c_LIBS@
pm_read_LDFLAGS = -latomic
