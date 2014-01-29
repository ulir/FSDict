#ifndef FSDICT_TESTMINDIC_H
#define FSDICT_TESTMINDIC_H FSDICT_TESTMINDIC_H

#include "../../Global.h"
#include "../FBDicString.h"

#include <cppunit/extensions/HelperMacros.h>


namespace fsdict {
    class TestFBDicString : public CppUnit::TestFixture  {

	CPPUNIT_TEST_SUITE( TestFBDicString );
	CPPUNIT_TEST( testBasics );
	CPPUNIT_TEST_SUITE_END();
    public:
	TestFBDicString();

	void run();

	void testBasics();


    };

    CPPUNIT_TEST_SUITE_REGISTRATION( TestFBDicString );

    TestFBDicString::TestFBDicString() {
    }

    void TestFBDicString::run() {
	testBasics();
    }
    

    void TestFBDicString::testBasics() {
	fsdict::FBDicString dic;
	dic.compileDic( "../fsdict/FBDicString/Test/test.lex" ); 

    }

} // namespace fsdict


#endif
