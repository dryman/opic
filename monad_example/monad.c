#include <stdbool.h>
#include "monad.h"

void m_return(OPObject* self, void* data)
{
  OP_TYPECLASS_METHOD_FACTORY(Monad, m_return, self->isa, self, data);
}

void m_bind(OPObject* self, m_bind_callback cb, OPObject* next)
{
  OP_TYPECLASS_METHOD_FACTORY(Monad, m_bind,  self->isa, self, cb, next);
}

void m_then(OPObject* self, OPObject* next)
{
  OP_TYPECLASS_METHOD_FACTORY(Monad, m_then, self->isa, self, next);
}

void default_m_then(OPObject* self, OPObject* next) {}
