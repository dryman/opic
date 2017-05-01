// city_workaround.cc ---
//
// Filename: city_workaround.cc
// Description:
// Author: Felix Chern
// Maintainer:
// Copyright: (c) 2017 Felix Chern
// Created: Sun Apr 30 23:57:05 2017 (-0700)
// Version:
// Package-Requires: ()
// Last-Updated:
//           By:
//     Update #: 0
// URL:
// Doc URL:
// Keywords:
// Compatibility:
//
//

// Commentary:
//
//
//
//

// Change Log:
//
//
//
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or (at
// your option) any later version.
//
// This program is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
//

// Code:

#include <city.h>
#include <cstdint>

extern "C" uint64_t CCityHash64(const char *buf, size_t len)
{
  return CityHash64(buf, len);
}

//
// city_workaround.cc ends here
