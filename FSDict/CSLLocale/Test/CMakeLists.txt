IF( CPPUNIT_FOUND )
 add_executable( testCSLLocale exec_testCSLLocale.cxx )
 target_link_libraries( testCSLLocale  csl ${CPPUNIT_LIBRARIES} )

 ADD_TEST( testCSLLocale ${EXECUTABLE_OUTPUT_PATH}/testCSLLocale )

ENDIF( CPPUNIT_FOUND )
