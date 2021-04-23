#include "gl_text.h"
#include "gl_character.h"
#include "etk/font_rendering/font_rendering.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "helpers.h"
#include <iterator>

etk::renderer::opengl::GLText::~GLText()
{
    glDeleteBuffers(1, &mVBO);
    glDeleteVertexArrays(1, &mVAO);
}

void etk::renderer::opengl::GLText::UpdateText(const std::wstring& text)
{
	auto context = GetContext().lock();

    auto book = context->GetFontBook();
    auto atlas = book->GetAtlas("Arial", GetSize().GetPt(0,0,0,0), "C:\\Windows\\Fonts\\Arial.ttf");

    mGlyphs.clear();
    auto max_height = 0;
    auto max_width = 0;
    for (auto i = text.cbegin(); i != text.cend(); ++i) {
        auto glyph = atlas->GetGlyph(*i);
        mGlyphs.emplace_back(glyph);
        max_width += glyph->GetAdvance();
        if (glyph->GetHeight() > max_height) max_height = glyph->GetHeight();
    }
    SetWidth(max_width);
    SetHeight(max_height);

    float x = GetPos().x;
	mBlockCache.resize(mGlyphs.size() * 24);
    auto begin = mBlockCache.begin();
    for (auto& i : mGlyphs) {
        i->LoadVertices(begin, x);
    }

    auto program = context->GetProgramHolder(GLCharacterProgram::GetId());
    if (program.expired()) {
        context->SetProgram(GLCharacterProgram::GetId(), std::make_shared<GLCharacterProgram>(context));
        program = context->GetProgramHolder(GLCharacterProgram::GetId());
    }

    mProgramCache = std::dynamic_pointer_cast<GLCharacterProgram>(program.lock()).get();
    mProgramCache->GetProgram()->Use();

    glGenVertexArrays(1, &mVAO);
    glBindVertexArray(mVAO);

    glGenBuffers(1, &mVBO);
    glBindBuffer(GL_ARRAY_BUFFER, mVBO);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), nullptr);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * mBlockCache.size(), NULL, GL_DYNAMIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, mBlockCache.size()*sizeof(float), mBlockCache.data());

    glDeleteTextures(1, &mTexture);
    glGenTextures(1, &mTexture);

    glBindTexture(GL_TEXTURE_2D, mTexture);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, atlas->GetWidth(), atlas->GetHeight(), 0, GL_RED, GL_UNSIGNED_BYTE, atlas->GetAtlas());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void etk::renderer::opengl::GLText::UpdateColor()
{
}

void etk::renderer::opengl::GLText::UpdatePosition()
{

}

void etk::renderer::opengl::GLText::Draw(std::weak_ptr<ScreenBox> box) noexcept
{
    auto context = GetContext().lock();
    auto p = mProgramCache;
    auto program = p->GetProgram();
    program->Use();

    GLint textColorId = p->GetTextColorId();
    program->SetUniform3fv(textColorId, GetColor().GetFloatPtr());

    glm::mat4 view(1.0f);
    GLint viewId = p->GetViewId();
    view = glm::translate(view, glm::vec3(GetPos().x, -1.0f*(GetHeight() + GetPos().y), 0.0f));
    program->SetUniformMat4fv(viewId, glm::value_ptr(view));

    GLint uniProjView = p->GetProjId();
    glm::mat4 proj = etk::renderer::opengl::CreateOrtho(box.lock()->GetShift(), context->GetWidth(), context->GetHeight());
    program->SetUniformMat4fv(uniProjView, glm::value_ptr(proj));

    glBindTexture(GL_TEXTURE_2D, mTexture);
    glBindVertexArray(mVAO);
    glDrawArrays(GL_TRIANGLES, 0, mBlockCache.size()/4);
}
