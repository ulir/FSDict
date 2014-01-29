# - Find CPPUNIT
# Find CPPUNIT
#  CPPUNIT_INCLUDE_DIR, where to find the headers
#  CPPUNIT_LIBRARIES, where to find the libraries
#  CPPUNIT_FOUND, If false, do not try to use CPPUNIT.


MESSAGE(STATUS "CPPUNIT_FIND_REQUIRED is: ${CPPUNIT_FIND_REQUIRED}")

FIND_PATH(CPPUNIT_INCLUDE_DIR cppunit/Test.h
 /usr/local/include
 /usr/include
 ${USER_SOFTWARE_DIRS}/include
)


MESSAGE(STATUS "CPPUNIT_INCLUDE_DIR is: ${CPPUNIT_INCLUDE_DIR}")


SET(CPPUNIT_NAMES ${CPPUNIT_NAMES} cppunit)
FIND_LIBRARY(CPPUNIT_LIBRARY
  NAMES ${CPPUNIT_NAMES}
  PATHS /usr/lib /usr/local/lib  ${USER_SOFTWARE_DIRS}/lib
  )

IF ( CPPUNIT_LIBRARY AND CPPUNIT_INCLUDE_DIR )
  SET( CPPUNIT_LIBRARIES ${CPPUNIT_LIBRARY} )
  SET( CPPUNIT_FOUND TRUE )
ENDIF ( CPPUNIT_LIBRARY AND CPPUNIT_INCLUDE_DIR )

# for unix, search and add the dl library
IF( UNIX )
 FIND_LIBRARY(CPPUNIT_LIBRARY_DL
  NAMES dl
  PATHS /usr/lib /usr/local/lib  ${USER_SOFTWARE_DIRS}/lib
  )
  IF( CPPUNIT_LIBRARY_DL)
	SET( CPPUNIT_LIBRARIES ${CPPUNIT_LIBRARIES} ${CPPUNIT_LIBRARY_DL} )
  ELSE( CPPUNIT_LIBRARY_DL)
	SET( CPPUNIT_FOUND FALSE )
  ENDIF( CPPUNIT_LIBRARY_DL)
  

ENDIF( UNIX)


MESSAGE(STATUS " CPPUNIT_LIBRARY_DL is: ${CPPUNIT_LIBRARY_DL}")
MESSAGE(STATUS " CPPUNIT_LIBRARY is: ${CPPUNIT_LIBRARY}")



IF (CPPUNIT_FOUND)
   IF (NOT CPPUNIT_FIND_QUIETLY)
      MESSAGE(STATUS "Found CPPUNIT: ${CPPUNIT_LIBRARIES}")
   ENDIF (NOT CPPUNIT_FIND_QUIETLY)
ELSE (CPPUNIT_FOUND)
  IF (CPPUNIT_FIND_REQUIRED)
    MESSAGE(FATAL_ERROR "Could not find CPPUNIT library")
  ELSIF (CPPUNIT_FIND_REQUIRED)
    MESSAGE(STATUS "Could not find CPPUNIT library (not required)")
  ENDIF (CPPUNIT_FIND_REQUIRED)
ENDIF (CPPUNIT_FOUND)

MARK_AS_ADVANCED(
  CPPUNIT_LIBRARIES
  CPPUNIT_INCLUDE_DIR
)



