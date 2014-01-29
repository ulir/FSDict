#ifndef CSL_SIMPLEFSA_MINDIC_H
#define CSL_SIMPLEFSA_MINDIC_H CSL_SIMPLEFSA_MINDIC_H

#include<iostream>
#include<fstream>
#include<set>

#include"../../Global.h"
#include "../SimpleFSA.h"

namespace csl {

    namespace SimpleFSA {
	
	/**
	 * @brief StateLess is the compare-operator that is used to manage the "StateRegister"
	 */
	class StateLess {
	public:
	    /**
	     * @brief returns true if @c a is (by definition) less than @c b
	     */
	    bool operator () ( Automaton::State_t const* a, Automaton::State_t const* b ) {
		if( ( ! a->isFinal() ) && b->isFinal() ) return true;
		if( a->isFinal() && ! b->isFinal() ) return false;

		Automaton::State_t::const_trans_iterator a_trans = a->trans_begin();
		Automaton::State_t::const_trans_iterator b_trans = b->trans_begin();

		for( ; a_trans != a->trans_end(); ++a_trans, ++b_trans ) {
		    if( b_trans == b->trans_end() ) return false;
		    else if( a_trans->first < b_trans->first ) return true;
		    else if( a_trans->first > b_trans->first ) return false;
		    else if( a_trans->second < b_trans->second ) return true;
		    else if( a_trans->second > b_trans->second ) return false;
		}
		if( b_trans != b->trans_end() ) return true;

		return false;
	    }
	};

	/**
	 * @brief class @c MinDic is for the construction and usage of minimized acyclic automata from wordlists.
	 *
	 * It pretty much follows the ideas in the paper by Daciuk, Mihov et. al.
	 * 
	 */
	class MinDic : public Automaton {
	private:
	    /**
	     * As data structure for the stateRegister of known states we use a std::set with a custom-made comparison-operator
	     */
	    typedef std::set< State_t*, StateLess > StateSet_t;

	    /**
	     * A collection of variables only needed during construction
	     */
	    struct ConstrData {
		StateSet_t stateRegister;
	    };

	public:
	    /**
	     * @brief Constructor does like nothing
	     */
	    MinDic() :
		constrData_( 0 ) {
		
	    }
	    
	    /**
	     * @brief initialises the MinDic for construction of a new dictionary
	     *
	     * Always call this method before using addToken() for the first time
	     */
	    void initConstruction() {
		constrData_ = new ConstrData();
	    }
	    
	    /**
	     * @brief read a finite set of words from @c filename and compile a MinDic containing those words.
	     *
	     * @param filename a file containing one word per line
	     */
	    void compileDic( char const* filename ) {
		std::wstring word;
		std::wifstream in( filename );
		
		initConstruction();
		
		size_t count = 0;
		while( std::getline( in, word ).good() ) {

		    // toDot(); // DEBUG
		    //std::wcerr<<"add "<< word << std::endl;
		    
		    addToken( word );

		    if( ++count % 100000 == 0 ) {
			std::wcerr<<count / 1000 << "k tokens processed" << std::endl;
		    }
		}

		finishConstruction();

		// toDot(); // DEBUG
	    }
	    
	    /**
	     * @brief Add a token to the MinDic during construction
	     *
	     *
	     */
	    void addToken( std::wstring const& word ) {
		// check if object is ready to add tokens
		if( ! constrData_ ) {
		    throw exceptions::LogicalError( "csl::SimpleFSA::MinDic: addToken() called while object is not in the construction phase" );
		}
		
		// std::wcout<<"[MinDic::addToken] "<<word << std::endl;

		// we need thet last word to check for alphabetical ordering
		static std::wstring lastWord;

		if( lastWord >= word ) {
		    throw exceptions::badInput( "csl::SimpleFSA::MinDic: Alphabetical input order violated" );
		}

		// compute common prefix and splitState
		State_t* splitState = getRoot();
		wchar_t const* w = word.c_str();
		State_t* nextState = 0;
		while( ( nextState = splitState->delta( *w ) ) ) {
		    splitState = nextState;
		    ++w;
		}

		// call replaceOrRegister on splitState's bottom-most child
		if( splitState->hasTransitions() ) {
		    State_t* childState = replaceOrRegister( splitState->getLastTransition().second );
		    // possibly redirect the transition
		    splitState->setTransition( splitState->getLastTransition().first,
					       childState );
		}

		// add suffix of current word
		State_t* st = splitState;
		for( ; *w; ++w ) {
		    State_t* newState = Automaton::newState();
		    st->setTransition( *w, newState );
		    st = newState;
		}
		st->setFinal( true );

		lastWord = word;
	    }
	    

	    /**
	     * @brief finishes the construction phase and deletes temporary data structures
	     *
	     * Always call this method before using the automaton!
	     */
	    void finishConstruction() {
		
		replaceOrRegister( getRoot() );
		delete( constrData_ );
		std::wcerr<< "FSL::SimpleFSA::MinDic::finishConstruction: autmaton has "
			  << Automaton::getNumberOfStates()
			  << " states."<<std::endl;
	    }


	private: // methods

	    /**
	     * @brief for the bottom-most path from @c state this method executes the minimzation step
	     *
	     * For each state on the bottom-most path from right to left the method checks if that 
	     * state can be found in the register. If YES, the given state is deleted, 
	     * the "old" state from the register is returned instead. If NO, the state is added to 
	     * the register and returned.
	     */
	    State_t* replaceOrRegister( State_t* state ) {
		// proceed recursively first, then process the state at hand (post order)
		if( state->hasTransitions() ) {
		    // recursive call
		    State_t* nextState = replaceOrRegister( state->getLastTransition().second );
		    // possibly redirect the transition
		    state->setTransition( state->getLastTransition().first, nextState );
		}
		
		// try to insert the state into the register
		std::pair< StateSet_t::iterator, bool > registerInsertStatus = constrData_->stateRegister.insert( state );

		// if state could be inserted, i.e. was NOT found in the set of existing states
		if( registerInsertStatus.second == true ) { 
		    return state;
		}
		// else (state could be found)
		else {
		    // delete the state and return the found state
		    Automaton::removeState( state );
		    return *( registerInsertStatus.first );
		}
	    }
	    

	private: // member variables
	    /**
	     * For construction an object with temporary data is built here
	     */
	    ConstrData* constrData_;

	};



    } // simpleFSA
} // eon

#endif
