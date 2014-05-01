include_directories (${csl_SOURCE_DIR})
link_directories (${csl_BINARY_DIR}/csl)

add_executable(compileFBDicString compileFBDicString.cxx)
target_link_libraries (compileFBDicString csl)

install(
  TARGETS compileFBDicString
  DESTINATION bin

  )
