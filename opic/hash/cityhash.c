// Copyright (c) 2011 Google, Inc.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//
// CityHash, by Geoff Pike and Jyrki Alakuijala
//
// This file provides cityhash64() and related functions.
//
// It's probably possible to create even faster hash functions by
// writing a program that systematically explores some of the space of
// possible hash functions, by using SIMD instructions, or by
// compromising on hash quality.

#include <assert.h>
#include <string.h>

#include "cityhash.h"

#define likely(x) (__builtin_expect(!!(x), 1))

#ifdef LITTLE_ENDIAN
#define uint32_t_in_expected_order(x) (x)
#define uint64_t_in_expected_order(x) (x)
#else
#define uint32_t_in_expected_order(x) (bswap32(x))
#define uint64_t_in_expected_order(x) (bswap64(x))
#endif

#define PERMUTE3_32(a, b, c)                                                   \
  do {                                                                         \
    swap32(a, b);                                                              \
    swap32(a, c);                                                              \
  } while (0)

#define PERMUTE3_64(a, b, c)                                                   \
  do {                                                                         \
    swap64(a, b);                                                              \
    swap64(a, c);                                                              \
  } while (0)

// some primes between 2^63 and 2^64 for various uses
const uint64_t k0 = 0xc3a5c85c97cb3127;
const uint64_t k1 = 0xb492b66fbe98f273;
const uint64_t k2 = 0x9ae16a3b2f90404f;

// magic numbers for 32-bit hashing, copied from murmur3
static const uint32_t c1 = 0xcc9e2d51;
static const uint32_t c2 = 0x1b873593;

static uint64_t uload64(const uint8_t* p) {
  uint64_t result;

  memcpy(&result, p, sizeof(result));

  return result;
}

static uint32_t uload32(const uint8_t* p) {
  uint32_t result;

  memcpy(&result, p, sizeof(result));

  return result;
}

static uint64_t fetch64(const uint8_t* p) {
  return uint64_t_in_expected_order(uload64(p));
}

static uint32_t fetch32(const uint8_t* p) {
  return uint32_t_in_expected_order(uload32(p));
}

static uint32_t bswap32(const uint32_t x) {

  uint32_t y = x;

  for (size_t i = 0; i<sizeof(uint32_t)>> 1; i++) {

    uint32_t d = sizeof(uint32_t) - i - 1;

    uint32_t mh = ((uint32_t)0xff) << (d << 3);
    uint32_t ml = ((uint32_t)0xff) << (i << 3);

    uint32_t h = x & mh;
    uint32_t l = x & ml;

    uint64_t t = (l << ((d - i) << 3)) | (h >> ((d - i) << 3));

    y = t | (y & ~(mh | ml));
  }

  return y;
}

static uint64_t bswap64(const uint64_t x) {

  uint64_t y = x;

  for (size_t i = 0; i<sizeof(uint64_t)>> 1; i++) {

    uint64_t d = sizeof(uint64_t) - i - 1;

    uint64_t mh = ((uint64_t)0xff) << (d << 3);
    uint64_t ml = ((uint64_t)0xff) << (i << 3);

    uint64_t h = x & mh;
    uint64_t l = x & ml;

    uint64_t t = (l << ((d - i) << 3)) | (h >> ((d - i) << 3));

    y = t | (y & ~(mh | ml));
  }

  return y;
}

static void swap32(uint32_t* a, uint32_t* b) {
  uint32_t t;

  t = *a;
  *a = *b;
  *b = t;
}

static void swap64(uint64_t* a, uint64_t* b) {
  uint64_t t;

  t = *a;
  *a = *b;
  *b = t;
}

// a 32-bit to 32-bit integer hash copied from murmur3
static uint32_t fmix(uint32_t h) {

  h ^= h >> 16;
  h *= 0x85ebca6b;
  h ^= h >> 13;
  h *= 0xc2b2ae35;
  h ^= h >> 16;

  return h;
}

static uint32_t rotate32(uint32_t val, size_t shift) {

  assert(shift < 32);
  return (val >> shift) | (val << (32 - shift));
}

// helper from murmur3 for combining two 32-bit values
static uint32_t mur(uint32_t a, uint32_t h) {

  a *= c1;
  a = rotate32(a, 17);
  a *= c2;
  h ^= a;
  h = rotate32(h, 19);

  return h * 5 + 0xe6546b64;
}

static uint32_t hash32_13_to_24(const uint8_t* s, size_t len) {

  uint32_t a = fetch32(s - 4 + (len >> 1));
  uint32_t b = fetch32(s + 4);
  uint32_t c = fetch32(s + len - 8);
  uint32_t d = fetch32(s + (len >> 1));
  uint32_t e = fetch32(s);
  uint32_t f = fetch32(s + len - 4);
  uint32_t h = len;

  return fmix(mur(f, mur(e, mur(d, mur(c, mur(b, mur(a, h)))))));
}

static uint32_t hash32_0_to_4(const uint8_t* s, size_t len) {

  uint32_t b = 0;
  uint32_t c = 9;

  for (size_t i = 0; i < len; i++) {

    int8_t v = (int8_t)s[i];

    b = b * c1 + v;
    c ^= b;
  }

  return fmix(mur(b, mur(len, c)));
}

static uint32_t hash32_5_to_12(const uint8_t* s, size_t len) {

  uint32_t a = len, b = len * 5, c = 9, d = b;

  a += fetch32(s);
  b += fetch32(s + len - 4);
  c += fetch32(s + ((len >> 1) & 4));

  return fmix(mur(c, mur(b, mur(a, d))));
}

uint32_t cityhash32(const uint8_t* s, size_t len) {

  if (len <= 24) {

    return len <= 12
               ? (len <= 4 ? hash32_0_to_4(s, len) : hash32_5_to_12(s, len))
               : hash32_13_to_24(s, len);
  }

  // len > 24
  uint32_t h = len, g = c1 * len, f = g;
  uint32_t a0 = rotate32(fetch32(s + len - 4) * c1, 17) * c2;
  uint32_t a1 = rotate32(fetch32(s + len - 8) * c1, 17) * c2;
  uint32_t a2 = rotate32(fetch32(s + len - 16) * c1, 17) * c2;
  uint32_t a3 = rotate32(fetch32(s + len - 12) * c1, 17) * c2;
  uint32_t a4 = rotate32(fetch32(s + len - 20) * c1, 17) * c2;

  h ^= a0;
  h = rotate32(h, 19);
  h = h * 5 + 0xe6546b64;
  h ^= a2;
  h = rotate32(h, 19);
  h = h * 5 + 0xe6546b64;
  g ^= a1;
  g = rotate32(g, 19);
  g = g * 5 + 0xe6546b64;
  g ^= a3;
  g = rotate32(g, 19);
  g = g * 5 + 0xe6546b64;
  f += a4;
  f = rotate32(f, 19);
  f = f * 5 + 0xe6546b64;

  size_t iters = (len - 1) / 20;

  do {

    uint32_t a0 = rotate32(fetch32(s) * c1, 17) * c2;
    uint32_t a1 = fetch32(s + 4);
    uint32_t a2 = rotate32(fetch32(s + 8) * c1, 17) * c2;
    uint32_t a3 = rotate32(fetch32(s + 12) * c1, 17) * c2;
    uint32_t a4 = fetch32(s + 16);

    h ^= a0;
    h = rotate32(h, 18);
    h = h * 5 + 0xe6546b64;
    f += a1;
    f = rotate32(f, 19);
    f = f * c1;
    g += a2;
    g = rotate32(g, 18);
    g = g * 5 + 0xe6546b64;
    h ^= a3 + a1;
    h = rotate32(h, 19);
    h = h * 5 + 0xe6546b64;
    g ^= a4;
    g = bswap32(g) * 5;
    h += a4 * 5;
    h = bswap32(h);
    f += a0;
    PERMUTE3_32(&f, &h, &g);
    s += 20;
  } while (--iters != 0);

  g = rotate32(g, 11) * c1;
  g = rotate32(g, 17) * c1;
  f = rotate32(f, 11) * c1;
  f = rotate32(f, 17) * c1;
  h = rotate32(h + g, 19);
  h = h * 5 + 0xe6546b64;
  h = rotate32(h, 17) * c1;
  h = rotate32(h + f, 19);
  h = h * 5 + 0xe6546b64;
  h = rotate32(h, 17) * c1;

  return h;
}

// bitwise right rotate, normally this will compile to a single
// instruction, especially if the shift is a manifest constant.
static uint64_t rotate64(uint64_t val, size_t shift) {

  assert(shift < 64);
  return (val >> shift) | (val << (64 - shift));
}

static uint64_t smix(uint64_t val) { return val ^ (val >> 47); }

static uint64_t hash_16(uint64_t u, uint64_t v) {

  uint128_t result = {u, v};
  return hash_128_to_64(result);
}

static uint64_t hash_mur_16(uint64_t u, uint64_t v, uint64_t mul) {
  // murmur-inspired hashing

  uint64_t a = (u ^ v) * mul;
  a ^= (a >> 47);
  uint64_t b = (v ^ a) * mul;
  b ^= (b >> 47);
  b *= mul;

  return b;
}

static uint64_t hash_0_to_16(const uint8_t* s, size_t len) {

  if (len >= 8) {

    uint64_t mul = k2 + len * 2;
    uint64_t a = fetch64(s) + k2;
    uint64_t b = fetch64(s + len - 8);
    uint64_t c = rotate64(b, 37) * mul + a;
    uint64_t d = (rotate64(a, 25) + b) * mul;

    return hash_mur_16(c, d, mul);
  }

  if (len >= 4) {

    uint64_t mul = k2 + len * 2;
    uint64_t a = fetch32(s);

    return hash_mur_16(len + (a << 3), fetch32(s + len - 4), mul);
  }

  if (len > 0) {

    uint8_t a = s[0];
    uint8_t b = s[len >> 1];
    uint8_t c = s[len - 1];
    uint32_t y = ((uint32_t)a) + (((uint32_t)b) << 8);
    uint32_t z = len + (((uint32_t)c) << 2);

    return smix(y * k2 ^ z * k0) * k2;
  }

  return k2;
}

// This probably works well for 16-byte strings as well, but it may be overkill
// in that case.
static uint64_t hash_17_to_32(const uint8_t* s, size_t len) {

  uint64_t mul = k2 + len * 2;
  uint64_t a = fetch64(s) * k1;
  uint64_t b = fetch64(s + 8);
  uint64_t c = fetch64(s + len - 8) * mul;
  uint64_t d = fetch64(s + len - 16) * k2;

  return hash_mur_16(rotate64(a + b, 43) + rotate64(c, 30) + d,
                     a + rotate64(b + k2, 18) + c, mul);
}

// return a 16-byte hash for 48 bytes, quick and dirty
// callers do best to use "random-looking" values for a and b
static uint128_t weak_hash_32_with_seeds(uint64_t w, uint64_t x, uint64_t y,
                                         uint64_t z, uint64_t a, uint64_t b) {

  a += w;
  b = rotate64(b + a + z, 21);
  uint64_t c = a;
  a += x;
  a += y;
  b += rotate64(a, 44);

  uint128_t result = {a + z, b + c};

  return result;
}

// return a 16-byte hash for s[0] ... s[31], a, and b, quick and dirty
static uint128_t weak_hash_32_with_seeds_raw(const uint8_t* s, uint64_t a,
                                             uint64_t b) {

  return weak_hash_32_with_seeds(fetch64(s), fetch64(s + 8), fetch64(s + 16),
                                 fetch64(s + 24), a, b);
}

// return an 8-byte hash for 33 to 64 bytes
static uint64_t hash_33_to_64(const uint8_t* s, size_t len) {

  uint64_t mul = k2 + len * 2;
  uint64_t a = fetch64(s) * k2;
  uint64_t b = fetch64(s + 8);
  uint64_t c = fetch64(s + len - 24);
  uint64_t d = fetch64(s + len - 32);
  uint64_t e = fetch64(s + 16) * k2;
  uint64_t f = fetch64(s + 24) * 9;
  uint64_t g = fetch64(s + len - 8);
  uint64_t h = fetch64(s + len - 16) * mul;
  uint64_t u = rotate64(a + g, 43) + (rotate64(b, 30) + c) * 9;
  uint64_t v = ((a + g) ^ d) + f + 1;
  uint64_t w = bswap64((u + v) * mul) + h;
  uint64_t x = rotate64(e + f, 42) + c;
  uint64_t y = (bswap64((v + w) * mul) + g) * mul;
  uint64_t z = e + f + c;

  a = bswap64((x + z) * mul + y) + b;
  b = smix((z + a) * mul + d + h) * mul;

  return b + x;
}

uint64_t cityhash64(const uint8_t* s, size_t len) {

  if (len <= 32) {

    if (len <= 16) {

      return hash_0_to_16(s, len);
    } else {

      return hash_17_to_32(s, len);
    }
  } else if (len <= 64) {

    return hash_33_to_64(s, len);
  }

  // for strings over 64 bytes we hash the end first, and then as we
  // loop we keep 56 bytes of state: v, w, x, y, and z
  uint64_t x = fetch64(s + len - 40);
  uint64_t y = fetch64(s + len - 16) + fetch64(s + len - 56);
  uint64_t z = hash_16(fetch64(s + len - 48) + len, fetch64(s + len - 24));
  uint128_t v = weak_hash_32_with_seeds_raw(s + len - 64, len, z);
  uint128_t w = weak_hash_32_with_seeds_raw(s + len - 32, y + k1, x);

  x = x * k1 + fetch64(s);

  // decrease len to the nearest multiple of 64, and operate on 64-byte chunks
  len = (len - 1) & ~((size_t)63);

  do {

    x = rotate64(x + y + v.a + fetch64(s + 8), 37) * k1;
    y = rotate64(y + v.b + fetch64(s + 48), 42) * k1;
    x ^= w.b;
    y += v.a + fetch64(s + 40);
    z = rotate64(z + w.a, 33) * k1;
    v = weak_hash_32_with_seeds_raw(s, v.b * k1, x + w.a);
    w = weak_hash_32_with_seeds_raw(s + 32, z + w.b, y + fetch64(s + 16));
    swap64(&z, &x);
    s += 64;
    len -= 64;
  } while (len != 0);

  return hash_16(hash_16(v.a, w.a) + smix(y) * k1 + z, hash_16(v.b, w.b) + x);
}

uint64_t cityhash64_with_seed(const uint8_t* s, size_t len, uint64_t seed) {
  return cityhash64_with_seeds(s, len, k2, seed);
}

uint64_t cityhash64_with_seeds(const uint8_t* s, size_t len, uint64_t seed0,
                               uint64_t seed1) {
  return hash_16(cityhash64(s, len) - seed0, seed1);
}

// a subroutine for cityhash128(), returns a decent 128-bit hash for strings
// of any length representable in signed long, based on city and murmur
static uint128_t city_murmur(const uint8_t* s, size_t len, uint128_t seed) {

  uint64_t a = seed.a;
  uint64_t b = seed.b;
  uint64_t c = 0;
  uint64_t d = 0;
  signed long l = len - 16;

  if (l <= 0) { // len <= 16

    a = smix(a * k1) * k1;
    c = b * k1 + hash_0_to_16(s, len);
    d = smix(a + (len >= 8 ? fetch64(s) : c));
  } else { // len > 16

    c = hash_16(fetch64(s + len - 8) + k1, a);
    d = hash_16(b + len, c + fetch64(s + len - 16));
    a += d;

    do {

      a ^= smix(fetch64(s) * k1) * k1;
      a *= k1;
      b ^= a;
      c ^= smix(fetch64(s + 8) * k1) * k1;
      c *= k1;
      d ^= c;
      s += 16;
      l -= 16;
    } while (l > 0);
  }

  a = hash_16(a, c);
  b = hash_16(d, b);

  uint128_t result = {a ^ b, hash_16(b, a)};

  return result;
}

uint128_t cityhash128_with_seed(const uint8_t* s, size_t len, uint128_t seed) {

  if (len < 128) {
    return city_murmur(s, len, seed);
  }

  // we expect len >= 128 to be the common case, keep 56 bytes of state:
  // v, w, x, y, and z
  uint128_t v, w;
  uint64_t x = seed.a;
  uint64_t y = seed.b;
  uint64_t z = len * k1;

  v.a = rotate64(y ^ k1, 49) * k1 + fetch64(s);
  v.b = rotate64(v.a, 42) * k1 + fetch64(s + 8);
  w.a = rotate64(y + z, 35) * k1 + x;
  w.b = rotate64(x + fetch64(s + 88), 53) * k1;

  // this is the same inner loop as cityhash64(), manually unrolled
  do {

    x = rotate64(x + y + v.a + fetch64(s + 8), 37) * k1;
    y = rotate64(y + v.b + fetch64(s + 48), 42) * k1;
    x ^= w.b;
    y += v.a + fetch64(s + 40);
    z = rotate64(z + w.a, 33) * k1;
    v = weak_hash_32_with_seeds_raw(s, v.b * k1, x + w.a);
    w = weak_hash_32_with_seeds_raw(s + 32, z + w.b, y + fetch64(s + 16));
    swap64(&z, &x);
    s += 64;
    x = rotate64(x + y + v.a + fetch64(s + 8), 37) * k1;
    y = rotate64(y + v.b + fetch64(s + 48), 42) * k1;
    x ^= w.b;
    y += v.a + fetch64(s + 40);
    z = rotate64(z + w.a, 33) * k1;
    v = weak_hash_32_with_seeds_raw(s, v.b * k1, x + w.a);
    w = weak_hash_32_with_seeds_raw(s + 32, z + w.b, y + fetch64(s + 16));
    swap64(&z, &x);
    s += 64;
    len -= 128;
  } while (likely(len >= 128));

  x += rotate64(v.a + z, 49) * k0;
  y = y * k0 + rotate64(w.b, 37);
  z = z * k0 + rotate64(w.a, 27);
  w.a *= 9;
  v.a *= k0;

  // if 0 < len < 128, hash up to 4 chunks of 32 bytes each from the end of s
  for (size_t tail_done = 0; tail_done < len;) {

    tail_done += 32;
    y = rotate64(x + y, 42) * k0 + v.b;
    w.a += fetch64(s + len - tail_done + 16);
    x = x * k0 + w.a;
    z += w.b + fetch64(s + len - tail_done);
    w.b += v.a;
    v = weak_hash_32_with_seeds_raw(s + len - tail_done, v.a + z, v.b);
    v.a *= k0;
  }

  // at this point our 56 bytes of state should contain more than
  // enough information for a strong 128-bit hash, we use two
  // different 56-byte-to-8-byte hashes to get a 16-byte final result
  x = hash_16(x, v.a);
  y = hash_16(y + z, w.a);

  uint128_t result = {hash_16(x + v.b, w.b) + y, hash_16(x + w.b, y + v.b)};

  return result;
}

uint128_t cityhash128(const uint8_t* s, size_t len) {

  uint128_t seed;

  if (len >= 16) {

    uint128_t seed = {fetch64(s), fetch64(s + 8) + k0};
    return cityhash128_with_seed(s + 16, len - 16, seed);

  } else {

    uint128_t seed = {k0, k1};
    return cityhash128_with_seed(s, len, seed);
  }
}

// conditionally include declarations for versions of City that require SSE4.2
// instructions to be available
#if defined(__SSE4_2__) && defined(__x86_64)

#include <smmintrin.h>

// requires len >= 240
static uint256_t cityhash256_crc_long(const uint8_t* s, size_t len,
                                      uint32_t seed) {

  uint256_t result;

  uint64_t a = fetch64(s + 56) + k0;
  uint64_t b = fetch64(s + 96) + k0;
  uint64_t c = result.a = hash_16(b, len);
  uint64_t d = result.b = fetch64(s + 120) * k0 + len;
  uint64_t e = fetch64(s + 184) + seed;
  uint64_t f = 0;
  uint64_t g = 0;
  uint64_t h = c + d;
  uint64_t x = seed;
  uint64_t y = 0;
  uint64_t z = 0;

  // 240 bytes of input per iter
  size_t iters = len / 240;
  len -= iters * 240;

  do {
#define CHUNK(r)                                                               \
  PERMUTE3_64(&x, &z, &y);                                                     \
  b += fetch64(s);                                                             \
  c += fetch64(s + 8);                                                         \
  d += fetch64(s + 16);                                                        \
  e += fetch64(s + 24);                                                        \
  f += fetch64(s + 32);                                                        \
  a += b;                                                                      \
  h += f;                                                                      \
  b += c;                                                                      \
  f += d;                                                                      \
  g += e;                                                                      \
  e += z;                                                                      \
  g += x;                                                                      \
  z = _mm_crc32_u64(z, b + g);                                                 \
  y = _mm_crc32_u64(y, e + h);                                                 \
  x = _mm_crc32_u64(x, f + a);                                                 \
  e = rotate64(e, r);                                                          \
  c += e;                                                                      \
  s += 40

    CHUNK(0);
    PERMUTE3_64(&a, &h, &c);
    CHUNK(33);
    PERMUTE3_64(&a, &h, &f);
    CHUNK(0);
    PERMUTE3_64(&b, &h, &f);
    CHUNK(42);
    PERMUTE3_64(&b, &h, &d);
    CHUNK(0);
    PERMUTE3_64(&b, &h, &e);
    CHUNK(33);
    PERMUTE3_64(&a, &h, &e);
  } while (--iters > 0);

  while (len >= 40) {

    CHUNK(29);
    e ^= rotate64(a, 20);
    h += rotate64(b, 30);
    g ^= rotate64(c, 40);
    f += rotate64(d, 34);
    PERMUTE3_64(&c, &h, &g);
    len -= 40;
  }

  if (len > 0) {
    s = s + len - 40;
    CHUNK(33);
    e ^= rotate64(a, 43);
    h += rotate64(b, 42);
    g ^= rotate64(c, 41);
    f += rotate64(d, 40);
  }

  result.a ^= h;
  result.b ^= g;
  g += h;
  a = hash_16(a, g + z);
  x += y << 32;
  b += x;
  c = hash_16(c, z) + h;
  d = hash_16(d, e + result.a);
  g += e;
  h += hash_16(x, f);
  e = hash_16(a, d) + g;
  z = hash_16(b, c) + a;
  y = hash_16(g, h) + c;
  result.a = e + z + y + x;
  a = smix((a + y) * k0) * k0 + b;
  result.b += a + result.a;
  a = smix(a * k0) * k0 + c;
  result.c = a + result.b;
  a = smix((a + e) * k0) * k0;
  result.d = a + result.c;

  return result;
}

// requires len < 240
static uint256_t cityhash256_crc_short(const uint8_t* s, size_t len) {

  uint8_t buf[240];

  memcpy(buf, s, len);
  memset(buf + len, 0, 240 - len);

  return cityhash256_crc_long(buf, 240, ~((uint32_t)len));
}

uint256_t cityhash256_crc(const uint8_t* s, size_t len) {

  if (likely(len >= 240)) {
    return cityhash256_crc_long(s, len, 0);
  } else {
    return cityhash256_crc_short(s, len);
  }
}

uint128_t cityhash128_crc_with_seed(const uint8_t* s, size_t len,
                                    uint128_t seed) {

  if (len <= 900) {

    return cityhash128_with_seed(s, len, seed);

  } else {

    uint256_t hash = cityhash256_crc(s, len);

    uint64_t u = seed.b + hash.a;
    uint64_t v = seed.a + hash.b;

    uint128_t result = {hash_16(u, v + hash.c),
                        hash_16(rotate64(v, 32), u * k0 + hash.d)};
    return result;
  }
}

uint128_t cityhash128_crc(const uint8_t* s, size_t len) {

  if (len <= 900) {

    return cityhash128(s, len);
  } else {

    uint256_t hash = cityhash256_crc(s, len);
    uint128_t result = {hash.c, hash.d};

    return result;
  }
}

#endif
