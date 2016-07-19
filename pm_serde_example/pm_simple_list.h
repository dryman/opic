#ifndef PM_SIMPLE_LIST_H
#define PM_SIMPLE_LIST_H

#include <stdint.h>
#include "../src/op_trait.h"
#include "../src/op_serializable.h"
#include "../src/pm_memory_manager.h"

OP_BEGIN_DECLS

typedef struct List List;

struct List 
{
  struct OPObject base;
  List* next;
  union PtrEquivalent value;
};

void List_serde_serialize(OPObject* obj, PMMemoryManager* ctx);
void List_serde_deserialize(OPObject* obj, PMMemoryManager* ctx);

OP_DECLARE_ISA(List);

OP_END_DECLS

#endif /* PM_SIMPLE_LIST_H */
