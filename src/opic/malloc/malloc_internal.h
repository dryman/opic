#ifndef MALLOC_INTERNAL_H
#define MALLOC_INTERNAL_H

#include <stdint.h>
#include <stdbool.h>
#include <stdatomic.h>
#include "magic.h"
#include "opic/common/op_macros.h"

OP_BEGIN_DECLS

typedef struct UnarySpan UnarySpan;
typedef struct BolbSpan BlobSpan;
typedef struct HugePage HugePage;

struct UnarySpan
{
  const Magic magic;
  const uint8_t bitmap_cnt;
  const uint8_t bitmap_headroom;
  const uint8_t bitmap_padding;
  uint8_t bitmap_hint;
  UnarySpan* prev;
  UnarySpan* next;
};

static_assert(sizeof(UnarySpan) == 24, "UnaryPSpan size should be 24\n");

struct BlobSpan
{
  const Magic magic;
};

struct HugePage 
{
  const Magic magic;
  int32_t padding;
  HugePage* next;
  atomic_uint_fast64_t occupy_bmap[8];
  atomic_uint_fast64_t header_bmap[8];
};

static_assert(sizeof(HugePage) == 144, "HugePage size should be 144\n");

OP_END_DECLS

#endif
