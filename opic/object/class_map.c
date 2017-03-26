#include <stdlib.h>
#include "config.h"
#include "class_map.h"

struct ClassMap
{
  size_t size;
  ClassNode* map;
  Class** classes;
};

struct ClassNode
{
  Class* key;
  OPMPool* pool;
  uint16_t order;
};

static int ptr_cmp (const void* a, const void* b);
static ClassNode* CMGetInternal(ClassMap* self, Class* key);

int CMCreate(ClassMap** self, size_t size)
{
  if (!(*self = calloc(sizeof(ClassMap), 1)))
    return -1;
  if (!((*self)->map = calloc(sizeof(ClassNode), 1 << 16)))
    {
      free(*self);
      return -1;
    }
  if (!((*self)->classes = calloc(sizeof(Class*), 1 << 16)))
    {
      free((*self)->map);
      free(*self);
      return -1;
    }
  return 0;
}
      
void CMDestroy(ClassMap* self)
{
  if (self == NULL) return;
  free(self->map);
  free(self->classes);
  free(self);
}

OPMPool* CMGet(ClassMap* self, Class* key)
{
  ClassNode* node = CMGetInternal(self, key);
  if (node == NULL) return NULL;
  return node->pool;
}

int CMGetOrder(ClassMap* self, Class* key)
{
  ClassNode* node = CMGetInternal(self, key);
  if (node == NULL) return -1;
  return node->order;
}

void CMPut(ClassMap* self, Class* key, OPMPool* value)
{
  const size_t offset = key->hash & ((1<<16) - 1);
  for (size_t i = offset; i < (1 << 16); i++)
    {
      ClassNode* node = self->map + i;
      if (node->key == NULL)
        {
          node->key = key;
          node->pool = value;
          self->classes[self->size++] = key;
          return;
        }
    }
  // circle back to the begining
  for (size_t i = 0; i < offset; i++)
    {
      ClassNode* node = self->map + i;
      if (node->key == NULL)
        {
          node->key = key;
          node->pool = value;
          self->classes[self->size++] = key;
          return;
        }
    }
  op_assert(0, "ClassMap is full\n");
}

size_t CMSize(ClassMap* self)
{
  return self->size;
}

Class** CMIterator(ClassMap* self)
{
  qsort(self->classes, self->size, sizeof(Class*), ptr_cmp);
  for (uint16_t i = 0; i < self->size; i++)
    {
      ClassNode* node = CMGetInternal(self, self->classes[i]);
      node->order = i;
    }
  return self->classes;
}



ClassNode* CMGetInternal(ClassMap* self, Class* key)
{
  const size_t offset = key->hash & ((1<<16) - 1);
  ClassNode* node;
  for (size_t i = offset; i < (1 << 16); i++)
    {
      node = self->map + i;
      if (node->key == NULL) return NULL;
      if (node->key == key) return node;
    }
  // circle back to the begining
  for (size_t i = 0; i < offset; i++)
    {
      node = self->map + i;
      if (node->key == NULL) return NULL;
      if (node->key == key) return node;
    }
  return NULL;
}

int ptr_cmp (const void* a, const void* b)
{
  if (*(void**)a < *(void**)b) return -1;
  if (*(void**)a == *(void**)b) return 0;
  return 1;
}

