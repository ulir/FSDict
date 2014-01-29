#ifndef FSDICT_CSLLOCALE_CXX
#define FSDICT_CSLLOCALE_CXX FSDICT_CSLLOCALE_CXX


#include "./CSLLocale.h"
#include<fsdict/codecvt/UTF8_Codecvt.h>

namespace fsdict {

    CSLLocale::CSLLocale() :
	std::locale( std::locale( std::locale( "C" ), new UTF8_Codecvt() ), new Ctype_OldGerman( std::locale( "C" ) ) )  {
	
    }

}

#endif
