#include <stdio.h>
#include <limits.h>
#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>
#include <string.h>
#include "pm_memory_manager.h"
#include "op_serializable.h"
#include "../common/op_log.h"


typedef struct PMLPMap PMLPMap; // LP states for Linear Probing
typedef struct PMLPMapData PMLPMapData;

struct PMMemoryManager {
  PMLPMap* type_map;
  PRMObj* pointer_map;
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

struct PMLPMap {
  size_t size;
  PMLPMapData* data;
};

struct PMLPMapData {
  Class* key;
  PMPool* pool;
};

static int PMSlot_new(PMSlot** self, PMPool* pool, PRMObj* pointer_map, size_t size);
static void* PMSlot_alloc_obj(PMSlot* self);
static void PMSlot_free_obj(PMSlot* self, void* obj);
static inline void PMSlot_pqueue_heapify(PMSlot* self);
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
  if (PRMCreate(&(*self)->pointer_map))
    {
      free(*self);
      return -1;
    }
  if (PMLPMap_new(&(*self)->type_map, 128)) 
    {
      PRMDestroy((*self)->pointer_map);
      free(*self);
      return -1;
    }
  return 0;
}

void PMMemoryManager_destroy(PMMemoryManager* self)
{
  PMLPMap_destroy(self->type_map);
  PRMDestroy(self->pointer_map);
}

void* PMAlloc(PMMemoryManager* ctx, Class* klass)
{
  PMPool* pool = PMLPMap_get(ctx->type_map, klass);
  if (!pool) {
    pool = calloc(sizeof(PMPool), 1);
    pool->klass = klass;
    PMSlot_new(&pool->slot, pool, ctx->pointer_map, 2048);
    PMLPMap_put(ctx->type_map, klass, pool);
  }
  PMSlot* slot = pool->slot, *prev_slot;
  while(slot) {
    void* obj = PMSlot_alloc_obj(slot);
    if (obj) return obj;
    prev_slot = slot;
    slot = slot->next;
  }
  PMSlot_new(&prev_slot->next, pool, ctx->pointer_map, prev_slot->size*2);
  slot = prev_slot->next;
  return PMSlot_alloc_obj(slot);
}
    
void* PMFree(PMMemoryManager* ctx, void* obj)
{
  op_assert((*(Class**)obj), "object %p is already freed\n", obj);
  PMSlot* slot = PRMFind(ctx->pointer_map, obj);
  PMSlot_free_obj(slot, obj);
  /* TODO if slot is empty, free the slot */
}


int PMSerialize(PMMemoryManager* ctx, FILE* fd, uint32_t n, ...)
{
  void* inbounds[n];
  void* inbounds_id[n];
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
          op_assert(tc_isa_instance_of(k, "OPSerializable"),
            "Class %p %s is not Serializable\n", k, k->classname
          );
          klass_num++;
        }
    }
  op_assert(klass_num <= UINT8_MAX,
    "Number of available classes exceeds 256\n");
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
      op_assert(write_buf_len  == total_size,
        "Write buffer size mismatch. write buffer len: %zu,"
        " slot total len: %zu\n",
        write_buf_len, total_size);
      for (void* p = write_buf; p < write_buf_next_free; 
           p += obj_size)
        {
          if (*(Class**)p)
            {
              serde_serialize(p, ctx);
              memset(p, -1, sizeof(Class*)-1);
              // last byte preserved for metadata
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
      inbounds_id[i] = PMSerializePtr2Ref(inbounds[i], ctx);
    }
  fwrite(&n, sizeof(uint32_t), 1, fd);
  fwrite(inbounds_id, sizeof(void*), n, fd);
  fflush(fd);

  free(ctx->klasses);
}

OP_LOGGER_FACTORY(de_logger, "opic.pm_memory_manager.PMDeserialize")

PMMemoryManager* PMDeserialize(FILE* fd, ...)
{
  PMMemoryManager* ctx;
  if (PMMemoryManager_new(&ctx)) return NULL;

  fread(&ctx->klass_num, 1, 1, fd);
  ctx->klasses = malloc(sizeof(Class*) * ctx->klass_num);

  for (uint8_t i = 0; i < ctx->klass_num; i++)
    {
      size_t classname_len;
      size_t total_size, total_cnt;
      size_t obj_size;
      char* classname;
      fread(&classname_len, sizeof(size_t), 1, fd);
      classname = malloc(classname_len + 1);
      fread(classname, 1, classname_len, fd);
      classname[classname_len] = '\0';
      fread(&total_size, sizeof(size_t), 1, fd);
      log4c_category_log(de_logger, LOG4C_PRIORITY_INFO,
        "Deserializing class: %s", classname);
      free(classname);

      Class* klass = LPTypeMap_get(classname);
      log4c_category_log(de_logger, LOG4C_PRIORITY_INFO,
        "Deserializing, found matching klass addr: %p, %s",
        klass, klass->classname);
      ctx->klasses[i] = klass;
      obj_size = klass->size;
      total_cnt = total_size / obj_size;
      PMPool* pool = calloc(sizeof(PMPool), 1);
      pool->klass = klass;
      PMSlot_new(&pool->slot, pool, ctx->pointer_map, total_cnt);

      PMSlot* slot = pool->slot;
      fread(slot->data, 1, total_size, fd);
      slot->data_next_free = slot->data + total_size;
      for (void* p = slot->data;
           p < slot->data_next_free;
           p += obj_size)
        {
          if (*(Class**)p)
            {
              *(Class**)p = klass;
              OPObject* obj = (OPObject*) p;
#ifndef NDEBUG
              log4c_category_log(de_logger, LOG4C_PRIORITY_DEBUG, 
                "obj->isa: %p", obj->isa);
#endif
            }
          else
            {
              PMSlot_free_obj(slot, p);
            }
        }
      PMLPMap_put(ctx->type_map, klass, pool);
    }

  // now restore the pointers
  for (uint8_t i = 0; i < ctx->klass_num; i++)
    {
      PMSlot* slot = PMLPMap_get(ctx->type_map, ctx->klasses[i])->slot;
      const size_t obj_size = slot->pool->klass->size;
      for (void* p = slot->data;
           p < slot->data_next_free;
           p += obj_size)
        {
          if (*(Class**)p)
            {
              // printf("deserailize %p\n", p);
              OPObject* obj = (OPObject*)p;
              // printf("class addr: %p, classname: %s\n", obj->isa, obj->isa->classname);
              serde_deserialize(p, ctx);
            }
        }
    }

  // finally the inbounds
  uint32_t inbounds_len;
  fread(&inbounds_len, sizeof(uint32_t), 1, fd);
  void* inbounds[inbounds_len];
  fread(inbounds, sizeof(void*), inbounds_len, fd);
  va_list args;
  va_start(args, fd);
  void** ptr;
  for (uint32_t i = 0; i < inbounds_len; i++)
    {
      ptr = va_arg(args, void**);
      *ptr = PMDeserializeRef2Ptr(inbounds[i], ctx);
    }
  va_end(args);
  free(ctx->klasses);
  return ctx;
}

void* PMSerializePtr2Ref (void* ptr, PMMemoryManager* ctx)
{
  PMSlot* slot = PRMFind(ctx->pointer_map, ptr);
  Class* klass = slot->pool->klass;
  Class** klasses = ctx->klasses;
  uint8_t low=0, high = ctx->klass_num-1, type_id;
  size_t offset, ref;
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
  op_assert(0, "Counld not find type id for klass: %p %s\n", 
            klass, klass->classname);
type_id_found:
  offset = ptr - slot->data;
  ref = (((size_t)type_id) << (sizeof(size_t)-1)*CHAR_BIT) | offset;
  return (void*)ref;
}

void* PMDeserializeRef2Ptr(void* ref, PMMemoryManager* ctx)
{
  int shift = (sizeof(size_t)-1) * CHAR_BIT;
  int klass_idx = ((size_t)ref & (0xffL << shift)) >> shift;
  Class* klass = ctx->klasses[klass_idx];
  size_t offset = (size_t)ref & ~(0xffL << shift);
  PMPool* pool = PMLPMap_get(ctx->type_map, klass);
  PMSlot* slot = pool->slot;
  return slot->data + offset;
}

/* Start of internal functions */

int PMSlot_new(PMSlot** self, PMPool* pool, PRMObj* pointer_map, size_t size)
{
  if(!(*self=calloc(sizeof(PMSlot), 1))) return -1;
  (*self)->pool = pool;
  (*self)->size = size;
  (*self)->data = calloc(pool->klass->size, size);
  (*self)->data_next_free = (*self)->data;
  (*self)->data_bound = (*self)->data + pool->klass->size * size;
  (*self)->pqueue = calloc(sizeof(void*), size);
  (*self)->pqueue_next_free = (*self)->pqueue;
  PRMInsert(pointer_map, (*self)->data, (*self)->data_bound, *self);
  return 0;
}

void PMSlot_destroy(PMSlot* self)
{
  if (self->next) PMSlot_destroy(self->next);
  // TODO should pass PRMObj in and delete ptr ranges
  free(self->data);
  free(self->pqueue);
  free(self);
}

OP_LOGGER_FACTORY(alloc_logger, "opic.pm_memory_manager.PMSlot_alloc_obj")

void* PMSlot_alloc_obj(PMSlot* self)
{
  void* obj;
  const size_t obj_size = self->pool->klass->size;
  if (self->pqueue != self->pqueue_next_free) {
    log4c_category_log(alloc_logger, LOG4C_PRIORITY_INFO,
      "alloc from pqueue, with slot: %p", self);
    obj = *self->pqueue;
    self->pqueue_next_free--;
    *self->pqueue = *self->pqueue_next_free;
    PMSlot_pqueue_heapify(self);
  } else if(self->data_next_free < self->data_bound) {
    log4c_category_log(alloc_logger, LOG4C_PRIORITY_INFO,
      "alloc from data chunk, with slot: %p", self);
    obj = self->data_next_free;
    log4c_category_log(alloc_logger, LOG4C_PRIORITY_INFO,
      "data_next_free: %p, size: %d", self->data_next_free, obj_size);
    self->data_next_free += obj_size;
    log4c_category_log(alloc_logger, LOG4C_PRIORITY_INFO,
      "data_next_free: %p, size: %d", self->data_next_free, obj_size);
  } else {
    return NULL;
  }
  return obj;
}

void PMSlot_free_obj(PMSlot* self, void* obj)
{
  const size_t obj_size = self->pool->klass->size;
  memset(obj, 0, obj_size);
  if (self->data_next_free == obj + obj_size)
    {
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
    op_assert(self->data[i].key != key, "key collision in PMLPMap\n");
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

