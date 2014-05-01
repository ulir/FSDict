#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>

#include "./TestCtype_OldGerman.h"


int main() {

    fsdict::TestCtype_OldGerman tester;
    tester.testBasics();

    // Adds the test to the list of test to run
    CppUnit::TextUi::TestRunner runner;
    runner.addTest( fsdict::TestCtype_OldGerman::suite() );

//     // Change the default outputter to a compiler error format outputter
//     runner.setOutputter( new CppUnit::CompilerOutputter( &runner.result(),
// 							 std::cerr ) );

    // Run the tests.
    bool wasSucessful = runner.run();

    // Return error code 1 if the one of tests failed.
    return wasSucessful ? 0 : 1;
}
