/* inline_aux.h ---
 *
 * Filename: inline_aux.h
 * Description:
 * Author: Felix Chern
 * Maintainer:
 * Copyright: (c) 2016 Felix Chern
 * Created: Sat Mar  4 09:42:46 2017 (-0800)
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

#ifndef OPIC_MALLOC_INLINE_AUX_H
#define OPIC_MALLOC_INLINE_AUX_H 1

#include <stdint.h>
#include <stddef.h>

#include "opic/common/op_atomic.h"
#include "opic/common/op_macros.h"
#include "magic.h"
#include "objdef.h"

OP_BEGIN_DECLS

// TODO: may Rewrite with inline function + C11 generics
#define round_up_div(X, Y) ((X) + (Y) - 1)/(Y)


static inline void
EnqueueUSpan(UnarySpanQueue* uspan_queue, UnarySpan* uspan)
{
  UnarySpan** it = &uspan_queue->uspan;

  while (*it && (*it) < uspan)
    it = &(*it)->next;

  if (*it != uspan)
    {
      if (*it > uspan)
        uspan->next = *it;
      *it = uspan;
    }

  atomic_store_explicit(&uspan->state, SPAN_ENQUEUED, memory_order_release);
}

static inline void
DequeueUSpan(UnarySpanQueue* uspan_queue, UnarySpan* uspan)
{
  UnarySpan** it = &uspan_queue->uspan;

  while (*it != uspan && *it)
    it = &(*it)->next;

  if (*it)
    *it = (*it)->next;

  atomic_store_explicit(&uspan->state, SPAN_DEQUEUED, memory_order_release);
}

static inline void
EnqueueHPage(HugePageQueue* hpage_queue, HugePage* hpage)
{
  HugePage** it = &hpage_queue->hpage;

  while (*it && (*it) < hpage)
    it = &(*it)->next;

  if (*it != hpage)
    {
      if (*it > hpage)
        hpage->next = *it;

      *it = hpage;
    }

  atomic_store_explicit(&hpage->state, SPAN_ENQUEUED, memory_order_release);
}

static inline void
DequeueHPage(HugePageQueue* hpage_queue, HugePage* hpage)
{
  HugePage** it = &hpage_queue->hpage;

  while (*it && *it != hpage)
    it = &(*it)->next;

  if (*it)
    *it = (*it)->next;

  atomic_store_explicit(&hpage->state, SPAN_DEQUEUED, memory_order_release);
}

OP_END_DECLS

#endif
/* inline_aux.h ends here */
