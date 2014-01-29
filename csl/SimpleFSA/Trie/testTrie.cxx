#include<cstdlib>
#include "./Trie.h"

/**
 * @file
 *
 * This program uses the class @c SimpleTrie to compile a trie from a given txt file.
 * This is for testing.
 */

int main( int argc, const char** argv ) {
    std::locale::global( std::locale( "" ) );

    csl::SimpleFSA::Trie trie;

    if( argc != 2 ) {
	std::wcerr<<"Use like: testTrie <txtFile>"<<std::endl;
	exit( 1 );
    }

    trie.compileTrie( argv[1] );

    trie.traverse_depthFirst();
    trie.traverse_depthFirst_recursive();
    trie.traverse_breadthFirst();

}
