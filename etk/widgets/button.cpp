#include "button.h"

#include "../color.h"

void etk::Button::Draw()
{
	mBackgroundRenderer->Draw(GetBox());
	mTextVisual->Draw(GetBox());
}

void etk::Button::SetDrawableFactory(std::weak_ptr<etk::renderer::DrawableFactory> factory)
{
	Widget::SetDrawableFactory(factory);
	if (!factory.expired()) {
		auto fact = GetDrawableFactory().lock();
		mTextVisual = fact->CreateText();
		mTextVisual->SetSize(GetStyle().lock()->GetFontSize());
		mTextVisual->SetColor(GetStyle().lock()->GetTextColor());
		mBackgroundRenderer = fact->CreateFilledRectangle();
		mBackgroundRenderer->SetColor(GetBackgroundColor());
		UpdateText();
	}
}
