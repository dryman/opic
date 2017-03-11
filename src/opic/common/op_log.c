/* op_log.c ---
 *
 * Filename: op_log.c
 * Description:
 * Author: Felix Chern
 * Maintainer:
 * Copyright: (c) 2016-2017 Felix Chern
 * Created: Sep 3, 2016
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


#include <stdbool.h>
#include "config.h"
#include "op_log.h"

static bool _log4c_initialized;

void opic_log4c_init()
{
  if (!_log4c_initialized)
    {
      log4c_init();
      _log4c_initialized = true;
    }
}

/* op_log.c ends here */
