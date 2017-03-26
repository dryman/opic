/* demomalloc.h ---
 *
 * Filename: demomalloc.h
 * Description:
 * Author: Felix Chern
 * Maintainer:
 * Copyright: (c) 2017 Felix Chern
 * Created: Sun Mar 26 12:07:34 2017 (-0700)
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

#ifndef OPIC_DEMOMALLOC_H
#define OPIC_DEMOMALLOC_H 1

#include "opic/common/op_macros.h"
#include "opic/op_malloc.h"

OP_BEGIN_DECLS

void* OPDemoMalloc(size_t size)
  __attribute__((malloc));

void* OPDemoCalloc(size_t num, size_t size)
  __attribute__((malloc));

void* OPDemoRealloc(void* addr, size_t size)
  __attribute__((malloc));

void OPDemoFree(void* addr);

/*
 * Somehow I cannot compile the code below on OSX.
 * Since replacing malloc is not the major goal, I'll just leave it here.
 */

/*
void* malloc(size_t size)
  __attribute__((weak, alias("OPDemoMalloc"))) __attribute__((malloc));

void* calloc(size_t num, size_t size)
  __attribute__((weak, alias("OPDemoCalloc"))) __attribute__((malloc));

void* realloc(void* addr, size_t size)
  __attribute__((weak, alias("OPDemoRealloc"))) __attribute__((malloc));

void free(void* addr)
  __attribute__((weak, alias("OPDemoFree")));
*/

OP_END_DECLS

#endif

/* demomalloc.h ends here */
