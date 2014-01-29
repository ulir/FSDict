#include "../Global.h"
#include "../Alphabet/Alphabet.h"
#include "./SearchText.h"

using namespace csl;

/**
 * searchText
 * 
 * @author Uli Reffle, <uli@cis.uni-muenchen.de>
 * @date 2007
 */
int main( size_t argc, char** argv ) {
    setlocale(LC_CTYPE, "de_DE.UTF-8");  /*Setzt das Default Encoding für das Programm */

    if( argc != 2 ) {
	std::cerr<<"Use like: "<<argv[0]<<" <binDic>"<<std::endl;
	exit(1);
    }



    SearchText searcher( argv[1] );
    searcher.search();



    return 0;
}
