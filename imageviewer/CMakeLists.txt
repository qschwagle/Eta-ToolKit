set(SOURCE_FILES 
	main.cpp
)

add_executable(imageviewer ${SOURCE_FILES})

target_link_libraries(imageviewer PRIVATE ${PROJECT_NAME})

