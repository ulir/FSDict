add_subdirectory( Test )

add_executable( simpleFSA_compileCompoundDic exec_compileCompoundDic.cxx )
target_link_libraries( simpleFSA_compileCompoundDic csl )

add_executable( simpleFSA_lookupCompoundDic exec_lookupSimpleCompoundDic.cxx )


add_executable( simpleFSA_produceCompounds exec_produceCompounds.cxx )
add_executable( simpleFSA_trivialDecomp exec_trivialDecomp.cxx )
