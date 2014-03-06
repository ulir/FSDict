FSDict
======

Store dozens of millions of strings, together with a numerical value (or any other data type of fixed length)

Highlights
==========
* Incremental O(n) construction of minimized deterministic finite state automata, using a highly optimized sparse table implementation.
* Complexity for lookup of key k is O(|k|), independent of the dictionary size.
* Complexity for iterating over all m transitions of a given state is O(m), independent of the alphabet size
* Very fast algorithm for approximate search in the dictionary. Find similar keys for a given string (w.r.t. Levenshtein distance) using the state-of-the-art algorithm (Mihov/Schulz).

Documentation
============
Please find documentation of the latest release [here](http://ulir.github.io/FSDict/v0.1.1/api/).


How to build
============
To compile the csl library and all command line tools, you need the build
program 'cmake', which is part of virtually any linux distribution.

Unpack the source tarball and change into its root directory. Then type:

```sh
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=RELEASE [-DCMAKE_INSTALL_PREFIX=/some/path/] ..
make
```

This should build the library in ./lib and all executables in ./bin .

You can also try 'make install', but I don't guarantee I haven't forgotten
to specify one or the other binary to be installed. It does install the
library to CMAKE_INSTALL_PREFIX/lib and the more important programs to
CMAKE_INSTALL_PREFIX/bin . CMAKE_INSTALL_PREFIX defaults to "/usr/local/", but
you can use 'ccmake' to change the prefix.
Just do

```sh
cmake ..
ccmake .  # only if you want to change paths. Just follow the help given in the program.
make
make install  # not very well tested
```

Please report bugs, problems etc. on https://github.com/ulir/FSDict .
