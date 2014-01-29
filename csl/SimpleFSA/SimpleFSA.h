#ifndef CSL_SIMPLEFSA_SIMPLEFSA
#define CSL_SIMPLEFSA_SIMPLEFSA csl_SIMPLEFSA_SIMPLEFSA

#include "../Global.h"

#include<map>
#include<set>
#include<iostream>


//#define CSL_SIMPLEFSA_SLIMSTATE 1

namespace csl {
    
    namespace SimpleFSA {
	
	/**
	 * @brief @c State represents one state of a @c SimpleFSA::Automaton.
	 *
	 * This class has only a private constructor, all instances are created by its friend class,
	 * SimpleFSA::Automaton. The user only gets pointers to the states. 
	 *
	 */
	class State {
	private:
	    /**
	     * @brief Internal datatype for the representation of the @c State 's transitions
	     */
	    typedef std::map< wchar_t, State* > TransMap_t;
	    
	    
	    /**
	     * @brief initialises a state with a number that serves as a name.
	     *
	     * The constructor is private, so that users cannot create State s of their own. Instead they
	     * have to request a new state with a call to Automaton::newState() 
	     */
	    State( int number = -1 ) : 
#ifndef CSL_SIMPLEFSA_SLIMSTATE
		number_( number ),
#endif
		isFinal_( false ) {
	    }
	    
	    void setNumber( int nr ) {
#ifndef CSL_SIMPLEFSA_SLIMSTATE
		number_ = nr;
#endif
	    }
	    
	public:
	    friend class Automaton;

	    /**
	     * @brief A transition is a std::pair containing the transition's label and target state
	     */
	    typedef std::pair< wchar_t, State* > Transition_t;

	    /**
	     * @brief iterator-type for iterating through all transitions of the state.
	     *
	     * This typedef is no good solution as it does not hide the implementation of the transitions.
	     */
	    typedef TransMap_t::iterator trans_iterator;

	    /**
	     * @brief constant iterator-type for iterating through all transitions of the state.
	     */
	    typedef TransMap_t::const_iterator const_trans_iterator;


	    /**
	     * @brief return the @c state's number
	     * @return the @c state's number
	     */
	    int getNumber() const {
#ifndef CSL_SIMPLEFSA_SLIMSTATE
		return number_;
#else
		return 42;
#endif
	    }

	    /**
	     * @brief the transition function: For a label @c c, it returns a pointer to the appropriate target state,
	     * or a 0-pointer if such a transition does not exist.
	     * @return a pointer to the target state or 0 if the requested transition does not exist. 
	     */
	    State* delta( wchar_t c ) {
		TransMap_t::const_iterator it = transitions_.find( c );
		if( it != transitions_.end() ) {
		    return  it->second;
		}
		else return 0;
	    }

	    /**
	     * @brief the const-version of the delta method
	     */
	    State const* delta( wchar_t c ) const {
		TransMap_t::const_iterator it = transitions_.find( c );
		if( it != transitions_.end() ) {
		    return  it->second;
		}
		else return 0;
	    }

	    /**
	     * @brief the string version of the delta function, often referred to as 'delta*'
	     */
	    State const* delta_string( const std::wstring& str ) const {
		wchar_t const* c = str.c_str();
		State const* st = this;
		
		while( *c && st ) {
		    st = st->delta( *c );
		    ++c;
		}
		return st;
	    } 
	    
	    /**
	     * @brief returns true iff the state is marked as final.
	     * @return true iff the state is marked as final.
	     */
	    bool isFinal() const { return isFinal_; }

	    /**
	     * @brief set the state's final/not-final status
	     */
	    void setFinal( bool b )  { isFinal_ = b; }

	    /**
	     * @brief sets an outgoing transition of the state
	     * @param c label of the transition
	     * @param target target state of the transition
	     */
	    void setTransition( wchar_t c, State* target ) {
		transitions_[ c ] = target;
	    }

	    void reset() {
#ifndef CSL_SIMPLEFSA_SLIMSTATE
		number_ = -1;
#endif
		transitions_.clear();
		isFinal_ = false;
	    }

	    size_t getNrOfTransitions() const {
		return transitions_.size();
	    }

	    bool hasTransitions() const {
		return ! transitions_.empty();
	    }

	    /**
	     * @brief if the state has one or more transitions, this method returns the transition with 
	     * the alphabetically largest label. If there are no transitions, it returns an undefined value!
	     * 
	     * Before usage, use @c hasTransitions() to check if there are transitions at all!!!
	     */
	    Transition_t getLastTransition() const {
		return *( transitions_.rbegin() );
	    }

	    trans_iterator trans_begin() {
		return transitions_.begin();
	    }
	    
	    const_trans_iterator trans_begin() const {
		return transitions_.begin();
	    }
	    
	    trans_iterator trans_end() {
		return transitions_.end();
	    }
	    
	    const_trans_iterator trans_end() const {
		return transitions_.end();
	    }

	    

	private:
#ifndef CSL_SIMPLEFSA_SLIMSTATE
	    int number_;
#endif
	    std::map< wchar_t, State* > transitions_;
	    bool isFinal_;
	}; // class State







	/**
	 * @brief class @c Automaton is the main class of our "trivial" FSA implementation.
	 *
	 * It provides basic functionality for creating any kind of deterministic finite state automaton.
	 * See method documentation for details
	 *
	 * @c Automaton creates all its states on the heap (using the @c new()-operator). To the user, it gives away
	 * pointers to these states.
	 *
	 * @author Ulrich Reffle
	 */
	class Automaton {
	public:
	    /**
	     * @brief The datatype representing one state of the automaton
	     */
	    typedef State State_t;

	    /**
	     * @brief An iterator type to iterate through (the pointers to) all states of the automaton.
	     */
	    typedef std::set< State* >::iterator state_iterator;

	    /**
	     * @brief The const version of the state iterator
	     */
	    typedef std::set< State* >::const_iterator const_state_iterator;
	    
	    /**
	     * @brief A simple constructor, adding a start (or:root) state to the FSA.
	     */
	    Automaton() :
		nextFreeStateNumber_( 0 ) {

		root_ = newState(); // add root state at index 0, with number 0
	    }

	    /**
	     * @brief Deletes all states from the heap.
	     */
	    ~Automaton() {
		for( const_state_iterator st = states_begin();
		     st != states_end();
		     ++st ) {
		    delete( *st );
		}
	    }

	    /**
	     * @brief returns a pointer to the root
	     * @return a pointer to the root
	     */
	    State* getRoot() {
		return root_;
	    }

	    /**
	     * @brief returns a const pointer to the root
	     * @return a const pointer to the root
	     */
	    State const* getRoot() const {
		return root_;
	    }


	    /**
	     * @brief returns true iff @c str is recognized by the automaton
	     * @return true iff @c str is recognized by the automaton
	     */
	    bool lookup( const std::wstring& str ) const {
		State const* st = getRoot();
		st = st->delta_string( str );
		return ( st && st->isFinal() );
	    }


	    /**
	     * @brief create a new state (without any transitions) and return a pointer to it.
	     * @return a pointer to a new state.
	     */
	    State* newState() {
		State* newState = new State( nextFreeStateNumber_ );

		states_.insert( newState );

		++nextFreeStateNumber_;
		return newState;
	    }

	    /**
	     * @brief Removes a state from the automaton
	     */
	    void removeState( State* st ) {
		if( states_.erase( st ) ) {
		    // ok
		}
		else {
		    throw exceptions::LogicalError( "SimpleFSA::Automaton::removeState: State was not part of automaton" );
		}
		delete( st );
	    }
	    
	    /**
	     * @brief create a new state outside the automaton. It can be inserted later with
	     * insertTempState()
	     *
	     * For the moment the user is responsible for the destruction of the state! Only 
	     * when the user adds it to the automaton she also gives away this obligation.
	     *
	     * @return a pointer to a new state.
	     */
	    State* getTempState() {
		return new State();
	    }

	    /**
	     * @brief Insert a state into the automaton
	     */
	    void insertTempState( State* state ) {
		state->setNumber( nextFreeStateNumber_ );
		if( states_.insert( state ).second ) {
		    // insert ok
		}
		else {
		    throw exceptions::LogicalError("Tried to insert same tempState twice");
		}
		++nextFreeStateNumber_;
	    }
	    

	    /**
	     * @return a state_iterator pointing to the first state in the list
	     */
	    state_iterator states_begin() {
		return states_.begin();
	    }
	    
	    /**
	     * @return a const_state_iterator pointing to the first state in the list
	     */
	    const_state_iterator states_begin() const {
		return states_.begin();
	    }
	    
	    /**
	     * @return a state_iterator pointing to the after-the-end state in the list
	     */
	    state_iterator states_end() {
		return states_.end();
	    }
	    
	    /**
	     * @return a const_state_iterator pointing to the after-the-end state in the list
	     */
	    const_state_iterator states_end() const {
		return states_.end();
	    }

	    /**
	     * @brief returns the number of states in the automaton.
	     */
	    size_t getNumberOfStates() const {
		return states_.size();
	    }

	    /**
	     * @brief prints some plaintext statistics of the Automaton to the specified stream
	     *
	     * @param[out] a reference to an @c wostream -object, default: std::wcout
	     */
	    void analyze( std::wostream& os = std::wcout ) const {
		std::wcerr << "Compute nr of transitions ... " << std::flush;
		size_t nrOfTransitions = 0;
		for( SimpleFSA::Automaton::const_state_iterator it = states_begin(); it != states_end(); ++it ) {
		    nrOfTransitions += (*it)->getNrOfTransitions();
		}
		std::wcerr << "ok" << std::endl;
		
		os << "******* SimpleFSA Analysis **********" << std::endl;
		os << "nr of states:      " << getNumberOfStates() << std::endl;
		os << "nr of transitions: " << nrOfTransitions << std::endl;
		
	    }

	    /**
	     * @brief print a dot-representation of the FSA
	     *
	     * @param[out] a reference to an @c wostream -object, default: std::wcout
	     */
	    void toDot( std::wostream& out = std::wcout ) const {
		out << 
		    "Digraph TransTable_out { //DOTCODE" << std::endl <<
		    "rankdir=LR; //DOTCODE" << std::endl <<
		    "ordering=out; //DOTCODE" << std::endl;
		
		for( const_state_iterator state = states_begin();
		     state != states_end();
		     ++state ) {
		    
		    out <<
			(**state).getNumber() <<
			"[peripheries="<< ( ( (**state).isFinal() )? "2" : "1" ) << "]; // DOTCODE" <<
			std::endl;
		    for( State_t::const_trans_iterator trans = (**state).trans_begin();
			 trans != (**state).trans_end();
			 ++trans ) {
			out <<
			    (**state).getNumber() << "->" << trans->second->getNumber() <<
			    "[label=\""<< trans->first << "\"]; // DOTCODE" <<
			    std::endl;
		    }
		}

		out << "} // DOTCODE " << std::endl;
	    }


	private:
	    /**
	     * @brief 
	     */
	    std::set< State* > states_;
	    State* root_;

	    size_t nextFreeStateNumber_;
	};
    }
    
} // eon

namespace std {

    wostream& operator<<(wostream& out, const csl::SimpleFSA::State& s ) {
	for( csl::SimpleFSA::State::const_trans_iterator t = s.trans_begin();
	     t != s.trans_end();
	     ++t ) {
	    out<<"("<<t->first<<","<<t->second->getNumber()<<")";
	}
	return out;
    }

    wostream& operator<<(wostream& out, const csl::SimpleFSA::Automaton& a ) {
	for( csl::SimpleFSA::Automaton::const_state_iterator s = a.states_begin();
	     s != a.states_end();
	     ++s ) {
	    out<<**s<<"|";
	}
	return out;
    }
}

#endif
