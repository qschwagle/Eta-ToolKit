#include "gl_filled_rectangle.h"

#include "gl_filled_rectangle_program.h"

#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

#include "helpers.h"

#include <string>

#include<GL/glew.h>
#include<GLFW/glfw3.h>

etk::renderer::opengl::GLFilledRectangle::GLFilledRectangle(std::weak_ptr<GLDrawableContext> context) : GLObject(context)
{
    auto c = context.lock();
    auto weakProgram = c->GetProgramHolder(GLFilledRectangleProgram::GetId());
    if (weakProgram.expired()) {
        c->SetProgram(GLFilledRectangleProgram::GetId(), std::make_shared<GLFilledRectangleProgram>(context));
        weakProgram = c->GetProgramHolder(GLFilledRectangleProgram::GetId());
    }
    auto program = weakProgram.lock();
    program->GetProgram()->Use();


	glGenVertexArrays(1, &mVAO);
	glBindVertexArray(mVAO);

	glGenBuffers(1, &mVBO);
	glBindBuffer(GL_ARRAY_BUFFER, mVBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 2, NULL, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), nullptr);
}

etk::renderer::opengl::GLFilledRectangle::~GLFilledRectangle()
{
    glDeleteBuffers(1, &mVBO);
    glDeleteVertexArrays(1, &mVAO);
}

void etk::renderer::opengl::GLFilledRectangle::Draw(glm::vec2 eye)
{
    if (GetContext().expired()) {
        throw std::exception("etk::renderer::opengl::GLFilledRectangle::Draw(): Tried to draw object without context");
        return;
    }

    const glm::vec2& pos = GetPos();


    // Does not check if exists since the context should contain it given that it was created with the context
    // and the constructor was called before Draw()
    auto context = GetContext().lock();
    auto program = context->GetProgramHolder(GLFilledRectangleProgram::GetId()).lock()->GetProgram();
    program->Use();

    glBindVertexArray(mVAO);
    float vertices[6][2] = {
        { pos.x, pos.y + GetHeight() },
        { pos.x, pos.y },
        { pos.x + GetWidth() , pos.y },
        { pos.x, pos.y + GetHeight() },
        { pos.x + GetWidth() , pos.y },
        { pos.x + GetWidth(), pos.y + GetHeight() }
    };
	GLint uniProjView = program->GetUniformLoc(std::string("proj"));
    glm::mat4 proj = CreateOrtho(eye, context->GetWidth(), context->GetHeight());
    program->SetUniformMat4fv(uniProjView, glm::value_ptr(proj));

    glm::mat4 model{ 1.0f };
    model = glm::scale(model, glm::vec3(1.0f, -1.0f, 1.0f));

	GLint modelId = program->GetUniformLoc(std::string("model"));
    program->SetUniformMat4fv(modelId, glm::value_ptr(model));

	GLint colorUniform = program->GetUniformLoc(std::string("color"));
    program->SetUniform3fv(colorUniform, GetColor().GetFloatPtr());

    glBindBuffer(GL_ARRAY_BUFFER, mVBO);
	glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), nullptr);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}