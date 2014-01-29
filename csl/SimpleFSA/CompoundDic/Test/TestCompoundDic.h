

#include "../CompoundDic.h"


class TestCompoundDic {
public:
    bool testSetOfStates() {
	csl::SimpleFSA::CompoundDic::SetOfStates sos;

	csl::SimpleFSA::CompoundDic::JoinState jst1;
	csl::SimpleFSA::CompoundDic::JoinState jst2;

	/// ALL if-statements are of the form if( ! EXPECTED BEHAVIOUR )

	// 1st insert should work
	if( ! ( sos.insert( &jst1 ).second == true ) ) {
	    std::wcout<<"TEST1 FAIL"<<std::endl;
	    return false;
	}

	// repeated insert should not work
	if( ! ( sos.insert( &jst1 ).second == false ) ) {
	    std::wcout<<"TEST2 FAIL"<<std::endl;
	    return false;
	}

	// st2 is equivalkent to st1 so it should not work
	if( ! ( sos.insert( &jst2 ).second == false ) ) {
	    std::wcout<<"TEST3 FAIL"<<std::endl;
	    return false;
	}

	csl::SimpleFSA::Automaton aut;
	csl::SimpleFSA::State* st1 = aut.newState();
	csl::SimpleFSA::State* st2 = aut.newState();
	csl::SimpleFSA::CompoundDic::JoinState jst3;

	jst3.push_back( st1 );
	jst3.push_back( st2 );
	// jst3 should be inserted
	if( ! ( sos.insert( &jst3 ).second == true ) ) {
	    std::wcout<<"TEST4 FAIL"<<std::endl;
	    return false;
	}
	
	// 2nd time it should not work
	if( ! ( sos.insert( &jst3 ).second == false ) ) {
	    std::wcout<<"TEST5 FAIL"<<std::endl;
	    return false;
	}
	
	csl::SimpleFSA::CompoundDic::JoinState jst4;
	jst4.push_back( st2 );
	jst4.push_back( st1 );
	jst4.normalize();
	// jst4 is equivalent to jst3 (notwithstanding the different order of states), should not be inserted
	if( ! ( sos.insert( &jst4 ).second == false ) ) {
	    std::wcout<<"TEST6 FAIL"<<std::endl;
	    return false;
	}


	
	return true;

    }

};
