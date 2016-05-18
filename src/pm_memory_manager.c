#include <stdio.h>
#include <limits.h>
#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>
#include <string.h>
#include "pm_memory_manager.h"
#include "tc_serializable.h"

typedef struct PMPool PMPool;
typedef struct PMSlot PMSlot;
typedef struct PMLPMap PMLPMap; // LP states for Linear Probing
typedef struct PMLPMapData PMLPMapData;

struct PMMemoryManager {
  PMLPMap* type_map;
  PMAVLNode* pointer_map;
  Class** klasses;
  uint8_t klass_num;
};

struct PMPool {
  Class* klass;
  PMSlot* slot;
};

struct PMSlot {
  PMPool* pool;
  size_t size;
  size_t offset; // only used in serialization
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
static void PMSlotExportOffset(PMSlot* self, size_t offset);

static inline unsigned int pointer_hash(void*);

static int ptr_cmp (const void* a, const void* b)
{
  if (*(void**)a < *(void**)b) return -1;
  if (*(void**)a == *(void**)b) return 0;
  return 1;
}

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
  tc_assert((*(Class**)obj), "object %p is already freed\n", obj);
  PMSlot* slot = PMAVLFind(ctx->pointer_map, obj);
  PMSlot_free_obj(slot, obj);
  /* TODO if slot is empty, free the slot */
}


int PMSerialize(PMMemoryManager* ctx, FILE* fd, uint32_t n, ...)
{
  void* inbounds[n];
  size_t inbounds_id[n];
  va_list args;
  va_start(args, n);
  for(uint32_t i = 0; i < n; i++)
    {
      inbounds[i] = va_arg(args, void*);
    }
  va_end(args);

  int klass_num = 0;
  for (int i = 0; i < ctx->type_map->size; i++)
    {
      Class* k = ctx->type_map->data[i].key;
      if (k)
        {
          tc_assert(tc_isa_instance_of(k, "TCSerializable"),
            "Class %p %s is not Serializable\n", k, k->classname
          );
          klass_num++;
        }
    }
  tc_assert(klass_num <= UINT8_MAX);
  ctx->klass_num = (uint8_t) klass_num;
  ctx->klasses = malloc(sizeof(Class*)*klass_num);
    // TODO assert types not larger than 255

  int klass_idx = 0;
  for (int i = 0; i < ctx->type_map->size; i++)
    {
      if (ctx->type_map->data[i].key)
        ctx->klasses[klass_idx++] = ctx->type_map->data[i].key;
    }
  qsort(ctx->klasses, ctx->klass_num, sizeof(Class*), ptr_cmp);

  /* 1. number of classes we have */
  fwrite(&ctx->klass_num, sizeof(uint8_t), 1, fd);

  /* 2. Preprocess offset so that PMGetSerializeId can 
   *    work properly */
  for (uint8_t i = 0; i < klass_num; i++)
    {
      PMPool* pool = PMLPMap_get(ctx->type_map, ctx->klasses[i]);
      const size_t obj_size = pool->klass->size;
      size_t offset = 0;
      PMSlot* slot = pool->slot;
      while(slot)
        {
          slot->offset = offset;
          offset += (slot->data_next_free - slot->data) / obj_size;
          slot = slot->next;
        }
    }

  /* 3. each klass we serialize:
   * 3.1 class name
   * 3.2 packed data len
   * 3.3 packed data
   * pqueue data can be restored from null values in the data array
   */
  for (uint8_t i = 0; i < klass_num; i++)
    {
      // 3.1 class name
      PMPool* pool;
      PMSlot* slot;
      pool = PMLPMap_get(ctx->type_map, ctx->klasses[i]);
      size_t classname_len = strlen(pool->klass->classname);
      fwrite(&classname_len, sizeof(size_t), 1, fd);
      fwrite(pool->klass->classname, 1, classname_len, fd);
  
      // 3.2 packed data len
      const size_t obj_size = pool->klass->size;
      slot = pool->slot;
      while(slot->next) 
        slot = slot->next;
      size_t total_cnt = slot->offset + 
        (slot->data_next_free - slot->data) / obj_size;
      size_t total_size = total_cnt * obj_size;
      fwrite(&total_size, sizeof(size_t), 1, fd);
  
      // 3.3 packed data
      void* write_buf = malloc(total_size);
      void* write_buf_next_free = write_buf;
      slot = pool->slot;
      while (slot)
        {
          size_t copy_size = slot->data_next_free - slot->data;
          memcpy(write_buf_next_free, slot->data, copy_size);
          write_buf_next_free += copy_size;
          slot = slot->next;
        }
      size_t write_buf_len = write_buf_next_free - write_buf;
      tc_assert(write_buf_len  == total_size,
        "Write buffer size mismatch. write buffer len: %zu,"
        " slot total len: %zu\n",
        write_buf_len, total_size);
      for (void* p = write_buf; p < write_buf_next_free; 
           p += obj_size)
        {
          if (*(Class**)p)
            {
              serde_serialize(p, ctx);
              memset(p, -1, sizeof(Class*));
            }
        }
      fwrite(write_buf, 1, total_size, fd);
      free(write_buf);
    }

  /*
   * serialize inbounds
   * 4.1 serialize # of inbounds
   * 4.2 convert ptr to id and serialize
   */
  for(uint32_t i = 0; i < n; i++)
    {
      inbounds_id[i] = PMGetSerializeId(ctx, inbounds[i]);
    }
  fwrite(&n, sizeof(uint32_t), 1, fd);
  fwrite(inbounds_id, sizeof(size_t), n, fd);

  free(ctx->klasses);
}

PMMemoryManager* PMDeserialize(FILE* fd, ...)
{

}

size_t PMGetSerializeId(PMMemoryManager* ctx, void* ptr)
{
  PMSlot* slot = PMAVLFind(ctx->pointer_map, ptr);
  Class* klass = slot->pool->klass;
  Class** klasses = ctx->klasses;
  uint8_t low=0, high = ctx->klass_num-1, type_id;
  size_t offset, ptr_id;
  while(low <= high)
    {
      type_id = (high-low)/2 + low;
      if (klasses[type_id] < klass)
        low = type_id+1;
      else if (klasses[type_id] > klass)
        high = type_id-1;
      else
        goto type_id_found;
    }
  tc_assert(0, "Counld not find type id for klass: %p %s\n", 
            klass, klass->classname);
type_id_found:
  offset = (ptr - slot->data)/klass->size;
  ptr_id = (((size_t)type_id) << (sizeof(size_t)-1)*CHAR_BIT) | offset;
  return ptr_id;
}

/* Start of internal functions */

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
    printf("alloc from pqueue, with slot: %p\n", self);
    obj = *self->pqueue;
    self->pqueue_next_free--;
    *self->pqueue = *self->pqueue_next_free;
    PMSlot_pqueue_heapify(self);
  } else if(self->data_next_free < self->data_bound) {
    printf("alloc from data chunk, with slot: %p\n", self);
    obj = self->data_next_free;
    printf("data_next_free: %p, size: %d\n", self->data_next_free, obj_size);
    self->data_next_free += obj_size;
    printf("data_next_free: %p, size: %d\n", self->data_next_free, obj_size);
  } else {
    return NULL;
  }
  return obj;
}

void PMSlot_free_obj(PMSlot* self, void* obj)
{
  printf("freeobj %p with slot %p\n", obj, self);
  const size_t obj_size = self->pool->klass->size;
  memset(obj, 0, obj_size);
  printf("data_next_free: %p, obj: %p, obj next: %p\n", self->data_next_free, obj, obj+obj_size);
  if (self->data_next_free == obj + obj_size) {
    printf("recycle to data chunk\n");
    self->data_next_free -= obj_size;
    return;
  }
  printf("recycle to heap\n");
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
      self->data[i].key = key;
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

