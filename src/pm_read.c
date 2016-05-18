#include "../include/typeclass.h"
#include "pm_memory_manager.h"
#include "pm_simple_list.h"

int main (int argc, char** argv)
{
  List* node_iter, *node;
  FILE* in = fopen("list_serialized", "r");
  PMMemoryManager* ctx = PMDeserialize(in, &node);
  fclose(in);

  for (node_iter = node; node_iter; node_iter = node_iter->next)
    {
      printf("Node: %p, value %d\n", node_iter, node_iter->value);
    }
  return 0;
}
