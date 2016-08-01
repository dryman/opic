#ifndef OP_LIST_H
#define OP_LIST_H 1
#include <stdbool.h>
#include "op_macros.h"
#include "op_trait.h"
#include "op_functional.h"
#include "op_iterator.h"

OP_BEGIN_DECLS
OP_DECLARE_TYPECLASS(OPListIterator);
#define OPListIterator_OP_METHODS li_forEachRemaining, li_hasNext, \
li_hasPrevious, li_next, li_nextIndex, li_previous, li_previousIndex
OP_DECLARE_METHOD(li_forEachRemaining, void, OPObject* obj, fp_unary func, void* ctx);
OP_DECLARE_METHOD(li_hasNext,                bool, OPObject* obj);
OP_DECLARE_METHOD(li_hasPrevious,            bool, OPObject* obj);
OP_DECLARE_METHOD(li_next,              OPGeneric, OPObject* obj);
OP_DECLARE_METHOD(li_nextIndex,            size_t, OPObject* obj);
OP_DECLARE_METHOD(li_previous,          OPGeneric, OPObject* obj);
OP_DECLARE_METHOD(li_previousIndex,        size_t, OPObject* obj);

OP_DECLARE_TYPECLASS(OPMutableListIterator);
#define OPMutableListIterator_OP_METHODS mli_add, mli_remove, mli_set
OP_DECLARE_METHOD(mli_insert,                void, OPObject* obj, OPGeneric element);
OP_DECLARE_METHOD(mli_remove,                void, OPObject* obj);
OP_DECLARE_METHOD(mli_set,                   void, OPObject* obj, OPGeneric element);

OP_DECLARE_TYPECLASS(OPList);
#define OPList_OP_METHODS lst_get, lst_indexOf, lastIndexOf, lst_listIterator, \
  lst_listIteratorFrom, lst_subList
OP_DECLARE_METHOD(lst_get,              OPGeneric, OPObject* obj, size_t index);
OP_DECLARE_METHOD(lst_indexOf,             size_t, OPObject* obj, OPGeneric element);
OP_DECLARE_METHOD(lst_lastIndexOf,         size_t, OPObject* obj, OPGeneric element);
OP_DECLARE_METHOD(lst_listIterator,     OPObject*, OPObject* obj);
OP_DECLARE_METHOD(lst_listIteratorFrom, OPObject*, OPObject* obj, size_t index);

OP_DECLARE_TYPECLASS(OPMutableList);
#define OPMutableList_OP_METHODS mslt_insert, mslt_insertAll, mlst_remove, \
  mlst_removeAll, mlst_retainAll, mlst_replaceAll, mlst_set, mlst_sort, \
  mlst_mutableListIterator, mlst_mutableListIteratorFrom
OP_DECLARE_METHOD(mlst_insert,               bool, OPObject* obj, size_t index, OPGeneric element);
OP_DECLARE_METHOD(mlst_insertAll,            bool, OPObject* obj, size_t index, OPObject* collection);
OP_DECLARE_METHOD(mlst_remove,          OPGeneric, OPObject* obj, size_t index);
OP_DECLARE_METHOD(mlst_removeAll,       OPGeneric, OPObject* obj, OPObject* collection);
OP_DECLARE_METHOD(mlst_replaceAll,           void, OPObject* obj, fp_unary map_func);
OP_DECLARE_METHOD(mlst_set,             OPGeneric, OPObject* obj, size_t index, OPGeneric element);
OP_DECLARE_METHOD(mlst_sort,                 void, OPObject* obj, fp_comparator comparator);
OP_DECLARE_METHOD(mlst_mutableListIterator,     OPObject*, OPObject* obj);
OP_DECLARE_METHOD(mlst_mutableListIteratorFrom, OPObject*, OPObject* obj, size_t index);

OP_END_DECLS
#endif /* OP_LIST_H */
