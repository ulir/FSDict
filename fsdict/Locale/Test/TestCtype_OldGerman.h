#ifndef FSDICT_TESTCTYPE_OLDGERMAN_H
#define FSDICT_TESTCTYPE_OLDGERMAN_H FSDICT_TESTCTYPE_OLDGERMAN_H

#include "../../Global.h"
#include "../Ctype_OldGerman.h"

#include <cppunit/extensions/HelperMacros.h>


namespace fsdict {
    class TestCtype_OldGerman : public CppUnit::TestFixture  {

	CPPUNIT_TEST_SUITE( TestCtype_OldGerman );
	CPPUNIT_TEST( testBasics );
	CPPUNIT_TEST_SUITE_END();
    public:
	TestCtype_OldGerman();

	void run();

	void testBasics();


    private:
    };

    CPPUNIT_TEST_SUITE_REGISTRATION( TestCtype_OldGerman );

    TestCtype_OldGerman::TestCtype_OldGerman() {
    }

    void TestCtype_OldGerman::run() {
	testBasics();
    }
    

    /**
     * test the basic methods
     */
    void TestCtype_OldGerman::testBasics() {
	std::locale baseLoc = std::locale( "" );
	std::locale loc( baseLoc, new Ctype_OldGerman( baseLoc ) );
	
	// ä=0xE4, Ä=0xC4
	CPPUNIT_ASSERT( std::isupper( L'A', loc ) );
	CPPUNIT_ASSERT( std::islower( L'a', loc ) );
	CPPUNIT_ASSERT( std::toupper( L'a', loc ) == L'A' ); 
	CPPUNIT_ASSERT( std::tolower( L'A', loc ) == L'a' ); 
	
	// ä=0xE4, Ä=0xC4
	CPPUNIT_ASSERT( std::isupper( (wchar_t)0xC4, loc ) );
	CPPUNIT_ASSERT( std::islower( (wchar_t)0xE4, loc ) );
	CPPUNIT_ASSERT( std::toupper( (wchar_t)0xE4, loc ) == (wchar_t)0xC4 ); 
	CPPUNIT_ASSERT( std::toupper( (wchar_t)0xC4, loc ) == (wchar_t)0xC4 ); 
	CPPUNIT_ASSERT( std::tolower( (wchar_t)0xC4, loc ) == (wchar_t)0xE4 ); 
	CPPUNIT_ASSERT( std::tolower( (wchar_t)0xE4, loc ) == (wchar_t)0xE4 ); 

	// ö=0xF6, Ö=0xD6
	CPPUNIT_ASSERT( std::isupper( (wchar_t)0xD6, loc ) );
	CPPUNIT_ASSERT( std::islower( (wchar_t)0xF6, loc ) );
	CPPUNIT_ASSERT( std::toupper( (wchar_t)0xF6, loc ) == (wchar_t)0xD6 ); 
	CPPUNIT_ASSERT( std::toupper( (wchar_t)0xD6, loc ) == (wchar_t)0xD6 ); 
	CPPUNIT_ASSERT( std::tolower( (wchar_t)0xD6, loc ) == (wchar_t)0xF6 ); 
	CPPUNIT_ASSERT( std::tolower( (wchar_t)0xF6, loc ) == (wchar_t)0xF6 ); 

	// ü=0xFC, Ü=0xDC
	CPPUNIT_ASSERT( std::isupper( (wchar_t)0xDC, loc ) );
	CPPUNIT_ASSERT( std::islower( (wchar_t)0xFC, loc ) );
	CPPUNIT_ASSERT( std::toupper( (wchar_t)0xFC, loc ) == (wchar_t)0xDC ); 
	CPPUNIT_ASSERT( std::toupper( (wchar_t)0xDC, loc ) == (wchar_t)0xDC ); 
	CPPUNIT_ASSERT( std::tolower( (wchar_t)0xDC, loc ) == (wchar_t)0xFC ); 
	CPPUNIT_ASSERT( std::tolower( (wchar_t)0xFC, loc ) == (wchar_t)0xFC ); 

	// ß=0xDF : leave it the way it is!
	CPPUNIT_ASSERT( std::islower( (wchar_t)0xDF, loc ) );
	CPPUNIT_ASSERT( std::toupper( (wchar_t)0xDF, loc ) == (wchar_t)0xDF ); 
	CPPUNIT_ASSERT( std::tolower( (wchar_t)0xDF, loc ) == (wchar_t)0xDF ); 

	

    }
}
#endif
