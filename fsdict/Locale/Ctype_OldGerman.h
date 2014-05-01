#ifndef FSDICT_CTYPE_OLDGERMAN_H
#define FSDICT_CTYPE_OLDGERMAN_H FSDICT_CTYPE_OLDGERMAN_H

#include<locale>
#include<iostream>
#include<vector>
#include<errno.h>

/**
 * @brief This is a custom implementation of a ctype facet, including German umlaute
 * and also the combining diacritical marks used for old texts.
 *
 * Please consult some STL documentation for info on the methods.
 *
 * Here is the best ever unicode table: http://triggertek.com/r/unicode/
 *
 * @author Ulrich Reffle, 2008
 */
class Ctype_OldGerman : public std::ctype< wchar_t > {

public:

    Ctype_OldGerman( std::locale const& loc ) :
	builtInLocale_( loc ) { // copy given locale

        // initialize codepoint-mapping. 0 means that for teh given codepoint no special CharInfo exists.
	char2index_.resize( maxChar, 0 );

	masks_.push_back( CharInfo( 0, 0, 0 ) ); // block the the 0-th field of the vector

	// map upper-lower case characters for Latin-1 supplement of unicode
	// see: http://triggertek.com/r/unicode/00A0-00FF
	for( size_t c = 0xC0; c <= 0xDE; ++c ) {
            if( c == 0xD7 ) continue; // this is the "MULTIPLICATION SIGN" and is an exception!

	    // the uppercase char at pos c
	    masks_.push_back( CharInfo( c, ( alnum | alpha | upper | graph | print ), c + 0x20 ) );
	    char2index_.at( c ) = masks_.size() - 1;

	    // the corr. lowercase char at pos c + 0x20
	    masks_.push_back( CharInfo( c + 0x20, ( alnum | alpha | lower | graph | print ), c  ) );
	    char2index_.at( c + 0x20 ) = masks_.size() - 1;
	}
	// special treatment for 'ß'=0xDF
	masks_.push_back( CharInfo( 0xDF, ( alnum | alpha | lower | graph | print ), 0xDF ) );
	char2index_.at( 0xDF ) = masks_.size() - 1;

	// give property 'alnum|alpha' to all combining diacritical marks
	// http://triggertek.com/r/unicode/0300-036F
	for( size_t c = 0x300; c <= 0x36f; ++c ) {
	    // the uppercase char at pos c
	    masks_.push_back( CharInfo( c, ( alnum | alpha | graph | print ), c ) );
	    char2index_.at( c ) = masks_.size() - 1;
	}
    }


    bool do_is (mask m, wchar_t c ) const {
	if( char2index_.at( c ) ) {
	    return ( masks_.at( char2index_.at( c ) ).mask_ & m ) != 0;
	}
	else {
	    return std::use_facet< std::ctype< wchar_t > >( builtInLocale_ ).is( m, c );
	}
    }

    wchar_t do_toupper( wchar_t c ) const {
	if( char2index_.at( c ) ) {
	    if( is( lower, c ) ) {
		return masks_.at( char2index_.at( c ) ).otherCase_;
	    }
	    else return c;
	}
	else {
	    return std::use_facet< std::ctype< wchar_t > >( builtInLocale_ ).toupper(  c );
	}
    }

    wchar_t do_tolower( wchar_t c ) const {
	if( char2index_.at( c ) ) {
	    if( is( upper, c ) ) {
		return masks_.at( char2index_.at( c ) ).otherCase_;
	    }
	    else return c;
	}
	else {
	    return std::use_facet< std::ctype< wchar_t > >( builtInLocale_ ).tolower(  c );
	}
    }


private:
    class CharInfo {
    public:
	CharInfo( wchar_t c, mask m, wchar_t oc ) :
	    c_( c ),
	    mask_( m ),
	    otherCase_( oc ) {
	}

	wchar_t c_;
	mask mask_;
	wchar_t otherCase_;

    };

    std::locale builtInLocale_;
    static const size_t maxChar = 65535;

    /**
     * has size maxChar and maps codepoints to CharInfos in the masks_ vector
     */
    std::vector< size_t > char2index_;

    std::vector< CharInfo > masks_;

}; // class

#endif
