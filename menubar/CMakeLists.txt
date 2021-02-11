set(SOURCE_FILES 
	main.cpp
)

add_executable(menubar ${SOURCE_FILES})

target_link_libraries(menubar PRIVATE ${PROJECT_NAME})

