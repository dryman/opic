#ifndef PM_MEMORY_MANAGER_H
#define PM_MEMORY_MANAGER_H 1

#include "../../include/typeclass.h"

typedef struct PMMemoryManager PMMemoryManager;
typedef struct PMPool PMPool;
typedef struct PMSlot PMSlot;

int PMPool_new(PMPool**);
void PMPool_destroy(PMPool*);

struct PMMemoryManager {
  PMTypeMap* type_map;
  PMPointerMap* pointer_map;
};

struct PMPool {
  Class* klass;
  PMSlot* slot;
};

struct PMSlot {
  PMPool* pool;
  size_t count;
  void* data;
  void* data_unused;
  size_t* pqueue;
  size_t* pqueue_unused;
  PMSlot* next;
};

#endif /* PM_MEMORY_MANAGER_H */
