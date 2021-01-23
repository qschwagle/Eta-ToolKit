#include "gl_character_program.h"

static std::string vertex_shader_source = "\
#version 330 core \n\
layout (location=0) in vec4 vertex;\n\
out vec2 outTex;\n\
uniform mat4 proj;\n\
uniform mat4 model;\n\
void main() \n\
{\n\
	gl_Position = proj * model * vec4(vertex.xy, -1.0, 1.0);\n\
	outTex = vertex.zw;\n\
}\
";

static std::string fragment_shader_source = "\
#version 330 core \n\
in vec2 outTex ; \n\
out vec4 FragColor; \n\
uniform sampler2D text;\n\
uniform vec3 textColor;\n\
void main() \n\
{ \n\
    vec4 sampled = vec4(1.0, 1.0, 1.0, texture(text, outTex).r);\n\
    FragColor = vec4(textColor, 1.0) * sampled;\n\
}\
";

etk::renderer::opengl::GLCharacterProgram::GLCharacterProgram(std::weak_ptr<GLDrawableContext> context) : GLObject(context)
{
    mProgram.SetVertSource(vertex_shader_source);
    mProgram.SetFragSource(fragment_shader_source);
    mProgram.Compile();
}


etk::renderer::opengl::GLCharacterProgram::~GLCharacterProgram()
{

}
