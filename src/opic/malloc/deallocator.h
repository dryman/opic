/* deallocator.h ---
 *
 * Filename: deallocator.h
 * Description:
 * Author: Felix Chern
 * Maintainer:
 * Copyright: (c) 2017 Felix Chern
 * Created: Thu Mar 16 22:04:38 2017 (-0700)
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


#ifndef OPIC_MALLOC_DEALLOCATOR_H
#define OPIC_MALLOC_DEALLOCATOR_H 1

#include "objdef.h"

OP_BEGIN_DECLS

void USpanReleaseAddr(UnarySpan* uspan, void* addr);
void HPageReleaseSSpan(HugePage* hpage, SmallSpanPtr sspan);
void OPHeapReleaseHSpan(HugeSpanPtr hspan);

OP_END_DECLS

#endif
/* deallocator.h ends here */
