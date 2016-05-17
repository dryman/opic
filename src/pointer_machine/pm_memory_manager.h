#ifndef PM_MEMORY_MANAGER_H
#define PM_MEMORY_MANAGER_H 1

#include "pmlinear_probing_map.h"

typedef struct PMMemoryManager PMMemoryManager;
typedef struct PMPool PMPool;
typedef struct PMSlot PMSlot;

int PMMemoryManager_new(PMMemoryManager**);
void PMMemoryManager_destroy(PMMemoryManager*);
void* PMAlloc(PMMemoryManager* ctx, Class* klass);
void* PMFree(PMMemoryManager* ctx, void* obj);

struct PMMemoryManager {
  PMLinearProbingMap* type_map;
  PMLinearProbingMap* pointer_map;
};

struct PMPool {
  Class* klass;
  PMSlot* slot;
};

struct PMSlot {
  PMPool* pool;
  size_t size;
  void* data;
  void* data_next_free;
  void* data_bound;
  void** pqueue;
  void** pqueue_next_free;
  PMSlot* next;
};

#endif /* PM_MEMORY_MANAGER_H */
