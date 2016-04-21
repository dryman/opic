#include <stdio.h>
#include <stdlib.h>
#include "trait.h"
#include "maybe.h"

void my_fmap(void* _a, void**_b) {
  int* a = (int*) _a;
  int** b = (int**) _b;
  **b = *a +1;
}

int main (int argc, char** argv) 
{
  maybe_s maybe = {};
  int x = 3;
  just(&maybe, &x);
  f_fmap((base_s*)&maybe, (base_s*)&maybe, &my_fmap); 
  
  printf("just %d\n", *(int*)maybe.data);
  return 0;
}
  
