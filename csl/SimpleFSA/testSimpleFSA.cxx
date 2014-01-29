#include<iostream>
#include<fstream>

#include "./SimpleFSA.h"

int main( int argc, char** argv ) {

    std::locale::global( std::locale( "" ) );

    typedef csl::SimpleFSA::State State_t;

    csl::SimpleFSA::Automaton fsa;

    std::wcout<<*( fsa.getRoot() )<<std::endl;
	
    std::wstring word;
    std::wifstream in( argv[1] );
  
    while( std::getline( in, word).good() ) {
	// std::wcerr<<"add "<< word << std::endl;
	wchar_t const* c = word.c_str();
	State_t* splitState = fsa.getRoot();
	
	while( splitState->delta( *c ) ) {
	    splitState = splitState->delta( *c );
	    ++c;
	}

	if( *c == 0 ) { // if the whole word was found as prefix in the trie
	    splitState->setFinal( true );
	}
	else { 
	    wchar_t const* c2 = word.c_str() + ( word.length() -1 );
	    State_t* lastState = fsa.newState();
	    lastState->setFinal( true );
	    while( ! ( c2 == c ) ) {
		State_t* newState = fsa.newState();
		newState->setTransition( *c2, lastState );
		lastState = newState;
		--c2;
	    }
	    splitState->setTransition( *c, lastState );
	}
    }

    fsa.toDot(); 
//    std::wcout<<fsa<<std::endl;

//    std::wstring bla; std::wcin>>bla;

    return 0;
}
