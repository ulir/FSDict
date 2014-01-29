
#include "./TestCSLLocale.h"
#include<csl/Global.h>
#include<csl/CSLLocale/CSLLocale.h>

int main() {
    std::locale::global( std::locale( "en_GB.utf-8" ) );

    csl::TestCSLLocale t;

    try {
	t.run();
    } catch( std::exception& exc ) {
	std::wstring wideWhat;
	csl::CSLLocale::string2wstring( exc.what(), wideWhat );
	std::wcerr << wideWhat << std::endl;
    }


}
