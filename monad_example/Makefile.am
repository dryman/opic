AUTOMAKE_OPTIONS = subdir-objects
bin_PROGRAMS = maybe
maybe_SOURCES = \
  ../src/opic.h \
  monad.h \
  monad.c \
  functor.h \
  functor.c \
  maybe.h \
  maybe.c \
  maybe_main.c
maybe_LDADD = ../src/libopic.la @PTHREAD_LIBS@
maybe_CFLAGS = -std=c11 @log4c_CFLAGS@ @PTHREAD_CFLAGS@
maybe_LDFLAGS = -latomic
