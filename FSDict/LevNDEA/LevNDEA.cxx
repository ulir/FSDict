#ifndef LEVNDEA_CXX
#define LEVNDEA_CXX LEVNDEA_CXX

#include "LevNDEA.h"

namespace csl {

    LevNDEA::LevNDEA() :
	charvecs_( Global::maxNrOfChars, 0 ) 
    {
	pattern_[0] = 0;
    }

    LevNDEA::~LevNDEA() {
    }


    void LevNDEA::loadPattern( const wchar_t* pattern, size_t maxDist ) {
	cleanCharvecs();

	patLength_ = wcslen( pattern );
	if( patLength_ > Global::lengthOfWord -1 ) {
	    throw exceptions::badInput( "csl::LevNDEA::loadPattern: pattern length restricted to Global::lengthOfWord -1 symbols." );
	}
	wcsncpy( pattern_, pattern, Global::lengthOfWord );
	memset( floors, 0, ( Global::lengthOfWord * Global::lengthOfWord ) ); // prepare memory

	calcCharvec();

	
	maxFloorIndex_ = ( maxDist != (size_t)-1 ) ? maxDist : patLength_;

	lastBit_ = firstBit_ >> patLength_;
	allBits_ = 0;
	
	for ( size_t i = 0; i <= patLength_; ++i ) { // is there a better way to do that?
	    allBits_ |= firstBit_ >> i;
	}

	floors[0][0] = firstBit_; // activate start state of lower stackframe
	// epsilon closure for lowest automaton of stack: activate diagonal line
	for ( size_t i = 0; i <= maxFloorIndex_; ++i ) {
	    floors[0][i] = firstBit_ >> i;
	}

//  printFloors(0);

	//    std::cout<<"New pattern: '"<<pattern<<"' with length "<<patLength<<std::endl;
    }

    void LevNDEA::cleanCharvecs() {
	for( const wchar_t* pat = pattern_; *pat; ++pat ) {
	    charvecs_.at( *pat ) = 0;
	}
    }
    

    void LevNDEA::calcCharvec() {
	bits64 c = firstBit_;
	size_t nrOfChars = 0;
	for ( wchar_t* pat = pattern_; *pat; ++pat, c >>= 1 ) {
	    if ( charvecs_[*pat] == 0 ) { //if char appeared for the 1st time
		allChars[nrOfChars++] = *pat;
	    }
	    charvecs_.at( *pat ) |= c;
	}
	allChars[nrOfChars] = 0;
	std::sort( allChars, allChars + nrOfChars );
    }
    
    bool LevNDEA::walk( wchar_t c, size_t stackIndex ) {
	static bool couldWalk;

	// horizontal transition for lower floor
	floors[stackIndex+1][0] = ( floors[stackIndex][0] & charvec( c ) ) >> 1;

	couldWalk = floors[stackIndex+1][0];


	// write updated automaton into stackIndex+1
	// check if there are active states at all (-> couldWalk)
	for ( size_t curFloor = 1; curFloor <= maxFloorIndex_; ++curFloor ) {

	    floors[stackIndex+1][curFloor] =
		( ( floors[stackIndex][curFloor] & charvec( c ) ) >> 1 ) | // horizontal transition
		floors[stackIndex][curFloor-1] |  // vertical transition: no matter what c is
		( floors[stackIndex][curFloor-1] >> 1 ) |  // diagonal transition: no matter what c is (note the |= and the >>1 operator!)
		( floors[stackIndex+1][curFloor-1] >> 1 );  // diagonal epsilon transition: note that a shifted version of the SAME stack's lower floor is used

	    // delete bits beyond the relevant range
	    // might be unnecessary
	    floors[stackIndex+1][curFloor] &= allBits_;

	    
	    // update couldWalk
	    couldWalk = couldWalk || floors[stackIndex+1][curFloor];
	    
	    // printFloors(stackIndex+1);

	}
	return couldWalk;
    }





    void LevNDEA::printFloor( int stackIndex, int floor ) {
	for ( size_t i = 63;i >= 63 - patLength_; --i ) {
	    printf( "%u ", ( unsigned int )( 1 & ( floors[stackIndex][floor] >> i ) ) );
	}
	printf( "\n" );

    }
    void LevNDEA::printFloors( int stackIndex ) {
	for ( int i = (int)maxFloorIndex_; i >= 0; --i ) {
	    printf( "%2d ** ", i );
	    printFloor( stackIndex, i );
	}
	printf( "       " );

	for ( size_t i = 0;pattern_[i]; ++i ) {
	    printf( "%lc ", pattern_[i] );
	}
	printf( "\n" );

    }




} // eon




#endif
