#pragma once

#include "widget.h"

#include "../renderer/generic/text.h"

#include<string>

namespace etk {
class Label : public Widget {
public:
	Label();
	void Draw() override;

	void SetText(std::wstring t) {
		mData->SetText(t);
	}

	void Init() override;

	class Data {
	public:
		void SetText(std::wstring text) {
			mText = text;
			Update();
		}
		const std::wstring& GetText(void) const { return mText; }

		void SetOwner(std::weak_ptr<Label> owner) {
			mOwner = owner;
			Update();
		}

		void Update() {
			if (!mOwner.expired()) mOwner.lock()->Notify();
		}

	private:
		std::weak_ptr<Label> mOwner;
		std::wstring mText;
	};

	void Notify() {
		if (mTextVisual) {
			mTextVisual->UpdateText(mData->GetText());
			SetInternalHeight(mTextVisual->GetHeight());
			SetInternalWidth(mTextVisual->GetWidth());
		}
	}

private:
	std::unique_ptr<etk::renderer::Text> mTextVisual;
	std::shared_ptr<Data> mData;
};

}