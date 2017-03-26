#include <stdio.h>
#include <limits.h>
#include <pthread.h>
#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>
#include <string.h>
#include "config.h"
#include "op_object_def.h"
#include "op_object.h"
#include "class_map.h"
#include "op_serializable.h"
#include "ptr_range_map.h"
#include "../common/op_log.h"

OP_LOGGER_FACTORY(logger, "opic.op_malloc_manager")

typedef struct ClassMap ClassMap;
typedef struct ClassNode ClassNode;

struct OPMallocManager
{
  ClassMap* class_map;
  PRMObj* pointer_map;
  Class** classes;
  pthread_mutex_t m_lock; // malloc lock
  pthread_mutex_t o_lock; // object lock
};

struct OPMPool
{
  Class* klass;
  OPMSlot* slot;
};

struct OPMSlot
{
  OPMPool* pool;
  size_t size;
  size_t offset; // only used in serialization
  void* data;
  void* data_next_free;
  void* data_bound;
  void** pqueue;
  void** pqueue_next_free;
  OPMSlot* next;
};



static int OPMSlotCreate(OPMSlot** self, OPMPool* pool, PRMObj* pointer_map, size_t size);
static void OPMSlotDestroy(OPMSlot* self);
static void* OPMSlotAlloc(OPMSlot* self);
static void OPMSlotFree(OPMSlot* self, void* obj);
static inline void OPMSlotHeapifyPQueue(OPMSlot* self);


int OPMallocManagerCreate(OPMallocManager** ctx)
{
  if (!(*ctx = calloc(sizeof(OPMallocManager), 1)))
    return -1;
  
  OPMallocManager* self = *ctx;
  
  if (PRMCreate(&self->pointer_map))
    {
      free(self);
      return -1;
    }
  
  if (CMCreate(&self->class_map, 128))
    {
      PRMDestroy(self->pointer_map);
      free(self);
      return -1;
    }
  return 0;
}

void OPMallocManagerDestroy(OPMallocManager* self)
{
  const uint16_t klass_num = CMSize(self->class_map);
  self->classes = CMIterator(self->class_map);
  for (uint16_t i = 0; i < klass_num; i++)
    {
      OPMPool* pool = CMGet(self->class_map, self->classes[i]);
      OPMSlotDestroy(pool->slot);
    }
  CMDestroy(self->class_map);
  PRMDestroy(self->pointer_map);
  free(self);
}
  
void* OPMalloc(OPMallocManager* self, Class* klass)
{
  pthread_mutex_lock(&self->m_lock);
  void* obj = NULL;
  
  OPMPool* pool = CMGet(self->class_map, klass);
  if (!pool) 
    {
      pool = calloc(sizeof(OPMPool), 1);
      pool->klass = klass;
      OPMSlotCreate(&pool->slot, pool, self->pointer_map, 2048);
      CMPut(self->class_map, klass, pool);
    }
  OPMSlot *slot = pool->slot, *prev_slot = NULL;
  while (slot)
    {
      if ((obj = OPMSlotAlloc(slot)))
        {
          goto return_barier;
        }
      prev_slot = slot;
      slot = slot->next;
    }
  OPMSlotCreate(&prev_slot->next, pool, self->pointer_map, prev_slot->size * 2);
  slot = prev_slot->next;
  obj = OPMSlotAlloc(slot);
  
 return_barier:
  ((OPObject*) obj)->manager = self;
  ((OPObject*) obj)->isa = klass;
  OPRetain((OPObject*) obj);
  pthread_mutex_unlock(&self->m_lock);
  return obj;
}

void OPFree(void* obj)
{
  if (obj == NULL) return;

  OPMallocManager* self = ((OPObject*)obj)->manager;
  pthread_mutex_lock(&self->m_lock);
  if (obj == NULL || *(Class**)obj == NULL)
    {
      OP_LOG_ERROR(logger, "Attempt to free invalid ptr %p", obj);
      goto return_barier;
    }
  OPMSlotFree(PRMFind(self->pointer_map, obj), obj);
  
 return_barier:
  pthread_mutex_unlock(&self->m_lock);
}

int OPObjLock(OPMallocManager* self)
{
  return pthread_mutex_lock(&self->o_lock);
}

int OPObjTrylock(OPMallocManager* self)
{
  return pthread_mutex_trylock(&self->o_lock);
}

int OPObjUnlock(OPMallocManager* self)
{
  return pthread_mutex_unlock(&self->o_lock);
}

int OPSerialize(OPMallocManager* self, FILE* fd, uint32_t n, ...)
{
  pthread_mutex_lock(&self->o_lock);
  // May have race condition here
  pthread_mutex_lock(&self->m_lock);

  void* inbounds[n];
  void* inbounds_id[n];
  va_list args;
  va_start(args, n);
  for(uint32_t i = 0; i < n; i++)
    {
      inbounds[i] = va_arg(args, void*);
    }
  va_end(args);

  /* 1. number of classes we have */
  uint16_t klass_num = (uint16_t) CMSize(self->class_map);
  fwrite(&klass_num, sizeof(uint16_t), 1, fd);

  /* 2. Preprocess slot offset so that PMGetSerializeId can 
   *    work properly */
  self->classes = CMIterator(self->class_map);
  for (uint16_t i = 0; i < klass_num; i++)
    {
      OPMPool* pool = CMGet(self->class_map, self->classes[i]);
      size_t offset = 0;
      OPMSlot* slot = pool->slot;
      while(slot)
        {
          slot->offset = offset;
          offset += slot->data_next_free - slot->data;
          slot = slot->next;
        }
    }

  /* 3. each klass we serialize:
   * 3.1 class name
   * 3.2 packed data len
   * 3.3 packed data
   * pqueue data can be restored from null values in the data array
   */
  for (uint16_t i = 0; i < klass_num; i++)
    {
      // 3.1 class name
      OPMPool* pool;
      OPMSlot* slot;
      pool = CMGet(self->class_map, self->classes[i]);
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
      printf("total size for class %s: %zu\n", pool->klass->classname, total_size);
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
              serde_serialize(p, self);
              memset(p + 1, -1, sizeof(Class*) - 1);
              // Set high bytes to -1,
              // last byte preserved for metadata
              //
              // When deserializing, if high bytes were -1,
              // we restore the class; else it would be data
              // slot that were freed.
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
      inbounds_id[i] = OPPtr2Ref(self, inbounds[i]);
    }
  fwrite(&n, sizeof(uint32_t), 1, fd);
  fwrite(inbounds_id, sizeof(void*), n, fd);
  fflush(fd);
  self->classes = NULL;

  return 0;
}


int OPDeserialize(OPMallocManager** self_ref, FILE* fd, ...)
{
  if (OPMallocManagerCreate(self_ref)) return -1;

  OPMallocManager* self = *self_ref;
  uint16_t klass_num;
  fread(&klass_num, 2, 1, fd);

  for (uint16_t i = 0; i < klass_num; i++)
    {
      size_t classname_len;
      size_t total_size, total_cnt;
      size_t obj_size;
      char* classname;
      OPMPool* pool;
      OPMSlot* slot;
      
      fread(&classname_len, sizeof(size_t), 1, fd);
      classname = malloc(classname_len + 1);
      fread(classname, 1, classname_len, fd);
      classname[classname_len] = '\0';
            
      OP_LOG_INFO(logger, "Deserializing class: %s", classname);
        
      Class* klass = LPTypeMap_get(classname);
      OP_LOG_INFO(logger,
        "Deserializing, found matching klass addr: %p, %s",
        klass, klass->classname);
      free(classname);

      fread(&total_size, sizeof(size_t), 1, fd);
      obj_size = klass->size;
      total_cnt = total_size / obj_size;
      
      pool = calloc(sizeof(OPMPool), 1);
      pool->klass = klass;
      CMPut(self->class_map, klass, pool);

      // A workaround for memory manager version 2
      if (total_cnt == 0) 
        {
#ifndef NDEBUG
          OP_LOG_DEBUG(logger, "Empty class: %s", klass->classname);
#endif
          OPMSlotCreate(&pool->slot, pool, self->pointer_map, 2048);
        }
      else 
        {
          OPMSlotCreate(&pool->slot, pool, self->pointer_map, total_cnt);

          slot = pool->slot;
          fread(slot->data, 1, total_size, fd);
          slot->data_next_free = slot->data + total_size;
          for (void* p = slot->data;
               p < slot->data_next_free;
               p += obj_size)
            {
              if (*(Class**)p)
                {
                  // BUG: Need to copy the last byte
                  *(Class**)p = klass;
#ifndef NDEBUG
                  OP_LOG_DEBUG(logger, "obj->isa: %p", ((OPObject*)p)->isa);
#endif
                }
              else
                {
                  // put the reference into pqueue
                  OPMSlotFree(slot, p);
                }
            }
        }
      
    }
  
  // Second pass, restore the pointers
  self->classes = CMIterator(self->class_map);
  for (uint16_t i = 0; i < klass_num; i++)
    {
      OPMPool* pool = CMGet(self->class_map, self->classes[i]);
      OPMSlot* slot = pool->slot;
      
      const size_t obj_size = pool->klass->size;
      for (void* p = slot->data;
           p < slot->data_next_free;
           p += obj_size)
        {
#ifndef NDEBUG
          OP_LOG_DEBUG(logger, "Restoring pointer %p for klass %s",
                        p, pool->klass->classname);
#endif
          if (*(Class**)p)
            {
              OPObject* obj = (OPObject*)p;
              obj->manager = self;
              serde_deserialize(p, self);
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
      *ptr = OPRef2Ptr(self, inbounds[i]);
    }
  va_end(args);
  return 0;
}

void* OPPtr2Ref(OPMallocManager* self, void* ptr)
{
  OPMSlot* slot = PRMFind(self->pointer_map, ptr);
  int order = CMGetOrder(self->class_map, slot->pool->klass);
  op_assert(order >= 0, "Could not find class for pointer %p\n", ptr);

  size_t offset, ref;
  offset = ptr - slot->data + slot->offset;
  // The two most significant byte indicates the type, and
  // the remaining bits records the offset
  ref = (((size_t)order) << (sizeof(size_t)-2)*CHAR_BIT) | offset;
  return (void*)ref;
}

void* OPRef2Ptr(OPMallocManager* self, void* ref)
{
  int shift = (sizeof(size_t)-2) * CHAR_BIT;
  int order = ((size_t)ref & (0xFFFFL << shift)) >> shift;
  Class* klass = self->classes[order];
  size_t offset = (size_t)ref & ((1L << shift)-1);
  OPMPool* pool = CMGet(self->class_map, klass);
  OPMSlot* slot = pool->slot;
  return slot->data + offset;
}


/* static functions */


int OPMSlotCreate(OPMSlot** ctx, OPMPool* pool, PRMObj* pointer_map, size_t size)
{
  if (!(*ctx = calloc(sizeof(OPMSlot), 1))) return -1;
  OPMSlot* self = *ctx;
  self->pool = pool;
  self->size = size;
  if (!(self->data = calloc(pool->klass->size, size)))
    {
      free(self);
      return -1;
    }
  if (!(self->pqueue = calloc(sizeof(void*), size)))
    {
      free(self->data);
      free(self);
      return -1;
    }
  self->data_next_free = self->data;
  self->data_bound = self->data + pool->klass->size * size;
  self->pqueue_next_free = self->pqueue;
  PRMInsert(pointer_map, self->data, self->data_bound, self);
  return 0;
}

void OPMSlotDestroy(OPMSlot* self)
{
  if (self == NULL) return;
  free(self->data);
  free(self->pqueue);
  OPMSlotDestroy(self->next);
  free(self);
}


void* OPMSlotAlloc(OPMSlot* self)
{
  void* obj;
  const size_t obj_size = self->pool->klass->size;
  
  if (self->pqueue != self->pqueue_next_free)
    {
      obj = *self->pqueue;
      self->pqueue_next_free--;
      *self->pqueue = *self->pqueue_next_free;
      OPMSlotHeapifyPQueue(self);
    }
  else if (self->data_next_free < self->data_bound)
    {
      obj = self->data_next_free;
      self->data_next_free += obj_size;
    }
  else 
    {
      return NULL;
    }
  return obj;
}

void OPMSlotFree(OPMSlot* self, void* obj)
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
  OPMSlotHeapifyPQueue(self);
}

void OPMSlotHeapifyPQueue(OPMSlot* self)
{
  if (self->pqueue == self->pqueue_next_free) return;
  for (ptrdiff_t i = (self->pqueue_next_free - self->pqueue)-1;
       !i; i/=2)
    {
      void* node   = self->pqueue[i];
      void* parent = self->pqueue[i/2];
      if(node < parent)
        {
          self->pqueue[i]   = parent;
          self->pqueue[i/2] = node;
        }
      else
        {
          break;
        }
    }
}
