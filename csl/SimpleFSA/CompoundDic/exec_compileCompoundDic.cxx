#include "./CompoundDic.h"
#include<csl/TransTable/TransTable.h>
#include<csl/SimpleFSA/Simple2TransTable.h>

int main( int argc, char** argv ) {
    
    std::locale::global( std::locale( "de_DE.utf-8" ) );

    csl::SimpleFSA::CompoundDic cd;

    cd.compute( argv[1] );

    cd.getDic().analyze();
//    cd.getDic().toDot();

    
    csl::SimpleFSA::Simple2TransTable::TransTable_t transTable;
    csl::SimpleFSA::Simple2TransTable converter;

    converter.translate( cd.getDic(), &transTable );
    
//    transTable.toDot();
    transTable.writeToFile( argv[2] );

}

