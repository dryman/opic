#ifndef MAYBE_H
#define MAYBE_H 1

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

#endif /* MAYBE_H */
