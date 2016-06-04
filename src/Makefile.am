bin_PROGRAMS = pm_test pm_read
pm_test_SOURCES = op_trait.h op_trait.c pm_memory_manager.c pm_memory_manager.h \
 pm_test.c op_serializable.c op_serializable.h \
 pm_simple_list.c pm_simple_list.h
pm_test_CFLAGS = -std=c11
pm_test_LDFLAGS = -latomic

pm_read_SOURCES = op_trait.h op_trait.c pm_memory_manager.c pm_memory_manager.h \
 pm_read.c op_serializable.c op_serializable.h \
 pm_simple_list.c pm_simple_list.h
pm_read_CFLAGS = -std=c11
pm_read_LDFLAGS = -latomic

include_HEADERS = op_macros.h op_assert.h op_trait.h tc_map.h
