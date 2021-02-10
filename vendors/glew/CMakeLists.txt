if(NOT glew_POPULATED)
	FETCHCONTENT_POPULATE(glew)

	add_subdirectory(${glew_SOURCE_DIR} ${glew_BINARY_DIR})
endif()
