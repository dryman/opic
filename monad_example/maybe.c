#include <stdbool.h>
#include <pthread.h>
#include <stdio.h>
#include "maybe.h"
#include "monad.h"
#include "functor.h"

OP_DEFINE_ISA_WITH_TYPECLASSES(Maybe,Monad,Functor,Applicative)

void just(Maybe* self, void* data) {
  /* Maybe_init_isa(self); */
  self->maybe_e = MAYBE_JUST;
  self->data = data;
}

void nothing(Maybe* self) {
  /* Maybe_init_isa(self); */
  self->maybe_e = MAYBE_NOTHING;
}

bool is_nothing(Maybe* self) 
{
  return self->maybe_e == MAYBE_NOTHING;
}


void Maybe_m_return(OPObject* _self, void* data)
{
  Maybe* self = (Maybe*) _self;
  just(self, data);
}

void Maybe_m_bind(OPObject* _self, m_bind_callback cb, OPObject* _next)
{
  Maybe* self = (Maybe*) _self;
  Maybe* next = (Maybe*) _next;
  if (is_nothing(self) && self != next) {
    nothing(next);
  }
  cb(self->data, _next);
}

void Maybe_m_then(OPObject* self, OPObject* next) {}

void Maybe_f_fmap(OPObject* _self, OPObject* _next, f_fmap_callback cb)
{
  Maybe* self = (Maybe*) _self;
  Maybe* next = (Maybe*) _next;
  if (is_nothing(self) && self != next) {
    nothing(next);
  }
  cb(self->data, &next->data);
}
  
void Maybe_a_pure(OPObject* _self, void* data)
{
  Maybe* self = (Maybe*) _self;
  just(self, data);
}

void Maybe_a_ap(OPObject* _self, OPObject* _a, OPObject* _b)
{
  Maybe* self = (Maybe*) _self;
  Maybe_f_fmap(_a, _b, self->apply);
}
