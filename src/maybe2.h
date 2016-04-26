#ifndef MAYBE2_H
#define MAYBE2_H 1

#include "typeclass.h"

#ifdef __cplusplus
extern "C" {
#endif


enum maybe_e {
  MAYBE_JUST,
  MAYBE_NOTHING,
};

typedef struct Maybe {
  struct TCObject;
  enum maybe_e maybe_e;
  union {
    void* data;
    void (*apply)(void*, void**);
  };
} Maybe;

void Maybe_new(Maybe* self);


#ifdef __cplusplus
}
#endif

#endif /* MAYBE2_H */
