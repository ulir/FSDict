#ifndef CSL_CSLLOCALE_CXX
#define CSL_CSLLOCALE_CXX CSL_CSLLOCALE_CXX


#include "./CSLLocale.h"
#include<csl/codecvt/UTF8_Codecvt.h>

namespace csl {

    CSLLocale::CSLLocale() :
	std::locale( std::locale( std::locale( "C" ), new UTF8_Codecvt() ), new Ctype_OldGerman( std::locale( "C" ) ) )  {
	
    }

}

#endif
