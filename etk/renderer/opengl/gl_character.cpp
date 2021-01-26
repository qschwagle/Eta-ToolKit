#include "gl_character.h"

#include "gl_character_program.h"

#include "../../color.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "helpers.h"

static std::vector<float> rectangle = {
	 0.0f,  1.0f,  0.0, 0.0,
	 0.0f,  0.0f,  0.0, 1.0,
	 1.0f,  0.0f,  1.0, 1.0,

	 0.0f,  1.0f,  0.0, 0.0,
	 1.0f,  0.0f,  1.0, 1.0,
	 1.0f,  1.0f,  1.0, 0.0,
};

etk::renderer::opengl::GLCharacter::GLCharacter(std::weak_ptr<GLDrawableContext> context) : GLObject(context)
{

    auto c = context.lock();
    auto weakProgram = c->GetProgramHolder(GLCharacterProgram::GetId());
    if (weakProgram.expired()) {
        c->SetProgram(GLCharacterProgram::GetId(), std::make_shared<GLCharacterProgram>(context));
        weakProgram = c->GetProgramHolder(GLCharacterProgram::GetId());
    }
    auto program = weakProgram.lock();
    program->GetProgram()->Use();

    glGenVertexArrays(1, &mVAO);
    glBindVertexArray(mVAO);

    glGenBuffers(1, &mVBO);
    glBindBuffer(GL_ARRAY_BUFFER, mVBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), nullptr);

    glGenTextures(1, &mTexture);
}

etk::renderer::opengl::GLCharacter::~GLCharacter()
{
    glDeleteTextures(1, &mTexture);
    glDeleteBuffers(1, &mVBO);
    glDeleteVertexArrays(1, &mVAO);
}

void etk::renderer::opengl::GLCharacter::Draw(glm::vec2 eye)
{
	if (GetContext().expired()) {
        throw std::exception("etk::renderer::opengl::GLCharacter::Draw(): Tried to draw object without context");
        return;
    }

    auto context = GetContext().lock();
    auto program = context->GetProgramHolder(GLCharacterProgram::GetId()).lock()->GetProgram();
    program->Use();

    std::string uniformTextColor = "textColor";
    program->SetUniform3fv(program->GetUniformLoc(uniformTextColor), etk::colors::BLUE.GetFloatPtr());

    GLint uniProjView = program->GetUniformLoc(std::string("proj"));
    glm::mat4 proj = etk::renderer::opengl::CreateOrtho(eye, context->GetWidth(), context->GetHeight());
    program->SetUniformMat4fv(uniProjView, glm::value_ptr(proj));

    GLint modelId = program->GetUniformLoc(std::string("model"));

    glBindTexture(GL_TEXTURE_2D, mTexture);
    glBindVertexArray(mVAO);


    const auto shiftRight = GetBearingX();
    const auto shiftDown = 0;
    const auto shiftY = GetPos().y + shiftDown;
    const auto shiftX = GetPos().x + shiftRight;

    const auto sizeY = GetGlyphHeight();
    const auto sizeX = GetGlyphWidth();

    glm::mat4 model{ 1.0f };
    model = glm::translate(model, glm::vec3(shiftX, shiftY, 0.0f));
    model = glm::scale(model, glm::vec3(sizeX, sizeY, 1.0f));
    program->SetUniformMat4fv(modelId, glm::value_ptr(model));

    glBindBuffer(GL_ARRAY_BUFFER, mVBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, rectangle.size()*sizeof(float), rectangle.data());
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void etk::renderer::opengl::GLCharacter::LoadGlyph(unsigned int adv, unsigned int width, unsigned int height, int bearingX, int bearingY, unsigned char* data)
{
	SetAdvance(adv);
	SetGlyphWidth(width);
	SetGlyphHeight(height);
	SetBearingX(bearingX);
	SetBearingY(bearingY);

    glBindTexture(GL_TEXTURE_2D, mTexture);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, width, height, 0, GL_RED, GL_UNSIGNED_BYTE, data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}
