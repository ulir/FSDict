#include "./ErrDic.h"
#include<iostream>

using namespace csl;

int main(int argc, char** argv) {
    setlocale(LC_CTYPE, "de_DE.UTF-8");  /*Setzt das Default Encoding für das Programm */
    try {

	if(argc != 2) {
	    std::cerr<<"Use like: "<<argv[0]<<" <binDic>"<<std::endl;
	    exit(1);
	}

	ErrDic t;
	t.loadFromFile( argv[1] );

//	t.doAnalysis(); exit( 0 );

	uchar bytesIn[Global::lengthOfLongStr];
	wchar_t query[Global::lengthOfLongStr];
	// set the last byte to 0. So we can recognize when an overlong string was read by getline().
	bytesIn[Global::lengthOfLongStr - 1] = 0; 

	ErrDic::Entry e;
	while( std::cin.getline( ( char* ) bytesIn, Global::lengthOfLongStr ) ) {
 	    if ( bytesIn[Global::lengthOfLongStr-1] != 0 ) {
		throw exceptions::badInput( "csl::MinDic::compileDic:Maximum length of input line violated (set by Global::lengthOfLongStr)" );
	    }
	    mbstowcs( query, (char*)bytesIn, Global::lengthOfLongStr );

	    if( t.lookup( query, &e ) ) {
		printf( "ha: original='%ls', pattern='%ls'\n", e.getOriginal(), e.getErrorPattern() );
	    }
	    else printf( "\n" );

	}

    } catch( exceptions::cslException ex ) {
 	std::cout<<"lookupMD: "<<ex.what()<<std::endl;
	exit( 1 );
    }
    return 0;

}
