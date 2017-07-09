/* op_utils.h ---
 *
 * Filename: op_utils.h
 * Description: Utility functions
 * Author: Felix Chern
 * Maintainer: Felix Chern
 * Created: Sat Oct  1 19:25:28 2016
 * Version:
 * Package-Requires: ()
 * Last-Updated:
 *           By:
 *     Update #: 0
 * URL:
 * Doc URL:
 * Keywords:
 * Compatibility:
 *
 */

/* Change Log:
 *
 *
 */

/* This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/* Code: */


#ifndef OPIC_COMMON_OP_UTILS_H
#define OPIC_COMMON_OP_UTILS_H 1

#include <stdint.h>
#include <stdbool.h>

#ifdef __AVX__
#include <immintrin.h>
#endif
#ifdef __SSE4_1__
#include <smmintrin.h>
#include <pmmintrin.h>
#endif
#ifdef __SSE2__
#include <emmintrin.h>
#endif

#include "op_macros.h"
#include "config.h"

OP_BEGIN_DECLS

#define round_up_div(X, Y) ((X) + (Y) - 1)/(Y)

static inline bool memeq(const void* ptr1, const void* ptr2, size_t num)
{
  uintptr_t p1, p2;
  p1 = (uintptr_t)ptr1;
  p2 = (uintptr_t)ptr2;

#ifdef __AVX2__
  for (; num > 32; num -= 32, p1 += 32, p2 += 32)
    {
      __m256i d1 = _mm256_lddqu_si256((void*)p1);
      __m256i d2 = _mm256_lddqu_si256((void*)p2);
      __m256i cmp = _mm256_cmpeq_epi64(d1, d2);
      int result = _mm256_movemask_pd((__m256d)cmp);
      if (result != 0x0F)
        return false;
    }
#endif

#ifdef __SSE4_1__
  for (; num > 16; num -= 16, p1 += 16, p2 += 16)
    {
      __m128i d1 = _mm_lddqu_si128((void*)p1);
      __m128i d2 = _mm_lddqu_si128((void*)p2);
      __m128i cmp = _mm_cmpeq_epi64(d1, d2);
      int result = _mm_movemask_pd((__m128d)cmp);
      if (result != 0x3)
        return false;
    }
#elif defined(__SSE2__)
  for (; num > 16; num -= 16, p1 += 16, p2 += 16)
    {
      __m128i d1 = _mm_loadu_si128((void*)p1);
      __m128i d2 = _mm_loadu_si128((void*)p2);
      __m128i cmp = _mm_cmpeq_epi32(d1, d2);
      int result = _mm_movemask_epi8(cmp);
      if (result != 0xFFFF)
        return false;
    }
#endif

  for (; num > 8; num -= 8, p1 += 8, p2 += 8)
    {
      uint64_t *d1 = (uint64_t*)p1;
      uint64_t *d2 = (uint64_t*)p2;
      if (*d1 != *d2)
        return false;
    }

  uint32_t *d1_32, *d2_32;
  uint16_t *d1_16, *d2_16;
  uint8_t *d1_8, *d2_8;
  switch(num)
    {
    case 7:
      d1_32 = (uint32_t*)p1;
      d2_32 = (uint32_t*)p2;
      d1_16 = (uint16_t*)(p1+4);
      d2_16 = (uint16_t*)(p2+4);
      d1_8 = (uint8_t*)(p1+6);
      d2_8 = (uint8_t*)(p2+6);
      return *d1_32 == *d2_32 && *d1_16 == *d2_16 && *d1_8 == *d2_8;
    case 6:
      d1_32 = (uint32_t*)p1;
      d2_32 = (uint32_t*)p2;
      d1_16 = (uint16_t*)(p1+4);
      d2_16 = (uint16_t*)(p2+4);
      return *d1_32 == *d2_32 && *d1_16 == *d2_16;
    case 5:
      d1_32 = (uint32_t*)p1;
      d2_32 = (uint32_t*)p2;
      d1_8 = (uint8_t*)(p1+4);
      d2_8 = (uint8_t*)(p2+4);
      return *d1_32 == *d2_32 && *d1_8 == *d2_8;
    case 4:
      d1_32 = (uint32_t*)p1;
      d2_32 = (uint32_t*)p2;
      return *d1_32 == *d2_32;
    case 3:
      d1_16 = (uint16_t*)p1;
      d2_16 = (uint16_t*)p2;
      d1_8 = (uint8_t*)(p1+2);
      d2_8 = (uint8_t*)(p2+2);
      return *d1_16 == *d2_16 && *d1_8 == *d2_8;
    case 2:
      d1_16 = (uint16_t*)p1;
      d2_16 = (uint16_t*)p2;
      return *d1_16 == *d2_16;
    case 1:
      d1_8 = (uint8_t*)p1;
      d2_8 = (uint8_t*)p2;
      return *d1_8 == *d2_8;
    default:
      return true;
    }

  /*
  for (; num > 4; num -= 4, p1 += 4, p2 += 4)
    {
      uint32_t *d1 = (uint32_t*)p1;
      uint32_t *d2 = (uint32_t*)p2;
      if (*d1 != *d2)
        return false;
    }

  for (; num > 2; num -= 2, p1 += 2, p2 += 2)
    {
      uint16_t *d1 = (uint16_t*)p1;
      uint16_t *d2 = (uint16_t*)p2;
      if (*d1 != *d2)
        return false;
    }

  if (num)
    {
      uint8_t *d1 = (uint8_t*)p1;
      uint8_t *d2 = (uint8_t*)p2;
      if (*d1 != *d2)
        return false;
    }
  return true;
  */
}

static inline int fftstr1 (uint32_t x, int n)
{
  int s;
  while (n > 1)
    {
      s = n >> 1;
      x = x & (x >> s);
      n = n - s;
    }
  if (x == 0) return -1;
  return __builtin_ctz(x);
}

static inline int fftstr0 (uint32_t x, int n)
{
  return fftstr1(~x, n);
}

// find first trailing string of 1 bits
// return -1 if no such string exists
// TODO: docuemnt this better. This is used for some bitmap magic
static inline int fftstr1l (uint64_t x, int n)
{
  int s;
  while (n > 1)
    {
      s = n >> 1;
      x = x & (x >> s);
      n = n - s;
    }
  if (x == 0) return -1;
  return __builtin_ctzl(x);
}

static inline int fftstr0l (uint64_t x, int n)
{
  return fftstr1l(~x, n);
}

OP_END_DECLS

#endif
/* op_utils.h ends here */
