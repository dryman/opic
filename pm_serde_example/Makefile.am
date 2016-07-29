AUTOMAKE_OPTIONS = subdir-objects
bin_PROGRAMS = pm_test pm_read
pm_test_SOURCES = ../src/op_trait.h ../src/op_trait.c ../src/pm_memory_manager.c \
 ../src/pm_memory_manager.h \
 pm_test.c ../src/op_serializable.c ../src/op_serializable.h \
 pm_simple_list.c pm_simple_list.h \
 ../src/op_iterator.c ../src/op_iterator.h
pm_test_CFLAGS = -std=c11
pm_test_LDFLAGS = -latomic

pm_read_SOURCES = ../src/op_trait.h ../src/op_trait.c ../src/pm_memory_manager.c \
 ../src/pm_memory_manager.h \
 pm_read.c ../src/op_serializable.c ../src/op_serializable.h \
 pm_simple_list.c pm_simple_list.h
pm_read_CFLAGS = -std=c11
pm_read_LDFLAGS = -latomic
