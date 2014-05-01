#ifndef FSDICT_TESTHASH_H
#define FSDICT_TESTHASH_H FSDICT_TESTHASH_H

#include "../../Global.h"
#include "../Hash.h"

#include <cppunit/extensions/HelperMacros.h>


namespace fsdict {
    class TestHash : public CppUnit::TestFixture  {

	CPPUNIT_TEST_SUITE( TestHash );
	CPPUNIT_TEST( testBasics );
	CPPUNIT_TEST_SUITE_END();
    public:
	TestHash();

	void run();

	void testBasics();


    private:
	fsdict::Hash<> hash_;

    };

    /**
     * test the basic methods for reading access like getRoot, walk, isFinal etc.
     */
    void TestHash::testBasics() {

} // namespace fsdict


#endif
