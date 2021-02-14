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
			mTextVisual->UpdateText(text);
			SetInternalWidth(mTextVisual->GetWidth());
			SetInternalHeight(mTextVisual->GetHeight());
			mBackgroundRenderer->SetPos(GetPadding()[3] + GetPosition()[0], GetPadding()[0] + GetPosition()[1]);
			mBackgroundRenderer->SetHeight(GetMargin()[0] + GetMargin()[2] + GetInternalHeight());
			mBackgroundRenderer->SetWidth(GetMargin()[1] + GetMargin()[3] + GetInternalWidth());
		}
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