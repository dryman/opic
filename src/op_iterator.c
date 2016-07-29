#include "op_iterator.h"


void it_forEachRemaining(OPObject* obj, fp_unary func, void* ctx)
{
  OP_TYPECLASS_METHOD_FACTORY(OPIterator, it_forEachRemaining, obj->isa, obj, func, ctx);
}

bool it_hasNext(OPObject* obj)
{
  OP_TYPECLASS_METHOD_FACTORY(OPIterator, it_hasNext, obj->isa, obj);
}

void* it_next(OPObject* obj)
{
  OP_TYPECLASS_METHOD_FACTORY(OPIterator, it_next, obj->isa, obj);
}

void it_remove(OPObject* obj)
{
  OP_TYPECLASS_METHOD_FACTORY(OPIterator, it_remove, obj->isa, obj);
}

OPType it_type(OPObject* obj)
{
  OP_TYPECLASS_METHOD_FACTORY(OPIterator, it_type, obj->isa, obj);
}

void ib_forEach(OPObject* obj, fp_unary func, void* ctx)
{
  OP_TYPECLASS_METHOD_FACTORY(OPIterable, ib_forEach, obj->isa, obj, func, ctx);
}

OPObject* ib_iterator(OPObject* obj)
{
  OP_TYPECLASS_METHOD_FACTORY(OPIterable, ib_iterator, obj->isa, obj);
}

OPType ib_type(OPObject* obj)
{
  OP_TYPECLASS_METHOD_FACTORY(OPIterable, ib_type, obj->isa, obj);
}
