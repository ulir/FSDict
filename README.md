FSDict
======

A library to store and access very large dictionaries in an efficient way.

How to build
============
To compile the csl library and all command line tools, you need the build
program 'cmake', which is part of virtually any linux distribution.

Unpack the source tarball and change into its root directory. Then type:

```sh
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=RELEASE ..
make
```

This should build the library in ./lib and all executables in ./bin .
If cmake gives you trouble concerning the jni include directories, it might help
to specify a correct JAVA_HOME environment variable:

```sh
$ JAVA_HOME=/path/to/java/sdk  cmake #[...], see above
```

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
