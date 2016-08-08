#include "../src/op_trait.h"
#include "../src/pm_memory_manager.h"
#include "../src/op_collection.h"
#include "../src/op_list.h"
#include "../src/op_linked_list.h"

int main (int argc, char** argv)
{
  OPObject* list;
  FILE* in = fopen("list_serialized", "r");
  PMMemoryManager* ctx = PMDeserialize(in, &list);
  fclose(in);

  OPObject* it = lst_listIterator(list);
  while(li_hasNext(it))
    {
      printf("Node value: %zu\n", li_next(it).uint64);
    }
  free(it);
  return 0;
}
