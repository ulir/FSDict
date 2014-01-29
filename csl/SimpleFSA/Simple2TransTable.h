#ifndef CSL_SIMPLEFSA_SIMPLE2TRANSTABLE
#define CSL_SIMPLEFSA_SIMPLE2TRANSTABLE CSL_SIMPLEFSA_SIMPLE2TRANSTABLE

#include "./SimpleFSA.h"
#include<csl/TransTable/TransTable.h>
#include<csl/MinDic/MinDic.h>
#include<csl/MinDic2/MinDic2.h>
#include<csl/Stopwatch.h>


namespace csl {
    namespace SimpleFSA {


	/**
	 * @brief Simple2TransTable is a brute-force solution to store a SimpleFSA into a TransTable.
	 *
	 */
	class Simple2TransTable {
	private:
	    typedef uint32_t TransTableValue_t;
	public:
	    typedef TransTable< TT_PERFHASH, uint16_t, TransTableValue_t > TransTable_t;
	    typedef TransTable_t::TempState_t TempState_t ;
	    void translate( Automaton const& sfsa, TransTable_t* transTable  );

	private:
	    void translateState( State const* simpleState, TempState_t* tempState );

	    // this is an incredible waste! But the whole thing is a hack anyway ...
	    std::map< size_t, TransTableValue_t > number2Sparse_;
	    
	};


	void Simple2TransTable::translate( Automaton const& sfsa, TransTable_t* transTable ) {
	    std::wcerr << "Simple2TransTable::translate: start translation from SimpleFSA to sparse table" << std::endl;

	    transTable->initConstruction();

	    TempState_t tempState;

	    Stopwatch watch; watch.start();
	    std::wcerr <<"Insert states to TransTable ... "<<std::endl;
	    size_t count = 0;
	    for( Automaton::const_state_iterator state = sfsa.states_begin(); state != sfsa.states_end(); ++state ) {
		
		translateState( *state, &tempState );
		number2Sparse_[(*state)->getNumber()] = transTable->storeTempState( tempState );
		//std::wcout<<"number" << (*state)->getNumber() << " to sparse " << number2Sparse_[(*state)->getNumber()] << std::endl;

		// this is more than unlikely, but in this program, nothing is impossible ...
		if( (size_t)(*state)->getNumber() > std::numeric_limits< TransTableValue_t >::max() ) {
		    throw csl::exceptions::cslException( "csl::SimpleFSA::Simple2TransTable: SimpleFSA state number does not fit into TransTable value." );
		}

		if( ++count % 100000 == 0 ) std::wcerr<<count/1000<<"k states processed"<<std::endl;
	    }
	    transTable->setRoot( number2Sparse_[sfsa.getRoot()->getNumber()] );

	    TransTable_t::Cell_t* cells = transTable->getCells();
	    size_t nrOfCells = transTable->getNrOfCells();

	    watch.start();
	    std::wcerr <<"Rewrite TransTable ... "<<std::flush;
	    for( size_t i = 0; i < nrOfCells; ++i ) {
		if( cells[i].isTransition() ) {
		    cells[i].setValue( number2Sparse_[cells[i].getValue()] );
		}
	    }
	    std::wcerr <<"done. "<< watch.readSeconds() << " seconds" << std::endl;

	    transTable->finishConstruction();
	}

	void Simple2TransTable::translateState( State const* simpleState, TempState_t* tempState ) {
	    tempState->reset();

	    if( simpleState->isFinal() ) tempState->setFinal();
	    for( State::const_trans_iterator trans = simpleState->trans_begin();
		 trans != simpleState->trans_end(); 
		 ++trans ) {

		tempState->addTransition( trans->first, trans->second->getNumber(), 0 ); // 3rd arg ist the phValue ...
	    }
	}
    }
}

#endif
