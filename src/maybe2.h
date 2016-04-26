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

void Maybe_m_return(TCObject* _self, void* data);
void Maybe_m_bind(TCObject* _self, m_bind_callback cb, TCObject* _next);
void Maybe_m_then(TCObject* self, TCObject* next);

#ifdef __cplusplus
}
#endif

#endif /* MAYBE2_H */
