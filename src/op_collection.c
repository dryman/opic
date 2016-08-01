#include "op_collection.h"


bool coll_contains(OPObject* obj, OPGeneric element)
{
  OP_TYPECLASS_METHOD_FACTORY(OPCollection, coll_contains, obj->isa, obj, element);
}

bool coll_containsAll(OPObject* obj, OPObject* collection)
{
  OP_TYPECLASS_METHOD_FACTORY(OPCollection, coll_containsAll, obj->isa, obj, collection);
}

bool coll_isEmpty(OPObject* obj)
{
  OP_TYPECLASS_METHOD_FACTORY(OPCollection, coll_isEmpty, obj->isa, obj);
}

size_t coll_size(OPObject* obj)
{
  OP_TYPECLASS_METHOD_FACTORY(OPCollection, coll_size, obj->isa, obj);
}

OPTYpe coll_type(OPObject* obj)
{
  OP_TYPECLASS_METHOD_FACTORY(OPCollection, coll_contains, obj->isa, obj);
}


void mcoll_initWithType(OPObject* obj, OPType type)
{
  OP_TYPECLASS_METHOD_FACTORY(OPMutableCollection, mcoll_initWithType, obj->isa, obj, type);
}

bool mcoll_add(OPObject* obj, OPGeneric element)
{
  OP_TYPECLASS_METHOD_FACTORY(OPMutableCollection, mcoll_add, obj->isa, obj, element);
}

bool mcoll_addAll(OPObject* obj, OPObject* collection)
{
  OP_TYPECLASS_METHOD_FACTORY(OPMutableCollection, mcoll_addAll, obj->isa, obj, collection);
}

void mcoll_clear(OPObject* obj)
{
  OP_TYPECLASS_METHOD_FACTORY(OPMutableCollection, mcoll_clear, obj->isa, obj);
}

bool mcoll_removeIf(OPObject* obj, fp_predicate predicate)
{
  OP_TYPECLASS_METHOD_FACTORY(OPMutableCollection, mcoll_removeIf, obj->isa, obj, predicate);
}

bool mcoll_retainAll(OPObject* obj, OPObject* collection)
{
  OP_TYPECLASS_METHOD_FACTORY(OPMutableCollection, mcoll_retainAll, obj->isa, obj, collection);
}

