
#include "./TestUTF8Locale.h"
#include<fsdict/Global.h>
#include<fsdict/UTF8Locale/UTF8Locale.h>

int main() {
    std::locale::global( std::locale( "de_DE.utf8" ) );

    fsdict::TestUTF8Locale t;

    try {
	t.run();
    } catch( std::exception& exc ) {
	std::wstring wideWhat;
	fsdict::UTF8Locale::string2wstring( exc.what(), wideWhat );
	std::wcerr << wideWhat << std::endl;
    }


}
