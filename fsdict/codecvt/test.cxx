#include <iostream>
#include <fstream>
#include <string>
#include <locale>

#include "./UTF8_Codecvt.h"

int main(int argc, char** argv) {



    std::locale::global( std::locale( "" ) );

//    std::locale::global( std::locale( "de_DE.utf-8" ) );
//    std::wcin.imbue( std::locale( "de_DE.utf-8" ) );

    std::wofstream fileOut;
    fileOut.imbue( FSDICT_UTF8_LOCALE ); // set the stream locale
    fileOut.open( "out.txt" ); // use binary to prevent fwrite from replacing \n with \r\n
 
    std::wifstream fileIn; 
    fileIn.imbue( FSDICT_UTF8_LOCALE ); // set the stream locale

    fileIn.open( argv[1] ); // use binary to prevent fwrite from replacing \n with \r\n


    std::wstring str;

    while( std::getline( fileIn, str ).good() ) {
	fileOut << str << std::endl;
    }

    fileOut.close();

    return 0;
}
