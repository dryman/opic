#ifndef OP_LINKDED_LIST_H
#define OP_LINKDED_LIST_H 1
#include <stdbool.h>
#include "opic.h"
#include "opic/object/op_trait.h"
#include "op_functional.h"
#include "op_collection.h"
#include "op_list.h"

OP_BEGIN_DECLS

typedef struct OPLinkedList OPLinkedList;
typedef struct OPLinkedListIterator OPLinkedListIterator;
typedef struct OPLinkedListNode OPLinkedListNode;
OP_DECLARE_ISA(OPLinkedList);
OP_DECLARE_ISA(OPLinkedListIterator);
OP_DECLARE_ISA(OPLinkedListNode);

void      OPLinkedListNode_serde_serialize(OPObject* obj, PMMemoryManager* ctx);
void      OPLinkedListNode_serde_deserialize(OPObject* obj, PMMemoryManager* ctx);

void      OPLinkedList_serde_serialize(OPObject* obj, PMMemoryManager* ctx);
void      OPLinkedList_serde_deserialize(OPObject* obj, PMMemoryManager* ctx);

bool      OPLinkedList_coll_contains(OPObject* obj, OPGeneric element);
bool      OPLinkedList_coll_containsAll(OPObject* obj, OPObject* collection);
bool      OPLinkedList_coll_isEmpty(OPObject* obj);
size_t    OPLinkedList_coll_size(OPObject* obj);
OPType    OPLinkedList_coll_type(OPObject* obj);

OPGeneric OPLinkedList_lst_get(OPObject* obj, size_t index);
size_t    OPLinkedList_lst_indexOf(OPObject* obj, OPGeneric element);
size_t    OPLinkedList_lst_lastIndexOf(OPObject* obj, OPGeneric element);
OPObject* OPLinkedList_lst_listIterator(OPObject* obj);
OPObject* OPLinkedList_lst_listIteratorFrom(OPObject* obj, size_t index);

void      OPLinkedList_mcoll_init(OPObject* obj, OPType type, PMMemoryManager* manager);
bool      OPLinkedList_mcoll_add(OPObject* obj, OPGeneric element);
bool      OPLinkedList_mcoll_addAll(OPObject* obj, OPObject* collection);
void      OPLinkedList_mcoll_clear(OPObject* obj);
bool      OPLinkedList_mcoll_removeIf(OPObject* obj, fp_predicate predicate);
bool      OPLinkedList_mcoll_retainAll(OPObject* obj, OPObject* collection);

bool      OPLinkedList_mlst_insert(OPObject* obj, size_t index, OPGeneric element);
bool      OPLinkedList_mlst_insertAll(OPObject* obj, size_t index, OPObject* collection);
OPGeneric OPLinkedList_mlst_remove(OPObject* obj, size_t index);
OPGeneric OPLinkedList_mlst_removeAll(OPObject* obj, OPObject* collection);
void      OPLinkedList_mlst_replaceAll(OPObject* obj, fp_unary map_func);
OPGeneric OPLinkedList_mlst_set(OPObject* obj, size_t index, OPGeneric element);
void      OPLinkedList_mlst_sort(OPObject* obj, fp_comparator comparator);
OPObject* OPLinkedList_mlst_mutableListIterator(OPObject* obj);
OPObject* OPLinkedList_mlst_mutableListIteratorFrom(OPObject* obj, size_t index);


void      OPLinkedListIterator_li_forEachRemaining(OPObject* obj, fp_unary func, void* ctx);
bool      OPLinkedListIterator_li_hasNext(OPObject* obj);
bool      OPLinkedListIterator_li_hasPrevious(OPObject* obj);
OPGeneric OPLinkedListIterator_li_next(OPObject* obj);
OPGeneric OPLinkedListIterator_li_previous(OPObject* obj);
// size_t    OPLinkedListIterator_li_nextIndex(OPObject* obj);
// size_t    OPLinkedListIterator_li_previousIndex(OPObject* obj);

void      OPLinkedListIterator_mli_insert(OPObject* obj, OPGeneric element);
void      OPLinkedListIterator_mli_remove(OPObject* obj);
void      OPLinkedListIterator_mli_set(OPObject* obj, OPGeneric element);


OP_END_DECLS
#endif /* OP_LINKDED_LIST_H */
