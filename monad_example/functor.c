#include "../include/typeclass.h"
#include <stdbool.h>
#include "functor.h"

bool f_fmap(TCObject* self, TCObject* next, f_fmap_callback cb)
{
  TC_TYPECLASS_METHOD_FACTORY(Functor, f_fmap, self->isa, self, next, cb);
}

bool a_pure(TCObject* self, void* data)
{
  TC_TYPECLASS_METHOD_FACTORY(Applicative, a_pure, self->isa, self, data);
}

bool a_ap(TCObject* self, TCObject* a, TCObject* b)
{
  TC_TYPECLASS_METHOD_FACTORY(Applicative, a_ap, self->isa, self, a, b);
}
