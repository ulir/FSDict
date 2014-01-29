
#include<string>
#include<stack>
#include<errno.h>
#include"../MinDic/MinDic.h"



namespace csl {
    
    namespace SimpleFSA {

	class TrivialDecomp {
	public:
	    TrivialDecomp( char const* lexFile ) {
		computeMinDic( lexFile );
	    }

	    bool decomp( std::wstring const& word ) const {
		std::wcout<<"!"<<word<<std::endl;
		std::stack< std::wstring > alternatives;
		State const* st = minDic_.getRoot();
		// std::wcerr<<"startstate is "<< st <<std::endl;
		std::wstring::const_iterator c = word.begin();
		while( ( c != word.end() ) && 
		       ( st = st->delta( *c ) ) ) {
		    
		    std::wcerr<<"char is "<<*c<< ", state is "<< st <<std::endl;
		    if( st->delta('#') ) {
			alternatives.push( word.substr( c - word.begin() + 1 ) );
		    }
		    ++c;
		}
		if( st && st->delta('$') ) {
		    std::wcerr<<"state is final:"<< st <<std::endl;
		
		    return true;
		}
		else {
		    while( ! alternatives.empty() ) {
			std::wcout<<"TRY STEP:"<<alternatives.top()<<std::endl;
			bool ret = decomp( alternatives.top() );
			if( ret ) return true;
			alternatives.pop();
		    }
		}
		return false;
	    }


	private:
	    MinDic minDic_;

	    void computeMinDic( char const* file ) {
	    std::wifstream fi( file );
	    if( ! fi.good() ) {
		throw exceptions::badFileHandle( "csl::CompoundDic: File Open Error" );
	    }
	    fi.imbue( std::locale( "de_DE.utf-8" ) );
	    minDic_.initConstruction();
	    std::wstring line;
	    size_t count = 0;
	    while( getline( fi, line).good() ) {
		if( line.size() < 8  ) continue;
		if( ++count % 100000 == 0 ) std::wcerr<< count / 1000 << "k tokens processed."<<std::endl;


		// note that line 'foo#11'  adds two lines to the dic: foo# and foo$
		if( *( line.end() - 2 ) == L'1' ) {
		    minDic_.addToken( line.substr( 0, line.size() - 3 ) + L'#' );
		}
		if( *( line.end() - 1 ) == L'1' ) {
		    minDic_.addToken( line.substr( 0, line.size() - 3 ) + L'$' );
		}
	    }
	    if( errno == EILSEQ ) {
		throw exceptions::badInput( "csl::CompoundDic: Encoding error" );
	    }

	    minDic_.finishConstruction();
	    // minDic_.toDot();

	}

	};
    }
}
