/* init_helper.c ---
 *
 * Filename: init_helper.c
 * Description:
 * Author: Felix Chern
 * Maintainer:
 * Created: Sat Mar  4 17:55:44 2017 (-0800)
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
 H*
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
 * You should have received a copy of the GNU Lesser General Public
 * License along with this program.  If not, see
 * <http://www.gnu.org/licenses/>.
 */

/* Code: */

void
OPHeapInit(OPHeap* heap)
{
}

void
HPageInit(HugePage* hpage)
{
}

void
HBlobInit(HugeBlob* hblob)
{
}

void
USpanInit(UnarySpan* uspan)
{
}

void
SBlobInit(SmallBlob* sblob)
{
}

void
OPHeapEmptiedBMaps(OPHeap* heap,
                   uint64_t* occupy_bmap,
                   uint64_t* header_bmap)
{
}

void
HPageEmptiedBMaps(HugePage* hpage,
                  uint64_t* occupy_bmap,
                  uint64_t* header_bmap)
{
}

void
USpanEmptiedBMap(UnarySpan* uspan, uint64_t* bmap)
{
}


/* init_helper.c ends here */
