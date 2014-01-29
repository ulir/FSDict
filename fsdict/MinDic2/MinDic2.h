#ifndef FSDICT_MINDIC2_H
#define FSDICT_MINDIC2_H FSDICT_MINDIC2_H

#include <fstream>
#include <vector>
#include <errno.h>
#include "../Global.h"
#include "../codecvt/UTF8_Codecvt.h"
#include "../TransTable/TransTable.h"
#include "../Alphabet/Alphabet.h"
#include "../MinDic/StateHash.h"

namespace fsdict {


    /**
     * class MinDic2 performs the construction and usage of minimal acyclic 
     * finite state automata for large finite dictionaries. 
     * It follows an algorithm described in 
     * Jan Daciuk et. al., Incremental Construction of Minimal Acyclic
     * Finite-State Automata, 2000.
     *
     * Many ideas for the implementation are adapted from a C-program written
     * by Stoyan Mihov.
     * 
     * While MinDic uses perfect hashing to store annotations with the entries, MinDic2 
     *  ... 
     *
     * Note that a MinDic2 inherits from TransTable and so offers all of TransTable's 
     * interface to the guts of the automaton. However this might change in the future.
     *
     *
     * @author Ulrich Reffle, <uli@cis.uni-muenchen.de>
     * @date Sept 2008
     *
     */
    class MinDic2 : public TransTable< TT_STANDARD, uint16_t > {
    public:
	typedef TransTable< TT_STANDARD, uint16_t > TransTable_t;

	typedef int AnnType_t;

	/**
	 * This class provides a much easier interface to the MinDic if the guts of the automaton
	 * have to be explored state- and transition-wise.
	 */
	class State {
	public:
	    /**
	     * @param a reference to the \c MinDic the \c State belongs to.
	     */
	    State( MinDic2 const& minDic ) :
		minDic_( &minDic ),
		dicPos_( minDic_->getRoot() )
		{
	    }
	    
	    /**
	     * 
	     */
	    bool walk( wchar_t c ) {
		dicPos_ = minDic_->walk( dicPos_, c );
		return isValid();
	    }

	    bool isValid() {
		return ( dicPos_ != 0 );
	    }

	    bool hasTransition( wchar_t c ) const {
			return ( minDic_->walk( dicPos_, c ) != 0 );
	    }

	    State getTransTarget( wchar_t c ) const {
		StateId_t newPos = minDic_->walk( dicPos_, c );
		return State( *minDic_, newPos );
	    }

	    const wchar_t* getSusoString() const;

	    size_t getPerfHashValue() const;

	    StateId_t getStateID() const {
		return dicPos_;
	    }

	    bool isFinal() const {
		return minDic_->isFinal( dicPos_ );
	    }
	    
	    AnnType_t getAnnotation() {
		return minDic_->getAnnotationAtState( dicPos_ );
	    }

	private:

	    State( MinDic2 const& minDic, StateId_t dicPos ) :
		minDic_( &minDic ),
		dicPos_( dicPos )
		{
		}

	    const MinDic2* minDic_;
	    StateId_t dicPos_;
	}; // class State

	/**
	 * @brief Create a new MinDic. An optional file-path as argument invokes a call to loadFromFile.
	 * @param a file containing a compiled MinDic. (optional; often: *.mdic)
	 */
	MinDic2( const char* dicFile = 0 );


	/**
	 * @name Lookup
	 */
	//@{

	/**
	 * Use this function to do a convenient lookup. If you don't need the annotation, just pass on
	 * a NULL-Pointer or omit the 2nd argument.
	 *
	 * @param[in] key a key of the dictionary
	 * @param[out] annotation a pointer where to store the found annotation. If NULL, then annotation is discarded
	 * @return true iff key was found in the dictionary
	 */
	inline bool lookup( const wchar_t* key, AnnType_t* annotation = 0 ) const;

	inline bool lookup( std::wstring const& key, AnnType_t* annotation = 0 ) const;

	inline bool hasPrefix( std::wstring const& prefix ) const;


	/**
	 * Get a State object of the automaton's root/ start state. 
	 * @return a State object of the automaton's root/ start state. 
	 * @see State
	 */
	inline State getRootState() const {
	    return State( *this );
	}

	//@}


	/**
	 * @name Loading from /writing to hard disk
	 */
	//@{
	/**
	 * @brief Load a compiled MinDic from hard disk.
	 * @param a file containing a compiled MinDic. (often: *.mdic)
	 */
	inline void loadFromFile( const char* binFile );
	
	/**
	 * @brief Load a compiled MinDic from an open file stream.
	 * @param fi a c-style file pointer.
	 */
	inline void loadFromStream( FILE* fi );
	
	/**
	 * @brief dump MinDic automaton to a file in binary form.
	 * @param binFile File to write the automaton into.
	 */
	inline void writeToFile( char const* binFile ) const;

	/**
	 * @brief dump MinDic automaton to an open file stream
	 * @param fo a c-style file pointer.
	 */
	inline void writeToStream( FILE* fo ) const;

	//@}
	
	/**
	 * @name Construction of a new MinDic
	 */
	//@{
	/**
	 * @brief The funtion that actually executes the computation of the trie.
	 * @todo Should this method be public??? Maybe not ...
	 * @param txtFile The dictionary (including annotations) in txt format
	 */
	inline void compileDic( const char* txtFile );

	/**
	 * @todo add documentation
	 */
	inline void parseAnnotation( std::wstring* str, AnnType_t* annotation ) const;

	/**
	 * @brief prepares the object for construction of a new MinDic.
	 * Call before calling addToken() for the first time. 
	 */
	inline void initConstruction();

	inline void finishConstruction();

	/**
	 * processes one input line: separates the key from the annotations (if present)
	 * and performs the insertion into the trie
	 * @arg a cstring pointing to the current line
	 */
	inline void addToken( const wchar_t* input, const AnnType_t& value );

	//@}

	/**
	 * @name Convenience, Information, Debug
	 */
	//@{

	inline void printDic() const;

	/// extracts the trie to stdout
	inline void printDic( StateId_t initState ) const;

	inline size_t getNrOfKeys() const;

	inline void doAnalysis() const;


	/**
	 * This method from TransTable is blocked for MinDic2, not implemented here!
	 */
	inline int getFirstAnn( StateId_t state );

 	//@}

    protected:
	inline const AnnType_t& annotationsAt( size_t n ) const;

    private:
	
	mutable size_t count_; // is used for counting during printing

	// Those vars are used for construction
	TempState_t *tempStates_;
	StateHash< TransTable_t >* hashtable_;

	wchar_t lastKey_[Global::lengthOfLongStr];

	size_t nrOfKeys_;

	inline StateId_t replaceOrRegister( TempState_t& state );

	void printDic_rec( StateId_t pos, int depth ) const;

	static const bits64 magicNumber_ = 562300680;
	class Header {
	public:
	    bits64 getMagicNumber() const {
		return magicNumber_;
	    }
	    size_t getNrOfKeys() const {
		return nrOfKeys_;
	    }

	    void set( MinDic2 const & minDic ) {
			magicNumber_ = minDic.magicNumber_;
			nrOfKeys_ = minDic.nrOfKeys_;
	    }
	private:
	    bits64 magicNumber_;
	    bits64 nrOfKeys_;
	};

	Header header_;

    };


} //eon

#include "./MinDic2.tcc"

#endif
