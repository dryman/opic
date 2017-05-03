SUBDIRS = spookyhash-c cityhash-c farmhash-c
noinst_PROGRAMS = robin_bench
AM_CFLAGS = -I$(top_builddir) @log4c_CFLAGS@

robin_bench_SOURCES = robin_bench.c \
  rhh_b_k_v.c \
  rhh_b_kv.c \
  rhh_bkv.c \
  rhh_bkv_v4qu.c \
  rhh_b16kv.c

robin_bench_LDADD = $(top_builddir)/opic/libopic.la \
  @PTHREAD_LIBS@ @atomic_LIBS@ @log4c_LIBS@ \
  spookyhash-c/libspookyhash-c.la \
  cityhash-c/libcityhash-c.la \
  farmhash-c/libfarmhash-c.la
robin_bench_LDFLAGS = -static
