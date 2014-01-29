#ifndef FSL_SIMPLEFSA_TRIE_H
#define FSL_SIMPLEFSA_TRIE_H FSL_SIMPLEFSA_TRIE_H

#include<iostream>
#include<fstream>
#include<stack>
#include<queue>
#include "../SimpleFSA.h"

namespace csl {

    namespace SimpleFSA {

	/**
	 * @brief class @c Trie is for the construction and usage of Trie-structures.
	 *
	 * 
	 */
	class Trie : public Automaton {
	public:
	    /**
	     * @brief read a finite set of words from @c filename and compile a trie containing those words.
	     *
	     * @param filename a file containing one word per line
	     */
	    void compileTrie( char const* filename ) {
		std::wstring word;
		std::wifstream in( filename );
  
		while( std::getline( in, word ).good() ) {

		    wchar_t const* c = word.c_str();
		    State_t* splitState = getRoot();
	
		    while( splitState->delta( *c ) ) {
			splitState = splitState->delta( *c );
			++c;
		    }

		    State* last = splitState;
		    while( *c != 0 ) {
			State_t* next = newState();
			last->setTransition( *c, next );
			last = next;
			++c;
		    }
		    last->setFinal( true );
		}
		std::wcerr<< "csl::SimpleFSA::Trie::compileTrie: autmaton has "
			  << Automaton::getNumberOfStates()
			  << " states."<<std::endl;
		
	    }


// 	    void compileTrie( char const* filename ) {
// 		std::wstring word;
// 		std::wifstream in( filename );
  
// 		while( std::getline( in, word ).good() ) {
// //		toDot(); // DEBUG
// 		    // std::wcerr<<"add "<< word << std::endl;
// 		    wchar_t const* c = word.c_str();
// 		    State_t* splitState = getRoot();
	
// 		    while( splitState->delta( *c ) ) {
// 			splitState = splitState->delta( *c );
// 			++c;
// 		    }

// 		    if( *c == 0 ) { // if the whole word was found as prefix in the trie
// 			splitState->setFinal( true );
// 		    }
// 		    else { 
// 			wchar_t const* c2 = word.c_str() + ( word.length() -1 );
// 			State_t* lastState = newState();
// 			lastState->setFinal( true );
// 			while( ! ( c2 == c ) ) {
// 			    State_t* newSt = newState();
// 			    newSt->setTransition( *c2, lastState );
// 			    lastState = newSt;
// 			    --c2;
// 			}
// 			splitState->setTransition( *c, lastState );
// 		    }
// 		}
// 		std::wcerr<< "csl::SimpleFSA::Trie::compileTrie: autmaton has "
// 			  << Automaton::getNumberOfStates()
// 			  << " states."<<std::endl;

// 	    }

	    /**
	     * @brief This method demonstrates how a trie can be traversed depth-first using a stack
	     */
	    void traverse_depthFirst() const {
		std::wcout<<"Traversal depth-first (using a stack explicitly)"<<std::endl;
		std::stack< State_t const* > stack;
		stack.push( getRoot() );
	    
		while( ! stack.empty() ) {
		    // take the first state from the stack
		    State_t const* cur  = stack.top();
		    stack.pop();

		    std::wcout << cur->getNumber() << std::endl;
		    // for all its transitions, push the target states on the stack
		    for( State_t::const_trans_iterator trans = cur->trans_begin();
			 trans !=  cur->trans_end();
			 ++trans ) {
			stack.push( trans->second );
		    }
		}
	    }
	
	    /**
	     * @brief This method demonstrates how a trie can be traversed depth-first using
	     * recursive function calls.
	     */
	    void traverse_depthFirst_recursive( State_t const* cur = 0 ) const {
		// this applies only for the initial call
		if( ! cur ) {
		    std::wcout<<"Traversal depth-first (recursive)"<<std::endl;
		    cur = getRoot();
		}
	    
		std::wcout << cur->getNumber() << std::endl;
		for( State_t::const_trans_iterator trans = cur->trans_begin();
		     trans !=  cur->trans_end();
		     ++trans ) {
		    traverse_depthFirst_recursive( trans->second );
		}
	    }


	    /**
	     * @brief This method demonstrates how a trie can be traversed breadth-first using a queue
	     */
	    void traverse_breadthFirst() const {
		std::wcout<<"Traversal breadth-first"<<std::endl;
		std::queue< State_t const* > queue;
		queue.push( getRoot() );
	    
		while( ! queue.empty() ) {
		    // take the first state from the stack
		    State_t const* cur  = queue.front(); 
		    queue.pop();

		    std::wcout << cur->getNumber() << std::endl;
		    // for all its transitions, push the target states on the stack
		    for( State_t::const_trans_iterator trans = cur->trans_begin();
			 trans !=  cur->trans_end();
			 ++trans ) {
			queue.push( trans->second );
		    }
		}
	    }


	    /**
	     * @brief Triggers a recursive traversal to print dot-code for the trie
	     */
	    void traverse_toDot() const {
		std::wcout << 
		    "Digraph TransTable_out { //DOTCODE" << std::endl <<
		    "rankdir=LR; //DOTCODE" << std::endl <<
		    "ordering=out; //DOTCODE" << std::endl;
		traverse_toDot( getRoot() );
		std::wcout << "} //DOTCODE" << std::endl;
	    
	    }
	
	    /**
	     * @brief recursive method to print dot-code during a depth-first traversal
	     */
	    void traverse_toDot( State_t const* cur ) const {

		size_t peripheries = ( cur->isFinal() )? 2 : 1;
		std::wcout << cur->getNumber()
			   << "[peripheries="<<peripheries<<"]"
			   << "; //DOTCODE" << std::endl;

		for( State_t::const_trans_iterator trans = cur->trans_begin();
		     trans !=  cur->trans_end();
		     ++trans ) {
		    std::wcout << cur->getNumber()
			       << "->"
			       << trans->second->getNumber()
			       << "[label=\"" << trans->first << "\"]"
			       << "; //DOTCODE" << std::endl;
		    traverse_toDot( trans->second );
		}
	    }

	private:

	};


    } // eon SimpleFSA
} // eon

#endif
