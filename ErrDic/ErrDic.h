#ifndef CSL_ERRDIC_H
#define CSL_ERRDIC_H CSL_ERRDIC_H

#include "../Global.h"
#include "../MinDic/MinDic.h"
#include "../Hash/Hash.h"
#include <sys/stat.h>

namespace csl {

    /**
     * This class provides the storage and lookup of error dictionaries.
     * Basically, it's made up of a MinDic that stores a std::pair with 
     * each entry - the values of the pair are pointing to a buffer of 
     * original word forms and to a buffer of error patterns.
     *
     * The implementations are stored in the file './ErrDic.tcc' and included
     * at the bottom of this header file. Because it's so much easier :-)
     *
     * @author Uli Reffle<uli@cis.uni-muenchen.de>
     * @date 2007
     */
    class ErrDic : public MinDic< std::pair< size_t, size_t > > {
    public:
	typedef std::pair< size_t, size_t > MdAnnType;
	typedef MinDic< MdAnnType > MinDic_t;
	/**
	 * Constructor. Doesn't do much but to set some variables to 0.
	 */
	inline ErrDic();
	/**
	 * The destructor deletes the allocated buffers.
	 */
	inline ~ErrDic();

	/**
	 * Changes the expected character that separates the key from the annotations in the txt-file
	 */
	inline void setKeyValueDelimiter( uchar c );

	/**
	 * For a lookup in the ErrDic, this is the returned object. 
	 * It becomes invalid when the respective ErrDic dies.
	 */
	class Entry {
	public:
	    Entry() :
		myErrDic_( 0 ),
		id_( 0 ) {
	    }
	    Entry( const ErrDic& myErrDic, size_t id ) :
		myErrDic_( &myErrDic ),
		id_( id ) {
		// do nothing else
	    }

	    // copy constructor
	    Entry( const Entry& other ) :
		myErrDic_( other.myErrDic_ ),
		id_( other.id_ ) {
	    }
	    Entry& operator=( const Entry& other ) {
		myErrDic_ = other.myErrDic_;
		id_ = other.id_;
		return *this;
	    }

	    const wchar_t* getOriginal() const {
		return myErrDic_->getOriginalById( id_ );
	    }
	    const wchar_t* getErrorPattern() const {
		return myErrDic_->getErrorPatternById( id_ );
	    }
	private:
	    const ErrDic* myErrDic_;
	    size_t id_;
	};

	/**
	 * The basic lookup function
	 * @param[in] a key
	 * @param[out] a pointer to an Entry-object - Here the result of the lookup is stored
	 * @return true iff key is found inte ErrDic
	 * 
	 */
	inline bool lookup( wchar_t* key, Entry* entry ) const;

	/**
	 * return the original token annotated with the entry with the given id (perfect hash value)
	 */
	inline const wchar_t* getOriginalById( size_t id ) const {
	    assert( getAnnotation( id ).first < header_.sizeOfOriginals_ );
	    return originals_ + getAnnotation( id ).first; 
	}

	/**
	 * return the error pattern annotated with the entry with the given perfect hash value
	 */
	inline const wchar_t* getErrorPatternById( size_t id ) const {
	    assert( getAnnotation( id ).second < header_.sizeOfErrorPatterns_ );
	    return errorPatterns_ + getAnnotation( id ).second; 
	}

	/**
	 * load an ErrDic from a binary file
	 */
	inline void loadFromFile( char* dicFile );
	/**
	 * load an ErrDic-object off an open stream
	 */
	inline void loadFromStream( FILE* fi );

	/**
	 * write the ErrDic in its current state to a file
	 */
	inline void writeToFile( char* dicFile ) const;

	/**
	 * write the ErrDic in its current state to an open stream
	 */
	inline void writeToStream( FILE* fo ) const;

	/**
	 * prepare the ErrDic-object for the creation of a new dictionary
	 */
	inline void initConstruction();
	/**
	 * do what is necessary to finish the construction of a new dictionary
	 */
	inline void finishConstruction();
	/**
	 * create a new dictionary from a given text file
	 */
	inline void compileDic( const char* lexFile );

	/**
	 * print all entries and annotations of the dictionary to stdout
	 */
	inline void printDic() const;

	/**
	 * print some statistics to stdout
	 */
	inline void doAnalysis() const;

    private:
	inline void printDic_rec( int pos, int depth, size_t perfHashValue ) const;


	static const bits64 magicNumber_ = 2343572;

	/**
	 * The header for ErrDic-files
	 */
	class Header {
	public:
	    Header() : sizeOfOriginals_( 0 ), sizeOfErrorPatterns_( 0 ) {}
	    static const bits64 magicNumber_ = 45893126;
	    size_t sizeOfOriginals_;
	    size_t sizeOfErrorPatterns_;
	}; // class Header

	Header header_;

	/**
	 * The buffer containing all the oroginal words
	 */
	wchar_t* originals_;

	/**
	 * The buffe containing all the error-patterns
	 */
	wchar_t* errorPatterns_;
	
	/**
	 * A hashtable for all the original words. That's how we manage to keep
	 * only one copy of each original in the buffer.
	 */
	Hash<wchar_t>* originalHash_;
	/**
	 * A hashtable for all the error patterns. That's how we manage to keep
	 * only one copy of each error pattern in the buffer.
	 */
	Hash<wchar_t>* patternHash_;

	/**
	 * The character that separates the key from the annotations in the txt-file
	 */
	uchar keyValueDelimiter_;	

	mutable size_t count_; // is used for counting during printing
    }; // class ErrDic

} // namespace csl

#include "./ErrDic.tcc"

#endif
