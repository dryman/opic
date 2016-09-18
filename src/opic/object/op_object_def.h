#ifndef OP_OBJECT_DEF
#define OP_OBJECT_DEF 1

#include <stdatomic.h>

#include <stdint.h>
#include <stdlib.h>
#include "../common/op_assert.h"
#include "../common/op_macros.h"


OP_BEGIN_DECLS

typedef struct TypeClass TypeClass;
typedef struct Class Class __attribute__ ((aligned(256)));
typedef struct OPObject OPObject;
typedef struct ClassMethod ClassMethod;
typedef struct OPMallocManager OPMallocManager;
typedef struct OPMPool OPMPool;
typedef struct OPMSlot OPMSlot;

struct TypeClass
{
  const char* name;
};

struct Class
{
  const char* const classname;
  const size_t size;
  uint64_t hash;
  TypeClass** traits;
}; 

struct OPObject
{
  Class* isa;
  OPMallocManager* manager;
  atomic_uint refcount;
};

struct ClassMethod
{
  Class* isa;
  void*  fn;
};

typedef _Atomic ClassMethod AtomicClassMethod;

typedef union
{
  OPObject* obj;
  uint64_t  uint64;
  int64_t   int64;
  double    float64;
} OPGeneric __attribute__ ((__transparent_union__));

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

OP_END_DECLS

#endif /* OP_OBJECT_DEF */
