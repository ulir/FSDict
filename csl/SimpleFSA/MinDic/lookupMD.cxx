#include "./MinDic.h"
#include<cstdlib>

/**
 * @file
 *
 * This program uses the class @c SimpleTrie to compile a trie from a given txt file.
 */

int main( int argc, const char** argv ) {
    std::locale::global( std::locale( "" ) );


    if( argc != 2 ) {
	std::wcerr<<"Use like: compileSimpleTrie <txtFile>"<<std::endl;
	exit( 1 );
    }

    csl::SimpleFSA::MinDic minDic;

    try {
	minDic.compileDic( argv[1] );
    } catch( csl::exceptions::cslException ex ) {
	std::wcerr<<"lookupMD: Error: "<< ex.what() << std::endl;
	exit( 1 );
    }

    minDic.analyze();

    std::wstring query;
    while( std::wcout<<"> " && std::getline( std::wcin, query).good() ) {
	if( minDic.lookup( query ) ) {
	    std::wcout << "YES" << std::endl;
	}
	else {
	    std::wcout << "NO" << std::endl;
	}
    }
}
