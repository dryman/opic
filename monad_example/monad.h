#ifndef MONAD_H
#define MONAD_H 1

#include <stdbool.h>
#include "../include/tc_common_macros.h"
#include "../include/typeclass.h"

TC_BEGIN_DECLS

// return :: a -> m a
// (>>=) :: m a -> (a -> m b) -> m b
// (>>) :: m a -> m b -> m b

typedef void (*m_bind_callback)(void*, TCObject*);

#define Monad_TC_METHODS m_return, m_bind, m_then
TC_DECLARE_METHOD(m_return, TCObject* self, void* data);
TC_DECLARE_METHOD(m_bind, TCObject* self, m_bind_callback cb, TCObject* next);
TC_DECLARE_METHOD(m_then, TCObject* self, TCObject* next);
TC_DECLARE_TYPECLASS(Monad);

bool default_m_then(TCObject* self, TCObject* next);

TC_END_DECLS

#endif
