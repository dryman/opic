AM_CPPFLAGS = -I/usr/local/include
noinst_PROGRAMS = malloc_bench

malloc_bench_SOURCES = malloc_bench.c
malloc_bench_LDADD = $(top_builddir)/opic/libopic.la \
  @PTHREAD_LIBS@ @atomic_LIBS@ @log4c_LIBS@
malloc_bench_LDFLAGS = -static
