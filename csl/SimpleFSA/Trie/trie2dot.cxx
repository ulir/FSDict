#include<cstdlib>
#include "./Trie.h"

/**
 * @file
 *
 * This program uses the class @c SimpleTrie to compile a trie from a given txt file.
 * Then it prints dot code for that trie.
 */

int main( int argc, const char** argv ) {
    std::locale::global( std::locale( "" ) );

    csl::SimpleFSA::Trie trie;

    if( argc != 2 ) {
	std::wcerr<<"Use like: trie2dot <txtFile>"<<std::endl;
	exit( 1 );
    }

    trie.compileTrie( argv[1] );

    trie.traverse_toDot();
//    trie.toDot();


}
