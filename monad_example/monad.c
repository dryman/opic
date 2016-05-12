#include "../include/typeclass.h"
#include "monad.h"

void m_return(TCObject* self, void* data)
{
  TC_TYPECLASS_METHOD_FACTORY(Monad, m_return, self->isa, self, data);
}

void m_bind(TCObject* self, m_bind_callback cb, TCObject* next)
{
  TC_TYPECLASS_METHOD_FACTORY(Monad, m_bind,  self->isa, self, cb, next);
}

void m_then(TCObject* self, TCObject* next)
{
  TC_TYPECLASS_METHOD_FACTORY(Monad, m_then, self->isa, self, next);
}

void default_m_then(TCObject* self, TCObject* next) {};
