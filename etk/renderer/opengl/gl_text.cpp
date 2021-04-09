#include "gl_text.h"

#include "gl_character.h"

#include "../../font_rendering/font_rendering.h"


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
}

void etk::renderer::opengl::GLText::UpdateColor()
{
	for (auto& i : mGLText) {
		i->SetColor(GetColor());
	}
}

void etk::renderer::opengl::GLText::UpdatePosition()
{
	float x = GetPos().x, y = -1.0f*(GetHeight() + GetPos().y);
	for (auto& i : mGLText) {
		i->SetPos(x, y);
		x += i->GetAdvance();
	}
}

void etk::renderer::opengl::GLText::Draw(std::weak_ptr<ScreenBox> box)
{
	auto i = mGLText.begin();
	if (i != mGLText.end()) {
		(*i)->Draw(box);
	}
	for (; i != mGLText.end(); ++i) {
		(*i)->DrawBlock();
	}

}
