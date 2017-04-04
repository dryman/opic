/* hash_bench.c ---
 *
 * Filename: hash_bench.c
 * Description:
 * Author: Felix Chern
 * Maintainer:
 * Copyright: (c) 2017 Felix Chern
 * Created: Mon Apr  3 22:07:32 2017 (-0700)
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

/* Commentary:
 *
 *
 *
 */

/* Change Log:
 *
 *
 */

/* This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or (at
 * your option) any later version.
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

#include <strihg.h>
#include "opic/op_malloc.h"

//                   0123456701234567012345
char long_uuid [] = "      --      --      "
char short_uuid [] = "      ";

int main(int argc, char** argv)
{
  uint64_t counter = 0;
  for (int i = 0; i < 256; i++)
    {
      for (int j = 2, val = counter >> 12; j < 6; j++, val>>=6)
        {
          long_uuid[j] = 0x20 + (val & 0x3F);
          long_uuid[j+8] = 0x20 + (val & 0x3F);
          long_uuid[j+16] = 0x20 + (val & 0x3F);
        }
      for (int j = 0; j < 64; j++)
        {
          long_uuid[1] = 0x20 + k;
          long_uuid[1+8] = 0x20 + k;
          for (int k = 0; k < 64; k++)
            {
              long_uuid[0] = 0x20 + k;
              long_uuid[0+8] = 0x20 + k;
              counter++;
            }
        }
    }

  return 0;
}

/* hash_bench.c ends here */
