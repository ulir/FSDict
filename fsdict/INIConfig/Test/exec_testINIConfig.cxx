

#include "./TestINIConfig.h"
#include <fsdict/CSLLocale/CSLLocale.h>


int main() {
    std::locale::global( std::locale( "" ) );
    
    fsdict::TestINIConfig ti;

    try { 
	ti.run();
    } catch( std::exception& exc ) {
	std::wstring wideWhat;
	fsdict::CSLLocale::string2wstring( exc.what(), wideWhat );
	std::wcout << "Exception: " << wideWhat << std::endl;
	
    }
    
};
