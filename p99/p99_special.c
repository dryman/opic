/* This may look like nonsense, but it really is -*- mode: C -*-              */
/*                                                                            */
/* Except for parts copied from previous work and as explicitly stated below, */
/* the authors and copyright holders for this work are as follows:            */
/* (C) copyright  2011-2013 Jens Gustedt, INRIA, France                       */
/* (C) copyright  2012 William Morris                                         */
/*                                                                            */
/* This file is free software; it is part of the P99 project.                 */
/* You can redistribute it and/or modify it under the terms of the QPL as     */
/* given in the file LICENSE. It is distributed without any warranty;         */
/* without even the implied warranty of merchantability or fitness for a      */
/* particular purpose.                                                        */
/*                                                                            */
/** @file
 ** @brief This file just contains automatically produced information for doxygen.
 **
 ** It will usually be overwritten for any new release.
 **/

/**
 ** @page safety Safety of macro programming and pitfalls
 **
 ** Often we may hear arguments that function-like macros obfuscate
 ** the code, are dangerous, not maintainable, in short: the big
 ** evil.
 **
 ** I am convinced that this is just one of the many urban
 ** legends. Macros as such are not less safe than, say, the use of
 ** pointers or of a high quality sharpened kitchen knife.  And they
 ** belong to C as much as the <code>for</code> or the <code>++</code>
 ** operator.
 **
 ** Macros can make your code easier to read and to maintain,
 ** more precise and more efficient than would be possible by writing
 ** code "directly" without macros. It is all about how you write
 ** them, if you do that yourself, and how you use them.
 **
 ** As one example look at the following code:
 ** @code
 ** if (P99_ARE_ORDERED(<, a, b, c, d, e, f)) {
 **   // all are in order, do something special
 ** } else {
 **   // handle the base case
 ** }
 ** @endcode
 **  - This is readable: you have all the variables that are to be
 **    checked by the condition at one glance.
 **  - This is maintainable: just change a variable name in one place,
 **    deleted one or add one without problems.
 **  - This is precise and describes exactly what it does.
 **  - This is efficient since its replacement is exactly the
 **    expression that is needed for that task:
 ** @code
 ** ((a) < (b)) && ((b) < (c)) && ((c) < (d)) && ((d) < (e)) && ((e) < (f))
 ** @endcode
 ** which by itself is not very readable, is difficult to maintain and is
 ** not very explicit in its intentions.
 **
 ** In the example, part of the efficiency also comes from the fact
 ** that it is <em>not a function</em>. This is interesting if, for example,
 ** some of the variables in the list are of integer type and
 ** others are of floating type: promotions from integer type to floating
 ** type will only be performed where necessary in a comparison of two
 ** adjacent variables. In such a way we can profit of the exact
 ** comparison for integer types and can avoid the problems of
 ** rounding an integer to the next representable double. (Think of
 ** comparing <code>e = UINT64_MAX - 1</code> and <code>e =
 ** UINT64_MAX</code>.)
 **
 ** But, macros have pitfalls, and <em>one</em> important pitfall
 ** in particular: you don't see from a macro call if the arguments are
 ** evaluated multiple times or not. So if you have the habit of
 ** programming with side effects, you really have to be careful.
 **
 ** The simplest solution is avoidance: don't use expressions with
 ** side effects such as <code>++</code> as arguments to macros or
 ** functions. Really, don't do that.
 **
 ** If you are programming macros, you have to be more careful since
 ** you can't assume that everybody knows what she or he is doing. For
 ** P99 we have an automatic suite of scripts that tests if any of the
 ** macros that start with "P99_" evaluate their arguments multiple
 ** times. This is a bit tricky, special care has to be taken for
 ** macros that use the ternary operator <code>?:</code> and the @c
 ** sizeof operator:
 **
 **  - For the ternary operator, P99 has many cases where the condition is
 **    constant and only one branch is evaluated for its type.
 **  - <code>sizeof</code> is also special because its argument is evaluated
 **    mostly for its type and not for its value. There is
 **    one exception to that rule, namely variable length arrays, VLA.
 **
 ** The scripts mentioned above help us detect these and other special cases
 ** and the documentation of the corresponding P99 macros is then
 ** annotated with warnings and remarks that document the special
 ** behavior of these macros.
 **
 ** @see P00_DECLARE_ATOMIC_TYPE(0) for argument <code>1</code>, <code>2</code>.
 ** @see P99_AALLOC(T, VB, N) for argument <code>T</code>, <code>VB</code>.
 ** @see P99_AARG(TYPE, NAME, DIM, VAR) for argument <code>TYPE</code>, <code>DIM</code>.
 ** @see P99_AASSIGN(TARGET, SOURCE, N) for argument <code>TARGET</code>, <code>SOURCE</code>.
 ** @see P99_ACALL(ARR, N, TYPE) for arguments <code>ARR</code>, <code>N</code>, <code>TYPE</code>.
 ** @see P99_ACCESSORS(X, N) for argument <code>X</code>, <code>N</code>.
 ** @see P99_ACOPY(TYPE, N, ...) for argument <code>__VA_ARG__[0]</code>, <code>__VA_ARG__[2]</code>.
 ** @see P99_ALEN(ARR, N) for argument <code>ARR</code>, <code>N</code>.
 ** @see P99_ALENS(ARR, N) for argument <code>ARR</code>, <code>N</code>.
 ** @see P99_ANAME(NAME, DIM, VAR) for argument <code>NAME</code>, <code>VAR</code>.
 ** @see P99_ARE_EQ(FIRST, ...) for argument <code>FIRST</code>.
 ** @see P99_ARE_ORDERED(OP, ...) for arguments <code>OP</code>, <code>__VA_ARG__[0]</code>, <code>__VA_ARG__[1]</code>.
 ** @see P99_ASORT(TAB, ...) for argument <code>TAB</code>.
 ** @see P99_ASUB(X, T, N, L) for argument <code>T</code>.
 ** @see P99_ATOMIC_INHERIT(T) for argument <code>T</code>.
 ** @see P99_AVALUE(X, ...) for arguments <code>X</code>, <code>__VA_ARG__[0]</code>, <code>__VA_ARG__[1]</code>, <code>__VA_ARG__[2]</code>.
 ** @see P99_BIGFUNC(FUNC, M, ...) for argument <code>M</code>.
 ** @see P99_BIGOP(OP, M, ...) for argument <code>M</code>.
 ** @see P99_CALLOC(T, N) for argument <code>T</code>.
 ** @see P99_CALL_DEFARG(NAME, M, ...) for argument <code>M</code>.
 ** @see P99_CALL_DEFARG_LIST(NAME, M, ...) for argument <code>M</code>.
 ** @see P99_CALL_VA_ARG(NAME, M, T, ...) for argument <code>M</code>.
 ** @see P99_CASERANGE(START, ...) for argument <code>START</code>, <code>__VA_ARG__[0]</code>.
 ** @see P99_CA_CALL(NAME, ACHECKS, PCHECKS, ...) for arguments <code>ACHECKS</code>, <code>PCHECKS</code>, <code>__VA_ARG__[0]</code>, <code>__VA_ARG__[1]</code>, <code>__VA_ARG__[2]</code>.
 ** @see P99_CDIM(NAME, ...) for argument <code>NAME</code>.
 ** @see P99_CHOOSE5(xT, cc, cs, ci, cl, cll) for argument <code>xT</code>.
 ** @see P99_CONSTANT(T, NAME, INIT) for argument <code>NAME</code>.
 ** @see P99_DECLARE_ATOMIC(T, NAME) for argument <code>T</code>, <code>NAME</code>.
 ** @see P99_DECLARE_ATOMIC_LOCK_FREE(T, NAME) for argument <code>T</code>, <code>NAME</code>.
 ** @see P99_DECLARE_DELETE(T) for argument <code>T</code>.
 ** @see P99_DECLARE_ENUM(T, ...) for arguments <code>T</code>, <code>__VA_ARG__[0]</code>, <code>__VA_ARG__[1]</code>, <code>__VA_ARG__[2]</code>.
 ** @see P99_DECLARE_ENUM_GETNAME(T, ...) for arguments <code>T</code>, <code>__VA_ARG__[0]</code>, <code>__VA_ARG__[1]</code>, <code>__VA_ARG__[2]</code>.
 ** @see P99_DECLARE_ENUM_PARSE(T, ...) for arguments <code>T</code>, <code>__VA_ARG__[0]</code>, <code>__VA_ARG__[1]</code>, <code>__VA_ARG__[2]</code>.
 ** @see P99_DECLARE_INIT_ONCE(T, NAME, ARG) for arguments <code>T</code>, <code>NAME</code>, <code>ARG</code>.
 ** @see P99_DECLARE_INLINE_EXPRESSION(EXT, BASE, EXP, ...) for arguments <code>EXT</code>, <code>BASE</code>, <code>EXP</code>.
 ** @see P99_DECLARE_INLINE_EXPRESSIONS(NEPL, ...) for argument <code>NEPL</code>.
 ** @see P99_DECLARE_STRUCT(NAME) for argument <code>NAME</code>.
 ** @see P99_DECLARE_UNION(NAME) for argument <code>NAME</code>.
 ** @see P99_DEC_DOUBLE(...) for arguments <code>__VA_ARG__[1]</code>, <code>__VA_ARG__[2]</code>, <code>__VA_ARG__[4]</code>.
 ** @see P99_DEFINE_ENUM(T) for argument <code>T</code>.
 ** @see P99_DEFINE_UNION(NAME, ...) for arguments <code>NAME</code>, <code>__VA_ARG__[0]</code>, <code>__VA_ARG__[1]</code>, <code>__VA_ARG__[2]</code>.
 ** @see P99_DERIVED_TYPES(T) for argument <code>T</code>.
 ** @see P99_DESIGNATED(VAR, ...) for arguments <code>VAR</code>, <code>__VA_ARG__[0]</code>, <code>__VA_ARG__[1]</code>, <code>__VA_ARG__[2]</code>.
 ** @see P99_DO(TYPE, VAR, ...) for argument <code>TYPE</code>.
 ** @see P99_ENC_DECLARE(T, NAME) for argument <code>T</code>, <code>NAME</code>.
 ** @see P99_FCALLOC(T, F, N) for arguments <code>T</code>, <code>F</code>, <code>N</code>.
 ** @see P99_FHEAD(T, F, P) for argument <code>T</code>.
 ** @see P99_FIFO_APPEND(L, EL) for argument <code>L</code>, <code>EL</code>.
 ** @see P99_FIFO_CLEAR(L) for argument <code>L</code>.
 ** @see P99_FIFO_POP(L) for argument <code>L</code>.
 ** @see P99_FIFO_TABULATE(TYPE, TAB, L) for arguments <code>TYPE</code>, <code>TAB</code>, <code>L</code>.
 ** @see P99_FMALLOC(T, F, N) for arguments <code>T</code>, <code>F</code>, <code>N</code>.
 ** @see P99_FOR(NAME, N, OP, FUNC, ...) for arguments <code>NAME</code>, <code>N</code>, <code>FUNC</code>.
 ** @see P99_FORALL(NAME, ...) for argument <code>NAME</code>.
 ** @see P99_FORMAT(...) for argument <code>__VA_ARG__[0]</code>, <code>__VA_ARG__[2]</code>.
 ** @see P99_FORMATS(...) for arguments <code>__VA_ARG__[0]</code>, <code>__VA_ARG__[1]</code>, <code>__VA_ARG__[2]</code>.
 ** @see P99_FPRINTF(F, FORMAT, ...) for arguments <code>__VA_ARG__[0]</code>, <code>__VA_ARG__[1]</code>, <code>__VA_ARG__[2]</code>.
 ** @see P99_FREALLOC(P, T, F, N) for arguments <code>T</code>, <code>F</code>, <code>N</code>.
 ** @see P99_FSIZEOF(T, F, N) for arguments <code>T</code>, <code>F</code>, <code>N</code>.
 ** @see P99_FUTEX_COMPARE_EXCHANGE(FUTEX, ACT, EXPECTED, DESIRED, WAKEMIN, WAKEMAX) for argument <code>ACT</code>.
 ** @see P99_GENERIC(...) for argument <code>__VA_ARG__[0]</code>, <code>__VA_ARG__[2]</code>.
 ** @see P99_GENERIC_INTEGRAL_CONSTANT(EXP, TRUE, FALSE) for argument <code>EXP</code>, <code>FALSE</code>.
 ** @see P99_GENERIC_LIT(...) for argument <code>__VA_ARG__[0]</code>, <code>__VA_ARG__[2]</code>.
 ** @see P99_GENERIC_NULLPTR(PEXP, TRUE, FALSE) for arguments <code>PEXP</code>, <code>TRUE</code>, <code>FALSE</code>.
 ** @see P99_GENERIC_PCONST(PEXP, NCONST, CONST) for argument <code>PEXP</code>.
 ** @see P99_GENERIC_PCONSTVOLATILE(PEXP, NON, FULL) for argument <code>PEXP</code>.
 ** @see P99_GENERIC_PQUALIFIED(PEXP, ...) for arguments <code>PEXP</code>, <code>__VA_ARG__[0]</code>, <code>__VA_ARG__[1]</code>, <code>__VA_ARG__[2]</code>.
 ** @see P99_GENERIC_PVOLATILE(PEXP, NVOLATILE, VOLATILE) for argument <code>PEXP</code>.
 ** @see P99_GENERIC_SIZE(UI, ...) for arguments <code>UI</code>, <code>__VA_ARG__[1]</code>, <code>__VA_ARG__[2]</code>.
 ** @see P99_GENERIC_SIZE_LIT(UI, ...) for arguments <code>UI</code>, <code>__VA_ARG__[1]</code>, <code>__VA_ARG__[2]</code>.
 ** @see P99_GENERIC_TCONST(T, NCONST, CONST) for argument <code>T</code>.
 ** @see P99_GENERIC_TCONSTVOLATILE(T, NON, FULL) for argument <code>T</code>.
 ** @see P99_GENERIC_TQUALIFIED(T, ...) for argument <code>T</code>.
 ** @see P99_GENERIC_TVOLATILE(T, NVOLATILE, VOLATILE) for argument <code>T</code>.
 ** @see P99_GEN_ABS(A) for argument <code>A</code>.
 ** @see P99_GEN_EXPR(BASE, EXPR, ...) for argument <code>BASE</code>, <code>EXPR</code>.
 ** @see P99_GEN_MAX(A, B) for argument <code>A</code>, <code>B</code>.
 ** @see P99_GEN_MIN(A, B) for argument <code>A</code>, <code>B</code>.
 ** @see P99_GEN_SIN(A) for argument <code>A</code>.
 ** @see P99_GETOPT_DECLARE(CHAR, T, ...) for argument <code>T</code>, <code>__VA_ARG__[0]</code>.
 ** @see P99_GETOPT_DEFINE(CHAR, T, ...) for argument <code>T</code>, <code>__VA_ARG__[0]</code>.
 ** @see P99_GUARDED_BLOCK(T, NAME, INITIAL, BEFORE, AFTER) for arguments <code>T</code>, <code>NAME</code>, <code>AFTER</code>.
 ** @see P99_HEX_DOUBLE(...) for arguments <code>__VA_ARG__[1]</code>, <code>__VA_ARG__[2]</code>, <code>__VA_ARG__[4]</code>.
 ** @see P99_HTONL(X) for argument <code>X</code>, <code>1</code>.
 ** @see P99_HTONS(X) for argument <code>X</code>, <code>1</code>.
 ** @see P99_INITIALIZE(X, L) for argument <code>X</code>, <code>L</code>.
 ** @see P99_INVARIANT(EXPR) for argument <code>EXPR</code>.
 ** @see P99_IN_RANGE(R, S, L) for argument <code>R</code>, <code>S</code>.
 ** @see P99_IPOW(N, X) for argument <code>N</code>, <code>X</code>.
 ** @see P99_ISSIGNED(T) for argument <code>T</code>.
 ** @see P99_IS_INF(FIRST, ...) for argument <code>FIRST</code>.
 ** @see P99_IS_INTEGRAL_CONSTANT(EXP) for argument <code>EXP</code>.
 ** @see P99_IS_MAX(FIRST, ...) for argument <code>FIRST</code>.
 ** @see P99_IS_MIN(FIRST, ...) for argument <code>FIRST</code>.
 ** @see P99_IS_NULLPTR(PEXP) for argument <code>PEXP</code>.
 ** @see P99_IS_ONE(FIRST, ...) for argument <code>FIRST</code>.
 ** @see P99_IS_SUP(FIRST, ...) for argument <code>FIRST</code>.
 ** @see P99_JOIN(...) for arguments <code>__VA_ARG__[0]</code>, <code>__VA_ARG__[1]</code>, <code>__VA_ARG__[2]</code>.
 ** @see P99_LCOPY(TYPE, VAR, ...) for arguments <code>TYPE</code>, <code>VAR</code>, <code>__VA_ARG__[0]</code>, <code>__VA_ARG__[1]</code>, <code>__VA_ARG__[2]</code>.
 ** @see P99_LIFO_CLEAR(L) for argument <code>L</code>.
 ** @see P99_LIFO_DECLARE(T) for argument <code>T</code>.
 ** @see P99_LIFO_POP(L) for argument <code>L</code>.
 ** @see P99_LIFO_PUSH(L, EL) for argument <code>L</code>, <code>EL</code>.
 ** @see P99_LIFO_TABULATE(TYPE, TAB, L) for arguments <code>TYPE</code>, <code>TAB</code>, <code>L</code>.
 ** @see P99_LIFO_TOP(L) for argument <code>L</code>.
 ** @see P99_LITERAL(...) for arguments <code>__VA_ARG__[0]</code>, <code>__VA_ARG__[1]</code>, <code>__VA_ARG__[2]</code>, <code>__VA_ARG__[3]</code>.
 ** @see P99_MACRO_PVAR(NAME, ...) for argument <code>NAME</code>, <code>__VA_ARG__[0]</code>.
 ** @see P99_MACRO_VAR(NAME, ...) for argument <code>NAME</code>, <code>__VA_ARG__[0]</code>.
 ** @see P99_MAC_ARGS(...) for arguments <code>__VA_ARG__[0]</code>, <code>__VA_ARG__[1]</code>, <code>__VA_ARG__[2]</code>.
 ** @see P99_MAXOF(0) for argument <code>1</code>.
 ** @see P99_MEMSET(TA, SO, N) for argument <code>SO</code>.
 ** @see P99_MEMZERO(T, TA, N) for argument <code>T</code>.
 ** @see P99_MINOF(A, B) for argument <code>A</code>, <code>B</code>.
 ** @see P99_MUTUAL_EXCLUDE(MUT) for argument <code>MUT</code>.
 ** @see P99_NAME(N, NAME) for argument <code>N</code>.
 ** @see P99_NTOHL(X) for argument <code>X</code>.
 ** @see P99_NTOHS(X) for argument <code>X</code>.
 ** @see P99_OBJLEN(X, ...) for arguments <code>X</code>, <code>__VA_ARG__[0]</code>, <code>__VA_ARG__[1]</code>, <code>__VA_ARG__[2]</code>.
 ** @see P99_OBJSIZE(X, ...) for arguments <code>X</code>, <code>__VA_ARG__[0]</code>, <code>__VA_ARG__[1]</code>, <code>__VA_ARG__[2]</code>.
 ** @see P99_OVALUE(X, ...) for arguments <code>X</code>, <code>__VA_ARG__[0]</code>, <code>__VA_ARG__[1]</code>, <code>__VA_ARG__[2]</code>.
 ** @see P99_PARALLEL_DO(TYPE, VAR, ...) for argument <code>TYPE</code>.
 ** @see P99_PARALLEL_FORALL(NAME, ...) for argument <code>NAME</code>.
 ** @see P99_PLAIN_TYPE(T) for argument <code>T</code>.
 ** @see P99_POINTER_TYPE(T) for argument <code>T</code>.
 ** @see P99_POSS(N) for argument <code>N</code>.
 ** @see P99_PRAGMA_DO(PRAG, TYPE, VAR, ...) for argument <code>TYPE</code>.
 ** @see P99_PRI(xT, F, LEN) for argument <code>xT</code>.
 ** @see P99_PRINTF(FORMAT, ...) for arguments <code>__VA_ARG__[0]</code>, <code>__VA_ARG__[1]</code>, <code>__VA_ARG__[2]</code>.
 ** @see P99_PROTOTYPE(...) for argument <code>__VA_ARG__[0]</code>, <code>__VA_ARG__[2]</code>.
 ** @see P99_PZERO(X, N) for argument <code>X</code>.
 ** @see P99_QSORT(TAB, NB, ...) for argument <code>TAB</code>.
 ** @see P99_QVALUE(X) for argument <code>X</code>.
 ** @see P99_REP(...) for arguments <code>__VA_ARG__[0]</code>, <code>__VA_ARG__[1]</code>, <code>__VA_ARG__[2]</code>.
 ** @see P99_REPEAT(MACRO, N) for argument <code>MACRO</code>, <code>N</code>.
 ** @see P99_SEA(MACRO, ...) for argument <code>MACRO</code>.
 ** @see P99_SEM(MACRO, ...) for argument <code>MACRO</code>.
 ** @see P99_SEP(MACRO, ...) for argument <code>MACRO</code>.
 ** @see P99_SEQ(MACRO, ...) for argument <code>MACRO</code>.
 ** @see P99_SER(MACRO, ...) for argument <code>MACRO</code>.
 ** @see P99_SIGNED_REPRESENTATION(T) for argument <code>T</code>.
 ** @see P99_SIZE_CHOICE(UI, YES, NO, ...) for arguments <code>UI</code>, <code>YES</code>, <code>NO</code>.
 ** @see P99_SIZE_INDICATOR(UI, ...) for argument <code>UI</code>.
 ** @see P99_SNPRINTF(S, N, FORMAT, ...) for arguments <code>__VA_ARG__[0]</code>, <code>__VA_ARG__[1]</code>, <code>__VA_ARG__[2]</code>.
 ** @see P99_SPRINTF(S, FORMAT, ...) for arguments <code>__VA_ARG__[0]</code>, <code>__VA_ARG__[1]</code>, <code>__VA_ARG__[2]</code>.
 ** @see P99_STRDUP(...) for arguments <code>__VA_ARG__[0]</code>, <code>__VA_ARG__[1]</code>, <code>__VA_ARG__[2]</code>.
 ** @see P99_STRUCT_LITERAL(TYPE, ...) for arguments <code>TYPE</code>, <code>__VA_ARG__[0]</code>, <code>__VA_ARG__[1]</code>, <code>__VA_ARG__[2]</code>.
 ** @see P99_STRUCT_TYPE0(TYPE, ...) for arguments <code>TYPE</code>, <code>__VA_ARG__[0]</code>, <code>__VA_ARG__[1]</code>, <code>__VA_ARG__[2]</code>, <code>__VA_ARG__[3]</code>.
 ** @see P99_STRUCT_TYPES(TYPE, ...) for arguments <code>TYPE</code>, <code>__VA_ARG__[0]</code>, <code>__VA_ARG__[1]</code>, <code>__VA_ARG__[2]</code>, <code>__VA_ARG__[3]</code>.
 ** @see P99_STRUCT_UNUSE(TYPE, VAR, ...) for arguments <code>TYPE</code>, <code>VAR</code>, <code>__VA_ARG__[0]</code>, <code>__VA_ARG__[1]</code>, <code>__VA_ARG__[2]</code>.
 ** @see P99_STRUCT_USE(TYPE, VAR, ...) for arguments <code>TYPE</code>, <code>VAR</code>, <code>__VA_ARG__[0]</code>, <code>__VA_ARG__[1]</code>, <code>__VA_ARG__[2]</code>.
 ** @see P99_SVALUE(X) for argument <code>X</code>.
 ** @see P99_SWAP(_0, _1) for argument <code>_0</code>, <code>_1</code>.
 ** @see P99_THROW_CALL_RANGE(F, ...) for arguments <code>F</code>, <code>__VA_ARG__[0]</code>, <code>__VA_ARG__[1]</code>, <code>__VA_ARG__[2]</code>, <code>__VA_ARG__[3]</code>.
 ** @see P99_TMAX(T) for argument <code>T</code>.
 ** @see P99_TMIN(T) for argument <code>T</code>.
 ** @see P99_TOKJOIN(TOK, ...) for argument <code>TOK</code>.
 ** @see P99_TO_UNSIGNED(T, MACRO) for argument <code>T</code>, <code>MACRO</code>.
 ** @see P99_TP_DECLARE(T) for argument <code>T</code>.
 ** @see P99_TP_REF_DECLARE(T) for argument <code>T</code>.
 ** @see P99_TP_REF_DEFINE(T) for argument <code>T</code>.
 ** @see P99_TP_REF_FUNCTIONS(T) for argument <code>T</code>.
 ** @see P99_TSS_DECLARE_LOCAL(T, NAME, DTOR) for argument <code>NAME</code>.
 ** @see P99_TYPE_ARITHMETIC(EXP) for argument <code>EXP</code>.
 ** @see P99_TYPE_BASIC(EXP) for argument <code>EXP</code>.
 ** @see P99_TYPE_CHARACTER(EXP) for argument <code>EXP</code>.
 ** @see P99_TYPE_CHOICE(EXP, YES, NO, ...) for arguments <code>EXP</code>, <code>YES</code>, <code>NO</code>.
 ** @see P99_TYPE_COMPLEX(EXP) for argument <code>EXP</code>.
 ** @see P99_TYPE_FLOATING(EXP) for argument <code>EXP</code>.
 ** @see P99_TYPE_INTEGER(EXP) for argument <code>EXP</code>.
 ** @see P99_TYPE_REAL(EXP) for argument <code>EXP</code>.
 ** @see P99_TYPE_REAL_FLOATING(EXP) for argument <code>EXP</code>.
 ** @see P99_TYPE_SIGNED(EXP) for argument <code>EXP</code>.
 ** @see P99_TYPE_UNSIGNED(EXP) for argument <code>EXP</code>.
 ** @see P99_TZERO(X) for argument <code>X</code>.
 ** @see P99_UINT_DEFAULT(T) for argument <code>T</code>.
 ** @see P99_UNROLL(MACRO, N) for argument <code>MACRO</code>, <code>N</code>.
 ** @see P99_UT_MAX(T) for argument <code>T</code>.
 ** @see P99_VASSIGNS(NAME, ...) for argument <code>NAME</code>.
 ** @see P99_VECTOR(T, NAME, N) for arguments <code>T</code>, <code>NAME</code>, <code>N</code>.
 **/
