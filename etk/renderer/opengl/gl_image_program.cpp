#include "gl_image_program.h"

static std::string vertex_shader_source = "\
#version 330 core \n\
layout (location=0) in vec2 aPos;\n\
layout (location=1) in vec2 aTex;\n\
out vec2 outTex;\n\
uniform mat4 model;\n\
uniform mat4 proj_view;\n\
out vec2 pos;\n\
void main() \n\
{\n\
	gl_Position = proj_view * model * vec4(aPos, -1.0, 1.0);\n\
	outTex = aTex;\n\
	pos = aPos;\n\
}\
";

static std::string fragment_shader_source = "\
#version 330 core \n\
in vec2 pos;\n\
in vec2 outTex ; \n\
out vec4 FragColor; \n\
uniform sampler2D ourTexture;\n\
uniform vec4 boundary;\n\
void main() \n\
{ \n\
	FragColor = texture(ourTexture, outTex); //* float (boundary.x < pos.x && pos.x < boundary.x + boundary.z && boundary.y < pos.y && pos.y < boundary.y + boundary.w);\n\
}\
";

etk::renderer::opengl::GLImageProgram::GLImageProgram(std::weak_ptr<GLDrawableContext> context) : GLObject(context)
{
	mProgram.SetVertSource(vertex_shader_source);
    mProgram.SetFragSource(fragment_shader_source);
    mProgram.Compile();
}
