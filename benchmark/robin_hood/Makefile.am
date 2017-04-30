noinst_PROGRAMS = robin_bench

robin_bench_SOURCES = robin_bench.c
robin_bench_LDADD = $(top_builddir)/opic/libopic.la \
  @PTHREAD_LIBS@ @atomic_LIBS@ @log4c_LIBS@
robin_bench_LDFLAGS = -static
