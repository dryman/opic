// Copyright (c) 2017 Felix Chern (Add extern "C" to make it compatible with C and C++)
// Copyright (c) 2015 Jason Schulz (Rewritten in C)
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
// http://code.google.com/p/cityhash/
//
// This file provides a few functions for hashing strings.  All of them are
// high-quality functions in the sense that they pass standard tests such
// as Austin Appleby's SMHasher.  They are also fast.
//
// For 64-bit x86 code, on short strings, we don't know of anything faster than
// CityHash64 that is of comparable quality.  We believe our nearest competitor
// is Murmur3.  For 64-bit x86 code, CityHash64 is an excellent choice for hash
// tables and most other hashing (excluding cryptography).
//
// For 64-bit x86 code, on long strings, the picture is more complicated.
// On many recent Intel CPUs, such as Nehalem, Westmere, Sandy Bridge, etc.,
// CityHashCrc128 appears to be faster than all competitors of comparable
// quality.  CityHash128 is also good but not quite as fast.  We believe our
// nearest competitor is Bob Jenkins' Spooky.  We don't have great data for
// other 64-bit CPUs, but for long strings we know that Spooky is slightly
// faster than CityHash on some relatively recent AMD x86-64 CPUs, for example.
// Note that CityHashCrc128 is declared in citycrc.h.
//
// For 32-bit x86 code, we don't know of anything faster than CityHash32 that
// is of comparable quality.  We believe our nearest competitor is Murmur3A.
// (On 64-bit CPUs, it is typically faster to use the other CityHash variants.)
//
// Functions in the CityHash family are not suitable for cryptography.
//
// Please see CityHash's README file for more details on our performance
// measurements and so on.
//
// WARNING: This code has been only lightly tested on big-endian platforms!
// It is known to work well on little-endian platforms that have a small penalty
// for unaligned reads, such as current Intel and AMD moderate-to-high-end CPUs.
// It should work on all 32-bit and 64-bit platforms that allow unaligned reads;
// bug reports are welcome.
//
// By the way, for some hash functions, given strings a and b, the hash
// of a+b is easily derived from the hashes of a and b.  This property
// doesn't hold for any hash functions in this file.

#ifndef C_CITYHASH_H
#define C_CITYHASH_H

#include <stdlib.h>
#include <stdint.h>
#include "largeint.h"

#if defined(__cplusplus)
extern "C" {
#endif

// hash function for a byte array
uint64_t cityhash64(const uint8_t* buf, size_t len);

// hash function for a byte array, for convenience a 64-bit seed is also
// hashed into the result
uint64_t cityhash64_with_seed(const uint8_t* buf, size_t len, uint64_t seed);

// hash function for a byte array, for convenience two seeds are also
// hashed into the result
uint64_t cityhash64_with_seeds(const uint8_t* buf, size_t len, uint64_t seed0,
                               uint64_t seed1);

// hash function for a byte array
uint128_t cityhash128(const uint8_t* s, size_t len);

// hash function for a byte array, for convenience a 128-bit seed is also
// hashed into the result
uint128_t cityhash128_with_seed(const uint8_t* s, size_t len, uint128_t seed);

// hash function for a byte array, most useful in 32-bit binaries
uint32_t cityhash32(const uint8_t* buf, size_t len);

// hash 128 input bits down to 64 bits of output
// this is intended to be a reasonably good hash function
static inline uint64_t hash_128_to_64(const uint128_t x) {

  // murmur-inspired hashing.
  const uint64_t kmul = 0x9ddfea08eb382d69; // 11376068507788127593

  uint64_t a, b;

  a = (x.a ^ x.b) * kmul;
  a ^= (a >> 47);

  b = (x.b ^ a) * kmul;
  b ^= (b >> 47);

  b *= kmul;

  return b;
}

// conditionally include declarations for versions of city that require SSE4.2
// instructions to be available
#if defined(__SSE4_2__) && defined(__x86_64)

// hash function for a byte array
uint128_t cityhash128_crc(const uint8_t* s, size_t len);

// hash function for a byte array, for convenience a 128-bit seed is also
// hashed into the result
uint128_t cityhash128_crc_with_seed(const uint8_t* s, size_t len,
                                    uint128_t seed);

// hash function for a byte array
uint256_t cityhash256_crc(const uint8_t* s, size_t len);

#endif

#if defined(__cplusplus)
}
#endif

#endif // C_CITY_HASH_H
