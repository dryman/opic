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


#ifndef OP_UTILS_H
#define OP_UTILS_H 1

#include "op_macros.h"
#include "config.h"
#include <stdint.h>

OP_BEGIN_DECLS

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
