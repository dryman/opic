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

#ifndef MAGIC_H
#define MAGIC_H 1

#include <assert.h>
#include <stdint.h>

#define OPHEAP_SIZE (1L << 36)
#define VPAGE_MASK (~((1L << 21) - 1))
#define PPAGE_MASK (~((1L << 12) - 1))
#define VSPAN_NUM (1 << 15)
#define VSPAN_BMAP_NUM (1 << 9)

#define TYPED_USPAN_PATTERN 0
#define RAW_USPAN_PATTERN 1
#define LARGE_USPAN_PATTERN 2
#define BLOBSPAN_PATTERN 3
#define TYPED_HPAGE_PATTERN 4
#define RAW_HPAGE_PATTERN 5
#define BLOB_HPAGE_PATTERN 6

// TODO the first hpage might need its own pattern?

typedef union Magic
{
  // generic struct only for querying pattern
  struct
  {
    uint8_t pattern : 4;
    uint32_t padding : 28;
  } generic;
  struct
  {
    uint8_t pattern : 4;
    uint16_t obj_size : 12;
    uint16_t padding;
  } uspan_generic;
  struct
  {
    uint8_t pattern : 4;
    uint16_t obj_size : 12;
    uint8_t thread_id : 4;
    uint16_t type_alias : 12;
  } typed_uspan;
  struct
  {
    uint8_t pattern : 4;
    uint16_t obj_size : 12; // obj_size is size_class
    uint8_t thread_id : 4;
    uint16_t padding : 12;
  } raw_uspan;
  struct
  {
    uint8_t pattern : 4;
    uint16_t obj_size : 12; // obj_size is size_class
    uint16_t padding;
  } large_uspan;
  struct
  {
    uint8_t pattern : 4;
    uint16_t pages : 12;
    uint16_t reserved;
  } blobspan;
  struct
  {
    uint8_t pattern : 4;
    uint16_t type_alias : 12;
    uint16_t reserved;
  } typed_hpage;
  struct
  {
    uint8_t pattern : 4;
    uint32_t reserved : 28;
  } raw_hpage;
  struct
  {
    uint8_t pattern : 4;
    uint16_t reserved : 12;
    uint16_t huge_pages;
  } blob_hpage;
} Magic;

static_assert(sizeof(Magic) == 4, "Magic should be 32bit");

#endif
/* magic.h ends here */
