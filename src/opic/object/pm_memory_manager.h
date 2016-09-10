#ifndef PM_MEMORY_MANAGER_H
#define PM_MEMORY_MANAGER_H 1

#include <stdint.h>
#include "../common/op_macros.h"
#include "op_trait.h"
#include "op_object_def.h"
#include "ptr_range_map.h"

OP_BEGIN_DECLS

typedef struct PMMemoryManager PMMemoryManager;

int PMMemoryManager_new(PMMemoryManager**);
void PMMemoryManager_destroy(PMMemoryManager*);
void* PMAlloc(PMMemoryManager* ctx, Class* klass);
void* PMFree(PMMemoryManager* ctx, void* obj);
int PMSerialize(PMMemoryManager* ctx, FILE* fd, uint32_t n, ...);
PMMemoryManager* PMDeserialize(FILE* fd, ...);

void* PMSerializePtr2Ref(void* ptr, PMMemoryManager* ctx);
void* PMDeserializeRef2Ptr(void* ref, PMMemoryManager* ctx);

#define PM_ALLOC(ctx, KLASS) PMAlloc((ctx), &OP_CLASS_OBJ(KLASS))

OP_END_DECLS
#endif /* PM_MEMORY_MANAGER_H */
