#include <stdbool.h>
#include <stdio.h>
#include "typeclass.h"
#include "maybe.h"

static void my_bind(void* _a, TCObject*_b) {
  int* a = (int*) _a;
  Maybe* b = (Maybe*) _b;
  int* b_data = (int*)b->data;
  *b_data = *a + 1;
}

int main(int argc, char** argv) {
  Maybe a = {};
  int x = 3;
  just(&a,&x);
  m_bind((TCObject*)&a, &my_bind, (TCObject*)&a);
  m_bind((TCObject*)&a, &my_bind, (TCObject*)&a);
  m_bind((TCObject*)&a, &my_bind, (TCObject*)&a);
  printf("%d\n",*(int*)a.data);
}
