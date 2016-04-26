#ifndef MONAD_H
#define MONAD_H 1

#include "typeclass.h"

// return :: a -> m a
// (>>=) :: m a -> (a -> m b) -> m b
// (>>) :: m a -> m b -> m b

#define MONAD_SIG "Monad"

typedef void (*m_bind_callback)(void*, Object*);
int m_return(void* data, Object* next);
int m_bind(Object* self, m_bind_callback cb, Object* next);
int m_then(Object* self, Object* next);

typedef struct Monad {
  struct Typeclass;
  void (*m_return)(void* data, Object* next);
  void (*m_bind)(Object* self, m_bind_callback cb, Object* next);
  void (*m_then)(Object* self, Object* next);
} Monad;

void default_m_then(base_s* self, Object* next);


#endif
