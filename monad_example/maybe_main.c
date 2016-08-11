#include <stdbool.h>
#include <stdio.h>
#include "monad.h"
#include "functor.h"
#include "maybe.h"

static void my_bind(void* _a, OPObject*_b) {
  int* a = (int*) _a;
  Maybe* b = (Maybe*) _b;
  int* b_data = (int*)b->data;
  *b_data = *a + 1;
}

void my_fmap(void* _a, void**_b) {
  int* a = (int*) _a;
  int** b = (int**) _b;
  **b = *a +1;
}

int main(int argc, char** argv) {
  Maybe a = {};
  int x = 3;
  just(&a,&x);
  Maybe b = {};
  m_bind((OPObject*)&a, &my_bind, (OPObject*)&a);
  m_bind((OPObject*)&a, &my_bind, (OPObject*)&a);
  m_bind((OPObject*)&a, &my_bind, (OPObject*)&a);
  f_fmap((OPObject*)&a, (OPObject*)&a, &my_fmap);
  f_fmap((OPObject*)&a, (OPObject*)&a, &my_fmap);
  f_fmap((OPObject*)&a, (OPObject*)&a, &my_fmap);
  printf("%d\n",*(int*)a.data);
  printf("sizeof object: %lu, getting size from klass: %zu\n", sizeof(a), a.base.isa->size);
}
