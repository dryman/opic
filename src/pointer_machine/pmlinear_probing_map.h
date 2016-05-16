#ifndef PM_LINEAR_PROBING_MAP_H
#define PM_LINEAR_PROBING_MAP_H 1

#include <stdbool.h>
#include "../../include/tc_common_macros.h"
#include "../../include/tc_map.h"
#include "../../include/typeclass.h"

TC_BEGIN_DECLS

typedef unsigned int (*tc_hash)(void*);
typedef bool (*tc_equal)(void*, void*);

typedef struct PMLinearProbingMap {
  struct TCObject;
  tc_hash hash_func;
  tc_equal equal_func;
  size_t size;
  size_t count;
  struct {
    void* key;
    void* value;
  } *data;
} PMLinearProbingMap;

/*
 * map interface
 */

void PMLinearProbingMap_map_clear(TCObject* self);
void* PMLinearProbingMap_map_get(TCObject* self, void* key);
bool PMLinearProbingMap_map_containsKey(TCObject* self, void* key);
bool PMLinearProbingMap_map_containsValue(TCObject* self, void* value);
void* PMLinearProbingMap_map_put(TCObject* self, void* key, void* value);
bool PMLinearProbingMap_map_isEmpty(TCObject* self);
bool PMLinearProbingMap_map_remove(TCObject* self, void* key);
size_t PMLinearProbingMap_map_size(TCObject* self);

/*
 * serialize interface is not ready yet
 */

bool PMLinearProbingMap_new(PMLinearProbingMap** self, tc_hash hash_func, tc_equal equal_func, size_t size);
void PMLinearProbingMap_destroy(PMLinearProbingMap* self);

TC_END_DECLS

/* the problem is...
   how do we serialize hash_func!?
   Maybe we need a TCFunc so that we can register it... no this won't work
   because you can't store a generic stuff
   macro SERIALIZABLE_FUNC(func name) => register
   func name <-> func address
   Oh.. we can also check if address is in global when people initialize it
 */

#endif /* PM_LINEAR_PROBING_MAP_H */
