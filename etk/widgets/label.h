#pragma once

#include "widget.h"

#include "../renderer/generic/text.h"

#include<string>

namespace etk {
class Label : public Widget {
public:
	Label();
	void Draw(const glm::vec2& eye) override;

	void SetText(std::wstring t) {
		mText = t;
		if (mTextVisual) {
			mTextVisual->SetText(t);
			SetInternalHeight(mTextVisual->GetHeight());
			SetInternalWidth(mTextVisual->GetWidth());
		}
	}

	void Init() override;

private:
	std::unique_ptr<etk::renderer::Text> mTextVisual;
	std::wstring mText;
};

}