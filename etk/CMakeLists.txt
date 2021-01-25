set(SOURCE_FILES
	application.cpp
	window.cpp 
	renderer/opengl/gl_factory.cpp 
	renderer/opengl/gl_filled_rectangle.cpp
	renderer/opengl/gl_character.cpp
	renderer/opengl/gl_image.cpp
	renderer/opengl/gl_text.cpp
	renderer/opengl/gl_rectangle.cpp
	renderer/opengl/gl_window_background.cpp 
	widgets/scene.cpp 
	widgets/button.cpp
	renderer/opengl/gl_shader_program.cpp
	renderer/opengl/gl_filled_rectangle_program.cpp 
	renderer/opengl/gl_drawable_context.cpp
	renderer/generic/ui_thread_scheduler.cpp 
	renderer/opengl/gl_character_program.cpp
	renderer/opengl/gl_image_program.cpp
	widgets/image.cpp 
	font_rendering/font_rendering.cpp
	widgets/label.cpp 
	widgets/linear_layout.cpp
	widgets/single_container.cpp)

find_package(glfw3 3.3 REQUIRED)


add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)

IF(MSVC)
	target_compile_options(${PROJECT_NAME} PRIVATE "/Wall")
ENDIF()

target_link_libraries(${PROJECT_NAME} PUBLIC glfw)

find_package(OpenGL REQUIRED)

target_link_libraries(${PROJECT_NAME} PRIVATE OpenGL::GL)


target_include_directories(${PROJECT_NAME} PUBLIC "${PROJECT_SOURCE_DIR}/")

find_package(GLEW REQUIRED)

target_link_libraries(${PROJECT_NAME} PRIVATE GLEW::GLEW)

find_package(glm REQUIRED)

target_link_libraries(${PROJECT_NAME} PUBLIC glm)


find_path(STB_INCLUDE_DIRS "stb.h" "stbi_image")
target_include_directories(${PROJECT_NAME} PRIVATE ${STB_INCLUDE_DIRS})

find_package(freetype CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE freetype)
