#include "./CompoundDic.h"
#include<vector>
#include<algorithm>
#include<time.h>
#include<string>

class ProduceCompounds {
public:
    ProduceCompounds( char const* dicFile ) :
	maxSize_( 0 ) {
	cd.compute( dicFile );
	srand( time( 0 ) );
    }


    void produce( size_t maxSize ) {
	maxSize_ = maxSize;

	traverse_depthFirst_recursive( cd.getDic().getRoot() );

    }

    std::wstring getOne() const {
	csl::SimpleFSA::State const* st = cd.getDic().getRoot();
	std::wstring word;

	while( 1 ) {
//	    std::wcout<<word<<std::endl;

	    if( st->getNrOfTransitions() == 0 ) return word;

	    int randomIndex = rand() %  st->getNrOfTransitions();
	    csl::SimpleFSA::State::const_trans_iterator trans = st->trans_begin();
	    while( --randomIndex >= 0 ) ++trans;
	    
	    word += trans->first;
	    st = trans->second;

	    if( st->isFinal() && ( rand() % 4 == 0 ) ) return word;
	}
    }

    void traverse_depthFirst_recursive( csl::SimpleFSA::State const* cur ) {
	static std::wstring str;
	
	
	if( str.size() > maxSize_ ) return;
	if( cur->isFinal() ) std::wcout<< str << std::endl;

	std::vector< std::pair< wchar_t, csl::SimpleFSA::State const* > > shuffledTrans;

	for( csl::SimpleFSA::State::const_trans_iterator trans = cur->trans_begin();
	     trans !=  cur->trans_end();
	     ++trans ) {
	    shuffledTrans.push_back( *trans );
	}
	std::random_shuffle( shuffledTrans.begin(), shuffledTrans.end() );
	
	if( ( str.size() > 0 ) && ( shuffledTrans.size() > 6 ) ) shuffledTrans.resize( 6 );
	    
	for( std::vector< std::pair< wchar_t, csl::SimpleFSA::State const* > >::const_iterator trans = shuffledTrans.begin();
	     trans !=  shuffledTrans.end();
	     ++trans ) {
	    str += trans->first;
	    traverse_depthFirst_recursive( trans->second );
	    str.resize( str.size() - 1 );
	}
    }

private:
    csl::SimpleFSA::CompoundDic cd;
    size_t maxSize_;
    
};



int main( int argc, char** argv ) {
    std::locale::global( std::locale( "de_DE.utf-8" ) );
    
    
    ProduceCompounds pc( argv[1] );
    size_t count = 0;
    while( count <  (size_t)atoi( argv[2] ) ) { 
	if( ++count % 10000 == 0 ) std::wcerr << count / 1000 << "k tokens produced" << std::endl;
	std::wcout<<pc.getOne()<<std::endl;
	++count;
    }
}

