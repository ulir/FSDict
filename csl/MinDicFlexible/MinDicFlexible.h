#ifndef CSL_MINDIC_FLEXIBLE_H
#define CSL_MINDIC_FLEXIBLE_H CSL_MINDIC_FLEXIBLE_H

#include<vector>
#include<csl/MinDic/MinDic.h>
#include<csl/Stopwatch.h>

namespace csl {

    /**
     * @brief csl::MinDicFlexible is a wrapper for csl::MinDic dictionary automata which allows
     *        much more flexible insertion and deletion of new entries at runtime
     *
     * 
     *
     * @author Ulrich Reffle, 2008
     */
    template< typename MinDicType = MinDic< int > >
    class MinDicFlexible  {
    public:
	typedef MinDicType MinDic_t;

	MinDicFlexible( char const* dicFile = 0 ) :
	    minDic_( 0 )    {
	    minDic_ = new MinDic_t( dicFile );
	    if( dicFile ) dicFile_ = dicFile;
	}

	~MinDicFlexible() {
	    if( minDic_ ) delete( minDic_ );
	}

	/**
	 * @returns 
	 */
	MinDic_t const& getMinDic() const {
	    return *minDic_;
	}

	void addToken( std::wstring const& word ) {
	    toAdd_.push_back( word );
	}

	void deleteToken( std::wstring const& word ) {
	    toDelete_.push_back( word );
	}

	void reBuild() {
	    Stopwatch stopwatch;
	    stopwatch.start();
	    std::sort( toAdd_.begin(), toAdd_.end() );
	    std::sort( toDelete_.begin(), toDelete_.end() );

	    MinDic_t* newDic_ = new MinDic_t();
	    newDic_->initConstruction();

	    typename MinDic_t::TokenIterator dicToken = minDic_->tokensBegin();
	    std::vector< std::wstring >::const_iterator tokenToAdd = toAdd_.begin();
	    std::vector< std::wstring >::const_iterator tokenToDelete = toDelete_.begin();
	    std::wstring insert;

	    while( ( dicToken != minDic_->tokensEnd() ) || ( tokenToAdd != toAdd_.end() ) ) {
		if( dicToken != minDic_->tokensEnd() ) { // more dicTokens
		    if( tokenToAdd != toAdd_.end() ) { // more tokenToAdd
			if( dicToken->compare( *tokenToAdd ) < 0 ) { // tokenToAdd is alph. larger than dicToken
			    insert = *dicToken;
			    ++dicToken;
			}
			else if( dicToken->compare( *tokenToAdd ) == 0 ) { // tokenToAdd equals dicToken
			    insert = *tokenToAdd;
			    ++tokenToAdd;
			    ++dicToken;
			}
			else { // tokenToAdd is alph. smaller than dicToken
			    insert = *tokenToAdd;
			    ++tokenToAdd;
			}
		    }
		    else { // no more tokenToAdd. There must be some more dicTokens
			insert = *dicToken;
			++dicToken;
		    }
		}
		else { // no more dicTokens. There must be some more tokenToAdd
		    insert = *tokenToAdd;
		    ++tokenToAdd;
		}
		
		if( tokenToDelete == toDelete_.end() ) { // no more tokenToDelete
		    newDic_->addToken( insert.c_str(), 42 );
		}
		else {
		    int cmp = insert.compare( *tokenToDelete );
		    if(  cmp == 0 ) {
			// string is on the delete-list, do not addToken!
			++tokenToDelete;
		    }
		    else if( cmp < 0 ) {
			// next string on delete list is alph. larger, do addToken:
			newDic_->addToken( insert.c_str(), 42 );
		    }
		    else if( cmp > 0 ) {
			// obviously someone tried to delete a token that wasn't there...
			// addToken, and move on in the delete-list
			newDic_->addToken( insert.c_str(), 42 );
			++tokenToDelete;
		    }
		}
	    }
	    newDic_->finishConstruction();
	    if( minDic_ ) delete( minDic_ );
	    minDic_ = newDic_;
	    std::wcerr << "csl::MinDicFlexible: rebuild in " << stopwatch.readMilliseconds() << " milliseconds. New size of MinDic: " << minDic_->getNrOfKeys() << std::endl;
	}
	

    private:
	MinDic_t* minDic_;
	std::string dicFile_;
	std::vector< std::wstring > toAdd_;
	std::vector< std::wstring > toDelete_;

    }; // class MinDicFlexible

} // namespace csl


#endif
