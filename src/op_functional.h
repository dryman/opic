#ifndef OP_FUNCTIONAL_H
#define OP_FUNCTIONAL_H
#include <stdbool.h>
#include "op_macros.h"
#include "op_trait.h"

typedef void (*fp_unary)(OPGeneric a, OPType a_type, void* ctx);
typedef void (*fp_binary)(OPGeneric a, OPType a_type, OPGeneric b, OPType b_type, void* ctx);
typedef bool (*fp_predicate)(OPGeneric a, OPType a_type, void* ctx);
typedef bool (*fp_bipredicate)(OPGeneric a, OPType a_type, OPGeneric b, OPType b_type, void* ctx);
typedef int (*fp_comparator)(OPGeneric a, OPType a_type, OPGeneric b, OPType b_type, void* ctx);

#endif /* OP_FUNCTIONAL_H */
