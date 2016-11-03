#include "config.h"
#include "opic.h"
#include "op_collection.h"
#include "op_list.h"
#include "op_linked_list.h"

int main (int argc, char** argv)
{
  OPObject* list;
  FILE* in = fopen("list_serialized", "r");
  OPMallocManager* ctx;
  OPDeserialize(&ctx, in, &list);
  fclose(in);

  OPObject* it = lst_listIterator(list);
  while(li_hasNext(it))
    {
      printf("Node value: %lu\n", li_next(it).uint64);
    }
  OPRelease(it);
  OPMallocManagerDestroy(ctx);
  return 0;
}
