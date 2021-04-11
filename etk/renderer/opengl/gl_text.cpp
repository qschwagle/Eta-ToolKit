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
	mGLText.clear();
	etk::font_rendering::FontRendering fontEngine("C:\\Windows\\Fonts\\Arial.ttf");
	auto context = GetContext().lock();
	for (auto& i : text) {
		mGLText.emplace_back(context->GetCharacter());
		std::shared_ptr<etk::renderer::Character> tempShared = std::static_pointer_cast<etk::renderer::Character>(mGLText.back());
		fontEngine.SetPt(static_cast<unsigned int>(GetSize().GetPt(0,0,0,0)));
		fontEngine.SetCharacter(tempShared, static_cast<unsigned int>(i));
	}
	SetWidth(fontEngine.GetWidth());
	SetHeight(fontEngine.GetHeight());
	UpdateColor();
	UpdatePosition();

	float x = GetPos().x, y = -1.0f*(GetHeight() + GetPos().y);
	for (auto& i : mGLText) {
		i->SetPos(x, y);
		x += i->GetAdvance();
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

	mBlockCache.resize(mGLText.size() * 24);
	auto iter = mBlockCache.begin();
	for (auto i : mGLText) {
		i->DrawBlockCall(iter);
	}
}

void etk::renderer::opengl::GLText::UpdateColor()
{
	//for (auto& i : mGLText) {
	//	i->SetColor(GetColor());
	//}
}

void etk::renderer::opengl::GLText::UpdatePosition()
{

}

void etk::renderer::opengl::GLText::Draw(std::weak_ptr<ScreenBox> box)
{
	auto i = mGLText.begin();
	if (i != mGLText.end()) {
	//	(*i)->Draw(box);
	}

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

    glBindTexture(GL_TEXTURE_2D, (*i)->mTexture);
    glBindVertexArray(mVAO);
    glBindBuffer(GL_ARRAY_BUFFER, mVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * mBlockCache.size(), NULL, GL_DYNAMIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, mBlockCache.size()*sizeof(float), mBlockCache.data());
    glDrawArrays(GL_TRIANGLES, 0, mBlockCache.size()/4);
}
