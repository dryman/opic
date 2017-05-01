noinst_PROGRAMS = robin_bench
AM_CFLAGS = -I$(top_builddir) @log4c_CFLAGS@
AM_CXXFLAGS =  -I$(top_builddir)/cityhash/src

robin_bench_SOURCES = robin_bench.c \
  city_workaround.cc \
  rhh_b_k_v.c \
  rhh_b_kv.c \
  rhh_bkv.c \
  rhh_bkv_v4qu.c \
  rhh_b16kv.c

robin_bench_LDADD = $(top_builddir)/opic/libopic.la \
  @PTHREAD_LIBS@ @atomic_LIBS@ @log4c_LIBS@ \
  $(top_builddir)/cityhash/src/libcityhash.la
robin_bench_LDFLAGS = -static
