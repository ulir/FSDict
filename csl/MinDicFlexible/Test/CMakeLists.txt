
IF( CPPUNIT_FOUND )
  add_executable( testMinDicFlexible testMinDicFlexible.cxx )
  target_link_libraries( testMinDicFlexible  csl ${CPPUNIT_LIBRARIES} )

  ADD_TEST( testMinDicFlexible ${EXECUTABLE_OUTPUT_PATH}/testMinDicFlexible )

ENDIF( CPPUNIT_FOUND )
