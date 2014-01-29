#ifndef SUGGESTITER_H
#define SUGGESTITER_H SUGGESTITER_H

class SuggestIter { // of class LevNDEA
 private: 
    LevNDEA& la_;
    size_t stackIndex;

    const wchar_t* susoString_; 

    // the currently suggested character
    wchar_t c;

    // floor and charPos to remember the position during intelligent suggesting
    // charPos is also used to move through the susoString
    size_t floor;
    const wchar_t* charPos;

    bool intelligentMode_;

    /** 
     * when a character c is checked, its charvec is or'd with this bitvector.
     * That way we can remember which chars have already been checked on lower floors
     */
    unsigned long long checked;

 public:
    SuggestIter( LevNDEA& initLa, int si = 0, const wchar_t* susoString = NULL )
	: la_( initLa ),
	  stackIndex( si ),
	  susoString_( susoString ) {

	intelligentMode_ = true;
	reset();
    }
	
    wchar_t operator*() const {
	return c; 
    }

    // find an intelligent suggestion in the automaton
    // may only be called with floor <= la_.getmaxDist()
    wchar_t findSuggestion() {
	if( floor > la_.getMaxDist() ) {
	    std::cerr<<"SuggestIter::findSuggestion: STRANGE BEHAVIOUR, this should not happen!"<<std::endl;
	    exit(1);
	}

	while( ( ( la_.charvec( *charPos ) & checked ) != 0 ) // while *charPos was checked before
 	       || ( la_.charvec(*charPos) & la_.getFloor( stackIndex, floor ) ) == 0 ) { //OR there's no horiz. transition on the current floor with label *charPos
	    
	    ++charPos;
	    if( ! *charPos ) { // tried all chars for current floor
		++floor; // try next floor
		if(floor > la_.getMaxDist()) { // all floors processed, no more intelligent guesses
		    intelligentMode_ = false;
		    charPos = susoString_; // initialise c for going through susoString
		    while( *charPos && ( la_.charvec( *charPos ) & checked ) != 0 ) { ++charPos; } // assign to c the next char of the susoString that wasn't checked before
		    c = *charPos;
		    return c;
		}
		charPos = la_.getAllChars(); // reset charPos to beginning of allChars
	    }
	}
	c = *charPos;
	checked |= la_.charvec( c );
	return c;
    }
    
    SuggestIter& operator++() {
	if( intelligentMode() ) {
	    if( floor > la_.getMaxDist() ) {  // this happens if the la's maxDist was decremented
		charPos = susoString_; // initialise c for going through susoString
		intelligentMode_ = false;
	    }
	    else {
		++charPos;
		c = findSuggestion(); // this might stop intelligentMode
	    }
	}
	else {
	    ++charPos; 
	}

	if( ! intelligentMode() ) { // this is no 'else', because intelligentMode_ can change in if-statement (findSuggestion)
	    while( *charPos && ( la_.charvec( *charPos ) & checked ) != 0 ) { ++charPos; } // assign to c the next char of the susoString that wasn't checked before
	    c = *charPos;
	}

	return *this;
    }

    void reset() {
	floor = 0;
	charPos = la_.getAllChars();
	c = 1;
	checked = (unsigned long long)-1ll;
	for( const wchar_t* cc = susoString_; *cc; ++cc ) {
	    checked = checked & ~la_.charvec( *cc );
	}

	c = findSuggestion();
	// PROBLEM HERE!! c can be 0 if none of the intelligent guesses applies !!!

    }

    bool intelligentMode() {
	return intelligentMode_;
    }
      
}; // End class SuggestIter

#endif
