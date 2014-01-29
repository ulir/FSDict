#include "./LevNDEA.cxx"
#include "../Global.h"
#include <iostream>
#include <cstdio>

using namespace fsdict;

int main(int argc, char** args) {
    setlocale( LC_CTYPE, "de_de.utf-8" );
    if(argc != 2) {
	std::cerr<<"Use like: levNDEA_test <pattern>"<<std::endl;
	exit(1);
    }

    wchar_t pattern[Global::lengthOfStr];
    mbstowcs( pattern, args[1], Global::lengthOfStr );
    LevNDEA lndea;

    std::cout<<"LevNDEA test"<<std::endl;

    lndea.loadPattern( pattern );
    lndea.printFloors(0);

//     char c;
//     char word[100];
//     int depth = 0;
//     while(c = std::fgetc(stdin)) {
// 	if(c==10) continue;
// 	word[depth] = c;
// 	word[depth+1] = 0;
// 	lndea.walk( c,depth);
// 	++depth;
// 	lndea.printFloors(depth);
// 	std::cout<<std::endl<<word<<std::flush;

//     }





    // print allChars
    std::cout<<"allChars="<<std::flush;
    const wchar_t* c = lndea.getAllChars();
    while( *c ) {
      std::wcout<<*c<<std::flush;
      ++c;
    }
    std::cout<<std::endl;


    LevNDEA::SuggestIter sug( lndea, 0, L"abctexyz" );
    // get suggestions
    while( *sug ) {
	printf( "Suggest: %lc\n", *sug );
	++sug;
    }
}
