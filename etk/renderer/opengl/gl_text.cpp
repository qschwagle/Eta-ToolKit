#include "gl_text.h"


#include "gl_character.h"

#include "../../font_rendering/font_rendering.h"


void etk::renderer::opengl::GLText::SetText(std::wstring text)
{
	mText = text;
	mGLText.clear();
	etk::font_rendering::FontRendering fontEngine(L"C:\\Windows\\Fonts\\DejaVuSans.ttf");
	auto context = GetContext().lock();
	for (auto& i : mText) {
		mGLText.emplace_back(context->GetCharacter());
		std::shared_ptr<etk::renderer::Character> tempShared = std::static_pointer_cast<etk::renderer::Character>(mGLText.back());
		fontEngine.SetCharacter(tempShared, static_cast<unsigned int>(i));
	}
	SetWidth(fontEngine.GetWidth());
	SetHeight(fontEngine.GetHeight());
}

void etk::renderer::opengl::GLText::Draw(glm::vec2 eye)
{
	float x = GetPos().x, y = -1.0f*(GetHeight() + GetPos().y);
	for (auto& i : mGLText) {
		i->SetPos(x, y);
		i->Draw(eye);
		x += i->GetAdvance();
	}
}
