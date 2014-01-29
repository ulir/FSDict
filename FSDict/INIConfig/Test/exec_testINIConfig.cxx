

#include "./TestINIConfig.h"
#include <csl/CSLLocale/CSLLocale.h>


int main() {
    std::locale::global( std::locale( "" ) );
    
    csl::TestINIConfig ti;

    try { 
	ti.run();
    } catch( std::exception& exc ) {
	std::wstring wideWhat;
	csl::CSLLocale::string2wstring( exc.what(), wideWhat );
	std::wcout << "Exception: " << wideWhat << std::endl;
	
    }
    
};
