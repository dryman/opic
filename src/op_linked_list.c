#include <stdlib.h>
#include "op_linked_list.h"
#include <limits.h>

// Last bit in ISA pointer denotes it is mutable or not
struct OPLinkedList
{
  struct OPObject base;
  OPType type;
  size_t size;
  PMMemoryManager* memory_manager;
  OPLinkedListNode* head;
  OPLinkedListNode* tail;
};

struct OPLinkedListNode
{
  struct OPObject base;
  OPLinkedList* container;
  OPGeneric value;
  OPLinkedListNode* next;
  OPLinkedListNode* prev;
};

struct OPLinkedListIterator
{
  struct OPObject base;
  OPType type;
  OPLinkedListNode* next;
  OPLinkedListNode* prev;
  OPLinkedList* container;
};

OP_DEFINE_ISA_WITH_TYPECLASSES(OPLinkedListNode, OPSerializable)
OP_DEFINE_ISA_WITH_TYPECLASSES(OPLinkedList, OPSerializable, OPCollection, OPList, OPMutableList)
OP_DEFINE_ISA_WITH_TYPECLASSES(OPLinkedListIterator, OPListIterator, OPMutableListIterator)

void OPLinkedListNode_serde_serialize(OPObject* obj, PMMemoryManager* ctx)
{
  OPLinkedListNode* self = (OPLinkedListNode*) obj;

  if (self->next)
    self->next = PMSerializePtr2Ref(self->next, ctx);
  if (self->prev)
    self->prev = PMSerializePtr2Ref(self->prev, ctx);

  if (self->container->type == op_object)
    self->value.obj = PMSerializePtr2Ref(self->value.obj, ctx);
  self->container = PMSerializePtr2Ref(self->container, ctx);
}

void OPLinkedListNode_serde_deserialize(OPObject* obj, PMMemoryManager* ctx)
{
  OPLinkedListNode* self = (OPLinkedListNode*) obj;
  if (self->next)
    self->next = PMDeserializeRef2Ptr(self->next, ctx);
  if (self->prev)
    self->prev = PMDeserializeRef2Ptr(self->prev, ctx);

  self->container = PMDeserializeRef2Ptr(self->container, ctx);
  if (self->container->type == op_object)
    self->value.obj = PMDeserializeRef2Ptr(self->value.obj, ctx);
}

void OPLinkedList_serde_serialize(OPObject* obj, PMMemoryManager* ctx)
{
  OPLinkedList* self = (OPLinkedList*) obj;
  op_assert(ctx == self->memory_manager, "Inconsistent memory manager\n");
  if (self->head)
    {
      self->head = PMSerializePtr2Ref(self->head, ctx);
      self->tail = PMSerializePtr2Ref(self->tail, ctx);
    }
  self->memory_manager = NULL;
}

void OPLinkedList_serde_deserialize(OPObject* obj, PMMemoryManager* ctx)
{
  OPLinkedList* self = (OPLinkedList*) obj;
  if (self->head)
    {
      self->head = PMDeserializeRef2Ptr(self->head, ctx);
      self->tail = PMDeserializeRef2Ptr(self->tail, ctx);
    }
  self->memory_manager = ctx;
}

bool      OPLinkedList_coll_contains(OPObject* obj, OPGeneric element)
{
  OPLinkedList* self = (OPLinkedList*) obj;
  OPObject* it = OPLinkedList_lst_listIterator(obj);
  bool ret = false;
  while(li_hasNext(it))
    {
      OPGeneric item = li_next(it);
      if (item.obj == element.obj)
        {
          ret = true;
          break;
        }
    }
  free(it);
  return ret;
}

bool      OPLinkedList_coll_containsAll(OPObject* obj, OPObject* collection)
{
  // TODO Need to check if collection is Iterable or Colleciton
  OPLinkedList* self = (OPLinkedList*) obj;
  OPObject* it = OPLinkedList_lst_listIterator(obj);
  bool ret = true;
  while(li_hasNext(it))
    {
      OPGeneric item = li_next(it);
      if (!coll_contains(collection, item))
        {
          ret = false;
          break;
        }
    }
  free(it);
  return ret;
}

bool      OPLinkedList_coll_isEmpty(OPObject* obj)
{
  OPLinkedList* self = (OPLinkedList*) obj;
  return self->size == 0;
}

size_t    OPLinkedList_coll_size(OPObject* obj)
{
  OPLinkedList* self = (OPLinkedList*) obj;
  return self->size;
}

OPType    OPLinkedList_coll_type(OPObject* obj)
{
  OPLinkedList* self = (OPLinkedList*) obj;
  return self->type;
}

OPGeneric OPLinkedList_lst_get(OPObject* obj, size_t index)
{
  OPLinkedList* self = (OPLinkedList*) obj;
  op_assert(index < self->size, "Index out of bound error. Index: %ld, ListSize: %ld\n", index, self->size);
  OPObject* it = OPLinkedList_lst_listIteratorFrom(obj, index);
  OPGeneric item = li_next(it);
  free(it);
  return item;
}

size_t    OPLinkedList_lst_indexOf(OPObject* obj, OPGeneric element)
{
  OPLinkedList* self = (OPLinkedList*) obj;
  OPObject* it = OPLinkedList_lst_listIterator(obj);
  size_t ret = SIZE_T_MAX;
  size_t cnt = 0;
  while(li_hasNext(it))
    {
      OPGeneric item = li_next(it);
      if (item.obj == element.obj)
        {
          ret = cnt;
          break;
        }
      cnt++;
    }
  free(it);
  return ret;
}

size_t    OPLinkedList_lst_lastIndexOf(OPObject* obj, OPGeneric element)
{
  OPLinkedList* self = (OPLinkedList*) obj;
  OPObject* it = OPLinkedList_lst_listIterator(obj);
  size_t ret = SIZE_T_MAX;
  size_t cnt = 0;
  while(li_hasNext(it))
    {
      OPGeneric item = li_next(it);
      if (item.obj == element.obj)
        {
          ret = cnt;
        }
      cnt++;
    }
  free(it);
  return ret;
}

OPObject* OPLinkedList_lst_listIterator(OPObject* obj)
{
  OPLinkedList* self = (OPLinkedList*) obj;
  OPLinkedListIterator* it = malloc(sizeof(OPLinkedListIterator));
  OPLinkedListIterator_init_isa(it);
  it->container = self;
  it->type = self->type;
  it->next = self->head;
  it->prev = NULL;
  return (OPObject*)it;
}

OPObject* OPLinkedList_lst_listIteratorFrom(OPObject* obj, size_t index)
{
  OPLinkedList* self = (OPLinkedList*) obj;
  op_assert(index < self->size, "Index out of bound error. Index: %ld, ListSize: %ld\n", index, self->size);
  OPObject* it = OPLinkedList_lst_listIterator(obj);
  for (int i = 0; i < index; i++)
    {
      li_next(it);
    }
  return it;
}

void      OPLinkedList_mcoll_init(OPObject* obj, OPType type, PMMemoryManager* manager)
{
  OPLinkedList* self = (OPLinkedList*) obj;
  OPLinkedList_init_isa(self); // incase the isa wasn't initialized
  self->type = type;
  self->memory_manager = manager;
}

bool      OPLinkedList_mcoll_add(OPObject* obj, OPGeneric element)
{
  OPLinkedList* self = (OPLinkedList*) obj;
  self->size++;
  OPLinkedListNode* node = OPLinkedListNode_init_isa(
      PM_ALLOC(self->memory_manager, OPLinkedListNode));
  node->container = self;
  // TODO how do we handle the possible reference count?
  node->value = element;

  if (self->tail)
    {
      self->tail->next = node;
      node->prev = self->tail;
      self->tail = node;
    }
  else
    {
      self->head = self->tail = node;
    }
  return true;
}

bool      OPLinkedList_mcoll_addAll(OPObject* obj, OPObject* collection)
{
  // TODO crap.. I need to asure collection have iterator
  // If Iterator contains ListIterator, we need to manage reference
  // memory as well...
  // iter->dealloc() => iter->iter->dealloc?
  //
  // or simply forward the call to ListIterator...

}
void      OPLinkedList_mcoll_clear(OPObject* obj)
{
  // TODO how do I handle dealloc here?
}
bool      OPLinkedList_mcoll_removeIf(OPObject* obj, fp_predicate predicate)
{
  // TODO
  return false;
}
bool      OPLinkedList_mcoll_retainAll(OPObject* obj, OPObject* collection)
{
  // TODO
  return false;
}
bool      OPLinkedList_mlst_insert(OPObject* obj, size_t index, OPGeneric element)
{
  // TODO
  return false;
}
bool      OPLinkedList_mlst_insertAll(OPObject* obj, size_t index, OPObject* collection)
{
  // TODO
  return false;
}

OPGeneric OPLinkedList_mlst_remove(OPObject* obj, size_t index)
{
  // TODO
  OPGeneric ret;
  ret.obj = NULL;
  return ret;
}
OPGeneric OPLinkedList_mlst_removeAll(OPObject* obj, OPObject* collection)
{
  // TODO
  OPGeneric ret;
  ret.obj = NULL;
  return ret;
}
void      OPLinkedList_mlst_replaceAll(OPObject* obj, fp_unary map_func)
{
  // TODO
}
OPGeneric OPLinkedList_mlst_set(OPObject* obj, size_t index, OPGeneric element)
{
  // TODO
  OPGeneric ret;
  ret.obj = NULL;
  return ret;
}
void      OPLinkedList_mlst_sort(OPObject* obj, fp_comparator comparator)
{
  // TODO
}

OPObject* OPLinkedList_mlst_mutableListIterator(OPObject* obj)
{
  return OPLinkedList_lst_listIterator(obj);
}

OPObject* OPLinkedList_mlst_mutableListIteratorFrom(OPObject* obj, size_t index)
{
  return OPLinkedList_lst_listIteratorFrom(obj, index);
}

void      OPLinkedListIterator_li_forEachRemaining(OPObject* obj, fp_unary func, void* ctx)
{
  OPLinkedListIterator* self = (OPLinkedListIterator*) obj;
  while (li_hasNext(obj))
    {
      func(li_next(obj), self->type, ctx);
    }
}

bool      OPLinkedListIterator_li_hasNext(OPObject* obj)
{
  OPLinkedListIterator* self = (OPLinkedListIterator*) obj;
  return self->next != NULL;
}

bool      OPLinkedListIterator_li_hasPrevious(OPObject* obj)
{
  OPLinkedListIterator* self = (OPLinkedListIterator*) obj;
  return self->prev != NULL;
}

OPGeneric OPLinkedListIterator_li_next(OPObject* obj)
{
  OPLinkedListIterator* self = (OPLinkedListIterator*) obj;
  op_assert(self->next != NULL, "next should not be null\n");
  OPGeneric ret = self->next->value;
  self->prev = self->next->prev;
  self->next = self->next->next;
  return ret;
}

OPGeneric OPLinkedListIterator_li_previous(OPObject* obj)
{
  OPLinkedListIterator* self = (OPLinkedListIterator*) obj;
  op_assert(self->prev != NULL, "prev should not be null\n");
  OPGeneric ret = self->prev->value;
  self->prev = self->prev->prev;
  self->next = self->prev->next;
  return ret;
}

void      OPLinkedListIterator_mli_insert(OPObject* obj, OPGeneric element)
{
  // TODO
}
void      OPLinkedListIterator_mli_remove(OPObject* obj)
{
  // TODO
}
void      OPLinkedListIterator_mli_set(OPObject* obj, OPGeneric element)
{
  // TODO
}
