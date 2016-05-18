#include "../include/typeclass.h"
#include "pm_memory_manager.h"

typedef struct List {
  struct TCObject;
  TCObject* next;
  int value;
} List;

TC_DEFINE_ISA(List)

int main (int argc, char** argv)
{
  PMMemoryManager* ctx;
  PMMemoryManager_new(&ctx);
  List* node = List_init_isa(PM_ALLOC(ctx, List));
  printf("first obj: %p\n", node);
  printf("obj: %p\n", PM_ALLOC(ctx,List));
  printf("obj: %p\n", PM_ALLOC(ctx,List));
  printf("obj: %p\n", PM_ALLOC(ctx,List));
  printf("List size: %d, from class: %d\n", sizeof(List), node->isa->size);
  node->value=3;
  printf("%d\n", node->value);
  PMFree(ctx,node);
  node = List_init_isa(PM_ALLOC(ctx, List));
  printf("%d\n", node->value);
  printf("first obj: %p\n", node);
  return 0;
}
