#ifndef OP_TRAIT_H
#define OP_TRAIT_H 1

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdatomic.h>
#include "op_assert.h"
#include "op_macros.h"

OP_BEGIN_DECLS

typedef struct TypeClass TypeClass;
typedef struct Class Class __attribute__ ((aligned(256)));
typedef struct OPObject OPObject;
typedef struct ClassMethod ClassMethod;

struct TypeClass
{
  const char* name;
};

// TODO: find good way to implement super
// two possible ways:
// 1. anonymous embeded super
//    Hard to handle traits (reuse, overwrite, ...)
// 2. pointer to supers (traverse pointers may take time..)
// Hakell type doesn't seems to have inheritance?
// Maybe we don't need it at all
struct Class
{
  const char* const classname; // useful for debugging
  const size_t size;
  TypeClass** traits;
  // methods should be struct extending class
}; 

struct OPObject
{
  Class* isa;
};

struct ClassMethod
{
  Class* isa;
  void*  fn;
};

typedef _Atomic ClassMethod AtomicClassMethod;

typedef union __attribute__ ((__transparent_union__))
{
  OPObject* obj;
  uint64_t  uint64;
  int64_t   int64;
  double    float64;
} OPGeneric;

typedef enum
{
  op_object = 0,
  op_int8,
  op_int16,
  op_int32,
  op_int64,
  op_uint8,
  op_uint16,
  op_uint32,
  op_uint64,
  op_float32,
  op_float64
} OPType;

Class* LPTypeMap_get(char* key);
void LPTypeMap_put(char* key, Class* value);
bool tc_isa_instance_of(Class* klass, char* trait);
bool tc_instance_of(OPObject* obj, char* trait);

OP_END_DECLS

#define OP_METHOD_TYPE(METHOD) METHOD ## _type

#define OP_TYPECLASS_METHODS(OP_TYPE) OP_TYPE ## _OP_METHODS

#define OP_DECLARE_METHOD(METHOD, RET, ...) \
  typedef RET OP_METHOD_TYPE(METHOD)(__VA_ARGS__); \
  OP_METHOD_TYPE(METHOD) METHOD;


#define _OP_METHOD_DECLARE_FIELD(METHOD,...) \
  OP_METHOD_TYPE(METHOD)* METHOD

#define OP_DECLARE_TYPECLASS(OP_TYPE)       \
  typedef struct OP_TYPE {                    \
    struct TypeClass base;                    \
    OP_MAP_SC_S0(_OP_METHOD_DECLARE_FIELD, OP_TYPECLASS_METHODS(OP_TYPE)); \
  } OP_TYPE;

// Simple fast universal hasing
// possible way to avoid collision: linear probing + simple tabular hasing
// size_t idx = ((size_t)ISA * 31) >> (sizeof(size_t)*8 - 16);
      /*
      In future we should use debug flag to enable these
      printf("ISA matched. ISA: %p, fn: %p\n", method.isa, method.fn); \
      printf("ISA mismatch.\n"); \
      */
#define OP_TYPECLASS_METHOD_FACTORY(OP_TYPE, METHOD, ISA,...)        \
  do { \
    Class* isa = (Class*)(((size_t)(ISA)) & (size_t)(~(0x0FL))); \
    static AtomicClassMethod method_cache[16]; \
    size_t idx = ((size_t)isa >> 3) & 0x0F; \
    op_assert(isa, "Class ISA is null\n"); \
    ClassMethod method; \
    method = atomic_load(&method_cache[idx]); \
    OP_METHOD_TYPE(METHOD)* fn = NULL; \
    if (method.isa == isa) { \
      fn = (OP_METHOD_TYPE(METHOD)*) method.fn; \
    } else {  \
      TypeClass** trait_it = isa->traits; \
      int i=0; \
      for (TypeClass** trait_it = isa->traits; *trait_it; trait_it++) {\
        if(!strcmp((*trait_it)->name, #OP_TYPE)) { \
          OP_TYPE* tc = *(OP_TYPE**) trait_it; \
          fn = tc->METHOD; \
          break; \
        } \
      } \
      op_assert(fn,"Class %s does implement %s.%s\n", isa->classname,#OP_TYPE,#METHOD); \
      method = (ClassMethod){.isa = isa, .fn = (void*) fn}; \
      atomic_store(&method_cache[idx], method); \
    } \
    return fn(__VA_ARGS__); \
  } while (0);

/*
#define OP_CLASS_DECLARE_OP_METHODS(KLASS) \
  void KLASS ## _init(KLASS*); \
  OP_MAP_SC_S1(_OP_CLASS_DECLARE_OP_METHOD,KLASS,

#define _OP_CLASS_DECLARE_OP_METHOD(METHOD,I,KLASS,...) \
  OP_METHOD_TYPE(METHOD) KLASS ## METHOD;
 */ 

#define OP_CLASS_OBJ(KLASS) KLASS ## _klass_

#define OP_DECLARE_ISA(KLASS) \
extern Class OP_CLASS_OBJ(KLASS); \
KLASS* KLASS##_init_isa(KLASS* self);

#define OP_DEFINE_ISA(KLASS) \
Class OP_CLASS_OBJ(KLASS) = {.classname = #KLASS, .size=sizeof(KLASS) }; \
__attribute__((constructor)) \
void define_##KLASS##_ISA() { \
  LPTypeMap_put(#KLASS, &OP_CLASS_OBJ(KLASS)); \
} \
KLASS* KLASS##_init_isa(KLASS* self) { \
  ((OPObject*)self)->isa = &OP_CLASS_OBJ(KLASS); \
  return self; \
}

#define OP_DEFINE_ISA_WITH_TYPECLASSES(KLASS,...) \
Class OP_CLASS_OBJ(KLASS) = {.classname = #KLASS, .size=sizeof(KLASS) }; \
__attribute__((constructor)) \
void define_##KLASS##_ISA() { \
  LPTypeMap_put(#KLASS, &OP_CLASS_OBJ(KLASS)); \
  OP_CLASS_OBJ(KLASS).traits = calloc(sizeof(void*), OP_LENGTH(__VA_ARGS__) + 1); \
  OP_MAP_SC_S1(OP_CLASS_ADD_TYPECLASS,KLASS,__VA_ARGS__); \
} \
KLASS* KLASS##_init_isa(KLASS* self) { \
  ((OPObject*)self)->isa = &OP_CLASS_OBJ(KLASS); \
  return self; \
}

  
#define OP_CLASS_ADD_TYPECLASS(OP_TRAIT_TYPE, SLOT, KLASS_TYPE,...) \
  do { \
    OP_TRAIT_TYPE* OP_TRAIT_TYPE##_var = malloc(sizeof(OP_TRAIT_TYPE)); \
    OP_TRAIT_TYPE##_var->base.name = #OP_TRAIT_TYPE; \
    OP_MAP_SC_S2_(_OP_METHOD_ASSIGN_IMPL, \
      OP_TRAIT_TYPE, KLASS_TYPE, \
      OP_TYPECLASS_METHODS(OP_TRAIT_TYPE)); \
    OP_CLASS_OBJ(KLASS_TYPE).traits[SLOT] = (TypeClass*) OP_TRAIT_TYPE##_var; \
  } while (0);

#define _OP_METHOD_ASSIGN_IMPL(METHOD,I,OP_TRAIT_TYPE,KLASS_TYPE,...) \
  OP_TRAIT_TYPE##_var->METHOD = &KLASS_TYPE##_##METHOD


#endif /* OP_TRAIT_H */
