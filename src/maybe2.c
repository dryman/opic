#include <stdbool.h>
#include <pthread.h>
#include <stdio.h>
#include "typeclass.h"
#include "maybe2.h"

static pthread_once_t _Maybe_pthread_once = PTHREAD_ONCE_INIT;
static Class _Maybe_klass;
static void _Maybe_klass_init();

void Maybe_new(Maybe* self) {
  pthread_once( &_Maybe_pthread_once, &_Maybe_klass_init);
  self->isa = &_Maybe_klass;
}

static void _Maybe_klass_init() {
  _Maybe_klass.traits = calloc(sizeof(void*), 2);
  TC_CLASS_ADD_TYPECLASS(Maybe,_Maybe_klass, Monad, 0);
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

void my_bind(void* _a, TCObject*_b) {
  int* a = (int*) _a;
  Maybe* b = (Maybe*) _b;
  int* b_data = (int*)b->data;
  *b_data = *a + 1;
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

void Maybe_m_then(TCObject* self, TCObject* next) {
}

int main(int argc, char** argv) {
  Maybe a = {};
  int x = 3;
  just(&a,&x);
  m_bind((TCObject*)&a, &my_bind, (TCObject*)&a);
  printf("%d\n",*(int*)a.data);
}

