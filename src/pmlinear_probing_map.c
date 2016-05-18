#include <stdbool.h>
#include "../include/tc_assert.h"
#include "pmlinear_probing_map.h"

TC_CLASS_INIT_FACTORY(PMLinearProbingMap,Map)

// we should name it non managed new
// and create another init like func
// also.. how do we handle anonymous struct? it is not managed...

int PMLinearProbingMap_new(PMLinearProbingMap** self, tc_hash hash_func, tc_equal equal_func, size_t size)
{
  if (!(*self = calloc(sizeof(PMLinearProbingMap),1))) return -1;
  PMLinearProbingMap_init(*self);
  (*self)->hash_func = hash_func;
  (*self)->equal_func = equal_func;
  (*self)->size = size << 2;
  (*self)->data = calloc(sizeof(((PMLinearProbingMap*)NULL)->data), (*self)->size);
  return 0;
}

void PMLinearProbingMap_destroy(PMLinearProbingMap* self, tc_destory destory_key, tc_destory destory_value)
{
  for (int i = 0; i < self->size; i++) {
    if (self->data[i].key) {
      destory_key(self->data[i].key);
      destory_value(self->data[i].value);
    }
  }
  free(self->data);
  free(self);
}

void PMLinearProbingMap_map_clear(TCObject* _self)
{
  PMLinearProbingMap* self = (PMLinearProbingMap*) _self;
  for(int i = 0; i < self->size; i++) {
    self->data[i].key = NULL;
    self->data[i].value = NULL;
  }
}

void* PMLinearProbingMap_map_get(TCObject* _self, void* key)
{
  PMLinearProbingMap* self = (PMLinearProbingMap*) _self;
  unsigned int hash = self->hash_func(key);
  tc_equal equal = self->equal_func;
  for (unsigned int i = hash % self->size; i < self->size; i++) {
    if (!self->data[i].key) return NULL;
    if (equal(self->data[i].key, key)) {
      return self->data[i].value;
    }
  }
  return NULL;
}

bool PMLinearProbingMap_map_containsKey(TCObject* self, void* key)
{
  return (bool)PMLinearProbingMap_map_get(self, key);
}

void* PMLinearProbingMap_map_put(TCObject* _self, void* key, void* value)
{
  PMLinearProbingMap* self = (PMLinearProbingMap*) _self;
  unsigned int hash = self->hash_func(key);
  tc_equal equal = self->equal_func;
  for (unsigned int i = hash % self->size; i < self->size; i++) {
    if (!self->data[i].key) {
      self->data[i].value = value;
      self->count++;
      return NULL;
    }
    if (equal(self->data[i].key, key)) {
      void* ret = self->data[i].value;
      self->data[i].value = value;
      return ret;
    }
  }
  // need to expand size and reassign all key value pairs
  tc_assert(0, "map is full\n");
  return NULL;
}
  

bool PMLinearProbingMap_map_isEmpty(TCObject* _self)
{
  PMLinearProbingMap* self = (PMLinearProbingMap*) _self;
  return self->count == 0;
}

void* PMLinearProbingMap_map_remove(TCObject* _self, void* key)
{
  PMLinearProbingMap* self = (PMLinearProbingMap*) _self;
  unsigned int hash = self->hash_func(key);
  tc_equal equal = self->equal_func;
  for (unsigned int i = hash % self->size; i < self->size; i++) {
    if (!self->data[i].key) return NULL;
    if (equal(self->data[i].key, key)) {
      void* ret = self->data[i].value;
      self->data[i].key = NULL;
      self->data[i].value = NULL;
      self->count--;
      return ret;
    }
  }
  return NULL;
}
  
size_t PMLinearProbingMap_map_size(TCObject* _self)
{
  PMLinearProbingMap* self = (PMLinearProbingMap*) _self;
  return self->count;
}

/*
 * serialize interface is not ready yet
 */

