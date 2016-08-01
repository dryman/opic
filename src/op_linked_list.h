#ifndef OP_LINKDED_LIST_H
#define OP_LINKDED_LIST_H 1
#include <stdbool.h>
#include "op_macros.h"
#include "op_trait.h"
#include "op_functional.h"
#include "op_list.h"
#include "op_collection.h"

OP_BEGIN_DECLS

typedef struct OPLinkedList OPLinkedList;
typedef struct OPLinkedListIterator OPLinkedListIterator;
typedef struct OPMutableLinkedList OPMutableLinkedList;
typedef struct OPMutableLinkedListIterator OPMutableLinkedListIterator;
OP_DECLARE_ISA(OPLinkedList);
OP_DECLARE_ISA(OPLinkedListIterator);
OP_DECLARE_ISA(OPMutableLinkedList);
OP_DECLARE_ISA(OPMutableLinkedListIterator);


void      OPLinkedList_serde_serialize(OPObject* obj, PMMemoryManager* ctx);
void      OPLinkedList_serde_deserialize(OPObject* obj, PMMemoryManager* ctx);

bool      OPLinkedList_coll_contains(OPObject* obj, OPGeneric element);
bool      OPLinkedList_coll_containsAll(OPObject* obj, OPObject* collection);
bool      OPLinkedList_coll_isEmpty(OPObject* obj);
size_t    OPLinkedList_coll_size(OPObject* obj);
OPTYpe    OPLinkedList_coll_type(OPObject* obj);

OPGeneric OPLinkedList_lst_get(OPObject* obj, size_t index);
size_t    OPLinkedList_lst_indexOf(OPObject* obj, OPGeneric element);
size_t    OPLinkedList_lst_lastIndexOf(OPObject* obj, OPGeneric element);
OPObject* OPLinkedList_lst_listIterator(OPObject* obj);
OPObject* OPLinkedList_lst_listIteratorFrom(OPObject* obj, size_t index);


void      OPLinkedListIterator_li_forEachRemaining(OPObject* obj, fp_unary func, void* ctx);
bool      OPLinkedListIterator_li_hasNext(OPObject* obj);
bool      OPLinkedListIterator_li_hasPrevious(OPObject* obj);
OPGeneric OPLinkedListIterator_li_next(OPObject* obj);
size_t    OPLinkedListIterator_li_nextIndex(OPObject* obj);
size_t    OPLinkedListIterator_li_nextIndex(OPObject* obj);
OPGeneric OPLinkedListIterator_li_previous(OPObject* obj);
size_t    OPLinkedListIterator_li_previousIndex(OPObject* obj);


void      OPMutableLinkedList_serde_serialize(OPObject* obj, PMMemoryManager* ctx);
void      OPMutableLinkedList_serde_deserialize(OPObject* obj, PMMemoryManager* ctx);

bool      OPMutableLinkedList_coll_contains(OPObject* obj, OPGeneric element);
bool      OPMutableLinkedList_coll_containsAll(OPObject* obj, OPObject* collection);
bool      OPMutableLinkedList_coll_isEmpty(OPObject* obj);
size_t    OPMutableLinkedList_coll_size(OPObject* obj);
OPTYpe    OPMutableLinkedList_coll_type(OPObject* obj);

void      OPMutableLinkedList_mcoll_initWithType(OPObject* obj, OPType type);
bool      OPMutableLinkedList_mcoll_add(OPObject* obj, OPGeneric element);
bool      OPMutableLinkedList_mcoll_addAll(OPObject* obj, OPObject* collection);
void      OPMutableLinkedList_mcoll_clear(OPObject* obj);
bool      OPMutableLinkedList_mcoll_removeIf(OPObject* obj, fp_predicate predicate);
bool      OPMutableLinkedList_mcoll_retainAll(OPObject* obj, OPObject* collection);

OPGeneric OPMutableLinkedList_lst_get(OPObject* obj, size_t index);
size_t    OPMutableLinkedList_lst_indexOf(OPObject* obj, OPGeneric element);
size_t    OPMutableLinkedList_lst_lastIndexOf(OPObject* obj, OPGeneric element);
OPObject* OPMutableLinkedList_lst_listIterator(OPObject* obj);
OPObject* OPMutableLinkedList_lst_listIteratorFrom(OPObject* obj, size_t index);

bool      OPMutableLinkedList_mlst_insert(OPObject* obj, size_t index, OPGeneric element);
bool      OPMutableLinkedList_mlst_insertAll(OPObject* obj, size_t index, OPObject* collection);
OPGeneric OPMutableLinkedList_mlst_remove(OPObject* obj, size_t index);
OPGeneric OPMutableLinkedList_mlst_removeAll(OPObject* obj, OPObject* collection);
void      OPMutableLinkedList_mlst_replaceAll(OPObject* obj, fp_unary map_func);
OPGeneric OPMutableLinkedList_mlst_set(OPObject* obj, size_t index, OPGeneric element);
void      OPMutableLinkedList_mlst_sort(OPObject* obj, fp_comparator comparator);
OPObject* OPMutableLinkedList_mlst_mutableListIterator(OPObject* obj);
OPObject* OPMutableLinkedList_mlst_mutableListIteratorFrom(OPObject* obj, size_t index);

void      OPMutableLinkedListIterator_li_forEachRemaining(OPObject* obj, fp_unary func, void* ctx);
bool      OPMutableLinkedListIterator_li_hasNext(OPObject* obj);
bool      OPMutableLinkedListIterator_li_hasPrevious(OPObject* obj);
OPGeneric OPMutableLinkedListIterator_li_next(OPObject* obj);
size_t    OPMutableLinkedListIterator_li_nextIndex(OPObject* obj);
size_t    OPMutableLinkedListIterator_li_nextIndex(OPObject* obj);
OPGeneric OPMutableLinkedListIterator_li_previous(OPObject* obj);
size_t    OPMutableLinkedListIterator_li_previousIndex(OPObject* obj);

void      OPMutableLinkedListIterator_mli_insert(OPObject* obj, OPGeneric element);
void      OPMutableLinkedListIterator_mli_remove(OPObject* obj);
void      OPMutableLinkedListIterator_mli_set(OPObject* obj, OPGeneric element);


OP_END_DECLS
#endif /* OP_LINKDED_LIST_H */
