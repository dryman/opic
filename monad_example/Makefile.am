AUTOMAKE_OPTIONS = subdir-objects
bin_PROGRAMS = maybe
maybe_SOURCES = ../src/op_trait.h ../src/op_macros.h \
monad.h monad.c functor.h functor.c maybe.h maybe.c maybe_main.c
maybe_LDADD = ../src/libopic.la
maybe_CFLAGS = -std=c11
maybe_LDFLAGS = -latomic
