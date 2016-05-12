#ifndef FUNCTOR_H
#define FUNCTOR_H 1
#include "../include/tc_common_macros.h"
#include "../include/typeclass.h"

TC_BEGIN_DECLS
// fmap :: (a -> b) -> f a -> f b
typedef void (*f_fmap_callback)(void* a, void** b);

#define Functor_TC_METHODS f_fmap
TC_DECLARE_METHOD(f_fmap, TCObject* self, TCObject* next, f_fmap_callback cb);
TC_DECLARE_TYPECLASS(Functor);

// pure :: a -> f a 
// (<*>) :: f (a -> b) -> f a -> f b
#define Applicative_TC_METHODS a_pure, a_ap
TC_DECLARE_METHOD(a_pure, TCObject* self, void* data);
TC_DECLARE_METHOD(a_ap, TCObject* self, TCObject* a, TCObject* b);
TC_DECLARE_TYPECLASS(Applicative);

TC_END_DECLS

#endif /* FUNCTOR_H */
