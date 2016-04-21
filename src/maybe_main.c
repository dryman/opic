#include <stdio.h>
#include <stdlib.h>
#include "trait.h"
#include "maybe.h"

int main (int argc, char** argv) 
{
  maybe_s maybe = {};
  int x = 3;
  just(&maybe, &x);
  printf("just %d\n", *(int*)maybe.data);
  return 0;
}
  
