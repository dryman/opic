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
#ifndef     P99_GETOPT_H_
# define    P99_GETOPT_H_

/**
 ** @file
 ** @brief Providing macros that handle variadic macro argument lists.
 **/

#include "p99_qsort.h"
#include "p99_callback.h"

typedef int p00_getopt_process_type(void*, char const*);

struct p00_getopt {
  void*const p00_o;
  p00_getopt_process_type*const p00_f;
  char const*const p00_a;
  char const*const p00_d;
  char const*const p00_t;
  char const*const p00_n;
  char const*const p00_v;
};

P99_TENTATIVE_DEC(void**, p00_getopt_allocations);

#define P00_GETOPT_PROCESS(T) P99_PASTE2(p00_getopt_process_, T)

#define P00_GETOPT_CHAR(CHAR) p00_getopt_char## CHAR
#define P00_GETOPT_BOOL(CHAR) p00_getopt_bool## CHAR

P99_WEAK(p00_getopt_comp)
int p00_getopt_comp(void const* p00_a, void const* p00_b, void* p00_context) {
  register struct p00_getopt const*const*const p00_A = p00_a;
  register struct p00_getopt const*const*const p00_B = p00_b;
  if (p00_A && (*p00_A) && (*p00_A)->p00_a)
    if (p00_B && (*p00_B) && (*p00_B)->p00_a)
      return strcmp((*p00_A)->p00_a, (*p00_B)->p00_a);
    else
      return -1;
  else if (p00_B && (*p00_B) && (*p00_B)->p00_a)
    return 1;
  else
    return 0;
}

P99_WEAK(p00_getopt_subcomp)
int p00_getopt_subcomp(void const* p00_a, void const* p00_b, void* p00_context) {
  register struct p00_getopt const*const*const p00_A = p00_a;
  register struct p00_getopt const*const*const p00_B = p00_b;
  if (p00_A && (*p00_A) && (*p00_A)->p00_a)
    if (p00_B && (*p00_B) && (*p00_B)->p00_a) {
      size_t p00_n = strlen((*p00_A)->p00_a);
      return strncmp((*p00_A)->p00_a, (*p00_B)->p00_a, p00_n);
    } else
      return -1;
  else if (p00_B && (*p00_B) && (*p00_B)->p00_a)
    return 1;
  else
    return 0;
}


#define P00_GETOPT_SIGNED(T)                                   \
static_inline                                                  \
int P00_GETOPT_PROCESS(T)(void* p00_o, char const* p00_c) {    \
  T*p00_O = p00_o;                                             \
  if (p00_c && p00_c[0]) {                                     \
    char* endptr = 0;                                          \
    *p00_O = strtoll(p00_c, &endptr, 0);                       \
    if (endptr) return strlen(p00_c);                          \
  }                                                            \
  return -1;                                                   \
}

P99_SER(P00_GETOPT_SIGNED,                                     \
        schar,                                                 \
        short,                                                 \
        int,                                                   \
        long,                                                  \
        llong                                                  \
       )

#define P00_GETOPT_UNSIGNED(T)                                 \
static_inline                                                  \
int P00_GETOPT_PROCESS(T)(void* p00_o, char const* p00_c) {    \
  T*p00_O = p00_o;                                             \
  if (p00_c && p00_c[0]) {                                     \
    char* endptr = 0;                                          \
    *p00_O = strtoull(p00_c, &endptr, 0);                      \
    if (endptr) return strlen(p00_c);                          \
  }                                                            \
  return -1;                                                   \
}

P99_SER(P00_GETOPT_UNSIGNED,                                   \
        uchar,                                                 \
        ushort,                                                \
        unsigned,                                              \
        ulong,                                                 \
        ullong)

static_inline
int P00_GETOPT_PROCESS(char)(void* p00_o, char const*p00_c) {
  char*p00_O = p00_o;
  if (p00_c && p00_c[0]) {
    *p00_O = p00_c[0];
    return 1;
  }
  return -1;
}

static_inline
int P00_GETOPT_PROCESS(_Bool)(void* p00_o, char const*p00_c) {
  P99_UNUSED(p00_c);
  bool*p00_O = p00_o;
  *p00_O = !*p00_O;
  return 0;
}

static_inline
int P00_GETOPT_PROCESS(char_cptr)(void* p00_o, char const*p00_c) {
  char const**p00_O = p00_o;
  if (p00_c) {
    *p00_getopt_allocations = P99_STRDUP(p00_c);
    *p00_O = *p00_getopt_allocations;
    ++p00_getopt_allocations;
    return strlen(p00_c) + 1;
  }
  return -1;
}

#define P00_GETOPT_FLOAT(T)                                    \
static_inline                                                  \
int P00_GETOPT_PROCESS(T)(void* p00_o, char const* p00_c) {    \
  T*p00_O = p00_o;                                             \
  if (p00_c && p00_c[0]) {                                     \
    char* endptr = 0;                                          \
    *p00_O = strtold(p00_c, &endptr);                          \
    if (endptr) return strlen(p00_c);                          \
  }                                                            \
  return -1;                                                   \
}

P99_SER(P00_GETOPT_FLOAT,                                      \
        float,                                                 \
        double,                                                \
        ldouble)


#define P00_GETOPT_PROCESS_CHOOSE_(T) (T, P00_GETOPT_PROCESS(T))

#define P00_GETOPT_PROCESS_CHOOSE(...) P99_SEQ(P00_GETOPT_PROCESS_CHOOSE_, __VA_ARGS__)

#define P00_GETOPT_DECLARE(CHAR, T, TS, DEFS, NAME, DEF, ALIAS, DOC, ...) \
  extern T NAME;                                                          \
  P99_TENTATIVE_DEF(bool const, P00_GETOPT_BOOL(CHAR)) = true;            \
  P99_TENTATIVE_DEF(struct p00_getopt const*const, P00_GETOPT_CHAR(CHAR)) \
  = &(struct p00_getopt const){                                           \
    .p00_o =  &(NAME),                                                    \
    .p00_f = P99_GENERIC(NAME, 0, __VA_ARGS__),                           \
    .p00_a = (ALIAS),                                                     \
    .p00_d = (DOC),                                                       \
    .p00_t = TS,                                                          \
    .p00_n = #NAME,                                                       \
    .p00_v = DEFS,                                                        \
  }

#define P00_GETOPT_DECLARE_(...) P00_GETOPT_DECLARE(__VA_ARGS__)

#ifdef P00_DOXYGEN
/**
 ** @brief Declare a commandline option for character option @a CHAR.
 **
 ** @param CHAR is either an alphanumeric character, an underscore or
 ** another character as encoded via ::p99_getopt_enum.
 **
 ** @param T is one of the basic types or <code>char const*</code>
 **
 ** @param NAME declares a global variable of type @a T.
 **
 ** @param DEF is the default value of @a NAME, @c 0 if omitted.
 ** @param ALIAS is an alias name (long option name) for the parameter, may be omitted.
 ** @param DOC is a documentation string for the option, may be omitted.
 **
 ** Commandline options for most types require a parameter to the
 ** option that is used to determine the value of @a NAME. With
 **
 ** @code
 ** P99_GETOPT_DECLARE(a, myvariable, unsignedVar, 47, "unsigned", "this an unsigned variable");
 ** @endcode
 **
 ** the global variable @c unsignedVar can be set on the commandline
 ** with the following equivalent options
 **
 ** @code
 ** -a78
 ** -a 78
 ** --myvariable=78
 ** --myvariable 78
 ** @endcode
 **
 ** Long options (aliases) may be shortened if the result is
 ** unambiguous. So if there would be no other alias starting with
 ** "my" the above could also be achieved with
 **
 ** @code
 ** --my 78
 ** @endcode
 **
 ** Boolean options (type @c _Bool or @c bool) are special, as they
 ** are considered to be just flags. They don't process an option
 ** argument but just toggle the value of their variable. Several
 ** option characters (not aliases) for such flags can be combined
 ** into a single commandline option starting with a <code>-</code>.
 **
 ** Three other options can be handled by default but which don't
 ** correspond to a user variable: the option characters
 ** <code>-?</code> and <code>-h</code> and the alias "help" terminate
 ** the program and provide a list of option characters, aliases,
 ** types, variable names on @c stderr. All three access methods for
 ** commandline help may be overwritten by the program.
 **
 ** @remark Usually ::P99_GETOPT_DECLARE would be used in a header
 ** (@c .h source file).
 **
 ** @remark All options that are processed via this mechanism are
 ** removed from @c argv and the @c argc parameter to @c main is
 ** adjusted accordingly.
 **
 ** @see P99_GETOPT_DEFINE for the corresponding macro that provides
 ** the definition of the underlying variable(s).
 **
 ** @see P99_MAIN_INTERCEPT to see how the commandline parsing can be
 ** launched automatically at program startup.
 **/
P00_DOCUMENT_TYPE_ARGUMENT(P99_GETOPT_DECLARE, 1)
P00_DOCUMENT_IDENTIFIER_ARGUMENT(P99_GETOPT_DECLARE, 2)
#define P99_GETOPT_DECLARE(CHAR, T, NAME, DEF, ALIAS, DOC)

/**
 ** @brief Define a commandline option that has been declared via
 ** ::P99_GETOPT_DECLARE
 **
 ** @remark Usually ::P99_GETOPT_DEFINE would and should be used in
 ** just one compilation unit (@c .c source file). It is a good idea
 ** that this would be the same as your @c main function definition.
 **
 ** @see P99_GETOPT_DECLARE for the corresponding macro that provides
 ** the declaration of the underlying variable(s).
 **/
P00_DOCUMENT_TYPE_ARGUMENT(P99_GETOPT_DEFINE, 1)
P00_DOCUMENT_IDENTIFIER_ARGUMENT(P99_GETOPT_DEFINE, 2)
#define P99_GETOPT_DEFINE(CHAR, T, NAME, DEF, ALIAS, DOC)
#else
P00_DOCUMENT_TYPE_ARGUMENT(P99_GETOPT_DECLARE, 1)
P00_DOCUMENT_IDENTIFIER_ARGUMENT(P99_GETOPT_DECLARE, 2)
#define P99_GETOPT_DECLARE(CHAR, T, ...)                                      \
P00_GETOPT_DECLARE_(_p00##CHAR,                                               \
                    T,                                                        \
                    #T,                                                       \
                    #__VA_ARGS__,                                             \
                    P99_IF_LT(P99_NARG(__VA_ARGS__), 2)                       \
                    (__VA_ARGS__, 0, 0, 0)                                    \
                    (P99_IF_LT(P99_NARG(__VA_ARGS__), 3)                      \
                     (__VA_ARGS__, 0, 0)                                      \
                     (P99_IF_LT(P99_NARG(__VA_ARGS__), 4)                     \
                      (__VA_ARGS__, 0)                                        \
                      (__VA_ARGS__))),                                        \
                    P00_GETOPT_PROCESS_CHOOSE(P99_STD_REAL_TYPES, char_cptr))


#define P00_GETOPT_DEFINE(CHAR, T, NAME, DEF, ALIAS, DOC)      \
T NAME = (DEF)

P00_DOCUMENT_TYPE_ARGUMENT(P99_GETOPT_DEFINE, 1)
P00_DOCUMENT_IDENTIFIER_ARGUMENT(P99_GETOPT_DEFINE, 2)
#define P99_GETOPT_DEFINE(CHAR, T, ...)                        \
P99_IF_LT(P99_NARG(__VA_ARGS__), 2)                            \
(P00_GETOPT_DEFINE(CHAR, T, __VA_ARGS__, 0, 0, 0))             \
(P99_IF_LT(P99_NARG(__VA_ARGS__), 3)                           \
 (P00_GETOPT_DEFINE(CHAR, T, __VA_ARGS__, 0, 0))               \
 (P99_IF_LT(P99_NARG(__VA_ARGS__), 4)                          \
  (P00_GETOPT_DEFINE(CHAR, T, __VA_ARGS__, 0))                 \
  (P00_GETOPT_DEFINE(CHAR, T, __VA_ARGS__))))
#endif


#define P00_GETOPT_STRUCT_DECL(CHAR)                                      \
  P99_TENTATIVE_DEC(bool const, P00_GETOPT_BOOL(CHAR));                   \
  P99_TENTATIVE_DEC(struct p00_getopt const*const ,P00_GETOPT_CHAR(CHAR))

#define P00_GETOPT_CHARS                                       \
_p00A, _p00B, _p00C, _p00D, _p00E, _p00F, _p00G,               \
  _p00H, _p00I, _p00J, _p00K, _p00L, _p00M, _p00N,             \
  _p00O, _p00P, _p00Q, _p00R, _p00S, _p00T, _p00U,             \
  _p00V, _p00W, _p00X, _p00Y, _p00Z,                           \
  _p00a, _p00b, _p00c, _p00d, _p00e, _p00f, _p00g,             \
  _p00h, _p00i, _p00j, _p00k, _p00l, _p00m, _p00n,             \
  _p00o, _p00p, _p00q, _p00r, _p00s, _p00t, _p00u,             \
  _p00v, _p00w, _p00x, _p00y, _p00z,                           \
  _p000, _p001, _p002, _p003, _p004, _p005, _p006,             \
  _p007, _p008, _p009, _p00_,                                  \
  _p00AMPERSAND,                                               \
  _p00APOSTROPHE,                                              \
  _p00ASTERISK,                                                \
  _p00AT,                                                      \
  _p00BACKSLASH,                                               \
  _p00BAR,                                                     \
  _p00BRACELEFT,                                               \
  _p00BRACERIGHT,                                              \
  _p00BRACKETLEFT,                                             \
  _p00BRACKETRIGHT,                                            \
  _p00CARRET,                                                  \
  _p00COLON,                                                   \
  _p00COMMA,                                                   \
  _p00DOLLAR,                                                  \
  _p00EQUAL,                                                   \
  _p00EXLAM,                                                   \
  _p00GRAVE,                                                   \
  _p00GREATER,                                                 \
  _p00HASH,                                                    \
  _p00HELP,                                                    \
  _p00LESS,                                                    \
  _p00PARENLEFT,                                               \
  _p00PARENRIGHT,                                              \
  _p00PERCENT,                                                 \
  _p00PERIOD,                                                  \
  _p00PLUS,                                                    \
  _p00QUOTEDBL,                                                \
  _p00SEMICOLON,                                               \
  _p00SLASH,                                                   \
  _p00TILDE

/**
 ** @brief A list of constants that can be used for option processing
 **
 ** Besides the characters that can be part of identifiers
 ** (alphanumeric characters and underscore), we provide several other
 ** characters for commandline option processing. The ones that are
 ** available can be deduced from the ending of the constant. E.g
 ** ::p99_getopt_enum_p00AT would be used with the token
 ** "AT" and corresponds to the @c @@ character:
 **
 ** @code
 ** P99_GETOPT_DECLARE(AT, char const*, char_cptrVar, 0, 0, "just a string");
 ** @endcode
 **/
enum p99_getopt_enum {
  p99_getopt_enum_p00A = 'A',
  p99_getopt_enum_p00B = 'B',
  p99_getopt_enum_p00C = 'C',
  p99_getopt_enum_p00D = 'D',
  p99_getopt_enum_p00E = 'E',
  p99_getopt_enum_p00F = 'F',
  p99_getopt_enum_p00G = 'G',
  p99_getopt_enum_p00H = 'H',
  p99_getopt_enum_p00I = 'I',
  p99_getopt_enum_p00J = 'J',
  p99_getopt_enum_p00K = 'K',
  p99_getopt_enum_p00L = 'L',
  p99_getopt_enum_p00M = 'M',
  p99_getopt_enum_p00N = 'N',
  p99_getopt_enum_p00O = 'O',
  p99_getopt_enum_p00P = 'P',
  p99_getopt_enum_p00Q = 'Q',
  p99_getopt_enum_p00R = 'R',
  p99_getopt_enum_p00S = 'S',
  p99_getopt_enum_p00T = 'T',
  p99_getopt_enum_p00U = 'U',
  p99_getopt_enum_p00V = 'V',
  p99_getopt_enum_p00W = 'W',
  p99_getopt_enum_p00X = 'X',
  p99_getopt_enum_p00Y = 'Y',
  p99_getopt_enum_p00Z = 'Z',
  p99_getopt_enum_p00a = 'a',
  p99_getopt_enum_p00b = 'b',
  p99_getopt_enum_p00c = 'c',
  p99_getopt_enum_p00d = 'd',
  p99_getopt_enum_p00e = 'e',
  p99_getopt_enum_p00f = 'f',
  p99_getopt_enum_p00g = 'g',
  p99_getopt_enum_p00h = 'h',
  p99_getopt_enum_p00i = 'i',
  p99_getopt_enum_p00j = 'j',
  p99_getopt_enum_p00k = 'k',
  p99_getopt_enum_p00l = 'l',
  p99_getopt_enum_p00m = 'm',
  p99_getopt_enum_p00n = 'n',
  p99_getopt_enum_p00o = 'o',
  p99_getopt_enum_p00p = 'p',
  p99_getopt_enum_p00q = 'q',
  p99_getopt_enum_p00r = 'r',
  p99_getopt_enum_p00s = 's',
  p99_getopt_enum_p00t = 't',
  p99_getopt_enum_p00u = 'u',
  p99_getopt_enum_p00v = 'v',
  p99_getopt_enum_p00w = 'w',
  p99_getopt_enum_p00x = 'x',
  p99_getopt_enum_p00y = 'y',
  p99_getopt_enum_p00z = 'z',
  p99_getopt_enum_p000 = '0',
  p99_getopt_enum_p001 = '1',
  p99_getopt_enum_p002 = '2',
  p99_getopt_enum_p003 = '3',
  p99_getopt_enum_p004 = '4',
  p99_getopt_enum_p005 = '5',
  p99_getopt_enum_p006 = '6',
  p99_getopt_enum_p007 = '7',
  p99_getopt_enum_p008 = '8',
  p99_getopt_enum_p009 = '9',
  p99_getopt_enum_p00_ = '_',
  p99_getopt_enum_p00AMPERSAND = '&',
  p99_getopt_enum_p00APOSTROPHE = '\'',
  p99_getopt_enum_p00ASTERISK = '*',
  p99_getopt_enum_p00AT = '@',
  p99_getopt_enum_p00BACKSLASH = '\\',
  p99_getopt_enum_p00BAR = '|',
  p99_getopt_enum_p00BRACELEFT = '{',
  p99_getopt_enum_p00BRACERIGHT = '}',
  p99_getopt_enum_p00BRACKETLEFT = '[',
  p99_getopt_enum_p00BRACKETRIGHT = ']',
  p99_getopt_enum_p00CARRET = '^',
  p99_getopt_enum_p00COLON = ':',
  p99_getopt_enum_p00COMMA = ',',
  p99_getopt_enum_p00DOLLAR = '$',
  p99_getopt_enum_p00EQUAL = '=',
  p99_getopt_enum_p00EXLAM = '!',
  p99_getopt_enum_p00GRAVE = '`',
  p99_getopt_enum_p00GREATER = '>',
  p99_getopt_enum_p00HASH = '#',
  p99_getopt_enum_p00HELP = '?',
  p99_getopt_enum_p00LESS = '<',
  p99_getopt_enum_p00PARENLEFT = '(',
  p99_getopt_enum_p00PARENRIGHT = ')',
  p99_getopt_enum_p00PERCENT = '%',
  p99_getopt_enum_p00PERIOD = '.',
  p99_getopt_enum_p00PLUS = '+',
  p99_getopt_enum_p00QUOTEDBL = '"',
  p99_getopt_enum_p00SEMICOLON = ';',
  p99_getopt_enum_p00SLASH = '/',
  p99_getopt_enum_p00TILDE = '~',
};

P99_SEP(P00_GETOPT_STRUCT_DECL, P00_GETOPT_CHARS);

static_inline
int P00_GETOPT_PROCESS(help)(void* p00_o, char const*p00_c);

typedef struct p00_getopt p00_getopt_pair[2];

P99_TENTATIVE_DEC(p00_getopt_pair, const p00_getopt_help) = {
  {
    .p00_f = P00_GETOPT_PROCESS(help),
    .p00_a = "help",
    .p00_d = "provide this help text",
  },
  {
    .p00_f = P00_GETOPT_PROCESS(help),
    .p00_d = "provide this help text",
  }
};

P99_TENTATIVE_DEC(char const*, p00_getopt_progname);


/* Split the "va_arg" argument of the P99_GETOPT macros into the name
   of the variable and the default value for that variable. We have to
   take the raw string produced from that argument such that we see
   the string as the programmer put it, not as the preprocessor
   expanded it. */
p99_inline
void p00_getopt_help_split(size_t p00_len, char p00_buf[p00_len],
                           char const**p00_n, char const** p00_v) {
  size_t p00_pos = 0;
  p00_pos += strspn(&p00_buf[p00_pos], " \t\n");
  *p00_n = &p00_buf[p00_pos];
  p00_pos += strcspn(p00_buf, ", \t\n");
  if (p00_buf[p00_pos]) {
    p00_buf[p00_pos] = 0;
    ++p00_pos;
    p00_pos += strspn(&p00_buf[p00_pos], ", \t\n");
    *p00_v = &p00_buf[p00_pos];
    p00_pos += strcspn(*p00_v, ", \t\n");
    p00_buf[p00_pos] = 0;
  } else *p00_v = "0";
}

p99_inline
void p00_getopt_help_count_(bool p00_set,
                            enum p99_getopt_enum p00_c,
                            struct p00_getopt const*p00_pc,
                            struct p00_getopt const*p00_help,
                            int p00_ns[4]) {
  register struct p00_getopt const*const p00_p
    = (p00_set
       ? p00_pc
       : (((p00_c != p99_getopt_enum_p00h) && (p00_c != p99_getopt_enum_p00HELP))
          ? 0
          : p00_help));
  if (p00_p) {
    if (p00_p->p00_a) p00_ns[0] = P99_GEN_MAX(p00_ns[0], strlen(p00_p->p00_a));
    if (p00_p->p00_t) p00_ns[1] = P99_GEN_MAX(p00_ns[1], strlen(p00_p->p00_t));
    char const* p00_n = p00_p->p00_n;
    char const* p00_v = "";
    size_t const p00_len = 1 + (p00_p->p00_v ? strlen(p00_p->p00_v) : 0);
    char p00_buf[p00_len];
    if (p00_p->p00_v) {
      strcpy(p00_buf, p00_p->p00_v);
      p00_getopt_help_split(p00_len, p00_buf, &p00_n, &p00_v);
    }
    if (p00_n) p00_ns[2] = P99_GEN_MAX(p00_ns[2], strlen(p00_n));
    if (p00_v) p00_ns[3] = P99_GEN_MAX(p00_ns[3], strlen(p00_v));
  }
}


#define P00_GETOPT_HELP_COUNT_(CHAR)  p00_getopt_help_count_(p00_getopt_bool## CHAR, p99_getopt_enum## CHAR, P00_GETOPT_CHAR(CHAR), p00_getopt_help, p00_ns)

#define P00_GETOPT_HELP_COUNT(...) P99_SEP(P00_GETOPT_HELP_COUNT_, __VA_ARGS__)

p99_inline
void p00_getopt_help_(bool p00_set, enum p99_getopt_enum p00_c, struct p00_getopt const*p00_pc, struct p00_getopt const*p00_help, int const p00_ns[4]) {
  register struct p00_getopt const*const p00_p
    = (p00_set
       ? p00_pc
       : (((p00_c != p99_getopt_enum_p00h) && (p00_c != p99_getopt_enum_p00HELP))
          ? 0
          : p00_help));
  if (p00_p) {
    char const*const p00_d = p00_p->p00_d ? p00_p->p00_d : "(not documented)";
    char const*const p00_t = p00_p->p00_t ? p00_p->p00_t : "";
    char const* p00_n = "";
    char const* p00_v = "";
    size_t const p00_len = 1 + (p00_p->p00_v ? strlen(p00_p->p00_v) : 0);
    char p00_buf[p00_len];
    if (p00_p->p00_v) {
      strcpy(p00_buf, p00_p->p00_v);
      p00_getopt_help_split(p00_len, p00_buf, &p00_n, &p00_v);
    }
    if (p00_p->p00_a)
      fprintf(stderr, "   -%c  --%-*s%-*s%-*s%-*s\t%s\n",
              p00_c,
              p00_ns[0]+2,
              p00_p->p00_a,
              p00_ns[1]+2,
              p00_t,
              p00_ns[2]+2,
              p00_n,
              p00_ns[3]+2,
              p00_v,
              p00_d);
    else
      fprintf(stderr, "   -%c    %-*s%-*s%-*s%-*s \t%s\n",
              p00_c,
              p00_ns[0]+2,
              "",
              p00_ns[1]+2,
              p00_t,
              p00_ns[2]+2,
              p00_n,
              p00_ns[3]+2,
              p00_v,
              p00_d);
  }
}


#define P00_GETOPT_HELP_(CHAR) p00_getopt_help_(p00_getopt_bool## CHAR, p99_getopt_enum## CHAR, P00_GETOPT_CHAR(CHAR), p00_getopt_help, p00_ns)


#define P00_GETOPT_HELP(...) P99_SEP(P00_GETOPT_HELP_, __VA_ARGS__)

P99_TENTATIVE_DEC(char const*const, p00_getopt_synopsis);

P99_TENTATIVE_DEC(p99_callback_void_func*const, p00_getopt_callback);

/**
 ** @brief Add a synopsis to the commandline option documentation
 **
 ** @param LINE should be a string literal
 **/
#define P99_GETOPT_SYNOPSIS(LINE)                                                      \
P00_TENTATIVE_DEF(p00_getopt_synopsis) char const*const p00_getopt_synopsis = { LINE }


/**
 ** @brief Add a callback to the commandline option documentation
 **
 ** @param CALLBACK must be assignment compatible to a pointer to
 ** ::p99_callback_void_func.
 **/
#define P99_GETOPT_CALLBACK(CALLBACK)                                                                \
P00_TENTATIVE_DEF(p00_getopt_callback) p99_callback_void_func*const p00_getopt_callback = (CALLBACK)


static_inline
int P00_GETOPT_PROCESS(help)(void* p00_o, char const*p00_c) {
  P99_UNUSED(p00_o);
  int p00_ns[4] = { 0 };
  P00_GETOPT_HELP_COUNT(P00_GETOPT_CHARS);
  if (p00_getopt_progname || p00_getopt_synopsis)
    fprintf(stderr, "%s%s%s\n\toptions:\n",
            (p00_getopt_progname ? p00_getopt_progname : ""),
            (p00_getopt_progname && p00_getopt_synopsis ? " -- " : ""),
            (p00_getopt_synopsis ? p00_getopt_synopsis : ""));
  fprintf(stderr, "short  %-*s%-*s%-*s%-*s \t%s\n",
          p00_ns[0]+4,
          "long",
          p00_ns[1]+2,
          "type",
          p00_ns[2]+2,
          "name",
          p00_ns[3]+2,
          "default",
          "");
  P00_GETOPT_HELP(P00_GETOPT_CHARS);
  if (p00_getopt_callback) {
    fputs("-----------------------------------------------------\n", stderr);
    p00_getopt_callback();
  }
  exit(EXIT_FAILURE);
}

#define P00_GETOPT_INITIALIZE_(CHAR)                                                                              \
 case p99_getopt_enum## CHAR: {                                                                                   \
   register struct p00_getopt const*const p00_p                                                                   \
     = (((p99_getopt_enum## CHAR != p99_getopt_enum_p00h) && (p99_getopt_enum## CHAR != p99_getopt_enum_p00HELP)) \
        ? (P00_GETOPT_BOOL(CHAR) ? P00_GETOPT_CHAR(CHAR) : 0)                                                     \
        : (P00_GETOPT_BOOL(CHAR) ? P00_GETOPT_CHAR(CHAR) : p00_getopt_help));                                     \
   if (p00_p) {                                                                                                   \
     void* p00_o = p00_p->p00_o;                                                                                  \
     p00_used = p00_p->p00_f(p00_o, p00_str);                                                                     \
     if (p00_used >= 0) break;                                                                                    \
   }                                                                                                              \
   p00_err0 = "unparsable argument";                                                                              \
   goto P00_REARANGE;                                                                                             \
 }

#define P00_GETOPT_INITIALIZE(...) P99_SER(P00_GETOPT_INITIALIZE_, __VA_ARGS__)

#define P00_GETOPT_ARRAY_ASSIGN_(CHAR) p00_A[p99_getopt_enum## CHAR] = (P00_GETOPT_BOOL(CHAR) ? P00_GETOPT_CHAR(CHAR) : 0)

#define P00_GETOPT_ARRAY_ASSIGN(...) P99_SEP(P00_GETOPT_ARRAY_ASSIGN_, __VA_ARGS__)

#define P00_GETOPT_ARRAY_INIT_(CHAR) [p99_getopt_enum## CHAR] = 0

#define P00_GETOPT_ARRAY_INIT(...) P99_SEQ(P00_GETOPT_ARRAY_INIT_, __VA_ARGS__)

#define P00_GETOPT_ALLOCATIONS(CHAR) [p99_getopt_enum## CHAR] = 0

P99_TENTATIVE_DEC(void**, p00_getopt_allocations_base);

static_inline
void p00_getopt_atexit(void) {
  size_t p00_len = p00_getopt_allocations - p00_getopt_allocations_base;
  void** p00_tmp = p00_getopt_allocations_base;
  p00_getopt_allocations = 0;
  p00_getopt_allocations_base = 0;
  P99_DO(size_t, p00_i, 0, p00_len)
  free(p00_tmp[p00_i]);
  free(p00_tmp);
}

p99_inline
struct p00_getopt const*
p00_getopt_find_alias(char const* p00_al, size_t p00_size, struct p00_getopt const* p00_A[p00_size]) {
  /* Search for a matching alias in the array */
  struct p00_getopt const*const p00_el = &(struct p00_getopt const) { .p00_a = p00_al, };
  register struct p00_getopt const*const* p00_p = bsearch_s(&p00_el,
      p00_A,
      p00_size,
      sizeof *p00_A,
      p00_getopt_subcomp,
      0);
  if (p00_p && (*p00_p)) {
    /* Now search if there are several matches. */
    while (p00_p != p00_A && !p00_getopt_subcomp(&p00_el, p00_p - 1, 0)) --p00_p;
    /* An exact match must always come first and is preferred.
       If the first is not an exact match, second shouldn't be
       a partial match. */
    if (!p00_getopt_comp(&p00_el, p00_p, 0) || (p00_getopt_subcomp(&p00_el, p00_p+1, 0) < 0))
      return *p00_p;
  }
  return 0;
}

p99_inline
void
p00_getopt_diagnostic(char const* p00_err0, char const* p00_err1, char const* p00_err2) {
  fprintf(stderr, "Warning: %s for \"--%s\" with \"%s\"\n",
          p00_err0,
          p00_err1,
          p00_err2);
}

/**
 ** @brief Parse the commandline arguments
 **
 ** If you use the getopt facilities you have to launch the parsing of
 ** the arguments at the beginning of @c main, with preference before
 ** your program does anything else.
 **
 ** @warning All getopt variable declarations must be visible in the
 ** same compilation unit that issues the call to this function,
 ** usually @c main.
 **
 ** This function is <code>static inline</code> because it has to use
 ** all these variable declarations.
 **
 ** @see P99_GETOPT_DECLARE
 ** @see P99_GETOPT_SYNOPSIS
 ** @see P99_GETOPT_CALLBACK
 **/
static inline
void p99_getopt_initialize(int * p00_argc, char***p00_argv) {
  p00_getopt_allocations_base = P99_CALLOC(void*, *p00_argc);
  p00_getopt_allocations = p00_getopt_allocations_base;
  atexit(p00_getopt_atexit);
  char const* p00_err0 = 0;
  char const* p00_err1 = 0;
  char const* p00_err2 = 0;
  /* Create a sorted array with all the aliases, such that we may then
     search for a matching key. */
  static struct p00_getopt const* p00_A[] = {
    P00_GETOPT_ARRAY_INIT(P00_GETOPT_CHARS),
  };
  memset(p00_A, 0, sizeof p00_A);
  {
    P00_GETOPT_ARRAY_ASSIGN(P00_GETOPT_CHARS);
  }
  qsort_s(p00_A, P99_ALEN(p00_A), sizeof *p00_A, p00_getopt_comp, 0);

  register struct p00_getopt const** p00_up = p00_A;
  while (*p00_up) ++p00_up;

  /* If --help is already used by the application code cancel the
     mention of --help in p00_getopt_help otherwise insert the alias. */
  if (p00_getopt_find_alias("help", p00_up-p00_A, p00_A)) {
    *p00_up = &p00_getopt_help[1];
  } else {
    *p00_up = &p00_getopt_help[0];
  }
  ++p00_up;
  qsort_s(p00_A, p00_up - p00_A, sizeof *p00_A, p00_getopt_comp, 0);

  p00_getopt_progname = (*p00_argv)[0];

  /* Now comes the main processing loop. One character arguments may
     be aggregated into one option, that is why this loop looks a bit
     scary. */
  int p00_arg = 1;
  for (; p00_arg < *p00_argc && (*p00_argv)[p00_arg]; ++p00_arg) {
    /* All options must start with a dash, otherwise this finishes
       option processing. */
    if ((*p00_argv)[p00_arg][0] != '-') {
      goto P00_REARANGE;
    } else {
      /* A "--" without anything else finishes option processing. */
      if ((*p00_argv)[p00_arg][1] == '-' && !(*p00_argv)[p00_arg][2]) {
        ++p00_arg;
        goto P00_REARANGE;
      }
      for (char const* p00_str = (*p00_argv)[p00_arg] + 1; p00_str && p00_str[0];) {
        int p00_used = 0;
        bool p00_extra = false;
        char p00_C = p00_str[0];
        ++p00_str;
        /* If there was nothing left in the option, take the next one
           as an argument. */
        if (!p00_str[0]) {
          p00_str = (*p00_argv)[p00_arg + 1];
          if (p00_str) p00_extra = true;
        }
        static char p00_err[2];
        p00_err[0] = p00_C;
        p00_err1 = p00_err;
        p00_err2 = p00_str;
        switch (p00_C) {
          /* The cases for the one-character options are hidden
             here. */
          P00_GETOPT_INITIALIZE(P00_GETOPT_CHARS)
        /* If the initial string was "--" this announces a long
           option. */
        case '-': {
          /* First split up the option string into option and
             argument, if possible. */
          char p00_al[strlen(p00_str) + 1];
          strcpy(p00_al, p00_str);
          char* p00_ar = strchr(p00_al, '=');
          if (p00_ar) {
            *p00_ar = 0;
            ++p00_ar;
          } else {
            /* If not, suppose that the argument has been given in
               the next option. */
            p00_ar = (*p00_argv)[p00_arg + 1];
            p00_extra = true;
          }
          p00_err1 = p00_al;
          p00_err2 = p00_ar;
          /* Search for a matching alias in the array */
          register struct p00_getopt const*const p00_p = p00_getopt_find_alias(p00_al, p00_up - p00_A, p00_A);
          if (p00_p) {
            void* p00_o = p00_p->p00_o;
            p00_used = p00_p->p00_f(p00_o, p00_ar);
            if (p00_used >= 0) break;
            else p00_getopt_diagnostic("unparsable argument", p00_err1, p00_err2);
          } else p00_getopt_diagnostic("no or ambiguous option alias", p00_err1, p00_err2);
          goto P00_REARANGE;
        }
        }
        /* If this used the option argument and the argument was found
           in the next element of argv, skip that. */
        if (p00_used > 0) {
          p00_arg += p00_extra;
          break;
        } else
          /* Otherwise if this was a flag and we tried to obtain from
             the next element in argv, check that element again, it
             might be an option, too. */
          if (p00_extra) break;
      }
    }
  }
P00_REARANGE:
  if (p00_err0) p00_getopt_diagnostic(p00_err0, p00_err1, p00_err2);
  /* At the end of the processing, shift all unused options down, such
     that they appear at front in the argv array. */
  *p00_argc -= (p00_arg - 1);
  for (int p00_n = 1; p00_n < *p00_argc; ++p00_n) {
    (*p00_argv)[p00_n] = (*p00_argv)[p00_n + (p00_arg - 1)];
  }
}

#endif      /* !P99_GETOPT_H_ */
