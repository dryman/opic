#include "op_serializable.h"

void serde_serialize(TCObject* obj, PMMemoryManager* ctx)
{
  TC_TYPECLASS_METHOD_FACTORY(TCSerializable, serde_serialize, obj->isa, obj, ctx);
}
void serde_deserialize(TCObject* obj, PMMemoryManager* ctx)
{
  TC_TYPECLASS_METHOD_FACTORY(TCSerializable, serde_deserialize, obj->isa, obj, ctx);
}
