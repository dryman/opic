//-----------------------------------------------------------------------------
// MurmurHash3 was written by Austin Appleby, and is placed in the public
// domain. The author hereby disclaims copyright to this source code.

#ifndef _MURMURHASH3_H_
#define _MURMURHASH3_H_

#include "opic/common/op_macros.h"

//-----------------------------------------------------------------------------
// Platform-specific functions and macros

// Microsoft Visual Studio

#if defined(_MSC_VER) && (_MSC_VER < 1600)

typedef unsigned char uint8_t;
typedef unsigned int uint32_t;
typedef unsigned __int64 uint64_t;

// Other compilers

#else	// defined(_MSC_VER)

#include <stdint.h>

#endif // !defined(_MSC_VER)

//-----------------------------------------------------------------------------

OP_BEGIN_DECLS

void MurmurHash3_x64_128 ( const void * key, const int len,
                           const uint32_t seed, void * out );

void MurmurHash3_crc_x64_128 (const void * key, int len,
                              uint32_t seed, void * out,
                              uint32_t * crc_out);

OP_END_DECLS

//-----------------------------------------------------------------------------

#endif // _MURMURHASH3_H_
