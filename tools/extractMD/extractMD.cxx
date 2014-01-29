#include<iostream>
#include "csl/Getopt/Getopt.h"
#include "csl/Alphabet/Alphabet.h"
#include "csl/MinDic/MinDic.h"
#include "csl/FBDic/FBDic.h"

using namespace csl;

int main( int argc, const char** argv ) {
    std::locale::global( std::locale("") ); // set the environment's default locale

    csl::Getopt options( argc, argv );


    if( options.getArgumentCount() != 1 ) {
	std::wcerr<<std::endl
		  <<"Use like: extractMD [options] <binDic> "<<std::endl
		  <<"Options:"<<std::endl
		  <<"--stat=1\tto print statistics of the MinDic"<<std::endl
		  <<"--dot=1\tto print dotcode for the MinDic"<<std::endl
		  <<std::endl<<std::endl;
	
	exit( 1 );
    }
    try {

	csl::MinDic<> const* minDic = 0;
	csl::FBDic<>* fbdic = 0; // this one is loaded in case a fbdic is passed to the program

	// In case a .fbdic file is passed, open it and use the FWDic
	if( ( options.getArgument( 0 ).size() >= 5 ) && options.getArgument( 0 ).substr( options.getArgument( 0 ).size() - 5 ) == "fbdic" ) {
	    fbdic= new csl::FBDic<>( options.getArgument( 0 ).c_str() );
	    minDic = &( fbdic->getFWDic() );
	}
	else {
	    minDic = new csl::MinDic<>( options.getArgument( 0 ).c_str() );
	}
      
	if( options.hasOption( "dot" ) ) {
	  minDic->toDot();
	}
	else if( options.hasOption( "stat" ) ) {
	  minDic->doAnalysis();
	}
	else minDic->printDic();
	return 0;
   
    } catch ( exceptions::cslException ex ) {
	std::wcerr << "Dictionary extraction failed: " << ex.what() << std::endl;
	return 1;
    }
}
