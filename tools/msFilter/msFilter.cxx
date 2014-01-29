#include "csl/Getopt/Getopt.h"
#include "csl/MSMatch/MSMatch.h"
#include "csl/ResultSet/ResultSet.h"
#include "csl/Global.h"
#include "csl/Stopwatch.h"
using namespace csl;


/**
 * @todo The wstring handling in this program is hopelessly deprecated!!! Update!
 */

int main( int argc, char const** argv ) {
    setlocale(LC_CTYPE, "de_DE.UTF-8");  /*Setzt das Default Encoding für das Programm */

    Getopt opt( argc, argv );

    if( opt.getArgumentCount() != 2 ) {
	std::cerr << "Use like: msFilter [--machineReadable=1] [--stats=1] <dlev> <fb_dic>" << std::endl;
	exit( 1 );
    }

    bool machineReadable = false;
    if( opt.hasOption( "machineReadable" ) ) {
	machineReadable = true;
    }
    bool stats = false;
    if( opt.hasOption( "stats" ) ) {
	stats = true;
    }

    try {
	MSMatch< FW_BW > matcher( atoi( opt.getArgument( 0 ).c_str() ), opt.getArgument( 1 ).c_str() );
//	MSMatch< STANDARD > matcher( atoi( argv[1] ), argv[2] );

	ResultSet list;


	uchar bytesIn[Global::lengthOfLongStr];
	wchar_t query[Global::lengthOfLongStr];

	// set the last byte to 0. So we can recognize when an overlong string was read by getline().
	bytesIn[Global::lengthOfLongStr - 1] = 0; 

	csl::Stopwatch watch;
	watch.start();

	size_t nrOfQueries = 0;
	while( std::cin.getline( ( char* ) bytesIn, Global::lengthOfLongStr ) ) {
	  try {
 	    if ( bytesIn[Global::lengthOfLongStr-1] != 0 ) {
		throw exceptions::badInput( "csl::msFilter: Maximum length of input line violated (set by Global::lengthOfLongStr)" );
	    }
	    mbstowcs( query, (char*)bytesIn, Global::lengthOfLongStr );

	    wprintf( L"Query: %ls\n", query );
	    
	    list.reset(); // forget candidates that might be stored from earlier use

	    try {
		matcher.query( query, list );
	    } catch( exceptions::bufferOverflow& exc ) {
		fprintf( stderr, "%s: %lu\n",exc.what(), (unsigned long)list.getSize() );
	    }

// 	    std::cout<<list.getSize()<<" hits."<<std::endl;
//    	    list.sortUnique();
//   	    std::cout<<list.getSize()<<" hits."<<std::endl;


	    // print all hits

	    if( machineReadable ) { // print all hits in one line
		size_t i = 0;
		for( i = 0; i < list.getSize(); ++i ) {
		    wprintf( L"%ls,%d,%d", list[i].getStr(), list[i].getLevDistance(), list[i].getAnn() );
		    if( i + 1  != list.getSize() ) std::wcout<<"|";
		}
		wprintf( L"\n" );
	    }
	    else {
		size_t i = 0;
		for( i = 0;i < list.getSize();++i ) {
		  wprintf( L"%ls\t%d\t%d\n", list[i].getStr(), list[i].getAnn(), list[i].getLevDistance() );
		}
	    }
	  }
	  catch( exceptions::badInput& exc ) {
	    std::cerr << "Bad input: "<< exc.what() << std::endl;
	  }
	  ++nrOfQueries;
	} // while getline

	if( stats ) {
	  std::wcerr<<watch.readMilliseconds()<<" ms for "<< nrOfQueries << " queries. AVG: " 
		    << (double)watch.readMilliseconds() / (double)nrOfQueries << "ms" << std::endl;
	}
    } 
    catch( exceptions::cslException& exc ) {
	std::cerr << "msFilter caught exception: "<< exc.what() << std::endl;
    }
}
