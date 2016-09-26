#include <log4c.h>
#include "config.h"
#include "opic.h"
#include "op_collection.h"
#include "op_list.h"
#include "op_linked_list.h"


OP_LOGGER_FACTORY(logger, "pm_test");

int main (int argc, char** argv)
{
  OPMallocManager* ctx;
  
  OPMallocManagerCreate(&ctx);
  printf("sizeof(OPType): %d\n", sizeof(OPType));
  OPObject* list = OP_MALLOC(ctx, OPLinkedList);
  mcoll_init(list, op_int32);

  for (int i = 0; i<10; i++)
    {
      mcoll_add(list, (uint64_t)i);
    }
  OPObject* it = lst_listIterator(list);
  while(li_hasNext(it))
    {
      printf("Node value: %zu\n", li_next(it).uint64);
    }
  OPRelease(it);
  FILE* out = fopen("list_serialized", "w");
  OPSerialize(ctx, out, 1, list);
  fclose(out);

  OPMallocManagerDestroy(ctx);
  /*
  PMFree(ctx,node);
  node = List_init_isa(PM_ALLOC(ctx, List));
  printf("%d\n", node->value);
  printf("first obj: %p\n", node);
  */
  return 0;
}
