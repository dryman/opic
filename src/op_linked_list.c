#include "op_linked_list.h"

typedef struct OPLinkedListNode;

// Last bit in ISA pointer denotes it is mutable or not
struct OPLinkedList
{
  struct OPObject base;
  OPType type;
  size_t size;
  OPLinkedListNode* head;
};

struct OPLinkedListNode
{
  struct OPObject base;
  OPGeneric value;
  OPLinkedListNode* next;
  OPLinkedListNode* prev;
};

struct OPLinkedListIterator
{
  struct OPObject base;
  OPType type;
  OPLinkedListNode* cursor;
  OPLinkedList* container;
}


void OPLinkedList_serde_serialize(OPObject* obj, PMMemoryManager* ctx)
{
  OPLinkedList* self = (OPLinkedList*) obj;
  if (self->head)
    self->head = PMSerializePtr2Ref(self->head, ctx);
}

void OPLinkedList_serde_deserialize(OPObject* obj, PMMemoryManager* ctx)
{
  OPLinkedList* self = (OPLinkedList*) obj;
  if (self->head)
    self->head = PMDeserializeRef2Ptr(self->head, ctx);
}

bool      OPLinkedList_coll_contains(OPObject* obj, OPGeneric element);
bool      OPLinkedList_coll_containsAll(OPObject* obj, OPObject* collection);
bool      OPLinkedList_coll_isEmpty(OPObject* obj);
size_t    OPLinkedList_coll_size(OPObject* obj);
OPTYpe    OPLinkedList_coll_type(OPObject* obj);

OP_DEFINE_ISA_WITH_TYPECLASSES(OPLinkedList, OPSerializable, OPCollection, OPList);
OP_DEFINE_ISA_WITH_TYPECLASSES(OPLinkedListNode, OPSerializable);
OP_DEFINE_ISA_WITH_TYPECLASSES(OPLinkedListIterator, OPListIterator);
OP_DEFINE_ISA_WITH_TYPECLASSES(OPMutableLinkedList, OPSerializable, 
  OPCollection, OPList, OPMutableList);
OP_DEFINE_ISA_WITH_TYPECLASSES(OPMutableLinkedListIterator, OPListIterator
  OPMutableListIterator);
