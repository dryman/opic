/* This may look like nonsense, but it really is -*- mode: C -*-              */
/*                                                                            */
/* Except for parts copied from previous work and as explicitly stated below, */
/* the author and copyright holder for this work is                           */
/* (C) copyright  2012-2014 Jens Gustedt, INRIA, France                       */
/*                                                                            */
/* This file is free software; it is part of the P99 project.                 */
/* You can redistribute it and/or modify it under the terms of the QPL as     */
/* given in the file LICENSE. It is distributed without any warranty;         */
/* without even the implied warranty of merchantability or fitness for a      */
/* particular purpose.                                                        */
/*                                                                            */
#ifndef P99_RAND_H
#define P99_RAND_H
#include "p99_threads.h"
#include "p99_new.h"
#include "p99_clib.h"

/** @file
 **
 ** @brief An implementation of George Marsaglia's xorshift PRG
 ** with a period of about 2^160
 **/

/**
 ** @addtogroup random Pseudo Random Generator
 ** @{
 **/

/* From: George Marsaglia (geo@stat.fsu.edu)    */
/* Subject: Re: good C random number generator  */
/* Newsgroups: comp.lang.c                      */
/* Date: 2003-05-13 08:55:05 PST                */

/* Here is an example with k=5, period about 2^160, one of the fastest
   long period RNGs, returns more than 120 million random 32-bit
   integers/second (1.8MHz CPU), seems to pass all tests: */

P99_CONSTANT(int, p00_seed160_len, 6);
typedef uint32_t p00_seed160[p00_seed160_len];

p99_inline
uint32_t p00_xorshift(p00_seed160 * p00_s) {
  /* Use the 6th element as the running index, and compute the
     necessary derived indices mod 5 */
  ++(*p00_s)[5];
  register uint32_t const p00_0 = ((*p00_s)[5]) % 5;
  register uint32_t const p00_4 = p00_0 == 0 ? 4 : p00_0-1;
  register uint32_t const p00_2 = (p00_0 == 4) ? 1 : ((p00_0 == 3) ? 0 : p00_0+2);

  /* Load the part of the state variable that we need. */
  register uint32_t const p00_x = (*p00_s)[p00_0];
  register uint32_t const p00_y = (*p00_s)[p00_2];
  register uint32_t const p00_v = (*p00_s)[p00_4];

  register uint32_t t = (p00_x^(p00_x>>7));
  t = (p00_v^(p00_v<<6))^(t^(t<<13));

  /* Change just one place in the state variables. */
  (*p00_s)[p00_4] = t;

  /* Multiply with an odd number */
  return (2*p00_y + 1) * t;
}

/**
 ** @brief The internal state that the PRG for ::p99_rand and
 ** ::p99_drand uses.
 **
 ** @remark Usually you don't have to deal with this type other than
 ** the cases described for ::p99_seed_get.
 **
 ** This is currently a set of 12 values of type @c uint32_t, so 384
 ** bits. Any reasonable initialization with true random bits of such
 ** a state variable should give you a different PRG of cycle length
 ** 2^160. (Reasonable here means that initializations with 160
 ** consecutive 0 bits or more should be avoided.)
 **
 ** P99 initializes a different state for each thread that uses the
 ** corresponding functions. The setup of that state for each thread
 ** may incur a cost of about 16 to 20 times the call to
 ** ::p99_rand. The initialization only produces one state out of
 ** 2^160 possibilities, so the state space of 384 is not used
 ** optimally.
 **
 ** Please let me know if you have an idea of using other portable
 ** sources of randomness for the initialization, currently we use the
 ** wall clock time, monotonic time (if available), the stack address
 ** of the thread and a per thread malloced address. This guarantees
 ** that the states are different for all threads that run
 ** concurrently (they will not have the same stack or malloced
 ** address) or that are scheduled with a suitable time difference
 ** that exceeds the clock granularity (they will not use the same
 ** time stamp).
 **
 ** All of this is only a heuristic and can be spoofed; it might
 ** give the same initial state for threads that are schedule in short
 ** sequence if:
 **  - the first thread terminates before the second is started
 **  - the second obtains the same time stamp as the first
 **  - the second is scheduled with the same stack address as the first
 **  - the second receives exactly the same address from @c malloc.
 **
 ** Under non-hostile circumstance this should only occur on a
 ** combination of platform and code that quickly launches a lot of
 ** threads (thousands) and has no good address randomization and a
 ** low granularity clock.
 **/
typedef p00_seed160 p99_seed[2];

struct p00_rand160 {
  p99_once_flag p00_flag;
  p99_seed p00_seed;
};

P99_DECLARE_THREAD_LOCAL(struct p00_rand160, p00_seed);

#define P00_BIGPRIME                                           \
UINT64_C(10007814641597694113),                                \
UINT64_C(10015183610531627897),                                \
UINT64_C(10089390291074425231),                                \
UINT64_C(10117275823191396191),                                \
UINT64_C(10215588060907623179),                                \
UINT64_C(10389441874873414061),                                \
UINT64_C(10602620510410479149),                                \
UINT64_C(10690793455755991027),                                \
UINT64_C(10793439684376201283),                                \
UINT64_C(10969167379420052431),                                \
UINT64_C(11050883422537956197),                                \
UINT64_C(11110712460003231287),                                \
UINT64_C(11342254921836171103),                                \
UINT64_C(11388752923558666351),                                \
UINT64_C(11682943258734137249),                                \
UINT64_C(11697622259988783581),                                \
UINT64_C(11731205802697935733),                                \
UINT64_C(11799524298339249581),                                \
UINT64_C(11862963432241722239),                                \
UINT64_C(11903172551239393097),                                \
UINT64_C(11937270107112816793),                                \
UINT64_C(11962673972948293321),                                \
UINT64_C(12001454206321043837),                                \
UINT64_C(12066567988703197129),                                \
UINT64_C(12090279337620046961),                                \
UINT64_C(12320220036580238077),                                \
UINT64_C(12409336420886496139),                                \
UINT64_C(12441355201341188273),                                \
UINT64_C(12444926949253327381),                                \
UINT64_C(12464345941324672183),                                \
UINT64_C(12469071720100075169),                                \
UINT64_C(12541090550165194183),                                \
UINT64_C(12558029109792848393),                                \
UINT64_C(12629045726855953273),                                \
UINT64_C(12845265184712635099),                                \
UINT64_C(12904165305535099733),                                \
UINT64_C(12949777725323667257),                                \
UINT64_C(13014679980528315931),                                \
UINT64_C(13027415158206533719),                                \
UINT64_C(13073256976558063279),                                \
UINT64_C(13153853421202095331),                                \
UINT64_C(13381351390611252151),                                \
UINT64_C(13825543164380321747),                                \
UINT64_C(13917403769616578911),                                \
UINT64_C(13929904570285153753),                                \
UINT64_C(14140216129016347127),                                \
UINT64_C(14184039880925065139),                                \
UINT64_C(14271570646513640671),                                \
UINT64_C(14446852824178510313),                                \
UINT64_C(14666997777683867003),                                \
UINT64_C(14692182605128454039),                                \
UINT64_C(14771388299183335229),                                \
UINT64_C(15059759696658839237),                                \
UINT64_C(15091316017205268437),                                \
UINT64_C(15180626055737690959),                                \
UINT64_C(15339437418814258573),                                \
UINT64_C(15601183704045111169),                                \
UINT64_C(15983170142123181797),                                \
UINT64_C(16545722488476290101),                                \
UINT64_C(16580005714519352107),                                \
UINT64_C(16589193612296178103),                                \
UINT64_C(16620171437104037921),                                \
UINT64_C(16713706803710883721),                                \
UINT64_C(16826711990149094791),                                \
UINT64_C(16886322755473635461),                                \
UINT64_C(16950140700365130619),                                \
UINT64_C(16952043704640877837),                                \
UINT64_C(17020386452131177189),                                \
UINT64_C(17020824347466355583),                                \
UINT64_C(17044414685455096133),                                \
UINT64_C(17089443963053420461),                                \
UINT64_C(17165479835541081871),                                \
UINT64_C(17185820514261086599),                                \
UINT64_C(17191892745505804273),                                \
UINT64_C(17613198595545138731),                                \
UINT64_C(17653178755564367203),                                \
UINT64_C(17653752776501147281),                                \
UINT64_C(17728444844615762171),                                \
UINT64_C(17744620187156425403),                                \
UINT64_C(17816722786105806973),                                \
UINT64_C(17831662963314755641),                                \
UINT64_C(17886004545482299117),                                \
UINT64_C(17920151933265509833),                                \
UINT64_C(17969552600607433963),                                \
UINT64_C(18066918898331824901),                                \
UINT64_C(18094173144238831753),                                \
UINT64_C(18134240252569387847),                                \
UINT64_C(18219113917191524677),                                \
UINT64_C(18298168206731166317),                                \
UINT64_C(18319234190200763803)

P99_CONST_FUNCTION
p99_inline
uint32_t p00_bitpack(void const* p00_p) {
  uintptr_t p00_u = (uintptr_t)p00_p;
#if UINTPTR_MAX == UINT32_MAX
  return p00_u;
#else
  uint32_t p00_r = 0;
  do {
    p00_r ^= p00_u;
    p00_u >>= (sizeof(uint32_t)*CHAR_BIT);
  } while (p00_u);
  return p00_r;
#endif
}


P99_WEAK(p00_rand_init)
void p00_rand_init(void* p00_p) {
  p99_seed * p00_s = p00_p
                     ? p00_p
                     : &P99_THREAD_LOCAL(p00_seed).p00_seed;
  /* local to this initialization call, stack address */
  uint32_t p00_0 = p00_bitpack(&p00_s);
  /* unique to this thread, heap address */
  uint32_t p00_1 = p00_bitpack(p00_p);
  struct timespec p00_ts;
  timespec_get(&p00_ts, TIME_UTC);
  uint32_t p00_2 = p00_ts.tv_sec;
  uint32_t p00_3 = p00_ts.tv_nsec;
#ifdef TIME_MONOTONIC
  struct timespec p00_tm;
  timespec_get(&p00_tm, TIME_MONOTONIC);
  uint32_t p00_4 = p00_tm.tv_nsec;
#else
  uint32_t p00_4 = p00_bitpack(__func__);
#endif
  /* index, unique to this thread */
  uint32_t p00_ind = p00_0 ^ p00_1 ^ p00_2 ^ p00_3 ^ p00_4;
  p00_seed160 p00_st = {
    p00_0,
    p00_1,
    p00_2,
    p00_3,
    p00_4,
    p00_ind,
  };
  /* mix things up a bit */
  for (unsigned p00_i = 0; p00_i < 32; ++p00_i) p00_xorshift(&p00_st);
  /* Now create two different state vectors that are de-phased. We
     can be in any state of the xorshift generator, so there are
     2^160 different initializations. */
  for (unsigned p00_j = 0; p00_j < 2; ++p00_j) {
    for (unsigned p00_i = 0; p00_i < p00_seed160_len; ++p00_i)
      (*p00_s)[p00_j][p00_i] = p00_xorshift(&p00_st);
  }
}

/**
 ** @brief Access the seed state for this particular thread.
 **
 ** The main purpose in user code of this function is to be able to
 ** store a pointer to the seed state at the beginning of the
 ** execution an then re-use that pointer on calls to ::p99_rand or
 ** ::p99_drand.
 **
 ** @code
 ** p99_seed * seed = p99_seed_get();
 **
 **
 ** for (size_t i = 0; i < largeNumber; ++i) {
 **   A[i] = p99_drand(seed);
 ** }
 ** @endcode
 **
 ** This avoids repetitive invocations of calls to ::p99_seed_get that
 ** usually can't be optimized away by the compiler.
 **
 ** It may also serve to establish a reproducible state of the random
 ** generator. You'd have to use this to access the state and pump any
 ** bit pattern of your favor over that state.
 **
 ** @code
 ** p99_seed * seed = p99_seed_get();
 ** memcpy(seed, (char [sizeof *seed]){ "some long string" }, sizeof *seed);
 ** @endcode
 **
 ** But beware that you'd have to apply that strategy in @b all
 ** threads and to a different value for each.
 **/
p99_inline
p99_seed * p99_seed_get(void) {
  struct p00_rand160 * p00_loc = &P99_THREAD_LOCAL(p00_seed);
  p99_call_once(&p00_loc->p00_flag, p00_rand_init, &p00_loc->p00_seed);
  return &p00_loc->p00_seed;
}

P99_WEAK(p00_bigprime)
uint64_t const p00_bigprime[] = { P00_BIGPRIME };

P99_CONSTANT(int, p00_bigprime_len, P99_ALEN(p00_bigprime));

/**
 ** @brief Return 64 bits of pseudo randomness
 **
 ** This uses a folded variant of the xorshift pseudo random
 ** generator.  It implements a set of about 2^160 pseudo random
 ** generators, each with a period of about 2^160. The main idea is to
 ** have two different xorshift generators run in sync giving two 32
 ** bit quantities and then to mangle up their results such that the
 ** individual bits can not be traced.
 **
 ** @warning This is not guaranteed to be cryptographically secure.
 **
 ** @param p00_seed is optional and represents state variable for the
 ** PRG. If omitted, every thread uses its own seed for this function.
 **
 ** @see p99_drand for a similar function that returns a @c double
 ** @see p99_seed_get for a discussion of the per thread state variable
 **/
P99_DEFARG_DOCU(p99_rand)
p99_inline
uint64_t p99_rand(register p99_seed * p00_seed) {
  uint32_t p00_0 = p00_xorshift(&(*p00_seed)[0]);
  uint64_t p00_1 = p00_xorshift(&(*p00_seed)[1]);
  uint64_t p00_0r = p00_0 % p00_bigprime_len;
  uint64_t p00_0d = p00_0 / p00_bigprime_len;
  /* Use part of the bits to choose a big number */
  p00_1 *= p00_bigprime[p00_0r];
  /* Use the rest of the bits to add more randomness */
  return (p00_0d ^ p00_1);
}

#ifndef DOXYGEN
#define p99_rand(...) P99_CALL_DEFARG(p99_rand, 1, __VA_ARGS__)
#define p99_rand_defarg_0() (p99_seed_get())
#endif

/**
 ** @brief Return a pseudo random double in the range from @c 0
 ** (inclusive) to @c 1 (exclusive).
 **
 ** @warning This is not guaranteed to be cryptographically secure.
 **
 ** @param p00_seed is optional and represents state variable for the
 ** PRG. If omitted, every thread uses its own seed for this function.
 **
 ** @see p99_rand for a similar function that returns an @c uint64_t
 ** and for a discussion of the PRG that is used
 **
 ** @see p99_seed_get for a discussion of the per thread state variable
 **/
P99_DEFARG_DOCU(p99_drand)
p99_inline
double p99_drand(register p99_seed * p00_seed) {
  enum {
    p00_s = (DBL_MANT_DIG > 64 ? 64 : DBL_MANT_DIG),
    p00_0 = 64 - p00_s,
    p00_m = (1 << p00_0),
  };
  double const p00_imax = 1.0 / (UINT64_C(1) << p00_s);
  uint64_t p00_r = p99_rand(p00_seed);
  double p00_1 = ((p00_r >> p00_0)^(p00_r & p00_m)) * p00_imax;
  return p00_1;
}

#ifndef DOXYGEN
#define p99_drand(...) P99_CALL_DEFARG(p99_drand, 1, __VA_ARGS__)
#define p99_drand_defarg_0() (p99_seed_get())
#endif

/**
 ** @}
 **/

#endif
