/* row_schema.h ---
 *
 * Filename: row_schema.h
 * Description:
 * Author: Felix Chern
 * Maintainer:
 * Copyright: (c) 2017 Felix Chern
 * Created: Sat Aug 26 10:58:19 2017 (-0700)
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

#ifndef OPIC_TABLE_ROW_SCHEMA_H
#define OPIC_TABLE_ROW_SCHEMA_H

#include "opic/common/op_macros.h"
#include <stddef.h>

OP_BEGIN_DECLS

typedef enum RSFieldType RSFieldType;
typedef struct RSField RSField;

enum RSFieldType
  {
    RS_INT_8 = 1,
    RS_INT_16 = 2,
    RS_INT_32 = 3,
    RS_INT_64 = 4,
    RS_UINT_8 = 5,
    RS_UINT_16 = 6,
    RS_UINT_32 = 7,
    RS_UINT_64 = 8,
    RS_STR = 9,
    RS_BLOB = 10,
    RS_RESERVED = 65535,
  } __attribute__((packed));

struct RSField
{
  RSFieldType rstype;
  size_t offset;
  size_t size;
};

struct RSFieldAlias
{
  RSFieldType rstype;
  void* data;
  size_t size;
}

OP_END_DECLS

#endif

/* row_schema.h ends here */
