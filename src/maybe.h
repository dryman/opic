#ifndef MAYBE_H
#define MAYBE_H 1

#include <stdbool.h>
#include "trait.h"

enum maybe_e {
  MAYBE_JUST,
  MAYBE_NOTHING,
};

typedef struct maybe_s {
  struct base_s;
  enum maybe_e maybe_e;
  union {
    void* data;
    void (*apply)(void*, void**);
  };
} maybe_s;

void just(maybe_s* self, void* data);
void nothing(maybe_s* self);
bool is_nothing(maybe_s* self);
/* super bad macro, MUST CHANGE! */
#define print_maybe(self, format, type) \
  do { \
    if (is_nothing(&self)) { \
      printf("Nothing\n"); \
    } else {                                    \
      printf("Just " format "\n", *(type*)self.data); \
    } \
  } while (0)

#endif /* MAYBE_H */
