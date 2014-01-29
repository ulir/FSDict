IF( CPPUNIT_FOUND )
 add_executable( testVaam exec_testVaam.cxx )
 target_link_libraries( testVaam  csl ${CPPUNIT_LIBRARIES} )


ENDIF( CPPUNIT_FOUND )
