/* This may look like nonsense, but it really is -*- mode: C -*-              */
/*                                                                            */
/* Except for parts copied from previous work and as explicitly stated below, */
/* the authors and copyright holders for this work are as follows:            */
/* (C) copyright  2011-2012, 2014 Jens Gustedt, INRIA, France                 */
/* (C) copyright  2012 William Morris                                         */
/*                                                                            */
/* This file is free software; it is part of the P99 project.                 */
/* You can redistribute it and/or modify it under the terms of the QPL as     */
/* given in the file LICENSE. It is distributed without any warranty;         */
/* without even the implied warranty of merchantability or fitness for a      */
/* particular purpose.                                                        */
/*                                                                            */
#ifndef     P99_TYPENAMES_H_
# define    P99_TYPENAMES_H_

/**
 ** @file
 ** @brief Declare types derived from the standard types.
 **/

#include "p99_compiler.h"
#include "p99_type.h"

/** @addtogroup one_token One token type names
 ** @brief A bunch of types that are one-token synonyms for standard types.
 ** @{
 **/

P00_ONE_TOK(unsigned long, ulong);
P00_ONE_TOK(signed long, slong);
P00_ONE_TOK(unsigned int, uint);
P00_ONE_TOK(signed int, sint);
P00_ONE_TOK(unsigned short, ushort);
P00_ONE_TOK(signed short, sshort);
P00_ONE_TOK(unsigned char, uchar);
P00_ONE_TOK(signed char, schar);
P00_ONE_TOK(long long, llong);
P00_ONE_TOK(signed long long, sllong);
P00_ONE_TOK(unsigned long long, ullong);
P00_ONE_TOK(long double, ldouble);
#ifndef __STDC_NO_COMPLEX__
P00_ONE_TOK(float _Complex, cfloat);
P00_ONE_TOK(double _Complex, cdouble);
P00_ONE_TOK(long double _Complex, cldouble);
#endif

/**
 ** @}
 **/

/** @addtogroup typenames Type Names
 ** @brief A bunch of types that are derived from the
 ** standard types.
 **
 ** This is not included by default in p99.h
 ** @{
 **/



P99_POINTER_TYPE(void);
P99_POINTER_TYPE(float);
P99_POINTER_TYPE(double);
P99_POINTER_TYPE(ldouble);
#ifndef __STDC_NO_COMPLEX__
P99_POINTER_TYPE(cfloat);
P99_POINTER_TYPE(cdouble);
P99_POINTER_TYPE(cldouble);
#endif
P99_POINTER_TYPE(ullong);
P99_POINTER_TYPE(sllong);
P99_POINTER_TYPE(llong);
P99_POINTER_TYPE(long);
P99_POINTER_TYPE(ulong);
P99_POINTER_TYPE(slong);
P99_POINTER_TYPE(int);
P99_POINTER_TYPE(uint);
P99_POINTER_TYPE(sint);
P99_POINTER_TYPE(short);
P99_POINTER_TYPE(ushort);
P99_POINTER_TYPE(sshort);
P99_POINTER_TYPE(char);
P99_POINTER_TYPE(uchar);
P99_POINTER_TYPE(schar);

P99_POINTER_TYPE(signed);
P99_POINTER_TYPE(unsigned);

P99_POINTER_TYPE(size_t);
P99_POINTER_TYPE(intmax_t);
P99_POINTER_TYPE(uintmax_t);
P99_POINTER_TYPE(intptr_t);
P99_POINTER_TYPE(uintptr_t);
P99_POINTER_TYPE(ptrdiff_t);
P99_POINTER_TYPE(int8_t);
P99_POINTER_TYPE(uint8_t);
P99_POINTER_TYPE(int16_t);
P99_POINTER_TYPE(uint16_t);
P99_POINTER_TYPE(int32_t);
P99_POINTER_TYPE(uint32_t);
P99_POINTER_TYPE(int64_t);
P99_POINTER_TYPE(uint64_t);


P99_PLAIN_TYPE(void_ptr);
P99_PLAIN_TYPE(void_cptr);

P99_DERIVED_TYPES(float);
P99_DERIVED_TYPES(double);
P99_DERIVED_TYPES(ldouble);
#ifndef __STDC_NO_COMPLEX__
P99_DERIVED_TYPES(cfloat);
P99_DERIVED_TYPES(cdouble);
P99_DERIVED_TYPES(cldouble);
#endif
P99_DERIVED_TYPES(ullong);
P99_DERIVED_TYPES(sllong);
P99_DERIVED_TYPES(llong);
P99_DERIVED_TYPES(ulong);
P99_DERIVED_TYPES(slong);
P99_DERIVED_TYPES(long);
P99_DERIVED_TYPES(uint);
P99_DERIVED_TYPES(sint);
P99_DERIVED_TYPES(int);
P99_DERIVED_TYPES(ushort);
P99_DERIVED_TYPES(short);
P99_DERIVED_TYPES(uchar);
P99_DERIVED_TYPES(schar);
P99_DERIVED_TYPES(char);

P99_DERIVED_TYPES(unsigned);
P99_DERIVED_TYPES(signed);

P99_DERIVED_TYPES(size_t);
P99_DERIVED_TYPES(intmax_t);
P99_DERIVED_TYPES(uintmax_t);
P99_DERIVED_TYPES(intptr_t);
P99_DERIVED_TYPES(uintptr_t);
P99_DERIVED_TYPES(ptrdiff_t);
P99_DERIVED_TYPES(int8_t);
P99_DERIVED_TYPES(uint8_t);
P99_DERIVED_TYPES(int16_t);
P99_DERIVED_TYPES(uint16_t);
P99_DERIVED_TYPES(int32_t);
P99_DERIVED_TYPES(uint32_t);
P99_DERIVED_TYPES(int64_t);
P99_DERIVED_TYPES(uint64_t);

/**
 ** @}
 **/

/** @addtogroup bool_specials bool specials
 ** @brief @c bool must be handled specially since it is not a @c
 ** typedef but a macro
 ** @{
 **/
P99_POINTER_TYPE(_Bool);
P99_DERIVED_TYPES(_Bool);
#define bool_cptr_delete _Bool_cptr_delete
#define bool_cptr_destroy _Bool_cptr_destroy
#define bool_cptr_init _Bool_cptr_init
#define bool_cptr_vdelete _Bool_cptr_vdelete
#define bool_cptr_vnew _Bool_cptr_vnew
#define bool_cptr_vrealloc _Bool_cptr_vrealloc
#define bool_delete _Bool_delete
#define bool_destroy _Bool_destroy
#define bool_init _Bool_init
#define bool_ptr_delete _Bool_ptr_delete
#define bool_ptr_destroy _Bool_ptr_destroy
#define bool_ptr_init _Bool_ptr_init
#define bool_ptr_vdelete _Bool_ptr_vdelete
#define bool_ptr_vnew _Bool_ptr_vnew
#define bool_ptr_vrealloc _Bool_ptr_vrealloc
#define bool_vdelete _Bool_vdelete
#define bool_vnew _Bool_vnew
#define bool_vrealloc _Bool_vrealloc
/**
 ** @}
 **/

#endif      /* !P99_TYPENAMES_H_ */
