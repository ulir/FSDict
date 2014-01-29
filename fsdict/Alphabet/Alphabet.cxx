#ifndef FSDICT_ALPHABET_CXX
#define FSDICT_ALPHABET_CXX FSDICT_ALPHABET_CXX

#include<iostream>
#include<algorithm>
#include "./Alphabet.h"


namespace fsdict {

    Alphabet::Alphabet() :
	magicNumber_( 42 ),
	hasChar_( Global::maxNrOfChars, false )
    {
	
    }

    /**
     * @todo trouble with signed/unsigned
     */
    void Alphabet::addChar( wchar_t c ) {
	if( (size_t)c >= Global::maxNrOfChars ) {
	    throw exceptions::outOfRange( "Alphabet::addChar: add requested for out-of-range codepoint." );
	}
	// printf( "fsdict::Alphabet::addChar: Add char %lc\n", c ); // DEBUG
	if( ! hasChar_[c] ) {
	    hasChar_[c] = true;
	    allChars_.push_back( c );
	}
    }

    bool Alphabet::hasChar( wchar_t c ) const {
	if( (size_t)c >= Global::maxNrOfChars )
	    throw exceptions::outOfRange( "Alphabet::hasChar: lookup requested for out-of-range codepoint." );
	return hasChar_[ c ];
    }

    void Alphabet::initConstruction() {
	header_.magicNumber_ = magicNumber_;
    }

    void Alphabet::finishConstruction() {
	std::sort( allChars_.begin(), allChars_.end() );
	header_.size_ = allChars_.size();
    }

    void Alphabet::loadFromStream( FILE* fi ) {
	if ( !fi )
	    throw exceptions::badFileHandle( "fsdict::Alphabet:loadFromStream: Couldn't read from filehandle." );

	size_t readElements = fread( &header_, sizeof( Header ), 1, fi );
	if( readElements != 1 ) throw exceptions::cslException( "fsdict::Alphabet::loadFromStream: Errors while reading Header." );
	
	if ( ( header_.magicNumber_ != magicNumber_ ) )
	    throw exceptions::badDictFile( "fsdict::Alphabet::loadFromStream: Magic number comparison failed.\n" );

	allChars_.reserve( (size_t)header_.size_ );
	wchar_t c;
	for( size_t i = 0; i < header_.size_; ++i ) {
	    readElements = fread( &c, sizeof( wchar_t), 1, fi );
	    if( readElements != 1 ) throw exceptions::cslException( "fsdict::Alphabet::loadFromStream: Errors while reading alphabet characters." );

	    addChar( c );
	    hasChar_.at( c ) = true;
	}
    }

    void Alphabet::writeToStream( FILE* fo ) const {
	if ( !fo ) {
	    throw exceptions::badFileHandle( "fsdict::Alphabet::writeToStream: Couldn't write to filehandle." );
	}
	fwrite( &header_, sizeof( header_ ), 1, fo );
	fwrite( &allChars_[0], sizeof( wchar_t), allChars_.size(), fo );
    }
} // end of namespace fsdict

#endif
