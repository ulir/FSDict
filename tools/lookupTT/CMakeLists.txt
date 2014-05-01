include_directories (${csl_SOURCE_DIR})
link_directories (${csl_BINARY_DIR}/csl)

add_executable(lookupTT lookupTT.cxx)
target_link_libraries (lookupTT csl)

install(
  TARGETS lookupTT
  DESTINATION bin
  )
