#ifndef TYPECLASS_H
#define TYPECLASS_H 1

#include <pthread.h>
#include <stdatomic.h>
#include "../p99/p99.h"

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

typedef struct TCObject
{
  Class* isa;
} TCObject;

typedef struct ClassMethod
{
  Class* isa;
  void*  fn;
} ClassMethod;

typedef _Atomic ClassMethod AtomicClassMethod;



#define TC_METHOD_TYPE(METHOD) METHOD ## _type

#define TC_TYPECLASS_METHODS(TC_TYPE) TC_TYPE ## _TC_METHODS

#define TC_DECLARE_METHOD(METHOD, ...) \
  typedef void TC_METHOD_TYPE(METHOD)(__VA_ARGS__); \
  TC_METHOD_TYPE(METHOD) METHOD;


#define _TC_METHOD_DECLARE_FIELD(METHOD) \
  TC_METHOD_TYPE(METHOD)* METHOD

#define TC_DECLARE_TYPECLASS(TC_TYPE)       \
  typedef struct TC_TYPE {                    \
    struct Typeclass;                         \
    P99_SEP(_TC_METHOD_DECLARE_FIELD,TC_TYPECLASS_METHODS(TC_TYPE)) \
  } TC_TYPE;

// Simple fast universal hasing
// possible way to avoid collision: linear probing + simple tabular hasing
#define TC_TYPECLASS_METHOD_FACTORY(TC_TYPE, METHOD, ISA,...)        \
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


#define _TC_METHOD_ASSIGN_IMPL(TC_TYPE,METHOD,I) \
  TC_TYPE##_var->METHOD = P99_PASTE(&TC_TYPE,_,METHOD)

#define TC_CLASS_ADD_TYPECLASS(KLASS, TC_TYPE, SLOT) \
  do { \
    TC_TYPE* TC_TYPE##_var = malloc(sizeof(TC_TYPE)); \
    TC_TYPE##_var->name = #TC_TYPE; \
    P99_FOR(TC_TYPE, P99_NARG(TC_TYPECLASS_METHODS(TC_TYPE)), \
            P00_SEP, _TC_METHOD_ASSIGN_IMPL, \
            TC_TYPECLASS_METHODS(TC_TYPE) \
            ) \
    KLASS.traits[SLOT] = (TypeClass*) TC_TYPE##_var; \
  while (0);


typedef void (*m_bind_callback)(void*, TCObject*);

#define Monad_TC_METHODS m_return, m_bind, m_then
TC_DECLARE_METHOD(m_return, TCObject* self, void* data);
TC_DECLARE_METHOD(m_bind, TCObject* self, m_bind_callback cb, TCObject* next);
TC_DECLARE_METHOD(m_then, TCObject* self, TCObject* next);
TC_DECLARE_TYPECLASS(Monad);

 
#ifdef __cplusplus
}
#endif

#endif /* TYPECLASS_H */
