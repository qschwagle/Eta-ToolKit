#include "label.h"

#include <memory>

#include "../renderer/generic/text.h"

etk::Label::Label()
{

}

void etk::Label::Draw()
{
	mTextVisual->SetPos(GetPadding()[3] + GetMargin()[3] + GetPosition().x, GetPadding()[0] + GetMargin()[0] + GetPosition().y);
	mTextVisual->Draw(GetBox());
}

void etk::Label::SetDrawableFactory(std::weak_ptr<etk::renderer::DrawableFactory> factory)
{
	Widget::SetDrawableFactory(factory);
	if (!factory.expired()) {
		auto fact = GetDrawableFactory().lock();
		mTextVisual = fact->CreateText();
		mTextVisual->UpdateText(mData->GetText());
		SetInternalHeight(mTextVisual->GetHeight());
		SetInternalWidth(mTextVisual->GetWidth());
	}
}
