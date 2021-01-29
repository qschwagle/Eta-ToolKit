#pragma once

#include "widget.h"

#include "../renderer/generic/rectangle.h"
#include "../renderer/generic/text.h"

namespace etk {
class Button : public Widget {
public:
	void Draw() override;

	void Init() override;

	void Invalidate() override {
		mBackgroundRenderer = nullptr;
	}

	void SetText(std::wstring text) {
		mText = text;
		if (IsInitialized()) {
			mTextVisual->SetText(text);
			SetInternalWidth(mTextVisual->GetWidth());
			SetInternalHeight(mTextVisual->GetHeight());
			mBackgroundRenderer->SetPos(GetPadding()[3] + GetPosition()[0], GetPadding()[0] + GetPosition()[1]);
			mBackgroundRenderer->SetHeight(GetMargin()[0] + GetMargin()[2] + GetInternalHeight());
			mBackgroundRenderer->SetWidth(GetMargin()[1] + GetMargin()[3] + GetInternalWidth());
		}
	}
private:
	std::wstring mText;
	std::unique_ptr<etk::renderer::Text> mTextVisual{ nullptr };
	std::unique_ptr<etk::renderer::FilledRectangle> mBackgroundRenderer{ nullptr };
};
}