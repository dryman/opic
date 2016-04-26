/* This may look like nonsense, but it really is -*- mode: C -*-              */
/*                                                                            */
/* Except for parts copied from previous work and as explicitly stated below, */
/* the author and copyright holder for this work is                           */
/* (C) copyright  2013-2014 Jens Gustedt, INRIA, France                       */
/*                                                                            */
/* This file is free software; it is part of the P99 project.                 */
/* You can redistribute it and/or modify it under the terms of the QPL as     */
/* given in the file LICENSE. It is distributed without any warranty;         */
/* without even the implied warranty of merchantability or fitness for a      */
/* particular purpose.                                                        */
/*                                                                            */
#ifndef P99_RP_H
#define P99_RP_H 1

#include "p99_enum.h"
#include "p99_generic.h"

/* Additions by C11 */
# if __STDC_VERSION__ < 201100L
#  include "p99_atomic.h"
# endif

#ifdef P99_TP_NEED_INTEGER
# if UINTPTR_MAX == UINT32_MAX
typedef uint64_t p00_tp_glue;
# else
#  if defined(UINT128_MAX)
typedef uint128_t p00_tp_glue;
#  else
typedef p99x_uint128 p00_tp_glue;
#  endif
# endif

P99_CONSTANT(int, p00_tp_bits, sizeof(p00_tp_glue)*CHAR_BIT);
P99_CONSTANT(int, p00_tp_shift, p00_tp_bits/2);

p99_inline
p00_tp_glue p00_tp_p2i(void * p, uintptr_t t) {
  return (((p00_tp_glue)t)<<p00_tp_shift)|(uintptr_t)p;
}

#define P00_TP_GLUE_INITIALIZER(VAL, TIC) ((((p00_tp_glue)VAL)<<p00_tp_shift)|((uintptr_t){(TIC)}))


p99_inline
void * p00_tp_i2p(p00_tp_glue v) {
  return (void*)(uintptr_t)v;
}

p99_inline
uintptr_t p00_tp_i2i(p00_tp_glue v) {
  return v >> p00_tp_shift;
}

#else
P99_DECLARE_STRUCT(p00_tp_glue);

struct p00_tp_glue {
  uintptr_t p00_tag;
  void* p00_val;
};

#define P00_TP_GLUE_INITIALIZER(VAL, TIC) { .p00_tag = (TIC), .p00_val = (VAL), }

p99_inline
p00_tp_glue p00_tp_p2i(void * p00_val, uintptr_t p00_tag) {
  return (p00_tp_glue) { .p00_tag = p00_tag, .p00_val = p00_val, };
}

p99_inline
void * p00_tp_i2p(p00_tp_glue p00_sta) {
  return p00_sta.p00_val;
}

p99_inline
uintptr_t p00_tp_i2i(p00_tp_glue p00_sta) {
  return p00_sta.p00_tag;
}
#endif

P99_DECLARE_ATOMIC(p00_tp_glue);

P99_DECLARE_STRUCT(p99_tp);
P99_DECLARE_STRUCT(p99_tp_state);


/* The tag part of a p99_tp ideally would be unique during the whole
   run of a program instance. Since we might not have more than 32 bit
   for this, this will not be possible in general, but we try to get
   as close as possible to that.

   The problem should generally only arise for several accesses to the
   same memory that are close in time. Particularly problematic are
   such usages that go across free and re-malloc boundaries, because
   two instances of p99_tp that are realized on the same address could
   look the same if by coincidence their tags are the same.

   Therefore we compose each tag from two parts. One is a thread
   specific counter (p00_tp_tick), and the other is a global counter
   (p00_tp_tack) that is only consulted, when the thread counter
   wraps.

   If uintptr_t is 64 bit wide this should be safe. Each of the type
   of counters only would wrap after 4 billion increments. In
   particular we only could have a duplicate tag after 4 billion
   events that consist in the creation of a new thread or in
   p00_tp_tick wrapping for certain threads.

   */
P99_DECLARE_THREAD_LOCAL(uintptr_t volatile, p00_tp_tick);
P99_WEAK(p00_tp_tack) _Atomic(uintptr_t) volatile p00_tp_tack;

p99_inline
uintptr_t p00_tp_tick_get(void) {
  enum { p00_bits = sizeof(uintptr_t)*CHAR_BIT/2, };
  register uintptr_t const p00_mask = (UINTPTR_MAX >> p00_bits);
  register uintptr_t volatile*const p00_ret = &P99_THREAD_LOCAL(p00_tp_tick);
  if (P99_UNLIKELY(!(*p00_ret & p00_mask))) {
    uintptr_t p00_tack = 0;
    while (!p00_tack) {
      p00_tack = atomic_fetch_add_explicit(&p00_tp_tack, 1u, memory_order_acq_rel);
      p00_tack &= p00_mask;
    }
    *p00_ret = (p00_tack << p00_bits);
  }
  return ++(*p00_ret);
}

p99_inline
p00_tp_glue volatile* p00_tp_glue_init(p00_tp_glue volatile* el, void * p) {
  if (el) {
    *el = (p00_tp_glue)P00_TP_GLUE_INITIALIZER(p, p00_tp_tick_get());
  }
  return el;
}

/**
 ** @brief A tagged pointer for atomic storage.
 **
 ** The idea of this data structure is to store a unique transaction
 ** ID together with a pointer such that different usages of the same
 ** pointer can be distinguished.
 **
 ** @see p99_tp_state
 **/
struct p99_tp {
  _Atomic(p00_tp_glue) volatile p00_val;
  void*const p00_init;
};

/**
 ** @brief A local view of a tagged pointer for atomic storage.
 **
 ** This is to be used together with ::p99_tp.
 **
 ** @code
 ** p99_tp tp = P99_TP_INITIALIZER(0);
 ** ...
 ** void * fut = &(int){ 37 };
 ** p99_tp_state st = p99_tp_state_initializer(&tp, fut);
 ** void * val = p99_tp_state_get(&st);
 ** // do something with the current value, then
 ** // commit the new value "fut" if possible
 ** if (!p99_tp_state_commit(&st)) abort();
 ** @endcode
 **
 ** @see p99_tp_state_get
 ** @see p99_tp_state_set
 ** @see p99_tp_state_commit
 ** @see p99_tp_state_initializer
 **/
struct p99_tp_state {
  p00_tp_glue p00_val;
  p00_tp_glue p00_next;
  p99_tp volatile* p00_tp;
};

# define P00_TP_INITIALIZER(VAL) {                             \
    .p00_val = ATOMIC_VAR_INIT(0),                             \
    .p00_init = (VAL),                                         \
}

p99_inline
bool p00_tp_cmpxchg(_Atomic(p00_tp_glue) volatile*const p00_p, p00_tp_glue volatile*const p00_prev, p00_tp_glue p00_new) {
  P99_MARK("wide cmpxchg start");
  bool ret = atomic_compare_exchange_weak_explicit(p00_p, p00_prev, p00_new, memory_order_acq_rel, memory_order_consume);
  P99_MARK("wide cmpxchg end");
  return ret;
}

p99_inline
p00_tp_glue p00_tp_get(register p99_tp volatile*const p00_tp) {
  register p00_tp_glue p00_ret
    = P99_LIKELY(p00_tp)
      ? atomic_load_explicit(&p00_tp->p00_val, memory_order_consume)
      : (p00_tp_glue)P00_TP_GLUE_INITIALIZER((void*)0, p00_tp_tick_get());
  if (p00_tp && P99_UNLIKELY(!p00_tp_i2i(p00_ret))) {
    /* Only store it in addressable memory if we can't avoid it. */
    p00_tp_glue p00_ter = p00_ret;
    register p00_tp_glue p00_rep = P00_TP_GLUE_INITIALIZER(p00_tp->p00_init, p00_tp_tick_get());
    if (p00_tp_cmpxchg(&p00_tp->p00_val, &p00_ter, p00_rep))
      p00_ret = p00_rep;
    else
      p00_ret = p00_ter;
  }
  return p00_ret;
}

/**
 ** @brief Set to new value @a p00_val and return previous value.
 **/
p99_inline
p00_tp_glue p99_tp_xchg(p99_tp volatile* p00_tp, void* p00_val) {
  p00_tp_glue p00_ret
    = P99_LIKELY(p00_tp)
      ? atomic_load_explicit(&p00_tp->p00_val, memory_order_consume)
      : (p00_tp_glue)P00_TP_GLUE_INITIALIZER((void*)0, p00_tp_tick_get());
  if (P99_LIKELY(p00_tp)) {
    register p00_tp_glue p00_rep = P00_TP_GLUE_INITIALIZER(p00_val, p00_tp_tick_get());
    while (!p00_tp_cmpxchg(&p00_tp->p00_val, &p00_ret, p00_rep));
    /* if this p99_tp has not been used before, return the value that
       p99_tp_get would have returned. */
    if (P99_UNLIKELY(!p00_tp_i2i(p00_ret))) {
      p00_ret = (p00_tp_glue)P00_TP_GLUE_INITIALIZER(p00_tp->p00_init, p00_tp_tick_get());
    }
  }
  return p00_ret;
}

/**
 ** @brief Load the value of @a p00_tp into the state variable and
 ** prepare it to commit value @a p00_p later.
 **/
p99_inline
p99_tp_state p99_tp_state_initializer(register p99_tp volatile*const p00_tp, register void*const p00_p) {
  return (p99_tp_state) {
    .p00_val = p00_tp_get(p00_tp),
     .p00_next = P00_TP_GLUE_INITIALIZER(p00_p, p00_tp_tick_get()),
      .p00_tp = p00_tp,
  };
}

p99_inline
void * p99_tp_state_get(register p99_tp_state volatile*const p00_state) {
  return P99_LIKELY(p00_state) ? p00_tp_i2p(p00_state->p00_val) : 0;
}

p99_inline
void * p99_tp_get(register p99_tp volatile*const p00_tp) {
  return p00_tp_i2p(p00_tp_get(p00_tp));
}

p99_inline
void p99_tp_state_set(register p99_tp_state volatile*const p00_state, register void*const p00_p) {
  if (P99_LIKELY(p00_state)) p00_state->p00_next = p00_tp_p2i(p00_p, p00_tp_i2i(p00_state->p00_next));
}

p99_inline
bool p99_tp_state_commit(register p99_tp_state volatile*const p00_state) {
  return P99_LIKELY(p00_state)
         ? p00_tp_cmpxchg(&p00_state->p00_tp->p00_val, &p00_state->p00_val, p00_state->p00_next)
         : false;
}

p99_inline
bool p99_tp_state_check(register p99_tp_state volatile*const p00_state) {
  return P99_LIKELY(p00_state)
         ? p00_tp_cmpxchg(&p00_state->p00_tp->p00_val, &p00_state->p00_val, p00_state->p00_val)
         : 0;
}

# define P99_TP(T) P99_PASTE2(p00_tp_, T)
# define P99_TP_STATE(T) P99_PASTE2(p00_tp_glue_, T)

P00_DOCUMENT_TYPE_ARGUMENT(P99_TP_DECLARE, 0)
# define P99_TP_DECLARE(T)                                       \
typedef union P99_TP(T) P99_TP(T);                               \
typedef union P99_TP_STATE(T) P99_TP_STATE(T);                   \
union P99_TP(T) {                                                \
  p99_tp p00_tp;                                                 \
  T p00_dum;                /* we only need this for its type */ \
  P99_TP_STATE(T)* p00_mud; /* we only need this for its type */ \
  max_align_t p00_align;    /* ensure maximal alignment       */ \
};                                                               \
union P99_TP_STATE(T) {                                          \
  p99_tp_state p00_st;                                           \
  T p00_dum;             /* we only need this for its type */    \
  P99_TP(T)* p00_mud;    /* we only need this for its type */    \
  max_align_t p00_align; /* ensure maximal alignment       */    \
}

# define P99_TP_TYPE(TP) __typeof__(*(TP)->p00_dum)
# define P99_TP_TYPE_STATE(TP) __typeof__(*(TP)->p00_mud)
# define P99_TP_STATE_TYPE(TPS) __typeof__(*(TPS)->p00_dum)


# define P99_TP_INITIALIZER(VAL) { .p00_tp = P00_TP_INITIALIZER(VAL), }

p99_inline
void p00_tp_init(register p99_tp volatile*const p00_el, register void*const p00_val) {
  if (P99_LIKELY(p00_el)) {
    atomic_init(&p00_el->p00_val, p00_tp_p2i(p00_val, p00_tp_tick_get()));
  }
}

# define p99_tp_init(EL, VAL)                                    \
p99_extension ({                                                 \
    register __typeof__(EL) const p00_el = (EL);                 \
    if (P99_LIKELY(p00_el)) p00_tp_init(&p00_el->p00_tp, (VAL)); \
    p00_el;                                                      \
  })

/**
 ** @brief Load the value of @a TP into the state variable.
 **
 ** @see P99_TP_STATE_COMMIT to commit value @a P, later
 **
 ** @see P99_TP_STATE_CHECK to check if the such initialized state is
 ** still consistent with @a TP
 **/
#define P99_TP_STATE_INITIALIZER(TP, P)                          \
p99_extension ({                                                 \
    P99_MACRO_VAR(p00_tp, (TP));                                 \
    /* ensure that P is assignment compatible to the */          \
    /* base type, and that the return can't be used as lvalue */ \
    register P99_TP_TYPE(p00_tp)* const p00_p = (P);             \
    register P99_TP_TYPE_STATE(p00_tp) const p00_r = {           \
      .p00_st =                                                  \
      p00_tp                                                     \
      ? p99_tp_state_initializer(&p00_tp->p00_tp, p00_p)         \
      : (p99_tp_state)P99_INIT,                                  \
    };                                                           \
    p00_r;                                                       \
})

/**
 ** @brief Unconditionally exchange the value of @a TP to @a VAL and
 ** return the previous value.
 **/
#define P99_TP_XCHG(TP, VAL)                                            \
p99_extension ({                                                        \
    P99_MACRO_VAR(p00_tp, (TP));                                        \
    /* ensure that the pointers that are converted to the */            \
    /* base type, and that the return can't be used as lvalue */        \
    register P99_TP_TYPE(p00_tp)* const p00_val = (VAL);                \
    register P99_TP_TYPE(p00_tp)* const p00_r                           \
      = p00_tp ? p00_tp_i2p(p99_tp_xchg(&p00_tp->p00_tp, p00_val)) : 0; \
    p00_r;                                                              \
})

/**
 ** @brief Unconditionally return the value of @a TP.
 **/
#define P99_TP_GET(TP)                                             \
p99_extension ({                                                   \
    P99_MACRO_VAR(p00_tp, (TP));                                   \
    /* ensure that pointer that is returned is converted to the */ \
    /* base type, and that the return can't be used as lvalue */   \
    register P99_TP_TYPE(p00_tp)* const p00_r                      \
      = p00_tp ? p99_tp_get(&p00_tp->p00_tp) : 0;                  \
    p00_r;                                                         \
})

/**
 ** @brief Return the value the underlying tagged pointer of @a TPS as
 ** it was found when initializing @a TPS.
 **
 ** @see P99_TP_STATE_CHECK to know if that returned value is still
 ** valid.
 **/
#define P99_TP_STATE_GET(TPS)                                      \
p99_extension ({                                                   \
    P99_MACRO_VAR(p00_tps, (TPS));                                 \
    /* ensure that pointer that is returned is converted to the */ \
    /* base type, and that the return can't be used as lvalue */   \
    register P99_TP_STATE_TYPE(p00_tps)* const p00_r               \
      = p00_tps ? p99_tp_state_get(&p00_tps->p00_st) : 0;          \
    p00_r;                                                         \
})


/**
 ** @brief Change the value to which the tagged pointer will be
 ** updated.
 **/
#define P99_TP_STATE_SET(TPS, P)                               \
do {                                                           \
    P99_MACRO_VAR(p00_tps, (TPS));                             \
    /* ensure that P is assignment compatible to the */        \
    /* base type.                                    */        \
    register P99_TP_STATE_TYPE(p00_tps)*const p00_p = (P);     \
    if (p00_tps) p99_tp_state_set(&p00_tps->p00_st, p00_p);    \
} while (false)

/**
 ** @brief Commit the registered value change to the underlying tagged
 ** pointer.
 **
 ** @return @c true if the commit was succesful, @c false otherwise.
 **/
#define P99_TP_STATE_COMMIT(TPS)                               \
p99_extension ({                                               \
 P99_MACRO_VAR(p00_tps, (TPS));                                \
 register bool const p00_r                                     \
 = p00_tps ? p99_tp_state_commit(&p00_tps->p00_st) : false;    \
 p00_r;                                                        \
})

/**
 ** @brief Check if the registered value is still consistent with the
 ** underlying tagged pointer.
 **
 ** @return @c true if the value is still consistent, @c false
 ** otherwise.
 **/
#define P99_TP_STATE_CHECK(TPS)                                   \
p99_extension ({                                                  \
    P99_MACRO_VAR(p00_tps, (TPS));                                \
    register bool const p00_r                                     \
      = p00_tps ? p99_tp_state_check(&(p00_tps)->p00_st) : false; \
    p00_r;                                                        \
  })


#define P99_REF_ACCOUNT(REF)                                                        \
p99_extension ({                                                                    \
    P99_MACRO_VAR(p00_ref, (REF));                                                  \
    /* ensure that the pointer is converted to the */                               \
    /* base type, and that the return can't be used as lvalue */                    \
    register __typeof__(p00_ref) const p00_r = p00_ref;                             \
    if (p00_r) atomic_fetch_add_explicit(&p00_r->p99_cnt, 1, memory_order_acq_rel); \
    p00_r;                                                                          \
})

#define P99_TP_REF_ACCOUNT(TP, REF)                                                 \
p99_extension ({                                                                    \
    P99_MACRO_VAR(p00_tp, (TP));                                                    \
    /* ensure that pointer that is returned is converted to the */                  \
    /* base type, and that the return can't be used as lvalue */                    \
    register P99_TP_TYPE(p00_tp)* const p00_r = (REF);                              \
    if (p00_r) atomic_fetch_add_explicit(&p00_r->p99_cnt, 1, memory_order_acq_rel); \
    p00_r;                                                                          \
})

#define P99_REF_DISCOUNT(REF, DELETE)                                                        \
p99_extension ({                                                                             \
    P99_MACRO_VAR(p00_ref, (REF));                                                           \
    register void (*const p00_d)(__typeof__(*p00_ref) const*)                                \
      = (DELETE);                                                                            \
    /* ensure that the pointer is converted to the */                                        \
    /* base type, and that the return can't be used as lvalue */                             \
    register __typeof__(*p00_ref)*const p00_r = p00_ref;                                     \
    if (p00_r && (atomic_fetch_sub_explicit(&p00_r->p99_cnt, 1, memory_order_acq_rel) == 1)) \
      p00_d(p00_r);                                                                          \
    p00_r;                                                                                   \
})

#define P99_TP_REF_INITIALIZER(VAL, ACCOUNT) P99_TP_INITIALIZER(P99_GENERIC_NULLPTR_CONSTANT(VAL, (void*)0, ACCOUNT(VAL)))

#define P00_TP_REF_INIT2(TP, VAL)                                  \
p99_extension ({                                                   \
    P99_MACRO_VAR(p00_tp, (TP));                                   \
    /* ensure that pointer that is returned is converted to the */ \
    /* base type, and that the return can't be used as lvalue */   \
    register P99_TP_TYPE(p00_tp)* const p00_val = (VAL);           \
    p99_tp_init(p00_tp, P99_REF_ACCOUNT(p00_val));                 \
})


#define P00_TP_REF_INIT1(TP) p99_tp_init(TP, 0)

#define P99_TP_REF_INIT(...)                                   \
P99_IF_LT(P99_NARG(__VA_ARGS__), 2)                            \
(P00_TP_REF_INIT1(__VA_ARGS__))                                \
(P00_TP_REF_INIT2(__VA_ARGS__))

#define P99_TP_REF_REPLACE(TP, SP, DELETE)                         \
P99_REF_DISCOUNT(P99_TP_XCHG((TP), P99_REF_ACCOUNT(SP)), (DELETE))

#define P99_TP_REF_MV(TP, SP, DELETE)                               \
P99_REF_DISCOUNT(P99_TP_XCHG((TP), P99_TP_XCHG((SP), 0)), (DELETE))

#define P99_TP_REF_DESTROY(TP, DELETE)                         \
(void)P99_REF_DISCOUNT(P99_TP_XCHG((TP), 0), (DELETE))


/**
 ** @brief Declare a reference counter type for type @a T
 **
 ** @a T should be a @c struct that contains a field
 ** @code
 ** _Atomic(size_t) p99_cnt;
 ** @endcode
 **
 ** that is used as a reference counter. On initialization this
 ** counter must be set to @c 0.
 **
 ** In addition the following function must be provided:
 **
 ** @code
 ** void T ## _delete(T const*);
 ** @endcode
 **
 ** This function should take a pointer to an object of type @a T,
 ** destroy its contents (if necessary) and then call @c free on that
 ** pointer.
 **
 ** @warning A type @a T that is administrated with that should never
 ** be allocated other than dynamically through @c malloc (or better
 ** ::P99_NEW) and friends.
 **
 ** @see P99_TP_REF_FUNCTIONS for the macro that generates the @c
 ** inline functions that are needed for this to work
 **
 ** @see P99_TP_REF_DEFINE to instantiate all functions
 **
 ** @see P99_DECLARE_DELETE
 ** @see P99_DEFINE_DELETE
 ** @see P99_NEW
 **/
P00_DOCUMENT_TYPE_ARGUMENT(P99_TP_REF_DECLARE, 0)
#ifdef P00_DOXYGEN
#define P99_TP_REF_DECLARE(T)                                                              \
typedef struct T ## _ref T ## _ref;                                                        \
 /** \brief A reference to an object of type T **/                                         \
 /** \remark This is an opaque object type, only use it through the related functions. **/ \
 /** \see P99_TP_REF_FUNCTIONS **/                                                         \
struct T ## _ref {                                                                         \
  T* p00_ref;                                                                              \
}
#else
#define P99_TP_REF_DECLARE(T)                                  \
P99_POINTER_TYPE(T);                                           \
P99_TP_DECLARE(P99_PASTE2(T, _ptr));                           \
 /** @brief A reference to a @a T object **/                   \
typedef P99_TP(P99_PASTE2(T, _ptr)) P99_PASTE2(T, _ref)
#endif

P00_DOCUMENT_TYPE_ARGUMENT(P99_TP_REF_DEFINE, 0)
#define P99_TP_REF_DEFINE(T)                                                               \
P99_INSTANTIATE(T*, P99_PASTE2(T, _account), T*);                                          \
P99_INSTANTIATE(T*, P99_PASTE2(T, _discount), T*);                                         \
P99_INSTANTIATE(P99_PASTE2(T, _ref)*, P99_PASTE2(T, _ref_init), P99_PASTE2(T, _ref)*, T*); \
P99_INSTANTIATE(T*, P99_PASTE2(T, _ref_init_defarg_1), void);                              \
P99_INSTANTIATE(T*, P99_PASTE2(T, _ref_get), P99_PASTE2(T, _ref) volatile*);               \
P99_INSTANTIATE(T*, P99_PASTE2(T, _ref_replace), P99_PASTE2(T, _ref) volatile*, T*);       \
P99_INSTANTIATE(T*, P99_PASTE2(T, _ref_mv), P99_PASTE2(T, _ref) volatile*,                 \
                P99_PASTE2(T, _ref) volatile*);                                            \
P99_INSTANTIATE(T*, P99_PASTE2(T, _ref_assign), P99_PASTE2(T, _ref) volatile*,             \
                P99_PASTE2(T, _ref) volatile*);                                            \
P99_INSTANTIATE(void, P99_PASTE2(T, _ref_destroy), P99_PASTE2(T, _ref)*)

#ifdef P00_DOXYGEN
P00_DOCUMENT_TYPE_ARGUMENT(P99_TP_REF_FUNCTIONS, 0)
#define P99_TP_REF_FUNCTIONS(T)                                                                                                      \
  /** \brief used for reference counting **/                                                                                         \
  /** \related T **/                                                                                                                 \
inline T* P99_PASTE2(T, _account)(T*){}                                                                                              \
 /** \brief used for reference counting **/                                                                                          \
 /** \remark may destroy the object if the reference count falls to 0 **/                                                            \
 /** \related T **/                                                                                                                  \
inline T* P99_PASTE2(T, _discount)(T*){}                                                                                             \
 /** \brief initialize a reference count **/                                                                                         \
 /** \remark If ::P99_CALL_DEFARG is used to provide defaults for the arguments, the second argument defaults to \c 0 if omitted **/ \
 /** \related T ## _ref **/                                                                                                          \
inline P99_PASTE2(T, _ref)* P99_PASTE2(T, _ref_init)(P99_PASTE2(T, _ref)*, T*){}                                                     \
 /** \brief provide a default argument for ::T ## _ref_init **/                                                                      \
 /** \see ::P99_CALL_DEFARG **/                                                                                                      \
 /** \related T ## _ref **/                                                                                                          \
inline T* P99_PASTE2(T, _ref_init_defarg_1)(void){}                                                                                  \
 /** \brief get the value of a reference **/                                                                                         \
 /** \return the pointer to the object that is handled **/                                                                           \
 /** \related T ## _ref **/                                                                                                          \
inline T* P99_PASTE2(T, _ref_get)(P99_PASTE2(T, _ref) volatile*){}                                                                   \
 /** \brief replace the value of a reference **/                                                                                     \
 /** \return the previous pointer before replacement **/                                                                             \
 /** \related T ## _ref **/                                                                                                          \
inline T* P99_PASTE2(T, _ref_replace)(P99_PASTE2(T, _ref) volatile*, T*){}                                                           \
 /** \brief replace the value of a reference by that of the second argument **/                                                      \
 /** \remark sets the value of the second argument to \c 0 **/                                                                       \
 /** \return the previous pointer before replacement **/                                                                             \
 /** \related T ## _ref **/                                                                                                          \
inline T* P99_PASTE2(T, _ref_mv)(P99_PASTE2(T, _ref) volatile*,                                                                      \
                                 P99_PASTE2(T, _ref) volatile*){}                                                                    \
 /** \brief replace the value of a reference by that of the second argument **/                                                      \
 /** \remark the value of the second argument remains untouched **/                                                                  \
 /** \return the previous pointer before replacement **/                                                                             \
 /** \related T ## _ref **/                                                                                                          \
inline T* P99_PASTE2(T, _ref_assign)(P99_PASTE2(T, _ref) volatile*,                                                                  \
                                     P99_PASTE2(T, _ref) volatile*){}                                                                \
 /** \brief destroy a reference object **/                                                                                           \
 /** \remark this should always be called at the end of the lifetime of a T ## _ref object **/                                       \
 /** \related T ## _ref **/                                                                                                          \
inline void P99_PASTE2(T, _ref_destroy)(P99_PASTE2(T, _ref)*) {}                                                                     \
P99_MACRO_END(P99_TP_REF_FUNCTIONS)

#else
P00_DOCUMENT_TYPE_ARGUMENT(P99_TP_REF_FUNCTIONS, 0)
#define P99_TP_REF_FUNCTIONS(T)                                                       \
                                                                                      \
  inline                                                                              \
  T*                                                                                  \
  P99_PASTE2(T, _account)(T* p00_el) {                                                \
    return P99_REF_ACCOUNT(p00_el);                                                   \
  }                                                                                   \
                                                                                      \
  inline                                                                              \
  T*                                                                                  \
  P99_PASTE2(T, _discount)(T* p00_el) {                                               \
    return P99_REF_DISCOUNT(p00_el, P99_PASTE2(T, _delete));                          \
  }                                                                                   \
                                                                                      \
  inline                                                                              \
  P99_PASTE2(T, _ref)* P99_PASTE2(T, _ref_init)(P99_PASTE2(T, _ref)* el, T* p00_v) {  \
    return P99_TP_REF_INIT(el, p00_v);                                                \
  }                                                                                   \
                                                                                      \
  inline                                                                              \
  T* P99_PASTE2(T, _ref_init_defarg_1)(void) {                                        \
    return 0;                                                                         \
  }                                                                                   \
                                                                                      \
  inline                                                                              \
  T* P99_PASTE2(T, _ref_get)(P99_PASTE2(T, _ref) volatile* p00_ref) {                 \
    return P99_TP_GET(p00_ref);                                                       \
  }                                                                                   \
                                                                                      \
  inline                                                                              \
  T* P99_PASTE2(T, _ref_replace)(P99_PASTE2(T, _ref) volatile* p00_tar, T* p00_sou) { \
    return P99_TP_REF_REPLACE(p00_tar, p00_sou, P99_PASTE2(T, _delete));              \
  }                                                                                   \
                                                                                      \
  inline                                                                              \
  T* P99_PASTE2(T, _ref_mv)(P99_PASTE2(T, _ref) volatile* p00_tar,                    \
                            P99_PASTE2(T, _ref) volatile* p00_sou) {                  \
    return P99_TP_REF_MV(p00_tar, p00_sou, P99_PASTE2(T, _delete));                   \
  }                                                                                   \
                                                                                      \
  inline                                                                              \
  T* P99_PASTE2(T, _ref_assign)(P99_PASTE2(T, _ref) volatile* p00_tar,                \
                                P99_PASTE2(T, _ref) volatile* p00_sou) {              \
    return P99_TP_REF_REPLACE(p00_tar, P99_TP_GET(p00_sou), P99_PASTE2(T, _delete));  \
  }                                                                                   \
                                                                                      \
  inline                                                                              \
  void P99_PASTE2(T, _ref_destroy)(P99_PASTE2(T, _ref)* p00_ref) {                    \
    P99_TP_REF_DESTROY(p00_ref, P99_PASTE2(T, _delete));                              \
  }                                                                                   \
                                                                                      \
P99_MACRO_END(P99_TP_REF_FUNCTIONS)

#endif


#endif
