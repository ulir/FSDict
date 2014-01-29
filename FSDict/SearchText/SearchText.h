#include<istream>
#include<errno.h>
#include "../Global.h"
#include "../MinDicString/MinDicString.h"

namespace csl {

    class SearchText {
    private:
	class Buffer {
	public:
	    Buffer( std::wistream& );
	
	    /**
	     * return the character at the current position
	     */
	    wchar_t getCurChar();

	    wchar_t moveOn();
	    
	    size_t getTextPos();

	    wchar_t goBack( int delta );

	private:
	    static const size_t bufSize_ = Global::lengthOfStr;
	    wchar_t buffer_[bufSize_];
	    
	    std::wistream& stream_;

	    size_t textPos_; ///< denotes the position of the current char in the text (0, if standing at the 1st char)
	    size_t textRead_; ///< denotes the position of the last text symbol loaded into the buffer (0 if only the 1st symbol is loaded)

	}; // class Buffer

	Buffer buffer_;
	
	MinDicString mdicString_;
	
	const wctype_t alnumType;

	bool isSeparator( wchar_t c ) const;

	
    public:
	SearchText( char* mdicFile, std::wistream& stream );
	
	void search();
	
    }; // class Buffer



    SearchText::SearchText( char* mdicFile, std::wistream& stream = std::wcin ) : buffer_( stream ),
										  alnumType( wctype( "alnum" ) )
    {
	mdicString_.loadFromFile( mdicFile );
    }

    void SearchText::search() {
	wchar_t c;
	
	wchar_t str[Global::lengthOfLongStr];
	str[Global::lengthOfLongStr - 1] = 0;
	size_t strLength = 0;
	
	size_t pos = mdicString_.getRoot();
	size_t perfHashValue = 0;
	size_t matchAt = 0;
	size_t matchPerfHashValue = 0;
	int separatorAt = -1;

	c = buffer_.getCurChar();
	if( c == 0 ) return;

	while( c ) {
	    pos = mdicString_.getRoot();
	    strLength = 0 ;
	    perfHashValue = 0;
	    matchAt = 0;
	    matchPerfHashValue = 0;
	    separatorAt = -1;

	    // add c to string, regardless of whether it fits a path of the dictionary
	    while( ( str[strLength] = c, str[++strLength] = 0 ),
		   ( c && pos && ( pos = mdicString_.walkPerfHash( pos, c, perfHashValue ) ) ) ) {
		if( isSeparator( c ) && ( separatorAt == -1 ) ) {
		    separatorAt = strLength - 1;
		}
		if( mdicString_.isFinal( pos ) ) {
		    matchAt = strLength;
		    matchPerfHashValue = perfHashValue;
		}
		// printf( "could walk: '%lc', pos=%d, str='%ls'\n", c, pos, str ); // DEBUG

		c = buffer_.moveOn(); // move c to next textposition
		
	    }
	    // printf( "Raus aus der Schleife, str='%ls', matchAt = %d\n", str, matchAt ); // DEBUG
	    
	    if( matchAt && isSeparator( str[matchAt] ) ) {
		str[matchAt] = 0;
		// printf( "Found '%s' on textpos %d\n", str, buffer_.getTextPos() );
		printf( "%ls#%s\n", str, mdicString_.getAnnByPerfHashValue( matchPerfHashValue ) );
		// printf( "%ls#%s\n", str, mdicString_.lookup( str ) );
		c = buffer_.goBack( strLength - matchAt - 1 );
	    }
	    else { // no hit
// 		if( strLength == 1 ) { // fail on the very first char
// 		    c = buffer_.moveOn();
// 		}

		if( separatorAt == -1 ) {
		    if( isSeparator( c ) ) {
			c = buffer_.moveOn();
		    }
		    else {
			while( ! isSeparator ( c ) ) {
			    // printf( "Skipped: '%lc'\n", c ); // DEBUG
			    c = buffer_.moveOn();
			}
		    }
		}
		else if( separatorAt == 0 ) {
		    //                  back to start | one to the right 
		    c = buffer_.goBack( strLength - 1 - 1 );
		}
		else if( separatorAt > 0 ) {
		    //                  back to start | move to the right 
		    c = buffer_.goBack( strLength - 1 - separatorAt );
		}
	    }
	}
    }

    bool SearchText::isSeparator( wchar_t c ) const {
	return ! iswctype( c, alnumType );
    }

    /////////////////// B U F F E R //////////////////////////////////////////////////

    SearchText::Buffer::Buffer( std::wistream& stream ) : stream_( stream ),
						    textPos_( 0 ),
						    textRead_( 0 )
    {
	stream_.get( buffer_[0] );
	if( stream.eof() ) {
	    buffer_[0] = 0;
	}
    }

    wchar_t SearchText::Buffer::getCurChar() {
	assert( textPos_ <= textRead_ );
	return buffer_[(textPos_) % bufSize_];
    }


    wchar_t SearchText::Buffer::moveOn() {

// 	if( textPos_ == 2* bufSize_ ) {
// 	    assert( textRead_ > bufSize_ );
// 	    textPos_ -= bufSize_;
// 	    textPos_ -= bufSize_;
// 	}

	++textPos_;
	if( textPos_ > textRead_ ) { // the difference must never be more than 1
	    ++textRead_;

	    stream_.get( buffer_[textRead_ % bufSize_] );

	    // HOW CAN AN ENCODING ERROR BE DETECTED???
	    if( errno == EILSEQ ) { // if failbit is set BEFORE eof
		throw exceptions::badInput( "SearchText: Encoding error in input sequence." );
	    }

	    // printf( "Read char: '%lc'\n", getCurChar() ); // DEBUG
	    if( stream_.eof() ) {
		buffer_[textRead_ % bufSize_] = 0;
	    }


//	    printf( "Read '%lc' on pos %d\n", buffer_[textPos_ % bufSize_], textPos_ ); // DEBUG
	    
	}
	assert( textPos_ <= textRead_ );
//	printf( "Return '%lc'\n", buffer_[(textPos_) % bufSize_] ); // DEBUG
	return buffer_[(textPos_) % bufSize_];
    }

	    
    size_t SearchText::Buffer::getTextPos() {
	return textPos_;
    }

    wchar_t SearchText::Buffer::goBack( int delta ) {
	assert( delta >= 0 );
	textPos_ -= delta;
	return getCurChar();
    }

} // eon
