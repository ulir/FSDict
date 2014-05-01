#include "fsdict/MinDic2/MinDic2.h"
#include "fsdict/Getopt/Getopt.h"
#include "fsdict/Global.h"
#include<iostream>

void printHelp(); // forward declaration

/**
 * @brief Program used to compute a fsdict::MinDic2 from a word list and dump the automaton to a file.
 *
 */

int main(int argc, char const** argv) {
    std::locale::global( std::locale( "" ) );

    fsdict::Getopt opt( argc, argv );


    if( opt.hasOption( "stdin" ) ) {
	if( opt.getArgumentCount() != 1 ) {
	    printHelp();
	    exit( 1 );
	}

	try {
	    fsdict::MinDic2 t;

	    t.initConstruction();

	    std::wstring line;
	    int annotation = 0;

	    while( std::getline( std::wcin, line ), std::wcin.good() ) {

		t.parseAnnotation( &line, &annotation );
		t.addToken( line.c_str(), annotation );
	    }
	    if( errno == EILSEQ ) { // catch encoding error
		throw fsdict::exceptions::badInput( "MinDic::compileDic: Encoding error in input sequence." );
	    }

	    t.finishConstruction();

	    t.writeToFile( opt.getArgument( 0 ).c_str() );

	    //   t.toDot();
	    //   t.printCells();

	} catch ( std::exception& ex ) {
	    std::wcout<<"compileMD failed: "<<ex.what()<<std::endl;
	    return(1);
	}

    }
    else if( opt.getArgumentCount() == 2 ) {
	try {
	    fsdict::MinDic2 t;
	    t.compileDic( argv[1] );

	    t.writeToFile( argv[2] );

	    //   t.toDot();
	    //   t.printCells();

	} catch ( std::exception& ex ) {
	    std::wcout<<"compileMD failed: "<<ex.what()<<std::endl;
	    return(1);
	}

    }
    else {
	printHelp();
	exit( 1 );
    }

}


void printHelp() {
    std::wcerr<<"Use like: compileMD <txtDic> <binDic>" <<std::endl;
}
