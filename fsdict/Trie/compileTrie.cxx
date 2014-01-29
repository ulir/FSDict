#include "./Trie.h"
#include<iostream>

using namespace fsdict;

int main(int argc, char** argv) {
    setlocale(LC_CTYPE, "de_DE.UTF-8");  /*Setzt das Default Encoding für das Programm */


    if(argc != 3) {
	std::cerr<<"Use like: "<<argv[0]<<" <txtDic> <binDic>"<<std::endl;
	exit(1);
    }

    try {
	Trie< int > t;

	t.compileDic( argv[1] );
	t.writeToFile( argv[2] );
	t.toDot();
//	t.printDic();
//      t.printCells();
	t.doAnalysis();
    }
    catch( exceptions::fsdictException ex ) {
	std::cerr<<"compileTrie:"<<ex.what()<<std::endl;
	return 1;
    }

    return 0;
}
