add_library(JNIDictSearch SHARED 
            csl_DictSearch_DictSearch.cxx
	    )
target_link_libraries( JNIDictSearch csl )

install( 
  TARGETS JNIDictSearch
  DESTINATION lib
  )


