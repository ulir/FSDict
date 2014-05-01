

#include "./TestINIConfig.h"
#include <fsdict/UTF8Locale/UTF8Locale.h>


int main() {
    std::locale::global( std::locale( "" ) );

    fsdict::TestINIConfig ti;

    try {
	ti.run();
    } catch( std::exception& exc ) {
	std::wstring wideWhat;
	fsdict::UTF8Locale::string2wstring( exc.what(), wideWhat );
	std::wcout << "Exception: " << wideWhat << std::endl;

    }
}
