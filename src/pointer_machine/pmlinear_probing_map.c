#include <stdbool.h>
#include "linear_probing_map.h"

TC_CLASS_INIT_FACTORY(PMLinearProbingMap,Map)

// we should name it non managed new
// and create another init like func
// also.. how do we handle anonymous struct? it is not managed...

bool PMLinearProbingMap_new(LinearProbingMap** self, tc_hash hash_func, tc_equal equal_func, size_t size)
{
  if (!*self = calloc(sizeof(LinearProbingMap),1)) return false;
  LinearProbingMap_init(*self);
  (*self)->hash_func = hash_func;
  (*self)->equal_func = equal_func;
  (*self)->size = size << 2;
  (*self)->data = calloc(sizeof(((LinearProbingMap*)NULL)->data), (*self)->size);
  return true;
}

void PMLinearProbingMap_destroy(LinearProbingMap* self)
{
  free(self->data);
  free(self);
}

bool PMLinearProbingMap_map_clear(TCObject* self)
{
  for(int i = 0; i < self->size; i++) {
    self->data.key = NULL;
    self->data.value = NULL;
  }
  return true;
}

bool PMLinearProbingMap_map_get(TCObject* self, void* key, void** value)
{
  unsigned int hash = self->hash_func(key);
  tc_equal equal = self->equal_func;
  for (unsigned int i = hash % self->size; i < self->size; i++) {
    if (!self->data[i].key) return false;
    if (equal(self->data[i].key, key)) {
      *value = self->data[i].value;
      return true;
    }
  }
  return false;
}

bool PMLinearProbingMap_map_containsKey(TCObject* self, void* key)
{
  void* value;
  return PMLinearProbingMap_map_get(self, key, &value);
}

bool PMLinearProbingMap_map_containsValue(TCObject* self, void* value)
{
  tc_assert("Not implemented");
}

bool PMLinearProbingMap_map_isEmpty(TCObject* self)
{
  return self->size == 0;
}

bool PMLinearProbingMap_map_remove(TCObject* self, void* key)
{
  unsigned int hash = self->hash_func(key);
  tc_equal equal = self->equal_func;
  for (unsigned int i = hash % self->size; i < self->size; i++) {
    if (!self->data[i].key) return false;
    if (equal(self->data[i].key, key)) {
      self->data[i].key = NULL;
      self->data[i].value = NULL;
      self->size--;
      return true;
    }
  }
  return false;
}
  
bool PMLinearProbingMap_map_size(TCObject* self);

/*
 * serialize interface is not ready yet
 */

