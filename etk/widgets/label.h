#pragma once

#include "widget.h"

#include "../renderer/generic/text.h"

#include<string>

namespace etk {
class Label : public Widget {
public:
	Label();
	void Draw() override;

	void SetDrawableFactory(std::weak_ptr<etk::renderer::DrawableFactory> factory) override; 

	void SetText(std::wstring t) {

		if (!mData) {
			mData = std::make_shared<Data>();
			auto ptr = std::dynamic_pointer_cast<etk::Label>(shared_from_this());
			mData->AddObserver(ptr);
		}
		mData->SetText(t);
	}

	class Data {
	public:
		void SetText(std::wstring text) {
			mText = text;
			Notify();
		}
		const std::wstring& GetText(void) const { return mText; }

		void AddObserver(std::weak_ptr<Label> o) {
			mObs.push_back(o);
			Notify();
		}

		void Notify() {
			for(auto& i: mObs) if (!i.expired()) i.lock()->Update();
		}

	private:
		std::vector<std::weak_ptr<Label>> mObs;
		std::wstring mText;
	};

	void Update() {
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