
IF( CPPUNIT_FOUND )
 add_executable( testCtype_OldGerman exec_testCtype_OldGerman.cxx )
 target_link_libraries( testCtype_OldGerman  csl ${CPPUNIT_LIBRARIES} )

 ADD_TEST( testCtype_OldGerman ${EXECUTABLE_OUTPUT_PATH}/testCtype_OldGerman )

ENDIF( CPPUNIT_FOUND )
