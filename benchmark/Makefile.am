noinst_PROGRAMS = malloc_bench hash_bench

malloc_bench_SOURCES = malloc_bench.c
malloc_bench_LDADD = $(top_builddir)/opic/libdemomalloc.la \
  @PTHREAD_LIBS@ @atomic_LIBS@
malloc_bench_LDFLAGS = -static

hash_bench_SOURCES = hash_bench.c
hash_bench_LDADD = $(top_builddir)/opic/libdemomalloc.la \
  @PTHREAD_LIBS@ @atomic_LIBS@ -lm
hash_bench_LDFLAGS = -static
