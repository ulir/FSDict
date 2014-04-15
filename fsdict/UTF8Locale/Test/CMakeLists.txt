IF( CPPUNIT_FOUND )
 add_executable( testUTF8Locale exec_testUTF8Locale.cxx )
 target_link_libraries( testUTF8Locale  csl ${CPPUNIT_LIBRARIES} )

 ADD_TEST( testUTF8Locale ${EXECUTABLE_OUTPUT_PATH}/testUTF8Locale )

ENDIF( CPPUNIT_FOUND )
