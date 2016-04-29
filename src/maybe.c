#include <stdbool.h>
#include <pthread.h>
#include <stdio.h>
#include "typeclass.h"
#include "maybe.h"

static pthread_once_t _Maybe_pthread_once = PTHREAD_ONCE_INIT;
static Class _Maybe_klass;
static void _Maybe_klass_init();

void Maybe_new(Maybe* self) {
  pthread_once( &_Maybe_pthread_once, &_Maybe_klass_init);
  self->isa = &_Maybe_klass;
}

static void _Maybe_klass_init() {
  _Maybe_klass.traits = calloc(sizeof(void*), 4);
  TC_CLASS_ADD_TYPECLASS(Maybe,_Maybe_klass, Monad, 0);
  TC_CLASS_ADD_TYPECLASS(Maybe,_Maybe_klass, Functor, 1);
  TC_CLASS_ADD_TYPECLASS(Maybe,_Maybe_klass, Applicative, 2);
}

void just(Maybe* self, void* data) {
  Maybe_new(self);
  self->maybe_e = MAYBE_JUST;
  self->data = data;
}

void nothing(Maybe* self) {
  Maybe_new(self);
  self->maybe_e = MAYBE_NOTHING;
}

bool is_nothing(Maybe* self) 
{
  return self->maybe_e == MAYBE_NOTHING;
}


void Maybe_m_return(TCObject* _self, void* data)
{
  Maybe* self = (Maybe*) _self;
  self->maybe_e = MAYBE_JUST;
  self->data = data;
}

void Maybe_m_bind(TCObject* _self, m_bind_callback cb, TCObject* _next)
{
  Maybe* self = (Maybe*) _self;
  Maybe* next = (Maybe*) _next;
  if (is_nothing(self) && self != next) {
    nothing(next);
    return;
  }
  cb(self->data, _next);
}

void Maybe_m_then(TCObject* self, TCObject* next) { }

void Maybe_f_fmap(TCObject* _self, TCObject* _next, f_fmap_callback cb)
{
  Maybe* self = (Maybe*) _self;
  Maybe* next = (Maybe*) _next;
  if (is_nothing(self) && self != next) {
    nothing(next);
    return;
  }
  cb(self->data, &next->data);
}
  
void Maybe_a_pure(TCObject* _self, void* data)
{
  Maybe* self = (Maybe*) _self;
  self->data = data;
}

void Maybe_a_ap(TCObject* _self, TCObject* _a, TCObject* _b)
{
  Maybe* self = (Maybe*) _self;
  Maybe_f_fmap(_a, _b, self->apply);
}
