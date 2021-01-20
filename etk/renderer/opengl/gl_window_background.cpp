#include "gl_window_background.h"

#include <gl/glew.h>

void etk::renderer::opengl::GLWindowBackground::Draw()
{
	auto color = GetColor().GetFloatPtr();
	glClearColor(color[0], color[1], color[2], color[3]);
}
