#include "op_serializable.h"
#include "config.h"

void serde_serialize(OPObject* obj, OPMallocManager* ctx)
{
  OP_TYPECLASS_METHOD_FACTORY(OPSerializable, serde_serialize, obj->isa, obj, ctx);
}
void serde_deserialize(OPObject* obj, OPMallocManager* ctx)
{
  OP_TYPECLASS_METHOD_FACTORY(OPSerializable, serde_deserialize, obj->isa, obj, ctx);
}
