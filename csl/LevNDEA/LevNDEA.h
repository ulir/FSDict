#ifndef LEVNDEA_H
#define LEVNDEA_H LEVNDEA_H

#include<iostream>
#include<vector>
#include<algorithm>
#include "../Global.h"

namespace csl {

    /**
     * LevNDEA is to represent a nondeterministic automaton computing levenshtein distances.
     *
     * The design of the automaton is the well-known one described e.g. in ???
     *
     * +---+---+---+---+---+---+---+
     * | / | / | / | / | / | / | / |
     * +---+---+---+---+---+---+---+
     * | / | / | / | / | / | / | / |
     * +---+---+---+---+---+---+---+
     *   p   a   t   t   e   r   n
     *
     * @author Ulrich Reffle
     * @date 2006
     */
    class LevNDEA {
    private:
	// we need stacksize = word_length+1: one for reading each character, one for the start configuration
	static const int stacksize = Global::lengthOfWord+1;

	bits64 floors[stacksize][Global::lengthOfWord];

	wchar_t pattern_[Global::lengthOfWord];
	size_t patLength_;

	wchar_t allChars[Global::lengthOfWord]; ///< holds all characters appearing in the pattern
  
	std::vector< unsigned long long > charvecs_;
	
	size_t maxFloorIndex_;

	static const bits64 firstBit_ = 1ll << 63; // that's a '1' followed by 63 '0's
	bits64 lastBit_; // the lowest needed bit
	bits64 allBits_; // all needed bits



	////////PRIVATE METHODS


	void cleanCharvecs();
	void calcCharvec();
    

    public:
	LevNDEA();
	~LevNDEA();

#include "SuggestIter.h"  

	void loadPattern( const wchar_t* p, size_t maxDist = (size_t)-1 );
	bool walk( wchar_t c, size_t stackIndex );

	inline int isFinal(int stackIndex) const {
	    size_t curFloor = 0;
	    while( ( curFloor <= maxFloorIndex_ ) && !( floors[stackIndex][curFloor] & lastBit_ ) ) {
		++curFloor;
	    }
	    return (curFloor <= maxFloorIndex_)? curFloor : -1;
	}

	inline void setMaxDist( size_t d ) {
	    maxFloorIndex_ = d;
	}
	
	inline size_t getMaxDist() const {
	    return maxFloorIndex_;
	}

	inline const bits64& getFloor( int stackIndex, int floor ) const {
	    return floors[stackIndex][floor];
	}

	/**
	 * returns a c-string of all chars appearing in the pattern in alphabetical order
	 */
	inline const wchar_t* getAllChars() const {
	    return allChars;
	}
	
	inline const bits64& charvec( wchar_t c ) const {
	    return charvecs_[c];
	}

	void printFloor(int stackIndex, int floor);
	void printFloors(int stackIndex);
    };



} //eon
#endif
