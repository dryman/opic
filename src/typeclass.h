#ifndef TYPECLASS_H
#define TYPECLASS_H

#include <pthread.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct TypeClass
{
  const char* name;
} TypeClass;

// TODO: find good way to implement super
// two possible ways:
// 1. anonymous embeded super
//    Hard to handle traits (reuse, overwrite, ...)
// 2. pointer to supers (traverse pointers may take time..)
// Hakell type doesn't seems to have inheritance?
// Maybe we don't need it at all
typedef struct Class
{
  TypeClass** traits;
  // methods should be struct extending class
} Class;

typedef struct Object
{
  Class* isa;
} Object;

typedef struct ClassMethod
{
  Class* isa;
  void*  fn;
} ClassMethod;

typedef _Atomic ClassMethod AtomicClassMethod;

#define PP_NARG(...) \
         PP_NARG_(__VA_ARGS__,PP_RSEQ_N())
#define PP_NARG_(...) \
         PP_ARG_N(__VA_ARGS__)
#define PP_ARG_N( \
          _1, _2, _3, _4, _5, _6, _7, _8, _9,_10, \
         _11,_12,N,...) N
#define PP_RSEQ_N() \
         12,11,10,9,8,7,6,5,4,3,2,1,0

/* FOREACH macro created by Gregory Pakosz and Marvin 
 * reference: http://stackoverflow.com/questions/1872220/is-it-possible-to-iterate-over-arguments-in-variadic-macros
 */
#define FE_1(WHAT, X) WHAT(X) 
#define FE_2(WHAT, X, ...) WHAT(X)FE_1(WHAT, __VA_ARGS__)
#define FE_3(WHAT, X, ...) WHAT(X)FE_2(WHAT, __VA_ARGS__)
#define FE_4(WHAT, X, ...) WHAT(X)FE_3(WHAT, __VA_ARGS__)
#define FE_5(WHAT, X, ...) WHAT(X)FE_4(WHAT, __VA_ARGS__)
#define FE_6(WHAT, X, ...) WHAT(X)FE_5(WHAT, __VA_ARGS__)
#define FE_7(WHAT, X, ...) WHAT(X)FE_6(WHAT, __VA_ARGS__)
#define FE_8(WHAT, X, ...) WHAT(X)FE_7(WHAT, __VA_ARGS__)
#define FE_9(WHAT, X, ...) WHAT(X)FE_8(WHAT, __VA_ARGS__)
#define FE_10(WHAT, X, ...) WHAT(X)FE_9(WHAT, __VA_ARGS__)
#define FE_11(WHAT, X, ...) WHAT(X)FE_10(WHAT, __VA_ARGS__)
#define FE_12(WHAT, X, ...) WHAT(X)FE_11(WHAT, __VA_ARGS__)

#define GET_MACRO(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,NAME,...) NAME 
#define FOR_EACH(action,...) \
  GET_MACRO(__VA_ARGS__,FE_12,FE_11,FE_10,FE_9,FE_8,FE_7,FE_6,FE_5,FE_4,FE_3,FE_2,FE_1,)(action,__VA_ARGS__)


#define TC_METHOD_TYPE(METHOD) METHOD ## _type

/** User must specify Type_TC_METHODS
 */
#define TC_TYPECLASS_METHODS(TC_TYPE) TC_TYPE ## _TC_METHODS

#define TC_DECLARE_METHOD(METHOD, ...) \
  typedef void TC_METHOD_TYPE(METHOD)(__VA_ARGS__); \
  TC_METHOD_TYPE(METHOD) METHOD;


#define _TC_FE_TC_METHOD_DECLARE_FIELD(METHOD) \
  TC_METHOD_TYPE(METHOD)* METHOD;

#define TC_DECLARE_TYPECLASS(TC_TYPE)       \
  typedef struct TC_TYPE {                    \
    struct Typeclass;                         \
    FOR_EACH(_TC_FE_TC_METHOD_DECLARE_FIELD, TC_TYPECLASS_METHODS(TC_TYPE)) \
  } TC_TYPE;

// Simple fast universal hasing
// possible way to avoid collision: linear probing + simple tabular hasing
#define TC_METHOD_FACTORY(TC_TYPE, METHOD, ISA,...)        \
  do { \
    static AtomicClassMethod method_cache[16]; \
    size_t idx = ((size_t)ISA * 31) >> (sizeof(size_t) - 16); \
    ClassMethod method = atomic_load(&method_cache[idx]); \
    TC_METHOD_TYPE(METHOD)* fn = NULL; \
    if (method.isa == ISA) { \
      fn = (TC_METHOD_TYPE(METHOD)*) method.fn; \
    } else {  \
      TypeClass** trait_it = ISA->traits; \
      for (TypeClass** trait_it = ISA->traits; trait_it; triat_it++) \
        if(!strcmp((*triat_it)->name, #TC_TYPE)) { \
          TC_TYPE* tc = *(TC_TYPE**) trait_it; \
          fn = tc->METHOD; \
          break; \
        } \
      } \
      assert(fn); \
      ClassMethod method = {.isa = ISA, .fn = (void*) fn}; \
      atomic_store(&method_cache[idx], method); \
    } \
    fn(__VA_ARGS__); \
  } while (0);


#define _TC_FE_TC_METHOD_ASSIGN_IMPL(METHOD) \
  TC_TYPE##_var->METHOD = &TC_TYPE ## METHOD;

#define _TC_FE_TYPECLASS_DO(TC_TYPE) \
  TC_TYPE* TC_TYPE##_var = malloc(sizeof(TC_TYPE)); \
  TC_TYPE##_var->name = #TC_TYPE; \
  FOR_EACH(_TC_FE_TC_METHOD_ASSIGN_IMPL, TC_TYPECLASS_METHODS(TC_TYPE)) \
  KLASS.traits[i++] = (TypeClass*) TC_TYPE##_var;

#define TC_CLASS_INIT_TRAITS(KLASS, ...) \
  do { \
    KLASS.traits = calloc(sizeof(void*), PP_NARG(__VA_ARGS__)+1); \
    int i = 0; \
    FOR_EACH(_TC_FE_TYPECLASS_DO, __VA_ARGS__) \
  } while (0)

/*
 * Lazily initialize klass instance.
 * how do we support inheritance?
 * can we assign methods automatically? (by naming convention?)

static pthread_once_t _Myabe_pthread_once = PTHREAD_ONCE_INIT;
static Maybe* _Maybe_klass;
static void _Maybe_klass_init();
Maybe_new(Maybe* self) {
  pthread_once( &_Maybe_klass, &Maybe_init);
  // we can't make Maybe_init know where klass is!
  self->klass = &klass;

static (void)_Maybe_klass_init() {
  // setup traits
  1. figure out the length of __VA_ARGS__, calloc that length
  2. we need a macro to expand TC_TYPE to methods...

  Too much hacks.. use stupid way first?

Monad_METHOD_TYPES => m_return_type m_bind ...

in DECLARE_TYPECLASS
check
#ifndef Monad_IMPL
#error
#endif
 */

typedef void (*m_bind_callback)(void*, base_s*);

#define Monad_TC_METHODS m_return, m_bind, m_then
TC_DECLARE_METHOD(m_return, base_s* self, void* data);
TC_DECLARE_METHOD(m_bind, base_s* self, m_bind_callback cb, base_s* next);
TC_DECLARE_METHOD(m_then, base_s* self, base_s* next);
TC_DECLARE_TYPECLASS(Monad);

void m_return(base_s* self, void* data) {
  TC_METHOD_FACTORY(Monad, m_return, self, data);
}

void m_bind(base_s* self, m_bind_callback cb, base_s* next) {
  TC_METHOD_FACTORY(Monad, m_bind, self, cb, next);
}

void m_then(base_s* self, base_s* next) {
  TC_METHOD_FACTORY(Monad, self, next);
}

enum maybe_e {
  MAYBE_JUST,
  MAYBE_NOTHING,
};

typedef struct Maybe {
  struct Object;
  enum maybe_e maybe_e;
  union {
    void* data;
    void (*apply)(void*, void**);
  };
} Maybe;

static pthread_once_t _Maybe_pthread_once = PTHREAD_ONCE_INIT;
static Class _Maybe_klass;
static void _Maybe_klass_init();
void Maybe_new(Maybe* self) {
  pthread_once( &_Maybe_pthread_once, &_Maybe_klass_init);
  self->klass = &_Maybe_klass;
}

static (void)_Maybe_klass_init() {
  TC_CLASS_INIT_TRAITS(_Maybe_klass, Monad);
}

/*
 fn_type,
 fn <- generic function name
 fn_type* fn_method;
 (fn_type*) ptr (__VA_ARGS__)

 fn_type -> fn is easy.

 User must define fn_type, and define fn manually.
 There simply no easy way to convert fn_type to fn. 
 You don't have to use _type, as our preprocessor doesn't make that assumption.

 */


// We should try to see if we can use inline function..
// Urr seems hard...
// We also need the cache

/*
 * Intput: trait name
 *            stringify trait name...
 *         func name (func type is encoded in trait)
 *         func type (type cast void* to fp)
 *         args send to func

 * We still need a static var to store the cache, but this can be
 * embeded in fuction, so it's ok

 Instead of type cast, use variadic function argument
 may be easier... (though the function might look ugly..)
 then all the functions are func(...)

 We can typedef function type =>
 typedef void fn_t(...)
 fn_t fn //just declaration
 typedef struct Monad {
   struct ...;
   fn_t* m_bind;
 } Monad;

  klass -> void*
  ((fn_t*) ptr)(__VA_ARGS__)

  since we already defined the fn_t...
  can we also build the typeclass from it?
  I guess we can... in a super ugly way.. (because CPP has no for variadic macro)
  
 */
 
#ifdef __cplusplus
}
#endif

#endif /* TYPECLASS_H */
