#include "./CompoundDic.h"

int main( int argc, char** argv ) {
    

    std::locale::global( std::locale( "de_DE.utf-8" ) );

    csl::SimpleFSA::CompoundDic cd;

    cd.compute( argv[1] );

    std::wcout<<"Automaton has " << cd.getDic().getNumberOfStates() << " states." << std::endl;

    std::wstring line;

    std::wcout<<">> ";
    while( std::getline( std::wcin, line ).good() ) {
	if( cd.getDic().lookup( line ) ) {
	    std::wcout << line << ": YES" << std::endl;
	}
	else {
	    std::wcout << line << ": NO" << std::endl;
	}
    }

}

