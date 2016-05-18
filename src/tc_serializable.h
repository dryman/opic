#ifndef TC_SERIALIZABLE_H

#include "../include/tc_common_macros.h"
#include "../include/typeclass.h"
#include "pm_memory_manager.h"

TC_BEGIN_DECLS

#define TCSerializable_TC_METHODS serde_serialize, serde_deserialize
TC_DECLARE_METHOD(serde_serialize,   void, TCObject* obj, PMMemoryManager* ctx);
TC_DECLARE_METHOD(serde_deserialize, void, TCObject* obj, PMMemoryManager* ctx);

TC_DECLARE_TYPECLASS(TCSerializable);

TC_END_DECLS

#endif /* TC_SERIALIZABLE_H */
