#include <fsdict/UTF8Locale/UTF8Locale.h>
#include <fsdict/DictSearch/DictSearch.h>
#include <fsdict/Getopt/Getopt.h>
#include <fsdict/INIConfig/INIConfig.h>

// uncomment this if you want so suppress output for the words
//#define FSDICT_DICTSEARCH_PRINTNONE 1;

void printHelp() {
    std::wcerr<< std::endl
	      << "Use like: runDictSearch"<<std::endl
	      << "--config=<configFile>         configuration file (obligatory)" << std::endl
	      << "--machineReadable             Print (even more) machine-readable output, that is, all answers in one line, separated by '|'" << std::endl
	      << std::endl<<std::endl;
}


int main( int argc, char const** argv ) {
    std::locale::global( std::locale( "" ) ); // set a default locale

    fsdict::Getopt options;
    options.specifyOption( "help", fsdict::Getopt::VOID );
    options.specifyOption( "config", fsdict::Getopt::STRING );
    options.specifyOption( "machineReadable", fsdict::Getopt::VOID );

    options.getOptionsAsSpecified( argc, argv );

    
    if( options.hasOption( "help" ) ) {
	printHelp();
	return EXIT_SUCCESS;
    }
    if( !options.hasOption( "config" ) ) {
	printHelp();
	return EXIT_FAILURE;
    }
    
    // create a DictSearch-object
    fsdict::DictSearch dictSearch;

    fsdict::INIConfig config( options.getOption( "config" ) );
    dictSearch.readConfiguration( config );
    
    
    
    std::wstring query;
    fsdict::DictSearch::CandidateSet candSet;

    bool machineReadable = false;
    if( options.hasOption( "machineReadable" ) ) {
	machineReadable = true;
    }

    
    while( std::getline( std::wcin, query ).good() ) {
	candSet.clear(); // empty the CandidateSet
	dictSearch.query( query, &candSet ); // execute lookup
	
#ifndef FSDICT_DICTSEARCH_PRINTNONE
	std::sort( candSet.begin(), candSet.end() ); // sort candidates following a very coarse order relation
	if( candSet.empty() ) {
	    std::wcout<<"--NONE--"<<std::endl;
	}
	else if( machineReadable ) {
	    // all interpretations of the query in one line
	    for( fsdict::DictSearch::CandidateSet::const_iterator it = candSet.begin(); it != candSet.end(); ++it ) {
		std::wcout << *it;
		if( it + 1  != candSet.end() ) std::wcout<<"|";
	    }
	    std::wcout<<std::endl;
	}
	else {
	    for( fsdict::DictSearch::CandidateSet::const_iterator it = candSet.begin(); it != candSet.end(); ++it ) {
		std::wcout << *it << std::endl;
	    }
	}
#endif
    }
    
}
