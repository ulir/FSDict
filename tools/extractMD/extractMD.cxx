#include<iostream>
#include "fsdict/Getopt/Getopt.h"
#include "fsdict/Alphabet/Alphabet.h"
#include "fsdict/MinDic/MinDic.h"
#include "fsdict/FBDic/FBDic.h"

using namespace fsdict;

int main( int argc, const char** argv ) {
    std::locale::global( std::locale("") ); // set the environment's default locale

    fsdict::Getopt options( argc, argv );


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

	fsdict::MinDic<> const* minDic = 0;
	fsdict::FBDic<>* fbdic = 0; // this one is loaded in case a fbdic is passed to the program

	// In case a .fbdic file is passed, open it and use the FWDic
	if( ( options.getArgument( 0 ).size() >= 5 ) && options.getArgument( 0 ).substr( options.getArgument( 0 ).size() - 5 ) == "fbdic" ) {
	    fbdic= new fsdict::FBDic<>( options.getArgument( 0 ).c_str() );
	    minDic = &( fbdic->getFWDic() );
	}
	else {
	    minDic = new fsdict::MinDic<>( options.getArgument( 0 ).c_str() );
	}
      
	if( options.hasOption( "dot" ) ) {
	  minDic->toDot();
	}
	else if( options.hasOption( "stat" ) ) {
	  minDic->doAnalysis();
	}
	else minDic->printDic();
	return 0;
   
    } catch ( exceptions::fsdictException ex ) {
	std::wcerr << "Dictionary extraction failed: " << ex.what() << std::endl;
	return 1;
    }
}
