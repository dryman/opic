#ifndef FUNCTOR_H
#define FUNCTOR_H 1
#include "../src/opic.h"

OP_BEGIN_DECLS
// fmap :: (a -> b) -> f a -> f b
typedef void (*f_fmap_callback)(void* a, void** b);

#define Functor_OP_METHODS f_fmap
OP_DECLARE_METHOD(f_fmap, void, OPObject* self, OPObject* next, f_fmap_callback cb);
OP_DECLARE_TYPECLASS(Functor);

// pure :: a -> f a 
// (<*>) :: f (a -> b) -> f a -> f b
#define Applicative_OP_METHODS a_pure, a_ap
OP_DECLARE_METHOD(a_pure, void, OPObject* self, void* data);
OP_DECLARE_METHOD(a_ap, void, OPObject* self, OPObject* a, OPObject* b);
OP_DECLARE_TYPECLASS(Applicative);

OP_END_DECLS

#endif /* FUNCTOR_H */
