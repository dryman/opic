#include "../include/typeclass.h"
#include "pm_memory_manager.h"
#include "pm_simple_list.h"


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
  FILE* out = fopen("list_serialized", "w");
  PMSerialize(ctx, out, 1, node);
  fclose(out);
  /*
  PMFree(ctx,node);
  node = List_init_isa(PM_ALLOC(ctx, List));
  printf("%d\n", node->value);
  printf("first obj: %p\n", node);
  */
  return 0;
}
