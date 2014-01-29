
#include<iostream>
#include<csl/Getopt/Getopt.h>
#include<csl/MinDic/MinDic.h>
#include<csl/Pattern/PatternGraph.h>


int main(int argc, const char** argv ) {

    std::locale::global( std::locale( "de_DE.utf-8" ) );
    
    csl::Getopt opt( argc, argv );
    
    if( opt.getArgumentCount() < 1 ) {
	std::wcerr<<"so nicht!"<<std::endl;
	exit( 1 );
    }

    csl::PatternGraph patGraph;
    patGraph.loadPatterns( opt.getArgument( 0 ).c_str() );

    patGraph.toDot();

}
