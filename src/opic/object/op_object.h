#ifndef OP_OBJECT_H
#define OP_OBJECT_H 1

#include "op_object_def.h"
#include "op_trait.h"

// TODO: maybe support full rewrite lock for objects?

OP_BEGIN_DECLS

int OPMallocManagerCreate(OPMallocManager** ctx);
void OPMallocManagerDestroy(OPMallocManager* ctx);
void* OPMalloc(OPMallocManager* ctx, Class* klass);
void OPFree(void* obj);
int OPObjLock(OPMallocManager* ctx);
int OPObjTrylock(OPMallocManager* ctx);
int OPObjUnlock(OPMallocManager* ctx);
int OPSerialize(OPMallocManager* ctx, FILE* fd, uint32_t n, ...);
int OPDeserialize(OPMallocManager** ctx, FILE* fd, ...);
void* OPPtr2Ref(OPMallocManager* ctx, void* ptr);
void* OPRef2Ptr(OPMallocManager* ctx, void* ptr);

void OPRetain(void* obj);
void OPRelease(void* obj);

#define OP_MALLOC(ctx, KLASS) OPMalloc((ctx), &OP_CLASS_OBJ(KLASS))

// Should add copy, deep_copy, hash, isEqual, etc
#define OPObjectBase_OP_METHODS op_dealloc
OP_DECLARE_METHOD(op_dealloc, void, void* obj);
OP_DECLARE_TYPECLASS(OPObjectBase);

OP_END_DECLS

#endif /* OP_OBJECT_H */
