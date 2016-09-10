#ifndef PTR_RANGE_MAP_H
#define PTR_RANGE_MAP_H 1

#include "../common/op_macros.h"
#include "op_object_def.h"

OP_BEGIN_DECLS

typedef struct PRMObj PRMObj;

int PRMCreate(PRMObj** ctx);
void PRMDestroy(PRMObj* ctx);
void PRMInsert(PRMObj* ctx, void* ptr_low, void* ptr_high, PMSlot* slot);
void PRMDelete(PRMObj* ctx, void* ptr_low);
PMSlot* PRMFind(PRMObj* ctx, void* ptr);

OP_END_DECLS

#endif /* PTR_RANGE_MAP_H */
