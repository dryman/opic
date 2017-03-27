bin_PROGRAMS = malloc_bench

malloc_bench_SOURCES = malloc_bench.c
malloc_bench_LDADD = $(top_builddir)/opic/libdemomalloc.la @PTHREAD_LIBS@ @atomic_LIBS@
malloc_bench_LDFLAGS = -static
