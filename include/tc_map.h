#ifndef TC_MAP_H
#define TC_MAP_H 1

#include "typeclass.h"

TC_BEGIN_DECLS

#define Map_TC_METHODS \
map_clear, map_get, map_containsKey, map_containsValue, \
map_isEmpty, map_put, map_remove, map_size

TC_DECLARE_METHOD(map_clear, void, TCObject* self);
TC_DECLARE_METHOD(map_get, void*, TCObject* self, void* key);
TC_DECLARE_METHOD(map_containsKey, bool, TCObject* self, void* key);
TC_DECLARE_METHOD(map_containsValue, bool, TCObject* self, void* value);
TC_DECLARE_METHOD(map_put, void*, TCObject* self, void* key, void* value);
TC_DECLARE_METHOD(map_isEmpty, bool, TCObject* self);
TC_DECLARE_METHOD(map_remove, bool, TCObject* self, void* key);
TC_DECLARE_METHOD(map_size, size_t, TCObject* self);
TC_DECLARE_TYPECLASS(Map);

/* methods not yet implemented:
 Set<Map.Entry<K,V>> entrySet
 Set<K> keySet;
 putAll(Map<K,V> m);
 */


 TC_END_DECLS

 #endif /* TC_MAP_H */
