#include "label.h"

#include "../renderer/generic/text.h"

etk::Label::Label()
{
}

void etk::Label::Init()
{
	etk::Widget::Init();
	auto fact = GetDrawableFactory().lock();
	mTextVisual = fact->CreateText();
	mTextVisual->SetText(mText);
	SetInternalHeight(mTextVisual->GetHeight());
	SetInternalWidth(mTextVisual->GetWidth());
}

void etk::Label::Draw(const glm::vec2& eye)
{
	mTextVisual->SetPos(GetPadding()[3] + GetMargin()[3] + GetPosition().x, GetPadding()[0] + GetMargin()[0] + GetPosition().y);
	mTextVisual->Draw(eye + GetEye());
}
