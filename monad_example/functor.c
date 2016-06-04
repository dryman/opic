#include <stdbool.h>
#include "functor.h"

void f_fmap(OPObject* self, OPObject* next, f_fmap_callback cb)
{
  OP_TYPECLASS_METHOD_FACTORY(Functor, f_fmap, self->isa, self, next, cb);
}

void a_pure(OPObject* self, void* data)
{
  OP_TYPECLASS_METHOD_FACTORY(Applicative, a_pure, self->isa, self, data);
}

void a_ap(OPObject* self, OPObject* a, OPObject* b)
{
  OP_TYPECLASS_METHOD_FACTORY(Applicative, a_ap, self->isa, self, a, b);
}
