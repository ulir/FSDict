#include<cstdlib>
#include "./Trie.h"

/**
 * @file
 *
 * This program uses the class @c SimpleTrie to compile a trie from a given txt file.
 */

int main( int argc, const char** argv ) {
    std::locale::global( std::locale( "" ) );


    if( argc != 2 ) {
	std::wcerr<<"Use like: lookupTrie <txtFile>"<<std::endl;
	exit( 1 );
    }

    csl::SimpleFSA::Trie trie;
    trie.compileTrie( argv[1] );



    std::wstring query;
    while( std::wcout<<"> " && std::getline( std::wcin, query).good() ) {
	if( trie.lookup( query ) ) {
	    std::wcout << "YES" << std::endl;
	}
	else {
	    std::wcout << "NO" << std::endl;
	}
    }
    
}
