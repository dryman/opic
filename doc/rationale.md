RATIONALE AND ROADMAP {#rationale}
---------------------

In most of the programming models, program operates on in memory
objects, and operations on off-heap (disk, network) objects are usually
afterthoughts. The off-heap object representations are mostly
implemented per application basis, such as database, primitive only
serialization format (protobuf, thrift, avro), search engine index, or
document format like Microsoft Word. Implementing new serialization
formats for every new applications is painful, so we decided to create a
general framework to rule it all.

A general purpose serialization framework can do more than that. We
target to serialize all possible data structures. BST, Hash table, B+
Tree, suffix array, anything. As you might notice, these are the core
data structures to build databases and search engines. Not only should
you be able to write a hobby transactional database out of this
framework, but you can also build your own NoSQL, multi-layer DB like
LevelDB/RocksDB, bitmap based DB like Druid, or experiment new database
concepts that no one has seen before. This is one core aspect for
ADT (abstract data type) serialization.

This concept can be further extend to serialize the general program
state (not yet implemented). The motivation comes from bad experiances
on using memory aggressive browsers. The browser performance is not
satisfactory when having dozens of browser tabs opened, even though the
OS should swap out the memory to disk but it just doesn't perform well.
Instead, why not serialize the whole Javascript and DOM state out, and
restore it back when user requires it? Our initial attempt is build a
lambda calculus engine base on the serialization framework, then
optimize its performance and write Javascipt compiler to the lambda
form.

If you also feel excited on this project, your contributions and patches
are always welcome.

PROJECT STRUCTURES AND PLANS
----------------------------

This section describes a high level view of the program abstraction and
near future roadmap.

### Language Choice

Before we jump to the serialization abstraction, let me briefly discuss
the language choice. This framework is implemented in pure C, following
C11 standard and GCC extensions. C11 is chosen for atomic variables; A
subset of GCC extensions are carefully picked in which it has the
support from clang as well.  Other compiler (Visual Studio, Intel C)
support are not considered on current stage of development.  The use of
GCC extensions are necessary because many important language features do
not exist in C99/C11 standards. The extensions we use and plan to use
are:

* constructor function
* address alignment
* SIMD vector types
* may add more if needed.

Though breaking portability across multiple compilers could be a
problem, we plan to overcome it by using Autoconf configuration
to detect compiler supported features before actual compilation.
If the feature test failed, it would not try to compile.

Many people asked me why didn't I just use C++ instead. There are two
main reasons. First, serializing general types is crucial in C++.  You
have to serialize the internal C++ structures such as vtable (which is
implementation defined), having your own memory allocator to restore
load the de-serialized C++ type, and probably trace all the method
address of an object. That's too much hack. And since the compiler may
use different vtable layout on different versions, you have to test
against all possible ones! Nope, not a good idea. Second reason relates
to how I want this framework to be used. ALL programming languages has C
bindings, and that is a perfect place to hide the complicated internals
and expose high level API to end users. For instance, expose a
programmable database interface to Python that looks like a regular
container. As all the states are written in C, it is also easier to pass
it to other language's C bindings.

Same considerations apply to all other possible candidates, including
go, rust, swift, OCaml, Haskell, Java, Scala, etc. Unless you can
serialize its internal structure easily with deterministic performance,
it won't be taken onto the table.

### Generics (completed)

So, we decided to use C. But it is so featureless! How do we balance out
the low level control and high level abstraction to make programming
less painful? As you might guess, we use macros to create a DSL. The
main feature I tired to implement is generic type and interface (also
called traits, or typeclass in haskell). See the following example of
how it makes language semantics cleaner.

```c
serialize((void*)obj, fd);
```

A prototype function like above can behave differently with different
object instance. If the object has internal object that need to get
serialized, simply recursively call `serialize` again with the internal
object.

For now we only implemented generics (method polymorphism), without
inheritance support. Though it is not hard but we won't do it until we
really need it. Yet, the generics abstraction is already powerful enough
for us to write Haskell Monads and Functors in C. See
[monad_example](https://github.com/dryman/opic/tree/master/monad_example)
for how it works.

### Serializable Pointer Machine (completed)

You can think [pointer machine][pmachine] is a academic synonym to
object oriented programming model. It is also a general form of LISP
machine which is used by many functional languages.

I follow the Schönhage's SMM (Schönhage's Storage Modification Machine)
definition of pointer machine, where the machine is formed by number of
"nodes" with a inbound link to the root node. Each node have constant
number of field; a field could be an outbound pointer to other node, or
a primitive type.  Only certain operations are permitted: create (new),
destroy (free) nodes, follow the pointers, or mutate the fields in a
node. This pretty much models general object oriented program behavior,
and it can emulate LISP machine as well. 

This model is also carefully picked for other practical reasons.

* Since pointer machine can only use constant size objects, we can
  group same type of objects in large chunk of array, and can serialize
  it in batches.
* Compare to the model above, RAM model is harder to manage and make
  it deterministic on serialization operation.

The detail explaination is in
[pm_serde_example](https://github.com/dryman/opic/tree/master/pm_serde_example).

[pmachine]: https://en.wikipedia.org/wiki/Pointer_machine

### Common Abastract Data Types (TODO)

Implements common collection types for good code reuse. In contrast to
most real time applications, one major use of this library is for
serialization which only require good amortized complexity. Therefore we
permit and encourage amortized data structures like Fibonacci heap to be
included in this library. This unleashes many powerful data structures
that only exist in papers but yet used in real world.

Sounds fun, right?

### Primitive Serialization (TODO)

* Row based, suite with TX enabled data processing or data stream
* Columnar. Type based compression should get examined.
* Dremel like nested columnar store. Except repetition number and
  definition number are not packed with data, but stored separately as
  integer type. This should improve the compression ratio.

### Cache Oblivious Data Structures (TODO)

See [Eric Demaine's Note][cache oblivious].

[cache oblivious]: http://erikdemaine.org/papers/BRICS2002/paper.pdf

### Freezable Lambda Calculus (TODO)

Implement a simple compute engine that can serialize the whole state at
any time.
