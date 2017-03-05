#include "objdef.h"
#include <stdio.h>
#include <inttypes.h>
#include "inline_aux.h"

int main()
{
  printf("size of USpan: %zu\n", sizeof(UnarySpan));
  printf("size of USpanQueue: %zu\n", sizeof(UnarySpanQueue));
  printf("sizeof(RawType): %zu\n", sizeof(RawType));
  return 0;
}
