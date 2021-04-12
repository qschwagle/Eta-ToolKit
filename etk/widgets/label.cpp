#include "label.h"

#include <memory>

#include "../renderer/generic/text.h"

etk::Label::Label()
{

}

void etk::Label::Draw()
{
	if (GetBox().lock()->OnScreen(GetPosition().x, GetPosition().y, GetExternalWidth(), GetExternalHeight())) {
		auto margin = GetMargin();
		mTextVisual->SetPos(GetPadding()[3] + margin[3] + GetPosition().x, GetPadding()[0] + margin[0] + GetPosition().y);
		mTextVisual->Draw(GetBox());
	}
}

void etk::Label::SetDrawableFactory(std::weak_ptr<etk::renderer::DrawableFactory> factory)
{
	Widget::SetDrawableFactory(factory);
	if (!factory.expired()) {
		auto fact = GetDrawableFactory().lock();
		mTextVisual = fact->CreateText();
		mTextVisual->SetSize(GetStyle().lock()->GetFontSize());
		mTextVisual->UpdateText(mData->GetText());
		mTextVisual->SetColor(GetStyle().lock()->GetTextColor());
		SetInternalHeight(mTextVisual->GetHeight());
		SetInternalWidth(mTextVisual->GetWidth());
	}
}
