/* This may look like nonsense, but it really is -*- mode: C -*-              */
/*                                                                            */
/* Except for parts copied from previous work and as explicitly stated below, */
/* the author and copyright holder for this work is                           */
/* (C) copyright  2012-2013 Jens Gustedt, INRIA, France                       */
/*                                                                            */
/* This file is free software; it is part of the P99 project.                 */
/* You can redistribute it and/or modify it under the terms of the QPL as     */
/* given in the file LICENSE. It is distributed without any warranty;         */
/* without even the implied warranty of merchantability or fitness for a      */
/* particular purpose.                                                        */
/*                                                                            */
#ifndef P99_BITSET_H_
#define P99_BITSET_H_

#include "p99_tss.h"
#include "p99_c99.h"
#include "p99_errno.h"
#include "p99_int.h"


#if defined(UINT128_MAX)
typedef uint128_t p99_bitset;
# define P00_ISIN p00_isin2
#elif defined(p99x_uint128)
typedef p99x_uint128 p99_bitset;
# define P00_ISIN p00_isin2
#else
//#error "didn't find 128 bit type"
typedef uint64_t p99_bitset;
# define P00_ISIN p00_isin4
#endif

# define P99_BITSET_C(X) ((p99_bitset)+(X))

P99_CONSTANT(int, p99_bitset_bit, sizeof(p99_bitset)*CHAR_BIT);
P99_CONSTANT(int, p00_bitset_bit1, p99_bitset_bit);
P99_CONSTANT(int, p00_bitset_bit2, p99_bitset_bit<<1);
P99_CONSTANT(int, p00_bitset_bit3, p00_bitset_bit1|p00_bitset_bit2);

P99_CONST_FUNCTION
p99_inline
uint8_t p00_bit_low(uint8_t p00_c) {
  return p00_c % p99_bitset_bit;
}

P99_CONST_FUNCTION
p99_inline
uint8_t p00_bit_high(uint8_t p00_c) {
  return p00_c / p99_bitset_bit;
}

P99_CONST_FUNCTION
p99_inline
p99_bitset p00_set_bit(uint8_t p00_c) {
  return P99_BITSET_C(1) << p00_bit_low(p00_c);
}

#define P00_BITSET_CASE(B, _1, I) case I: if (p00_bit_high(p00_s2[I]) == B) p00_ret |= p00_set_bit(p00_s2[I])
#define P00_BITSET_CASE128(B, _1, I) case I+128: if (p00_bit_high(p00_s2[I+128]) == B) p00_ret |= p00_set_bit(p00_s2[I+128])


#define P00_BITS_DECLARE(B)                                                                         \
P99_CONST_FUNCTION                                                                                  \
p99_inline                                                                                          \
p99_bitset P99_PASTE2(p00_bits, B)(rsize_t p00_s2l, uint8_t const p00_s2[const restrict p00_s2l]) { \
  p99_bitset p00_ret = 0;                                                                           \
  switch (p00_s2l - 2) {                                                                            \
    P99_FOR(B, 128, P00_PES, P00_BITSET_CASE128, P00_ALLZERO);                                      \
    P99_FOR(B, 128, P00_PES, P00_BITSET_CASE, P00_ALLZERO);                                         \
  }                                                                                                 \
  return p00_ret;                                                                                   \
}                                                                                                   \
P99_MACRO_END(P00_BITS_DECLARE, B)

P00_BITS_DECLARE(0);
P00_BITS_DECLARE(1);
P00_BITS_DECLARE(2);
P00_BITS_DECLARE(3);

P99_CONST_FUNCTION
p99_inline
p99_bitset p00_isin1(uint8_t p00_c,
                     rsize_t p00_s2l, uint8_t const p00_s2[const restrict p00_s2l]) {
  register p99_bitset const p00_b0 = p00_bits0(p00_s2l, p00_s2);
  register p99_bitset p00_ret = p00_set_bit(p00_c);
  p00_ret &= p00_b0;
  return p00_ret;
}

P99_CONST_FUNCTION
p99_inline
p99_bitset p00_isin2(uint8_t p00_c,
                     rsize_t p00_s2l, uint8_t const p00_s2[const restrict p00_s2l]) {
  register p99_bitset const p00_b0 = p00_bits0(p00_s2l, p00_s2);
  register p99_bitset const p00_b1 = p00_bits1(p00_s2l, p00_s2);

  register p99_bitset p00_ret = p00_set_bit(p00_c);
  p00_ret &= (p00_c < p99_bitset_bit) ? p00_b0 : p00_b1;
  return p00_ret;
}

P99_CONST_FUNCTION
p99_inline
p99_bitset p00_isin4(uint8_t p00_c,
                     rsize_t p00_s2l, uint8_t const p00_s2[const restrict p00_s2l]) {
  register p99_bitset const p00_b0 = p00_bits0(p00_s2l, p00_s2);
  register p99_bitset const p00_b1 = p00_bits1(p00_s2l, p00_s2);
  register p99_bitset const p00_b2 = p00_bits2(p00_s2l, p00_s2);
  register p99_bitset const p00_b3 = p00_bits3(p00_s2l, p00_s2);

  register p99_bitset p00_ret = p00_set_bit(p00_c);
  switch (p00_c & p00_bitset_bit3) {
  default: p00_ret &= p00_b0; break;
  case p00_bitset_bit1: p00_ret &= p00_b1; break;
  case p00_bitset_bit2: p00_ret &= p00_b2; break;
  case p00_bitset_bit3: p00_ret &= p00_b3; break;
  }
  return p00_ret;
}

#define P00_BLANK " \t"
#define P00_SPACE " \f\n\r\t\v"
#define P00_LOWER "abcdefghijklmnopqrstuvwxyz"
#define P00_UPPER "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
#define P00_ALPHA P00_UPPER P00_LOWER
#define P00_DIGIT "0123456789"
#define P00_ALNUM P00_ALPHA P00_DIGIT
#define P00_XDIGIT "0123456789abcdefABCDEF"

P99_CONST_FUNCTION
p99_inline
p99_bitset p99_is_blank(uint8_t p00_c) {
  return P00_ISIN(p00_c, sizeof P00_BLANK, (uint8_t const*)P00_BLANK);
}

P99_CONST_FUNCTION
p99_inline
p99_bitset p99_is_space(uint8_t p00_c) {
  return P00_ISIN(p00_c, sizeof P00_SPACE, (uint8_t const*)P00_SPACE);
}

P99_CONST_FUNCTION
p99_inline
p99_bitset p99_is_lower(uint8_t p00_c) {
  return P00_ISIN(p00_c, sizeof P00_LOWER, (uint8_t const*)P00_LOWER);
}

P99_CONST_FUNCTION
p99_inline
p99_bitset p99_is_upper(uint8_t p00_c) {
  return P00_ISIN(p00_c, sizeof P00_UPPER, (uint8_t const*)P00_UPPER);
}

P99_CONST_FUNCTION
p99_inline
p99_bitset p99_is_alpha(uint8_t p00_c) {
  return P00_ISIN(p00_c, sizeof P00_ALPHA, (uint8_t const*)P00_ALPHA);
}

P99_CONST_FUNCTION
p99_inline
p99_bitset p99_is_digit(uint8_t p00_c) {
  return P00_ISIN(p00_c, sizeof P00_DIGIT, (uint8_t const*)P00_DIGIT);
}

P99_CONST_FUNCTION
p99_inline
p99_bitset p99_is_xdigit(uint8_t p00_c) {
  return P00_ISIN(p00_c, sizeof P00_XDIGIT, (uint8_t const*)P00_XDIGIT);
}

P99_CONST_FUNCTION
p99_inline
p99_bitset p99_is_alnum(uint8_t p00_c) {
  return P00_ISIN(p00_c, sizeof P00_ALNUM, (uint8_t const*)P00_ALNUM);
}

#endif
