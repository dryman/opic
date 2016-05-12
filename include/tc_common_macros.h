#ifndef TC_COMMON_MACROS_H
#define TC_COMMON_MACROS_H 1

/* copied from sys/cdefs.h */
#if defined(__cplusplus)
#define TC_BEGIN_DECLS   extern "C" {
#define TC_END_DECLS }
#else
#define TC_BEGIN_DECLS
#define TC_END_DECLS
#endif
/* clang */
#ifndef __has_builtin
#define __has_builtin(x) 0
#endif

#if defined __GNUC__ || __has_builtin(__builtin_expect)
#define tc_likely(x) __builtin_expect ((x), 1)
#define tc_unlikely(x) __builtin_expect ((x), 0)
#else
#define tc_likely(x) (x)
#define tc_unlikely(x) (x)
#endif

#ifndef INLINE
# if __GNUC__ && !__GNUC_STDC_INLINE__
#  define INLINE extern inline
# else
#  define INLINE inline
# endif
#endif

#define _TC_GET_MACRO_BY_ARGS(_01,_02,_03,_04,_05,_06,_07,_08,_09,_10, \
                              _11,_12,_13,_14,_15,_16,_17,_18,_19,_20, \
                              _21,_22,_23,_24,_25,_26,_27,_28,_29,_30, \
                              _31,_32,_33,_34,_35,_36, NAME,...) NAME 

/**
 * TC_MR_S0(M,R)
 * Map Reduce macro without any scope variable
 * M must have signature M(X,IDX,...)
 * R must have signature R(X,ACC,...)
 */
#define TC_MR_S0(M,R,               ...) TC_MR_S1(M,R,,__VA_ARGS__)
#define TC_MR_S1(M,R,S1,            ...) TC_MR_S2(M,R,S1,,__VA_ARGS__)
#define TC_MR_S2(M,R,S1,S2,         ...) TC_MR_S3(M,R,S1,S2,,__VA_ARGS__)
#define TC_MR_S3(M,R,S1,S2,S3,      ...) TC_MR_S4(M,R,S1,S2,S3,,__VA_ARGS__)
#define TC_MR_S4(M,R,S1,S2,S3,S4,   ...) TC_MR_S5(M,R,S1,S2,S3,S4,,__VA_ARGS__)
#define TC_MR_S5(M,R,S1,S2,S3,S4,S5,...) TC_MR_S6(M,R,S1,S2,S3,S4,S5,,__VA_ARGS__)


#define TC_M_IDENTITY(X,...) X
#define TC_R_SPACE(X,ACC,...) X ACC
#define TC_R_COMMA(X,ACC,...) X, ACC
#define TC_R_SEMICOLON(X,ACC,...) X; ACC

#define TC_MAP_SP_S0(M,               ...)    TC_MAP_SP_S1(M,,__VA_ARGS__)
#define TC_MAP_SP_S1(M,S1,            ...)    TC_MAP_SP_S2(M,S1,,__VA_ARGS__)
#define TC_MAP_SP_S2(M,S1,S2,         ...)    TC_MAP_SP_S3(M,S1,S2,,__VA_ARGS__)
#define TC_MAP_SP_S3(M,S1,S2,S3,      ...)    TC_MAP_SP_S4(M,S1,S2,S3,,__VA_ARGS__)
#define TC_MAP_SP_S4(M,S1,S2,S3,S4,   ...)    TC_MAP_SP_S5(M,S1,S2,S3,S4,,__VA_ARGS__)
#define TC_MAP_SP_S5(M,S1,S2,S3,S4,S5,...)    TC_MAP_SP_S6(M,S1,S2,S3,S4,S5,,__VA_ARGS__)
#define TC_MAP_SP_S6(M,S1,S2,S3,S4,S5,S6,...) TC_MR_S6(M,TC_R_SPACE,S1,S2,S3,S4,S5,S6,__VA_ARGS__)

#define TC_MAP_CM_S0(M,               ...)    TC_MAP_CM_S1(M,,__VA_ARGS__)
#define TC_MAP_CM_S1(M,S1,            ...)    TC_MAP_CM_S2(M,S1,,__VA_ARGS__)
#define TC_MAP_CM_S2(M,S1,S2,         ...)    TC_MAP_CM_S3(M,S1,S2,,__VA_ARGS__)
#define TC_MAP_CM_S3(M,S1,S2,S3,      ...)    TC_MAP_CM_S4(M,S1,S2,S3,,__VA_ARGS__)
#define TC_MAP_CM_S4(M,S1,S2,S3,S4,   ...)    TC_MAP_CM_S5(M,S1,S2,S3,S4,,__VA_ARGS__)
#define TC_MAP_CM_S5(M,S1,S2,S3,S4,S5,...)    TC_MAP_CM_S6(M,S1,S2,S3,S4,S5,,__VA_ARGS__)
#define TC_MAP_CM_S6(M,S1,S2,S3,S4,S5,S6,...) TC_MR_S6(M,TC_R_COMMA,S1,S2,S3,S4,S5,S6,__VA_ARGS__)

#define TC_MAP_SC_S0(M,               ...)    TC_MAP_SC_S1(M,,__VA_ARGS__)
#define TC_MAP_SC_S1(M,S1,            ...)    TC_MAP_SC_S2(M,S1,,__VA_ARGS__)
#define TC_MAP_SC_S2(M,S1,S2,         ...)    TC_MAP_SC_S3(M,S1,S2,,__VA_ARGS__)
#define TC_MAP_SC_S3(M,S1,S2,S3,      ...)    TC_MAP_SC_S4(M,S1,S2,S3,,__VA_ARGS__)
#define TC_MAP_SC_S4(M,S1,S2,S3,S4,   ...)    TC_MAP_SC_S5(M,S1,S2,S3,S4,,__VA_ARGS__)
#define TC_MAP_SC_S5(M,S1,S2,S3,S4,S5,...)    TC_MAP_SC_S6(M,S1,S2,S3,S4,S5,,__VA_ARGS__)
#define TC_MAP_SC_S6(M,S1,S2,S3,S4,S5,S6,...) TC_MR_S6(M,TC_R_SEMICOLON,S1,S2,S3,S4,S5,S6,__VA_ARGS__)

#define TC_FOLDR_S0(R,                  ...) TC_FOLDR_S6(R,,__VA_ARGS__)
#define TC_FOLDR_S1(R,S1,               ...) TC_FOLDR_S6(R,S1,,__VA_ARGS__)
#define TC_FOLDR_S2(R,S1,S2,            ...) TC_FOLDR_S6(R,S1,S2,,__VA_ARGS__)
#define TC_FOLDR_S3(R,S1,S2,S3,         ...) TC_FOLDR_S6(R,S1,S2,S3,,__VA_ARGS__)
#define TC_FOLDR_S4(R,S1,S2,S3,S4,      ...) TC_FOLDR_S6(R,S1,S2,S3,S4,,__VA_ARGS__)
#define TC_FOLDR_S5(R,S1,S2,S3,S4,S5,   ...) TC_FOLDR_S6(R,S1,S2,S3,S4,S5,,__VA_ARGS__)
#define TC_FOLDR_S6(R,S1,S2,S3,S4,S5,S6,...) TC_MR_S6(TC_M_IDENTITY,R,S1,S2,S3,S4,S5,S6,__VA_ARGS__)

#define TC_FOLDL_S0(R,                  ...) TC_FOLDL_S6(R,,__VA_ARGS__)
#define TC_FOLDL_S1(R,S1,               ...) TC_FOLDL_S6(R,S1,,__VA_ARGS__)
#define TC_FOLDL_S2(R,S1,S2,            ...) TC_FOLDL_S6(R,S1,S2,,__VA_ARGS__)
#define TC_FOLDL_S3(R,S1,S2,S3,         ...) TC_FOLDL_S6(R,S1,S2,S3,,__VA_ARGS__)
#define TC_FOLDL_S4(R,S1,S2,S3,S4,      ...) TC_FOLDL_S6(R,S1,S2,S3,S4,,__VA_ARGS__)
#define TC_FOLDL_S5(R,S1,S2,S3,S4,S5,   ...) TC_FOLDL_S6(R,S1,S2,S3,S4,S5,,__VA_ARGS__)
#define TC_FOLDL_S6(R,S1,S2,S3,S4,S5,S6,...) TC_FOLDR_S6(R,S1,S2,S3,S4,S5,S6,TC_REVERSE(__VA_ARGS__))

#define TC_MR_S6(M,R,S1,S2,S3,S4,S5,S6,...) \
  _TC_GET_MACRO_BY_ARGS(__VA_ARGS__, \
   TC_MR_36, TC_MR_35, TC_MR_34, TC_MR_33, \
   TC_MR_32, TC_MR_31, TC_MR_30, TC_MR_29, \
   TC_MR_28, TC_MR_27, TC_MR_26, TC_MR_25, \
   TC_MR_24, TC_MR_23, TC_MR_22, TC_MR_21, \
   TC_MR_20, TC_MR_19, TC_MR_18, TC_MR_17, \
   TC_MR_16, TC_MR_15, TC_MR_14, TC_MR_13, \
   TC_MR_12, TC_MR_11, TC_MR_10, TC_MR_09, \
   TC_MR_08, TC_MR_07, TC_MR_06, TC_MR_05, \
   TC_MR_04, TC_MR_03, TC_MR_02, TC_MR_01,)(_TC_CNT_,M,R,S1,S2,S3,S4,S5,S6,__VA_ARGS__)

#define TC_REVERSE(...) \
  _TC_GET_MACRO_BY_ARGS(__VA_ARGS__, \
   TC_REV_36, TC_REV_35, TC_REV_34, TC_REV_33, \
   TC_REV_32, TC_REV_31, TC_REV_30, TC_REV_29, \
   TC_REV_28, TC_REV_27, TC_REV_26, TC_REV_25, \
   TC_REV_24, TC_REV_23, TC_REV_22, TC_REV_21, \
   TC_REV_20, TC_REV_19, TC_REV_18, TC_REV_17, \
   TC_REV_16, TC_REV_15, TC_REV_14, TC_REV_13, \
   TC_REV_12, TC_REV_11, TC_REV_10, TC_REV_09, \
   TC_REV_08, TC_REV_07, TC_REV_06, TC_REV_05, \
   TC_REV_04, TC_REV_03, TC_REV_02, TC_REV_01,)(__VA_ARGS__)

#define TC_LENGTH(...) \
  _TC_GET_MACRO_BY_ARGS(__VA_ARGS__, \
   TC_LEN_36, TC_LEN_35, TC_LEN_34, TC_LEN_33, \
   TC_LEN_32, TC_LEN_31, TC_LEN_30, TC_LEN_29, \
   TC_LEN_28, TC_LEN_27, TC_LEN_26, TC_LEN_25, \
   TC_LEN_24, TC_LEN_23, TC_LEN_22, TC_LEN_21, \
   TC_LEN_20, TC_LEN_19, TC_LEN_18, TC_LEN_17, \
   TC_LEN_16, TC_LEN_15, TC_LEN_14, TC_LEN_13, \
   TC_LEN_12, TC_LEN_11, TC_LEN_10, TC_LEN_09, \
   TC_LEN_08, TC_LEN_07, TC_LEN_06, TC_LEN_05, \
   TC_LEN_04, TC_LEN_03, TC_LEN_02, TC_LEN_01,)

#define TC_MR_01(I, M, R, S1, S2, S3, S4, S5, S6, X)        M(X,I,S1,S2,S3,S4,S5,S6)
#define TC_MR_02(I, M, R, S1, S2, S3, S4, S5, S6, X, ...) R(M(X,I,S1,S2,S3,S4,S5,S6), TC_MR_01(I##1,M,R,S1,S2,S3,S4,S5,S6,__VA_ARGS__) ,S1,S2,S3,S4,S5,S6)
#define TC_MR_03(I, M, R, S1, S2, S3, S4, S5, S6, X, ...) R(M(X,I,S1,S2,S3,S4,S5,S6), TC_MR_02(I##1,M,R,S1,S2,S3,S4,S5,S6,__VA_ARGS__) ,S1,S2,S3,S4,S5,S6)
#define TC_MR_04(I, M, R, S1, S2, S3, S4, S5, S6, X, ...) R(M(X,I,S1,S2,S3,S4,S5,S6), TC_MR_03(I##1,M,R,S1,S2,S3,S4,S5,S6,__VA_ARGS__) ,S1,S2,S3,S4,S5,S6)
#define TC_MR_05(I, M, R, S1, S2, S3, S4, S5, S6, X, ...) R(M(X,I,S1,S2,S3,S4,S5,S6), TC_MR_04(I##1,M,R,S1,S2,S3,S4,S5,S6,__VA_ARGS__) ,S1,S2,S3,S4,S5,S6)
#define TC_MR_06(I, M, R, S1, S2, S3, S4, S5, S6, X, ...) R(M(X,I,S1,S2,S3,S4,S5,S6), TC_MR_05(I##1,M,R,S1,S2,S3,S4,S5,S6,__VA_ARGS__) ,S1,S2,S3,S4,S5,S6)
#define TC_MR_07(I, M, R, S1, S2, S3, S4, S5, S6, X, ...) R(M(X,I,S1,S2,S3,S4,S5,S6), TC_MR_06(I##1,M,R,S1,S2,S3,S4,S5,S6,__VA_ARGS__) ,S1,S2,S3,S4,S5,S6)
#define TC_MR_08(I, M, R, S1, S2, S3, S4, S5, S6, X, ...) R(M(X,I,S1,S2,S3,S4,S5,S6), TC_MR_07(I##1,M,R,S1,S2,S3,S4,S5,S6,__VA_ARGS__) ,S1,S2,S3,S4,S5,S6)
#define TC_MR_09(I, M, R, S1, S2, S3, S4, S5, S6, X, ...) R(M(X,I,S1,S2,S3,S4,S5,S6), TC_MR_08(I##1,M,R,S1,S2,S3,S4,S5,S6,__VA_ARGS__) ,S1,S2,S3,S4,S5,S6)
#define TC_MR_10(I, M, R, S1, S2, S3, S4, S5, S6, X, ...) R(M(X,I,S1,S2,S3,S4,S5,S6), TC_MR_09(I##1,M,R,S1,S2,S3,S4,S5,S6,__VA_ARGS__) ,S1,S2,S3,S4,S5,S6)
#define TC_MR_11(I, M, R, S1, S2, S3, S4, S5, S6, X, ...) R(M(X,I,S1,S2,S3,S4,S5,S6), TC_MR_10(I##1,M,R,S1,S2,S3,S4,S5,S6,__VA_ARGS__) ,S1,S2,S3,S4,S5,S6)
#define TC_MR_12(I, M, R, S1, S2, S3, S4, S5, S6, X, ...) R(M(X,I,S1,S2,S3,S4,S5,S6), TC_MR_11(I##1,M,R,S1,S2,S3,S4,S5,S6,__VA_ARGS__) ,S1,S2,S3,S4,S5,S6)
#define TC_MR_13(I, M, R, S1, S2, S3, S4, S5, S6, X, ...) R(M(X,I,S1,S2,S3,S4,S5,S6), TC_MR_12(I##1,M,R,S1,S2,S3,S4,S5,S6,__VA_ARGS__) ,S1,S2,S3,S4,S5,S6)
#define TC_MR_14(I, M, R, S1, S2, S3, S4, S5, S6, X, ...) R(M(X,I,S1,S2,S3,S4,S5,S6), TC_MR_13(I##1,M,R,S1,S2,S3,S4,S5,S6,__VA_ARGS__) ,S1,S2,S3,S4,S5,S6)
#define TC_MR_15(I, M, R, S1, S2, S3, S4, S5, S6, X, ...) R(M(X,I,S1,S2,S3,S4,S5,S6), TC_MR_14(I##1,M,R,S1,S2,S3,S4,S5,S6,__VA_ARGS__) ,S1,S2,S3,S4,S5,S6)
#define TC_MR_16(I, M, R, S1, S2, S3, S4, S5, S6, X, ...) R(M(X,I,S1,S2,S3,S4,S5,S6), TC_MR_15(I##1,M,R,S1,S2,S3,S4,S5,S6,__VA_ARGS__) ,S1,S2,S3,S4,S5,S6)
#define TC_MR_17(I, M, R, S1, S2, S3, S4, S5, S6, X, ...) R(M(X,I,S1,S2,S3,S4,S5,S6), TC_MR_16(I##1,M,R,S1,S2,S3,S4,S5,S6,__VA_ARGS__) ,S1,S2,S3,S4,S5,S6)
#define TC_MR_18(I, M, R, S1, S2, S3, S4, S5, S6, X, ...) R(M(X,I,S1,S2,S3,S4,S5,S6), TC_MR_17(I##1,M,R,S1,S2,S3,S4,S5,S6,__VA_ARGS__) ,S1,S2,S3,S4,S5,S6)
#define TC_MR_19(I, M, R, S1, S2, S3, S4, S5, S6, X, ...) R(M(X,I,S1,S2,S3,S4,S5,S6), TC_MR_18(I##1,M,R,S1,S2,S3,S4,S5,S6,__VA_ARGS__) ,S1,S2,S3,S4,S5,S6)
#define TC_MR_20(I, M, R, S1, S2, S3, S4, S5, S6, X, ...) R(M(X,I,S1,S2,S3,S4,S5,S6), TC_MR_19(I##1,M,R,S1,S2,S3,S4,S5,S6,__VA_ARGS__) ,S1,S2,S3,S4,S5,S6)
#define TC_MR_21(I, M, R, S1, S2, S3, S4, S5, S6, X, ...) R(M(X,I,S1,S2,S3,S4,S5,S6), TC_MR_20(I##1,M,R,S1,S2,S3,S4,S5,S6,__VA_ARGS__) ,S1,S2,S3,S4,S5,S6)
#define TC_MR_22(I, M, R, S1, S2, S3, S4, S5, S6, X, ...) R(M(X,I,S1,S2,S3,S4,S5,S6), TC_MR_21(I##1,M,R,S1,S2,S3,S4,S5,S6,__VA_ARGS__) ,S1,S2,S3,S4,S5,S6)
#define TC_MR_23(I, M, R, S1, S2, S3, S4, S5, S6, X, ...) R(M(X,I,S1,S2,S3,S4,S5,S6), TC_MR_22(I##1,M,R,S1,S2,S3,S4,S5,S6,__VA_ARGS__) ,S1,S2,S3,S4,S5,S6)
#define TC_MR_24(I, M, R, S1, S2, S3, S4, S5, S6, X, ...) R(M(X,I,S1,S2,S3,S4,S5,S6), TC_MR_23(I##1,M,R,S1,S2,S3,S4,S5,S6,__VA_ARGS__) ,S1,S2,S3,S4,S5,S6)
#define TC_MR_25(I, M, R, S1, S2, S3, S4, S5, S6, X, ...) R(M(X,I,S1,S2,S3,S4,S5,S6), TC_MR_24(I##1,M,R,S1,S2,S3,S4,S5,S6,__VA_ARGS__) ,S1,S2,S3,S4,S5,S6)
#define TC_MR_26(I, M, R, S1, S2, S3, S4, S5, S6, X, ...) R(M(X,I,S1,S2,S3,S4,S5,S6), TC_MR_25(I##1,M,R,S1,S2,S3,S4,S5,S6,__VA_ARGS__) ,S1,S2,S3,S4,S5,S6)
#define TC_MR_27(I, M, R, S1, S2, S3, S4, S5, S6, X, ...) R(M(X,I,S1,S2,S3,S4,S5,S6), TC_MR_26(I##1,M,R,S1,S2,S3,S4,S5,S6,__VA_ARGS__) ,S1,S2,S3,S4,S5,S6)
#define TC_MR_28(I, M, R, S1, S2, S3, S4, S5, S6, X, ...) R(M(X,I,S1,S2,S3,S4,S5,S6), TC_MR_27(I##1,M,R,S1,S2,S3,S4,S5,S6,__VA_ARGS__) ,S1,S2,S3,S4,S5,S6)
#define TC_MR_29(I, M, R, S1, S2, S3, S4, S5, S6, X, ...) R(M(X,I,S1,S2,S3,S4,S5,S6), TC_MR_28(I##1,M,R,S1,S2,S3,S4,S5,S6,__VA_ARGS__) ,S1,S2,S3,S4,S5,S6)
#define TC_MR_30(I, M, R, S1, S2, S3, S4, S5, S6, X, ...) R(M(X,I,S1,S2,S3,S4,S5,S6), TC_MR_29(I##1,M,R,S1,S2,S3,S4,S5,S6,__VA_ARGS__) ,S1,S2,S3,S4,S5,S6)
#define TC_MR_31(I, M, R, S1, S2, S3, S4, S5, S6, X, ...) R(M(X,I,S1,S2,S3,S4,S5,S6), TC_MR_30(I##1,M,R,S1,S2,S3,S4,S5,S6,__VA_ARGS__) ,S1,S2,S3,S4,S5,S6)
#define TC_MR_32(I, M, R, S1, S2, S3, S4, S5, S6, X, ...) R(M(X,I,S1,S2,S3,S4,S5,S6), TC_MR_31(I##1,M,R,S1,S2,S3,S4,S5,S6,__VA_ARGS__) ,S1,S2,S3,S4,S5,S6)
#define TC_MR_33(I, M, R, S1, S2, S3, S4, S5, S6, X, ...) R(M(X,I,S1,S2,S3,S4,S5,S6), TC_MR_32(I##1,M,R,S1,S2,S3,S4,S5,S6,__VA_ARGS__) ,S1,S2,S3,S4,S5,S6)
#define TC_MR_34(I, M, R, S1, S2, S3, S4, S5, S6, X, ...) R(M(X,I,S1,S2,S3,S4,S5,S6), TC_MR_33(I##1,M,R,S1,S2,S3,S4,S5,S6,__VA_ARGS__) ,S1,S2,S3,S4,S5,S6)
#define TC_MR_35(I, M, R, S1, S2, S3, S4, S5, S6, X, ...) R(M(X,I,S1,S2,S3,S4,S5,S6), TC_MR_34(I##1,M,R,S1,S2,S3,S4,S5,S6,__VA_ARGS__) ,S1,S2,S3,S4,S5,S6)
#define TC_MR_36(I, M, R, S1, S2, S3, S4, S5, S6, X, ...) R(M(X,I,S1,S2,S3,S4,S5,S6), TC_MR_35(I##1,M,R,S1,S2,S3,S4,S5,S6,__VA_ARGS__) ,S1,S2,S3,S4,S5,S6)


#define TC_REV_01(X) X
#define TC_REV_02(X,...) TC_REV_01(__VA_ARGS__), X
#define TC_REV_03(X,...) TC_REV_02(__VA_ARGS__), X
#define TC_REV_04(X,...) TC_REV_03(__VA_ARGS__), X
#define TC_REV_05(X,...) TC_REV_04(__VA_ARGS__), X
#define TC_REV_06(X,...) TC_REV_05(__VA_ARGS__), X
#define TC_REV_07(X,...) TC_REV_06(__VA_ARGS__), X
#define TC_REV_08(X,...) TC_REV_07(__VA_ARGS__), X
#define TC_REV_09(X,...) TC_REV_08(__VA_ARGS__), X
#define TC_REV_10(X,...) TC_REV_09(__VA_ARGS__), X
#define TC_REV_11(X,...) TC_REV_10(__VA_ARGS__), X
#define TC_REV_12(X,...) TC_REV_11(__VA_ARGS__), X
#define TC_REV_13(X,...) TC_REV_12(__VA_ARGS__), X
#define TC_REV_14(X,...) TC_REV_13(__VA_ARGS__), X
#define TC_REV_15(X,...) TC_REV_14(__VA_ARGS__), X
#define TC_REV_16(X,...) TC_REV_15(__VA_ARGS__), X
#define TC_REV_17(X,...) TC_REV_16(__VA_ARGS__), X
#define TC_REV_18(X,...) TC_REV_17(__VA_ARGS__), X
#define TC_REV_19(X,...) TC_REV_18(__VA_ARGS__), X
#define TC_REV_20(X,...) TC_REV_19(__VA_ARGS__), X
#define TC_REV_21(X,...) TC_REV_20(__VA_ARGS__), X
#define TC_REV_22(X,...) TC_REV_21(__VA_ARGS__), X
#define TC_REV_23(X,...) TC_REV_22(__VA_ARGS__), X
#define TC_REV_24(X,...) TC_REV_23(__VA_ARGS__), X
#define TC_REV_25(X,...) TC_REV_24(__VA_ARGS__), X
#define TC_REV_26(X,...) TC_REV_25(__VA_ARGS__), X
#define TC_REV_27(X,...) TC_REV_26(__VA_ARGS__), X
#define TC_REV_28(X,...) TC_REV_27(__VA_ARGS__), X
#define TC_REV_29(X,...) TC_REV_28(__VA_ARGS__), X
#define TC_REV_30(X,...) TC_REV_29(__VA_ARGS__), X
#define TC_REV_31(X,...) TC_REV_30(__VA_ARGS__), X
#define TC_REV_32(X,...) TC_REV_31(__VA_ARGS__), X
#define TC_REV_33(X,...) TC_REV_32(__VA_ARGS__), X
#define TC_REV_34(X,...) TC_REV_33(__VA_ARGS__), X
#define TC_REV_35(X,...) TC_REV_34(__VA_ARGS__), X
#define TC_REV_36(X,...) TC_REV_35(__VA_ARGS__), X

#define TC_LEN_01 1
#define TC_LEN_02 2
#define TC_LEN_03 3
#define TC_LEN_04 4
#define TC_LEN_05 5
#define TC_LEN_06 6
#define TC_LEN_07 7
#define TC_LEN_08 8
#define TC_LEN_09 9
#define TC_LEN_10 10
#define TC_LEN_11 11
#define TC_LEN_12 12
#define TC_LEN_13 13
#define TC_LEN_14 14
#define TC_LEN_15 15
#define TC_LEN_16 16
#define TC_LEN_17 17
#define TC_LEN_18 18
#define TC_LEN_19 19
#define TC_LEN_20 20
#define TC_LEN_21 21
#define TC_LEN_22 22
#define TC_LEN_23 23
#define TC_LEN_24 24
#define TC_LEN_25 25
#define TC_LEN_26 26
#define TC_LEN_27 27
#define TC_LEN_28 28
#define TC_LEN_29 29
#define TC_LEN_30 30
#define TC_LEN_31 31
#define TC_LEN_32 32
#define TC_LEN_33 33
#define TC_LEN_34 34
#define TC_LEN_35 35
#define TC_LEN_36 36

#define _TC_CNT_ 0
#define _TC_CNT_1 1
#define _TC_CNT_11 2
#define _TC_CNT_111 3
#define _TC_CNT_1111 4
#define _TC_CNT_11111 5
#define _TC_CNT_111111 6
#define _TC_CNT_1111111 7
#define _TC_CNT_11111111 8
#define _TC_CNT_111111111 9
#define _TC_CNT_1111111111 10
#define _TC_CNT_11111111111 11
#define _TC_CNT_111111111111 12
#define _TC_CNT_1111111111111 13
#define _TC_CNT_11111111111111 14
#define _TC_CNT_111111111111111 15
#define _TC_CNT_1111111111111111 16
#define _TC_CNT_11111111111111111 17
#define _TC_CNT_111111111111111111 18
#define _TC_CNT_1111111111111111111 19
#define _TC_CNT_11111111111111111111 20
#define _TC_CNT_111111111111111111111 21
#define _TC_CNT_1111111111111111111111 22
#define _TC_CNT_11111111111111111111111 23
#define _TC_CNT_111111111111111111111111 24
#define _TC_CNT_1111111111111111111111111 25
#define _TC_CNT_11111111111111111111111111 26
#define _TC_CNT_111111111111111111111111111 27
#define _TC_CNT_1111111111111111111111111111 28
#define _TC_CNT_11111111111111111111111111111 29
#define _TC_CNT_111111111111111111111111111111 30
#define _TC_CNT_1111111111111111111111111111111 31
#define _TC_CNT_11111111111111111111111111111111 32
#define _TC_CNT_111111111111111111111111111111111 33
#define _TC_CNT_1111111111111111111111111111111111 34
#define _TC_CNT_11111111111111111111111111111111111 35
#define _TC_CNT_111111111111111111111111111111111111 36

/* same macros in with postfix _ to work around nested macro expansions */

#define TC_MR_S0_(M,R,               ...) TC_MR_S1_(M,R,,__VA_ARGS__)
#define TC_MR_S1_(M,R,S1,            ...) TC_MR_S2_(M,R,S1,,__VA_ARGS__)
#define TC_MR_S2_(M,R,S1,S2,         ...) TC_MR_S3_(M,R,S1,S2,,__VA_ARGS__)
#define TC_MR_S3_(M,R,S1,S2,S3,      ...) TC_MR_S4_(M,R,S1,S2,S3,,__VA_ARGS__)
#define TC_MR_S4_(M,R,S1,S2,S3,S4,   ...) TC_MR_S5_(M,R,S1,S2,S3,S4,,__VA_ARGS__)
#define TC_MR_S5_(M,R,S1,S2,S3,S4,S5,...) TC_MR_S6_(M,R,S1,S2,S3,S4,S5,,__VA_ARGS__)

#define TC_M_IDENTITY_(X,...) X
#define TC_R_SPACE_(X,ACC,...) X ACC
#define TC_R_COMMA_(X,ACC,...) X, ACC
#define TC_R_SEMICOLON_(X,ACC,...) X; ACC

#define TC_MAP_SP_S0_(M,               ...)    TC_MAP_SP_S1_(M,,__VA_ARGS__)
#define TC_MAP_SP_S1_(M,S1,            ...)    TC_MAP_SP_S2_(M,S1,,__VA_ARGS__)
#define TC_MAP_SP_S2_(M,S1,S2,         ...)    TC_MAP_SP_S3_(M,S1,S2,,__VA_ARGS__)
#define TC_MAP_SP_S3_(M,S1,S2,S3,      ...)    TC_MAP_SP_S4_(M,S1,S2,S3,,__VA_ARGS__)
#define TC_MAP_SP_S4_(M,S1,S2,S3,S4,   ...)    TC_MAP_SP_S5_(M,S1,S2,S3,S4,,__VA_ARGS__)
#define TC_MAP_SP_S5_(M,S1,S2,S3,S4,S5,...)    TC_MAP_SP_S6_(M,S1,S2,S3,S4,S5,,__VA_ARGS__)
#define TC_MAP_SP_S6_(M,S1,S2,S3,S4,S5,S6,...) TC_MR_S6_(M,TC_R_SPACE_,S1,S2,S3,S4,S5,S6,__VA_ARGS__)

#define TC_MAP_CM_S0_(M,               ...)    TC_MAP_CM_S1_(M,,__VA_ARGS__)
#define TC_MAP_CM_S1_(M,S1,            ...)    TC_MAP_CM_S2_(M,S1,,__VA_ARGS__)
#define TC_MAP_CM_S2_(M,S1,S2,         ...)    TC_MAP_CM_S3_(M,S1,S2,,__VA_ARGS__)
#define TC_MAP_CM_S3_(M,S1,S2,S3,      ...)    TC_MAP_CM_S4_(M,S1,S2,S3,,__VA_ARGS__)
#define TC_MAP_CM_S4_(M,S1,S2,S3,S4,   ...)    TC_MAP_CM_S5_(M,S1,S2,S3,S4,,__VA_ARGS__)
#define TC_MAP_CM_S5_(M,S1,S2,S3,S4,S5,...)    TC_MAP_CM_S6_(M,S1,S2,S3,S4,S5,,__VA_ARGS__)
#define TC_MAP_CM_S6_(M,S1,S2,S3,S4,S5,S6,...) TC_MR_S6_(M,TC_R_COMMA_,S1,S2,S3,S4,S5,S6,__VA_ARGS__)

#define TC_MAP_SC_S0_(M,               ...)    TC_MAP_SC_S1_(M,,__VA_ARGS__)
#define TC_MAP_SC_S1_(M,S1,            ...)    TC_MAP_SC_S2_(M,S1,,__VA_ARGS__)
#define TC_MAP_SC_S2_(M,S1,S2,         ...)    TC_MAP_SC_S3_(M,S1,S2,,__VA_ARGS__)
#define TC_MAP_SC_S3_(M,S1,S2,S3,      ...)    TC_MAP_SC_S4_(M,S1,S2,S3,,__VA_ARGS__)
#define TC_MAP_SC_S4_(M,S1,S2,S3,S4,   ...)    TC_MAP_SC_S5_(M,S1,S2,S3,S4,,__VA_ARGS__)
#define TC_MAP_SC_S5_(M,S1,S2,S3,S4,S5,...)    TC_MAP_SC_S6_(M,S1,S2,S3,S4,S5,,__VA_ARGS__)
#define TC_MAP_SC_S6_(M,S1,S2,S3,S4,S5,S6,...) TC_MR_S6_(M,TC_R_SEMICOLON_,S1,S2,S3,S4,S5,S6,__VA_ARGS__)

#define TC_FOLDR_S0_(R,                  ...) TC_FOLDR_S6_(R,,__VA_ARGS__)
#define TC_FOLDR_S1_(R,S1,               ...) TC_FOLDR_S6_(R,S1,,__VA_ARGS__)
#define TC_FOLDR_S2_(R,S1,S2,            ...) TC_FOLDR_S6_(R,S1,S2,,__VA_ARGS__)
#define TC_FOLDR_S3_(R,S1,S2,S3,         ...) TC_FOLDR_S6_(R,S1,S2,S3,,__VA_ARGS__)
#define TC_FOLDR_S4_(R,S1,S2,S3,S4,      ...) TC_FOLDR_S6_(R,S1,S2,S3,S4,,__VA_ARGS__)
#define TC_FOLDR_S5_(R,S1,S2,S3,S4,S5,   ...) TC_FOLDR_S6_(R,S1,S2,S3,S4,S5,,__VA_ARGS__)
#define TC_FOLDR_S6_(R,S1,S2,S3,S4,S5,S6,...) TC_MR_S6_(TC_M_IDENTITY_,R,S1,S2,S3,S4,S5,S6,__VA_ARGS__)


#define TC_MR_S6_(M,R,S1,S2,S3,S4,S5,S6,...) \
  _TC_GET_MACRO_BY_ARGS(__VA_ARGS__, \
   TC_MR_36_, TC_MR_35_, TC_MR_34_, TC_MR_33_, \
   TC_MR_32_, TC_MR_31_, TC_MR_30_, TC_MR_29_, \
   TC_MR_28_, TC_MR_27_, TC_MR_26_, TC_MR_25_, \
   TC_MR_24_, TC_MR_23_, TC_MR_22_, TC_MR_21_, \
   TC_MR_20_, TC_MR_19_, TC_MR_18_, TC_MR_17_, \
   TC_MR_16_, TC_MR_15_, TC_MR_14_, TC_MR_13_, \
   TC_MR_12_, TC_MR_11_, TC_MR_10_, TC_MR_09_, \
   TC_MR_08_, TC_MR_07_, TC_MR_06_, TC_MR_05_, \
   TC_MR_04_, TC_MR_03_, TC_MR_02_, TC_MR_01_,)(_TC_CNT_,M,R,S1,S2,S3,S4,S5,S6,__VA_ARGS__)

#define TC_MR_01_(I, M, R, S1, S2, S3, S4, S5, S6, X)        M(X,I,S1,S2,S3,S4,S5,S6)
#define TC_MR_02_(I, M, R, S1, S2, S3, S4, S5, S6, X, ...) R(M(X,I,S1,S2,S3,S4,S5,S6), TC_MR_01_(I##1,M,R,S1,S2,S3,S4,S5,S6,__VA_ARGS__) ,S1,S2,S3,S4,S5,S6)
#define TC_MR_03_(I, M, R, S1, S2, S3, S4, S5, S6, X, ...) R(M(X,I,S1,S2,S3,S4,S5,S6), TC_MR_02_(I##1,M,R,S1,S2,S3,S4,S5,S6,__VA_ARGS__) ,S1,S2,S3,S4,S5,S6)
#define TC_MR_04_(I, M, R, S1, S2, S3, S4, S5, S6, X, ...) R(M(X,I,S1,S2,S3,S4,S5,S6), TC_MR_03_(I##1,M,R,S1,S2,S3,S4,S5,S6,__VA_ARGS__) ,S1,S2,S3,S4,S5,S6)
#define TC_MR_05_(I, M, R, S1, S2, S3, S4, S5, S6, X, ...) R(M(X,I,S1,S2,S3,S4,S5,S6), TC_MR_04_(I##1,M,R,S1,S2,S3,S4,S5,S6,__VA_ARGS__) ,S1,S2,S3,S4,S5,S6)
#define TC_MR_06_(I, M, R, S1, S2, S3, S4, S5, S6, X, ...) R(M(X,I,S1,S2,S3,S4,S5,S6), TC_MR_05_(I##1,M,R,S1,S2,S3,S4,S5,S6,__VA_ARGS__) ,S1,S2,S3,S4,S5,S6)
#define TC_MR_07_(I, M, R, S1, S2, S3, S4, S5, S6, X, ...) R(M(X,I,S1,S2,S3,S4,S5,S6), TC_MR_06_(I##1,M,R,S1,S2,S3,S4,S5,S6,__VA_ARGS__) ,S1,S2,S3,S4,S5,S6)
#define TC_MR_08_(I, M, R, S1, S2, S3, S4, S5, S6, X, ...) R(M(X,I,S1,S2,S3,S4,S5,S6), TC_MR_07_(I##1,M,R,S1,S2,S3,S4,S5,S6,__VA_ARGS__) ,S1,S2,S3,S4,S5,S6)
#define TC_MR_09_(I, M, R, S1, S2, S3, S4, S5, S6, X, ...) R(M(X,I,S1,S2,S3,S4,S5,S6), TC_MR_08_(I##1,M,R,S1,S2,S3,S4,S5,S6,__VA_ARGS__) ,S1,S2,S3,S4,S5,S6)
#define TC_MR_10_(I, M, R, S1, S2, S3, S4, S5, S6, X, ...) R(M(X,I,S1,S2,S3,S4,S5,S6), TC_MR_09_(I##1,M,R,S1,S2,S3,S4,S5,S6,__VA_ARGS__) ,S1,S2,S3,S4,S5,S6)
#define TC_MR_11_(I, M, R, S1, S2, S3, S4, S5, S6, X, ...) R(M(X,I,S1,S2,S3,S4,S5,S6), TC_MR_10_(I##1,M,R,S1,S2,S3,S4,S5,S6,__VA_ARGS__) ,S1,S2,S3,S4,S5,S6)
#define TC_MR_12_(I, M, R, S1, S2, S3, S4, S5, S6, X, ...) R(M(X,I,S1,S2,S3,S4,S5,S6), TC_MR_11_(I##1,M,R,S1,S2,S3,S4,S5,S6,__VA_ARGS__) ,S1,S2,S3,S4,S5,S6)
#define TC_MR_13_(I, M, R, S1, S2, S3, S4, S5, S6, X, ...) R(M(X,I,S1,S2,S3,S4,S5,S6), TC_MR_12_(I##1,M,R,S1,S2,S3,S4,S5,S6,__VA_ARGS__) ,S1,S2,S3,S4,S5,S6)
#define TC_MR_14_(I, M, R, S1, S2, S3, S4, S5, S6, X, ...) R(M(X,I,S1,S2,S3,S4,S5,S6), TC_MR_13_(I##1,M,R,S1,S2,S3,S4,S5,S6,__VA_ARGS__) ,S1,S2,S3,S4,S5,S6)
#define TC_MR_15_(I, M, R, S1, S2, S3, S4, S5, S6, X, ...) R(M(X,I,S1,S2,S3,S4,S5,S6), TC_MR_14_(I##1,M,R,S1,S2,S3,S4,S5,S6,__VA_ARGS__) ,S1,S2,S3,S4,S5,S6)
#define TC_MR_16_(I, M, R, S1, S2, S3, S4, S5, S6, X, ...) R(M(X,I,S1,S2,S3,S4,S5,S6), TC_MR_15_(I##1,M,R,S1,S2,S3,S4,S5,S6,__VA_ARGS__) ,S1,S2,S3,S4,S5,S6)
#define TC_MR_17_(I, M, R, S1, S2, S3, S4, S5, S6, X, ...) R(M(X,I,S1,S2,S3,S4,S5,S6), TC_MR_16_(I##1,M,R,S1,S2,S3,S4,S5,S6,__VA_ARGS__) ,S1,S2,S3,S4,S5,S6)
#define TC_MR_18_(I, M, R, S1, S2, S3, S4, S5, S6, X, ...) R(M(X,I,S1,S2,S3,S4,S5,S6), TC_MR_17_(I##1,M,R,S1,S2,S3,S4,S5,S6,__VA_ARGS__) ,S1,S2,S3,S4,S5,S6)
#define TC_MR_19_(I, M, R, S1, S2, S3, S4, S5, S6, X, ...) R(M(X,I,S1,S2,S3,S4,S5,S6), TC_MR_18_(I##1,M,R,S1,S2,S3,S4,S5,S6,__VA_ARGS__) ,S1,S2,S3,S4,S5,S6)
#define TC_MR_20_(I, M, R, S1, S2, S3, S4, S5, S6, X, ...) R(M(X,I,S1,S2,S3,S4,S5,S6), TC_MR_19_(I##1,M,R,S1,S2,S3,S4,S5,S6,__VA_ARGS__) ,S1,S2,S3,S4,S5,S6)
#define TC_MR_21_(I, M, R, S1, S2, S3, S4, S5, S6, X, ...) R(M(X,I,S1,S2,S3,S4,S5,S6), TC_MR_20_(I##1,M,R,S1,S2,S3,S4,S5,S6,__VA_ARGS__) ,S1,S2,S3,S4,S5,S6)
#define TC_MR_22_(I, M, R, S1, S2, S3, S4, S5, S6, X, ...) R(M(X,I,S1,S2,S3,S4,S5,S6), TC_MR_21_(I##1,M,R,S1,S2,S3,S4,S5,S6,__VA_ARGS__) ,S1,S2,S3,S4,S5,S6)
#define TC_MR_23_(I, M, R, S1, S2, S3, S4, S5, S6, X, ...) R(M(X,I,S1,S2,S3,S4,S5,S6), TC_MR_22_(I##1,M,R,S1,S2,S3,S4,S5,S6,__VA_ARGS__) ,S1,S2,S3,S4,S5,S6)
#define TC_MR_24_(I, M, R, S1, S2, S3, S4, S5, S6, X, ...) R(M(X,I,S1,S2,S3,S4,S5,S6), TC_MR_23_(I##1,M,R,S1,S2,S3,S4,S5,S6,__VA_ARGS__) ,S1,S2,S3,S4,S5,S6)
#define TC_MR_25_(I, M, R, S1, S2, S3, S4, S5, S6, X, ...) R(M(X,I,S1,S2,S3,S4,S5,S6), TC_MR_24_(I##1,M,R,S1,S2,S3,S4,S5,S6,__VA_ARGS__) ,S1,S2,S3,S4,S5,S6)
#define TC_MR_26_(I, M, R, S1, S2, S3, S4, S5, S6, X, ...) R(M(X,I,S1,S2,S3,S4,S5,S6), TC_MR_25_(I##1,M,R,S1,S2,S3,S4,S5,S6,__VA_ARGS__) ,S1,S2,S3,S4,S5,S6)
#define TC_MR_27_(I, M, R, S1, S2, S3, S4, S5, S6, X, ...) R(M(X,I,S1,S2,S3,S4,S5,S6), TC_MR_26_(I##1,M,R,S1,S2,S3,S4,S5,S6,__VA_ARGS__) ,S1,S2,S3,S4,S5,S6)
#define TC_MR_28_(I, M, R, S1, S2, S3, S4, S5, S6, X, ...) R(M(X,I,S1,S2,S3,S4,S5,S6), TC_MR_27_(I##1,M,R,S1,S2,S3,S4,S5,S6,__VA_ARGS__) ,S1,S2,S3,S4,S5,S6)
#define TC_MR_29_(I, M, R, S1, S2, S3, S4, S5, S6, X, ...) R(M(X,I,S1,S2,S3,S4,S5,S6), TC_MR_28_(I##1,M,R,S1,S2,S3,S4,S5,S6,__VA_ARGS__) ,S1,S2,S3,S4,S5,S6)
#define TC_MR_30_(I, M, R, S1, S2, S3, S4, S5, S6, X, ...) R(M(X,I,S1,S2,S3,S4,S5,S6), TC_MR_29_(I##1,M,R,S1,S2,S3,S4,S5,S6,__VA_ARGS__) ,S1,S2,S3,S4,S5,S6)
#define TC_MR_31_(I, M, R, S1, S2, S3, S4, S5, S6, X, ...) R(M(X,I,S1,S2,S3,S4,S5,S6), TC_MR_30_(I##1,M,R,S1,S2,S3,S4,S5,S6,__VA_ARGS__) ,S1,S2,S3,S4,S5,S6)
#define TC_MR_32_(I, M, R, S1, S2, S3, S4, S5, S6, X, ...) R(M(X,I,S1,S2,S3,S4,S5,S6), TC_MR_31_(I##1,M,R,S1,S2,S3,S4,S5,S6,__VA_ARGS__) ,S1,S2,S3,S4,S5,S6)
#define TC_MR_33_(I, M, R, S1, S2, S3, S4, S5, S6, X, ...) R(M(X,I,S1,S2,S3,S4,S5,S6), TC_MR_32_(I##1,M,R,S1,S2,S3,S4,S5,S6,__VA_ARGS__) ,S1,S2,S3,S4,S5,S6)
#define TC_MR_34_(I, M, R, S1, S2, S3, S4, S5, S6, X, ...) R(M(X,I,S1,S2,S3,S4,S5,S6), TC_MR_33_(I##1,M,R,S1,S2,S3,S4,S5,S6,__VA_ARGS__) ,S1,S2,S3,S4,S5,S6)
#define TC_MR_35_(I, M, R, S1, S2, S3, S4, S5, S6, X, ...) R(M(X,I,S1,S2,S3,S4,S5,S6), TC_MR_34_(I##1,M,R,S1,S2,S3,S4,S5,S6,__VA_ARGS__) ,S1,S2,S3,S4,S5,S6)
#define TC_MR_36_(I, M, R, S1, S2, S3, S4, S5, S6, X, ...) R(M(X,I,S1,S2,S3,S4,S5,S6), TC_MR_35_(I##1,M,R,S1,S2,S3,S4,S5,S6,__VA_ARGS__) ,S1,S2,S3,S4,S5,S6)

#endif /* TC_COMMON_MACROS_H */
