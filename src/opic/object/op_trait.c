#include <stdint.h>
#include <stdlib.h>
#include "op_trait.h"
#include "config.h"
#include "../common/op_log.h"

OP_LOGGER_FACTORY(logger, "opic.op_trait")

#define LP_TYPE_MAP_INIT_SIZE 1024

typedef struct LPTypeMap LPTypeMap;
typedef struct LPTypeMapData LPTypeMapData;

static uint64_t sdbm(char* str);
static LPTypeMap __lp_type_map;

struct LPTypeMap
{
  size_t size;
  LPTypeMapData* data;
};
  
struct LPTypeMapData
{
  char* key;
  Class* value;
};

Class* LPTypeMap_get(char* key)
{
  op_assert(__lp_type_map.size, "type map should not be empty when querying\n");
  uint64_t hash = sdbm(key);
  for (size_t i = hash % __lp_type_map.size; 
       i < __lp_type_map.size; i++) 
    {
      op_assert(__lp_type_map.data[i].key, "no matching bucket for key %s\n", key);
      if (!strcmp(__lp_type_map.data[i].key, key)) 
        {
          return __lp_type_map.data[i].value;
        }
    }
  op_assert(0, "Could not find key %s\n", key);
}

void LPTypeMap_put(char* key, Class* value)
{
  if (op_unlikely(!__lp_type_map.size))
    {
      __lp_type_map.size = LP_TYPE_MAP_INIT_SIZE;
      __lp_type_map.data = calloc(sizeof(LPTypeMapData), LP_TYPE_MAP_INIT_SIZE);
    }
  uint64_t hash = sdbm(key);
  for (size_t i = hash % __lp_type_map.size; 
              i < __lp_type_map.size; i++) 
    {
      if (!__lp_type_map.data[i].key) 
        {
          __lp_type_map.data[i].key = key;
          __lp_type_map.data[i].value = value;
          return;
        }
      op_assert(strcmp(__lp_type_map.data[i].key, key), "Collision key %s in LPTypeMap\n", key);
  }
  size_t old_size = __lp_type_map.size;
  LPTypeMapData* old_data = __lp_type_map.data;

  __lp_type_map.size = __lp_type_map.size << 1;
  __lp_type_map.data = calloc(sizeof(LPTypeMapData), __lp_type_map.size);
  for (size_t i = 0; i < old_size; i++) 
    {
      if (!old_data[i].key) 
        {
          LPTypeMap_put(old_data[i].key, old_data[i].value);
        }
    }
  LPTypeMap_put(key, value);
}

bool tc_isa_instance_of(Class* klass, char* trait)
{
  for (TypeClass** t = klass->traits; t; t++)
    {
      if (!strcmp((*t)->name, trait))
        return true;
    }
  return false;
}

bool tc_instance_of(OPObject* obj, char* trait)
{
  return tc_isa_instance_of(obj->isa, trait);
}

uint64_t sdbm(char* str)
{
  uint64_t hash = 0;
  int c;
  while ((c = *str++))
    {
      hash = c + (hash << 6) + (hash << 16) - hash;
    }
  return hash;
}

uint64_t op_murmur_hash(void* ptr)
{
  // copied from murmur hash 3.. 
  uint64_t k = (uint64_t) ptr;
  k ^= k >> 33;
  k *= 0xff51afd7ed558ccd;
  k ^= k >> 33;
  k *= 0xc4ceb9fe1a85ec53;
  k ^= k >> 33;
  return k;
}
