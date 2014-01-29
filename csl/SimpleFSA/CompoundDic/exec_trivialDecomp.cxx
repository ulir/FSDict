
#include "./TrivialDecomp.h"
#include<iostream>
#include<string>

int main( int argc, char** argv ) {

    std::locale::global( std::locale( "" ) );


    csl::SimpleFSA::TrivialDecomp decomp( argv[1] );

    std::wstring line;

    size_t count = 0;
    while( std::getline( std::wcin, line ).good() ) {
	if( ++count % 1000000 == 0 ) std::wcerr << "trivialDecomp: " <<count / 1000000 << "million tokens processed." << std::endl;
	if( decomp.decomp( line ) ) {
	    std::wcout << line << std::endl;
	}
	else {
	    //std::wcout<<"NO: "<< line <<std::endl;
	    //return 1;
	}
    }
}
