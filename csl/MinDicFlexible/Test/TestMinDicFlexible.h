#ifndef CSL_TESTMINDICFLEXIBLE_H
#define CSL_TESTMINDICFLEXIBLE_H CSL_TESTMINDICFLEXIBLE_H

#include "../../Global.h"
#include "../MinDicFlexible.h"
#include <cppunit/extensions/HelperMacros.h>


namespace csl {
    class TestMinDicFlexible : public CppUnit::TestFixture  {
	
	CPPUNIT_TEST_SUITE( TestMinDicFlexible );
	CPPUNIT_TEST( testBasics );
	CPPUNIT_TEST( testLarger );
	CPPUNIT_TEST_SUITE_END();
    public:
	
	void run();
	
	void testBasics();
	void testLarger();
	
	
    private:
    };

    CPPUNIT_TEST_SUITE_REGISTRATION( TestMinDicFlexible );
    
//	std::wcout<<"KONSTRUKTOR"<<std::endl;
    
    
    void TestMinDicFlexible::run() {
	testBasics();
    }
    

    /**
     * test the basic methods for reading access like getRoot, walk, isFinal etc.
     */
    void TestMinDicFlexible::testBasics() {
	MinDicFlexible< MinDic< int > > mdic;
	mdic.addToken( L"anna" );
	mdic.addToken( L"carl" );
	mdic.addToken( L"berta" );
	mdic.deleteToken( L"berta" );
	mdic.reBuild();
	CPPUNIT_ASSERT( mdic.getMinDic().lookup( L"anna" ) );
	CPPUNIT_ASSERT( ! mdic.getMinDic().lookup( L"berta" ) );
	CPPUNIT_ASSERT( mdic.getMinDic().lookup( L"carl" ) );

	mdic.addToken( L"berta" );
	mdic.reBuild();
	CPPUNIT_ASSERT( mdic.getMinDic().lookup( L"berta" ) );
    }

    void TestMinDicFlexible::testLarger() {
	MinDicFlexible< MinDic< int > > mdic( "/mounts/Users/student/uli/implement/RESSOURCES/LEXIKA/all_d_100/all_d_100.frq.mdic" );
	CPPUNIT_ASSERT( mdic.getMinDic().lookup( L"aalen" ) );
	mdic.deleteToken( L"aalen" );
	mdic.addToken( L"reffle" );
	mdic.addToken( L"gotscharek" );
	mdic.addToken( L"ringlstetter" );
	mdic.reBuild();
	CPPUNIT_ASSERT( ! mdic.getMinDic().lookup( L"aalen" ) );
	CPPUNIT_ASSERT( mdic.getMinDic().lookup( L"gotscharek" ) );
	CPPUNIT_ASSERT( mdic.getMinDic().lookup( L"reffle" ) );
	CPPUNIT_ASSERT( mdic.getMinDic().lookup( L"ringlstetter" ) );
    }



} // namespace csl


#endif
