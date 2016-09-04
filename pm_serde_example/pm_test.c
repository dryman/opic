#include "../src/opic.h"
#include "../src/op_collection.h"
#include "../src/op_list.h"
#include "../src/op_linked_list.h"


int main (int argc, char** argv)
{
  PMMemoryManager* ctx;
  PMMemoryManager_new(&ctx);
  printf("sizeof(OPType): %d\n", sizeof(OPType));
  OPObject* list = (OPObject*)OPLinkedList_init_isa(PM_ALLOC(ctx, OPLinkedList));
  mcoll_init(list, op_int32, ctx);

  for (int i = 0; i<10; i++)
    {
      mcoll_add(list, (uint64_t)i);
    }
  OPObject* it = lst_listIterator(list);
  while(li_hasNext(it))
    {
      printf("Node value: %zu\n", li_next(it).uint64);
    }
  free(it);
  FILE* out = fopen("list_serialized", "w");
  PMSerialize(ctx, out, 1, list);
  fclose(out);

  PMMemoryManager_destroy(ctx);
  /*
  PMFree(ctx,node);
  node = List_init_isa(PM_ALLOC(ctx, List));
  printf("%d\n", node->value);
  printf("first obj: %p\n", node);
  */
  return 0;
}
