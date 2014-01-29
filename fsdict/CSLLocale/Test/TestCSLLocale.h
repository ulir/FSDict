#ifndef FSDICT_TESTCSLLOCALE_H
#define FSDICT_TESTCSLLOCALE_H FSDICT_TESTCSLLOCALE_H


#include <cppunit/extensions/HelperMacros.h>

#include "../CSLLocale.h"

namespace fsdict {
    class TestCSLLocale : public CppUnit::TestFixture  {

	CPPUNIT_TEST_SUITE( TestCSLLocale );
	CPPUNIT_TEST( testBasics );
	CPPUNIT_TEST_SUITE_END();
    public:

	void run();

	void testBasics();
	void testSTDIO();
	

    private:
	
    };

    CPPUNIT_TEST_SUITE_REGISTRATION( TestCSLLocale );

    void TestCSLLocale::run() {
	testBasics();
	testSTDIO();
    }
    

    /**
     * test the basic methods
     */
    void TestCSLLocale::testBasics() {


	CPPUNIT_ASSERT_EQUAL_MESSAGE( "Test if decimal point is dot not comma", 
				      L'.', std::use_facet< std::numpunct< wchar_t > >( CSLLocale::Instance() ).decimal_point() );


	// read int
	int x_int = 0;
	CPPUNIT_ASSERT_EQUAL( CSLLocale::string2number< int >( std::wstring( L"42" ) ), (int)42 );

	// throw exception if not complete input can be interpreted as number
	CPPUNIT_ASSERT_THROW( CSLLocale::string2number< int >( std::wstring( L"42bla" ) ), exceptions::fsdictException );

	// read float
	float x_float = 0;
	CPPUNIT_ASSERT_EQUAL( CSLLocale::string2number< float >( std::wstring( L"42.13" ) ), (float)42.13 );

	// throw exception for comma as decimal point
	CPPUNIT_ASSERT_THROW( CSLLocale::string2number< float >( std::wstring( L"42,13" ) ), exceptions::fsdictException );

    }

    void TestCSLLocale::testSTDIO() {
	std::wstring wideName;

	CSLLocale::string2wstring( std::wcout.getloc().name(), wideName );
	std::wcout << "Name " << wideName << std::endl;

	std::wcout.imbue( std::locale( "de_CH.utf8" ) );

	CSLLocale::string2wstring( std::wcout.getloc().name(), wideName );
	std::wcout << "Name " << wideName << std::endl;

	std::wcout.imbue( CSLLocale::Instance() );

	CSLLocale::string2wstring( std::wcout.getloc().name(), wideName );
	std::wcout << "Name " << wideName << std::endl;

	
    }

} // namespace fsdict


#endif
