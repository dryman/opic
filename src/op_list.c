#include "op_list.h"


void li_forEachRemaining(OPObject* obj, fp_unary func, void* ctx)
{
  OP_TYPECLASS_METHOD_FACTORY(OPListIterator, li_forEachRemaining, obj->isa, obj, func, ctx);
}

bool li_hasNext(OPObject* obj)
{
  OP_TYPECLASS_METHOD_FACTORY(OPListIterator, li_hasNext, obj->isa, obj);
}

bool li_hasPrevious(OPObject* obj)
{
  OP_TYPECLASS_METHOD_FACTORY(OPListIterator, li_hasPrevious, obj->isa, obj);
}

OPGeneric li_next(OPObject* obj)
{
  OP_TYPECLASS_METHOD_FACTORY(OPListIterator, li_next, obj->isa, obj);
}

OPGeneric li_previous(OPObject* obj)
{
  OP_TYPECLASS_METHOD_FACTORY(OPListIterator, li_previous, obj->isa, obj);
}

/*
size_t li_nextIndex(OPObject* obj)
{
  OP_TYPECLASS_METHOD_FACTORY(OPListIterator, li_nextIndex, obj->isa, obj);
}

size_t li_previousIndex(OPObject* obj)
{
  OP_TYPECLASS_METHOD_FACTORY(OPListIterator, li_previousIndex, obj->isa, obj);
}
*/


void mli_insert(OPObject* obj, OPGeneric element)
{
  OP_TYPECLASS_METHOD_FACTORY(OPMutableListIterator, mli_insert, obj->isa, obj, element);
}

void mli_remove(OPObject* obj)
{
  OP_TYPECLASS_METHOD_FACTORY(OPMutableListIterator, mli_remove, obj->isa, obj);
}

void mli_set(OPObject* obj, OPGeneric element)
{
  OP_TYPECLASS_METHOD_FACTORY(OPMutableListIterator, mli_set, obj->isa, obj, element);
}


OPGeneric lst_get(OPObject* obj, size_t index)
{
  OP_TYPECLASS_METHOD_FACTORY(OPList, lst_get, obj->isa, obj, index);
}

size_t lst_indexOf(OPObject* obj, OPGeneric element)
{
  OP_TYPECLASS_METHOD_FACTORY(OPList, lst_indexOf, obj->isa, obj, element);
}

size_t lst_lastIndexOf(OPObject* obj, OPGeneric element)
{
  OP_TYPECLASS_METHOD_FACTORY(OPList, lst_lastIndexOf, obj->isa, obj, element);
}

OPObject* lst_listIterator(OPObject* obj)
{
  OP_TYPECLASS_METHOD_FACTORY(OPList, lst_listIterator, obj->isa, obj);
}

OPObject* lst_listIteratorFrom(OPObject* obj, size_t index)
{
  OP_TYPECLASS_METHOD_FACTORY(OPList, lst_listIteratorFrom, obj->isa, obj, index);
}


bool mlst_insert(OPObject* obj, size_t index, OPGeneric element)
{
  OP_TYPECLASS_METHOD_FACTORY(OPMutableList, mlst_insert, obj->isa, obj, index, element);
}

bool mlst_insertAll(OPObject* obj, size_t index, OPObject* collection)
{
  OP_TYPECLASS_METHOD_FACTORY(OPMutableList, mlst_insertAll, obj->isa, obj, index, collection);
}

OPGeneric mlst_remove(OPObject* obj, size_t index)
{
  OP_TYPECLASS_METHOD_FACTORY(OPMutableList, mlst_remove, obj->isa, obj, index);
}

OPGeneric mlst_removeAll(OPObject* obj, OPObject* collection)
{
  OP_TYPECLASS_METHOD_FACTORY(OPMutableList, mlst_removeAll, obj->isa, obj, collection);
}

void mlst_replaceAll(OPObject* obj, fp_unary map_func)
{
  OP_TYPECLASS_METHOD_FACTORY(OPMutableList, mlst_replaceAll, obj->isa, obj, map_func);
}

OPGeneric mlst_set(OPObject* obj, size_t index, OPGeneric element)
{
  OP_TYPECLASS_METHOD_FACTORY(OPMutableList, mlst_set, obj->isa, obj, index, element);
}

void mlst_sort(OPObject* obj, fp_comparator comparator)
{
  OP_TYPECLASS_METHOD_FACTORY(OPMutableList, mlst_replaceAll, obj->isa, obj, comparator);
}

OPObject* mlst_mutableListIterator(OPObject* obj)
{
  OP_TYPECLASS_METHOD_FACTORY(OPMutableList, mlst_mutableListIterator, obj->isa, obj);
}

OPObject* mlst_mutableListIteratorFrom(OPObject* obj, size_t index)
{
  OP_TYPECLASS_METHOD_FACTORY(OPMutableList, mlst_mutableListIteratorFrom, obj->isa, obj, index);
}
