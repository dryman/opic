
#include <stdio.h>
#include "tc_assert.h"

void my_diag(int a) {
  fprintf(stderr, "a is %d\n", a);
}

int main(int argc, char** argv) {
  //tc_assert(0,"assert test %d",0);
  //tc_assert(0,"Intended assert failure");
  tc_assert_diagnose(0,my_diag,3);
  return 0;
}
