bin_PROGRAMS = pm_test pm_read
pm_test_SOURCES = pm_test.c 
pm_test_CPPFLAGS = -I$(top_srcdir)/src
pm_test_CFLAGS = -std=c11 @log4c_CFLAGS@
pm_test_LDADD = $(top_srcdir)/src/libopic.la @log4c_LIBS@ -latomic @PTHREAD_LIBS@
pm_test_LDFLAGS = -static

pm_read_SOURCES = pm_read.c
pm_read_CPPFLAGS = -I$(top_srcdir)/src
pm_read_CFLAGS = -std=c11 @log4c_CFLAGS@
pm_read_LDADD = $(top_srcdir)/src/libopic.la @log4c_LIBS@ -latomic @PTHREAD_LIBS@
