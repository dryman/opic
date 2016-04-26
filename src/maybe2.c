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

static (void)_Maybe_klass_init() {
  _Maybe_klass.traits = calloc(sizeof(void*), 2);
  TC_CLASS_ADD_TYPECLASS(_Maybe_klass, Monad, 0);
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

void my_fmap(void* _a, void**_b) {
  int* a = (int*) _a;
  int** b = (int**) _b;
  **b = *a +1;
}


int main(int argc, char** argv) {
  Maybe a = {};
  int x = 3;
  f_fmap((TCObject*)&maybe, (TCObject*)&maybe, &my_fmap);
  printf("%d\n",*(int*)a.data);
}

