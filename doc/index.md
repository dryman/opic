OPIC       {#mainpage}
======================

Object Persistence In C
-----------------------

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

1. @ref rationale and roadmap of this project

<!--
The mission is to extend memory-oriented programming model to
local disks, network drives, or even tapes  so that the applications built on
this framework can easily scale 

mission 1:
scability

mission 2
persistence

mission 3
throughput

mission 4
real time (deterministic) and concurrent querying layer

mission 5
embed this runtime to most major languages

It aims for high performance load and off-load between primary
storage (memory) and secondary storage 

1. Create new databases. Database is a special case of object persistence.
Both SQL and NoSQL are engines that stores and loads records to/from disk. The
index to the records is usually implemented as serializable b-tree or other data
structures as well, which is also a direct application that OPIC can bring to
you.

2. Search engines and information retrieval in general. Any data structures that
doesn't fit into memory or need to save for later use can be built with OPIC.

3. Persistent program state. If you built new runtime based on this framework,
you can *save* the entire state of the program by serializing it out, and
restore it back later on. The intermediate state between each snapshot can be
implemented as WAL (Write Ahead Log) like most databases do.

The project goals:

Data processing applications.
* batch class in background
* concurrent class for foreground serving.

Compare to other approaches:
* Unified serialization <=> custom serialization for different data types.
* Batch processing as primary citizen for better throughput.


* A new abstraction that blends primary storage and secondary storage.
* Batch processing as primary citizen.

Currently OPIC is targeted for X86_64 architecture and POSIX compliant operating
systems. It uses C99/C11 standards and some carefully picked GCC/Clang
extensions. Once the core features are done it can be imported to other
languages as extensions.


For
the intermediate changes of the states could be implemented as [WAL (Write Ahead
Log)][wal]. With the [WAL][wal] you can replay the changes on the snapshot you
saved and restore the program state.
-->

