#include <stdbool.h>
#include <pthread.h>
#include <stdio.h>
#include "../include/typeclass.h"
#include "maybe.h"
#include "monad.h"
#include "functor.h"


TC_CLASS_INIT_FACTORY(Maybe,Monad,Functor,Applicative)

void just(Maybe* self, void* data) {
  Maybe_init(self);
  self->maybe_e = MAYBE_JUST;
  self->data = data;
}

void nothing(Maybe* self) {
  Maybe_init(self);
  self->maybe_e = MAYBE_NOTHING;
}

bool is_nothing(Maybe* self) 
{
  return self->maybe_e == MAYBE_NOTHING;
}


bool Maybe_m_return(TCObject* _self, void* data)
{
  Maybe* self = (Maybe*) _self;
  just(self, data);
  return true;
}

bool Maybe_m_bind(TCObject* _self, m_bind_callback cb, TCObject* _next)
{
  Maybe* self = (Maybe*) _self;
  Maybe* next = (Maybe*) _next;
  if (is_nothing(self) && self != next) {
    nothing(next);
    return true;
  }
  cb(self->data, _next);
  return true;
}

bool Maybe_m_then(TCObject* self, TCObject* next) {return 0;}

bool Maybe_f_fmap(TCObject* _self, TCObject* _next, f_fmap_callback cb)
{
  Maybe* self = (Maybe*) _self;
  Maybe* next = (Maybe*) _next;
  if (is_nothing(self) && self != next) {
    nothing(next);
    return true;
  }
  cb(self->data, &next->data);
}
  
bool Maybe_a_pure(TCObject* _self, void* data)
{
  Maybe* self = (Maybe*) _self;
  just(self, data);
  return true;
}

bool Maybe_a_ap(TCObject* _self, TCObject* _a, TCObject* _b)
{
  Maybe* self = (Maybe*) _self;
  Maybe_f_fmap(_a, _b, self->apply);
  return true;
}
