#include <stddef.h>
#include "pm_pool.h"

static int PMSlot_new(PMSlot** self, PMPool* pool, PMLinearProbingMap* pointer_map, size_t size);
static inline void PMSlot_pqueue_heapify(PMSlot* self);

static unsigned int pointer_hash(void*);
static bool pointer_equal(void*, void*);

int PMMemoryManager_new(PMMemoryManager**)
{
  if (!(*self = calloc(sizeof(PMMemoryManager),1))) return -1;
  if (PMLinearProbingMap_new(&self->type_map
    pointer_hash, pointer_equal, 128)) return -1;
  if (PMLinearProbingMap_new(&self->pointer_map
    pointer_hash, pointer_equal, 1024)) return -1;
  return 0;
}

void PMMemoryManager_destroy(PMMemoryManager*)
{
  // oh no... values would have memory leak...
  // ah.. still won't work.. need to pass in deconstructor..
  PMLinearProbingMap_destroy(self->type_map, false, true);
  PMLinearProbingMap_destroy(self->pointer_map, false, false);
}

void* PMAlloc(PMMemoryManager* ctx, Class* klass)
{
  PMPool* pool = map_get(ctx->type_map);
  if (!pool) {
    pool = calloc(sizeof(PMPool), 1);
    pool->klass = klass;
    PMSlot_new(&pool->slot, pool, self->pointer_map, 2048);
    map_put(self->type_map, klass, pool);
  }
  PMSlot* slot = pool->slot, *prev_slot;
  while(slot) {
    void* obj = PMSlot_alloc_obj(slot);
    if (obj) return obj;
    prev_slot = slot;
    slot = slot->next;
  }
  PMSlot_new(&prev_slot->next, pool, self->pointer_map, prev_slot->size*2);
  slot = prev_slot->next;
  return PMSlot_alloc_obj(slot);
}
    
void* PMFree(PMMemoryManager* ctx, void* obj)
{
  tc_assert(!(*(char*)obj), "object %p is already freed\n", obj);
  PMSlot* slot = rmap_get(ctx->pointer_map, obj);
  tc_assert(slot, "object %p does not belong to PMMemoryManager %p\n", obj, ctx);
  PMSlot_free_obj(slot, obj);
  /* TODO if slot is empty, free the slot */
}

int PMSlot_new(PMSlot** self, PMPool* pool, PMLinearProbingMap* pointer_map, size_t size)
{
  if(!(*self=calloc(sizeof(PMSlot), 1))) return -1;
  self->pool = pool;
  self->size = size;
  self->data = calloc(sizeof(pool->klass->size), size);
  self->data_next_free = self->data;
  self->data_bound = self->data + pool->klass->size * size;
  self->pqueue = calloc(sizeof(void*), size);
  self->pqueue_next_free = self->pqueue;
  return 0;
}

void* PMSlot_alloc_obj(PMSlot* self)
{
  void* obj;
  const size_t obj_size = self->pool->klass->size;
  if (self->pqueue != self->pqueue_next_free) {
    obj = *self->pqueue;
    self->pqueue_next_free--;
    *self->pqueue = *self->pqueue_next_free;
    PMSlot_pqueue_heapify(self);
  } else if(self->data_next_free < self->data_bound) {
    obj = self->data_next_free;
    self->data_next_free += obj_size;
  } else {
    return NULL;
  }
  return obj;
}

void PMSlot_free_obj(PMSlot* self, void* obj)
{
  const size_t obj_size = self->pool->klass->size;
  memset(obj, 0, obj_size);
  if (self->data_next_free == obj + obj_size) {
    self->data_next_free -= obj_size;
    return;
  }
  *self->pqueue_next_free = obj;
  self->pqueue_next_free++;
  PMSlot_pqueue_heapify(self);
}

static inline void PMSlot_pqueue_heapify(PMSlot* self)
{
  if (self->pqueue == self->pqueue_next_free) return;
  for (ptrdiff_t i = (self->pqueue_next_free - self->pqueue)-1;
       !i; i/=2) {
    void* node   = self->pqueue[i];
    void* parent = self->pqueue[i/2];
    if(node < parent) {
      self->pqueue[i]   = parent;
      self->pqueue[i/2] = node;
    } else {
      break;
    }
  }
}

static unsigned int pointer_hash(void* ptr)
{
  // copied from murmur hash 3
  uint64_t k = (uint64_t) ptr;
  k ^= k >> 33;
  k *= 0xff51afd7ed558ccd;
  k ^= k >> 33;
  k *= 0xc4ceb9fe1a85ec53;
  k ^= k >> 33;
  return (unsigned int) k;
}

static bool pointer_equal(void* a, void* b)
{
  return a == b;
}
