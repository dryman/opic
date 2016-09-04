#ifndef OP_ITERATOR_H
#define OP_ITERATOR_H 1
#include <stdbool.h>
#include "opic.h"
#include "op_functional.h"

OP_BEGIN_DECLS

#define OPIterator_OP_METHODS it_forEachRemaining, it_hasNext, \
  it_next, it_type
OP_DECLARE_METHOD(it_forEachRemaining, void, OPObject* obj, fp_unary func, void* ctx);
OP_DECLARE_METHOD(it_hasNext,          bool, OPObject* obj);
OP_DECLARE_METHOD(it_next,        OPGeneric, OPObject* obj);
OP_DECLARE_METHOD(it_type,           OPType, OPObject* obj);
OP_DECLARE_TYPECLASS(OPIterator);

#define OPMutableIterator_OP_METHODS mit_remove
OP_DECLARE_METHOD(mit_remove,          void, OPObject* obj);
OP_DECLARE_TYPECLASS(OPMutableIterator);

#define OPIterable_OP_METHODS ib_forEach, ib_iterator, ib_type
OP_DECLARE_METHOD(ib_forEach,          void, OPObject* obj, fp_unary func, void* ctx);
OP_DECLARE_METHOD(ib_iterator,    OPObject*, OPObject* obj);
OP_DECLARE_METHOD(ib_type,           OPType, OPObject* obj);
OP_DECLARE_TYPECLASS(OPIterable);

OP_END_DECLS
#endif /* OP_ITERATOR_H */
