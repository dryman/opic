#ifndef OP_FUNCTIONAL_H
#define OP_FUNCTIONAL_H
#include <stdbool.h>
#include "op_macros.h"
#include "op_trait.h"

typedef void (*fp_unary)(void* a, OPType a_type, void* ctx);
typedef void (*fp_binary)(void* a, OPType a_type, void* b, OPType b_type, void* ctx);
typedef bool (*fp_predicate)(void* a, OPType a_type, void* ctx);
typedef bool (*fp_bipredicate)(void* a, OPType a_type, void* b, OPType b_type, void* ctx);
typedef int (*fp_comparator)(void* a, OPType a_type, void* b, OPType b_type, void* ctx);

#endif /* OP_FUNCTIONAL_H */
