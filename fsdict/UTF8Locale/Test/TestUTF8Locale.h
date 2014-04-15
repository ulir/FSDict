#ifndef FSDICT_TESTCSLLOCALE_H
#define FSDICT_TESTCSLLOCALE_H FSDICT_TESTCSLLOCALE_H


#include <cppunit/extensions/HelperMacros.h>

#include "../UTF8Locale.h"

namespace fsdict {
    class TestUTF8Locale : public CppUnit::TestFixture  {

	CPPUNIT_TEST_SUITE( TestUTF8Locale );
	CPPUNIT_TEST( testBasics );
	CPPUNIT_TEST_SUITE_END();
    public:

	void run();

	void testBasics();
	void testSTDIO();
	

    private:
	
    };

    CPPUNIT_TEST_SUITE_REGISTRATION( TestUTF8Locale );

    void TestUTF8Locale::run() {
	testBasics();
	testSTDIO();
    }
    

    /**
     * test the basic methods
     */
    void TestUTF8Locale::testBasics() {


	CPPUNIT_ASSERT_EQUAL_MESSAGE( "Test if decimal point is dot not comma", 
				      L'.', std::use_facet< std::numpunct< wchar_t > >( UTF8Locale::Instance() ).decimal_point() );


	// read int
	CPPUNIT_ASSERT_EQUAL( UTF8Locale::string2number< int >( std::wstring( L"42" ) ), (int)42 );

	// throw exception if not complete input can be interpreted as number
	CPPUNIT_ASSERT_THROW( UTF8Locale::string2number< int >( std::wstring( L"42bla" ) ), exceptions::fsdictException );

	// read float
	CPPUNIT_ASSERT_EQUAL( UTF8Locale::string2number< float >( std::wstring( L"42.13" ) ), (float)42.13 );

	// throw exception for comma as decimal point
	CPPUNIT_ASSERT_THROW( UTF8Locale::string2number< float >( std::wstring( L"42,13" ) ), exceptions::fsdictException );

    }

    void TestUTF8Locale::testSTDIO() {
	std::wstring wideName;

	UTF8Locale::string2wstring( std::wcout.getloc().name(), wideName );
	std::wcout << "Name " << wideName << std::endl;

	std::wcout.imbue( std::locale( "de_CH.utf8" ) );

	UTF8Locale::string2wstring( std::wcout.getloc().name(), wideName );
	std::wcout << "Name " << wideName << std::endl;

	std::wcout.imbue( UTF8Locale::Instance() );

	UTF8Locale::string2wstring( std::wcout.getloc().name(), wideName );
	std::wcout << "Name " << wideName << std::endl;

	
    }

} // namespace fsdict


#endif
