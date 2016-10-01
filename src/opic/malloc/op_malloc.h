#ifndef OP_MALLOC_H
#define OP_MALLOC_H 1

#include <stdint.h>


typedef struct OPMemoryManager OPMemoryManager;

struct VSpanBase
{
  uint16_t flags;
};

int OPMemoryManagerCreate(OPMemoryManager** ref);
void OPMemoryManagerDestory(OPMemoryManager* self);
void* OPMallocVSpan(OPMemoryManager* self, int pages);
void OPFreeVSpan(OPMemoryManager* self, void* addr, int pages);

#endif /* OP_MALLOC_H */
