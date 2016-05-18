#include "../include/typeclass.h"
#include "pm_memory_manager.h"
#include "tc_serializable.h"

typedef struct List List;

struct List {
  struct TCObject;
  List* next;
  int value;
};


void List_serde_serialize(TCObject* obj, PMMemoryManager* ctx)
{
  List* self = (List*) obj;
  self->next = (void*) PMGetSerializeId(ctx, self->next);
}

void List_serde_deserialize(TCObject* obj, PMMemoryManager* ctx)
{
}

TC_DEFINE_ISA_WITH_TYPECLASSES(List, TCSerializable)

int main (int argc, char** argv)
{
  PMMemoryManager* ctx;
  PMMemoryManager_new(&ctx);
  List* node_iter, *node;
  node_iter = node = List_init_isa(PM_ALLOC(ctx, List));
  node_iter->value = 0;
  for (int i = 1; i<10; i++)
    {
      node_iter->next = List_init_isa(PM_ALLOC(ctx, List));
      node_iter = node_iter->next;
      node_iter->value = i;
    }
  for (node_iter = node; node_iter; node_iter = node_iter->next)
    {
      printf("Node: %p, value %d\n", node_iter, node_iter->value);
    }
  /*
  PMFree(ctx,node);
  node = List_init_isa(PM_ALLOC(ctx, List));
  printf("%d\n", node->value);
  printf("first obj: %p\n", node);
  */
  return 0;
}
