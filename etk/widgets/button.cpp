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
		mTextVisual->UpdateText(mText);
		mTextVisual->SetColor(GetStyle().lock()->GetTextColor());
		SetInternalHeight(mTextVisual->GetHeight());
		SetInternalWidth(mTextVisual->GetWidth());
		auto margin = GetMargin();
		mTextVisual->SetPos(GetPadding()[3] + margin[3] + GetPosition()[0], GetPadding()[0] + GetPosition()[1] + margin[0]);
		mBackgroundRenderer = fact->CreateFilledRectangle();
		mBackgroundRenderer->SetPos(GetPadding()[3] + GetPosition()[0], GetPadding()[0] + GetPosition()[1]);
		mBackgroundRenderer->SetHeight(margin[0] + margin[2] + GetInternalHeight());
		mBackgroundRenderer->SetWidth(margin[1] + margin[3] + GetInternalWidth());
		mBackgroundRenderer->SetColor(GetBackgroundColor());
		InvalidateOwner();
	}
}
