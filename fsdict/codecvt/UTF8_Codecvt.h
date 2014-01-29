#ifndef FSDICT_UTF8_CODECVT_H
#define FSDICT_UTF8_CODECVT_H FSDICT_UTF8_CODECVT_H

#include<locale>
#include<iostream>
#include<errno.h>

/**
 * This is a convenience macro to create a new locale with most of
 * the system's standard locale but with the csl_internal utf8 codecvt facet.
 */
#define FSDICT_UTF8_LOCALE ( std::locale( std::locale( "" ), new fsdict::UTF8_Codecvt() ) )

namespace fsdict {

/**
 * @brief This is a custom implementation of a codecvt facet for utf-8, as it does not seem
 * to be present on all systems (especially WIN).
 *
 * All methods implemented here are implementations of virtual methods of std::codecvt.
 * Please consult some STL documentation for info on the methods.
 *
 * @author Ulrich Reffle, 2008
 */
    class UTF8_Codecvt : public std::codecvt< wchar_t, char, std::mbstate_t > {

    public:
	virtual bool do_always_noconv() const throw() {
	    return false; // we always convert
	}

	virtual int do_encoding() const throw() {
	    return sizeof(wchar_t);
	}

	virtual int do_length(state_type& state, const char *first1, const char *last, size_t len) const {
	    return len * sizeof( char );
	}
    
	virtual int do_max_length() const throw() {
	    return 4;
	}

	virtual result do_unshift(state_type& state, char *first, char *last, char *& next) const {
	    return error;
	}

	virtual result do_in(state_type& state, const char *from, const char *fromEnd, const char *&fromNext,
			     wchar_t *to, wchar_t *toEnd, wchar_t *&toNext) const {
	

	    const unsigned int leadByteMasks[5] = {256, 256, 31, 15, 7};

	    while( from != fromEnd ) {
		// the ...Next variables remain on positions where complete characters are processed, i.e. no
		// special mbstate_t is needed in case of "partial" return
		fromNext = from;
		toNext = to;
		if( to == toEnd ) return partial; // per run of this loop we write exactly one internal char

		if( ( *from & 0x80 ) == 0 ) { // 1-byte leadbyte with leading 0
		    // std::wcerr<<"1 sequence"<<std::endl;  // DEBUG
		    *to = *from;
		    ++to; ++from;
		}
		else if( *from & 0xC0 ) { // multibyte leadbyte: at least two 1 bits at beginning 
		    // find out how many bytes the whole sequence has (that is, how many leading 1-bits there are)
		    char leadByte = *from << 2;
		    size_t nrOfBytes = 2;
		    while( leadByte & 0x80 ) {
			++nrOfBytes;
			leadByte <<= 1;
		    }
		    // std::wcerr<<nrOfBytes<<" sequence"<<std::endl;  // DEBUG

		    *to = *from & leadByteMasks[nrOfBytes];
		
		    if( from + nrOfBytes - 1 >= fromEnd ) {
			return partial;
		    }
		    while( --nrOfBytes ) {
			++from;
			if( ! ( ( *from & 0x80 ) && !( *from & 0x40 ) ) ) { // if not a proper follow-byte
			    errno = EILSEQ;
			    return error;
			}
			*to <<= 6;
			*to |= *from & 0x3f;
		    }
		    ++to; ++from;
		}
		else {
		    // no leadbyte, though expected
		    errno = EILSEQ;
		    return error;
		}
	    }

	    fromNext = from;
	    toNext = to;
	    // std::wcout<<"just finished a do_in: "<<toNext<<std::endl;
	    return ok;
	}



	virtual result do_out( state_type& state, wchar_t const* from, wchar_t const* fromEnd, wchar_t const*& fromNext,
			       char* to, char* toEnd, char*& toNext) const {

	    while(  from != fromEnd ) {
		if( to == toEnd ) {
		    std::wcerr<< "to-Buffer too small" <<std::endl;
		    return partial;
		}

		// if( *from == L'1' ) { //   TEEEEST !!!!!!!!!!!
		//     *to = 'Y';
		//     ++to;
		// }
		else if( *from < 0x80 ) { // 1 byte
		    // std::wcout<<"1-byte: "<<*from<<std::endl; // DEBUG
		    *to = static_cast< char >( *from );
		    ++to;
		}
		else if( *from < 0x800 ) { // 2 bytes
		    if( to + 1 >= toEnd ) {
			std::wcout<< "to-Buffer too small" <<std::endl;
			return partial;
		    }
		    // std::wcerr<<"2-byte: "<<*from<<std::endl;  // DEBUG

		    *to = ( *from >> 6 ) | 0xC0;
		    *( to + 1 ) = ( *from & 0x3F ) | 0x80;
		
		    to += 2;
		}
		else if( *from < 0x10000 ) { // 3 bytes		
		    if( to + 2 >= toEnd ) {
			// std::wcerr<< "to-Buffer too small" <<std::endl;  // DEBUG
			return partial;
		    }
		    // std::wcerr<<"3-byte: "<<*from<<std::endl;  // DEBUG
		    *( to + 2 ) = ( *from & 0x3F ) | 0x80;
		    *( to + 1 ) = ( ( *from >> 6 ) & 0x3F ) | 0x80;
		    *to = ( *from >> 12 ) | 0xE0;
		
		    to += 3;
		}
		else { // 4 bytes
		    if( to + 3 >= toEnd ) {
			std::wcerr<< "to-Buffer too small" <<std::endl;
			return partial;
		    }
		    // std::wcerr<<"4-byte: "<<*from<<std::endl;  // DEBUG
		    *( to + 3 ) = ( *from & 0x3F ) | 0x80;
		    *( to + 2 ) = ( ( *from >> 6 ) & 0x3F ) | 0x80;
		    *( to + 1 ) = ( ( *from >> 12 ) & 0x3F ) | 0x80;
		    *to = ( *from >> 18 ) | 0xF0;
		
		    to += 4;
		}

		++from;
	    }
	    fromNext = from;
	    toNext = to;

	    return ok;
	} // do_out

	
    }; // class

} //eon

#endif
