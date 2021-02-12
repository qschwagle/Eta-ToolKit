#include "gl_shader_program.h"

#include <iostream>

GLShaderProgram::GLShaderProgram()
{
}

GLShaderProgram::~GLShaderProgram()
{
    if(mWasCompiled) glDeleteProgram(mShaderProgram);
}

bool GLShaderProgram::SetVertSource(std::string& src)
{
    return CompileShader(src, GL_VERTEX_SHADER, mVertexShader);
}

bool GLShaderProgram::SetFragSource(std::string& src)
{
    return CompileShader(src, GL_FRAGMENT_SHADER, mFragmentShader);
}

bool GLShaderProgram::Compile()
{
    int success;
    char infoLog[512];
    mShaderProgram = glCreateProgram();
    glAttachShader(mShaderProgram, mVertexShader);
    glAttachShader(mShaderProgram, mFragmentShader);
    glLinkProgram(mShaderProgram);
    glGetProgramiv(mShaderProgram, GL_LINK_STATUS, &success);
    mWasCompiled = true;
    if (!success) {
        glGetProgramInfoLog(mShaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::COMPILATION_FAILED\n" << infoLog << std::endl;
        return false;
    }
    glDeleteShader(mVertexShader);
    glDeleteShader(mFragmentShader);
    return true;
}

void GLShaderProgram::Use()
{
    glUseProgram(mShaderProgram);
}

int GLShaderProgram::GetUniformLoc(std::string& id)
{
	return glGetUniformLocation(mShaderProgram, id.c_str());
}

void GLShaderProgram::SetUniformMat4fv(GLint loc, const float* mat4)
{
	glUniformMatrix4fv(loc, 1, GL_FALSE, mat4);
}

void GLShaderProgram::SetUniform3fv(GLint loc, const float* vec3)
{
	glUniform3fv(loc, 1, vec3);
}

void GLShaderProgram::SetUniform3f(GLint loc, float x, float y, float z)
{
    glUniform3f(loc, x, y, z);
}

void GLShaderProgram::SetUniform4f(GLint loc, float x, float y, float z, float w)
{
    glUniform4f(loc, x, y, z, w);
}

void GLShaderProgram::SetUniform4fv(GLint loc, const float* vec4)
{
    glUniform4fv(loc, 1, vec4);
}

bool GLShaderProgram::CompileShader(std::string& src, GLenum type, unsigned int& shader)
{
    int success;
    char infoLog[512];
    shader = glCreateShader(type);
    const char* temp = src.c_str();
    glShaderSource(shader, 1, &temp, NULL);
    glCompileShader(shader);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
        return false;
    }
    std::cout << "Shader Created" << std::endl;
    return true;
}
