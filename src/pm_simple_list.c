#include "pm_simple_list.h"

OP_DEFINE_ISA_WITH_TYPECLASSES(List, OPSerializable)

void List_serde_serialize(OPObject* obj, PMMemoryManager* ctx)
{
  List* self = (List*) obj;
  if (self->next)
    self->next = PMSerializePtr2Ref(self->next, ctx);
}

void List_serde_deserialize(OPObject* obj, PMMemoryManager* ctx)
{
  List* self = (List*) obj;
  printf("reached deserialize\n");
  if (self->next)
    self->next = PMDeserializeRef2Ptr(self->next, ctx);
}

