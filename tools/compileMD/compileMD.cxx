#include "fsdict/MinDic/MinDic.h"
#include "fsdict/Getopt/Getopt.h"
#include "fsdict/Global.h"
#include<iostream>


void printHelp() {
    std::wcerr<< "Use like:                compileMD <txtDic> [<binDic>]"   << std::endl
	      << "          cat <txtDic> | compileMD --stdin  <binDic>" << std::endl
	      << std::endl
	      << "Optional arguments:" << std::endl
	      << "--delimiter <c>          The key-value delimiter (Default: #)" << std::endl
	      << std::endl
	      << std::endl;
}

/**
 * @brief Program used to compute a MinDic<> from a word list and dump the automaton to a file.
 *
 */
int main(int argc, char const** argv) {
    std::locale::global( std::locale( "" ) );

    fsdict::Getopt options;
    options.specifyOption( "help", fsdict::Getopt::VOID );
    options.specifyOption( "stdin", fsdict::Getopt::VOID );
    options.specifyOption( "delimiter", fsdict::Getopt::STRING );
    options.getOptionsAsSpecified( argc, argv );

    if( options.hasOption( "help" ) ) {
	printHelp();
	return EXIT_SUCCESS;
    }

    if( options.getArgumentCount() == 0 ) {
	printHelp();
	return EXIT_FAILURE;
    }


    fsdict::MinDic< int > t;

    if( options.hasOption( "delimiter" ) ) {

	if( options.getOption( "delimiter" ) == "\\t" ) { // special hack to correctly interpret the \t character.
	    options.setOption( "delimiter", "\t" );
	}
	else if( options.getOption( "delimiter" ).length() != 1 ) {
	    std::wcerr << "The delimiter (specified with --delimiter) must be exactly 1 character." << std::endl;
	    return EXIT_FAILURE;
	}
	t.setKeyValueDelimiter( options.getOption( "delimiter" ).at( 0 ) );
    }

    if( options.hasOption( "stdin" ) ) {
	if( options.getArgumentCount() != 1 ) {
	    printHelp();
	    return EXIT_FAILURE;
	}

	try {

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

	    t.writeToFile( options.getArgument( 0 ).c_str() );

	    //   t.toDot();
	    //   t.printCells();
	    return EXIT_SUCCESS;

	} catch ( fsdict::exceptions::fsdictException& ex ) {
	    std::wcout<<"compileMD failed: "<<ex.what()<<std::endl;
	    return EXIT_FAILURE;
	} catch ( std::exception& ex ) {
	    std::wcout<<"compileMD failed: "<<ex.what()<<std::endl;
	    return EXIT_FAILURE;
	}

    }
    else  {
	try {
	    std::string inFile = options.getArgument( 0 );
	    std::string outFile;

	    if( options.getArgumentCount() == 2 ) {
		outFile = options.getArgument( 1 );
	    }
	    else {
		if( inFile.size() > 4 && ( inFile.substr( inFile.size() - 4 ) == ".lex" ) ) {
		    outFile = inFile;
		    outFile.replace( outFile.size() - 4, 4, ".mdic" );
		}
		else {
		    std::wcerr << "Your input filename does not end with '.lex'. In this case please provide an output filename as second argument." << std::endl;
		    return EXIT_FAILURE;
		}
	    }

	    t.compileDic( inFile.c_str() );

	    t.writeToFile( outFile.c_str() );

	    //   t.toDot();
	    //   t.printCells();

	} catch ( std::exception& ex ) {
	    std::wcout<<"compileMD failed: "<<ex.what()<<std::endl;
	    return EXIT_FAILURE;
	}

    }

}
