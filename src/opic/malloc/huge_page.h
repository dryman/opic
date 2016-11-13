/* huge_page.h --- 
 * 
 * Filename: huge_page.h
 * Description: 
 * Author: Felix Chern
 * Maintainer: 
 * Copyright: (c) 2016 Felix Chern
 * Created: Sat Oct 22, 2016
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

#ifndef HUGE_PAGE_H
#define HUGE_PAGE_H 1

#include <stdint.h>
#include <stdbool.h>
#include <stdatomic.h>
#include "opic/common/op_macros.h"
#include "opic/common/op_assert.h"
#include "opic/common/op_log.h"
#include "malloc_internal.h"
#include <assert.h>

OP_BEGIN_DECLS


HugePage* HugePageInit(void* addr, Magic magic)
  __attribute__((nonnull));

UnarySpan* ObtainUSpan(HugePage* self,
                       Magic magic,
                       unsigned int span_cnt)
  __attribute__((nonnull));

FreeStatus HugePageFree(HugePage* self, void* addr)
  __attribute__((nonnull));


OP_END_DECLS

#endif

/* huge_page.h ends here */
