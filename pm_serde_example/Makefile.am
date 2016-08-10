AUTOMAKE_OPTIONS = subdir-objects
bin_PROGRAMS = pm_test pm_read
pm_test_SOURCES = ../src/op_trait.h ../src/op_trait.c ../src/pm_memory_manager.c \
 ../src/pm_memory_manager.h \
 pm_test.c ../src/op_serializable.c ../src/op_serializable.h \
 ../src/op_collection.h ../src/op_collection.c \
 ../src/op_list.c ../src/op_list.h \
 ../src/op_linked_list.c ../src/op_linked_list.h
pm_test_CFLAGS = -std=c11
pm_test_LDFLAGS = -latomic

pm_read_SOURCES = ../src/op_trait.h ../src/op_trait.c ../src/pm_memory_manager.c \
 ../src/pm_memory_manager.h \
 pm_read.c ../src/op_serializable.c ../src/op_serializable.h \
 ../src/op_collection.h ../src/op_collection.c \
 ../src/op_list.c ../src/op_list.h \
 ../src/op_linked_list.c ../src/op_linked_list.h
pm_read_CFLAGS = -std=c11
pm_read_LDFLAGS = -latomic
