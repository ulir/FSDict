#ifndef FSDICT_TESTLEVDEA_H
#define FSDICT_TESTLEVDEA_H FSDICT_TESTLEVDEA_H

#include<stdlib.h>
#include<sstream>
#include "../../Global.h"
#include<fsdict/LevDEA/LevDEA.h>
#include<fsdict/UTF8Locale/UTF8Locale.h>

#include <cppunit/extensions/HelperMacros.h>

namespace fsdict {
    class TestLevDEA : public CppUnit::TestFixture  {

	CPPUNIT_TEST_SUITE( TestLevDEA );
	CPPUNIT_TEST( testBasics );
	CPPUNIT_TEST( testSuffixMatch );
	CPPUNIT_TEST_SUITE_END();
    public:
	TestLevDEA();

	void run();

	/**
	 * @brief Utility function to conveniently test if a given input string leads to a valid/final state in the LevDEA.
	 */
	inline void testWithInputString( std::string const msg, std::wstring const& str, bool valid, bool final=false, int distance=-1);

	inline void testBasics();
	inline void testSuffixMatch();

    private:
	LevDEA levDEA_;
    };

    CPPUNIT_TEST_SUITE_REGISTRATION( TestLevDEA );

    TestLevDEA::TestLevDEA() : levDEA_() {
    }

    template<typename T>
    std::string toString(const T& value) {
	std::ostringstream oss;
	oss << value;
	return oss.str();
    }

    void TestLevDEA::run() {
	testBasics();
    }

    void TestLevDEA::testWithInputString( std::string msg, std::wstring const& str, bool valid, bool final, int distance ) {
	std::string narrowStr = UTF8Locale::wstring2string( str );
	std::string narrowPattern = UTF8Locale::wstring2string( levDEA_.getPattern() );

	std::string msgBase;
	msgBase += std::string( "pattern=" ) + narrowPattern + ", threshold=" + toString( levDEA_.getThreshold() ) + ", input=" + narrowStr + ". " + msg + " - ";

	LevDEA::Pos p = levDEA_.walkStr( levDEA_.getRoot(), str );
	if( valid ) {
	    CPPUNIT_ASSERT_MESSAGE( msgBase + "Should lead to valid state.",  p.isValid() );
	    if( final ) {
		CPPUNIT_ASSERT_MESSAGE( msgBase + "Should lead to final state.",  levDEA_.isFinal( p ) );
		CPPUNIT_ASSERT_EQUAL_MESSAGE( msgBase + "Should return given lev distance.", distance, levDEA_.getDistance( p ) );
	    }
	}
	else { // if ! valid
	    CPPUNIT_ASSERT_MESSAGE( msgBase + "Should lead to fail state.",  ! p.isValid() );
	}
    }

    void TestLevDEA::testBasics() {


	levDEA_.loadPattern( L"1aabbccdd2" );


	// Test success cases with 1 edit operation. Those should succeed also fo thesholds >1, so we test those as well.
	for( size_t threshold = 1; threshold <=2; ++threshold ) {
	    levDEA_.setThreshold( threshold );
	    testWithInputString( "Match, distance 0.", L"1aabbccdd2", true, true, 0 );

	    testWithInputString( "One simple substitution.", L"1aabxccdd2", true, true, 1 );
	    testWithInputString( "One substitution at first char.", L"xaabbccdd2", true, true, 1 );
	    testWithInputString( "One substitution at last char.", L"1aabbccddx", true, true, 1 );
	    testWithInputString( "One substitution.", L"1aaabccdd2", true, true, 1 );

	    testWithInputString( "One insertion.", L"1aabxbccdd2", true, true, 1 );
	    testWithInputString( "One insertion at first char.", L"x1aabbccdd2", true, true, 1 );
	    testWithInputString( "One insertion at last char", L"1aabbccdd2x", true, true, 1 );
	    testWithInputString( "One insertion", L"1aaabbccdd2", true, true, 1 );

	    testWithInputString( "One deletion.", L"1aabbccd2", true, true, 1 );
	    testWithInputString( "One deletion at first char.", L"aabbccdd2", true, true, 1 );
	    testWithInputString( "One deletion at last char.", L"1aabbccdd", true, true, 1 );

	    testWithInputString( "One transposition.", L"1ababccdd2", true, true, 1 );
	    testWithInputString( "One transposition at beginning.", L"a1abbccdd2", true, true, 1 );
	    testWithInputString( "One transposition at end.", L"1aabbccd2d", true, true, 1 );

	    testWithInputString( "Prefix of pattern. Should be valid, but not final.", L"aabbc", true, false );
	}


	// Test short strings
	levDEA_.setThreshold( 1 );
	levDEA_.loadPattern( L"a" );
	testWithInputString( "Match.", L"a", true, true, 0 );
	testWithInputString( "Substitution.", L"x", true, true, 1 );
	testWithInputString( "Insert at the beginning.", L"xa", true, true, 1 );
	testWithInputString( "Insert at the end.", L"ax", true, true, 1 );

	levDEA_.loadPattern( L"ab" );
	testWithInputString( "Match.", L"ab", true, true, 0 );

	levDEA_.setThreshold( 2 );
	levDEA_.loadPattern( L"1aabbccdd2" );
	testWithInputString( "2 substitutions.", L"1aaabcxdd2", true, true, 2 );
	testWithInputString( "2 substitutions at the end.", L"1aabbccdbb", true, true, 2 );

	testWithInputString( "2 insertions at the end.", L"1aabbccdd2xx", true, true, 2 );

	testWithInputString( "3 insertions at the end. Should fail.", L"1aabbccdd2xxx", false );
	testWithInputString( "3 deletions at the end. Should be valid, but not final.", L"1aabbcc", true, false );

	testWithInputString( "sub + trans", L"1xabcbcdd2", true, true, 2 );
	testWithInputString( "sub + trans 2", L"1aabbccx2d", true, true, 2 );

	// Some cases that occurred during debugging
	levDEA_.setThreshold( 1 );
	levDEA_.loadPattern(L"iphone");
	testWithInputString( "Should be valid, not final.", L"ipgh", true, false );

    }

    void TestLevDEA::testSuffixMatch() {

	levDEA_.loadPattern( L"abcdef" );
	levDEA_.setThreshold( 2 );
	std::vector< size_t > offsets;
	LevDEA::Pos p = levDEA_.getRoot(); // arbitrary initialization

	// Two wrong characters at the beginning: Each can be an insert or sub.
	p = levDEA_.walkStr( levDEA_.getRoot(), L"xy" );
	CPPUNIT_ASSERT( levDEA_.startSuffixMatch( p, &offsets ) );
	std::wcout << p.position()  << std::endl;
	CPPUNIT_ASSERT_EQUAL( (size_t)3, offsets.size() );
	CPPUNIT_ASSERT_EQUAL( (size_t)0, offsets.at( 0 ) );
	CPPUNIT_ASSERT_EQUAL( (size_t)1, offsets.at( 1 ) );
	CPPUNIT_ASSERT_EQUAL( (size_t)2, offsets.at( 2 ) );

	// Two wrong characters after the first char: Each can be an insert or sub.
	p = levDEA_.walkStr( levDEA_.getRoot(), L"axy" );
	offsets.clear();
	CPPUNIT_ASSERT( levDEA_.startSuffixMatch( p, &offsets ) );
	std::wcout << p.position()  << std::endl;
	CPPUNIT_ASSERT_EQUAL( (size_t)3, offsets.size() );
	CPPUNIT_ASSERT_EQUAL( (size_t)1, offsets.at( 0 ) );
	CPPUNIT_ASSERT_EQUAL( (size_t)2, offsets.at( 1 ) );
	CPPUNIT_ASSERT_EQUAL( (size_t)3, offsets.at( 2 ) );

	// After "ac", it's still possible to get a transposition "acb", so we can'T start suffix matching.
	levDEA_.setThreshold( 1 );
	p = levDEA_.walkStr( levDEA_.getRoot(), L"ac" );
	offsets.clear();
	CPPUNIT_ASSERT_MESSAGE( "startSuffixMatch returns false", ! levDEA_.startSuffixMatch( p, &offsets ) );

	// After "acd", start suffixMatch
	levDEA_.setThreshold( 1 );
	p = levDEA_.walkStr( levDEA_.getRoot(), L"acd" );
	offsets.clear();
	CPPUNIT_ASSERT_MESSAGE( "startSuffixMatch returns true", levDEA_.startSuffixMatch( p, &offsets ) );
	std::wcout << p.position()  << std::endl;
	CPPUNIT_ASSERT_EQUAL_MESSAGE( "Get 1 offset", (size_t)1, offsets.size() );
	CPPUNIT_ASSERT_EQUAL_MESSAGE( "First and only offset is at pos 4",  (size_t)4, offsets.at( 0 ) );

	// The "iphone" example
	levDEA_.loadPattern( L"ipone" );
	levDEA_.setThreshold( 1 );

	p = levDEA_.walkStr( levDEA_.getRoot(), L"ip" );
	offsets.clear();
	CPPUNIT_ASSERT_MESSAGE( "startSuffixMatch returns false", ! levDEA_.startSuffixMatch( p, &offsets ) );

	p = levDEA_.walkStr( levDEA_.getRoot(), L"ipo" );
	offsets.clear();
	CPPUNIT_ASSERT_MESSAGE( "startSuffixMatch returns false, transposition still possible", ! levDEA_.startSuffixMatch( p, &offsets ) );

	p = levDEA_.walkStr( levDEA_.getRoot(), L"iph" );
	offsets.clear();
	CPPUNIT_ASSERT_MESSAGE( "startSuffixMatch returns true", levDEA_.startSuffixMatch( p, &offsets ) );

	CPPUNIT_ASSERT_EQUAL_MESSAGE( "Get 1 offset", (size_t)2, offsets.size() );
	CPPUNIT_ASSERT_EQUAL_MESSAGE( "First and only offset is at pos 2",  (size_t)2, offsets.at( 0 ) );
	CPPUNIT_ASSERT_EQUAL_MESSAGE( "First and only offset is at pos 3",  (size_t)3, offsets.at( 1 ) );



	levDEA_.setThreshold( 2 );
	testWithInputString( "Pattern ipone, string ihpnoe.", L"ihpnoe", true, true, 2 );

	p = levDEA_.walkStr( levDEA_.getRoot(), L"i" );
	offsets.clear();
	CPPUNIT_ASSERT_MESSAGE( "startSuffixMatch returns false", ! levDEA_.startSuffixMatch( p, &offsets ) );

	p = levDEA_.walkStr( levDEA_.getRoot(), L"ih" );
	offsets.clear();
	CPPUNIT_ASSERT_MESSAGE( "startSuffixMatch returns false", ! levDEA_.startSuffixMatch( p, &offsets ) );

	p = levDEA_.walkStr( levDEA_.getRoot(), L"ihp" );
	offsets.clear();
	CPPUNIT_ASSERT_MESSAGE( "startSuffixMatch returns false", ! levDEA_.startSuffixMatch( p, &offsets ) );

	p = levDEA_.walkStr( levDEA_.getRoot(), L"ihpn" );
	offsets.clear();
	CPPUNIT_ASSERT_MESSAGE( "startSuffixMatch returns false", ! levDEA_.startSuffixMatch( p, &offsets ) );

	p = levDEA_.walkStr( levDEA_.getRoot(), L"ihpno" );
	offsets.clear();
	CPPUNIT_ASSERT_MESSAGE( "startSuffixMatch returns true", levDEA_.startSuffixMatch( p, &offsets ) );




    }

} // namespace fsdict


#endif
