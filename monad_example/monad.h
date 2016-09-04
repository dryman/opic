#ifndef MONAD_H
#define MONAD_H 1

#include <stdbool.h>
#include "../src/opic.h"

OP_BEGIN_DECLS

// return :: a -> m a
// (>>=) :: m a -> (a -> m b) -> m b
// (>>) :: m a -> m b -> m b

typedef void (*m_bind_callback)(void*, OPObject*);

#define Monad_OP_METHODS m_return, m_bind, m_then
OP_DECLARE_METHOD(m_return, void, OPObject* self, void* data);
OP_DECLARE_METHOD(m_bind, void, OPObject* self, m_bind_callback cb, OPObject* next);
OP_DECLARE_METHOD(m_then, void, OPObject* self, OPObject* next);
OP_DECLARE_TYPECLASS(Monad);

void default_m_then(OPObject* self, OPObject* next);

OP_END_DECLS

#endif
