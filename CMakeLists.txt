project(fsdict)

cmake_minimum_required(VERSION 2.6)

ADD_CUSTOM_TARGET(MinDic DEPENDS fsdict compileMD lookupMD extractMD   )
ADD_CUSTOM_TARGET(FBDic DEPENDS fsdict compileFBDic lookupFBDic extractFBDic   )
#ADD_CUSTOM_TARGET(DictSearch DEPENDS fsdict MinDic FBDic)

ADD_CUSTOM_TARGET(Vaam DEPENDS fsdict MinDic FBDic )

# use, i.e. don't skip the full RPATH for the build tree
SET(CMAKE_SKIP_BUILD_RPATH  FALSE)
# when building, don't use the install RPATH already
# (but later on when installing)
SET(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE)
# the RPATH to be used when installing
SET(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")

if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-long-long -pedantic")
endif()

#SET(CMAKE_VERBOSE_MAKEFILE true)

SET( COMPILE_DEFINITIONS ${COMPILE_DEFINITIONS} FSDICT_ROOTDIR='"${fsdict_SOURCE_DIR}/"' )

ENABLE_TESTING()


include_directories (${fsdict_SOURCE_DIR})

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules/")
FIND_PACKAGE( CPPUNIT )

IF( CPPUNIT_FOUND )
 include_directories( ${CPPUNIT_INCLUDE_DIR} )
ENDIF( CPPUNIT_FOUND )


SET(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

add_subdirectory(fsdict)
add_subdirectory(tools)
