#ifndef LEVDEA_CXX
#define LEVDEA_CXX LEVDEA_CXX

#include<fsdict/UTF8Locale/UTF8Locale.h>
#include<stdlib.h>
#include "./LevDEA.h"

namespace fsdict {

    LevDEA::LevDEA( int init_k ) : k_( init_k ),
				   transitions_(0),
				   finalInfo_(0),
				   charvecs_( Global::maxNrOfChars, 0 )
    {
	setThreshold( init_k );
    }

    LevDEA::~LevDEA() {
    }

    void LevDEA::setThreshold( size_t initK ) {
	k_ = initK;

	if( k_ == 0 ) {
	    transitions_ =        AutData< 0 >::transitions;
	    finalInfo_   =        AutData< 0 >::finalInfo;
	    suffixMatch_ =        AutData< 0 >::suffixMatch;
	    bitVectorLength_ =    AutData< 0 >::bitVectorLength;
	}
	else if( k_ == 1 ) {
	    transitions_ =        AutData< 1 >::transitions;
	    finalInfo_   =        AutData< 1 >::finalInfo;
	    suffixMatch_ =        AutData< 1 >::suffixMatch;
	    bitVectorLength_ =    AutData< 1 >::bitVectorLength;
	}
	else if( k_ == 2 ) {
	    transitions_ =        AutData< 2 >::transitions;
	    finalInfo_   =        AutData< 2 >::finalInfo;
	    suffixMatch_ =        AutData< 2 >::suffixMatch;
	    bitVectorLength_ =    AutData< 2 >::bitVectorLength;
	}
	else {
	    throw exceptions::fsdictException("Invalid Levenshtein threshold");
	}

	nrOfTransitions_ = 1 << bitVectorLength_;
	zeroShift_ = bitVectorLength_ / 2;

	/*
	  In case of k==1, z2k1 would be 111  (==7) ( 2k+1 set bits )
	  z2k2 would be 1111 (==15)  ( 2k+2 set bits )
	*/
	z2k1 = 1ll;
	z2k1 <<=  2 * k_ + 1;
	z2k1--; // a sequence of 2k+1 1-values
	z2k2 = 1ll;
	z2k2 <<= 2 * k_ + 2;
	z2k2--; // a sequence of 2k+2 1-values
    }

    size_t LevDEA::getThreshold() const {
	return k_;
    }

    void LevDEA::loadPattern( const wchar_t* p ) {
	cleanCharvecs(); // do this while the old pattern is still loaded!
	pattern_ = p;
	if( pattern_.length() > Global::lengthOfWord ) {
	    throw exceptions::badInput( "fsdict::LevDEA::loadPattern: Maximum Pattern length (as specified by Global::lengthOfWord) violated." );
	}
	calcCharvec();
    }

    void LevDEA::loadPattern_utf8( const char* p ) {
	std::wstring patternWide_;
	UTF8Locale::string2wstring( std::string( p ), patternWide_ );
	loadPattern( patternWide_.c_str() );
    }

    void LevDEA::cleanCharvecs() {
	for( std::wstring::const_iterator c = pattern_.begin(); c != pattern_.end(); ++c ) {
	    charvecs_.at( *c ) = 0;
	}
    }

    void LevDEA::calcCharvec() {
	bits64 bit = 1ll<<( pattern_.length()-1 );
	for( std::wstring::const_iterator c = pattern_.begin(); c != pattern_.end(); ++c ) {
	    if( static_cast< size_t >( *c ) > Global::maxNrOfChars ) {
		std::cerr << "Invalid codepoint:" << static_cast< size_t >( *c ) << std::endl;
		throw exceptions::fsdictException("Global::maxNrOfChars violated.");
	    }
	    charvecs_.at( *c ) |= bit;
	    bit >>= 1;
	}
    }

    void LevDEA::printTable() const {
    }

    void LevDEA::printCharvec() const {
	std::cout << "-------------" << std::endl;
	for( std::wstring::const_iterator c = pattern_.begin(); c != pattern_.end(); ++c ) {
	    printf( "%lc\n", *c );
	    printBits( charvecs_[*c] );
	}
	std::cout << "-------------" << std::endl;
    }

    void LevDEA::printBits( const bits64& n ) const {
	int i;
	for( i = 63;i >= 0;--i ) {
	    if( ( i % 10 ) == 0 ) printf( "%d", i / 10 );
	    else if( ( i % 10 ) == 5 ) printf( "|" );
	    else printf( " " );
	}
	printf( "\n" );
	for( i = 63;i >= 0;--i ) {
	    printf( "%i", ( int )( 1 & ( n >> i ) ) );
	}
	printf( "\n" );

    }

} // eon
#endif
