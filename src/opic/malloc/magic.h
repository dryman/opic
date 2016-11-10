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

typedef union Magic
{
  // generic struct only for querying pattern
  struct
  {
    uint8_t pattern : 4;
    uint32_t padding : 28;
  } generic;
  // pattern = 0
  struct
  {
    uint8_t pattern : 4;
    uint16_t obj_size : 12;
    uint8_t thread_id : 4;
    uint16_t type_alias : 12;
  } typed_uspan;
  // pattern = 1
  struct
  {
    uint8_t pattern : 4;
    uint16_t obj_size : 12; // obj_size is size_class
    uint8_t thread_id : 4;
    uint16_t padding : 12;      
  } raw_uspan;
  // pattern = 2
  struct
  {
    uint8_t pattern : 4;
    uint16_t obj_size : 12;
    uint8_t thread_id : 4;
    uint16_t type_alias : 12;
  } typed_polyspan;
  // pattern = 3
  struct
  {
    uint8_t pattern : 4;
    uint16_t obj_size : 12;
    uint8_t thread_id : 4;
    uint16_t size_class : 12;      
  } raw_polyspan;
  // pattern = 4
  struct
  {
    uint8_t pattern : 4;
    uint16_t pages : 12;
    uint16_t reserved;
  } blobspan;
  // pattern = 5
  struct
  {
    uint8_t pattern : 4;
    uint16_t type_alias : 12;
    uint16_t reserved;
  } typed_hpage;
  // pattern = 6
  struct
  {
    uint8_t pattern : 4;
    uint32_t reserved : 28;
  } raw_hpage;
  // pattern = 7
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
