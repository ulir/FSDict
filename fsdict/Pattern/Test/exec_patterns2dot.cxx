
#include<iostream>
#include<fsdict/Getopt/Getopt.h>
#include<fsdict/MinDic/MinDic.h>
#include<fsdict/Pattern/PatternGraph.h>


int main(int argc, const char** argv ) {

    std::locale::global( std::locale( "de_DE.utf-8" ) );

    fsdict::Getopt opt( argc, argv );

    if( opt.getArgumentCount() < 1 ) {
	std::wcerr<<"so nicht!"<<std::endl;
	exit( 1 );
    }

    fsdict::PatternGraph patGraph;
    patGraph.loadPatterns( opt.getArgument( 0 ).c_str() );

    patGraph.toDot();

}
