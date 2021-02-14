#include "gl_filled_rectangle.h"
#include "gl_filled_rectangle_program.h"

static std::string vertex_shader_source = "\
#version 330 core \n\
layout (location=0) in vec2 vertex;\n\
uniform mat4 proj;\n\
void main() \n\
{\n\
	gl_Position = proj * vec4(vertex.xy, -1.0, 1.0);\n\
}\
";

static std::string fragment_shader_source = "\
#version 330 core \n\
out vec4 FragColor; \n\
uniform vec4 color;\n\
void main() \n\
{ \n\
    FragColor = vec4(color);\n\
}\
";

etk::renderer::opengl::GLFilledRectangleProgram::GLFilledRectangleProgram(std::weak_ptr<GLDrawableContext> context) : GLObject(context)
{
	mProgram.SetVertSource(vertex_shader_source);
    mProgram.SetFragSource(fragment_shader_source);
    mProgram.Compile();
}

etk::renderer::opengl::GLFilledRectangleProgram::~GLFilledRectangleProgram()
{
}

