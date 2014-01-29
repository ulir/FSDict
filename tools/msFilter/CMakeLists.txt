
add_executable(msFilter msFilter.cxx)
target_link_libraries (msFilter csl)

install(
  TARGETS msFilter
  DESTINATION bin
)
