#ifndef FSDICT_TRIE_H
#define FSDICT_TRIE_H FSDICT_TRIE_H

#include <fstream>
#include <vector>
#include <stack>
#include <errno.h>
#include "../Global.h"
#include <fsdict/iDictionary/iDictionary.h>
#include "../codecvt/UTF8_Codecvt.h"
#include "../TransTable/TransTable.h"
#include "../Alphabet/Alphabet.h"

namespace fsdict {


    /**
     * @brief class Trie performs the construction and usage of tries 
     * for large finite dictionaries. 
     *
     * Note that a Trie inherits from TransTable and so offers all of TransTable's 
     * interface to the guts of the automaton. However this might change in the future.
     *
     * @author Ulrich Reffle, <uli@cis.uni-muenchen.de>
     * @date Apr 2006
     *
     */
    template< class AnnType = int >
    class Trie : public TransTable< TT_PERFHASH, uint16_t >,
		   public iDictionary {
    public:
	typedef TransTable< TT_PERFHASH, uint16_t > TransTable_t;

	/**
	 * @brief The datatype of the annotation that comes with each dictionary entry.
	 * Note that \c AnnType_t, currently,  has to be a trivial datatype: if you store
	 * an object x of type AnnType_t, the Trie will store exactly sizeof(AnnType_t) bytes,
	 * beginning at address &x. Heap data will be lost.
	 */
	typedef AnnType AnnType_t;

	/**
	 * This class provides a much easier interface to the Trie if the guts of the automaton
	 * have to be explored state- and transition-wise.
	 */
	class State {
	public:
	    /**
	     * @param a reference to the \c Trie the \c State belongs to.
	     */
	    State( const Trie< AnnType >& minDic ) :
		minDic_( &minDic ),
		dicPos_( minDic_->getRoot() ),
		perfHashValue_( 0 ) {
	    }
	    
	    /**
	     * 
	     */
	    bool walk( wchar_t c ) {
		dicPos_ = minDic_->walkPerfHash( dicPos_, c, &perfHashValue_ );
		return isValid();
	    }

	    bool isValid() {
		return ( dicPos_ != 0 );
	    }

	    bool hasTransition( wchar_t c ) const {
		return minDic_->walk( dicPos_, c );
	    }

	    State getTransTarget( wchar_t c ) const {
		size_t tmpPHValue = perfHashValue_;
		StateId_t newPos = minDic_->walkPerfHash( dicPos_, c, &tmpPHValue );
		return State( *minDic_, newPos, tmpPHValue );
	    }

	    const wchar_t* getSusoString() const {
		return minDic_->getSusoString( dicPos_ );
	    }

	    size_t getPerfHashValue() const {
		return perfHashValue_;
	    }

	    StateId_t getStateID() const {
		return dicPos_;
	    }

	    bool isFinal() const {
		return minDic_->isFinal( dicPos_ );
	    }
	    
	    const AnnType& getAnnotation() {
		return minDic_->getAnnotation( getPerfHashValue() );
	    }

	private:

	    State( const Trie< AnnType >& minDic, StateId_t dicPos, size_t perfHashValue ) :
		minDic_( &minDic ),
		dicPos_( dicPos ),
		perfHashValue_( perfHashValue ) {
	    }

	    const Trie< AnnType >* minDic_;
	    StateId_t dicPos_;
	    size_t perfHashValue_;
	}; // class State

	class TokenIterator {
	private:
	    typedef std::pair< State, size_t > StackItem_t;
	public:
	    /**
	     * @brief creates an iterator that equals tokensEnd()
	     *        because of its empty currentString_
	     */
	    TokenIterator() {
	    }

	    TokenIterator( State const& rootState ) {
		if( ( rootState.getSusoString())[0] == 0 ) { // no transitions from root state
		    return; // iterator now equals to tokensEnd()
		}
		stack_.push( std::make_pair( rootState, 0 ) );
		State st = rootState;
		while( st.isValid() && ! st.isFinal() ) {
		    wchar_t nextChar = (st.getSusoString())[0]; // this might be \0
		    st.walk( nextChar );
		    ++( stack_.top().second ); // we used the first transition
		    if( nextChar ) {
			stack_.push( std::make_pair( st, 0 ) );
			currentString_ += nextChar;
		    }
		}
	    }

	    bool operator==( TokenIterator const& other ) const {
		return currentString_ == other.currentString_;
	    }

	    bool operator!=( TokenIterator const& other ) const {
		return !( *this == other );
	    }

	    /**
	     * @brief returns a reference to the current token. CAUTION: This reference becomes invalid
	     *        as soon as the iterator is moved forward.
	     */
	    std::wstring const& operator*() const {
		return currentString_;
	    }

	    std::wstring const* operator->() const {
		return &currentString_;
	    }

	    TokenIterator& operator++() {
		do {
		    //std::wcout << "At: " << stack_.top().first.getStateID() << "," << stack_.top().second << std::endl;
		    wchar_t nextChar = (stack_.top().first.getSusoString())[ stack_.top().second ];
		    if( nextChar ) { // more paths to go from this state
			++( stack_.top().second );
			State st = stack_.top().first.getTransTarget( nextChar );
			stack_.push( std::make_pair( st, 0 ) );
			currentString_ += nextChar;
			// std::wcout << "forward to " << stack_.top().first.getStateID() << std::endl;
		    }
		    else {
			stack_.pop();
			if( ! stack_.empty() ) {
			    currentString_.resize( currentString_.size() - 1 );
			    // std::wcout << "back to " << stack_.top().first.getStateID() << std::endl;
			}
		    }
		} while( ! ( stack_.empty() || // quit if stack is empty or if final state is reached for the 1st time
			     ( stack_.top().first.isFinal() && stack_.top().second == 0 ) 
			     ) 
		    );
	    }

	private:
	    std::wstring currentString_;
	    /**
	     * @brief the std::pair holds (first) a state and (second) the index in this state's susoString that is due to be
	     * processed nect
	     */
	    std::stack< StackItem_t > stack_;
	};

	/**
	 * @brief Create a new Trie. An optional file-path as argument invokes a call to loadFromFile.
	 * @param a file containing a compiled Trie. (optional; often: *.mdic)
	 */
	Trie( const char* dicFile = 0 );
	
	
	/**
	 * @brief The copy constructor is NOT IMPLEMENTED at the moment
	 */
	Trie( Trie< AnnType_t > const& other );
	
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
	 * @deprecacted this method is renamed to lookup()
	 */
	inline bool getAnnotation( const wchar_t* key, AnnType_t* annotation ) const;


	inline const AnnType_t& getAnnotation( size_t perfHashValue ) const;

	/**
	 * Get a State object of the automaton's root/ start state. 
	 * @return a State object of the automaton's root/ start state. 
	 * @see State
	 */
	inline State getRootState() const {
	    return State( *this );
	}

	inline TokenIterator tokensBegin() const {
	    if( readyToRead() ) {
		return TokenIterator( getRootState() );
	    }
	    else {
		return tokensEnd();
	    }
	}

	inline TokenIterator tokensEnd() const {
	    return TokenIterator();
	}
	
	//@}


	/**
	 * @name Loading from /writing to hard disk
	 */
	//@{
	/**
	 * @brief Load a compiled Trie from hard disk.
	 * @param a file containing a compiled Trie. (often: *.mdic)
	 */
	inline void loadFromFile( const char* binFile );
	
	/**
	 * @brief Load a compiled Trie from an open file stream.
	 * @param fi a c-style file pointer.
	 */
	inline void loadFromStream( FILE* fi );
	
	/**
	 * @brief dump Trie automaton to a file in binary form.
	 * @param binFile File to write the automaton into.
	 */
	inline void writeToFile( char const* binFile ) const;

	/**
	 * @brief dump Trie automaton to an open file stream
	 * @param fo a c-style file pointer.
	 */
	inline void writeToStream( FILE* fo ) const;

	//@}
	
	/**
	 * @name Construction of a new Trie
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
	 * @brief prepares the object for construction of a new Trie.
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
	 * This method from TransTable is blocked for Trie, not implemented here!
	 */
	inline int getFirstAnn( StateId_t state );

 	//@}

    protected:
	inline const AnnType_t& annotationsAt( size_t n ) const;

    private:
	
	mutable size_t count_; // is used for counting during printing

	// Those vars are used for construction
	TempState_t *tempStates_;

	wchar_t lastKey_[Global::lengthOfLongStr];

	AnnType_t* annotations_;
	size_t sizeOfAnnotationBuffer_;

	size_t nrOfKeys_;


	void printDic_rec( StateId_t pos, int depth, size_t perfHashValue ) const;

	static const bits64 magicNumber_ = 47247821;
	class Header {
	public:
	    bits64 getMagicNumber() const {
		return magicNumber_;
	    }
	    size_t getNrOfKeys() const {
		return nrOfKeys_;
	    }

	    void set( const Trie& trie ) {
			magicNumber_ = trie.magicNumber_;
			nrOfKeys_ = trie.nrOfKeys_;
	    }
	private:
	    bits64 magicNumber_;
	    bits64 nrOfKeys_;
	};

	Header header_;

    };


} //eon

#include "./Trie.tcc"

#endif
