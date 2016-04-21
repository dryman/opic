#include <stdlib.h>
#include <string.h>
#include "trait.h"

#define TRAIT_FACTORY(trait_type, trait_str, trait_func, ...)           \
  trait_s** trait = self->traits;                                       \
  while(trait) {                                                        \
    if (!strcmp((*trait)->trait_name, trait_str)) {                     \
      trait_type* instance = *(trait_type**) trait;                     \
      instance->trait_func( __VA_ARGS__ );                              \
      return TRAIT_SUCCESS;                                             \
    } else {                                                            \
      trait++;                                                          \
    }                                                                   \
    return TRAIT_NOT_FOUND;                                             \
  }                                                                   



#define MONAD_FACTORY(trait_func, ...) \
  TRAIT_FACTORY(monad_s, MONAD_TRAIT, trait_func, __VA_ARGS__ )

#define FUNCTOR_FACTORY(trait_func, ...) \
  TRAIT_FACTORY(functor_s, FUNCTOR_TRAIT, trait_func, __VA_ARGS__ )

#define APPLICATIVE_FACTORY(trait_func, ...) \
  TRAIT_FACTORY(applicative_s, APPLICATIVE_TRAIT, trait_func, __VA_ARGS__ )

int m_return(base_s* self, void* data) {
  MONAD_FACTORY(m_return, self, data);
}

int m_bind(base_s* self, m_bind_callback cb, base_s* next) {
  MONAD_FACTORY(m_bind, self, cb, next);
}

int m_then(base_s* self, base_s* next) {
  MONAD_FACTORY(m_then, self, next);
}

void default_m_then(base_s* self, base_s* next) {
  return;
}

int f_fmap(base_s* self, base_s* next, f_fmap_callback cb) {
  FUNCTOR_FACTORY(f_fmap, self, next, cb);
}

int a_pure(base_s* self, void* data) {
  APPLICATIVE_FACTORY(a_pure, self, data);
}

int a_ap(base_s* self, base_s* next) {
  APPLICATIVE_FACTORY(a_ap, self, next);
}
