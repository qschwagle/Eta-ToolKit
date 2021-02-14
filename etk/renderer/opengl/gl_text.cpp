#include "gl_text.h"

#include "gl_character.h"

#include "../../font_rendering/font_rendering.h"


void etk::renderer::opengl::GLText::UpdateText(const std::wstring& text)
{
	mGLText.clear();
	etk::font_rendering::FontRendering fontEngine(L"C:\\Windows\\Fonts\\Arial.ttf");
	auto context = GetContext().lock();
	for (auto& i : text) {
		mGLText.emplace_back(context->GetCharacter());
		std::shared_ptr<etk::renderer::Character> tempShared = std::static_pointer_cast<etk::renderer::Character>(mGLText.back());
		fontEngine.SetPt(static_cast<unsigned int>(GetSize().GetPt(0,0,0,0)));
		fontEngine.SetCharacter(tempShared, static_cast<unsigned int>(i));
	}
	SetWidth(fontEngine.GetWidth());
	SetHeight(fontEngine.GetHeight());
}

void etk::renderer::opengl::GLText::Draw(std::weak_ptr<ScreenBox> box)
{
	float x = GetPos().x, y = -1.0f*(GetHeight() + GetPos().y);
	for (auto& i : mGLText) {
		i->SetColor(GetColor());
		i->SetPos(x, y);
		i->Draw(box);
		x += i->GetAdvance();
	}
}
