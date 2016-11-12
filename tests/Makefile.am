TESTS = span_test huge_page_test
check_PROGRAMS = span_test huge_page_test

span_test_SOURCES = span_test.c
span_test_CPPFLAGS = -I$(top_srcdir)/src
span_test_CFLAGS = -std=c11 @log4c_CFLAGS@ @cmocka_CFLAGS@
span_test_LDADD = $(top_builddir)/src/libopic.la @log4c_LIBS@ @PTHREAD_LIBS@ @cmocka_LIBS@ @atomic_LIBS@
span_test_LDFLAGS = -static

huge_page_test_SOURCES = huge_page_test.c
huge_page_test_CPPFLAGS = -I$(top_srcdir)/src
huge_page_test_CFLAGS = -std=c11 @log4c_CFLAGS@ @cmocka_CFLAGS@
huge_page_test_LDADD = $(top_builddir)/src/libopic.la @log4c_LIBS@ @PTHREAD_LIBS@ @cmocka_LIBS@ @atomic_LIBS@
huge_page_test_LDFLAGS = -static
