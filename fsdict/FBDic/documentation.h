/**
@page fbDic_manual FBDic Manual

On this page the use of "fbdic"s from the csl library is explained. "fb" means <em>forward-backward</em>: This type of dictionary
is used for approximate search with fsdict::MSMatch, which also needs the dictionary of all words in reverse order. FBDic is a simple wrapper
that holds two data structures of type fsdict::MinDic, holding the dictionary in regular and in reverse order.

@section compileFBDic Use the program compileFBDic to create binary automata files from text lists
This section explains how to obtain an FBDic binary file from a text list.

In the directory INSTALL_PREFIX/bin you find a program @c compileFBDic. Use it like:

@code
compileFBDic foo.lex foo.fbdic
@endcode

A .lex file is a text file of the form:
@code
anna#42
bill#50
charly#54
@endcode
That is, an alphabetically sorted list of keys, followed by a '#' delimiter symbol and some integer value
which is stored with the key. If delimiter and integer are omitted, the value 0 will be annotated with each key.

It is important that the .lex file is utf8 encoded and sorted properly. You can sort your dictionary with
the tool @c sortLex included in this package. Much faster is the following unix command:
@code
LC_ALL=C sort -t'#' -k1,1 foo.unsorted > foo.lex
@endcode

The resulting .fbdic file is a binary representation of the dictionary automaton and can now be used with other csl tools.

@section load Load a binary file into a fsdict::FBDic object
Loading a binary automaton file into a c++ object is easy:
@code
fsdict::FBDic<> fbDic( "path-to/some.fbdic" );
@endcode
or
@code
fsdict::FBDic<> fbDic;
fbDic.loadFromFile( "path-to/some.fbdic" );
@endcode

@section compile compile a fsdict::FBDic automaton from a .lex file at runtime
@code
fsdict::FBDic<> fbDic;
fbDic.compileDic( "path-to/some.lex" );
@endcode

*/
