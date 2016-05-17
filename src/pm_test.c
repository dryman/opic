#include "../include/typeclass.h"
#include "pm_memory_manager.h"

typedef struct List {
  struct TCObject;
  TCObject* next;
  int value;
} List;

Class TC_CLASS_OBJ(List) = {.classname = "List", .size = sizeof(List)};
void List_init(List* obj)
{
  obj->isa = &TC_CLASS_OBJ(List);
}

int main (int argc, char** argv)
{
  PMMemoryManager* ctx;
  PMMemoryManager_new(&ctx);
  List* node = PM_ALLOC(ctx, List);
  printf("first obj: %p\n", node);
  printf("obj: %p\n", PM_ALLOC(ctx,List));
  printf("obj: %p\n", PM_ALLOC(ctx,List));
  printf("obj: %p\n", PM_ALLOC(ctx,List));
  List_init(node);
  node->value=3;
  printf("%d\n", node->value);
  PMFree(ctx,node);
  node = PM_ALLOC(ctx, List);
  List_init(node);
  printf("%d\n", node->value);
  printf("first obj: %p\n", node);
  return 0;
}
