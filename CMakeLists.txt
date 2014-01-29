project(csl)

cmake_minimum_required(VERSION 2.6)



ADD_CUSTOM_TARGET(MinDic DEPENDS csl compileMD lookupMD extractMD   )
ADD_CUSTOM_TARGET(FBDic DEPENDS csl compileFBDic lookupFBDic extractFBDic   )
#ADD_CUSTOM_TARGET(DictSearch DEPENDS csl MinDic FBDic)

ADD_CUSTOM_TARGET(Vaam DEPENDS csl MinDic FBDic )



# use, i.e. don't skip the full RPATH for the build tree
SET(CMAKE_SKIP_BUILD_RPATH  FALSE)
# when building, don't use the install RPATH already
# (but later on when installing)
SET(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE) 
# the RPATH to be used when installing
SET(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")




#SET(CMAKE_VERBOSE_MAKEFILE true)

SET( COMPILE_DEFINITIONS ${COMPILE_DEFINITIONS} CSL_ROOTDIR='"${csl_SOURCE_DIR}/"' )

ENABLE_TESTING()


include_directories (${csl_SOURCE_DIR})

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules/")
FIND_PACKAGE( CPPUNIT )

IF( CPPUNIT_FOUND )
 include_directories( ${CPPUNIT_INCLUDE_DIR} )
ENDIF( CPPUNIT_FOUND )


SET(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

add_subdirectory(csl)
add_subdirectory(tools)

