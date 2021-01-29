#include "button.h"

#include "../color.h"

void etk::Button::Draw()
{
	mBackgroundRenderer->Draw(GetBox().lock()->GetShift());
	mTextVisual->Draw(GetBox().lock()->GetShift());
}

void etk::Button::Init()
{
	etk::Widget::Init();
	auto fact = GetDrawableFactory().lock();
	mTextVisual = fact->CreateText();
	mTextVisual->SetText(mText);
	SetInternalHeight(mTextVisual->GetHeight());
	SetInternalWidth(mTextVisual->GetWidth());
	mTextVisual->SetPos(GetPadding()[3] + GetMargin()[3] + GetPosition()[0], GetPadding()[0] + GetPosition()[1] +GetMargin()[0]);
	mBackgroundRenderer = fact->CreateFilledRectangle();
	mBackgroundRenderer->SetPos(GetPadding()[3] + GetPosition()[0], GetPadding()[0] + GetPosition()[1]);
	mBackgroundRenderer->SetHeight(GetMargin()[0] + GetMargin()[2] + GetInternalHeight());
	mBackgroundRenderer->SetWidth(GetMargin()[1] + GetMargin()[3] + GetInternalWidth());
	mBackgroundRenderer->SetColor(etk::colors::ORANGE);
}
