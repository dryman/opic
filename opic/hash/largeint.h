#ifndef LARGE_INT_H
#define LARGE_INT_H 1

#include <stdint.h>

struct uint128_t {
  uint64_t a;
  uint64_t b;
};

typedef struct uint128_t uint128_t;

static inline uint64_t uint128_t_low64(const uint128_t x) { return x.a; }
static inline uint64_t uint128_t_high64(const uint128_t x) { return x.b; }

static inline uint128_t make_uint128_t(uint64_t lo, uint64_t hi)
{
  uint128_t x = {lo, hi};
  return x;
}


// conditionally include declarations for versions of city that require SSE4.2
// instructions to be available
#if defined(__SSE4_2__) && defined(__x86_64)

struct uint256_t {
  uint64_t a;
  uint64_t b;
  uint64_t c;
  uint64_t d;
};

typedef struct uint256_t uint256_t;

#endif

#endif
