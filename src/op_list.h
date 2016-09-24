#ifndef OP_LIST_H
#define OP_LIST_H 1
#include <stdbool.h>
#include "opic.h"
#include "op_functional.h"

OP_BEGIN_DECLS
#define OPListIterator_OP_METHODS li_forEachRemaining, li_hasNext, \
li_hasPrevious, li_next, li_previous
OP_DECLARE_METHOD(li_forEachRemaining, void, OPObject* obj, fp_unary func, void* ctx);
OP_DECLARE_METHOD(li_hasNext,                bool, OPObject* obj);
OP_DECLARE_METHOD(li_hasPrevious,            bool, OPObject* obj);
OP_DECLARE_METHOD(li_next,              OPGeneric, OPObject* obj);
OP_DECLARE_METHOD(li_previous,          OPGeneric, OPObject* obj);
OP_DECLARE_TYPECLASS(OPListIterator);
// OP_DECLARE_METHOD(li_nextIndex,            size_t, OPObject* obj);
// OP_DECLARE_METHOD(li_previousIndex,        size_t, OPObject* obj);

#define OPMutableListIterator_OP_METHODS mli_insert, mli_remove, mli_set
OP_DECLARE_METHOD(mli_insert,                bool, OPObject* obj, OPGeneric element);
OP_DECLARE_METHOD(mli_remove,                void, OPObject* obj);
OP_DECLARE_METHOD(mli_set,                   void, OPObject* obj, OPGeneric element);
OP_DECLARE_TYPECLASS(OPMutableListIterator);

#define OPList_OP_METHODS lst_get, lst_indexOf, lst_lastIndexOf, lst_listIterator, \
  lst_listIteratorFrom
OP_DECLARE_METHOD(lst_get,              OPGeneric, OPObject* obj, size_t index);
OP_DECLARE_METHOD(lst_indexOf,             size_t, OPObject* obj, OPGeneric element);
OP_DECLARE_METHOD(lst_lastIndexOf,         size_t, OPObject* obj, OPGeneric element);
OP_DECLARE_METHOD(lst_listIterator,     OPObject*, OPObject* obj);
OP_DECLARE_METHOD(lst_listIteratorFrom, OPObject*, OPObject* obj, size_t index);
// sublist
OP_DECLARE_TYPECLASS(OPList);

#define OPMutableList_OP_METHODS mlst_insert, mlst_insertAll, mlst_remove, \
  mlst_removeAll, mlst_replaceAll, mlst_set, mlst_sort, \
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
OP_DECLARE_TYPECLASS(OPMutableList);
// retainAll

OP_END_DECLS
#endif /* OP_LIST_H */
