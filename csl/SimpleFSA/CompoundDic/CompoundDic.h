#ifndef CSL_COMPOUNDFSA_COMPOUNDFSA
#define CSL_COMPOUNDFSA_COMPOUNDFSA CSL_COMPOUNDFSA_COMPOUNDFSA

#include "../../Global.h"
#include "../MinDic/MinDic.h"

#include<errno.h>
#include<functional>
#include<algorithm>
#include<vector>
#include<set>
#include<map>
#include<stack>
#include<iostream>
#include<fstream>

#define FSL_COMPOUNDFSA_SLIMSTATE 1


namespace csl {
    
    namespace SimpleFSA {

	class CompoundDic {
	public:
#include "./SetOfStates.h"
	    CompoundDic();
	    void compute( char const* file );

	    Automaton const& getDic() const {
		return compoundDic_;
	    }


	private:
	    void computeMinDic( char const* file );
	    
	    MinDic minDic_;
	    Automaton compoundDic_;

	    SetOfStates* setOfStates_;
	    
	}; // class CompoundDic

	CompoundDic::CompoundDic() :
	    setOfStates_( 0 ) {
	}



	void CompoundDic::compute( char const* file ) {
	    std::wcerr << "CompoundDic: Compute SimpleFSA::MinDic from textfile" << std::endl;
	    computeMinDic( file );


	    std::wcerr << "CompoundDic: Compute SimpleFSA version of Compound Dic" << std::endl;

	    std::stack< JoinState* > stack;
	    JoinState* root = new JoinState( compoundDic_.getRoot() );
	    root->push_back( minDic_.getRoot() );
	    setOfStates_ = new SetOfStates();

	    // add root state to the set of JoinStates
	    setOfStates_->insert( root ); 
	    // add root state to the stack
	    stack.push( root ); 

	    while( ! stack.empty() ) {
		JoinState& cur = *( stack.top() ); 
		// cur.print();std::wcout<< std::endl;

		stack.pop();

		std::map< wchar_t, JoinState* > targets;
		
		// collect all target-JoinStates
		for( JoinState::const_iterator state = cur.begin(); state != cur.end(); ++state ) {
		    for( State::const_trans_iterator trans = (*state)->trans_begin(); trans != (*state)->trans_end(); ++trans ) {
			
			if( trans->first ==  L'#' ) {
			    cur.isFuge_ = true;
			}
			else if( trans->first ==  L'$' ) {
			    cur.isFinal_ = true;
			}
			else {
			    std::map< wchar_t, JoinState* >::iterator jointTrans = targets.find( trans->first );
			    if( jointTrans == targets.end() ) {
				targets[trans->first] = new JoinState();
			    }
			    targets[trans->first]->push_back( trans->second );
			}
		    }
		}
		
		for( std::map< wchar_t, JoinState* >::iterator transition = targets.begin(); transition != targets.end(); ++transition ) {
		    if( transition->second->isFuge_ ) {
			transition->second->push_back( minDic_.getRoot() );
		    }
		    transition->second->normalize();

		    // std::wcout<<"Look for: "; transition->second->print(); std::wcout<<std::endl; // DEBUG
		    // setOfStates_->print(); // DEBUG
		    
		    std::pair< SetOfStates::iterator, bool > insertResult = setOfStates_->insert( transition->second );
		    if( insertResult.second == true ) { // element was NOT FOUND in the set

			if( setOfStates_->size() % 50000 == 0 ) std::wcerr<<setOfStates_->size() / 1000 << "k states" << std::endl;

			// std::wcout<<"Not found: "; transition->second->print(); std::wcout<< std::endl;
			transition->second->state_ = compoundDic_.newState();
			transition->second->state_->setFinal( transition->second->isFinal_ );

			stack.push( transition->second );
		    }
		    else {
			// std::wcout<<"Found for "; transition->second->print(); std::wcout<<" --> "; (*(insertResult.first))->print() ;std::wcout<<std::endl; // DEBUG
		    }

		    cur.state_->setTransition( transition->first, (*(insertResult.first))->state_ );

		    cur.state_->getNumber();
		    (*(insertResult.first))->state_->getNumber();

		    // std::wcout<<"Add transition: "<<cur.state_->getNumber() << "->" <<(*(insertResult.first))->state_->getNumber() << " - ";cur.print(); std::wcout<< "->" ; (*(insertResult.first))->print(); std::wcout << std::endl;

		}
	    }

	    // compoundDic_.toDot();
	    delete( setOfStates_ );
	    std::wcerr<<"CompoundDic: Automaton has " << getDic().getNumberOfStates() << " states." << std::endl;

	}

	void CompoundDic::computeMinDic( char const* file ) {
	    std::wifstream fi( file );
	    if( ! fi.good() ) {
		throw exceptions::badFileHandle( "csl::SimpleFSA::CompoundDic: File Open Error" );
	    }
	    fi.imbue( std::locale( "de_DE.utf-8" ) );
	    minDic_.initConstruction();
	    std::wstring line;
	    size_t count = 0;
	    while( getline( fi, line).good() ) {
		if( ++count % 200000 == 0 ) std::wcerr<< count / 1000 << "k tokens processed."<<std::endl;
		if( *( line.end() - 2 ) == L'1' ) {
		    minDic_.addToken( line.substr( 0, line.size() - 3 ) + L'#' );
		}
		if( *( line.end() - 1 ) == L'1' ) {
		    minDic_.addToken( line.substr( 0, line.size() - 3 ) + L'$' );
		}
	    }
	    if( errno == EILSEQ ) {
		throw exceptions::badInput( "CompoundDic: Encoding error" );
	    }

	    minDic_.finishConstruction();
	    // minDic_.toDot();
	    minDic_.analyze( std::wcerr );

	}

    }
}



#endif
