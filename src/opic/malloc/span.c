/* op_pspan.c --- 
 * 
 * Filename: op_pspan.c
 * Description: 
 * Author: Felix Chern
 * Maintainer: 
 * Copyright: (c) 2016 Felix Chern
 * Created: Sat Oct 8, 2016
 * Version: 0.3.0
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

#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include "span.h"
#include "opic/common/op_atomic.h"

#define round_up_div(X, Y) ((X) + (Y) - 1)/(Y)

extern void enqueue_uspan(UnarySpan* uspan);
extern void dequeue_uspan(UnarySpan* uspan);

UnarySpan* USpanInit(void* addr, Magic magic, size_t span_size)
{
  /* Unit test as of Oct 9, 2016 doesn't support op_assert
     Our workaround is return NULL instead. But this should be fixed.
  op_assert(addr, "address cannot be NULL");
  op_assert(obj_size, "object size in bytes should be greater than 0\n");
  op_assert(page_size, "allocated physical pages should be greater than 0\n");
  */
  if (op_unlikely(!magic.typed_uspan.obj_size)) return NULL;
  if (op_unlikely(!span_size)) return NULL;
  
  unsigned int obj_size, obj_cnt, bitmap_cnt, padding, headroom;
  uintptr_t iaddr;
  uint64_t* bmap;
  
  obj_size = magic.typed_uspan.obj_size;
  /* Number of objects fits into the span, regardless of header.  Note
   * this is different to the capcity of object that can stored in this
   * span.  The capacity should be calculated as
   * bitmap_cnt * 64 - headroom - padding.
   */
  obj_cnt = span_size / obj_size;
  bitmap_cnt = round_up_div(obj_cnt, 64);
  padding = (bitmap_cnt << 6) - obj_cnt;
  headroom = (sizeof(UnarySpan) + bitmap_cnt*8 + obj_size - 1)/obj_size;

  op_assert(headroom < 64,
            "headroom should be less equal to 64, but were %d\n", headroom);
  
  UnarySpan span = 
    {
      .magic = magic,
      .bitmap_cnt = (uint8_t)bitmap_cnt,
      .bitmap_headroom = (uint8_t)headroom,
      .bitmap_padding = (uint8_t)padding,
      .bitmap_hint = 0,
      .pcard = 0,
      .obj_cnt = 0,
      .state = BM_NEW,
      .next = NULL
    };

  memcpy(addr, &span, sizeof(span));

  // Point to the first bitmap
  iaddr = (uintptr_t)addr + sizeof(UnarySpan);
  // Set all bitmap to 0
  memset((void*)iaddr, 0, bitmap_cnt << 3);
  // Mark the headroom bits
  bmap = (uint64_t*)iaddr;
  *bmap |= (1UL << headroom) - 1;
  
  // Mark the padding bits
  if (padding)
    {
      bmap = (uint64_t*)(iaddr + (bitmap_cnt - 1) * 8);
      *bmap |=  ~((1UL << (64-padding))-1);
    }
  
  atomic_thread_fence(memory_order_release);
  return (UnarySpan*) addr;
}

bool USpanMalloc(UnarySpan* self, void** addr)
{
  if (!atomic_check_in(&self->pcard))
    return false;

  BitMapState state;
  a_uint64_t *bitmap_base, *bitmap;
  uintptr_t base;
  ptrdiff_t bitmap_offset, item_offset;
  uint64_t old_bmap, new_bmap;
  uint16_t obj_size, obj_cnt, obj_capacity;
  OPHeap* heap;
  
  state = atomic_load_explicit(&self->state,
                               memory_order_relaxed);

  // TODO: document the state machine.
  // When state == BM_NEW, obj_cnt can change from 0 to 1;
  // but when state is BM_NORMAL, obj_cnt == 0 is same as BM_TOMBSTONE
  if (state == BM_NORMAL &&
      atomic_load_explicit(&self->obj_cnt,
                           memory_order_relaxed) == 0)
    {
      atomic_check_out(&self->pcard);
      return false;
    }

  obj_cnt = atomic_fetch_add_explicit(&self->obj_cnt, 1,
                                      memory_order_acquire);
  obj_capacity = ((uint16_t)self->bitmap_cnt)*64 -
    self->bitmap_headroom - self->bitmap_padding;

  if (obj_cnt > obj_capacity)
    {
      goto uspan_full;
    }

  base = (uintptr_t)self;
  obj_size = self->magic.typed_uspan.obj_size;
  bitmap_base = (a_uint64_t *)(base + sizeof(UnarySpan));
  bitmap_offset = (ptrdiff_t)self->bitmap_hint;
  bitmap = bitmap_base + bitmap_offset;

  while (1)
    {
      old_bmap = atomic_load_explicit(bitmap, memory_order_relaxed);
      do
        {
          if (old_bmap == ~0UL) goto next_bmap;
          new_bmap = (old_bmap + 1);
          item_offset = __builtin_ctzl(new_bmap);
          new_bmap |= old_bmap;
        }
      while(!atomic_compare_exchange_strong_explicit
            (bitmap, &old_bmap, new_bmap,
             memory_order_relaxed,
             memory_order_relaxed));
      *addr = (void*)(base + (bitmap_offset * 64 + item_offset) * obj_size);
      self->bitmap_hint = (uint8_t)bitmap_offset;
      atomic_check_out(&self->pcard);
      return true;
      
    next_bmap:
      bitmap_offset++;
      bitmap_offset %= self->bitmap_cnt;
      bitmap = bitmap_base + bitmap_offset;
    }
  
 uspan_full:
  /* If we couldn't book, there were some other thread booked the critical
     section.  Retry and start over again. */
  if (!atomic_book_critical(&self->pcard))
    {
      atomic_fetch_sub_explicit(&self->obj_cnt, 1, memory_order_relaxed);
      atomic_check_out(&self->pcard);
      return false;
    }
  while (!atomic_enter_critical(&self->pcard))
    ;
  atomic_store_explicit(&self->state, BM_FULL, memory_order_relaxed);
  atomic_fetch_sub_explicit(&self->obj_cnt, 1, memory_order_relaxed);

  heap = get_opheap(self);

  // TODO: document why we check-out then do the check-in, book loops.
  // This is how we avoid data races.
  switch (self->magic.uspan_generic.pattern)
    {
    case TYPED_USPAN_PATTERN:
      {
        TypeAlias* ta = &heap->type_alias[self->magic.typed_uspan.type_alias];
        int tid = self->magic.typed_uspan.thread_id;
        atomic_check_out(&ta->uspan_pcard[tid]);
        while (1) 
          {
            if (!atomic_check_in(&ta->uspan_pcard[tid]))
              continue;            
            if (atomic_book_critical(&ta->uspan_pcard[tid]))
              break;
            atomic_check_out(&ta->uspan_pcard[tid]);
          }
        while (!dequeue_uspan(&ta->uspan[tid],
                              &ta->uspan_pcard[tid],
                              self))
          ;
        break;
      }
    case RAW_USPAN_PATTERN:
      {
        uint16_t size_class = self->magic.raw_uspan.obj_size / 16;
        int tid = self->magic.raw_uspan.thread_id;
        atomic_check_out(&heap->raw_type.uspan_pcard[size_class][tid]);
        while (1)
          {
            if (!atomic_check_in(&heap->raw_type.uspan_pcard[size_class][tid]))
              continue;
            if (atomic_book_critical
                (&heap->raw_type.uspan_pcard[size_class][tid]))
              break;
            atomic_check_out(&heap->raw_type.uspan_pcard[size_class][tid]);
          }
        while (!dequeue_uspan
               (&heap->raw_type.uspan[size_class][tid],
                &heap->raw_type.uspan_pcard[size_class][tid],
                self))
          ;
        break;
      }
    case LARGE_USPAN_PATTERN:
      {
        uint16_t obj_size = self->magic.large_uspan.obj_size;
        int uid =
          obj_size == 512 ? 0 :
          obj_size == 1024 ? 1 : 2;
        atomic_check_out(&heap->raw_type.large_uspan_pcard[uid]);
        while (1)
          {
            if (!atomic_check_in(&heap->raw_type.large_uspan_pcard[uid]))
              continue;
            if (atomic_book_critical
                (&heap->raw_type.large_uspan_pcard[uid]))
              break;
            atomic_check_out(&heap->raw_type.large_uspan_pcard[uid]);
          }
        while (!dequeue_uspan
               (&heap->raw_type.large_uspan[uid],
                &heap->raw_type.large_uspan_pcard[uid],
                self))
          ;
        break;
      }
    } // end of switch
  atomic_check_out(&self->pcard);
  return false;
}

BitMapState USpanFree(UnarySpan* self, void* addr)
{
  uintptr_t base, iaddr, bound;
  int obj_size, addr_idx, bmap_idx, item_idx;
  a_uint64_t* bitmap;
  OPHeap* heap;
  uint16_t obj_cnt;
  uint64_t expected_empty_bmap;


  // Locate the bitmap and item index, and validate its correctness
  base = (uintptr_t)self;
  iaddr = (uintptr_t)addr;
  obj_size = self->magic.uspan_generic->obj_size;
  bound = base + obj_size * (64 * self->bitmap_cnt - self->bitmap_padding);
  bitmap = (a_uint64_t *)(base + sizeof(UnarySpan));
  addr_idx = (iaddr - base) / obj_size;
  bmap_idx = addr_idx / 64;
  item_idx = addr_idx - bmap_idx * 64;
  heap = get_opheap(self);

  op_assert(iaddr > base && iaddr < bound,
            "Free address %p should within span from %p and %p",
            addr, (void*)base, (void*)bound);
  
  op_assert(addr_idx * obj_size + base == iaddr,
            "Free address %p should align with obj_size %d\n",
            addr, obj_size);
  
  if (bmap_idx == 0)
    {
      op_assert(item_idx >= self->bitmap_headroom,
                "Free address %p cannot overlap span %p headroom\n",
                addr, self);
    }

 retry:
  if (!atomic_check_in(&self->pcard))
    goto retry;

  // TODO switch on state

 free_bm_full:
  if (!atomic_book_critical(&self->pcard))
    {
      atomic_check_out(&self->pcard);
      goto retry;
    }
  while (!atomic_enter_critical(&self->pcard))
    ;

  atomic_fetch_sub_explicit(&self->obj_cnt, 1, memory_order_relaxed);
  atomic_store_explicit(&self->state, BM_NORMAL, memory_order_relaxed);
  atomic_fetch_and_explicit(&bitmap[bmap_idx],
                            ~(1UL<<remainder),
                            memory_order_relaxed);

  // enqueue_uspan
  switch (self->magic.uspan_generic.pattern)
    {
    case TYPED_USPAN_PATTERN:
      {
        TypeAlias* ta = &heap->type_alias[self->magic.typed_uspan.type_alias];
        int tid = self->magic.typed_uspan.thread_id;
        while (1) 
          {
            if (!atomic_check_in(&ta->uspan_pcard[tid]))
              continue;            
            if (atomic_book_critical(&ta->uspan_pcard[tid]))
              break;
            atomic_check_out(&ta->uspan_pcard[tid]);
          }
        while (!enqueue_uspan(&ta->uspan[tid],
                              &ta->uspan_pcard[tid],
                              self))
          ;
        atomic_check_out(&ta->uspan_pcard[tid]);
        break;
      }
    case RAW_USPAN_PATTERN:
      {
        uint16_t size_class = self->magic.raw_uspan.obj_size / 16;
        int tid = self->magic.raw_uspan.thread_id;
        while (1)
          {
            if (!atomic_check_in(&heap->raw_type.uspan_pcard[size_class][tid]))
              continue;
            if (atomic_book_critical
                (&heap->raw_type.uspan_pcard[size_class][tid]))
              break;
            atomic_check_out(&heap->raw_type.uspan_pcard[size_class][tid]);
          }
        while (!enqueue_uspan
               (&heap->raw_type.uspan[size_class][tid],
                &heap->raw_type.uspan_pcard[size_class][tid],
                self))
          ;
        atomic_check_out(&heap->raw_type.uspan_pcard[size_class][tid]);
        break;
      }
    case LARGE_USPAN_PATTERN:
      {
        uint16_t obj_size = self->magic.large_uspan.obj_size;
        int uid =
          obj_size == 512 ? 0 :
          obj_size == 1024 ? 1 : 2;
        while (1)
          {
            if (!atomic_check_in(&heap->raw_type.large_uspan_pcard[uid]))
              continue;
            if (atomic_book_critical
                (&heap->raw_type.large_uspan_pcard[uid]))
              break;
            atomic_check_out(&heap->raw_type.large_uspan_pcard[uid]);
          }
        while (!enqueue_uspan
               (&heap->raw_type.large_uspan[uid],
                &heap->raw_type.large_uspan_pcard[uid],
                self))
          ;
        atomic_check_out(&heap->raw_type.large_uspan_pcard[uid]);
        break;
      }
    } // end of switch
  
  atomic_exit_critical(&self->pcard);
  atomic_check_out(&self->pcard);
  return BM_NORMAL;

 free_bm_normal:

    // TODO think about this order again..
  obj_cnt = atomic_fetch_sub_explicit(&self->obj_cnt, 1,
                                      memory_order_acq_rel);


  // TODO: document why we check-out then do the check-in, book loops.
  // This is how we avoid data races.
  switch (self->magic.uspan_generic.pattern)
    {
    case TYPED_USPAN_PATTERN:
      {
        TypeAlias* ta = &heap->type_alias[self->magic.typed_uspan.type_alias];
        int tid = self->magic.typed_uspan.thread_id;
        atomic_check_out(&ta->uspan_pcard[tid]);
        while (1) 
          {
            if (!atomic_check_in(&ta->uspan_pcard[tid]))
              continue;            
            if (atomic_book_critical(&ta->uspan_pcard[tid]))
              break;
            atomic_check_out(&ta->uspan_pcard[tid]);
          }
        while (!dequeue_uspan(&ta->uspan[tid],
                              &ta->uspan_pcard[tid],
                              self))
          ;
        break;
      }
    case RAW_USPAN_PATTERN:
      {
        uint16_t size_class = self->magic.raw_uspan.obj_size / 16;
        int tid = self->magic.raw_uspan.thread_id;
        atomic_check_out(&heap->raw_type.uspan_pcard[size_class][tid]);
        while (1)
          {
            if (!atomic_check_in(&heap->raw_type.uspan_pcard[size_class][tid]))
              continue;
            if (atomic_book_critical
                (&heap->raw_type.uspan_pcard[size_class][tid]))
              break;
            atomic_check_out(&heap->raw_type.uspan_pcard[size_class][tid]);
          }
        while (!dequeue_uspan
               (&heap->raw_type.uspan[size_class][tid],
                &heap->raw_type.uspan_pcard[size_class][tid],
                self))
          ;
        break;
      }
    case LARGE_USPAN_PATTERN:
      {
        uint16_t obj_size = self->magic.large_uspan.obj_size;
        int uid =
          obj_size == 512 ? 0 :
          obj_size == 1024 ? 1 : 2;
        atomic_check_out(&heap->raw_type.large_uspan_pcard[uid]);
        while (1)
          {
            if (!atomic_check_in(&heap->raw_type.large_uspan_pcard[uid]))
              continue;
            if (atomic_book_critical
                (&heap->raw_type.large_uspan_pcard[uid]))
              break;
            atomic_check_out(&heap->raw_type.large_uspan_pcard[uid]);
          }
        while (!dequeue_uspan
               (&heap->raw_type.large_uspan[uid],
                &heap->raw_type.large_uspan_pcard[uid],
                self))
          ;
        break;
      }
    } // end of switch


  

  if (obj_cnt > 1)
    {
      atomic_fetch_and_explicit(&bitmap[bmap_idx],
                                ~(1UL<<remainder),
                                memory_order_relaxed);
      atomic_check_out(&self->pcard);
      return BM_NORMAL;
    }

  // At this stage it is still possible to have alloc

  while (1)
    {
      switch(atomic_load_explicit(&self->state,
                                  memory_order_relaxed))
        {
        case BM_NORMAL:
          old_rwlock = atomic_fetch_add_explicit(&self->rwlock,
                                                 1,
                                                 memory_order_acquire);
          if (old_rwlock > 0)
            goto normal_bmap_free;
          atomic_fetch_sub_explicit(&self->rwlock,
                                    1,
                                    memory_order_relaxed);
          continue;
        case BM_FULL:
          old_rwlock = 0;
          if (atomic_compare_exchange_weak_explicit(&self->rwlock,
                                                    &old_rwlock,
                                                    INT16_MIN,
                                                    memory_order_acquire,
                                                    memory_order_relaxed))
            goto full_bmap_free;
          continue;
        default:
          op_assert("Invalid free: free on tombstone uspan %p", self);
        }
    }
 full_bmap_free:

  // the free operation should happen before the enqueue
  atomic_fetch_and_explicit(&bitmap[bmap_idx],
                            ~(1UL<<remainder),
                            memory_order_acquire);
  enqueue_uspan(self);
  // release rwlock
  atomic_store_explicit(&self->rwlock, 0, memory_order_release);

  // we transitioned from BM_FULL to BM_NORMAL
  return BM_NORMAL;
  
 normal_bmap_free:

  atomic_fetch_and_explicit(&bitmap[bmap_idx],
                            ~(1UL<<remainder),
                            memory_order_relaxed);


  
  if (self->bitmap_cnt == 1 &&
      atomic_load_explicit(bitmap, memory_order_relaxed) ==
      ((1UL << self->bitmap_headroom)-1) |
      ~((1UL << (64-self->bitmap_padding))-1))
    {
      goto try_bury;
    }
  else if (bmap_idx == 0 &&
           atomic_load_explicit(bitmap, memory_order_relaxed)==
           (1UL << self->bitmap_headroom)-1)
    {
      goto try_bury;
    }
  else if (bmap_idx == self->bitmap_cnt - 1)
    {
      if (atomic_load_explicit(&bitmap[bmap_idx], memory_order_relaxed) ==
          (self->bitmap_padding ?
           ~((1UL << (64 - self->bitmap_padding))-1) :
           0UL))
        goto try_bury;
    }
  else if (!atomic_load_explicit(&bitmap[bmap_idx], memory_order_relaxed))
    {
      goto try_bury;
    }
  else
    {
      rel_rlock(&self->rwlock);
      return BM_NORMAL;
    }

  // We should use counter instead of iterating all the bitmaps
 try_bury:
  atomic_fetch_sub_explicit(&self->rwlock, 1, memory_order_acquire);
  atomic_fetch_add_explicit(&self->del_attempt, 1, memory_order_acquire);
  do 
    {
      if (atomic_load_explicit(&self->state, memory_order_relaxed)
          == BM_TOMBSTONE)
        {
          atomic_fetch_sub_explicit(&self->del_attempt,
                                    1,
                                    memory_order_release);
          return BM_NORMAL;
        }
      expected_rwlock = 0;
    }
  while (!atomic_compare_exchange_weak_explicit
         (&self->rwlock, &expected_rwlock, INT16_MIN,
          memory_order_acq_rel,
          memory_order_relaxed));

  if (self->bitmap_cnt == 1 &&
      atomic_load_explicit(bitmap, memory_order_relaxed)
      == ((1UL << self->bitmap_headroom)-1) |
      ~((1UL << (64-self->bitmap_padding))-1))
    {
      atomic_store_explicit(&self->state, BM_TOMBSTONE,
                            memory_order_release);
      while (atomic_load_explicit(&self->del_attempt,
                                  memory_order_release) > 1)
        ;
      dequeue_uspan(self);
      atomic_store_explicit(&self->rwlock, 0,
                            memory_order_release);
      return BM_TOMESTONE;
    }

  // headroom
  if (!atomic_load_explicit(&bitmap[0], memory_order_relaxed))
    {
      atomic_fetch_sub_explicit(&self->del_attempt,
                                1,
                                memory_order_relaxed);
      atomic_store_explicit(&self->rwlock, 0,
                            memory_order_release);
      return BM_NORMAL;
    }

  // body
  for (int i = 1; i < self->bitmap_cnt-1; i++)
    {
      if (atomic_load_explicit(&bitmap[iter],
                               memory_order_relaxed)
          != 0UL)
        {
          atomic_fetch_sub_explicit(&self->del_attempt,
                                    1,
                                    memory_order_relaxed);
          atomic_store_explicit(&self->rwlock, 0,
                                memory_order_release);
          return BM_NORMAL;
        }
    }

  // padding
  if (atomic_load_explicit(&bitmap[self->bitmap_cnt-1],
                           memory_order_relaxed) !=
      (self->bitmap_padding ?
       ~((1UL << (64 - self->bitmap_padding))-1) :
       0UL))
    {
      atomic_fetch_sub_explicit(&self->del_attempt,
                                1,
                                memory_order_relaxed);
      atomic_store_explicit(&self->rwlock, 0,
                            memory_order_release);
      return BM_NORMAL;
    }
  
  atomic_store_explicit(&self->state, BM_TOMBSTONE,
                        memory_order_release);
  while (atomic_load_explicit(&self->del_attempt,
                              memory_order_release) > 1)
    ;
  dequeue_uspan(self);
  atomic_store_explicit(&self->rwlock, 0,
                        memory_order_release);
  return BM_TOMESTONE;
}


FreeStatus USpanFreeOld(UnarySpan* self, void* addr)
{
  int obj_size = self->magic.typed_uspan.obj_size;
  void* const base = (void*)self;
  void* const bound = base +
    obj_size*(64*self->bitmap_cnt - self->bitmap_padding);

  op_assert(addr > base && addr < bound,
            "Free address %p should within span from %p and %p",
            addr, base, bound);
  
  ptrdiff_t diff = (addr - base) / obj_size;
  _Atomic uint64_t *bitmap = (_Atomic uint64_t *)(self+1);
  const int bmap_idx = diff >> 6;
  const int remainder = diff - (bmap_idx << 6);

  op_assert(diff * obj_size + base == addr,
            "Free address %p should align with obj_size %d\n",
            addr, obj_size);
  if (bmap_idx == 0)
    op_assert(remainder >= self->bitmap_headroom,
              "Free address %p cannot overlap span %p headroom\n",
              addr, self);

  // A very special condition: While we're in try_full_free mode, if
  // someone tries to free element that is marked occupied, which were
  // marked by try_full_free, it's really hard to detect such invalid
  // free. In the context of full free it's not an issue, but if we
  // used it as conjunction with alloc, we get into an ABA problem.
  // The alloc will fill in the double free address, but the full_free
  // may still satisfy and free the span.  We need some way to prevent
  // people from doing stupid things, or at least make the problem
  // easy to diagnose.
  //
  // A possible solution is to use the LSB of headroom to indicate
  // we're in full_free mode, guard with memory_order_release, and
  // have alloc to acquire a spin lock on that bit.  For invalid
  // double-free, we might just ignore it so we can squeez out a bit
  // more performance.
  
  uint64_t old_bmap = atomic_fetch_and_explicit(&bitmap[bmap_idx],
                                                ~(1UL<<remainder),
                                                memory_order_relaxed);

  if (self->bitmap_cnt == 1)
    {
      uint64_t expected_empty_bmap =
        ((1UL << self->bitmap_headroom)-1) |
        ~((1UL << (64-self->bitmap_padding))-1);
      if (atomic_compare_exchange_strong_explicit
          (bitmap, &expected_empty_bmap, ~0UL,
           memory_order_release,
           memory_order_relaxed))
      return FREE_REACHED_EMPTY;
    }
  else if (old_bmap == ~0UL)
    {
      return FREE_FROM_FULL;
    }
  else if (bmap_idx == 0 &&
           atomic_load_explicit(bitmap, memory_order_relaxed)==
           (1UL << self->bitmap_headroom)-1)
    {
      goto try_fullfree;
    }
  else if (bmap_idx == self->bitmap_cnt - 1)
    {
      if (atomic_load_explicit(&bitmap[bmap_idx], memory_order_relaxed) ==
          (self->bitmap_padding ?
           ~((1UL << (64 - self->bitmap_padding))-1) :
           0UL))
        goto try_fullfree;
    }
  else if (!atomic_load_explicit(&bitmap[bmap_idx], memory_order_relaxed))
    {
      goto try_fullfree;
    }
  else
    return FREE_NORMAL;

  int iter;
  uint64_t expected_headroom, expected_body, expected_padding;
  
 try_fullfree:
  
  iter = 0;
  expected_headroom = (1UL << self->bitmap_headroom)-1;
  expected_body = 0UL;
  expected_padding = self->bitmap_padding ?
    ~((1UL << (64 - self->bitmap_padding))-1) : 0UL;

  // headroom
  if (!atomic_compare_exchange_strong_explicit
      (&bitmap[0], &expected_headroom, ~0UL,
       memory_order_release,
       memory_order_relaxed))
    return FREE_NORMAL;

  // body
  for (iter = 1; iter < self->bitmap_cnt - 1; iter++)
    {
      expected_body = 0UL;
    if (!atomic_compare_exchange_strong_explicit
        (&bitmap[iter], &expected_body, ~0UL,
         memory_order_release,
         memory_order_relaxed))
      goto catch_nonempty_exception;
    }

  // padding
  if (atomic_compare_exchange_strong_explicit
      (&bitmap[iter], &expected_padding, ~0UL,
       memory_order_release,
       memory_order_relaxed))
    return FREE_REACHED_EMPTY;

 catch_nonempty_exception:

  // headroom
  expected_headroom = (1UL << self->bitmap_headroom)-1;
  atomic_store_explicit(&bitmap[0], expected_headroom, memory_order_relaxed);

  // body
  for (int i = 1; i < iter; i++)
    {
      atomic_store_explicit(&bitmap[i], 0UL, memory_order_release);
    }
  
  return FREE_NORMAL;
}


/* op_pspan.c ends here */
