#ifndef OP_ITERATOR_H
#define OP_ITERATOR_H 1
#include <stdbool.h>
#include "op_macros.h"
#include "op_trait.h"
#include "op_functional.h"

OP_BEGIN_DECLS

#define OPIterator_OP_METHODS it_forEachRemaining, it_hasNext, \
  it_next, it_remove, it_type
OP_DECLARE_METHOD(it_forEachRemaining, void, fp_unary func, void* ctx);
OP_DECLARE_METHOD(it_hasNext, bool, void);
OP_DECLARE_METHOD(it_next, void*, void);
OP_DECLARE_METHOD(it_remove, void, void);
OP_DECLARE_METHOD(it_type, OPType, void);

#define OPIterable_OP_METHODS ib_forEach, ib_iterator, ib_type
OP_DECLARE_METHOD(ib_forEach, void, fp_unary func, void* ctx);
OP_DECLARE_METHOD(ib_iterator, OPObject*, void);
OP_DECLARE_TYPECLASS(OPIterable);

OP_END_DECLS
#endif /* OP_ITERATOR_H */
