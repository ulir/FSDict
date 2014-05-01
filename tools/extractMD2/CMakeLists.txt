include_directories (${csl_SOURCE_DIR})
link_directories (${csl_BINARY_DIR}/csl)

add_executable(extractMD2 extractMD2.cxx)
target_link_libraries (extractMD2 csl)

install(
  TARGETS extractMD2
  DESTINATION bin

  )
