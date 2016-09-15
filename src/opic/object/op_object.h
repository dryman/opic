#ifndef OP_OBJECT_H
#define OP_OBJECT_H 1

#include "op_object_def.h"
#include "op_trait.h"

// TODO: maybe support full rewrite lock for objects?

int OPMallocManagerCreate(OPMallocManager** ctx);
void OPMallocManagerDestroy(OPMallocManager* ctx);
void* OPMalloc(OPMallocManager* ctx, Class* klass);
void OPFree(OPMallocManager* ctx, void* obj);
int OPObjLock(OPMallocManager* ctx);
int OPObjTrylock(OPMallocManager* ctx);
int OPObjUnlock(OPMallocManager* ctx);
int OPSerialize(OPMallocManager* ctx, FILE* fd, uint32_t n, ...);
int OPDeserialize(OPMallocManager** ctx, FILE* fd, ...);

void* OPPtr2Ref(OPMallocManager* ctx, void* ptr);
void* OPRef2Ptr(OPMallocManager* ctx, void* ptr);

#define OP_MALLOC(ctx, KLASS) OPMalloc((ctx), &OP_CLASS_OBJ(KLASS))

#endif /* OP_OBJECT_H */
