#ifndef CLASS_MAP_H
#define CLASS_MAP_H 1

#include "op_object_def.h"

typedef struct ClassMap ClassMap;
typedef struct ClassNode ClassNode;

int CMCreate(ClassMap** self, size_t size);
void CMDestroy(ClassMap* self);
OPMPool* CMGet(ClassMap* self, Class* key);
int CMGetOrder(ClassMap* self, Class* key);
void CMPut(ClassMap* self, Class* key, OPMPool* value);
size_t CMSize(ClassMap* self);
Class** CMIterator(ClassMap* self);

#endif /* CLASS_MAP_H */
