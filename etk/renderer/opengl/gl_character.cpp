#include "gl_character.h"

#include "gl_character_program.h"

#include "../../color.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "helpers.h"

#include <iterator>

/// <summary>
/// Allocates the Character resources such as vertex array and vertex bufffer
/// </summary>
/// <param name="context">the context associated with the character</param>
etk::renderer::opengl::GLCharacter::GLCharacter(std::weak_ptr<GLDrawableContext> context) : GLObject(context)
{
    auto c = context.lock();
    auto program = c->GetProgramHolder(GLCharacterProgram::GetId());
    if (program.expired()) {
        c->SetProgram(GLCharacterProgram::GetId(), std::make_shared<GLCharacterProgram>(context));
        program = c->GetProgramHolder(GLCharacterProgram::GetId());
    }
    mProgramCache = std::dynamic_pointer_cast<GLCharacterProgram>(program.lock()).get();
    mProgramCache->GetProgram()->Use();

    glGenVertexArrays(1, &mVAO);
    glBindVertexArray(mVAO);

    glGenBuffers(1, &mVBO);
    glBindBuffer(GL_ARRAY_BUFFER, mVBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), nullptr);

    glGenTextures(1, &mTexture);

    GenerateVertices();
}

/// <summary>
/// Deconstructor. deletes gl resources
/// </summary>
etk::renderer::opengl::GLCharacter::~GLCharacter()
{
    glDeleteTextures(1, &mTexture);
    glDeleteBuffers(1, &mVBO);
    glDeleteVertexArrays(1, &mVAO);
}

/// <summary>
/// Draws the character
/// </summary>
/// <param name="eye">the upper left hand corner</param>
void etk::renderer::opengl::GLCharacter::Draw(std::weak_ptr<ScreenBox> box)
{
	if (GetContext().expired()) {
        throw std::exception("etk::renderer::opengl::GLCharacter::Draw(): Tried to draw object without context");
        return;
    }

    auto context = GetContext().lock();
    auto p = mProgramCache;
    auto program = p->GetProgram();
    program->Use();

    GLint textColorId = p->GetTextColorId();
    program->SetUniform3fv(textColorId, GetColor().GetFloatPtr());

    GLint uniProjView = p->GetProjId();
    glm::mat4 proj = etk::renderer::opengl::CreateOrtho(box.lock()->GetShift(), context->GetWidth(), context->GetHeight());
    program->SetUniformMat4fv(uniProjView, glm::value_ptr(proj));

    glBindTexture(GL_TEXTURE_2D, mTexture);
    glBindVertexArray(mVAO);

	auto lbox = box.lock();
	//glViewport(lbox->GetPosAnchor().x, lbox->GetPosAnchor().y, lbox->GetDimensions().x - lbox->GetPosAnchor().x, lbox->GetDimensions().y + lbox->GetPosAnchor().y);

    glBindBuffer(GL_ARRAY_BUFFER, mVBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, mVertices.size()*sizeof(float), mVertices.data());
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

/**
* Used for drawing a block of text. It assumes everything is setup besides the arrays and texture.
*/
void etk::renderer::opengl::GLCharacter::DrawBlock()
{
    glBindTexture(GL_TEXTURE_2D, mTexture);
    glBindVertexArray(mVAO);

    glBindBuffer(GL_ARRAY_BUFFER, mVBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, mVertices.size()*sizeof(float), mVertices.data());
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void etk::renderer::opengl::GLCharacter::DrawBlockCall(std::vector<float> block)
{
    std::copy(mVertices.begin(), mVertices.end(), std::back_inserter(block));
}

/// <summary>
/// Loads the Glyph and associated properties
/// </summary>
/// <param name="adv">advancement distance to next charcter</param>
/// <param name="width">width of the character</param>
/// <param name="height">height of the charcter</param>
/// <param name="bearingX">bearing of character in x</param>
/// <param name="bearingY">bearing of character in y</param>
/// <param name="data">glyph alpha image</param>
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

/// <summary>
/// Generate the Vertices for a given character
/// </summary>
void etk::renderer::opengl::GLCharacter::GenerateVertices()
{
    const float x = GetPos().x; 
    const float y = GetPos().y;
    const float xW = x + GetGlyphWidth();
    const float yH = GetPos().y + GetGlyphHeight() - GetGlyphHeight() + GetBearingY();
    mVertices[0] = x;
    mVertices[1] = yH;
    mVertices[2] = 0.0f;
    mVertices[3] = 0.0f;

    mVertices[4] = x;
    mVertices[5] = y;
    mVertices[6] = 0.0f;
    mVertices[7] = 1.0f;

    mVertices[8] = xW;
    mVertices[9] = y;
    mVertices[10] = 1.0f;
    mVertices[11] = 1.0f;

    mVertices[12] = x;
    mVertices[13] = yH;
    mVertices[14] = 0.0f;
    mVertices[15] = 0.0f;

    mVertices[16] = xW;
    mVertices[17] = y;
    mVertices[18] = 1.0f;
    mVertices[19] = 1.0f;

    mVertices[20] = xW;
    mVertices[21] = yH;
    mVertices[22] = 1.0f;
    mVertices[23] = 0.0f;
}
