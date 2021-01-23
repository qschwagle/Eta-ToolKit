#include "button.h"

#include "../color.h"

void etk::Button::Draw()
{
	if (!mBackgroundRenderer) {
		auto factory = GetDrawableFactory().lock();
		mBackgroundRenderer = factory->CreateFilledRectangle();
		glm::vec4 padding = GetPadding();
		mBackgroundRenderer->SetPos(padding[3] + GetPosition()[0], padding[0] + GetPosition()[1]);
		mBackgroundRenderer->SetHeight(GetMargin()[0] + GetMargin()[2] + GetInternalHeight());
		mBackgroundRenderer->SetWidth(GetMargin()[1] + GetMargin()[3] + GetInternalWidth());
		mBackgroundRenderer->SetColor(etk::colors::ORANGE);
	}
	mBackgroundRenderer->Draw();
}
