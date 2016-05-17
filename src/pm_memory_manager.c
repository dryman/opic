#include <stddef.h>
#include "pm_memory_manager.h"

typedef struct PMPool PMPool;
typedef struct PMSlot PMSlot;
typedef struct PMLPMap PMLPMap; // LP states for Linear Probing
typedef struct PMLPMapData PMLPMapData;

struct PMMemoryManager {
  PMLPMap* type_map;
  PMAVLNode* pointer_map;
};

struct PMPool {
  Class* klass;
  PMSlot* slot;
};

struct PMSlot {
  PMPool* pool;
  size_t size;
  void* data;
  void* data_next_free;
  void* data_bound;
  void** pqueue;
  void** pqueue_next_free;
  PMSlot* next;
};

struct PMAVLNode {
  unsigned int height;
  void* ptr_low;
  void* ptr_high; // close-open interval
  PMSlot* slot;
  PMAVLNode* left;
  PMAVLNode* right;
};

struct PMLPMap {
  size_t size;
  PMLPMapData* data;
};

struct PMLPMapData {
  Class* key;
  PMPool* pool;
};

static int PMSlot_new(PMSlot** self, PMPool* pool, PMAVLNode** pointer_map, size_t size);
static void* PMSlot_alloc_obj(PMSlot* self);
static void PMSlot_free_obj(PMSlot* self, void* obj);
static inline void PMSlot_pqueue_heapify(PMSlot* self);
static inline void PMAVLRotateLeft(PMAVLNode** node);
static inline void PMAVLRotateRight(PMAVLNode** node);
static inline unsigned int PMAVLGetHeight(PMAVLNode* node);
static unsigned int PMAVLInsert(PMAVLNode** node, void* ptr_low, void* ptr_high, PMSlot* slot);
static PMSlot* PMAVLFind(PMAVLNode* node, void* ptr);
static void PMAVL_destroy(PMAVLNode* node);
static int PMLPMap_new(PMLPMap** self, size_t size);
static void PMLPMap_destroy(PMLPMap* self);
static PMPool* PMLPMap_get(PMLPMap* self, Class* key);
static void PMLPMap_put(PMLPMap* self, Class* key, PMPool* value);

static inline unsigned int pointer_hash(void*);

int PMMemoryManager_new(PMMemoryManager** self)
{
  if (!(*self = calloc(sizeof(PMMemoryManager),1))) return -1;
  if (PMLPMap_new(&(*self)->type_map, 128)) return -1;
  return 0;
}

void PMMemoryManager_destroy(PMMemoryManager* self)
{
  PMLPMap_destroy(self->type_map);
  PMAVL_destroy(self->pointer_map);
}

void* PMAlloc(PMMemoryManager* ctx, Class* klass)
{
  PMPool* pool = PMLPMap_get(ctx->type_map, klass);
  if (!pool) {
    pool = calloc(sizeof(PMPool), 1);
    pool->klass = klass;
    PMSlot_new(&pool->slot, pool, &ctx->pointer_map, 2048);
    PMLPMap_put(ctx->type_map, klass, pool);
  }
  PMSlot* slot = pool->slot, *prev_slot;
  while(slot) {
    void* obj = PMSlot_alloc_obj(slot);
    if (obj) return obj;
    prev_slot = slot;
    slot = slot->next;
  }
  PMSlot_new(&prev_slot->next, pool, &ctx->pointer_map, prev_slot->size*2);
  slot = prev_slot->next;
  return PMSlot_alloc_obj(slot);
}
    
void* PMFree(PMMemoryManager* ctx, void* obj)
{
  tc_assert(!(*(char*)obj), "object %p is already freed\n", obj);
  PMSlot* slot = PMAVLFind(ctx->pointer_map, obj);
  PMSlot_free_obj(slot, obj);
  /* TODO if slot is empty, free the slot */
}

int PMSlot_new(PMSlot** self, PMPool* pool, PMAVLNode** pointer_map, size_t size)
{
  if(!(*self=calloc(sizeof(PMSlot), 1))) return -1;
  (*self)->pool = pool;
  (*self)->size = size;
  (*self)->data = calloc(sizeof(pool->klass->size), size);
  (*self)->data_next_free = (*self)->data;
  (*self)->data_bound = (*self)->data + pool->klass->size * size;
  (*self)->pqueue = calloc(sizeof(void*), size);
  (*self)->pqueue_next_free = (*self)->pqueue;
  PMAVLInsert(pointer_map, (*self)->data, (*self)->data_bound, *self);
  return 0;
}

void PMSlot_destroy(PMSlot* self)
{
  if (self->next) PMSlot_destroy(self->next);
  free(self->data);
  free(self->pqueue);
  free(self);
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


unsigned int PMAVLInsert(PMAVLNode** node, void* ptr_low, void* ptr_high, PMSlot* slot)
{
  if (*node == NULL) {
    *node = calloc(sizeof(PMAVLNode),1);
    (*node)->ptr_low = ptr_low;
    (*node)->ptr_high = ptr_high;
    (*node)->slot = slot;
    (*node)->height = 1;
    return (*node)->height;
  }
  tc_assert(ptr_low != (*node)->ptr_low, "should not see address collision\n");
  if (ptr_low < (*node)->ptr_low) {
    unsigned int h = PMAVLInsert(&(*node)->left, ptr_low, ptr_high, slot);
    if (!(*node)->right && h > 1) {
      PMAVLRotateRight(node);
    } else if ((*node)->right) {
      PMAVLNode* right = (*node)->right;
      if (h > right->height+1) PMAVLRotateRight(node);
    }
  } else {
    unsigned int h = PMAVLInsert(&(*node)->right, ptr_low, ptr_high, slot);
    if (!(*node)->left && h > 1) {
      PMAVLRotateLeft(node);
    } else if ((*node)->left) {
      PMAVLNode* left = (*node)->right;
      if (h > left->height+1) PMAVLRotateLeft(node);
    }
  }
  (*node)->height = PMAVLGetHeight(*node);
  return (*node)->height;
}

PMSlot* PMAVLFind(PMAVLNode* node, void* ptr)
{
  tc_assert(node, "NULL PMAVLNode\n");
  if (ptr < node->ptr_low)
    return PMAVLFind(node->left, ptr);
  if (ptr < node->ptr_high)
    return node->slot;
  return PMAVLFind(node->right, ptr);
}

void PMAVL_destroy(PMAVLNode* node)
{
  if (!node) return;
  PMAVL_destroy(node->left);
  PMAVL_destroy(node->right);
  free(node);
}

void PMAVLRotateLeft(PMAVLNode** node)
{
  PMAVLNode* p = *node, *r = (*node)->right;
  p->right = r->left;
  r->left = p;
  p->height = PMAVLGetHeight(p);
  r->height = PMAVLGetHeight(r);
  *node = r;
}

void PMAVLRotateRight(PMAVLNode** node)
{
  PMAVLNode* p = *node, *l = (*node)->left;
  p->left = l->right;
  l->left = p;
  p->height = PMAVLGetHeight(p);
  l->height = PMAVLGetHeight(l);
  *node = l;
}

unsigned int PMAVLGetHeight(PMAVLNode* node)
{
  unsigned int left_h, right_h;
  left_h = node->left ? node->left->height : 0;
  right_h = node->right ? node->right->height : 0;
  return left_h > right_h ? left_h : right_h;
}

int PMLPMap_new(PMLPMap** self, size_t size)
{
  if (!(*self = calloc(sizeof(PMLPMap),1))) return -1;
  (*self)->size = size << 2;
  (*self)->data = calloc(sizeof(PMLPMapData), (*self)->size);
  return 0;
}

void PMLPMap_destroy(PMLPMap* self)
{
  for (int i = 0; i < self->size; i++) {
    if (self->data[i].key)
      PMSlot_destroy(self->data[i].pool->slot);
  }
  free(self->data);
  free(self);
}

PMPool* PMLPMap_get(PMLPMap* self, Class* key)
{
  unsigned int hash = pointer_hash(key);
  for (unsigned int i = hash % self->size; i < self->size; i++) {
    if (!self->data[i].key) return NULL;
    if (self->data[i].key == key) {
      return self->data[i].pool;
    }
  }
  return NULL;
}

void PMLPMap_put(PMLPMap* self, Class* key, PMPool* pool)
{
  unsigned int hash = pointer_hash(key);
  for (unsigned int i = hash % self->size; i < self->size; i++) {
    if (!self->data[i].key) {
      self->data[i].pool = pool;
      return;
    }
    tc_assert(self->data[i].key != key, "key collision in PMLPMap\n");
  }
  size_t old_size = self->size;
  PMLPMapData* old_data = self->data;

  self->size = self->size << 1;
  self->data = calloc(sizeof(PMLPMapData), self->size);
  for (unsigned int i = 0; i < old_size; i++) {
    if (!old_data[i].key) {
      PMLPMap_put(self, old_data[i].key, old_data[i].pool);
    }
  }
  PMLPMap_put(self, key, pool);
}

unsigned int pointer_hash(void* ptr)
{
  // copied from murmur hash 3.. 
  // not sure if I want these arithmetics
  uint64_t k = (uint64_t) ptr;
  k ^= k >> 33;
  k *= 0xff51afd7ed558ccd;
  k ^= k >> 33;
  k *= 0xc4ceb9fe1a85ec53;
  k ^= k >> 33;
  return (unsigned int) k;
}

