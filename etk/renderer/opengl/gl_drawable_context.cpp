#include "gl_drawable_context.h"

#include <Gl/glew.h>
#include <GLFW/glfw3.h>

#include <exception>

#include "gl_character.h"

etk::renderer::opengl::GLDrawableContext::GLDrawableContext() : mFontBook {std::make_unique<etk::font_rendering::FontBook>()}
{
}

void etk::renderer::opengl::GLDrawableContext::WindowInit(int width, int height)
{
    glewExperimental = true;

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SRGB_CAPABLE, GLFW_TRUE);

	UpdateDimensions(width, height);
}

void etk::renderer::opengl::GLDrawableContext::Init()
{
	glEnable(GL_MULTISAMPLE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	if (glewInit() != GLEW_OK)
	{
		throw std::exception("failed to initialize glew");
	}
}

void etk::renderer::opengl::GLDrawableContext::Clear()
{
	glClear(GL_COLOR_BUFFER_BIT);
}

void etk::renderer::opengl::GLDrawableContext::UpdateDimensions(const int width, const int height)
{
	glViewport(0, 0, width, height);
	etk::renderer::DrawableContext::UpdateDimensions(width, height);
}

/// <summary>
/// Provides an interface for getting characters with context
/// </summary>
/// <returns></returns>
std::shared_ptr<etk::renderer::opengl::GLCharacter> etk::renderer::opengl::GLDrawableContext::GetCharacter()
{
	return std::make_shared<etk::renderer::opengl::GLCharacter>(shared_from_this());
}
