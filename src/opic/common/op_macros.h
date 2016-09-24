#ifndef OP_MACROS_H
#define OP_MACROS_H 1

/* copied from sys/cdefs.h */
#if defined(__cplusplus)
#define OP_BEGIN_DECLS   extern "C" {
#define OP_END_DECLS }
#else
#define OP_BEGIN_DECLS
#define OP_END_DECLS
#endif
/* clang */
#ifndef __has_builtin
#define __has_builtin(x) 0
#endif

#if defined __GNUC__ || __has_builtin(__builtin_expect)
#define op_likely(x) __builtin_expect ((x), 1)
#define op_unlikely(x) __builtin_expect ((x), 0)
#else
#define op_likely(x) (x)
#define op_unlikely(x) (x)
#endif

#ifndef INLINE
# if __GNUC__ && !__GNUC_STDC_INLINE__
#  define INLINE extern inline
# else
#  define INLINE inline
# endif
#endif

#define _OP_GET_MACRO_BY_ARGS(_01,_02,_03,_04,_05,_06,_07,_08,_09,_10, \
                              _11,_12,_13,_14,_15,_16,_17,_18,_19,_20, \
                              _21,_22,_23,_24,_25,_26,_27,_28,_29,_30, \
                              _31,_32,_33,_34,_35,_36, NAME,...) NAME 

/**
 * OP_MR_S0(M,R)
 * Map Reduce macro without any scope variable
 * M must have signature M(X,IDX,...)
 * R must have signature R(X,ACC,...)
 */
#define OP_MR_S0(M,R,               ...) OP_MR_S1(M,R,,__VA_ARGS__)
#define OP_MR_S1(M,R,S1,            ...) OP_MR_S2(M,R,S1,,__VA_ARGS__)
#define OP_MR_S2(M,R,S1,S2,         ...) OP_MR_S3(M,R,S1,S2,,__VA_ARGS__)
#define OP_MR_S3(M,R,S1,S2,S3,      ...) OP_MR_S4(M,R,S1,S2,S3,,__VA_ARGS__)
#define OP_MR_S4(M,R,S1,S2,S3,S4,   ...) OP_MR_S5(M,R,S1,S2,S3,S4,,__VA_ARGS__)
#define OP_MR_S5(M,R,S1,S2,S3,S4,S5,...) OP_MR_S6(M,R,S1,S2,S3,S4,S5,,__VA_ARGS__)


#define OP_M_IDENTITY(X,...) X
#define OP_R_SPACE(X,ACC,...) X ACC
#define OP_R_COMMA(X,ACC,...) X, ACC
#define OP_R_SEMICOLON(X,ACC,...) X; ACC

#define OP_MAP_SP_S0(M,               ...)    OP_MAP_SP_S1(M,,__VA_ARGS__)
#define OP_MAP_SP_S1(M,S1,            ...)    OP_MAP_SP_S2(M,S1,,__VA_ARGS__)
#define OP_MAP_SP_S2(M,S1,S2,         ...)    OP_MAP_SP_S3(M,S1,S2,,__VA_ARGS__)
#define OP_MAP_SP_S3(M,S1,S2,S3,      ...)    OP_MAP_SP_S4(M,S1,S2,S3,,__VA_ARGS__)
#define OP_MAP_SP_S4(M,S1,S2,S3,S4,   ...)    OP_MAP_SP_S5(M,S1,S2,S3,S4,,__VA_ARGS__)
#define OP_MAP_SP_S5(M,S1,S2,S3,S4,S5,...)    OP_MAP_SP_S6(M,S1,S2,S3,S4,S5,,__VA_ARGS__)
#define OP_MAP_SP_S6(M,S1,S2,S3,S4,S5,S6,...) OP_MR_S6(M,OP_R_SPACE,S1,S2,S3,S4,S5,S6,__VA_ARGS__)

#define OP_MAP_CM_S0(M,               ...)    OP_MAP_CM_S1(M,,__VA_ARGS__)
#define OP_MAP_CM_S1(M,S1,            ...)    OP_MAP_CM_S2(M,S1,,__VA_ARGS__)
#define OP_MAP_CM_S2(M,S1,S2,         ...)    OP_MAP_CM_S3(M,S1,S2,,__VA_ARGS__)
#define OP_MAP_CM_S3(M,S1,S2,S3,      ...)    OP_MAP_CM_S4(M,S1,S2,S3,,__VA_ARGS__)
#define OP_MAP_CM_S4(M,S1,S2,S3,S4,   ...)    OP_MAP_CM_S5(M,S1,S2,S3,S4,,__VA_ARGS__)
#define OP_MAP_CM_S5(M,S1,S2,S3,S4,S5,...)    OP_MAP_CM_S6(M,S1,S2,S3,S4,S5,,__VA_ARGS__)
#define OP_MAP_CM_S6(M,S1,S2,S3,S4,S5,S6,...) OP_MR_S6(M,OP_R_COMMA,S1,S2,S3,S4,S5,S6,__VA_ARGS__)

#define OP_MAP_SC_S0(M,               ...)    OP_MAP_SC_S1(M,,__VA_ARGS__)
#define OP_MAP_SC_S1(M,S1,            ...)    OP_MAP_SC_S2(M,S1,,__VA_ARGS__)
#define OP_MAP_SC_S2(M,S1,S2,         ...)    OP_MAP_SC_S3(M,S1,S2,,__VA_ARGS__)
#define OP_MAP_SC_S3(M,S1,S2,S3,      ...)    OP_MAP_SC_S4(M,S1,S2,S3,,__VA_ARGS__)
#define OP_MAP_SC_S4(M,S1,S2,S3,S4,   ...)    OP_MAP_SC_S5(M,S1,S2,S3,S4,,__VA_ARGS__)
#define OP_MAP_SC_S5(M,S1,S2,S3,S4,S5,...)    OP_MAP_SC_S6(M,S1,S2,S3,S4,S5,,__VA_ARGS__)
#define OP_MAP_SC_S6(M,S1,S2,S3,S4,S5,S6,...) OP_MR_S6(M,OP_R_SEMICOLON,S1,S2,S3,S4,S5,S6,__VA_ARGS__)

#define OP_FOLDR_S0(R,                  ...) OP_FOLDR_S6(R,,__VA_ARGS__)
#define OP_FOLDR_S1(R,S1,               ...) OP_FOLDR_S6(R,S1,,__VA_ARGS__)
#define OP_FOLDR_S2(R,S1,S2,            ...) OP_FOLDR_S6(R,S1,S2,,__VA_ARGS__)
#define OP_FOLDR_S3(R,S1,S2,S3,         ...) OP_FOLDR_S6(R,S1,S2,S3,,__VA_ARGS__)
#define OP_FOLDR_S4(R,S1,S2,S3,S4,      ...) OP_FOLDR_S6(R,S1,S2,S3,S4,,__VA_ARGS__)
#define OP_FOLDR_S5(R,S1,S2,S3,S4,S5,   ...) OP_FOLDR_S6(R,S1,S2,S3,S4,S5,,__VA_ARGS__)
#define OP_FOLDR_S6(R,S1,S2,S3,S4,S5,S6,...) OP_MR_S6(OP_M_IDENTITY,R,S1,S2,S3,S4,S5,S6,__VA_ARGS__)

#define OP_FOLDL_S0(R,                  ...) OP_FOLDL_S6(R,,__VA_ARGS__)
#define OP_FOLDL_S1(R,S1,               ...) OP_FOLDL_S6(R,S1,,__VA_ARGS__)
#define OP_FOLDL_S2(R,S1,S2,            ...) OP_FOLDL_S6(R,S1,S2,,__VA_ARGS__)
#define OP_FOLDL_S3(R,S1,S2,S3,         ...) OP_FOLDL_S6(R,S1,S2,S3,,__VA_ARGS__)
#define OP_FOLDL_S4(R,S1,S2,S3,S4,      ...) OP_FOLDL_S6(R,S1,S2,S3,S4,,__VA_ARGS__)
#define OP_FOLDL_S5(R,S1,S2,S3,S4,S5,   ...) OP_FOLDL_S6(R,S1,S2,S3,S4,S5,,__VA_ARGS__)
#define OP_FOLDL_S6(R,S1,S2,S3,S4,S5,S6,...) OP_FOLDR_S6(R,S1,S2,S3,S4,S5,S6,OP_REVERSE(__VA_ARGS__))

#define OP_MR_S6(M,R,S1,S2,S3,S4,S5,S6,...) \
  _OP_GET_MACRO_BY_ARGS(__VA_ARGS__, \
   OP_MR_36, OP_MR_35, OP_MR_34, OP_MR_33, \
   OP_MR_32, OP_MR_31, OP_MR_30, OP_MR_29, \
   OP_MR_28, OP_MR_27, OP_MR_26, OP_MR_25, \
   OP_MR_24, OP_MR_23, OP_MR_22, OP_MR_21, \
   OP_MR_20, OP_MR_19, OP_MR_18, OP_MR_17, \
   OP_MR_16, OP_MR_15, OP_MR_14, OP_MR_13, \
   OP_MR_12, OP_MR_11, OP_MR_10, OP_MR_09, \
   OP_MR_08, OP_MR_07, OP_MR_06, OP_MR_05, \
   OP_MR_04, OP_MR_03, OP_MR_02, OP_MR_01,)(_OP_CNT_,M,R,S1,S2,S3,S4,S5,S6,__VA_ARGS__)

#define OP_REVERSE(...) \
  _OP_GET_MACRO_BY_ARGS(__VA_ARGS__, \
   OP_REV_36, OP_REV_35, OP_REV_34, OP_REV_33, \
   OP_REV_32, OP_REV_31, OP_REV_30, OP_REV_29, \
   OP_REV_28, OP_REV_27, OP_REV_26, OP_REV_25, \
   OP_REV_24, OP_REV_23, OP_REV_22, OP_REV_21, \
   OP_REV_20, OP_REV_19, OP_REV_18, OP_REV_17, \
   OP_REV_16, OP_REV_15, OP_REV_14, OP_REV_13, \
   OP_REV_12, OP_REV_11, OP_REV_10, OP_REV_09, \
   OP_REV_08, OP_REV_07, OP_REV_06, OP_REV_05, \
   OP_REV_04, OP_REV_03, OP_REV_02, OP_REV_01,)(__VA_ARGS__)

#define OP_LENGTH(...) \
  _OP_GET_MACRO_BY_ARGS(__VA_ARGS__, \
   OP_LEN_36, OP_LEN_35, OP_LEN_34, OP_LEN_33, \
   OP_LEN_32, OP_LEN_31, OP_LEN_30, OP_LEN_29, \
   OP_LEN_28, OP_LEN_27, OP_LEN_26, OP_LEN_25, \
   OP_LEN_24, OP_LEN_23, OP_LEN_22, OP_LEN_21, \
   OP_LEN_20, OP_LEN_19, OP_LEN_18, OP_LEN_17, \
   OP_LEN_16, OP_LEN_15, OP_LEN_14, OP_LEN_13, \
   OP_LEN_12, OP_LEN_11, OP_LEN_10, OP_LEN_09, \
   OP_LEN_08, OP_LEN_07, OP_LEN_06, OP_LEN_05, \
   OP_LEN_04, OP_LEN_03, OP_LEN_02, OP_LEN_01,)

#define OP_MR_01(I, M, R, S1, S2, S3, S4, S5, S6, X)        M(X,I,S1,S2,S3,S4,S5,S6)
#define OP_MR_02(I, M, R, S1, S2, S3, S4, S5, S6, X, ...) R(M(X,I,S1,S2,S3,S4,S5,S6), OP_MR_01(I##1,M,R,S1,S2,S3,S4,S5,S6,__VA_ARGS__) ,S1,S2,S3,S4,S5,S6)
#define OP_MR_03(I, M, R, S1, S2, S3, S4, S5, S6, X, ...) R(M(X,I,S1,S2,S3,S4,S5,S6), OP_MR_02(I##1,M,R,S1,S2,S3,S4,S5,S6,__VA_ARGS__) ,S1,S2,S3,S4,S5,S6)
#define OP_MR_04(I, M, R, S1, S2, S3, S4, S5, S6, X, ...) R(M(X,I,S1,S2,S3,S4,S5,S6), OP_MR_03(I##1,M,R,S1,S2,S3,S4,S5,S6,__VA_ARGS__) ,S1,S2,S3,S4,S5,S6)
#define OP_MR_05(I, M, R, S1, S2, S3, S4, S5, S6, X, ...) R(M(X,I,S1,S2,S3,S4,S5,S6), OP_MR_04(I##1,M,R,S1,S2,S3,S4,S5,S6,__VA_ARGS__) ,S1,S2,S3,S4,S5,S6)
#define OP_MR_06(I, M, R, S1, S2, S3, S4, S5, S6, X, ...) R(M(X,I,S1,S2,S3,S4,S5,S6), OP_MR_05(I##1,M,R,S1,S2,S3,S4,S5,S6,__VA_ARGS__) ,S1,S2,S3,S4,S5,S6)
#define OP_MR_07(I, M, R, S1, S2, S3, S4, S5, S6, X, ...) R(M(X,I,S1,S2,S3,S4,S5,S6), OP_MR_06(I##1,M,R,S1,S2,S3,S4,S5,S6,__VA_ARGS__) ,S1,S2,S3,S4,S5,S6)
#define OP_MR_08(I, M, R, S1, S2, S3, S4, S5, S6, X, ...) R(M(X,I,S1,S2,S3,S4,S5,S6), OP_MR_07(I##1,M,R,S1,S2,S3,S4,S5,S6,__VA_ARGS__) ,S1,S2,S3,S4,S5,S6)
#define OP_MR_09(I, M, R, S1, S2, S3, S4, S5, S6, X, ...) R(M(X,I,S1,S2,S3,S4,S5,S6), OP_MR_08(I##1,M,R,S1,S2,S3,S4,S5,S6,__VA_ARGS__) ,S1,S2,S3,S4,S5,S6)
#define OP_MR_10(I, M, R, S1, S2, S3, S4, S5, S6, X, ...) R(M(X,I,S1,S2,S3,S4,S5,S6), OP_MR_09(I##1,M,R,S1,S2,S3,S4,S5,S6,__VA_ARGS__) ,S1,S2,S3,S4,S5,S6)
#define OP_MR_11(I, M, R, S1, S2, S3, S4, S5, S6, X, ...) R(M(X,I,S1,S2,S3,S4,S5,S6), OP_MR_10(I##1,M,R,S1,S2,S3,S4,S5,S6,__VA_ARGS__) ,S1,S2,S3,S4,S5,S6)
#define OP_MR_12(I, M, R, S1, S2, S3, S4, S5, S6, X, ...) R(M(X,I,S1,S2,S3,S4,S5,S6), OP_MR_11(I##1,M,R,S1,S2,S3,S4,S5,S6,__VA_ARGS__) ,S1,S2,S3,S4,S5,S6)
#define OP_MR_13(I, M, R, S1, S2, S3, S4, S5, S6, X, ...) R(M(X,I,S1,S2,S3,S4,S5,S6), OP_MR_12(I##1,M,R,S1,S2,S3,S4,S5,S6,__VA_ARGS__) ,S1,S2,S3,S4,S5,S6)
#define OP_MR_14(I, M, R, S1, S2, S3, S4, S5, S6, X, ...) R(M(X,I,S1,S2,S3,S4,S5,S6), OP_MR_13(I##1,M,R,S1,S2,S3,S4,S5,S6,__VA_ARGS__) ,S1,S2,S3,S4,S5,S6)
#define OP_MR_15(I, M, R, S1, S2, S3, S4, S5, S6, X, ...) R(M(X,I,S1,S2,S3,S4,S5,S6), OP_MR_14(I##1,M,R,S1,S2,S3,S4,S5,S6,__VA_ARGS__) ,S1,S2,S3,S4,S5,S6)
#define OP_MR_16(I, M, R, S1, S2, S3, S4, S5, S6, X, ...) R(M(X,I,S1,S2,S3,S4,S5,S6), OP_MR_15(I##1,M,R,S1,S2,S3,S4,S5,S6,__VA_ARGS__) ,S1,S2,S3,S4,S5,S6)
#define OP_MR_17(I, M, R, S1, S2, S3, S4, S5, S6, X, ...) R(M(X,I,S1,S2,S3,S4,S5,S6), OP_MR_16(I##1,M,R,S1,S2,S3,S4,S5,S6,__VA_ARGS__) ,S1,S2,S3,S4,S5,S6)
#define OP_MR_18(I, M, R, S1, S2, S3, S4, S5, S6, X, ...) R(M(X,I,S1,S2,S3,S4,S5,S6), OP_MR_17(I##1,M,R,S1,S2,S3,S4,S5,S6,__VA_ARGS__) ,S1,S2,S3,S4,S5,S6)
#define OP_MR_19(I, M, R, S1, S2, S3, S4, S5, S6, X, ...) R(M(X,I,S1,S2,S3,S4,S5,S6), OP_MR_18(I##1,M,R,S1,S2,S3,S4,S5,S6,__VA_ARGS__) ,S1,S2,S3,S4,S5,S6)
#define OP_MR_20(I, M, R, S1, S2, S3, S4, S5, S6, X, ...) R(M(X,I,S1,S2,S3,S4,S5,S6), OP_MR_19(I##1,M,R,S1,S2,S3,S4,S5,S6,__VA_ARGS__) ,S1,S2,S3,S4,S5,S6)
#define OP_MR_21(I, M, R, S1, S2, S3, S4, S5, S6, X, ...) R(M(X,I,S1,S2,S3,S4,S5,S6), OP_MR_20(I##1,M,R,S1,S2,S3,S4,S5,S6,__VA_ARGS__) ,S1,S2,S3,S4,S5,S6)
#define OP_MR_22(I, M, R, S1, S2, S3, S4, S5, S6, X, ...) R(M(X,I,S1,S2,S3,S4,S5,S6), OP_MR_21(I##1,M,R,S1,S2,S3,S4,S5,S6,__VA_ARGS__) ,S1,S2,S3,S4,S5,S6)
#define OP_MR_23(I, M, R, S1, S2, S3, S4, S5, S6, X, ...) R(M(X,I,S1,S2,S3,S4,S5,S6), OP_MR_22(I##1,M,R,S1,S2,S3,S4,S5,S6,__VA_ARGS__) ,S1,S2,S3,S4,S5,S6)
#define OP_MR_24(I, M, R, S1, S2, S3, S4, S5, S6, X, ...) R(M(X,I,S1,S2,S3,S4,S5,S6), OP_MR_23(I##1,M,R,S1,S2,S3,S4,S5,S6,__VA_ARGS__) ,S1,S2,S3,S4,S5,S6)
#define OP_MR_25(I, M, R, S1, S2, S3, S4, S5, S6, X, ...) R(M(X,I,S1,S2,S3,S4,S5,S6), OP_MR_24(I##1,M,R,S1,S2,S3,S4,S5,S6,__VA_ARGS__) ,S1,S2,S3,S4,S5,S6)
#define OP_MR_26(I, M, R, S1, S2, S3, S4, S5, S6, X, ...) R(M(X,I,S1,S2,S3,S4,S5,S6), OP_MR_25(I##1,M,R,S1,S2,S3,S4,S5,S6,__VA_ARGS__) ,S1,S2,S3,S4,S5,S6)
#define OP_MR_27(I, M, R, S1, S2, S3, S4, S5, S6, X, ...) R(M(X,I,S1,S2,S3,S4,S5,S6), OP_MR_26(I##1,M,R,S1,S2,S3,S4,S5,S6,__VA_ARGS__) ,S1,S2,S3,S4,S5,S6)
#define OP_MR_28(I, M, R, S1, S2, S3, S4, S5, S6, X, ...) R(M(X,I,S1,S2,S3,S4,S5,S6), OP_MR_27(I##1,M,R,S1,S2,S3,S4,S5,S6,__VA_ARGS__) ,S1,S2,S3,S4,S5,S6)
#define OP_MR_29(I, M, R, S1, S2, S3, S4, S5, S6, X, ...) R(M(X,I,S1,S2,S3,S4,S5,S6), OP_MR_28(I##1,M,R,S1,S2,S3,S4,S5,S6,__VA_ARGS__) ,S1,S2,S3,S4,S5,S6)
#define OP_MR_30(I, M, R, S1, S2, S3, S4, S5, S6, X, ...) R(M(X,I,S1,S2,S3,S4,S5,S6), OP_MR_29(I##1,M,R,S1,S2,S3,S4,S5,S6,__VA_ARGS__) ,S1,S2,S3,S4,S5,S6)
#define OP_MR_31(I, M, R, S1, S2, S3, S4, S5, S6, X, ...) R(M(X,I,S1,S2,S3,S4,S5,S6), OP_MR_30(I##1,M,R,S1,S2,S3,S4,S5,S6,__VA_ARGS__) ,S1,S2,S3,S4,S5,S6)
#define OP_MR_32(I, M, R, S1, S2, S3, S4, S5, S6, X, ...) R(M(X,I,S1,S2,S3,S4,S5,S6), OP_MR_31(I##1,M,R,S1,S2,S3,S4,S5,S6,__VA_ARGS__) ,S1,S2,S3,S4,S5,S6)
#define OP_MR_33(I, M, R, S1, S2, S3, S4, S5, S6, X, ...) R(M(X,I,S1,S2,S3,S4,S5,S6), OP_MR_32(I##1,M,R,S1,S2,S3,S4,S5,S6,__VA_ARGS__) ,S1,S2,S3,S4,S5,S6)
#define OP_MR_34(I, M, R, S1, S2, S3, S4, S5, S6, X, ...) R(M(X,I,S1,S2,S3,S4,S5,S6), OP_MR_33(I##1,M,R,S1,S2,S3,S4,S5,S6,__VA_ARGS__) ,S1,S2,S3,S4,S5,S6)
#define OP_MR_35(I, M, R, S1, S2, S3, S4, S5, S6, X, ...) R(M(X,I,S1,S2,S3,S4,S5,S6), OP_MR_34(I##1,M,R,S1,S2,S3,S4,S5,S6,__VA_ARGS__) ,S1,S2,S3,S4,S5,S6)
#define OP_MR_36(I, M, R, S1, S2, S3, S4, S5, S6, X, ...) R(M(X,I,S1,S2,S3,S4,S5,S6), OP_MR_35(I##1,M,R,S1,S2,S3,S4,S5,S6,__VA_ARGS__) ,S1,S2,S3,S4,S5,S6)


#define OP_REV_01(X) X
#define OP_REV_02(X,...) OP_REV_01(__VA_ARGS__), X
#define OP_REV_03(X,...) OP_REV_02(__VA_ARGS__), X
#define OP_REV_04(X,...) OP_REV_03(__VA_ARGS__), X
#define OP_REV_05(X,...) OP_REV_04(__VA_ARGS__), X
#define OP_REV_06(X,...) OP_REV_05(__VA_ARGS__), X
#define OP_REV_07(X,...) OP_REV_06(__VA_ARGS__), X
#define OP_REV_08(X,...) OP_REV_07(__VA_ARGS__), X
#define OP_REV_09(X,...) OP_REV_08(__VA_ARGS__), X
#define OP_REV_10(X,...) OP_REV_09(__VA_ARGS__), X
#define OP_REV_11(X,...) OP_REV_10(__VA_ARGS__), X
#define OP_REV_12(X,...) OP_REV_11(__VA_ARGS__), X
#define OP_REV_13(X,...) OP_REV_12(__VA_ARGS__), X
#define OP_REV_14(X,...) OP_REV_13(__VA_ARGS__), X
#define OP_REV_15(X,...) OP_REV_14(__VA_ARGS__), X
#define OP_REV_16(X,...) OP_REV_15(__VA_ARGS__), X
#define OP_REV_17(X,...) OP_REV_16(__VA_ARGS__), X
#define OP_REV_18(X,...) OP_REV_17(__VA_ARGS__), X
#define OP_REV_19(X,...) OP_REV_18(__VA_ARGS__), X
#define OP_REV_20(X,...) OP_REV_19(__VA_ARGS__), X
#define OP_REV_21(X,...) OP_REV_20(__VA_ARGS__), X
#define OP_REV_22(X,...) OP_REV_21(__VA_ARGS__), X
#define OP_REV_23(X,...) OP_REV_22(__VA_ARGS__), X
#define OP_REV_24(X,...) OP_REV_23(__VA_ARGS__), X
#define OP_REV_25(X,...) OP_REV_24(__VA_ARGS__), X
#define OP_REV_26(X,...) OP_REV_25(__VA_ARGS__), X
#define OP_REV_27(X,...) OP_REV_26(__VA_ARGS__), X
#define OP_REV_28(X,...) OP_REV_27(__VA_ARGS__), X
#define OP_REV_29(X,...) OP_REV_28(__VA_ARGS__), X
#define OP_REV_30(X,...) OP_REV_29(__VA_ARGS__), X
#define OP_REV_31(X,...) OP_REV_30(__VA_ARGS__), X
#define OP_REV_32(X,...) OP_REV_31(__VA_ARGS__), X
#define OP_REV_33(X,...) OP_REV_32(__VA_ARGS__), X
#define OP_REV_34(X,...) OP_REV_33(__VA_ARGS__), X
#define OP_REV_35(X,...) OP_REV_34(__VA_ARGS__), X
#define OP_REV_36(X,...) OP_REV_35(__VA_ARGS__), X

#define OP_LEN_01 1
#define OP_LEN_02 2
#define OP_LEN_03 3
#define OP_LEN_04 4
#define OP_LEN_05 5
#define OP_LEN_06 6
#define OP_LEN_07 7
#define OP_LEN_08 8
#define OP_LEN_09 9
#define OP_LEN_10 10
#define OP_LEN_11 11
#define OP_LEN_12 12
#define OP_LEN_13 13
#define OP_LEN_14 14
#define OP_LEN_15 15
#define OP_LEN_16 16
#define OP_LEN_17 17
#define OP_LEN_18 18
#define OP_LEN_19 19
#define OP_LEN_20 20
#define OP_LEN_21 21
#define OP_LEN_22 22
#define OP_LEN_23 23
#define OP_LEN_24 24
#define OP_LEN_25 25
#define OP_LEN_26 26
#define OP_LEN_27 27
#define OP_LEN_28 28
#define OP_LEN_29 29
#define OP_LEN_30 30
#define OP_LEN_31 31
#define OP_LEN_32 32
#define OP_LEN_33 33
#define OP_LEN_34 34
#define OP_LEN_35 35
#define OP_LEN_36 36

#define _OP_CNT_ 0
#define _OP_CNT_1 1
#define _OP_CNT_11 2
#define _OP_CNT_111 3
#define _OP_CNT_1111 4
#define _OP_CNT_11111 5
#define _OP_CNT_111111 6
#define _OP_CNT_1111111 7
#define _OP_CNT_11111111 8
#define _OP_CNT_111111111 9
#define _OP_CNT_1111111111 10
#define _OP_CNT_11111111111 11
#define _OP_CNT_111111111111 12
#define _OP_CNT_1111111111111 13
#define _OP_CNT_11111111111111 14
#define _OP_CNT_111111111111111 15
#define _OP_CNT_1111111111111111 16
#define _OP_CNT_11111111111111111 17
#define _OP_CNT_111111111111111111 18
#define _OP_CNT_1111111111111111111 19
#define _OP_CNT_11111111111111111111 20
#define _OP_CNT_111111111111111111111 21
#define _OP_CNT_1111111111111111111111 22
#define _OP_CNT_11111111111111111111111 23
#define _OP_CNT_111111111111111111111111 24
#define _OP_CNT_1111111111111111111111111 25
#define _OP_CNT_11111111111111111111111111 26
#define _OP_CNT_111111111111111111111111111 27
#define _OP_CNT_1111111111111111111111111111 28
#define _OP_CNT_11111111111111111111111111111 29
#define _OP_CNT_111111111111111111111111111111 30
#define _OP_CNT_1111111111111111111111111111111 31
#define _OP_CNT_11111111111111111111111111111111 32
#define _OP_CNT_111111111111111111111111111111111 33
#define _OP_CNT_1111111111111111111111111111111111 34
#define _OP_CNT_11111111111111111111111111111111111 35
#define _OP_CNT_111111111111111111111111111111111111 36

/* same macros in with postfix _ to work around nested macro expansions */

#define OP_MR_S0_(M,R,               ...) OP_MR_S1_(M,R,,__VA_ARGS__)
#define OP_MR_S1_(M,R,S1,            ...) OP_MR_S2_(M,R,S1,,__VA_ARGS__)
#define OP_MR_S2_(M,R,S1,S2,         ...) OP_MR_S3_(M,R,S1,S2,,__VA_ARGS__)
#define OP_MR_S3_(M,R,S1,S2,S3,      ...) OP_MR_S4_(M,R,S1,S2,S3,,__VA_ARGS__)
#define OP_MR_S4_(M,R,S1,S2,S3,S4,   ...) OP_MR_S5_(M,R,S1,S2,S3,S4,,__VA_ARGS__)
#define OP_MR_S5_(M,R,S1,S2,S3,S4,S5,...) OP_MR_S6_(M,R,S1,S2,S3,S4,S5,,__VA_ARGS__)

#define OP_M_IDENTITY_(X,...) X
#define OP_R_SPACE_(X,ACC,...) X ACC
#define OP_R_COMMA_(X,ACC,...) X, ACC
#define OP_R_SEMICOLON_(X,ACC,...) X; ACC

#define OP_MAP_SP_S0_(M,               ...)    OP_MAP_SP_S1_(M,,__VA_ARGS__)
#define OP_MAP_SP_S1_(M,S1,            ...)    OP_MAP_SP_S2_(M,S1,,__VA_ARGS__)
#define OP_MAP_SP_S2_(M,S1,S2,         ...)    OP_MAP_SP_S3_(M,S1,S2,,__VA_ARGS__)
#define OP_MAP_SP_S3_(M,S1,S2,S3,      ...)    OP_MAP_SP_S4_(M,S1,S2,S3,,__VA_ARGS__)
#define OP_MAP_SP_S4_(M,S1,S2,S3,S4,   ...)    OP_MAP_SP_S5_(M,S1,S2,S3,S4,,__VA_ARGS__)
#define OP_MAP_SP_S5_(M,S1,S2,S3,S4,S5,...)    OP_MAP_SP_S6_(M,S1,S2,S3,S4,S5,,__VA_ARGS__)
#define OP_MAP_SP_S6_(M,S1,S2,S3,S4,S5,S6,...) OP_MR_S6_(M,OP_R_SPACE_,S1,S2,S3,S4,S5,S6,__VA_ARGS__)

#define OP_MAP_CM_S0_(M,               ...)    OP_MAP_CM_S1_(M,,__VA_ARGS__)
#define OP_MAP_CM_S1_(M,S1,            ...)    OP_MAP_CM_S2_(M,S1,,__VA_ARGS__)
#define OP_MAP_CM_S2_(M,S1,S2,         ...)    OP_MAP_CM_S3_(M,S1,S2,,__VA_ARGS__)
#define OP_MAP_CM_S3_(M,S1,S2,S3,      ...)    OP_MAP_CM_S4_(M,S1,S2,S3,,__VA_ARGS__)
#define OP_MAP_CM_S4_(M,S1,S2,S3,S4,   ...)    OP_MAP_CM_S5_(M,S1,S2,S3,S4,,__VA_ARGS__)
#define OP_MAP_CM_S5_(M,S1,S2,S3,S4,S5,...)    OP_MAP_CM_S6_(M,S1,S2,S3,S4,S5,,__VA_ARGS__)
#define OP_MAP_CM_S6_(M,S1,S2,S3,S4,S5,S6,...) OP_MR_S6_(M,OP_R_COMMA_,S1,S2,S3,S4,S5,S6,__VA_ARGS__)

#define OP_MAP_SC_S0_(M,               ...)    OP_MAP_SC_S1_(M,,__VA_ARGS__)
#define OP_MAP_SC_S1_(M,S1,            ...)    OP_MAP_SC_S2_(M,S1,,__VA_ARGS__)
#define OP_MAP_SC_S2_(M,S1,S2,         ...)    OP_MAP_SC_S3_(M,S1,S2,,__VA_ARGS__)
#define OP_MAP_SC_S3_(M,S1,S2,S3,      ...)    OP_MAP_SC_S4_(M,S1,S2,S3,,__VA_ARGS__)
#define OP_MAP_SC_S4_(M,S1,S2,S3,S4,   ...)    OP_MAP_SC_S5_(M,S1,S2,S3,S4,,__VA_ARGS__)
#define OP_MAP_SC_S5_(M,S1,S2,S3,S4,S5,...)    OP_MAP_SC_S6_(M,S1,S2,S3,S4,S5,,__VA_ARGS__)
#define OP_MAP_SC_S6_(M,S1,S2,S3,S4,S5,S6,...) OP_MR_S6_(M,OP_R_SEMICOLON_,S1,S2,S3,S4,S5,S6,__VA_ARGS__)

#define OP_FOLDR_S0_(R,                  ...) OP_FOLDR_S6_(R,,__VA_ARGS__)
#define OP_FOLDR_S1_(R,S1,               ...) OP_FOLDR_S6_(R,S1,,__VA_ARGS__)
#define OP_FOLDR_S2_(R,S1,S2,            ...) OP_FOLDR_S6_(R,S1,S2,,__VA_ARGS__)
#define OP_FOLDR_S3_(R,S1,S2,S3,         ...) OP_FOLDR_S6_(R,S1,S2,S3,,__VA_ARGS__)
#define OP_FOLDR_S4_(R,S1,S2,S3,S4,      ...) OP_FOLDR_S6_(R,S1,S2,S3,S4,,__VA_ARGS__)
#define OP_FOLDR_S5_(R,S1,S2,S3,S4,S5,   ...) OP_FOLDR_S6_(R,S1,S2,S3,S4,S5,,__VA_ARGS__)
#define OP_FOLDR_S6_(R,S1,S2,S3,S4,S5,S6,...) OP_MR_S6_(OP_M_IDENTITY_,R,S1,S2,S3,S4,S5,S6,__VA_ARGS__)


#define OP_MR_S6_(M,R,S1,S2,S3,S4,S5,S6,...) \
  _OP_GET_MACRO_BY_ARGS(__VA_ARGS__, \
   OP_MR_36_, OP_MR_35_, OP_MR_34_, OP_MR_33_, \
   OP_MR_32_, OP_MR_31_, OP_MR_30_, OP_MR_29_, \
   OP_MR_28_, OP_MR_27_, OP_MR_26_, OP_MR_25_, \
   OP_MR_24_, OP_MR_23_, OP_MR_22_, OP_MR_21_, \
   OP_MR_20_, OP_MR_19_, OP_MR_18_, OP_MR_17_, \
   OP_MR_16_, OP_MR_15_, OP_MR_14_, OP_MR_13_, \
   OP_MR_12_, OP_MR_11_, OP_MR_10_, OP_MR_09_, \
   OP_MR_08_, OP_MR_07_, OP_MR_06_, OP_MR_05_, \
   OP_MR_04_, OP_MR_03_, OP_MR_02_, OP_MR_01_,)(_OP_CNT_,M,R,S1,S2,S3,S4,S5,S6,__VA_ARGS__)

#define OP_MR_01_(I, M, R, S1, S2, S3, S4, S5, S6, X)        M(X,I,S1,S2,S3,S4,S5,S6)
#define OP_MR_02_(I, M, R, S1, S2, S3, S4, S5, S6, X, ...) R(M(X,I,S1,S2,S3,S4,S5,S6), OP_MR_01_(I##1,M,R,S1,S2,S3,S4,S5,S6,__VA_ARGS__) ,S1,S2,S3,S4,S5,S6)
#define OP_MR_03_(I, M, R, S1, S2, S3, S4, S5, S6, X, ...) R(M(X,I,S1,S2,S3,S4,S5,S6), OP_MR_02_(I##1,M,R,S1,S2,S3,S4,S5,S6,__VA_ARGS__) ,S1,S2,S3,S4,S5,S6)
#define OP_MR_04_(I, M, R, S1, S2, S3, S4, S5, S6, X, ...) R(M(X,I,S1,S2,S3,S4,S5,S6), OP_MR_03_(I##1,M,R,S1,S2,S3,S4,S5,S6,__VA_ARGS__) ,S1,S2,S3,S4,S5,S6)
#define OP_MR_05_(I, M, R, S1, S2, S3, S4, S5, S6, X, ...) R(M(X,I,S1,S2,S3,S4,S5,S6), OP_MR_04_(I##1,M,R,S1,S2,S3,S4,S5,S6,__VA_ARGS__) ,S1,S2,S3,S4,S5,S6)
#define OP_MR_06_(I, M, R, S1, S2, S3, S4, S5, S6, X, ...) R(M(X,I,S1,S2,S3,S4,S5,S6), OP_MR_05_(I##1,M,R,S1,S2,S3,S4,S5,S6,__VA_ARGS__) ,S1,S2,S3,S4,S5,S6)
#define OP_MR_07_(I, M, R, S1, S2, S3, S4, S5, S6, X, ...) R(M(X,I,S1,S2,S3,S4,S5,S6), OP_MR_06_(I##1,M,R,S1,S2,S3,S4,S5,S6,__VA_ARGS__) ,S1,S2,S3,S4,S5,S6)
#define OP_MR_08_(I, M, R, S1, S2, S3, S4, S5, S6, X, ...) R(M(X,I,S1,S2,S3,S4,S5,S6), OP_MR_07_(I##1,M,R,S1,S2,S3,S4,S5,S6,__VA_ARGS__) ,S1,S2,S3,S4,S5,S6)
#define OP_MR_09_(I, M, R, S1, S2, S3, S4, S5, S6, X, ...) R(M(X,I,S1,S2,S3,S4,S5,S6), OP_MR_08_(I##1,M,R,S1,S2,S3,S4,S5,S6,__VA_ARGS__) ,S1,S2,S3,S4,S5,S6)
#define OP_MR_10_(I, M, R, S1, S2, S3, S4, S5, S6, X, ...) R(M(X,I,S1,S2,S3,S4,S5,S6), OP_MR_09_(I##1,M,R,S1,S2,S3,S4,S5,S6,__VA_ARGS__) ,S1,S2,S3,S4,S5,S6)
#define OP_MR_11_(I, M, R, S1, S2, S3, S4, S5, S6, X, ...) R(M(X,I,S1,S2,S3,S4,S5,S6), OP_MR_10_(I##1,M,R,S1,S2,S3,S4,S5,S6,__VA_ARGS__) ,S1,S2,S3,S4,S5,S6)
#define OP_MR_12_(I, M, R, S1, S2, S3, S4, S5, S6, X, ...) R(M(X,I,S1,S2,S3,S4,S5,S6), OP_MR_11_(I##1,M,R,S1,S2,S3,S4,S5,S6,__VA_ARGS__) ,S1,S2,S3,S4,S5,S6)
#define OP_MR_13_(I, M, R, S1, S2, S3, S4, S5, S6, X, ...) R(M(X,I,S1,S2,S3,S4,S5,S6), OP_MR_12_(I##1,M,R,S1,S2,S3,S4,S5,S6,__VA_ARGS__) ,S1,S2,S3,S4,S5,S6)
#define OP_MR_14_(I, M, R, S1, S2, S3, S4, S5, S6, X, ...) R(M(X,I,S1,S2,S3,S4,S5,S6), OP_MR_13_(I##1,M,R,S1,S2,S3,S4,S5,S6,__VA_ARGS__) ,S1,S2,S3,S4,S5,S6)
#define OP_MR_15_(I, M, R, S1, S2, S3, S4, S5, S6, X, ...) R(M(X,I,S1,S2,S3,S4,S5,S6), OP_MR_14_(I##1,M,R,S1,S2,S3,S4,S5,S6,__VA_ARGS__) ,S1,S2,S3,S4,S5,S6)
#define OP_MR_16_(I, M, R, S1, S2, S3, S4, S5, S6, X, ...) R(M(X,I,S1,S2,S3,S4,S5,S6), OP_MR_15_(I##1,M,R,S1,S2,S3,S4,S5,S6,__VA_ARGS__) ,S1,S2,S3,S4,S5,S6)
#define OP_MR_17_(I, M, R, S1, S2, S3, S4, S5, S6, X, ...) R(M(X,I,S1,S2,S3,S4,S5,S6), OP_MR_16_(I##1,M,R,S1,S2,S3,S4,S5,S6,__VA_ARGS__) ,S1,S2,S3,S4,S5,S6)
#define OP_MR_18_(I, M, R, S1, S2, S3, S4, S5, S6, X, ...) R(M(X,I,S1,S2,S3,S4,S5,S6), OP_MR_17_(I##1,M,R,S1,S2,S3,S4,S5,S6,__VA_ARGS__) ,S1,S2,S3,S4,S5,S6)
#define OP_MR_19_(I, M, R, S1, S2, S3, S4, S5, S6, X, ...) R(M(X,I,S1,S2,S3,S4,S5,S6), OP_MR_18_(I##1,M,R,S1,S2,S3,S4,S5,S6,__VA_ARGS__) ,S1,S2,S3,S4,S5,S6)
#define OP_MR_20_(I, M, R, S1, S2, S3, S4, S5, S6, X, ...) R(M(X,I,S1,S2,S3,S4,S5,S6), OP_MR_19_(I##1,M,R,S1,S2,S3,S4,S5,S6,__VA_ARGS__) ,S1,S2,S3,S4,S5,S6)
#define OP_MR_21_(I, M, R, S1, S2, S3, S4, S5, S6, X, ...) R(M(X,I,S1,S2,S3,S4,S5,S6), OP_MR_20_(I##1,M,R,S1,S2,S3,S4,S5,S6,__VA_ARGS__) ,S1,S2,S3,S4,S5,S6)
#define OP_MR_22_(I, M, R, S1, S2, S3, S4, S5, S6, X, ...) R(M(X,I,S1,S2,S3,S4,S5,S6), OP_MR_21_(I##1,M,R,S1,S2,S3,S4,S5,S6,__VA_ARGS__) ,S1,S2,S3,S4,S5,S6)
#define OP_MR_23_(I, M, R, S1, S2, S3, S4, S5, S6, X, ...) R(M(X,I,S1,S2,S3,S4,S5,S6), OP_MR_22_(I##1,M,R,S1,S2,S3,S4,S5,S6,__VA_ARGS__) ,S1,S2,S3,S4,S5,S6)
#define OP_MR_24_(I, M, R, S1, S2, S3, S4, S5, S6, X, ...) R(M(X,I,S1,S2,S3,S4,S5,S6), OP_MR_23_(I##1,M,R,S1,S2,S3,S4,S5,S6,__VA_ARGS__) ,S1,S2,S3,S4,S5,S6)
#define OP_MR_25_(I, M, R, S1, S2, S3, S4, S5, S6, X, ...) R(M(X,I,S1,S2,S3,S4,S5,S6), OP_MR_24_(I##1,M,R,S1,S2,S3,S4,S5,S6,__VA_ARGS__) ,S1,S2,S3,S4,S5,S6)
#define OP_MR_26_(I, M, R, S1, S2, S3, S4, S5, S6, X, ...) R(M(X,I,S1,S2,S3,S4,S5,S6), OP_MR_25_(I##1,M,R,S1,S2,S3,S4,S5,S6,__VA_ARGS__) ,S1,S2,S3,S4,S5,S6)
#define OP_MR_27_(I, M, R, S1, S2, S3, S4, S5, S6, X, ...) R(M(X,I,S1,S2,S3,S4,S5,S6), OP_MR_26_(I##1,M,R,S1,S2,S3,S4,S5,S6,__VA_ARGS__) ,S1,S2,S3,S4,S5,S6)
#define OP_MR_28_(I, M, R, S1, S2, S3, S4, S5, S6, X, ...) R(M(X,I,S1,S2,S3,S4,S5,S6), OP_MR_27_(I##1,M,R,S1,S2,S3,S4,S5,S6,__VA_ARGS__) ,S1,S2,S3,S4,S5,S6)
#define OP_MR_29_(I, M, R, S1, S2, S3, S4, S5, S6, X, ...) R(M(X,I,S1,S2,S3,S4,S5,S6), OP_MR_28_(I##1,M,R,S1,S2,S3,S4,S5,S6,__VA_ARGS__) ,S1,S2,S3,S4,S5,S6)
#define OP_MR_30_(I, M, R, S1, S2, S3, S4, S5, S6, X, ...) R(M(X,I,S1,S2,S3,S4,S5,S6), OP_MR_29_(I##1,M,R,S1,S2,S3,S4,S5,S6,__VA_ARGS__) ,S1,S2,S3,S4,S5,S6)
#define OP_MR_31_(I, M, R, S1, S2, S3, S4, S5, S6, X, ...) R(M(X,I,S1,S2,S3,S4,S5,S6), OP_MR_30_(I##1,M,R,S1,S2,S3,S4,S5,S6,__VA_ARGS__) ,S1,S2,S3,S4,S5,S6)
#define OP_MR_32_(I, M, R, S1, S2, S3, S4, S5, S6, X, ...) R(M(X,I,S1,S2,S3,S4,S5,S6), OP_MR_31_(I##1,M,R,S1,S2,S3,S4,S5,S6,__VA_ARGS__) ,S1,S2,S3,S4,S5,S6)
#define OP_MR_33_(I, M, R, S1, S2, S3, S4, S5, S6, X, ...) R(M(X,I,S1,S2,S3,S4,S5,S6), OP_MR_32_(I##1,M,R,S1,S2,S3,S4,S5,S6,__VA_ARGS__) ,S1,S2,S3,S4,S5,S6)
#define OP_MR_34_(I, M, R, S1, S2, S3, S4, S5, S6, X, ...) R(M(X,I,S1,S2,S3,S4,S5,S6), OP_MR_33_(I##1,M,R,S1,S2,S3,S4,S5,S6,__VA_ARGS__) ,S1,S2,S3,S4,S5,S6)
#define OP_MR_35_(I, M, R, S1, S2, S3, S4, S5, S6, X, ...) R(M(X,I,S1,S2,S3,S4,S5,S6), OP_MR_34_(I##1,M,R,S1,S2,S3,S4,S5,S6,__VA_ARGS__) ,S1,S2,S3,S4,S5,S6)
#define OP_MR_36_(I, M, R, S1, S2, S3, S4, S5, S6, X, ...) R(M(X,I,S1,S2,S3,S4,S5,S6), OP_MR_35_(I##1,M,R,S1,S2,S3,S4,S5,S6,__VA_ARGS__) ,S1,S2,S3,S4,S5,S6)

#endif /* OP_MACROS_H */
