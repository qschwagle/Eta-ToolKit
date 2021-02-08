set(SOURCE_FILES 
	main.cpp
)

add_executable(imageviewer2 ${SOURCE_FILES})

target_link_libraries(imageviewer2 PRIVATE ${PROJECT_NAME})

