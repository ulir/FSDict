#include<iostream>
#include "fsdict/Vaam/Vaam.h"
#include "fsdict/Getopt/Getopt.h"
#include "fsdict/Stopwatch.h"
#include "fsdict/FBDic/FBDic.h"

#define FSDICT_VAAMFILTER_PRINTNONE true

/**
 * Vaam
 * 
 * @file
 *
 * @see fsdict::Vaam
 * @author Ulrich Reffle, <uli@cis.uni-muenchen.de>
 * 
 */


#ifdef FSDICT_VAAMFILTER_USE_TRANSTABLE
typedef fsdict::Vaam< fsdict::TransTable< fsdict::TT_PERFHASH, uint16_t, uint32_t > > Vaam_t;
#else
typedef fsdict::Vaam< fsdict::MinDic<> > Vaam_t;
#endif


int main(int argc, const char** argv ) {

    try {

    fsdict::Stopwatch watch;
    watch.start();

    std::locale::global( std::locale("") ); // set the environment's default locale

    fsdict::Getopt opt( argc, argv );

    if( opt.getArgumentCount() < 3 ) {
	std::wcerr<< "Use like: vaamFilter [options] <distance> <dictionary> <pattern-file>"<<std::endl
		  << std::endl
		  << "Options:" << std::endl
		  << "--minNrOfPatterns=N       Allow only interpretations with N or more pattern applications. Defaults to 0." << std::endl
		  << "--maxNrOfPatterns=N       Allow only interpretations with at most N pattern applications. Defaults to INFINITE." << std::endl
		  << "--machineReadable=1       Print (even more) machine-readable output, i.e. all answers in one line, separated by '|'" << std::endl;
	exit( 1 );
    }

    
    Vaam_t::MinDic_t const* baseDic = 0;
    fsdict::FBDic<> const* fbdic = 0;

    // In case a .fbdic file is passed, open it and use the FWDic
    if( opt.getArgument( 1 ).substr( opt.getArgument( 1 ).size() - 5 ) == "fbdic" ) {
	fbdic= new fsdict::FBDic<>( opt.getArgument( 1 ).c_str() );
	baseDic = &( fbdic->getFWDic() );
    }
    else {
	Vaam_t::MinDic_t* tmp = 0;

	// this tmp-hack is because of the const-ness of baseDic
	tmp = new Vaam_t::MinDic_t();
	tmp->loadFromFile( opt.getArgument( 1 ).c_str() );
	baseDic = tmp;
	
    }


    Vaam_t vaam( *baseDic, opt.getArgument( 2 ).c_str() );

    if( opt.hasOption( "maxNrOfPatterns" ) ) {
	vaam.setMaxNrOfPatterns( atoi( opt.getOption( "maxNrOfPatterns" ).c_str() ) );
    }

    if( opt.hasOption( "minNrOfPatterns" ) ) {
	vaam.setMinNrOfPatterns( atoi( opt.getOption( "minNrOfPatterns" ).c_str() ) );
    }

    bool machineReadable = false;
    if( opt.hasOption( "machineReadable" ) ) {
	machineReadable = true;
    }


    Vaam_t::CandidateReceiver answers;

    std::wstring query;

    size_t maxDistance = atoi( opt.getArgument( 0 ).c_str() );
    vaam.setDistance( maxDistance );

    size_t nrOfQueries = 0;
    size_t sumOfCandidates = 0;

    if( machineReadable ) {
	std::wcout << "fsdict::Vaam: READY [machineReadable=true]" << std::endl;
    }
    else {
	std::wcout << "fsdict::Vaam: READY [machineReadable=false]" << std::endl;
    }

    std::wcerr << "vaamFilter startup time: " << watch.readMilliseconds() << "ms" << std::endl;
    watch.start();

    while( std::getline( std::wcin, query ).good() ) {
	++nrOfQueries;
	answers.clear();
	vaam.query( query, &answers );

#ifndef FSDICT_VAAMFILTER_PRINTNONE
	std::sort( answers.begin(), answers.end() );
#endif

	sumOfCandidates += answers.size(); 

	if( answers.empty() ) {
#ifndef FSDICT_VAAMFILTER_PRINTNONE
	    std::wcout<<query<<":NONE"<<std::endl;
#endif
	}
	else if( machineReadable ) {
	    // all interpretations of the query in one line
#ifndef FSDICT_VAAMFILTER_PRINTNONE
	    for( std::vector< fsdict::Interpretation >::const_iterator it = answers.begin(); it!= answers.end(); ++it ) {
		it->print();
		if( it + 1  != answers.end() ) std::wcout<<"|";
	    }
	    std::wcout<<std::endl;
#endif
	}
	else {
	    // new line for each interpretation of the query
#ifndef FSDICT_VAAMFILTER_PRINTNONE
	    for( std::vector< fsdict::Interpretation >::const_iterator it = answers.begin(); it!= answers.end(); ++it ) {
		it->print();
		std::wcout<<std::endl;
	    }
#endif
	}
	
//	std::wcout<<watch.readMilliseconds()<<" ms"<<std::endl;
    } // for all input

    if( errno == EILSEQ ) {
	throw fsdict::exceptions::badInput( "fsdict::vaamFilter: Input encodig error" );
    }
    

    std::wcout<<watch.readMilliseconds()<<" ms for "<< nrOfQueries << " queries. AVG: " 
	      << (double)watch.readMilliseconds() / (double)nrOfQueries << "ms" << std::endl;
    std::wcout<<sumOfCandidates << " answers for "<< nrOfQueries << " queries. AVG: " 
	      << (double)sumOfCandidates / (double)nrOfQueries << std::endl;
    

    if( fbdic ) {
	delete( fbdic );
	fbdic = 0;
	baseDic = 0;
    }
    
    if( baseDic ) {
	delete( baseDic );
	baseDic = 0;
    }
    
    } catch( fsdict::exceptions::fsdictException ex ) {
	std::wcout<<"Caught exception: "<<ex.what()<< std::endl;
    }
    
    

    return 0;
}
