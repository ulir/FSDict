INCLUDE(CPack)

add_subdirectory(Alphabet)
add_subdirectory(UTF8Locale)
add_subdirectory(DictSearch)
add_subdirectory(FBDic)
add_subdirectory(FBDicString)
add_subdirectory(Getopt)
add_subdirectory(INIConfig)
add_subdirectory(LevDEA)
add_subdirectory(LevDistance)
add_subdirectory(Locale)
add_subdirectory(MinDic)
add_subdirectory(MinDicString)
add_subdirectory(Pattern)
add_subdirectory(Vaam)
add_subdirectory(Val)

SET(FILES_FOR_LIB   
  UTF8Locale/UTF8Locale.cxx
  Alphabet/Alphabet.cxx 
  LevDEA/LevDEA.cxx
  LevDEA/AutData.cxx
  DictSearch/DictSearch.cxx
  Pattern/Pattern.cxx
  Pattern/ComputeInstruction.cxx
  Pattern/Instruction.cxx
  Pattern/Interpretation.cxx
  Pattern/PatternWeights.cxx
  INIConfig/INIConfig.cxx INIConfig/INIParser.cxx INIConfig/dictionary.c
)

ADD_LIBRARY( csl        SHARED ${FILES_FOR_LIB} )
ADD_LIBRARY( csl_static STATIC ${FILES_FOR_LIB} )

#TARGET_LINK_LIBRARIES( csl Alphabet )
#TARGET_LINK_LIBRARIES( csl LevDEA )
#TARGET_LINK_LIBRARIES( csl DictSearch )
#TARGET_LINK_LIBRARIES( csl Pattern )
#TARGET_LINK_LIBRARIES( csl DictSearch )

install( 
  TARGETS csl csl_static
  DESTINATION lib
  )

INSTALL(DIRECTORY . 
	DESTINATION include/fsdict/
	FILES_MATCHING
 	PATTERN "*.h"
 	PATTERN "*.tcc"
 	PATTERN "*CMake*" EXCLUDE
 )

