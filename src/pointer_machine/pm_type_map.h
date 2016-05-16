#ifndef PM_TYPE_MAP
#define PM_TYPE_MAP

// #include "../../include/typeclass.h"
// We should define a map interface...
/*
 void clear;
 bool containsKey;
 bool containsValue;
 (Set<Map.Entry<K,V>> entrySet) Do we need this?
 bool isEmpty;
 Set<K> keySet;
 put(K key, V value); (how do we get the value already in there?)
 putAll(Map<K,V> m);
 remove(key)
 size;
 values;
 */


typedef struct PMTypeMap PMTypeMap;

struct PMTypeMap {
  // TCObject base;
  struct {
    Class* klass;
    PMPool* pool;
  }* map;
  size_t map_size;
}


#endif /* PM_TYPE_MAP */
