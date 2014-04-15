#ifndef FSDICT_CSLLOCALE_H
#define FSDICT_CSLLOCALE_H FSDICT_CSLLOCALE_H

#include<locale>
#include<sstream>
#include<fsdict/Global.h>
#include<fsdict/codecvt/UTF8_Codecvt.h>
#include<fsdict/Locale/Ctype_OldGerman.h>

namespace fsdict {

    /**
     * @brief A locale using our own implementation of a utf8 codecvt, and a ctype facet handling umlauts and other peculiarities properly.
     */
    class UTF8Locale : public std::locale {
    public:
	inline static UTF8Locale& Instance() {
	    static UTF8Locale cslLocale_;  // local static object initialization
	    return cslLocale_;
	}

	/**
	 * @brief Goes the STL facet-based way to transform a string to a number
	 * @param[in]  str     a string containing the number and nothing else
	 *
	 * Throws a fsdictException if the conversion causes problems.
	 */
	template< typename T, typename char_type >
	inline static T string2number( std::basic_string< char_type > const& str ) {
	    T number;
	    std::basic_istringstream< char_type > iss;
	    iss.imbue( Instance() );
	    iss.str( str );

	    iss >> number;
	    
	    // no badbit, no failbit, no goodbit: only the eofbit, because the complete string should be interpreted
	    if( iss.rdstate() != (  std::wistringstream::eofbit ) ) {
		throw exceptions::fsdictException( "fsdict::UTF8Locale::string2number: could not interpret string:" );
	    }
	    return number;
	}


	/**
	 * @brief converts a std::wstring into its byte-character equivalent
	 *
	 * @param[in]  wstr the input string
	 * @param[out] str  the output string
	 */
	inline static void wstring2string( std::wstring const& wstr, std::string& str ) {
	    std::codecvt< wchar_t, char, std::mbstate_t > const& ccvt = std::use_facet< std::codecvt< wchar_t, char, std::mbstate_t > >( Instance() );

	    str.resize( wstr.size() * ccvt.max_length() );
	    std::codecvt< wchar_t, char, std::mbstate_t >::state_type state; 
	    wchar_t const* fromNext = 0;
	    char* toNext = 0;
	    ccvt.out( state, 
		      wstr.c_str(), 
		      wstr.c_str()+wstr.size(), 
		      fromNext, 
		      (char*)str.c_str(),
		      (char*)str.c_str() + str.size(), 
		      toNext 
		);

	    str.resize( toNext - str.c_str() );
	}


	/**
	 * @brief converts a std::string into its wide-character equivalent
	 *
	 * @param[in]  str  the input string
	 * @param[out] wstr the output string
	 */
	inline static void string2wstring( std::string const& str, std::wstring& wstr ) {
	    std::codecvt< wchar_t, char, std::mbstate_t > const& ccvt = std::use_facet< std::codecvt< wchar_t, char, std::mbstate_t > >( Instance() );
	    
	    wstr.resize( str.size() * ccvt.max_length() ); // this makes no sense?! str.size() would be enough
	    std::codecvt< wchar_t, char, std::mbstate_t >::state_type state; 
	    char const* fromNext = 0;
	    wchar_t* toNext = 0;
	    ccvt.in( state, 
		     str.c_str(), 
		     str.c_str()+str.size(), 
		     fromNext, 
		     (wchar_t*)wstr.
		     c_str(),
		     (wchar_t*)wstr.c_str() + wstr.size(), 
		     toNext 
		);
	    
	    wstr.resize( toNext - wstr.c_str() );
	}
	
	/**
	 * @brief Returns a copy of a wide string equivalent to the given narrow string.
	 */
	inline static std::wstring string2wstring( std::string const& str ) {
	    std::wstring ret;
	    string2wstring( str, ret );
	    return ret;
	}

	/**
	 * @brief Returns a copy of a narrow string equivalent to the given wide string.
	 */
	inline static std::string wstring2string( std::wstring const& str ) {
	    std::string ret;
	    wstring2string( str, ret );
	    return ret;
	}




    private:
	/**
	 * @brief private constructor
	 */
	UTF8Locale();

	/**
	 * @brief private destructor
	 */
	UTF8Locale( UTF8Locale const & );

	inline ~UTF8Locale() { 
	}  

	UTF8Locale &operator=( UTF8Locale const & );  // assignment operator is hidden

    };

	
} // eon






#endif
