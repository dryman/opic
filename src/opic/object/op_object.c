#include "op_object.h"
#include "config.h"


void OPRetain(void* obj)
{
  OPObject* _obj = (OPObject*) obj;
  atomic_fetch_add_explicit(&_obj->refcount, 1, memory_order_relaxed);
}

void OPRelease(void* obj)
{
  OPObject* _obj = (OPObject*) obj;
  if (_obj == NULL || *(Class**)_obj == NULL)
    {
      /* log4c_category_log(free_logger, LOG4C_PRIORITY_ERROR, */
      /*                    "Attempt to free invalid ptr %p", obj); */
      return;
    }

  if (atomic_fetch_sub_explicit(&_obj->refcount, 1,
                                memory_order_release)
      == 1)
    {
      atomic_thread_fence(memory_order_acquire);
      op_dealloc(obj);
    }
}

void op_dealloc(void* obj)
{
  OPObject* _obj = obj;
  Class* isa = (Class*)((size_t)_obj->isa & (size_t)(~0x0FL));
  static AtomicClassMethod method_cache[65536];
  size_t idx = ((size_t) isa >> 3) & (1<<16 - 1);
  
  ClassMethod method = atomic_load(&method_cache[idx]);
  void(*fn)(void*) = NULL;
  if (method.isa == isa)
    {
      fn = (void(*)(void*))method.fn;
    }
  else
    {
      TypeClass** trait_it = isa->traits;
      int i = 0;
      for (; *trait_it; trait_it++)
        {
          if (!strcmp((*trait_it)->name, "OPObjectBase"))
            {              
              OPObjectBase* tc = *(OPObjectBase**) trait_it;
              fn = tc->op_dealloc;
              break;
            }
        }
      method = (ClassMethod) { .isa = isa, .fn = (void*) fn};
      atomic_store(&method_cache[idx], method);
    }
  if (fn)
    {
      fn(obj);
    }
  OPFree(obj);
}
