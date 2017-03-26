/* magic.h ---
 *
 * Filename: magic.h
 * Description:
 * Author: Felix Chern
 * Maintainer:
 * Copyright: (c) 2016 Felix Chern
 * Created: Sun Nov  6 2016
 * Version:
 * Package-Requires: ()
 * Last-Updated:
 *           By:
 *     Update #: 0
 * URL:
 * Doc URL:
 * Keywords:
 * Compatibility:
 *
 */

/* Commentary:
 *
 *
 *
 */

/* Change Log:
 *
 *
 */

/* This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or (at
 * your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/* Code: */

#ifndef OPIC_MALLOC_MAGIC_H
#define OPIC_MALLOC_MAGIC_H 1

#include <assert.h>
#include <stdint.h>

#define OPHEAP_VERSION 3

#define HPAGE_BITS 21
#define SPAGE_BITS 12
#define HPAGE_SIZE (1UL << HPAGE_BITS)
#define SPAGE_SIZE (1UL << SPAGE_BITS)
#define HPAGE_BMAP_NUM 512
#define TYPE_ALIAS_NUM 2048

typedef union Magic Magic;
typedef enum MagicPattern MagicPattern;

enum MagicPattern
  {
    TYPED_USPAN_PATTERN = 0,
    RAW_USPAN_PATTERN = 1,
    LARGE_USPAN_PATTERN = 2,
    SMALL_BLOB_PATTERN = 3,
    TYPED_HPAGE_PATTERN = 4,
    RAW_HPAGE_PATTERN = 5,
    HUGE_BLOB_PATTERN = 6,
  } __attribute__((packed));

static_assert(sizeof(MagicPattern) == 1, "MagicPattern is 1 byte");

union Magic
{
  // generic struct only for querying pattern
  struct
  {
    MagicPattern pattern : 4;
    uint32_t padding : 28;
  } generic;
  struct
  {
    MagicPattern pattern : 4;
    uint16_t obj_size : 12;
    uint16_t padding;
  } uspan_generic;
  struct
  {
    MagicPattern pattern : 4;
    uint16_t obj_size : 12;
    uint8_t thread_id : 4;
    uint16_t type_alias : 12;
  } typed_uspan;
  struct
  {
    MagicPattern pattern : 4;
    uint16_t obj_size : 12; // obj_size is size_class
    uint8_t thread_id : 4;
    uint16_t padding : 12;
  } raw_uspan;
  struct
  {
    MagicPattern pattern : 4;
    uint16_t obj_size : 12; // obj_size is size_class
    uint16_t padding;
  } large_uspan;
  struct
  {
    MagicPattern pattern : 4;
    uint16_t pages : 12;
    uint16_t reserved;
  } small_blob;
  struct
  {
    MagicPattern pattern : 4;
    uint16_t type_alias : 12;
    uint16_t reserved;
  } typed_hpage;
  struct
  {
    MagicPattern pattern : 4;
    uint32_t reserved : 28;
  } raw_hpage;
  struct
  {
    MagicPattern pattern : 4;
    uint16_t reserved : 12;
    uint16_t huge_pages;
  } huge_blob;
  uint32_t int_value;
};

static_assert(sizeof(Magic) == 4, "sizeof(Magic)");

#endif
/* magic.h ends here */
