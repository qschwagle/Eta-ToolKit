#pragma once

#include<GL/glew.h>

#include<GLFW/glfw3.h>

#include <string>

class GLShaderProgram {
public:
    GLShaderProgram();
    ~GLShaderProgram();
    bool SetVertSource(std::string &src);
    bool SetFragSource(std::string &src);
    bool Compile();
    void Use();
    unsigned int GetProgram(void) const { return mShaderProgram; }
	int GetUniformLoc(std::string& id);
	void SetUniformMat4fv(GLint loc, const float* mat4);
	void SetUniform3fv(GLint loc, const float* vec3);
    void SetUniform3f(GLint, float x, float y, float z);
    void SetUniform4f(GLint, float x, float y, float z, float w);

private:
    bool CompileShader(std::string &src, GLenum type, unsigned int &shader);

private:
    unsigned int mVertexShader= 0;
    unsigned int mFragmentShader= 0;
    unsigned int mShaderProgram = 0;
    bool mWasCompiled{ false };
};