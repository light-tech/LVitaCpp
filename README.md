LVitaCpp -- Essential C++ Library
=================================

At Lightech, we invented a new vitamin: Vitamin C++.
LVitaCpp (short for "Lightech Vitamin C++") is an essential library of data structure templates, abstracted out of our UWP applications.
For example, `LTTree` data structure is used in LawTeX to implement virtual file system, code suggestion and package suggestion; and `LTMap` is used to keep track of SVG documents.
These templates are much simpler than the C++ STL, significantly reducing the size of the object binary.

The idea is that STL implementation are more general and account for general usage.
In some application, there is no need for such degree of generality.
For instance, STL `std::map` internally makes use of Red-Black tree which doesn't need to reallocate (expand) the array like our `LTMap`.
Our application of map doesn't need to reallocate a lot as the map is more stable.

Goal
----

This is a small implementation of the C++ library, intended to replace the standard and heavy C++ template API.

 1. The problem with standard C++ headers is that they increase the size of the compiled binary significantly. Most of them adds at least 500KB to the object compiled by Visual Studio.

    For example, an inclusion of the (very frequently used) `<string>` header increases the object file (compiled by Visual Studio) by about 1MB. Likewise, include `<regex>` incurs a cost of 2MB.

 2. Worsen the problem is the fact that the standard C++ library are implemented via `template`. That means that the compiler has to instantiate the template and inject the same code to every source that makes use of them.

    For instance, if `A.cpp` and `B.cpp` includes `<string>` then both of the objects `A.obj` and `B.obj` adds the implementation of the same class `std::string`.

 3. Due to duplicated types, the linker later has to match isomorphic types (costly operation if there are many objects to link) and remove them when optimizing the final executable.

We replace the C++ `std::string` with an `LString` that is a few KB object.

Similarly, we replace standard containers such as `std::vector`, `std::map`, `std::stack`, ... with our own  `LTArray`, `LTMap`, `LTStack` which are significantly smaller in size. We also provide a basic search tree `LTTree` which is missing from C++. All of these templates are very small.

Beyond that, there are various utility functions such as one to read a file to an array.

TODO
----

 * The templates are converted from C counter-part, using lots of callbacks (function pointers).
   It would be preferable to use functional template arguments to allow for capture lambda.

License
-------

 * Lightech Public License:
   You are free to use this library however you want as long as you give attribution to us. In particular, inform the user that your program uses LVitaCpp at https://github.com/light-tech/LVitaCpp.git in binary or source distribution of your program.