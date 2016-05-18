#ifndef TYPECLASS_H
#define TYPECLASS_H 1

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdatomic.h>
#include "tc_assert.h"
#include "tc_common_macros.h"

TC_BEGIN_DECLS

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
  const char* const classname; // useful for debugging
  const size_t size;
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

Class* LPTypeMap_get(char* key);
void LPTypeMap_put(char* key, Class* value);
bool tc_isa_instance_of(Class* klass, char* trait);
bool tc_instance_of(TCObject* obj, char* trait);

TC_END_DECLS

#define TC_METHOD_TYPE(METHOD) METHOD ## _type

#define TC_TYPECLASS_METHODS(TC_TYPE) TC_TYPE ## _TC_METHODS

#define TC_DECLARE_METHOD(METHOD, RET, ...) \
  typedef RET TC_METHOD_TYPE(METHOD)(__VA_ARGS__); \
  TC_METHOD_TYPE(METHOD) METHOD;


#define _TC_METHOD_DECLARE_FIELD(METHOD,...) \
  TC_METHOD_TYPE(METHOD)* METHOD

#define TC_DECLARE_TYPECLASS(TC_TYPE)       \
  typedef struct TC_TYPE {                    \
    struct TypeClass;                         \
    TC_MAP_SC_S0(_TC_METHOD_DECLARE_FIELD, TC_TYPECLASS_METHODS(TC_TYPE)); \
  } TC_TYPE;

// Simple fast universal hasing
// possible way to avoid collision: linear probing + simple tabular hasing
// size_t idx = ((size_t)ISA * 31) >> (sizeof(size_t)*8 - 16);
      /*
      In future we should use debug flag to enable these
      printf("ISA matched. ISA: %p, fn: %p\n", method.isa, method.fn); \
      printf("ISA mismatch.\n"); \
      */
#define TC_TYPECLASS_METHOD_FACTORY(TC_TYPE, METHOD, ISA,...)        \
  do { \
    static AtomicClassMethod method_cache[16]; \
    size_t idx = ((size_t)ISA >> 3) & 0x0F; \
    tc_assert((ISA), "Class ISA is null\n"); \
    ClassMethod method; \
    method = atomic_load(&method_cache[idx]); \
    TC_METHOD_TYPE(METHOD)* fn = NULL; \
    if (method.isa == ISA) { \
      fn = (TC_METHOD_TYPE(METHOD)*) method.fn; \
    } else {  \
      TypeClass** trait_it = ISA->traits; \
      int i=0; \
      for (TypeClass** trait_it = ISA->traits; *trait_it; trait_it++) {\
        if(!strcmp((*trait_it)->name, #TC_TYPE)) { \
          TC_TYPE* tc = *(TC_TYPE**) trait_it; \
          fn = tc->METHOD; \
          break; \
        } \
      } \
      tc_assert(fn,"Class %s does implement %s.%s\n", ISA->classname,#TC_TYPE,#METHOD); \
      method = (ClassMethod){.isa = ISA, .fn = (void*) fn}; \
      atomic_store(&method_cache[idx], method); \
    } \
    return fn(__VA_ARGS__); \
  } while (0);

/*
#define TC_CLASS_DECLARE_TC_METHODS(KLASS) \
  void KLASS ## _init(KLASS*); \
  TC_MAP_SC_S1(_TC_CLASS_DECLARE_TC_METHOD,KLASS,

#define _TC_CLASS_DECLARE_TC_METHOD(METHOD,I,KLASS,...) \
  TC_METHOD_TYPE(METHOD) KLASS ## METHOD;
 */ 

#define TC_CLASS_OBJ(KLASS) KLASS ## _klass_

#define TC_DECLARE_ISA(KLASS) \
extern Class TC_CLASS_OBJ(KLASS);

#define TC_DEFINE_ISA(KLASS) \
Class TC_CLASS_OBJ(KLASS) = {.classname = #KLASS, .size=sizeof(KLASS) }; \
__attribute__((constructor)) \
void define_##KLASS##_ISA() { \
  LPTypeMap_put(#KLASS, &TC_CLASS_OBJ(KLASS)); \
} \
KLASS* KLASS##_init_isa(KLASS* self) { \
  self->isa = &TC_CLASS_OBJ(KLASS); \
  return self; \
}

#define TC_DEFINE_ISA_WITH_TYPECLASSES(KLASS,...) \
Class TC_CLASS_OBJ(KLASS) = {.classname = #KLASS, .size=sizeof(KLASS) }; \
__attribute__((constructor)) \
void define_##KLASS##_ISA() { \
  LPTypeMap_put(#KLASS, &TC_CLASS_OBJ(KLASS)); \
  TC_CLASS_OBJ(KLASS).traits = calloc(sizeof(void*), TC_LENGTH(__VA_ARGS__) + 1); \
  TC_MAP_SC_S1(TC_CLASS_ADD_TYPECLASS,KLASS,__VA_ARGS__); \
} \
KLASS* KLASS##_init_isa(KLASS* self) { \
  self->isa = &TC_CLASS_OBJ(KLASS); \
  return self; \
}

  
#define TC_CLASS_ADD_TYPECLASS(TC_TRAIT_TYPE, SLOT, KLASS_TYPE,...) \
  do { \
    TC_TRAIT_TYPE* TC_TRAIT_TYPE##_var = malloc(sizeof(TC_TRAIT_TYPE)); \
    TC_TRAIT_TYPE##_var->name = #TC_TRAIT_TYPE; \
    TC_MAP_SC_S2_(_TC_METHOD_ASSIGN_IMPL, \
      TC_TRAIT_TYPE, KLASS_TYPE, \
      TC_TYPECLASS_METHODS(TC_TRAIT_TYPE)); \
    TC_CLASS_OBJ(KLASS_TYPE).traits[SLOT] = (TypeClass*) TC_TRAIT_TYPE##_var; \
  } while (0);

#define _TC_METHOD_ASSIGN_IMPL(METHOD,I,TC_TRAIT_TYPE,KLASS_TYPE,...) \
  TC_TRAIT_TYPE##_var->METHOD = &KLASS_TYPE##_##METHOD


#endif /* TYPECLASS_H */
