#include "op_serializable.h"

void serde_serialize(OPObject* obj, PMMemoryManager* ctx)
{
  OP_TYPECLASS_METHOD_FACTORY(OPSerializable, serde_serialize, obj->isa, obj, ctx);
}
void serde_deserialize(OPObject* obj, PMMemoryManager* ctx)
{
  OP_TYPECLASS_METHOD_FACTORY(OPSerializable, serde_deserialize, obj->isa, obj, ctx);
}
