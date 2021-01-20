#include "gl_factory.h"

#include "gl_filled_rectangle.h"
#include "gl_character.h"
#include "gl_image.h"
#include "gl_text.h"
#include "gl_rectangle.h"
#include "gl_window_background.h"

etk::renderer::opengl::GLFactory::GLFactory()
{
}

void etk::renderer::opengl::GLFactory::Init()
{

}

std::unique_ptr<etk::renderer::Character> etk::renderer::opengl::GLFactory::CreateCharacter()
{
	return std::make_unique<etk::renderer::opengl::GLCharacter>();
}

std::unique_ptr<etk::renderer::FilledRectangle> etk::renderer::opengl::GLFactory::CreateFilledRectangle()
{
	return std::make_unique<etk::renderer::opengl::GLFilledRectangle>();
}

std::unique_ptr<etk::renderer::Image> etk::renderer::opengl::GLFactory::CreateImage()
{
	return std::make_unique<etk::renderer::opengl::GLImage>();
}

std::unique_ptr<etk::renderer::Rectangle> etk::renderer::opengl::GLFactory::CreateRectangle()
{
	return std::make_unique<etk::renderer::opengl::GLRectangle>();
}

std::unique_ptr<etk::renderer::Text> etk::renderer::opengl::GLFactory::CreateText()
{
	return std::make_unique<etk::renderer::opengl::GLText>();
}

std::unique_ptr<etk::renderer::WindowBackground> etk::renderer::opengl::GLFactory::CreateBackground()
{
	return std::make_unique<etk::renderer::opengl::GLWindowBackground>();
}

