#include "./CompoundDic.h"

int main( int argc, char** argv ) {
    
    std::locale::global( std::locale( "de_DE.utf-8" ) );

    csl::SimpleFSA::CompoundDic cd;

    cd.compute( argv[1] );

    cd.getDic().analyze();


    std::wstring query;
    while( std::wcout<<"> " && std::getline( std::wcin, query).good() ) {
	if( cd.getDic().lookup( query ) ) {
	    std::wcout << "YES" << std::endl;
	}
	else {
	    std::wcout << "NO" << std::endl;
	}
    }
    

}

