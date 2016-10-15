#include <stdlib.h>
#include <limits.h>
#include "config.h"
#include "op_linked_list.h"

/* Max integer that can be stored in a size_t object. */
#ifndef SIZE_T_MAX
#define SIZE_T_MAX UINT_MAX
#endif /* !SIZE_T_MAX */

// Last bit in ISA pointer denotes it is mutable or not
struct OPLinkedList
{
  struct OPObject base;
  OPType type;
  size_t size;
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
  OPLinkedListNode* last;
  OPLinkedList* container;
};

OP_DEFINE_ISA_WITH_TYPECLASSES(OPLinkedListNode, OPObjectBase, OPSerializable)
OP_DEFINE_ISA_WITH_TYPECLASSES(OPLinkedList, OPObjectBase, OPSerializable,
                               OPCollection, OPMutableCollection,
                               OPList, OPMutableList)
OP_DEFINE_ISA_WITH_TYPECLASSES(OPLinkedListIterator, OPIterator, OPMutableIterator,
                               OPListIterator, OPMutableListIterator)

void OPLinkedListNode_op_dealloc(void* obj)
{
  OPLinkedListNode* self = (OPLinkedListNode*) obj;
  if (self->container->type == op_object)
    {
      OPRelease(self->value.obj);
    }
  if (self->next)
    {
      OPRelease(self->next);
    }
}

void OPLinkedListNode_serde_serialize(OPObject* obj, OPMallocManager* ctx)
{
  OPLinkedListNode* self = (OPLinkedListNode*) obj;

  self->next = self->next ?  OPPtr2Ref(ctx, self->next) : (void*)~0L;
  self->prev = self->prev ?  OPPtr2Ref(ctx, self->prev) : (void*)~0L;

  if (self->container->type == op_object)
    self->value.obj = OPPtr2Ref(ctx, self->value.obj);
  self->container = OPPtr2Ref(ctx, self->container);
}

void OPLinkedListNode_serde_deserialize(OPObject* obj, OPMallocManager* ctx)
{
  OPLinkedListNode* self = (OPLinkedListNode*) obj;
  // TODO if the pointer were ~0L, restore as null, else call deref
  self->next = (size_t)self->next == ~0L? 
    NULL:
    OPRef2Ptr(ctx, self->next);
  self->prev = (size_t)self->prev == ~0L? 
    NULL:
    OPRef2Ptr(ctx, self->prev);

  self->container = OPRef2Ptr(ctx, self->container);
  if (self->container->type == op_object)
    self->value.obj = OPRef2Ptr(ctx, self->value.obj);
}

void OPLinkedList_serde_serialize(OPObject* obj, OPMallocManager* ctx)
{
  OPLinkedList* self = (OPLinkedList*) obj;
  if (self->head)
    {
      self->head = OPPtr2Ref(ctx, self->head);
      self->tail = OPPtr2Ref(ctx, self->tail);
    }
  else
    {
      self->head = (void*)~0L;
      self->tail = (void*)~0L;
    }
}

void OPLinkedList_op_dealloc(void* obj)
{
  OPLinkedList* self = (OPLinkedList*) obj;
  if (self->head)
    {
      OPRelease(self->head);
    }
}

void OPLinkedList_serde_deserialize(OPObject* obj, OPMallocManager* ctx)
{
  OPLinkedList* self = (OPLinkedList*) obj;
  if ((size_t)self->head == ~0L)
    {
      self->head = NULL;
      self->tail = NULL;
    }
  else
    {
      self->head = OPRef2Ptr(ctx, self->head);
      self->tail = OPRef2Ptr(ctx, self->tail);
    }
}

bool      OPLinkedList_coll_contains(OPObject* obj, OPGeneric element)
{
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

OPObject* OPLinkedList_coll_iterator(OPObject* obj)
{
  return OPLinkedList_lst_listIterator(obj);
}

OPGeneric OPLinkedList_lst_get(OPObject* obj, size_t index)
{
  OPLinkedList* self = (OPLinkedList*) obj;
  op_assert(index < self->size, "Index out of bound error. Index: %ld, ListSize: %ld\n", index, self->size);
  OPObject* it = OPLinkedList_lst_listIteratorFrom(obj, index);
  OPGeneric item = li_next(it);
  OPRelease(it);
  return item;
}

size_t    OPLinkedList_lst_indexOf(OPObject* obj, OPGeneric element)
{
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
  OPRelease(it);
  return ret;
}

size_t    OPLinkedList_lst_lastIndexOf(OPObject* obj, OPGeneric element)
{
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
  OPRelease(it);
  return ret;
}

OPObject* OPLinkedList_lst_listIterator(OPObject* obj)
{
  OPLinkedList* self = (OPLinkedList*) obj;
  OPLinkedListIterator* it = OP_MALLOC(self->base.manager, OPLinkedListIterator);
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

void      OPLinkedList_mcoll_init(OPObject* obj, OPType type)
{
  OPLinkedList* self = (OPLinkedList*) obj;
  self->type = type;
}

bool      OPLinkedList_mcoll_add(OPObject* obj, OPGeneric element)
{
  OPLinkedList* self = (OPLinkedList*) obj;
  self->size++;
  OPLinkedListNode* node = OP_MALLOC(self->base.manager, OPLinkedListNode);
  node->container = self;
  node->value = element;
  if (self->type == op_object)
    {
      OPRetain(node->value.obj);
    }

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
  OPLinkedList* self = (OPLinkedList*) obj;
  if (!tc_instance_of(collection, "OPCollection")) 
    {
      // log error
      return false;
    }
  if (coll_type(collection) != self->type)
    {
      // log error
      return false;
    }
  
  OPObject* it = coll_iterator(collection);

  while (it_hasNext(it))
    {
      mcoll_add(obj, it_next(it));
    }
  OPRelease(it);
  return true;
}

void      OPLinkedList_mcoll_clear(OPObject* obj)
{
  OPLinkedList* self = (OPLinkedList*) obj;
  if (self->head) 
    {
      OPRelease(self->head);
      self->head = self->tail = NULL;
      self->size = 0;
    }
}

/*
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
*/

bool      OPLinkedList_mlst_insert(OPObject* obj, size_t index, OPGeneric element)
{
  OPObject* it = mlst_mutableListIteratorFrom(obj, index);
  mli_insert(it, element);
  OPRelease(it);
  return true;
}

bool      OPLinkedList_mlst_insertAll(OPObject* obj, size_t index, OPObject* collection)
{
  OPLinkedList* self = (OPLinkedList*) obj;
  if (!tc_instance_of(collection, "OPCollection")) 
    {
      // TODO log error
      return false;
    }
  if (coll_type(collection) != self->type)
    {
      // TODO log error
      return false;
    }
  OPObject* self_it = mlst_mutableListIteratorFrom(obj, index);
  OPObject* other_it = coll_iterator(collection);

  while (it_hasNext(other_it))
    {
      mli_insert(self_it, it_next(other_it));
      it_next(self_it);
    }
  return false;
}

OPGeneric OPLinkedList_mlst_remove(OPObject* obj, size_t index)
{
  OPObject* it = mlst_mutableListIteratorFrom(obj, index);
  OPGeneric value = li_next(it);
  mli_remove(it);
  OPRelease(it);
  return value;
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

void      OPLinkedListIterator_it_forEachRemaining(OPObject* obj, fp_unary func, void* ctx)
{
  OPLinkedListIterator_li_forEachRemaining(obj, func, ctx);
}

bool      OPLinkedListIterator_it_hasNext(OPObject* obj)
{
  return OPLinkedListIterator_li_hasNext(obj);
}

OPGeneric OPLinkedListIterator_it_next(OPObject* obj)
{
  return OPLinkedListIterator_li_next(obj);
}

void      OPLinkedListIterator_mit_remove(OPObject* obj)
{
  OPLinkedListIterator_mli_remove(obj);
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
  self->last = self->next;
  self->prev = self->next->prev;
  self->next = self->next->next;
  return self->last->value;
}

OPGeneric OPLinkedListIterator_li_previous(OPObject* obj)
{
  OPLinkedListIterator* self = (OPLinkedListIterator*) obj;
  op_assert(self->prev != NULL, "prev should not be null\n");
  self->last = self->prev;
  self->prev = self->prev->prev;
  self->next = self->prev->next;
  return self->last->value;
}

bool    OPLinkedListIterator_mli_insert(OPObject* obj, OPGeneric element)
{
  OPLinkedListIterator* self = (OPLinkedListIterator*) obj;

  OPLinkedListNode* new_node = OP_MALLOC(self->base.manager, OPLinkedListNode);
  new_node->container = self->container;
  new_node->value = element;
  if (self->container->type == op_object)
    {
      OPRetain(element.obj);
    }

  new_node->next = self->next;
  new_node->prev = self->prev;
  
  if (self->next)
    {
      self->next->prev = new_node;
    }
  else
    {
      self->container->tail = new_node;
    }
  
  if (self->prev)
    {
      self->prev->next = new_node;
      self->prev = new_node;
    }
  else
    {
      self->container->head = new_node;
    }
  
  self->container->size++;
  return true;
}

void   OPLinkedListIterator_mli_remove(OPObject* obj)
{
  OPLinkedListIterator* self = (OPLinkedListIterator*) obj;

  op_assert(self->last, "mli_remove can only be invoked after li_next"
            "or li_previous\n");
  if (!self->last) return;

  OPLinkedListNode* node = self->last;
  self->next = node->next;
  self->prev = node->prev;
  self->last = NULL;
  
  if (self->next)
    {
      self->next->prev = self->prev;
    }
  else
    {
      self->container->tail = self->prev;
    }

  if (self->prev)
    {
      self->prev->next = self->next;
    }
  else
    {
      self->container->head = self->next;
    }
  
  self->container->size--;
  OPGeneric value = node->value;
  if (self->container->type == op_object)
    {
      OPRelease(value.obj);
    }
  
  node->next = NULL;
  node->prev = NULL;
  OPRelease(node);
}

void      OPLinkedListIterator_mli_set(OPObject* obj, OPGeneric element)
{
  OPLinkedListIterator* self = (OPLinkedListIterator*) obj;

  op_assert(self->last, "mli_set can only be invoked after li_next"
            "or li_previous\n");

  OPLinkedListNode* node = self->last;

  if (self->container->type == op_object &&
      node->value.obj != element.obj)
    {
      OPRelease(node->value.obj);
      OPRetain(element.obj);
    }
  
  node->value = element;
}
