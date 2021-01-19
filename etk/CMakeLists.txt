set(SOURCE_FILES
	application.cpp
 "window.cpp" "RunOnUIThread.cpp")

find_package(glfw3 3.3 REQUIRED)


add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES} "widget.h")

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)

target_link_libraries(${PROJECT_NAME} PUBLIC glfw)

find_package(OpenGL REQUIRED)

target_link_libraries(${PROJECT_NAME} PRIVATE OpenGL::GL)


target_include_directories(${PROJECT_NAME} PUBLIC "${PROJECT_SOURCE_DIR}/")

find_package(GLEW REQUIRED)

target_link_libraries(${PROJECT_NAME} PRIVATE GLEW::GLEW)

find_package(glm REQUIRED)

target_link_libraries(${PROJECT_NAME} PUBLIC glm)
