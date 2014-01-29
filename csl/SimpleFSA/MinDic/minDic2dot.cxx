#include<cstdlib>
#include "../../Global.h"
#include "./MinDic.h"

/**
 * @file
 *
 * This program uses the class @c SimpleFSA::MinDic to compile a minimzed dictionary automaton
 * from a given txt file.
 * Then it prints dot code for that automaton.
 */
int main( int argc, const char** argv ) {
    std::locale::global( std::locale( "" ) );
    
    csl::SimpleFSA::MinDic minDic;
    
    if( argc != 2 ) {
	std::wcerr<<"Use like: minDic2dot <txtFile>"<<std::endl;
	exit( 1 );
    }

    try {
	minDic.compileDic( argv[1] );
	minDic.toDot();
    } catch( csl::exceptions::cslException ex ) {
	std::wcerr<<"minDic2dot: Error: "<< ex.what() << std::endl;
	
    }


}
