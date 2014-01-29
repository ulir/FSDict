IF( CPPUNIT_FOUND )
 add_executable( testVal testVal.cxx )
 target_link_libraries( testVal  csl ${CPPUNIT_LIBRARIES} )

ENDIF( CPPUNIT_FOUND )
