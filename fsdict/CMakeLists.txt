INCLUDE(CPack)

add_subdirectory(Alphabet)
add_subdirectory(CSLLocale)
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

ADD_LIBRARY( csl SHARED 
  CSLLocale/CSLLocale.cxx
  Alphabet/Alphabet.cxx 
  LevDEA/LevDEA.cxx
  DictSearch/DictSearch.cxx
  Pattern/Pattern.cxx
  Pattern/ComputeInstruction.cxx
  Pattern/Instruction.cxx
  Pattern/Interpretation.cxx
  Pattern/PatternWeights.cxx
  INIConfig/INIConfig.cxx INIConfig/INIParser.cxx INIConfig/dictionary.c
  )

install( 
  TARGETS csl
  DESTINATION lib
  )

INSTALL(DIRECTORY . DESTINATION include/fsdict/
 PATTERN "*svn*" EXCLUDE
 PATTERN "*CMake*" EXCLUDE
 )

