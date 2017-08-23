Object Persistence In C (Beta)
===================================

[![Build Status](https://travis-ci.org/dryman/opic.svg?branch=master)](https://travis-ci.org/dryman/opic)

OPIC is a revolutionary serialization framework for C.  Unlike traditional
approaches which walk through the in-memory objects and write it to disk, OPIC
itself is a memory allocator where all the objects created with it have the same
representation in memory and on disk. "Serializing/deserializing" is extreme
cheap with OPIC, because the memory can write directly to disk, and the
deserialization is simply a mmap syscall.


OPIC is suitable for building database indexes, key-value store, or even search
engines. At the moment of writing we provide a hash table to demonstrate how
easy it is to build an embedded key-value store engine.

SYNOPSIS
--------

```c
#include "opic/op_malloc.h"
#include "opic/hash/op_hash_table.h"

struct S1
{
  opref_t s2_ref;
};

struct S2
{
  char[1024] data;
};

void simple_object_database(char* filename)
{
  OPHeap* heap1, heap2;

  OPHeapNew(&heap1);

  struct S1* s1 = (struct S1*)OPMalloc(heap1, sizeof(struct S1));
  struct S2* s2 = (struct S2*)OPMalloc(heap1, sizeof(struct S2));

  // object relationships in OPIC must convert to opref_t
  s1->s2_ref = OPPtr2Ref(s2);

  // opref_t can convert back to pointer via OPRef2Ptr
  struct S2* s2_ptr = OPRef2Ptr(heap1, s1->s2ref);

  // Serialize the heap to a file
  OPHeapStorePtr(heap1, s1, 0);

  fd = fopen(filename, "w");
  OPHeapWrite(heap1, fd)
  fclose(fd);
  OPHeapDestroy(heap1);

  // Deserialize the heap and restore the objects
  fd = fopen(filename, "r");
  OPHeapRead(&heap2, fd);
  fclose(fd);

  s1 = (struct S1*)OPHeapRestorePtr(heap2, 0);
  s2 = s2_ptr = OPRef2Ptr(heap2, s1->s2_ref);
  OPHeapDestroy(heap2);
}
```

DEPENDENCY
----------

* C compiler with support of C11 atomics.
  - gcc 4.9, gcc 5, gcc 6
  - TODO: figure out which versions of clang support C11 atomics.
* [log4c (>= 1.2.4)](http://log4c.sourceforge.net)
  - I guess 1.2.1 also works, but 1.2.4 was released since 2008. Getting
  it on most distros shouldn't be hard.
* [cmocka (>= 1.0.1)](https://cmocka.org)
  - Required for unit testing.
* GNU Autotools for people who want to build from head
  - autoconf
  - automake
  - libtools

INSTALL
-------

```bash
# For people who download the tarball release
./configure
make
sudo make install

# For people who clone from github
git submodule update --init --recursive
./bootstrap.sh
./configure
make
sudo make install
```

DATA STRUCTURES INCLUDED
------------------------

* RobinHoodHash, can be used as
  - HashMap
  - HashSet
  - HashMultimap
  - TODO: document benchmark results

* TODO (like a wishlist):
  - Integer DS which support predecessor quries
  - Tries
  - Succinct data structures
  - Integer compression (for columnar store)

DOCUMENTATION
-------------

* [API documentation][doc]
* TODO: tutorial
* TODO: advanced examples which explains how it work

[doc]: http://dryman.github.com/opic/

LICENSE
-------

Copyright (c) 2016, 2017 Felix Chern

    OPIC is free software: you can redistribute it and/or modify it under the
    terms of the GNU Lesser General Public License as published by the Free
    Software Foundation, either version 3 of the License, or (at your option)
    any later version.

    OPIC is distributed in the hope that it will be useful, but WITHOUT ANY
    WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
    FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for
    more details.

    You should have received a copy of the GNU Lesser General Public License
    along with OPIC.  If not, see <http://www.gnu.org/licenses/>.

Cityhash is included in this project. Here is the copyright statements for
cityhash:

    Copyright (c) 2011 Google, Inc.

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
    THE SOFTWARE.

CODE STYLE FOR CONTRIBUTORS
---------------------------

Please follow the [GNU Coding Standards][gnuc]. On the moment of this
writing we still have some portion of the code hasn't yet convert to GNU
formatting styles, but this should be fixed in near future.

[gnuc]: https://www.gnu.org/prep/standards/standards.html
