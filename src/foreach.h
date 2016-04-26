#ifndef FOREACH_H
#define FOREACH_H 1

#define GET_FE_MACRO(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,NAME,...) NAME 

#define A1_FE_1(WHAT, X) WHAT(X) 
#define A1_FE_2(WHAT, X, ...)  WHAT(X) A1_FE_1(WHAT, __VA_ARGS__)
#define A1_FE_3(WHAT, X, ...)  WHAT(X) A1_FE_2(WHAT, __VA_ARGS__)
#define A1_FE_4(WHAT, X, ...)  WHAT(X) A1_FE_3(WHAT, __VA_ARGS__)
#define A1_FE_5(WHAT, X, ...)  WHAT(X) A1_FE_4(WHAT, __VA_ARGS__)
#define A1_FE_6(WHAT, X, ...)  WHAT(X) A1_FE_5(WHAT, __VA_ARGS__)
#define A1_FE_7(WHAT, X, ...)  WHAT(X) A1_FE_6(WHAT, __VA_ARGS__)
#define A1_FE_8(WHAT, X, ...)  WHAT(X) A1_FE_7(WHAT, __VA_ARGS__)
#define A1_FE_9(WHAT, X, ...)  WHAT(X) A1_FE_8(WHAT, __VA_ARGS__)
#define A1_FE_10(WHAT, X, ...) WHAT(X) A1_FE_9(WHAT, __VA_ARGS__)
#define A1_FE_11(WHAT, X, ...) WHAT(X) A1_FE_10(WHAT, __VA_ARGS__)
#define A1_FE_12(WHAT, X, ...) WHAT(X) A1_FE_11(WHAT, __VA_ARGS__)

#define FOR_EACH_A1(action,...) \
  GET_FE_MACRO(__VA_ARGS__, \
   A1_FE_12, A1_FE_11,A1_FE_10,A1_FE_9, \
   A1_FE_8,  A1_FE_7, A1_FE_6, A1_FE_5, \
   A1_FE_4,  A1_FE_3, A1_FE_2, A1_FE_1,)(action,__VA_ARGS__)

#define A2_FE_1(WHAT,  V1, X) WHAT(V1,X) 
#define A2_FE_2(WHAT,  V1, X, ...)  WHAT(V1,X) A2_FE_1(WHAT, V1, __VA_ARGS__)
#define A2_FE_3(WHAT,  V1, X, ...)  WHAT(V1,X) A2_FE_2(WHAT, V1, __VA_ARGS__)
#define A2_FE_4(WHAT,  V1, X, ...)  WHAT(V1,X) A2_FE_3(WHAT, V1, __VA_ARGS__)
#define A2_FE_5(WHAT,  V1, X, ...)  WHAT(V1,X) A2_FE_4(WHAT, V1, __VA_ARGS__)
#define A2_FE_6(WHAT,  V1, X, ...)  WHAT(V1,X) A2_FE_5(WHAT, V1, __VA_ARGS__)
#define A2_FE_7(WHAT,  V1, X, ...)  WHAT(V1,X) A2_FE_6(WHAT, V1, __VA_ARGS__)
#define A2_FE_8(WHAT,  V1, X, ...)  WHAT(V1,X) A2_FE_7(WHAT, V1, __VA_ARGS__)
#define A2_FE_9(WHAT,  V1, X, ...)  WHAT(V1,X) A2_FE_8(WHAT, V1, __VA_ARGS__)
#define A2_FE_10(WHAT, V1, X, ...)  WHAT(V1,X) A2_FE_9(WHAT, V1, __VA_ARGS__)
#define A2_FE_11(WHAT, V1, X, ...)  WHAT(V1,X) A2_FE_10(WHAT,V1,  __VA_ARGS__)
#define A2_FE_12(WHAT, V1, X, ...)  WHAT(V1,X) A2_FE_11(WHAT,V1,  __VA_ARGS__)

#define FOR_EACH_A2(action,V1,...) \
  GET_FE_MACRO(__VA_ARGS__, \
   A2_FE_12, A2_FE_11,A2_FE_10,A2_FE_9, \
   A2_FE_8,  A2_FE_7, A2_FE_6, A2_FE_5, \
   A2_FE_4,  A2_FE_3, A2_FE_2, A2_FE_1,)(action,V1,__VA_ARGS__)

#define A3_FE_1(WHAT,  V1, V2, X) WHAT(V1,V2,X)
#define A3_FE_2(WHAT,  V1, V2, X,...)  WHAT(V1,V2,X) A3_FE_1(WHAT, V1, V2, __VA_ARGS__)
#define A3_FE_3(WHAT,  V1, V2, X,...)  WHAT(V1,V2,X) A3_FE_2(WHAT, V1, V2, __VA_ARGS__)
#define A3_FE_4(WHAT,  V1, V2, X,...)  WHAT(V1,V2,X) A3_FE_3(WHAT, V1, V2, __VA_ARGS__)
#define A3_FE_5(WHAT,  V1, V2, X,...)  WHAT(V1,V2,X) A3_FE_4(WHAT, V1, V2, __VA_ARGS__)
#define A3_FE_6(WHAT,  V1, V2, X,...)  WHAT(V1,V2,X) A3_FE_5(WHAT, V1, V2, __VA_ARGS__)
#define A3_FE_7(WHAT,  V1, V2, X,...)  WHAT(V1,V2,X) A3_FE_6(WHAT, V1, V2, __VA_ARGS__)
#define A3_FE_8(WHAT,  V1, V2, X,...)  WHAT(V1,V2,X) A3_FE_7(WHAT, V1, V2, __VA_ARGS__)
#define A3_FE_9(WHAT,  V1, V2, X,...)  WHAT(V1,V2,X) A3_FE_8(WHAT, V1, V2, __VA_ARGS__)
#define A3_FE_10(WHAT, V1, V2, X,...)  WHAT(V1,V2,X) A3_FE_9(WHAT, V1, V2, __VA_ARGS__)
#define A3_FE_11(WHAT, V1, V2, X,...)  WHAT(V1,V2,X) A3_FE_10(WHAT,V1, V2, __VA_ARGS__)
#define A3_FE_12(WHAT, V1, V2, X,...)  WHAT(V1,V2,X) A3_FE_11(WHAT,V1, V2, __VA_ARGS__)

#define FOR_EACH_A3(action,V1,V2,...) \
  GET_FE_MACRO(__VA_ARGS__, \
   A3_FE_12, A3_FE_11,A3_FE_10,A3_FE_9, \
   A3_FE_8,  A3_FE_7, A3_FE_6, A3_FE_5, \
   A3_FE_4,  A3_FE_3, A3_FE_2, A3_FE_1,)(action,V1,V2,__VA_ARGS__)

#endif /* FOREACH_H */
