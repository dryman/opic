noinst_PROGRAMS = robin_bench
AM_CFLAGS = -I$(top_builddir) @log4c_CFLAGS@

robin_bench_SOURCES = robin_bench.c rhh_b_k_v.c

robin_bench_LDADD = $(top_builddir)/opic/libopic.la \
  @PTHREAD_LIBS@ @atomic_LIBS@ @log4c_LIBS@
robin_bench_LDFLAGS = -static
