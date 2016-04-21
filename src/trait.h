#ifndef TRAIT_H
#define TRAIT_H 1

typedef struct trait_s {
  const char* trait_name;
} trait_s;

typedef struct base_s {
  trait_s** traits;
} base_s;

#define MONAD_TRAIT "monad"
#define FUNCTOR_TRAIT "functor"
#define APPLICATIVE_TRAIT "applicative"

#define TRAIT_SUCCESS 0
#define TRAIT_NOT_FOUND 1

// return :: a -> m a
// (>>=) :: m a -> (a -> m b) -> m b
// (>>) :: m a -> m b -> m b

typedef void (*m_bind_callback)(void*, base_s*);
int m_return(base_s* self, void* data);
int m_bind(base_s* self, m_bind_callback cb, base_s* next);
int m_then(base_s* self, base_s* next);

typedef struct monad_s {
  struct trait_s;
  void (*m_return)(base_s* self, void* data);
  void (*m_bind)(base_s* self, m_bind_callback cb, base_s* next);
  void (*m_then)(base_s* self, base_s* next); // would discard the value of self
} monad_s;

void default_m_then(base_s* self, base_s* next);


// fmap :: (a -> b) -> f a -> f b
typedef void (*f_fmap_callback)(void* a, void** b);

int f_fmap(base_s* self, base_s* next, f_fmap_callback cb);

typedef struct functor_s {
  struct trait_s;
  void (*f_fmap)(base_s* self, base_s* next, f_fmap_callback cb);
} functor_s;

// pure :: a -> f a 
// (<*>) :: f (a -> b) -> f a -> f b
int a_pure(base_s* self, void* data);
int a_ap(base_s* self, base_s* a, base_s* b);

typedef struct applicative_s {
  struct trait_s;
  void (*a_pure)(base_s* self, void* data);
  void (*a_ap)(base_s* self, base_s* a, base_s* b);
} applicative_s;


#endif /* TRAIT_H */
