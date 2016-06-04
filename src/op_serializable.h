#ifndef OP_SERIALIZABLE_H

#include "op_macros.h"
#include "op_trait.h"
#include "pm_memory_manager.h"

OP_BEGIN_DECLS

#define TCSerializable_TC_METHODS serde_serialize, serde_deserialize
TC_DECLARE_METHOD(serde_serialize,   void, TCObject* obj, PMMemoryManager* ctx);
TC_DECLARE_METHOD(serde_deserialize, void, TCObject* obj, PMMemoryManager* ctx);

TC_DECLARE_TYPECLASS(TCSerializable);

OP_END_DECLS

#endif /* OP_SERIALIZABLE_H */
