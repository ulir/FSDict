IF( CPPUNIT_FOUND )
add_executable( testDictSearch exec_testDictSearch.cxx )
target_link_libraries( testDictSearch ${CPPUNIT_LIBRARIES} csl )
ADD_TEST( testDictSearch ${EXECUTABLE_OUTPUT_PATH}/testDictSearch )

ENDIF( CPPUNIT_FOUND )
