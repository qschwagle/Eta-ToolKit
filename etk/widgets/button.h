#pragma once

#include "widget.h"

#include "../renderer/generic/rectangle.h"
#include "../renderer/generic/text.h"
#include <etk/renderer/generic/drawable_factory.h>

namespace etk {
class Button : public Widget {
public:
	void Draw() override;

	void Invalidate() override {
		mBackgroundRenderer = nullptr;
		InvalidateOwner();
	}

	void SetDrawableFactory(std::weak_ptr<etk::renderer::DrawableFactory> factory) override; 

	void SetText(std::wstring text) {
		mText = text;
		if (!GetDrawableFactory().expired()) {
			UpdateText();
		}
	}

	void UpdateText() {
   		mTextVisual->UpdateText(mText);
		auto margin = GetMargin();
		mTextVisual->SetPos(GetPadding()[3] + margin[3] + GetPosition()[0], GetPadding()[0] + GetPosition()[1] + margin[0]);
   		SetInternalWidth(mTextVisual->GetWidth());
   		SetInternalHeight(mTextVisual->GetHeight());
		mBackgroundRenderer->SetPos(GetPadding()[3] + GetPosition()[0], GetPadding()[0] + GetPosition()[1]);
		mBackgroundRenderer->SetHeight(margin[0] + margin[2] + GetInternalHeight());
		mBackgroundRenderer->SetWidth(margin[1] + margin[3] + GetInternalWidth());
		InvalidateOwner();
	}

	void SetFontSize(DimensionalUnit u) {
		GetStyle().lock()->SetFontSize(u);
		if (mTextVisual) {
			mTextVisual->SetSize(u);
		}

	}

	void SetTextColor(Color c) {
		GetStyle().lock()->SetTextColor(c);
		if (mTextVisual) {
			mTextVisual->SetColor(c);
		}
	}

private:
	std::wstring mText;
	std::unique_ptr<etk::renderer::Text> mTextVisual{ nullptr };
	std::unique_ptr<etk::renderer::FilledRectangle> mBackgroundRenderer{ nullptr };
};
}