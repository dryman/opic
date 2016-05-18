#ifndef PM_MEMORY_MANAGER_H
#define PM_MEMORY_MANAGER_H 1

#include <stdint.h>
#include "../include/typeclass.h"
#include "../include/tc_common_macros.h"

TC_BEGIN_DECLS

typedef struct PMMemoryManager PMMemoryManager;
typedef struct PMAVLNode PMAVLNode;

int PMMemoryManager_new(PMMemoryManager**);
void PMMemoryManager_destroy(PMMemoryManager*);
void* PMAlloc(PMMemoryManager* ctx, Class* klass);
void* PMFree(PMMemoryManager* ctx, void* obj);

size_t PMGetSerializeId(PMMemoryManager* ctx, void* ptr);

#define PM_ALLOC(ctx, KLASS) PMAlloc((ctx), &TC_CLASS_OBJ(KLASS))

TC_END_DECLS
#endif /* PM_MEMORY_MANAGER_H */
