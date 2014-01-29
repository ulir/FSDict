#include <fsdict/Global.h>
#include <fsdict/MinDicString/MinDicString.h>
#include <fsdict/Getopt/Getopt.h>
#include <fsdict/CSLLocale/CSLLocale.h>

using namespace fsdict;
int main( int argc, const char** argv ) {

    std::locale::global( std::locale( "" ) );


    try { 
	Getopt options( argc, argv );
	
	if( options.getArgumentCount() != 2 ) {
	    std::cerr<<"Use like: "<<argv[0]<<" <txtDic> <binDic>"<<std::endl;
	    return 1;
	}
	
	MinDicString mds;
	
	if( options.hasOption( "cislex" ) ) {
	    mds.setKeyValueDelimiter( '.' );
	}
	
	mds.compileDic( options.getArgument( 0 ).c_str() );
	mds.writeToFile( options.getArgument( 1 ).c_str() );
	
//   mds.printDic();

    }
    catch( fsdict::exceptions::fsdictException exc ) {
	std::wstring wide_what;
	fsdict::CSLLocale::string2wstring( exc.what(), wide_what );
	std::wcerr << "fsdict::compileMDString: caught fsdictException and aborted: " << wide_what << std::endl;
	return 1;
    }
    catch( std::exception exc ) {
	std::wcerr << "fsdict::compileMDString: caught std::exception. Aborted." << std::endl;
	return 1;
    }

    return 0;
}
