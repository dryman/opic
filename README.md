Object Persistence In C (Beta)
===================================

[![Build Status](https://travis-ci.org/dryman/opic.svg?branch=master)](https://travis-ci.org/dryman/opic)


OPIC is a revolutionary serialization framework for C.  Unlike
traditional approaches which walk through the in-memory objects and
write it to disk, OPIC itself is a memory allocator where all the
objects created are backed by a memory mapped file.  To save the
current snapshot of objects , simply call `OPHeapMSync()` and all the
changes are flushed to disk. Regular serialization may take several
seconds, even up to minutes to write large amont of data.  In
contrast, OPIC only takes few milliseconds to perform both read and
write.  For reading, `mmap()` system call only takes 0.0005 seconds to
map the file into memory region. The data is not loaded into memory
until the program access it. For writing, `msync()` is quite fast as
well.

SYNOPSIS --------

Using OPIC we can quickly draft out a poor man's key value store.
OPIC provides two types of hash table: `OPHashTable` for fixed length
key (like `CHAR(20)` in database), and `PascalHashTable` for length
varying key. `PascalHashTable` provide a short string optimization
similar to what [C++ does][sso]. Instead of using 24 bytes for inline
string in hash table buckets, user can specify the size of the inline
buffer. If the size of the key exceeds the inline buffer, extra space
is allocated in OPIC to hold the key and the bucket would represent as
pointer to key instead of inline key.

See the example below on how to write a mini key-value store in
few lines of C.

[sso]: https://stackoverflow.com/questions/21694302/what-are-the-mechanics-of-short-string-optimization-in-libc?answertab=active#tab-top

```c
// gcc -lopic $(log4c-config --libs) opic_write.c -o opic_write
#include <opic/op_malloc.h>
#include <opic/hash/pascal_hash_table.h>

int main(int argc, char** argv)
{
  uint64_t data = 10;
  OPHeap* heap = OPHeapOpen("myheap", O_RDWR | O_CREAT);
  PascalHashTable* table = PHNew(heap,
                                 20,     // table size: 20 elements
                                 0.7,    // table load: 70%
                                 10,     // inline size for key
                                 sizeof(data)); // value size
  // store table ptr at slot 0
  OPHeapStorePtr(heap, table, 0);

  // "ABC" stored inline in table.
  PHInsert(table,   // Object oriented C. The object instance is the first arg.
           "ABC",   // The key we want to store
           4,       // Length of the key (3 char + 1 NULL)
           &data);  // pointer to value, value would get copied to table.
  data++;
  PHInsert(table, "DEF", 4, &data);  // DEF stored inline in table.
  data++;
  PHInsert(table, "This is a long string", 22, &data);
  // key stored as pointer to a string with length of 22 (last byte NULL).

  OPHeapClose(heap);
  return 0;
}

// gcc-6 -lopic $(log4c-config --libs) opic_read.c -o opic_read
#include <inttypes.h>
#include <opic/op_malloc.h>
#include <opic/hash/pascal_hash_table.h>

int main(int argc, char** argv)
{
  OPHeap* heap = OPHeapOpen("myheap", O_RDWR);
  // restore table pointer from slot 0
  PascalHashTable* table = OPHeapRestorePtr(heap, 0);

  uint64_t* val;
  val = PHGet(table, "ABC", 4);
  printf("ABC -> %" PRIu64 "\n", *val);
  val = PHGet(table, "DEF", 4);
  printf("DEF -> %" PRIu64 "\n", *val);
  val = PHGet(table, "This is a long string", 22);
  printf("This is a long string -> %" PRIu64 "\n", *val);
  val = PHGet(table, "NAN", 4);
  printf("Nan -> %p\n", val);

  OPHeapClose(heap);
  return 0;
}
```

DEPENDENCY
----------

* C compiler with support of C11 atomics.
  - gcc 4.9, gcc 5, gcc 6, and above
  - TODO: figure out which versions of clang support C11 atomics.
* [log4c (>= 1.2.4)](http://log4c.sourceforge.net)
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

HOW DOES IT WORK?
-----------------

I wrote a initial draft to explain how it works. Check out my blog post:
http://www.idryman.org/blog/2017/06/28/opic-a-memory-allocator-for-fast-serialization/

DATA STRUCTURES INCLUDED
------------------------

* OPHashTable. For fixed length key. Can be used as
  - HashMap
  - HashSet
  - HashMultimap

* PascalHashTable. For length varying key. Can be used as
  - HashMap
  - HashSet
  - HashMultimap

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
