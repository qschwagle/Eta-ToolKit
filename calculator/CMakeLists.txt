set(SOURCE_FILES 
	main.cpp
)

add_executable(calculator ${SOURCE_FILES})

target_link_libraries(calculator PRIVATE ${PROJECT_NAME})

