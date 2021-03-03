cmake_minimum_required(VERSION 3.17)
project(etk)
include(FetchContent)

#FetchContent_Declare(
#    glew	
#	URL https://github.com/nigels-com/glew/releases/download/glew-2.2.0/glew-2.2.0.zip
#)
#
#FETCHCONTENT_MAKEAVAILABLE(glew)

FetchContent_Declare(
	glfw3
	GIT_REPOSITORY https://github.com/glfw/glfw.git
	GIT_TAG 3.3.2
)

FETCHCONTENT_MAKEAVAILABLE(glfw3)

FetchContent_Declare(
	glm	
	GIT_REPOSITORY https://github.com/g-truc/glm.git
	GIT_TAG 0.9.9.8
)

FETCHCONTENT_MAKEAVAILABLE(glm)

FetchContent_Declare(
	stb	
	GIT_REPOSITORY https://github.com/aganm/stb.git
)

FETCHCONTENT_MAKEAVAILABLE(stb)

FETCHCONTENT_DECLARE(
	freetype
	GIT_REPOSITORY https://github.com/freetype/freetype.git
	GIT_TAG VER-2-10-2
)

FETCHCONTENT_MAKEAVAILABLE(freetype)

add_subdirectory(extern/glew-2.2.0/build/cmake)

add_subdirectory(etk)
add_subdirectory(imageviewer2)
add_subdirectory(tests)
