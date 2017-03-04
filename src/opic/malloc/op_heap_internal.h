/* op_lock_utils.h ---
 *
 * Filename: op_lock_utils.h
 * Description:
 * Author: Felix Chern
 * Maintainer:
 * Copyright: (c) 2016 Felix Chern
 * Created: Thu Nov  3 2016
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

#ifndef OP_HEAP_INTERNAL_H
#define OP_HEAP_INTERNAL_H 1

#include <stdint.h>
#include <stdbool.h>
#include <stdatomic.h>
#include "opic/common/op_macros.h"
#include "opic/common/op_atomic.h"
#include "opic/malloc/huge_page.h"
#include "opic/malloc/op_heap.h"

OP_BEGIN_DECLS


HugePage* ObtainHPage(OPHeap* self, Magic magic);

static inline OPHeap* get_opheap(void* addr)
{
  return (OPHeap*)((uintptr_t)addr & ~(OPHEAP_SIZE-1));
}

static inline void
insert_hpage_internal(HugePage** hpage_ref, HugePage* hpage)
{
  HugePage** it = hpage_ref;
  while (*it && (*it) < hpage)
    it = &(*it)->next;

  if (*it == NULL)
    {
      *it = hpage;
      return;
    }
  // TODO maybe we should assert *it > hpage
  // because equal case should not happen because we always
  // use try wlock.
  else if (*it > hpage)
    {
      hpage->next = (*it);
      *it = hpage;
      return;
    }
}

static inline bool
enqueue_new_raw_hpage(HugePage** hpage_ref,
                      a_int16_t* h_pcard,
                      OPHeap* heap)
{
  if (!atomic_enter_critical(h_pcard))
    return false;
  Magic magic = {.raw_hpage = {.pattern = RAW_HPAGE_PATTERN}};
  HugePage* hpage = ObtainHPage(heap, magic);
  insert_hpage_internal(hpage_ref, hpage);
  atomic_exit_critical(h_pcard);
  return true;
}

static inline bool
enqueue_new_typed_hpage(uint16_t type_alias_id,
                        HugePage** hpage_ref,
                        a_int16_t* h_pcard,
                        OPHeap* heap)
{
  if (!atomic_enter_critical(h_pcard))
    return false;
  Magic magic =
    {
      .typed_hpage =
      {
        .pattern = TYPED_HPAGE_PATTERN,
        .type_alias = type_alias_id
      }
    };
  HugePage* hpage = ObtainHPage(heap, magic);
  insert_hpage_internal(hpage_ref, hpage);
  atomic_exit_critical(h_pcard);
  return true;
}

static inline bool
enqueue_hpage(HugePage** hpage_ref,
              a_int16_t* h_pcard,
              HugePage* hpage)
{
  if (!atomic_enter_critical(h_pcard))
    return false;
  insert_hpage_internal(hpage_ref, hpage);
  atomic_exit_critical(h_pcard);
  return true;
}

static inline bool
dequeue_hpage(HugePage** hpage_ref,
              a_int16_t* h_pcard,
              HugePage* hpage)
{
  if (!atomic_enter_critical(h_pcard))
    return false;

  HugePage** it = hpage_ref;
  while (*it != hpage)
    it = &(*it)->next;

  *it = (*it)->next;
  atomic_exit_critical(h_pcard);
  return true;
}

static inline void
enqueue_uspan(UnarySpan** uspan_queue, UnarySpan* uspan)
{
  UnarySpan** it = uspan_ref;
  while (*it && (*it) < uspan)
    it = &(*it)->next;

  if (*it == NULL)
    {
      *it = uspan;
      return;
    }
  else if (*it > uspan)
    {
      uspan->next = (*it);
      *it = uspan;
      return;
    }
}

static inline void
insert_uspan_internal(UnarySpan** uspan_ref, UnarySpan* uspan)
{
  UnarySpan** it = uspan_ref;
  while (*it && (*it) < uspan)
    it = &(*it)->next;

  if (*it == NULL)
    {
      *it = uspan;
      return;
    }
  else if (*it > uspan)
    {
      uspan->next = (*it);
      *it = uspan;
      return;
    }
}

static inline bool
enqueue_new_raw_uspan(RawType* raw_type,
                      uint16_t size_class,
                      uint8_t tid,
                      OPHeap* heap)
{
  if (!atomic_enter_critical(&raw_type->uspan_pcard[size_class][tid]))
    return false;

  HugePage* hpage = NULL;
  UnarySpan* uspan = NULL;
  Magic magic =
    {
      .raw_uspan =
      {
        .pattern = RAW_USPAN_PATTERN,
        .obj_size = size_class,
        .thread_id = tid
      }
    };

  // TODO: we copied this part for three times
  // Shouldn't we create a new inline function for this?
  while (1)
    {
      if(!atomic_check_in(&raw_type->hpage_pcard))
        continue;
      hpage = raw_type->hpage;
      if (hpage == NULL)
        {
          if (!atomic_book_critical(&raw_type->hpage_pcard))
            {
              atomic_check_out(&raw_type->hpage_pcard);
              continue;
            }
          while (!enqueue_new_raw_hpage(&raw_type->hpage,
                                        &raw_type->hpage_pcard,
                                        heap))
            ;
        }

      // TODO: should optimize for different size classes
      // TODO: should pass-in uspan ref
      // TODO: use do {} while (obtained_state != BM_NORMAL)
      uspan = ObtainUSpan(hpage, magic, 1);
      atomic_check_out(&raw_type->hpage_pcard);
      if (uspan)
        break;
    }
  insert_uspan_internal(&raw_type->uspan[size_class][tid], uspan);
  atomic_exit_critical(&raw_type->uspan_pcard[size_class][tid]);
  return true;
}


static inline bool
enqueue_new_typed_uspan(TypeAlias* type_alias,
                        uint16_t obj_size,
                        uint8_t tid,
                        uint16_t type_alias_id,
                        OPHeap* heap)
{
  if (!atomic_enter_critical(&type_alias->uspan_pcard[tid]))
    return false;

  HugePage* hpage = NULL;
  UnarySpan* uspan = NULL;
  Magic magic =
    {
      .typed_uspan =
      {
        .pattern = TYPED_USPAN_PATTERN,
        .obj_size = obj_size,
        .thread_id = tid,
        .type_alias = type_alias_id
      }
    };

  while (1)
    {
      if(!atomic_check_in(&type_alias->hpage_pcard))
        continue;
      hpage = type_alias->hpage;
      if (hpage == NULL)
        {
          if (!atomic_book_critical(&type_alias->hpage_pcard))
            {
              atomic_check_out(&type_alias->hpage_pcard);
              continue;
            }
          while (!enqueue_new_typed_hpage(type_alias_id,
                                          &type_alias->hpage,
                                          &type_alias->hpage_pcard,
                                          heap))
            ;
        }

      // TODO: should optimize for different object size
      // TODO: should pass-in uspan ref
      // TODO: use do {} while (obtained_state != BM_NORMAL)
      uspan = ObtainUSpan(hpage, magic, 1);
      atomic_check_out(&type_alias->hpage_pcard);
      if (uspan)
        break;
    }

  insert_uspan_internal(&type_alias->uspan[tid], uspan);
  atomic_exit_critical(&type_alias->uspan_pcard[tid]);
  return true;
}

static inline bool
enqueue_new_large_uspan(RawType* raw_type,
                        int large_uspan_id,
                        int size_class,
                        int favor,
                        OPHeap* heap)
{
  if (!atomic_enter_critical(&raw_type->large_uspan_pcard[large_uspan_id]))
    return false;
  HugePage* hpage = NULL;
  UnarySpan* uspan = NULL;
  Magic magic =
    {
      .large_uspan =
      {
        .pattern = LARGE_USPAN_PATTERN,
        .obj_size = size_class,
      }
    };

  while (1)
    {
      if(!atomic_check_in(&raw_type->hpage_pcard))
        continue;
      hpage = raw_type->hpage;
      if (hpage == NULL)
        {
          if (!atomic_book_critical(&raw_type->hpage_pcard))
            {
              atomic_check_out(&raw_type->hpage_pcard);
              continue;
            }
          while (!enqueue_new_raw_hpage(&raw_type->hpage,
                                        &raw_type->hpage_pcard,
                                        heap))
            ;
        }

      // TODO: should optimize for different object size
      // TODO: should pass-in uspan ref
      // TODO: use do {} while (obtained_state != BM_NORMAL)
      uspan = ObtainUSpan(hpage, magic, 1);
      atomic_check_out(&raw_type->hpage_pcard);
      if (uspan)
        break;
    }

  insert_uspan_internal(&raw_type->large_uspan[large_uspan_id], uspan);
  atomic_exit_critical(&raw_type->large_uspan_pcard[large_uspan_id]);
  return true;
}

static inline bool
dequeue_hpage(HugePage** hpage_ref,
              a_int16_t pcard,
              HugePage* hpage)
{
  if (!atomic_enter_critical(pcard))
    return false;

  HugePage** it = hpage_ref;
  while (*it != hpage)
    it = &(*it)->next;

  *it = (*it)->next;
  atomic_exit_critical(pcard);
  return true;
}


static inline bool
dequeue_uspan(UnarySpan** uspan_ref,
              a_int8_t* pcard,
              UnarySpan* uspan)
{
  if (!atomic_enter_critical(pcard))
    return false;

  UnarySpan** it = uspan_ref;
  while (*it != uspan)
    it = &(*it)->next;

  *it = (*it)->next;
  atomic_exit_critical(pcard);
  return true;
}


static inline bool
dequeue_large_uspan(UnarySpan** uspan_ref,
                    a_int16_t* pcard,
                    UnarySpan* uspan)
{
  if (!atomic_enter_critical(pcard))
    return false;

  UnarySpan** it = uspan_ref;
  while (*it != uspan)
    it = &(*it)->next;

  *it = (*it)->next;
  atomic_exit_critical(pcard);
  return true;
}

OP_END_DECLS

#endif /* OP_HEAP_INTERNAL_H */
/* op_lock_utils.h ends here */
