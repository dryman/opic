#include <stdbool.h>
#include <stdlib.h>
#include "trait.h"
#include "maybe.h"

static void maybe_m_return(base_s* self, void* data);
static void maybe_m_bind(base_s* self, m_bind_callback cb, base_s* next);
static void maybe_f_fmap(base_s* self, base_s* next, f_fmap_callback cb);
static void maybe_a_pure(base_s* self, void* data);
static void maybe_a_ap(base_s* self, base_s* next);

static void init_maybe(maybe_s* self);
static inline bool is_nothing(maybe_s* self);

int data_marker = 0;

void just(maybe_s* self, void* data)
{
  if (!self->traits) init_maybe(self);
  self->maybe_e = MAYBE_JUST;
  self->data = data;
}

void nothing(maybe_s* self)
{
  if (!self->traits) init_maybe(self);
  self->maybe_e = MAYBE_NOTHING;
}


void maybe_m_return(base_s* _self, void* data)
{
  maybe_s* self = (maybe_s*) _self;
  self->maybe_e = MAYBE_JUST;
  self->data = data;
}

void maybe_m_bind(base_s* _self, m_bind_callback cb, base_s* _next)
{
  maybe_s* self = (maybe_s*) _self;
  maybe_s* next = (maybe_s*) _next;
  if (is_nothing(self) && self != next && !is_nothing(next)) {
    next->maybe_e = MAYBE_NOTHING;
    if (next->data > &data_marker) free(next->data);
    next->data = NULL;
    return;
  }
  cb(self->data, _next);
}

static void maybe_f_fmap(base_s* _self, base_s* _next, f_fmap_callback cb)
{
  maybe_s* self = (maybe_s*) _self;
  maybe_s* next = (maybe_s*) _next;
  if (is_nothing(self) && self != next && !is_nothing(next)) {
    next->maybe_e = MAYBE_NOTHING;
    if (next->data > &data_marker) free(next->data);
    next->data = NULL;
    return;
  }
  cb(self->data, &next->data);
}

static void maybe_a_pure(base_s* _self, void* data)
{
  maybe_s* self = (maybe_s*) _self;
  self->data = data;
}
  
static void maybe_a_ap(base_s* _self, base_s* _next)
{
  maybe_s* self = (maybe_s*) _self;
  maybe_s* next = (maybe_s*) _next;
  self->apply(self->data, &next->data);
}


static void init_maybe(maybe_s* self)
{
  self->traits = calloc(sizeof(void*),4);
  
  monad_s* monad = malloc(sizeof(monad_s));
  monad->trait_name = MONAD_TRAIT;
  monad->m_return = &maybe_m_return;
  monad->m_bind = &maybe_m_bind;
  monad->m_then = &default_m_then;
  self->traits[0] = (trait_s*) monad;

  functor_s* functor = malloc(sizeof(functor_s));
  functor->trait_name = FUNCTOR_TRAIT;
  functor->f_fmap = &maybe_f_fmap;
  self->traits[1] = (trait_s*) functor;

  applicative_s* applicative = malloc(sizeof(applicative_s));
  applicative->trait_name = APPLICATIVE_TRAIT;
  applicative->a_pure = &maybe_a_pure;
  applicative->a_ap = &maybe_a_ap;
  self->traits[2] = (trait_s*)applicative;

}

static inline bool is_nothing(maybe_s* self) 
{
  return self->maybe_e == MAYBE_NOTHING;
}
