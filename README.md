Object Persistence In C (Alpha)
===================================

OPIC is a new approach to serialize general data structures, object types, and
primitive types. It's a new data stack from the ground up -- from object
oriented model, generics, to memory management. With everything redesigned for
scalability, we visioned a new distributed computing ecosystem for the 21st
century.

Our key to success is to extend the memory oriented programming model to other
tier of storages: disk, SSD, network, or even tape. Accessing data should not be
limited by memory address on single machine; instead, all data types should be
serializable so that it can be shared across network or save for future use.
Having serialzability as the core design brings many benefits for free:

* Scalability. When all the data types are serializable, the application can
easily scale up with multiple strategies, including sharing data between nodes,
off load certain data for later use, or build caches from the same serialization
abstraction.

* Data persistence. Think of databases' durability. Since all the data types are
serializable, you can save the snapshot of the entire program state whenever you
want. This can make database applications way easier to build, and also make
debugging easier.

* Generality for data processing applications. All the data processing systems,
including RDBMS, map reduce, search engines, even RPC involves are some sort of
special case of serialization. Why duplicates the effort for each of those
applications instead of having one powerful and optimized framework?

Most of the functionalities will be implemented in C. Our end goal is to embed
this framework into other higher level languages like python, java, nodejs for
wider adoption.

To begin with, please check out our [documentation page][doc].

[doc]: http://dryman.github.com/opic/

LICENSE
-------

Copyright (c) 2016 Felix Chern

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

In future we may also form a commercial license and support.

CODE STYLE FOR CONTRIBUTORS
---------------------------

Please follow the [GNU Coding Standards][gnuc]. On the moment of this
writing we still have some portion of the code hasn't yet convert to GNU
formatting styles, but this should be fixed in near future.

[gnuc]: https://www.gnu.org/prep/standards/standards.html

