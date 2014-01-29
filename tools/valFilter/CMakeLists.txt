add_executable(valFilter valFilter.cxx)
target_link_libraries (valFilter csl)

add_executable(valEvaluation valEvaluation.cxx)
target_link_libraries (valEvaluation csl)

install( 
  TARGETS valFilter
  DESTINATION bin
  
  )
