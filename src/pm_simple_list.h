#ifndef PM_SIMPLE_LIST_H
#define PM_SIMPLE_LIST_H

#include <stdint.h>
#include "../include/typeclass.h"
#include "tc_serializable.h"
#include "pm_memory_manager.h"

TC_BEGIN_DECLS

typedef struct List List;

struct List {
  struct TCObject;
  List* next;
  union PtrEquivalent value;
};

void List_serde_serialize(TCObject* obj, PMMemoryManager* ctx);
void List_serde_deserialize(TCObject* obj, PMMemoryManager* ctx);

TC_DECLARE_ISA(List);

TC_END_DECLS

#endif /* PM_SIMPLE_LIST_H */
