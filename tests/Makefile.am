TESTS = op_pspan_test op_vpage_test
check_PROGRAMS = op_pspan_test op_vpage_test

op_pspan_test_SOURCES = op_pspan_test.c
op_pspan_test_CPPFLAGS = -I$(top_srcdir)/src
op_pspan_test_CFLAGS = -std=c11 @log4c_CFLAGS@ @cmocka_CFLAGS@
op_pspan_test_LDADD = $(top_builddir)/src/libopic.la @log4c_LIBS@ @PTHREAD_LIBS@ @cmocka_LIBS@
op_pspan_test_LDFLAGS = -static

op_vpage_test_SOURCES = op_vpage_test.c
op_vpage_test_CPPFLAGS = -I$(top_srcdir)/src
op_vpage_test_CFLAGS = -std=c11 @log4c_CFLAGS@ @cmocka_CFLAGS@
op_vpage_test_LDADD = $(top_builddir)/src/libopic.la @log4c_LIBS@ @PTHREAD_LIBS@ @cmocka_LIBS@
op_vpage_test_LDFLAGS = -static
