
#include "./TestCSLLocale.h"
#include<fsdict/Global.h>
#include<fsdict/CSLLocale/CSLLocale.h>

int main() {
    std::locale::global( std::locale( "en_GB.utf-8" ) );

    fsdict::TestCSLLocale t;

    try {
	t.run();
    } catch( std::exception& exc ) {
	std::wstring wideWhat;
	fsdict::CSLLocale::string2wstring( exc.what(), wideWhat );
	std::wcerr << wideWhat << std::endl;
    }


}
