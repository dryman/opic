AUTOMAKE_OPTIONS = subdir-objects
AM_CPPFLAGS = -I$(top_srcdir)/src

# Only used for debugging headers
bin_PROGRAMS = objdef
objdef_SOURCES = objdef.c ../common/op_log.c
objdef_CFLAGS = @log4c_CFLAGS@
#objdef_LDADD = $(top_srcdir)/src/opic/common/libopic_common.la @log4c_LIBS@ @PTHREAD_LIBS@
objdef_LDADD = @log4c_LIBS@ @PTHREAD_LIBS@
