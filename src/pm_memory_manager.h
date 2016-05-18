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
int PMSerialize(PMMemoryManager* ctx, FILE* fd, uint32_t n, ...);

void* PMSerializePtr2Ref(void* ptr, PMMemoryManager* ctx);
void* PMDeSerializeRef2Ptr(void* ref, PMMemoryManager* ctx);

#define PM_ALLOC(ctx, KLASS) PMAlloc((ctx), &TC_CLASS_OBJ(KLASS))

TC_END_DECLS
#endif /* PM_MEMORY_MANAGER_H */
