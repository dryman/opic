/* This may look like nonsense, but it really is -*- mode: C -*-              */
/*                                                                            */
/* Except for parts copied from previous work and as explicitly stated below, */
/* the author and copyright holder for this work is                           */
/* (C) copyright  2010-2013, 2015 Jens Gustedt, INRIA, France                 */
/*                                                                            */
/* This file is free software; it is part of the P99 project.                 */
/* You can redistribute it and/or modify it under the terms of the QPL as     */
/* given in the file LICENSE. It is distributed without any warranty;         */
/* without even the implied warranty of merchantability or fitness for a      */
/* particular purpose.                                                        */
/*                                                                            */
/***********************************************
automatically generated, do not change manually.
***********************************************/


#ifndef P99_GENERATED_H
#define P99_GENERATED_H

/** @file
 ** @brief automatically generated macros to handle variadic macros.
 **
 ** You should probably never include this file directly but through
 ** other P99 header files that define macros that are of direct use.
 **/

/** @brief The version of the P99 collection indicated by the commit date.
 **
 ** This should appear as an RFC2822 style date as you encounter e.g in emails.
 ** If this doesn't contain a date but a bizarre `format' with $ signs
 ** you have a version that is directly taken from the git repostitory.
 **/
#define P99_VERSION_DATE "Sun Jan 31 22:35:36 2016 +0100"

/** @brief The version of the P99 collection indicated by a unique commit ID.
 **
 ** This should appear as a long string of hexadecimal digits.
 ** If this contains but a bizarre "format" with $ signs
 ** you have a version that is directly taken from the git repostitory.
 **/
#define P99_VERSION_ID "d83e6ac40e442ba427bb1273e4c2d9e88428f742"

#define P00_VERSION_DATE "Tue, 09 Jun 2015 08:28:18 +0200"
#define P00_VERSION_ID "054b2bab90f7a9ecdbe71b2fb71a52d37dd2da21"

/** @brief The maximal number of arguments the P99 macros can handle.
 **
 ** This limit applies also to the integer arithmetic that is
 ** performed by the macros in @ref preprocessor_arithmetic.
 **/
#define P99_MAX_NUMBER 158
#define P00_ARG(                                               \
 _1, _2, _3, _4, _5, _6, _7, _8,                               \
 _9, _10, _11, _12, _13, _14, _15, _16,                        \
 _17, _18, _19, _20, _21, _22, _23, _24,                       \
 _25, _26, _27, _28, _29, _30, _31, _32,                       \
 _33, _34, _35, _36, _37, _38, _39, _40,                       \
 _41, _42, _43, _44, _45, _46, _47, _48,                       \
 _49, _50, _51, _52, _53, _54, _55, _56,                       \
 _57, _58, _59, _60, _61, _62, _63, _64,                       \
 _65, _66, _67, _68, _69, _70, _71, _72,                       \
 _73, _74, _75, _76, _77, _78, _79, _80,                       \
 _81, _82, _83, _84, _85, _86, _87, _88,                       \
 _89, _90, _91, _92, _93, _94, _95, _96,                       \
 _97, _98, _99, _100, _101, _102, _103, _104,                  \
 _105, _106, _107, _108, _109, _110, _111, _112,               \
 _113, _114, _115, _116, _117, _118, _119, _120,               \
 _121, _122, _123, _124, _125, _126, _127, _128,               \
 _129, _130, _131, _132, _133, _134, _135, _136,               \
 _137, _138, _139, _140, _141, _142, _143, _144,               \
 _145, _146, _147, _148, _149, _150, _151, _152,               \
 _153, _154, _155, _156, _157, _158, _159,                     \
 ...) _159
#define P00_NARG_1(...) P00_ARG(__VA_ARGS__,  158, 157, 156, 155, 154, 153, 152, \
 151, 150, 149, 148, 147, 146, 145, 144,                                         \
 143, 142, 141, 140, 139, 138, 137, 136,                                         \
 135, 134, 133, 132, 131, 130, 129, 128,                                         \
 127, 126, 125, 124, 123, 122, 121, 120,                                         \
 119, 118, 117, 116, 115, 114, 113, 112,                                         \
 111, 110, 109, 108, 107, 106, 105, 104,                                         \
 103, 102, 101, 100, 99, 98, 97, 96,                                             \
 95, 94, 93, 92, 91, 90, 89, 88,                                                 \
 87, 86, 85, 84, 83, 82, 81, 80,                                                 \
 79, 78, 77, 76, 75, 74, 73, 72,                                                 \
 71, 70, 69, 68, 67, 66, 65, 64,                                                 \
 63, 62, 61, 60, 59, 58, 57, 56,                                                 \
 55, 54, 53, 52, 51, 50, 49, 48,                                                 \
 47, 46, 45, 44, 43, 42, 41, 40,                                                 \
 39, 38, 37, 36, 35, 34, 33, 32,                                                 \
 31, 30, 29, 28, 27, 26, 25, 24,                                                 \
 23, 22, 21, 20, 19, 18, 17, 16,                                                 \
 15, 14, 13, 12, 11, 10, 9, 8,                                                   \
 7, 6, 5, 4, 3, 2, 1, 0,)
#define P00_NARG_2(...) P00_ARG(__VA_ARGS__,  79, P00_INV(2), 78, P00_INV(2), 77, P00_INV(2), 76, \
 P00_INV(2), 75, P00_INV(2), 74, P00_INV(2), 73, P00_INV(2), 72,                                  \
 P00_INV(2), 71, P00_INV(2), 70, P00_INV(2), 69, P00_INV(2), 68,                                  \
 P00_INV(2), 67, P00_INV(2), 66, P00_INV(2), 65, P00_INV(2), 64,                                  \
 P00_INV(2), 63, P00_INV(2), 62, P00_INV(2), 61, P00_INV(2), 60,                                  \
 P00_INV(2), 59, P00_INV(2), 58, P00_INV(2), 57, P00_INV(2), 56,                                  \
 P00_INV(2), 55, P00_INV(2), 54, P00_INV(2), 53, P00_INV(2), 52,                                  \
 P00_INV(2), 51, P00_INV(2), 50, P00_INV(2), 49, P00_INV(2), 48,                                  \
 P00_INV(2), 47, P00_INV(2), 46, P00_INV(2), 45, P00_INV(2), 44,                                  \
 P00_INV(2), 43, P00_INV(2), 42, P00_INV(2), 41, P00_INV(2), 40,                                  \
 P00_INV(2), 39, P00_INV(2), 38, P00_INV(2), 37, P00_INV(2), 36,                                  \
 P00_INV(2), 35, P00_INV(2), 34, P00_INV(2), 33, P00_INV(2), 32,                                  \
 P00_INV(2), 31, P00_INV(2), 30, P00_INV(2), 29, P00_INV(2), 28,                                  \
 P00_INV(2), 27, P00_INV(2), 26, P00_INV(2), 25, P00_INV(2), 24,                                  \
 P00_INV(2), 23, P00_INV(2), 22, P00_INV(2), 21, P00_INV(2), 20,                                  \
 P00_INV(2), 19, P00_INV(2), 18, P00_INV(2), 17, P00_INV(2), 16,                                  \
 P00_INV(2), 15, P00_INV(2), 14, P00_INV(2), 13, P00_INV(2), 12,                                  \
 P00_INV(2), 11, P00_INV(2), 10, P00_INV(2), 9, P00_INV(2), 8,                                    \
 P00_INV(2), 7, P00_INV(2), 6, P00_INV(2), 5, P00_INV(2), 4,                                      \
 P00_INV(2), 3, P00_INV(2), 2, P00_INV(2), 1, P00_INV(2), 0,)
#define P00_NARG_3(...) P00_ARG(__VA_ARGS__,  P00_INV(3), P00_INV(3), 52, P00_INV(3), P00_INV(3), 51, P00_INV(3), \
 P00_INV(3), 50, P00_INV(3), P00_INV(3), 49, P00_INV(3), P00_INV(3), 48,                                          \
 P00_INV(3), P00_INV(3), 47, P00_INV(3), P00_INV(3), 46, P00_INV(3), P00_INV(3),                                  \
 45, P00_INV(3), P00_INV(3), 44, P00_INV(3), P00_INV(3), 43, P00_INV(3),                                          \
 P00_INV(3), 42, P00_INV(3), P00_INV(3), 41, P00_INV(3), P00_INV(3), 40,                                          \
 P00_INV(3), P00_INV(3), 39, P00_INV(3), P00_INV(3), 38, P00_INV(3), P00_INV(3),                                  \
 37, P00_INV(3), P00_INV(3), 36, P00_INV(3), P00_INV(3), 35, P00_INV(3),                                          \
 P00_INV(3), 34, P00_INV(3), P00_INV(3), 33, P00_INV(3), P00_INV(3), 32,                                          \
 P00_INV(3), P00_INV(3), 31, P00_INV(3), P00_INV(3), 30, P00_INV(3), P00_INV(3),                                  \
 29, P00_INV(3), P00_INV(3), 28, P00_INV(3), P00_INV(3), 27, P00_INV(3),                                          \
 P00_INV(3), 26, P00_INV(3), P00_INV(3), 25, P00_INV(3), P00_INV(3), 24,                                          \
 P00_INV(3), P00_INV(3), 23, P00_INV(3), P00_INV(3), 22, P00_INV(3), P00_INV(3),                                  \
 21, P00_INV(3), P00_INV(3), 20, P00_INV(3), P00_INV(3), 19, P00_INV(3),                                          \
 P00_INV(3), 18, P00_INV(3), P00_INV(3), 17, P00_INV(3), P00_INV(3), 16,                                          \
 P00_INV(3), P00_INV(3), 15, P00_INV(3), P00_INV(3), 14, P00_INV(3), P00_INV(3),                                  \
 13, P00_INV(3), P00_INV(3), 12, P00_INV(3), P00_INV(3), 11, P00_INV(3),                                          \
 P00_INV(3), 10, P00_INV(3), P00_INV(3), 9, P00_INV(3), P00_INV(3), 8,                                            \
 P00_INV(3), P00_INV(3), 7, P00_INV(3), P00_INV(3), 6, P00_INV(3), P00_INV(3),                                    \
 5, P00_INV(3), P00_INV(3), 4, P00_INV(3), P00_INV(3), 3, P00_INV(3),                                             \
 P00_INV(3), 2, P00_INV(3), P00_INV(3), 1, P00_INV(3), P00_INV(3), 0,)
#define P00_NARG_4(...) P00_ARG(__VA_ARGS__,  P00_INV(4), P00_INV(4), 39, P00_INV(4), P00_INV(4), P00_INV(4), 38, \
 P00_INV(4), P00_INV(4), P00_INV(4), 37, P00_INV(4), P00_INV(4), P00_INV(4), 36,                                  \
 P00_INV(4), P00_INV(4), P00_INV(4), 35, P00_INV(4), P00_INV(4), P00_INV(4), 34,                                  \
 P00_INV(4), P00_INV(4), P00_INV(4), 33, P00_INV(4), P00_INV(4), P00_INV(4), 32,                                  \
 P00_INV(4), P00_INV(4), P00_INV(4), 31, P00_INV(4), P00_INV(4), P00_INV(4), 30,                                  \
 P00_INV(4), P00_INV(4), P00_INV(4), 29, P00_INV(4), P00_INV(4), P00_INV(4), 28,                                  \
 P00_INV(4), P00_INV(4), P00_INV(4), 27, P00_INV(4), P00_INV(4), P00_INV(4), 26,                                  \
 P00_INV(4), P00_INV(4), P00_INV(4), 25, P00_INV(4), P00_INV(4), P00_INV(4), 24,                                  \
 P00_INV(4), P00_INV(4), P00_INV(4), 23, P00_INV(4), P00_INV(4), P00_INV(4), 22,                                  \
 P00_INV(4), P00_INV(4), P00_INV(4), 21, P00_INV(4), P00_INV(4), P00_INV(4), 20,                                  \
 P00_INV(4), P00_INV(4), P00_INV(4), 19, P00_INV(4), P00_INV(4), P00_INV(4), 18,                                  \
 P00_INV(4), P00_INV(4), P00_INV(4), 17, P00_INV(4), P00_INV(4), P00_INV(4), 16,                                  \
 P00_INV(4), P00_INV(4), P00_INV(4), 15, P00_INV(4), P00_INV(4), P00_INV(4), 14,                                  \
 P00_INV(4), P00_INV(4), P00_INV(4), 13, P00_INV(4), P00_INV(4), P00_INV(4), 12,                                  \
 P00_INV(4), P00_INV(4), P00_INV(4), 11, P00_INV(4), P00_INV(4), P00_INV(4), 10,                                  \
 P00_INV(4), P00_INV(4), P00_INV(4), 9, P00_INV(4), P00_INV(4), P00_INV(4), 8,                                    \
 P00_INV(4), P00_INV(4), P00_INV(4), 7, P00_INV(4), P00_INV(4), P00_INV(4), 6,                                    \
 P00_INV(4), P00_INV(4), P00_INV(4), 5, P00_INV(4), P00_INV(4), P00_INV(4), 4,                                    \
 P00_INV(4), P00_INV(4), P00_INV(4), 3, P00_INV(4), P00_INV(4), P00_INV(4), 2,                                    \
 P00_INV(4), P00_INV(4), P00_INV(4), 1, P00_INV(4), P00_INV(4), P00_INV(4), 0,)
/** @ingroup basic_list_operations                                                 */
/** @brief Determine of the argument list has a comma, i.e at least two arguments. */
#define P99_HAS_COMMA(...) P00_ARG(__VA_ARGS__,                \
 1, 1, 1, 1, 1, 1, 1,                                          \
 1, 1, 1, 1, 1, 1, 1, 1,                                       \
 1, 1, 1, 1, 1, 1, 1, 1,                                       \
 1, 1, 1, 1, 1, 1, 1, 1,                                       \
 1, 1, 1, 1, 1, 1, 1, 1,                                       \
 1, 1, 1, 1, 1, 1, 1, 1,                                       \
 1, 1, 1, 1, 1, 1, 1, 1,                                       \
 1, 1, 1, 1, 1, 1, 1, 1,                                       \
 1, 1, 1, 1, 1, 1, 1, 1,                                       \
 1, 1, 1, 1, 1, 1, 1, 1,                                       \
 1, 1, 1, 1, 1, 1, 1, 1,                                       \
 1, 1, 1, 1, 1, 1, 1, 1,                                       \
 1, 1, 1, 1, 1, 1, 1, 1,                                       \
 1, 1, 1, 1, 1, 1, 1, 1,                                       \
 1, 1, 1, 1, 1, 1, 1, 1,                                       \
 1, 1, 1, 1, 1, 1, 1, 1,                                       \
 1, 1, 1, 1, 1, 1, 1, 1,                                       \
 1, 1, 1, 1, 1, 1, 1, 1,                                       \
 1, 1, 1, 1, 1, 1, 1, 1,                                       \
 1, 1, 1, 1, 1, 1, 0, 0)
#define P00_SKP2(_0, ...) P00_SKP1(__VA_ARGS__)
#define P00_SKP3(_0, ...) P00_SKP2(__VA_ARGS__)
#define P00_SKP4(_0, ...) P00_SKP3(__VA_ARGS__)
#define P00_SKP5(_0, ...) P00_SKP4(__VA_ARGS__)
#define P00_SKP6(_0, ...) P00_SKP5(__VA_ARGS__)
#define P00_SKP7(_0, ...) P00_SKP6(__VA_ARGS__)
#define P00_SKP8(_0, ...) P00_SKP7(__VA_ARGS__)
#define P00_SKP9(_0, ...) P00_SKP8(__VA_ARGS__)
#define P00_SKP10(_0, ...) P00_SKP9(__VA_ARGS__)
#define P00_SKP11(_0, ...) P00_SKP10(__VA_ARGS__)
#define P00_SKP12(_0, ...) P00_SKP11(__VA_ARGS__)
#define P00_SKP13(_0, ...) P00_SKP12(__VA_ARGS__)
#define P00_SKP14(_0, ...) P00_SKP13(__VA_ARGS__)
#define P00_SKP15(_0, ...) P00_SKP14(__VA_ARGS__)
#define P00_SKP16(_0, ...) P00_SKP15(__VA_ARGS__)
#define P00_SKP17(_0, ...) P00_SKP16(__VA_ARGS__)
#define P00_SKP18(_0, ...) P00_SKP17(__VA_ARGS__)
#define P00_SKP19(_0, ...) P00_SKP18(__VA_ARGS__)
#define P00_SKP20(_0, ...) P00_SKP19(__VA_ARGS__)
#define P00_SKP21(_0, ...) P00_SKP20(__VA_ARGS__)
#define P00_SKP22(_0, ...) P00_SKP21(__VA_ARGS__)
#define P00_SKP23(_0, ...) P00_SKP22(__VA_ARGS__)
#define P00_SKP24(_0, ...) P00_SKP23(__VA_ARGS__)
#define P00_SKP25(_0, ...) P00_SKP24(__VA_ARGS__)
#define P00_SKP26(_0, ...) P00_SKP25(__VA_ARGS__)
#define P00_SKP27(_0, ...) P00_SKP26(__VA_ARGS__)
#define P00_SKP28(_0, ...) P00_SKP27(__VA_ARGS__)
#define P00_SKP29(_0, ...) P00_SKP28(__VA_ARGS__)
#define P00_SKP30(_0, ...) P00_SKP29(__VA_ARGS__)
#define P00_SKP31(_0, ...) P00_SKP30(__VA_ARGS__)
#define P00_SKP32(_0, ...) P00_SKP31(__VA_ARGS__)
#define P00_SKP33(_0, ...) P00_SKP32(__VA_ARGS__)
#define P00_SKP34(_0, ...) P00_SKP33(__VA_ARGS__)
#define P00_SKP35(_0, ...) P00_SKP34(__VA_ARGS__)
#define P00_SKP36(_0, ...) P00_SKP35(__VA_ARGS__)
#define P00_SKP37(_0, ...) P00_SKP36(__VA_ARGS__)
#define P00_SKP38(_0, ...) P00_SKP37(__VA_ARGS__)
#define P00_SKP39(_0, ...) P00_SKP38(__VA_ARGS__)
#define P00_SKP40(_0, ...) P00_SKP39(__VA_ARGS__)
#define P00_SKP41(_0, ...) P00_SKP40(__VA_ARGS__)
#define P00_SKP42(_0, ...) P00_SKP41(__VA_ARGS__)
#define P00_SKP43(_0, ...) P00_SKP42(__VA_ARGS__)
#define P00_SKP44(_0, ...) P00_SKP43(__VA_ARGS__)
#define P00_SKP45(_0, ...) P00_SKP44(__VA_ARGS__)
#define P00_SKP46(_0, ...) P00_SKP45(__VA_ARGS__)
#define P00_SKP47(_0, ...) P00_SKP46(__VA_ARGS__)
#define P00_SKP48(_0, ...) P00_SKP47(__VA_ARGS__)
#define P00_SKP49(_0, ...) P00_SKP48(__VA_ARGS__)
#define P00_SKP50(_0, ...) P00_SKP49(__VA_ARGS__)
#define P00_SKP51(_0, ...) P00_SKP50(__VA_ARGS__)
#define P00_SKP52(_0, ...) P00_SKP51(__VA_ARGS__)
#define P00_SKP53(_0, ...) P00_SKP52(__VA_ARGS__)
#define P00_SKP54(_0, ...) P00_SKP53(__VA_ARGS__)
#define P00_SKP55(_0, ...) P00_SKP54(__VA_ARGS__)
#define P00_SKP56(_0, ...) P00_SKP55(__VA_ARGS__)
#define P00_SKP57(_0, ...) P00_SKP56(__VA_ARGS__)
#define P00_SKP58(_0, ...) P00_SKP57(__VA_ARGS__)
#define P00_SKP59(_0, ...) P00_SKP58(__VA_ARGS__)
#define P00_SKP60(_0, ...) P00_SKP59(__VA_ARGS__)
#define P00_SKP61(_0, ...) P00_SKP60(__VA_ARGS__)
#define P00_SKP62(_0, ...) P00_SKP61(__VA_ARGS__)
#define P00_SKP63(_0, ...) P00_SKP62(__VA_ARGS__)
#define P00_SKP64(_0, ...) P00_SKP63(__VA_ARGS__)
#define P00_SKP65(_0, ...) P00_SKP64(__VA_ARGS__)
#define P00_SKP66(_0, ...) P00_SKP65(__VA_ARGS__)
#define P00_SKP67(_0, ...) P00_SKP66(__VA_ARGS__)
#define P00_SKP68(_0, ...) P00_SKP67(__VA_ARGS__)
#define P00_SKP69(_0, ...) P00_SKP68(__VA_ARGS__)
#define P00_SKP70(_0, ...) P00_SKP69(__VA_ARGS__)
#define P00_SKP71(_0, ...) P00_SKP70(__VA_ARGS__)
#define P00_SKP72(_0, ...) P00_SKP71(__VA_ARGS__)
#define P00_SKP73(_0, ...) P00_SKP72(__VA_ARGS__)
#define P00_SKP74(_0, ...) P00_SKP73(__VA_ARGS__)
#define P00_SKP75(_0, ...) P00_SKP74(__VA_ARGS__)
#define P00_SKP76(_0, ...) P00_SKP75(__VA_ARGS__)
#define P00_SKP77(_0, ...) P00_SKP76(__VA_ARGS__)
#define P00_SKP78(_0, ...) P00_SKP77(__VA_ARGS__)
#define P00_SKP79(_0, ...) P00_SKP78(__VA_ARGS__)
#define P00_SKP80(_0, ...) P00_SKP79(__VA_ARGS__)
#define P00_SKP81(_0, ...) P00_SKP80(__VA_ARGS__)
#define P00_SKP82(_0, ...) P00_SKP81(__VA_ARGS__)
#define P00_SKP83(_0, ...) P00_SKP82(__VA_ARGS__)
#define P00_SKP84(_0, ...) P00_SKP83(__VA_ARGS__)
#define P00_SKP85(_0, ...) P00_SKP84(__VA_ARGS__)
#define P00_SKP86(_0, ...) P00_SKP85(__VA_ARGS__)
#define P00_SKP87(_0, ...) P00_SKP86(__VA_ARGS__)
#define P00_SKP88(_0, ...) P00_SKP87(__VA_ARGS__)
#define P00_SKP89(_0, ...) P00_SKP88(__VA_ARGS__)
#define P00_SKP90(_0, ...) P00_SKP89(__VA_ARGS__)
#define P00_SKP91(_0, ...) P00_SKP90(__VA_ARGS__)
#define P00_SKP92(_0, ...) P00_SKP91(__VA_ARGS__)
#define P00_SKP93(_0, ...) P00_SKP92(__VA_ARGS__)
#define P00_SKP94(_0, ...) P00_SKP93(__VA_ARGS__)
#define P00_SKP95(_0, ...) P00_SKP94(__VA_ARGS__)
#define P00_SKP96(_0, ...) P00_SKP95(__VA_ARGS__)
#define P00_SKP97(_0, ...) P00_SKP96(__VA_ARGS__)
#define P00_SKP98(_0, ...) P00_SKP97(__VA_ARGS__)
#define P00_SKP99(_0, ...) P00_SKP98(__VA_ARGS__)
#define P00_SKP100(_0, ...) P00_SKP99(__VA_ARGS__)
#define P00_SKP101(_0, ...) P00_SKP100(__VA_ARGS__)
#define P00_SKP102(_0, ...) P00_SKP101(__VA_ARGS__)
#define P00_SKP103(_0, ...) P00_SKP102(__VA_ARGS__)
#define P00_SKP104(_0, ...) P00_SKP103(__VA_ARGS__)
#define P00_SKP105(_0, ...) P00_SKP104(__VA_ARGS__)
#define P00_SKP106(_0, ...) P00_SKP105(__VA_ARGS__)
#define P00_SKP107(_0, ...) P00_SKP106(__VA_ARGS__)
#define P00_SKP108(_0, ...) P00_SKP107(__VA_ARGS__)
#define P00_SKP109(_0, ...) P00_SKP108(__VA_ARGS__)
#define P00_SKP110(_0, ...) P00_SKP109(__VA_ARGS__)
#define P00_SKP111(_0, ...) P00_SKP110(__VA_ARGS__)
#define P00_SKP112(_0, ...) P00_SKP111(__VA_ARGS__)
#define P00_SKP113(_0, ...) P00_SKP112(__VA_ARGS__)
#define P00_SKP114(_0, ...) P00_SKP113(__VA_ARGS__)
#define P00_SKP115(_0, ...) P00_SKP114(__VA_ARGS__)
#define P00_SKP116(_0, ...) P00_SKP115(__VA_ARGS__)
#define P00_SKP117(_0, ...) P00_SKP116(__VA_ARGS__)
#define P00_SKP118(_0, ...) P00_SKP117(__VA_ARGS__)
#define P00_SKP119(_0, ...) P00_SKP118(__VA_ARGS__)
#define P00_SKP120(_0, ...) P00_SKP119(__VA_ARGS__)
#define P00_SKP121(_0, ...) P00_SKP120(__VA_ARGS__)
#define P00_SKP122(_0, ...) P00_SKP121(__VA_ARGS__)
#define P00_SKP123(_0, ...) P00_SKP122(__VA_ARGS__)
#define P00_SKP124(_0, ...) P00_SKP123(__VA_ARGS__)
#define P00_SKP125(_0, ...) P00_SKP124(__VA_ARGS__)
#define P00_SKP126(_0, ...) P00_SKP125(__VA_ARGS__)
#define P00_SKP127(_0, ...) P00_SKP126(__VA_ARGS__)
#define P00_SKP128(_0, ...) P00_SKP127(__VA_ARGS__)
#define P00_SKP129(_0, ...) P00_SKP128(__VA_ARGS__)
#define P00_SKP130(_0, ...) P00_SKP129(__VA_ARGS__)
#define P00_SKP131(_0, ...) P00_SKP130(__VA_ARGS__)
#define P00_SKP132(_0, ...) P00_SKP131(__VA_ARGS__)
#define P00_SKP133(_0, ...) P00_SKP132(__VA_ARGS__)
#define P00_SKP134(_0, ...) P00_SKP133(__VA_ARGS__)
#define P00_SKP135(_0, ...) P00_SKP134(__VA_ARGS__)
#define P00_SKP136(_0, ...) P00_SKP135(__VA_ARGS__)
#define P00_SKP137(_0, ...) P00_SKP136(__VA_ARGS__)
#define P00_SKP138(_0, ...) P00_SKP137(__VA_ARGS__)
#define P00_SKP139(_0, ...) P00_SKP138(__VA_ARGS__)
#define P00_SKP140(_0, ...) P00_SKP139(__VA_ARGS__)
#define P00_SKP141(_0, ...) P00_SKP140(__VA_ARGS__)
#define P00_SKP142(_0, ...) P00_SKP141(__VA_ARGS__)
#define P00_SKP143(_0, ...) P00_SKP142(__VA_ARGS__)
#define P00_SKP144(_0, ...) P00_SKP143(__VA_ARGS__)
#define P00_SKP145(_0, ...) P00_SKP144(__VA_ARGS__)
#define P00_SKP146(_0, ...) P00_SKP145(__VA_ARGS__)
#define P00_SKP147(_0, ...) P00_SKP146(__VA_ARGS__)
#define P00_SKP148(_0, ...) P00_SKP147(__VA_ARGS__)
#define P00_SKP149(_0, ...) P00_SKP148(__VA_ARGS__)
#define P00_SKP150(_0, ...) P00_SKP149(__VA_ARGS__)
#define P00_SKP151(_0, ...) P00_SKP150(__VA_ARGS__)
#define P00_SKP152(_0, ...) P00_SKP151(__VA_ARGS__)
#define P00_SKP153(_0, ...) P00_SKP152(__VA_ARGS__)
#define P00_SKP154(_0, ...) P00_SKP153(__VA_ARGS__)
#define P00_SKP155(_0, ...) P00_SKP154(__VA_ARGS__)
#define P00_SKP156(_0, ...) P00_SKP155(__VA_ARGS__)
#define P00_SKP157(_0, ...) P00_SKP156(__VA_ARGS__)
#define P00_SKP158(_0, ...) P00_SKP157(__VA_ARGS__)
#define P00_PRE2(_0, ...) _0, P00_PRE1(__VA_ARGS__)
#define P00_PRE3(_0, ...) _0, P00_PRE2(__VA_ARGS__)
#define P00_PRE4(_0, ...) _0, P00_PRE3(__VA_ARGS__)
#define P00_PRE5(_0, ...) _0, P00_PRE4(__VA_ARGS__)
#define P00_PRE6(_0, ...) _0, P00_PRE5(__VA_ARGS__)
#define P00_PRE7(_0, ...) _0, P00_PRE6(__VA_ARGS__)
#define P00_PRE8(_0, ...) _0, P00_PRE7(__VA_ARGS__)
#define P00_PRE9(_0, ...) _0, P00_PRE8(__VA_ARGS__)
#define P00_PRE10(_0, ...) _0, P00_PRE9(__VA_ARGS__)
#define P00_PRE11(_0, ...) _0, P00_PRE10(__VA_ARGS__)
#define P00_PRE12(_0, ...) _0, P00_PRE11(__VA_ARGS__)
#define P00_PRE13(_0, ...) _0, P00_PRE12(__VA_ARGS__)
#define P00_PRE14(_0, ...) _0, P00_PRE13(__VA_ARGS__)
#define P00_PRE15(_0, ...) _0, P00_PRE14(__VA_ARGS__)
#define P00_PRE16(_0, ...) _0, P00_PRE15(__VA_ARGS__)
#define P00_PRE17(_0, ...) _0, P00_PRE16(__VA_ARGS__)
#define P00_PRE18(_0, ...) _0, P00_PRE17(__VA_ARGS__)
#define P00_PRE19(_0, ...) _0, P00_PRE18(__VA_ARGS__)
#define P00_PRE20(_0, ...) _0, P00_PRE19(__VA_ARGS__)
#define P00_PRE21(_0, ...) _0, P00_PRE20(__VA_ARGS__)
#define P00_PRE22(_0, ...) _0, P00_PRE21(__VA_ARGS__)
#define P00_PRE23(_0, ...) _0, P00_PRE22(__VA_ARGS__)
#define P00_PRE24(_0, ...) _0, P00_PRE23(__VA_ARGS__)
#define P00_PRE25(_0, ...) _0, P00_PRE24(__VA_ARGS__)
#define P00_PRE26(_0, ...) _0, P00_PRE25(__VA_ARGS__)
#define P00_PRE27(_0, ...) _0, P00_PRE26(__VA_ARGS__)
#define P00_PRE28(_0, ...) _0, P00_PRE27(__VA_ARGS__)
#define P00_PRE29(_0, ...) _0, P00_PRE28(__VA_ARGS__)
#define P00_PRE30(_0, ...) _0, P00_PRE29(__VA_ARGS__)
#define P00_PRE31(_0, ...) _0, P00_PRE30(__VA_ARGS__)
#define P00_PRE32(_0, ...) _0, P00_PRE31(__VA_ARGS__)
#define P00_PRE33(_0, ...) _0, P00_PRE32(__VA_ARGS__)
#define P00_PRE34(_0, ...) _0, P00_PRE33(__VA_ARGS__)
#define P00_PRE35(_0, ...) _0, P00_PRE34(__VA_ARGS__)
#define P00_PRE36(_0, ...) _0, P00_PRE35(__VA_ARGS__)
#define P00_PRE37(_0, ...) _0, P00_PRE36(__VA_ARGS__)
#define P00_PRE38(_0, ...) _0, P00_PRE37(__VA_ARGS__)
#define P00_PRE39(_0, ...) _0, P00_PRE38(__VA_ARGS__)
#define P00_PRE40(_0, ...) _0, P00_PRE39(__VA_ARGS__)
#define P00_PRE41(_0, ...) _0, P00_PRE40(__VA_ARGS__)
#define P00_PRE42(_0, ...) _0, P00_PRE41(__VA_ARGS__)
#define P00_PRE43(_0, ...) _0, P00_PRE42(__VA_ARGS__)
#define P00_PRE44(_0, ...) _0, P00_PRE43(__VA_ARGS__)
#define P00_PRE45(_0, ...) _0, P00_PRE44(__VA_ARGS__)
#define P00_PRE46(_0, ...) _0, P00_PRE45(__VA_ARGS__)
#define P00_PRE47(_0, ...) _0, P00_PRE46(__VA_ARGS__)
#define P00_PRE48(_0, ...) _0, P00_PRE47(__VA_ARGS__)
#define P00_PRE49(_0, ...) _0, P00_PRE48(__VA_ARGS__)
#define P00_PRE50(_0, ...) _0, P00_PRE49(__VA_ARGS__)
#define P00_PRE51(_0, ...) _0, P00_PRE50(__VA_ARGS__)
#define P00_PRE52(_0, ...) _0, P00_PRE51(__VA_ARGS__)
#define P00_PRE53(_0, ...) _0, P00_PRE52(__VA_ARGS__)
#define P00_PRE54(_0, ...) _0, P00_PRE53(__VA_ARGS__)
#define P00_PRE55(_0, ...) _0, P00_PRE54(__VA_ARGS__)
#define P00_PRE56(_0, ...) _0, P00_PRE55(__VA_ARGS__)
#define P00_PRE57(_0, ...) _0, P00_PRE56(__VA_ARGS__)
#define P00_PRE58(_0, ...) _0, P00_PRE57(__VA_ARGS__)
#define P00_PRE59(_0, ...) _0, P00_PRE58(__VA_ARGS__)
#define P00_PRE60(_0, ...) _0, P00_PRE59(__VA_ARGS__)
#define P00_PRE61(_0, ...) _0, P00_PRE60(__VA_ARGS__)
#define P00_PRE62(_0, ...) _0, P00_PRE61(__VA_ARGS__)
#define P00_PRE63(_0, ...) _0, P00_PRE62(__VA_ARGS__)
#define P00_PRE64(_0, ...) _0, P00_PRE63(__VA_ARGS__)
#define P00_PRE65(_0, ...) _0, P00_PRE64(__VA_ARGS__)
#define P00_PRE66(_0, ...) _0, P00_PRE65(__VA_ARGS__)
#define P00_PRE67(_0, ...) _0, P00_PRE66(__VA_ARGS__)
#define P00_PRE68(_0, ...) _0, P00_PRE67(__VA_ARGS__)
#define P00_PRE69(_0, ...) _0, P00_PRE68(__VA_ARGS__)
#define P00_PRE70(_0, ...) _0, P00_PRE69(__VA_ARGS__)
#define P00_PRE71(_0, ...) _0, P00_PRE70(__VA_ARGS__)
#define P00_PRE72(_0, ...) _0, P00_PRE71(__VA_ARGS__)
#define P00_PRE73(_0, ...) _0, P00_PRE72(__VA_ARGS__)
#define P00_PRE74(_0, ...) _0, P00_PRE73(__VA_ARGS__)
#define P00_PRE75(_0, ...) _0, P00_PRE74(__VA_ARGS__)
#define P00_PRE76(_0, ...) _0, P00_PRE75(__VA_ARGS__)
#define P00_PRE77(_0, ...) _0, P00_PRE76(__VA_ARGS__)
#define P00_PRE78(_0, ...) _0, P00_PRE77(__VA_ARGS__)
#define P00_PRE79(_0, ...) _0, P00_PRE78(__VA_ARGS__)
#define P00_PRE80(_0, ...) _0, P00_PRE79(__VA_ARGS__)
#define P00_PRE81(_0, ...) _0, P00_PRE80(__VA_ARGS__)
#define P00_PRE82(_0, ...) _0, P00_PRE81(__VA_ARGS__)
#define P00_PRE83(_0, ...) _0, P00_PRE82(__VA_ARGS__)
#define P00_PRE84(_0, ...) _0, P00_PRE83(__VA_ARGS__)
#define P00_PRE85(_0, ...) _0, P00_PRE84(__VA_ARGS__)
#define P00_PRE86(_0, ...) _0, P00_PRE85(__VA_ARGS__)
#define P00_PRE87(_0, ...) _0, P00_PRE86(__VA_ARGS__)
#define P00_PRE88(_0, ...) _0, P00_PRE87(__VA_ARGS__)
#define P00_PRE89(_0, ...) _0, P00_PRE88(__VA_ARGS__)
#define P00_PRE90(_0, ...) _0, P00_PRE89(__VA_ARGS__)
#define P00_PRE91(_0, ...) _0, P00_PRE90(__VA_ARGS__)
#define P00_PRE92(_0, ...) _0, P00_PRE91(__VA_ARGS__)
#define P00_PRE93(_0, ...) _0, P00_PRE92(__VA_ARGS__)
#define P00_PRE94(_0, ...) _0, P00_PRE93(__VA_ARGS__)
#define P00_PRE95(_0, ...) _0, P00_PRE94(__VA_ARGS__)
#define P00_PRE96(_0, ...) _0, P00_PRE95(__VA_ARGS__)
#define P00_PRE97(_0, ...) _0, P00_PRE96(__VA_ARGS__)
#define P00_PRE98(_0, ...) _0, P00_PRE97(__VA_ARGS__)
#define P00_PRE99(_0, ...) _0, P00_PRE98(__VA_ARGS__)
#define P00_PRE100(_0, ...) _0, P00_PRE99(__VA_ARGS__)
#define P00_PRE101(_0, ...) _0, P00_PRE100(__VA_ARGS__)
#define P00_PRE102(_0, ...) _0, P00_PRE101(__VA_ARGS__)
#define P00_PRE103(_0, ...) _0, P00_PRE102(__VA_ARGS__)
#define P00_PRE104(_0, ...) _0, P00_PRE103(__VA_ARGS__)
#define P00_PRE105(_0, ...) _0, P00_PRE104(__VA_ARGS__)
#define P00_PRE106(_0, ...) _0, P00_PRE105(__VA_ARGS__)
#define P00_PRE107(_0, ...) _0, P00_PRE106(__VA_ARGS__)
#define P00_PRE108(_0, ...) _0, P00_PRE107(__VA_ARGS__)
#define P00_PRE109(_0, ...) _0, P00_PRE108(__VA_ARGS__)
#define P00_PRE110(_0, ...) _0, P00_PRE109(__VA_ARGS__)
#define P00_PRE111(_0, ...) _0, P00_PRE110(__VA_ARGS__)
#define P00_PRE112(_0, ...) _0, P00_PRE111(__VA_ARGS__)
#define P00_PRE113(_0, ...) _0, P00_PRE112(__VA_ARGS__)
#define P00_PRE114(_0, ...) _0, P00_PRE113(__VA_ARGS__)
#define P00_PRE115(_0, ...) _0, P00_PRE114(__VA_ARGS__)
#define P00_PRE116(_0, ...) _0, P00_PRE115(__VA_ARGS__)
#define P00_PRE117(_0, ...) _0, P00_PRE116(__VA_ARGS__)
#define P00_PRE118(_0, ...) _0, P00_PRE117(__VA_ARGS__)
#define P00_PRE119(_0, ...) _0, P00_PRE118(__VA_ARGS__)
#define P00_PRE120(_0, ...) _0, P00_PRE119(__VA_ARGS__)
#define P00_PRE121(_0, ...) _0, P00_PRE120(__VA_ARGS__)
#define P00_PRE122(_0, ...) _0, P00_PRE121(__VA_ARGS__)
#define P00_PRE123(_0, ...) _0, P00_PRE122(__VA_ARGS__)
#define P00_PRE124(_0, ...) _0, P00_PRE123(__VA_ARGS__)
#define P00_PRE125(_0, ...) _0, P00_PRE124(__VA_ARGS__)
#define P00_PRE126(_0, ...) _0, P00_PRE125(__VA_ARGS__)
#define P00_PRE127(_0, ...) _0, P00_PRE126(__VA_ARGS__)
#define P00_PRE128(_0, ...) _0, P00_PRE127(__VA_ARGS__)
#define P00_PRE129(_0, ...) _0, P00_PRE128(__VA_ARGS__)
#define P00_PRE130(_0, ...) _0, P00_PRE129(__VA_ARGS__)
#define P00_PRE131(_0, ...) _0, P00_PRE130(__VA_ARGS__)
#define P00_PRE132(_0, ...) _0, P00_PRE131(__VA_ARGS__)
#define P00_PRE133(_0, ...) _0, P00_PRE132(__VA_ARGS__)
#define P00_PRE134(_0, ...) _0, P00_PRE133(__VA_ARGS__)
#define P00_PRE135(_0, ...) _0, P00_PRE134(__VA_ARGS__)
#define P00_PRE136(_0, ...) _0, P00_PRE135(__VA_ARGS__)
#define P00_PRE137(_0, ...) _0, P00_PRE136(__VA_ARGS__)
#define P00_PRE138(_0, ...) _0, P00_PRE137(__VA_ARGS__)
#define P00_PRE139(_0, ...) _0, P00_PRE138(__VA_ARGS__)
#define P00_PRE140(_0, ...) _0, P00_PRE139(__VA_ARGS__)
#define P00_PRE141(_0, ...) _0, P00_PRE140(__VA_ARGS__)
#define P00_PRE142(_0, ...) _0, P00_PRE141(__VA_ARGS__)
#define P00_PRE143(_0, ...) _0, P00_PRE142(__VA_ARGS__)
#define P00_PRE144(_0, ...) _0, P00_PRE143(__VA_ARGS__)
#define P00_PRE145(_0, ...) _0, P00_PRE144(__VA_ARGS__)
#define P00_PRE146(_0, ...) _0, P00_PRE145(__VA_ARGS__)
#define P00_PRE147(_0, ...) _0, P00_PRE146(__VA_ARGS__)
#define P00_PRE148(_0, ...) _0, P00_PRE147(__VA_ARGS__)
#define P00_PRE149(_0, ...) _0, P00_PRE148(__VA_ARGS__)
#define P00_PRE150(_0, ...) _0, P00_PRE149(__VA_ARGS__)
#define P00_PRE151(_0, ...) _0, P00_PRE150(__VA_ARGS__)
#define P00_PRE152(_0, ...) _0, P00_PRE151(__VA_ARGS__)
#define P00_PRE153(_0, ...) _0, P00_PRE152(__VA_ARGS__)
#define P00_PRE154(_0, ...) _0, P00_PRE153(__VA_ARGS__)
#define P00_PRE155(_0, ...) _0, P00_PRE154(__VA_ARGS__)
#define P00_PRE156(_0, ...) _0, P00_PRE155(__VA_ARGS__)
#define P00_PRE157(_0, ...) _0, P00_PRE156(__VA_ARGS__)
#define P00_PRE158(_0, ...) _0, P00_PRE157(__VA_ARGS__)
#define P00_ASCENDING()                                        \
 0, 1, 2, 3, 4, 5, 6, 7,                                       \
 8, 9, 10, 11, 12, 13, 14, 15,                                 \
 16, 17, 18, 19, 20, 21, 22, 23,                               \
 24, 25, 26, 27, 28, 29, 30, 31,                               \
 32, 33, 34, 35, 36, 37, 38, 39,                               \
 40, 41, 42, 43, 44, 45, 46, 47,                               \
 48, 49, 50, 51, 52, 53, 54, 55,                               \
 56, 57, 58, 59, 60, 61, 62, 63,                               \
 64, 65, 66, 67, 68, 69, 70, 71,                               \
 72, 73, 74, 75, 76, 77, 78, 79,                               \
 80, 81, 82, 83, 84, 85, 86, 87,                               \
 88, 89, 90, 91, 92, 93, 94, 95,                               \
 96, 97, 98, 99, 100, 101, 102, 103,                           \
 104, 105, 106, 107, 108, 109, 110, 111,                       \
 112, 113, 114, 115, 116, 117, 118, 119,                       \
 120, 121, 122, 123, 124, 125, 126, 127,                       \
 128, 129, 130, 131, 132, 133, 134, 135,                       \
 136, 137, 138, 139, 140, 141, 142, 143,                       \
 144, 145, 146, 147, 148, 149, 150, 151,                       \
 152, 153, 154, 155, 156, 157, 158,
#define P00_DESCENDING()  158, 157, 156, 155, 154, 153,        \
 152, 151, 150, 149, 148, 147, 146, 145,                       \
 144, 143, 142, 141, 140, 139, 138, 137,                       \
 136, 135, 134, 133, 132, 131, 130, 129,                       \
 128, 127, 126, 125, 124, 123, 122, 121,                       \
 120, 119, 118, 117, 116, 115, 114, 113,                       \
 112, 111, 110, 109, 108, 107, 106, 105,                       \
 104, 103, 102, 101, 100, 99, 98, 97,                          \
 96, 95, 94, 93, 92, 91, 90, 89,                               \
 88, 87, 86, 85, 84, 83, 82, 81,                               \
 80, 79, 78, 77, 76, 75, 74, 73,                               \
 72, 71, 70, 69, 68, 67, 66, 65,                               \
 64, 63, 62, 61, 60, 59, 58, 57,                               \
 56, 55, 54, 53, 52, 51, 50, 49,                               \
 48, 47, 46, 45, 44, 43, 42, 41,                               \
 40, 39, 38, 37, 36, 35, 34, 33,                               \
 32, 31, 30, 29, 28, 27, 26, 25,                               \
 24, 23, 22, 21, 20, 19, 18, 17,                               \
 16, 15, 14, 13, 12, 11, 10, 9,                                \
 8, 7, 6, 5, 4, 3, 2, 1,                                       \
 0,
#define P00_ALL_ZEROES()                                       \
 0, 0, 0, 0, 0, 0, 0, 0,                                       \
 0, 0, 0, 0, 0, 0, 0, 0,                                       \
 0, 0, 0, 0, 0, 0, 0, 0,                                       \
 0, 0, 0, 0, 0, 0, 0, 0,                                       \
 0, 0, 0, 0, 0, 0, 0, 0,                                       \
 0, 0, 0, 0, 0, 0, 0, 0,                                       \
 0, 0, 0, 0, 0, 0, 0, 0,                                       \
 0, 0, 0, 0, 0, 0, 0, 0,                                       \
 0, 0, 0, 0, 0, 0, 0, 0,                                       \
 0, 0, 0, 0, 0, 0, 0, 0,                                       \
 0, 0, 0, 0, 0, 0, 0, 0,                                       \
 0, 0, 0, 0, 0, 0, 0, 0,                                       \
 0, 0, 0, 0, 0, 0, 0, 0,                                       \
 0, 0, 0, 0, 0, 0, 0, 0,                                       \
 0, 0, 0, 0, 0, 0, 0, 0,                                       \
 0, 0, 0, 0, 0, 0, 0, 0,                                       \
 0, 0, 0, 0, 0, 0, 0, 0,                                       \
 0, 0, 0, 0, 0, 0, 0, 0,                                       \
 0, 0, 0, 0, 0, 0, 0, 0,                                       \
 0, 0, 0, 0, 0, 0, 0,
#define P00_ALL_ONES()                                         \
 1, 1, 1, 1, 1, 1, 1, 1,                                       \
 1, 1, 1, 1, 1, 1, 1, 1,                                       \
 1, 1, 1, 1, 1, 1, 1, 1,                                       \
 1, 1, 1, 1, 1, 1, 1, 1,                                       \
 1, 1, 1, 1, 1, 1, 1, 1,                                       \
 1, 1, 1, 1, 1, 1, 1, 1,                                       \
 1, 1, 1, 1, 1, 1, 1, 1,                                       \
 1, 1, 1, 1, 1, 1, 1, 1,                                       \
 1, 1, 1, 1, 1, 1, 1, 1,                                       \
 1, 1, 1, 1, 1, 1, 1, 1,                                       \
 1, 1, 1, 1, 1, 1, 1, 1,                                       \
 1, 1, 1, 1, 1, 1, 1, 1,                                       \
 1, 1, 1, 1, 1, 1, 1, 1,                                       \
 1, 1, 1, 1, 1, 1, 1, 1,                                       \
 1, 1, 1, 1, 1, 1, 1, 1,                                       \
 1, 1, 1, 1, 1, 1, 1, 1,                                       \
 1, 1, 1, 1, 1, 1, 1, 1,                                       \
 1, 1, 1, 1, 1, 1, 1, 1,                                       \
 1, 1, 1, 1, 1, 1, 1, 1,                                       \
 1, 1, 1, 1, 1, 1, 1,
/** @brief Paste 7 arguments at their boundary.*/
#define P99_PASTE7(...) P00_PASTE7(P99_LAST(__VA_ARGS__), P99_ALLBUTLAST(__VA_ARGS__))
#define P00_PASTE7(L, ...) P99_PASTE2(P99_PASTE6(__VA_ARGS__), L)
/** @brief Paste 8 arguments at their boundary.*/
#define P99_PASTE8(...) P00_PASTE8(P99_LAST(__VA_ARGS__), P99_ALLBUTLAST(__VA_ARGS__))
#define P00_PASTE8(L, ...) P99_PASTE2(P99_PASTE7(__VA_ARGS__), L)
/** @brief Paste 9 arguments at their boundary.*/
#define P99_PASTE9(...) P00_PASTE9(P99_LAST(__VA_ARGS__), P99_ALLBUTLAST(__VA_ARGS__))
#define P00_PASTE9(L, ...) P99_PASTE2(P99_PASTE8(__VA_ARGS__), L)
/** @brief Paste 10 arguments at their boundary.*/
#define P99_PASTE10(...) P00_PASTE10(P99_LAST(__VA_ARGS__), P99_ALLBUTLAST(__VA_ARGS__))
#define P00_PASTE10(L, ...) P99_PASTE2(P99_PASTE9(__VA_ARGS__), L)
/** @brief Paste 11 arguments at their boundary.*/
#define P99_PASTE11(...) P00_PASTE11(P99_LAST(__VA_ARGS__), P99_ALLBUTLAST(__VA_ARGS__))
#define P00_PASTE11(L, ...) P99_PASTE2(P99_PASTE10(__VA_ARGS__), L)
/** @brief Paste 12 arguments at their boundary.*/
#define P99_PASTE12(...) P00_PASTE12(P99_LAST(__VA_ARGS__), P99_ALLBUTLAST(__VA_ARGS__))
#define P00_PASTE12(L, ...) P99_PASTE2(P99_PASTE11(__VA_ARGS__), L)
/** @brief Paste 13 arguments at their boundary.*/
#define P99_PASTE13(...) P00_PASTE13(P99_LAST(__VA_ARGS__), P99_ALLBUTLAST(__VA_ARGS__))
#define P00_PASTE13(L, ...) P99_PASTE2(P99_PASTE12(__VA_ARGS__), L)
/** @brief Paste 14 arguments at their boundary.*/
#define P99_PASTE14(...) P00_PASTE14(P99_LAST(__VA_ARGS__), P99_ALLBUTLAST(__VA_ARGS__))
#define P00_PASTE14(L, ...) P99_PASTE2(P99_PASTE13(__VA_ARGS__), L)
/** @brief Paste 15 arguments at their boundary.*/
#define P99_PASTE15(...) P00_PASTE15(P99_LAST(__VA_ARGS__), P99_ALLBUTLAST(__VA_ARGS__))
#define P00_PASTE15(L, ...) P99_PASTE2(P99_PASTE14(__VA_ARGS__), L)
/** @brief Paste 16 arguments at their boundary.*/
#define P99_PASTE16(...) P00_PASTE16(P99_LAST(__VA_ARGS__), P99_ALLBUTLAST(__VA_ARGS__))
#define P00_PASTE16(L, ...) P99_PASTE2(P99_PASTE15(__VA_ARGS__), L)
/** @brief Paste 17 arguments at their boundary.*/
#define P99_PASTE17(...) P00_PASTE17(P99_LAST(__VA_ARGS__), P99_ALLBUTLAST(__VA_ARGS__))
#define P00_PASTE17(L, ...) P99_PASTE2(P99_PASTE16(__VA_ARGS__), L)
/** @brief Paste 18 arguments at their boundary.*/
#define P99_PASTE18(...) P00_PASTE18(P99_LAST(__VA_ARGS__), P99_ALLBUTLAST(__VA_ARGS__))
#define P00_PASTE18(L, ...) P99_PASTE2(P99_PASTE17(__VA_ARGS__), L)
/** @brief Paste 19 arguments at their boundary.*/
#define P99_PASTE19(...) P00_PASTE19(P99_LAST(__VA_ARGS__), P99_ALLBUTLAST(__VA_ARGS__))
#define P00_PASTE19(L, ...) P99_PASTE2(P99_PASTE18(__VA_ARGS__), L)
/** @brief Paste 20 arguments at their boundary.*/
#define P99_PASTE20(...) P00_PASTE20(P99_LAST(__VA_ARGS__), P99_ALLBUTLAST(__VA_ARGS__))
#define P00_PASTE20(L, ...) P99_PASTE2(P99_PASTE19(__VA_ARGS__), L)
/** @brief Paste 21 arguments at their boundary.*/
#define P99_PASTE21(...) P00_PASTE21(P99_LAST(__VA_ARGS__), P99_ALLBUTLAST(__VA_ARGS__))
#define P00_PASTE21(L, ...) P99_PASTE2(P99_PASTE20(__VA_ARGS__), L)
/** @brief Paste 22 arguments at their boundary.*/
#define P99_PASTE22(...) P00_PASTE22(P99_LAST(__VA_ARGS__), P99_ALLBUTLAST(__VA_ARGS__))
#define P00_PASTE22(L, ...) P99_PASTE2(P99_PASTE21(__VA_ARGS__), L)
/** @brief Paste 23 arguments at their boundary.*/
#define P99_PASTE23(...) P00_PASTE23(P99_LAST(__VA_ARGS__), P99_ALLBUTLAST(__VA_ARGS__))
#define P00_PASTE23(L, ...) P99_PASTE2(P99_PASTE22(__VA_ARGS__), L)
/** @brief Paste 24 arguments at their boundary.*/
#define P99_PASTE24(...) P00_PASTE24(P99_LAST(__VA_ARGS__), P99_ALLBUTLAST(__VA_ARGS__))
#define P00_PASTE24(L, ...) P99_PASTE2(P99_PASTE23(__VA_ARGS__), L)
/** @brief Paste 25 arguments at their boundary.*/
#define P99_PASTE25(...) P00_PASTE25(P99_LAST(__VA_ARGS__), P99_ALLBUTLAST(__VA_ARGS__))
#define P00_PASTE25(L, ...) P99_PASTE2(P99_PASTE24(__VA_ARGS__), L)
/** @brief Paste 26 arguments at their boundary.*/
#define P99_PASTE26(...) P00_PASTE26(P99_LAST(__VA_ARGS__), P99_ALLBUTLAST(__VA_ARGS__))
#define P00_PASTE26(L, ...) P99_PASTE2(P99_PASTE25(__VA_ARGS__), L)
/** @brief Paste 27 arguments at their boundary.*/
#define P99_PASTE27(...) P00_PASTE27(P99_LAST(__VA_ARGS__), P99_ALLBUTLAST(__VA_ARGS__))
#define P00_PASTE27(L, ...) P99_PASTE2(P99_PASTE26(__VA_ARGS__), L)
/** @brief Paste 28 arguments at their boundary.*/
#define P99_PASTE28(...) P00_PASTE28(P99_LAST(__VA_ARGS__), P99_ALLBUTLAST(__VA_ARGS__))
#define P00_PASTE28(L, ...) P99_PASTE2(P99_PASTE27(__VA_ARGS__), L)
/** @brief Paste 29 arguments at their boundary.*/
#define P99_PASTE29(...) P00_PASTE29(P99_LAST(__VA_ARGS__), P99_ALLBUTLAST(__VA_ARGS__))
#define P00_PASTE29(L, ...) P99_PASTE2(P99_PASTE28(__VA_ARGS__), L)
/** @brief Paste 30 arguments at their boundary.*/
#define P99_PASTE30(...) P00_PASTE30(P99_LAST(__VA_ARGS__), P99_ALLBUTLAST(__VA_ARGS__))
#define P00_PASTE30(L, ...) P99_PASTE2(P99_PASTE29(__VA_ARGS__), L)
/** @brief Paste 31 arguments at their boundary.*/
#define P99_PASTE31(...) P00_PASTE31(P99_LAST(__VA_ARGS__), P99_ALLBUTLAST(__VA_ARGS__))
#define P00_PASTE31(L, ...) P99_PASTE2(P99_PASTE30(__VA_ARGS__), L)
/** @brief Paste 32 arguments at their boundary.*/
#define P99_PASTE32(...) P00_PASTE32(P99_LAST(__VA_ARGS__), P99_ALLBUTLAST(__VA_ARGS__))
#define P00_PASTE32(L, ...) P99_PASTE2(P99_PASTE31(__VA_ARGS__), L)
/** @brief Paste 33 arguments at their boundary.*/
#define P99_PASTE33(...) P00_PASTE33(P99_LAST(__VA_ARGS__), P99_ALLBUTLAST(__VA_ARGS__))
#define P00_PASTE33(L, ...) P99_PASTE2(P99_PASTE32(__VA_ARGS__), L)
/** @brief Paste 34 arguments at their boundary.*/
#define P99_PASTE34(...) P00_PASTE34(P99_LAST(__VA_ARGS__), P99_ALLBUTLAST(__VA_ARGS__))
#define P00_PASTE34(L, ...) P99_PASTE2(P99_PASTE33(__VA_ARGS__), L)
/** @brief Paste 35 arguments at their boundary.*/
#define P99_PASTE35(...) P00_PASTE35(P99_LAST(__VA_ARGS__), P99_ALLBUTLAST(__VA_ARGS__))
#define P00_PASTE35(L, ...) P99_PASTE2(P99_PASTE34(__VA_ARGS__), L)
/** @brief Paste 36 arguments at their boundary.*/
#define P99_PASTE36(...) P00_PASTE36(P99_LAST(__VA_ARGS__), P99_ALLBUTLAST(__VA_ARGS__))
#define P00_PASTE36(L, ...) P99_PASTE2(P99_PASTE35(__VA_ARGS__), L)
/** @brief Paste 37 arguments at their boundary.*/
#define P99_PASTE37(...) P00_PASTE37(P99_LAST(__VA_ARGS__), P99_ALLBUTLAST(__VA_ARGS__))
#define P00_PASTE37(L, ...) P99_PASTE2(P99_PASTE36(__VA_ARGS__), L)
/** @brief Paste 38 arguments at their boundary.*/
#define P99_PASTE38(...) P00_PASTE38(P99_LAST(__VA_ARGS__), P99_ALLBUTLAST(__VA_ARGS__))
#define P00_PASTE38(L, ...) P99_PASTE2(P99_PASTE37(__VA_ARGS__), L)
/** @brief Paste 39 arguments at their boundary.*/
#define P99_PASTE39(...) P00_PASTE39(P99_LAST(__VA_ARGS__), P99_ALLBUTLAST(__VA_ARGS__))
#define P00_PASTE39(L, ...) P99_PASTE2(P99_PASTE38(__VA_ARGS__), L)
/** @brief Paste 40 arguments at their boundary.*/
#define P99_PASTE40(...) P00_PASTE40(P99_LAST(__VA_ARGS__), P99_ALLBUTLAST(__VA_ARGS__))
#define P00_PASTE40(L, ...) P99_PASTE2(P99_PASTE39(__VA_ARGS__), L)
/** @brief Paste 41 arguments at their boundary.*/
#define P99_PASTE41(...) P00_PASTE41(P99_LAST(__VA_ARGS__), P99_ALLBUTLAST(__VA_ARGS__))
#define P00_PASTE41(L, ...) P99_PASTE2(P99_PASTE40(__VA_ARGS__), L)
/** @brief Paste 42 arguments at their boundary.*/
#define P99_PASTE42(...) P00_PASTE42(P99_LAST(__VA_ARGS__), P99_ALLBUTLAST(__VA_ARGS__))
#define P00_PASTE42(L, ...) P99_PASTE2(P99_PASTE41(__VA_ARGS__), L)
/** @brief Paste 43 arguments at their boundary.*/
#define P99_PASTE43(...) P00_PASTE43(P99_LAST(__VA_ARGS__), P99_ALLBUTLAST(__VA_ARGS__))
#define P00_PASTE43(L, ...) P99_PASTE2(P99_PASTE42(__VA_ARGS__), L)
/** @brief Paste 44 arguments at their boundary.*/
#define P99_PASTE44(...) P00_PASTE44(P99_LAST(__VA_ARGS__), P99_ALLBUTLAST(__VA_ARGS__))
#define P00_PASTE44(L, ...) P99_PASTE2(P99_PASTE43(__VA_ARGS__), L)
/** @brief Paste 45 arguments at their boundary.*/
#define P99_PASTE45(...) P00_PASTE45(P99_LAST(__VA_ARGS__), P99_ALLBUTLAST(__VA_ARGS__))
#define P00_PASTE45(L, ...) P99_PASTE2(P99_PASTE44(__VA_ARGS__), L)
/** @brief Paste 46 arguments at their boundary.*/
#define P99_PASTE46(...) P00_PASTE46(P99_LAST(__VA_ARGS__), P99_ALLBUTLAST(__VA_ARGS__))
#define P00_PASTE46(L, ...) P99_PASTE2(P99_PASTE45(__VA_ARGS__), L)
/** @brief Paste 47 arguments at their boundary.*/
#define P99_PASTE47(...) P00_PASTE47(P99_LAST(__VA_ARGS__), P99_ALLBUTLAST(__VA_ARGS__))
#define P00_PASTE47(L, ...) P99_PASTE2(P99_PASTE46(__VA_ARGS__), L)
/** @brief Paste 48 arguments at their boundary.*/
#define P99_PASTE48(...) P00_PASTE48(P99_LAST(__VA_ARGS__), P99_ALLBUTLAST(__VA_ARGS__))
#define P00_PASTE48(L, ...) P99_PASTE2(P99_PASTE47(__VA_ARGS__), L)
/** @brief Paste 49 arguments at their boundary.*/
#define P99_PASTE49(...) P00_PASTE49(P99_LAST(__VA_ARGS__), P99_ALLBUTLAST(__VA_ARGS__))
#define P00_PASTE49(L, ...) P99_PASTE2(P99_PASTE48(__VA_ARGS__), L)
/** @brief Paste 50 arguments at their boundary.*/
#define P99_PASTE50(...) P00_PASTE50(P99_LAST(__VA_ARGS__), P99_ALLBUTLAST(__VA_ARGS__))
#define P00_PASTE50(L, ...) P99_PASTE2(P99_PASTE49(__VA_ARGS__), L)
/** @brief Paste 51 arguments at their boundary.*/
#define P99_PASTE51(...) P00_PASTE51(P99_LAST(__VA_ARGS__), P99_ALLBUTLAST(__VA_ARGS__))
#define P00_PASTE51(L, ...) P99_PASTE2(P99_PASTE50(__VA_ARGS__), L)
/** @brief Paste 52 arguments at their boundary.*/
#define P99_PASTE52(...) P00_PASTE52(P99_LAST(__VA_ARGS__), P99_ALLBUTLAST(__VA_ARGS__))
#define P00_PASTE52(L, ...) P99_PASTE2(P99_PASTE51(__VA_ARGS__), L)
/** @brief Paste 53 arguments at their boundary.*/
#define P99_PASTE53(...) P00_PASTE53(P99_LAST(__VA_ARGS__), P99_ALLBUTLAST(__VA_ARGS__))
#define P00_PASTE53(L, ...) P99_PASTE2(P99_PASTE52(__VA_ARGS__), L)
/** @brief Paste 54 arguments at their boundary.*/
#define P99_PASTE54(...) P00_PASTE54(P99_LAST(__VA_ARGS__), P99_ALLBUTLAST(__VA_ARGS__))
#define P00_PASTE54(L, ...) P99_PASTE2(P99_PASTE53(__VA_ARGS__), L)
/** @brief Paste 55 arguments at their boundary.*/
#define P99_PASTE55(...) P00_PASTE55(P99_LAST(__VA_ARGS__), P99_ALLBUTLAST(__VA_ARGS__))
#define P00_PASTE55(L, ...) P99_PASTE2(P99_PASTE54(__VA_ARGS__), L)
/** @brief Paste 56 arguments at their boundary.*/
#define P99_PASTE56(...) P00_PASTE56(P99_LAST(__VA_ARGS__), P99_ALLBUTLAST(__VA_ARGS__))
#define P00_PASTE56(L, ...) P99_PASTE2(P99_PASTE55(__VA_ARGS__), L)
/** @brief Paste 57 arguments at their boundary.*/
#define P99_PASTE57(...) P00_PASTE57(P99_LAST(__VA_ARGS__), P99_ALLBUTLAST(__VA_ARGS__))
#define P00_PASTE57(L, ...) P99_PASTE2(P99_PASTE56(__VA_ARGS__), L)
/** @brief Paste 58 arguments at their boundary.*/
#define P99_PASTE58(...) P00_PASTE58(P99_LAST(__VA_ARGS__), P99_ALLBUTLAST(__VA_ARGS__))
#define P00_PASTE58(L, ...) P99_PASTE2(P99_PASTE57(__VA_ARGS__), L)
/** @brief Paste 59 arguments at their boundary.*/
#define P99_PASTE59(...) P00_PASTE59(P99_LAST(__VA_ARGS__), P99_ALLBUTLAST(__VA_ARGS__))
#define P00_PASTE59(L, ...) P99_PASTE2(P99_PASTE58(__VA_ARGS__), L)
/** @brief Paste 60 arguments at their boundary.*/
#define P99_PASTE60(...) P00_PASTE60(P99_LAST(__VA_ARGS__), P99_ALLBUTLAST(__VA_ARGS__))
#define P00_PASTE60(L, ...) P99_PASTE2(P99_PASTE59(__VA_ARGS__), L)
/** @brief Paste 61 arguments at their boundary.*/
#define P99_PASTE61(...) P00_PASTE61(P99_LAST(__VA_ARGS__), P99_ALLBUTLAST(__VA_ARGS__))
#define P00_PASTE61(L, ...) P99_PASTE2(P99_PASTE60(__VA_ARGS__), L)
/** @brief Paste 62 arguments at their boundary.*/
#define P99_PASTE62(...) P00_PASTE62(P99_LAST(__VA_ARGS__), P99_ALLBUTLAST(__VA_ARGS__))
#define P00_PASTE62(L, ...) P99_PASTE2(P99_PASTE61(__VA_ARGS__), L)
/** @brief Paste 63 arguments at their boundary.*/
#define P99_PASTE63(...) P00_PASTE63(P99_LAST(__VA_ARGS__), P99_ALLBUTLAST(__VA_ARGS__))
#define P00_PASTE63(L, ...) P99_PASTE2(P99_PASTE62(__VA_ARGS__), L)
/** @brief Paste 64 arguments at their boundary.*/
#define P99_PASTE64(...) P00_PASTE64(P99_LAST(__VA_ARGS__), P99_ALLBUTLAST(__VA_ARGS__))
#define P00_PASTE64(L, ...) P99_PASTE2(P99_PASTE63(__VA_ARGS__), L)
/** @brief Paste 65 arguments at their boundary.*/
#define P99_PASTE65(...) P00_PASTE65(P99_LAST(__VA_ARGS__), P99_ALLBUTLAST(__VA_ARGS__))
#define P00_PASTE65(L, ...) P99_PASTE2(P99_PASTE64(__VA_ARGS__), L)
/** @brief Paste 66 arguments at their boundary.*/
#define P99_PASTE66(...) P00_PASTE66(P99_LAST(__VA_ARGS__), P99_ALLBUTLAST(__VA_ARGS__))
#define P00_PASTE66(L, ...) P99_PASTE2(P99_PASTE65(__VA_ARGS__), L)
/** @brief Paste 67 arguments at their boundary.*/
#define P99_PASTE67(...) P00_PASTE67(P99_LAST(__VA_ARGS__), P99_ALLBUTLAST(__VA_ARGS__))
#define P00_PASTE67(L, ...) P99_PASTE2(P99_PASTE66(__VA_ARGS__), L)
/** @brief Paste 68 arguments at their boundary.*/
#define P99_PASTE68(...) P00_PASTE68(P99_LAST(__VA_ARGS__), P99_ALLBUTLAST(__VA_ARGS__))
#define P00_PASTE68(L, ...) P99_PASTE2(P99_PASTE67(__VA_ARGS__), L)
/** @brief Paste 69 arguments at their boundary.*/
#define P99_PASTE69(...) P00_PASTE69(P99_LAST(__VA_ARGS__), P99_ALLBUTLAST(__VA_ARGS__))
#define P00_PASTE69(L, ...) P99_PASTE2(P99_PASTE68(__VA_ARGS__), L)
/** @brief Paste 70 arguments at their boundary.*/
#define P99_PASTE70(...) P00_PASTE70(P99_LAST(__VA_ARGS__), P99_ALLBUTLAST(__VA_ARGS__))
#define P00_PASTE70(L, ...) P99_PASTE2(P99_PASTE69(__VA_ARGS__), L)
/** @brief Paste 71 arguments at their boundary.*/
#define P99_PASTE71(...) P00_PASTE71(P99_LAST(__VA_ARGS__), P99_ALLBUTLAST(__VA_ARGS__))
#define P00_PASTE71(L, ...) P99_PASTE2(P99_PASTE70(__VA_ARGS__), L)
/** @brief Paste 72 arguments at their boundary.*/
#define P99_PASTE72(...) P00_PASTE72(P99_LAST(__VA_ARGS__), P99_ALLBUTLAST(__VA_ARGS__))
#define P00_PASTE72(L, ...) P99_PASTE2(P99_PASTE71(__VA_ARGS__), L)
/** @brief Paste 73 arguments at their boundary.*/
#define P99_PASTE73(...) P00_PASTE73(P99_LAST(__VA_ARGS__), P99_ALLBUTLAST(__VA_ARGS__))
#define P00_PASTE73(L, ...) P99_PASTE2(P99_PASTE72(__VA_ARGS__), L)
/** @brief Paste 74 arguments at their boundary.*/
#define P99_PASTE74(...) P00_PASTE74(P99_LAST(__VA_ARGS__), P99_ALLBUTLAST(__VA_ARGS__))
#define P00_PASTE74(L, ...) P99_PASTE2(P99_PASTE73(__VA_ARGS__), L)
/** @brief Paste 75 arguments at their boundary.*/
#define P99_PASTE75(...) P00_PASTE75(P99_LAST(__VA_ARGS__), P99_ALLBUTLAST(__VA_ARGS__))
#define P00_PASTE75(L, ...) P99_PASTE2(P99_PASTE74(__VA_ARGS__), L)
/** @brief Paste 76 arguments at their boundary.*/
#define P99_PASTE76(...) P00_PASTE76(P99_LAST(__VA_ARGS__), P99_ALLBUTLAST(__VA_ARGS__))
#define P00_PASTE76(L, ...) P99_PASTE2(P99_PASTE75(__VA_ARGS__), L)
/** @brief Paste 77 arguments at their boundary.*/
#define P99_PASTE77(...) P00_PASTE77(P99_LAST(__VA_ARGS__), P99_ALLBUTLAST(__VA_ARGS__))
#define P00_PASTE77(L, ...) P99_PASTE2(P99_PASTE76(__VA_ARGS__), L)
/** @brief Paste 78 arguments at their boundary.*/
#define P99_PASTE78(...) P00_PASTE78(P99_LAST(__VA_ARGS__), P99_ALLBUTLAST(__VA_ARGS__))
#define P00_PASTE78(L, ...) P99_PASTE2(P99_PASTE77(__VA_ARGS__), L)
/** @brief Paste 79 arguments at their boundary.*/
#define P99_PASTE79(...) P00_PASTE79(P99_LAST(__VA_ARGS__), P99_ALLBUTLAST(__VA_ARGS__))
#define P00_PASTE79(L, ...) P99_PASTE2(P99_PASTE78(__VA_ARGS__), L)
/** @brief Paste 80 arguments at their boundary.*/
#define P99_PASTE80(...) P00_PASTE80(P99_LAST(__VA_ARGS__), P99_ALLBUTLAST(__VA_ARGS__))
#define P00_PASTE80(L, ...) P99_PASTE2(P99_PASTE79(__VA_ARGS__), L)
/** @brief Paste 81 arguments at their boundary.*/
#define P99_PASTE81(...) P00_PASTE81(P99_LAST(__VA_ARGS__), P99_ALLBUTLAST(__VA_ARGS__))
#define P00_PASTE81(L, ...) P99_PASTE2(P99_PASTE80(__VA_ARGS__), L)
/** @brief Paste 82 arguments at their boundary.*/
#define P99_PASTE82(...) P00_PASTE82(P99_LAST(__VA_ARGS__), P99_ALLBUTLAST(__VA_ARGS__))
#define P00_PASTE82(L, ...) P99_PASTE2(P99_PASTE81(__VA_ARGS__), L)
/** @brief Paste 83 arguments at their boundary.*/
#define P99_PASTE83(...) P00_PASTE83(P99_LAST(__VA_ARGS__), P99_ALLBUTLAST(__VA_ARGS__))
#define P00_PASTE83(L, ...) P99_PASTE2(P99_PASTE82(__VA_ARGS__), L)
/** @brief Paste 84 arguments at their boundary.*/
#define P99_PASTE84(...) P00_PASTE84(P99_LAST(__VA_ARGS__), P99_ALLBUTLAST(__VA_ARGS__))
#define P00_PASTE84(L, ...) P99_PASTE2(P99_PASTE83(__VA_ARGS__), L)
/** @brief Paste 85 arguments at their boundary.*/
#define P99_PASTE85(...) P00_PASTE85(P99_LAST(__VA_ARGS__), P99_ALLBUTLAST(__VA_ARGS__))
#define P00_PASTE85(L, ...) P99_PASTE2(P99_PASTE84(__VA_ARGS__), L)
/** @brief Paste 86 arguments at their boundary.*/
#define P99_PASTE86(...) P00_PASTE86(P99_LAST(__VA_ARGS__), P99_ALLBUTLAST(__VA_ARGS__))
#define P00_PASTE86(L, ...) P99_PASTE2(P99_PASTE85(__VA_ARGS__), L)
/** @brief Paste 87 arguments at their boundary.*/
#define P99_PASTE87(...) P00_PASTE87(P99_LAST(__VA_ARGS__), P99_ALLBUTLAST(__VA_ARGS__))
#define P00_PASTE87(L, ...) P99_PASTE2(P99_PASTE86(__VA_ARGS__), L)
/** @brief Paste 88 arguments at their boundary.*/
#define P99_PASTE88(...) P00_PASTE88(P99_LAST(__VA_ARGS__), P99_ALLBUTLAST(__VA_ARGS__))
#define P00_PASTE88(L, ...) P99_PASTE2(P99_PASTE87(__VA_ARGS__), L)
/** @brief Paste 89 arguments at their boundary.*/
#define P99_PASTE89(...) P00_PASTE89(P99_LAST(__VA_ARGS__), P99_ALLBUTLAST(__VA_ARGS__))
#define P00_PASTE89(L, ...) P99_PASTE2(P99_PASTE88(__VA_ARGS__), L)
/** @brief Paste 90 arguments at their boundary.*/
#define P99_PASTE90(...) P00_PASTE90(P99_LAST(__VA_ARGS__), P99_ALLBUTLAST(__VA_ARGS__))
#define P00_PASTE90(L, ...) P99_PASTE2(P99_PASTE89(__VA_ARGS__), L)
/** @brief Paste 91 arguments at their boundary.*/
#define P99_PASTE91(...) P00_PASTE91(P99_LAST(__VA_ARGS__), P99_ALLBUTLAST(__VA_ARGS__))
#define P00_PASTE91(L, ...) P99_PASTE2(P99_PASTE90(__VA_ARGS__), L)
/** @brief Paste 92 arguments at their boundary.*/
#define P99_PASTE92(...) P00_PASTE92(P99_LAST(__VA_ARGS__), P99_ALLBUTLAST(__VA_ARGS__))
#define P00_PASTE92(L, ...) P99_PASTE2(P99_PASTE91(__VA_ARGS__), L)
/** @brief Paste 93 arguments at their boundary.*/
#define P99_PASTE93(...) P00_PASTE93(P99_LAST(__VA_ARGS__), P99_ALLBUTLAST(__VA_ARGS__))
#define P00_PASTE93(L, ...) P99_PASTE2(P99_PASTE92(__VA_ARGS__), L)
/** @brief Paste 94 arguments at their boundary.*/
#define P99_PASTE94(...) P00_PASTE94(P99_LAST(__VA_ARGS__), P99_ALLBUTLAST(__VA_ARGS__))
#define P00_PASTE94(L, ...) P99_PASTE2(P99_PASTE93(__VA_ARGS__), L)
/** @brief Paste 95 arguments at their boundary.*/
#define P99_PASTE95(...) P00_PASTE95(P99_LAST(__VA_ARGS__), P99_ALLBUTLAST(__VA_ARGS__))
#define P00_PASTE95(L, ...) P99_PASTE2(P99_PASTE94(__VA_ARGS__), L)
/** @brief Paste 96 arguments at their boundary.*/
#define P99_PASTE96(...) P00_PASTE96(P99_LAST(__VA_ARGS__), P99_ALLBUTLAST(__VA_ARGS__))
#define P00_PASTE96(L, ...) P99_PASTE2(P99_PASTE95(__VA_ARGS__), L)
/** @brief Paste 97 arguments at their boundary.*/
#define P99_PASTE97(...) P00_PASTE97(P99_LAST(__VA_ARGS__), P99_ALLBUTLAST(__VA_ARGS__))
#define P00_PASTE97(L, ...) P99_PASTE2(P99_PASTE96(__VA_ARGS__), L)
/** @brief Paste 98 arguments at their boundary.*/
#define P99_PASTE98(...) P00_PASTE98(P99_LAST(__VA_ARGS__), P99_ALLBUTLAST(__VA_ARGS__))
#define P00_PASTE98(L, ...) P99_PASTE2(P99_PASTE97(__VA_ARGS__), L)
/** @brief Paste 99 arguments at their boundary.*/
#define P99_PASTE99(...) P00_PASTE99(P99_LAST(__VA_ARGS__), P99_ALLBUTLAST(__VA_ARGS__))
#define P00_PASTE99(L, ...) P99_PASTE2(P99_PASTE98(__VA_ARGS__), L)
/** @brief Paste 100 arguments at their boundary.*/
#define P99_PASTE100(...) P00_PASTE100(P99_LAST(__VA_ARGS__), P99_ALLBUTLAST(__VA_ARGS__))
#define P00_PASTE100(L, ...) P99_PASTE2(P99_PASTE99(__VA_ARGS__), L)
/** @brief Paste 101 arguments at their boundary.*/
#define P99_PASTE101(...) P00_PASTE101(P99_LAST(__VA_ARGS__), P99_ALLBUTLAST(__VA_ARGS__))
#define P00_PASTE101(L, ...) P99_PASTE2(P99_PASTE100(__VA_ARGS__), L)
/** @brief Paste 102 arguments at their boundary.*/
#define P99_PASTE102(...) P00_PASTE102(P99_LAST(__VA_ARGS__), P99_ALLBUTLAST(__VA_ARGS__))
#define P00_PASTE102(L, ...) P99_PASTE2(P99_PASTE101(__VA_ARGS__), L)
/** @brief Paste 103 arguments at their boundary.*/
#define P99_PASTE103(...) P00_PASTE103(P99_LAST(__VA_ARGS__), P99_ALLBUTLAST(__VA_ARGS__))
#define P00_PASTE103(L, ...) P99_PASTE2(P99_PASTE102(__VA_ARGS__), L)
/** @brief Paste 104 arguments at their boundary.*/
#define P99_PASTE104(...) P00_PASTE104(P99_LAST(__VA_ARGS__), P99_ALLBUTLAST(__VA_ARGS__))
#define P00_PASTE104(L, ...) P99_PASTE2(P99_PASTE103(__VA_ARGS__), L)
/** @brief Paste 105 arguments at their boundary.*/
#define P99_PASTE105(...) P00_PASTE105(P99_LAST(__VA_ARGS__), P99_ALLBUTLAST(__VA_ARGS__))
#define P00_PASTE105(L, ...) P99_PASTE2(P99_PASTE104(__VA_ARGS__), L)
/** @brief Paste 106 arguments at their boundary.*/
#define P99_PASTE106(...) P00_PASTE106(P99_LAST(__VA_ARGS__), P99_ALLBUTLAST(__VA_ARGS__))
#define P00_PASTE106(L, ...) P99_PASTE2(P99_PASTE105(__VA_ARGS__), L)
/** @brief Paste 107 arguments at their boundary.*/
#define P99_PASTE107(...) P00_PASTE107(P99_LAST(__VA_ARGS__), P99_ALLBUTLAST(__VA_ARGS__))
#define P00_PASTE107(L, ...) P99_PASTE2(P99_PASTE106(__VA_ARGS__), L)
/** @brief Paste 108 arguments at their boundary.*/
#define P99_PASTE108(...) P00_PASTE108(P99_LAST(__VA_ARGS__), P99_ALLBUTLAST(__VA_ARGS__))
#define P00_PASTE108(L, ...) P99_PASTE2(P99_PASTE107(__VA_ARGS__), L)
/** @brief Paste 109 arguments at their boundary.*/
#define P99_PASTE109(...) P00_PASTE109(P99_LAST(__VA_ARGS__), P99_ALLBUTLAST(__VA_ARGS__))
#define P00_PASTE109(L, ...) P99_PASTE2(P99_PASTE108(__VA_ARGS__), L)
/** @brief Paste 110 arguments at their boundary.*/
#define P99_PASTE110(...) P00_PASTE110(P99_LAST(__VA_ARGS__), P99_ALLBUTLAST(__VA_ARGS__))
#define P00_PASTE110(L, ...) P99_PASTE2(P99_PASTE109(__VA_ARGS__), L)
/** @brief Paste 111 arguments at their boundary.*/
#define P99_PASTE111(...) P00_PASTE111(P99_LAST(__VA_ARGS__), P99_ALLBUTLAST(__VA_ARGS__))
#define P00_PASTE111(L, ...) P99_PASTE2(P99_PASTE110(__VA_ARGS__), L)
/** @brief Paste 112 arguments at their boundary.*/
#define P99_PASTE112(...) P00_PASTE112(P99_LAST(__VA_ARGS__), P99_ALLBUTLAST(__VA_ARGS__))
#define P00_PASTE112(L, ...) P99_PASTE2(P99_PASTE111(__VA_ARGS__), L)
/** @brief Paste 113 arguments at their boundary.*/
#define P99_PASTE113(...) P00_PASTE113(P99_LAST(__VA_ARGS__), P99_ALLBUTLAST(__VA_ARGS__))
#define P00_PASTE113(L, ...) P99_PASTE2(P99_PASTE112(__VA_ARGS__), L)
/** @brief Paste 114 arguments at their boundary.*/
#define P99_PASTE114(...) P00_PASTE114(P99_LAST(__VA_ARGS__), P99_ALLBUTLAST(__VA_ARGS__))
#define P00_PASTE114(L, ...) P99_PASTE2(P99_PASTE113(__VA_ARGS__), L)
/** @brief Paste 115 arguments at their boundary.*/
#define P99_PASTE115(...) P00_PASTE115(P99_LAST(__VA_ARGS__), P99_ALLBUTLAST(__VA_ARGS__))
#define P00_PASTE115(L, ...) P99_PASTE2(P99_PASTE114(__VA_ARGS__), L)
/** @brief Paste 116 arguments at their boundary.*/
#define P99_PASTE116(...) P00_PASTE116(P99_LAST(__VA_ARGS__), P99_ALLBUTLAST(__VA_ARGS__))
#define P00_PASTE116(L, ...) P99_PASTE2(P99_PASTE115(__VA_ARGS__), L)
/** @brief Paste 117 arguments at their boundary.*/
#define P99_PASTE117(...) P00_PASTE117(P99_LAST(__VA_ARGS__), P99_ALLBUTLAST(__VA_ARGS__))
#define P00_PASTE117(L, ...) P99_PASTE2(P99_PASTE116(__VA_ARGS__), L)
/** @brief Paste 118 arguments at their boundary.*/
#define P99_PASTE118(...) P00_PASTE118(P99_LAST(__VA_ARGS__), P99_ALLBUTLAST(__VA_ARGS__))
#define P00_PASTE118(L, ...) P99_PASTE2(P99_PASTE117(__VA_ARGS__), L)
/** @brief Paste 119 arguments at their boundary.*/
#define P99_PASTE119(...) P00_PASTE119(P99_LAST(__VA_ARGS__), P99_ALLBUTLAST(__VA_ARGS__))
#define P00_PASTE119(L, ...) P99_PASTE2(P99_PASTE118(__VA_ARGS__), L)
/** @brief Paste 120 arguments at their boundary.*/
#define P99_PASTE120(...) P00_PASTE120(P99_LAST(__VA_ARGS__), P99_ALLBUTLAST(__VA_ARGS__))
#define P00_PASTE120(L, ...) P99_PASTE2(P99_PASTE119(__VA_ARGS__), L)
/** @brief Paste 121 arguments at their boundary.*/
#define P99_PASTE121(...) P00_PASTE121(P99_LAST(__VA_ARGS__), P99_ALLBUTLAST(__VA_ARGS__))
#define P00_PASTE121(L, ...) P99_PASTE2(P99_PASTE120(__VA_ARGS__), L)
/** @brief Paste 122 arguments at their boundary.*/
#define P99_PASTE122(...) P00_PASTE122(P99_LAST(__VA_ARGS__), P99_ALLBUTLAST(__VA_ARGS__))
#define P00_PASTE122(L, ...) P99_PASTE2(P99_PASTE121(__VA_ARGS__), L)
/** @brief Paste 123 arguments at their boundary.*/
#define P99_PASTE123(...) P00_PASTE123(P99_LAST(__VA_ARGS__), P99_ALLBUTLAST(__VA_ARGS__))
#define P00_PASTE123(L, ...) P99_PASTE2(P99_PASTE122(__VA_ARGS__), L)
/** @brief Paste 124 arguments at their boundary.*/
#define P99_PASTE124(...) P00_PASTE124(P99_LAST(__VA_ARGS__), P99_ALLBUTLAST(__VA_ARGS__))
#define P00_PASTE124(L, ...) P99_PASTE2(P99_PASTE123(__VA_ARGS__), L)
/** @brief Paste 125 arguments at their boundary.*/
#define P99_PASTE125(...) P00_PASTE125(P99_LAST(__VA_ARGS__), P99_ALLBUTLAST(__VA_ARGS__))
#define P00_PASTE125(L, ...) P99_PASTE2(P99_PASTE124(__VA_ARGS__), L)
/** @brief Paste 126 arguments at their boundary.*/
#define P99_PASTE126(...) P00_PASTE126(P99_LAST(__VA_ARGS__), P99_ALLBUTLAST(__VA_ARGS__))
#define P00_PASTE126(L, ...) P99_PASTE2(P99_PASTE125(__VA_ARGS__), L)
/** @brief Paste 127 arguments at their boundary.*/
#define P99_PASTE127(...) P00_PASTE127(P99_LAST(__VA_ARGS__), P99_ALLBUTLAST(__VA_ARGS__))
#define P00_PASTE127(L, ...) P99_PASTE2(P99_PASTE126(__VA_ARGS__), L)
/** @brief Paste 128 arguments at their boundary.*/
#define P99_PASTE128(...) P00_PASTE128(P99_LAST(__VA_ARGS__), P99_ALLBUTLAST(__VA_ARGS__))
#define P00_PASTE128(L, ...) P99_PASTE2(P99_PASTE127(__VA_ARGS__), L)
/** @brief Paste 129 arguments at their boundary.*/
#define P99_PASTE129(...) P00_PASTE129(P99_LAST(__VA_ARGS__), P99_ALLBUTLAST(__VA_ARGS__))
#define P00_PASTE129(L, ...) P99_PASTE2(P99_PASTE128(__VA_ARGS__), L)
/** @brief Paste 130 arguments at their boundary.*/
#define P99_PASTE130(...) P00_PASTE130(P99_LAST(__VA_ARGS__), P99_ALLBUTLAST(__VA_ARGS__))
#define P00_PASTE130(L, ...) P99_PASTE2(P99_PASTE129(__VA_ARGS__), L)
/** @brief Paste 131 arguments at their boundary.*/
#define P99_PASTE131(...) P00_PASTE131(P99_LAST(__VA_ARGS__), P99_ALLBUTLAST(__VA_ARGS__))
#define P00_PASTE131(L, ...) P99_PASTE2(P99_PASTE130(__VA_ARGS__), L)
/** @brief Paste 132 arguments at their boundary.*/
#define P99_PASTE132(...) P00_PASTE132(P99_LAST(__VA_ARGS__), P99_ALLBUTLAST(__VA_ARGS__))
#define P00_PASTE132(L, ...) P99_PASTE2(P99_PASTE131(__VA_ARGS__), L)
/** @brief Paste 133 arguments at their boundary.*/
#define P99_PASTE133(...) P00_PASTE133(P99_LAST(__VA_ARGS__), P99_ALLBUTLAST(__VA_ARGS__))
#define P00_PASTE133(L, ...) P99_PASTE2(P99_PASTE132(__VA_ARGS__), L)
/** @brief Paste 134 arguments at their boundary.*/
#define P99_PASTE134(...) P00_PASTE134(P99_LAST(__VA_ARGS__), P99_ALLBUTLAST(__VA_ARGS__))
#define P00_PASTE134(L, ...) P99_PASTE2(P99_PASTE133(__VA_ARGS__), L)
/** @brief Paste 135 arguments at their boundary.*/
#define P99_PASTE135(...) P00_PASTE135(P99_LAST(__VA_ARGS__), P99_ALLBUTLAST(__VA_ARGS__))
#define P00_PASTE135(L, ...) P99_PASTE2(P99_PASTE134(__VA_ARGS__), L)
/** @brief Paste 136 arguments at their boundary.*/
#define P99_PASTE136(...) P00_PASTE136(P99_LAST(__VA_ARGS__), P99_ALLBUTLAST(__VA_ARGS__))
#define P00_PASTE136(L, ...) P99_PASTE2(P99_PASTE135(__VA_ARGS__), L)
/** @brief Paste 137 arguments at their boundary.*/
#define P99_PASTE137(...) P00_PASTE137(P99_LAST(__VA_ARGS__), P99_ALLBUTLAST(__VA_ARGS__))
#define P00_PASTE137(L, ...) P99_PASTE2(P99_PASTE136(__VA_ARGS__), L)
/** @brief Paste 138 arguments at their boundary.*/
#define P99_PASTE138(...) P00_PASTE138(P99_LAST(__VA_ARGS__), P99_ALLBUTLAST(__VA_ARGS__))
#define P00_PASTE138(L, ...) P99_PASTE2(P99_PASTE137(__VA_ARGS__), L)
/** @brief Paste 139 arguments at their boundary.*/
#define P99_PASTE139(...) P00_PASTE139(P99_LAST(__VA_ARGS__), P99_ALLBUTLAST(__VA_ARGS__))
#define P00_PASTE139(L, ...) P99_PASTE2(P99_PASTE138(__VA_ARGS__), L)
/** @brief Paste 140 arguments at their boundary.*/
#define P99_PASTE140(...) P00_PASTE140(P99_LAST(__VA_ARGS__), P99_ALLBUTLAST(__VA_ARGS__))
#define P00_PASTE140(L, ...) P99_PASTE2(P99_PASTE139(__VA_ARGS__), L)
/** @brief Paste 141 arguments at their boundary.*/
#define P99_PASTE141(...) P00_PASTE141(P99_LAST(__VA_ARGS__), P99_ALLBUTLAST(__VA_ARGS__))
#define P00_PASTE141(L, ...) P99_PASTE2(P99_PASTE140(__VA_ARGS__), L)
/** @brief Paste 142 arguments at their boundary.*/
#define P99_PASTE142(...) P00_PASTE142(P99_LAST(__VA_ARGS__), P99_ALLBUTLAST(__VA_ARGS__))
#define P00_PASTE142(L, ...) P99_PASTE2(P99_PASTE141(__VA_ARGS__), L)
/** @brief Paste 143 arguments at their boundary.*/
#define P99_PASTE143(...) P00_PASTE143(P99_LAST(__VA_ARGS__), P99_ALLBUTLAST(__VA_ARGS__))
#define P00_PASTE143(L, ...) P99_PASTE2(P99_PASTE142(__VA_ARGS__), L)
/** @brief Paste 144 arguments at their boundary.*/
#define P99_PASTE144(...) P00_PASTE144(P99_LAST(__VA_ARGS__), P99_ALLBUTLAST(__VA_ARGS__))
#define P00_PASTE144(L, ...) P99_PASTE2(P99_PASTE143(__VA_ARGS__), L)
/** @brief Paste 145 arguments at their boundary.*/
#define P99_PASTE145(...) P00_PASTE145(P99_LAST(__VA_ARGS__), P99_ALLBUTLAST(__VA_ARGS__))
#define P00_PASTE145(L, ...) P99_PASTE2(P99_PASTE144(__VA_ARGS__), L)
/** @brief Paste 146 arguments at their boundary.*/
#define P99_PASTE146(...) P00_PASTE146(P99_LAST(__VA_ARGS__), P99_ALLBUTLAST(__VA_ARGS__))
#define P00_PASTE146(L, ...) P99_PASTE2(P99_PASTE145(__VA_ARGS__), L)
/** @brief Paste 147 arguments at their boundary.*/
#define P99_PASTE147(...) P00_PASTE147(P99_LAST(__VA_ARGS__), P99_ALLBUTLAST(__VA_ARGS__))
#define P00_PASTE147(L, ...) P99_PASTE2(P99_PASTE146(__VA_ARGS__), L)
/** @brief Paste 148 arguments at their boundary.*/
#define P99_PASTE148(...) P00_PASTE148(P99_LAST(__VA_ARGS__), P99_ALLBUTLAST(__VA_ARGS__))
#define P00_PASTE148(L, ...) P99_PASTE2(P99_PASTE147(__VA_ARGS__), L)
/** @brief Paste 149 arguments at their boundary.*/
#define P99_PASTE149(...) P00_PASTE149(P99_LAST(__VA_ARGS__), P99_ALLBUTLAST(__VA_ARGS__))
#define P00_PASTE149(L, ...) P99_PASTE2(P99_PASTE148(__VA_ARGS__), L)
/** @brief Paste 150 arguments at their boundary.*/
#define P99_PASTE150(...) P00_PASTE150(P99_LAST(__VA_ARGS__), P99_ALLBUTLAST(__VA_ARGS__))
#define P00_PASTE150(L, ...) P99_PASTE2(P99_PASTE149(__VA_ARGS__), L)
/** @brief Paste 151 arguments at their boundary.*/
#define P99_PASTE151(...) P00_PASTE151(P99_LAST(__VA_ARGS__), P99_ALLBUTLAST(__VA_ARGS__))
#define P00_PASTE151(L, ...) P99_PASTE2(P99_PASTE150(__VA_ARGS__), L)
/** @brief Paste 152 arguments at their boundary.*/
#define P99_PASTE152(...) P00_PASTE152(P99_LAST(__VA_ARGS__), P99_ALLBUTLAST(__VA_ARGS__))
#define P00_PASTE152(L, ...) P99_PASTE2(P99_PASTE151(__VA_ARGS__), L)
/** @brief Paste 153 arguments at their boundary.*/
#define P99_PASTE153(...) P00_PASTE153(P99_LAST(__VA_ARGS__), P99_ALLBUTLAST(__VA_ARGS__))
#define P00_PASTE153(L, ...) P99_PASTE2(P99_PASTE152(__VA_ARGS__), L)
/** @brief Paste 154 arguments at their boundary.*/
#define P99_PASTE154(...) P00_PASTE154(P99_LAST(__VA_ARGS__), P99_ALLBUTLAST(__VA_ARGS__))
#define P00_PASTE154(L, ...) P99_PASTE2(P99_PASTE153(__VA_ARGS__), L)
/** @brief Paste 155 arguments at their boundary.*/
#define P99_PASTE155(...) P00_PASTE155(P99_LAST(__VA_ARGS__), P99_ALLBUTLAST(__VA_ARGS__))
#define P00_PASTE155(L, ...) P99_PASTE2(P99_PASTE154(__VA_ARGS__), L)
/** @brief Paste 156 arguments at their boundary.*/
#define P99_PASTE156(...) P00_PASTE156(P99_LAST(__VA_ARGS__), P99_ALLBUTLAST(__VA_ARGS__))
#define P00_PASTE156(L, ...) P99_PASTE2(P99_PASTE155(__VA_ARGS__), L)
/** @brief Paste 157 arguments at their boundary.*/
#define P99_PASTE157(...) P00_PASTE157(P99_LAST(__VA_ARGS__), P99_ALLBUTLAST(__VA_ARGS__))
#define P00_PASTE157(L, ...) P99_PASTE2(P99_PASTE156(__VA_ARGS__), L)
/** @brief Paste 158 arguments at their boundary.*/
#define P99_PASTE158(...) P00_PASTE158(P99_LAST(__VA_ARGS__), P99_ALLBUTLAST(__VA_ARGS__))
#define P00_PASTE158(L, ...) P99_PASTE2(P99_PASTE157(__VA_ARGS__), L)
/** @brief Paste 3 partial identifiers separated by an underscore.*/
#define P99_PASTID3(...) P00_PASTID3(P99_ALLBUTLAST(__VA_ARGS__), P99_LAST(__VA_ARGS__))
#define P00_PASTID3(S, L) P99_PASTID2(P99_PASTID2(S), L)
/** @brief Paste 4 partial identifiers separated by an underscore.*/
#define P99_PASTID4(...) P00_PASTID4(P99_ALLBUTLAST(__VA_ARGS__), P99_LAST(__VA_ARGS__))
#define P00_PASTID4(S, L) P99_PASTID2(P99_PASTID3(S), L)
/** @brief Paste 5 partial identifiers separated by an underscore.*/
#define P99_PASTID5(...) P00_PASTID5(P99_ALLBUTLAST(__VA_ARGS__), P99_LAST(__VA_ARGS__))
#define P00_PASTID5(S, L) P99_PASTID2(P99_PASTID4(S), L)
/** @brief Paste 6 partial identifiers separated by an underscore.*/
#define P99_PASTID6(...) P00_PASTID6(P99_ALLBUTLAST(__VA_ARGS__), P99_LAST(__VA_ARGS__))
#define P00_PASTID6(S, L) P99_PASTID2(P99_PASTID5(S), L)
/** @brief Paste 7 partial identifiers separated by an underscore.*/
#define P99_PASTID7(...) P00_PASTID7(P99_ALLBUTLAST(__VA_ARGS__), P99_LAST(__VA_ARGS__))
#define P00_PASTID7(S, L) P99_PASTID2(P99_PASTID6(S), L)
/** @brief Paste 8 partial identifiers separated by an underscore.*/
#define P99_PASTID8(...) P00_PASTID8(P99_ALLBUTLAST(__VA_ARGS__), P99_LAST(__VA_ARGS__))
#define P00_PASTID8(S, L) P99_PASTID2(P99_PASTID7(S), L)
/** @brief Paste 9 partial identifiers separated by an underscore.*/
#define P99_PASTID9(...) P00_PASTID9(P99_ALLBUTLAST(__VA_ARGS__), P99_LAST(__VA_ARGS__))
#define P00_PASTID9(S, L) P99_PASTID2(P99_PASTID8(S), L)
/** @brief Paste 10 partial identifiers separated by an underscore.*/
#define P99_PASTID10(...) P00_PASTID10(P99_ALLBUTLAST(__VA_ARGS__), P99_LAST(__VA_ARGS__))
#define P00_PASTID10(S, L) P99_PASTID2(P99_PASTID9(S), L)
/** @brief Paste 11 partial identifiers separated by an underscore.*/
#define P99_PASTID11(...) P00_PASTID11(P99_ALLBUTLAST(__VA_ARGS__), P99_LAST(__VA_ARGS__))
#define P00_PASTID11(S, L) P99_PASTID2(P99_PASTID10(S), L)
/** @brief Paste 12 partial identifiers separated by an underscore.*/
#define P99_PASTID12(...) P00_PASTID12(P99_ALLBUTLAST(__VA_ARGS__), P99_LAST(__VA_ARGS__))
#define P00_PASTID12(S, L) P99_PASTID2(P99_PASTID11(S), L)
/** @brief Paste 13 partial identifiers separated by an underscore.*/
#define P99_PASTID13(...) P00_PASTID13(P99_ALLBUTLAST(__VA_ARGS__), P99_LAST(__VA_ARGS__))
#define P00_PASTID13(S, L) P99_PASTID2(P99_PASTID12(S), L)
/** @brief Paste 14 partial identifiers separated by an underscore.*/
#define P99_PASTID14(...) P00_PASTID14(P99_ALLBUTLAST(__VA_ARGS__), P99_LAST(__VA_ARGS__))
#define P00_PASTID14(S, L) P99_PASTID2(P99_PASTID13(S), L)
/** @brief Paste 15 partial identifiers separated by an underscore.*/
#define P99_PASTID15(...) P00_PASTID15(P99_ALLBUTLAST(__VA_ARGS__), P99_LAST(__VA_ARGS__))
#define P00_PASTID15(S, L) P99_PASTID2(P99_PASTID14(S), L)
/** @brief Paste 16 partial identifiers separated by an underscore.*/
#define P99_PASTID16(...) P00_PASTID16(P99_ALLBUTLAST(__VA_ARGS__), P99_LAST(__VA_ARGS__))
#define P00_PASTID16(S, L) P99_PASTID2(P99_PASTID15(S), L)
/** @brief Paste 17 partial identifiers separated by an underscore.*/
#define P99_PASTID17(...) P00_PASTID17(P99_ALLBUTLAST(__VA_ARGS__), P99_LAST(__VA_ARGS__))
#define P00_PASTID17(S, L) P99_PASTID2(P99_PASTID16(S), L)
/** @brief Paste 18 partial identifiers separated by an underscore.*/
#define P99_PASTID18(...) P00_PASTID18(P99_ALLBUTLAST(__VA_ARGS__), P99_LAST(__VA_ARGS__))
#define P00_PASTID18(S, L) P99_PASTID2(P99_PASTID17(S), L)
/** @brief Paste 19 partial identifiers separated by an underscore.*/
#define P99_PASTID19(...) P00_PASTID19(P99_ALLBUTLAST(__VA_ARGS__), P99_LAST(__VA_ARGS__))
#define P00_PASTID19(S, L) P99_PASTID2(P99_PASTID18(S), L)
/** @brief Paste 20 partial identifiers separated by an underscore.*/
#define P99_PASTID20(...) P00_PASTID20(P99_ALLBUTLAST(__VA_ARGS__), P99_LAST(__VA_ARGS__))
#define P00_PASTID20(S, L) P99_PASTID2(P99_PASTID19(S), L)
/** @brief Paste 21 partial identifiers separated by an underscore.*/
#define P99_PASTID21(...) P00_PASTID21(P99_ALLBUTLAST(__VA_ARGS__), P99_LAST(__VA_ARGS__))
#define P00_PASTID21(S, L) P99_PASTID2(P99_PASTID20(S), L)
/** @brief Paste 22 partial identifiers separated by an underscore.*/
#define P99_PASTID22(...) P00_PASTID22(P99_ALLBUTLAST(__VA_ARGS__), P99_LAST(__VA_ARGS__))
#define P00_PASTID22(S, L) P99_PASTID2(P99_PASTID21(S), L)
/** @brief Paste 23 partial identifiers separated by an underscore.*/
#define P99_PASTID23(...) P00_PASTID23(P99_ALLBUTLAST(__VA_ARGS__), P99_LAST(__VA_ARGS__))
#define P00_PASTID23(S, L) P99_PASTID2(P99_PASTID22(S), L)
/** @brief Paste 24 partial identifiers separated by an underscore.*/
#define P99_PASTID24(...) P00_PASTID24(P99_ALLBUTLAST(__VA_ARGS__), P99_LAST(__VA_ARGS__))
#define P00_PASTID24(S, L) P99_PASTID2(P99_PASTID23(S), L)
/** @brief Paste 25 partial identifiers separated by an underscore.*/
#define P99_PASTID25(...) P00_PASTID25(P99_ALLBUTLAST(__VA_ARGS__), P99_LAST(__VA_ARGS__))
#define P00_PASTID25(S, L) P99_PASTID2(P99_PASTID24(S), L)
/** @brief Paste 26 partial identifiers separated by an underscore.*/
#define P99_PASTID26(...) P00_PASTID26(P99_ALLBUTLAST(__VA_ARGS__), P99_LAST(__VA_ARGS__))
#define P00_PASTID26(S, L) P99_PASTID2(P99_PASTID25(S), L)
/** @brief Paste 27 partial identifiers separated by an underscore.*/
#define P99_PASTID27(...) P00_PASTID27(P99_ALLBUTLAST(__VA_ARGS__), P99_LAST(__VA_ARGS__))
#define P00_PASTID27(S, L) P99_PASTID2(P99_PASTID26(S), L)
/** @brief Paste 28 partial identifiers separated by an underscore.*/
#define P99_PASTID28(...) P00_PASTID28(P99_ALLBUTLAST(__VA_ARGS__), P99_LAST(__VA_ARGS__))
#define P00_PASTID28(S, L) P99_PASTID2(P99_PASTID27(S), L)
/** @brief Paste 29 partial identifiers separated by an underscore.*/
#define P99_PASTID29(...) P00_PASTID29(P99_ALLBUTLAST(__VA_ARGS__), P99_LAST(__VA_ARGS__))
#define P00_PASTID29(S, L) P99_PASTID2(P99_PASTID28(S), L)
/** @brief Paste 30 partial identifiers separated by an underscore.*/
#define P99_PASTID30(...) P00_PASTID30(P99_ALLBUTLAST(__VA_ARGS__), P99_LAST(__VA_ARGS__))
#define P00_PASTID30(S, L) P99_PASTID2(P99_PASTID29(S), L)
/** @brief Paste 31 partial identifiers separated by an underscore.*/
#define P99_PASTID31(...) P00_PASTID31(P99_ALLBUTLAST(__VA_ARGS__), P99_LAST(__VA_ARGS__))
#define P00_PASTID31(S, L) P99_PASTID2(P99_PASTID30(S), L)
/** @brief Paste 32 partial identifiers separated by an underscore.*/
#define P99_PASTID32(...) P00_PASTID32(P99_ALLBUTLAST(__VA_ARGS__), P99_LAST(__VA_ARGS__))
#define P00_PASTID32(S, L) P99_PASTID2(P99_PASTID31(S), L)
/** @brief Paste 33 partial identifiers separated by an underscore.*/
#define P99_PASTID33(...) P00_PASTID33(P99_ALLBUTLAST(__VA_ARGS__), P99_LAST(__VA_ARGS__))
#define P00_PASTID33(S, L) P99_PASTID2(P99_PASTID32(S), L)
/** @brief Paste 34 partial identifiers separated by an underscore.*/
#define P99_PASTID34(...) P00_PASTID34(P99_ALLBUTLAST(__VA_ARGS__), P99_LAST(__VA_ARGS__))
#define P00_PASTID34(S, L) P99_PASTID2(P99_PASTID33(S), L)
/** @brief Paste 35 partial identifiers separated by an underscore.*/
#define P99_PASTID35(...) P00_PASTID35(P99_ALLBUTLAST(__VA_ARGS__), P99_LAST(__VA_ARGS__))
#define P00_PASTID35(S, L) P99_PASTID2(P99_PASTID34(S), L)
/** @brief Paste 36 partial identifiers separated by an underscore.*/
#define P99_PASTID36(...) P00_PASTID36(P99_ALLBUTLAST(__VA_ARGS__), P99_LAST(__VA_ARGS__))
#define P00_PASTID36(S, L) P99_PASTID2(P99_PASTID35(S), L)
/** @brief Paste 37 partial identifiers separated by an underscore.*/
#define P99_PASTID37(...) P00_PASTID37(P99_ALLBUTLAST(__VA_ARGS__), P99_LAST(__VA_ARGS__))
#define P00_PASTID37(S, L) P99_PASTID2(P99_PASTID36(S), L)
/** @brief Paste 38 partial identifiers separated by an underscore.*/
#define P99_PASTID38(...) P00_PASTID38(P99_ALLBUTLAST(__VA_ARGS__), P99_LAST(__VA_ARGS__))
#define P00_PASTID38(S, L) P99_PASTID2(P99_PASTID37(S), L)
/** @brief Paste 39 partial identifiers separated by an underscore.*/
#define P99_PASTID39(...) P00_PASTID39(P99_ALLBUTLAST(__VA_ARGS__), P99_LAST(__VA_ARGS__))
#define P00_PASTID39(S, L) P99_PASTID2(P99_PASTID38(S), L)
/** @brief Paste 40 partial identifiers separated by an underscore.*/
#define P99_PASTID40(...) P00_PASTID40(P99_ALLBUTLAST(__VA_ARGS__), P99_LAST(__VA_ARGS__))
#define P00_PASTID40(S, L) P99_PASTID2(P99_PASTID39(S), L)
/** @brief Paste 41 partial identifiers separated by an underscore.*/
#define P99_PASTID41(...) P00_PASTID41(P99_ALLBUTLAST(__VA_ARGS__), P99_LAST(__VA_ARGS__))
#define P00_PASTID41(S, L) P99_PASTID2(P99_PASTID40(S), L)
/** @brief Paste 42 partial identifiers separated by an underscore.*/
#define P99_PASTID42(...) P00_PASTID42(P99_ALLBUTLAST(__VA_ARGS__), P99_LAST(__VA_ARGS__))
#define P00_PASTID42(S, L) P99_PASTID2(P99_PASTID41(S), L)
/** @brief Paste 43 partial identifiers separated by an underscore.*/
#define P99_PASTID43(...) P00_PASTID43(P99_ALLBUTLAST(__VA_ARGS__), P99_LAST(__VA_ARGS__))
#define P00_PASTID43(S, L) P99_PASTID2(P99_PASTID42(S), L)
/** @brief Paste 44 partial identifiers separated by an underscore.*/
#define P99_PASTID44(...) P00_PASTID44(P99_ALLBUTLAST(__VA_ARGS__), P99_LAST(__VA_ARGS__))
#define P00_PASTID44(S, L) P99_PASTID2(P99_PASTID43(S), L)
/** @brief Paste 45 partial identifiers separated by an underscore.*/
#define P99_PASTID45(...) P00_PASTID45(P99_ALLBUTLAST(__VA_ARGS__), P99_LAST(__VA_ARGS__))
#define P00_PASTID45(S, L) P99_PASTID2(P99_PASTID44(S), L)
/** @brief Paste 46 partial identifiers separated by an underscore.*/
#define P99_PASTID46(...) P00_PASTID46(P99_ALLBUTLAST(__VA_ARGS__), P99_LAST(__VA_ARGS__))
#define P00_PASTID46(S, L) P99_PASTID2(P99_PASTID45(S), L)
/** @brief Paste 47 partial identifiers separated by an underscore.*/
#define P99_PASTID47(...) P00_PASTID47(P99_ALLBUTLAST(__VA_ARGS__), P99_LAST(__VA_ARGS__))
#define P00_PASTID47(S, L) P99_PASTID2(P99_PASTID46(S), L)
/** @brief Paste 48 partial identifiers separated by an underscore.*/
#define P99_PASTID48(...) P00_PASTID48(P99_ALLBUTLAST(__VA_ARGS__), P99_LAST(__VA_ARGS__))
#define P00_PASTID48(S, L) P99_PASTID2(P99_PASTID47(S), L)
/** @brief Paste 49 partial identifiers separated by an underscore.*/
#define P99_PASTID49(...) P00_PASTID49(P99_ALLBUTLAST(__VA_ARGS__), P99_LAST(__VA_ARGS__))
#define P00_PASTID49(S, L) P99_PASTID2(P99_PASTID48(S), L)
/** @brief Paste 50 partial identifiers separated by an underscore.*/
#define P99_PASTID50(...) P00_PASTID50(P99_ALLBUTLAST(__VA_ARGS__), P99_LAST(__VA_ARGS__))
#define P00_PASTID50(S, L) P99_PASTID2(P99_PASTID49(S), L)
/** @brief Paste 51 partial identifiers separated by an underscore.*/
#define P99_PASTID51(...) P00_PASTID51(P99_ALLBUTLAST(__VA_ARGS__), P99_LAST(__VA_ARGS__))
#define P00_PASTID51(S, L) P99_PASTID2(P99_PASTID50(S), L)
/** @brief Paste 52 partial identifiers separated by an underscore.*/
#define P99_PASTID52(...) P00_PASTID52(P99_ALLBUTLAST(__VA_ARGS__), P99_LAST(__VA_ARGS__))
#define P00_PASTID52(S, L) P99_PASTID2(P99_PASTID51(S), L)
/** @brief Paste 53 partial identifiers separated by an underscore.*/
#define P99_PASTID53(...) P00_PASTID53(P99_ALLBUTLAST(__VA_ARGS__), P99_LAST(__VA_ARGS__))
#define P00_PASTID53(S, L) P99_PASTID2(P99_PASTID52(S), L)
/** @brief Paste 54 partial identifiers separated by an underscore.*/
#define P99_PASTID54(...) P00_PASTID54(P99_ALLBUTLAST(__VA_ARGS__), P99_LAST(__VA_ARGS__))
#define P00_PASTID54(S, L) P99_PASTID2(P99_PASTID53(S), L)
/** @brief Paste 55 partial identifiers separated by an underscore.*/
#define P99_PASTID55(...) P00_PASTID55(P99_ALLBUTLAST(__VA_ARGS__), P99_LAST(__VA_ARGS__))
#define P00_PASTID55(S, L) P99_PASTID2(P99_PASTID54(S), L)
/** @brief Paste 56 partial identifiers separated by an underscore.*/
#define P99_PASTID56(...) P00_PASTID56(P99_ALLBUTLAST(__VA_ARGS__), P99_LAST(__VA_ARGS__))
#define P00_PASTID56(S, L) P99_PASTID2(P99_PASTID55(S), L)
/** @brief Paste 57 partial identifiers separated by an underscore.*/
#define P99_PASTID57(...) P00_PASTID57(P99_ALLBUTLAST(__VA_ARGS__), P99_LAST(__VA_ARGS__))
#define P00_PASTID57(S, L) P99_PASTID2(P99_PASTID56(S), L)
/** @brief Paste 58 partial identifiers separated by an underscore.*/
#define P99_PASTID58(...) P00_PASTID58(P99_ALLBUTLAST(__VA_ARGS__), P99_LAST(__VA_ARGS__))
#define P00_PASTID58(S, L) P99_PASTID2(P99_PASTID57(S), L)
/** @brief Paste 59 partial identifiers separated by an underscore.*/
#define P99_PASTID59(...) P00_PASTID59(P99_ALLBUTLAST(__VA_ARGS__), P99_LAST(__VA_ARGS__))
#define P00_PASTID59(S, L) P99_PASTID2(P99_PASTID58(S), L)
/** @brief Paste 60 partial identifiers separated by an underscore.*/
#define P99_PASTID60(...) P00_PASTID60(P99_ALLBUTLAST(__VA_ARGS__), P99_LAST(__VA_ARGS__))
#define P00_PASTID60(S, L) P99_PASTID2(P99_PASTID59(S), L)
/** @brief Paste 61 partial identifiers separated by an underscore.*/
#define P99_PASTID61(...) P00_PASTID61(P99_ALLBUTLAST(__VA_ARGS__), P99_LAST(__VA_ARGS__))
#define P00_PASTID61(S, L) P99_PASTID2(P99_PASTID60(S), L)
/** @brief Paste 62 partial identifiers separated by an underscore.*/
#define P99_PASTID62(...) P00_PASTID62(P99_ALLBUTLAST(__VA_ARGS__), P99_LAST(__VA_ARGS__))
#define P00_PASTID62(S, L) P99_PASTID2(P99_PASTID61(S), L)
/** @brief Paste 63 partial identifiers separated by an underscore.*/
#define P99_PASTID63(...) P00_PASTID63(P99_ALLBUTLAST(__VA_ARGS__), P99_LAST(__VA_ARGS__))
#define P00_PASTID63(S, L) P99_PASTID2(P99_PASTID62(S), L)
/** @brief Paste 64 partial identifiers separated by an underscore.*/
#define P99_PASTID64(...) P00_PASTID64(P99_ALLBUTLAST(__VA_ARGS__), P99_LAST(__VA_ARGS__))
#define P00_PASTID64(S, L) P99_PASTID2(P99_PASTID63(S), L)
/** @brief Paste 65 partial identifiers separated by an underscore.*/
#define P99_PASTID65(...) P00_PASTID65(P99_ALLBUTLAST(__VA_ARGS__), P99_LAST(__VA_ARGS__))
#define P00_PASTID65(S, L) P99_PASTID2(P99_PASTID64(S), L)
/** @brief Paste 66 partial identifiers separated by an underscore.*/
#define P99_PASTID66(...) P00_PASTID66(P99_ALLBUTLAST(__VA_ARGS__), P99_LAST(__VA_ARGS__))
#define P00_PASTID66(S, L) P99_PASTID2(P99_PASTID65(S), L)
/** @brief Paste 67 partial identifiers separated by an underscore.*/
#define P99_PASTID67(...) P00_PASTID67(P99_ALLBUTLAST(__VA_ARGS__), P99_LAST(__VA_ARGS__))
#define P00_PASTID67(S, L) P99_PASTID2(P99_PASTID66(S), L)
/** @brief Paste 68 partial identifiers separated by an underscore.*/
#define P99_PASTID68(...) P00_PASTID68(P99_ALLBUTLAST(__VA_ARGS__), P99_LAST(__VA_ARGS__))
#define P00_PASTID68(S, L) P99_PASTID2(P99_PASTID67(S), L)
/** @brief Paste 69 partial identifiers separated by an underscore.*/
#define P99_PASTID69(...) P00_PASTID69(P99_ALLBUTLAST(__VA_ARGS__), P99_LAST(__VA_ARGS__))
#define P00_PASTID69(S, L) P99_PASTID2(P99_PASTID68(S), L)
/** @brief Paste 70 partial identifiers separated by an underscore.*/
#define P99_PASTID70(...) P00_PASTID70(P99_ALLBUTLAST(__VA_ARGS__), P99_LAST(__VA_ARGS__))
#define P00_PASTID70(S, L) P99_PASTID2(P99_PASTID69(S), L)
/** @brief Paste 71 partial identifiers separated by an underscore.*/
#define P99_PASTID71(...) P00_PASTID71(P99_ALLBUTLAST(__VA_ARGS__), P99_LAST(__VA_ARGS__))
#define P00_PASTID71(S, L) P99_PASTID2(P99_PASTID70(S), L)
/** @brief Paste 72 partial identifiers separated by an underscore.*/
#define P99_PASTID72(...) P00_PASTID72(P99_ALLBUTLAST(__VA_ARGS__), P99_LAST(__VA_ARGS__))
#define P00_PASTID72(S, L) P99_PASTID2(P99_PASTID71(S), L)
/** @brief Paste 73 partial identifiers separated by an underscore.*/
#define P99_PASTID73(...) P00_PASTID73(P99_ALLBUTLAST(__VA_ARGS__), P99_LAST(__VA_ARGS__))
#define P00_PASTID73(S, L) P99_PASTID2(P99_PASTID72(S), L)
/** @brief Paste 74 partial identifiers separated by an underscore.*/
#define P99_PASTID74(...) P00_PASTID74(P99_ALLBUTLAST(__VA_ARGS__), P99_LAST(__VA_ARGS__))
#define P00_PASTID74(S, L) P99_PASTID2(P99_PASTID73(S), L)
/** @brief Paste 75 partial identifiers separated by an underscore.*/
#define P99_PASTID75(...) P00_PASTID75(P99_ALLBUTLAST(__VA_ARGS__), P99_LAST(__VA_ARGS__))
#define P00_PASTID75(S, L) P99_PASTID2(P99_PASTID74(S), L)
/** @brief Paste 76 partial identifiers separated by an underscore.*/
#define P99_PASTID76(...) P00_PASTID76(P99_ALLBUTLAST(__VA_ARGS__), P99_LAST(__VA_ARGS__))
#define P00_PASTID76(S, L) P99_PASTID2(P99_PASTID75(S), L)
/** @brief Paste 77 partial identifiers separated by an underscore.*/
#define P99_PASTID77(...) P00_PASTID77(P99_ALLBUTLAST(__VA_ARGS__), P99_LAST(__VA_ARGS__))
#define P00_PASTID77(S, L) P99_PASTID2(P99_PASTID76(S), L)
/** @brief Paste 78 partial identifiers separated by an underscore.*/
#define P99_PASTID78(...) P00_PASTID78(P99_ALLBUTLAST(__VA_ARGS__), P99_LAST(__VA_ARGS__))
#define P00_PASTID78(S, L) P99_PASTID2(P99_PASTID77(S), L)
/** @brief Paste 79 partial identifiers separated by an underscore.*/
#define P99_PASTID79(...) P00_PASTID79(P99_ALLBUTLAST(__VA_ARGS__), P99_LAST(__VA_ARGS__))
#define P00_PASTID79(S, L) P99_PASTID2(P99_PASTID78(S), L)
/** @brief Paste 80 partial identifiers separated by an underscore.*/
#define P99_PASTID80(...) P00_PASTID80(P99_ALLBUTLAST(__VA_ARGS__), P99_LAST(__VA_ARGS__))
#define P00_PASTID80(S, L) P99_PASTID2(P99_PASTID79(S), L)
/** @brief Paste 81 partial identifiers separated by an underscore.*/
#define P99_PASTID81(...) P00_PASTID81(P99_ALLBUTLAST(__VA_ARGS__), P99_LAST(__VA_ARGS__))
#define P00_PASTID81(S, L) P99_PASTID2(P99_PASTID80(S), L)
/** @brief Paste 82 partial identifiers separated by an underscore.*/
#define P99_PASTID82(...) P00_PASTID82(P99_ALLBUTLAST(__VA_ARGS__), P99_LAST(__VA_ARGS__))
#define P00_PASTID82(S, L) P99_PASTID2(P99_PASTID81(S), L)
/** @brief Paste 83 partial identifiers separated by an underscore.*/
#define P99_PASTID83(...) P00_PASTID83(P99_ALLBUTLAST(__VA_ARGS__), P99_LAST(__VA_ARGS__))
#define P00_PASTID83(S, L) P99_PASTID2(P99_PASTID82(S), L)
/** @brief Paste 84 partial identifiers separated by an underscore.*/
#define P99_PASTID84(...) P00_PASTID84(P99_ALLBUTLAST(__VA_ARGS__), P99_LAST(__VA_ARGS__))
#define P00_PASTID84(S, L) P99_PASTID2(P99_PASTID83(S), L)
/** @brief Paste 85 partial identifiers separated by an underscore.*/
#define P99_PASTID85(...) P00_PASTID85(P99_ALLBUTLAST(__VA_ARGS__), P99_LAST(__VA_ARGS__))
#define P00_PASTID85(S, L) P99_PASTID2(P99_PASTID84(S), L)
/** @brief Paste 86 partial identifiers separated by an underscore.*/
#define P99_PASTID86(...) P00_PASTID86(P99_ALLBUTLAST(__VA_ARGS__), P99_LAST(__VA_ARGS__))
#define P00_PASTID86(S, L) P99_PASTID2(P99_PASTID85(S), L)
/** @brief Paste 87 partial identifiers separated by an underscore.*/
#define P99_PASTID87(...) P00_PASTID87(P99_ALLBUTLAST(__VA_ARGS__), P99_LAST(__VA_ARGS__))
#define P00_PASTID87(S, L) P99_PASTID2(P99_PASTID86(S), L)
/** @brief Paste 88 partial identifiers separated by an underscore.*/
#define P99_PASTID88(...) P00_PASTID88(P99_ALLBUTLAST(__VA_ARGS__), P99_LAST(__VA_ARGS__))
#define P00_PASTID88(S, L) P99_PASTID2(P99_PASTID87(S), L)
/** @brief Paste 89 partial identifiers separated by an underscore.*/
#define P99_PASTID89(...) P00_PASTID89(P99_ALLBUTLAST(__VA_ARGS__), P99_LAST(__VA_ARGS__))
#define P00_PASTID89(S, L) P99_PASTID2(P99_PASTID88(S), L)
/** @brief Paste 90 partial identifiers separated by an underscore.*/
#define P99_PASTID90(...) P00_PASTID90(P99_ALLBUTLAST(__VA_ARGS__), P99_LAST(__VA_ARGS__))
#define P00_PASTID90(S, L) P99_PASTID2(P99_PASTID89(S), L)
/** @brief Paste 91 partial identifiers separated by an underscore.*/
#define P99_PASTID91(...) P00_PASTID91(P99_ALLBUTLAST(__VA_ARGS__), P99_LAST(__VA_ARGS__))
#define P00_PASTID91(S, L) P99_PASTID2(P99_PASTID90(S), L)
/** @brief Paste 92 partial identifiers separated by an underscore.*/
#define P99_PASTID92(...) P00_PASTID92(P99_ALLBUTLAST(__VA_ARGS__), P99_LAST(__VA_ARGS__))
#define P00_PASTID92(S, L) P99_PASTID2(P99_PASTID91(S), L)
/** @brief Paste 93 partial identifiers separated by an underscore.*/
#define P99_PASTID93(...) P00_PASTID93(P99_ALLBUTLAST(__VA_ARGS__), P99_LAST(__VA_ARGS__))
#define P00_PASTID93(S, L) P99_PASTID2(P99_PASTID92(S), L)
/** @brief Paste 94 partial identifiers separated by an underscore.*/
#define P99_PASTID94(...) P00_PASTID94(P99_ALLBUTLAST(__VA_ARGS__), P99_LAST(__VA_ARGS__))
#define P00_PASTID94(S, L) P99_PASTID2(P99_PASTID93(S), L)
/** @brief Paste 95 partial identifiers separated by an underscore.*/
#define P99_PASTID95(...) P00_PASTID95(P99_ALLBUTLAST(__VA_ARGS__), P99_LAST(__VA_ARGS__))
#define P00_PASTID95(S, L) P99_PASTID2(P99_PASTID94(S), L)
/** @brief Paste 96 partial identifiers separated by an underscore.*/
#define P99_PASTID96(...) P00_PASTID96(P99_ALLBUTLAST(__VA_ARGS__), P99_LAST(__VA_ARGS__))
#define P00_PASTID96(S, L) P99_PASTID2(P99_PASTID95(S), L)
/** @brief Paste 97 partial identifiers separated by an underscore.*/
#define P99_PASTID97(...) P00_PASTID97(P99_ALLBUTLAST(__VA_ARGS__), P99_LAST(__VA_ARGS__))
#define P00_PASTID97(S, L) P99_PASTID2(P99_PASTID96(S), L)
/** @brief Paste 98 partial identifiers separated by an underscore.*/
#define P99_PASTID98(...) P00_PASTID98(P99_ALLBUTLAST(__VA_ARGS__), P99_LAST(__VA_ARGS__))
#define P00_PASTID98(S, L) P99_PASTID2(P99_PASTID97(S), L)
/** @brief Paste 99 partial identifiers separated by an underscore.*/
#define P99_PASTID99(...) P00_PASTID99(P99_ALLBUTLAST(__VA_ARGS__), P99_LAST(__VA_ARGS__))
#define P00_PASTID99(S, L) P99_PASTID2(P99_PASTID98(S), L)
/** @brief Paste 100 partial identifiers separated by an underscore.*/
#define P99_PASTID100(...) P00_PASTID100(P99_ALLBUTLAST(__VA_ARGS__), P99_LAST(__VA_ARGS__))
#define P00_PASTID100(S, L) P99_PASTID2(P99_PASTID99(S), L)
/** @brief Paste 101 partial identifiers separated by an underscore.*/
#define P99_PASTID101(...) P00_PASTID101(P99_ALLBUTLAST(__VA_ARGS__), P99_LAST(__VA_ARGS__))
#define P00_PASTID101(S, L) P99_PASTID2(P99_PASTID100(S), L)
/** @brief Paste 102 partial identifiers separated by an underscore.*/
#define P99_PASTID102(...) P00_PASTID102(P99_ALLBUTLAST(__VA_ARGS__), P99_LAST(__VA_ARGS__))
#define P00_PASTID102(S, L) P99_PASTID2(P99_PASTID101(S), L)
/** @brief Paste 103 partial identifiers separated by an underscore.*/
#define P99_PASTID103(...) P00_PASTID103(P99_ALLBUTLAST(__VA_ARGS__), P99_LAST(__VA_ARGS__))
#define P00_PASTID103(S, L) P99_PASTID2(P99_PASTID102(S), L)
/** @brief Paste 104 partial identifiers separated by an underscore.*/
#define P99_PASTID104(...) P00_PASTID104(P99_ALLBUTLAST(__VA_ARGS__), P99_LAST(__VA_ARGS__))
#define P00_PASTID104(S, L) P99_PASTID2(P99_PASTID103(S), L)
/** @brief Paste 105 partial identifiers separated by an underscore.*/
#define P99_PASTID105(...) P00_PASTID105(P99_ALLBUTLAST(__VA_ARGS__), P99_LAST(__VA_ARGS__))
#define P00_PASTID105(S, L) P99_PASTID2(P99_PASTID104(S), L)
/** @brief Paste 106 partial identifiers separated by an underscore.*/
#define P99_PASTID106(...) P00_PASTID106(P99_ALLBUTLAST(__VA_ARGS__), P99_LAST(__VA_ARGS__))
#define P00_PASTID106(S, L) P99_PASTID2(P99_PASTID105(S), L)
/** @brief Paste 107 partial identifiers separated by an underscore.*/
#define P99_PASTID107(...) P00_PASTID107(P99_ALLBUTLAST(__VA_ARGS__), P99_LAST(__VA_ARGS__))
#define P00_PASTID107(S, L) P99_PASTID2(P99_PASTID106(S), L)
/** @brief Paste 108 partial identifiers separated by an underscore.*/
#define P99_PASTID108(...) P00_PASTID108(P99_ALLBUTLAST(__VA_ARGS__), P99_LAST(__VA_ARGS__))
#define P00_PASTID108(S, L) P99_PASTID2(P99_PASTID107(S), L)
/** @brief Paste 109 partial identifiers separated by an underscore.*/
#define P99_PASTID109(...) P00_PASTID109(P99_ALLBUTLAST(__VA_ARGS__), P99_LAST(__VA_ARGS__))
#define P00_PASTID109(S, L) P99_PASTID2(P99_PASTID108(S), L)
/** @brief Paste 110 partial identifiers separated by an underscore.*/
#define P99_PASTID110(...) P00_PASTID110(P99_ALLBUTLAST(__VA_ARGS__), P99_LAST(__VA_ARGS__))
#define P00_PASTID110(S, L) P99_PASTID2(P99_PASTID109(S), L)
/** @brief Paste 111 partial identifiers separated by an underscore.*/
#define P99_PASTID111(...) P00_PASTID111(P99_ALLBUTLAST(__VA_ARGS__), P99_LAST(__VA_ARGS__))
#define P00_PASTID111(S, L) P99_PASTID2(P99_PASTID110(S), L)
/** @brief Paste 112 partial identifiers separated by an underscore.*/
#define P99_PASTID112(...) P00_PASTID112(P99_ALLBUTLAST(__VA_ARGS__), P99_LAST(__VA_ARGS__))
#define P00_PASTID112(S, L) P99_PASTID2(P99_PASTID111(S), L)
/** @brief Paste 113 partial identifiers separated by an underscore.*/
#define P99_PASTID113(...) P00_PASTID113(P99_ALLBUTLAST(__VA_ARGS__), P99_LAST(__VA_ARGS__))
#define P00_PASTID113(S, L) P99_PASTID2(P99_PASTID112(S), L)
/** @brief Paste 114 partial identifiers separated by an underscore.*/
#define P99_PASTID114(...) P00_PASTID114(P99_ALLBUTLAST(__VA_ARGS__), P99_LAST(__VA_ARGS__))
#define P00_PASTID114(S, L) P99_PASTID2(P99_PASTID113(S), L)
/** @brief Paste 115 partial identifiers separated by an underscore.*/
#define P99_PASTID115(...) P00_PASTID115(P99_ALLBUTLAST(__VA_ARGS__), P99_LAST(__VA_ARGS__))
#define P00_PASTID115(S, L) P99_PASTID2(P99_PASTID114(S), L)
/** @brief Paste 116 partial identifiers separated by an underscore.*/
#define P99_PASTID116(...) P00_PASTID116(P99_ALLBUTLAST(__VA_ARGS__), P99_LAST(__VA_ARGS__))
#define P00_PASTID116(S, L) P99_PASTID2(P99_PASTID115(S), L)
/** @brief Paste 117 partial identifiers separated by an underscore.*/
#define P99_PASTID117(...) P00_PASTID117(P99_ALLBUTLAST(__VA_ARGS__), P99_LAST(__VA_ARGS__))
#define P00_PASTID117(S, L) P99_PASTID2(P99_PASTID116(S), L)
/** @brief Paste 118 partial identifiers separated by an underscore.*/
#define P99_PASTID118(...) P00_PASTID118(P99_ALLBUTLAST(__VA_ARGS__), P99_LAST(__VA_ARGS__))
#define P00_PASTID118(S, L) P99_PASTID2(P99_PASTID117(S), L)
/** @brief Paste 119 partial identifiers separated by an underscore.*/
#define P99_PASTID119(...) P00_PASTID119(P99_ALLBUTLAST(__VA_ARGS__), P99_LAST(__VA_ARGS__))
#define P00_PASTID119(S, L) P99_PASTID2(P99_PASTID118(S), L)
/** @brief Paste 120 partial identifiers separated by an underscore.*/
#define P99_PASTID120(...) P00_PASTID120(P99_ALLBUTLAST(__VA_ARGS__), P99_LAST(__VA_ARGS__))
#define P00_PASTID120(S, L) P99_PASTID2(P99_PASTID119(S), L)
/** @brief Paste 121 partial identifiers separated by an underscore.*/
#define P99_PASTID121(...) P00_PASTID121(P99_ALLBUTLAST(__VA_ARGS__), P99_LAST(__VA_ARGS__))
#define P00_PASTID121(S, L) P99_PASTID2(P99_PASTID120(S), L)
/** @brief Paste 122 partial identifiers separated by an underscore.*/
#define P99_PASTID122(...) P00_PASTID122(P99_ALLBUTLAST(__VA_ARGS__), P99_LAST(__VA_ARGS__))
#define P00_PASTID122(S, L) P99_PASTID2(P99_PASTID121(S), L)
/** @brief Paste 123 partial identifiers separated by an underscore.*/
#define P99_PASTID123(...) P00_PASTID123(P99_ALLBUTLAST(__VA_ARGS__), P99_LAST(__VA_ARGS__))
#define P00_PASTID123(S, L) P99_PASTID2(P99_PASTID122(S), L)
/** @brief Paste 124 partial identifiers separated by an underscore.*/
#define P99_PASTID124(...) P00_PASTID124(P99_ALLBUTLAST(__VA_ARGS__), P99_LAST(__VA_ARGS__))
#define P00_PASTID124(S, L) P99_PASTID2(P99_PASTID123(S), L)
/** @brief Paste 125 partial identifiers separated by an underscore.*/
#define P99_PASTID125(...) P00_PASTID125(P99_ALLBUTLAST(__VA_ARGS__), P99_LAST(__VA_ARGS__))
#define P00_PASTID125(S, L) P99_PASTID2(P99_PASTID124(S), L)
/** @brief Paste 126 partial identifiers separated by an underscore.*/
#define P99_PASTID126(...) P00_PASTID126(P99_ALLBUTLAST(__VA_ARGS__), P99_LAST(__VA_ARGS__))
#define P00_PASTID126(S, L) P99_PASTID2(P99_PASTID125(S), L)
/** @brief Paste 127 partial identifiers separated by an underscore.*/
#define P99_PASTID127(...) P00_PASTID127(P99_ALLBUTLAST(__VA_ARGS__), P99_LAST(__VA_ARGS__))
#define P00_PASTID127(S, L) P99_PASTID2(P99_PASTID126(S), L)
/** @brief Paste 128 partial identifiers separated by an underscore.*/
#define P99_PASTID128(...) P00_PASTID128(P99_ALLBUTLAST(__VA_ARGS__), P99_LAST(__VA_ARGS__))
#define P00_PASTID128(S, L) P99_PASTID2(P99_PASTID127(S), L)
/** @brief Paste 129 partial identifiers separated by an underscore.*/
#define P99_PASTID129(...) P00_PASTID129(P99_ALLBUTLAST(__VA_ARGS__), P99_LAST(__VA_ARGS__))
#define P00_PASTID129(S, L) P99_PASTID2(P99_PASTID128(S), L)
/** @brief Paste 130 partial identifiers separated by an underscore.*/
#define P99_PASTID130(...) P00_PASTID130(P99_ALLBUTLAST(__VA_ARGS__), P99_LAST(__VA_ARGS__))
#define P00_PASTID130(S, L) P99_PASTID2(P99_PASTID129(S), L)
/** @brief Paste 131 partial identifiers separated by an underscore.*/
#define P99_PASTID131(...) P00_PASTID131(P99_ALLBUTLAST(__VA_ARGS__), P99_LAST(__VA_ARGS__))
#define P00_PASTID131(S, L) P99_PASTID2(P99_PASTID130(S), L)
/** @brief Paste 132 partial identifiers separated by an underscore.*/
#define P99_PASTID132(...) P00_PASTID132(P99_ALLBUTLAST(__VA_ARGS__), P99_LAST(__VA_ARGS__))
#define P00_PASTID132(S, L) P99_PASTID2(P99_PASTID131(S), L)
/** @brief Paste 133 partial identifiers separated by an underscore.*/
#define P99_PASTID133(...) P00_PASTID133(P99_ALLBUTLAST(__VA_ARGS__), P99_LAST(__VA_ARGS__))
#define P00_PASTID133(S, L) P99_PASTID2(P99_PASTID132(S), L)
/** @brief Paste 134 partial identifiers separated by an underscore.*/
#define P99_PASTID134(...) P00_PASTID134(P99_ALLBUTLAST(__VA_ARGS__), P99_LAST(__VA_ARGS__))
#define P00_PASTID134(S, L) P99_PASTID2(P99_PASTID133(S), L)
/** @brief Paste 135 partial identifiers separated by an underscore.*/
#define P99_PASTID135(...) P00_PASTID135(P99_ALLBUTLAST(__VA_ARGS__), P99_LAST(__VA_ARGS__))
#define P00_PASTID135(S, L) P99_PASTID2(P99_PASTID134(S), L)
/** @brief Paste 136 partial identifiers separated by an underscore.*/
#define P99_PASTID136(...) P00_PASTID136(P99_ALLBUTLAST(__VA_ARGS__), P99_LAST(__VA_ARGS__))
#define P00_PASTID136(S, L) P99_PASTID2(P99_PASTID135(S), L)
/** @brief Paste 137 partial identifiers separated by an underscore.*/
#define P99_PASTID137(...) P00_PASTID137(P99_ALLBUTLAST(__VA_ARGS__), P99_LAST(__VA_ARGS__))
#define P00_PASTID137(S, L) P99_PASTID2(P99_PASTID136(S), L)
/** @brief Paste 138 partial identifiers separated by an underscore.*/
#define P99_PASTID138(...) P00_PASTID138(P99_ALLBUTLAST(__VA_ARGS__), P99_LAST(__VA_ARGS__))
#define P00_PASTID138(S, L) P99_PASTID2(P99_PASTID137(S), L)
/** @brief Paste 139 partial identifiers separated by an underscore.*/
#define P99_PASTID139(...) P00_PASTID139(P99_ALLBUTLAST(__VA_ARGS__), P99_LAST(__VA_ARGS__))
#define P00_PASTID139(S, L) P99_PASTID2(P99_PASTID138(S), L)
/** @brief Paste 140 partial identifiers separated by an underscore.*/
#define P99_PASTID140(...) P00_PASTID140(P99_ALLBUTLAST(__VA_ARGS__), P99_LAST(__VA_ARGS__))
#define P00_PASTID140(S, L) P99_PASTID2(P99_PASTID139(S), L)
/** @brief Paste 141 partial identifiers separated by an underscore.*/
#define P99_PASTID141(...) P00_PASTID141(P99_ALLBUTLAST(__VA_ARGS__), P99_LAST(__VA_ARGS__))
#define P00_PASTID141(S, L) P99_PASTID2(P99_PASTID140(S), L)
/** @brief Paste 142 partial identifiers separated by an underscore.*/
#define P99_PASTID142(...) P00_PASTID142(P99_ALLBUTLAST(__VA_ARGS__), P99_LAST(__VA_ARGS__))
#define P00_PASTID142(S, L) P99_PASTID2(P99_PASTID141(S), L)
/** @brief Paste 143 partial identifiers separated by an underscore.*/
#define P99_PASTID143(...) P00_PASTID143(P99_ALLBUTLAST(__VA_ARGS__), P99_LAST(__VA_ARGS__))
#define P00_PASTID143(S, L) P99_PASTID2(P99_PASTID142(S), L)
/** @brief Paste 144 partial identifiers separated by an underscore.*/
#define P99_PASTID144(...) P00_PASTID144(P99_ALLBUTLAST(__VA_ARGS__), P99_LAST(__VA_ARGS__))
#define P00_PASTID144(S, L) P99_PASTID2(P99_PASTID143(S), L)
/** @brief Paste 145 partial identifiers separated by an underscore.*/
#define P99_PASTID145(...) P00_PASTID145(P99_ALLBUTLAST(__VA_ARGS__), P99_LAST(__VA_ARGS__))
#define P00_PASTID145(S, L) P99_PASTID2(P99_PASTID144(S), L)
/** @brief Paste 146 partial identifiers separated by an underscore.*/
#define P99_PASTID146(...) P00_PASTID146(P99_ALLBUTLAST(__VA_ARGS__), P99_LAST(__VA_ARGS__))
#define P00_PASTID146(S, L) P99_PASTID2(P99_PASTID145(S), L)
/** @brief Paste 147 partial identifiers separated by an underscore.*/
#define P99_PASTID147(...) P00_PASTID147(P99_ALLBUTLAST(__VA_ARGS__), P99_LAST(__VA_ARGS__))
#define P00_PASTID147(S, L) P99_PASTID2(P99_PASTID146(S), L)
/** @brief Paste 148 partial identifiers separated by an underscore.*/
#define P99_PASTID148(...) P00_PASTID148(P99_ALLBUTLAST(__VA_ARGS__), P99_LAST(__VA_ARGS__))
#define P00_PASTID148(S, L) P99_PASTID2(P99_PASTID147(S), L)
/** @brief Paste 149 partial identifiers separated by an underscore.*/
#define P99_PASTID149(...) P00_PASTID149(P99_ALLBUTLAST(__VA_ARGS__), P99_LAST(__VA_ARGS__))
#define P00_PASTID149(S, L) P99_PASTID2(P99_PASTID148(S), L)
/** @brief Paste 150 partial identifiers separated by an underscore.*/
#define P99_PASTID150(...) P00_PASTID150(P99_ALLBUTLAST(__VA_ARGS__), P99_LAST(__VA_ARGS__))
#define P00_PASTID150(S, L) P99_PASTID2(P99_PASTID149(S), L)
/** @brief Paste 151 partial identifiers separated by an underscore.*/
#define P99_PASTID151(...) P00_PASTID151(P99_ALLBUTLAST(__VA_ARGS__), P99_LAST(__VA_ARGS__))
#define P00_PASTID151(S, L) P99_PASTID2(P99_PASTID150(S), L)
/** @brief Paste 152 partial identifiers separated by an underscore.*/
#define P99_PASTID152(...) P00_PASTID152(P99_ALLBUTLAST(__VA_ARGS__), P99_LAST(__VA_ARGS__))
#define P00_PASTID152(S, L) P99_PASTID2(P99_PASTID151(S), L)
/** @brief Paste 153 partial identifiers separated by an underscore.*/
#define P99_PASTID153(...) P00_PASTID153(P99_ALLBUTLAST(__VA_ARGS__), P99_LAST(__VA_ARGS__))
#define P00_PASTID153(S, L) P99_PASTID2(P99_PASTID152(S), L)
/** @brief Paste 154 partial identifiers separated by an underscore.*/
#define P99_PASTID154(...) P00_PASTID154(P99_ALLBUTLAST(__VA_ARGS__), P99_LAST(__VA_ARGS__))
#define P00_PASTID154(S, L) P99_PASTID2(P99_PASTID153(S), L)
/** @brief Paste 155 partial identifiers separated by an underscore.*/
#define P99_PASTID155(...) P00_PASTID155(P99_ALLBUTLAST(__VA_ARGS__), P99_LAST(__VA_ARGS__))
#define P00_PASTID155(S, L) P99_PASTID2(P99_PASTID154(S), L)
/** @brief Paste 156 partial identifiers separated by an underscore.*/
#define P99_PASTID156(...) P00_PASTID156(P99_ALLBUTLAST(__VA_ARGS__), P99_LAST(__VA_ARGS__))
#define P00_PASTID156(S, L) P99_PASTID2(P99_PASTID155(S), L)
/** @brief Paste 157 partial identifiers separated by an underscore.*/
#define P99_PASTID157(...) P00_PASTID157(P99_ALLBUTLAST(__VA_ARGS__), P99_LAST(__VA_ARGS__))
#define P00_PASTID157(S, L) P99_PASTID2(P99_PASTID156(S), L)
/** @brief Paste 158 partial identifiers separated by an underscore.*/
#define P99_PASTID158(...) P00_PASTID158(P99_ALLBUTLAST(__VA_ARGS__), P99_LAST(__VA_ARGS__))
#define P00_PASTID158(S, L) P99_PASTID2(P99_PASTID157(S), L)
/**
 ** @addtogroup preprocessor_text
 **
 ** @brief These macros allow the handling of small texts and tokens.
 **
 ** For the following tokens, the macro ::P99_TOK_EQ will work.
 ** - decimal numbers: 0 ... 159
 ** - keywords:
 **     @c _Bool
 **     @c _Complex
 **     @c _Imaginary
 **     @c auto
 **     @c break
 **     @c case
 **     @c char
 **     @c const
 **     @c continue
 **     @c default
 **     @c do
 **     @c double
 **     @c else
 **     @c enum
 **     @c extern
 **     @c float
 **     @c for
 **     @c goto
 **     @c if
 **     @c inline
 **     @c int
 **     @c long
 **     @c register
 **     @c restrict
 **     @c return
 **     @c short
 **     @c signed
 **     @c sizeof
 **     @c static
 **     @c struct
 **     @c switch
 **     @c typedef
 **     @c union
 **     @c unsigned
 **     @c void
 **     @c volatile
 **     @c while
 ** - typedefs:
 **     @c clock_t
 **     @c div_t
 **     @c double_t
 **     @c fenv_t
 **     @c fexcept_t
 **     @c float_t
 **     @c fpos_t
 **     @c imaxdiv_t
 **     @c int16_t
 **     @c int32_t
 **     @c int64_t
 **     @c int8_t
 **     @c intfast16_t
 **     @c intfast32_t
 **     @c intfast64_t
 **     @c intfast8_t
 **     @c intleast16_t
 **     @c intleast32_t
 **     @c intleast64_t
 **     @c intleast8_t
 **     @c intmax_t
 **     @c intptr_t
 **     @c ldiv_t
 **     @c lldiv_t
 **     @c mbstate_t
 **     @c off_t
 **     @c ptrdiff_t
 **     @c sig_atomic_t
 **     @c size_t
 **     @c ssize_t
 **     @c time_t
 **     @c uint16_t
 **     @c uint32_t
 **     @c uint64_t
 **     @c uint8_t
 **     @c uintfast16_t
 **     @c uintfast32_t
 **     @c uintfast64_t
 **     @c uintfast8_t
 **     @c uintleast16_t
 **     @c uintleast32_t
 **     @c uintleast64_t
 **     @c uintleast8_t
 **     @c uintmax_t
 **     @c uintptr_t
 **     @c wchar_t
 **     @c wctrans_t
 **     @c wctype_t
 **     @c wint_t
 ** - functions or functional macros:
 **     @c _Exit
 **     @c abort
 **     @c abs
 **     @c acos
 **     @c asctime
 **     @c asin
 **     @c assert
 **     @c atan
 **     @c atan2
 **     @c atexit
 **     @c atof
 **     @c atoi
 **     @c atol
 **     @c bsearch
 **     @c btowc
 **     @c cabs
 **     @c cacos
 **     @c cacosh
 **     @c calloc
 **     @c carg
 **     @c casin
 **     @c casinh
 **     @c catan
 **     @c catanh
 **     @c ccos
 **     @c ccosh
 **     @c ceil
 **     @c cexp
 **     @c cimag
 **     @c clearerr
 **     @c clock
 **     @c clog
 **     @c conj
 **     @c cos
 **     @c cosh
 **     @c cpow
 **     @c cproj
 **     @c creal
 **     @c csin
 **     @c csinh
 **     @c csqrt
 **     @c ctan
 **     @c ctanh
 **     @c ctime
 **     @c difftime
 **     @c div
 **     @c exit
 **     @c exp
 **     @c fabs
 **     @c fclose
 **     @c fdopen
 **     @c feof
 **     @c ferror
 **     @c fflush
 **     @c fgetc
 **     @c fgetpos
 **     @c fgets
 **     @c fgetwc
 **     @c fgetws
 **     @c floor
 **     @c fopen
 **     @c fprintf
 **     @c fputc
 **     @c fputchar
 **     @c fputs
 **     @c fputwc
 **     @c fputws
 **     @c fread
 **     @c free
 **     @c freopen
 **     @c frexp
 **     @c fscanf
 **     @c fseek
 **     @c fsetpos
 **     @c ftell
 **     @c fwide
 **     @c fwprintf
 **     @c fwrite
 **     @c fwscanf
 **     @c getaddrinfo
 **     @c getc
 **     @c getchar
 **     @c getenv
 **     @c getnameinfo
 **     @c gets
 **     @c getwc
 **     @c getwchar
 **     @c gmtime
 **     @c imaxabs
 **     @c imaxdiv
 **     @c isalnum
 **     @c isalpha
 **     @c isblank
 **     @c iscntrl
 **     @c isdigit
 **     @c isgraph
 **     @c islower
 **     @c isprint
 **     @c ispunct
 **     @c isspace
 **     @c isupper
 **     @c iswalnum
 **     @c iswalpha
 **     @c iswcntrl
 **     @c iswctype
 **     @c iswdigit
 **     @c iswgraph
 **     @c iswlower
 **     @c iswprint
 **     @c iswpunct
 **     @c iswspace
 **     @c iswupper
 **     @c iswxdigit
 **     @c isxdigit
 **     @c labs
 **     @c ldexp
 **     @c ldiv
 **     @c localeconv
 **     @c localtime
 **     @c log
 **     @c log10
 **     @c longjmp
 **     @c malloc
 **     @c mbrlen
 **     @c mbrtowc
 **     @c mbsinit
 **     @c mbsrtowcs
 **     @c memchr
 **     @c memcmp
 **     @c memcpy
 **     @c memmove
 **     @c memset
 **     @c mktime
 **     @c modf
 **     @c offsetof
 **     @c perror
 **     @c pow
 **     @c printf
 **     @c putc
 **     @c putchar
 **     @c puts
 **     @c putwc
 **     @c putwchar
 **     @c qsort
 **     @c raise
 **     @c rand
 **     @c realloc
 **     @c remove
 **     @c rename
 **     @c rewind
 **     @c scanf
 **     @c setbuf
 **     @c setjmp
 **     @c setlocale
 **     @c setvbuf
 **     @c sin
 **     @c sinh
 **     @c snprintf
 **     @c sprintf
 **     @c sqrt
 **     @c srand
 **     @c sscanf
 **     @c strcat
 **     @c strchr
 **     @c strcmp
 **     @c strcoll
 **     @c strcpy
 **     @c strcspn
 **     @c strerror
 **     @c strftime
 **     @c strlen
 **     @c strncat
 **     @c strncmp
 **     @c strncpy
 **     @c strpbrk
 **     @c strrchr
 **     @c strspn
 **     @c strstr
 **     @c strtod
 **     @c strtoimax
 **     @c strtok
 **     @c strtol
 **     @c strtoul
 **     @c strtoumax
 **     @c strxfrm
 **     @c swprintf
 **     @c swscanf
 **     @c system
 **     @c tan
 **     @c tanh
 **     @c time
 **     @c tmpfile
 **     @c tmpnam
 **     @c tolower
 **     @c toupper
 **     @c towctrans
 **     @c towlower
 **     @c towupper
 **     @c ungetc
 **     @c ungetwc
 **     @c va_arg
 **     @c va_copy
 **     @c va_end
 **     @c va_start
 **     @c vfprintf
 **     @c vfscanf
 **     @c vfwprintf
 **     @c vprintf
 **     @c vscanf
 **     @c vsprintf
 **     @c vsscanf
 **     @c vswprintf
 **     @c vwprintf
 **     @c wcrtomb
 **     @c wcscat
 **     @c wcschr
 **     @c wcscmp
 **     @c wcscoll
 **     @c wcscpy
 **     @c wcscspn
 **     @c wcsftime
 **     @c wcslen
 **     @c wcsncat
 **     @c wcsncmp
 **     @c wcsncpy
 **     @c wcspbrk
 **     @c wcsrchr
 **     @c wcsrtombs
 **     @c wcsspn
 **     @c wcsstr
 **     @c wcstod
 **     @c wcstoimax
 **     @c wcstok
 **     @c wcstol
 **     @c wcstoul
 **     @c wcstoumax
 **     @c wcsxfrm
 **     @c wctob
 **     @c wctrans
 **     @c wctype
 **     @c wmemchr
 **     @c wmemcmp
 **     @c wmemcpy
 **     @c wmemmove
 **     @c wmemset
 **     @c wprintf
 **     @c wscanf
 **
 ** @warning Non-functional macros cannot be captured by this mechanism since they will
 ** be expanded before we may actually handle them. This concerns in particular
 ** the following tokens that are defined to be macros:
 **     @c NULL
 **     @c and
 **     @c and_eq
 **     @c bitand
 **     @c bitor
 **     @c bool
 **     @c compl
 **     @c false
 **     @c not
 **     @c not_eq
 **     @c offsetof
 **     @c or
 **     @c or_eq
 **     @c true
 **     @c xor
 **     @c xor_eq
 ** @{
 **/
#define P00_IS_0_EQ_0(...) ,
#define P00_IS_1_EQ_1(...) ,
#define P00_IS_2_EQ_2(...) ,
#define P00_IS_3_EQ_3(...) ,
#define P00_IS_4_EQ_4(...) ,
#define P00_IS_5_EQ_5(...) ,
#define P00_IS_6_EQ_6(...) ,
#define P00_IS_7_EQ_7(...) ,
#define P00_IS_8_EQ_8(...) ,
#define P00_IS_9_EQ_9(...) ,
#define P00_IS_10_EQ_10(...) ,
#define P00_IS_11_EQ_11(...) ,
#define P00_IS_12_EQ_12(...) ,
#define P00_IS_13_EQ_13(...) ,
#define P00_IS_14_EQ_14(...) ,
#define P00_IS_15_EQ_15(...) ,
#define P00_IS_16_EQ_16(...) ,
#define P00_IS_17_EQ_17(...) ,
#define P00_IS_18_EQ_18(...) ,
#define P00_IS_19_EQ_19(...) ,
#define P00_IS_20_EQ_20(...) ,
#define P00_IS_21_EQ_21(...) ,
#define P00_IS_22_EQ_22(...) ,
#define P00_IS_23_EQ_23(...) ,
#define P00_IS_24_EQ_24(...) ,
#define P00_IS_25_EQ_25(...) ,
#define P00_IS_26_EQ_26(...) ,
#define P00_IS_27_EQ_27(...) ,
#define P00_IS_28_EQ_28(...) ,
#define P00_IS_29_EQ_29(...) ,
#define P00_IS_30_EQ_30(...) ,
#define P00_IS_31_EQ_31(...) ,
#define P00_IS_32_EQ_32(...) ,
#define P00_IS_33_EQ_33(...) ,
#define P00_IS_34_EQ_34(...) ,
#define P00_IS_35_EQ_35(...) ,
#define P00_IS_36_EQ_36(...) ,
#define P00_IS_37_EQ_37(...) ,
#define P00_IS_38_EQ_38(...) ,
#define P00_IS_39_EQ_39(...) ,
#define P00_IS_40_EQ_40(...) ,
#define P00_IS_41_EQ_41(...) ,
#define P00_IS_42_EQ_42(...) ,
#define P00_IS_43_EQ_43(...) ,
#define P00_IS_44_EQ_44(...) ,
#define P00_IS_45_EQ_45(...) ,
#define P00_IS_46_EQ_46(...) ,
#define P00_IS_47_EQ_47(...) ,
#define P00_IS_48_EQ_48(...) ,
#define P00_IS_49_EQ_49(...) ,
#define P00_IS_50_EQ_50(...) ,
#define P00_IS_51_EQ_51(...) ,
#define P00_IS_52_EQ_52(...) ,
#define P00_IS_53_EQ_53(...) ,
#define P00_IS_54_EQ_54(...) ,
#define P00_IS_55_EQ_55(...) ,
#define P00_IS_56_EQ_56(...) ,
#define P00_IS_57_EQ_57(...) ,
#define P00_IS_58_EQ_58(...) ,
#define P00_IS_59_EQ_59(...) ,
#define P00_IS_60_EQ_60(...) ,
#define P00_IS_61_EQ_61(...) ,
#define P00_IS_62_EQ_62(...) ,
#define P00_IS_63_EQ_63(...) ,
#define P00_IS_64_EQ_64(...) ,
#define P00_IS_65_EQ_65(...) ,
#define P00_IS_66_EQ_66(...) ,
#define P00_IS_67_EQ_67(...) ,
#define P00_IS_68_EQ_68(...) ,
#define P00_IS_69_EQ_69(...) ,
#define P00_IS_70_EQ_70(...) ,
#define P00_IS_71_EQ_71(...) ,
#define P00_IS_72_EQ_72(...) ,
#define P00_IS_73_EQ_73(...) ,
#define P00_IS_74_EQ_74(...) ,
#define P00_IS_75_EQ_75(...) ,
#define P00_IS_76_EQ_76(...) ,
#define P00_IS_77_EQ_77(...) ,
#define P00_IS_78_EQ_78(...) ,
#define P00_IS_79_EQ_79(...) ,
#define P00_IS_80_EQ_80(...) ,
#define P00_IS_81_EQ_81(...) ,
#define P00_IS_82_EQ_82(...) ,
#define P00_IS_83_EQ_83(...) ,
#define P00_IS_84_EQ_84(...) ,
#define P00_IS_85_EQ_85(...) ,
#define P00_IS_86_EQ_86(...) ,
#define P00_IS_87_EQ_87(...) ,
#define P00_IS_88_EQ_88(...) ,
#define P00_IS_89_EQ_89(...) ,
#define P00_IS_90_EQ_90(...) ,
#define P00_IS_91_EQ_91(...) ,
#define P00_IS_92_EQ_92(...) ,
#define P00_IS_93_EQ_93(...) ,
#define P00_IS_94_EQ_94(...) ,
#define P00_IS_95_EQ_95(...) ,
#define P00_IS_96_EQ_96(...) ,
#define P00_IS_97_EQ_97(...) ,
#define P00_IS_98_EQ_98(...) ,
#define P00_IS_99_EQ_99(...) ,
#define P00_IS_100_EQ_100(...) ,
#define P00_IS_101_EQ_101(...) ,
#define P00_IS_102_EQ_102(...) ,
#define P00_IS_103_EQ_103(...) ,
#define P00_IS_104_EQ_104(...) ,
#define P00_IS_105_EQ_105(...) ,
#define P00_IS_106_EQ_106(...) ,
#define P00_IS_107_EQ_107(...) ,
#define P00_IS_108_EQ_108(...) ,
#define P00_IS_109_EQ_109(...) ,
#define P00_IS_110_EQ_110(...) ,
#define P00_IS_111_EQ_111(...) ,
#define P00_IS_112_EQ_112(...) ,
#define P00_IS_113_EQ_113(...) ,
#define P00_IS_114_EQ_114(...) ,
#define P00_IS_115_EQ_115(...) ,
#define P00_IS_116_EQ_116(...) ,
#define P00_IS_117_EQ_117(...) ,
#define P00_IS_118_EQ_118(...) ,
#define P00_IS_119_EQ_119(...) ,
#define P00_IS_120_EQ_120(...) ,
#define P00_IS_121_EQ_121(...) ,
#define P00_IS_122_EQ_122(...) ,
#define P00_IS_123_EQ_123(...) ,
#define P00_IS_124_EQ_124(...) ,
#define P00_IS_125_EQ_125(...) ,
#define P00_IS_126_EQ_126(...) ,
#define P00_IS_127_EQ_127(...) ,
#define P00_IS_128_EQ_128(...) ,
#define P00_IS_129_EQ_129(...) ,
#define P00_IS_130_EQ_130(...) ,
#define P00_IS_131_EQ_131(...) ,
#define P00_IS_132_EQ_132(...) ,
#define P00_IS_133_EQ_133(...) ,
#define P00_IS_134_EQ_134(...) ,
#define P00_IS_135_EQ_135(...) ,
#define P00_IS_136_EQ_136(...) ,
#define P00_IS_137_EQ_137(...) ,
#define P00_IS_138_EQ_138(...) ,
#define P00_IS_139_EQ_139(...) ,
#define P00_IS_140_EQ_140(...) ,
#define P00_IS_141_EQ_141(...) ,
#define P00_IS_142_EQ_142(...) ,
#define P00_IS_143_EQ_143(...) ,
#define P00_IS_144_EQ_144(...) ,
#define P00_IS_145_EQ_145(...) ,
#define P00_IS_146_EQ_146(...) ,
#define P00_IS_147_EQ_147(...) ,
#define P00_IS_148_EQ_148(...) ,
#define P00_IS_149_EQ_149(...) ,
#define P00_IS_150_EQ_150(...) ,
#define P00_IS_151_EQ_151(...) ,
#define P00_IS_152_EQ_152(...) ,
#define P00_IS_153_EQ_153(...) ,
#define P00_IS_154_EQ_154(...) ,
#define P00_IS_155_EQ_155(...) ,
#define P00_IS_156_EQ_156(...) ,
#define P00_IS_157_EQ_157(...) ,
#define P00_IS_158_EQ_158(...) ,
#define P00_IS_159_EQ_159(...) ,
#define P00_IS__Bool_EQ__Bool(...) ,
#define P00_IS__Complex_EQ__Complex(...) ,
#define P00_IS__Exit_EQ__Exit(...) ,
#define P00_IS__Imaginary_EQ__Imaginary(...) ,
#define P00_IS_abort_EQ_abort(...) ,
#define P00_IS_abs_EQ_abs(...) ,
#define P00_IS_acos_EQ_acos(...) ,
#define P00_IS_asctime_EQ_asctime(...) ,
#define P00_IS_asin_EQ_asin(...) ,
#define P00_IS_assert_EQ_assert(...) ,
#define P00_IS_atan_EQ_atan(...) ,
#define P00_IS_atan2_EQ_atan2(...) ,
#define P00_IS_atexit_EQ_atexit(...) ,
#define P00_IS_atof_EQ_atof(...) ,
#define P00_IS_atoi_EQ_atoi(...) ,
#define P00_IS_atol_EQ_atol(...) ,
#define P00_IS_auto_EQ_auto(...) ,
#define P00_IS_break_EQ_break(...) ,
#define P00_IS_bsearch_EQ_bsearch(...) ,
#define P00_IS_btowc_EQ_btowc(...) ,
#define P00_IS_cabs_EQ_cabs(...) ,
#define P00_IS_cacos_EQ_cacos(...) ,
#define P00_IS_cacosh_EQ_cacosh(...) ,
#define P00_IS_calloc_EQ_calloc(...) ,
#define P00_IS_carg_EQ_carg(...) ,
#define P00_IS_case_EQ_case(...) ,
#define P00_IS_casin_EQ_casin(...) ,
#define P00_IS_casinh_EQ_casinh(...) ,
#define P00_IS_catan_EQ_catan(...) ,
#define P00_IS_catanh_EQ_catanh(...) ,
#define P00_IS_ccos_EQ_ccos(...) ,
#define P00_IS_ccosh_EQ_ccosh(...) ,
#define P00_IS_ceil_EQ_ceil(...) ,
#define P00_IS_cexp_EQ_cexp(...) ,
#define P00_IS_char_EQ_char(...) ,
#define P00_IS_cimag_EQ_cimag(...) ,
#define P00_IS_clearerr_EQ_clearerr(...) ,
#define P00_IS_clock_EQ_clock(...) ,
#define P00_IS_clock_t_EQ_clock_t(...) ,
#define P00_IS_clog_EQ_clog(...) ,
#define P00_IS_conj_EQ_conj(...) ,
#define P00_IS_const_EQ_const(...) ,
#define P00_IS_continue_EQ_continue(...) ,
#define P00_IS_cos_EQ_cos(...) ,
#define P00_IS_cosh_EQ_cosh(...) ,
#define P00_IS_cpow_EQ_cpow(...) ,
#define P00_IS_cproj_EQ_cproj(...) ,
#define P00_IS_creal_EQ_creal(...) ,
#define P00_IS_csin_EQ_csin(...) ,
#define P00_IS_csinh_EQ_csinh(...) ,
#define P00_IS_csqrt_EQ_csqrt(...) ,
#define P00_IS_ctan_EQ_ctan(...) ,
#define P00_IS_ctanh_EQ_ctanh(...) ,
#define P00_IS_ctime_EQ_ctime(...) ,
#define P00_IS_default_EQ_default(...) ,
#define P00_IS_difftime_EQ_difftime(...) ,
#define P00_IS_div_EQ_div(...) ,
#define P00_IS_div_t_EQ_div_t(...) ,
#define P00_IS_do_EQ_do(...) ,
#define P00_IS_double_EQ_double(...) ,
#define P00_IS_double_t_EQ_double_t(...) ,
#define P00_IS_else_EQ_else(...) ,
#define P00_IS_enum_EQ_enum(...) ,
#define P00_IS_exit_EQ_exit(...) ,
#define P00_IS_exp_EQ_exp(...) ,
#define P00_IS_extern_EQ_extern(...) ,
#define P00_IS_fabs_EQ_fabs(...) ,
#define P00_IS_fclose_EQ_fclose(...) ,
#define P00_IS_fdopen_EQ_fdopen(...) ,
#define P00_IS_fenv_t_EQ_fenv_t(...) ,
#define P00_IS_feof_EQ_feof(...) ,
#define P00_IS_ferror_EQ_ferror(...) ,
#define P00_IS_fexcept_t_EQ_fexcept_t(...) ,
#define P00_IS_fflush_EQ_fflush(...) ,
#define P00_IS_fgetc_EQ_fgetc(...) ,
#define P00_IS_fgetpos_EQ_fgetpos(...) ,
#define P00_IS_fgets_EQ_fgets(...) ,
#define P00_IS_fgetwc_EQ_fgetwc(...) ,
#define P00_IS_fgetws_EQ_fgetws(...) ,
#define P00_IS_float_EQ_float(...) ,
#define P00_IS_float_t_EQ_float_t(...) ,
#define P00_IS_floor_EQ_floor(...) ,
#define P00_IS_fopen_EQ_fopen(...) ,
#define P00_IS_for_EQ_for(...) ,
#define P00_IS_fpos_t_EQ_fpos_t(...) ,
#define P00_IS_fprintf_EQ_fprintf(...) ,
#define P00_IS_fputc_EQ_fputc(...) ,
#define P00_IS_fputchar_EQ_fputchar(...) ,
#define P00_IS_fputs_EQ_fputs(...) ,
#define P00_IS_fputwc_EQ_fputwc(...) ,
#define P00_IS_fputws_EQ_fputws(...) ,
#define P00_IS_fread_EQ_fread(...) ,
#define P00_IS_free_EQ_free(...) ,
#define P00_IS_freopen_EQ_freopen(...) ,
#define P00_IS_frexp_EQ_frexp(...) ,
#define P00_IS_fscanf_EQ_fscanf(...) ,
#define P00_IS_fseek_EQ_fseek(...) ,
#define P00_IS_fsetpos_EQ_fsetpos(...) ,
#define P00_IS_ftell_EQ_ftell(...) ,
#define P00_IS_fwide_EQ_fwide(...) ,
#define P00_IS_fwprintf_EQ_fwprintf(...) ,
#define P00_IS_fwrite_EQ_fwrite(...) ,
#define P00_IS_fwscanf_EQ_fwscanf(...) ,
#define P00_IS_getaddrinfo_EQ_getaddrinfo(...) ,
#define P00_IS_getc_EQ_getc(...) ,
#define P00_IS_getchar_EQ_getchar(...) ,
#define P00_IS_getenv_EQ_getenv(...) ,
#define P00_IS_getnameinfo_EQ_getnameinfo(...) ,
#define P00_IS_gets_EQ_gets(...) ,
#define P00_IS_getwc_EQ_getwc(...) ,
#define P00_IS_getwchar_EQ_getwchar(...) ,
#define P00_IS_gmtime_EQ_gmtime(...) ,
#define P00_IS_goto_EQ_goto(...) ,
#define P00_IS_if_EQ_if(...) ,
#define P00_IS_imaxabs_EQ_imaxabs(...) ,
#define P00_IS_imaxdiv_EQ_imaxdiv(...) ,
#define P00_IS_imaxdiv_t_EQ_imaxdiv_t(...) ,
#define P00_IS_inline_EQ_inline(...) ,
#define P00_IS_int_EQ_int(...) ,
#define P00_IS_int16_t_EQ_int16_t(...) ,
#define P00_IS_int32_t_EQ_int32_t(...) ,
#define P00_IS_int64_t_EQ_int64_t(...) ,
#define P00_IS_int8_t_EQ_int8_t(...) ,
#define P00_IS_intfast16_t_EQ_intfast16_t(...) ,
#define P00_IS_intfast32_t_EQ_intfast32_t(...) ,
#define P00_IS_intfast64_t_EQ_intfast64_t(...) ,
#define P00_IS_intfast8_t_EQ_intfast8_t(...) ,
#define P00_IS_intleast16_t_EQ_intleast16_t(...) ,
#define P00_IS_intleast32_t_EQ_intleast32_t(...) ,
#define P00_IS_intleast64_t_EQ_intleast64_t(...) ,
#define P00_IS_intleast8_t_EQ_intleast8_t(...) ,
#define P00_IS_intmax_t_EQ_intmax_t(...) ,
#define P00_IS_intptr_t_EQ_intptr_t(...) ,
#define P00_IS_isalnum_EQ_isalnum(...) ,
#define P00_IS_isalpha_EQ_isalpha(...) ,
#define P00_IS_isblank_EQ_isblank(...) ,
#define P00_IS_iscntrl_EQ_iscntrl(...) ,
#define P00_IS_isdigit_EQ_isdigit(...) ,
#define P00_IS_isgraph_EQ_isgraph(...) ,
#define P00_IS_islower_EQ_islower(...) ,
#define P00_IS_isprint_EQ_isprint(...) ,
#define P00_IS_ispunct_EQ_ispunct(...) ,
#define P00_IS_isspace_EQ_isspace(...) ,
#define P00_IS_isupper_EQ_isupper(...) ,
#define P00_IS_iswalnum_EQ_iswalnum(...) ,
#define P00_IS_iswalpha_EQ_iswalpha(...) ,
#define P00_IS_iswcntrl_EQ_iswcntrl(...) ,
#define P00_IS_iswctype_EQ_iswctype(...) ,
#define P00_IS_iswdigit_EQ_iswdigit(...) ,
#define P00_IS_iswgraph_EQ_iswgraph(...) ,
#define P00_IS_iswlower_EQ_iswlower(...) ,
#define P00_IS_iswprint_EQ_iswprint(...) ,
#define P00_IS_iswpunct_EQ_iswpunct(...) ,
#define P00_IS_iswspace_EQ_iswspace(...) ,
#define P00_IS_iswupper_EQ_iswupper(...) ,
#define P00_IS_iswxdigit_EQ_iswxdigit(...) ,
#define P00_IS_isxdigit_EQ_isxdigit(...) ,
#define P00_IS_labs_EQ_labs(...) ,
#define P00_IS_ldexp_EQ_ldexp(...) ,
#define P00_IS_ldiv_EQ_ldiv(...) ,
#define P00_IS_ldiv_t_EQ_ldiv_t(...) ,
#define P00_IS_lldiv_t_EQ_lldiv_t(...) ,
#define P00_IS_localeconv_EQ_localeconv(...) ,
#define P00_IS_localtime_EQ_localtime(...) ,
#define P00_IS_log_EQ_log(...) ,
#define P00_IS_log10_EQ_log10(...) ,
#define P00_IS_long_EQ_long(...) ,
#define P00_IS_longjmp_EQ_longjmp(...) ,
#define P00_IS_malloc_EQ_malloc(...) ,
#define P00_IS_mbrlen_EQ_mbrlen(...) ,
#define P00_IS_mbrtowc_EQ_mbrtowc(...) ,
#define P00_IS_mbsinit_EQ_mbsinit(...) ,
#define P00_IS_mbsrtowcs_EQ_mbsrtowcs(...) ,
#define P00_IS_mbstate_t_EQ_mbstate_t(...) ,
#define P00_IS_memchr_EQ_memchr(...) ,
#define P00_IS_memcmp_EQ_memcmp(...) ,
#define P00_IS_memcpy_EQ_memcpy(...) ,
#define P00_IS_memmove_EQ_memmove(...) ,
#define P00_IS_memset_EQ_memset(...) ,
#define P00_IS_mktime_EQ_mktime(...) ,
#define P00_IS_modf_EQ_modf(...) ,
#define P00_IS_off_t_EQ_off_t(...) ,
#define P00_IS_offsetof_EQ_offsetof(...) ,
#define P00_IS_perror_EQ_perror(...) ,
#define P00_IS_pow_EQ_pow(...) ,
#define P00_IS_printf_EQ_printf(...) ,
#define P00_IS_ptrdiff_t_EQ_ptrdiff_t(...) ,
#define P00_IS_putc_EQ_putc(...) ,
#define P00_IS_putchar_EQ_putchar(...) ,
#define P00_IS_puts_EQ_puts(...) ,
#define P00_IS_putwc_EQ_putwc(...) ,
#define P00_IS_putwchar_EQ_putwchar(...) ,
#define P00_IS_qsort_EQ_qsort(...) ,
#define P00_IS_raise_EQ_raise(...) ,
#define P00_IS_rand_EQ_rand(...) ,
#define P00_IS_realloc_EQ_realloc(...) ,
#define P00_IS_register_EQ_register(...) ,
#define P00_IS_remove_EQ_remove(...) ,
#define P00_IS_rename_EQ_rename(...) ,
#define P00_IS_restrict_EQ_restrict(...) ,
#define P00_IS_return_EQ_return(...) ,
#define P00_IS_rewind_EQ_rewind(...) ,
#define P00_IS_scanf_EQ_scanf(...) ,
#define P00_IS_setbuf_EQ_setbuf(...) ,
#define P00_IS_setjmp_EQ_setjmp(...) ,
#define P00_IS_setlocale_EQ_setlocale(...) ,
#define P00_IS_setvbuf_EQ_setvbuf(...) ,
#define P00_IS_short_EQ_short(...) ,
#define P00_IS_sig_atomic_t_EQ_sig_atomic_t(...) ,
#define P00_IS_signed_EQ_signed(...) ,
#define P00_IS_sin_EQ_sin(...) ,
#define P00_IS_sinh_EQ_sinh(...) ,
#define P00_IS_size_t_EQ_size_t(...) ,
#define P00_IS_sizeof_EQ_sizeof(...) ,
#define P00_IS_snprintf_EQ_snprintf(...) ,
#define P00_IS_sprintf_EQ_sprintf(...) ,
#define P00_IS_sqrt_EQ_sqrt(...) ,
#define P00_IS_srand_EQ_srand(...) ,
#define P00_IS_sscanf_EQ_sscanf(...) ,
#define P00_IS_ssize_t_EQ_ssize_t(...) ,
#define P00_IS_static_EQ_static(...) ,
#define P00_IS_strcat_EQ_strcat(...) ,
#define P00_IS_strchr_EQ_strchr(...) ,
#define P00_IS_strcmp_EQ_strcmp(...) ,
#define P00_IS_strcoll_EQ_strcoll(...) ,
#define P00_IS_strcpy_EQ_strcpy(...) ,
#define P00_IS_strcspn_EQ_strcspn(...) ,
#define P00_IS_strerror_EQ_strerror(...) ,
#define P00_IS_strftime_EQ_strftime(...) ,
#define P00_IS_strlen_EQ_strlen(...) ,
#define P00_IS_strncat_EQ_strncat(...) ,
#define P00_IS_strncmp_EQ_strncmp(...) ,
#define P00_IS_strncpy_EQ_strncpy(...) ,
#define P00_IS_strpbrk_EQ_strpbrk(...) ,
#define P00_IS_strrchr_EQ_strrchr(...) ,
#define P00_IS_strspn_EQ_strspn(...) ,
#define P00_IS_strstr_EQ_strstr(...) ,
#define P00_IS_strtod_EQ_strtod(...) ,
#define P00_IS_strtoimax_EQ_strtoimax(...) ,
#define P00_IS_strtok_EQ_strtok(...) ,
#define P00_IS_strtol_EQ_strtol(...) ,
#define P00_IS_strtoul_EQ_strtoul(...) ,
#define P00_IS_strtoumax_EQ_strtoumax(...) ,
#define P00_IS_struct_EQ_struct(...) ,
#define P00_IS_strxfrm_EQ_strxfrm(...) ,
#define P00_IS_switch_EQ_switch(...) ,
#define P00_IS_swprintf_EQ_swprintf(...) ,
#define P00_IS_swscanf_EQ_swscanf(...) ,
#define P00_IS_system_EQ_system(...) ,
#define P00_IS_tan_EQ_tan(...) ,
#define P00_IS_tanh_EQ_tanh(...) ,
#define P00_IS_time_EQ_time(...) ,
#define P00_IS_time_t_EQ_time_t(...) ,
#define P00_IS_tmpfile_EQ_tmpfile(...) ,
#define P00_IS_tmpnam_EQ_tmpnam(...) ,
#define P00_IS_tolower_EQ_tolower(...) ,
#define P00_IS_toupper_EQ_toupper(...) ,
#define P00_IS_towctrans_EQ_towctrans(...) ,
#define P00_IS_towlower_EQ_towlower(...) ,
#define P00_IS_towupper_EQ_towupper(...) ,
#define P00_IS_typedef_EQ_typedef(...) ,
#define P00_IS_uint16_t_EQ_uint16_t(...) ,
#define P00_IS_uint32_t_EQ_uint32_t(...) ,
#define P00_IS_uint64_t_EQ_uint64_t(...) ,
#define P00_IS_uint8_t_EQ_uint8_t(...) ,
#define P00_IS_uintfast16_t_EQ_uintfast16_t(...) ,
#define P00_IS_uintfast32_t_EQ_uintfast32_t(...) ,
#define P00_IS_uintfast64_t_EQ_uintfast64_t(...) ,
#define P00_IS_uintfast8_t_EQ_uintfast8_t(...) ,
#define P00_IS_uintleast16_t_EQ_uintleast16_t(...) ,
#define P00_IS_uintleast32_t_EQ_uintleast32_t(...) ,
#define P00_IS_uintleast64_t_EQ_uintleast64_t(...) ,
#define P00_IS_uintleast8_t_EQ_uintleast8_t(...) ,
#define P00_IS_uintmax_t_EQ_uintmax_t(...) ,
#define P00_IS_uintptr_t_EQ_uintptr_t(...) ,
#define P00_IS_ungetc_EQ_ungetc(...) ,
#define P00_IS_ungetwc_EQ_ungetwc(...) ,
#define P00_IS_union_EQ_union(...) ,
#define P00_IS_unsigned_EQ_unsigned(...) ,
#define P00_IS_va_arg_EQ_va_arg(...) ,
#define P00_IS_va_copy_EQ_va_copy(...) ,
#define P00_IS_va_end_EQ_va_end(...) ,
#define P00_IS_va_start_EQ_va_start(...) ,
#define P00_IS_vfprintf_EQ_vfprintf(...) ,
#define P00_IS_vfscanf_EQ_vfscanf(...) ,
#define P00_IS_vfwprintf_EQ_vfwprintf(...) ,
#define P00_IS_void_EQ_void(...) ,
#define P00_IS_volatile_EQ_volatile(...) ,
#define P00_IS_vprintf_EQ_vprintf(...) ,
#define P00_IS_vscanf_EQ_vscanf(...) ,
#define P00_IS_vsprintf_EQ_vsprintf(...) ,
#define P00_IS_vsscanf_EQ_vsscanf(...) ,
#define P00_IS_vswprintf_EQ_vswprintf(...) ,
#define P00_IS_vwprintf_EQ_vwprintf(...) ,
#define P00_IS_wchar_t_EQ_wchar_t(...) ,
#define P00_IS_wcrtomb_EQ_wcrtomb(...) ,
#define P00_IS_wcscat_EQ_wcscat(...) ,
#define P00_IS_wcschr_EQ_wcschr(...) ,
#define P00_IS_wcscmp_EQ_wcscmp(...) ,
#define P00_IS_wcscoll_EQ_wcscoll(...) ,
#define P00_IS_wcscpy_EQ_wcscpy(...) ,
#define P00_IS_wcscspn_EQ_wcscspn(...) ,
#define P00_IS_wcsftime_EQ_wcsftime(...) ,
#define P00_IS_wcslen_EQ_wcslen(...) ,
#define P00_IS_wcsncat_EQ_wcsncat(...) ,
#define P00_IS_wcsncmp_EQ_wcsncmp(...) ,
#define P00_IS_wcsncpy_EQ_wcsncpy(...) ,
#define P00_IS_wcspbrk_EQ_wcspbrk(...) ,
#define P00_IS_wcsrchr_EQ_wcsrchr(...) ,
#define P00_IS_wcsrtombs_EQ_wcsrtombs(...) ,
#define P00_IS_wcsspn_EQ_wcsspn(...) ,
#define P00_IS_wcsstr_EQ_wcsstr(...) ,
#define P00_IS_wcstod_EQ_wcstod(...) ,
#define P00_IS_wcstoimax_EQ_wcstoimax(...) ,
#define P00_IS_wcstok_EQ_wcstok(...) ,
#define P00_IS_wcstol_EQ_wcstol(...) ,
#define P00_IS_wcstoul_EQ_wcstoul(...) ,
#define P00_IS_wcstoumax_EQ_wcstoumax(...) ,
#define P00_IS_wcsxfrm_EQ_wcsxfrm(...) ,
#define P00_IS_wctob_EQ_wctob(...) ,
#define P00_IS_wctrans_EQ_wctrans(...) ,
#define P00_IS_wctrans_t_EQ_wctrans_t(...) ,
#define P00_IS_wctype_EQ_wctype(...) ,
#define P00_IS_wctype_t_EQ_wctype_t(...) ,
#define P00_IS_while_EQ_while(...) ,
#define P00_IS_wint_t_EQ_wint_t(...) ,
#define P00_IS_wmemchr_EQ_wmemchr(...) ,
#define P00_IS_wmemcmp_EQ_wmemcmp(...) ,
#define P00_IS_wmemcpy_EQ_wmemcpy(...) ,
#define P00_IS_wmemmove_EQ_wmemmove(...) ,
#define P00_IS_wmemset_EQ_wmemset(...) ,
#define P00_IS_wprintf_EQ_wprintf(...) ,
#define P00_IS_wscanf_EQ_wscanf(...) ,
#define P00_IS_256_EQ_256(...) ,
#define P00_IS_512_EQ_512(...) ,
#define P00_IS_1024_EQ_1024(...) ,
#define P00_IS_2048_EQ_2048(...) ,
#define P00_IS_4096_EQ_4096(...) ,
#define P00_IS_8192_EQ_8192(...) ,
#define P00_IS_16384_EQ_16384(...) ,
#define P00_IS_32768_EQ_32768(...) ,
#define P00_IS_65536_EQ_65536(...) ,
#define P00_IS_131072_EQ_131072(...) ,
#define P00_IS_262144_EQ_262144(...) ,
#define P00_IS_524288_EQ_524288(...) ,
#define P00_IS_1048576_EQ_1048576(...) ,
#define P00_IS_2097152_EQ_2097152(...) ,
#define P00_IS_4194304_EQ_4194304(...) ,
#define P00_IS_8388608_EQ_8388608(...) ,
#define P00_IS_16777216_EQ_16777216(...) ,
#define P00_IS_33554432_EQ_33554432(...) ,
#define P00_IS_67108864_EQ_67108864(...) ,
#define P00_IS_134217728_EQ_134217728(...) ,
#define P00_IS_268435456_EQ_268435456(...) ,
#define P00_IS_536870912_EQ_536870912(...) ,
#define P00_IS_1073741824_EQ_1073741824(...) ,
#define P00_IS_2147483648_EQ_2147483648(...) ,
#define P00_IS_4294967296_EQ_4294967296(...) ,
#define P00_IS_8589934592_EQ_8589934592(...) ,
#define P00_IS_17179869184_EQ_17179869184(...) ,
#define P00_IS_34359738368_EQ_34359738368(...) ,
#define P00_IS_68719476736_EQ_68719476736(...) ,
#define P00_IS_137438953472_EQ_137438953472(...) ,
#define P00_IS_274877906944_EQ_274877906944(...) ,
#define P00_IS_549755813888_EQ_549755813888(...) ,
#define P00_IS_1099511627776_EQ_1099511627776(...) ,
#define P00_IS_2199023255552_EQ_2199023255552(...) ,
#define P00_IS_4398046511104_EQ_4398046511104(...) ,
#define P00_IS_8796093022208_EQ_8796093022208(...) ,
#define P00_IS_17592186044416_EQ_17592186044416(...) ,
#define P00_IS_35184372088832_EQ_35184372088832(...) ,
#define P00_IS_70368744177664_EQ_70368744177664(...) ,
#define P00_IS_140737488355328_EQ_140737488355328(...) ,
#define P00_IS_281474976710656_EQ_281474976710656(...) ,
#define P00_IS_562949953421312_EQ_562949953421312(...) ,
#define P00_IS_1125899906842624_EQ_1125899906842624(...) ,
#define P00_IS_2251799813685248_EQ_2251799813685248(...) ,
#define P00_IS_4503599627370496_EQ_4503599627370496(...) ,
#define P00_IS_9007199254740992_EQ_9007199254740992(...) ,
#define P00_IS_18014398509481984_EQ_18014398509481984(...) ,
#define P00_IS_36028797018963968_EQ_36028797018963968(...) ,
#define P00_IS_72057594037927936_EQ_72057594037927936(...) ,
#define P00_IS_144115188075855872_EQ_144115188075855872(...) ,
#define P00_IS_288230376151711744_EQ_288230376151711744(...) ,
#define P00_IS_576460752303423488_EQ_576460752303423488(...) ,
#define P00_IS_1152921504606846976_EQ_1152921504606846976(...) ,
#define P00_IS_2305843009213693952_EQ_2305843009213693952(...) ,
#define P00_IS_4611686018427387904_EQ_4611686018427387904(...) ,
#define P00_IS_9223372036854775808_EQ_9223372036854775808(...) ,
#define P00_TOK_0_STARTS_0 ,
#define P00_TOK_1_STARTS_1 ,
#define P00_TOK_2_STARTS_2 ,
#define P00_TOK_3_STARTS_3 ,
#define P00_TOK_4_STARTS_4 ,
#define P00_TOK_5_STARTS_5 ,
#define P00_TOK_6_STARTS_6 ,
#define P00_TOK_7_STARTS_7 ,
#define P00_TOK_8_STARTS_8 ,
#define P00_TOK_9_STARTS_9 ,
#define P00_TOK_10_STARTS_10 ,
#define P00_TOK_11_STARTS_11 ,
#define P00_TOK_12_STARTS_12 ,
#define P00_TOK_13_STARTS_13 ,
#define P00_TOK_14_STARTS_14 ,
#define P00_TOK_15_STARTS_15 ,
#define P00_TOK_16_STARTS_16 ,
#define P00_TOK_17_STARTS_17 ,
#define P00_TOK_18_STARTS_18 ,
#define P00_TOK_19_STARTS_19 ,
#define P00_TOK_20_STARTS_20 ,
#define P00_TOK_21_STARTS_21 ,
#define P00_TOK_22_STARTS_22 ,
#define P00_TOK_23_STARTS_23 ,
#define P00_TOK_24_STARTS_24 ,
#define P00_TOK_25_STARTS_25 ,
#define P00_TOK_26_STARTS_26 ,
#define P00_TOK_27_STARTS_27 ,
#define P00_TOK_28_STARTS_28 ,
#define P00_TOK_29_STARTS_29 ,
#define P00_TOK_30_STARTS_30 ,
#define P00_TOK_31_STARTS_31 ,
#define P00_TOK_32_STARTS_32 ,
#define P00_TOK_33_STARTS_33 ,
#define P00_TOK_34_STARTS_34 ,
#define P00_TOK_35_STARTS_35 ,
#define P00_TOK_36_STARTS_36 ,
#define P00_TOK_37_STARTS_37 ,
#define P00_TOK_38_STARTS_38 ,
#define P00_TOK_39_STARTS_39 ,
#define P00_TOK_40_STARTS_40 ,
#define P00_TOK_41_STARTS_41 ,
#define P00_TOK_42_STARTS_42 ,
#define P00_TOK_43_STARTS_43 ,
#define P00_TOK_44_STARTS_44 ,
#define P00_TOK_45_STARTS_45 ,
#define P00_TOK_46_STARTS_46 ,
#define P00_TOK_47_STARTS_47 ,
#define P00_TOK_48_STARTS_48 ,
#define P00_TOK_49_STARTS_49 ,
#define P00_TOK_50_STARTS_50 ,
#define P00_TOK_51_STARTS_51 ,
#define P00_TOK_52_STARTS_52 ,
#define P00_TOK_53_STARTS_53 ,
#define P00_TOK_54_STARTS_54 ,
#define P00_TOK_55_STARTS_55 ,
#define P00_TOK_56_STARTS_56 ,
#define P00_TOK_57_STARTS_57 ,
#define P00_TOK_58_STARTS_58 ,
#define P00_TOK_59_STARTS_59 ,
#define P00_TOK_60_STARTS_60 ,
#define P00_TOK_61_STARTS_61 ,
#define P00_TOK_62_STARTS_62 ,
#define P00_TOK_63_STARTS_63 ,
#define P00_TOK_64_STARTS_64 ,
#define P00_TOK_65_STARTS_65 ,
#define P00_TOK_66_STARTS_66 ,
#define P00_TOK_67_STARTS_67 ,
#define P00_TOK_68_STARTS_68 ,
#define P00_TOK_69_STARTS_69 ,
#define P00_TOK_70_STARTS_70 ,
#define P00_TOK_71_STARTS_71 ,
#define P00_TOK_72_STARTS_72 ,
#define P00_TOK_73_STARTS_73 ,
#define P00_TOK_74_STARTS_74 ,
#define P00_TOK_75_STARTS_75 ,
#define P00_TOK_76_STARTS_76 ,
#define P00_TOK_77_STARTS_77 ,
#define P00_TOK_78_STARTS_78 ,
#define P00_TOK_79_STARTS_79 ,
#define P00_TOK_80_STARTS_80 ,
#define P00_TOK_81_STARTS_81 ,
#define P00_TOK_82_STARTS_82 ,
#define P00_TOK_83_STARTS_83 ,
#define P00_TOK_84_STARTS_84 ,
#define P00_TOK_85_STARTS_85 ,
#define P00_TOK_86_STARTS_86 ,
#define P00_TOK_87_STARTS_87 ,
#define P00_TOK_88_STARTS_88 ,
#define P00_TOK_89_STARTS_89 ,
#define P00_TOK_90_STARTS_90 ,
#define P00_TOK_91_STARTS_91 ,
#define P00_TOK_92_STARTS_92 ,
#define P00_TOK_93_STARTS_93 ,
#define P00_TOK_94_STARTS_94 ,
#define P00_TOK_95_STARTS_95 ,
#define P00_TOK_96_STARTS_96 ,
#define P00_TOK_97_STARTS_97 ,
#define P00_TOK_98_STARTS_98 ,
#define P00_TOK_99_STARTS_99 ,
#define P00_TOK_100_STARTS_100 ,
#define P00_TOK_101_STARTS_101 ,
#define P00_TOK_102_STARTS_102 ,
#define P00_TOK_103_STARTS_103 ,
#define P00_TOK_104_STARTS_104 ,
#define P00_TOK_105_STARTS_105 ,
#define P00_TOK_106_STARTS_106 ,
#define P00_TOK_107_STARTS_107 ,
#define P00_TOK_108_STARTS_108 ,
#define P00_TOK_109_STARTS_109 ,
#define P00_TOK_110_STARTS_110 ,
#define P00_TOK_111_STARTS_111 ,
#define P00_TOK_112_STARTS_112 ,
#define P00_TOK_113_STARTS_113 ,
#define P00_TOK_114_STARTS_114 ,
#define P00_TOK_115_STARTS_115 ,
#define P00_TOK_116_STARTS_116 ,
#define P00_TOK_117_STARTS_117 ,
#define P00_TOK_118_STARTS_118 ,
#define P00_TOK_119_STARTS_119 ,
#define P00_TOK_120_STARTS_120 ,
#define P00_TOK_121_STARTS_121 ,
#define P00_TOK_122_STARTS_122 ,
#define P00_TOK_123_STARTS_123 ,
#define P00_TOK_124_STARTS_124 ,
#define P00_TOK_125_STARTS_125 ,
#define P00_TOK_126_STARTS_126 ,
#define P00_TOK_127_STARTS_127 ,
#define P00_TOK_128_STARTS_128 ,
#define P00_TOK_129_STARTS_129 ,
#define P00_TOK_130_STARTS_130 ,
#define P00_TOK_131_STARTS_131 ,
#define P00_TOK_132_STARTS_132 ,
#define P00_TOK_133_STARTS_133 ,
#define P00_TOK_134_STARTS_134 ,
#define P00_TOK_135_STARTS_135 ,
#define P00_TOK_136_STARTS_136 ,
#define P00_TOK_137_STARTS_137 ,
#define P00_TOK_138_STARTS_138 ,
#define P00_TOK_139_STARTS_139 ,
#define P00_TOK_140_STARTS_140 ,
#define P00_TOK_141_STARTS_141 ,
#define P00_TOK_142_STARTS_142 ,
#define P00_TOK_143_STARTS_143 ,
#define P00_TOK_144_STARTS_144 ,
#define P00_TOK_145_STARTS_145 ,
#define P00_TOK_146_STARTS_146 ,
#define P00_TOK_147_STARTS_147 ,
#define P00_TOK_148_STARTS_148 ,
#define P00_TOK_149_STARTS_149 ,
#define P00_TOK_150_STARTS_150 ,
#define P00_TOK_151_STARTS_151 ,
#define P00_TOK_152_STARTS_152 ,
#define P00_TOK_153_STARTS_153 ,
#define P00_TOK_154_STARTS_154 ,
#define P00_TOK_155_STARTS_155 ,
#define P00_TOK_156_STARTS_156 ,
#define P00_TOK_157_STARTS_157 ,
#define P00_TOK_158_STARTS_158 ,
#define P00_TOK_159_STARTS_159 ,
#define P00_TOK__Bool_STARTS__Bool ,
#define P00_TOK__Complex_STARTS__Complex ,
#define P00_TOK__Exit_STARTS__Exit ,
#define P00_TOK__Imaginary_STARTS__Imaginary ,
#define P00_TOK_abort_STARTS_abort ,
#define P00_TOK_abs_STARTS_abs ,
#define P00_TOK_acos_STARTS_acos ,
#define P00_TOK_asctime_STARTS_asctime ,
#define P00_TOK_asin_STARTS_asin ,
#define P00_TOK_assert_STARTS_assert ,
#define P00_TOK_atan_STARTS_atan ,
#define P00_TOK_atan2_STARTS_atan2 ,
#define P00_TOK_atexit_STARTS_atexit ,
#define P00_TOK_atof_STARTS_atof ,
#define P00_TOK_atoi_STARTS_atoi ,
#define P00_TOK_atol_STARTS_atol ,
#define P00_TOK_auto_STARTS_auto ,
#define P00_TOK_break_STARTS_break ,
#define P00_TOK_bsearch_STARTS_bsearch ,
#define P00_TOK_btowc_STARTS_btowc ,
#define P00_TOK_cabs_STARTS_cabs ,
#define P00_TOK_cacos_STARTS_cacos ,
#define P00_TOK_cacosh_STARTS_cacosh ,
#define P00_TOK_calloc_STARTS_calloc ,
#define P00_TOK_carg_STARTS_carg ,
#define P00_TOK_case_STARTS_case ,
#define P00_TOK_casin_STARTS_casin ,
#define P00_TOK_casinh_STARTS_casinh ,
#define P00_TOK_catan_STARTS_catan ,
#define P00_TOK_catanh_STARTS_catanh ,
#define P00_TOK_ccos_STARTS_ccos ,
#define P00_TOK_ccosh_STARTS_ccosh ,
#define P00_TOK_ceil_STARTS_ceil ,
#define P00_TOK_cexp_STARTS_cexp ,
#define P00_TOK_char_STARTS_char ,
#define P00_TOK_cimag_STARTS_cimag ,
#define P00_TOK_clearerr_STARTS_clearerr ,
#define P00_TOK_clock_STARTS_clock ,
#define P00_TOK_clock_t_STARTS_clock_t ,
#define P00_TOK_clog_STARTS_clog ,
#define P00_TOK_conj_STARTS_conj ,
#define P00_TOK_const_STARTS_const ,
#define P00_TOK_continue_STARTS_continue ,
#define P00_TOK_cos_STARTS_cos ,
#define P00_TOK_cosh_STARTS_cosh ,
#define P00_TOK_cpow_STARTS_cpow ,
#define P00_TOK_cproj_STARTS_cproj ,
#define P00_TOK_creal_STARTS_creal ,
#define P00_TOK_csin_STARTS_csin ,
#define P00_TOK_csinh_STARTS_csinh ,
#define P00_TOK_csqrt_STARTS_csqrt ,
#define P00_TOK_ctan_STARTS_ctan ,
#define P00_TOK_ctanh_STARTS_ctanh ,
#define P00_TOK_ctime_STARTS_ctime ,
#define P00_TOK_default_STARTS_default ,
#define P00_TOK_difftime_STARTS_difftime ,
#define P00_TOK_div_STARTS_div ,
#define P00_TOK_div_t_STARTS_div_t ,
#define P00_TOK_do_STARTS_do ,
#define P00_TOK_double_STARTS_double ,
#define P00_TOK_double_t_STARTS_double_t ,
#define P00_TOK_else_STARTS_else ,
#define P00_TOK_enum_STARTS_enum ,
#define P00_TOK_exit_STARTS_exit ,
#define P00_TOK_exp_STARTS_exp ,
#define P00_TOK_extern_STARTS_extern ,
#define P00_TOK_fabs_STARTS_fabs ,
#define P00_TOK_fclose_STARTS_fclose ,
#define P00_TOK_fdopen_STARTS_fdopen ,
#define P00_TOK_fenv_t_STARTS_fenv_t ,
#define P00_TOK_feof_STARTS_feof ,
#define P00_TOK_ferror_STARTS_ferror ,
#define P00_TOK_fexcept_t_STARTS_fexcept_t ,
#define P00_TOK_fflush_STARTS_fflush ,
#define P00_TOK_fgetc_STARTS_fgetc ,
#define P00_TOK_fgetpos_STARTS_fgetpos ,
#define P00_TOK_fgets_STARTS_fgets ,
#define P00_TOK_fgetwc_STARTS_fgetwc ,
#define P00_TOK_fgetws_STARTS_fgetws ,
#define P00_TOK_float_STARTS_float ,
#define P00_TOK_float_t_STARTS_float_t ,
#define P00_TOK_floor_STARTS_floor ,
#define P00_TOK_fopen_STARTS_fopen ,
#define P00_TOK_for_STARTS_for ,
#define P00_TOK_fpos_t_STARTS_fpos_t ,
#define P00_TOK_fprintf_STARTS_fprintf ,
#define P00_TOK_fputc_STARTS_fputc ,
#define P00_TOK_fputchar_STARTS_fputchar ,
#define P00_TOK_fputs_STARTS_fputs ,
#define P00_TOK_fputwc_STARTS_fputwc ,
#define P00_TOK_fputws_STARTS_fputws ,
#define P00_TOK_fread_STARTS_fread ,
#define P00_TOK_free_STARTS_free ,
#define P00_TOK_freopen_STARTS_freopen ,
#define P00_TOK_frexp_STARTS_frexp ,
#define P00_TOK_fscanf_STARTS_fscanf ,
#define P00_TOK_fseek_STARTS_fseek ,
#define P00_TOK_fsetpos_STARTS_fsetpos ,
#define P00_TOK_ftell_STARTS_ftell ,
#define P00_TOK_fwide_STARTS_fwide ,
#define P00_TOK_fwprintf_STARTS_fwprintf ,
#define P00_TOK_fwrite_STARTS_fwrite ,
#define P00_TOK_fwscanf_STARTS_fwscanf ,
#define P00_TOK_getaddrinfo_STARTS_getaddrinfo ,
#define P00_TOK_getc_STARTS_getc ,
#define P00_TOK_getchar_STARTS_getchar ,
#define P00_TOK_getenv_STARTS_getenv ,
#define P00_TOK_getnameinfo_STARTS_getnameinfo ,
#define P00_TOK_gets_STARTS_gets ,
#define P00_TOK_getwc_STARTS_getwc ,
#define P00_TOK_getwchar_STARTS_getwchar ,
#define P00_TOK_gmtime_STARTS_gmtime ,
#define P00_TOK_goto_STARTS_goto ,
#define P00_TOK_if_STARTS_if ,
#define P00_TOK_imaxabs_STARTS_imaxabs ,
#define P00_TOK_imaxdiv_STARTS_imaxdiv ,
#define P00_TOK_imaxdiv_t_STARTS_imaxdiv_t ,
#define P00_TOK_inline_STARTS_inline ,
#define P00_TOK_int_STARTS_int ,
#define P00_TOK_int16_t_STARTS_int16_t ,
#define P00_TOK_int32_t_STARTS_int32_t ,
#define P00_TOK_int64_t_STARTS_int64_t ,
#define P00_TOK_int8_t_STARTS_int8_t ,
#define P00_TOK_intfast16_t_STARTS_intfast16_t ,
#define P00_TOK_intfast32_t_STARTS_intfast32_t ,
#define P00_TOK_intfast64_t_STARTS_intfast64_t ,
#define P00_TOK_intfast8_t_STARTS_intfast8_t ,
#define P00_TOK_intleast16_t_STARTS_intleast16_t ,
#define P00_TOK_intleast32_t_STARTS_intleast32_t ,
#define P00_TOK_intleast64_t_STARTS_intleast64_t ,
#define P00_TOK_intleast8_t_STARTS_intleast8_t ,
#define P00_TOK_intmax_t_STARTS_intmax_t ,
#define P00_TOK_intptr_t_STARTS_intptr_t ,
#define P00_TOK_isalnum_STARTS_isalnum ,
#define P00_TOK_isalpha_STARTS_isalpha ,
#define P00_TOK_isblank_STARTS_isblank ,
#define P00_TOK_iscntrl_STARTS_iscntrl ,
#define P00_TOK_isdigit_STARTS_isdigit ,
#define P00_TOK_isgraph_STARTS_isgraph ,
#define P00_TOK_islower_STARTS_islower ,
#define P00_TOK_isprint_STARTS_isprint ,
#define P00_TOK_ispunct_STARTS_ispunct ,
#define P00_TOK_isspace_STARTS_isspace ,
#define P00_TOK_isupper_STARTS_isupper ,
#define P00_TOK_iswalnum_STARTS_iswalnum ,
#define P00_TOK_iswalpha_STARTS_iswalpha ,
#define P00_TOK_iswcntrl_STARTS_iswcntrl ,
#define P00_TOK_iswctype_STARTS_iswctype ,
#define P00_TOK_iswdigit_STARTS_iswdigit ,
#define P00_TOK_iswgraph_STARTS_iswgraph ,
#define P00_TOK_iswlower_STARTS_iswlower ,
#define P00_TOK_iswprint_STARTS_iswprint ,
#define P00_TOK_iswpunct_STARTS_iswpunct ,
#define P00_TOK_iswspace_STARTS_iswspace ,
#define P00_TOK_iswupper_STARTS_iswupper ,
#define P00_TOK_iswxdigit_STARTS_iswxdigit ,
#define P00_TOK_isxdigit_STARTS_isxdigit ,
#define P00_TOK_labs_STARTS_labs ,
#define P00_TOK_ldexp_STARTS_ldexp ,
#define P00_TOK_ldiv_STARTS_ldiv ,
#define P00_TOK_ldiv_t_STARTS_ldiv_t ,
#define P00_TOK_lldiv_t_STARTS_lldiv_t ,
#define P00_TOK_localeconv_STARTS_localeconv ,
#define P00_TOK_localtime_STARTS_localtime ,
#define P00_TOK_log_STARTS_log ,
#define P00_TOK_log10_STARTS_log10 ,
#define P00_TOK_long_STARTS_long ,
#define P00_TOK_longjmp_STARTS_longjmp ,
#define P00_TOK_malloc_STARTS_malloc ,
#define P00_TOK_mbrlen_STARTS_mbrlen ,
#define P00_TOK_mbrtowc_STARTS_mbrtowc ,
#define P00_TOK_mbsinit_STARTS_mbsinit ,
#define P00_TOK_mbsrtowcs_STARTS_mbsrtowcs ,
#define P00_TOK_mbstate_t_STARTS_mbstate_t ,
#define P00_TOK_memchr_STARTS_memchr ,
#define P00_TOK_memcmp_STARTS_memcmp ,
#define P00_TOK_memcpy_STARTS_memcpy ,
#define P00_TOK_memmove_STARTS_memmove ,
#define P00_TOK_memset_STARTS_memset ,
#define P00_TOK_mktime_STARTS_mktime ,
#define P00_TOK_modf_STARTS_modf ,
#define P00_TOK_off_t_STARTS_off_t ,
#define P00_TOK_offsetof_STARTS_offsetof ,
#define P00_TOK_perror_STARTS_perror ,
#define P00_TOK_pow_STARTS_pow ,
#define P00_TOK_printf_STARTS_printf ,
#define P00_TOK_ptrdiff_t_STARTS_ptrdiff_t ,
#define P00_TOK_putc_STARTS_putc ,
#define P00_TOK_putchar_STARTS_putchar ,
#define P00_TOK_puts_STARTS_puts ,
#define P00_TOK_putwc_STARTS_putwc ,
#define P00_TOK_putwchar_STARTS_putwchar ,
#define P00_TOK_qsort_STARTS_qsort ,
#define P00_TOK_raise_STARTS_raise ,
#define P00_TOK_rand_STARTS_rand ,
#define P00_TOK_realloc_STARTS_realloc ,
#define P00_TOK_register_STARTS_register ,
#define P00_TOK_remove_STARTS_remove ,
#define P00_TOK_rename_STARTS_rename ,
#define P00_TOK_restrict_STARTS_restrict ,
#define P00_TOK_return_STARTS_return ,
#define P00_TOK_rewind_STARTS_rewind ,
#define P00_TOK_scanf_STARTS_scanf ,
#define P00_TOK_setbuf_STARTS_setbuf ,
#define P00_TOK_setjmp_STARTS_setjmp ,
#define P00_TOK_setlocale_STARTS_setlocale ,
#define P00_TOK_setvbuf_STARTS_setvbuf ,
#define P00_TOK_short_STARTS_short ,
#define P00_TOK_sig_atomic_t_STARTS_sig_atomic_t ,
#define P00_TOK_signed_STARTS_signed ,
#define P00_TOK_sin_STARTS_sin ,
#define P00_TOK_sinh_STARTS_sinh ,
#define P00_TOK_size_t_STARTS_size_t ,
#define P00_TOK_sizeof_STARTS_sizeof ,
#define P00_TOK_snprintf_STARTS_snprintf ,
#define P00_TOK_sprintf_STARTS_sprintf ,
#define P00_TOK_sqrt_STARTS_sqrt ,
#define P00_TOK_srand_STARTS_srand ,
#define P00_TOK_sscanf_STARTS_sscanf ,
#define P00_TOK_ssize_t_STARTS_ssize_t ,
#define P00_TOK_static_STARTS_static ,
#define P00_TOK_strcat_STARTS_strcat ,
#define P00_TOK_strchr_STARTS_strchr ,
#define P00_TOK_strcmp_STARTS_strcmp ,
#define P00_TOK_strcoll_STARTS_strcoll ,
#define P00_TOK_strcpy_STARTS_strcpy ,
#define P00_TOK_strcspn_STARTS_strcspn ,
#define P00_TOK_strerror_STARTS_strerror ,
#define P00_TOK_strftime_STARTS_strftime ,
#define P00_TOK_strlen_STARTS_strlen ,
#define P00_TOK_strncat_STARTS_strncat ,
#define P00_TOK_strncmp_STARTS_strncmp ,
#define P00_TOK_strncpy_STARTS_strncpy ,
#define P00_TOK_strpbrk_STARTS_strpbrk ,
#define P00_TOK_strrchr_STARTS_strrchr ,
#define P00_TOK_strspn_STARTS_strspn ,
#define P00_TOK_strstr_STARTS_strstr ,
#define P00_TOK_strtod_STARTS_strtod ,
#define P00_TOK_strtoimax_STARTS_strtoimax ,
#define P00_TOK_strtok_STARTS_strtok ,
#define P00_TOK_strtol_STARTS_strtol ,
#define P00_TOK_strtoul_STARTS_strtoul ,
#define P00_TOK_strtoumax_STARTS_strtoumax ,
#define P00_TOK_struct_STARTS_struct ,
#define P00_TOK_strxfrm_STARTS_strxfrm ,
#define P00_TOK_switch_STARTS_switch ,
#define P00_TOK_swprintf_STARTS_swprintf ,
#define P00_TOK_swscanf_STARTS_swscanf ,
#define P00_TOK_system_STARTS_system ,
#define P00_TOK_tan_STARTS_tan ,
#define P00_TOK_tanh_STARTS_tanh ,
#define P00_TOK_time_STARTS_time ,
#define P00_TOK_time_t_STARTS_time_t ,
#define P00_TOK_tmpfile_STARTS_tmpfile ,
#define P00_TOK_tmpnam_STARTS_tmpnam ,
#define P00_TOK_tolower_STARTS_tolower ,
#define P00_TOK_toupper_STARTS_toupper ,
#define P00_TOK_towctrans_STARTS_towctrans ,
#define P00_TOK_towlower_STARTS_towlower ,
#define P00_TOK_towupper_STARTS_towupper ,
#define P00_TOK_typedef_STARTS_typedef ,
#define P00_TOK_uint16_t_STARTS_uint16_t ,
#define P00_TOK_uint32_t_STARTS_uint32_t ,
#define P00_TOK_uint64_t_STARTS_uint64_t ,
#define P00_TOK_uint8_t_STARTS_uint8_t ,
#define P00_TOK_uintfast16_t_STARTS_uintfast16_t ,
#define P00_TOK_uintfast32_t_STARTS_uintfast32_t ,
#define P00_TOK_uintfast64_t_STARTS_uintfast64_t ,
#define P00_TOK_uintfast8_t_STARTS_uintfast8_t ,
#define P00_TOK_uintleast16_t_STARTS_uintleast16_t ,
#define P00_TOK_uintleast32_t_STARTS_uintleast32_t ,
#define P00_TOK_uintleast64_t_STARTS_uintleast64_t ,
#define P00_TOK_uintleast8_t_STARTS_uintleast8_t ,
#define P00_TOK_uintmax_t_STARTS_uintmax_t ,
#define P00_TOK_uintptr_t_STARTS_uintptr_t ,
#define P00_TOK_ungetc_STARTS_ungetc ,
#define P00_TOK_ungetwc_STARTS_ungetwc ,
#define P00_TOK_union_STARTS_union ,
#define P00_TOK_unsigned_STARTS_unsigned ,
#define P00_TOK_va_arg_STARTS_va_arg ,
#define P00_TOK_va_copy_STARTS_va_copy ,
#define P00_TOK_va_end_STARTS_va_end ,
#define P00_TOK_va_start_STARTS_va_start ,
#define P00_TOK_vfprintf_STARTS_vfprintf ,
#define P00_TOK_vfscanf_STARTS_vfscanf ,
#define P00_TOK_vfwprintf_STARTS_vfwprintf ,
#define P00_TOK_void_STARTS_void ,
#define P00_TOK_volatile_STARTS_volatile ,
#define P00_TOK_vprintf_STARTS_vprintf ,
#define P00_TOK_vscanf_STARTS_vscanf ,
#define P00_TOK_vsprintf_STARTS_vsprintf ,
#define P00_TOK_vsscanf_STARTS_vsscanf ,
#define P00_TOK_vswprintf_STARTS_vswprintf ,
#define P00_TOK_vwprintf_STARTS_vwprintf ,
#define P00_TOK_wchar_t_STARTS_wchar_t ,
#define P00_TOK_wcrtomb_STARTS_wcrtomb ,
#define P00_TOK_wcscat_STARTS_wcscat ,
#define P00_TOK_wcschr_STARTS_wcschr ,
#define P00_TOK_wcscmp_STARTS_wcscmp ,
#define P00_TOK_wcscoll_STARTS_wcscoll ,
#define P00_TOK_wcscpy_STARTS_wcscpy ,
#define P00_TOK_wcscspn_STARTS_wcscspn ,
#define P00_TOK_wcsftime_STARTS_wcsftime ,
#define P00_TOK_wcslen_STARTS_wcslen ,
#define P00_TOK_wcsncat_STARTS_wcsncat ,
#define P00_TOK_wcsncmp_STARTS_wcsncmp ,
#define P00_TOK_wcsncpy_STARTS_wcsncpy ,
#define P00_TOK_wcspbrk_STARTS_wcspbrk ,
#define P00_TOK_wcsrchr_STARTS_wcsrchr ,
#define P00_TOK_wcsrtombs_STARTS_wcsrtombs ,
#define P00_TOK_wcsspn_STARTS_wcsspn ,
#define P00_TOK_wcsstr_STARTS_wcsstr ,
#define P00_TOK_wcstod_STARTS_wcstod ,
#define P00_TOK_wcstoimax_STARTS_wcstoimax ,
#define P00_TOK_wcstok_STARTS_wcstok ,
#define P00_TOK_wcstol_STARTS_wcstol ,
#define P00_TOK_wcstoul_STARTS_wcstoul ,
#define P00_TOK_wcstoumax_STARTS_wcstoumax ,
#define P00_TOK_wcsxfrm_STARTS_wcsxfrm ,
#define P00_TOK_wctob_STARTS_wctob ,
#define P00_TOK_wctrans_STARTS_wctrans ,
#define P00_TOK_wctrans_t_STARTS_wctrans_t ,
#define P00_TOK_wctype_STARTS_wctype ,
#define P00_TOK_wctype_t_STARTS_wctype_t ,
#define P00_TOK_while_STARTS_while ,
#define P00_TOK_wint_t_STARTS_wint_t ,
#define P00_TOK_wmemchr_STARTS_wmemchr ,
#define P00_TOK_wmemcmp_STARTS_wmemcmp ,
#define P00_TOK_wmemcpy_STARTS_wmemcpy ,
#define P00_TOK_wmemmove_STARTS_wmemmove ,
#define P00_TOK_wmemset_STARTS_wmemset ,
#define P00_TOK_wprintf_STARTS_wprintf ,
#define P00_TOK_wscanf_STARTS_wscanf ,
#define P00_TOK_256_STARTS_256 ,
#define P00_TOK_512_STARTS_512 ,
#define P00_TOK_1024_STARTS_1024 ,
#define P00_TOK_2048_STARTS_2048 ,
#define P00_TOK_4096_STARTS_4096 ,
#define P00_TOK_8192_STARTS_8192 ,
#define P00_TOK_16384_STARTS_16384 ,
#define P00_TOK_32768_STARTS_32768 ,
#define P00_TOK_65536_STARTS_65536 ,
#define P00_TOK_131072_STARTS_131072 ,
#define P00_TOK_262144_STARTS_262144 ,
#define P00_TOK_524288_STARTS_524288 ,
#define P00_TOK_1048576_STARTS_1048576 ,
#define P00_TOK_2097152_STARTS_2097152 ,
#define P00_TOK_4194304_STARTS_4194304 ,
#define P00_TOK_8388608_STARTS_8388608 ,
#define P00_TOK_16777216_STARTS_16777216 ,
#define P00_TOK_33554432_STARTS_33554432 ,
#define P00_TOK_67108864_STARTS_67108864 ,
#define P00_TOK_134217728_STARTS_134217728 ,
#define P00_TOK_268435456_STARTS_268435456 ,
#define P00_TOK_536870912_STARTS_536870912 ,
#define P00_TOK_1073741824_STARTS_1073741824 ,
#define P00_TOK_2147483648_STARTS_2147483648 ,
#define P00_TOK_4294967296_STARTS_4294967296 ,
#define P00_TOK_8589934592_STARTS_8589934592 ,
#define P00_TOK_17179869184_STARTS_17179869184 ,
#define P00_TOK_34359738368_STARTS_34359738368 ,
#define P00_TOK_68719476736_STARTS_68719476736 ,
#define P00_TOK_137438953472_STARTS_137438953472 ,
#define P00_TOK_274877906944_STARTS_274877906944 ,
#define P00_TOK_549755813888_STARTS_549755813888 ,
#define P00_TOK_1099511627776_STARTS_1099511627776 ,
#define P00_TOK_2199023255552_STARTS_2199023255552 ,
#define P00_TOK_4398046511104_STARTS_4398046511104 ,
#define P00_TOK_8796093022208_STARTS_8796093022208 ,
#define P00_TOK_17592186044416_STARTS_17592186044416 ,
#define P00_TOK_35184372088832_STARTS_35184372088832 ,
#define P00_TOK_70368744177664_STARTS_70368744177664 ,
#define P00_TOK_140737488355328_STARTS_140737488355328 ,
#define P00_TOK_281474976710656_STARTS_281474976710656 ,
#define P00_TOK_562949953421312_STARTS_562949953421312 ,
#define P00_TOK_1125899906842624_STARTS_1125899906842624 ,
#define P00_TOK_2251799813685248_STARTS_2251799813685248 ,
#define P00_TOK_4503599627370496_STARTS_4503599627370496 ,
#define P00_TOK_9007199254740992_STARTS_9007199254740992 ,
#define P00_TOK_18014398509481984_STARTS_18014398509481984 ,
#define P00_TOK_36028797018963968_STARTS_36028797018963968 ,
#define P00_TOK_72057594037927936_STARTS_72057594037927936 ,
#define P00_TOK_144115188075855872_STARTS_144115188075855872 ,
#define P00_TOK_288230376151711744_STARTS_288230376151711744 ,
#define P00_TOK_576460752303423488_STARTS_576460752303423488 ,
#define P00_TOK_1152921504606846976_STARTS_1152921504606846976 ,
#define P00_TOK_2305843009213693952_STARTS_2305843009213693952 ,
#define P00_TOK_4611686018427387904_STARTS_4611686018427387904 ,
#define P00_TOK_9223372036854775808_STARTS_9223372036854775808 ,
/*! @brief Test if the argument consists of exactly the token @c 0 */
#define P99_IS_EQ_0(...) P99_TOK_EQ(0, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 1 */
#define P99_IS_EQ_1(...) P99_TOK_EQ(1, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 2 */
#define P99_IS_EQ_2(...) P99_TOK_EQ(2, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 3 */
#define P99_IS_EQ_3(...) P99_TOK_EQ(3, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 4 */
#define P99_IS_EQ_4(...) P99_TOK_EQ(4, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 5 */
#define P99_IS_EQ_5(...) P99_TOK_EQ(5, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 6 */
#define P99_IS_EQ_6(...) P99_TOK_EQ(6, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 7 */
#define P99_IS_EQ_7(...) P99_TOK_EQ(7, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 8 */
#define P99_IS_EQ_8(...) P99_TOK_EQ(8, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 9 */
#define P99_IS_EQ_9(...) P99_TOK_EQ(9, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 10 */
#define P99_IS_EQ_10(...) P99_TOK_EQ(10, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 11 */
#define P99_IS_EQ_11(...) P99_TOK_EQ(11, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 12 */
#define P99_IS_EQ_12(...) P99_TOK_EQ(12, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 13 */
#define P99_IS_EQ_13(...) P99_TOK_EQ(13, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 14 */
#define P99_IS_EQ_14(...) P99_TOK_EQ(14, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 15 */
#define P99_IS_EQ_15(...) P99_TOK_EQ(15, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 16 */
#define P99_IS_EQ_16(...) P99_TOK_EQ(16, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 17 */
#define P99_IS_EQ_17(...) P99_TOK_EQ(17, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 18 */
#define P99_IS_EQ_18(...) P99_TOK_EQ(18, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 19 */
#define P99_IS_EQ_19(...) P99_TOK_EQ(19, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 20 */
#define P99_IS_EQ_20(...) P99_TOK_EQ(20, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 21 */
#define P99_IS_EQ_21(...) P99_TOK_EQ(21, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 22 */
#define P99_IS_EQ_22(...) P99_TOK_EQ(22, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 23 */
#define P99_IS_EQ_23(...) P99_TOK_EQ(23, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 24 */
#define P99_IS_EQ_24(...) P99_TOK_EQ(24, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 25 */
#define P99_IS_EQ_25(...) P99_TOK_EQ(25, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 26 */
#define P99_IS_EQ_26(...) P99_TOK_EQ(26, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 27 */
#define P99_IS_EQ_27(...) P99_TOK_EQ(27, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 28 */
#define P99_IS_EQ_28(...) P99_TOK_EQ(28, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 29 */
#define P99_IS_EQ_29(...) P99_TOK_EQ(29, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 30 */
#define P99_IS_EQ_30(...) P99_TOK_EQ(30, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 31 */
#define P99_IS_EQ_31(...) P99_TOK_EQ(31, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 32 */
#define P99_IS_EQ_32(...) P99_TOK_EQ(32, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 33 */
#define P99_IS_EQ_33(...) P99_TOK_EQ(33, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 34 */
#define P99_IS_EQ_34(...) P99_TOK_EQ(34, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 35 */
#define P99_IS_EQ_35(...) P99_TOK_EQ(35, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 36 */
#define P99_IS_EQ_36(...) P99_TOK_EQ(36, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 37 */
#define P99_IS_EQ_37(...) P99_TOK_EQ(37, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 38 */
#define P99_IS_EQ_38(...) P99_TOK_EQ(38, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 39 */
#define P99_IS_EQ_39(...) P99_TOK_EQ(39, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 40 */
#define P99_IS_EQ_40(...) P99_TOK_EQ(40, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 41 */
#define P99_IS_EQ_41(...) P99_TOK_EQ(41, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 42 */
#define P99_IS_EQ_42(...) P99_TOK_EQ(42, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 43 */
#define P99_IS_EQ_43(...) P99_TOK_EQ(43, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 44 */
#define P99_IS_EQ_44(...) P99_TOK_EQ(44, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 45 */
#define P99_IS_EQ_45(...) P99_TOK_EQ(45, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 46 */
#define P99_IS_EQ_46(...) P99_TOK_EQ(46, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 47 */
#define P99_IS_EQ_47(...) P99_TOK_EQ(47, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 48 */
#define P99_IS_EQ_48(...) P99_TOK_EQ(48, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 49 */
#define P99_IS_EQ_49(...) P99_TOK_EQ(49, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 50 */
#define P99_IS_EQ_50(...) P99_TOK_EQ(50, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 51 */
#define P99_IS_EQ_51(...) P99_TOK_EQ(51, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 52 */
#define P99_IS_EQ_52(...) P99_TOK_EQ(52, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 53 */
#define P99_IS_EQ_53(...) P99_TOK_EQ(53, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 54 */
#define P99_IS_EQ_54(...) P99_TOK_EQ(54, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 55 */
#define P99_IS_EQ_55(...) P99_TOK_EQ(55, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 56 */
#define P99_IS_EQ_56(...) P99_TOK_EQ(56, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 57 */
#define P99_IS_EQ_57(...) P99_TOK_EQ(57, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 58 */
#define P99_IS_EQ_58(...) P99_TOK_EQ(58, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 59 */
#define P99_IS_EQ_59(...) P99_TOK_EQ(59, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 60 */
#define P99_IS_EQ_60(...) P99_TOK_EQ(60, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 61 */
#define P99_IS_EQ_61(...) P99_TOK_EQ(61, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 62 */
#define P99_IS_EQ_62(...) P99_TOK_EQ(62, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 63 */
#define P99_IS_EQ_63(...) P99_TOK_EQ(63, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 64 */
#define P99_IS_EQ_64(...) P99_TOK_EQ(64, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 65 */
#define P99_IS_EQ_65(...) P99_TOK_EQ(65, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 66 */
#define P99_IS_EQ_66(...) P99_TOK_EQ(66, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 67 */
#define P99_IS_EQ_67(...) P99_TOK_EQ(67, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 68 */
#define P99_IS_EQ_68(...) P99_TOK_EQ(68, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 69 */
#define P99_IS_EQ_69(...) P99_TOK_EQ(69, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 70 */
#define P99_IS_EQ_70(...) P99_TOK_EQ(70, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 71 */
#define P99_IS_EQ_71(...) P99_TOK_EQ(71, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 72 */
#define P99_IS_EQ_72(...) P99_TOK_EQ(72, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 73 */
#define P99_IS_EQ_73(...) P99_TOK_EQ(73, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 74 */
#define P99_IS_EQ_74(...) P99_TOK_EQ(74, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 75 */
#define P99_IS_EQ_75(...) P99_TOK_EQ(75, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 76 */
#define P99_IS_EQ_76(...) P99_TOK_EQ(76, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 77 */
#define P99_IS_EQ_77(...) P99_TOK_EQ(77, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 78 */
#define P99_IS_EQ_78(...) P99_TOK_EQ(78, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 79 */
#define P99_IS_EQ_79(...) P99_TOK_EQ(79, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 80 */
#define P99_IS_EQ_80(...) P99_TOK_EQ(80, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 81 */
#define P99_IS_EQ_81(...) P99_TOK_EQ(81, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 82 */
#define P99_IS_EQ_82(...) P99_TOK_EQ(82, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 83 */
#define P99_IS_EQ_83(...) P99_TOK_EQ(83, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 84 */
#define P99_IS_EQ_84(...) P99_TOK_EQ(84, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 85 */
#define P99_IS_EQ_85(...) P99_TOK_EQ(85, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 86 */
#define P99_IS_EQ_86(...) P99_TOK_EQ(86, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 87 */
#define P99_IS_EQ_87(...) P99_TOK_EQ(87, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 88 */
#define P99_IS_EQ_88(...) P99_TOK_EQ(88, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 89 */
#define P99_IS_EQ_89(...) P99_TOK_EQ(89, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 90 */
#define P99_IS_EQ_90(...) P99_TOK_EQ(90, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 91 */
#define P99_IS_EQ_91(...) P99_TOK_EQ(91, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 92 */
#define P99_IS_EQ_92(...) P99_TOK_EQ(92, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 93 */
#define P99_IS_EQ_93(...) P99_TOK_EQ(93, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 94 */
#define P99_IS_EQ_94(...) P99_TOK_EQ(94, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 95 */
#define P99_IS_EQ_95(...) P99_TOK_EQ(95, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 96 */
#define P99_IS_EQ_96(...) P99_TOK_EQ(96, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 97 */
#define P99_IS_EQ_97(...) P99_TOK_EQ(97, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 98 */
#define P99_IS_EQ_98(...) P99_TOK_EQ(98, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 99 */
#define P99_IS_EQ_99(...) P99_TOK_EQ(99, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 100 */
#define P99_IS_EQ_100(...) P99_TOK_EQ(100, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 101 */
#define P99_IS_EQ_101(...) P99_TOK_EQ(101, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 102 */
#define P99_IS_EQ_102(...) P99_TOK_EQ(102, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 103 */
#define P99_IS_EQ_103(...) P99_TOK_EQ(103, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 104 */
#define P99_IS_EQ_104(...) P99_TOK_EQ(104, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 105 */
#define P99_IS_EQ_105(...) P99_TOK_EQ(105, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 106 */
#define P99_IS_EQ_106(...) P99_TOK_EQ(106, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 107 */
#define P99_IS_EQ_107(...) P99_TOK_EQ(107, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 108 */
#define P99_IS_EQ_108(...) P99_TOK_EQ(108, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 109 */
#define P99_IS_EQ_109(...) P99_TOK_EQ(109, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 110 */
#define P99_IS_EQ_110(...) P99_TOK_EQ(110, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 111 */
#define P99_IS_EQ_111(...) P99_TOK_EQ(111, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 112 */
#define P99_IS_EQ_112(...) P99_TOK_EQ(112, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 113 */
#define P99_IS_EQ_113(...) P99_TOK_EQ(113, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 114 */
#define P99_IS_EQ_114(...) P99_TOK_EQ(114, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 115 */
#define P99_IS_EQ_115(...) P99_TOK_EQ(115, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 116 */
#define P99_IS_EQ_116(...) P99_TOK_EQ(116, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 117 */
#define P99_IS_EQ_117(...) P99_TOK_EQ(117, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 118 */
#define P99_IS_EQ_118(...) P99_TOK_EQ(118, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 119 */
#define P99_IS_EQ_119(...) P99_TOK_EQ(119, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 120 */
#define P99_IS_EQ_120(...) P99_TOK_EQ(120, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 121 */
#define P99_IS_EQ_121(...) P99_TOK_EQ(121, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 122 */
#define P99_IS_EQ_122(...) P99_TOK_EQ(122, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 123 */
#define P99_IS_EQ_123(...) P99_TOK_EQ(123, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 124 */
#define P99_IS_EQ_124(...) P99_TOK_EQ(124, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 125 */
#define P99_IS_EQ_125(...) P99_TOK_EQ(125, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 126 */
#define P99_IS_EQ_126(...) P99_TOK_EQ(126, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 127 */
#define P99_IS_EQ_127(...) P99_TOK_EQ(127, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 128 */
#define P99_IS_EQ_128(...) P99_TOK_EQ(128, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 129 */
#define P99_IS_EQ_129(...) P99_TOK_EQ(129, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 130 */
#define P99_IS_EQ_130(...) P99_TOK_EQ(130, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 131 */
#define P99_IS_EQ_131(...) P99_TOK_EQ(131, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 132 */
#define P99_IS_EQ_132(...) P99_TOK_EQ(132, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 133 */
#define P99_IS_EQ_133(...) P99_TOK_EQ(133, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 134 */
#define P99_IS_EQ_134(...) P99_TOK_EQ(134, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 135 */
#define P99_IS_EQ_135(...) P99_TOK_EQ(135, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 136 */
#define P99_IS_EQ_136(...) P99_TOK_EQ(136, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 137 */
#define P99_IS_EQ_137(...) P99_TOK_EQ(137, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 138 */
#define P99_IS_EQ_138(...) P99_TOK_EQ(138, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 139 */
#define P99_IS_EQ_139(...) P99_TOK_EQ(139, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 140 */
#define P99_IS_EQ_140(...) P99_TOK_EQ(140, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 141 */
#define P99_IS_EQ_141(...) P99_TOK_EQ(141, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 142 */
#define P99_IS_EQ_142(...) P99_TOK_EQ(142, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 143 */
#define P99_IS_EQ_143(...) P99_TOK_EQ(143, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 144 */
#define P99_IS_EQ_144(...) P99_TOK_EQ(144, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 145 */
#define P99_IS_EQ_145(...) P99_TOK_EQ(145, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 146 */
#define P99_IS_EQ_146(...) P99_TOK_EQ(146, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 147 */
#define P99_IS_EQ_147(...) P99_TOK_EQ(147, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 148 */
#define P99_IS_EQ_148(...) P99_TOK_EQ(148, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 149 */
#define P99_IS_EQ_149(...) P99_TOK_EQ(149, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 150 */
#define P99_IS_EQ_150(...) P99_TOK_EQ(150, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 151 */
#define P99_IS_EQ_151(...) P99_TOK_EQ(151, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 152 */
#define P99_IS_EQ_152(...) P99_TOK_EQ(152, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 153 */
#define P99_IS_EQ_153(...) P99_TOK_EQ(153, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 154 */
#define P99_IS_EQ_154(...) P99_TOK_EQ(154, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 155 */
#define P99_IS_EQ_155(...) P99_TOK_EQ(155, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 156 */
#define P99_IS_EQ_156(...) P99_TOK_EQ(156, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 157 */
#define P99_IS_EQ_157(...) P99_TOK_EQ(157, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 158 */
#define P99_IS_EQ_158(...) P99_TOK_EQ(158, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 159 */
#define P99_IS_EQ_159(...) P99_TOK_EQ(159, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c _Bool */
#define P99_IS_EQ__Bool(...) P99_TOK_EQ(_Bool, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c _Complex */
#define P99_IS_EQ__Complex(...) P99_TOK_EQ(_Complex, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c _Exit */
#define P99_IS_EQ__Exit(...) P99_TOK_EQ(_Exit, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c _Imaginary */
#define P99_IS_EQ__Imaginary(...) P99_TOK_EQ(_Imaginary, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c abort */
#define P99_IS_EQ_abort(...) P99_TOK_EQ(abort, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c abs */
#define P99_IS_EQ_abs(...) P99_TOK_EQ(abs, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c acos */
#define P99_IS_EQ_acos(...) P99_TOK_EQ(acos, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c asctime */
#define P99_IS_EQ_asctime(...) P99_TOK_EQ(asctime, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c asin */
#define P99_IS_EQ_asin(...) P99_TOK_EQ(asin, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c assert */
#define P99_IS_EQ_assert(...) P99_TOK_EQ(assert, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c atan */
#define P99_IS_EQ_atan(...) P99_TOK_EQ(atan, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c atan2 */
#define P99_IS_EQ_atan2(...) P99_TOK_EQ(atan2, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c atexit */
#define P99_IS_EQ_atexit(...) P99_TOK_EQ(atexit, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c atof */
#define P99_IS_EQ_atof(...) P99_TOK_EQ(atof, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c atoi */
#define P99_IS_EQ_atoi(...) P99_TOK_EQ(atoi, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c atol */
#define P99_IS_EQ_atol(...) P99_TOK_EQ(atol, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c auto */
#define P99_IS_EQ_auto(...) P99_TOK_EQ(auto, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c break */
#define P99_IS_EQ_break(...) P99_TOK_EQ(break, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c bsearch */
#define P99_IS_EQ_bsearch(...) P99_TOK_EQ(bsearch, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c btowc */
#define P99_IS_EQ_btowc(...) P99_TOK_EQ(btowc, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c cabs */
#define P99_IS_EQ_cabs(...) P99_TOK_EQ(cabs, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c cacos */
#define P99_IS_EQ_cacos(...) P99_TOK_EQ(cacos, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c cacosh */
#define P99_IS_EQ_cacosh(...) P99_TOK_EQ(cacosh, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c calloc */
#define P99_IS_EQ_calloc(...) P99_TOK_EQ(calloc, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c carg */
#define P99_IS_EQ_carg(...) P99_TOK_EQ(carg, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c case */
#define P99_IS_EQ_case(...) P99_TOK_EQ(case, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c casin */
#define P99_IS_EQ_casin(...) P99_TOK_EQ(casin, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c casinh */
#define P99_IS_EQ_casinh(...) P99_TOK_EQ(casinh, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c catan */
#define P99_IS_EQ_catan(...) P99_TOK_EQ(catan, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c catanh */
#define P99_IS_EQ_catanh(...) P99_TOK_EQ(catanh, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c ccos */
#define P99_IS_EQ_ccos(...) P99_TOK_EQ(ccos, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c ccosh */
#define P99_IS_EQ_ccosh(...) P99_TOK_EQ(ccosh, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c ceil */
#define P99_IS_EQ_ceil(...) P99_TOK_EQ(ceil, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c cexp */
#define P99_IS_EQ_cexp(...) P99_TOK_EQ(cexp, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c char */
#define P99_IS_EQ_char(...) P99_TOK_EQ(char, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c cimag */
#define P99_IS_EQ_cimag(...) P99_TOK_EQ(cimag, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c clearerr */
#define P99_IS_EQ_clearerr(...) P99_TOK_EQ(clearerr, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c clock */
#define P99_IS_EQ_clock(...) P99_TOK_EQ(clock, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c clock_t */
#define P99_IS_EQ_clock_t(...) P99_TOK_EQ(clock_t, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c clog */
#define P99_IS_EQ_clog(...) P99_TOK_EQ(clog, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c conj */
#define P99_IS_EQ_conj(...) P99_TOK_EQ(conj, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c const */
#define P99_IS_EQ_const(...) P99_TOK_EQ(const, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c continue */
#define P99_IS_EQ_continue(...) P99_TOK_EQ(continue, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c cos */
#define P99_IS_EQ_cos(...) P99_TOK_EQ(cos, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c cosh */
#define P99_IS_EQ_cosh(...) P99_TOK_EQ(cosh, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c cpow */
#define P99_IS_EQ_cpow(...) P99_TOK_EQ(cpow, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c cproj */
#define P99_IS_EQ_cproj(...) P99_TOK_EQ(cproj, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c creal */
#define P99_IS_EQ_creal(...) P99_TOK_EQ(creal, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c csin */
#define P99_IS_EQ_csin(...) P99_TOK_EQ(csin, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c csinh */
#define P99_IS_EQ_csinh(...) P99_TOK_EQ(csinh, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c csqrt */
#define P99_IS_EQ_csqrt(...) P99_TOK_EQ(csqrt, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c ctan */
#define P99_IS_EQ_ctan(...) P99_TOK_EQ(ctan, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c ctanh */
#define P99_IS_EQ_ctanh(...) P99_TOK_EQ(ctanh, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c ctime */
#define P99_IS_EQ_ctime(...) P99_TOK_EQ(ctime, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c default */
#define P99_IS_EQ_default(...) P99_TOK_EQ(default, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c difftime */
#define P99_IS_EQ_difftime(...) P99_TOK_EQ(difftime, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c div */
#define P99_IS_EQ_div(...) P99_TOK_EQ(div, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c div_t */
#define P99_IS_EQ_div_t(...) P99_TOK_EQ(div_t, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c do */
#define P99_IS_EQ_do(...) P99_TOK_EQ(do, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c double */
#define P99_IS_EQ_double(...) P99_TOK_EQ(double, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c double_t */
#define P99_IS_EQ_double_t(...) P99_TOK_EQ(double_t, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c else */
#define P99_IS_EQ_else(...) P99_TOK_EQ(else, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c enum */
#define P99_IS_EQ_enum(...) P99_TOK_EQ(enum, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c exit */
#define P99_IS_EQ_exit(...) P99_TOK_EQ(exit, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c exp */
#define P99_IS_EQ_exp(...) P99_TOK_EQ(exp, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c extern */
#define P99_IS_EQ_extern(...) P99_TOK_EQ(extern, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c fabs */
#define P99_IS_EQ_fabs(...) P99_TOK_EQ(fabs, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c fclose */
#define P99_IS_EQ_fclose(...) P99_TOK_EQ(fclose, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c fdopen */
#define P99_IS_EQ_fdopen(...) P99_TOK_EQ(fdopen, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c fenv_t */
#define P99_IS_EQ_fenv_t(...) P99_TOK_EQ(fenv_t, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c feof */
#define P99_IS_EQ_feof(...) P99_TOK_EQ(feof, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c ferror */
#define P99_IS_EQ_ferror(...) P99_TOK_EQ(ferror, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c fexcept_t */
#define P99_IS_EQ_fexcept_t(...) P99_TOK_EQ(fexcept_t, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c fflush */
#define P99_IS_EQ_fflush(...) P99_TOK_EQ(fflush, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c fgetc */
#define P99_IS_EQ_fgetc(...) P99_TOK_EQ(fgetc, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c fgetpos */
#define P99_IS_EQ_fgetpos(...) P99_TOK_EQ(fgetpos, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c fgets */
#define P99_IS_EQ_fgets(...) P99_TOK_EQ(fgets, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c fgetwc */
#define P99_IS_EQ_fgetwc(...) P99_TOK_EQ(fgetwc, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c fgetws */
#define P99_IS_EQ_fgetws(...) P99_TOK_EQ(fgetws, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c float */
#define P99_IS_EQ_float(...) P99_TOK_EQ(float, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c float_t */
#define P99_IS_EQ_float_t(...) P99_TOK_EQ(float_t, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c floor */
#define P99_IS_EQ_floor(...) P99_TOK_EQ(floor, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c fopen */
#define P99_IS_EQ_fopen(...) P99_TOK_EQ(fopen, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c for */
#define P99_IS_EQ_for(...) P99_TOK_EQ(for, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c fpos_t */
#define P99_IS_EQ_fpos_t(...) P99_TOK_EQ(fpos_t, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c fprintf */
#define P99_IS_EQ_fprintf(...) P99_TOK_EQ(fprintf, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c fputc */
#define P99_IS_EQ_fputc(...) P99_TOK_EQ(fputc, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c fputchar */
#define P99_IS_EQ_fputchar(...) P99_TOK_EQ(fputchar, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c fputs */
#define P99_IS_EQ_fputs(...) P99_TOK_EQ(fputs, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c fputwc */
#define P99_IS_EQ_fputwc(...) P99_TOK_EQ(fputwc, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c fputws */
#define P99_IS_EQ_fputws(...) P99_TOK_EQ(fputws, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c fread */
#define P99_IS_EQ_fread(...) P99_TOK_EQ(fread, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c free */
#define P99_IS_EQ_free(...) P99_TOK_EQ(free, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c freopen */
#define P99_IS_EQ_freopen(...) P99_TOK_EQ(freopen, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c frexp */
#define P99_IS_EQ_frexp(...) P99_TOK_EQ(frexp, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c fscanf */
#define P99_IS_EQ_fscanf(...) P99_TOK_EQ(fscanf, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c fseek */
#define P99_IS_EQ_fseek(...) P99_TOK_EQ(fseek, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c fsetpos */
#define P99_IS_EQ_fsetpos(...) P99_TOK_EQ(fsetpos, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c ftell */
#define P99_IS_EQ_ftell(...) P99_TOK_EQ(ftell, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c fwide */
#define P99_IS_EQ_fwide(...) P99_TOK_EQ(fwide, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c fwprintf */
#define P99_IS_EQ_fwprintf(...) P99_TOK_EQ(fwprintf, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c fwrite */
#define P99_IS_EQ_fwrite(...) P99_TOK_EQ(fwrite, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c fwscanf */
#define P99_IS_EQ_fwscanf(...) P99_TOK_EQ(fwscanf, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c getaddrinfo */
#define P99_IS_EQ_getaddrinfo(...) P99_TOK_EQ(getaddrinfo, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c getc */
#define P99_IS_EQ_getc(...) P99_TOK_EQ(getc, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c getchar */
#define P99_IS_EQ_getchar(...) P99_TOK_EQ(getchar, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c getenv */
#define P99_IS_EQ_getenv(...) P99_TOK_EQ(getenv, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c getnameinfo */
#define P99_IS_EQ_getnameinfo(...) P99_TOK_EQ(getnameinfo, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c gets */
#define P99_IS_EQ_gets(...) P99_TOK_EQ(gets, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c getwc */
#define P99_IS_EQ_getwc(...) P99_TOK_EQ(getwc, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c getwchar */
#define P99_IS_EQ_getwchar(...) P99_TOK_EQ(getwchar, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c gmtime */
#define P99_IS_EQ_gmtime(...) P99_TOK_EQ(gmtime, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c goto */
#define P99_IS_EQ_goto(...) P99_TOK_EQ(goto, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c if */
#define P99_IS_EQ_if(...) P99_TOK_EQ(if, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c imaxabs */
#define P99_IS_EQ_imaxabs(...) P99_TOK_EQ(imaxabs, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c imaxdiv */
#define P99_IS_EQ_imaxdiv(...) P99_TOK_EQ(imaxdiv, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c imaxdiv_t */
#define P99_IS_EQ_imaxdiv_t(...) P99_TOK_EQ(imaxdiv_t, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c inline */
#define P99_IS_EQ_inline(...) P99_TOK_EQ(inline, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c int */
#define P99_IS_EQ_int(...) P99_TOK_EQ(int, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c int16_t */
#define P99_IS_EQ_int16_t(...) P99_TOK_EQ(int16_t, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c int32_t */
#define P99_IS_EQ_int32_t(...) P99_TOK_EQ(int32_t, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c int64_t */
#define P99_IS_EQ_int64_t(...) P99_TOK_EQ(int64_t, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c int8_t */
#define P99_IS_EQ_int8_t(...) P99_TOK_EQ(int8_t, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c intfast16_t */
#define P99_IS_EQ_intfast16_t(...) P99_TOK_EQ(intfast16_t, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c intfast32_t */
#define P99_IS_EQ_intfast32_t(...) P99_TOK_EQ(intfast32_t, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c intfast64_t */
#define P99_IS_EQ_intfast64_t(...) P99_TOK_EQ(intfast64_t, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c intfast8_t */
#define P99_IS_EQ_intfast8_t(...) P99_TOK_EQ(intfast8_t, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c intleast16_t */
#define P99_IS_EQ_intleast16_t(...) P99_TOK_EQ(intleast16_t, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c intleast32_t */
#define P99_IS_EQ_intleast32_t(...) P99_TOK_EQ(intleast32_t, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c intleast64_t */
#define P99_IS_EQ_intleast64_t(...) P99_TOK_EQ(intleast64_t, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c intleast8_t */
#define P99_IS_EQ_intleast8_t(...) P99_TOK_EQ(intleast8_t, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c intmax_t */
#define P99_IS_EQ_intmax_t(...) P99_TOK_EQ(intmax_t, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c intptr_t */
#define P99_IS_EQ_intptr_t(...) P99_TOK_EQ(intptr_t, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c isalnum */
#define P99_IS_EQ_isalnum(...) P99_TOK_EQ(isalnum, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c isalpha */
#define P99_IS_EQ_isalpha(...) P99_TOK_EQ(isalpha, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c isblank */
#define P99_IS_EQ_isblank(...) P99_TOK_EQ(isblank, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c iscntrl */
#define P99_IS_EQ_iscntrl(...) P99_TOK_EQ(iscntrl, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c isdigit */
#define P99_IS_EQ_isdigit(...) P99_TOK_EQ(isdigit, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c isgraph */
#define P99_IS_EQ_isgraph(...) P99_TOK_EQ(isgraph, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c islower */
#define P99_IS_EQ_islower(...) P99_TOK_EQ(islower, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c isprint */
#define P99_IS_EQ_isprint(...) P99_TOK_EQ(isprint, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c ispunct */
#define P99_IS_EQ_ispunct(...) P99_TOK_EQ(ispunct, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c isspace */
#define P99_IS_EQ_isspace(...) P99_TOK_EQ(isspace, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c isupper */
#define P99_IS_EQ_isupper(...) P99_TOK_EQ(isupper, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c iswalnum */
#define P99_IS_EQ_iswalnum(...) P99_TOK_EQ(iswalnum, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c iswalpha */
#define P99_IS_EQ_iswalpha(...) P99_TOK_EQ(iswalpha, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c iswcntrl */
#define P99_IS_EQ_iswcntrl(...) P99_TOK_EQ(iswcntrl, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c iswctype */
#define P99_IS_EQ_iswctype(...) P99_TOK_EQ(iswctype, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c iswdigit */
#define P99_IS_EQ_iswdigit(...) P99_TOK_EQ(iswdigit, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c iswgraph */
#define P99_IS_EQ_iswgraph(...) P99_TOK_EQ(iswgraph, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c iswlower */
#define P99_IS_EQ_iswlower(...) P99_TOK_EQ(iswlower, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c iswprint */
#define P99_IS_EQ_iswprint(...) P99_TOK_EQ(iswprint, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c iswpunct */
#define P99_IS_EQ_iswpunct(...) P99_TOK_EQ(iswpunct, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c iswspace */
#define P99_IS_EQ_iswspace(...) P99_TOK_EQ(iswspace, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c iswupper */
#define P99_IS_EQ_iswupper(...) P99_TOK_EQ(iswupper, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c iswxdigit */
#define P99_IS_EQ_iswxdigit(...) P99_TOK_EQ(iswxdigit, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c isxdigit */
#define P99_IS_EQ_isxdigit(...) P99_TOK_EQ(isxdigit, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c labs */
#define P99_IS_EQ_labs(...) P99_TOK_EQ(labs, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c ldexp */
#define P99_IS_EQ_ldexp(...) P99_TOK_EQ(ldexp, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c ldiv */
#define P99_IS_EQ_ldiv(...) P99_TOK_EQ(ldiv, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c ldiv_t */
#define P99_IS_EQ_ldiv_t(...) P99_TOK_EQ(ldiv_t, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c lldiv_t */
#define P99_IS_EQ_lldiv_t(...) P99_TOK_EQ(lldiv_t, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c localeconv */
#define P99_IS_EQ_localeconv(...) P99_TOK_EQ(localeconv, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c localtime */
#define P99_IS_EQ_localtime(...) P99_TOK_EQ(localtime, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c log */
#define P99_IS_EQ_log(...) P99_TOK_EQ(log, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c log10 */
#define P99_IS_EQ_log10(...) P99_TOK_EQ(log10, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c long */
#define P99_IS_EQ_long(...) P99_TOK_EQ(long, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c longjmp */
#define P99_IS_EQ_longjmp(...) P99_TOK_EQ(longjmp, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c malloc */
#define P99_IS_EQ_malloc(...) P99_TOK_EQ(malloc, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c mbrlen */
#define P99_IS_EQ_mbrlen(...) P99_TOK_EQ(mbrlen, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c mbrtowc */
#define P99_IS_EQ_mbrtowc(...) P99_TOK_EQ(mbrtowc, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c mbsinit */
#define P99_IS_EQ_mbsinit(...) P99_TOK_EQ(mbsinit, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c mbsrtowcs */
#define P99_IS_EQ_mbsrtowcs(...) P99_TOK_EQ(mbsrtowcs, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c mbstate_t */
#define P99_IS_EQ_mbstate_t(...) P99_TOK_EQ(mbstate_t, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c memchr */
#define P99_IS_EQ_memchr(...) P99_TOK_EQ(memchr, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c memcmp */
#define P99_IS_EQ_memcmp(...) P99_TOK_EQ(memcmp, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c memcpy */
#define P99_IS_EQ_memcpy(...) P99_TOK_EQ(memcpy, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c memmove */
#define P99_IS_EQ_memmove(...) P99_TOK_EQ(memmove, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c memset */
#define P99_IS_EQ_memset(...) P99_TOK_EQ(memset, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c mktime */
#define P99_IS_EQ_mktime(...) P99_TOK_EQ(mktime, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c modf */
#define P99_IS_EQ_modf(...) P99_TOK_EQ(modf, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c off_t */
#define P99_IS_EQ_off_t(...) P99_TOK_EQ(off_t, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c offsetof */
#define P99_IS_EQ_offsetof(...) P99_TOK_EQ(offsetof, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c perror */
#define P99_IS_EQ_perror(...) P99_TOK_EQ(perror, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c pow */
#define P99_IS_EQ_pow(...) P99_TOK_EQ(pow, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c printf */
#define P99_IS_EQ_printf(...) P99_TOK_EQ(printf, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c ptrdiff_t */
#define P99_IS_EQ_ptrdiff_t(...) P99_TOK_EQ(ptrdiff_t, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c putc */
#define P99_IS_EQ_putc(...) P99_TOK_EQ(putc, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c putchar */
#define P99_IS_EQ_putchar(...) P99_TOK_EQ(putchar, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c puts */
#define P99_IS_EQ_puts(...) P99_TOK_EQ(puts, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c putwc */
#define P99_IS_EQ_putwc(...) P99_TOK_EQ(putwc, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c putwchar */
#define P99_IS_EQ_putwchar(...) P99_TOK_EQ(putwchar, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c qsort */
#define P99_IS_EQ_qsort(...) P99_TOK_EQ(qsort, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c raise */
#define P99_IS_EQ_raise(...) P99_TOK_EQ(raise, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c rand */
#define P99_IS_EQ_rand(...) P99_TOK_EQ(rand, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c realloc */
#define P99_IS_EQ_realloc(...) P99_TOK_EQ(realloc, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c register */
#define P99_IS_EQ_register(...) P99_TOK_EQ(register, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c remove */
#define P99_IS_EQ_remove(...) P99_TOK_EQ(remove, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c rename */
#define P99_IS_EQ_rename(...) P99_TOK_EQ(rename, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c restrict */
#define P99_IS_EQ_restrict(...) P99_TOK_EQ(restrict, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c return */
#define P99_IS_EQ_return(...) P99_TOK_EQ(return, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c rewind */
#define P99_IS_EQ_rewind(...) P99_TOK_EQ(rewind, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c scanf */
#define P99_IS_EQ_scanf(...) P99_TOK_EQ(scanf, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c setbuf */
#define P99_IS_EQ_setbuf(...) P99_TOK_EQ(setbuf, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c setjmp */
#define P99_IS_EQ_setjmp(...) P99_TOK_EQ(setjmp, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c setlocale */
#define P99_IS_EQ_setlocale(...) P99_TOK_EQ(setlocale, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c setvbuf */
#define P99_IS_EQ_setvbuf(...) P99_TOK_EQ(setvbuf, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c short */
#define P99_IS_EQ_short(...) P99_TOK_EQ(short, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c sig_atomic_t */
#define P99_IS_EQ_sig_atomic_t(...) P99_TOK_EQ(sig_atomic_t, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c signed */
#define P99_IS_EQ_signed(...) P99_TOK_EQ(signed, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c sin */
#define P99_IS_EQ_sin(...) P99_TOK_EQ(sin, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c sinh */
#define P99_IS_EQ_sinh(...) P99_TOK_EQ(sinh, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c size_t */
#define P99_IS_EQ_size_t(...) P99_TOK_EQ(size_t, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c sizeof */
#define P99_IS_EQ_sizeof(...) P99_TOK_EQ(sizeof, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c snprintf */
#define P99_IS_EQ_snprintf(...) P99_TOK_EQ(snprintf, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c sprintf */
#define P99_IS_EQ_sprintf(...) P99_TOK_EQ(sprintf, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c sqrt */
#define P99_IS_EQ_sqrt(...) P99_TOK_EQ(sqrt, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c srand */
#define P99_IS_EQ_srand(...) P99_TOK_EQ(srand, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c sscanf */
#define P99_IS_EQ_sscanf(...) P99_TOK_EQ(sscanf, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c ssize_t */
#define P99_IS_EQ_ssize_t(...) P99_TOK_EQ(ssize_t, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c static */
#define P99_IS_EQ_static(...) P99_TOK_EQ(static, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c strcat */
#define P99_IS_EQ_strcat(...) P99_TOK_EQ(strcat, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c strchr */
#define P99_IS_EQ_strchr(...) P99_TOK_EQ(strchr, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c strcmp */
#define P99_IS_EQ_strcmp(...) P99_TOK_EQ(strcmp, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c strcoll */
#define P99_IS_EQ_strcoll(...) P99_TOK_EQ(strcoll, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c strcpy */
#define P99_IS_EQ_strcpy(...) P99_TOK_EQ(strcpy, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c strcspn */
#define P99_IS_EQ_strcspn(...) P99_TOK_EQ(strcspn, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c strerror */
#define P99_IS_EQ_strerror(...) P99_TOK_EQ(strerror, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c strftime */
#define P99_IS_EQ_strftime(...) P99_TOK_EQ(strftime, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c strlen */
#define P99_IS_EQ_strlen(...) P99_TOK_EQ(strlen, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c strncat */
#define P99_IS_EQ_strncat(...) P99_TOK_EQ(strncat, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c strncmp */
#define P99_IS_EQ_strncmp(...) P99_TOK_EQ(strncmp, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c strncpy */
#define P99_IS_EQ_strncpy(...) P99_TOK_EQ(strncpy, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c strpbrk */
#define P99_IS_EQ_strpbrk(...) P99_TOK_EQ(strpbrk, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c strrchr */
#define P99_IS_EQ_strrchr(...) P99_TOK_EQ(strrchr, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c strspn */
#define P99_IS_EQ_strspn(...) P99_TOK_EQ(strspn, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c strstr */
#define P99_IS_EQ_strstr(...) P99_TOK_EQ(strstr, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c strtod */
#define P99_IS_EQ_strtod(...) P99_TOK_EQ(strtod, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c strtoimax */
#define P99_IS_EQ_strtoimax(...) P99_TOK_EQ(strtoimax, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c strtok */
#define P99_IS_EQ_strtok(...) P99_TOK_EQ(strtok, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c strtol */
#define P99_IS_EQ_strtol(...) P99_TOK_EQ(strtol, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c strtoul */
#define P99_IS_EQ_strtoul(...) P99_TOK_EQ(strtoul, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c strtoumax */
#define P99_IS_EQ_strtoumax(...) P99_TOK_EQ(strtoumax, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c struct */
#define P99_IS_EQ_struct(...) P99_TOK_EQ(struct, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c strxfrm */
#define P99_IS_EQ_strxfrm(...) P99_TOK_EQ(strxfrm, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c switch */
#define P99_IS_EQ_switch(...) P99_TOK_EQ(switch, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c swprintf */
#define P99_IS_EQ_swprintf(...) P99_TOK_EQ(swprintf, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c swscanf */
#define P99_IS_EQ_swscanf(...) P99_TOK_EQ(swscanf, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c system */
#define P99_IS_EQ_system(...) P99_TOK_EQ(system, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c tan */
#define P99_IS_EQ_tan(...) P99_TOK_EQ(tan, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c tanh */
#define P99_IS_EQ_tanh(...) P99_TOK_EQ(tanh, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c time */
#define P99_IS_EQ_time(...) P99_TOK_EQ(time, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c time_t */
#define P99_IS_EQ_time_t(...) P99_TOK_EQ(time_t, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c tmpfile */
#define P99_IS_EQ_tmpfile(...) P99_TOK_EQ(tmpfile, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c tmpnam */
#define P99_IS_EQ_tmpnam(...) P99_TOK_EQ(tmpnam, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c tolower */
#define P99_IS_EQ_tolower(...) P99_TOK_EQ(tolower, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c toupper */
#define P99_IS_EQ_toupper(...) P99_TOK_EQ(toupper, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c towctrans */
#define P99_IS_EQ_towctrans(...) P99_TOK_EQ(towctrans, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c towlower */
#define P99_IS_EQ_towlower(...) P99_TOK_EQ(towlower, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c towupper */
#define P99_IS_EQ_towupper(...) P99_TOK_EQ(towupper, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c typedef */
#define P99_IS_EQ_typedef(...) P99_TOK_EQ(typedef, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c uint16_t */
#define P99_IS_EQ_uint16_t(...) P99_TOK_EQ(uint16_t, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c uint32_t */
#define P99_IS_EQ_uint32_t(...) P99_TOK_EQ(uint32_t, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c uint64_t */
#define P99_IS_EQ_uint64_t(...) P99_TOK_EQ(uint64_t, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c uint8_t */
#define P99_IS_EQ_uint8_t(...) P99_TOK_EQ(uint8_t, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c uintfast16_t */
#define P99_IS_EQ_uintfast16_t(...) P99_TOK_EQ(uintfast16_t, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c uintfast32_t */
#define P99_IS_EQ_uintfast32_t(...) P99_TOK_EQ(uintfast32_t, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c uintfast64_t */
#define P99_IS_EQ_uintfast64_t(...) P99_TOK_EQ(uintfast64_t, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c uintfast8_t */
#define P99_IS_EQ_uintfast8_t(...) P99_TOK_EQ(uintfast8_t, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c uintleast16_t */
#define P99_IS_EQ_uintleast16_t(...) P99_TOK_EQ(uintleast16_t, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c uintleast32_t */
#define P99_IS_EQ_uintleast32_t(...) P99_TOK_EQ(uintleast32_t, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c uintleast64_t */
#define P99_IS_EQ_uintleast64_t(...) P99_TOK_EQ(uintleast64_t, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c uintleast8_t */
#define P99_IS_EQ_uintleast8_t(...) P99_TOK_EQ(uintleast8_t, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c uintmax_t */
#define P99_IS_EQ_uintmax_t(...) P99_TOK_EQ(uintmax_t, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c uintptr_t */
#define P99_IS_EQ_uintptr_t(...) P99_TOK_EQ(uintptr_t, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c ungetc */
#define P99_IS_EQ_ungetc(...) P99_TOK_EQ(ungetc, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c ungetwc */
#define P99_IS_EQ_ungetwc(...) P99_TOK_EQ(ungetwc, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c union */
#define P99_IS_EQ_union(...) P99_TOK_EQ(union, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c unsigned */
#define P99_IS_EQ_unsigned(...) P99_TOK_EQ(unsigned, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c va_arg */
#define P99_IS_EQ_va_arg(...) P99_TOK_EQ(va_arg, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c va_copy */
#define P99_IS_EQ_va_copy(...) P99_TOK_EQ(va_copy, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c va_end */
#define P99_IS_EQ_va_end(...) P99_TOK_EQ(va_end, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c va_start */
#define P99_IS_EQ_va_start(...) P99_TOK_EQ(va_start, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c vfprintf */
#define P99_IS_EQ_vfprintf(...) P99_TOK_EQ(vfprintf, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c vfscanf */
#define P99_IS_EQ_vfscanf(...) P99_TOK_EQ(vfscanf, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c vfwprintf */
#define P99_IS_EQ_vfwprintf(...) P99_TOK_EQ(vfwprintf, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c void */
#define P99_IS_EQ_void(...) P99_TOK_EQ(void, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c volatile */
#define P99_IS_EQ_volatile(...) P99_TOK_EQ(volatile, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c vprintf */
#define P99_IS_EQ_vprintf(...) P99_TOK_EQ(vprintf, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c vscanf */
#define P99_IS_EQ_vscanf(...) P99_TOK_EQ(vscanf, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c vsprintf */
#define P99_IS_EQ_vsprintf(...) P99_TOK_EQ(vsprintf, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c vsscanf */
#define P99_IS_EQ_vsscanf(...) P99_TOK_EQ(vsscanf, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c vswprintf */
#define P99_IS_EQ_vswprintf(...) P99_TOK_EQ(vswprintf, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c vwprintf */
#define P99_IS_EQ_vwprintf(...) P99_TOK_EQ(vwprintf, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c wchar_t */
#define P99_IS_EQ_wchar_t(...) P99_TOK_EQ(wchar_t, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c wcrtomb */
#define P99_IS_EQ_wcrtomb(...) P99_TOK_EQ(wcrtomb, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c wcscat */
#define P99_IS_EQ_wcscat(...) P99_TOK_EQ(wcscat, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c wcschr */
#define P99_IS_EQ_wcschr(...) P99_TOK_EQ(wcschr, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c wcscmp */
#define P99_IS_EQ_wcscmp(...) P99_TOK_EQ(wcscmp, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c wcscoll */
#define P99_IS_EQ_wcscoll(...) P99_TOK_EQ(wcscoll, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c wcscpy */
#define P99_IS_EQ_wcscpy(...) P99_TOK_EQ(wcscpy, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c wcscspn */
#define P99_IS_EQ_wcscspn(...) P99_TOK_EQ(wcscspn, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c wcsftime */
#define P99_IS_EQ_wcsftime(...) P99_TOK_EQ(wcsftime, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c wcslen */
#define P99_IS_EQ_wcslen(...) P99_TOK_EQ(wcslen, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c wcsncat */
#define P99_IS_EQ_wcsncat(...) P99_TOK_EQ(wcsncat, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c wcsncmp */
#define P99_IS_EQ_wcsncmp(...) P99_TOK_EQ(wcsncmp, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c wcsncpy */
#define P99_IS_EQ_wcsncpy(...) P99_TOK_EQ(wcsncpy, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c wcspbrk */
#define P99_IS_EQ_wcspbrk(...) P99_TOK_EQ(wcspbrk, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c wcsrchr */
#define P99_IS_EQ_wcsrchr(...) P99_TOK_EQ(wcsrchr, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c wcsrtombs */
#define P99_IS_EQ_wcsrtombs(...) P99_TOK_EQ(wcsrtombs, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c wcsspn */
#define P99_IS_EQ_wcsspn(...) P99_TOK_EQ(wcsspn, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c wcsstr */
#define P99_IS_EQ_wcsstr(...) P99_TOK_EQ(wcsstr, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c wcstod */
#define P99_IS_EQ_wcstod(...) P99_TOK_EQ(wcstod, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c wcstoimax */
#define P99_IS_EQ_wcstoimax(...) P99_TOK_EQ(wcstoimax, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c wcstok */
#define P99_IS_EQ_wcstok(...) P99_TOK_EQ(wcstok, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c wcstol */
#define P99_IS_EQ_wcstol(...) P99_TOK_EQ(wcstol, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c wcstoul */
#define P99_IS_EQ_wcstoul(...) P99_TOK_EQ(wcstoul, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c wcstoumax */
#define P99_IS_EQ_wcstoumax(...) P99_TOK_EQ(wcstoumax, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c wcsxfrm */
#define P99_IS_EQ_wcsxfrm(...) P99_TOK_EQ(wcsxfrm, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c wctob */
#define P99_IS_EQ_wctob(...) P99_TOK_EQ(wctob, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c wctrans */
#define P99_IS_EQ_wctrans(...) P99_TOK_EQ(wctrans, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c wctrans_t */
#define P99_IS_EQ_wctrans_t(...) P99_TOK_EQ(wctrans_t, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c wctype */
#define P99_IS_EQ_wctype(...) P99_TOK_EQ(wctype, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c wctype_t */
#define P99_IS_EQ_wctype_t(...) P99_TOK_EQ(wctype_t, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c while */
#define P99_IS_EQ_while(...) P99_TOK_EQ(while, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c wint_t */
#define P99_IS_EQ_wint_t(...) P99_TOK_EQ(wint_t, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c wmemchr */
#define P99_IS_EQ_wmemchr(...) P99_TOK_EQ(wmemchr, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c wmemcmp */
#define P99_IS_EQ_wmemcmp(...) P99_TOK_EQ(wmemcmp, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c wmemcpy */
#define P99_IS_EQ_wmemcpy(...) P99_TOK_EQ(wmemcpy, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c wmemmove */
#define P99_IS_EQ_wmemmove(...) P99_TOK_EQ(wmemmove, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c wmemset */
#define P99_IS_EQ_wmemset(...) P99_TOK_EQ(wmemset, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c wprintf */
#define P99_IS_EQ_wprintf(...) P99_TOK_EQ(wprintf, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c wscanf */
#define P99_IS_EQ_wscanf(...) P99_TOK_EQ(wscanf, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 256 */
#define P99_IS_EQ_256(...) P99_TOK_EQ(256, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 512 */
#define P99_IS_EQ_512(...) P99_TOK_EQ(512, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 1024 */
#define P99_IS_EQ_1024(...) P99_TOK_EQ(1024, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 2048 */
#define P99_IS_EQ_2048(...) P99_TOK_EQ(2048, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 4096 */
#define P99_IS_EQ_4096(...) P99_TOK_EQ(4096, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 8192 */
#define P99_IS_EQ_8192(...) P99_TOK_EQ(8192, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 16384 */
#define P99_IS_EQ_16384(...) P99_TOK_EQ(16384, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 32768 */
#define P99_IS_EQ_32768(...) P99_TOK_EQ(32768, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 65536 */
#define P99_IS_EQ_65536(...) P99_TOK_EQ(65536, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 131072 */
#define P99_IS_EQ_131072(...) P99_TOK_EQ(131072, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 262144 */
#define P99_IS_EQ_262144(...) P99_TOK_EQ(262144, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 524288 */
#define P99_IS_EQ_524288(...) P99_TOK_EQ(524288, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 1048576 */
#define P99_IS_EQ_1048576(...) P99_TOK_EQ(1048576, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 2097152 */
#define P99_IS_EQ_2097152(...) P99_TOK_EQ(2097152, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 4194304 */
#define P99_IS_EQ_4194304(...) P99_TOK_EQ(4194304, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 8388608 */
#define P99_IS_EQ_8388608(...) P99_TOK_EQ(8388608, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 16777216 */
#define P99_IS_EQ_16777216(...) P99_TOK_EQ(16777216, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 33554432 */
#define P99_IS_EQ_33554432(...) P99_TOK_EQ(33554432, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 67108864 */
#define P99_IS_EQ_67108864(...) P99_TOK_EQ(67108864, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 134217728 */
#define P99_IS_EQ_134217728(...) P99_TOK_EQ(134217728, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 268435456 */
#define P99_IS_EQ_268435456(...) P99_TOK_EQ(268435456, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 536870912 */
#define P99_IS_EQ_536870912(...) P99_TOK_EQ(536870912, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 1073741824 */
#define P99_IS_EQ_1073741824(...) P99_TOK_EQ(1073741824, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 2147483648 */
#define P99_IS_EQ_2147483648(...) P99_TOK_EQ(2147483648, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 4294967296 */
#define P99_IS_EQ_4294967296(...) P99_TOK_EQ(4294967296, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 8589934592 */
#define P99_IS_EQ_8589934592(...) P99_TOK_EQ(8589934592, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 17179869184 */
#define P99_IS_EQ_17179869184(...) P99_TOK_EQ(17179869184, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 34359738368 */
#define P99_IS_EQ_34359738368(...) P99_TOK_EQ(34359738368, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 68719476736 */
#define P99_IS_EQ_68719476736(...) P99_TOK_EQ(68719476736, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 137438953472 */
#define P99_IS_EQ_137438953472(...) P99_TOK_EQ(137438953472, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 274877906944 */
#define P99_IS_EQ_274877906944(...) P99_TOK_EQ(274877906944, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 549755813888 */
#define P99_IS_EQ_549755813888(...) P99_TOK_EQ(549755813888, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 1099511627776 */
#define P99_IS_EQ_1099511627776(...) P99_TOK_EQ(1099511627776, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 2199023255552 */
#define P99_IS_EQ_2199023255552(...) P99_TOK_EQ(2199023255552, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 4398046511104 */
#define P99_IS_EQ_4398046511104(...) P99_TOK_EQ(4398046511104, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 8796093022208 */
#define P99_IS_EQ_8796093022208(...) P99_TOK_EQ(8796093022208, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 17592186044416 */
#define P99_IS_EQ_17592186044416(...) P99_TOK_EQ(17592186044416, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 35184372088832 */
#define P99_IS_EQ_35184372088832(...) P99_TOK_EQ(35184372088832, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 70368744177664 */
#define P99_IS_EQ_70368744177664(...) P99_TOK_EQ(70368744177664, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 140737488355328 */
#define P99_IS_EQ_140737488355328(...) P99_TOK_EQ(140737488355328, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 281474976710656 */
#define P99_IS_EQ_281474976710656(...) P99_TOK_EQ(281474976710656, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 562949953421312 */
#define P99_IS_EQ_562949953421312(...) P99_TOK_EQ(562949953421312, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 1125899906842624 */
#define P99_IS_EQ_1125899906842624(...) P99_TOK_EQ(1125899906842624, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 2251799813685248 */
#define P99_IS_EQ_2251799813685248(...) P99_TOK_EQ(2251799813685248, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 4503599627370496 */
#define P99_IS_EQ_4503599627370496(...) P99_TOK_EQ(4503599627370496, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 9007199254740992 */
#define P99_IS_EQ_9007199254740992(...) P99_TOK_EQ(9007199254740992, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 18014398509481984 */
#define P99_IS_EQ_18014398509481984(...) P99_TOK_EQ(18014398509481984, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 36028797018963968 */
#define P99_IS_EQ_36028797018963968(...) P99_TOK_EQ(36028797018963968, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 72057594037927936 */
#define P99_IS_EQ_72057594037927936(...) P99_TOK_EQ(72057594037927936, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 144115188075855872 */
#define P99_IS_EQ_144115188075855872(...) P99_TOK_EQ(144115188075855872, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 288230376151711744 */
#define P99_IS_EQ_288230376151711744(...) P99_TOK_EQ(288230376151711744, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 576460752303423488 */
#define P99_IS_EQ_576460752303423488(...) P99_TOK_EQ(576460752303423488, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 1152921504606846976 */
#define P99_IS_EQ_1152921504606846976(...) P99_TOK_EQ(1152921504606846976, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 2305843009213693952 */
#define P99_IS_EQ_2305843009213693952(...) P99_TOK_EQ(2305843009213693952, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 4611686018427387904 */
#define P99_IS_EQ_4611686018427387904(...) P99_TOK_EQ(4611686018427387904, __VA_ARGS__)
/*! @brief Test if the argument consists of exactly the token @c 9223372036854775808 */
#define P99_IS_EQ_9223372036854775808(...) P99_TOK_EQ(9223372036854775808, __VA_ARGS__)
#define P00_EAT_0
#define P00_EAT_1
#define P00_EAT_2
#define P00_EAT_3
#define P00_EAT_4
#define P00_EAT_5
#define P00_EAT_6
#define P00_EAT_7
#define P00_EAT_8
#define P00_EAT_9
#define P00_EAT_10
#define P00_EAT_11
#define P00_EAT_12
#define P00_EAT_13
#define P00_EAT_14
#define P00_EAT_15
#define P00_EAT_16
#define P00_EAT_17
#define P00_EAT_18
#define P00_EAT_19
#define P00_EAT_20
#define P00_EAT_21
#define P00_EAT_22
#define P00_EAT_23
#define P00_EAT_24
#define P00_EAT_25
#define P00_EAT_26
#define P00_EAT_27
#define P00_EAT_28
#define P00_EAT_29
#define P00_EAT_30
#define P00_EAT_31
#define P00_EAT_32
#define P00_EAT_33
#define P00_EAT_34
#define P00_EAT_35
#define P00_EAT_36
#define P00_EAT_37
#define P00_EAT_38
#define P00_EAT_39
#define P00_EAT_40
#define P00_EAT_41
#define P00_EAT_42
#define P00_EAT_43
#define P00_EAT_44
#define P00_EAT_45
#define P00_EAT_46
#define P00_EAT_47
#define P00_EAT_48
#define P00_EAT_49
#define P00_EAT_50
#define P00_EAT_51
#define P00_EAT_52
#define P00_EAT_53
#define P00_EAT_54
#define P00_EAT_55
#define P00_EAT_56
#define P00_EAT_57
#define P00_EAT_58
#define P00_EAT_59
#define P00_EAT_60
#define P00_EAT_61
#define P00_EAT_62
#define P00_EAT_63
#define P00_EAT_64
#define P00_EAT_65
#define P00_EAT_66
#define P00_EAT_67
#define P00_EAT_68
#define P00_EAT_69
#define P00_EAT_70
#define P00_EAT_71
#define P00_EAT_72
#define P00_EAT_73
#define P00_EAT_74
#define P00_EAT_75
#define P00_EAT_76
#define P00_EAT_77
#define P00_EAT_78
#define P00_EAT_79
#define P00_EAT_80
#define P00_EAT_81
#define P00_EAT_82
#define P00_EAT_83
#define P00_EAT_84
#define P00_EAT_85
#define P00_EAT_86
#define P00_EAT_87
#define P00_EAT_88
#define P00_EAT_89
#define P00_EAT_90
#define P00_EAT_91
#define P00_EAT_92
#define P00_EAT_93
#define P00_EAT_94
#define P00_EAT_95
#define P00_EAT_96
#define P00_EAT_97
#define P00_EAT_98
#define P00_EAT_99
#define P00_EAT_100
#define P00_EAT_101
#define P00_EAT_102
#define P00_EAT_103
#define P00_EAT_104
#define P00_EAT_105
#define P00_EAT_106
#define P00_EAT_107
#define P00_EAT_108
#define P00_EAT_109
#define P00_EAT_110
#define P00_EAT_111
#define P00_EAT_112
#define P00_EAT_113
#define P00_EAT_114
#define P00_EAT_115
#define P00_EAT_116
#define P00_EAT_117
#define P00_EAT_118
#define P00_EAT_119
#define P00_EAT_120
#define P00_EAT_121
#define P00_EAT_122
#define P00_EAT_123
#define P00_EAT_124
#define P00_EAT_125
#define P00_EAT_126
#define P00_EAT_127
#define P00_EAT_128
#define P00_EAT_129
#define P00_EAT_130
#define P00_EAT_131
#define P00_EAT_132
#define P00_EAT_133
#define P00_EAT_134
#define P00_EAT_135
#define P00_EAT_136
#define P00_EAT_137
#define P00_EAT_138
#define P00_EAT_139
#define P00_EAT_140
#define P00_EAT_141
#define P00_EAT_142
#define P00_EAT_143
#define P00_EAT_144
#define P00_EAT_145
#define P00_EAT_146
#define P00_EAT_147
#define P00_EAT_148
#define P00_EAT_149
#define P00_EAT_150
#define P00_EAT_151
#define P00_EAT_152
#define P00_EAT_153
#define P00_EAT_154
#define P00_EAT_155
#define P00_EAT_156
#define P00_EAT_157
#define P00_EAT_158
#define P00_EAT_159
#define P00_EAT__Bool
#define P00_EAT__Complex
#define P00_EAT__Exit
#define P00_EAT__Imaginary
#define P00_EAT_abort
#define P00_EAT_abs
#define P00_EAT_acos
#define P00_EAT_asctime
#define P00_EAT_asin
#define P00_EAT_assert
#define P00_EAT_atan
#define P00_EAT_atan2
#define P00_EAT_atexit
#define P00_EAT_atof
#define P00_EAT_atoi
#define P00_EAT_atol
#define P00_EAT_auto
#define P00_EAT_break
#define P00_EAT_bsearch
#define P00_EAT_btowc
#define P00_EAT_cabs
#define P00_EAT_cacos
#define P00_EAT_cacosh
#define P00_EAT_calloc
#define P00_EAT_carg
#define P00_EAT_case
#define P00_EAT_casin
#define P00_EAT_casinh
#define P00_EAT_catan
#define P00_EAT_catanh
#define P00_EAT_ccos
#define P00_EAT_ccosh
#define P00_EAT_ceil
#define P00_EAT_cexp
#define P00_EAT_char
#define P00_EAT_cimag
#define P00_EAT_clearerr
#define P00_EAT_clock
#define P00_EAT_clock_t
#define P00_EAT_clog
#define P00_EAT_conj
#define P00_EAT_const
#define P00_EAT_continue
#define P00_EAT_cos
#define P00_EAT_cosh
#define P00_EAT_cpow
#define P00_EAT_cproj
#define P00_EAT_creal
#define P00_EAT_csin
#define P00_EAT_csinh
#define P00_EAT_csqrt
#define P00_EAT_ctan
#define P00_EAT_ctanh
#define P00_EAT_ctime
#define P00_EAT_default
#define P00_EAT_difftime
#define P00_EAT_div
#define P00_EAT_div_t
#define P00_EAT_do
#define P00_EAT_double
#define P00_EAT_double_t
#define P00_EAT_else
#define P00_EAT_enum
#define P00_EAT_exit
#define P00_EAT_exp
#define P00_EAT_extern
#define P00_EAT_fabs
#define P00_EAT_fclose
#define P00_EAT_fdopen
#define P00_EAT_fenv_t
#define P00_EAT_feof
#define P00_EAT_ferror
#define P00_EAT_fexcept_t
#define P00_EAT_fflush
#define P00_EAT_fgetc
#define P00_EAT_fgetpos
#define P00_EAT_fgets
#define P00_EAT_fgetwc
#define P00_EAT_fgetws
#define P00_EAT_float
#define P00_EAT_float_t
#define P00_EAT_floor
#define P00_EAT_fopen
#define P00_EAT_for
#define P00_EAT_fpos_t
#define P00_EAT_fprintf
#define P00_EAT_fputc
#define P00_EAT_fputchar
#define P00_EAT_fputs
#define P00_EAT_fputwc
#define P00_EAT_fputws
#define P00_EAT_fread
#define P00_EAT_free
#define P00_EAT_freopen
#define P00_EAT_frexp
#define P00_EAT_fscanf
#define P00_EAT_fseek
#define P00_EAT_fsetpos
#define P00_EAT_ftell
#define P00_EAT_fwide
#define P00_EAT_fwprintf
#define P00_EAT_fwrite
#define P00_EAT_fwscanf
#define P00_EAT_getaddrinfo
#define P00_EAT_getc
#define P00_EAT_getchar
#define P00_EAT_getenv
#define P00_EAT_getnameinfo
#define P00_EAT_gets
#define P00_EAT_getwc
#define P00_EAT_getwchar
#define P00_EAT_gmtime
#define P00_EAT_goto
#define P00_EAT_if
#define P00_EAT_imaxabs
#define P00_EAT_imaxdiv
#define P00_EAT_imaxdiv_t
#define P00_EAT_inline
#define P00_EAT_int
#define P00_EAT_int16_t
#define P00_EAT_int32_t
#define P00_EAT_int64_t
#define P00_EAT_int8_t
#define P00_EAT_intfast16_t
#define P00_EAT_intfast32_t
#define P00_EAT_intfast64_t
#define P00_EAT_intfast8_t
#define P00_EAT_intleast16_t
#define P00_EAT_intleast32_t
#define P00_EAT_intleast64_t
#define P00_EAT_intleast8_t
#define P00_EAT_intmax_t
#define P00_EAT_intptr_t
#define P00_EAT_isalnum
#define P00_EAT_isalpha
#define P00_EAT_isblank
#define P00_EAT_iscntrl
#define P00_EAT_isdigit
#define P00_EAT_isgraph
#define P00_EAT_islower
#define P00_EAT_isprint
#define P00_EAT_ispunct
#define P00_EAT_isspace
#define P00_EAT_isupper
#define P00_EAT_iswalnum
#define P00_EAT_iswalpha
#define P00_EAT_iswcntrl
#define P00_EAT_iswctype
#define P00_EAT_iswdigit
#define P00_EAT_iswgraph
#define P00_EAT_iswlower
#define P00_EAT_iswprint
#define P00_EAT_iswpunct
#define P00_EAT_iswspace
#define P00_EAT_iswupper
#define P00_EAT_iswxdigit
#define P00_EAT_isxdigit
#define P00_EAT_labs
#define P00_EAT_ldexp
#define P00_EAT_ldiv
#define P00_EAT_ldiv_t
#define P00_EAT_lldiv_t
#define P00_EAT_localeconv
#define P00_EAT_localtime
#define P00_EAT_log
#define P00_EAT_log10
#define P00_EAT_long
#define P00_EAT_longjmp
#define P00_EAT_malloc
#define P00_EAT_mbrlen
#define P00_EAT_mbrtowc
#define P00_EAT_mbsinit
#define P00_EAT_mbsrtowcs
#define P00_EAT_mbstate_t
#define P00_EAT_memchr
#define P00_EAT_memcmp
#define P00_EAT_memcpy
#define P00_EAT_memmove
#define P00_EAT_memset
#define P00_EAT_mktime
#define P00_EAT_modf
#define P00_EAT_off_t
#define P00_EAT_offsetof
#define P00_EAT_perror
#define P00_EAT_pow
#define P00_EAT_printf
#define P00_EAT_ptrdiff_t
#define P00_EAT_putc
#define P00_EAT_putchar
#define P00_EAT_puts
#define P00_EAT_putwc
#define P00_EAT_putwchar
#define P00_EAT_qsort
#define P00_EAT_raise
#define P00_EAT_rand
#define P00_EAT_realloc
#define P00_EAT_register
#define P00_EAT_remove
#define P00_EAT_rename
#define P00_EAT_restrict
#define P00_EAT_return
#define P00_EAT_rewind
#define P00_EAT_scanf
#define P00_EAT_setbuf
#define P00_EAT_setjmp
#define P00_EAT_setlocale
#define P00_EAT_setvbuf
#define P00_EAT_short
#define P00_EAT_sig_atomic_t
#define P00_EAT_signed
#define P00_EAT_sin
#define P00_EAT_sinh
#define P00_EAT_size_t
#define P00_EAT_sizeof
#define P00_EAT_snprintf
#define P00_EAT_sprintf
#define P00_EAT_sqrt
#define P00_EAT_srand
#define P00_EAT_sscanf
#define P00_EAT_ssize_t
#define P00_EAT_static
#define P00_EAT_strcat
#define P00_EAT_strchr
#define P00_EAT_strcmp
#define P00_EAT_strcoll
#define P00_EAT_strcpy
#define P00_EAT_strcspn
#define P00_EAT_strerror
#define P00_EAT_strftime
#define P00_EAT_strlen
#define P00_EAT_strncat
#define P00_EAT_strncmp
#define P00_EAT_strncpy
#define P00_EAT_strpbrk
#define P00_EAT_strrchr
#define P00_EAT_strspn
#define P00_EAT_strstr
#define P00_EAT_strtod
#define P00_EAT_strtoimax
#define P00_EAT_strtok
#define P00_EAT_strtol
#define P00_EAT_strtoul
#define P00_EAT_strtoumax
#define P00_EAT_struct
#define P00_EAT_strxfrm
#define P00_EAT_switch
#define P00_EAT_swprintf
#define P00_EAT_swscanf
#define P00_EAT_system
#define P00_EAT_tan
#define P00_EAT_tanh
#define P00_EAT_time
#define P00_EAT_time_t
#define P00_EAT_tmpfile
#define P00_EAT_tmpnam
#define P00_EAT_tolower
#define P00_EAT_toupper
#define P00_EAT_towctrans
#define P00_EAT_towlower
#define P00_EAT_towupper
#define P00_EAT_typedef
#define P00_EAT_uint16_t
#define P00_EAT_uint32_t
#define P00_EAT_uint64_t
#define P00_EAT_uint8_t
#define P00_EAT_uintfast16_t
#define P00_EAT_uintfast32_t
#define P00_EAT_uintfast64_t
#define P00_EAT_uintfast8_t
#define P00_EAT_uintleast16_t
#define P00_EAT_uintleast32_t
#define P00_EAT_uintleast64_t
#define P00_EAT_uintleast8_t
#define P00_EAT_uintmax_t
#define P00_EAT_uintptr_t
#define P00_EAT_ungetc
#define P00_EAT_ungetwc
#define P00_EAT_union
#define P00_EAT_unsigned
#define P00_EAT_va_arg
#define P00_EAT_va_copy
#define P00_EAT_va_end
#define P00_EAT_va_start
#define P00_EAT_vfprintf
#define P00_EAT_vfscanf
#define P00_EAT_vfwprintf
#define P00_EAT_void
#define P00_EAT_volatile
#define P00_EAT_vprintf
#define P00_EAT_vscanf
#define P00_EAT_vsprintf
#define P00_EAT_vsscanf
#define P00_EAT_vswprintf
#define P00_EAT_vwprintf
#define P00_EAT_wchar_t
#define P00_EAT_wcrtomb
#define P00_EAT_wcscat
#define P00_EAT_wcschr
#define P00_EAT_wcscmp
#define P00_EAT_wcscoll
#define P00_EAT_wcscpy
#define P00_EAT_wcscspn
#define P00_EAT_wcsftime
#define P00_EAT_wcslen
#define P00_EAT_wcsncat
#define P00_EAT_wcsncmp
#define P00_EAT_wcsncpy
#define P00_EAT_wcspbrk
#define P00_EAT_wcsrchr
#define P00_EAT_wcsrtombs
#define P00_EAT_wcsspn
#define P00_EAT_wcsstr
#define P00_EAT_wcstod
#define P00_EAT_wcstoimax
#define P00_EAT_wcstok
#define P00_EAT_wcstol
#define P00_EAT_wcstoul
#define P00_EAT_wcstoumax
#define P00_EAT_wcsxfrm
#define P00_EAT_wctob
#define P00_EAT_wctrans
#define P00_EAT_wctrans_t
#define P00_EAT_wctype
#define P00_EAT_wctype_t
#define P00_EAT_while
#define P00_EAT_wint_t
#define P00_EAT_wmemchr
#define P00_EAT_wmemcmp
#define P00_EAT_wmemcpy
#define P00_EAT_wmemmove
#define P00_EAT_wmemset
#define P00_EAT_wprintf
#define P00_EAT_wscanf
#define P00_EAT_256
#define P00_EAT_512
#define P00_EAT_1024
#define P00_EAT_2048
#define P00_EAT_4096
#define P00_EAT_8192
#define P00_EAT_16384
#define P00_EAT_32768
#define P00_EAT_65536
#define P00_EAT_131072
#define P00_EAT_262144
#define P00_EAT_524288
#define P00_EAT_1048576
#define P00_EAT_2097152
#define P00_EAT_4194304
#define P00_EAT_8388608
#define P00_EAT_16777216
#define P00_EAT_33554432
#define P00_EAT_67108864
#define P00_EAT_134217728
#define P00_EAT_268435456
#define P00_EAT_536870912
#define P00_EAT_1073741824
#define P00_EAT_2147483648
#define P00_EAT_4294967296
#define P00_EAT_8589934592
#define P00_EAT_17179869184
#define P00_EAT_34359738368
#define P00_EAT_68719476736
#define P00_EAT_137438953472
#define P00_EAT_274877906944
#define P00_EAT_549755813888
#define P00_EAT_1099511627776
#define P00_EAT_2199023255552
#define P00_EAT_4398046511104
#define P00_EAT_8796093022208
#define P00_EAT_17592186044416
#define P00_EAT_35184372088832
#define P00_EAT_70368744177664
#define P00_EAT_140737488355328
#define P00_EAT_281474976710656
#define P00_EAT_562949953421312
#define P00_EAT_1125899906842624
#define P00_EAT_2251799813685248
#define P00_EAT_4503599627370496
#define P00_EAT_9007199254740992
#define P00_EAT_18014398509481984
#define P00_EAT_36028797018963968
#define P00_EAT_72057594037927936
#define P00_EAT_144115188075855872
#define P00_EAT_288230376151711744
#define P00_EAT_576460752303423488
#define P00_EAT_1152921504606846976
#define P00_EAT_2305843009213693952
#define P00_EAT_4611686018427387904
#define P00_EAT_9223372036854775808
#define P00_TOKEN_0 ,
#define P00_TOKEN_1 ,
#define P00_TOKEN_2 ,
#define P00_TOKEN_3 ,
#define P00_TOKEN_4 ,
#define P00_TOKEN_5 ,
#define P00_TOKEN_6 ,
#define P00_TOKEN_7 ,
#define P00_TOKEN_8 ,
#define P00_TOKEN_9 ,
#define P00_TOKEN_10 ,
#define P00_TOKEN_11 ,
#define P00_TOKEN_12 ,
#define P00_TOKEN_13 ,
#define P00_TOKEN_14 ,
#define P00_TOKEN_15 ,
#define P00_TOKEN_16 ,
#define P00_TOKEN_17 ,
#define P00_TOKEN_18 ,
#define P00_TOKEN_19 ,
#define P00_TOKEN_20 ,
#define P00_TOKEN_21 ,
#define P00_TOKEN_22 ,
#define P00_TOKEN_23 ,
#define P00_TOKEN_24 ,
#define P00_TOKEN_25 ,
#define P00_TOKEN_26 ,
#define P00_TOKEN_27 ,
#define P00_TOKEN_28 ,
#define P00_TOKEN_29 ,
#define P00_TOKEN_30 ,
#define P00_TOKEN_31 ,
#define P00_TOKEN_32 ,
#define P00_TOKEN_33 ,
#define P00_TOKEN_34 ,
#define P00_TOKEN_35 ,
#define P00_TOKEN_36 ,
#define P00_TOKEN_37 ,
#define P00_TOKEN_38 ,
#define P00_TOKEN_39 ,
#define P00_TOKEN_40 ,
#define P00_TOKEN_41 ,
#define P00_TOKEN_42 ,
#define P00_TOKEN_43 ,
#define P00_TOKEN_44 ,
#define P00_TOKEN_45 ,
#define P00_TOKEN_46 ,
#define P00_TOKEN_47 ,
#define P00_TOKEN_48 ,
#define P00_TOKEN_49 ,
#define P00_TOKEN_50 ,
#define P00_TOKEN_51 ,
#define P00_TOKEN_52 ,
#define P00_TOKEN_53 ,
#define P00_TOKEN_54 ,
#define P00_TOKEN_55 ,
#define P00_TOKEN_56 ,
#define P00_TOKEN_57 ,
#define P00_TOKEN_58 ,
#define P00_TOKEN_59 ,
#define P00_TOKEN_60 ,
#define P00_TOKEN_61 ,
#define P00_TOKEN_62 ,
#define P00_TOKEN_63 ,
#define P00_TOKEN_64 ,
#define P00_TOKEN_65 ,
#define P00_TOKEN_66 ,
#define P00_TOKEN_67 ,
#define P00_TOKEN_68 ,
#define P00_TOKEN_69 ,
#define P00_TOKEN_70 ,
#define P00_TOKEN_71 ,
#define P00_TOKEN_72 ,
#define P00_TOKEN_73 ,
#define P00_TOKEN_74 ,
#define P00_TOKEN_75 ,
#define P00_TOKEN_76 ,
#define P00_TOKEN_77 ,
#define P00_TOKEN_78 ,
#define P00_TOKEN_79 ,
#define P00_TOKEN_80 ,
#define P00_TOKEN_81 ,
#define P00_TOKEN_82 ,
#define P00_TOKEN_83 ,
#define P00_TOKEN_84 ,
#define P00_TOKEN_85 ,
#define P00_TOKEN_86 ,
#define P00_TOKEN_87 ,
#define P00_TOKEN_88 ,
#define P00_TOKEN_89 ,
#define P00_TOKEN_90 ,
#define P00_TOKEN_91 ,
#define P00_TOKEN_92 ,
#define P00_TOKEN_93 ,
#define P00_TOKEN_94 ,
#define P00_TOKEN_95 ,
#define P00_TOKEN_96 ,
#define P00_TOKEN_97 ,
#define P00_TOKEN_98 ,
#define P00_TOKEN_99 ,
#define P00_TOKEN_100 ,
#define P00_TOKEN_101 ,
#define P00_TOKEN_102 ,
#define P00_TOKEN_103 ,
#define P00_TOKEN_104 ,
#define P00_TOKEN_105 ,
#define P00_TOKEN_106 ,
#define P00_TOKEN_107 ,
#define P00_TOKEN_108 ,
#define P00_TOKEN_109 ,
#define P00_TOKEN_110 ,
#define P00_TOKEN_111 ,
#define P00_TOKEN_112 ,
#define P00_TOKEN_113 ,
#define P00_TOKEN_114 ,
#define P00_TOKEN_115 ,
#define P00_TOKEN_116 ,
#define P00_TOKEN_117 ,
#define P00_TOKEN_118 ,
#define P00_TOKEN_119 ,
#define P00_TOKEN_120 ,
#define P00_TOKEN_121 ,
#define P00_TOKEN_122 ,
#define P00_TOKEN_123 ,
#define P00_TOKEN_124 ,
#define P00_TOKEN_125 ,
#define P00_TOKEN_126 ,
#define P00_TOKEN_127 ,
#define P00_TOKEN_128 ,
#define P00_TOKEN_129 ,
#define P00_TOKEN_130 ,
#define P00_TOKEN_131 ,
#define P00_TOKEN_132 ,
#define P00_TOKEN_133 ,
#define P00_TOKEN_134 ,
#define P00_TOKEN_135 ,
#define P00_TOKEN_136 ,
#define P00_TOKEN_137 ,
#define P00_TOKEN_138 ,
#define P00_TOKEN_139 ,
#define P00_TOKEN_140 ,
#define P00_TOKEN_141 ,
#define P00_TOKEN_142 ,
#define P00_TOKEN_143 ,
#define P00_TOKEN_144 ,
#define P00_TOKEN_145 ,
#define P00_TOKEN_146 ,
#define P00_TOKEN_147 ,
#define P00_TOKEN_148 ,
#define P00_TOKEN_149 ,
#define P00_TOKEN_150 ,
#define P00_TOKEN_151 ,
#define P00_TOKEN_152 ,
#define P00_TOKEN_153 ,
#define P00_TOKEN_154 ,
#define P00_TOKEN_155 ,
#define P00_TOKEN_156 ,
#define P00_TOKEN_157 ,
#define P00_TOKEN_158 ,
#define P00_TOKEN_159 ,
#define P00_TOKEN__Bool ,
#define P00_TOKEN__Complex ,
#define P00_TOKEN__Exit ,
#define P00_TOKEN__Imaginary ,
#define P00_TOKEN_abort ,
#define P00_TOKEN_abs ,
#define P00_TOKEN_acos ,
#define P00_TOKEN_asctime ,
#define P00_TOKEN_asin ,
#define P00_TOKEN_assert ,
#define P00_TOKEN_atan ,
#define P00_TOKEN_atan2 ,
#define P00_TOKEN_atexit ,
#define P00_TOKEN_atof ,
#define P00_TOKEN_atoi ,
#define P00_TOKEN_atol ,
#define P00_TOKEN_auto ,
#define P00_TOKEN_break ,
#define P00_TOKEN_bsearch ,
#define P00_TOKEN_btowc ,
#define P00_TOKEN_cabs ,
#define P00_TOKEN_cacos ,
#define P00_TOKEN_cacosh ,
#define P00_TOKEN_calloc ,
#define P00_TOKEN_carg ,
#define P00_TOKEN_case ,
#define P00_TOKEN_casin ,
#define P00_TOKEN_casinh ,
#define P00_TOKEN_catan ,
#define P00_TOKEN_catanh ,
#define P00_TOKEN_ccos ,
#define P00_TOKEN_ccosh ,
#define P00_TOKEN_ceil ,
#define P00_TOKEN_cexp ,
#define P00_TOKEN_char ,
#define P00_TOKEN_cimag ,
#define P00_TOKEN_clearerr ,
#define P00_TOKEN_clock ,
#define P00_TOKEN_clock_t ,
#define P00_TOKEN_clog ,
#define P00_TOKEN_conj ,
#define P00_TOKEN_const ,
#define P00_TOKEN_continue ,
#define P00_TOKEN_cos ,
#define P00_TOKEN_cosh ,
#define P00_TOKEN_cpow ,
#define P00_TOKEN_cproj ,
#define P00_TOKEN_creal ,
#define P00_TOKEN_csin ,
#define P00_TOKEN_csinh ,
#define P00_TOKEN_csqrt ,
#define P00_TOKEN_ctan ,
#define P00_TOKEN_ctanh ,
#define P00_TOKEN_ctime ,
#define P00_TOKEN_default ,
#define P00_TOKEN_difftime ,
#define P00_TOKEN_div ,
#define P00_TOKEN_div_t ,
#define P00_TOKEN_do ,
#define P00_TOKEN_double ,
#define P00_TOKEN_double_t ,
#define P00_TOKEN_else ,
#define P00_TOKEN_enum ,
#define P00_TOKEN_exit ,
#define P00_TOKEN_exp ,
#define P00_TOKEN_extern ,
#define P00_TOKEN_fabs ,
#define P00_TOKEN_fclose ,
#define P00_TOKEN_fdopen ,
#define P00_TOKEN_fenv_t ,
#define P00_TOKEN_feof ,
#define P00_TOKEN_ferror ,
#define P00_TOKEN_fexcept_t ,
#define P00_TOKEN_fflush ,
#define P00_TOKEN_fgetc ,
#define P00_TOKEN_fgetpos ,
#define P00_TOKEN_fgets ,
#define P00_TOKEN_fgetwc ,
#define P00_TOKEN_fgetws ,
#define P00_TOKEN_float ,
#define P00_TOKEN_float_t ,
#define P00_TOKEN_floor ,
#define P00_TOKEN_fopen ,
#define P00_TOKEN_for ,
#define P00_TOKEN_fpos_t ,
#define P00_TOKEN_fprintf ,
#define P00_TOKEN_fputc ,
#define P00_TOKEN_fputchar ,
#define P00_TOKEN_fputs ,
#define P00_TOKEN_fputwc ,
#define P00_TOKEN_fputws ,
#define P00_TOKEN_fread ,
#define P00_TOKEN_free ,
#define P00_TOKEN_freopen ,
#define P00_TOKEN_frexp ,
#define P00_TOKEN_fscanf ,
#define P00_TOKEN_fseek ,
#define P00_TOKEN_fsetpos ,
#define P00_TOKEN_ftell ,
#define P00_TOKEN_fwide ,
#define P00_TOKEN_fwprintf ,
#define P00_TOKEN_fwrite ,
#define P00_TOKEN_fwscanf ,
#define P00_TOKEN_getaddrinfo ,
#define P00_TOKEN_getc ,
#define P00_TOKEN_getchar ,
#define P00_TOKEN_getenv ,
#define P00_TOKEN_getnameinfo ,
#define P00_TOKEN_gets ,
#define P00_TOKEN_getwc ,
#define P00_TOKEN_getwchar ,
#define P00_TOKEN_gmtime ,
#define P00_TOKEN_goto ,
#define P00_TOKEN_if ,
#define P00_TOKEN_imaxabs ,
#define P00_TOKEN_imaxdiv ,
#define P00_TOKEN_imaxdiv_t ,
#define P00_TOKEN_inline ,
#define P00_TOKEN_int ,
#define P00_TOKEN_int16_t ,
#define P00_TOKEN_int32_t ,
#define P00_TOKEN_int64_t ,
#define P00_TOKEN_int8_t ,
#define P00_TOKEN_intfast16_t ,
#define P00_TOKEN_intfast32_t ,
#define P00_TOKEN_intfast64_t ,
#define P00_TOKEN_intfast8_t ,
#define P00_TOKEN_intleast16_t ,
#define P00_TOKEN_intleast32_t ,
#define P00_TOKEN_intleast64_t ,
#define P00_TOKEN_intleast8_t ,
#define P00_TOKEN_intmax_t ,
#define P00_TOKEN_intptr_t ,
#define P00_TOKEN_isalnum ,
#define P00_TOKEN_isalpha ,
#define P00_TOKEN_isblank ,
#define P00_TOKEN_iscntrl ,
#define P00_TOKEN_isdigit ,
#define P00_TOKEN_isgraph ,
#define P00_TOKEN_islower ,
#define P00_TOKEN_isprint ,
#define P00_TOKEN_ispunct ,
#define P00_TOKEN_isspace ,
#define P00_TOKEN_isupper ,
#define P00_TOKEN_iswalnum ,
#define P00_TOKEN_iswalpha ,
#define P00_TOKEN_iswcntrl ,
#define P00_TOKEN_iswctype ,
#define P00_TOKEN_iswdigit ,
#define P00_TOKEN_iswgraph ,
#define P00_TOKEN_iswlower ,
#define P00_TOKEN_iswprint ,
#define P00_TOKEN_iswpunct ,
#define P00_TOKEN_iswspace ,
#define P00_TOKEN_iswupper ,
#define P00_TOKEN_iswxdigit ,
#define P00_TOKEN_isxdigit ,
#define P00_TOKEN_labs ,
#define P00_TOKEN_ldexp ,
#define P00_TOKEN_ldiv ,
#define P00_TOKEN_ldiv_t ,
#define P00_TOKEN_lldiv_t ,
#define P00_TOKEN_localeconv ,
#define P00_TOKEN_localtime ,
#define P00_TOKEN_log ,
#define P00_TOKEN_log10 ,
#define P00_TOKEN_long ,
#define P00_TOKEN_longjmp ,
#define P00_TOKEN_malloc ,
#define P00_TOKEN_mbrlen ,
#define P00_TOKEN_mbrtowc ,
#define P00_TOKEN_mbsinit ,
#define P00_TOKEN_mbsrtowcs ,
#define P00_TOKEN_mbstate_t ,
#define P00_TOKEN_memchr ,
#define P00_TOKEN_memcmp ,
#define P00_TOKEN_memcpy ,
#define P00_TOKEN_memmove ,
#define P00_TOKEN_memset ,
#define P00_TOKEN_mktime ,
#define P00_TOKEN_modf ,
#define P00_TOKEN_off_t ,
#define P00_TOKEN_offsetof ,
#define P00_TOKEN_perror ,
#define P00_TOKEN_pow ,
#define P00_TOKEN_printf ,
#define P00_TOKEN_ptrdiff_t ,
#define P00_TOKEN_putc ,
#define P00_TOKEN_putchar ,
#define P00_TOKEN_puts ,
#define P00_TOKEN_putwc ,
#define P00_TOKEN_putwchar ,
#define P00_TOKEN_qsort ,
#define P00_TOKEN_raise ,
#define P00_TOKEN_rand ,
#define P00_TOKEN_realloc ,
#define P00_TOKEN_register ,
#define P00_TOKEN_remove ,
#define P00_TOKEN_rename ,
#define P00_TOKEN_restrict ,
#define P00_TOKEN_return ,
#define P00_TOKEN_rewind ,
#define P00_TOKEN_scanf ,
#define P00_TOKEN_setbuf ,
#define P00_TOKEN_setjmp ,
#define P00_TOKEN_setlocale ,
#define P00_TOKEN_setvbuf ,
#define P00_TOKEN_short ,
#define P00_TOKEN_sig_atomic_t ,
#define P00_TOKEN_signed ,
#define P00_TOKEN_sin ,
#define P00_TOKEN_sinh ,
#define P00_TOKEN_size_t ,
#define P00_TOKEN_sizeof ,
#define P00_TOKEN_snprintf ,
#define P00_TOKEN_sprintf ,
#define P00_TOKEN_sqrt ,
#define P00_TOKEN_srand ,
#define P00_TOKEN_sscanf ,
#define P00_TOKEN_ssize_t ,
#define P00_TOKEN_static ,
#define P00_TOKEN_strcat ,
#define P00_TOKEN_strchr ,
#define P00_TOKEN_strcmp ,
#define P00_TOKEN_strcoll ,
#define P00_TOKEN_strcpy ,
#define P00_TOKEN_strcspn ,
#define P00_TOKEN_strerror ,
#define P00_TOKEN_strftime ,
#define P00_TOKEN_strlen ,
#define P00_TOKEN_strncat ,
#define P00_TOKEN_strncmp ,
#define P00_TOKEN_strncpy ,
#define P00_TOKEN_strpbrk ,
#define P00_TOKEN_strrchr ,
#define P00_TOKEN_strspn ,
#define P00_TOKEN_strstr ,
#define P00_TOKEN_strtod ,
#define P00_TOKEN_strtoimax ,
#define P00_TOKEN_strtok ,
#define P00_TOKEN_strtol ,
#define P00_TOKEN_strtoul ,
#define P00_TOKEN_strtoumax ,
#define P00_TOKEN_struct ,
#define P00_TOKEN_strxfrm ,
#define P00_TOKEN_switch ,
#define P00_TOKEN_swprintf ,
#define P00_TOKEN_swscanf ,
#define P00_TOKEN_system ,
#define P00_TOKEN_tan ,
#define P00_TOKEN_tanh ,
#define P00_TOKEN_time ,
#define P00_TOKEN_time_t ,
#define P00_TOKEN_tmpfile ,
#define P00_TOKEN_tmpnam ,
#define P00_TOKEN_tolower ,
#define P00_TOKEN_toupper ,
#define P00_TOKEN_towctrans ,
#define P00_TOKEN_towlower ,
#define P00_TOKEN_towupper ,
#define P00_TOKEN_typedef ,
#define P00_TOKEN_uint16_t ,
#define P00_TOKEN_uint32_t ,
#define P00_TOKEN_uint64_t ,
#define P00_TOKEN_uint8_t ,
#define P00_TOKEN_uintfast16_t ,
#define P00_TOKEN_uintfast32_t ,
#define P00_TOKEN_uintfast64_t ,
#define P00_TOKEN_uintfast8_t ,
#define P00_TOKEN_uintleast16_t ,
#define P00_TOKEN_uintleast32_t ,
#define P00_TOKEN_uintleast64_t ,
#define P00_TOKEN_uintleast8_t ,
#define P00_TOKEN_uintmax_t ,
#define P00_TOKEN_uintptr_t ,
#define P00_TOKEN_ungetc ,
#define P00_TOKEN_ungetwc ,
#define P00_TOKEN_union ,
#define P00_TOKEN_unsigned ,
#define P00_TOKEN_va_arg ,
#define P00_TOKEN_va_copy ,
#define P00_TOKEN_va_end ,
#define P00_TOKEN_va_start ,
#define P00_TOKEN_vfprintf ,
#define P00_TOKEN_vfscanf ,
#define P00_TOKEN_vfwprintf ,
#define P00_TOKEN_void ,
#define P00_TOKEN_volatile ,
#define P00_TOKEN_vprintf ,
#define P00_TOKEN_vscanf ,
#define P00_TOKEN_vsprintf ,
#define P00_TOKEN_vsscanf ,
#define P00_TOKEN_vswprintf ,
#define P00_TOKEN_vwprintf ,
#define P00_TOKEN_wchar_t ,
#define P00_TOKEN_wcrtomb ,
#define P00_TOKEN_wcscat ,
#define P00_TOKEN_wcschr ,
#define P00_TOKEN_wcscmp ,
#define P00_TOKEN_wcscoll ,
#define P00_TOKEN_wcscpy ,
#define P00_TOKEN_wcscspn ,
#define P00_TOKEN_wcsftime ,
#define P00_TOKEN_wcslen ,
#define P00_TOKEN_wcsncat ,
#define P00_TOKEN_wcsncmp ,
#define P00_TOKEN_wcsncpy ,
#define P00_TOKEN_wcspbrk ,
#define P00_TOKEN_wcsrchr ,
#define P00_TOKEN_wcsrtombs ,
#define P00_TOKEN_wcsspn ,
#define P00_TOKEN_wcsstr ,
#define P00_TOKEN_wcstod ,
#define P00_TOKEN_wcstoimax ,
#define P00_TOKEN_wcstok ,
#define P00_TOKEN_wcstol ,
#define P00_TOKEN_wcstoul ,
#define P00_TOKEN_wcstoumax ,
#define P00_TOKEN_wcsxfrm ,
#define P00_TOKEN_wctob ,
#define P00_TOKEN_wctrans ,
#define P00_TOKEN_wctrans_t ,
#define P00_TOKEN_wctype ,
#define P00_TOKEN_wctype_t ,
#define P00_TOKEN_while ,
#define P00_TOKEN_wint_t ,
#define P00_TOKEN_wmemchr ,
#define P00_TOKEN_wmemcmp ,
#define P00_TOKEN_wmemcpy ,
#define P00_TOKEN_wmemmove ,
#define P00_TOKEN_wmemset ,
#define P00_TOKEN_wprintf ,
#define P00_TOKEN_wscanf ,
#define P00_TOKEN_256 ,
#define P00_TOKEN_512 ,
#define P00_TOKEN_1024 ,
#define P00_TOKEN_2048 ,
#define P00_TOKEN_4096 ,
#define P00_TOKEN_8192 ,
#define P00_TOKEN_16384 ,
#define P00_TOKEN_32768 ,
#define P00_TOKEN_65536 ,
#define P00_TOKEN_131072 ,
#define P00_TOKEN_262144 ,
#define P00_TOKEN_524288 ,
#define P00_TOKEN_1048576 ,
#define P00_TOKEN_2097152 ,
#define P00_TOKEN_4194304 ,
#define P00_TOKEN_8388608 ,
#define P00_TOKEN_16777216 ,
#define P00_TOKEN_33554432 ,
#define P00_TOKEN_67108864 ,
#define P00_TOKEN_134217728 ,
#define P00_TOKEN_268435456 ,
#define P00_TOKEN_536870912 ,
#define P00_TOKEN_1073741824 ,
#define P00_TOKEN_2147483648 ,
#define P00_TOKEN_4294967296 ,
#define P00_TOKEN_8589934592 ,
#define P00_TOKEN_17179869184 ,
#define P00_TOKEN_34359738368 ,
#define P00_TOKEN_68719476736 ,
#define P00_TOKEN_137438953472 ,
#define P00_TOKEN_274877906944 ,
#define P00_TOKEN_549755813888 ,
#define P00_TOKEN_1099511627776 ,
#define P00_TOKEN_2199023255552 ,
#define P00_TOKEN_4398046511104 ,
#define P00_TOKEN_8796093022208 ,
#define P00_TOKEN_17592186044416 ,
#define P00_TOKEN_35184372088832 ,
#define P00_TOKEN_70368744177664 ,
#define P00_TOKEN_140737488355328 ,
#define P00_TOKEN_281474976710656 ,
#define P00_TOKEN_562949953421312 ,
#define P00_TOKEN_1125899906842624 ,
#define P00_TOKEN_2251799813685248 ,
#define P00_TOKEN_4503599627370496 ,
#define P00_TOKEN_9007199254740992 ,
#define P00_TOKEN_18014398509481984 ,
#define P00_TOKEN_36028797018963968 ,
#define P00_TOKEN_72057594037927936 ,
#define P00_TOKEN_144115188075855872 ,
#define P00_TOKEN_288230376151711744 ,
#define P00_TOKEN_576460752303423488 ,
#define P00_TOKEN_1152921504606846976 ,
#define P00_TOKEN_2305843009213693952 ,
#define P00_TOKEN_4611686018427387904 ,
#define P00_TOKEN_9223372036854775808 ,
#define P00_QUALIFIER_const ,
#define P00_QUALIFIER_restrict ,
#define P00_QUALIFIER_volatile ,
#define P00_VOID_void ,
#define P00_BOOL__Bool ,
#define P00_BOOL_bool ,
#define P00_INTEGER_char ,
#define P00_INTEGER_int ,
#define P00_INTEGER_long ,
#define P00_INTEGER_short ,
#define P00_INTEGER_signed ,
#define P00_INTEGER_unsigned ,
#define P00_REAL_double ,
#define P00_REAL_float ,
#define P00_REAL_long ,
#define P00_FLOAT__Complex ,
#define P00_FLOAT__Imaginary ,
#define P00_FLOAT_double ,
#define P00_FLOAT_float ,
#define P00_FLOAT_long ,
#define P00_TYPE__Bool ,
#define P00_TYPE__Complex ,
#define P00_TYPE__Imaginary ,
#define P00_TYPE_char ,
#define P00_TYPE_const ,
#define P00_TYPE_double ,
#define P00_TYPE_float ,
#define P00_TYPE_int ,
#define P00_TYPE_long ,
#define P00_TYPE_restrict ,
#define P00_TYPE_short ,
#define P00_TYPE_signed ,
#define P00_TYPE_unsigned ,
#define P00_TYPE_void ,
#define P00_TYPE_volatile ,
#define P00_VOID_QUAL_void ,
#define P00_VOID_QUAL_const ,
#define P00_VOID_QUAL_restrict ,
#define P00_VOID_QUAL_volatile ,
#define P00_BOOL_QUAL__Bool ,
#define P00_BOOL_QUAL_bool ,
#define P00_BOOL_QUAL_const ,
#define P00_BOOL_QUAL_restrict ,
#define P00_BOOL_QUAL_volatile ,
#define P00_INTEGER_QUAL_char ,
#define P00_INTEGER_QUAL_int ,
#define P00_INTEGER_QUAL_long ,
#define P00_INTEGER_QUAL_short ,
#define P00_INTEGER_QUAL_signed ,
#define P00_INTEGER_QUAL_unsigned ,
#define P00_INTEGER_QUAL_const ,
#define P00_INTEGER_QUAL_restrict ,
#define P00_INTEGER_QUAL_volatile ,
#define P00_REAL_QUAL_double ,
#define P00_REAL_QUAL_float ,
#define P00_REAL_QUAL_long ,
#define P00_REAL_QUAL_const ,
#define P00_REAL_QUAL_restrict ,
#define P00_REAL_QUAL_volatile ,
#define P00_FLOAT_QUAL__Complex ,
#define P00_FLOAT_QUAL__Imaginary ,
#define P00_FLOAT_QUAL_double ,
#define P00_FLOAT_QUAL_float ,
#define P00_FLOAT_QUAL_long ,
#define P00_FLOAT_QUAL_const ,
#define P00_FLOAT_QUAL_restrict ,
#define P00_FLOAT_QUAL_volatile ,
#define P00_TYPE_QUAL__Bool ,
#define P00_TYPE_QUAL__Complex ,
#define P00_TYPE_QUAL__Imaginary ,
#define P00_TYPE_QUAL_char ,
#define P00_TYPE_QUAL_const ,
#define P00_TYPE_QUAL_double ,
#define P00_TYPE_QUAL_float ,
#define P00_TYPE_QUAL_int ,
#define P00_TYPE_QUAL_long ,
#define P00_TYPE_QUAL_restrict ,
#define P00_TYPE_QUAL_short ,
#define P00_TYPE_QUAL_signed ,
#define P00_TYPE_QUAL_unsigned ,
#define P00_TYPE_QUAL_void ,
#define P00_TYPE_QUAL_volatile ,
#define P00_KEYWORD__Bool ,
#define P00_KEYWORD__Complex ,
#define P00_KEYWORD__Imaginary ,
#define P00_KEYWORD_auto ,
#define P00_KEYWORD_break ,
#define P00_KEYWORD_case ,
#define P00_KEYWORD_char ,
#define P00_KEYWORD_const ,
#define P00_KEYWORD_continue ,
#define P00_KEYWORD_default ,
#define P00_KEYWORD_do ,
#define P00_KEYWORD_double ,
#define P00_KEYWORD_else ,
#define P00_KEYWORD_enum ,
#define P00_KEYWORD_extern ,
#define P00_KEYWORD_float ,
#define P00_KEYWORD_for ,
#define P00_KEYWORD_goto ,
#define P00_KEYWORD_if ,
#define P00_KEYWORD_inline ,
#define P00_KEYWORD_int ,
#define P00_KEYWORD_long ,
#define P00_KEYWORD_register ,
#define P00_KEYWORD_restrict ,
#define P00_KEYWORD_return ,
#define P00_KEYWORD_short ,
#define P00_KEYWORD_signed ,
#define P00_KEYWORD_sizeof ,
#define P00_KEYWORD_static ,
#define P00_KEYWORD_struct ,
#define P00_KEYWORD_switch ,
#define P00_KEYWORD_typedef ,
#define P00_KEYWORD_union ,
#define P00_KEYWORD_unsigned ,
#define P00_KEYWORD_void ,
#define P00_KEYWORD_volatile ,
#define P00_KEYWORD_while ,
#define P00_RESERVED__Bool ,
#define P00_RESERVED__Complex ,
#define P00_RESERVED__Exit ,
#define P00_RESERVED__Imaginary ,
#define P00_RESERVED_abort ,
#define P00_RESERVED_abs ,
#define P00_RESERVED_acos ,
#define P00_RESERVED_asctime ,
#define P00_RESERVED_asin ,
#define P00_RESERVED_assert ,
#define P00_RESERVED_atan ,
#define P00_RESERVED_atan2 ,
#define P00_RESERVED_atexit ,
#define P00_RESERVED_atof ,
#define P00_RESERVED_atoi ,
#define P00_RESERVED_atol ,
#define P00_RESERVED_auto ,
#define P00_RESERVED_break ,
#define P00_RESERVED_bsearch ,
#define P00_RESERVED_btowc ,
#define P00_RESERVED_cabs ,
#define P00_RESERVED_cacos ,
#define P00_RESERVED_cacosh ,
#define P00_RESERVED_calloc ,
#define P00_RESERVED_carg ,
#define P00_RESERVED_case ,
#define P00_RESERVED_casin ,
#define P00_RESERVED_casinh ,
#define P00_RESERVED_catan ,
#define P00_RESERVED_catanh ,
#define P00_RESERVED_ccos ,
#define P00_RESERVED_ccosh ,
#define P00_RESERVED_ceil ,
#define P00_RESERVED_cexp ,
#define P00_RESERVED_char ,
#define P00_RESERVED_cimag ,
#define P00_RESERVED_clearerr ,
#define P00_RESERVED_clock ,
#define P00_RESERVED_clock_t ,
#define P00_RESERVED_clog ,
#define P00_RESERVED_conj ,
#define P00_RESERVED_const ,
#define P00_RESERVED_continue ,
#define P00_RESERVED_cos ,
#define P00_RESERVED_cosh ,
#define P00_RESERVED_cpow ,
#define P00_RESERVED_cproj ,
#define P00_RESERVED_creal ,
#define P00_RESERVED_csin ,
#define P00_RESERVED_csinh ,
#define P00_RESERVED_csqrt ,
#define P00_RESERVED_ctan ,
#define P00_RESERVED_ctanh ,
#define P00_RESERVED_ctime ,
#define P00_RESERVED_default ,
#define P00_RESERVED_difftime ,
#define P00_RESERVED_div ,
#define P00_RESERVED_div_t ,
#define P00_RESERVED_do ,
#define P00_RESERVED_double ,
#define P00_RESERVED_double_t ,
#define P00_RESERVED_else ,
#define P00_RESERVED_enum ,
#define P00_RESERVED_exit ,
#define P00_RESERVED_exp ,
#define P00_RESERVED_extern ,
#define P00_RESERVED_fabs ,
#define P00_RESERVED_fclose ,
#define P00_RESERVED_fdopen ,
#define P00_RESERVED_fenv_t ,
#define P00_RESERVED_feof ,
#define P00_RESERVED_ferror ,
#define P00_RESERVED_fexcept_t ,
#define P00_RESERVED_fflush ,
#define P00_RESERVED_fgetc ,
#define P00_RESERVED_fgetpos ,
#define P00_RESERVED_fgets ,
#define P00_RESERVED_fgetwc ,
#define P00_RESERVED_fgetws ,
#define P00_RESERVED_float ,
#define P00_RESERVED_float_t ,
#define P00_RESERVED_floor ,
#define P00_RESERVED_fopen ,
#define P00_RESERVED_for ,
#define P00_RESERVED_fpos_t ,
#define P00_RESERVED_fprintf ,
#define P00_RESERVED_fputc ,
#define P00_RESERVED_fputchar ,
#define P00_RESERVED_fputs ,
#define P00_RESERVED_fputwc ,
#define P00_RESERVED_fputws ,
#define P00_RESERVED_fread ,
#define P00_RESERVED_free ,
#define P00_RESERVED_freopen ,
#define P00_RESERVED_frexp ,
#define P00_RESERVED_fscanf ,
#define P00_RESERVED_fseek ,
#define P00_RESERVED_fsetpos ,
#define P00_RESERVED_ftell ,
#define P00_RESERVED_fwide ,
#define P00_RESERVED_fwprintf ,
#define P00_RESERVED_fwrite ,
#define P00_RESERVED_fwscanf ,
#define P00_RESERVED_getaddrinfo ,
#define P00_RESERVED_getc ,
#define P00_RESERVED_getchar ,
#define P00_RESERVED_getenv ,
#define P00_RESERVED_getnameinfo ,
#define P00_RESERVED_gets ,
#define P00_RESERVED_getwc ,
#define P00_RESERVED_getwchar ,
#define P00_RESERVED_gmtime ,
#define P00_RESERVED_goto ,
#define P00_RESERVED_if ,
#define P00_RESERVED_imaxabs ,
#define P00_RESERVED_imaxdiv ,
#define P00_RESERVED_imaxdiv_t ,
#define P00_RESERVED_inline ,
#define P00_RESERVED_int ,
#define P00_RESERVED_int16_t ,
#define P00_RESERVED_int32_t ,
#define P00_RESERVED_int64_t ,
#define P00_RESERVED_int8_t ,
#define P00_RESERVED_intfast16_t ,
#define P00_RESERVED_intfast32_t ,
#define P00_RESERVED_intfast64_t ,
#define P00_RESERVED_intfast8_t ,
#define P00_RESERVED_intleast16_t ,
#define P00_RESERVED_intleast32_t ,
#define P00_RESERVED_intleast64_t ,
#define P00_RESERVED_intleast8_t ,
#define P00_RESERVED_intmax_t ,
#define P00_RESERVED_intptr_t ,
#define P00_RESERVED_isalnum ,
#define P00_RESERVED_isalpha ,
#define P00_RESERVED_isblank ,
#define P00_RESERVED_iscntrl ,
#define P00_RESERVED_isdigit ,
#define P00_RESERVED_isgraph ,
#define P00_RESERVED_islower ,
#define P00_RESERVED_isprint ,
#define P00_RESERVED_ispunct ,
#define P00_RESERVED_isspace ,
#define P00_RESERVED_isupper ,
#define P00_RESERVED_iswalnum ,
#define P00_RESERVED_iswalpha ,
#define P00_RESERVED_iswcntrl ,
#define P00_RESERVED_iswctype ,
#define P00_RESERVED_iswdigit ,
#define P00_RESERVED_iswgraph ,
#define P00_RESERVED_iswlower ,
#define P00_RESERVED_iswprint ,
#define P00_RESERVED_iswpunct ,
#define P00_RESERVED_iswspace ,
#define P00_RESERVED_iswupper ,
#define P00_RESERVED_iswxdigit ,
#define P00_RESERVED_isxdigit ,
#define P00_RESERVED_labs ,
#define P00_RESERVED_ldexp ,
#define P00_RESERVED_ldiv ,
#define P00_RESERVED_ldiv_t ,
#define P00_RESERVED_lldiv_t ,
#define P00_RESERVED_localeconv ,
#define P00_RESERVED_localtime ,
#define P00_RESERVED_log ,
#define P00_RESERVED_log10 ,
#define P00_RESERVED_long ,
#define P00_RESERVED_longjmp ,
#define P00_RESERVED_malloc ,
#define P00_RESERVED_mbrlen ,
#define P00_RESERVED_mbrtowc ,
#define P00_RESERVED_mbsinit ,
#define P00_RESERVED_mbsrtowcs ,
#define P00_RESERVED_mbstate_t ,
#define P00_RESERVED_memchr ,
#define P00_RESERVED_memcmp ,
#define P00_RESERVED_memcpy ,
#define P00_RESERVED_memmove ,
#define P00_RESERVED_memset ,
#define P00_RESERVED_mktime ,
#define P00_RESERVED_modf ,
#define P00_RESERVED_off_t ,
#define P00_RESERVED_offsetof ,
#define P00_RESERVED_perror ,
#define P00_RESERVED_pow ,
#define P00_RESERVED_printf ,
#define P00_RESERVED_ptrdiff_t ,
#define P00_RESERVED_putc ,
#define P00_RESERVED_putchar ,
#define P00_RESERVED_puts ,
#define P00_RESERVED_putwc ,
#define P00_RESERVED_putwchar ,
#define P00_RESERVED_qsort ,
#define P00_RESERVED_raise ,
#define P00_RESERVED_rand ,
#define P00_RESERVED_realloc ,
#define P00_RESERVED_register ,
#define P00_RESERVED_remove ,
#define P00_RESERVED_rename ,
#define P00_RESERVED_restrict ,
#define P00_RESERVED_return ,
#define P00_RESERVED_rewind ,
#define P00_RESERVED_scanf ,
#define P00_RESERVED_setbuf ,
#define P00_RESERVED_setjmp ,
#define P00_RESERVED_setlocale ,
#define P00_RESERVED_setvbuf ,
#define P00_RESERVED_short ,
#define P00_RESERVED_sig_atomic_t ,
#define P00_RESERVED_signed ,
#define P00_RESERVED_sin ,
#define P00_RESERVED_sinh ,
#define P00_RESERVED_size_t ,
#define P00_RESERVED_sizeof ,
#define P00_RESERVED_snprintf ,
#define P00_RESERVED_sprintf ,
#define P00_RESERVED_sqrt ,
#define P00_RESERVED_srand ,
#define P00_RESERVED_sscanf ,
#define P00_RESERVED_ssize_t ,
#define P00_RESERVED_static ,
#define P00_RESERVED_strcat ,
#define P00_RESERVED_strchr ,
#define P00_RESERVED_strcmp ,
#define P00_RESERVED_strcoll ,
#define P00_RESERVED_strcpy ,
#define P00_RESERVED_strcspn ,
#define P00_RESERVED_strerror ,
#define P00_RESERVED_strftime ,
#define P00_RESERVED_strlen ,
#define P00_RESERVED_strncat ,
#define P00_RESERVED_strncmp ,
#define P00_RESERVED_strncpy ,
#define P00_RESERVED_strpbrk ,
#define P00_RESERVED_strrchr ,
#define P00_RESERVED_strspn ,
#define P00_RESERVED_strstr ,
#define P00_RESERVED_strtod ,
#define P00_RESERVED_strtoimax ,
#define P00_RESERVED_strtok ,
#define P00_RESERVED_strtol ,
#define P00_RESERVED_strtoul ,
#define P00_RESERVED_strtoumax ,
#define P00_RESERVED_struct ,
#define P00_RESERVED_strxfrm ,
#define P00_RESERVED_switch ,
#define P00_RESERVED_swprintf ,
#define P00_RESERVED_swscanf ,
#define P00_RESERVED_system ,
#define P00_RESERVED_tan ,
#define P00_RESERVED_tanh ,
#define P00_RESERVED_time ,
#define P00_RESERVED_time_t ,
#define P00_RESERVED_tmpfile ,
#define P00_RESERVED_tmpnam ,
#define P00_RESERVED_tolower ,
#define P00_RESERVED_toupper ,
#define P00_RESERVED_towctrans ,
#define P00_RESERVED_towlower ,
#define P00_RESERVED_towupper ,
#define P00_RESERVED_typedef ,
#define P00_RESERVED_uint16_t ,
#define P00_RESERVED_uint32_t ,
#define P00_RESERVED_uint64_t ,
#define P00_RESERVED_uint8_t ,
#define P00_RESERVED_uintfast16_t ,
#define P00_RESERVED_uintfast32_t ,
#define P00_RESERVED_uintfast64_t ,
#define P00_RESERVED_uintfast8_t ,
#define P00_RESERVED_uintleast16_t ,
#define P00_RESERVED_uintleast32_t ,
#define P00_RESERVED_uintleast64_t ,
#define P00_RESERVED_uintleast8_t ,
#define P00_RESERVED_uintmax_t ,
#define P00_RESERVED_uintptr_t ,
#define P00_RESERVED_ungetc ,
#define P00_RESERVED_ungetwc ,
#define P00_RESERVED_union ,
#define P00_RESERVED_unsigned ,
#define P00_RESERVED_va_arg ,
#define P00_RESERVED_va_copy ,
#define P00_RESERVED_va_end ,
#define P00_RESERVED_va_start ,
#define P00_RESERVED_vfprintf ,
#define P00_RESERVED_vfscanf ,
#define P00_RESERVED_vfwprintf ,
#define P00_RESERVED_void ,
#define P00_RESERVED_volatile ,
#define P00_RESERVED_vprintf ,
#define P00_RESERVED_vscanf ,
#define P00_RESERVED_vsprintf ,
#define P00_RESERVED_vsscanf ,
#define P00_RESERVED_vswprintf ,
#define P00_RESERVED_vwprintf ,
#define P00_RESERVED_wchar_t ,
#define P00_RESERVED_wcrtomb ,
#define P00_RESERVED_wcscat ,
#define P00_RESERVED_wcschr ,
#define P00_RESERVED_wcscmp ,
#define P00_RESERVED_wcscoll ,
#define P00_RESERVED_wcscpy ,
#define P00_RESERVED_wcscspn ,
#define P00_RESERVED_wcsftime ,
#define P00_RESERVED_wcslen ,
#define P00_RESERVED_wcsncat ,
#define P00_RESERVED_wcsncmp ,
#define P00_RESERVED_wcsncpy ,
#define P00_RESERVED_wcspbrk ,
#define P00_RESERVED_wcsrchr ,
#define P00_RESERVED_wcsrtombs ,
#define P00_RESERVED_wcsspn ,
#define P00_RESERVED_wcsstr ,
#define P00_RESERVED_wcstod ,
#define P00_RESERVED_wcstoimax ,
#define P00_RESERVED_wcstok ,
#define P00_RESERVED_wcstol ,
#define P00_RESERVED_wcstoul ,
#define P00_RESERVED_wcstoumax ,
#define P00_RESERVED_wcsxfrm ,
#define P00_RESERVED_wctob ,
#define P00_RESERVED_wctrans ,
#define P00_RESERVED_wctrans_t ,
#define P00_RESERVED_wctype ,
#define P00_RESERVED_wctype_t ,
#define P00_RESERVED_while ,
#define P00_RESERVED_wint_t ,
#define P00_RESERVED_wmemchr ,
#define P00_RESERVED_wmemcmp ,
#define P00_RESERVED_wmemcpy ,
#define P00_RESERVED_wmemmove ,
#define P00_RESERVED_wmemset ,
#define P00_RESERVED_wprintf ,
#define P00_RESERVED_wscanf ,
#define P00_RESERVED_256 ,
#define P00_RESERVED_512 ,
#define P00_RESERVED_1024 ,
#define P00_RESERVED_2048 ,
#define P00_RESERVED_4096 ,
#define P00_RESERVED_8192 ,
#define P00_RESERVED_16384 ,
#define P00_RESERVED_32768 ,
#define P00_RESERVED_65536 ,
#define P00_RESERVED_131072 ,
#define P00_RESERVED_262144 ,
#define P00_RESERVED_524288 ,
#define P00_RESERVED_1048576 ,
#define P00_RESERVED_2097152 ,
#define P00_RESERVED_4194304 ,
#define P00_RESERVED_8388608 ,
#define P00_RESERVED_16777216 ,
#define P00_RESERVED_33554432 ,
#define P00_RESERVED_67108864 ,
#define P00_RESERVED_134217728 ,
#define P00_RESERVED_268435456 ,
#define P00_RESERVED_536870912 ,
#define P00_RESERVED_1073741824 ,
#define P00_RESERVED_2147483648 ,
#define P00_RESERVED_4294967296 ,
#define P00_RESERVED_8589934592 ,
#define P00_RESERVED_17179869184 ,
#define P00_RESERVED_34359738368 ,
#define P00_RESERVED_68719476736 ,
#define P00_RESERVED_137438953472 ,
#define P00_RESERVED_274877906944 ,
#define P00_RESERVED_549755813888 ,
#define P00_RESERVED_1099511627776 ,
#define P00_RESERVED_2199023255552 ,
#define P00_RESERVED_4398046511104 ,
#define P00_RESERVED_8796093022208 ,
#define P00_RESERVED_17592186044416 ,
#define P00_RESERVED_35184372088832 ,
#define P00_RESERVED_70368744177664 ,
#define P00_RESERVED_140737488355328 ,
#define P00_RESERVED_281474976710656 ,
#define P00_RESERVED_562949953421312 ,
#define P00_RESERVED_1125899906842624 ,
#define P00_RESERVED_2251799813685248 ,
#define P00_RESERVED_4503599627370496 ,
#define P00_RESERVED_9007199254740992 ,
#define P00_RESERVED_18014398509481984 ,
#define P00_RESERVED_36028797018963968 ,
#define P00_RESERVED_72057594037927936 ,
#define P00_RESERVED_144115188075855872 ,
#define P00_RESERVED_288230376151711744 ,
#define P00_RESERVED_576460752303423488 ,
#define P00_RESERVED_1152921504606846976 ,
#define P00_RESERVED_2305843009213693952 ,
#define P00_RESERVED_4611686018427387904 ,
#define P00_RESERVED_9223372036854775808 ,
#define P00_CONST7(SEQ) P99_IF_ELSE(P99_IS_CONST_TOK(SEQ))(8)(7)
#define P00_CONST6(SEQ) P99_IF_ELSE(P99_IS_CONST_TOK(SEQ))(P00_CONST7(P00_EAT_FIRST(SEQ)))(6)
#define P00_CONST5(SEQ) P99_IF_ELSE(P99_IS_CONST_TOK(SEQ))(P00_CONST6(P00_EAT_FIRST(SEQ)))(5)
#define P00_CONST4(SEQ) P99_IF_ELSE(P99_IS_CONST_TOK(SEQ))(P00_CONST5(P00_EAT_FIRST(SEQ)))(4)
#define P00_CONST3(SEQ) P99_IF_ELSE(P99_IS_CONST_TOK(SEQ))(P00_CONST4(P00_EAT_FIRST(SEQ)))(3)
#define P00_CONST2(SEQ) P99_IF_ELSE(P99_IS_CONST_TOK(SEQ))(P00_CONST3(P00_EAT_FIRST(SEQ)))(2)
#define P00_CONST1(SEQ) P99_IF_ELSE(P99_IS_CONST_TOK(SEQ))(P00_CONST2(P00_EAT_FIRST(SEQ)))(1)
#define P00_CONST_CLASSIFY_7(SEQ) P99_PASTE2(P00_CONST_CLASSIFY_, SEQ) P00_CONST_CLASSIFY_6(P00_EAT_FIRST(SEQ))
#define P00_CONST_CLASSIFY_6(SEQ) P99_PASTE2(P00_CONST_CLASSIFY_, SEQ) P00_CONST_CLASSIFY_5(P00_EAT_FIRST(SEQ))
#define P00_CONST_CLASSIFY_5(SEQ) P99_PASTE2(P00_CONST_CLASSIFY_, SEQ) P00_CONST_CLASSIFY_4(P00_EAT_FIRST(SEQ))
#define P00_CONST_CLASSIFY_4(SEQ) P99_PASTE2(P00_CONST_CLASSIFY_, SEQ) P00_CONST_CLASSIFY_3(P00_EAT_FIRST(SEQ))
#define P00_CONST_CLASSIFY_3(SEQ) P99_PASTE2(P00_CONST_CLASSIFY_, SEQ) P00_CONST_CLASSIFY_2(P00_EAT_FIRST(SEQ))
#define P00_CONST_CLASSIFY_2(SEQ) P99_PASTE2(P00_CONST_CLASSIFY_, SEQ) P00_CONST_CLASSIFY_1(P00_EAT_FIRST(SEQ))
#define P00_CONST_CLASSIFY_1(SEQ) P99_PASTE2(P00_CONST_CLASSIFY_, SEQ)
#define P00_CONST_CLASSIFY___(CODE) P99_IF_ELSE(P00_CONST_VALIDATE(CODE))(P99_PASTE2(P00_CONST_CLASSIFY__, CODE))(INVALID_CONST_TYPE_EXPRESSION[CODE])
#define P00_CONST_CLASSIFY__(N, ...) P00_CONST_CLASSIFY___(P00_NARG(__VA_ARGS__))
#define P00_CONST_CLASSIFY_(N, SEQ) P99_IF_ELSE(P99_IS_EQ_0(N))()(P00_CONST_CLASSIFY__(N, P99_PASTE2(P00_CONST_CLASSIFY_, N)(SEQ)))
/*! @brief Classify the tokens in sequence @a SEQ that all are of kind CONST */
#define P00_CONST_CLASSIFY(SEQ) P00_CONST_CLASSIFY_(P99_CONST_QUAL_LEN(SEQ), SEQ)
/*! @brief Check if @a CODE corresponds to a valid combination of tokens of kind CONST */
#define P00_CONST_VALIDATE(CODE) P99_IS_EQ_2(P99_NARG(P99_PASTE2(P00_CONST_VALIDATE__, CODE)))
/*! @brief Count the number of tokens in sequence @a SEQ that all are of kind CONST */
#define P99_CONST_LEN(SEQ) P99_IF_ELSE(P99_IS_CONST_TOK(SEQ))(P00_CONST1(P00_EAT_FIRST(SEQ)))(0)
/*! @brief Test if the token sequence @a SEQ starts with a token of kind CONST */
#define P99_IS_CONST_TOK(SEQ) P99_HAS_COMMA(P99_PASTE2(P00_CONST_, SEQ))
#define P00_VOLATILE7(SEQ) P99_IF_ELSE(P99_IS_VOLATILE_TOK(SEQ))(8)(7)
#define P00_VOLATILE6(SEQ) P99_IF_ELSE(P99_IS_VOLATILE_TOK(SEQ))(P00_VOLATILE7(P00_EAT_FIRST(SEQ)))(6)
#define P00_VOLATILE5(SEQ) P99_IF_ELSE(P99_IS_VOLATILE_TOK(SEQ))(P00_VOLATILE6(P00_EAT_FIRST(SEQ)))(5)
#define P00_VOLATILE4(SEQ) P99_IF_ELSE(P99_IS_VOLATILE_TOK(SEQ))(P00_VOLATILE5(P00_EAT_FIRST(SEQ)))(4)
#define P00_VOLATILE3(SEQ) P99_IF_ELSE(P99_IS_VOLATILE_TOK(SEQ))(P00_VOLATILE4(P00_EAT_FIRST(SEQ)))(3)
#define P00_VOLATILE2(SEQ) P99_IF_ELSE(P99_IS_VOLATILE_TOK(SEQ))(P00_VOLATILE3(P00_EAT_FIRST(SEQ)))(2)
#define P00_VOLATILE1(SEQ) P99_IF_ELSE(P99_IS_VOLATILE_TOK(SEQ))(P00_VOLATILE2(P00_EAT_FIRST(SEQ)))(1)
#define P00_VOLATILE_CLASSIFY_7(SEQ) P99_PASTE2(P00_VOLATILE_CLASSIFY_, SEQ) P00_VOLATILE_CLASSIFY_6(P00_EAT_FIRST(SEQ))
#define P00_VOLATILE_CLASSIFY_6(SEQ) P99_PASTE2(P00_VOLATILE_CLASSIFY_, SEQ) P00_VOLATILE_CLASSIFY_5(P00_EAT_FIRST(SEQ))
#define P00_VOLATILE_CLASSIFY_5(SEQ) P99_PASTE2(P00_VOLATILE_CLASSIFY_, SEQ) P00_VOLATILE_CLASSIFY_4(P00_EAT_FIRST(SEQ))
#define P00_VOLATILE_CLASSIFY_4(SEQ) P99_PASTE2(P00_VOLATILE_CLASSIFY_, SEQ) P00_VOLATILE_CLASSIFY_3(P00_EAT_FIRST(SEQ))
#define P00_VOLATILE_CLASSIFY_3(SEQ) P99_PASTE2(P00_VOLATILE_CLASSIFY_, SEQ) P00_VOLATILE_CLASSIFY_2(P00_EAT_FIRST(SEQ))
#define P00_VOLATILE_CLASSIFY_2(SEQ) P99_PASTE2(P00_VOLATILE_CLASSIFY_, SEQ) P00_VOLATILE_CLASSIFY_1(P00_EAT_FIRST(SEQ))
#define P00_VOLATILE_CLASSIFY_1(SEQ) P99_PASTE2(P00_VOLATILE_CLASSIFY_, SEQ)
#define P00_VOLATILE_CLASSIFY___(CODE) P99_IF_ELSE(P00_VOLATILE_VALIDATE(CODE))(P99_PASTE2(P00_VOLATILE_CLASSIFY__, CODE))(INVALID_VOLATILE_TYPE_EXPRESSION[CODE])
#define P00_VOLATILE_CLASSIFY__(N, ...) P00_VOLATILE_CLASSIFY___(P00_NARG(__VA_ARGS__))
#define P00_VOLATILE_CLASSIFY_(N, SEQ) P99_IF_ELSE(P99_IS_EQ_0(N))()(P00_VOLATILE_CLASSIFY__(N, P99_PASTE2(P00_VOLATILE_CLASSIFY_, N)(SEQ)))
/*! @brief Classify the tokens in sequence @a SEQ that all are of kind VOLATILE */
#define P00_VOLATILE_CLASSIFY(SEQ) P00_VOLATILE_CLASSIFY_(P99_VOLATILE_QUAL_LEN(SEQ), SEQ)
/*! @brief Check if @a CODE corresponds to a valid combination of tokens of kind VOLATILE */
#define P00_VOLATILE_VALIDATE(CODE) P99_IS_EQ_2(P99_NARG(P99_PASTE2(P00_VOLATILE_VALIDATE__, CODE)))
/*! @brief Count the number of tokens in sequence @a SEQ that all are of kind VOLATILE */
#define P99_VOLATILE_LEN(SEQ) P99_IF_ELSE(P99_IS_VOLATILE_TOK(SEQ))(P00_VOLATILE1(P00_EAT_FIRST(SEQ)))(0)
/*! @brief Test if the token sequence @a SEQ starts with a token of kind VOLATILE */
#define P99_IS_VOLATILE_TOK(SEQ) P99_HAS_COMMA(P99_PASTE2(P00_VOLATILE_, SEQ))
#define P00_RESTRICT7(SEQ) P99_IF_ELSE(P99_IS_RESTRICT_TOK(SEQ))(8)(7)
#define P00_RESTRICT6(SEQ) P99_IF_ELSE(P99_IS_RESTRICT_TOK(SEQ))(P00_RESTRICT7(P00_EAT_FIRST(SEQ)))(6)
#define P00_RESTRICT5(SEQ) P99_IF_ELSE(P99_IS_RESTRICT_TOK(SEQ))(P00_RESTRICT6(P00_EAT_FIRST(SEQ)))(5)
#define P00_RESTRICT4(SEQ) P99_IF_ELSE(P99_IS_RESTRICT_TOK(SEQ))(P00_RESTRICT5(P00_EAT_FIRST(SEQ)))(4)
#define P00_RESTRICT3(SEQ) P99_IF_ELSE(P99_IS_RESTRICT_TOK(SEQ))(P00_RESTRICT4(P00_EAT_FIRST(SEQ)))(3)
#define P00_RESTRICT2(SEQ) P99_IF_ELSE(P99_IS_RESTRICT_TOK(SEQ))(P00_RESTRICT3(P00_EAT_FIRST(SEQ)))(2)
#define P00_RESTRICT1(SEQ) P99_IF_ELSE(P99_IS_RESTRICT_TOK(SEQ))(P00_RESTRICT2(P00_EAT_FIRST(SEQ)))(1)
#define P00_RESTRICT_CLASSIFY_7(SEQ) P99_PASTE2(P00_RESTRICT_CLASSIFY_, SEQ) P00_RESTRICT_CLASSIFY_6(P00_EAT_FIRST(SEQ))
#define P00_RESTRICT_CLASSIFY_6(SEQ) P99_PASTE2(P00_RESTRICT_CLASSIFY_, SEQ) P00_RESTRICT_CLASSIFY_5(P00_EAT_FIRST(SEQ))
#define P00_RESTRICT_CLASSIFY_5(SEQ) P99_PASTE2(P00_RESTRICT_CLASSIFY_, SEQ) P00_RESTRICT_CLASSIFY_4(P00_EAT_FIRST(SEQ))
#define P00_RESTRICT_CLASSIFY_4(SEQ) P99_PASTE2(P00_RESTRICT_CLASSIFY_, SEQ) P00_RESTRICT_CLASSIFY_3(P00_EAT_FIRST(SEQ))
#define P00_RESTRICT_CLASSIFY_3(SEQ) P99_PASTE2(P00_RESTRICT_CLASSIFY_, SEQ) P00_RESTRICT_CLASSIFY_2(P00_EAT_FIRST(SEQ))
#define P00_RESTRICT_CLASSIFY_2(SEQ) P99_PASTE2(P00_RESTRICT_CLASSIFY_, SEQ) P00_RESTRICT_CLASSIFY_1(P00_EAT_FIRST(SEQ))
#define P00_RESTRICT_CLASSIFY_1(SEQ) P99_PASTE2(P00_RESTRICT_CLASSIFY_, SEQ)
#define P00_RESTRICT_CLASSIFY___(CODE) P99_IF_ELSE(P00_RESTRICT_VALIDATE(CODE))(P99_PASTE2(P00_RESTRICT_CLASSIFY__, CODE))(INVALID_RESTRICT_TYPE_EXPRESSION[CODE])
#define P00_RESTRICT_CLASSIFY__(N, ...) P00_RESTRICT_CLASSIFY___(P00_NARG(__VA_ARGS__))
#define P00_RESTRICT_CLASSIFY_(N, SEQ) P99_IF_ELSE(P99_IS_EQ_0(N))()(P00_RESTRICT_CLASSIFY__(N, P99_PASTE2(P00_RESTRICT_CLASSIFY_, N)(SEQ)))
/*! @brief Classify the tokens in sequence @a SEQ that all are of kind RESTRICT */
#define P00_RESTRICT_CLASSIFY(SEQ) P00_RESTRICT_CLASSIFY_(P99_RESTRICT_QUAL_LEN(SEQ), SEQ)
/*! @brief Check if @a CODE corresponds to a valid combination of tokens of kind RESTRICT */
#define P00_RESTRICT_VALIDATE(CODE) P99_IS_EQ_2(P99_NARG(P99_PASTE2(P00_RESTRICT_VALIDATE__, CODE)))
/*! @brief Count the number of tokens in sequence @a SEQ that all are of kind RESTRICT */
#define P99_RESTRICT_LEN(SEQ) P99_IF_ELSE(P99_IS_RESTRICT_TOK(SEQ))(P00_RESTRICT1(P00_EAT_FIRST(SEQ)))(0)
/*! @brief Test if the token sequence @a SEQ starts with a token of kind RESTRICT */
#define P99_IS_RESTRICT_TOK(SEQ) P99_HAS_COMMA(P99_PASTE2(P00_RESTRICT_, SEQ))
#define P00_BOOL7(SEQ) P99_IF_ELSE(P99_IS_BOOL_TOK(SEQ))(8)(7)
#define P00_BOOL6(SEQ) P99_IF_ELSE(P99_IS_BOOL_TOK(SEQ))(P00_BOOL7(P00_EAT_FIRST(SEQ)))(6)
#define P00_BOOL5(SEQ) P99_IF_ELSE(P99_IS_BOOL_TOK(SEQ))(P00_BOOL6(P00_EAT_FIRST(SEQ)))(5)
#define P00_BOOL4(SEQ) P99_IF_ELSE(P99_IS_BOOL_TOK(SEQ))(P00_BOOL5(P00_EAT_FIRST(SEQ)))(4)
#define P00_BOOL3(SEQ) P99_IF_ELSE(P99_IS_BOOL_TOK(SEQ))(P00_BOOL4(P00_EAT_FIRST(SEQ)))(3)
#define P00_BOOL2(SEQ) P99_IF_ELSE(P99_IS_BOOL_TOK(SEQ))(P00_BOOL3(P00_EAT_FIRST(SEQ)))(2)
#define P00_BOOL1(SEQ) P99_IF_ELSE(P99_IS_BOOL_TOK(SEQ))(P00_BOOL2(P00_EAT_FIRST(SEQ)))(1)
#define P00_BOOL_CLASSIFY_7(SEQ) P99_PASTE2(P00_BOOL_CLASSIFY_, SEQ) P00_BOOL_CLASSIFY_6(P00_EAT_FIRST(SEQ))
#define P00_BOOL_CLASSIFY_6(SEQ) P99_PASTE2(P00_BOOL_CLASSIFY_, SEQ) P00_BOOL_CLASSIFY_5(P00_EAT_FIRST(SEQ))
#define P00_BOOL_CLASSIFY_5(SEQ) P99_PASTE2(P00_BOOL_CLASSIFY_, SEQ) P00_BOOL_CLASSIFY_4(P00_EAT_FIRST(SEQ))
#define P00_BOOL_CLASSIFY_4(SEQ) P99_PASTE2(P00_BOOL_CLASSIFY_, SEQ) P00_BOOL_CLASSIFY_3(P00_EAT_FIRST(SEQ))
#define P00_BOOL_CLASSIFY_3(SEQ) P99_PASTE2(P00_BOOL_CLASSIFY_, SEQ) P00_BOOL_CLASSIFY_2(P00_EAT_FIRST(SEQ))
#define P00_BOOL_CLASSIFY_2(SEQ) P99_PASTE2(P00_BOOL_CLASSIFY_, SEQ) P00_BOOL_CLASSIFY_1(P00_EAT_FIRST(SEQ))
#define P00_BOOL_CLASSIFY_1(SEQ) P99_PASTE2(P00_BOOL_CLASSIFY_, SEQ)
#define P00_BOOL_CLASSIFY___(CODE) P99_IF_ELSE(P00_BOOL_VALIDATE(CODE))(P99_PASTE2(P00_BOOL_CLASSIFY__, CODE))(INVALID_BOOL_TYPE_EXPRESSION[CODE])
#define P00_BOOL_CLASSIFY__(N, ...) P00_BOOL_CLASSIFY___(P00_NARG(__VA_ARGS__))
#define P00_BOOL_CLASSIFY_(N, SEQ) P99_IF_ELSE(P99_IS_EQ_0(N))()(P00_BOOL_CLASSIFY__(N, P99_PASTE2(P00_BOOL_CLASSIFY_, N)(SEQ)))
/*! @brief Classify the tokens in sequence @a SEQ that all are of kind BOOL */
#define P00_BOOL_CLASSIFY(SEQ) P00_BOOL_CLASSIFY_(P99_BOOL_QUAL_LEN(SEQ), SEQ)
/*! @brief Check if @a CODE corresponds to a valid combination of tokens of kind BOOL */
#define P00_BOOL_VALIDATE(CODE) P99_IS_EQ_2(P99_NARG(P99_PASTE2(P00_BOOL_VALIDATE__, CODE)))
/*! @brief Count the number of tokens in sequence @a SEQ that all are of kind BOOL */
#define P99_BOOL_LEN(SEQ) P99_IF_ELSE(P99_IS_BOOL_TOK(SEQ))(P00_BOOL1(P00_EAT_FIRST(SEQ)))(0)
/*! @brief Test if the token sequence @a SEQ starts with a token of kind BOOL */
#define P99_IS_BOOL_TOK(SEQ) P99_HAS_COMMA(P99_PASTE2(P00_BOOL_, SEQ))
#define P00_VOID7(SEQ) P99_IF_ELSE(P99_IS_VOID_TOK(SEQ))(8)(7)
#define P00_VOID6(SEQ) P99_IF_ELSE(P99_IS_VOID_TOK(SEQ))(P00_VOID7(P00_EAT_FIRST(SEQ)))(6)
#define P00_VOID5(SEQ) P99_IF_ELSE(P99_IS_VOID_TOK(SEQ))(P00_VOID6(P00_EAT_FIRST(SEQ)))(5)
#define P00_VOID4(SEQ) P99_IF_ELSE(P99_IS_VOID_TOK(SEQ))(P00_VOID5(P00_EAT_FIRST(SEQ)))(4)
#define P00_VOID3(SEQ) P99_IF_ELSE(P99_IS_VOID_TOK(SEQ))(P00_VOID4(P00_EAT_FIRST(SEQ)))(3)
#define P00_VOID2(SEQ) P99_IF_ELSE(P99_IS_VOID_TOK(SEQ))(P00_VOID3(P00_EAT_FIRST(SEQ)))(2)
#define P00_VOID1(SEQ) P99_IF_ELSE(P99_IS_VOID_TOK(SEQ))(P00_VOID2(P00_EAT_FIRST(SEQ)))(1)
#define P00_VOID_CLASSIFY_7(SEQ) P99_PASTE2(P00_VOID_CLASSIFY_, SEQ) P00_VOID_CLASSIFY_6(P00_EAT_FIRST(SEQ))
#define P00_VOID_CLASSIFY_6(SEQ) P99_PASTE2(P00_VOID_CLASSIFY_, SEQ) P00_VOID_CLASSIFY_5(P00_EAT_FIRST(SEQ))
#define P00_VOID_CLASSIFY_5(SEQ) P99_PASTE2(P00_VOID_CLASSIFY_, SEQ) P00_VOID_CLASSIFY_4(P00_EAT_FIRST(SEQ))
#define P00_VOID_CLASSIFY_4(SEQ) P99_PASTE2(P00_VOID_CLASSIFY_, SEQ) P00_VOID_CLASSIFY_3(P00_EAT_FIRST(SEQ))
#define P00_VOID_CLASSIFY_3(SEQ) P99_PASTE2(P00_VOID_CLASSIFY_, SEQ) P00_VOID_CLASSIFY_2(P00_EAT_FIRST(SEQ))
#define P00_VOID_CLASSIFY_2(SEQ) P99_PASTE2(P00_VOID_CLASSIFY_, SEQ) P00_VOID_CLASSIFY_1(P00_EAT_FIRST(SEQ))
#define P00_VOID_CLASSIFY_1(SEQ) P99_PASTE2(P00_VOID_CLASSIFY_, SEQ)
#define P00_VOID_CLASSIFY___(CODE) P99_IF_ELSE(P00_VOID_VALIDATE(CODE))(P99_PASTE2(P00_VOID_CLASSIFY__, CODE))(INVALID_VOID_TYPE_EXPRESSION[CODE])
#define P00_VOID_CLASSIFY__(N, ...) P00_VOID_CLASSIFY___(P00_NARG(__VA_ARGS__))
#define P00_VOID_CLASSIFY_(N, SEQ) P99_IF_ELSE(P99_IS_EQ_0(N))()(P00_VOID_CLASSIFY__(N, P99_PASTE2(P00_VOID_CLASSIFY_, N)(SEQ)))
/*! @brief Classify the tokens in sequence @a SEQ that all are of kind VOID */
#define P00_VOID_CLASSIFY(SEQ) P00_VOID_CLASSIFY_(P99_VOID_QUAL_LEN(SEQ), SEQ)
/*! @brief Check if @a CODE corresponds to a valid combination of tokens of kind VOID */
#define P00_VOID_VALIDATE(CODE) P99_IS_EQ_2(P99_NARG(P99_PASTE2(P00_VOID_VALIDATE__, CODE)))
/*! @brief Count the number of tokens in sequence @a SEQ that all are of kind VOID */
#define P99_VOID_LEN(SEQ) P99_IF_ELSE(P99_IS_VOID_TOK(SEQ))(P00_VOID1(P00_EAT_FIRST(SEQ)))(0)
/*! @brief Test if the token sequence @a SEQ starts with a token of kind VOID */
#define P99_IS_VOID_TOK(SEQ) P99_HAS_COMMA(P99_PASTE2(P00_VOID_, SEQ))
#define P00_INTEGER7(SEQ) P99_IF_ELSE(P99_IS_INTEGER_TOK(SEQ))(8)(7)
#define P00_INTEGER6(SEQ) P99_IF_ELSE(P99_IS_INTEGER_TOK(SEQ))(P00_INTEGER7(P00_EAT_FIRST(SEQ)))(6)
#define P00_INTEGER5(SEQ) P99_IF_ELSE(P99_IS_INTEGER_TOK(SEQ))(P00_INTEGER6(P00_EAT_FIRST(SEQ)))(5)
#define P00_INTEGER4(SEQ) P99_IF_ELSE(P99_IS_INTEGER_TOK(SEQ))(P00_INTEGER5(P00_EAT_FIRST(SEQ)))(4)
#define P00_INTEGER3(SEQ) P99_IF_ELSE(P99_IS_INTEGER_TOK(SEQ))(P00_INTEGER4(P00_EAT_FIRST(SEQ)))(3)
#define P00_INTEGER2(SEQ) P99_IF_ELSE(P99_IS_INTEGER_TOK(SEQ))(P00_INTEGER3(P00_EAT_FIRST(SEQ)))(2)
#define P00_INTEGER1(SEQ) P99_IF_ELSE(P99_IS_INTEGER_TOK(SEQ))(P00_INTEGER2(P00_EAT_FIRST(SEQ)))(1)
#define P00_INTEGER_CLASSIFY_7(SEQ) P99_PASTE2(P00_INTEGER_CLASSIFY_, SEQ) P00_INTEGER_CLASSIFY_6(P00_EAT_FIRST(SEQ))
#define P00_INTEGER_CLASSIFY_6(SEQ) P99_PASTE2(P00_INTEGER_CLASSIFY_, SEQ) P00_INTEGER_CLASSIFY_5(P00_EAT_FIRST(SEQ))
#define P00_INTEGER_CLASSIFY_5(SEQ) P99_PASTE2(P00_INTEGER_CLASSIFY_, SEQ) P00_INTEGER_CLASSIFY_4(P00_EAT_FIRST(SEQ))
#define P00_INTEGER_CLASSIFY_4(SEQ) P99_PASTE2(P00_INTEGER_CLASSIFY_, SEQ) P00_INTEGER_CLASSIFY_3(P00_EAT_FIRST(SEQ))
#define P00_INTEGER_CLASSIFY_3(SEQ) P99_PASTE2(P00_INTEGER_CLASSIFY_, SEQ) P00_INTEGER_CLASSIFY_2(P00_EAT_FIRST(SEQ))
#define P00_INTEGER_CLASSIFY_2(SEQ) P99_PASTE2(P00_INTEGER_CLASSIFY_, SEQ) P00_INTEGER_CLASSIFY_1(P00_EAT_FIRST(SEQ))
#define P00_INTEGER_CLASSIFY_1(SEQ) P99_PASTE2(P00_INTEGER_CLASSIFY_, SEQ)
#define P00_INTEGER_CLASSIFY___(CODE) P99_IF_ELSE(P00_INTEGER_VALIDATE(CODE))(P99_PASTE2(P00_INTEGER_CLASSIFY__, CODE))(INVALID_INTEGER_TYPE_EXPRESSION[CODE])
#define P00_INTEGER_CLASSIFY__(N, ...) P00_INTEGER_CLASSIFY___(P00_NARG(__VA_ARGS__))
#define P00_INTEGER_CLASSIFY_(N, SEQ) P99_IF_ELSE(P99_IS_EQ_0(N))()(P00_INTEGER_CLASSIFY__(N, P99_PASTE2(P00_INTEGER_CLASSIFY_, N)(SEQ)))
/*! @brief Classify the tokens in sequence @a SEQ that all are of kind INTEGER */
#define P00_INTEGER_CLASSIFY(SEQ) P00_INTEGER_CLASSIFY_(P99_INTEGER_QUAL_LEN(SEQ), SEQ)
/*! @brief Check if @a CODE corresponds to a valid combination of tokens of kind INTEGER */
#define P00_INTEGER_VALIDATE(CODE) P99_IS_EQ_2(P99_NARG(P99_PASTE2(P00_INTEGER_VALIDATE__, CODE)))
/*! @brief Count the number of tokens in sequence @a SEQ that all are of kind INTEGER */
#define P99_INTEGER_LEN(SEQ) P99_IF_ELSE(P99_IS_INTEGER_TOK(SEQ))(P00_INTEGER1(P00_EAT_FIRST(SEQ)))(0)
/*! @brief Test if the token sequence @a SEQ starts with a token of kind INTEGER */
#define P99_IS_INTEGER_TOK(SEQ) P99_HAS_COMMA(P99_PASTE2(P00_INTEGER_, SEQ))
#define P00_REAL7(SEQ) P99_IF_ELSE(P99_IS_REAL_TOK(SEQ))(8)(7)
#define P00_REAL6(SEQ) P99_IF_ELSE(P99_IS_REAL_TOK(SEQ))(P00_REAL7(P00_EAT_FIRST(SEQ)))(6)
#define P00_REAL5(SEQ) P99_IF_ELSE(P99_IS_REAL_TOK(SEQ))(P00_REAL6(P00_EAT_FIRST(SEQ)))(5)
#define P00_REAL4(SEQ) P99_IF_ELSE(P99_IS_REAL_TOK(SEQ))(P00_REAL5(P00_EAT_FIRST(SEQ)))(4)
#define P00_REAL3(SEQ) P99_IF_ELSE(P99_IS_REAL_TOK(SEQ))(P00_REAL4(P00_EAT_FIRST(SEQ)))(3)
#define P00_REAL2(SEQ) P99_IF_ELSE(P99_IS_REAL_TOK(SEQ))(P00_REAL3(P00_EAT_FIRST(SEQ)))(2)
#define P00_REAL1(SEQ) P99_IF_ELSE(P99_IS_REAL_TOK(SEQ))(P00_REAL2(P00_EAT_FIRST(SEQ)))(1)
#define P00_REAL_CLASSIFY_7(SEQ) P99_PASTE2(P00_REAL_CLASSIFY_, SEQ) P00_REAL_CLASSIFY_6(P00_EAT_FIRST(SEQ))
#define P00_REAL_CLASSIFY_6(SEQ) P99_PASTE2(P00_REAL_CLASSIFY_, SEQ) P00_REAL_CLASSIFY_5(P00_EAT_FIRST(SEQ))
#define P00_REAL_CLASSIFY_5(SEQ) P99_PASTE2(P00_REAL_CLASSIFY_, SEQ) P00_REAL_CLASSIFY_4(P00_EAT_FIRST(SEQ))
#define P00_REAL_CLASSIFY_4(SEQ) P99_PASTE2(P00_REAL_CLASSIFY_, SEQ) P00_REAL_CLASSIFY_3(P00_EAT_FIRST(SEQ))
#define P00_REAL_CLASSIFY_3(SEQ) P99_PASTE2(P00_REAL_CLASSIFY_, SEQ) P00_REAL_CLASSIFY_2(P00_EAT_FIRST(SEQ))
#define P00_REAL_CLASSIFY_2(SEQ) P99_PASTE2(P00_REAL_CLASSIFY_, SEQ) P00_REAL_CLASSIFY_1(P00_EAT_FIRST(SEQ))
#define P00_REAL_CLASSIFY_1(SEQ) P99_PASTE2(P00_REAL_CLASSIFY_, SEQ)
#define P00_REAL_CLASSIFY___(CODE) P99_IF_ELSE(P00_REAL_VALIDATE(CODE))(P99_PASTE2(P00_REAL_CLASSIFY__, CODE))(INVALID_REAL_TYPE_EXPRESSION[CODE])
#define P00_REAL_CLASSIFY__(N, ...) P00_REAL_CLASSIFY___(P00_NARG(__VA_ARGS__))
#define P00_REAL_CLASSIFY_(N, SEQ) P99_IF_ELSE(P99_IS_EQ_0(N))()(P00_REAL_CLASSIFY__(N, P99_PASTE2(P00_REAL_CLASSIFY_, N)(SEQ)))
/*! @brief Classify the tokens in sequence @a SEQ that all are of kind REAL */
#define P00_REAL_CLASSIFY(SEQ) P00_REAL_CLASSIFY_(P99_REAL_QUAL_LEN(SEQ), SEQ)
/*! @brief Check if @a CODE corresponds to a valid combination of tokens of kind REAL */
#define P00_REAL_VALIDATE(CODE) P99_IS_EQ_2(P99_NARG(P99_PASTE2(P00_REAL_VALIDATE__, CODE)))
/*! @brief Count the number of tokens in sequence @a SEQ that all are of kind REAL */
#define P99_REAL_LEN(SEQ) P99_IF_ELSE(P99_IS_REAL_TOK(SEQ))(P00_REAL1(P00_EAT_FIRST(SEQ)))(0)
/*! @brief Test if the token sequence @a SEQ starts with a token of kind REAL */
#define P99_IS_REAL_TOK(SEQ) P99_HAS_COMMA(P99_PASTE2(P00_REAL_, SEQ))
#define P00_FLOAT7(SEQ) P99_IF_ELSE(P99_IS_FLOAT_TOK(SEQ))(8)(7)
#define P00_FLOAT6(SEQ) P99_IF_ELSE(P99_IS_FLOAT_TOK(SEQ))(P00_FLOAT7(P00_EAT_FIRST(SEQ)))(6)
#define P00_FLOAT5(SEQ) P99_IF_ELSE(P99_IS_FLOAT_TOK(SEQ))(P00_FLOAT6(P00_EAT_FIRST(SEQ)))(5)
#define P00_FLOAT4(SEQ) P99_IF_ELSE(P99_IS_FLOAT_TOK(SEQ))(P00_FLOAT5(P00_EAT_FIRST(SEQ)))(4)
#define P00_FLOAT3(SEQ) P99_IF_ELSE(P99_IS_FLOAT_TOK(SEQ))(P00_FLOAT4(P00_EAT_FIRST(SEQ)))(3)
#define P00_FLOAT2(SEQ) P99_IF_ELSE(P99_IS_FLOAT_TOK(SEQ))(P00_FLOAT3(P00_EAT_FIRST(SEQ)))(2)
#define P00_FLOAT1(SEQ) P99_IF_ELSE(P99_IS_FLOAT_TOK(SEQ))(P00_FLOAT2(P00_EAT_FIRST(SEQ)))(1)
#define P00_FLOAT_CLASSIFY_7(SEQ) P99_PASTE2(P00_FLOAT_CLASSIFY_, SEQ) P00_FLOAT_CLASSIFY_6(P00_EAT_FIRST(SEQ))
#define P00_FLOAT_CLASSIFY_6(SEQ) P99_PASTE2(P00_FLOAT_CLASSIFY_, SEQ) P00_FLOAT_CLASSIFY_5(P00_EAT_FIRST(SEQ))
#define P00_FLOAT_CLASSIFY_5(SEQ) P99_PASTE2(P00_FLOAT_CLASSIFY_, SEQ) P00_FLOAT_CLASSIFY_4(P00_EAT_FIRST(SEQ))
#define P00_FLOAT_CLASSIFY_4(SEQ) P99_PASTE2(P00_FLOAT_CLASSIFY_, SEQ) P00_FLOAT_CLASSIFY_3(P00_EAT_FIRST(SEQ))
#define P00_FLOAT_CLASSIFY_3(SEQ) P99_PASTE2(P00_FLOAT_CLASSIFY_, SEQ) P00_FLOAT_CLASSIFY_2(P00_EAT_FIRST(SEQ))
#define P00_FLOAT_CLASSIFY_2(SEQ) P99_PASTE2(P00_FLOAT_CLASSIFY_, SEQ) P00_FLOAT_CLASSIFY_1(P00_EAT_FIRST(SEQ))
#define P00_FLOAT_CLASSIFY_1(SEQ) P99_PASTE2(P00_FLOAT_CLASSIFY_, SEQ)
#define P00_FLOAT_CLASSIFY___(CODE) P99_IF_ELSE(P00_FLOAT_VALIDATE(CODE))(P99_PASTE2(P00_FLOAT_CLASSIFY__, CODE))(INVALID_FLOAT_TYPE_EXPRESSION[CODE])
#define P00_FLOAT_CLASSIFY__(N, ...) P00_FLOAT_CLASSIFY___(P00_NARG(__VA_ARGS__))
#define P00_FLOAT_CLASSIFY_(N, SEQ) P99_IF_ELSE(P99_IS_EQ_0(N))()(P00_FLOAT_CLASSIFY__(N, P99_PASTE2(P00_FLOAT_CLASSIFY_, N)(SEQ)))
/*! @brief Classify the tokens in sequence @a SEQ that all are of kind FLOAT */
#define P00_FLOAT_CLASSIFY(SEQ) P00_FLOAT_CLASSIFY_(P99_FLOAT_QUAL_LEN(SEQ), SEQ)
/*! @brief Check if @a CODE corresponds to a valid combination of tokens of kind FLOAT */
#define P00_FLOAT_VALIDATE(CODE) P99_IS_EQ_2(P99_NARG(P99_PASTE2(P00_FLOAT_VALIDATE__, CODE)))
/*! @brief Count the number of tokens in sequence @a SEQ that all are of kind FLOAT */
#define P99_FLOAT_LEN(SEQ) P99_IF_ELSE(P99_IS_FLOAT_TOK(SEQ))(P00_FLOAT1(P00_EAT_FIRST(SEQ)))(0)
/*! @brief Test if the token sequence @a SEQ starts with a token of kind FLOAT */
#define P99_IS_FLOAT_TOK(SEQ) P99_HAS_COMMA(P99_PASTE2(P00_FLOAT_, SEQ))
#define P00_TYPE7(SEQ) P99_IF_ELSE(P99_IS_TYPE_TOK(SEQ))(8)(7)
#define P00_TYPE6(SEQ) P99_IF_ELSE(P99_IS_TYPE_TOK(SEQ))(P00_TYPE7(P00_EAT_FIRST(SEQ)))(6)
#define P00_TYPE5(SEQ) P99_IF_ELSE(P99_IS_TYPE_TOK(SEQ))(P00_TYPE6(P00_EAT_FIRST(SEQ)))(5)
#define P00_TYPE4(SEQ) P99_IF_ELSE(P99_IS_TYPE_TOK(SEQ))(P00_TYPE5(P00_EAT_FIRST(SEQ)))(4)
#define P00_TYPE3(SEQ) P99_IF_ELSE(P99_IS_TYPE_TOK(SEQ))(P00_TYPE4(P00_EAT_FIRST(SEQ)))(3)
#define P00_TYPE2(SEQ) P99_IF_ELSE(P99_IS_TYPE_TOK(SEQ))(P00_TYPE3(P00_EAT_FIRST(SEQ)))(2)
#define P00_TYPE1(SEQ) P99_IF_ELSE(P99_IS_TYPE_TOK(SEQ))(P00_TYPE2(P00_EAT_FIRST(SEQ)))(1)
#define P00_TYPE_CLASSIFY_7(SEQ) P99_PASTE2(P00_TYPE_CLASSIFY_, SEQ) P00_TYPE_CLASSIFY_6(P00_EAT_FIRST(SEQ))
#define P00_TYPE_CLASSIFY_6(SEQ) P99_PASTE2(P00_TYPE_CLASSIFY_, SEQ) P00_TYPE_CLASSIFY_5(P00_EAT_FIRST(SEQ))
#define P00_TYPE_CLASSIFY_5(SEQ) P99_PASTE2(P00_TYPE_CLASSIFY_, SEQ) P00_TYPE_CLASSIFY_4(P00_EAT_FIRST(SEQ))
#define P00_TYPE_CLASSIFY_4(SEQ) P99_PASTE2(P00_TYPE_CLASSIFY_, SEQ) P00_TYPE_CLASSIFY_3(P00_EAT_FIRST(SEQ))
#define P00_TYPE_CLASSIFY_3(SEQ) P99_PASTE2(P00_TYPE_CLASSIFY_, SEQ) P00_TYPE_CLASSIFY_2(P00_EAT_FIRST(SEQ))
#define P00_TYPE_CLASSIFY_2(SEQ) P99_PASTE2(P00_TYPE_CLASSIFY_, SEQ) P00_TYPE_CLASSIFY_1(P00_EAT_FIRST(SEQ))
#define P00_TYPE_CLASSIFY_1(SEQ) P99_PASTE2(P00_TYPE_CLASSIFY_, SEQ)
#define P00_TYPE_CLASSIFY___(CODE) P99_IF_ELSE(P00_TYPE_VALIDATE(CODE))(P99_PASTE2(P00_TYPE_CLASSIFY__, CODE))(INVALID_TYPE_TYPE_EXPRESSION[CODE])
#define P00_TYPE_CLASSIFY__(N, ...) P00_TYPE_CLASSIFY___(P00_NARG(__VA_ARGS__))
#define P00_TYPE_CLASSIFY_(N, SEQ) P99_IF_ELSE(P99_IS_EQ_0(N))()(P00_TYPE_CLASSIFY__(N, P99_PASTE2(P00_TYPE_CLASSIFY_, N)(SEQ)))
/*! @brief Classify the tokens in sequence @a SEQ that all are of kind TYPE */
#define P00_TYPE_CLASSIFY(SEQ) P00_TYPE_CLASSIFY_(P99_TYPE_QUAL_LEN(SEQ), SEQ)
/*! @brief Check if @a CODE corresponds to a valid combination of tokens of kind TYPE */
#define P00_TYPE_VALIDATE(CODE) P99_IS_EQ_2(P99_NARG(P99_PASTE2(P00_TYPE_VALIDATE__, CODE)))
/*! @brief Count the number of tokens in sequence @a SEQ that all are of kind TYPE */
#define P99_TYPE_LEN(SEQ) P99_IF_ELSE(P99_IS_TYPE_TOK(SEQ))(P00_TYPE1(P00_EAT_FIRST(SEQ)))(0)
/*! @brief Test if the token sequence @a SEQ starts with a token of kind TYPE */
#define P99_IS_TYPE_TOK(SEQ) P99_HAS_COMMA(P99_PASTE2(P00_TYPE_, SEQ))
#define P00_BOOL_QUAL7(SEQ) P99_IF_ELSE(P99_IS_BOOL_QUAL_TOK(SEQ))(8)(7)
#define P00_BOOL_QUAL6(SEQ) P99_IF_ELSE(P99_IS_BOOL_QUAL_TOK(SEQ))(P00_BOOL_QUAL7(P00_EAT_FIRST(SEQ)))(6)
#define P00_BOOL_QUAL5(SEQ) P99_IF_ELSE(P99_IS_BOOL_QUAL_TOK(SEQ))(P00_BOOL_QUAL6(P00_EAT_FIRST(SEQ)))(5)
#define P00_BOOL_QUAL4(SEQ) P99_IF_ELSE(P99_IS_BOOL_QUAL_TOK(SEQ))(P00_BOOL_QUAL5(P00_EAT_FIRST(SEQ)))(4)
#define P00_BOOL_QUAL3(SEQ) P99_IF_ELSE(P99_IS_BOOL_QUAL_TOK(SEQ))(P00_BOOL_QUAL4(P00_EAT_FIRST(SEQ)))(3)
#define P00_BOOL_QUAL2(SEQ) P99_IF_ELSE(P99_IS_BOOL_QUAL_TOK(SEQ))(P00_BOOL_QUAL3(P00_EAT_FIRST(SEQ)))(2)
#define P00_BOOL_QUAL1(SEQ) P99_IF_ELSE(P99_IS_BOOL_QUAL_TOK(SEQ))(P00_BOOL_QUAL2(P00_EAT_FIRST(SEQ)))(1)
#define P00_BOOL_QUAL_CLASSIFY_7(SEQ) P99_PASTE2(P00_BOOL_QUAL_CLASSIFY_, SEQ) P00_BOOL_QUAL_CLASSIFY_6(P00_EAT_FIRST(SEQ))
#define P00_BOOL_QUAL_CLASSIFY_6(SEQ) P99_PASTE2(P00_BOOL_QUAL_CLASSIFY_, SEQ) P00_BOOL_QUAL_CLASSIFY_5(P00_EAT_FIRST(SEQ))
#define P00_BOOL_QUAL_CLASSIFY_5(SEQ) P99_PASTE2(P00_BOOL_QUAL_CLASSIFY_, SEQ) P00_BOOL_QUAL_CLASSIFY_4(P00_EAT_FIRST(SEQ))
#define P00_BOOL_QUAL_CLASSIFY_4(SEQ) P99_PASTE2(P00_BOOL_QUAL_CLASSIFY_, SEQ) P00_BOOL_QUAL_CLASSIFY_3(P00_EAT_FIRST(SEQ))
#define P00_BOOL_QUAL_CLASSIFY_3(SEQ) P99_PASTE2(P00_BOOL_QUAL_CLASSIFY_, SEQ) P00_BOOL_QUAL_CLASSIFY_2(P00_EAT_FIRST(SEQ))
#define P00_BOOL_QUAL_CLASSIFY_2(SEQ) P99_PASTE2(P00_BOOL_QUAL_CLASSIFY_, SEQ) P00_BOOL_QUAL_CLASSIFY_1(P00_EAT_FIRST(SEQ))
#define P00_BOOL_QUAL_CLASSIFY_1(SEQ) P99_PASTE2(P00_BOOL_QUAL_CLASSIFY_, SEQ)
#define P00_BOOL_QUAL_CLASSIFY___(CODE) P99_IF_ELSE(P00_BOOL_QUAL_VALIDATE(CODE))(P99_PASTE2(P00_BOOL_QUAL_CLASSIFY__, CODE))(INVALID_BOOL_QUAL_TYPE_EXPRESSION[CODE])
#define P00_BOOL_QUAL_CLASSIFY__(N, ...) P00_BOOL_QUAL_CLASSIFY___(P00_NARG(__VA_ARGS__))
#define P00_BOOL_QUAL_CLASSIFY_(N, SEQ) P99_IF_ELSE(P99_IS_EQ_0(N))()(P00_BOOL_QUAL_CLASSIFY__(N, P99_PASTE2(P00_BOOL_QUAL_CLASSIFY_, N)(SEQ)))
/*! @brief Classify the tokens in sequence @a SEQ that all are of kind BOOL_QUAL */
#define P00_BOOL_QUAL_CLASSIFY(SEQ) P00_BOOL_QUAL_CLASSIFY_(P99_BOOL_QUAL_QUAL_LEN(SEQ), SEQ)
/*! @brief Check if @a CODE corresponds to a valid combination of tokens of kind BOOL_QUAL */
#define P00_BOOL_QUAL_VALIDATE(CODE) P99_IS_EQ_2(P99_NARG(P99_PASTE2(P00_BOOL_QUAL_VALIDATE__, CODE)))
/*! @brief Count the number of tokens in sequence @a SEQ that all are of kind BOOL_QUAL */
#define P99_BOOL_QUAL_LEN(SEQ) P99_IF_ELSE(P99_IS_BOOL_QUAL_TOK(SEQ))(P00_BOOL_QUAL1(P00_EAT_FIRST(SEQ)))(0)
/*! @brief Test if the token sequence @a SEQ starts with a token of kind BOOL_QUAL */
#define P99_IS_BOOL_QUAL_TOK(SEQ) P99_HAS_COMMA(P99_PASTE2(P00_BOOL_QUAL_, SEQ))
#define P00_VOID_QUAL7(SEQ) P99_IF_ELSE(P99_IS_VOID_QUAL_TOK(SEQ))(8)(7)
#define P00_VOID_QUAL6(SEQ) P99_IF_ELSE(P99_IS_VOID_QUAL_TOK(SEQ))(P00_VOID_QUAL7(P00_EAT_FIRST(SEQ)))(6)
#define P00_VOID_QUAL5(SEQ) P99_IF_ELSE(P99_IS_VOID_QUAL_TOK(SEQ))(P00_VOID_QUAL6(P00_EAT_FIRST(SEQ)))(5)
#define P00_VOID_QUAL4(SEQ) P99_IF_ELSE(P99_IS_VOID_QUAL_TOK(SEQ))(P00_VOID_QUAL5(P00_EAT_FIRST(SEQ)))(4)
#define P00_VOID_QUAL3(SEQ) P99_IF_ELSE(P99_IS_VOID_QUAL_TOK(SEQ))(P00_VOID_QUAL4(P00_EAT_FIRST(SEQ)))(3)
#define P00_VOID_QUAL2(SEQ) P99_IF_ELSE(P99_IS_VOID_QUAL_TOK(SEQ))(P00_VOID_QUAL3(P00_EAT_FIRST(SEQ)))(2)
#define P00_VOID_QUAL1(SEQ) P99_IF_ELSE(P99_IS_VOID_QUAL_TOK(SEQ))(P00_VOID_QUAL2(P00_EAT_FIRST(SEQ)))(1)
#define P00_VOID_QUAL_CLASSIFY_7(SEQ) P99_PASTE2(P00_VOID_QUAL_CLASSIFY_, SEQ) P00_VOID_QUAL_CLASSIFY_6(P00_EAT_FIRST(SEQ))
#define P00_VOID_QUAL_CLASSIFY_6(SEQ) P99_PASTE2(P00_VOID_QUAL_CLASSIFY_, SEQ) P00_VOID_QUAL_CLASSIFY_5(P00_EAT_FIRST(SEQ))
#define P00_VOID_QUAL_CLASSIFY_5(SEQ) P99_PASTE2(P00_VOID_QUAL_CLASSIFY_, SEQ) P00_VOID_QUAL_CLASSIFY_4(P00_EAT_FIRST(SEQ))
#define P00_VOID_QUAL_CLASSIFY_4(SEQ) P99_PASTE2(P00_VOID_QUAL_CLASSIFY_, SEQ) P00_VOID_QUAL_CLASSIFY_3(P00_EAT_FIRST(SEQ))
#define P00_VOID_QUAL_CLASSIFY_3(SEQ) P99_PASTE2(P00_VOID_QUAL_CLASSIFY_, SEQ) P00_VOID_QUAL_CLASSIFY_2(P00_EAT_FIRST(SEQ))
#define P00_VOID_QUAL_CLASSIFY_2(SEQ) P99_PASTE2(P00_VOID_QUAL_CLASSIFY_, SEQ) P00_VOID_QUAL_CLASSIFY_1(P00_EAT_FIRST(SEQ))
#define P00_VOID_QUAL_CLASSIFY_1(SEQ) P99_PASTE2(P00_VOID_QUAL_CLASSIFY_, SEQ)
#define P00_VOID_QUAL_CLASSIFY___(CODE) P99_IF_ELSE(P00_VOID_QUAL_VALIDATE(CODE))(P99_PASTE2(P00_VOID_QUAL_CLASSIFY__, CODE))(INVALID_VOID_QUAL_TYPE_EXPRESSION[CODE])
#define P00_VOID_QUAL_CLASSIFY__(N, ...) P00_VOID_QUAL_CLASSIFY___(P00_NARG(__VA_ARGS__))
#define P00_VOID_QUAL_CLASSIFY_(N, SEQ) P99_IF_ELSE(P99_IS_EQ_0(N))()(P00_VOID_QUAL_CLASSIFY__(N, P99_PASTE2(P00_VOID_QUAL_CLASSIFY_, N)(SEQ)))
/*! @brief Classify the tokens in sequence @a SEQ that all are of kind VOID_QUAL */
#define P00_VOID_QUAL_CLASSIFY(SEQ) P00_VOID_QUAL_CLASSIFY_(P99_VOID_QUAL_QUAL_LEN(SEQ), SEQ)
/*! @brief Check if @a CODE corresponds to a valid combination of tokens of kind VOID_QUAL */
#define P00_VOID_QUAL_VALIDATE(CODE) P99_IS_EQ_2(P99_NARG(P99_PASTE2(P00_VOID_QUAL_VALIDATE__, CODE)))
/*! @brief Count the number of tokens in sequence @a SEQ that all are of kind VOID_QUAL */
#define P99_VOID_QUAL_LEN(SEQ) P99_IF_ELSE(P99_IS_VOID_QUAL_TOK(SEQ))(P00_VOID_QUAL1(P00_EAT_FIRST(SEQ)))(0)
/*! @brief Test if the token sequence @a SEQ starts with a token of kind VOID_QUAL */
#define P99_IS_VOID_QUAL_TOK(SEQ) P99_HAS_COMMA(P99_PASTE2(P00_VOID_QUAL_, SEQ))
#define P00_INTEGER_QUAL7(SEQ) P99_IF_ELSE(P99_IS_INTEGER_QUAL_TOK(SEQ))(8)(7)
#define P00_INTEGER_QUAL6(SEQ) P99_IF_ELSE(P99_IS_INTEGER_QUAL_TOK(SEQ))(P00_INTEGER_QUAL7(P00_EAT_FIRST(SEQ)))(6)
#define P00_INTEGER_QUAL5(SEQ) P99_IF_ELSE(P99_IS_INTEGER_QUAL_TOK(SEQ))(P00_INTEGER_QUAL6(P00_EAT_FIRST(SEQ)))(5)
#define P00_INTEGER_QUAL4(SEQ) P99_IF_ELSE(P99_IS_INTEGER_QUAL_TOK(SEQ))(P00_INTEGER_QUAL5(P00_EAT_FIRST(SEQ)))(4)
#define P00_INTEGER_QUAL3(SEQ) P99_IF_ELSE(P99_IS_INTEGER_QUAL_TOK(SEQ))(P00_INTEGER_QUAL4(P00_EAT_FIRST(SEQ)))(3)
#define P00_INTEGER_QUAL2(SEQ) P99_IF_ELSE(P99_IS_INTEGER_QUAL_TOK(SEQ))(P00_INTEGER_QUAL3(P00_EAT_FIRST(SEQ)))(2)
#define P00_INTEGER_QUAL1(SEQ) P99_IF_ELSE(P99_IS_INTEGER_QUAL_TOK(SEQ))(P00_INTEGER_QUAL2(P00_EAT_FIRST(SEQ)))(1)
#define P00_INTEGER_QUAL_CLASSIFY_7(SEQ) P99_PASTE2(P00_INTEGER_QUAL_CLASSIFY_, SEQ) P00_INTEGER_QUAL_CLASSIFY_6(P00_EAT_FIRST(SEQ))
#define P00_INTEGER_QUAL_CLASSIFY_6(SEQ) P99_PASTE2(P00_INTEGER_QUAL_CLASSIFY_, SEQ) P00_INTEGER_QUAL_CLASSIFY_5(P00_EAT_FIRST(SEQ))
#define P00_INTEGER_QUAL_CLASSIFY_5(SEQ) P99_PASTE2(P00_INTEGER_QUAL_CLASSIFY_, SEQ) P00_INTEGER_QUAL_CLASSIFY_4(P00_EAT_FIRST(SEQ))
#define P00_INTEGER_QUAL_CLASSIFY_4(SEQ) P99_PASTE2(P00_INTEGER_QUAL_CLASSIFY_, SEQ) P00_INTEGER_QUAL_CLASSIFY_3(P00_EAT_FIRST(SEQ))
#define P00_INTEGER_QUAL_CLASSIFY_3(SEQ) P99_PASTE2(P00_INTEGER_QUAL_CLASSIFY_, SEQ) P00_INTEGER_QUAL_CLASSIFY_2(P00_EAT_FIRST(SEQ))
#define P00_INTEGER_QUAL_CLASSIFY_2(SEQ) P99_PASTE2(P00_INTEGER_QUAL_CLASSIFY_, SEQ) P00_INTEGER_QUAL_CLASSIFY_1(P00_EAT_FIRST(SEQ))
#define P00_INTEGER_QUAL_CLASSIFY_1(SEQ) P99_PASTE2(P00_INTEGER_QUAL_CLASSIFY_, SEQ)
#define P00_INTEGER_QUAL_CLASSIFY___(CODE) P99_IF_ELSE(P00_INTEGER_QUAL_VALIDATE(CODE))(P99_PASTE2(P00_INTEGER_QUAL_CLASSIFY__, CODE))(INVALID_INTEGER_QUAL_TYPE_EXPRESSION[CODE])
#define P00_INTEGER_QUAL_CLASSIFY__(N, ...) P00_INTEGER_QUAL_CLASSIFY___(P00_NARG(__VA_ARGS__))
#define P00_INTEGER_QUAL_CLASSIFY_(N, SEQ) P99_IF_ELSE(P99_IS_EQ_0(N))()(P00_INTEGER_QUAL_CLASSIFY__(N, P99_PASTE2(P00_INTEGER_QUAL_CLASSIFY_, N)(SEQ)))
/*! @brief Classify the tokens in sequence @a SEQ that all are of kind INTEGER_QUAL */
#define P00_INTEGER_QUAL_CLASSIFY(SEQ) P00_INTEGER_QUAL_CLASSIFY_(P99_INTEGER_QUAL_QUAL_LEN(SEQ), SEQ)
/*! @brief Check if @a CODE corresponds to a valid combination of tokens of kind INTEGER_QUAL */
#define P00_INTEGER_QUAL_VALIDATE(CODE) P99_IS_EQ_2(P99_NARG(P99_PASTE2(P00_INTEGER_QUAL_VALIDATE__, CODE)))
/*! @brief Count the number of tokens in sequence @a SEQ that all are of kind INTEGER_QUAL */
#define P99_INTEGER_QUAL_LEN(SEQ) P99_IF_ELSE(P99_IS_INTEGER_QUAL_TOK(SEQ))(P00_INTEGER_QUAL1(P00_EAT_FIRST(SEQ)))(0)
/*! @brief Test if the token sequence @a SEQ starts with a token of kind INTEGER_QUAL */
#define P99_IS_INTEGER_QUAL_TOK(SEQ) P99_HAS_COMMA(P99_PASTE2(P00_INTEGER_QUAL_, SEQ))
#define P00_REAL_QUAL7(SEQ) P99_IF_ELSE(P99_IS_REAL_QUAL_TOK(SEQ))(8)(7)
#define P00_REAL_QUAL6(SEQ) P99_IF_ELSE(P99_IS_REAL_QUAL_TOK(SEQ))(P00_REAL_QUAL7(P00_EAT_FIRST(SEQ)))(6)
#define P00_REAL_QUAL5(SEQ) P99_IF_ELSE(P99_IS_REAL_QUAL_TOK(SEQ))(P00_REAL_QUAL6(P00_EAT_FIRST(SEQ)))(5)
#define P00_REAL_QUAL4(SEQ) P99_IF_ELSE(P99_IS_REAL_QUAL_TOK(SEQ))(P00_REAL_QUAL5(P00_EAT_FIRST(SEQ)))(4)
#define P00_REAL_QUAL3(SEQ) P99_IF_ELSE(P99_IS_REAL_QUAL_TOK(SEQ))(P00_REAL_QUAL4(P00_EAT_FIRST(SEQ)))(3)
#define P00_REAL_QUAL2(SEQ) P99_IF_ELSE(P99_IS_REAL_QUAL_TOK(SEQ))(P00_REAL_QUAL3(P00_EAT_FIRST(SEQ)))(2)
#define P00_REAL_QUAL1(SEQ) P99_IF_ELSE(P99_IS_REAL_QUAL_TOK(SEQ))(P00_REAL_QUAL2(P00_EAT_FIRST(SEQ)))(1)
#define P00_REAL_QUAL_CLASSIFY_7(SEQ) P99_PASTE2(P00_REAL_QUAL_CLASSIFY_, SEQ) P00_REAL_QUAL_CLASSIFY_6(P00_EAT_FIRST(SEQ))
#define P00_REAL_QUAL_CLASSIFY_6(SEQ) P99_PASTE2(P00_REAL_QUAL_CLASSIFY_, SEQ) P00_REAL_QUAL_CLASSIFY_5(P00_EAT_FIRST(SEQ))
#define P00_REAL_QUAL_CLASSIFY_5(SEQ) P99_PASTE2(P00_REAL_QUAL_CLASSIFY_, SEQ) P00_REAL_QUAL_CLASSIFY_4(P00_EAT_FIRST(SEQ))
#define P00_REAL_QUAL_CLASSIFY_4(SEQ) P99_PASTE2(P00_REAL_QUAL_CLASSIFY_, SEQ) P00_REAL_QUAL_CLASSIFY_3(P00_EAT_FIRST(SEQ))
#define P00_REAL_QUAL_CLASSIFY_3(SEQ) P99_PASTE2(P00_REAL_QUAL_CLASSIFY_, SEQ) P00_REAL_QUAL_CLASSIFY_2(P00_EAT_FIRST(SEQ))
#define P00_REAL_QUAL_CLASSIFY_2(SEQ) P99_PASTE2(P00_REAL_QUAL_CLASSIFY_, SEQ) P00_REAL_QUAL_CLASSIFY_1(P00_EAT_FIRST(SEQ))
#define P00_REAL_QUAL_CLASSIFY_1(SEQ) P99_PASTE2(P00_REAL_QUAL_CLASSIFY_, SEQ)
#define P00_REAL_QUAL_CLASSIFY___(CODE) P99_IF_ELSE(P00_REAL_QUAL_VALIDATE(CODE))(P99_PASTE2(P00_REAL_QUAL_CLASSIFY__, CODE))(INVALID_REAL_QUAL_TYPE_EXPRESSION[CODE])
#define P00_REAL_QUAL_CLASSIFY__(N, ...) P00_REAL_QUAL_CLASSIFY___(P00_NARG(__VA_ARGS__))
#define P00_REAL_QUAL_CLASSIFY_(N, SEQ) P99_IF_ELSE(P99_IS_EQ_0(N))()(P00_REAL_QUAL_CLASSIFY__(N, P99_PASTE2(P00_REAL_QUAL_CLASSIFY_, N)(SEQ)))
/*! @brief Classify the tokens in sequence @a SEQ that all are of kind REAL_QUAL */
#define P00_REAL_QUAL_CLASSIFY(SEQ) P00_REAL_QUAL_CLASSIFY_(P99_REAL_QUAL_QUAL_LEN(SEQ), SEQ)
/*! @brief Check if @a CODE corresponds to a valid combination of tokens of kind REAL_QUAL */
#define P00_REAL_QUAL_VALIDATE(CODE) P99_IS_EQ_2(P99_NARG(P99_PASTE2(P00_REAL_QUAL_VALIDATE__, CODE)))
/*! @brief Count the number of tokens in sequence @a SEQ that all are of kind REAL_QUAL */
#define P99_REAL_QUAL_LEN(SEQ) P99_IF_ELSE(P99_IS_REAL_QUAL_TOK(SEQ))(P00_REAL_QUAL1(P00_EAT_FIRST(SEQ)))(0)
/*! @brief Test if the token sequence @a SEQ starts with a token of kind REAL_QUAL */
#define P99_IS_REAL_QUAL_TOK(SEQ) P99_HAS_COMMA(P99_PASTE2(P00_REAL_QUAL_, SEQ))
#define P00_FLOAT_QUAL7(SEQ) P99_IF_ELSE(P99_IS_FLOAT_QUAL_TOK(SEQ))(8)(7)
#define P00_FLOAT_QUAL6(SEQ) P99_IF_ELSE(P99_IS_FLOAT_QUAL_TOK(SEQ))(P00_FLOAT_QUAL7(P00_EAT_FIRST(SEQ)))(6)
#define P00_FLOAT_QUAL5(SEQ) P99_IF_ELSE(P99_IS_FLOAT_QUAL_TOK(SEQ))(P00_FLOAT_QUAL6(P00_EAT_FIRST(SEQ)))(5)
#define P00_FLOAT_QUAL4(SEQ) P99_IF_ELSE(P99_IS_FLOAT_QUAL_TOK(SEQ))(P00_FLOAT_QUAL5(P00_EAT_FIRST(SEQ)))(4)
#define P00_FLOAT_QUAL3(SEQ) P99_IF_ELSE(P99_IS_FLOAT_QUAL_TOK(SEQ))(P00_FLOAT_QUAL4(P00_EAT_FIRST(SEQ)))(3)
#define P00_FLOAT_QUAL2(SEQ) P99_IF_ELSE(P99_IS_FLOAT_QUAL_TOK(SEQ))(P00_FLOAT_QUAL3(P00_EAT_FIRST(SEQ)))(2)
#define P00_FLOAT_QUAL1(SEQ) P99_IF_ELSE(P99_IS_FLOAT_QUAL_TOK(SEQ))(P00_FLOAT_QUAL2(P00_EAT_FIRST(SEQ)))(1)
#define P00_FLOAT_QUAL_CLASSIFY_7(SEQ) P99_PASTE2(P00_FLOAT_QUAL_CLASSIFY_, SEQ) P00_FLOAT_QUAL_CLASSIFY_6(P00_EAT_FIRST(SEQ))
#define P00_FLOAT_QUAL_CLASSIFY_6(SEQ) P99_PASTE2(P00_FLOAT_QUAL_CLASSIFY_, SEQ) P00_FLOAT_QUAL_CLASSIFY_5(P00_EAT_FIRST(SEQ))
#define P00_FLOAT_QUAL_CLASSIFY_5(SEQ) P99_PASTE2(P00_FLOAT_QUAL_CLASSIFY_, SEQ) P00_FLOAT_QUAL_CLASSIFY_4(P00_EAT_FIRST(SEQ))
#define P00_FLOAT_QUAL_CLASSIFY_4(SEQ) P99_PASTE2(P00_FLOAT_QUAL_CLASSIFY_, SEQ) P00_FLOAT_QUAL_CLASSIFY_3(P00_EAT_FIRST(SEQ))
#define P00_FLOAT_QUAL_CLASSIFY_3(SEQ) P99_PASTE2(P00_FLOAT_QUAL_CLASSIFY_, SEQ) P00_FLOAT_QUAL_CLASSIFY_2(P00_EAT_FIRST(SEQ))
#define P00_FLOAT_QUAL_CLASSIFY_2(SEQ) P99_PASTE2(P00_FLOAT_QUAL_CLASSIFY_, SEQ) P00_FLOAT_QUAL_CLASSIFY_1(P00_EAT_FIRST(SEQ))
#define P00_FLOAT_QUAL_CLASSIFY_1(SEQ) P99_PASTE2(P00_FLOAT_QUAL_CLASSIFY_, SEQ)
#define P00_FLOAT_QUAL_CLASSIFY___(CODE) P99_IF_ELSE(P00_FLOAT_QUAL_VALIDATE(CODE))(P99_PASTE2(P00_FLOAT_QUAL_CLASSIFY__, CODE))(INVALID_FLOAT_QUAL_TYPE_EXPRESSION[CODE])
#define P00_FLOAT_QUAL_CLASSIFY__(N, ...) P00_FLOAT_QUAL_CLASSIFY___(P00_NARG(__VA_ARGS__))
#define P00_FLOAT_QUAL_CLASSIFY_(N, SEQ) P99_IF_ELSE(P99_IS_EQ_0(N))()(P00_FLOAT_QUAL_CLASSIFY__(N, P99_PASTE2(P00_FLOAT_QUAL_CLASSIFY_, N)(SEQ)))
/*! @brief Classify the tokens in sequence @a SEQ that all are of kind FLOAT_QUAL */
#define P00_FLOAT_QUAL_CLASSIFY(SEQ) P00_FLOAT_QUAL_CLASSIFY_(P99_FLOAT_QUAL_QUAL_LEN(SEQ), SEQ)
/*! @brief Check if @a CODE corresponds to a valid combination of tokens of kind FLOAT_QUAL */
#define P00_FLOAT_QUAL_VALIDATE(CODE) P99_IS_EQ_2(P99_NARG(P99_PASTE2(P00_FLOAT_QUAL_VALIDATE__, CODE)))
/*! @brief Count the number of tokens in sequence @a SEQ that all are of kind FLOAT_QUAL */
#define P99_FLOAT_QUAL_LEN(SEQ) P99_IF_ELSE(P99_IS_FLOAT_QUAL_TOK(SEQ))(P00_FLOAT_QUAL1(P00_EAT_FIRST(SEQ)))(0)
/*! @brief Test if the token sequence @a SEQ starts with a token of kind FLOAT_QUAL */
#define P99_IS_FLOAT_QUAL_TOK(SEQ) P99_HAS_COMMA(P99_PASTE2(P00_FLOAT_QUAL_, SEQ))
#define P00_TYPE_QUAL7(SEQ) P99_IF_ELSE(P99_IS_TYPE_QUAL_TOK(SEQ))(8)(7)
#define P00_TYPE_QUAL6(SEQ) P99_IF_ELSE(P99_IS_TYPE_QUAL_TOK(SEQ))(P00_TYPE_QUAL7(P00_EAT_FIRST(SEQ)))(6)
#define P00_TYPE_QUAL5(SEQ) P99_IF_ELSE(P99_IS_TYPE_QUAL_TOK(SEQ))(P00_TYPE_QUAL6(P00_EAT_FIRST(SEQ)))(5)
#define P00_TYPE_QUAL4(SEQ) P99_IF_ELSE(P99_IS_TYPE_QUAL_TOK(SEQ))(P00_TYPE_QUAL5(P00_EAT_FIRST(SEQ)))(4)
#define P00_TYPE_QUAL3(SEQ) P99_IF_ELSE(P99_IS_TYPE_QUAL_TOK(SEQ))(P00_TYPE_QUAL4(P00_EAT_FIRST(SEQ)))(3)
#define P00_TYPE_QUAL2(SEQ) P99_IF_ELSE(P99_IS_TYPE_QUAL_TOK(SEQ))(P00_TYPE_QUAL3(P00_EAT_FIRST(SEQ)))(2)
#define P00_TYPE_QUAL1(SEQ) P99_IF_ELSE(P99_IS_TYPE_QUAL_TOK(SEQ))(P00_TYPE_QUAL2(P00_EAT_FIRST(SEQ)))(1)
#define P00_TYPE_QUAL_CLASSIFY_7(SEQ) P99_PASTE2(P00_TYPE_QUAL_CLASSIFY_, SEQ) P00_TYPE_QUAL_CLASSIFY_6(P00_EAT_FIRST(SEQ))
#define P00_TYPE_QUAL_CLASSIFY_6(SEQ) P99_PASTE2(P00_TYPE_QUAL_CLASSIFY_, SEQ) P00_TYPE_QUAL_CLASSIFY_5(P00_EAT_FIRST(SEQ))
#define P00_TYPE_QUAL_CLASSIFY_5(SEQ) P99_PASTE2(P00_TYPE_QUAL_CLASSIFY_, SEQ) P00_TYPE_QUAL_CLASSIFY_4(P00_EAT_FIRST(SEQ))
#define P00_TYPE_QUAL_CLASSIFY_4(SEQ) P99_PASTE2(P00_TYPE_QUAL_CLASSIFY_, SEQ) P00_TYPE_QUAL_CLASSIFY_3(P00_EAT_FIRST(SEQ))
#define P00_TYPE_QUAL_CLASSIFY_3(SEQ) P99_PASTE2(P00_TYPE_QUAL_CLASSIFY_, SEQ) P00_TYPE_QUAL_CLASSIFY_2(P00_EAT_FIRST(SEQ))
#define P00_TYPE_QUAL_CLASSIFY_2(SEQ) P99_PASTE2(P00_TYPE_QUAL_CLASSIFY_, SEQ) P00_TYPE_QUAL_CLASSIFY_1(P00_EAT_FIRST(SEQ))
#define P00_TYPE_QUAL_CLASSIFY_1(SEQ) P99_PASTE2(P00_TYPE_QUAL_CLASSIFY_, SEQ)
#define P00_TYPE_QUAL_CLASSIFY___(CODE) P99_IF_ELSE(P00_TYPE_QUAL_VALIDATE(CODE))(P99_PASTE2(P00_TYPE_QUAL_CLASSIFY__, CODE))(INVALID_TYPE_QUAL_TYPE_EXPRESSION[CODE])
#define P00_TYPE_QUAL_CLASSIFY__(N, ...) P00_TYPE_QUAL_CLASSIFY___(P00_NARG(__VA_ARGS__))
#define P00_TYPE_QUAL_CLASSIFY_(N, SEQ) P99_IF_ELSE(P99_IS_EQ_0(N))()(P00_TYPE_QUAL_CLASSIFY__(N, P99_PASTE2(P00_TYPE_QUAL_CLASSIFY_, N)(SEQ)))
/*! @brief Classify the tokens in sequence @a SEQ that all are of kind TYPE_QUAL */
#define P00_TYPE_QUAL_CLASSIFY(SEQ) P00_TYPE_QUAL_CLASSIFY_(P99_TYPE_QUAL_QUAL_LEN(SEQ), SEQ)
/*! @brief Check if @a CODE corresponds to a valid combination of tokens of kind TYPE_QUAL */
#define P00_TYPE_QUAL_VALIDATE(CODE) P99_IS_EQ_2(P99_NARG(P99_PASTE2(P00_TYPE_QUAL_VALIDATE__, CODE)))
/*! @brief Count the number of tokens in sequence @a SEQ that all are of kind TYPE_QUAL */
#define P99_TYPE_QUAL_LEN(SEQ) P99_IF_ELSE(P99_IS_TYPE_QUAL_TOK(SEQ))(P00_TYPE_QUAL1(P00_EAT_FIRST(SEQ)))(0)
/*! @brief Test if the token sequence @a SEQ starts with a token of kind TYPE_QUAL */
#define P99_IS_TYPE_QUAL_TOK(SEQ) P99_HAS_COMMA(P99_PASTE2(P00_TYPE_QUAL_, SEQ))
#define P00_KEYWORD7(SEQ) P99_IF_ELSE(P99_IS_KEYWORD_TOK(SEQ))(8)(7)
#define P00_KEYWORD6(SEQ) P99_IF_ELSE(P99_IS_KEYWORD_TOK(SEQ))(P00_KEYWORD7(P00_EAT_FIRST(SEQ)))(6)
#define P00_KEYWORD5(SEQ) P99_IF_ELSE(P99_IS_KEYWORD_TOK(SEQ))(P00_KEYWORD6(P00_EAT_FIRST(SEQ)))(5)
#define P00_KEYWORD4(SEQ) P99_IF_ELSE(P99_IS_KEYWORD_TOK(SEQ))(P00_KEYWORD5(P00_EAT_FIRST(SEQ)))(4)
#define P00_KEYWORD3(SEQ) P99_IF_ELSE(P99_IS_KEYWORD_TOK(SEQ))(P00_KEYWORD4(P00_EAT_FIRST(SEQ)))(3)
#define P00_KEYWORD2(SEQ) P99_IF_ELSE(P99_IS_KEYWORD_TOK(SEQ))(P00_KEYWORD3(P00_EAT_FIRST(SEQ)))(2)
#define P00_KEYWORD1(SEQ) P99_IF_ELSE(P99_IS_KEYWORD_TOK(SEQ))(P00_KEYWORD2(P00_EAT_FIRST(SEQ)))(1)
#define P00_KEYWORD_CLASSIFY_7(SEQ) P99_PASTE2(P00_KEYWORD_CLASSIFY_, SEQ) P00_KEYWORD_CLASSIFY_6(P00_EAT_FIRST(SEQ))
#define P00_KEYWORD_CLASSIFY_6(SEQ) P99_PASTE2(P00_KEYWORD_CLASSIFY_, SEQ) P00_KEYWORD_CLASSIFY_5(P00_EAT_FIRST(SEQ))
#define P00_KEYWORD_CLASSIFY_5(SEQ) P99_PASTE2(P00_KEYWORD_CLASSIFY_, SEQ) P00_KEYWORD_CLASSIFY_4(P00_EAT_FIRST(SEQ))
#define P00_KEYWORD_CLASSIFY_4(SEQ) P99_PASTE2(P00_KEYWORD_CLASSIFY_, SEQ) P00_KEYWORD_CLASSIFY_3(P00_EAT_FIRST(SEQ))
#define P00_KEYWORD_CLASSIFY_3(SEQ) P99_PASTE2(P00_KEYWORD_CLASSIFY_, SEQ) P00_KEYWORD_CLASSIFY_2(P00_EAT_FIRST(SEQ))
#define P00_KEYWORD_CLASSIFY_2(SEQ) P99_PASTE2(P00_KEYWORD_CLASSIFY_, SEQ) P00_KEYWORD_CLASSIFY_1(P00_EAT_FIRST(SEQ))
#define P00_KEYWORD_CLASSIFY_1(SEQ) P99_PASTE2(P00_KEYWORD_CLASSIFY_, SEQ)
#define P00_KEYWORD_CLASSIFY___(CODE) P99_IF_ELSE(P00_KEYWORD_VALIDATE(CODE))(P99_PASTE2(P00_KEYWORD_CLASSIFY__, CODE))(INVALID_KEYWORD_TYPE_EXPRESSION[CODE])
#define P00_KEYWORD_CLASSIFY__(N, ...) P00_KEYWORD_CLASSIFY___(P00_NARG(__VA_ARGS__))
#define P00_KEYWORD_CLASSIFY_(N, SEQ) P99_IF_ELSE(P99_IS_EQ_0(N))()(P00_KEYWORD_CLASSIFY__(N, P99_PASTE2(P00_KEYWORD_CLASSIFY_, N)(SEQ)))
/*! @brief Classify the tokens in sequence @a SEQ that all are of kind KEYWORD */
#define P00_KEYWORD_CLASSIFY(SEQ) P00_KEYWORD_CLASSIFY_(P99_KEYWORD_QUAL_LEN(SEQ), SEQ)
/*! @brief Check if @a CODE corresponds to a valid combination of tokens of kind KEYWORD */
#define P00_KEYWORD_VALIDATE(CODE) P99_IS_EQ_2(P99_NARG(P99_PASTE2(P00_KEYWORD_VALIDATE__, CODE)))
/*! @brief Count the number of tokens in sequence @a SEQ that all are of kind KEYWORD */
#define P99_KEYWORD_LEN(SEQ) P99_IF_ELSE(P99_IS_KEYWORD_TOK(SEQ))(P00_KEYWORD1(P00_EAT_FIRST(SEQ)))(0)
/*! @brief Test if the token sequence @a SEQ starts with a token of kind KEYWORD */
#define P99_IS_KEYWORD_TOK(SEQ) P99_HAS_COMMA(P99_PASTE2(P00_KEYWORD_, SEQ))
#define P00_RESERVED7(SEQ) P99_IF_ELSE(P99_IS_RESERVED_TOK(SEQ))(8)(7)
#define P00_RESERVED6(SEQ) P99_IF_ELSE(P99_IS_RESERVED_TOK(SEQ))(P00_RESERVED7(P00_EAT_FIRST(SEQ)))(6)
#define P00_RESERVED5(SEQ) P99_IF_ELSE(P99_IS_RESERVED_TOK(SEQ))(P00_RESERVED6(P00_EAT_FIRST(SEQ)))(5)
#define P00_RESERVED4(SEQ) P99_IF_ELSE(P99_IS_RESERVED_TOK(SEQ))(P00_RESERVED5(P00_EAT_FIRST(SEQ)))(4)
#define P00_RESERVED3(SEQ) P99_IF_ELSE(P99_IS_RESERVED_TOK(SEQ))(P00_RESERVED4(P00_EAT_FIRST(SEQ)))(3)
#define P00_RESERVED2(SEQ) P99_IF_ELSE(P99_IS_RESERVED_TOK(SEQ))(P00_RESERVED3(P00_EAT_FIRST(SEQ)))(2)
#define P00_RESERVED1(SEQ) P99_IF_ELSE(P99_IS_RESERVED_TOK(SEQ))(P00_RESERVED2(P00_EAT_FIRST(SEQ)))(1)
#define P00_RESERVED_CLASSIFY_7(SEQ) P99_PASTE2(P00_RESERVED_CLASSIFY_, SEQ) P00_RESERVED_CLASSIFY_6(P00_EAT_FIRST(SEQ))
#define P00_RESERVED_CLASSIFY_6(SEQ) P99_PASTE2(P00_RESERVED_CLASSIFY_, SEQ) P00_RESERVED_CLASSIFY_5(P00_EAT_FIRST(SEQ))
#define P00_RESERVED_CLASSIFY_5(SEQ) P99_PASTE2(P00_RESERVED_CLASSIFY_, SEQ) P00_RESERVED_CLASSIFY_4(P00_EAT_FIRST(SEQ))
#define P00_RESERVED_CLASSIFY_4(SEQ) P99_PASTE2(P00_RESERVED_CLASSIFY_, SEQ) P00_RESERVED_CLASSIFY_3(P00_EAT_FIRST(SEQ))
#define P00_RESERVED_CLASSIFY_3(SEQ) P99_PASTE2(P00_RESERVED_CLASSIFY_, SEQ) P00_RESERVED_CLASSIFY_2(P00_EAT_FIRST(SEQ))
#define P00_RESERVED_CLASSIFY_2(SEQ) P99_PASTE2(P00_RESERVED_CLASSIFY_, SEQ) P00_RESERVED_CLASSIFY_1(P00_EAT_FIRST(SEQ))
#define P00_RESERVED_CLASSIFY_1(SEQ) P99_PASTE2(P00_RESERVED_CLASSIFY_, SEQ)
#define P00_RESERVED_CLASSIFY___(CODE) P99_IF_ELSE(P00_RESERVED_VALIDATE(CODE))(P99_PASTE2(P00_RESERVED_CLASSIFY__, CODE))(INVALID_RESERVED_TYPE_EXPRESSION[CODE])
#define P00_RESERVED_CLASSIFY__(N, ...) P00_RESERVED_CLASSIFY___(P00_NARG(__VA_ARGS__))
#define P00_RESERVED_CLASSIFY_(N, SEQ) P99_IF_ELSE(P99_IS_EQ_0(N))()(P00_RESERVED_CLASSIFY__(N, P99_PASTE2(P00_RESERVED_CLASSIFY_, N)(SEQ)))
/*! @brief Classify the tokens in sequence @a SEQ that all are of kind RESERVED */
#define P00_RESERVED_CLASSIFY(SEQ) P00_RESERVED_CLASSIFY_(P99_RESERVED_QUAL_LEN(SEQ), SEQ)
/*! @brief Check if @a CODE corresponds to a valid combination of tokens of kind RESERVED */
#define P00_RESERVED_VALIDATE(CODE) P99_IS_EQ_2(P99_NARG(P99_PASTE2(P00_RESERVED_VALIDATE__, CODE)))
/*! @brief Count the number of tokens in sequence @a SEQ that all are of kind RESERVED */
#define P99_RESERVED_LEN(SEQ) P99_IF_ELSE(P99_IS_RESERVED_TOK(SEQ))(P00_RESERVED1(P00_EAT_FIRST(SEQ)))(0)
/*! @brief Test if the token sequence @a SEQ starts with a token of kind RESERVED */
#define P99_IS_RESERVED_TOK(SEQ) P99_HAS_COMMA(P99_PASTE2(P00_RESERVED_, SEQ))
#define P00_CONST_CLASSIFY_const /* 1 */ ,
#define P00_CONST_CLASSIFY__1
#define P00_CONST_VALIDATE__1 ,
#define P00_CONST_CLASSIFY__2 const
#define P00_CONST_VALIDATE__2 ,
#define P00_CONST_CLASSIFY__3 const
#define P00_CONST_VALIDATE__3 ,
#define P00_CONST_CLASSIFY__4 const
#define P00_CONST_VALIDATE__4 ,
#define P00_CONST_CLASSIFY__5 const
#define P00_CONST_VALIDATE__5 ,
#define P00_CONST_CLASSIFY__6 const
#define P00_CONST_VALIDATE__6 ,
#define P00_CONST_CLASSIFY__7 const
#define P00_CONST_VALIDATE__7 ,
#define P00_VOLATILE_CLASSIFY_volatile /* 1 */ ,
#define P00_VOLATILE_CLASSIFY__1
#define P00_VOLATILE_VALIDATE__1 ,
#define P00_VOLATILE_CLASSIFY__2 volatile
#define P00_VOLATILE_VALIDATE__2 ,
#define P00_VOLATILE_CLASSIFY__3 volatile
#define P00_VOLATILE_VALIDATE__3 ,
#define P00_VOLATILE_CLASSIFY__4 volatile
#define P00_VOLATILE_VALIDATE__4 ,
#define P00_VOLATILE_CLASSIFY__5 volatile
#define P00_VOLATILE_VALIDATE__5 ,
#define P00_VOLATILE_CLASSIFY__6 volatile
#define P00_VOLATILE_VALIDATE__6 ,
#define P00_VOLATILE_CLASSIFY__7 volatile
#define P00_VOLATILE_VALIDATE__7 ,
#define P00_VOID_CLASSIFY_void /* 1 */ ,
#define P00_VOID_CLASSIFY__1
#define P00_VOID_VALIDATE__1 ,
#define P00_VOID_CLASSIFY__2 v
#define P00_VOID_VALIDATE__2 ,
#define P00_BOOL_CLASSIFY__Bool /* 1 */ ,
#define P00_BOOL_CLASSIFY__1
#define P00_BOOL_VALIDATE__1 ,
#define P00_BOOL_CLASSIFY__2 b
#define P00_BOOL_VALIDATE__2 ,
#define P00_INTEGER_CLASSIFY_long /* 1 */ ,
#define P00_INTEGER_CLASSIFY_short /* 4 */ ,,,,
#define P00_INTEGER_CLASSIFY_char /* 8 */ ,,,,,,,,
#define P00_INTEGER_CLASSIFY_signed /* 16 */ ,,,,,,,,,,,,,,,,
#define P00_INTEGER_CLASSIFY_unsigned /* 32 */ ,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,
#define P00_INTEGER_CLASSIFY_int /* 64 */ ,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,
#define P00_INTEGER_CLASSIFY__2 l
#define P00_INTEGER_VALIDATE__2 ,
#define P00_INTEGER_CLASSIFY__3 ll
#define P00_INTEGER_VALIDATE__3 ,
#define P00_INTEGER_CLASSIFY__5 h
#define P00_INTEGER_VALIDATE__5 ,
#define P00_INTEGER_CLASSIFY__9 c
#define P00_INTEGER_VALIDATE__9 ,
#define P00_INTEGER_CLASSIFY__17 i
#define P00_INTEGER_VALIDATE__17 ,
#define P00_INTEGER_CLASSIFY__18 l
#define P00_INTEGER_VALIDATE__18 ,
#define P00_INTEGER_CLASSIFY__19 ll
#define P00_INTEGER_VALIDATE__19 ,
#define P00_INTEGER_CLASSIFY__21 h
#define P00_INTEGER_VALIDATE__21 ,
#define P00_INTEGER_CLASSIFY__25 hh
#define P00_INTEGER_VALIDATE__25 ,
#define P00_INTEGER_CLASSIFY__33 u
#define P00_INTEGER_VALIDATE__33 ,
#define P00_INTEGER_CLASSIFY__34 ul
#define P00_INTEGER_VALIDATE__34 ,
#define P00_INTEGER_CLASSIFY__35 ull
#define P00_INTEGER_VALIDATE__35 ,
#define P00_INTEGER_CLASSIFY__37 uh
#define P00_INTEGER_VALIDATE__37 ,
#define P00_INTEGER_CLASSIFY__41 uhh
#define P00_INTEGER_VALIDATE__41 ,
#define P00_INTEGER_CLASSIFY__65 i
#define P00_INTEGER_VALIDATE__65 ,
#define P00_INTEGER_CLASSIFY__66 l
#define P00_INTEGER_VALIDATE__66 ,
#define P00_INTEGER_CLASSIFY__67 ll
#define P00_INTEGER_VALIDATE__67 ,
#define P00_INTEGER_CLASSIFY__69 h
#define P00_INTEGER_VALIDATE__69 ,
#define P00_INTEGER_CLASSIFY__81 i
#define P00_INTEGER_VALIDATE__81 ,
#define P00_INTEGER_CLASSIFY__82 l
#define P00_INTEGER_VALIDATE__82 ,
#define P00_INTEGER_CLASSIFY__83 ll
#define P00_INTEGER_VALIDATE__83 ,
#define P00_INTEGER_CLASSIFY__85 h
#define P00_INTEGER_VALIDATE__85 ,
#define P00_INTEGER_CLASSIFY__97 u
#define P00_INTEGER_VALIDATE__97 ,
#define P00_INTEGER_CLASSIFY__98 ul
#define P00_INTEGER_VALIDATE__98 ,
#define P00_INTEGER_CLASSIFY__99 ull
#define P00_INTEGER_VALIDATE__99 ,
#define P00_INTEGER_CLASSIFY__101 uh
#define P00_INTEGER_VALIDATE__101 ,
#define P00_FLOAT_CLASSIFY_long /* 1 */ ,
#define P00_FLOAT_CLASSIFY_double /* 4 */ ,,,,
#define P00_FLOAT_CLASSIFY_float /* 16 */ ,,,,,,,,,,,,,,,,
#define P00_FLOAT_CLASSIFY__Complex /* 32 */ ,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,
#define P00_FLOAT_CLASSIFY__5 d
#define P00_FLOAT_VALIDATE__5 ,
#define P00_FLOAT_CLASSIFY__6 ld
#define P00_FLOAT_VALIDATE__6 ,
#define P00_FLOAT_CLASSIFY__17 f
#define P00_FLOAT_VALIDATE__17 ,
#define P00_FLOAT_CLASSIFY__37 dc
#define P00_FLOAT_VALIDATE__37 ,
#define P00_FLOAT_CLASSIFY__38 ldc
#define P00_FLOAT_VALIDATE__38 ,
#define P00_FLOAT_CLASSIFY__49 fc
#define P00_FLOAT_VALIDATE__49 ,
/**
 ** @brief Find a builtin type according to a code such as `ull' or `ld'
 **
 ** E.g ::P99_BUILTIN_TYPE(ull) should expand to @c unsigned @c long
 ** @c long. The complete list for the 35 builtin types (+ required typedefs):
 ** <table>
 ** <tr><th>code</th><th>type</th><th>is signed</th><th>signed</th><th>unsigned</th><th>integer rank</th></tr>
 ** <tr><td>b</td><td><code>_Bool</code></td><td>0</td><td></td><td>b</td><td>0</td></tr>
 ** <tr><td>c</td><td><code>char</code></td><td></td><td>hh</td><td>uhh</td><td>1</td></tr>
 ** <tr><td>d</td><td><code>double</code></td><td></td><td></td><td></td><td></td></tr>
 ** <tr><td>dc</td><td><code>double _Complex</code></td><td></td><td></td><td></td><td></td></tr>
 ** <tr><td>f</td><td><code>float</code></td><td></td><td></td><td></td><td></td></tr>
 ** <tr><td>fc</td><td><code>float _Complex</code></td><td></td><td></td><td></td><td></td></tr>
 ** <tr><td>i128</td><td><code>int_least128_t</code></td><td></td><td></td><td></td><td></td></tr>
 ** <tr><td>i16</td><td><code>int_least16_t</code></td><td></td><td></td><td></td><td></td></tr>
 ** <tr><td>i32</td><td><code>int_least32_t</code></td><td></td><td></td><td></td><td></td></tr>
 ** <tr><td>i64</td><td><code>int_least64_t</code></td><td></td><td></td><td></td><td></td></tr>
 ** <tr><td>i8</td><td><code>int_least8_t</code></td><td></td><td></td><td></td><td></td></tr>
 ** <tr><td>j</td><td><code>intmax_t</code></td><td></td><td></td><td></td><td></td></tr>
 ** <tr><td>ld</td><td><code>long double</code></td><td></td><td></td><td></td><td></td></tr>
 ** <tr><td>ldc</td><td><code>long double _Complex</code></td><td></td><td></td><td></td><td></td></tr>
 ** <tr><td>t</td><td><code>ptrdiff_t</code></td><td></td><td></td><td></td><td></td></tr>
 ** <tr><td>i</td><td><code>signed</code></td><td>1</td><td>i</td><td>u</td><td>3</td></tr>
 ** <tr><td>hh</td><td><code>signed char</code></td><td>1</td><td>hh</td><td>uhh</td><td>1</td></tr>
 ** <tr><td>l</td><td><code>signed long</code></td><td>1</td><td>l</td><td>ul</td><td>4</td></tr>
 ** <tr><td>ll</td><td><code>signed long long</code></td><td>1</td><td>ll</td><td>ull</td><td>5</td></tr>
 ** <tr><td>h</td><td><code>signed short</code></td><td>1</td><td>h</td><td>uh</td><td>2</td></tr>
 ** <tr><td>uz</td><td><code>size_t</code></td><td></td><td></td><td></td><td></td></tr>
 ** <tr><td>u128</td><td><code>uint_least128_t</code></td><td></td><td></td><td></td><td></td></tr>
 ** <tr><td>u16</td><td><code>uint_least16_t</code></td><td></td><td></td><td></td><td></td></tr>
 ** <tr><td>u32</td><td><code>uint_least32_t</code></td><td></td><td></td><td></td><td></td></tr>
 ** <tr><td>u64</td><td><code>uint_least64_t</code></td><td></td><td></td><td></td><td></td></tr>
 ** <tr><td>u8</td><td><code>uint_least8_t</code></td><td></td><td></td><td></td><td></td></tr>
 ** <tr><td>uj</td><td><code>uintmax_t</code></td><td></td><td></td><td></td><td></td></tr>
 ** <tr><td>u</td><td><code>unsigned</code></td><td>0</td><td>i</td><td>u</td><td>3</td></tr>
 ** <tr><td>uc</td><td><code>unsigned char</code></td><td></td><td></td><td></td><td></td></tr>
 ** <tr><td>ul</td><td><code>unsigned long</code></td><td>0</td><td>l</td><td>ul</td><td>4</td></tr>
 ** <tr><td>ull</td><td><code>unsigned long long</code></td><td>0</td><td>ll</td><td>ull</td><td>5</td></tr>
 ** <tr><td>uh</td><td><code>unsigned short</code></td><td>0</td><td>h</td><td>uh</td><td>2</td></tr>
 ** <tr><td>v</td><td><code>void</code></td><td></td><td></td><td></td><td></td></tr>
 ** </table>
 **/
#define P99_BUILTIN_TYPE(...) P99_PASTE2(P00_, P99_PASTE(BUILTIN_TYPE_, __VA_ARGS__))
#define P00_BUILTIN_TYPE_ signed
#define P00_BUILTIN_TYPE_b _Bool
#define P00_BUILTIN_TYPE_c char
#define P00_BUILTIN_TYPE_d double
#define P00_BUILTIN_TYPE_dc double _Complex
#define P00_BUILTIN_TYPE_f float
#define P00_BUILTIN_TYPE_fc float _Complex
#define P00_BUILTIN_TYPE_h signed short
#define P00_BUILTIN_TYPE_hh signed char
#define P00_BUILTIN_TYPE_i signed
#define P00_BUILTIN_TYPE_i128 int_least128_t
#define P00_BUILTIN_TYPE_i16 int_least16_t
#define P00_BUILTIN_TYPE_i32 int_least32_t
#define P00_BUILTIN_TYPE_i64 int_least64_t
#define P00_BUILTIN_TYPE_i8 int_least8_t
#define P00_BUILTIN_TYPE_j intmax_t
#define P00_BUILTIN_TYPE_l signed long
#define P00_BUILTIN_TYPE_ld long double
#define P00_BUILTIN_TYPE_ldc long double _Complex
#define P00_BUILTIN_TYPE_ll signed long long
#define P00_BUILTIN_TYPE_t ptrdiff_t
#define P00_BUILTIN_TYPE_u unsigned
#define P00_BUILTIN_TYPE_u128 uint_least128_t
#define P00_BUILTIN_TYPE_u16 uint_least16_t
#define P00_BUILTIN_TYPE_u32 uint_least32_t
#define P00_BUILTIN_TYPE_u64 uint_least64_t
#define P00_BUILTIN_TYPE_u8 uint_least8_t
#define P00_BUILTIN_TYPE_uc unsigned char
#define P00_BUILTIN_TYPE_uh unsigned short
#define P00_BUILTIN_TYPE_uhh unsigned char
#define P00_BUILTIN_TYPE_uj uintmax_t
#define P00_BUILTIN_TYPE_ul unsigned long
#define P00_BUILTIN_TYPE_ull unsigned long long
#define P00_BUILTIN_TYPE_uz size_t
#define P00_BUILTIN_TYPE_v void
#define P99_BUILTIN_MAX(...) P99_PASTE2(P00_, P99_PASTE(BUILTIN_MAX_, __VA_ARGS__))
#define P00_BUILTIN_MAX_ INT_MAX
#define P00_BUILTIN_MAX_b 1
#define P00_BUILTIN_MAX_c CHAR_MAX
#define P00_BUILTIN_MAX_h SHRT_MAX
#define P00_BUILTIN_MAX_hh SCHAR_MAX
#define P00_BUILTIN_MAX_i INT_MAX
#define P00_BUILTIN_MAX_i128 INT128_MAX
#define P00_BUILTIN_MAX_i16 INT16_MAX
#define P00_BUILTIN_MAX_i32 INT32_MAX
#define P00_BUILTIN_MAX_i64 INT64_MAX
#define P00_BUILTIN_MAX_i8 INT8_MAX
#define P00_BUILTIN_MAX_j INTMAX_MAX
#define P00_BUILTIN_MAX_l LONG_MAX
#define P00_BUILTIN_MAX_ll LLONG_MAX
#define P00_BUILTIN_MAX_t PTRDIFF_MAX
#define P00_BUILTIN_MAX_u UINT_MAX
#define P00_BUILTIN_MAX_u128 UINT128_MAX
#define P00_BUILTIN_MAX_u16 UINT16_MAX
#define P00_BUILTIN_MAX_u32 UINT32_MAX
#define P00_BUILTIN_MAX_u64 UINT64_MAX
#define P00_BUILTIN_MAX_u8 UINT8_MAX
#define P00_BUILTIN_MAX_uc UCHAR_MAX
#define P00_BUILTIN_MAX_uh USHRT_MAX
#define P00_BUILTIN_MAX_uhh UCHAR_MAX
#define P00_BUILTIN_MAX_uj UINTMAX_MAX
#define P00_BUILTIN_MAX_ul ULONG_MAX
#define P00_BUILTIN_MAX_ull ULLONG_MAX
#define P00_BUILTIN_MAX_uz SIZE_MAX
#define P99_BUILTIN_MIN(...) P99_PASTE2(P00_, P99_PASTE(BUILTIN_MIN_, __VA_ARGS__))
#define P00_BUILTIN_MIN_ INT_MIN
#define P00_BUILTIN_MIN_b 0
#define P00_BUILTIN_MIN_c CHAR_MIN
#define P00_BUILTIN_MIN_h SHRT_MIN
#define P00_BUILTIN_MIN_hh SCHAR_MIN
#define P00_BUILTIN_MIN_i INT_MIN
#define P00_BUILTIN_MIN_i128 INT128_MIN
#define P00_BUILTIN_MIN_i16 INT16_MIN
#define P00_BUILTIN_MIN_i32 INT32_MIN
#define P00_BUILTIN_MIN_i64 INT64_MIN
#define P00_BUILTIN_MIN_i8 INT8_MIN
#define P00_BUILTIN_MIN_j INTMAX_MIN
#define P00_BUILTIN_MIN_l LONG_MIN
#define P00_BUILTIN_MIN_ll LLONG_MIN
#define P00_BUILTIN_MIN_t PTRDIFF_MIN
#define P00_BUILTIN_MIN_u 0
#define P00_BUILTIN_MIN_u128 UINT128_C(0)
#define P00_BUILTIN_MIN_u16 UINT16_C(0)
#define P00_BUILTIN_MIN_u32 UINT32_C(0)
#define P00_BUILTIN_MIN_u64 UINT64_C(0)
#define P00_BUILTIN_MIN_u8 UINT8_C(0)
#define P00_BUILTIN_MIN_uc 0
#define P00_BUILTIN_MIN_uh 0
#define P00_BUILTIN_MIN_uhh 0
#define P00_BUILTIN_MIN_uj 0ULL
#define P00_BUILTIN_MIN_ul 0UL
#define P00_BUILTIN_MIN_ull 0ULL
#define P00_BUILTIN_MIN_uz 0
#define P99_INTEGER_RANK(...) P99_PASTE2(P00_, P99_PASTE(INTEGER_RANK_, __VA_ARGS__))
#define P00_INTEGER_RANK_ 3
#define P00_INTEGER_RANK_b 0
#define P00_INTEGER_RANK_c 1
#define P00_INTEGER_RANK_h 2
#define P00_INTEGER_RANK_hh 1
#define P00_INTEGER_RANK_i 3
#define P00_INTEGER_RANK_l 4
#define P00_INTEGER_RANK_ll 5
#define P00_INTEGER_RANK_u 3
#define P00_INTEGER_RANK_uh 2
#define P00_INTEGER_RANK_uhh 1
#define P00_INTEGER_RANK_ul 4
#define P00_INTEGER_RANK_ull 5
#define P99_INTEGER_SIGN(...) P99_PASTE2(P00_, P99_PASTE(INTEGER_SIGN_, __VA_ARGS__))
#define P00_INTEGER_SIGN_ 1
#define P00_INTEGER_SIGN_b 0
#define P00_INTEGER_SIGN_h 1
#define P00_INTEGER_SIGN_hh 1
#define P00_INTEGER_SIGN_i 1
#define P00_INTEGER_SIGN_l 1
#define P00_INTEGER_SIGN_ll 1
#define P00_INTEGER_SIGN_u 0
#define P00_INTEGER_SIGN_uh 0
#define P00_INTEGER_SIGN_uhh 0
#define P00_INTEGER_SIGN_ul 0
#define P00_INTEGER_SIGN_ull 0
#define P99_INTEGER_SIGNED(...) P99_PASTE2(P00_, P99_PASTE(INTEGER_SIGNED_, __VA_ARGS__))
#define P00_INTEGER_SIGNED_ i
#define P00_INTEGER_SIGNED_1 hh
#define P00_INTEGER_SIGNED_2 h
#define P00_INTEGER_SIGNED_3 i
#define P00_INTEGER_SIGNED_4 l
#define P00_INTEGER_SIGNED_5 ll
#define P00_INTEGER_SIGNED_c hh
#define P00_INTEGER_SIGNED_h h
#define P00_INTEGER_SIGNED_hh hh
#define P00_INTEGER_SIGNED_i i
#define P00_INTEGER_SIGNED_l l
#define P00_INTEGER_SIGNED_ll ll
#define P00_INTEGER_SIGNED_u i
#define P00_INTEGER_SIGNED_uh h
#define P00_INTEGER_SIGNED_uhh hh
#define P00_INTEGER_SIGNED_ul l
#define P00_INTEGER_SIGNED_ull ll
#define P99_INTEGER_UNSIGNED(...) P99_PASTE2(P00_, P99_PASTE(INTEGER_UNSIGNED_, __VA_ARGS__))
#define P00_INTEGER_UNSIGNED_ u
#define P00_INTEGER_UNSIGNED_0 b
#define P00_INTEGER_UNSIGNED_1 uhh
#define P00_INTEGER_UNSIGNED_2 uh
#define P00_INTEGER_UNSIGNED_3 u
#define P00_INTEGER_UNSIGNED_4 ul
#define P00_INTEGER_UNSIGNED_5 ull
#define P00_INTEGER_UNSIGNED_b b
#define P00_INTEGER_UNSIGNED_c uhh
#define P00_INTEGER_UNSIGNED_h uh
#define P00_INTEGER_UNSIGNED_hh uhh
#define P00_INTEGER_UNSIGNED_i u
#define P00_INTEGER_UNSIGNED_l ul
#define P00_INTEGER_UNSIGNED_ll ull
#define P00_INTEGER_UNSIGNED_u u
#define P00_INTEGER_UNSIGNED_uh uh
#define P00_INTEGER_UNSIGNED_uhh uhh
#define P00_INTEGER_UNSIGNED_ul ul
#define P00_INTEGER_UNSIGNED_ull ull
/**
 ** @}
 **/
#define P00_PRED_1 0
#define P00_PRED_2 1
#define P00_PRED_3 2
#define P00_PRED_4 3
#define P00_PRED_5 4
#define P00_PRED_6 5
#define P00_PRED_7 6
#define P00_PRED_8 7
#define P00_PRED_9 8
#define P00_PRED_10 9
#define P00_PRED_11 10
#define P00_PRED_12 11
#define P00_PRED_13 12
#define P00_PRED_14 13
#define P00_PRED_15 14
#define P00_PRED_16 15
#define P00_PRED_17 16
#define P00_PRED_18 17
#define P00_PRED_19 18
#define P00_PRED_20 19
#define P00_PRED_21 20
#define P00_PRED_22 21
#define P00_PRED_23 22
#define P00_PRED_24 23
#define P00_PRED_25 24
#define P00_PRED_26 25
#define P00_PRED_27 26
#define P00_PRED_28 27
#define P00_PRED_29 28
#define P00_PRED_30 29
#define P00_PRED_31 30
#define P00_PRED_32 31
#define P00_PRED_33 32
#define P00_PRED_34 33
#define P00_PRED_35 34
#define P00_PRED_36 35
#define P00_PRED_37 36
#define P00_PRED_38 37
#define P00_PRED_39 38
#define P00_PRED_40 39
#define P00_PRED_41 40
#define P00_PRED_42 41
#define P00_PRED_43 42
#define P00_PRED_44 43
#define P00_PRED_45 44
#define P00_PRED_46 45
#define P00_PRED_47 46
#define P00_PRED_48 47
#define P00_PRED_49 48
#define P00_PRED_50 49
#define P00_PRED_51 50
#define P00_PRED_52 51
#define P00_PRED_53 52
#define P00_PRED_54 53
#define P00_PRED_55 54
#define P00_PRED_56 55
#define P00_PRED_57 56
#define P00_PRED_58 57
#define P00_PRED_59 58
#define P00_PRED_60 59
#define P00_PRED_61 60
#define P00_PRED_62 61
#define P00_PRED_63 62
#define P00_PRED_64 63
#define P00_PRED_65 64
#define P00_PRED_66 65
#define P00_PRED_67 66
#define P00_PRED_68 67
#define P00_PRED_69 68
#define P00_PRED_70 69
#define P00_PRED_71 70
#define P00_PRED_72 71
#define P00_PRED_73 72
#define P00_PRED_74 73
#define P00_PRED_75 74
#define P00_PRED_76 75
#define P00_PRED_77 76
#define P00_PRED_78 77
#define P00_PRED_79 78
#define P00_PRED_80 79
#define P00_PRED_81 80
#define P00_PRED_82 81
#define P00_PRED_83 82
#define P00_PRED_84 83
#define P00_PRED_85 84
#define P00_PRED_86 85
#define P00_PRED_87 86
#define P00_PRED_88 87
#define P00_PRED_89 88
#define P00_PRED_90 89
#define P00_PRED_91 90
#define P00_PRED_92 91
#define P00_PRED_93 92
#define P00_PRED_94 93
#define P00_PRED_95 94
#define P00_PRED_96 95
#define P00_PRED_97 96
#define P00_PRED_98 97
#define P00_PRED_99 98
#define P00_PRED_100 99
#define P00_PRED_101 100
#define P00_PRED_102 101
#define P00_PRED_103 102
#define P00_PRED_104 103
#define P00_PRED_105 104
#define P00_PRED_106 105
#define P00_PRED_107 106
#define P00_PRED_108 107
#define P00_PRED_109 108
#define P00_PRED_110 109
#define P00_PRED_111 110
#define P00_PRED_112 111
#define P00_PRED_113 112
#define P00_PRED_114 113
#define P00_PRED_115 114
#define P00_PRED_116 115
#define P00_PRED_117 116
#define P00_PRED_118 117
#define P00_PRED_119 118
#define P00_PRED_120 119
#define P00_PRED_121 120
#define P00_PRED_122 121
#define P00_PRED_123 122
#define P00_PRED_124 123
#define P00_PRED_125 124
#define P00_PRED_126 125
#define P00_PRED_127 126
#define P00_PRED_128 127
#define P00_PRED_129 128
#define P00_PRED_130 129
#define P00_PRED_131 130
#define P00_PRED_132 131
#define P00_PRED_133 132
#define P00_PRED_134 133
#define P00_PRED_135 134
#define P00_PRED_136 135
#define P00_PRED_137 136
#define P00_PRED_138 137
#define P00_PRED_139 138
#define P00_PRED_140 139
#define P00_PRED_141 140
#define P00_PRED_142 141
#define P00_PRED_143 142
#define P00_PRED_144 143
#define P00_PRED_145 144
#define P00_PRED_146 145
#define P00_PRED_147 146
#define P00_PRED_148 147
#define P00_PRED_149 148
#define P00_PRED_150 149
#define P00_PRED_151 150
#define P00_PRED_152 151
#define P00_PRED_153 152
#define P00_PRED_154 153
#define P00_PRED_155 154
#define P00_PRED_156 155
#define P00_PRED_157 156
#define P00_PRED_158 157
#define P00_PRED_159 158
#define P00_PRED_160 159
#define P00_PRED_minus_0 minus_1
#define P00_PRED_minus_1 minus_2
#define P00_PRED_minus_2 minus_3
#define P00_PRED_minus_3 minus_4
#define P00_PRED_minus_4 minus_5
#define P00_PRED_minus_5 minus_6
#define P00_PRED_minus_6 minus_7
#define P00_PRED_minus_7 minus_8
#define P00_PRED_minus_8 minus_9
#define P00_PRED_minus_9 minus_10
#define P00_PRED_minus_10 minus_11
#define P00_PRED_minus_11 minus_12
#define P00_PRED_minus_12 minus_13
#define P00_PRED_minus_13 minus_14
#define P00_PRED_minus_14 minus_15
#define P00_PRED_minus_15 minus_16
#define P00_PRED_minus_16 minus_17
#define P00_PRED_minus_17 minus_18
#define P00_PRED_minus_18 minus_19
#define P00_PRED_minus_19 minus_20
#define P00_PRED_minus_20 minus_21
#define P00_PRED_minus_21 minus_22
#define P00_PRED_minus_22 minus_23
#define P00_PRED_minus_23 minus_24
#define P00_PRED_minus_24 minus_25
#define P00_PRED_minus_25 minus_26
#define P00_PRED_minus_26 minus_27
#define P00_PRED_minus_27 minus_28
#define P00_PRED_minus_28 minus_29
#define P00_PRED_minus_29 minus_30
#define P00_PRED_minus_30 minus_31
#define P00_PRED_minus_31 minus_32
#define P00_PRED_minus_32 minus_33
#define P00_PRED_minus_33 minus_34
#define P00_PRED_minus_34 minus_35
#define P00_PRED_minus_35 minus_36
#define P00_PRED_minus_36 minus_37
#define P00_PRED_minus_37 minus_38
#define P00_PRED_minus_38 minus_39
#define P00_PRED_minus_39 minus_40
#define P00_PRED_minus_40 minus_41
#define P00_PRED_minus_41 minus_42
#define P00_PRED_minus_42 minus_43
#define P00_PRED_minus_43 minus_44
#define P00_PRED_minus_44 minus_45
#define P00_PRED_minus_45 minus_46
#define P00_PRED_minus_46 minus_47
#define P00_PRED_minus_47 minus_48
#define P00_PRED_minus_48 minus_49
#define P00_PRED_minus_49 minus_50
#define P00_PRED_minus_50 minus_51
#define P00_PRED_minus_51 minus_52
#define P00_PRED_minus_52 minus_53
#define P00_PRED_minus_53 minus_54
#define P00_PRED_minus_54 minus_55
#define P00_PRED_minus_55 minus_56
#define P00_PRED_minus_56 minus_57
#define P00_PRED_minus_57 minus_58
#define P00_PRED_minus_58 minus_59
#define P00_PRED_minus_59 minus_60
#define P00_PRED_minus_60 minus_61
#define P00_PRED_minus_61 minus_62
#define P00_PRED_minus_62 minus_63
#define P00_PRED_minus_63 minus_64
#define P00_PRED_minus_64 minus_65
#define P00_PRED_minus_65 minus_66
#define P00_PRED_minus_66 minus_67
#define P00_PRED_minus_67 minus_68
#define P00_PRED_minus_68 minus_69
#define P00_PRED_minus_69 minus_70
#define P00_PRED_minus_70 minus_71
#define P00_PRED_minus_71 minus_72
#define P00_PRED_minus_72 minus_73
#define P00_PRED_minus_73 minus_74
#define P00_PRED_minus_74 minus_75
#define P00_PRED_minus_75 minus_76
#define P00_PRED_minus_76 minus_77
#define P00_PRED_minus_77 minus_78
#define P00_PRED_minus_78 minus_79
#define P00_PRED_minus_79 minus_80
#define P00_PRED_minus_80 minus_81
#define P00_PRED_minus_81 minus_82
#define P00_PRED_minus_82 minus_83
#define P00_PRED_minus_83 minus_84
#define P00_PRED_minus_84 minus_85
#define P00_PRED_minus_85 minus_86
#define P00_PRED_minus_86 minus_87
#define P00_PRED_minus_87 minus_88
#define P00_PRED_minus_88 minus_89
#define P00_PRED_minus_89 minus_90
#define P00_PRED_minus_90 minus_91
#define P00_PRED_minus_91 minus_92
#define P00_PRED_minus_92 minus_93
#define P00_PRED_minus_93 minus_94
#define P00_PRED_minus_94 minus_95
#define P00_PRED_minus_95 minus_96
#define P00_PRED_minus_96 minus_97
#define P00_PRED_minus_97 minus_98
#define P00_PRED_minus_98 minus_99
#define P00_PRED_minus_99 minus_100
#define P00_PRED_minus_100 minus_101
#define P00_PRED_minus_101 minus_102
#define P00_PRED_minus_102 minus_103
#define P00_PRED_minus_103 minus_104
#define P00_PRED_minus_104 minus_105
#define P00_PRED_minus_105 minus_106
#define P00_PRED_minus_106 minus_107
#define P00_PRED_minus_107 minus_108
#define P00_PRED_minus_108 minus_109
#define P00_PRED_minus_109 minus_110
#define P00_PRED_minus_110 minus_111
#define P00_PRED_minus_111 minus_112
#define P00_PRED_minus_112 minus_113
#define P00_PRED_minus_113 minus_114
#define P00_PRED_minus_114 minus_115
#define P00_PRED_minus_115 minus_116
#define P00_PRED_minus_116 minus_117
#define P00_PRED_minus_117 minus_118
#define P00_PRED_minus_118 minus_119
#define P00_PRED_minus_119 minus_120
#define P00_PRED_minus_120 minus_121
#define P00_PRED_minus_121 minus_122
#define P00_PRED_minus_122 minus_123
#define P00_PRED_minus_123 minus_124
#define P00_PRED_minus_124 minus_125
#define P00_PRED_minus_125 minus_126
#define P00_PRED_minus_126 minus_127
#define P00_PRED_minus_127 minus_128
#define P00_PRED_minus_128 minus_129
#define P00_PRED_minus_129 minus_130
#define P00_PRED_minus_130 minus_131
#define P00_PRED_minus_131 minus_132
#define P00_PRED_minus_132 minus_133
#define P00_PRED_minus_133 minus_134
#define P00_PRED_minus_134 minus_135
#define P00_PRED_minus_135 minus_136
#define P00_PRED_minus_136 minus_137
#define P00_PRED_minus_137 minus_138
#define P00_PRED_minus_138 minus_139
#define P00_PRED_minus_139 minus_140
#define P00_PRED_minus_140 minus_141
#define P00_PRED_minus_141 minus_142
#define P00_PRED_minus_142 minus_143
#define P00_PRED_minus_143 minus_144
#define P00_PRED_minus_144 minus_145
#define P00_PRED_minus_145 minus_146
#define P00_PRED_minus_146 minus_147
#define P00_PRED_minus_147 minus_148
#define P00_PRED_minus_148 minus_149
#define P00_PRED_minus_149 minus_150
#define P00_PRED_minus_150 minus_151
#define P00_PRED_minus_151 minus_152
#define P00_PRED_minus_152 minus_153
#define P00_PRED_minus_153 minus_154
#define P00_PRED_minus_154 minus_155
#define P00_PRED_minus_155 minus_156
#define P00_PRED_minus_156 minus_157
#define P00_PRED_minus_157 minus_158
#define P00_PRED_minus_158 minus_159
#define P00_PRED_minus_159 minus_160
#define P00_minus_minus_0 0
#define P00_minus_minus_1 1
#define P00_minus_minus_2 2
#define P00_minus_minus_3 3
#define P00_minus_minus_4 4
#define P00_minus_minus_5 5
#define P00_minus_minus_6 6
#define P00_minus_minus_7 7
#define P00_minus_minus_8 8
#define P00_minus_minus_9 9
#define P00_minus_minus_10 10
#define P00_minus_minus_11 11
#define P00_minus_minus_12 12
#define P00_minus_minus_13 13
#define P00_minus_minus_14 14
#define P00_minus_minus_15 15
#define P00_minus_minus_16 16
#define P00_minus_minus_17 17
#define P00_minus_minus_18 18
#define P00_minus_minus_19 19
#define P00_minus_minus_20 20
#define P00_minus_minus_21 21
#define P00_minus_minus_22 22
#define P00_minus_minus_23 23
#define P00_minus_minus_24 24
#define P00_minus_minus_25 25
#define P00_minus_minus_26 26
#define P00_minus_minus_27 27
#define P00_minus_minus_28 28
#define P00_minus_minus_29 29
#define P00_minus_minus_30 30
#define P00_minus_minus_31 31
#define P00_minus_minus_32 32
#define P00_minus_minus_33 33
#define P00_minus_minus_34 34
#define P00_minus_minus_35 35
#define P00_minus_minus_36 36
#define P00_minus_minus_37 37
#define P00_minus_minus_38 38
#define P00_minus_minus_39 39
#define P00_minus_minus_40 40
#define P00_minus_minus_41 41
#define P00_minus_minus_42 42
#define P00_minus_minus_43 43
#define P00_minus_minus_44 44
#define P00_minus_minus_45 45
#define P00_minus_minus_46 46
#define P00_minus_minus_47 47
#define P00_minus_minus_48 48
#define P00_minus_minus_49 49
#define P00_minus_minus_50 50
#define P00_minus_minus_51 51
#define P00_minus_minus_52 52
#define P00_minus_minus_53 53
#define P00_minus_minus_54 54
#define P00_minus_minus_55 55
#define P00_minus_minus_56 56
#define P00_minus_minus_57 57
#define P00_minus_minus_58 58
#define P00_minus_minus_59 59
#define P00_minus_minus_60 60
#define P00_minus_minus_61 61
#define P00_minus_minus_62 62
#define P00_minus_minus_63 63
#define P00_minus_minus_64 64
#define P00_minus_minus_65 65
#define P00_minus_minus_66 66
#define P00_minus_minus_67 67
#define P00_minus_minus_68 68
#define P00_minus_minus_69 69
#define P00_minus_minus_70 70
#define P00_minus_minus_71 71
#define P00_minus_minus_72 72
#define P00_minus_minus_73 73
#define P00_minus_minus_74 74
#define P00_minus_minus_75 75
#define P00_minus_minus_76 76
#define P00_minus_minus_77 77
#define P00_minus_minus_78 78
#define P00_minus_minus_79 79
#define P00_minus_minus_80 80
#define P00_minus_minus_81 81
#define P00_minus_minus_82 82
#define P00_minus_minus_83 83
#define P00_minus_minus_84 84
#define P00_minus_minus_85 85
#define P00_minus_minus_86 86
#define P00_minus_minus_87 87
#define P00_minus_minus_88 88
#define P00_minus_minus_89 89
#define P00_minus_minus_90 90
#define P00_minus_minus_91 91
#define P00_minus_minus_92 92
#define P00_minus_minus_93 93
#define P00_minus_minus_94 94
#define P00_minus_minus_95 95
#define P00_minus_minus_96 96
#define P00_minus_minus_97 97
#define P00_minus_minus_98 98
#define P00_minus_minus_99 99
#define P00_minus_minus_100 100
#define P00_minus_minus_101 101
#define P00_minus_minus_102 102
#define P00_minus_minus_103 103
#define P00_minus_minus_104 104
#define P00_minus_minus_105 105
#define P00_minus_minus_106 106
#define P00_minus_minus_107 107
#define P00_minus_minus_108 108
#define P00_minus_minus_109 109
#define P00_minus_minus_110 110
#define P00_minus_minus_111 111
#define P00_minus_minus_112 112
#define P00_minus_minus_113 113
#define P00_minus_minus_114 114
#define P00_minus_minus_115 115
#define P00_minus_minus_116 116
#define P00_minus_minus_117 117
#define P00_minus_minus_118 118
#define P00_minus_minus_119 119
#define P00_minus_minus_120 120
#define P00_minus_minus_121 121
#define P00_minus_minus_122 122
#define P00_minus_minus_123 123
#define P00_minus_minus_124 124
#define P00_minus_minus_125 125
#define P00_minus_minus_126 126
#define P00_minus_minus_127 127
#define P00_minus_minus_128 128
#define P00_minus_minus_129 129
#define P00_minus_minus_130 130
#define P00_minus_minus_131 131
#define P00_minus_minus_132 132
#define P00_minus_minus_133 133
#define P00_minus_minus_134 134
#define P00_minus_minus_135 135
#define P00_minus_minus_136 136
#define P00_minus_minus_137 137
#define P00_minus_minus_138 138
#define P00_minus_minus_139 139
#define P00_minus_minus_140 140
#define P00_minus_minus_141 141
#define P00_minus_minus_142 142
#define P00_minus_minus_143 143
#define P00_minus_minus_144 144
#define P00_minus_minus_145 145
#define P00_minus_minus_146 146
#define P00_minus_minus_147 147
#define P00_minus_minus_148 148
#define P00_minus_minus_149 149
#define P00_minus_minus_150 150
#define P00_minus_minus_151 151
#define P00_minus_minus_152 152
#define P00_minus_minus_153 153
#define P00_minus_minus_154 154
#define P00_minus_minus_155 155
#define P00_minus_minus_156 156
#define P00_minus_minus_157 157
#define P00_minus_minus_158 158
#define P00_minus_minus_159 159
#define P00_IS_0_GE_0 ,
#define P00_IS_1_GE_0 ,
#define P00_IS_2_GE_0 ,
#define P00_IS_3_GE_0 ,
#define P00_IS_4_GE_0 ,
#define P00_IS_5_GE_0 ,
#define P00_IS_6_GE_0 ,
#define P00_IS_7_GE_0 ,
#define P00_IS_8_GE_0 ,
#define P00_IS_9_GE_0 ,
#define P00_IS_10_GE_0 ,
#define P00_IS_11_GE_0 ,
#define P00_IS_12_GE_0 ,
#define P00_IS_13_GE_0 ,
#define P00_IS_14_GE_0 ,
#define P00_IS_15_GE_0 ,
#define P00_IS_16_GE_0 ,
#define P00_IS_17_GE_0 ,
#define P00_IS_18_GE_0 ,
#define P00_IS_19_GE_0 ,
#define P00_IS_20_GE_0 ,
#define P00_IS_21_GE_0 ,
#define P00_IS_22_GE_0 ,
#define P00_IS_23_GE_0 ,
#define P00_IS_24_GE_0 ,
#define P00_IS_25_GE_0 ,
#define P00_IS_26_GE_0 ,
#define P00_IS_27_GE_0 ,
#define P00_IS_28_GE_0 ,
#define P00_IS_29_GE_0 ,
#define P00_IS_30_GE_0 ,
#define P00_IS_31_GE_0 ,
#define P00_IS_32_GE_0 ,
#define P00_IS_33_GE_0 ,
#define P00_IS_34_GE_0 ,
#define P00_IS_35_GE_0 ,
#define P00_IS_36_GE_0 ,
#define P00_IS_37_GE_0 ,
#define P00_IS_38_GE_0 ,
#define P00_IS_39_GE_0 ,
#define P00_IS_40_GE_0 ,
#define P00_IS_41_GE_0 ,
#define P00_IS_42_GE_0 ,
#define P00_IS_43_GE_0 ,
#define P00_IS_44_GE_0 ,
#define P00_IS_45_GE_0 ,
#define P00_IS_46_GE_0 ,
#define P00_IS_47_GE_0 ,
#define P00_IS_48_GE_0 ,
#define P00_IS_49_GE_0 ,
#define P00_IS_50_GE_0 ,
#define P00_IS_51_GE_0 ,
#define P00_IS_52_GE_0 ,
#define P00_IS_53_GE_0 ,
#define P00_IS_54_GE_0 ,
#define P00_IS_55_GE_0 ,
#define P00_IS_56_GE_0 ,
#define P00_IS_57_GE_0 ,
#define P00_IS_58_GE_0 ,
#define P00_IS_59_GE_0 ,
#define P00_IS_60_GE_0 ,
#define P00_IS_61_GE_0 ,
#define P00_IS_62_GE_0 ,
#define P00_IS_63_GE_0 ,
#define P00_IS_64_GE_0 ,
#define P00_IS_65_GE_0 ,
#define P00_IS_66_GE_0 ,
#define P00_IS_67_GE_0 ,
#define P00_IS_68_GE_0 ,
#define P00_IS_69_GE_0 ,
#define P00_IS_70_GE_0 ,
#define P00_IS_71_GE_0 ,
#define P00_IS_72_GE_0 ,
#define P00_IS_73_GE_0 ,
#define P00_IS_74_GE_0 ,
#define P00_IS_75_GE_0 ,
#define P00_IS_76_GE_0 ,
#define P00_IS_77_GE_0 ,
#define P00_IS_78_GE_0 ,
#define P00_IS_79_GE_0 ,
#define P00_IS_80_GE_0 ,
#define P00_IS_81_GE_0 ,
#define P00_IS_82_GE_0 ,
#define P00_IS_83_GE_0 ,
#define P00_IS_84_GE_0 ,
#define P00_IS_85_GE_0 ,
#define P00_IS_86_GE_0 ,
#define P00_IS_87_GE_0 ,
#define P00_IS_88_GE_0 ,
#define P00_IS_89_GE_0 ,
#define P00_IS_90_GE_0 ,
#define P00_IS_91_GE_0 ,
#define P00_IS_92_GE_0 ,
#define P00_IS_93_GE_0 ,
#define P00_IS_94_GE_0 ,
#define P00_IS_95_GE_0 ,
#define P00_IS_96_GE_0 ,
#define P00_IS_97_GE_0 ,
#define P00_IS_98_GE_0 ,
#define P00_IS_99_GE_0 ,
#define P00_IS_100_GE_0 ,
#define P00_IS_101_GE_0 ,
#define P00_IS_102_GE_0 ,
#define P00_IS_103_GE_0 ,
#define P00_IS_104_GE_0 ,
#define P00_IS_105_GE_0 ,
#define P00_IS_106_GE_0 ,
#define P00_IS_107_GE_0 ,
#define P00_IS_108_GE_0 ,
#define P00_IS_109_GE_0 ,
#define P00_IS_110_GE_0 ,
#define P00_IS_111_GE_0 ,
#define P00_IS_112_GE_0 ,
#define P00_IS_113_GE_0 ,
#define P00_IS_114_GE_0 ,
#define P00_IS_115_GE_0 ,
#define P00_IS_116_GE_0 ,
#define P00_IS_117_GE_0 ,
#define P00_IS_118_GE_0 ,
#define P00_IS_119_GE_0 ,
#define P00_IS_120_GE_0 ,
#define P00_IS_121_GE_0 ,
#define P00_IS_122_GE_0 ,
#define P00_IS_123_GE_0 ,
#define P00_IS_124_GE_0 ,
#define P00_IS_125_GE_0 ,
#define P00_IS_126_GE_0 ,
#define P00_IS_127_GE_0 ,
#define P00_IS_128_GE_0 ,
#define P00_IS_129_GE_0 ,
#define P00_IS_130_GE_0 ,
#define P00_IS_131_GE_0 ,
#define P00_IS_132_GE_0 ,
#define P00_IS_133_GE_0 ,
#define P00_IS_134_GE_0 ,
#define P00_IS_135_GE_0 ,
#define P00_IS_136_GE_0 ,
#define P00_IS_137_GE_0 ,
#define P00_IS_138_GE_0 ,
#define P00_IS_139_GE_0 ,
#define P00_IS_140_GE_0 ,
#define P00_IS_141_GE_0 ,
#define P00_IS_142_GE_0 ,
#define P00_IS_143_GE_0 ,
#define P00_IS_144_GE_0 ,
#define P00_IS_145_GE_0 ,
#define P00_IS_146_GE_0 ,
#define P00_IS_147_GE_0 ,
#define P00_IS_148_GE_0 ,
#define P00_IS_149_GE_0 ,
#define P00_IS_150_GE_0 ,
#define P00_IS_151_GE_0 ,
#define P00_IS_152_GE_0 ,
#define P00_IS_153_GE_0 ,
#define P00_IS_154_GE_0 ,
#define P00_IS_155_GE_0 ,
#define P00_IS_156_GE_0 ,
#define P00_IS_157_GE_0 ,
#define P00_IS_158_GE_0 ,
#define P00_IS_159_GE_0 ,
#define P00_dec_eval_0 0
#define P00_dec_eval_1 1
#define P00_dec_eval_2 2
#define P00_dec_eval_3 3
#define P00_dec_eval_4 4
#define P00_dec_eval_5 5
#define P00_dec_eval_6 6
#define P00_dec_eval_7 7
#define P00_dec_eval_8 8
#define P00_dec_eval_9 9
#define P00_dec_eval_10 10
#define P00_dec_eval_11 11
#define P00_dec_eval_12 12
#define P00_dec_eval_13 13
#define P00_dec_eval_14 14
#define P00_dec_eval_15 15
#define P00_dec_eval_16 16
#define P00_dec_eval_17 17
#define P00_dec_eval_18 18
#define P00_dec_eval_19 19
#define P00_dec_eval_20 20
#define P00_dec_eval_21 21
#define P00_dec_eval_22 22
#define P00_dec_eval_23 23
#define P00_dec_eval_24 24
#define P00_dec_eval_25 25
#define P00_dec_eval_26 26
#define P00_dec_eval_27 27
#define P00_dec_eval_28 28
#define P00_dec_eval_29 29
#define P00_dec_eval_30 30
#define P00_dec_eval_31 31
#define P00_dec_eval_32 32
#define P00_dec_eval_33 33
#define P00_dec_eval_34 34
#define P00_dec_eval_35 35
#define P00_dec_eval_36 36
#define P00_dec_eval_37 37
#define P00_dec_eval_38 38
#define P00_dec_eval_39 39
#define P00_dec_eval_40 40
#define P00_dec_eval_41 41
#define P00_dec_eval_42 42
#define P00_dec_eval_43 43
#define P00_dec_eval_44 44
#define P00_dec_eval_45 45
#define P00_dec_eval_46 46
#define P00_dec_eval_47 47
#define P00_dec_eval_48 48
#define P00_dec_eval_49 49
#define P00_dec_eval_50 50
#define P00_dec_eval_51 51
#define P00_dec_eval_52 52
#define P00_dec_eval_53 53
#define P00_dec_eval_54 54
#define P00_dec_eval_55 55
#define P00_dec_eval_56 56
#define P00_dec_eval_57 57
#define P00_dec_eval_58 58
#define P00_dec_eval_59 59
#define P00_dec_eval_60 60
#define P00_dec_eval_61 61
#define P00_dec_eval_62 62
#define P00_dec_eval_63 63
#define P00_dec_eval_64 64
#define P00_dec_eval_65 65
#define P00_dec_eval_66 66
#define P00_dec_eval_67 67
#define P00_dec_eval_68 68
#define P00_dec_eval_69 69
#define P00_dec_eval_70 70
#define P00_dec_eval_71 71
#define P00_dec_eval_72 72
#define P00_dec_eval_73 73
#define P00_dec_eval_74 74
#define P00_dec_eval_75 75
#define P00_dec_eval_76 76
#define P00_dec_eval_77 77
#define P00_dec_eval_78 78
#define P00_dec_eval_79 79
#define P00_dec_eval_80 80
#define P00_dec_eval_81 81
#define P00_dec_eval_82 82
#define P00_dec_eval_83 83
#define P00_dec_eval_84 84
#define P00_dec_eval_85 85
#define P00_dec_eval_86 86
#define P00_dec_eval_87 87
#define P00_dec_eval_88 88
#define P00_dec_eval_89 89
#define P00_dec_eval_90 90
#define P00_dec_eval_91 91
#define P00_dec_eval_92 92
#define P00_dec_eval_93 93
#define P00_dec_eval_94 94
#define P00_dec_eval_95 95
#define P00_dec_eval_96 96
#define P00_dec_eval_97 97
#define P00_dec_eval_98 98
#define P00_dec_eval_99 99
#define P00_dec_eval_100 100
#define P00_dec_eval_101 101
#define P00_dec_eval_102 102
#define P00_dec_eval_103 103
#define P00_dec_eval_104 104
#define P00_dec_eval_105 105
#define P00_dec_eval_106 106
#define P00_dec_eval_107 107
#define P00_dec_eval_108 108
#define P00_dec_eval_109 109
#define P00_dec_eval_110 110
#define P00_dec_eval_111 111
#define P00_dec_eval_112 112
#define P00_dec_eval_113 113
#define P00_dec_eval_114 114
#define P00_dec_eval_115 115
#define P00_dec_eval_116 116
#define P00_dec_eval_117 117
#define P00_dec_eval_118 118
#define P00_dec_eval_119 119
#define P00_dec_eval_120 120
#define P00_dec_eval_121 121
#define P00_dec_eval_122 122
#define P00_dec_eval_123 123
#define P00_dec_eval_124 124
#define P00_dec_eval_125 125
#define P00_dec_eval_126 126
#define P00_dec_eval_127 127
#define P00_dec_eval_128 128
#define P00_dec_eval_129 129
#define P00_dec_eval_130 130
#define P00_dec_eval_131 131
#define P00_dec_eval_132 132
#define P00_dec_eval_133 133
#define P00_dec_eval_134 134
#define P00_dec_eval_135 135
#define P00_dec_eval_136 136
#define P00_dec_eval_137 137
#define P00_dec_eval_138 138
#define P00_dec_eval_139 139
#define P00_dec_eval_140 140
#define P00_dec_eval_141 141
#define P00_dec_eval_142 142
#define P00_dec_eval_143 143
#define P00_dec_eval_144 144
#define P00_dec_eval_145 145
#define P00_dec_eval_146 146
#define P00_dec_eval_147 147
#define P00_dec_eval_148 148
#define P00_dec_eval_149 149
#define P00_dec_eval_150 150
#define P00_dec_eval_151 151
#define P00_dec_eval_152 152
#define P00_dec_eval_153 153
#define P00_dec_eval_154 154
#define P00_dec_eval_155 155
#define P00_dec_eval_156 156
#define P00_dec_eval_157 157
#define P00_dec_eval_158 158
#define P00_dec_eval_159 159
#define P00_dec_eval_minus_0 0
#define P00_dec_eval_minus_1 -1
#define P00_dec_eval_minus_2 -2
#define P00_dec_eval_minus_3 -3
#define P00_dec_eval_minus_4 -4
#define P00_dec_eval_minus_5 -5
#define P00_dec_eval_minus_6 -6
#define P00_dec_eval_minus_7 -7
#define P00_dec_eval_minus_8 -8
#define P00_dec_eval_minus_9 -9
#define P00_dec_eval_minus_10 -10
#define P00_dec_eval_minus_11 -11
#define P00_dec_eval_minus_12 -12
#define P00_dec_eval_minus_13 -13
#define P00_dec_eval_minus_14 -14
#define P00_dec_eval_minus_15 -15
#define P00_dec_eval_minus_16 -16
#define P00_dec_eval_minus_17 -17
#define P00_dec_eval_minus_18 -18
#define P00_dec_eval_minus_19 -19
#define P00_dec_eval_minus_20 -20
#define P00_dec_eval_minus_21 -21
#define P00_dec_eval_minus_22 -22
#define P00_dec_eval_minus_23 -23
#define P00_dec_eval_minus_24 -24
#define P00_dec_eval_minus_25 -25
#define P00_dec_eval_minus_26 -26
#define P00_dec_eval_minus_27 -27
#define P00_dec_eval_minus_28 -28
#define P00_dec_eval_minus_29 -29
#define P00_dec_eval_minus_30 -30
#define P00_dec_eval_minus_31 -31
#define P00_dec_eval_minus_32 -32
#define P00_dec_eval_minus_33 -33
#define P00_dec_eval_minus_34 -34
#define P00_dec_eval_minus_35 -35
#define P00_dec_eval_minus_36 -36
#define P00_dec_eval_minus_37 -37
#define P00_dec_eval_minus_38 -38
#define P00_dec_eval_minus_39 -39
#define P00_dec_eval_minus_40 -40
#define P00_dec_eval_minus_41 -41
#define P00_dec_eval_minus_42 -42
#define P00_dec_eval_minus_43 -43
#define P00_dec_eval_minus_44 -44
#define P00_dec_eval_minus_45 -45
#define P00_dec_eval_minus_46 -46
#define P00_dec_eval_minus_47 -47
#define P00_dec_eval_minus_48 -48
#define P00_dec_eval_minus_49 -49
#define P00_dec_eval_minus_50 -50
#define P00_dec_eval_minus_51 -51
#define P00_dec_eval_minus_52 -52
#define P00_dec_eval_minus_53 -53
#define P00_dec_eval_minus_54 -54
#define P00_dec_eval_minus_55 -55
#define P00_dec_eval_minus_56 -56
#define P00_dec_eval_minus_57 -57
#define P00_dec_eval_minus_58 -58
#define P00_dec_eval_minus_59 -59
#define P00_dec_eval_minus_60 -60
#define P00_dec_eval_minus_61 -61
#define P00_dec_eval_minus_62 -62
#define P00_dec_eval_minus_63 -63
#define P00_dec_eval_minus_64 -64
#define P00_dec_eval_minus_65 -65
#define P00_dec_eval_minus_66 -66
#define P00_dec_eval_minus_67 -67
#define P00_dec_eval_minus_68 -68
#define P00_dec_eval_minus_69 -69
#define P00_dec_eval_minus_70 -70
#define P00_dec_eval_minus_71 -71
#define P00_dec_eval_minus_72 -72
#define P00_dec_eval_minus_73 -73
#define P00_dec_eval_minus_74 -74
#define P00_dec_eval_minus_75 -75
#define P00_dec_eval_minus_76 -76
#define P00_dec_eval_minus_77 -77
#define P00_dec_eval_minus_78 -78
#define P00_dec_eval_minus_79 -79
#define P00_dec_eval_minus_80 -80
#define P00_dec_eval_minus_81 -81
#define P00_dec_eval_minus_82 -82
#define P00_dec_eval_minus_83 -83
#define P00_dec_eval_minus_84 -84
#define P00_dec_eval_minus_85 -85
#define P00_dec_eval_minus_86 -86
#define P00_dec_eval_minus_87 -87
#define P00_dec_eval_minus_88 -88
#define P00_dec_eval_minus_89 -89
#define P00_dec_eval_minus_90 -90
#define P00_dec_eval_minus_91 -91
#define P00_dec_eval_minus_92 -92
#define P00_dec_eval_minus_93 -93
#define P00_dec_eval_minus_94 -94
#define P00_dec_eval_minus_95 -95
#define P00_dec_eval_minus_96 -96
#define P00_dec_eval_minus_97 -97
#define P00_dec_eval_minus_98 -98
#define P00_dec_eval_minus_99 -99
#define P00_dec_eval_minus_100 -100
#define P00_dec_eval_minus_101 -101
#define P00_dec_eval_minus_102 -102
#define P00_dec_eval_minus_103 -103
#define P00_dec_eval_minus_104 -104
#define P00_dec_eval_minus_105 -105
#define P00_dec_eval_minus_106 -106
#define P00_dec_eval_minus_107 -107
#define P00_dec_eval_minus_108 -108
#define P00_dec_eval_minus_109 -109
#define P00_dec_eval_minus_110 -110
#define P00_dec_eval_minus_111 -111
#define P00_dec_eval_minus_112 -112
#define P00_dec_eval_minus_113 -113
#define P00_dec_eval_minus_114 -114
#define P00_dec_eval_minus_115 -115
#define P00_dec_eval_minus_116 -116
#define P00_dec_eval_minus_117 -117
#define P00_dec_eval_minus_118 -118
#define P00_dec_eval_minus_119 -119
#define P00_dec_eval_minus_120 -120
#define P00_dec_eval_minus_121 -121
#define P00_dec_eval_minus_122 -122
#define P00_dec_eval_minus_123 -123
#define P00_dec_eval_minus_124 -124
#define P00_dec_eval_minus_125 -125
#define P00_dec_eval_minus_126 -126
#define P00_dec_eval_minus_127 -127
#define P00_dec_eval_minus_128 -128
#define P00_dec_eval_minus_129 -129
#define P00_dec_eval_minus_130 -130
#define P00_dec_eval_minus_131 -131
#define P00_dec_eval_minus_132 -132
#define P00_dec_eval_minus_133 -133
#define P00_dec_eval_minus_134 -134
#define P00_dec_eval_minus_135 -135
#define P00_dec_eval_minus_136 -136
#define P00_dec_eval_minus_137 -137
#define P00_dec_eval_minus_138 -138
#define P00_dec_eval_minus_139 -139
#define P00_dec_eval_minus_140 -140
#define P00_dec_eval_minus_141 -141
#define P00_dec_eval_minus_142 -142
#define P00_dec_eval_minus_143 -143
#define P00_dec_eval_minus_144 -144
#define P00_dec_eval_minus_145 -145
#define P00_dec_eval_minus_146 -146
#define P00_dec_eval_minus_147 -147
#define P00_dec_eval_minus_148 -148
#define P00_dec_eval_minus_149 -149
#define P00_dec_eval_minus_150 -150
#define P00_dec_eval_minus_151 -151
#define P00_dec_eval_minus_152 -152
#define P00_dec_eval_minus_153 -153
#define P00_dec_eval_minus_154 -154
#define P00_dec_eval_minus_155 -155
#define P00_dec_eval_minus_156 -156
#define P00_dec_eval_minus_157 -157
#define P00_dec_eval_minus_158 -158
#define P00_dec_eval_minus_159 -159
#define P00_DUPL_2(...) __VA_ARGS__, P00_DUPL_1(__VA_ARGS__)
#define P00_DUPL_3(...) __VA_ARGS__, P00_DUPL_2(__VA_ARGS__)
#define P00_DUPL_4(...) __VA_ARGS__, P00_DUPL_3(__VA_ARGS__)
#define P00_DUPL_5(...) __VA_ARGS__, P00_DUPL_4(__VA_ARGS__)
#define P00_DUPL_6(...) __VA_ARGS__, P00_DUPL_5(__VA_ARGS__)
#define P00_DUPL_7(...) __VA_ARGS__, P00_DUPL_6(__VA_ARGS__)
#define P00_DUPL_8(...) __VA_ARGS__, P00_DUPL_7(__VA_ARGS__)
#define P00_DUPL_9(...) __VA_ARGS__, P00_DUPL_8(__VA_ARGS__)
#define P00_DUPL_10(...) __VA_ARGS__, P00_DUPL_9(__VA_ARGS__)
#define P00_DUPL_11(...) __VA_ARGS__, P00_DUPL_10(__VA_ARGS__)
#define P00_DUPL_12(...) __VA_ARGS__, P00_DUPL_11(__VA_ARGS__)
#define P00_DUPL_13(...) __VA_ARGS__, P00_DUPL_12(__VA_ARGS__)
#define P00_DUPL_14(...) __VA_ARGS__, P00_DUPL_13(__VA_ARGS__)
#define P00_DUPL_15(...) __VA_ARGS__, P00_DUPL_14(__VA_ARGS__)
#define P00_DUPL_16(...) __VA_ARGS__, P00_DUPL_15(__VA_ARGS__)
#define P00_DUPL_17(...) __VA_ARGS__, P00_DUPL_16(__VA_ARGS__)
#define P00_DUPL_18(...) __VA_ARGS__, P00_DUPL_17(__VA_ARGS__)
#define P00_DUPL_19(...) __VA_ARGS__, P00_DUPL_18(__VA_ARGS__)
#define P00_DUPL_20(...) __VA_ARGS__, P00_DUPL_19(__VA_ARGS__)
#define P00_DUPL_21(...) __VA_ARGS__, P00_DUPL_20(__VA_ARGS__)
#define P00_DUPL_22(...) __VA_ARGS__, P00_DUPL_21(__VA_ARGS__)
#define P00_DUPL_23(...) __VA_ARGS__, P00_DUPL_22(__VA_ARGS__)
#define P00_DUPL_24(...) __VA_ARGS__, P00_DUPL_23(__VA_ARGS__)
#define P00_DUPL_25(...) __VA_ARGS__, P00_DUPL_24(__VA_ARGS__)
#define P00_DUPL_26(...) __VA_ARGS__, P00_DUPL_25(__VA_ARGS__)
#define P00_DUPL_27(...) __VA_ARGS__, P00_DUPL_26(__VA_ARGS__)
#define P00_DUPL_28(...) __VA_ARGS__, P00_DUPL_27(__VA_ARGS__)
#define P00_DUPL_29(...) __VA_ARGS__, P00_DUPL_28(__VA_ARGS__)
#define P00_DUPL_30(...) __VA_ARGS__, P00_DUPL_29(__VA_ARGS__)
#define P00_DUPL_31(...) __VA_ARGS__, P00_DUPL_30(__VA_ARGS__)
#define P00_DUPL_32(...) __VA_ARGS__, P00_DUPL_31(__VA_ARGS__)
#define P00_DUPL_33(...) __VA_ARGS__, P00_DUPL_32(__VA_ARGS__)
#define P00_DUPL_34(...) __VA_ARGS__, P00_DUPL_33(__VA_ARGS__)
#define P00_DUPL_35(...) __VA_ARGS__, P00_DUPL_34(__VA_ARGS__)
#define P00_DUPL_36(...) __VA_ARGS__, P00_DUPL_35(__VA_ARGS__)
#define P00_DUPL_37(...) __VA_ARGS__, P00_DUPL_36(__VA_ARGS__)
#define P00_DUPL_38(...) __VA_ARGS__, P00_DUPL_37(__VA_ARGS__)
#define P00_DUPL_39(...) __VA_ARGS__, P00_DUPL_38(__VA_ARGS__)
#define P00_DUPL_40(...) __VA_ARGS__, P00_DUPL_39(__VA_ARGS__)
#define P00_DUPL_41(...) __VA_ARGS__, P00_DUPL_40(__VA_ARGS__)
#define P00_DUPL_42(...) __VA_ARGS__, P00_DUPL_41(__VA_ARGS__)
#define P00_DUPL_43(...) __VA_ARGS__, P00_DUPL_42(__VA_ARGS__)
#define P00_DUPL_44(...) __VA_ARGS__, P00_DUPL_43(__VA_ARGS__)
#define P00_DUPL_45(...) __VA_ARGS__, P00_DUPL_44(__VA_ARGS__)
#define P00_DUPL_46(...) __VA_ARGS__, P00_DUPL_45(__VA_ARGS__)
#define P00_DUPL_47(...) __VA_ARGS__, P00_DUPL_46(__VA_ARGS__)
#define P00_DUPL_48(...) __VA_ARGS__, P00_DUPL_47(__VA_ARGS__)
#define P00_DUPL_49(...) __VA_ARGS__, P00_DUPL_48(__VA_ARGS__)
#define P00_DUPL_50(...) __VA_ARGS__, P00_DUPL_49(__VA_ARGS__)
#define P00_DUPL_51(...) __VA_ARGS__, P00_DUPL_50(__VA_ARGS__)
#define P00_DUPL_52(...) __VA_ARGS__, P00_DUPL_51(__VA_ARGS__)
#define P00_DUPL_53(...) __VA_ARGS__, P00_DUPL_52(__VA_ARGS__)
#define P00_DUPL_54(...) __VA_ARGS__, P00_DUPL_53(__VA_ARGS__)
#define P00_DUPL_55(...) __VA_ARGS__, P00_DUPL_54(__VA_ARGS__)
#define P00_DUPL_56(...) __VA_ARGS__, P00_DUPL_55(__VA_ARGS__)
#define P00_DUPL_57(...) __VA_ARGS__, P00_DUPL_56(__VA_ARGS__)
#define P00_DUPL_58(...) __VA_ARGS__, P00_DUPL_57(__VA_ARGS__)
#define P00_DUPL_59(...) __VA_ARGS__, P00_DUPL_58(__VA_ARGS__)
#define P00_DUPL_60(...) __VA_ARGS__, P00_DUPL_59(__VA_ARGS__)
#define P00_DUPL_61(...) __VA_ARGS__, P00_DUPL_60(__VA_ARGS__)
#define P00_DUPL_62(...) __VA_ARGS__, P00_DUPL_61(__VA_ARGS__)
#define P00_DUPL_63(...) __VA_ARGS__, P00_DUPL_62(__VA_ARGS__)
#define P00_DUPL_64(...) __VA_ARGS__, P00_DUPL_63(__VA_ARGS__)
#define P00_DUPL_65(...) __VA_ARGS__, P00_DUPL_64(__VA_ARGS__)
#define P00_DUPL_66(...) __VA_ARGS__, P00_DUPL_65(__VA_ARGS__)
#define P00_DUPL_67(...) __VA_ARGS__, P00_DUPL_66(__VA_ARGS__)
#define P00_DUPL_68(...) __VA_ARGS__, P00_DUPL_67(__VA_ARGS__)
#define P00_DUPL_69(...) __VA_ARGS__, P00_DUPL_68(__VA_ARGS__)
#define P00_DUPL_70(...) __VA_ARGS__, P00_DUPL_69(__VA_ARGS__)
#define P00_DUPL_71(...) __VA_ARGS__, P00_DUPL_70(__VA_ARGS__)
#define P00_DUPL_72(...) __VA_ARGS__, P00_DUPL_71(__VA_ARGS__)
#define P00_DUPL_73(...) __VA_ARGS__, P00_DUPL_72(__VA_ARGS__)
#define P00_DUPL_74(...) __VA_ARGS__, P00_DUPL_73(__VA_ARGS__)
#define P00_DUPL_75(...) __VA_ARGS__, P00_DUPL_74(__VA_ARGS__)
#define P00_DUPL_76(...) __VA_ARGS__, P00_DUPL_75(__VA_ARGS__)
#define P00_DUPL_77(...) __VA_ARGS__, P00_DUPL_76(__VA_ARGS__)
#define P00_DUPL_78(...) __VA_ARGS__, P00_DUPL_77(__VA_ARGS__)
#define P00_DUPL_79(...) __VA_ARGS__, P00_DUPL_78(__VA_ARGS__)
#define P00_DUPL_80(...) __VA_ARGS__, P00_DUPL_79(__VA_ARGS__)
#define P00_DUPL_81(...) __VA_ARGS__, P00_DUPL_80(__VA_ARGS__)
#define P00_DUPL_82(...) __VA_ARGS__, P00_DUPL_81(__VA_ARGS__)
#define P00_DUPL_83(...) __VA_ARGS__, P00_DUPL_82(__VA_ARGS__)
#define P00_DUPL_84(...) __VA_ARGS__, P00_DUPL_83(__VA_ARGS__)
#define P00_DUPL_85(...) __VA_ARGS__, P00_DUPL_84(__VA_ARGS__)
#define P00_DUPL_86(...) __VA_ARGS__, P00_DUPL_85(__VA_ARGS__)
#define P00_DUPL_87(...) __VA_ARGS__, P00_DUPL_86(__VA_ARGS__)
#define P00_DUPL_88(...) __VA_ARGS__, P00_DUPL_87(__VA_ARGS__)
#define P00_DUPL_89(...) __VA_ARGS__, P00_DUPL_88(__VA_ARGS__)
#define P00_DUPL_90(...) __VA_ARGS__, P00_DUPL_89(__VA_ARGS__)
#define P00_DUPL_91(...) __VA_ARGS__, P00_DUPL_90(__VA_ARGS__)
#define P00_DUPL_92(...) __VA_ARGS__, P00_DUPL_91(__VA_ARGS__)
#define P00_DUPL_93(...) __VA_ARGS__, P00_DUPL_92(__VA_ARGS__)
#define P00_DUPL_94(...) __VA_ARGS__, P00_DUPL_93(__VA_ARGS__)
#define P00_DUPL_95(...) __VA_ARGS__, P00_DUPL_94(__VA_ARGS__)
#define P00_DUPL_96(...) __VA_ARGS__, P00_DUPL_95(__VA_ARGS__)
#define P00_DUPL_97(...) __VA_ARGS__, P00_DUPL_96(__VA_ARGS__)
#define P00_DUPL_98(...) __VA_ARGS__, P00_DUPL_97(__VA_ARGS__)
#define P00_DUPL_99(...) __VA_ARGS__, P00_DUPL_98(__VA_ARGS__)
#define P00_DUPL_100(...) __VA_ARGS__, P00_DUPL_99(__VA_ARGS__)
#define P00_DUPL_101(...) __VA_ARGS__, P00_DUPL_100(__VA_ARGS__)
#define P00_DUPL_102(...) __VA_ARGS__, P00_DUPL_101(__VA_ARGS__)
#define P00_DUPL_103(...) __VA_ARGS__, P00_DUPL_102(__VA_ARGS__)
#define P00_DUPL_104(...) __VA_ARGS__, P00_DUPL_103(__VA_ARGS__)
#define P00_DUPL_105(...) __VA_ARGS__, P00_DUPL_104(__VA_ARGS__)
#define P00_DUPL_106(...) __VA_ARGS__, P00_DUPL_105(__VA_ARGS__)
#define P00_DUPL_107(...) __VA_ARGS__, P00_DUPL_106(__VA_ARGS__)
#define P00_DUPL_108(...) __VA_ARGS__, P00_DUPL_107(__VA_ARGS__)
#define P00_DUPL_109(...) __VA_ARGS__, P00_DUPL_108(__VA_ARGS__)
#define P00_DUPL_110(...) __VA_ARGS__, P00_DUPL_109(__VA_ARGS__)
#define P00_DUPL_111(...) __VA_ARGS__, P00_DUPL_110(__VA_ARGS__)
#define P00_DUPL_112(...) __VA_ARGS__, P00_DUPL_111(__VA_ARGS__)
#define P00_DUPL_113(...) __VA_ARGS__, P00_DUPL_112(__VA_ARGS__)
#define P00_DUPL_114(...) __VA_ARGS__, P00_DUPL_113(__VA_ARGS__)
#define P00_DUPL_115(...) __VA_ARGS__, P00_DUPL_114(__VA_ARGS__)
#define P00_DUPL_116(...) __VA_ARGS__, P00_DUPL_115(__VA_ARGS__)
#define P00_DUPL_117(...) __VA_ARGS__, P00_DUPL_116(__VA_ARGS__)
#define P00_DUPL_118(...) __VA_ARGS__, P00_DUPL_117(__VA_ARGS__)
#define P00_DUPL_119(...) __VA_ARGS__, P00_DUPL_118(__VA_ARGS__)
#define P00_DUPL_120(...) __VA_ARGS__, P00_DUPL_119(__VA_ARGS__)
#define P00_DUPL_121(...) __VA_ARGS__, P00_DUPL_120(__VA_ARGS__)
#define P00_DUPL_122(...) __VA_ARGS__, P00_DUPL_121(__VA_ARGS__)
#define P00_DUPL_123(...) __VA_ARGS__, P00_DUPL_122(__VA_ARGS__)
#define P00_DUPL_124(...) __VA_ARGS__, P00_DUPL_123(__VA_ARGS__)
#define P00_DUPL_125(...) __VA_ARGS__, P00_DUPL_124(__VA_ARGS__)
#define P00_DUPL_126(...) __VA_ARGS__, P00_DUPL_125(__VA_ARGS__)
#define P00_DUPL_127(...) __VA_ARGS__, P00_DUPL_126(__VA_ARGS__)
#define P00_DUPL_128(...) __VA_ARGS__, P00_DUPL_127(__VA_ARGS__)
#define P00_DUPL_129(...) __VA_ARGS__, P00_DUPL_128(__VA_ARGS__)
#define P00_DUPL_130(...) __VA_ARGS__, P00_DUPL_129(__VA_ARGS__)
#define P00_DUPL_131(...) __VA_ARGS__, P00_DUPL_130(__VA_ARGS__)
#define P00_DUPL_132(...) __VA_ARGS__, P00_DUPL_131(__VA_ARGS__)
#define P00_DUPL_133(...) __VA_ARGS__, P00_DUPL_132(__VA_ARGS__)
#define P00_DUPL_134(...) __VA_ARGS__, P00_DUPL_133(__VA_ARGS__)
#define P00_DUPL_135(...) __VA_ARGS__, P00_DUPL_134(__VA_ARGS__)
#define P00_DUPL_136(...) __VA_ARGS__, P00_DUPL_135(__VA_ARGS__)
#define P00_DUPL_137(...) __VA_ARGS__, P00_DUPL_136(__VA_ARGS__)
#define P00_DUPL_138(...) __VA_ARGS__, P00_DUPL_137(__VA_ARGS__)
#define P00_DUPL_139(...) __VA_ARGS__, P00_DUPL_138(__VA_ARGS__)
#define P00_DUPL_140(...) __VA_ARGS__, P00_DUPL_139(__VA_ARGS__)
#define P00_DUPL_141(...) __VA_ARGS__, P00_DUPL_140(__VA_ARGS__)
#define P00_DUPL_142(...) __VA_ARGS__, P00_DUPL_141(__VA_ARGS__)
#define P00_DUPL_143(...) __VA_ARGS__, P00_DUPL_142(__VA_ARGS__)
#define P00_DUPL_144(...) __VA_ARGS__, P00_DUPL_143(__VA_ARGS__)
#define P00_DUPL_145(...) __VA_ARGS__, P00_DUPL_144(__VA_ARGS__)
#define P00_DUPL_146(...) __VA_ARGS__, P00_DUPL_145(__VA_ARGS__)
#define P00_DUPL_147(...) __VA_ARGS__, P00_DUPL_146(__VA_ARGS__)
#define P00_DUPL_148(...) __VA_ARGS__, P00_DUPL_147(__VA_ARGS__)
#define P00_DUPL_149(...) __VA_ARGS__, P00_DUPL_148(__VA_ARGS__)
#define P00_DUPL_150(...) __VA_ARGS__, P00_DUPL_149(__VA_ARGS__)
#define P00_DUPL_151(...) __VA_ARGS__, P00_DUPL_150(__VA_ARGS__)
#define P00_DUPL_152(...) __VA_ARGS__, P00_DUPL_151(__VA_ARGS__)
#define P00_DUPL_153(...) __VA_ARGS__, P00_DUPL_152(__VA_ARGS__)
#define P00_DUPL_154(...) __VA_ARGS__, P00_DUPL_153(__VA_ARGS__)
#define P00_DUPL_155(...) __VA_ARGS__, P00_DUPL_154(__VA_ARGS__)
#define P00_DUPL_156(...) __VA_ARGS__, P00_DUPL_155(__VA_ARGS__)
#define P00_DUPL_157(...) __VA_ARGS__, P00_DUPL_156(__VA_ARGS__)
#define P00_DUPL_158(...) __VA_ARGS__, P00_DUPL_157(__VA_ARGS__)
#define P00_DUPL_159(...) __VA_ARGS__, P00_DUPL_158(__VA_ARGS__)
#define P00_REP_2(...) P00_REP_1(__VA_ARGS__)__VA_ARGS__
#define P00_REP_3(...) P00_REP_2(__VA_ARGS__)__VA_ARGS__
#define P00_REP_4(...) P00_REP_3(__VA_ARGS__)__VA_ARGS__
#define P00_REP_5(...) P00_REP_4(__VA_ARGS__)__VA_ARGS__
#define P00_REP_6(...) P00_REP_5(__VA_ARGS__)__VA_ARGS__
#define P00_REP_7(...) P00_REP_6(__VA_ARGS__)__VA_ARGS__
#define P00_REP_8(...) P00_REP_7(__VA_ARGS__)__VA_ARGS__
#define P00_REP_9(...) P00_REP_8(__VA_ARGS__)__VA_ARGS__
#define P00_REP_10(...) P00_REP_9(__VA_ARGS__)__VA_ARGS__
#define P00_REP_11(...) P00_REP_10(__VA_ARGS__)__VA_ARGS__
#define P00_REP_12(...) P00_REP_11(__VA_ARGS__)__VA_ARGS__
#define P00_REP_13(...) P00_REP_12(__VA_ARGS__)__VA_ARGS__
#define P00_REP_14(...) P00_REP_13(__VA_ARGS__)__VA_ARGS__
#define P00_REP_15(...) P00_REP_14(__VA_ARGS__)__VA_ARGS__
#define P00_REP_16(...) P00_REP_15(__VA_ARGS__)__VA_ARGS__
#define P00_REP_17(...) P00_REP_16(__VA_ARGS__)__VA_ARGS__
#define P00_REP_18(...) P00_REP_17(__VA_ARGS__)__VA_ARGS__
#define P00_REP_19(...) P00_REP_18(__VA_ARGS__)__VA_ARGS__
#define P00_REP_20(...) P00_REP_19(__VA_ARGS__)__VA_ARGS__
#define P00_REP_21(...) P00_REP_20(__VA_ARGS__)__VA_ARGS__
#define P00_REP_22(...) P00_REP_21(__VA_ARGS__)__VA_ARGS__
#define P00_REP_23(...) P00_REP_22(__VA_ARGS__)__VA_ARGS__
#define P00_REP_24(...) P00_REP_23(__VA_ARGS__)__VA_ARGS__
#define P00_REP_25(...) P00_REP_24(__VA_ARGS__)__VA_ARGS__
#define P00_REP_26(...) P00_REP_25(__VA_ARGS__)__VA_ARGS__
#define P00_REP_27(...) P00_REP_26(__VA_ARGS__)__VA_ARGS__
#define P00_REP_28(...) P00_REP_27(__VA_ARGS__)__VA_ARGS__
#define P00_REP_29(...) P00_REP_28(__VA_ARGS__)__VA_ARGS__
#define P00_REP_30(...) P00_REP_29(__VA_ARGS__)__VA_ARGS__
#define P00_REP_31(...) P00_REP_30(__VA_ARGS__)__VA_ARGS__
#define P00_REP_32(...) P00_REP_31(__VA_ARGS__)__VA_ARGS__
#define P00_REP_33(...) P00_REP_32(__VA_ARGS__)__VA_ARGS__
#define P00_REP_34(...) P00_REP_33(__VA_ARGS__)__VA_ARGS__
#define P00_REP_35(...) P00_REP_34(__VA_ARGS__)__VA_ARGS__
#define P00_REP_36(...) P00_REP_35(__VA_ARGS__)__VA_ARGS__
#define P00_REP_37(...) P00_REP_36(__VA_ARGS__)__VA_ARGS__
#define P00_REP_38(...) P00_REP_37(__VA_ARGS__)__VA_ARGS__
#define P00_REP_39(...) P00_REP_38(__VA_ARGS__)__VA_ARGS__
#define P00_REP_40(...) P00_REP_39(__VA_ARGS__)__VA_ARGS__
#define P00_REP_41(...) P00_REP_40(__VA_ARGS__)__VA_ARGS__
#define P00_REP_42(...) P00_REP_41(__VA_ARGS__)__VA_ARGS__
#define P00_REP_43(...) P00_REP_42(__VA_ARGS__)__VA_ARGS__
#define P00_REP_44(...) P00_REP_43(__VA_ARGS__)__VA_ARGS__
#define P00_REP_45(...) P00_REP_44(__VA_ARGS__)__VA_ARGS__
#define P00_REP_46(...) P00_REP_45(__VA_ARGS__)__VA_ARGS__
#define P00_REP_47(...) P00_REP_46(__VA_ARGS__)__VA_ARGS__
#define P00_REP_48(...) P00_REP_47(__VA_ARGS__)__VA_ARGS__
#define P00_REP_49(...) P00_REP_48(__VA_ARGS__)__VA_ARGS__
#define P00_REP_50(...) P00_REP_49(__VA_ARGS__)__VA_ARGS__
#define P00_REP_51(...) P00_REP_50(__VA_ARGS__)__VA_ARGS__
#define P00_REP_52(...) P00_REP_51(__VA_ARGS__)__VA_ARGS__
#define P00_REP_53(...) P00_REP_52(__VA_ARGS__)__VA_ARGS__
#define P00_REP_54(...) P00_REP_53(__VA_ARGS__)__VA_ARGS__
#define P00_REP_55(...) P00_REP_54(__VA_ARGS__)__VA_ARGS__
#define P00_REP_56(...) P00_REP_55(__VA_ARGS__)__VA_ARGS__
#define P00_REP_57(...) P00_REP_56(__VA_ARGS__)__VA_ARGS__
#define P00_REP_58(...) P00_REP_57(__VA_ARGS__)__VA_ARGS__
#define P00_REP_59(...) P00_REP_58(__VA_ARGS__)__VA_ARGS__
#define P00_REP_60(...) P00_REP_59(__VA_ARGS__)__VA_ARGS__
#define P00_REP_61(...) P00_REP_60(__VA_ARGS__)__VA_ARGS__
#define P00_REP_62(...) P00_REP_61(__VA_ARGS__)__VA_ARGS__
#define P00_REP_63(...) P00_REP_62(__VA_ARGS__)__VA_ARGS__
#define P00_REP_64(...) P00_REP_63(__VA_ARGS__)__VA_ARGS__
#define P00_REP_65(...) P00_REP_64(__VA_ARGS__)__VA_ARGS__
#define P00_REP_66(...) P00_REP_65(__VA_ARGS__)__VA_ARGS__
#define P00_REP_67(...) P00_REP_66(__VA_ARGS__)__VA_ARGS__
#define P00_REP_68(...) P00_REP_67(__VA_ARGS__)__VA_ARGS__
#define P00_REP_69(...) P00_REP_68(__VA_ARGS__)__VA_ARGS__
#define P00_REP_70(...) P00_REP_69(__VA_ARGS__)__VA_ARGS__
#define P00_REP_71(...) P00_REP_70(__VA_ARGS__)__VA_ARGS__
#define P00_REP_72(...) P00_REP_71(__VA_ARGS__)__VA_ARGS__
#define P00_REP_73(...) P00_REP_72(__VA_ARGS__)__VA_ARGS__
#define P00_REP_74(...) P00_REP_73(__VA_ARGS__)__VA_ARGS__
#define P00_REP_75(...) P00_REP_74(__VA_ARGS__)__VA_ARGS__
#define P00_REP_76(...) P00_REP_75(__VA_ARGS__)__VA_ARGS__
#define P00_REP_77(...) P00_REP_76(__VA_ARGS__)__VA_ARGS__
#define P00_REP_78(...) P00_REP_77(__VA_ARGS__)__VA_ARGS__
#define P00_REP_79(...) P00_REP_78(__VA_ARGS__)__VA_ARGS__
#define P00_REP_80(...) P00_REP_79(__VA_ARGS__)__VA_ARGS__
#define P00_REP_81(...) P00_REP_80(__VA_ARGS__)__VA_ARGS__
#define P00_REP_82(...) P00_REP_81(__VA_ARGS__)__VA_ARGS__
#define P00_REP_83(...) P00_REP_82(__VA_ARGS__)__VA_ARGS__
#define P00_REP_84(...) P00_REP_83(__VA_ARGS__)__VA_ARGS__
#define P00_REP_85(...) P00_REP_84(__VA_ARGS__)__VA_ARGS__
#define P00_REP_86(...) P00_REP_85(__VA_ARGS__)__VA_ARGS__
#define P00_REP_87(...) P00_REP_86(__VA_ARGS__)__VA_ARGS__
#define P00_REP_88(...) P00_REP_87(__VA_ARGS__)__VA_ARGS__
#define P00_REP_89(...) P00_REP_88(__VA_ARGS__)__VA_ARGS__
#define P00_REP_90(...) P00_REP_89(__VA_ARGS__)__VA_ARGS__
#define P00_REP_91(...) P00_REP_90(__VA_ARGS__)__VA_ARGS__
#define P00_REP_92(...) P00_REP_91(__VA_ARGS__)__VA_ARGS__
#define P00_REP_93(...) P00_REP_92(__VA_ARGS__)__VA_ARGS__
#define P00_REP_94(...) P00_REP_93(__VA_ARGS__)__VA_ARGS__
#define P00_REP_95(...) P00_REP_94(__VA_ARGS__)__VA_ARGS__
#define P00_REP_96(...) P00_REP_95(__VA_ARGS__)__VA_ARGS__
#define P00_REP_97(...) P00_REP_96(__VA_ARGS__)__VA_ARGS__
#define P00_REP_98(...) P00_REP_97(__VA_ARGS__)__VA_ARGS__
#define P00_REP_99(...) P00_REP_98(__VA_ARGS__)__VA_ARGS__
#define P00_REP_100(...) P00_REP_99(__VA_ARGS__)__VA_ARGS__
#define P00_REP_101(...) P00_REP_100(__VA_ARGS__)__VA_ARGS__
#define P00_REP_102(...) P00_REP_101(__VA_ARGS__)__VA_ARGS__
#define P00_REP_103(...) P00_REP_102(__VA_ARGS__)__VA_ARGS__
#define P00_REP_104(...) P00_REP_103(__VA_ARGS__)__VA_ARGS__
#define P00_REP_105(...) P00_REP_104(__VA_ARGS__)__VA_ARGS__
#define P00_REP_106(...) P00_REP_105(__VA_ARGS__)__VA_ARGS__
#define P00_REP_107(...) P00_REP_106(__VA_ARGS__)__VA_ARGS__
#define P00_REP_108(...) P00_REP_107(__VA_ARGS__)__VA_ARGS__
#define P00_REP_109(...) P00_REP_108(__VA_ARGS__)__VA_ARGS__
#define P00_REP_110(...) P00_REP_109(__VA_ARGS__)__VA_ARGS__
#define P00_REP_111(...) P00_REP_110(__VA_ARGS__)__VA_ARGS__
#define P00_REP_112(...) P00_REP_111(__VA_ARGS__)__VA_ARGS__
#define P00_REP_113(...) P00_REP_112(__VA_ARGS__)__VA_ARGS__
#define P00_REP_114(...) P00_REP_113(__VA_ARGS__)__VA_ARGS__
#define P00_REP_115(...) P00_REP_114(__VA_ARGS__)__VA_ARGS__
#define P00_REP_116(...) P00_REP_115(__VA_ARGS__)__VA_ARGS__
#define P00_REP_117(...) P00_REP_116(__VA_ARGS__)__VA_ARGS__
#define P00_REP_118(...) P00_REP_117(__VA_ARGS__)__VA_ARGS__
#define P00_REP_119(...) P00_REP_118(__VA_ARGS__)__VA_ARGS__
#define P00_REP_120(...) P00_REP_119(__VA_ARGS__)__VA_ARGS__
#define P00_REP_121(...) P00_REP_120(__VA_ARGS__)__VA_ARGS__
#define P00_REP_122(...) P00_REP_121(__VA_ARGS__)__VA_ARGS__
#define P00_REP_123(...) P00_REP_122(__VA_ARGS__)__VA_ARGS__
#define P00_REP_124(...) P00_REP_123(__VA_ARGS__)__VA_ARGS__
#define P00_REP_125(...) P00_REP_124(__VA_ARGS__)__VA_ARGS__
#define P00_REP_126(...) P00_REP_125(__VA_ARGS__)__VA_ARGS__
#define P00_REP_127(...) P00_REP_126(__VA_ARGS__)__VA_ARGS__
#define P00_REP_128(...) P00_REP_127(__VA_ARGS__)__VA_ARGS__
#define P00_REP_129(...) P00_REP_128(__VA_ARGS__)__VA_ARGS__
#define P00_REP_130(...) P00_REP_129(__VA_ARGS__)__VA_ARGS__
#define P00_REP_131(...) P00_REP_130(__VA_ARGS__)__VA_ARGS__
#define P00_REP_132(...) P00_REP_131(__VA_ARGS__)__VA_ARGS__
#define P00_REP_133(...) P00_REP_132(__VA_ARGS__)__VA_ARGS__
#define P00_REP_134(...) P00_REP_133(__VA_ARGS__)__VA_ARGS__
#define P00_REP_135(...) P00_REP_134(__VA_ARGS__)__VA_ARGS__
#define P00_REP_136(...) P00_REP_135(__VA_ARGS__)__VA_ARGS__
#define P00_REP_137(...) P00_REP_136(__VA_ARGS__)__VA_ARGS__
#define P00_REP_138(...) P00_REP_137(__VA_ARGS__)__VA_ARGS__
#define P00_REP_139(...) P00_REP_138(__VA_ARGS__)__VA_ARGS__
#define P00_REP_140(...) P00_REP_139(__VA_ARGS__)__VA_ARGS__
#define P00_REP_141(...) P00_REP_140(__VA_ARGS__)__VA_ARGS__
#define P00_REP_142(...) P00_REP_141(__VA_ARGS__)__VA_ARGS__
#define P00_REP_143(...) P00_REP_142(__VA_ARGS__)__VA_ARGS__
#define P00_REP_144(...) P00_REP_143(__VA_ARGS__)__VA_ARGS__
#define P00_REP_145(...) P00_REP_144(__VA_ARGS__)__VA_ARGS__
#define P00_REP_146(...) P00_REP_145(__VA_ARGS__)__VA_ARGS__
#define P00_REP_147(...) P00_REP_146(__VA_ARGS__)__VA_ARGS__
#define P00_REP_148(...) P00_REP_147(__VA_ARGS__)__VA_ARGS__
#define P00_REP_149(...) P00_REP_148(__VA_ARGS__)__VA_ARGS__
#define P00_REP_150(...) P00_REP_149(__VA_ARGS__)__VA_ARGS__
#define P00_REP_151(...) P00_REP_150(__VA_ARGS__)__VA_ARGS__
#define P00_REP_152(...) P00_REP_151(__VA_ARGS__)__VA_ARGS__
#define P00_REP_153(...) P00_REP_152(__VA_ARGS__)__VA_ARGS__
#define P00_REP_154(...) P00_REP_153(__VA_ARGS__)__VA_ARGS__
#define P00_REP_155(...) P00_REP_154(__VA_ARGS__)__VA_ARGS__
#define P00_REP_156(...) P00_REP_155(__VA_ARGS__)__VA_ARGS__
#define P00_REP_157(...) P00_REP_156(__VA_ARGS__)__VA_ARGS__
#define P00_REP_158(...) P00_REP_157(__VA_ARGS__)__VA_ARGS__
#define P00_REP_159(...) P00_REP_158(__VA_ARGS__)__VA_ARGS__
#define P00_BRACKET_2(X, ...) [X]P00_BRACKET_1(__VA_ARGS__)
#define P00_BRACKET_3(X, ...) [X]P00_BRACKET_2(__VA_ARGS__)
#define P00_BRACKET_4(X, ...) [X]P00_BRACKET_3(__VA_ARGS__)
#define P00_BRACKET_5(X, ...) [X]P00_BRACKET_4(__VA_ARGS__)
#define P00_BRACKET_6(X, ...) [X]P00_BRACKET_5(__VA_ARGS__)
#define P00_BRACKET_7(X, ...) [X]P00_BRACKET_6(__VA_ARGS__)
#define P00_BRACKET_8(X, ...) [X]P00_BRACKET_7(__VA_ARGS__)
#define P00_BRACKET_9(X, ...) [X]P00_BRACKET_8(__VA_ARGS__)
#define P00_BRACKET_10(X, ...) [X]P00_BRACKET_9(__VA_ARGS__)
#define P00_BRACKET_11(X, ...) [X]P00_BRACKET_10(__VA_ARGS__)
#define P00_BRACKET_12(X, ...) [X]P00_BRACKET_11(__VA_ARGS__)
#define P00_BRACKET_13(X, ...) [X]P00_BRACKET_12(__VA_ARGS__)
#define P00_BRACKET_14(X, ...) [X]P00_BRACKET_13(__VA_ARGS__)
#define P00_BRACKET_15(X, ...) [X]P00_BRACKET_14(__VA_ARGS__)
#define P00_BRACKET_16(X, ...) [X]P00_BRACKET_15(__VA_ARGS__)
#define P00_BRACKET_17(X, ...) [X]P00_BRACKET_16(__VA_ARGS__)
#define P00_BRACKET_18(X, ...) [X]P00_BRACKET_17(__VA_ARGS__)
#define P00_BRACKET_19(X, ...) [X]P00_BRACKET_18(__VA_ARGS__)
#define P00_BRACKET_20(X, ...) [X]P00_BRACKET_19(__VA_ARGS__)
#define P00_BRACKET_21(X, ...) [X]P00_BRACKET_20(__VA_ARGS__)
#define P00_BRACKET_22(X, ...) [X]P00_BRACKET_21(__VA_ARGS__)
#define P00_BRACKET_23(X, ...) [X]P00_BRACKET_22(__VA_ARGS__)
#define P00_BRACKET_24(X, ...) [X]P00_BRACKET_23(__VA_ARGS__)
#define P00_BRACKET_25(X, ...) [X]P00_BRACKET_24(__VA_ARGS__)
#define P00_BRACKET_26(X, ...) [X]P00_BRACKET_25(__VA_ARGS__)
#define P00_BRACKET_27(X, ...) [X]P00_BRACKET_26(__VA_ARGS__)
#define P00_BRACKET_28(X, ...) [X]P00_BRACKET_27(__VA_ARGS__)
#define P00_BRACKET_29(X, ...) [X]P00_BRACKET_28(__VA_ARGS__)
#define P00_BRACKET_30(X, ...) [X]P00_BRACKET_29(__VA_ARGS__)
#define P00_BRACKET_31(X, ...) [X]P00_BRACKET_30(__VA_ARGS__)
#define P00_BRACKET_32(X, ...) [X]P00_BRACKET_31(__VA_ARGS__)
#define P00_BRACKET_33(X, ...) [X]P00_BRACKET_32(__VA_ARGS__)
#define P00_BRACKET_34(X, ...) [X]P00_BRACKET_33(__VA_ARGS__)
#define P00_BRACKET_35(X, ...) [X]P00_BRACKET_34(__VA_ARGS__)
#define P00_BRACKET_36(X, ...) [X]P00_BRACKET_35(__VA_ARGS__)
#define P00_BRACKET_37(X, ...) [X]P00_BRACKET_36(__VA_ARGS__)
#define P00_BRACKET_38(X, ...) [X]P00_BRACKET_37(__VA_ARGS__)
#define P00_BRACKET_39(X, ...) [X]P00_BRACKET_38(__VA_ARGS__)
#define P00_BRACKET_40(X, ...) [X]P00_BRACKET_39(__VA_ARGS__)
#define P00_BRACKET_41(X, ...) [X]P00_BRACKET_40(__VA_ARGS__)
#define P00_BRACKET_42(X, ...) [X]P00_BRACKET_41(__VA_ARGS__)
#define P00_BRACKET_43(X, ...) [X]P00_BRACKET_42(__VA_ARGS__)
#define P00_BRACKET_44(X, ...) [X]P00_BRACKET_43(__VA_ARGS__)
#define P00_BRACKET_45(X, ...) [X]P00_BRACKET_44(__VA_ARGS__)
#define P00_BRACKET_46(X, ...) [X]P00_BRACKET_45(__VA_ARGS__)
#define P00_BRACKET_47(X, ...) [X]P00_BRACKET_46(__VA_ARGS__)
#define P00_BRACKET_48(X, ...) [X]P00_BRACKET_47(__VA_ARGS__)
#define P00_BRACKET_49(X, ...) [X]P00_BRACKET_48(__VA_ARGS__)
#define P00_BRACKET_50(X, ...) [X]P00_BRACKET_49(__VA_ARGS__)
#define P00_BRACKET_51(X, ...) [X]P00_BRACKET_50(__VA_ARGS__)
#define P00_BRACKET_52(X, ...) [X]P00_BRACKET_51(__VA_ARGS__)
#define P00_BRACKET_53(X, ...) [X]P00_BRACKET_52(__VA_ARGS__)
#define P00_BRACKET_54(X, ...) [X]P00_BRACKET_53(__VA_ARGS__)
#define P00_BRACKET_55(X, ...) [X]P00_BRACKET_54(__VA_ARGS__)
#define P00_BRACKET_56(X, ...) [X]P00_BRACKET_55(__VA_ARGS__)
#define P00_BRACKET_57(X, ...) [X]P00_BRACKET_56(__VA_ARGS__)
#define P00_BRACKET_58(X, ...) [X]P00_BRACKET_57(__VA_ARGS__)
#define P00_BRACKET_59(X, ...) [X]P00_BRACKET_58(__VA_ARGS__)
#define P00_BRACKET_60(X, ...) [X]P00_BRACKET_59(__VA_ARGS__)
#define P00_BRACKET_61(X, ...) [X]P00_BRACKET_60(__VA_ARGS__)
#define P00_BRACKET_62(X, ...) [X]P00_BRACKET_61(__VA_ARGS__)
#define P00_BRACKET_63(X, ...) [X]P00_BRACKET_62(__VA_ARGS__)
#define P00_BRACKET_64(X, ...) [X]P00_BRACKET_63(__VA_ARGS__)
#define P00_BRACKET_65(X, ...) [X]P00_BRACKET_64(__VA_ARGS__)
#define P00_BRACKET_66(X, ...) [X]P00_BRACKET_65(__VA_ARGS__)
#define P00_BRACKET_67(X, ...) [X]P00_BRACKET_66(__VA_ARGS__)
#define P00_BRACKET_68(X, ...) [X]P00_BRACKET_67(__VA_ARGS__)
#define P00_BRACKET_69(X, ...) [X]P00_BRACKET_68(__VA_ARGS__)
#define P00_BRACKET_70(X, ...) [X]P00_BRACKET_69(__VA_ARGS__)
#define P00_BRACKET_71(X, ...) [X]P00_BRACKET_70(__VA_ARGS__)
#define P00_BRACKET_72(X, ...) [X]P00_BRACKET_71(__VA_ARGS__)
#define P00_BRACKET_73(X, ...) [X]P00_BRACKET_72(__VA_ARGS__)
#define P00_BRACKET_74(X, ...) [X]P00_BRACKET_73(__VA_ARGS__)
#define P00_BRACKET_75(X, ...) [X]P00_BRACKET_74(__VA_ARGS__)
#define P00_BRACKET_76(X, ...) [X]P00_BRACKET_75(__VA_ARGS__)
#define P00_BRACKET_77(X, ...) [X]P00_BRACKET_76(__VA_ARGS__)
#define P00_BRACKET_78(X, ...) [X]P00_BRACKET_77(__VA_ARGS__)
#define P00_BRACKET_79(X, ...) [X]P00_BRACKET_78(__VA_ARGS__)
#define P00_BRACKET_80(X, ...) [X]P00_BRACKET_79(__VA_ARGS__)
#define P00_BRACKET_81(X, ...) [X]P00_BRACKET_80(__VA_ARGS__)
#define P00_BRACKET_82(X, ...) [X]P00_BRACKET_81(__VA_ARGS__)
#define P00_BRACKET_83(X, ...) [X]P00_BRACKET_82(__VA_ARGS__)
#define P00_BRACKET_84(X, ...) [X]P00_BRACKET_83(__VA_ARGS__)
#define P00_BRACKET_85(X, ...) [X]P00_BRACKET_84(__VA_ARGS__)
#define P00_BRACKET_86(X, ...) [X]P00_BRACKET_85(__VA_ARGS__)
#define P00_BRACKET_87(X, ...) [X]P00_BRACKET_86(__VA_ARGS__)
#define P00_BRACKET_88(X, ...) [X]P00_BRACKET_87(__VA_ARGS__)
#define P00_BRACKET_89(X, ...) [X]P00_BRACKET_88(__VA_ARGS__)
#define P00_BRACKET_90(X, ...) [X]P00_BRACKET_89(__VA_ARGS__)
#define P00_BRACKET_91(X, ...) [X]P00_BRACKET_90(__VA_ARGS__)
#define P00_BRACKET_92(X, ...) [X]P00_BRACKET_91(__VA_ARGS__)
#define P00_BRACKET_93(X, ...) [X]P00_BRACKET_92(__VA_ARGS__)
#define P00_BRACKET_94(X, ...) [X]P00_BRACKET_93(__VA_ARGS__)
#define P00_BRACKET_95(X, ...) [X]P00_BRACKET_94(__VA_ARGS__)
#define P00_BRACKET_96(X, ...) [X]P00_BRACKET_95(__VA_ARGS__)
#define P00_BRACKET_97(X, ...) [X]P00_BRACKET_96(__VA_ARGS__)
#define P00_BRACKET_98(X, ...) [X]P00_BRACKET_97(__VA_ARGS__)
#define P00_BRACKET_99(X, ...) [X]P00_BRACKET_98(__VA_ARGS__)
#define P00_BRACKET_100(X, ...) [X]P00_BRACKET_99(__VA_ARGS__)
#define P00_BRACKET_101(X, ...) [X]P00_BRACKET_100(__VA_ARGS__)
#define P00_BRACKET_102(X, ...) [X]P00_BRACKET_101(__VA_ARGS__)
#define P00_BRACKET_103(X, ...) [X]P00_BRACKET_102(__VA_ARGS__)
#define P00_BRACKET_104(X, ...) [X]P00_BRACKET_103(__VA_ARGS__)
#define P00_BRACKET_105(X, ...) [X]P00_BRACKET_104(__VA_ARGS__)
#define P00_BRACKET_106(X, ...) [X]P00_BRACKET_105(__VA_ARGS__)
#define P00_BRACKET_107(X, ...) [X]P00_BRACKET_106(__VA_ARGS__)
#define P00_BRACKET_108(X, ...) [X]P00_BRACKET_107(__VA_ARGS__)
#define P00_BRACKET_109(X, ...) [X]P00_BRACKET_108(__VA_ARGS__)
#define P00_BRACKET_110(X, ...) [X]P00_BRACKET_109(__VA_ARGS__)
#define P00_BRACKET_111(X, ...) [X]P00_BRACKET_110(__VA_ARGS__)
#define P00_BRACKET_112(X, ...) [X]P00_BRACKET_111(__VA_ARGS__)
#define P00_BRACKET_113(X, ...) [X]P00_BRACKET_112(__VA_ARGS__)
#define P00_BRACKET_114(X, ...) [X]P00_BRACKET_113(__VA_ARGS__)
#define P00_BRACKET_115(X, ...) [X]P00_BRACKET_114(__VA_ARGS__)
#define P00_BRACKET_116(X, ...) [X]P00_BRACKET_115(__VA_ARGS__)
#define P00_BRACKET_117(X, ...) [X]P00_BRACKET_116(__VA_ARGS__)
#define P00_BRACKET_118(X, ...) [X]P00_BRACKET_117(__VA_ARGS__)
#define P00_BRACKET_119(X, ...) [X]P00_BRACKET_118(__VA_ARGS__)
#define P00_BRACKET_120(X, ...) [X]P00_BRACKET_119(__VA_ARGS__)
#define P00_BRACKET_121(X, ...) [X]P00_BRACKET_120(__VA_ARGS__)
#define P00_BRACKET_122(X, ...) [X]P00_BRACKET_121(__VA_ARGS__)
#define P00_BRACKET_123(X, ...) [X]P00_BRACKET_122(__VA_ARGS__)
#define P00_BRACKET_124(X, ...) [X]P00_BRACKET_123(__VA_ARGS__)
#define P00_BRACKET_125(X, ...) [X]P00_BRACKET_124(__VA_ARGS__)
#define P00_BRACKET_126(X, ...) [X]P00_BRACKET_125(__VA_ARGS__)
#define P00_BRACKET_127(X, ...) [X]P00_BRACKET_126(__VA_ARGS__)
#define P00_BRACKET_128(X, ...) [X]P00_BRACKET_127(__VA_ARGS__)
#define P00_BRACKET_129(X, ...) [X]P00_BRACKET_128(__VA_ARGS__)
#define P00_BRACKET_130(X, ...) [X]P00_BRACKET_129(__VA_ARGS__)
#define P00_BRACKET_131(X, ...) [X]P00_BRACKET_130(__VA_ARGS__)
#define P00_BRACKET_132(X, ...) [X]P00_BRACKET_131(__VA_ARGS__)
#define P00_BRACKET_133(X, ...) [X]P00_BRACKET_132(__VA_ARGS__)
#define P00_BRACKET_134(X, ...) [X]P00_BRACKET_133(__VA_ARGS__)
#define P00_BRACKET_135(X, ...) [X]P00_BRACKET_134(__VA_ARGS__)
#define P00_BRACKET_136(X, ...) [X]P00_BRACKET_135(__VA_ARGS__)
#define P00_BRACKET_137(X, ...) [X]P00_BRACKET_136(__VA_ARGS__)
#define P00_BRACKET_138(X, ...) [X]P00_BRACKET_137(__VA_ARGS__)
#define P00_BRACKET_139(X, ...) [X]P00_BRACKET_138(__VA_ARGS__)
#define P00_BRACKET_140(X, ...) [X]P00_BRACKET_139(__VA_ARGS__)
#define P00_BRACKET_141(X, ...) [X]P00_BRACKET_140(__VA_ARGS__)
#define P00_BRACKET_142(X, ...) [X]P00_BRACKET_141(__VA_ARGS__)
#define P00_BRACKET_143(X, ...) [X]P00_BRACKET_142(__VA_ARGS__)
#define P00_BRACKET_144(X, ...) [X]P00_BRACKET_143(__VA_ARGS__)
#define P00_BRACKET_145(X, ...) [X]P00_BRACKET_144(__VA_ARGS__)
#define P00_BRACKET_146(X, ...) [X]P00_BRACKET_145(__VA_ARGS__)
#define P00_BRACKET_147(X, ...) [X]P00_BRACKET_146(__VA_ARGS__)
#define P00_BRACKET_148(X, ...) [X]P00_BRACKET_147(__VA_ARGS__)
#define P00_BRACKET_149(X, ...) [X]P00_BRACKET_148(__VA_ARGS__)
#define P00_BRACKET_150(X, ...) [X]P00_BRACKET_149(__VA_ARGS__)
#define P00_BRACKET_151(X, ...) [X]P00_BRACKET_150(__VA_ARGS__)
#define P00_BRACKET_152(X, ...) [X]P00_BRACKET_151(__VA_ARGS__)
#define P00_BRACKET_153(X, ...) [X]P00_BRACKET_152(__VA_ARGS__)
#define P00_BRACKET_154(X, ...) [X]P00_BRACKET_153(__VA_ARGS__)
#define P00_BRACKET_155(X, ...) [X]P00_BRACKET_154(__VA_ARGS__)
#define P00_BRACKET_156(X, ...) [X]P00_BRACKET_155(__VA_ARGS__)
#define P00_BRACKET_157(X, ...) [X]P00_BRACKET_156(__VA_ARGS__)
#define P00_BRACKET_158(X, ...) [X]P00_BRACKET_157(__VA_ARGS__)
#define P00_BRACKET_159(X, ...) [X]P00_BRACKET_158(__VA_ARGS__)
#define P00_BRACE_2(X, ...) {X}, P00_BRACE_1(__VA_ARGS__)
#define P00_BRACE_3(X, ...) {X}, P00_BRACE_2(__VA_ARGS__)
#define P00_BRACE_4(X, ...) {X}, P00_BRACE_3(__VA_ARGS__)
#define P00_BRACE_5(X, ...) {X}, P00_BRACE_4(__VA_ARGS__)
#define P00_BRACE_6(X, ...) {X}, P00_BRACE_5(__VA_ARGS__)
#define P00_BRACE_7(X, ...) {X}, P00_BRACE_6(__VA_ARGS__)
#define P00_BRACE_8(X, ...) {X}, P00_BRACE_7(__VA_ARGS__)
#define P00_BRACE_9(X, ...) {X}, P00_BRACE_8(__VA_ARGS__)
#define P00_BRACE_10(X, ...) {X}, P00_BRACE_9(__VA_ARGS__)
#define P00_BRACE_11(X, ...) {X}, P00_BRACE_10(__VA_ARGS__)
#define P00_BRACE_12(X, ...) {X}, P00_BRACE_11(__VA_ARGS__)
#define P00_BRACE_13(X, ...) {X}, P00_BRACE_12(__VA_ARGS__)
#define P00_BRACE_14(X, ...) {X}, P00_BRACE_13(__VA_ARGS__)
#define P00_BRACE_15(X, ...) {X}, P00_BRACE_14(__VA_ARGS__)
#define P00_BRACE_16(X, ...) {X}, P00_BRACE_15(__VA_ARGS__)
#define P00_BRACE_17(X, ...) {X}, P00_BRACE_16(__VA_ARGS__)
#define P00_BRACE_18(X, ...) {X}, P00_BRACE_17(__VA_ARGS__)
#define P00_BRACE_19(X, ...) {X}, P00_BRACE_18(__VA_ARGS__)
#define P00_BRACE_20(X, ...) {X}, P00_BRACE_19(__VA_ARGS__)
#define P00_BRACE_21(X, ...) {X}, P00_BRACE_20(__VA_ARGS__)
#define P00_BRACE_22(X, ...) {X}, P00_BRACE_21(__VA_ARGS__)
#define P00_BRACE_23(X, ...) {X}, P00_BRACE_22(__VA_ARGS__)
#define P00_BRACE_24(X, ...) {X}, P00_BRACE_23(__VA_ARGS__)
#define P00_BRACE_25(X, ...) {X}, P00_BRACE_24(__VA_ARGS__)
#define P00_BRACE_26(X, ...) {X}, P00_BRACE_25(__VA_ARGS__)
#define P00_BRACE_27(X, ...) {X}, P00_BRACE_26(__VA_ARGS__)
#define P00_BRACE_28(X, ...) {X}, P00_BRACE_27(__VA_ARGS__)
#define P00_BRACE_29(X, ...) {X}, P00_BRACE_28(__VA_ARGS__)
#define P00_BRACE_30(X, ...) {X}, P00_BRACE_29(__VA_ARGS__)
#define P00_BRACE_31(X, ...) {X}, P00_BRACE_30(__VA_ARGS__)
#define P00_BRACE_32(X, ...) {X}, P00_BRACE_31(__VA_ARGS__)
#define P00_BRACE_33(X, ...) {X}, P00_BRACE_32(__VA_ARGS__)
#define P00_BRACE_34(X, ...) {X}, P00_BRACE_33(__VA_ARGS__)
#define P00_BRACE_35(X, ...) {X}, P00_BRACE_34(__VA_ARGS__)
#define P00_BRACE_36(X, ...) {X}, P00_BRACE_35(__VA_ARGS__)
#define P00_BRACE_37(X, ...) {X}, P00_BRACE_36(__VA_ARGS__)
#define P00_BRACE_38(X, ...) {X}, P00_BRACE_37(__VA_ARGS__)
#define P00_BRACE_39(X, ...) {X}, P00_BRACE_38(__VA_ARGS__)
#define P00_BRACE_40(X, ...) {X}, P00_BRACE_39(__VA_ARGS__)
#define P00_BRACE_41(X, ...) {X}, P00_BRACE_40(__VA_ARGS__)
#define P00_BRACE_42(X, ...) {X}, P00_BRACE_41(__VA_ARGS__)
#define P00_BRACE_43(X, ...) {X}, P00_BRACE_42(__VA_ARGS__)
#define P00_BRACE_44(X, ...) {X}, P00_BRACE_43(__VA_ARGS__)
#define P00_BRACE_45(X, ...) {X}, P00_BRACE_44(__VA_ARGS__)
#define P00_BRACE_46(X, ...) {X}, P00_BRACE_45(__VA_ARGS__)
#define P00_BRACE_47(X, ...) {X}, P00_BRACE_46(__VA_ARGS__)
#define P00_BRACE_48(X, ...) {X}, P00_BRACE_47(__VA_ARGS__)
#define P00_BRACE_49(X, ...) {X}, P00_BRACE_48(__VA_ARGS__)
#define P00_BRACE_50(X, ...) {X}, P00_BRACE_49(__VA_ARGS__)
#define P00_BRACE_51(X, ...) {X}, P00_BRACE_50(__VA_ARGS__)
#define P00_BRACE_52(X, ...) {X}, P00_BRACE_51(__VA_ARGS__)
#define P00_BRACE_53(X, ...) {X}, P00_BRACE_52(__VA_ARGS__)
#define P00_BRACE_54(X, ...) {X}, P00_BRACE_53(__VA_ARGS__)
#define P00_BRACE_55(X, ...) {X}, P00_BRACE_54(__VA_ARGS__)
#define P00_BRACE_56(X, ...) {X}, P00_BRACE_55(__VA_ARGS__)
#define P00_BRACE_57(X, ...) {X}, P00_BRACE_56(__VA_ARGS__)
#define P00_BRACE_58(X, ...) {X}, P00_BRACE_57(__VA_ARGS__)
#define P00_BRACE_59(X, ...) {X}, P00_BRACE_58(__VA_ARGS__)
#define P00_BRACE_60(X, ...) {X}, P00_BRACE_59(__VA_ARGS__)
#define P00_BRACE_61(X, ...) {X}, P00_BRACE_60(__VA_ARGS__)
#define P00_BRACE_62(X, ...) {X}, P00_BRACE_61(__VA_ARGS__)
#define P00_BRACE_63(X, ...) {X}, P00_BRACE_62(__VA_ARGS__)
#define P00_BRACE_64(X, ...) {X}, P00_BRACE_63(__VA_ARGS__)
#define P00_BRACE_65(X, ...) {X}, P00_BRACE_64(__VA_ARGS__)
#define P00_BRACE_66(X, ...) {X}, P00_BRACE_65(__VA_ARGS__)
#define P00_BRACE_67(X, ...) {X}, P00_BRACE_66(__VA_ARGS__)
#define P00_BRACE_68(X, ...) {X}, P00_BRACE_67(__VA_ARGS__)
#define P00_BRACE_69(X, ...) {X}, P00_BRACE_68(__VA_ARGS__)
#define P00_BRACE_70(X, ...) {X}, P00_BRACE_69(__VA_ARGS__)
#define P00_BRACE_71(X, ...) {X}, P00_BRACE_70(__VA_ARGS__)
#define P00_BRACE_72(X, ...) {X}, P00_BRACE_71(__VA_ARGS__)
#define P00_BRACE_73(X, ...) {X}, P00_BRACE_72(__VA_ARGS__)
#define P00_BRACE_74(X, ...) {X}, P00_BRACE_73(__VA_ARGS__)
#define P00_BRACE_75(X, ...) {X}, P00_BRACE_74(__VA_ARGS__)
#define P00_BRACE_76(X, ...) {X}, P00_BRACE_75(__VA_ARGS__)
#define P00_BRACE_77(X, ...) {X}, P00_BRACE_76(__VA_ARGS__)
#define P00_BRACE_78(X, ...) {X}, P00_BRACE_77(__VA_ARGS__)
#define P00_BRACE_79(X, ...) {X}, P00_BRACE_78(__VA_ARGS__)
#define P00_BRACE_80(X, ...) {X}, P00_BRACE_79(__VA_ARGS__)
#define P00_BRACE_81(X, ...) {X}, P00_BRACE_80(__VA_ARGS__)
#define P00_BRACE_82(X, ...) {X}, P00_BRACE_81(__VA_ARGS__)
#define P00_BRACE_83(X, ...) {X}, P00_BRACE_82(__VA_ARGS__)
#define P00_BRACE_84(X, ...) {X}, P00_BRACE_83(__VA_ARGS__)
#define P00_BRACE_85(X, ...) {X}, P00_BRACE_84(__VA_ARGS__)
#define P00_BRACE_86(X, ...) {X}, P00_BRACE_85(__VA_ARGS__)
#define P00_BRACE_87(X, ...) {X}, P00_BRACE_86(__VA_ARGS__)
#define P00_BRACE_88(X, ...) {X}, P00_BRACE_87(__VA_ARGS__)
#define P00_BRACE_89(X, ...) {X}, P00_BRACE_88(__VA_ARGS__)
#define P00_BRACE_90(X, ...) {X}, P00_BRACE_89(__VA_ARGS__)
#define P00_BRACE_91(X, ...) {X}, P00_BRACE_90(__VA_ARGS__)
#define P00_BRACE_92(X, ...) {X}, P00_BRACE_91(__VA_ARGS__)
#define P00_BRACE_93(X, ...) {X}, P00_BRACE_92(__VA_ARGS__)
#define P00_BRACE_94(X, ...) {X}, P00_BRACE_93(__VA_ARGS__)
#define P00_BRACE_95(X, ...) {X}, P00_BRACE_94(__VA_ARGS__)
#define P00_BRACE_96(X, ...) {X}, P00_BRACE_95(__VA_ARGS__)
#define P00_BRACE_97(X, ...) {X}, P00_BRACE_96(__VA_ARGS__)
#define P00_BRACE_98(X, ...) {X}, P00_BRACE_97(__VA_ARGS__)
#define P00_BRACE_99(X, ...) {X}, P00_BRACE_98(__VA_ARGS__)
#define P00_BRACE_100(X, ...) {X}, P00_BRACE_99(__VA_ARGS__)
#define P00_BRACE_101(X, ...) {X}, P00_BRACE_100(__VA_ARGS__)
#define P00_BRACE_102(X, ...) {X}, P00_BRACE_101(__VA_ARGS__)
#define P00_BRACE_103(X, ...) {X}, P00_BRACE_102(__VA_ARGS__)
#define P00_BRACE_104(X, ...) {X}, P00_BRACE_103(__VA_ARGS__)
#define P00_BRACE_105(X, ...) {X}, P00_BRACE_104(__VA_ARGS__)
#define P00_BRACE_106(X, ...) {X}, P00_BRACE_105(__VA_ARGS__)
#define P00_BRACE_107(X, ...) {X}, P00_BRACE_106(__VA_ARGS__)
#define P00_BRACE_108(X, ...) {X}, P00_BRACE_107(__VA_ARGS__)
#define P00_BRACE_109(X, ...) {X}, P00_BRACE_108(__VA_ARGS__)
#define P00_BRACE_110(X, ...) {X}, P00_BRACE_109(__VA_ARGS__)
#define P00_BRACE_111(X, ...) {X}, P00_BRACE_110(__VA_ARGS__)
#define P00_BRACE_112(X, ...) {X}, P00_BRACE_111(__VA_ARGS__)
#define P00_BRACE_113(X, ...) {X}, P00_BRACE_112(__VA_ARGS__)
#define P00_BRACE_114(X, ...) {X}, P00_BRACE_113(__VA_ARGS__)
#define P00_BRACE_115(X, ...) {X}, P00_BRACE_114(__VA_ARGS__)
#define P00_BRACE_116(X, ...) {X}, P00_BRACE_115(__VA_ARGS__)
#define P00_BRACE_117(X, ...) {X}, P00_BRACE_116(__VA_ARGS__)
#define P00_BRACE_118(X, ...) {X}, P00_BRACE_117(__VA_ARGS__)
#define P00_BRACE_119(X, ...) {X}, P00_BRACE_118(__VA_ARGS__)
#define P00_BRACE_120(X, ...) {X}, P00_BRACE_119(__VA_ARGS__)
#define P00_BRACE_121(X, ...) {X}, P00_BRACE_120(__VA_ARGS__)
#define P00_BRACE_122(X, ...) {X}, P00_BRACE_121(__VA_ARGS__)
#define P00_BRACE_123(X, ...) {X}, P00_BRACE_122(__VA_ARGS__)
#define P00_BRACE_124(X, ...) {X}, P00_BRACE_123(__VA_ARGS__)
#define P00_BRACE_125(X, ...) {X}, P00_BRACE_124(__VA_ARGS__)
#define P00_BRACE_126(X, ...) {X}, P00_BRACE_125(__VA_ARGS__)
#define P00_BRACE_127(X, ...) {X}, P00_BRACE_126(__VA_ARGS__)
#define P00_BRACE_128(X, ...) {X}, P00_BRACE_127(__VA_ARGS__)
#define P00_BRACE_129(X, ...) {X}, P00_BRACE_128(__VA_ARGS__)
#define P00_BRACE_130(X, ...) {X}, P00_BRACE_129(__VA_ARGS__)
#define P00_BRACE_131(X, ...) {X}, P00_BRACE_130(__VA_ARGS__)
#define P00_BRACE_132(X, ...) {X}, P00_BRACE_131(__VA_ARGS__)
#define P00_BRACE_133(X, ...) {X}, P00_BRACE_132(__VA_ARGS__)
#define P00_BRACE_134(X, ...) {X}, P00_BRACE_133(__VA_ARGS__)
#define P00_BRACE_135(X, ...) {X}, P00_BRACE_134(__VA_ARGS__)
#define P00_BRACE_136(X, ...) {X}, P00_BRACE_135(__VA_ARGS__)
#define P00_BRACE_137(X, ...) {X}, P00_BRACE_136(__VA_ARGS__)
#define P00_BRACE_138(X, ...) {X}, P00_BRACE_137(__VA_ARGS__)
#define P00_BRACE_139(X, ...) {X}, P00_BRACE_138(__VA_ARGS__)
#define P00_BRACE_140(X, ...) {X}, P00_BRACE_139(__VA_ARGS__)
#define P00_BRACE_141(X, ...) {X}, P00_BRACE_140(__VA_ARGS__)
#define P00_BRACE_142(X, ...) {X}, P00_BRACE_141(__VA_ARGS__)
#define P00_BRACE_143(X, ...) {X}, P00_BRACE_142(__VA_ARGS__)
#define P00_BRACE_144(X, ...) {X}, P00_BRACE_143(__VA_ARGS__)
#define P00_BRACE_145(X, ...) {X}, P00_BRACE_144(__VA_ARGS__)
#define P00_BRACE_146(X, ...) {X}, P00_BRACE_145(__VA_ARGS__)
#define P00_BRACE_147(X, ...) {X}, P00_BRACE_146(__VA_ARGS__)
#define P00_BRACE_148(X, ...) {X}, P00_BRACE_147(__VA_ARGS__)
#define P00_BRACE_149(X, ...) {X}, P00_BRACE_148(__VA_ARGS__)
#define P00_BRACE_150(X, ...) {X}, P00_BRACE_149(__VA_ARGS__)
#define P00_BRACE_151(X, ...) {X}, P00_BRACE_150(__VA_ARGS__)
#define P00_BRACE_152(X, ...) {X}, P00_BRACE_151(__VA_ARGS__)
#define P00_BRACE_153(X, ...) {X}, P00_BRACE_152(__VA_ARGS__)
#define P00_BRACE_154(X, ...) {X}, P00_BRACE_153(__VA_ARGS__)
#define P00_BRACE_155(X, ...) {X}, P00_BRACE_154(__VA_ARGS__)
#define P00_BRACE_156(X, ...) {X}, P00_BRACE_155(__VA_ARGS__)
#define P00_BRACE_157(X, ...) {X}, P00_BRACE_156(__VA_ARGS__)
#define P00_BRACE_158(X, ...) {X}, P00_BRACE_157(__VA_ARGS__)
#define P00_BRACE_159(X, ...) {X}, P00_BRACE_158(__VA_ARGS__)
#define P00_PAREN_2(X, ...) (X)P00_PAREN_1(__VA_ARGS__)
#define P00_PAREN_3(X, ...) (X)P00_PAREN_2(__VA_ARGS__)
#define P00_PAREN_4(X, ...) (X)P00_PAREN_3(__VA_ARGS__)
#define P00_PAREN_5(X, ...) (X)P00_PAREN_4(__VA_ARGS__)
#define P00_PAREN_6(X, ...) (X)P00_PAREN_5(__VA_ARGS__)
#define P00_PAREN_7(X, ...) (X)P00_PAREN_6(__VA_ARGS__)
#define P00_PAREN_8(X, ...) (X)P00_PAREN_7(__VA_ARGS__)
#define P00_PAREN_9(X, ...) (X)P00_PAREN_8(__VA_ARGS__)
#define P00_PAREN_10(X, ...) (X)P00_PAREN_9(__VA_ARGS__)
#define P00_PAREN_11(X, ...) (X)P00_PAREN_10(__VA_ARGS__)
#define P00_PAREN_12(X, ...) (X)P00_PAREN_11(__VA_ARGS__)
#define P00_PAREN_13(X, ...) (X)P00_PAREN_12(__VA_ARGS__)
#define P00_PAREN_14(X, ...) (X)P00_PAREN_13(__VA_ARGS__)
#define P00_PAREN_15(X, ...) (X)P00_PAREN_14(__VA_ARGS__)
#define P00_PAREN_16(X, ...) (X)P00_PAREN_15(__VA_ARGS__)
#define P00_PAREN_17(X, ...) (X)P00_PAREN_16(__VA_ARGS__)
#define P00_PAREN_18(X, ...) (X)P00_PAREN_17(__VA_ARGS__)
#define P00_PAREN_19(X, ...) (X)P00_PAREN_18(__VA_ARGS__)
#define P00_PAREN_20(X, ...) (X)P00_PAREN_19(__VA_ARGS__)
#define P00_PAREN_21(X, ...) (X)P00_PAREN_20(__VA_ARGS__)
#define P00_PAREN_22(X, ...) (X)P00_PAREN_21(__VA_ARGS__)
#define P00_PAREN_23(X, ...) (X)P00_PAREN_22(__VA_ARGS__)
#define P00_PAREN_24(X, ...) (X)P00_PAREN_23(__VA_ARGS__)
#define P00_PAREN_25(X, ...) (X)P00_PAREN_24(__VA_ARGS__)
#define P00_PAREN_26(X, ...) (X)P00_PAREN_25(__VA_ARGS__)
#define P00_PAREN_27(X, ...) (X)P00_PAREN_26(__VA_ARGS__)
#define P00_PAREN_28(X, ...) (X)P00_PAREN_27(__VA_ARGS__)
#define P00_PAREN_29(X, ...) (X)P00_PAREN_28(__VA_ARGS__)
#define P00_PAREN_30(X, ...) (X)P00_PAREN_29(__VA_ARGS__)
#define P00_PAREN_31(X, ...) (X)P00_PAREN_30(__VA_ARGS__)
#define P00_PAREN_32(X, ...) (X)P00_PAREN_31(__VA_ARGS__)
#define P00_PAREN_33(X, ...) (X)P00_PAREN_32(__VA_ARGS__)
#define P00_PAREN_34(X, ...) (X)P00_PAREN_33(__VA_ARGS__)
#define P00_PAREN_35(X, ...) (X)P00_PAREN_34(__VA_ARGS__)
#define P00_PAREN_36(X, ...) (X)P00_PAREN_35(__VA_ARGS__)
#define P00_PAREN_37(X, ...) (X)P00_PAREN_36(__VA_ARGS__)
#define P00_PAREN_38(X, ...) (X)P00_PAREN_37(__VA_ARGS__)
#define P00_PAREN_39(X, ...) (X)P00_PAREN_38(__VA_ARGS__)
#define P00_PAREN_40(X, ...) (X)P00_PAREN_39(__VA_ARGS__)
#define P00_PAREN_41(X, ...) (X)P00_PAREN_40(__VA_ARGS__)
#define P00_PAREN_42(X, ...) (X)P00_PAREN_41(__VA_ARGS__)
#define P00_PAREN_43(X, ...) (X)P00_PAREN_42(__VA_ARGS__)
#define P00_PAREN_44(X, ...) (X)P00_PAREN_43(__VA_ARGS__)
#define P00_PAREN_45(X, ...) (X)P00_PAREN_44(__VA_ARGS__)
#define P00_PAREN_46(X, ...) (X)P00_PAREN_45(__VA_ARGS__)
#define P00_PAREN_47(X, ...) (X)P00_PAREN_46(__VA_ARGS__)
#define P00_PAREN_48(X, ...) (X)P00_PAREN_47(__VA_ARGS__)
#define P00_PAREN_49(X, ...) (X)P00_PAREN_48(__VA_ARGS__)
#define P00_PAREN_50(X, ...) (X)P00_PAREN_49(__VA_ARGS__)
#define P00_PAREN_51(X, ...) (X)P00_PAREN_50(__VA_ARGS__)
#define P00_PAREN_52(X, ...) (X)P00_PAREN_51(__VA_ARGS__)
#define P00_PAREN_53(X, ...) (X)P00_PAREN_52(__VA_ARGS__)
#define P00_PAREN_54(X, ...) (X)P00_PAREN_53(__VA_ARGS__)
#define P00_PAREN_55(X, ...) (X)P00_PAREN_54(__VA_ARGS__)
#define P00_PAREN_56(X, ...) (X)P00_PAREN_55(__VA_ARGS__)
#define P00_PAREN_57(X, ...) (X)P00_PAREN_56(__VA_ARGS__)
#define P00_PAREN_58(X, ...) (X)P00_PAREN_57(__VA_ARGS__)
#define P00_PAREN_59(X, ...) (X)P00_PAREN_58(__VA_ARGS__)
#define P00_PAREN_60(X, ...) (X)P00_PAREN_59(__VA_ARGS__)
#define P00_PAREN_61(X, ...) (X)P00_PAREN_60(__VA_ARGS__)
#define P00_PAREN_62(X, ...) (X)P00_PAREN_61(__VA_ARGS__)
#define P00_PAREN_63(X, ...) (X)P00_PAREN_62(__VA_ARGS__)
#define P00_PAREN_64(X, ...) (X)P00_PAREN_63(__VA_ARGS__)
#define P00_PAREN_65(X, ...) (X)P00_PAREN_64(__VA_ARGS__)
#define P00_PAREN_66(X, ...) (X)P00_PAREN_65(__VA_ARGS__)
#define P00_PAREN_67(X, ...) (X)P00_PAREN_66(__VA_ARGS__)
#define P00_PAREN_68(X, ...) (X)P00_PAREN_67(__VA_ARGS__)
#define P00_PAREN_69(X, ...) (X)P00_PAREN_68(__VA_ARGS__)
#define P00_PAREN_70(X, ...) (X)P00_PAREN_69(__VA_ARGS__)
#define P00_PAREN_71(X, ...) (X)P00_PAREN_70(__VA_ARGS__)
#define P00_PAREN_72(X, ...) (X)P00_PAREN_71(__VA_ARGS__)
#define P00_PAREN_73(X, ...) (X)P00_PAREN_72(__VA_ARGS__)
#define P00_PAREN_74(X, ...) (X)P00_PAREN_73(__VA_ARGS__)
#define P00_PAREN_75(X, ...) (X)P00_PAREN_74(__VA_ARGS__)
#define P00_PAREN_76(X, ...) (X)P00_PAREN_75(__VA_ARGS__)
#define P00_PAREN_77(X, ...) (X)P00_PAREN_76(__VA_ARGS__)
#define P00_PAREN_78(X, ...) (X)P00_PAREN_77(__VA_ARGS__)
#define P00_PAREN_79(X, ...) (X)P00_PAREN_78(__VA_ARGS__)
#define P00_PAREN_80(X, ...) (X)P00_PAREN_79(__VA_ARGS__)
#define P00_PAREN_81(X, ...) (X)P00_PAREN_80(__VA_ARGS__)
#define P00_PAREN_82(X, ...) (X)P00_PAREN_81(__VA_ARGS__)
#define P00_PAREN_83(X, ...) (X)P00_PAREN_82(__VA_ARGS__)
#define P00_PAREN_84(X, ...) (X)P00_PAREN_83(__VA_ARGS__)
#define P00_PAREN_85(X, ...) (X)P00_PAREN_84(__VA_ARGS__)
#define P00_PAREN_86(X, ...) (X)P00_PAREN_85(__VA_ARGS__)
#define P00_PAREN_87(X, ...) (X)P00_PAREN_86(__VA_ARGS__)
#define P00_PAREN_88(X, ...) (X)P00_PAREN_87(__VA_ARGS__)
#define P00_PAREN_89(X, ...) (X)P00_PAREN_88(__VA_ARGS__)
#define P00_PAREN_90(X, ...) (X)P00_PAREN_89(__VA_ARGS__)
#define P00_PAREN_91(X, ...) (X)P00_PAREN_90(__VA_ARGS__)
#define P00_PAREN_92(X, ...) (X)P00_PAREN_91(__VA_ARGS__)
#define P00_PAREN_93(X, ...) (X)P00_PAREN_92(__VA_ARGS__)
#define P00_PAREN_94(X, ...) (X)P00_PAREN_93(__VA_ARGS__)
#define P00_PAREN_95(X, ...) (X)P00_PAREN_94(__VA_ARGS__)
#define P00_PAREN_96(X, ...) (X)P00_PAREN_95(__VA_ARGS__)
#define P00_PAREN_97(X, ...) (X)P00_PAREN_96(__VA_ARGS__)
#define P00_PAREN_98(X, ...) (X)P00_PAREN_97(__VA_ARGS__)
#define P00_PAREN_99(X, ...) (X)P00_PAREN_98(__VA_ARGS__)
#define P00_PAREN_100(X, ...) (X)P00_PAREN_99(__VA_ARGS__)
#define P00_PAREN_101(X, ...) (X)P00_PAREN_100(__VA_ARGS__)
#define P00_PAREN_102(X, ...) (X)P00_PAREN_101(__VA_ARGS__)
#define P00_PAREN_103(X, ...) (X)P00_PAREN_102(__VA_ARGS__)
#define P00_PAREN_104(X, ...) (X)P00_PAREN_103(__VA_ARGS__)
#define P00_PAREN_105(X, ...) (X)P00_PAREN_104(__VA_ARGS__)
#define P00_PAREN_106(X, ...) (X)P00_PAREN_105(__VA_ARGS__)
#define P00_PAREN_107(X, ...) (X)P00_PAREN_106(__VA_ARGS__)
#define P00_PAREN_108(X, ...) (X)P00_PAREN_107(__VA_ARGS__)
#define P00_PAREN_109(X, ...) (X)P00_PAREN_108(__VA_ARGS__)
#define P00_PAREN_110(X, ...) (X)P00_PAREN_109(__VA_ARGS__)
#define P00_PAREN_111(X, ...) (X)P00_PAREN_110(__VA_ARGS__)
#define P00_PAREN_112(X, ...) (X)P00_PAREN_111(__VA_ARGS__)
#define P00_PAREN_113(X, ...) (X)P00_PAREN_112(__VA_ARGS__)
#define P00_PAREN_114(X, ...) (X)P00_PAREN_113(__VA_ARGS__)
#define P00_PAREN_115(X, ...) (X)P00_PAREN_114(__VA_ARGS__)
#define P00_PAREN_116(X, ...) (X)P00_PAREN_115(__VA_ARGS__)
#define P00_PAREN_117(X, ...) (X)P00_PAREN_116(__VA_ARGS__)
#define P00_PAREN_118(X, ...) (X)P00_PAREN_117(__VA_ARGS__)
#define P00_PAREN_119(X, ...) (X)P00_PAREN_118(__VA_ARGS__)
#define P00_PAREN_120(X, ...) (X)P00_PAREN_119(__VA_ARGS__)
#define P00_PAREN_121(X, ...) (X)P00_PAREN_120(__VA_ARGS__)
#define P00_PAREN_122(X, ...) (X)P00_PAREN_121(__VA_ARGS__)
#define P00_PAREN_123(X, ...) (X)P00_PAREN_122(__VA_ARGS__)
#define P00_PAREN_124(X, ...) (X)P00_PAREN_123(__VA_ARGS__)
#define P00_PAREN_125(X, ...) (X)P00_PAREN_124(__VA_ARGS__)
#define P00_PAREN_126(X, ...) (X)P00_PAREN_125(__VA_ARGS__)
#define P00_PAREN_127(X, ...) (X)P00_PAREN_126(__VA_ARGS__)
#define P00_PAREN_128(X, ...) (X)P00_PAREN_127(__VA_ARGS__)
#define P00_PAREN_129(X, ...) (X)P00_PAREN_128(__VA_ARGS__)
#define P00_PAREN_130(X, ...) (X)P00_PAREN_129(__VA_ARGS__)
#define P00_PAREN_131(X, ...) (X)P00_PAREN_130(__VA_ARGS__)
#define P00_PAREN_132(X, ...) (X)P00_PAREN_131(__VA_ARGS__)
#define P00_PAREN_133(X, ...) (X)P00_PAREN_132(__VA_ARGS__)
#define P00_PAREN_134(X, ...) (X)P00_PAREN_133(__VA_ARGS__)
#define P00_PAREN_135(X, ...) (X)P00_PAREN_134(__VA_ARGS__)
#define P00_PAREN_136(X, ...) (X)P00_PAREN_135(__VA_ARGS__)
#define P00_PAREN_137(X, ...) (X)P00_PAREN_136(__VA_ARGS__)
#define P00_PAREN_138(X, ...) (X)P00_PAREN_137(__VA_ARGS__)
#define P00_PAREN_139(X, ...) (X)P00_PAREN_138(__VA_ARGS__)
#define P00_PAREN_140(X, ...) (X)P00_PAREN_139(__VA_ARGS__)
#define P00_PAREN_141(X, ...) (X)P00_PAREN_140(__VA_ARGS__)
#define P00_PAREN_142(X, ...) (X)P00_PAREN_141(__VA_ARGS__)
#define P00_PAREN_143(X, ...) (X)P00_PAREN_142(__VA_ARGS__)
#define P00_PAREN_144(X, ...) (X)P00_PAREN_143(__VA_ARGS__)
#define P00_PAREN_145(X, ...) (X)P00_PAREN_144(__VA_ARGS__)
#define P00_PAREN_146(X, ...) (X)P00_PAREN_145(__VA_ARGS__)
#define P00_PAREN_147(X, ...) (X)P00_PAREN_146(__VA_ARGS__)
#define P00_PAREN_148(X, ...) (X)P00_PAREN_147(__VA_ARGS__)
#define P00_PAREN_149(X, ...) (X)P00_PAREN_148(__VA_ARGS__)
#define P00_PAREN_150(X, ...) (X)P00_PAREN_149(__VA_ARGS__)
#define P00_PAREN_151(X, ...) (X)P00_PAREN_150(__VA_ARGS__)
#define P00_PAREN_152(X, ...) (X)P00_PAREN_151(__VA_ARGS__)
#define P00_PAREN_153(X, ...) (X)P00_PAREN_152(__VA_ARGS__)
#define P00_PAREN_154(X, ...) (X)P00_PAREN_153(__VA_ARGS__)
#define P00_PAREN_155(X, ...) (X)P00_PAREN_154(__VA_ARGS__)
#define P00_PAREN_156(X, ...) (X)P00_PAREN_155(__VA_ARGS__)
#define P00_PAREN_157(X, ...) (X)P00_PAREN_156(__VA_ARGS__)
#define P00_PAREN_158(X, ...) (X)P00_PAREN_157(__VA_ARGS__)
#define P00_PAREN_159(X, ...) (X)P00_PAREN_158(__VA_ARGS__)
#define P00_MAP_2(MAC, SEP, X, ...) MAC(X)P00_ROBUST SEP P00_MAP_1(MAC, SEP, __VA_ARGS__)
#define P00_MAP_3(MAC, SEP, X, ...) MAC(X)P00_ROBUST SEP P00_MAP_2(MAC, SEP, __VA_ARGS__)
#define P00_MAP_4(MAC, SEP, X, ...) MAC(X)P00_ROBUST SEP P00_MAP_3(MAC, SEP, __VA_ARGS__)
#define P00_MAP_5(MAC, SEP, X, ...) MAC(X)P00_ROBUST SEP P00_MAP_4(MAC, SEP, __VA_ARGS__)
#define P00_MAP_6(MAC, SEP, X, ...) MAC(X)P00_ROBUST SEP P00_MAP_5(MAC, SEP, __VA_ARGS__)
#define P00_MAP_7(MAC, SEP, X, ...) MAC(X)P00_ROBUST SEP P00_MAP_6(MAC, SEP, __VA_ARGS__)
#define P00_MAP_8(MAC, SEP, X, ...) MAC(X)P00_ROBUST SEP P00_MAP_7(MAC, SEP, __VA_ARGS__)
#define P00_MAP_9(MAC, SEP, X, ...) MAC(X)P00_ROBUST SEP P00_MAP_8(MAC, SEP, __VA_ARGS__)
#define P00_MAP_10(MAC, SEP, X, ...) MAC(X)P00_ROBUST SEP P00_MAP_9(MAC, SEP, __VA_ARGS__)
#define P00_MAP_11(MAC, SEP, X, ...) MAC(X)P00_ROBUST SEP P00_MAP_10(MAC, SEP, __VA_ARGS__)
#define P00_MAP_12(MAC, SEP, X, ...) MAC(X)P00_ROBUST SEP P00_MAP_11(MAC, SEP, __VA_ARGS__)
#define P00_MAP_13(MAC, SEP, X, ...) MAC(X)P00_ROBUST SEP P00_MAP_12(MAC, SEP, __VA_ARGS__)
#define P00_MAP_14(MAC, SEP, X, ...) MAC(X)P00_ROBUST SEP P00_MAP_13(MAC, SEP, __VA_ARGS__)
#define P00_MAP_15(MAC, SEP, X, ...) MAC(X)P00_ROBUST SEP P00_MAP_14(MAC, SEP, __VA_ARGS__)
#define P00_MAP_16(MAC, SEP, X, ...) MAC(X)P00_ROBUST SEP P00_MAP_15(MAC, SEP, __VA_ARGS__)
#define P00_MAP_17(MAC, SEP, X, ...) MAC(X)P00_ROBUST SEP P00_MAP_16(MAC, SEP, __VA_ARGS__)
#define P00_MAP_18(MAC, SEP, X, ...) MAC(X)P00_ROBUST SEP P00_MAP_17(MAC, SEP, __VA_ARGS__)
#define P00_MAP_19(MAC, SEP, X, ...) MAC(X)P00_ROBUST SEP P00_MAP_18(MAC, SEP, __VA_ARGS__)
#define P00_MAP_20(MAC, SEP, X, ...) MAC(X)P00_ROBUST SEP P00_MAP_19(MAC, SEP, __VA_ARGS__)
#define P00_MAP_21(MAC, SEP, X, ...) MAC(X)P00_ROBUST SEP P00_MAP_20(MAC, SEP, __VA_ARGS__)
#define P00_MAP_22(MAC, SEP, X, ...) MAC(X)P00_ROBUST SEP P00_MAP_21(MAC, SEP, __VA_ARGS__)
#define P00_MAP_23(MAC, SEP, X, ...) MAC(X)P00_ROBUST SEP P00_MAP_22(MAC, SEP, __VA_ARGS__)
#define P00_MAP_24(MAC, SEP, X, ...) MAC(X)P00_ROBUST SEP P00_MAP_23(MAC, SEP, __VA_ARGS__)
#define P00_MAP_25(MAC, SEP, X, ...) MAC(X)P00_ROBUST SEP P00_MAP_24(MAC, SEP, __VA_ARGS__)
#define P00_MAP_26(MAC, SEP, X, ...) MAC(X)P00_ROBUST SEP P00_MAP_25(MAC, SEP, __VA_ARGS__)
#define P00_MAP_27(MAC, SEP, X, ...) MAC(X)P00_ROBUST SEP P00_MAP_26(MAC, SEP, __VA_ARGS__)
#define P00_MAP_28(MAC, SEP, X, ...) MAC(X)P00_ROBUST SEP P00_MAP_27(MAC, SEP, __VA_ARGS__)
#define P00_MAP_29(MAC, SEP, X, ...) MAC(X)P00_ROBUST SEP P00_MAP_28(MAC, SEP, __VA_ARGS__)
#define P00_MAP_30(MAC, SEP, X, ...) MAC(X)P00_ROBUST SEP P00_MAP_29(MAC, SEP, __VA_ARGS__)
#define P00_MAP_31(MAC, SEP, X, ...) MAC(X)P00_ROBUST SEP P00_MAP_30(MAC, SEP, __VA_ARGS__)
#define P00_MAP_32(MAC, SEP, X, ...) MAC(X)P00_ROBUST SEP P00_MAP_31(MAC, SEP, __VA_ARGS__)
#define P00_MAP_33(MAC, SEP, X, ...) MAC(X)P00_ROBUST SEP P00_MAP_32(MAC, SEP, __VA_ARGS__)
#define P00_MAP_34(MAC, SEP, X, ...) MAC(X)P00_ROBUST SEP P00_MAP_33(MAC, SEP, __VA_ARGS__)
#define P00_MAP_35(MAC, SEP, X, ...) MAC(X)P00_ROBUST SEP P00_MAP_34(MAC, SEP, __VA_ARGS__)
#define P00_MAP_36(MAC, SEP, X, ...) MAC(X)P00_ROBUST SEP P00_MAP_35(MAC, SEP, __VA_ARGS__)
#define P00_MAP_37(MAC, SEP, X, ...) MAC(X)P00_ROBUST SEP P00_MAP_36(MAC, SEP, __VA_ARGS__)
#define P00_MAP_38(MAC, SEP, X, ...) MAC(X)P00_ROBUST SEP P00_MAP_37(MAC, SEP, __VA_ARGS__)
#define P00_MAP_39(MAC, SEP, X, ...) MAC(X)P00_ROBUST SEP P00_MAP_38(MAC, SEP, __VA_ARGS__)
#define P00_MAP_40(MAC, SEP, X, ...) MAC(X)P00_ROBUST SEP P00_MAP_39(MAC, SEP, __VA_ARGS__)
#define P00_MAP_41(MAC, SEP, X, ...) MAC(X)P00_ROBUST SEP P00_MAP_40(MAC, SEP, __VA_ARGS__)
#define P00_MAP_42(MAC, SEP, X, ...) MAC(X)P00_ROBUST SEP P00_MAP_41(MAC, SEP, __VA_ARGS__)
#define P00_MAP_43(MAC, SEP, X, ...) MAC(X)P00_ROBUST SEP P00_MAP_42(MAC, SEP, __VA_ARGS__)
#define P00_MAP_44(MAC, SEP, X, ...) MAC(X)P00_ROBUST SEP P00_MAP_43(MAC, SEP, __VA_ARGS__)
#define P00_MAP_45(MAC, SEP, X, ...) MAC(X)P00_ROBUST SEP P00_MAP_44(MAC, SEP, __VA_ARGS__)
#define P00_MAP_46(MAC, SEP, X, ...) MAC(X)P00_ROBUST SEP P00_MAP_45(MAC, SEP, __VA_ARGS__)
#define P00_MAP_47(MAC, SEP, X, ...) MAC(X)P00_ROBUST SEP P00_MAP_46(MAC, SEP, __VA_ARGS__)
#define P00_MAP_48(MAC, SEP, X, ...) MAC(X)P00_ROBUST SEP P00_MAP_47(MAC, SEP, __VA_ARGS__)
#define P00_MAP_49(MAC, SEP, X, ...) MAC(X)P00_ROBUST SEP P00_MAP_48(MAC, SEP, __VA_ARGS__)
#define P00_MAP_50(MAC, SEP, X, ...) MAC(X)P00_ROBUST SEP P00_MAP_49(MAC, SEP, __VA_ARGS__)
#define P00_MAP_51(MAC, SEP, X, ...) MAC(X)P00_ROBUST SEP P00_MAP_50(MAC, SEP, __VA_ARGS__)
#define P00_MAP_52(MAC, SEP, X, ...) MAC(X)P00_ROBUST SEP P00_MAP_51(MAC, SEP, __VA_ARGS__)
#define P00_MAP_53(MAC, SEP, X, ...) MAC(X)P00_ROBUST SEP P00_MAP_52(MAC, SEP, __VA_ARGS__)
#define P00_MAP_54(MAC, SEP, X, ...) MAC(X)P00_ROBUST SEP P00_MAP_53(MAC, SEP, __VA_ARGS__)
#define P00_MAP_55(MAC, SEP, X, ...) MAC(X)P00_ROBUST SEP P00_MAP_54(MAC, SEP, __VA_ARGS__)
#define P00_MAP_56(MAC, SEP, X, ...) MAC(X)P00_ROBUST SEP P00_MAP_55(MAC, SEP, __VA_ARGS__)
#define P00_MAP_57(MAC, SEP, X, ...) MAC(X)P00_ROBUST SEP P00_MAP_56(MAC, SEP, __VA_ARGS__)
#define P00_MAP_58(MAC, SEP, X, ...) MAC(X)P00_ROBUST SEP P00_MAP_57(MAC, SEP, __VA_ARGS__)
#define P00_MAP_59(MAC, SEP, X, ...) MAC(X)P00_ROBUST SEP P00_MAP_58(MAC, SEP, __VA_ARGS__)
#define P00_MAP_60(MAC, SEP, X, ...) MAC(X)P00_ROBUST SEP P00_MAP_59(MAC, SEP, __VA_ARGS__)
#define P00_MAP_61(MAC, SEP, X, ...) MAC(X)P00_ROBUST SEP P00_MAP_60(MAC, SEP, __VA_ARGS__)
#define P00_MAP_62(MAC, SEP, X, ...) MAC(X)P00_ROBUST SEP P00_MAP_61(MAC, SEP, __VA_ARGS__)
#define P00_MAP_63(MAC, SEP, X, ...) MAC(X)P00_ROBUST SEP P00_MAP_62(MAC, SEP, __VA_ARGS__)
#define P00_MAP_64(MAC, SEP, X, ...) MAC(X)P00_ROBUST SEP P00_MAP_63(MAC, SEP, __VA_ARGS__)
#define P00_MAP_65(MAC, SEP, X, ...) MAC(X)P00_ROBUST SEP P00_MAP_64(MAC, SEP, __VA_ARGS__)
#define P00_MAP_66(MAC, SEP, X, ...) MAC(X)P00_ROBUST SEP P00_MAP_65(MAC, SEP, __VA_ARGS__)
#define P00_MAP_67(MAC, SEP, X, ...) MAC(X)P00_ROBUST SEP P00_MAP_66(MAC, SEP, __VA_ARGS__)
#define P00_MAP_68(MAC, SEP, X, ...) MAC(X)P00_ROBUST SEP P00_MAP_67(MAC, SEP, __VA_ARGS__)
#define P00_MAP_69(MAC, SEP, X, ...) MAC(X)P00_ROBUST SEP P00_MAP_68(MAC, SEP, __VA_ARGS__)
#define P00_MAP_70(MAC, SEP, X, ...) MAC(X)P00_ROBUST SEP P00_MAP_69(MAC, SEP, __VA_ARGS__)
#define P00_MAP_71(MAC, SEP, X, ...) MAC(X)P00_ROBUST SEP P00_MAP_70(MAC, SEP, __VA_ARGS__)
#define P00_MAP_72(MAC, SEP, X, ...) MAC(X)P00_ROBUST SEP P00_MAP_71(MAC, SEP, __VA_ARGS__)
#define P00_MAP_73(MAC, SEP, X, ...) MAC(X)P00_ROBUST SEP P00_MAP_72(MAC, SEP, __VA_ARGS__)
#define P00_MAP_74(MAC, SEP, X, ...) MAC(X)P00_ROBUST SEP P00_MAP_73(MAC, SEP, __VA_ARGS__)
#define P00_MAP_75(MAC, SEP, X, ...) MAC(X)P00_ROBUST SEP P00_MAP_74(MAC, SEP, __VA_ARGS__)
#define P00_MAP_76(MAC, SEP, X, ...) MAC(X)P00_ROBUST SEP P00_MAP_75(MAC, SEP, __VA_ARGS__)
#define P00_MAP_77(MAC, SEP, X, ...) MAC(X)P00_ROBUST SEP P00_MAP_76(MAC, SEP, __VA_ARGS__)
#define P00_MAP_78(MAC, SEP, X, ...) MAC(X)P00_ROBUST SEP P00_MAP_77(MAC, SEP, __VA_ARGS__)
#define P00_MAP_79(MAC, SEP, X, ...) MAC(X)P00_ROBUST SEP P00_MAP_78(MAC, SEP, __VA_ARGS__)
#define P00_MAP_80(MAC, SEP, X, ...) MAC(X)P00_ROBUST SEP P00_MAP_79(MAC, SEP, __VA_ARGS__)
#define P00_MAP_81(MAC, SEP, X, ...) MAC(X)P00_ROBUST SEP P00_MAP_80(MAC, SEP, __VA_ARGS__)
#define P00_MAP_82(MAC, SEP, X, ...) MAC(X)P00_ROBUST SEP P00_MAP_81(MAC, SEP, __VA_ARGS__)
#define P00_MAP_83(MAC, SEP, X, ...) MAC(X)P00_ROBUST SEP P00_MAP_82(MAC, SEP, __VA_ARGS__)
#define P00_MAP_84(MAC, SEP, X, ...) MAC(X)P00_ROBUST SEP P00_MAP_83(MAC, SEP, __VA_ARGS__)
#define P00_MAP_85(MAC, SEP, X, ...) MAC(X)P00_ROBUST SEP P00_MAP_84(MAC, SEP, __VA_ARGS__)
#define P00_MAP_86(MAC, SEP, X, ...) MAC(X)P00_ROBUST SEP P00_MAP_85(MAC, SEP, __VA_ARGS__)
#define P00_MAP_87(MAC, SEP, X, ...) MAC(X)P00_ROBUST SEP P00_MAP_86(MAC, SEP, __VA_ARGS__)
#define P00_MAP_88(MAC, SEP, X, ...) MAC(X)P00_ROBUST SEP P00_MAP_87(MAC, SEP, __VA_ARGS__)
#define P00_MAP_89(MAC, SEP, X, ...) MAC(X)P00_ROBUST SEP P00_MAP_88(MAC, SEP, __VA_ARGS__)
#define P00_MAP_90(MAC, SEP, X, ...) MAC(X)P00_ROBUST SEP P00_MAP_89(MAC, SEP, __VA_ARGS__)
#define P00_MAP_91(MAC, SEP, X, ...) MAC(X)P00_ROBUST SEP P00_MAP_90(MAC, SEP, __VA_ARGS__)
#define P00_MAP_92(MAC, SEP, X, ...) MAC(X)P00_ROBUST SEP P00_MAP_91(MAC, SEP, __VA_ARGS__)
#define P00_MAP_93(MAC, SEP, X, ...) MAC(X)P00_ROBUST SEP P00_MAP_92(MAC, SEP, __VA_ARGS__)
#define P00_MAP_94(MAC, SEP, X, ...) MAC(X)P00_ROBUST SEP P00_MAP_93(MAC, SEP, __VA_ARGS__)
#define P00_MAP_95(MAC, SEP, X, ...) MAC(X)P00_ROBUST SEP P00_MAP_94(MAC, SEP, __VA_ARGS__)
#define P00_MAP_96(MAC, SEP, X, ...) MAC(X)P00_ROBUST SEP P00_MAP_95(MAC, SEP, __VA_ARGS__)
#define P00_MAP_97(MAC, SEP, X, ...) MAC(X)P00_ROBUST SEP P00_MAP_96(MAC, SEP, __VA_ARGS__)
#define P00_MAP_98(MAC, SEP, X, ...) MAC(X)P00_ROBUST SEP P00_MAP_97(MAC, SEP, __VA_ARGS__)
#define P00_MAP_99(MAC, SEP, X, ...) MAC(X)P00_ROBUST SEP P00_MAP_98(MAC, SEP, __VA_ARGS__)
#define P00_MAP_100(MAC, SEP, X, ...) MAC(X)P00_ROBUST SEP P00_MAP_99(MAC, SEP, __VA_ARGS__)
#define P00_MAP_101(MAC, SEP, X, ...) MAC(X)P00_ROBUST SEP P00_MAP_100(MAC, SEP, __VA_ARGS__)
#define P00_MAP_102(MAC, SEP, X, ...) MAC(X)P00_ROBUST SEP P00_MAP_101(MAC, SEP, __VA_ARGS__)
#define P00_MAP_103(MAC, SEP, X, ...) MAC(X)P00_ROBUST SEP P00_MAP_102(MAC, SEP, __VA_ARGS__)
#define P00_MAP_104(MAC, SEP, X, ...) MAC(X)P00_ROBUST SEP P00_MAP_103(MAC, SEP, __VA_ARGS__)
#define P00_MAP_105(MAC, SEP, X, ...) MAC(X)P00_ROBUST SEP P00_MAP_104(MAC, SEP, __VA_ARGS__)
#define P00_MAP_106(MAC, SEP, X, ...) MAC(X)P00_ROBUST SEP P00_MAP_105(MAC, SEP, __VA_ARGS__)
#define P00_MAP_107(MAC, SEP, X, ...) MAC(X)P00_ROBUST SEP P00_MAP_106(MAC, SEP, __VA_ARGS__)
#define P00_MAP_108(MAC, SEP, X, ...) MAC(X)P00_ROBUST SEP P00_MAP_107(MAC, SEP, __VA_ARGS__)
#define P00_MAP_109(MAC, SEP, X, ...) MAC(X)P00_ROBUST SEP P00_MAP_108(MAC, SEP, __VA_ARGS__)
#define P00_MAP_110(MAC, SEP, X, ...) MAC(X)P00_ROBUST SEP P00_MAP_109(MAC, SEP, __VA_ARGS__)
#define P00_MAP_111(MAC, SEP, X, ...) MAC(X)P00_ROBUST SEP P00_MAP_110(MAC, SEP, __VA_ARGS__)
#define P00_MAP_112(MAC, SEP, X, ...) MAC(X)P00_ROBUST SEP P00_MAP_111(MAC, SEP, __VA_ARGS__)
#define P00_MAP_113(MAC, SEP, X, ...) MAC(X)P00_ROBUST SEP P00_MAP_112(MAC, SEP, __VA_ARGS__)
#define P00_MAP_114(MAC, SEP, X, ...) MAC(X)P00_ROBUST SEP P00_MAP_113(MAC, SEP, __VA_ARGS__)
#define P00_MAP_115(MAC, SEP, X, ...) MAC(X)P00_ROBUST SEP P00_MAP_114(MAC, SEP, __VA_ARGS__)
#define P00_MAP_116(MAC, SEP, X, ...) MAC(X)P00_ROBUST SEP P00_MAP_115(MAC, SEP, __VA_ARGS__)
#define P00_MAP_117(MAC, SEP, X, ...) MAC(X)P00_ROBUST SEP P00_MAP_116(MAC, SEP, __VA_ARGS__)
#define P00_MAP_118(MAC, SEP, X, ...) MAC(X)P00_ROBUST SEP P00_MAP_117(MAC, SEP, __VA_ARGS__)
#define P00_MAP_119(MAC, SEP, X, ...) MAC(X)P00_ROBUST SEP P00_MAP_118(MAC, SEP, __VA_ARGS__)
#define P00_MAP_120(MAC, SEP, X, ...) MAC(X)P00_ROBUST SEP P00_MAP_119(MAC, SEP, __VA_ARGS__)
#define P00_MAP_121(MAC, SEP, X, ...) MAC(X)P00_ROBUST SEP P00_MAP_120(MAC, SEP, __VA_ARGS__)
#define P00_MAP_122(MAC, SEP, X, ...) MAC(X)P00_ROBUST SEP P00_MAP_121(MAC, SEP, __VA_ARGS__)
#define P00_MAP_123(MAC, SEP, X, ...) MAC(X)P00_ROBUST SEP P00_MAP_122(MAC, SEP, __VA_ARGS__)
#define P00_MAP_124(MAC, SEP, X, ...) MAC(X)P00_ROBUST SEP P00_MAP_123(MAC, SEP, __VA_ARGS__)
#define P00_MAP_125(MAC, SEP, X, ...) MAC(X)P00_ROBUST SEP P00_MAP_124(MAC, SEP, __VA_ARGS__)
#define P00_MAP_126(MAC, SEP, X, ...) MAC(X)P00_ROBUST SEP P00_MAP_125(MAC, SEP, __VA_ARGS__)
#define P00_MAP_127(MAC, SEP, X, ...) MAC(X)P00_ROBUST SEP P00_MAP_126(MAC, SEP, __VA_ARGS__)
#define P00_MAP_128(MAC, SEP, X, ...) MAC(X)P00_ROBUST SEP P00_MAP_127(MAC, SEP, __VA_ARGS__)
#define P00_MAP_129(MAC, SEP, X, ...) MAC(X)P00_ROBUST SEP P00_MAP_128(MAC, SEP, __VA_ARGS__)
#define P00_MAP_130(MAC, SEP, X, ...) MAC(X)P00_ROBUST SEP P00_MAP_129(MAC, SEP, __VA_ARGS__)
#define P00_MAP_131(MAC, SEP, X, ...) MAC(X)P00_ROBUST SEP P00_MAP_130(MAC, SEP, __VA_ARGS__)
#define P00_MAP_132(MAC, SEP, X, ...) MAC(X)P00_ROBUST SEP P00_MAP_131(MAC, SEP, __VA_ARGS__)
#define P00_MAP_133(MAC, SEP, X, ...) MAC(X)P00_ROBUST SEP P00_MAP_132(MAC, SEP, __VA_ARGS__)
#define P00_MAP_134(MAC, SEP, X, ...) MAC(X)P00_ROBUST SEP P00_MAP_133(MAC, SEP, __VA_ARGS__)
#define P00_MAP_135(MAC, SEP, X, ...) MAC(X)P00_ROBUST SEP P00_MAP_134(MAC, SEP, __VA_ARGS__)
#define P00_MAP_136(MAC, SEP, X, ...) MAC(X)P00_ROBUST SEP P00_MAP_135(MAC, SEP, __VA_ARGS__)
#define P00_MAP_137(MAC, SEP, X, ...) MAC(X)P00_ROBUST SEP P00_MAP_136(MAC, SEP, __VA_ARGS__)
#define P00_MAP_138(MAC, SEP, X, ...) MAC(X)P00_ROBUST SEP P00_MAP_137(MAC, SEP, __VA_ARGS__)
#define P00_MAP_139(MAC, SEP, X, ...) MAC(X)P00_ROBUST SEP P00_MAP_138(MAC, SEP, __VA_ARGS__)
#define P00_MAP_140(MAC, SEP, X, ...) MAC(X)P00_ROBUST SEP P00_MAP_139(MAC, SEP, __VA_ARGS__)
#define P00_MAP_141(MAC, SEP, X, ...) MAC(X)P00_ROBUST SEP P00_MAP_140(MAC, SEP, __VA_ARGS__)
#define P00_MAP_142(MAC, SEP, X, ...) MAC(X)P00_ROBUST SEP P00_MAP_141(MAC, SEP, __VA_ARGS__)
#define P00_MAP_143(MAC, SEP, X, ...) MAC(X)P00_ROBUST SEP P00_MAP_142(MAC, SEP, __VA_ARGS__)
#define P00_MAP_144(MAC, SEP, X, ...) MAC(X)P00_ROBUST SEP P00_MAP_143(MAC, SEP, __VA_ARGS__)
#define P00_MAP_145(MAC, SEP, X, ...) MAC(X)P00_ROBUST SEP P00_MAP_144(MAC, SEP, __VA_ARGS__)
#define P00_MAP_146(MAC, SEP, X, ...) MAC(X)P00_ROBUST SEP P00_MAP_145(MAC, SEP, __VA_ARGS__)
#define P00_MAP_147(MAC, SEP, X, ...) MAC(X)P00_ROBUST SEP P00_MAP_146(MAC, SEP, __VA_ARGS__)
#define P00_MAP_148(MAC, SEP, X, ...) MAC(X)P00_ROBUST SEP P00_MAP_147(MAC, SEP, __VA_ARGS__)
#define P00_MAP_149(MAC, SEP, X, ...) MAC(X)P00_ROBUST SEP P00_MAP_148(MAC, SEP, __VA_ARGS__)
#define P00_MAP_150(MAC, SEP, X, ...) MAC(X)P00_ROBUST SEP P00_MAP_149(MAC, SEP, __VA_ARGS__)
#define P00_MAP_151(MAC, SEP, X, ...) MAC(X)P00_ROBUST SEP P00_MAP_150(MAC, SEP, __VA_ARGS__)
#define P00_MAP_152(MAC, SEP, X, ...) MAC(X)P00_ROBUST SEP P00_MAP_151(MAC, SEP, __VA_ARGS__)
#define P00_MAP_153(MAC, SEP, X, ...) MAC(X)P00_ROBUST SEP P00_MAP_152(MAC, SEP, __VA_ARGS__)
#define P00_MAP_154(MAC, SEP, X, ...) MAC(X)P00_ROBUST SEP P00_MAP_153(MAC, SEP, __VA_ARGS__)
#define P00_MAP_155(MAC, SEP, X, ...) MAC(X)P00_ROBUST SEP P00_MAP_154(MAC, SEP, __VA_ARGS__)
#define P00_MAP_156(MAC, SEP, X, ...) MAC(X)P00_ROBUST SEP P00_MAP_155(MAC, SEP, __VA_ARGS__)
#define P00_MAP_157(MAC, SEP, X, ...) MAC(X)P00_ROBUST SEP P00_MAP_156(MAC, SEP, __VA_ARGS__)
#define P00_MAP_158(MAC, SEP, X, ...) MAC(X)P00_ROBUST SEP P00_MAP_157(MAC, SEP, __VA_ARGS__)
#define P00_MAP_159(MAC, SEP, X, ...) MAC(X)P00_ROBUST SEP P00_MAP_158(MAC, SEP, __VA_ARGS__)
#define P00_FOR2(NAME, OP, FUNC, ...)                                                                     \
 OP(NAME, 1, P00_FOR1(NAME, OP, FUNC, P99_ALLBUTLAST(__VA_ARGS__)), FUNC(NAME, P99_LAST(__VA_ARGS__), 1))
#define P00_FOR3(NAME, OP, FUNC, ...)                                                                     \
 OP(NAME, 2, P00_FOR2(NAME, OP, FUNC, P99_ALLBUTLAST(__VA_ARGS__)), FUNC(NAME, P99_LAST(__VA_ARGS__), 2))
#define P00_FOR4(NAME, OP, FUNC, ...)                                                                     \
 OP(NAME, 3, P00_FOR3(NAME, OP, FUNC, P99_ALLBUTLAST(__VA_ARGS__)), FUNC(NAME, P99_LAST(__VA_ARGS__), 3))
#define P00_FOR5(NAME, OP, FUNC, ...)                                                                     \
 OP(NAME, 4, P00_FOR4(NAME, OP, FUNC, P99_ALLBUTLAST(__VA_ARGS__)), FUNC(NAME, P99_LAST(__VA_ARGS__), 4))
#define P00_FOR6(NAME, OP, FUNC, ...)                                                                     \
 OP(NAME, 5, P00_FOR5(NAME, OP, FUNC, P99_ALLBUTLAST(__VA_ARGS__)), FUNC(NAME, P99_LAST(__VA_ARGS__), 5))
#define P00_FOR7(NAME, OP, FUNC, ...)                                                                     \
 OP(NAME, 6, P00_FOR6(NAME, OP, FUNC, P99_ALLBUTLAST(__VA_ARGS__)), FUNC(NAME, P99_LAST(__VA_ARGS__), 6))
#define P00_FOR8(NAME, OP, FUNC, ...)                                                                     \
 OP(NAME, 7, P00_FOR7(NAME, OP, FUNC, P99_ALLBUTLAST(__VA_ARGS__)), FUNC(NAME, P99_LAST(__VA_ARGS__), 7))
#define P00_FOR9(NAME, OP, FUNC, ...)                                                                     \
 OP(NAME, 8, P00_FOR8(NAME, OP, FUNC, P99_ALLBUTLAST(__VA_ARGS__)), FUNC(NAME, P99_LAST(__VA_ARGS__), 8))
#define P00_FOR10(NAME, OP, FUNC, ...)                                                                    \
 OP(NAME, 9, P00_FOR9(NAME, OP, FUNC, P99_ALLBUTLAST(__VA_ARGS__)), FUNC(NAME, P99_LAST(__VA_ARGS__), 9))
#define P00_FOR11(NAME, OP, FUNC, ...)                                                                       \
 OP(NAME, 10, P00_FOR10(NAME, OP, FUNC, P99_ALLBUTLAST(__VA_ARGS__)), FUNC(NAME, P99_LAST(__VA_ARGS__), 10))
#define P00_FOR12(NAME, OP, FUNC, ...)                                                                       \
 OP(NAME, 11, P00_FOR11(NAME, OP, FUNC, P99_ALLBUTLAST(__VA_ARGS__)), FUNC(NAME, P99_LAST(__VA_ARGS__), 11))
#define P00_FOR13(NAME, OP, FUNC, ...)                                                                       \
 OP(NAME, 12, P00_FOR12(NAME, OP, FUNC, P99_ALLBUTLAST(__VA_ARGS__)), FUNC(NAME, P99_LAST(__VA_ARGS__), 12))
#define P00_FOR14(NAME, OP, FUNC, ...)                                                                       \
 OP(NAME, 13, P00_FOR13(NAME, OP, FUNC, P99_ALLBUTLAST(__VA_ARGS__)), FUNC(NAME, P99_LAST(__VA_ARGS__), 13))
#define P00_FOR15(NAME, OP, FUNC, ...)                                                                       \
 OP(NAME, 14, P00_FOR14(NAME, OP, FUNC, P99_ALLBUTLAST(__VA_ARGS__)), FUNC(NAME, P99_LAST(__VA_ARGS__), 14))
#define P00_FOR16(NAME, OP, FUNC, ...)                                                                       \
 OP(NAME, 15, P00_FOR15(NAME, OP, FUNC, P99_ALLBUTLAST(__VA_ARGS__)), FUNC(NAME, P99_LAST(__VA_ARGS__), 15))
#define P00_FOR17(NAME, OP, FUNC, ...)                                                                       \
 OP(NAME, 16, P00_FOR16(NAME, OP, FUNC, P99_ALLBUTLAST(__VA_ARGS__)), FUNC(NAME, P99_LAST(__VA_ARGS__), 16))
#define P00_FOR18(NAME, OP, FUNC, ...)                                                                       \
 OP(NAME, 17, P00_FOR17(NAME, OP, FUNC, P99_ALLBUTLAST(__VA_ARGS__)), FUNC(NAME, P99_LAST(__VA_ARGS__), 17))
#define P00_FOR19(NAME, OP, FUNC, ...)                                                                       \
 OP(NAME, 18, P00_FOR18(NAME, OP, FUNC, P99_ALLBUTLAST(__VA_ARGS__)), FUNC(NAME, P99_LAST(__VA_ARGS__), 18))
#define P00_FOR20(NAME, OP, FUNC, ...)                                                                       \
 OP(NAME, 19, P00_FOR19(NAME, OP, FUNC, P99_ALLBUTLAST(__VA_ARGS__)), FUNC(NAME, P99_LAST(__VA_ARGS__), 19))
#define P00_FOR21(NAME, OP, FUNC, ...)                                                                       \
 OP(NAME, 20, P00_FOR20(NAME, OP, FUNC, P99_ALLBUTLAST(__VA_ARGS__)), FUNC(NAME, P99_LAST(__VA_ARGS__), 20))
#define P00_FOR22(NAME, OP, FUNC, ...)                                                                       \
 OP(NAME, 21, P00_FOR21(NAME, OP, FUNC, P99_ALLBUTLAST(__VA_ARGS__)), FUNC(NAME, P99_LAST(__VA_ARGS__), 21))
#define P00_FOR23(NAME, OP, FUNC, ...)                                                                       \
 OP(NAME, 22, P00_FOR22(NAME, OP, FUNC, P99_ALLBUTLAST(__VA_ARGS__)), FUNC(NAME, P99_LAST(__VA_ARGS__), 22))
#define P00_FOR24(NAME, OP, FUNC, ...)                                                                       \
 OP(NAME, 23, P00_FOR23(NAME, OP, FUNC, P99_ALLBUTLAST(__VA_ARGS__)), FUNC(NAME, P99_LAST(__VA_ARGS__), 23))
#define P00_FOR25(NAME, OP, FUNC, ...)                                                                       \
 OP(NAME, 24, P00_FOR24(NAME, OP, FUNC, P99_ALLBUTLAST(__VA_ARGS__)), FUNC(NAME, P99_LAST(__VA_ARGS__), 24))
#define P00_FOR26(NAME, OP, FUNC, ...)                                                                       \
 OP(NAME, 25, P00_FOR25(NAME, OP, FUNC, P99_ALLBUTLAST(__VA_ARGS__)), FUNC(NAME, P99_LAST(__VA_ARGS__), 25))
#define P00_FOR27(NAME, OP, FUNC, ...)                                                                       \
 OP(NAME, 26, P00_FOR26(NAME, OP, FUNC, P99_ALLBUTLAST(__VA_ARGS__)), FUNC(NAME, P99_LAST(__VA_ARGS__), 26))
#define P00_FOR28(NAME, OP, FUNC, ...)                                                                       \
 OP(NAME, 27, P00_FOR27(NAME, OP, FUNC, P99_ALLBUTLAST(__VA_ARGS__)), FUNC(NAME, P99_LAST(__VA_ARGS__), 27))
#define P00_FOR29(NAME, OP, FUNC, ...)                                                                       \
 OP(NAME, 28, P00_FOR28(NAME, OP, FUNC, P99_ALLBUTLAST(__VA_ARGS__)), FUNC(NAME, P99_LAST(__VA_ARGS__), 28))
#define P00_FOR30(NAME, OP, FUNC, ...)                                                                       \
 OP(NAME, 29, P00_FOR29(NAME, OP, FUNC, P99_ALLBUTLAST(__VA_ARGS__)), FUNC(NAME, P99_LAST(__VA_ARGS__), 29))
#define P00_FOR31(NAME, OP, FUNC, ...)                                                                       \
 OP(NAME, 30, P00_FOR30(NAME, OP, FUNC, P99_ALLBUTLAST(__VA_ARGS__)), FUNC(NAME, P99_LAST(__VA_ARGS__), 30))
#define P00_FOR32(NAME, OP, FUNC, ...)                                                                       \
 OP(NAME, 31, P00_FOR31(NAME, OP, FUNC, P99_ALLBUTLAST(__VA_ARGS__)), FUNC(NAME, P99_LAST(__VA_ARGS__), 31))
#define P00_FOR33(NAME, OP, FUNC, ...)                                                                       \
 OP(NAME, 32, P00_FOR32(NAME, OP, FUNC, P99_ALLBUTLAST(__VA_ARGS__)), FUNC(NAME, P99_LAST(__VA_ARGS__), 32))
#define P00_FOR34(NAME, OP, FUNC, ...)                                                                       \
 OP(NAME, 33, P00_FOR33(NAME, OP, FUNC, P99_ALLBUTLAST(__VA_ARGS__)), FUNC(NAME, P99_LAST(__VA_ARGS__), 33))
#define P00_FOR35(NAME, OP, FUNC, ...)                                                                       \
 OP(NAME, 34, P00_FOR34(NAME, OP, FUNC, P99_ALLBUTLAST(__VA_ARGS__)), FUNC(NAME, P99_LAST(__VA_ARGS__), 34))
#define P00_FOR36(NAME, OP, FUNC, ...)                                                                       \
 OP(NAME, 35, P00_FOR35(NAME, OP, FUNC, P99_ALLBUTLAST(__VA_ARGS__)), FUNC(NAME, P99_LAST(__VA_ARGS__), 35))
#define P00_FOR37(NAME, OP, FUNC, ...)                                                                       \
 OP(NAME, 36, P00_FOR36(NAME, OP, FUNC, P99_ALLBUTLAST(__VA_ARGS__)), FUNC(NAME, P99_LAST(__VA_ARGS__), 36))
#define P00_FOR38(NAME, OP, FUNC, ...)                                                                       \
 OP(NAME, 37, P00_FOR37(NAME, OP, FUNC, P99_ALLBUTLAST(__VA_ARGS__)), FUNC(NAME, P99_LAST(__VA_ARGS__), 37))
#define P00_FOR39(NAME, OP, FUNC, ...)                                                                       \
 OP(NAME, 38, P00_FOR38(NAME, OP, FUNC, P99_ALLBUTLAST(__VA_ARGS__)), FUNC(NAME, P99_LAST(__VA_ARGS__), 38))
#define P00_FOR40(NAME, OP, FUNC, ...)                                                                       \
 OP(NAME, 39, P00_FOR39(NAME, OP, FUNC, P99_ALLBUTLAST(__VA_ARGS__)), FUNC(NAME, P99_LAST(__VA_ARGS__), 39))
#define P00_FOR41(NAME, OP, FUNC, ...)                                                                       \
 OP(NAME, 40, P00_FOR40(NAME, OP, FUNC, P99_ALLBUTLAST(__VA_ARGS__)), FUNC(NAME, P99_LAST(__VA_ARGS__), 40))
#define P00_FOR42(NAME, OP, FUNC, ...)                                                                       \
 OP(NAME, 41, P00_FOR41(NAME, OP, FUNC, P99_ALLBUTLAST(__VA_ARGS__)), FUNC(NAME, P99_LAST(__VA_ARGS__), 41))
#define P00_FOR43(NAME, OP, FUNC, ...)                                                                       \
 OP(NAME, 42, P00_FOR42(NAME, OP, FUNC, P99_ALLBUTLAST(__VA_ARGS__)), FUNC(NAME, P99_LAST(__VA_ARGS__), 42))
#define P00_FOR44(NAME, OP, FUNC, ...)                                                                       \
 OP(NAME, 43, P00_FOR43(NAME, OP, FUNC, P99_ALLBUTLAST(__VA_ARGS__)), FUNC(NAME, P99_LAST(__VA_ARGS__), 43))
#define P00_FOR45(NAME, OP, FUNC, ...)                                                                       \
 OP(NAME, 44, P00_FOR44(NAME, OP, FUNC, P99_ALLBUTLAST(__VA_ARGS__)), FUNC(NAME, P99_LAST(__VA_ARGS__), 44))
#define P00_FOR46(NAME, OP, FUNC, ...)                                                                       \
 OP(NAME, 45, P00_FOR45(NAME, OP, FUNC, P99_ALLBUTLAST(__VA_ARGS__)), FUNC(NAME, P99_LAST(__VA_ARGS__), 45))
#define P00_FOR47(NAME, OP, FUNC, ...)                                                                       \
 OP(NAME, 46, P00_FOR46(NAME, OP, FUNC, P99_ALLBUTLAST(__VA_ARGS__)), FUNC(NAME, P99_LAST(__VA_ARGS__), 46))
#define P00_FOR48(NAME, OP, FUNC, ...)                                                                       \
 OP(NAME, 47, P00_FOR47(NAME, OP, FUNC, P99_ALLBUTLAST(__VA_ARGS__)), FUNC(NAME, P99_LAST(__VA_ARGS__), 47))
#define P00_FOR49(NAME, OP, FUNC, ...)                                                                       \
 OP(NAME, 48, P00_FOR48(NAME, OP, FUNC, P99_ALLBUTLAST(__VA_ARGS__)), FUNC(NAME, P99_LAST(__VA_ARGS__), 48))
#define P00_FOR50(NAME, OP, FUNC, ...)                                                                       \
 OP(NAME, 49, P00_FOR49(NAME, OP, FUNC, P99_ALLBUTLAST(__VA_ARGS__)), FUNC(NAME, P99_LAST(__VA_ARGS__), 49))
#define P00_FOR51(NAME, OP, FUNC, ...)                                                                       \
 OP(NAME, 50, P00_FOR50(NAME, OP, FUNC, P99_ALLBUTLAST(__VA_ARGS__)), FUNC(NAME, P99_LAST(__VA_ARGS__), 50))
#define P00_FOR52(NAME, OP, FUNC, ...)                                                                       \
 OP(NAME, 51, P00_FOR51(NAME, OP, FUNC, P99_ALLBUTLAST(__VA_ARGS__)), FUNC(NAME, P99_LAST(__VA_ARGS__), 51))
#define P00_FOR53(NAME, OP, FUNC, ...)                                                                       \
 OP(NAME, 52, P00_FOR52(NAME, OP, FUNC, P99_ALLBUTLAST(__VA_ARGS__)), FUNC(NAME, P99_LAST(__VA_ARGS__), 52))
#define P00_FOR54(NAME, OP, FUNC, ...)                                                                       \
 OP(NAME, 53, P00_FOR53(NAME, OP, FUNC, P99_ALLBUTLAST(__VA_ARGS__)), FUNC(NAME, P99_LAST(__VA_ARGS__), 53))
#define P00_FOR55(NAME, OP, FUNC, ...)                                                                       \
 OP(NAME, 54, P00_FOR54(NAME, OP, FUNC, P99_ALLBUTLAST(__VA_ARGS__)), FUNC(NAME, P99_LAST(__VA_ARGS__), 54))
#define P00_FOR56(NAME, OP, FUNC, ...)                                                                       \
 OP(NAME, 55, P00_FOR55(NAME, OP, FUNC, P99_ALLBUTLAST(__VA_ARGS__)), FUNC(NAME, P99_LAST(__VA_ARGS__), 55))
#define P00_FOR57(NAME, OP, FUNC, ...)                                                                       \
 OP(NAME, 56, P00_FOR56(NAME, OP, FUNC, P99_ALLBUTLAST(__VA_ARGS__)), FUNC(NAME, P99_LAST(__VA_ARGS__), 56))
#define P00_FOR58(NAME, OP, FUNC, ...)                                                                       \
 OP(NAME, 57, P00_FOR57(NAME, OP, FUNC, P99_ALLBUTLAST(__VA_ARGS__)), FUNC(NAME, P99_LAST(__VA_ARGS__), 57))
#define P00_FOR59(NAME, OP, FUNC, ...)                                                                       \
 OP(NAME, 58, P00_FOR58(NAME, OP, FUNC, P99_ALLBUTLAST(__VA_ARGS__)), FUNC(NAME, P99_LAST(__VA_ARGS__), 58))
#define P00_FOR60(NAME, OP, FUNC, ...)                                                                       \
 OP(NAME, 59, P00_FOR59(NAME, OP, FUNC, P99_ALLBUTLAST(__VA_ARGS__)), FUNC(NAME, P99_LAST(__VA_ARGS__), 59))
#define P00_FOR61(NAME, OP, FUNC, ...)                                                                       \
 OP(NAME, 60, P00_FOR60(NAME, OP, FUNC, P99_ALLBUTLAST(__VA_ARGS__)), FUNC(NAME, P99_LAST(__VA_ARGS__), 60))
#define P00_FOR62(NAME, OP, FUNC, ...)                                                                       \
 OP(NAME, 61, P00_FOR61(NAME, OP, FUNC, P99_ALLBUTLAST(__VA_ARGS__)), FUNC(NAME, P99_LAST(__VA_ARGS__), 61))
#define P00_FOR63(NAME, OP, FUNC, ...)                                                                       \
 OP(NAME, 62, P00_FOR62(NAME, OP, FUNC, P99_ALLBUTLAST(__VA_ARGS__)), FUNC(NAME, P99_LAST(__VA_ARGS__), 62))
#define P00_FOR64(NAME, OP, FUNC, ...)                                                                       \
 OP(NAME, 63, P00_FOR63(NAME, OP, FUNC, P99_ALLBUTLAST(__VA_ARGS__)), FUNC(NAME, P99_LAST(__VA_ARGS__), 63))
#define P00_FOR65(NAME, OP, FUNC, ...)                                                                       \
 OP(NAME, 64, P00_FOR64(NAME, OP, FUNC, P99_ALLBUTLAST(__VA_ARGS__)), FUNC(NAME, P99_LAST(__VA_ARGS__), 64))
#define P00_FOR66(NAME, OP, FUNC, ...)                                                                       \
 OP(NAME, 65, P00_FOR65(NAME, OP, FUNC, P99_ALLBUTLAST(__VA_ARGS__)), FUNC(NAME, P99_LAST(__VA_ARGS__), 65))
#define P00_FOR67(NAME, OP, FUNC, ...)                                                                       \
 OP(NAME, 66, P00_FOR66(NAME, OP, FUNC, P99_ALLBUTLAST(__VA_ARGS__)), FUNC(NAME, P99_LAST(__VA_ARGS__), 66))
#define P00_FOR68(NAME, OP, FUNC, ...)                                                                       \
 OP(NAME, 67, P00_FOR67(NAME, OP, FUNC, P99_ALLBUTLAST(__VA_ARGS__)), FUNC(NAME, P99_LAST(__VA_ARGS__), 67))
#define P00_FOR69(NAME, OP, FUNC, ...)                                                                       \
 OP(NAME, 68, P00_FOR68(NAME, OP, FUNC, P99_ALLBUTLAST(__VA_ARGS__)), FUNC(NAME, P99_LAST(__VA_ARGS__), 68))
#define P00_FOR70(NAME, OP, FUNC, ...)                                                                       \
 OP(NAME, 69, P00_FOR69(NAME, OP, FUNC, P99_ALLBUTLAST(__VA_ARGS__)), FUNC(NAME, P99_LAST(__VA_ARGS__), 69))
#define P00_FOR71(NAME, OP, FUNC, ...)                                                                       \
 OP(NAME, 70, P00_FOR70(NAME, OP, FUNC, P99_ALLBUTLAST(__VA_ARGS__)), FUNC(NAME, P99_LAST(__VA_ARGS__), 70))
#define P00_FOR72(NAME, OP, FUNC, ...)                                                                       \
 OP(NAME, 71, P00_FOR71(NAME, OP, FUNC, P99_ALLBUTLAST(__VA_ARGS__)), FUNC(NAME, P99_LAST(__VA_ARGS__), 71))
#define P00_FOR73(NAME, OP, FUNC, ...)                                                                       \
 OP(NAME, 72, P00_FOR72(NAME, OP, FUNC, P99_ALLBUTLAST(__VA_ARGS__)), FUNC(NAME, P99_LAST(__VA_ARGS__), 72))
#define P00_FOR74(NAME, OP, FUNC, ...)                                                                       \
 OP(NAME, 73, P00_FOR73(NAME, OP, FUNC, P99_ALLBUTLAST(__VA_ARGS__)), FUNC(NAME, P99_LAST(__VA_ARGS__), 73))
#define P00_FOR75(NAME, OP, FUNC, ...)                                                                       \
 OP(NAME, 74, P00_FOR74(NAME, OP, FUNC, P99_ALLBUTLAST(__VA_ARGS__)), FUNC(NAME, P99_LAST(__VA_ARGS__), 74))
#define P00_FOR76(NAME, OP, FUNC, ...)                                                                       \
 OP(NAME, 75, P00_FOR75(NAME, OP, FUNC, P99_ALLBUTLAST(__VA_ARGS__)), FUNC(NAME, P99_LAST(__VA_ARGS__), 75))
#define P00_FOR77(NAME, OP, FUNC, ...)                                                                       \
 OP(NAME, 76, P00_FOR76(NAME, OP, FUNC, P99_ALLBUTLAST(__VA_ARGS__)), FUNC(NAME, P99_LAST(__VA_ARGS__), 76))
#define P00_FOR78(NAME, OP, FUNC, ...)                                                                       \
 OP(NAME, 77, P00_FOR77(NAME, OP, FUNC, P99_ALLBUTLAST(__VA_ARGS__)), FUNC(NAME, P99_LAST(__VA_ARGS__), 77))
#define P00_FOR79(NAME, OP, FUNC, ...)                                                                       \
 OP(NAME, 78, P00_FOR78(NAME, OP, FUNC, P99_ALLBUTLAST(__VA_ARGS__)), FUNC(NAME, P99_LAST(__VA_ARGS__), 78))
#define P00_FOR80(NAME, OP, FUNC, ...)                                                                       \
 OP(NAME, 79, P00_FOR79(NAME, OP, FUNC, P99_ALLBUTLAST(__VA_ARGS__)), FUNC(NAME, P99_LAST(__VA_ARGS__), 79))
#define P00_FOR81(NAME, OP, FUNC, ...)                                                                       \
 OP(NAME, 80, P00_FOR80(NAME, OP, FUNC, P99_ALLBUTLAST(__VA_ARGS__)), FUNC(NAME, P99_LAST(__VA_ARGS__), 80))
#define P00_FOR82(NAME, OP, FUNC, ...)                                                                       \
 OP(NAME, 81, P00_FOR81(NAME, OP, FUNC, P99_ALLBUTLAST(__VA_ARGS__)), FUNC(NAME, P99_LAST(__VA_ARGS__), 81))
#define P00_FOR83(NAME, OP, FUNC, ...)                                                                       \
 OP(NAME, 82, P00_FOR82(NAME, OP, FUNC, P99_ALLBUTLAST(__VA_ARGS__)), FUNC(NAME, P99_LAST(__VA_ARGS__), 82))
#define P00_FOR84(NAME, OP, FUNC, ...)                                                                       \
 OP(NAME, 83, P00_FOR83(NAME, OP, FUNC, P99_ALLBUTLAST(__VA_ARGS__)), FUNC(NAME, P99_LAST(__VA_ARGS__), 83))
#define P00_FOR85(NAME, OP, FUNC, ...)                                                                       \
 OP(NAME, 84, P00_FOR84(NAME, OP, FUNC, P99_ALLBUTLAST(__VA_ARGS__)), FUNC(NAME, P99_LAST(__VA_ARGS__), 84))
#define P00_FOR86(NAME, OP, FUNC, ...)                                                                       \
 OP(NAME, 85, P00_FOR85(NAME, OP, FUNC, P99_ALLBUTLAST(__VA_ARGS__)), FUNC(NAME, P99_LAST(__VA_ARGS__), 85))
#define P00_FOR87(NAME, OP, FUNC, ...)                                                                       \
 OP(NAME, 86, P00_FOR86(NAME, OP, FUNC, P99_ALLBUTLAST(__VA_ARGS__)), FUNC(NAME, P99_LAST(__VA_ARGS__), 86))
#define P00_FOR88(NAME, OP, FUNC, ...)                                                                       \
 OP(NAME, 87, P00_FOR87(NAME, OP, FUNC, P99_ALLBUTLAST(__VA_ARGS__)), FUNC(NAME, P99_LAST(__VA_ARGS__), 87))
#define P00_FOR89(NAME, OP, FUNC, ...)                                                                       \
 OP(NAME, 88, P00_FOR88(NAME, OP, FUNC, P99_ALLBUTLAST(__VA_ARGS__)), FUNC(NAME, P99_LAST(__VA_ARGS__), 88))
#define P00_FOR90(NAME, OP, FUNC, ...)                                                                       \
 OP(NAME, 89, P00_FOR89(NAME, OP, FUNC, P99_ALLBUTLAST(__VA_ARGS__)), FUNC(NAME, P99_LAST(__VA_ARGS__), 89))
#define P00_FOR91(NAME, OP, FUNC, ...)                                                                       \
 OP(NAME, 90, P00_FOR90(NAME, OP, FUNC, P99_ALLBUTLAST(__VA_ARGS__)), FUNC(NAME, P99_LAST(__VA_ARGS__), 90))
#define P00_FOR92(NAME, OP, FUNC, ...)                                                                       \
 OP(NAME, 91, P00_FOR91(NAME, OP, FUNC, P99_ALLBUTLAST(__VA_ARGS__)), FUNC(NAME, P99_LAST(__VA_ARGS__), 91))
#define P00_FOR93(NAME, OP, FUNC, ...)                                                                       \
 OP(NAME, 92, P00_FOR92(NAME, OP, FUNC, P99_ALLBUTLAST(__VA_ARGS__)), FUNC(NAME, P99_LAST(__VA_ARGS__), 92))
#define P00_FOR94(NAME, OP, FUNC, ...)                                                                       \
 OP(NAME, 93, P00_FOR93(NAME, OP, FUNC, P99_ALLBUTLAST(__VA_ARGS__)), FUNC(NAME, P99_LAST(__VA_ARGS__), 93))
#define P00_FOR95(NAME, OP, FUNC, ...)                                                                       \
 OP(NAME, 94, P00_FOR94(NAME, OP, FUNC, P99_ALLBUTLAST(__VA_ARGS__)), FUNC(NAME, P99_LAST(__VA_ARGS__), 94))
#define P00_FOR96(NAME, OP, FUNC, ...)                                                                       \
 OP(NAME, 95, P00_FOR95(NAME, OP, FUNC, P99_ALLBUTLAST(__VA_ARGS__)), FUNC(NAME, P99_LAST(__VA_ARGS__), 95))
#define P00_FOR97(NAME, OP, FUNC, ...)                                                                       \
 OP(NAME, 96, P00_FOR96(NAME, OP, FUNC, P99_ALLBUTLAST(__VA_ARGS__)), FUNC(NAME, P99_LAST(__VA_ARGS__), 96))
#define P00_FOR98(NAME, OP, FUNC, ...)                                                                       \
 OP(NAME, 97, P00_FOR97(NAME, OP, FUNC, P99_ALLBUTLAST(__VA_ARGS__)), FUNC(NAME, P99_LAST(__VA_ARGS__), 97))
#define P00_FOR99(NAME, OP, FUNC, ...)                                                                       \
 OP(NAME, 98, P00_FOR98(NAME, OP, FUNC, P99_ALLBUTLAST(__VA_ARGS__)), FUNC(NAME, P99_LAST(__VA_ARGS__), 98))
#define P00_FOR100(NAME, OP, FUNC, ...)                                                                      \
 OP(NAME, 99, P00_FOR99(NAME, OP, FUNC, P99_ALLBUTLAST(__VA_ARGS__)), FUNC(NAME, P99_LAST(__VA_ARGS__), 99))
#define P00_FOR101(NAME, OP, FUNC, ...)                                                                         \
 OP(NAME, 100, P00_FOR100(NAME, OP, FUNC, P99_ALLBUTLAST(__VA_ARGS__)), FUNC(NAME, P99_LAST(__VA_ARGS__), 100))
#define P00_FOR102(NAME, OP, FUNC, ...)                                                                         \
 OP(NAME, 101, P00_FOR101(NAME, OP, FUNC, P99_ALLBUTLAST(__VA_ARGS__)), FUNC(NAME, P99_LAST(__VA_ARGS__), 101))
#define P00_FOR103(NAME, OP, FUNC, ...)                                                                         \
 OP(NAME, 102, P00_FOR102(NAME, OP, FUNC, P99_ALLBUTLAST(__VA_ARGS__)), FUNC(NAME, P99_LAST(__VA_ARGS__), 102))
#define P00_FOR104(NAME, OP, FUNC, ...)                                                                         \
 OP(NAME, 103, P00_FOR103(NAME, OP, FUNC, P99_ALLBUTLAST(__VA_ARGS__)), FUNC(NAME, P99_LAST(__VA_ARGS__), 103))
#define P00_FOR105(NAME, OP, FUNC, ...)                                                                         \
 OP(NAME, 104, P00_FOR104(NAME, OP, FUNC, P99_ALLBUTLAST(__VA_ARGS__)), FUNC(NAME, P99_LAST(__VA_ARGS__), 104))
#define P00_FOR106(NAME, OP, FUNC, ...)                                                                         \
 OP(NAME, 105, P00_FOR105(NAME, OP, FUNC, P99_ALLBUTLAST(__VA_ARGS__)), FUNC(NAME, P99_LAST(__VA_ARGS__), 105))
#define P00_FOR107(NAME, OP, FUNC, ...)                                                                         \
 OP(NAME, 106, P00_FOR106(NAME, OP, FUNC, P99_ALLBUTLAST(__VA_ARGS__)), FUNC(NAME, P99_LAST(__VA_ARGS__), 106))
#define P00_FOR108(NAME, OP, FUNC, ...)                                                                         \
 OP(NAME, 107, P00_FOR107(NAME, OP, FUNC, P99_ALLBUTLAST(__VA_ARGS__)), FUNC(NAME, P99_LAST(__VA_ARGS__), 107))
#define P00_FOR109(NAME, OP, FUNC, ...)                                                                         \
 OP(NAME, 108, P00_FOR108(NAME, OP, FUNC, P99_ALLBUTLAST(__VA_ARGS__)), FUNC(NAME, P99_LAST(__VA_ARGS__), 108))
#define P00_FOR110(NAME, OP, FUNC, ...)                                                                         \
 OP(NAME, 109, P00_FOR109(NAME, OP, FUNC, P99_ALLBUTLAST(__VA_ARGS__)), FUNC(NAME, P99_LAST(__VA_ARGS__), 109))
#define P00_FOR111(NAME, OP, FUNC, ...)                                                                         \
 OP(NAME, 110, P00_FOR110(NAME, OP, FUNC, P99_ALLBUTLAST(__VA_ARGS__)), FUNC(NAME, P99_LAST(__VA_ARGS__), 110))
#define P00_FOR112(NAME, OP, FUNC, ...)                                                                         \
 OP(NAME, 111, P00_FOR111(NAME, OP, FUNC, P99_ALLBUTLAST(__VA_ARGS__)), FUNC(NAME, P99_LAST(__VA_ARGS__), 111))
#define P00_FOR113(NAME, OP, FUNC, ...)                                                                         \
 OP(NAME, 112, P00_FOR112(NAME, OP, FUNC, P99_ALLBUTLAST(__VA_ARGS__)), FUNC(NAME, P99_LAST(__VA_ARGS__), 112))
#define P00_FOR114(NAME, OP, FUNC, ...)                                                                         \
 OP(NAME, 113, P00_FOR113(NAME, OP, FUNC, P99_ALLBUTLAST(__VA_ARGS__)), FUNC(NAME, P99_LAST(__VA_ARGS__), 113))
#define P00_FOR115(NAME, OP, FUNC, ...)                                                                         \
 OP(NAME, 114, P00_FOR114(NAME, OP, FUNC, P99_ALLBUTLAST(__VA_ARGS__)), FUNC(NAME, P99_LAST(__VA_ARGS__), 114))
#define P00_FOR116(NAME, OP, FUNC, ...)                                                                         \
 OP(NAME, 115, P00_FOR115(NAME, OP, FUNC, P99_ALLBUTLAST(__VA_ARGS__)), FUNC(NAME, P99_LAST(__VA_ARGS__), 115))
#define P00_FOR117(NAME, OP, FUNC, ...)                                                                         \
 OP(NAME, 116, P00_FOR116(NAME, OP, FUNC, P99_ALLBUTLAST(__VA_ARGS__)), FUNC(NAME, P99_LAST(__VA_ARGS__), 116))
#define P00_FOR118(NAME, OP, FUNC, ...)                                                                         \
 OP(NAME, 117, P00_FOR117(NAME, OP, FUNC, P99_ALLBUTLAST(__VA_ARGS__)), FUNC(NAME, P99_LAST(__VA_ARGS__), 117))
#define P00_FOR119(NAME, OP, FUNC, ...)                                                                         \
 OP(NAME, 118, P00_FOR118(NAME, OP, FUNC, P99_ALLBUTLAST(__VA_ARGS__)), FUNC(NAME, P99_LAST(__VA_ARGS__), 118))
#define P00_FOR120(NAME, OP, FUNC, ...)                                                                         \
 OP(NAME, 119, P00_FOR119(NAME, OP, FUNC, P99_ALLBUTLAST(__VA_ARGS__)), FUNC(NAME, P99_LAST(__VA_ARGS__), 119))
#define P00_FOR121(NAME, OP, FUNC, ...)                                                                         \
 OP(NAME, 120, P00_FOR120(NAME, OP, FUNC, P99_ALLBUTLAST(__VA_ARGS__)), FUNC(NAME, P99_LAST(__VA_ARGS__), 120))
#define P00_FOR122(NAME, OP, FUNC, ...)                                                                         \
 OP(NAME, 121, P00_FOR121(NAME, OP, FUNC, P99_ALLBUTLAST(__VA_ARGS__)), FUNC(NAME, P99_LAST(__VA_ARGS__), 121))
#define P00_FOR123(NAME, OP, FUNC, ...)                                                                         \
 OP(NAME, 122, P00_FOR122(NAME, OP, FUNC, P99_ALLBUTLAST(__VA_ARGS__)), FUNC(NAME, P99_LAST(__VA_ARGS__), 122))
#define P00_FOR124(NAME, OP, FUNC, ...)                                                                         \
 OP(NAME, 123, P00_FOR123(NAME, OP, FUNC, P99_ALLBUTLAST(__VA_ARGS__)), FUNC(NAME, P99_LAST(__VA_ARGS__), 123))
#define P00_FOR125(NAME, OP, FUNC, ...)                                                                         \
 OP(NAME, 124, P00_FOR124(NAME, OP, FUNC, P99_ALLBUTLAST(__VA_ARGS__)), FUNC(NAME, P99_LAST(__VA_ARGS__), 124))
#define P00_FOR126(NAME, OP, FUNC, ...)                                                                         \
 OP(NAME, 125, P00_FOR125(NAME, OP, FUNC, P99_ALLBUTLAST(__VA_ARGS__)), FUNC(NAME, P99_LAST(__VA_ARGS__), 125))
#define P00_FOR127(NAME, OP, FUNC, ...)                                                                         \
 OP(NAME, 126, P00_FOR126(NAME, OP, FUNC, P99_ALLBUTLAST(__VA_ARGS__)), FUNC(NAME, P99_LAST(__VA_ARGS__), 126))
#define P00_FOR128(NAME, OP, FUNC, ...)                                                                         \
 OP(NAME, 127, P00_FOR127(NAME, OP, FUNC, P99_ALLBUTLAST(__VA_ARGS__)), FUNC(NAME, P99_LAST(__VA_ARGS__), 127))
#define P00_FOR129(NAME, OP, FUNC, ...)                                                                         \
 OP(NAME, 128, P00_FOR128(NAME, OP, FUNC, P99_ALLBUTLAST(__VA_ARGS__)), FUNC(NAME, P99_LAST(__VA_ARGS__), 128))
#define P00_FOR130(NAME, OP, FUNC, ...)                                                                         \
 OP(NAME, 129, P00_FOR129(NAME, OP, FUNC, P99_ALLBUTLAST(__VA_ARGS__)), FUNC(NAME, P99_LAST(__VA_ARGS__), 129))
#define P00_FOR131(NAME, OP, FUNC, ...)                                                                         \
 OP(NAME, 130, P00_FOR130(NAME, OP, FUNC, P99_ALLBUTLAST(__VA_ARGS__)), FUNC(NAME, P99_LAST(__VA_ARGS__), 130))
#define P00_FOR132(NAME, OP, FUNC, ...)                                                                         \
 OP(NAME, 131, P00_FOR131(NAME, OP, FUNC, P99_ALLBUTLAST(__VA_ARGS__)), FUNC(NAME, P99_LAST(__VA_ARGS__), 131))
#define P00_FOR133(NAME, OP, FUNC, ...)                                                                         \
 OP(NAME, 132, P00_FOR132(NAME, OP, FUNC, P99_ALLBUTLAST(__VA_ARGS__)), FUNC(NAME, P99_LAST(__VA_ARGS__), 132))
#define P00_FOR134(NAME, OP, FUNC, ...)                                                                         \
 OP(NAME, 133, P00_FOR133(NAME, OP, FUNC, P99_ALLBUTLAST(__VA_ARGS__)), FUNC(NAME, P99_LAST(__VA_ARGS__), 133))
#define P00_FOR135(NAME, OP, FUNC, ...)                                                                         \
 OP(NAME, 134, P00_FOR134(NAME, OP, FUNC, P99_ALLBUTLAST(__VA_ARGS__)), FUNC(NAME, P99_LAST(__VA_ARGS__), 134))
#define P00_FOR136(NAME, OP, FUNC, ...)                                                                         \
 OP(NAME, 135, P00_FOR135(NAME, OP, FUNC, P99_ALLBUTLAST(__VA_ARGS__)), FUNC(NAME, P99_LAST(__VA_ARGS__), 135))
#define P00_FOR137(NAME, OP, FUNC, ...)                                                                         \
 OP(NAME, 136, P00_FOR136(NAME, OP, FUNC, P99_ALLBUTLAST(__VA_ARGS__)), FUNC(NAME, P99_LAST(__VA_ARGS__), 136))
#define P00_FOR138(NAME, OP, FUNC, ...)                                                                         \
 OP(NAME, 137, P00_FOR137(NAME, OP, FUNC, P99_ALLBUTLAST(__VA_ARGS__)), FUNC(NAME, P99_LAST(__VA_ARGS__), 137))
#define P00_FOR139(NAME, OP, FUNC, ...)                                                                         \
 OP(NAME, 138, P00_FOR138(NAME, OP, FUNC, P99_ALLBUTLAST(__VA_ARGS__)), FUNC(NAME, P99_LAST(__VA_ARGS__), 138))
#define P00_FOR140(NAME, OP, FUNC, ...)                                                                         \
 OP(NAME, 139, P00_FOR139(NAME, OP, FUNC, P99_ALLBUTLAST(__VA_ARGS__)), FUNC(NAME, P99_LAST(__VA_ARGS__), 139))
#define P00_FOR141(NAME, OP, FUNC, ...)                                                                         \
 OP(NAME, 140, P00_FOR140(NAME, OP, FUNC, P99_ALLBUTLAST(__VA_ARGS__)), FUNC(NAME, P99_LAST(__VA_ARGS__), 140))
#define P00_FOR142(NAME, OP, FUNC, ...)                                                                         \
 OP(NAME, 141, P00_FOR141(NAME, OP, FUNC, P99_ALLBUTLAST(__VA_ARGS__)), FUNC(NAME, P99_LAST(__VA_ARGS__), 141))
#define P00_FOR143(NAME, OP, FUNC, ...)                                                                         \
 OP(NAME, 142, P00_FOR142(NAME, OP, FUNC, P99_ALLBUTLAST(__VA_ARGS__)), FUNC(NAME, P99_LAST(__VA_ARGS__), 142))
#define P00_FOR144(NAME, OP, FUNC, ...)                                                                         \
 OP(NAME, 143, P00_FOR143(NAME, OP, FUNC, P99_ALLBUTLAST(__VA_ARGS__)), FUNC(NAME, P99_LAST(__VA_ARGS__), 143))
#define P00_FOR145(NAME, OP, FUNC, ...)                                                                         \
 OP(NAME, 144, P00_FOR144(NAME, OP, FUNC, P99_ALLBUTLAST(__VA_ARGS__)), FUNC(NAME, P99_LAST(__VA_ARGS__), 144))
#define P00_FOR146(NAME, OP, FUNC, ...)                                                                         \
 OP(NAME, 145, P00_FOR145(NAME, OP, FUNC, P99_ALLBUTLAST(__VA_ARGS__)), FUNC(NAME, P99_LAST(__VA_ARGS__), 145))
#define P00_FOR147(NAME, OP, FUNC, ...)                                                                         \
 OP(NAME, 146, P00_FOR146(NAME, OP, FUNC, P99_ALLBUTLAST(__VA_ARGS__)), FUNC(NAME, P99_LAST(__VA_ARGS__), 146))
#define P00_FOR148(NAME, OP, FUNC, ...)                                                                         \
 OP(NAME, 147, P00_FOR147(NAME, OP, FUNC, P99_ALLBUTLAST(__VA_ARGS__)), FUNC(NAME, P99_LAST(__VA_ARGS__), 147))
#define P00_FOR149(NAME, OP, FUNC, ...)                                                                         \
 OP(NAME, 148, P00_FOR148(NAME, OP, FUNC, P99_ALLBUTLAST(__VA_ARGS__)), FUNC(NAME, P99_LAST(__VA_ARGS__), 148))
#define P00_FOR150(NAME, OP, FUNC, ...)                                                                         \
 OP(NAME, 149, P00_FOR149(NAME, OP, FUNC, P99_ALLBUTLAST(__VA_ARGS__)), FUNC(NAME, P99_LAST(__VA_ARGS__), 149))
#define P00_FOR151(NAME, OP, FUNC, ...)                                                                         \
 OP(NAME, 150, P00_FOR150(NAME, OP, FUNC, P99_ALLBUTLAST(__VA_ARGS__)), FUNC(NAME, P99_LAST(__VA_ARGS__), 150))
#define P00_FOR152(NAME, OP, FUNC, ...)                                                                         \
 OP(NAME, 151, P00_FOR151(NAME, OP, FUNC, P99_ALLBUTLAST(__VA_ARGS__)), FUNC(NAME, P99_LAST(__VA_ARGS__), 151))
#define P00_FOR153(NAME, OP, FUNC, ...)                                                                         \
 OP(NAME, 152, P00_FOR152(NAME, OP, FUNC, P99_ALLBUTLAST(__VA_ARGS__)), FUNC(NAME, P99_LAST(__VA_ARGS__), 152))
#define P00_FOR154(NAME, OP, FUNC, ...)                                                                         \
 OP(NAME, 153, P00_FOR153(NAME, OP, FUNC, P99_ALLBUTLAST(__VA_ARGS__)), FUNC(NAME, P99_LAST(__VA_ARGS__), 153))
#define P00_FOR155(NAME, OP, FUNC, ...)                                                                         \
 OP(NAME, 154, P00_FOR154(NAME, OP, FUNC, P99_ALLBUTLAST(__VA_ARGS__)), FUNC(NAME, P99_LAST(__VA_ARGS__), 154))
#define P00_FOR156(NAME, OP, FUNC, ...)                                                                         \
 OP(NAME, 155, P00_FOR155(NAME, OP, FUNC, P99_ALLBUTLAST(__VA_ARGS__)), FUNC(NAME, P99_LAST(__VA_ARGS__), 155))
#define P00_FOR157(NAME, OP, FUNC, ...)                                                                         \
 OP(NAME, 156, P00_FOR156(NAME, OP, FUNC, P99_ALLBUTLAST(__VA_ARGS__)), FUNC(NAME, P99_LAST(__VA_ARGS__), 156))
#define P00_FOR158(NAME, OP, FUNC, ...)                                                                         \
 OP(NAME, 157, P00_FOR157(NAME, OP, FUNC, P99_ALLBUTLAST(__VA_ARGS__)), FUNC(NAME, P99_LAST(__VA_ARGS__), 157))

/* The preprocessor always computes with the precision of uintmax_t */
/* so for the preprocessor this is equivalent to UINITMAX_MAX       */
#define P00_UNSIGNED_MAX ~0u

#define P00_S0 0x01
#define P00_S1 0x02
#define P00_S2 0x04
#define P00_S3 0x08
#define P00_S4 0x10
#define P00_S5 0x20
#define P00_S6 0x40



/* This has to be such ugly #if/#else to ensure that the            */
/* preprocessor never sees a constant that is too large.            */
#ifndef P99_UINTMAX_MAX
# define P00_MASK_64 0xFFFFFFFFFFFFFFFF
# if P00_UNSIGNED_MAX == 0xFFFFFFFFFFFFFFFF
#  define P99_UINTMAX_WIDTH 64
#  define P99_UINTMAX_MAX 0xFFFFFFFFFFFFFFFFU
#  define P00_B0 0xAAAAAAAAAAAAAAAAU
#  define P00_B1 0xCCCCCCCCCCCCCCCCU
#  define P00_B2 0xF0F0F0F0F0F0F0F0U
#  define P00_B3 0xFF00FF00FF00FF00U
#  define P00_B4 0xFFFF0000FFFF0000U
#  define P00_B5 0xFFFFFFFF00000000U
#  define P00_B6 0x0U
# endif /* P00_UNSIGNED_MAX */
#endif /* P99_UINTMAX_MAX */
#ifndef P99_UINTMAX_MAX
# define P00_MASK_65 0x1FFFFFFFFFFFFFFFF
# if P00_UNSIGNED_MAX == 0x1FFFFFFFFFFFFFFFF
#  define P99_UINTMAX_WIDTH 65
#  define P99_UINTMAX_MAX 0x1FFFFFFFFFFFFFFFFU
#  define P00_B0 0xAAAAAAAAAAAAAAAAU
#  define P00_B1 0xCCCCCCCCCCCCCCCCU
#  define P00_B2 0xF0F0F0F0F0F0F0F0U
#  define P00_B3 0xFF00FF00FF00FF00U
#  define P00_B4 0xFFFF0000FFFF0000U
#  define P00_B5 0xFFFFFFFF00000000U
#  define P00_B6 0x10000000000000000U
# endif /* P00_UNSIGNED_MAX */
#endif /* P99_UINTMAX_MAX */
#ifndef P99_UINTMAX_MAX
# define P00_MASK_66 0x3FFFFFFFFFFFFFFFF
# if P00_UNSIGNED_MAX == 0x3FFFFFFFFFFFFFFFF
#  define P99_UINTMAX_WIDTH 66
#  define P99_UINTMAX_MAX 0x3FFFFFFFFFFFFFFFFU
#  define P00_B0 0x2AAAAAAAAAAAAAAAAU
#  define P00_B1 0xCCCCCCCCCCCCCCCCU
#  define P00_B2 0xF0F0F0F0F0F0F0F0U
#  define P00_B3 0xFF00FF00FF00FF00U
#  define P00_B4 0xFFFF0000FFFF0000U
#  define P00_B5 0xFFFFFFFF00000000U
#  define P00_B6 0x30000000000000000U
# endif /* P00_UNSIGNED_MAX */
#endif /* P99_UINTMAX_MAX */
#ifndef P99_UINTMAX_MAX
# define P00_MASK_67 0x7FFFFFFFFFFFFFFFF
# if P00_UNSIGNED_MAX == 0x7FFFFFFFFFFFFFFFF
#  define P99_UINTMAX_WIDTH 67
#  define P99_UINTMAX_MAX 0x7FFFFFFFFFFFFFFFFU
#  define P00_B0 0x2AAAAAAAAAAAAAAAAU
#  define P00_B1 0x4CCCCCCCCCCCCCCCCU
#  define P00_B2 0xF0F0F0F0F0F0F0F0U
#  define P00_B3 0xFF00FF00FF00FF00U
#  define P00_B4 0xFFFF0000FFFF0000U
#  define P00_B5 0xFFFFFFFF00000000U
#  define P00_B6 0x70000000000000000U
# endif /* P00_UNSIGNED_MAX */
#endif /* P99_UINTMAX_MAX */
#ifndef P99_UINTMAX_MAX
# define P00_MASK_68 0xFFFFFFFFFFFFFFFFF
# if P00_UNSIGNED_MAX == 0xFFFFFFFFFFFFFFFFF
#  define P99_UINTMAX_WIDTH 68
#  define P99_UINTMAX_MAX 0xFFFFFFFFFFFFFFFFFU
#  define P00_B0 0xAAAAAAAAAAAAAAAAAU
#  define P00_B1 0xCCCCCCCCCCCCCCCCCU
#  define P00_B2 0xF0F0F0F0F0F0F0F0U
#  define P00_B3 0xFF00FF00FF00FF00U
#  define P00_B4 0xFFFF0000FFFF0000U
#  define P00_B5 0xFFFFFFFF00000000U
#  define P00_B6 0xF0000000000000000U
# endif /* P00_UNSIGNED_MAX */
#endif /* P99_UINTMAX_MAX */
#ifndef P99_UINTMAX_MAX
# define P00_MASK_69 0x1FFFFFFFFFFFFFFFFF
# if P00_UNSIGNED_MAX == 0x1FFFFFFFFFFFFFFFFF
#  define P99_UINTMAX_WIDTH 69
#  define P99_UINTMAX_MAX 0x1FFFFFFFFFFFFFFFFFU
#  define P00_B0 0xAAAAAAAAAAAAAAAAAU
#  define P00_B1 0xCCCCCCCCCCCCCCCCCU
#  define P00_B2 0x10F0F0F0F0F0F0F0F0U
#  define P00_B3 0xFF00FF00FF00FF00U
#  define P00_B4 0xFFFF0000FFFF0000U
#  define P00_B5 0xFFFFFFFF00000000U
#  define P00_B6 0x1F0000000000000000U
# endif /* P00_UNSIGNED_MAX */
#endif /* P99_UINTMAX_MAX */
#ifndef P99_UINTMAX_MAX
# define P00_MASK_70 0x3FFFFFFFFFFFFFFFFF
# if P00_UNSIGNED_MAX == 0x3FFFFFFFFFFFFFFFFF
#  define P99_UINTMAX_WIDTH 70
#  define P99_UINTMAX_MAX 0x3FFFFFFFFFFFFFFFFFU
#  define P00_B0 0x2AAAAAAAAAAAAAAAAAU
#  define P00_B1 0xCCCCCCCCCCCCCCCCCU
#  define P00_B2 0x30F0F0F0F0F0F0F0F0U
#  define P00_B3 0xFF00FF00FF00FF00U
#  define P00_B4 0xFFFF0000FFFF0000U
#  define P00_B5 0xFFFFFFFF00000000U
#  define P00_B6 0x3F0000000000000000U
# endif /* P00_UNSIGNED_MAX */
#endif /* P99_UINTMAX_MAX */
#ifndef P99_UINTMAX_MAX
# define P00_MASK_71 0x7FFFFFFFFFFFFFFFFF
# if P00_UNSIGNED_MAX == 0x7FFFFFFFFFFFFFFFFF
#  define P99_UINTMAX_WIDTH 71
#  define P99_UINTMAX_MAX 0x7FFFFFFFFFFFFFFFFFU
#  define P00_B0 0x2AAAAAAAAAAAAAAAAAU
#  define P00_B1 0x4CCCCCCCCCCCCCCCCCU
#  define P00_B2 0x70F0F0F0F0F0F0F0F0U
#  define P00_B3 0xFF00FF00FF00FF00U
#  define P00_B4 0xFFFF0000FFFF0000U
#  define P00_B5 0xFFFFFFFF00000000U
#  define P00_B6 0x7F0000000000000000U
# endif /* P00_UNSIGNED_MAX */
#endif /* P99_UINTMAX_MAX */
#ifndef P99_UINTMAX_MAX
# define P00_MASK_72 0xFFFFFFFFFFFFFFFFFF
# if P00_UNSIGNED_MAX == 0xFFFFFFFFFFFFFFFFFF
#  define P99_UINTMAX_WIDTH 72
#  define P99_UINTMAX_MAX 0xFFFFFFFFFFFFFFFFFFU
#  define P00_B0 0xAAAAAAAAAAAAAAAAAAU
#  define P00_B1 0xCCCCCCCCCCCCCCCCCCU
#  define P00_B2 0xF0F0F0F0F0F0F0F0F0U
#  define P00_B3 0xFF00FF00FF00FF00U
#  define P00_B4 0xFFFF0000FFFF0000U
#  define P00_B5 0xFFFFFFFF00000000U
#  define P00_B6 0xFF0000000000000000U
# endif /* P00_UNSIGNED_MAX */
#endif /* P99_UINTMAX_MAX */
#ifndef P99_UINTMAX_MAX
# define P00_MASK_73 0x1FFFFFFFFFFFFFFFFFF
# if P00_UNSIGNED_MAX == 0x1FFFFFFFFFFFFFFFFFF
#  define P99_UINTMAX_WIDTH 73
#  define P99_UINTMAX_MAX 0x1FFFFFFFFFFFFFFFFFFU
#  define P00_B0 0xAAAAAAAAAAAAAAAAAAU
#  define P00_B1 0xCCCCCCCCCCCCCCCCCCU
#  define P00_B2 0xF0F0F0F0F0F0F0F0F0U
#  define P00_B3 0x100FF00FF00FF00FF00U
#  define P00_B4 0xFFFF0000FFFF0000U
#  define P00_B5 0xFFFFFFFF00000000U
#  define P00_B6 0x1FF0000000000000000U
# endif /* P00_UNSIGNED_MAX */
#endif /* P99_UINTMAX_MAX */
#ifndef P99_UINTMAX_MAX
# define P00_MASK_74 0x3FFFFFFFFFFFFFFFFFF
# if P00_UNSIGNED_MAX == 0x3FFFFFFFFFFFFFFFFFF
#  define P99_UINTMAX_WIDTH 74
#  define P99_UINTMAX_MAX 0x3FFFFFFFFFFFFFFFFFFU
#  define P00_B0 0x2AAAAAAAAAAAAAAAAAAU
#  define P00_B1 0xCCCCCCCCCCCCCCCCCCU
#  define P00_B2 0xF0F0F0F0F0F0F0F0F0U
#  define P00_B3 0x300FF00FF00FF00FF00U
#  define P00_B4 0xFFFF0000FFFF0000U
#  define P00_B5 0xFFFFFFFF00000000U
#  define P00_B6 0x3FF0000000000000000U
# endif /* P00_UNSIGNED_MAX */
#endif /* P99_UINTMAX_MAX */
#ifndef P99_UINTMAX_MAX
# define P00_MASK_75 0x7FFFFFFFFFFFFFFFFFF
# if P00_UNSIGNED_MAX == 0x7FFFFFFFFFFFFFFFFFF
#  define P99_UINTMAX_WIDTH 75
#  define P99_UINTMAX_MAX 0x7FFFFFFFFFFFFFFFFFFU
#  define P00_B0 0x2AAAAAAAAAAAAAAAAAAU
#  define P00_B1 0x4CCCCCCCCCCCCCCCCCCU
#  define P00_B2 0xF0F0F0F0F0F0F0F0F0U
#  define P00_B3 0x700FF00FF00FF00FF00U
#  define P00_B4 0xFFFF0000FFFF0000U
#  define P00_B5 0xFFFFFFFF00000000U
#  define P00_B6 0x7FF0000000000000000U
# endif /* P00_UNSIGNED_MAX */
#endif /* P99_UINTMAX_MAX */
#ifndef P99_UINTMAX_MAX
# define P00_MASK_76 0xFFFFFFFFFFFFFFFFFFF
# if P00_UNSIGNED_MAX == 0xFFFFFFFFFFFFFFFFFFF
#  define P99_UINTMAX_WIDTH 76
#  define P99_UINTMAX_MAX 0xFFFFFFFFFFFFFFFFFFFU
#  define P00_B0 0xAAAAAAAAAAAAAAAAAAAU
#  define P00_B1 0xCCCCCCCCCCCCCCCCCCCU
#  define P00_B2 0xF0F0F0F0F0F0F0F0F0U
#  define P00_B3 0xF00FF00FF00FF00FF00U
#  define P00_B4 0xFFFF0000FFFF0000U
#  define P00_B5 0xFFFFFFFF00000000U
#  define P00_B6 0xFFF0000000000000000U
# endif /* P00_UNSIGNED_MAX */
#endif /* P99_UINTMAX_MAX */
#ifndef P99_UINTMAX_MAX
# define P00_MASK_77 0x1FFFFFFFFFFFFFFFFFFF
# if P00_UNSIGNED_MAX == 0x1FFFFFFFFFFFFFFFFFFF
#  define P99_UINTMAX_WIDTH 77
#  define P99_UINTMAX_MAX 0x1FFFFFFFFFFFFFFFFFFFU
#  define P00_B0 0xAAAAAAAAAAAAAAAAAAAU
#  define P00_B1 0xCCCCCCCCCCCCCCCCCCCU
#  define P00_B2 0x10F0F0F0F0F0F0F0F0F0U
#  define P00_B3 0x1F00FF00FF00FF00FF00U
#  define P00_B4 0xFFFF0000FFFF0000U
#  define P00_B5 0xFFFFFFFF00000000U
#  define P00_B6 0x1FFF0000000000000000U
# endif /* P00_UNSIGNED_MAX */
#endif /* P99_UINTMAX_MAX */
#ifndef P99_UINTMAX_MAX
# define P00_MASK_78 0x3FFFFFFFFFFFFFFFFFFF
# if P00_UNSIGNED_MAX == 0x3FFFFFFFFFFFFFFFFFFF
#  define P99_UINTMAX_WIDTH 78
#  define P99_UINTMAX_MAX 0x3FFFFFFFFFFFFFFFFFFFU
#  define P00_B0 0x2AAAAAAAAAAAAAAAAAAAU
#  define P00_B1 0xCCCCCCCCCCCCCCCCCCCU
#  define P00_B2 0x30F0F0F0F0F0F0F0F0F0U
#  define P00_B3 0x3F00FF00FF00FF00FF00U
#  define P00_B4 0xFFFF0000FFFF0000U
#  define P00_B5 0xFFFFFFFF00000000U
#  define P00_B6 0x3FFF0000000000000000U
# endif /* P00_UNSIGNED_MAX */
#endif /* P99_UINTMAX_MAX */
#ifndef P99_UINTMAX_MAX
# define P00_MASK_79 0x7FFFFFFFFFFFFFFFFFFF
# if P00_UNSIGNED_MAX == 0x7FFFFFFFFFFFFFFFFFFF
#  define P99_UINTMAX_WIDTH 79
#  define P99_UINTMAX_MAX 0x7FFFFFFFFFFFFFFFFFFFU
#  define P00_B0 0x2AAAAAAAAAAAAAAAAAAAU
#  define P00_B1 0x4CCCCCCCCCCCCCCCCCCCU
#  define P00_B2 0x70F0F0F0F0F0F0F0F0F0U
#  define P00_B3 0x7F00FF00FF00FF00FF00U
#  define P00_B4 0xFFFF0000FFFF0000U
#  define P00_B5 0xFFFFFFFF00000000U
#  define P00_B6 0x7FFF0000000000000000U
# endif /* P00_UNSIGNED_MAX */
#endif /* P99_UINTMAX_MAX */
#ifndef P99_UINTMAX_MAX
# define P00_MASK_80 0xFFFFFFFFFFFFFFFFFFFF
# if P00_UNSIGNED_MAX == 0xFFFFFFFFFFFFFFFFFFFF
#  define P99_UINTMAX_WIDTH 80
#  define P99_UINTMAX_MAX 0xFFFFFFFFFFFFFFFFFFFFU
#  define P00_B0 0xAAAAAAAAAAAAAAAAAAAAU
#  define P00_B1 0xCCCCCCCCCCCCCCCCCCCCU
#  define P00_B2 0xF0F0F0F0F0F0F0F0F0F0U
#  define P00_B3 0xFF00FF00FF00FF00FF00U
#  define P00_B4 0xFFFF0000FFFF0000U
#  define P00_B5 0xFFFFFFFF00000000U
#  define P00_B6 0xFFFF0000000000000000U
# endif /* P00_UNSIGNED_MAX */
#endif /* P99_UINTMAX_MAX */
#ifndef P99_UINTMAX_MAX
# define P00_MASK_81 0x1FFFFFFFFFFFFFFFFFFFF
# if P00_UNSIGNED_MAX == 0x1FFFFFFFFFFFFFFFFFFFF
#  define P99_UINTMAX_WIDTH 81
#  define P99_UINTMAX_MAX 0x1FFFFFFFFFFFFFFFFFFFFU
#  define P00_B0 0xAAAAAAAAAAAAAAAAAAAAU
#  define P00_B1 0xCCCCCCCCCCCCCCCCCCCCU
#  define P00_B2 0xF0F0F0F0F0F0F0F0F0F0U
#  define P00_B3 0xFF00FF00FF00FF00FF00U
#  define P00_B4 0x10000FFFF0000FFFF0000U
#  define P00_B5 0xFFFFFFFF00000000U
#  define P00_B6 0x1FFFF0000000000000000U
# endif /* P00_UNSIGNED_MAX */
#endif /* P99_UINTMAX_MAX */
#ifndef P99_UINTMAX_MAX
# define P00_MASK_82 0x3FFFFFFFFFFFFFFFFFFFF
# if P00_UNSIGNED_MAX == 0x3FFFFFFFFFFFFFFFFFFFF
#  define P99_UINTMAX_WIDTH 82
#  define P99_UINTMAX_MAX 0x3FFFFFFFFFFFFFFFFFFFFU
#  define P00_B0 0x2AAAAAAAAAAAAAAAAAAAAU
#  define P00_B1 0xCCCCCCCCCCCCCCCCCCCCU
#  define P00_B2 0xF0F0F0F0F0F0F0F0F0F0U
#  define P00_B3 0xFF00FF00FF00FF00FF00U
#  define P00_B4 0x30000FFFF0000FFFF0000U
#  define P00_B5 0xFFFFFFFF00000000U
#  define P00_B6 0x3FFFF0000000000000000U
# endif /* P00_UNSIGNED_MAX */
#endif /* P99_UINTMAX_MAX */
#ifndef P99_UINTMAX_MAX
# define P00_MASK_83 0x7FFFFFFFFFFFFFFFFFFFF
# if P00_UNSIGNED_MAX == 0x7FFFFFFFFFFFFFFFFFFFF
#  define P99_UINTMAX_WIDTH 83
#  define P99_UINTMAX_MAX 0x7FFFFFFFFFFFFFFFFFFFFU
#  define P00_B0 0x2AAAAAAAAAAAAAAAAAAAAU
#  define P00_B1 0x4CCCCCCCCCCCCCCCCCCCCU
#  define P00_B2 0xF0F0F0F0F0F0F0F0F0F0U
#  define P00_B3 0xFF00FF00FF00FF00FF00U
#  define P00_B4 0x70000FFFF0000FFFF0000U
#  define P00_B5 0xFFFFFFFF00000000U
#  define P00_B6 0x7FFFF0000000000000000U
# endif /* P00_UNSIGNED_MAX */
#endif /* P99_UINTMAX_MAX */
#ifndef P99_UINTMAX_MAX
# define P00_MASK_84 0xFFFFFFFFFFFFFFFFFFFFF
# if P00_UNSIGNED_MAX == 0xFFFFFFFFFFFFFFFFFFFFF
#  define P99_UINTMAX_WIDTH 84
#  define P99_UINTMAX_MAX 0xFFFFFFFFFFFFFFFFFFFFFU
#  define P00_B0 0xAAAAAAAAAAAAAAAAAAAAAU
#  define P00_B1 0xCCCCCCCCCCCCCCCCCCCCCU
#  define P00_B2 0xF0F0F0F0F0F0F0F0F0F0U
#  define P00_B3 0xFF00FF00FF00FF00FF00U
#  define P00_B4 0xF0000FFFF0000FFFF0000U
#  define P00_B5 0xFFFFFFFF00000000U
#  define P00_B6 0xFFFFF0000000000000000U
# endif /* P00_UNSIGNED_MAX */
#endif /* P99_UINTMAX_MAX */
#ifndef P99_UINTMAX_MAX
# define P00_MASK_85 0x1FFFFFFFFFFFFFFFFFFFFF
# if P00_UNSIGNED_MAX == 0x1FFFFFFFFFFFFFFFFFFFFF
#  define P99_UINTMAX_WIDTH 85
#  define P99_UINTMAX_MAX 0x1FFFFFFFFFFFFFFFFFFFFFU
#  define P00_B0 0xAAAAAAAAAAAAAAAAAAAAAU
#  define P00_B1 0xCCCCCCCCCCCCCCCCCCCCCU
#  define P00_B2 0x10F0F0F0F0F0F0F0F0F0F0U
#  define P00_B3 0xFF00FF00FF00FF00FF00U
#  define P00_B4 0x1F0000FFFF0000FFFF0000U
#  define P00_B5 0xFFFFFFFF00000000U
#  define P00_B6 0x1FFFFF0000000000000000U
# endif /* P00_UNSIGNED_MAX */
#endif /* P99_UINTMAX_MAX */
#ifndef P99_UINTMAX_MAX
# define P00_MASK_86 0x3FFFFFFFFFFFFFFFFFFFFF
# if P00_UNSIGNED_MAX == 0x3FFFFFFFFFFFFFFFFFFFFF
#  define P99_UINTMAX_WIDTH 86
#  define P99_UINTMAX_MAX 0x3FFFFFFFFFFFFFFFFFFFFFU
#  define P00_B0 0x2AAAAAAAAAAAAAAAAAAAAAU
#  define P00_B1 0xCCCCCCCCCCCCCCCCCCCCCU
#  define P00_B2 0x30F0F0F0F0F0F0F0F0F0F0U
#  define P00_B3 0xFF00FF00FF00FF00FF00U
#  define P00_B4 0x3F0000FFFF0000FFFF0000U
#  define P00_B5 0xFFFFFFFF00000000U
#  define P00_B6 0x3FFFFF0000000000000000U
# endif /* P00_UNSIGNED_MAX */
#endif /* P99_UINTMAX_MAX */
#ifndef P99_UINTMAX_MAX
# define P00_MASK_87 0x7FFFFFFFFFFFFFFFFFFFFF
# if P00_UNSIGNED_MAX == 0x7FFFFFFFFFFFFFFFFFFFFF
#  define P99_UINTMAX_WIDTH 87
#  define P99_UINTMAX_MAX 0x7FFFFFFFFFFFFFFFFFFFFFU
#  define P00_B0 0x2AAAAAAAAAAAAAAAAAAAAAU
#  define P00_B1 0x4CCCCCCCCCCCCCCCCCCCCCU
#  define P00_B2 0x70F0F0F0F0F0F0F0F0F0F0U
#  define P00_B3 0xFF00FF00FF00FF00FF00U
#  define P00_B4 0x7F0000FFFF0000FFFF0000U
#  define P00_B5 0xFFFFFFFF00000000U
#  define P00_B6 0x7FFFFF0000000000000000U
# endif /* P00_UNSIGNED_MAX */
#endif /* P99_UINTMAX_MAX */
#ifndef P99_UINTMAX_MAX
# define P00_MASK_88 0xFFFFFFFFFFFFFFFFFFFFFF
# if P00_UNSIGNED_MAX == 0xFFFFFFFFFFFFFFFFFFFFFF
#  define P99_UINTMAX_WIDTH 88
#  define P99_UINTMAX_MAX 0xFFFFFFFFFFFFFFFFFFFFFFU
#  define P00_B0 0xAAAAAAAAAAAAAAAAAAAAAAU
#  define P00_B1 0xCCCCCCCCCCCCCCCCCCCCCCU
#  define P00_B2 0xF0F0F0F0F0F0F0F0F0F0F0U
#  define P00_B3 0xFF00FF00FF00FF00FF00U
#  define P00_B4 0xFF0000FFFF0000FFFF0000U
#  define P00_B5 0xFFFFFFFF00000000U
#  define P00_B6 0xFFFFFF0000000000000000U
# endif /* P00_UNSIGNED_MAX */
#endif /* P99_UINTMAX_MAX */
#ifndef P99_UINTMAX_MAX
# define P00_MASK_89 0x1FFFFFFFFFFFFFFFFFFFFFF
# if P00_UNSIGNED_MAX == 0x1FFFFFFFFFFFFFFFFFFFFFF
#  define P99_UINTMAX_WIDTH 89
#  define P99_UINTMAX_MAX 0x1FFFFFFFFFFFFFFFFFFFFFFU
#  define P00_B0 0xAAAAAAAAAAAAAAAAAAAAAAU
#  define P00_B1 0xCCCCCCCCCCCCCCCCCCCCCCU
#  define P00_B2 0xF0F0F0F0F0F0F0F0F0F0F0U
#  define P00_B3 0x100FF00FF00FF00FF00FF00U
#  define P00_B4 0x1FF0000FFFF0000FFFF0000U
#  define P00_B5 0xFFFFFFFF00000000U
#  define P00_B6 0x1FFFFFF0000000000000000U
# endif /* P00_UNSIGNED_MAX */
#endif /* P99_UINTMAX_MAX */
#ifndef P99_UINTMAX_MAX
# define P00_MASK_90 0x3FFFFFFFFFFFFFFFFFFFFFF
# if P00_UNSIGNED_MAX == 0x3FFFFFFFFFFFFFFFFFFFFFF
#  define P99_UINTMAX_WIDTH 90
#  define P99_UINTMAX_MAX 0x3FFFFFFFFFFFFFFFFFFFFFFU
#  define P00_B0 0x2AAAAAAAAAAAAAAAAAAAAAAU
#  define P00_B1 0xCCCCCCCCCCCCCCCCCCCCCCU
#  define P00_B2 0xF0F0F0F0F0F0F0F0F0F0F0U
#  define P00_B3 0x300FF00FF00FF00FF00FF00U
#  define P00_B4 0x3FF0000FFFF0000FFFF0000U
#  define P00_B5 0xFFFFFFFF00000000U
#  define P00_B6 0x3FFFFFF0000000000000000U
# endif /* P00_UNSIGNED_MAX */
#endif /* P99_UINTMAX_MAX */
#ifndef P99_UINTMAX_MAX
# define P00_MASK_91 0x7FFFFFFFFFFFFFFFFFFFFFF
# if P00_UNSIGNED_MAX == 0x7FFFFFFFFFFFFFFFFFFFFFF
#  define P99_UINTMAX_WIDTH 91
#  define P99_UINTMAX_MAX 0x7FFFFFFFFFFFFFFFFFFFFFFU
#  define P00_B0 0x2AAAAAAAAAAAAAAAAAAAAAAU
#  define P00_B1 0x4CCCCCCCCCCCCCCCCCCCCCCU
#  define P00_B2 0xF0F0F0F0F0F0F0F0F0F0F0U
#  define P00_B3 0x700FF00FF00FF00FF00FF00U
#  define P00_B4 0x7FF0000FFFF0000FFFF0000U
#  define P00_B5 0xFFFFFFFF00000000U
#  define P00_B6 0x7FFFFFF0000000000000000U
# endif /* P00_UNSIGNED_MAX */
#endif /* P99_UINTMAX_MAX */
#ifndef P99_UINTMAX_MAX
# define P00_MASK_92 0xFFFFFFFFFFFFFFFFFFFFFFF
# if P00_UNSIGNED_MAX == 0xFFFFFFFFFFFFFFFFFFFFFFF
#  define P99_UINTMAX_WIDTH 92
#  define P99_UINTMAX_MAX 0xFFFFFFFFFFFFFFFFFFFFFFFU
#  define P00_B0 0xAAAAAAAAAAAAAAAAAAAAAAAU
#  define P00_B1 0xCCCCCCCCCCCCCCCCCCCCCCCU
#  define P00_B2 0xF0F0F0F0F0F0F0F0F0F0F0U
#  define P00_B3 0xF00FF00FF00FF00FF00FF00U
#  define P00_B4 0xFFF0000FFFF0000FFFF0000U
#  define P00_B5 0xFFFFFFFF00000000U
#  define P00_B6 0xFFFFFFF0000000000000000U
# endif /* P00_UNSIGNED_MAX */
#endif /* P99_UINTMAX_MAX */
#ifndef P99_UINTMAX_MAX
# define P00_MASK_93 0x1FFFFFFFFFFFFFFFFFFFFFFF
# if P00_UNSIGNED_MAX == 0x1FFFFFFFFFFFFFFFFFFFFFFF
#  define P99_UINTMAX_WIDTH 93
#  define P99_UINTMAX_MAX 0x1FFFFFFFFFFFFFFFFFFFFFFFU
#  define P00_B0 0xAAAAAAAAAAAAAAAAAAAAAAAU
#  define P00_B1 0xCCCCCCCCCCCCCCCCCCCCCCCU
#  define P00_B2 0x10F0F0F0F0F0F0F0F0F0F0F0U
#  define P00_B3 0x1F00FF00FF00FF00FF00FF00U
#  define P00_B4 0x1FFF0000FFFF0000FFFF0000U
#  define P00_B5 0xFFFFFFFF00000000U
#  define P00_B6 0x1FFFFFFF0000000000000000U
# endif /* P00_UNSIGNED_MAX */
#endif /* P99_UINTMAX_MAX */
#ifndef P99_UINTMAX_MAX
# define P00_MASK_94 0x3FFFFFFFFFFFFFFFFFFFFFFF
# if P00_UNSIGNED_MAX == 0x3FFFFFFFFFFFFFFFFFFFFFFF
#  define P99_UINTMAX_WIDTH 94
#  define P99_UINTMAX_MAX 0x3FFFFFFFFFFFFFFFFFFFFFFFU
#  define P00_B0 0x2AAAAAAAAAAAAAAAAAAAAAAAU
#  define P00_B1 0xCCCCCCCCCCCCCCCCCCCCCCCU
#  define P00_B2 0x30F0F0F0F0F0F0F0F0F0F0F0U
#  define P00_B3 0x3F00FF00FF00FF00FF00FF00U
#  define P00_B4 0x3FFF0000FFFF0000FFFF0000U
#  define P00_B5 0xFFFFFFFF00000000U
#  define P00_B6 0x3FFFFFFF0000000000000000U
# endif /* P00_UNSIGNED_MAX */
#endif /* P99_UINTMAX_MAX */
#ifndef P99_UINTMAX_MAX
# define P00_MASK_95 0x7FFFFFFFFFFFFFFFFFFFFFFF
# if P00_UNSIGNED_MAX == 0x7FFFFFFFFFFFFFFFFFFFFFFF
#  define P99_UINTMAX_WIDTH 95
#  define P99_UINTMAX_MAX 0x7FFFFFFFFFFFFFFFFFFFFFFFU
#  define P00_B0 0x2AAAAAAAAAAAAAAAAAAAAAAAU
#  define P00_B1 0x4CCCCCCCCCCCCCCCCCCCCCCCU
#  define P00_B2 0x70F0F0F0F0F0F0F0F0F0F0F0U
#  define P00_B3 0x7F00FF00FF00FF00FF00FF00U
#  define P00_B4 0x7FFF0000FFFF0000FFFF0000U
#  define P00_B5 0xFFFFFFFF00000000U
#  define P00_B6 0x7FFFFFFF0000000000000000U
# endif /* P00_UNSIGNED_MAX */
#endif /* P99_UINTMAX_MAX */
#ifndef P99_UINTMAX_MAX
# define P00_MASK_96 0xFFFFFFFFFFFFFFFFFFFFFFFF
# if P00_UNSIGNED_MAX == 0xFFFFFFFFFFFFFFFFFFFFFFFF
#  define P99_UINTMAX_WIDTH 96
#  define P99_UINTMAX_MAX 0xFFFFFFFFFFFFFFFFFFFFFFFFU
#  define P00_B0 0xAAAAAAAAAAAAAAAAAAAAAAAAU
#  define P00_B1 0xCCCCCCCCCCCCCCCCCCCCCCCCU
#  define P00_B2 0xF0F0F0F0F0F0F0F0F0F0F0F0U
#  define P00_B3 0xFF00FF00FF00FF00FF00FF00U
#  define P00_B4 0xFFFF0000FFFF0000FFFF0000U
#  define P00_B5 0xFFFFFFFF00000000U
#  define P00_B6 0xFFFFFFFF0000000000000000U
# endif /* P00_UNSIGNED_MAX */
#endif /* P99_UINTMAX_MAX */
#ifndef P99_UINTMAX_MAX
# define P00_MASK_97 0x1FFFFFFFFFFFFFFFFFFFFFFFF
# if P00_UNSIGNED_MAX == 0x1FFFFFFFFFFFFFFFFFFFFFFFF
#  define P99_UINTMAX_WIDTH 97
#  define P99_UINTMAX_MAX 0x1FFFFFFFFFFFFFFFFFFFFFFFFU
#  define P00_B0 0xAAAAAAAAAAAAAAAAAAAAAAAAU
#  define P00_B1 0xCCCCCCCCCCCCCCCCCCCCCCCCU
#  define P00_B2 0xF0F0F0F0F0F0F0F0F0F0F0F0U
#  define P00_B3 0xFF00FF00FF00FF00FF00FF00U
#  define P00_B4 0xFFFF0000FFFF0000FFFF0000U
#  define P00_B5 0x100000000FFFFFFFF00000000U
#  define P00_B6 0x1FFFFFFFF0000000000000000U
# endif /* P00_UNSIGNED_MAX */
#endif /* P99_UINTMAX_MAX */
#ifndef P99_UINTMAX_MAX
# define P00_MASK_98 0x3FFFFFFFFFFFFFFFFFFFFFFFF
# if P00_UNSIGNED_MAX == 0x3FFFFFFFFFFFFFFFFFFFFFFFF
#  define P99_UINTMAX_WIDTH 98
#  define P99_UINTMAX_MAX 0x3FFFFFFFFFFFFFFFFFFFFFFFFU
#  define P00_B0 0x2AAAAAAAAAAAAAAAAAAAAAAAAU
#  define P00_B1 0xCCCCCCCCCCCCCCCCCCCCCCCCU
#  define P00_B2 0xF0F0F0F0F0F0F0F0F0F0F0F0U
#  define P00_B3 0xFF00FF00FF00FF00FF00FF00U
#  define P00_B4 0xFFFF0000FFFF0000FFFF0000U
#  define P00_B5 0x300000000FFFFFFFF00000000U
#  define P00_B6 0x3FFFFFFFF0000000000000000U
# endif /* P00_UNSIGNED_MAX */
#endif /* P99_UINTMAX_MAX */
#ifndef P99_UINTMAX_MAX
# define P00_MASK_99 0x7FFFFFFFFFFFFFFFFFFFFFFFF
# if P00_UNSIGNED_MAX == 0x7FFFFFFFFFFFFFFFFFFFFFFFF
#  define P99_UINTMAX_WIDTH 99
#  define P99_UINTMAX_MAX 0x7FFFFFFFFFFFFFFFFFFFFFFFFU
#  define P00_B0 0x2AAAAAAAAAAAAAAAAAAAAAAAAU
#  define P00_B1 0x4CCCCCCCCCCCCCCCCCCCCCCCCU
#  define P00_B2 0xF0F0F0F0F0F0F0F0F0F0F0F0U
#  define P00_B3 0xFF00FF00FF00FF00FF00FF00U
#  define P00_B4 0xFFFF0000FFFF0000FFFF0000U
#  define P00_B5 0x700000000FFFFFFFF00000000U
#  define P00_B6 0x7FFFFFFFF0000000000000000U
# endif /* P00_UNSIGNED_MAX */
#endif /* P99_UINTMAX_MAX */
#ifndef P99_UINTMAX_MAX
# define P00_MASK_100 0xFFFFFFFFFFFFFFFFFFFFFFFFF
# if P00_UNSIGNED_MAX == 0xFFFFFFFFFFFFFFFFFFFFFFFFF
#  define P99_UINTMAX_WIDTH 100
#  define P99_UINTMAX_MAX 0xFFFFFFFFFFFFFFFFFFFFFFFFFU
#  define P00_B0 0xAAAAAAAAAAAAAAAAAAAAAAAAAU
#  define P00_B1 0xCCCCCCCCCCCCCCCCCCCCCCCCCU
#  define P00_B2 0xF0F0F0F0F0F0F0F0F0F0F0F0U
#  define P00_B3 0xFF00FF00FF00FF00FF00FF00U
#  define P00_B4 0xFFFF0000FFFF0000FFFF0000U
#  define P00_B5 0xF00000000FFFFFFFF00000000U
#  define P00_B6 0xFFFFFFFFF0000000000000000U
# endif /* P00_UNSIGNED_MAX */
#endif /* P99_UINTMAX_MAX */
#ifndef P99_UINTMAX_MAX
# define P00_MASK_101 0x1FFFFFFFFFFFFFFFFFFFFFFFFF
# if P00_UNSIGNED_MAX == 0x1FFFFFFFFFFFFFFFFFFFFFFFFF
#  define P99_UINTMAX_WIDTH 101
#  define P99_UINTMAX_MAX 0x1FFFFFFFFFFFFFFFFFFFFFFFFFU
#  define P00_B0 0xAAAAAAAAAAAAAAAAAAAAAAAAAU
#  define P00_B1 0xCCCCCCCCCCCCCCCCCCCCCCCCCU
#  define P00_B2 0x10F0F0F0F0F0F0F0F0F0F0F0F0U
#  define P00_B3 0xFF00FF00FF00FF00FF00FF00U
#  define P00_B4 0xFFFF0000FFFF0000FFFF0000U
#  define P00_B5 0x1F00000000FFFFFFFF00000000U
#  define P00_B6 0x1FFFFFFFFF0000000000000000U
# endif /* P00_UNSIGNED_MAX */
#endif /* P99_UINTMAX_MAX */
#ifndef P99_UINTMAX_MAX
# define P00_MASK_102 0x3FFFFFFFFFFFFFFFFFFFFFFFFF
# if P00_UNSIGNED_MAX == 0x3FFFFFFFFFFFFFFFFFFFFFFFFF
#  define P99_UINTMAX_WIDTH 102
#  define P99_UINTMAX_MAX 0x3FFFFFFFFFFFFFFFFFFFFFFFFFU
#  define P00_B0 0x2AAAAAAAAAAAAAAAAAAAAAAAAAU
#  define P00_B1 0xCCCCCCCCCCCCCCCCCCCCCCCCCU
#  define P00_B2 0x30F0F0F0F0F0F0F0F0F0F0F0F0U
#  define P00_B3 0xFF00FF00FF00FF00FF00FF00U
#  define P00_B4 0xFFFF0000FFFF0000FFFF0000U
#  define P00_B5 0x3F00000000FFFFFFFF00000000U
#  define P00_B6 0x3FFFFFFFFF0000000000000000U
# endif /* P00_UNSIGNED_MAX */
#endif /* P99_UINTMAX_MAX */
#ifndef P99_UINTMAX_MAX
# define P00_MASK_103 0x7FFFFFFFFFFFFFFFFFFFFFFFFF
# if P00_UNSIGNED_MAX == 0x7FFFFFFFFFFFFFFFFFFFFFFFFF
#  define P99_UINTMAX_WIDTH 103
#  define P99_UINTMAX_MAX 0x7FFFFFFFFFFFFFFFFFFFFFFFFFU
#  define P00_B0 0x2AAAAAAAAAAAAAAAAAAAAAAAAAU
#  define P00_B1 0x4CCCCCCCCCCCCCCCCCCCCCCCCCU
#  define P00_B2 0x70F0F0F0F0F0F0F0F0F0F0F0F0U
#  define P00_B3 0xFF00FF00FF00FF00FF00FF00U
#  define P00_B4 0xFFFF0000FFFF0000FFFF0000U
#  define P00_B5 0x7F00000000FFFFFFFF00000000U
#  define P00_B6 0x7FFFFFFFFF0000000000000000U
# endif /* P00_UNSIGNED_MAX */
#endif /* P99_UINTMAX_MAX */
#ifndef P99_UINTMAX_MAX
# define P00_MASK_104 0xFFFFFFFFFFFFFFFFFFFFFFFFFF
# if P00_UNSIGNED_MAX == 0xFFFFFFFFFFFFFFFFFFFFFFFFFF
#  define P99_UINTMAX_WIDTH 104
#  define P99_UINTMAX_MAX 0xFFFFFFFFFFFFFFFFFFFFFFFFFFU
#  define P00_B0 0xAAAAAAAAAAAAAAAAAAAAAAAAAAU
#  define P00_B1 0xCCCCCCCCCCCCCCCCCCCCCCCCCCU
#  define P00_B2 0xF0F0F0F0F0F0F0F0F0F0F0F0F0U
#  define P00_B3 0xFF00FF00FF00FF00FF00FF00U
#  define P00_B4 0xFFFF0000FFFF0000FFFF0000U
#  define P00_B5 0xFF00000000FFFFFFFF00000000U
#  define P00_B6 0xFFFFFFFFFF0000000000000000U
# endif /* P00_UNSIGNED_MAX */
#endif /* P99_UINTMAX_MAX */
#ifndef P99_UINTMAX_MAX
# define P00_MASK_105 0x1FFFFFFFFFFFFFFFFFFFFFFFFFF
# if P00_UNSIGNED_MAX == 0x1FFFFFFFFFFFFFFFFFFFFFFFFFF
#  define P99_UINTMAX_WIDTH 105
#  define P99_UINTMAX_MAX 0x1FFFFFFFFFFFFFFFFFFFFFFFFFFU
#  define P00_B0 0xAAAAAAAAAAAAAAAAAAAAAAAAAAU
#  define P00_B1 0xCCCCCCCCCCCCCCCCCCCCCCCCCCU
#  define P00_B2 0xF0F0F0F0F0F0F0F0F0F0F0F0F0U
#  define P00_B3 0x100FF00FF00FF00FF00FF00FF00U
#  define P00_B4 0xFFFF0000FFFF0000FFFF0000U
#  define P00_B5 0x1FF00000000FFFFFFFF00000000U
#  define P00_B6 0x1FFFFFFFFFF0000000000000000U
# endif /* P00_UNSIGNED_MAX */
#endif /* P99_UINTMAX_MAX */
#ifndef P99_UINTMAX_MAX
# define P00_MASK_106 0x3FFFFFFFFFFFFFFFFFFFFFFFFFF
# if P00_UNSIGNED_MAX == 0x3FFFFFFFFFFFFFFFFFFFFFFFFFF
#  define P99_UINTMAX_WIDTH 106
#  define P99_UINTMAX_MAX 0x3FFFFFFFFFFFFFFFFFFFFFFFFFFU
#  define P00_B0 0x2AAAAAAAAAAAAAAAAAAAAAAAAAAU
#  define P00_B1 0xCCCCCCCCCCCCCCCCCCCCCCCCCCU
#  define P00_B2 0xF0F0F0F0F0F0F0F0F0F0F0F0F0U
#  define P00_B3 0x300FF00FF00FF00FF00FF00FF00U
#  define P00_B4 0xFFFF0000FFFF0000FFFF0000U
#  define P00_B5 0x3FF00000000FFFFFFFF00000000U
#  define P00_B6 0x3FFFFFFFFFF0000000000000000U
# endif /* P00_UNSIGNED_MAX */
#endif /* P99_UINTMAX_MAX */
#ifndef P99_UINTMAX_MAX
# define P00_MASK_107 0x7FFFFFFFFFFFFFFFFFFFFFFFFFF
# if P00_UNSIGNED_MAX == 0x7FFFFFFFFFFFFFFFFFFFFFFFFFF
#  define P99_UINTMAX_WIDTH 107
#  define P99_UINTMAX_MAX 0x7FFFFFFFFFFFFFFFFFFFFFFFFFFU
#  define P00_B0 0x2AAAAAAAAAAAAAAAAAAAAAAAAAAU
#  define P00_B1 0x4CCCCCCCCCCCCCCCCCCCCCCCCCCU
#  define P00_B2 0xF0F0F0F0F0F0F0F0F0F0F0F0F0U
#  define P00_B3 0x700FF00FF00FF00FF00FF00FF00U
#  define P00_B4 0xFFFF0000FFFF0000FFFF0000U
#  define P00_B5 0x7FF00000000FFFFFFFF00000000U
#  define P00_B6 0x7FFFFFFFFFF0000000000000000U
# endif /* P00_UNSIGNED_MAX */
#endif /* P99_UINTMAX_MAX */
#ifndef P99_UINTMAX_MAX
# define P00_MASK_108 0xFFFFFFFFFFFFFFFFFFFFFFFFFFF
# if P00_UNSIGNED_MAX == 0xFFFFFFFFFFFFFFFFFFFFFFFFFFF
#  define P99_UINTMAX_WIDTH 108
#  define P99_UINTMAX_MAX 0xFFFFFFFFFFFFFFFFFFFFFFFFFFFU
#  define P00_B0 0xAAAAAAAAAAAAAAAAAAAAAAAAAAAU
#  define P00_B1 0xCCCCCCCCCCCCCCCCCCCCCCCCCCCU
#  define P00_B2 0xF0F0F0F0F0F0F0F0F0F0F0F0F0U
#  define P00_B3 0xF00FF00FF00FF00FF00FF00FF00U
#  define P00_B4 0xFFFF0000FFFF0000FFFF0000U
#  define P00_B5 0xFFF00000000FFFFFFFF00000000U
#  define P00_B6 0xFFFFFFFFFFF0000000000000000U
# endif /* P00_UNSIGNED_MAX */
#endif /* P99_UINTMAX_MAX */
#ifndef P99_UINTMAX_MAX
# define P00_MASK_109 0x1FFFFFFFFFFFFFFFFFFFFFFFFFFF
# if P00_UNSIGNED_MAX == 0x1FFFFFFFFFFFFFFFFFFFFFFFFFFF
#  define P99_UINTMAX_WIDTH 109
#  define P99_UINTMAX_MAX 0x1FFFFFFFFFFFFFFFFFFFFFFFFFFFU
#  define P00_B0 0xAAAAAAAAAAAAAAAAAAAAAAAAAAAU
#  define P00_B1 0xCCCCCCCCCCCCCCCCCCCCCCCCCCCU
#  define P00_B2 0x10F0F0F0F0F0F0F0F0F0F0F0F0F0U
#  define P00_B3 0x1F00FF00FF00FF00FF00FF00FF00U
#  define P00_B4 0xFFFF0000FFFF0000FFFF0000U
#  define P00_B5 0x1FFF00000000FFFFFFFF00000000U
#  define P00_B6 0x1FFFFFFFFFFF0000000000000000U
# endif /* P00_UNSIGNED_MAX */
#endif /* P99_UINTMAX_MAX */
#ifndef P99_UINTMAX_MAX
# define P00_MASK_110 0x3FFFFFFFFFFFFFFFFFFFFFFFFFFF
# if P00_UNSIGNED_MAX == 0x3FFFFFFFFFFFFFFFFFFFFFFFFFFF
#  define P99_UINTMAX_WIDTH 110
#  define P99_UINTMAX_MAX 0x3FFFFFFFFFFFFFFFFFFFFFFFFFFFU
#  define P00_B0 0x2AAAAAAAAAAAAAAAAAAAAAAAAAAAU
#  define P00_B1 0xCCCCCCCCCCCCCCCCCCCCCCCCCCCU
#  define P00_B2 0x30F0F0F0F0F0F0F0F0F0F0F0F0F0U
#  define P00_B3 0x3F00FF00FF00FF00FF00FF00FF00U
#  define P00_B4 0xFFFF0000FFFF0000FFFF0000U
#  define P00_B5 0x3FFF00000000FFFFFFFF00000000U
#  define P00_B6 0x3FFFFFFFFFFF0000000000000000U
# endif /* P00_UNSIGNED_MAX */
#endif /* P99_UINTMAX_MAX */
#ifndef P99_UINTMAX_MAX
# define P00_MASK_111 0x7FFFFFFFFFFFFFFFFFFFFFFFFFFF
# if P00_UNSIGNED_MAX == 0x7FFFFFFFFFFFFFFFFFFFFFFFFFFF
#  define P99_UINTMAX_WIDTH 111
#  define P99_UINTMAX_MAX 0x7FFFFFFFFFFFFFFFFFFFFFFFFFFFU
#  define P00_B0 0x2AAAAAAAAAAAAAAAAAAAAAAAAAAAU
#  define P00_B1 0x4CCCCCCCCCCCCCCCCCCCCCCCCCCCU
#  define P00_B2 0x70F0F0F0F0F0F0F0F0F0F0F0F0F0U
#  define P00_B3 0x7F00FF00FF00FF00FF00FF00FF00U
#  define P00_B4 0xFFFF0000FFFF0000FFFF0000U
#  define P00_B5 0x7FFF00000000FFFFFFFF00000000U
#  define P00_B6 0x7FFFFFFFFFFF0000000000000000U
# endif /* P00_UNSIGNED_MAX */
#endif /* P99_UINTMAX_MAX */
#ifndef P99_UINTMAX_MAX
# define P00_MASK_112 0xFFFFFFFFFFFFFFFFFFFFFFFFFFFF
# if P00_UNSIGNED_MAX == 0xFFFFFFFFFFFFFFFFFFFFFFFFFFFF
#  define P99_UINTMAX_WIDTH 112
#  define P99_UINTMAX_MAX 0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFU
#  define P00_B0 0xAAAAAAAAAAAAAAAAAAAAAAAAAAAAU
#  define P00_B1 0xCCCCCCCCCCCCCCCCCCCCCCCCCCCCU
#  define P00_B2 0xF0F0F0F0F0F0F0F0F0F0F0F0F0F0U
#  define P00_B3 0xFF00FF00FF00FF00FF00FF00FF00U
#  define P00_B4 0xFFFF0000FFFF0000FFFF0000U
#  define P00_B5 0xFFFF00000000FFFFFFFF00000000U
#  define P00_B6 0xFFFFFFFFFFFF0000000000000000U
# endif /* P00_UNSIGNED_MAX */
#endif /* P99_UINTMAX_MAX */
#ifndef P99_UINTMAX_MAX
# define P00_MASK_113 0x1FFFFFFFFFFFFFFFFFFFFFFFFFFFF
# if P00_UNSIGNED_MAX == 0x1FFFFFFFFFFFFFFFFFFFFFFFFFFFF
#  define P99_UINTMAX_WIDTH 113
#  define P99_UINTMAX_MAX 0x1FFFFFFFFFFFFFFFFFFFFFFFFFFFFU
#  define P00_B0 0xAAAAAAAAAAAAAAAAAAAAAAAAAAAAU
#  define P00_B1 0xCCCCCCCCCCCCCCCCCCCCCCCCCCCCU
#  define P00_B2 0xF0F0F0F0F0F0F0F0F0F0F0F0F0F0U
#  define P00_B3 0xFF00FF00FF00FF00FF00FF00FF00U
#  define P00_B4 0x10000FFFF0000FFFF0000FFFF0000U
#  define P00_B5 0x1FFFF00000000FFFFFFFF00000000U
#  define P00_B6 0x1FFFFFFFFFFFF0000000000000000U
# endif /* P00_UNSIGNED_MAX */
#endif /* P99_UINTMAX_MAX */
#ifndef P99_UINTMAX_MAX
# define P00_MASK_114 0x3FFFFFFFFFFFFFFFFFFFFFFFFFFFF
# if P00_UNSIGNED_MAX == 0x3FFFFFFFFFFFFFFFFFFFFFFFFFFFF
#  define P99_UINTMAX_WIDTH 114
#  define P99_UINTMAX_MAX 0x3FFFFFFFFFFFFFFFFFFFFFFFFFFFFU
#  define P00_B0 0x2AAAAAAAAAAAAAAAAAAAAAAAAAAAAU
#  define P00_B1 0xCCCCCCCCCCCCCCCCCCCCCCCCCCCCU
#  define P00_B2 0xF0F0F0F0F0F0F0F0F0F0F0F0F0F0U
#  define P00_B3 0xFF00FF00FF00FF00FF00FF00FF00U
#  define P00_B4 0x30000FFFF0000FFFF0000FFFF0000U
#  define P00_B5 0x3FFFF00000000FFFFFFFF00000000U
#  define P00_B6 0x3FFFFFFFFFFFF0000000000000000U
# endif /* P00_UNSIGNED_MAX */
#endif /* P99_UINTMAX_MAX */
#ifndef P99_UINTMAX_MAX
# define P00_MASK_115 0x7FFFFFFFFFFFFFFFFFFFFFFFFFFFF
# if P00_UNSIGNED_MAX == 0x7FFFFFFFFFFFFFFFFFFFFFFFFFFFF
#  define P99_UINTMAX_WIDTH 115
#  define P99_UINTMAX_MAX 0x7FFFFFFFFFFFFFFFFFFFFFFFFFFFFU
#  define P00_B0 0x2AAAAAAAAAAAAAAAAAAAAAAAAAAAAU
#  define P00_B1 0x4CCCCCCCCCCCCCCCCCCCCCCCCCCCCU
#  define P00_B2 0xF0F0F0F0F0F0F0F0F0F0F0F0F0F0U
#  define P00_B3 0xFF00FF00FF00FF00FF00FF00FF00U
#  define P00_B4 0x70000FFFF0000FFFF0000FFFF0000U
#  define P00_B5 0x7FFFF00000000FFFFFFFF00000000U
#  define P00_B6 0x7FFFFFFFFFFFF0000000000000000U
# endif /* P00_UNSIGNED_MAX */
#endif /* P99_UINTMAX_MAX */
#ifndef P99_UINTMAX_MAX
# define P00_MASK_116 0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
# if P00_UNSIGNED_MAX == 0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
#  define P99_UINTMAX_WIDTH 116
#  define P99_UINTMAX_MAX 0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFU
#  define P00_B0 0xAAAAAAAAAAAAAAAAAAAAAAAAAAAAAU
#  define P00_B1 0xCCCCCCCCCCCCCCCCCCCCCCCCCCCCCU
#  define P00_B2 0xF0F0F0F0F0F0F0F0F0F0F0F0F0F0U
#  define P00_B3 0xFF00FF00FF00FF00FF00FF00FF00U
#  define P00_B4 0xF0000FFFF0000FFFF0000FFFF0000U
#  define P00_B5 0xFFFFF00000000FFFFFFFF00000000U
#  define P00_B6 0xFFFFFFFFFFFFF0000000000000000U
# endif /* P00_UNSIGNED_MAX */
#endif /* P99_UINTMAX_MAX */
#ifndef P99_UINTMAX_MAX
# define P00_MASK_117 0x1FFFFFFFFFFFFFFFFFFFFFFFFFFFFF
# if P00_UNSIGNED_MAX == 0x1FFFFFFFFFFFFFFFFFFFFFFFFFFFFF
#  define P99_UINTMAX_WIDTH 117
#  define P99_UINTMAX_MAX 0x1FFFFFFFFFFFFFFFFFFFFFFFFFFFFFU
#  define P00_B0 0xAAAAAAAAAAAAAAAAAAAAAAAAAAAAAU
#  define P00_B1 0xCCCCCCCCCCCCCCCCCCCCCCCCCCCCCU
#  define P00_B2 0x10F0F0F0F0F0F0F0F0F0F0F0F0F0F0U
#  define P00_B3 0xFF00FF00FF00FF00FF00FF00FF00U
#  define P00_B4 0x1F0000FFFF0000FFFF0000FFFF0000U
#  define P00_B5 0x1FFFFF00000000FFFFFFFF00000000U
#  define P00_B6 0x1FFFFFFFFFFFFF0000000000000000U
# endif /* P00_UNSIGNED_MAX */
#endif /* P99_UINTMAX_MAX */
#ifndef P99_UINTMAX_MAX
# define P00_MASK_118 0x3FFFFFFFFFFFFFFFFFFFFFFFFFFFFF
# if P00_UNSIGNED_MAX == 0x3FFFFFFFFFFFFFFFFFFFFFFFFFFFFF
#  define P99_UINTMAX_WIDTH 118
#  define P99_UINTMAX_MAX 0x3FFFFFFFFFFFFFFFFFFFFFFFFFFFFFU
#  define P00_B0 0x2AAAAAAAAAAAAAAAAAAAAAAAAAAAAAU
#  define P00_B1 0xCCCCCCCCCCCCCCCCCCCCCCCCCCCCCU
#  define P00_B2 0x30F0F0F0F0F0F0F0F0F0F0F0F0F0F0U
#  define P00_B3 0xFF00FF00FF00FF00FF00FF00FF00U
#  define P00_B4 0x3F0000FFFF0000FFFF0000FFFF0000U
#  define P00_B5 0x3FFFFF00000000FFFFFFFF00000000U
#  define P00_B6 0x3FFFFFFFFFFFFF0000000000000000U
# endif /* P00_UNSIGNED_MAX */
#endif /* P99_UINTMAX_MAX */
#ifndef P99_UINTMAX_MAX
# define P00_MASK_119 0x7FFFFFFFFFFFFFFFFFFFFFFFFFFFFF
# if P00_UNSIGNED_MAX == 0x7FFFFFFFFFFFFFFFFFFFFFFFFFFFFF
#  define P99_UINTMAX_WIDTH 119
#  define P99_UINTMAX_MAX 0x7FFFFFFFFFFFFFFFFFFFFFFFFFFFFFU
#  define P00_B0 0x2AAAAAAAAAAAAAAAAAAAAAAAAAAAAAU
#  define P00_B1 0x4CCCCCCCCCCCCCCCCCCCCCCCCCCCCCU
#  define P00_B2 0x70F0F0F0F0F0F0F0F0F0F0F0F0F0F0U
#  define P00_B3 0xFF00FF00FF00FF00FF00FF00FF00U
#  define P00_B4 0x7F0000FFFF0000FFFF0000FFFF0000U
#  define P00_B5 0x7FFFFF00000000FFFFFFFF00000000U
#  define P00_B6 0x7FFFFFFFFFFFFF0000000000000000U
# endif /* P00_UNSIGNED_MAX */
#endif /* P99_UINTMAX_MAX */
#ifndef P99_UINTMAX_MAX
# define P00_MASK_120 0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
# if P00_UNSIGNED_MAX == 0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
#  define P99_UINTMAX_WIDTH 120
#  define P99_UINTMAX_MAX 0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFU
#  define P00_B0 0xAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAU
#  define P00_B1 0xCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCU
#  define P00_B2 0xF0F0F0F0F0F0F0F0F0F0F0F0F0F0F0U
#  define P00_B3 0xFF00FF00FF00FF00FF00FF00FF00U
#  define P00_B4 0xFF0000FFFF0000FFFF0000FFFF0000U
#  define P00_B5 0xFFFFFF00000000FFFFFFFF00000000U
#  define P00_B6 0xFFFFFFFFFFFFFF0000000000000000U
# endif /* P00_UNSIGNED_MAX */
#endif /* P99_UINTMAX_MAX */
#ifndef P99_UINTMAX_MAX
# define P00_MASK_121 0x1FFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
# if P00_UNSIGNED_MAX == 0x1FFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
#  define P99_UINTMAX_WIDTH 121
#  define P99_UINTMAX_MAX 0x1FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFU
#  define P00_B0 0xAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAU
#  define P00_B1 0xCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCU
#  define P00_B2 0xF0F0F0F0F0F0F0F0F0F0F0F0F0F0F0U
#  define P00_B3 0x100FF00FF00FF00FF00FF00FF00FF00U
#  define P00_B4 0x1FF0000FFFF0000FFFF0000FFFF0000U
#  define P00_B5 0x1FFFFFF00000000FFFFFFFF00000000U
#  define P00_B6 0x1FFFFFFFFFFFFFF0000000000000000U
# endif /* P00_UNSIGNED_MAX */
#endif /* P99_UINTMAX_MAX */
#ifndef P99_UINTMAX_MAX
# define P00_MASK_122 0x3FFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
# if P00_UNSIGNED_MAX == 0x3FFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
#  define P99_UINTMAX_WIDTH 122
#  define P99_UINTMAX_MAX 0x3FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFU
#  define P00_B0 0x2AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAU
#  define P00_B1 0xCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCU
#  define P00_B2 0xF0F0F0F0F0F0F0F0F0F0F0F0F0F0F0U
#  define P00_B3 0x300FF00FF00FF00FF00FF00FF00FF00U
#  define P00_B4 0x3FF0000FFFF0000FFFF0000FFFF0000U
#  define P00_B5 0x3FFFFFF00000000FFFFFFFF00000000U
#  define P00_B6 0x3FFFFFFFFFFFFFF0000000000000000U
# endif /* P00_UNSIGNED_MAX */
#endif /* P99_UINTMAX_MAX */
#ifndef P99_UINTMAX_MAX
# define P00_MASK_123 0x7FFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
# if P00_UNSIGNED_MAX == 0x7FFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
#  define P99_UINTMAX_WIDTH 123
#  define P99_UINTMAX_MAX 0x7FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFU
#  define P00_B0 0x2AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAU
#  define P00_B1 0x4CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCU
#  define P00_B2 0xF0F0F0F0F0F0F0F0F0F0F0F0F0F0F0U
#  define P00_B3 0x700FF00FF00FF00FF00FF00FF00FF00U
#  define P00_B4 0x7FF0000FFFF0000FFFF0000FFFF0000U
#  define P00_B5 0x7FFFFFF00000000FFFFFFFF00000000U
#  define P00_B6 0x7FFFFFFFFFFFFFF0000000000000000U
# endif /* P00_UNSIGNED_MAX */
#endif /* P99_UINTMAX_MAX */
#ifndef P99_UINTMAX_MAX
# define P00_MASK_124 0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
# if P00_UNSIGNED_MAX == 0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
#  define P99_UINTMAX_WIDTH 124
#  define P99_UINTMAX_MAX 0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFU
#  define P00_B0 0xAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAU
#  define P00_B1 0xCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCU
#  define P00_B2 0xF0F0F0F0F0F0F0F0F0F0F0F0F0F0F0U
#  define P00_B3 0xF00FF00FF00FF00FF00FF00FF00FF00U
#  define P00_B4 0xFFF0000FFFF0000FFFF0000FFFF0000U
#  define P00_B5 0xFFFFFFF00000000FFFFFFFF00000000U
#  define P00_B6 0xFFFFFFFFFFFFFFF0000000000000000U
# endif /* P00_UNSIGNED_MAX */
#endif /* P99_UINTMAX_MAX */
#ifndef P99_UINTMAX_MAX
# define P00_MASK_125 0x1FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
# if P00_UNSIGNED_MAX == 0x1FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
#  define P99_UINTMAX_WIDTH 125
#  define P99_UINTMAX_MAX 0x1FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFU
#  define P00_B0 0xAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAU
#  define P00_B1 0xCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCU
#  define P00_B2 0x10F0F0F0F0F0F0F0F0F0F0F0F0F0F0F0U
#  define P00_B3 0x1F00FF00FF00FF00FF00FF00FF00FF00U
#  define P00_B4 0x1FFF0000FFFF0000FFFF0000FFFF0000U
#  define P00_B5 0x1FFFFFFF00000000FFFFFFFF00000000U
#  define P00_B6 0x1FFFFFFFFFFFFFFF0000000000000000U
# endif /* P00_UNSIGNED_MAX */
#endif /* P99_UINTMAX_MAX */
#ifndef P99_UINTMAX_MAX
# define P00_MASK_126 0x3FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
# if P00_UNSIGNED_MAX == 0x3FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
#  define P99_UINTMAX_WIDTH 126
#  define P99_UINTMAX_MAX 0x3FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFU
#  define P00_B0 0x2AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAU
#  define P00_B1 0xCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCU
#  define P00_B2 0x30F0F0F0F0F0F0F0F0F0F0F0F0F0F0F0U
#  define P00_B3 0x3F00FF00FF00FF00FF00FF00FF00FF00U
#  define P00_B4 0x3FFF0000FFFF0000FFFF0000FFFF0000U
#  define P00_B5 0x3FFFFFFF00000000FFFFFFFF00000000U
#  define P00_B6 0x3FFFFFFFFFFFFFFF0000000000000000U
# endif /* P00_UNSIGNED_MAX */
#endif /* P99_UINTMAX_MAX */
#ifndef P99_UINTMAX_MAX
# define P00_MASK_127 0x7FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
# if P00_UNSIGNED_MAX == 0x7FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
#  define P99_UINTMAX_WIDTH 127
#  define P99_UINTMAX_MAX 0x7FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFU
#  define P00_B0 0x2AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAU
#  define P00_B1 0x4CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCU
#  define P00_B2 0x70F0F0F0F0F0F0F0F0F0F0F0F0F0F0F0U
#  define P00_B3 0x7F00FF00FF00FF00FF00FF00FF00FF00U
#  define P00_B4 0x7FFF0000FFFF0000FFFF0000FFFF0000U
#  define P00_B5 0x7FFFFFFF00000000FFFFFFFF00000000U
#  define P00_B6 0x7FFFFFFFFFFFFFFF0000000000000000U
# endif /* P00_UNSIGNED_MAX */
#endif /* P99_UINTMAX_MAX */
#ifndef P99_UINTMAX_MAX
# define P00_MASK_128 0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
# if P00_UNSIGNED_MAX == 0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
#  define P99_UINTMAX_WIDTH 128
#  define P99_UINTMAX_MAX 0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFU
#  define P00_B0 0xAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAU
#  define P00_B1 0xCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCU
#  define P00_B2 0xF0F0F0F0F0F0F0F0F0F0F0F0F0F0F0F0U
#  define P00_B3 0xFF00FF00FF00FF00FF00FF00FF00FF00U
#  define P00_B4 0xFFFF0000FFFF0000FFFF0000FFFF0000U
#  define P00_B5 0xFFFFFFFF00000000FFFFFFFF00000000U
#  define P00_B6 0xFFFFFFFFFFFFFFFF0000000000000000U
# endif /* P00_UNSIGNED_MAX */
#endif /* P99_UINTMAX_MAX */
#define P00_MASK_0 0x0
#define P00_MASK_1 0x1
#define P00_MASK_2 0x3
#define P00_MASK_3 0x7
#define P00_MASK_4 0xF
#define P00_MASK_5 0x1F
#define P00_MASK_6 0x3F
#define P00_MASK_7 0x7F
#define P00_MASK_8 0xFF
#define P00_MASK_9 0x1FF
#define P00_MASK_10 0x3FF
#define P00_MASK_11 0x7FF
#define P00_MASK_12 0xFFF
#define P00_MASK_13 0x1FFF
#define P00_MASK_14 0x3FFF
#define P00_MASK_15 0x7FFF
#define P00_MASK_16 0xFFFF
#define P00_MASK_17 0x1FFFF
#define P00_MASK_18 0x3FFFF
#define P00_MASK_19 0x7FFFF
#define P00_MASK_20 0xFFFFF
#define P00_MASK_21 0x1FFFFF
#define P00_MASK_22 0x3FFFFF
#define P00_MASK_23 0x7FFFFF
#define P00_MASK_24 0xFFFFFF
#define P00_MASK_25 0x1FFFFFF
#define P00_MASK_26 0x3FFFFFF
#define P00_MASK_27 0x7FFFFFF
#define P00_MASK_28 0xFFFFFFF
#define P00_MASK_29 0x1FFFFFFF
#define P00_MASK_30 0x3FFFFFFF
#define P00_MASK_31 0x7FFFFFFF
#define P00_MASK_32 0xFFFFFFFF
#define P00_MASK_33 0x1FFFFFFFF
#define P00_MASK_34 0x3FFFFFFFF
#define P00_MASK_35 0x7FFFFFFFF
#define P00_MASK_36 0xFFFFFFFFF
#define P00_MASK_37 0x1FFFFFFFFF
#define P00_MASK_38 0x3FFFFFFFFF
#define P00_MASK_39 0x7FFFFFFFFF
#define P00_MASK_40 0xFFFFFFFFFF
#define P00_MASK_41 0x1FFFFFFFFFF
#define P00_MASK_42 0x3FFFFFFFFFF
#define P00_MASK_43 0x7FFFFFFFFFF
#define P00_MASK_44 0xFFFFFFFFFFF
#define P00_MASK_45 0x1FFFFFFFFFFF
#define P00_MASK_46 0x3FFFFFFFFFFF
#define P00_MASK_47 0x7FFFFFFFFFFF
#define P00_MASK_48 0xFFFFFFFFFFFF
#define P00_MASK_49 0x1FFFFFFFFFFFF
#define P00_MASK_50 0x3FFFFFFFFFFFF
#define P00_MASK_51 0x7FFFFFFFFFFFF
#define P00_MASK_52 0xFFFFFFFFFFFFF
#define P00_MASK_53 0x1FFFFFFFFFFFFF
#define P00_MASK_54 0x3FFFFFFFFFFFFF
#define P00_MASK_55 0x7FFFFFFFFFFFFF
#define P00_MASK_56 0xFFFFFFFFFFFFFF
#define P00_MASK_57 0x1FFFFFFFFFFFFFF
#define P00_MASK_58 0x3FFFFFFFFFFFFFF
#define P00_MASK_59 0x7FFFFFFFFFFFFFF
#define P00_MASK_60 0xFFFFFFFFFFFFFFF
#define P00_MASK_61 0x1FFFFFFFFFFFFFFF
#define P00_MASK_62 0x3FFFFFFFFFFFFFFF
#define P00_MASK_63 0x7FFFFFFFFFFFFFFF

//! @addtogroup P99
//! @{


#define P00_P99

//! @addtogroup compiler
//! @{


#define P00_compiler

//! @addtogroup compiler_utilities
//! @{


#define P00_compiler_utilities

//! @}

//! @addtogroup C11
//! @{


#define P00_C11

//! @addtogroup C11_keywords
//! @{


#define P00_C11_keywords

//! @}

//! @addtogroup C11_types
//! @{


#define P00_C11_types

//! @}

//! @addtogroup generic
//! @{


#define P00_generic

//! @addtogroup C11_types
//! @{


#define P00_C11_types

//! @addtogroup type_generic
//! @{


#define P00_type_generic

//! @}

//! @}

//! @addtogroup qualifiers
//! @{


#define P00_qualifiers

//! @}

//! @addtogroup tgprint
//! @{


#define P00_tgprint

//! @}

//! @}

//! @addtogroup atomic
//! @{


#define P00_atomic

//! @}

//! @addtogroup threads
//! @{


#define P00_threads

//! @}

//! @addtogroup C11_library
//! @{


#define P00_C11_library

//! @}

//! @}

//! @}

//! @addtogroup library_support
//! @{


#define P00_library_support

//! @addtogroup futex
//! @{


#define P00_futex

//! @}

//! @addtogroup library_wrappers
//! @{


#define P00_library_wrappers

//! @}

//! @addtogroup posix_default
//! @{


#define P00_posix_default

//! @}

//! @addtogroup callbacks
//! @{


#define P00_callbacks

//! @}

//! @addtogroup startup_hooks
//! @{


#define P00_startup_hooks

//! @}

//! @}

//! @addtogroup preprocessor_macros
//! @{


#define P00_preprocessor_macros

//! @addtogroup meta_programming
//! @{


#define P00_meta_programming

//! @addtogroup preprocessor_conditionals
//! @{


#define P00_preprocessor_conditionals

//! @}

//! @addtogroup preprocessor_for
//! @{


#define P00_preprocessor_for

//! @}

//! @addtogroup preprocessor_blocks
//! @{


#define P00_preprocessor_blocks

//! @addtogroup try
//! @{


#define P00_try

//! @}

//! @addtogroup validity
//! @{


#define P00_validity

//! @}

//! @}

//! @addtogroup double_constants
//! @{


#define P00_double_constants

//! @}

//! @addtogroup classification
//! @{


#define P00_classification

//! @}

//! @addtogroup list_processing
//! @{


#define P00_list_processing

//! @addtogroup basic_list_operations
//! @{


#define P00_basic_list_operations

//! @}

//! @addtogroup statement_lists
//! @{


#define P00_statement_lists

//! @}

//! @}

//! @}

//! @addtogroup preprocessor_operators
//! @{


#define P00_preprocessor_operators

//! @addtogroup preprocessor_logic
//! @{


#define P00_preprocessor_logic

//! @}

//! @addtogroup preprocessor_arithmetic
//! @{


#define P00_preprocessor_arithmetic

//! @}

//! @addtogroup preprocessor_text
//! @{


#define P00_preprocessor_text

//! @}

//! @}

//! @addtogroup code_augmenting
//! @{


#define P00_code_augmenting

//! @addtogroup preprocessor_allocation
//! @{


#define P00_preprocessor_allocation

//! @}

//! @addtogroup preprocessor_initialization
//! @{


#define P00_preprocessor_initialization

//! @}

//! @addtogroup default_arguments
//! @{


#define P00_default_arguments

//! @}

//! @addtogroup variadic
//! @{


#define P00_variadic

//! @}

//! @addtogroup VLA
//! @{


#define P00_VLA

//! @}

//! @addtogroup types
//! @{


#define P00_types

//! @addtogroup typenames
//! @{


#define P00_typenames

//! @addtogroup one_token
//! @{


#define P00_one_token

//! @}

//! @addtogroup bool_specials
//! @{


#define P00_bool_specials

//! @}

//! @}

//! @}

//! @addtogroup stringconversion
//! @{


#define P00_stringconversion

//! @}

//! @addtogroup integers
//! @{


#define P00_integers

//! @}

//! @}

//! @}

//! @}

/* This long list of compilers does not mean that we tested P99, nor
   does it even imply that there is a C99 mode for them. We just list
   compilers and detection macros for them for completeness. The
   information for that detection was wildly collected from the web.
   They are listed in alphabetic order, and their numbering is
   nothing that is supposed to stay fixed, reliable or anything. */
#define P99_COMPILER_APPLE 1U
#define P00_COMPILER_PRAGMA_APPLE(...)
#define P99_COMPILER_ARMCC 2U
#define P00_COMPILER_PRAGMA_ARMCC(...)
#define P99_COMPILER_BORLAND 4U
#define P00_COMPILER_PRAGMA_BORLAND(...)
#define P99_COMPILER_CLANG 8U
#define P00_COMPILER_PRAGMA_CLANG(...)
#define P99_COMPILER_COMEAU 16U
#define P00_COMPILER_PRAGMA_COMEAU(...)
#define P99_COMPILER_CRAY 32U
#define P00_COMPILER_PRAGMA_CRAY(...)
#define P99_COMPILER_DEC 64U
#define P00_COMPILER_PRAGMA_DEC(...)
#define P99_COMPILER_DIAB 128U
#define P00_COMPILER_PRAGMA_DIAB(...)
#define P99_COMPILER_GNU 256U
#define P00_COMPILER_PRAGMA_GNU(...)
#define P99_COMPILER_HP 512U
#define P00_COMPILER_PRAGMA_HP(...)
#define P99_COMPILER_IBM 1024U
#define P00_COMPILER_PRAGMA_IBM(...)
#define P99_COMPILER_INTEL 2048U
#define P00_COMPILER_PRAGMA_INTEL(...)
#define P99_COMPILER_KAI 4096U
#define P00_COMPILER_PRAGMA_KAI(...)
#define P99_COMPILER_LCC 8192U
#define P00_COMPILER_PRAGMA_LCC(...)
#define P99_COMPILER_METROWERKS 16384U
#define P00_COMPILER_PRAGMA_METROWERKS(...)
#define P99_COMPILER_MICROSOFT 32768U
#define P00_COMPILER_PRAGMA_MICROSOFT(...)
#define P99_COMPILER_OPEN64 65536U
#define P00_COMPILER_PRAGMA_OPEN64(...)
#define P99_COMPILER_PCC 131072U
#define P00_COMPILER_PRAGMA_PCC(...)
#define P99_COMPILER_PORTLAND 262144U
#define P00_COMPILER_PRAGMA_PORTLAND(...)
#define P99_COMPILER_SGI 524288U
#define P00_COMPILER_PRAGMA_SGI(...)
#define P99_COMPILER_SUN 1048576U
#define P00_COMPILER_PRAGMA_SUN(...)
#define P99_COMPILER_TINYC 2097152U
#define P00_COMPILER_PRAGMA_TINYC(...)
#define P99_COMPILER_WATCOM 4194304U
#define P00_COMPILER_PRAGMA_WATCOM(...)
#if defined(__ARMCC_VERSION)
# define P99_COMPILER 2U
# define P99_COMPILER_VERSION "armcc "
# undef P00_COMPILER_PRAGMA_ARMCC
# define P00_COMPILER_PRAGMA_ARMCC(...) _Pragma(__VA_ARGS__)
#elif defined(__BORLANDC__)
# define P99_COMPILER 4U
# define P99_COMPILER_VERSION "borland "
# undef P00_COMPILER_PRAGMA_BORLAND
# define P00_COMPILER_PRAGMA_BORLAND(...) _Pragma(__VA_ARGS__)
#elif defined(__COMO__)
# define P99_COMPILER 16U
# define P99_COMPILER_VERSION "comeau "
# undef P00_COMPILER_PRAGMA_COMEAU
# define P00_COMPILER_PRAGMA_COMEAU(...) _Pragma(__VA_ARGS__)
#elif defined(_CRAYC)
# define P99_COMPILER 32U
# define P99_COMPILER_VERSION "cray "
# undef P00_COMPILER_PRAGMA_CRAY
# define P00_COMPILER_PRAGMA_CRAY(...) _Pragma(__VA_ARGS__)
#elif defined(__DECC_VER)
# define P99_COMPILER 64U
# define P99_COMPILER_VERSION "dec "
# undef P00_COMPILER_PRAGMA_DEC
# define P00_COMPILER_PRAGMA_DEC(...) _Pragma(__VA_ARGS__)
#elif defined(__DCC__)
# define P99_COMPILER 128U
# define P99_COMPILER_VERSION "diab "
# undef P00_COMPILER_PRAGMA_DIAB
# define P00_COMPILER_PRAGMA_DIAB(...) _Pragma(__VA_ARGS__)
#elif defined(__HP_cc)
# define P99_COMPILER 512U
# define P99_COMPILER_VERSION "hp "
# undef P00_COMPILER_PRAGMA_HP
# define P00_COMPILER_PRAGMA_HP(...) _Pragma(__VA_ARGS__)
#elif defined(__IBMC__)
# define P99_COMPILER 1024U
# define P99_COMPILER_VERSION "ibm "
# undef P00_COMPILER_PRAGMA_IBM
# define P00_COMPILER_PRAGMA_IBM(...) _Pragma(__VA_ARGS__)
#elif defined(__INTEL_COMPILER)
# define P99_COMPILER 2048U
# define P99_COMPILER_VERSION "intel "
# undef P00_COMPILER_PRAGMA_INTEL
# define P00_COMPILER_PRAGMA_INTEL(...) _Pragma(__VA_ARGS__)
#elif defined(__KCC)
# define P99_COMPILER 4096U
# define P99_COMPILER_VERSION "kai "
# undef P00_COMPILER_PRAGMA_KAI
# define P00_COMPILER_PRAGMA_KAI(...) _Pragma(__VA_ARGS__)
#elif defined(__LCC__)
# define P99_COMPILER 8192U
# define P99_COMPILER_VERSION "lcc "
# undef P00_COMPILER_PRAGMA_LCC
# define P00_COMPILER_PRAGMA_LCC(...) _Pragma(__VA_ARGS__)
#elif defined(__MWERKS__)
# define P99_COMPILER 16384U
# define P99_COMPILER_VERSION "metrowerks "
# undef P00_COMPILER_PRAGMA_METROWERKS
# define P00_COMPILER_PRAGMA_METROWERKS(...) _Pragma(__VA_ARGS__)
#elif defined(_MSC_VER)
# define P99_COMPILER 32768U
# define P99_COMPILER_VERSION "microsoft "
# undef P00_COMPILER_PRAGMA_MICROSOFT
# define P00_COMPILER_PRAGMA_MICROSOFT(...) _Pragma(__VA_ARGS__)
#elif defined(__OPEN64__)
# define P99_COMPILER 65536U
# define P99_COMPILER_VERSION "open64 "
# undef P00_COMPILER_PRAGMA_OPEN64
# define P00_COMPILER_PRAGMA_OPEN64(...) _Pragma(__VA_ARGS__)
#elif defined(__PCC__)
# define P99_COMPILER 131072U
# define P99_COMPILER_VERSION "pcc "
# undef P00_COMPILER_PRAGMA_PCC
# define P00_COMPILER_PRAGMA_PCC(...) _Pragma(__VA_ARGS__)
#elif defined(__PGI)
# define P99_COMPILER 262144U
# define P99_COMPILER_VERSION "portland "
# undef P00_COMPILER_PRAGMA_PORTLAND
# define P00_COMPILER_PRAGMA_PORTLAND(...) _Pragma(__VA_ARGS__)
#elif defined(__sgi)
# define P99_COMPILER 524288U
# define P99_COMPILER_VERSION "sgi "
# undef P00_COMPILER_PRAGMA_SGI
# define P00_COMPILER_PRAGMA_SGI(...) _Pragma(__VA_ARGS__)
#elif defined(__SUNPRO_C)
# define P99_COMPILER 1048576U
# define P99_COMPILER_VERSION "sun "
# undef P00_COMPILER_PRAGMA_SUN
# define P00_COMPILER_PRAGMA_SUN(...) _Pragma(__VA_ARGS__)
#elif defined(__TINYC__)
# define P99_COMPILER 2097152U
# define P99_COMPILER_VERSION "tinyc "
# undef P00_COMPILER_PRAGMA_TINYC
# define P00_COMPILER_PRAGMA_TINYC(...) _Pragma(__VA_ARGS__)
#elif defined(__WATCOMC__)
# define P99_COMPILER 4194304U
# define P99_COMPILER_VERSION "watcom "
# undef P00_COMPILER_PRAGMA_WATCOM
# define P00_COMPILER_PRAGMA_WATCOM(...) _Pragma(__VA_ARGS__)
#elif defined(__apple_build_version__)
# define P99_COMPILER 1U
# define P99_COMPILER_VERSION "apple "
# undef P00_COMPILER_PRAGMA_APPLE
# define P00_COMPILER_PRAGMA_APPLE(...) _Pragma(__VA_ARGS__)
#elif defined(__clang__)
# define P99_COMPILER 8U
# define P99_COMPILER_VERSION "clang "
# undef P00_COMPILER_PRAGMA_CLANG
# define P00_COMPILER_PRAGMA_CLANG(...) _Pragma(__VA_ARGS__)
#elif defined(__GNUC__)
# define P99_COMPILER 256U
# define P99_COMPILER_VERSION "gnu "
# undef P00_COMPILER_PRAGMA_GNU
# define P00_COMPILER_PRAGMA_GNU(...) _Pragma(__VA_ARGS__)
#else
# define P99_COMPILER 0
#endif

#endif /* P99_GENERATED_H */
