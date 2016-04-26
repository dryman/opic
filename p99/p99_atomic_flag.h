/* This may look like nonsense, but it really is -*- mode: C -*-              */
/*                                                                            */
/* Except for parts copied from previous work and as explicitly stated below, */
/* the author and copyright holder for this work is                           */
/* (C) copyright  2013 Jens Gustedt, INRIA, France                            */
/*                                                                            */
/* This file is free software; it is part of the P99 project.                 */
/* You can redistribute it and/or modify it under the terms of the QPL as     */
/* given in the file LICENSE. It is distributed without any warranty;         */
/* without even the implied warranty of merchantability or fitness for a      */
/* particular purpose.                                                        */
/*                                                                            */
#ifndef P99_ATOMIC_FLAG_H_
#define P99_ATOMIC_FLAG_H_ 1

/**
 ** @brief extension: spin on @a p00_objp setting the flag until the state before was "clear"
 **
 ** This interprets an ::atomic_flag as a spinlock. State "clear"
 ** means unlocked and state "set" means locked.
 **
 ** This operation only guarantees acquire-consistency.
 **
 ** @related atomic_flag
 **/
p99_inline
void atomic_flag_lock(volatile atomic_flag *p00_objp) {
  while (atomic_flag_test_and_set_explicit(p00_objp, memory_order_acquire));
}

/**
 ** @brief extension: set the flag and return true if we are the first
 ** to do so
 **
 ** This interprets an ::atomic_flag as a spinlock. State "clear"
 ** means unlocked and state "set" means locked.
 **
 ** This operation only guarantees acquire-consistency.
 **
 ** @related atomic_flag
 **/
p99_inline
_Bool atomic_flag_trylock(volatile atomic_flag *p00_objp) {
  return !atomic_flag_test_and_set_explicit(p00_objp, memory_order_acquire);
}

/**
 ** @brief extension: clear the flag unconditionally
 **
 ** This operation only guarantees release-consistency.
 **
 ** @related atomic_flag
 **/
p99_inline
void atomic_flag_unlock(volatile atomic_flag *p00_objp) {
  atomic_flag_clear_explicit(p00_objp, memory_order_release);
}

/**
 ** @brief Protect the following block or statement as a critical
 ** section of the program by using @a FLAGP as a spinlock.
 **
 ** @param FLAGP is an expression that evaluates to a pointer to
 ** ::atomic_flag. The flag is used as a spinlock, so this is an
 ** active wait.
 **
 ** @remark @a FLAGP is only evaluated once at the beginning, so it
 ** would be safe to change it in the depending block or statement.
 **
 ** @warning Such a section should only contain a handful of
 ** statements.
 **
 ** @warning Such a section should not contain preliminary exits such
 ** as @c goto, @c break, @c return, @c longjmp, or ::P99_UNWIND etc.
 **
 ** Such a critical section is only protected against threads that try
 ** to enter this same critical section. Threads may well
 ** simultaneously be in different critical sections.
 **
 ** @see P99_MUTUAL_EXCLUDE that is more suited for larger sections.
 **/
#define P99_SPIN_EXCLUDE(FLAGP)   P00_SPIN_EXCLUDE(FLAGP, P99_UNIQ(flg))

#define P00_SPIN_EXCLUDE(FLAGP, ID)                            \
P00_BLK_START                                                  \
P00_BLK_DECL(register atomic_flag volatile*const, ID, (FLAGP)) \
P00_BLK_BEFAFT(atomic_flag_lock(ID),                           \
               atomic_flag_unlock(ID))                         \
P00_BLK_END

#endif
