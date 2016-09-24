#ifndef MAYBE_H
#define MAYBE_H 1

#include <stdbool.h>
#include "../src/opic.h"
#include "monad.h"
#include "functor.h"

OP_BEGIN_DECLS

enum maybe_e {
  MAYBE_JUST,
  MAYBE_NOTHING,
};

typedef struct Maybe {
  struct OPObject base;
  enum maybe_e maybe_e;
  union {
    void* data;
    void (*apply)(void*, void**);
  };
} Maybe;

void just(Maybe* self, void* data);
void nothing(Maybe* self);

void Maybe_m_return(OPObject* _self, void* data);
void Maybe_m_bind(OPObject* _self, m_bind_callback cb, OPObject* _next);
void Maybe_m_then(OPObject* self, OPObject* next);
void Maybe_f_fmap(OPObject* self, OPObject* next, f_fmap_callback cb);
void Maybe_a_pure(OPObject* self, void* data);
void Maybe_a_ap(OPObject* self, OPObject* a, OPObject* b);

OP_END_DECLS

#endif /* MAYBE_H */
