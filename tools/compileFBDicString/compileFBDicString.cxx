#include <fsdict/Global.h>
#include <fsdict/FBDicString/FBDicString.h>
#include <fsdict/Getopt/Getopt.h>

using namespace fsdict;
int main( int argc, const char** argv ) {

    std::locale::global( std::locale( "" ) );


    try { 
	Getopt options( argc, argv );
	
	if( options.getArgumentCount() != 2 ) {
	    std::cerr<<"Use like: "<<argv[0]<<" <txtDic> <binDic>"<<std::endl;
	    return 1;
	}
	
	FBDicString fbds;
	
	if( options.hasOption( "cislex" ) ) {
	    fbds.setKeyValueDelimiter( '.' );
	}
	
	fbds.compileDic( options.getArgument( 0 ).c_str() );
	fbds.writeToFile( options.getArgument( 1 ).c_str() );
	

    }
    catch( fsdict::exceptions::fsdictException& exc ) {
	std::wstring wide_what;
	fsdict::CSLLocale::string2wstring( exc.what(), wide_what );
	std::wcerr << "fsdict::compileFBDString: caught fsdictException and aborted: " << wide_what << std::endl;
	return 1;
    }
    catch( std::exception& exc ) {
	std::wcerr << "fsdict::compileFBDString: caught std::exception. Aborted." << std::endl;
	return 1;
    }

    return 0;
}
