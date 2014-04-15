
IF( CPPUNIT_FOUND )
 add_executable( testLevDEA exec_testLevDEA.cxx )
 target_link_libraries( testLevDEA  csl ${CPPUNIT_LIBRARIES} )

 ADD_TEST( testLevDEA ${EXECUTABLE_OUTPUT_PATH}/testLevDEA )

ENDIF( CPPUNIT_FOUND )
