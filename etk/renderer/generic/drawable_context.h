#pragma once

#include <string>

#include <unordered_map>
#include <memory>

#include "screen_box.h"

namespace etk {
namespace renderer {
class DrawableContext {
public:
	virtual ~DrawableContext() {}
	virtual void WindowInit(int width, int height) = 0;
	virtual void Init() = 0;
	virtual void Clear() = 0;
	void SetWidth (const int w) { 
		mWidth = w; 
		for (auto& i : mBoxes) i.lock()->SetDimensions(glm::vec2(w, i.lock()->GetDimensions().y));
	}
	void SetHeight(const int h) { 
		mHeight = h;  
		for (auto& i : mBoxes) i.lock()->SetDimensions(glm::vec2(i.lock()->GetDimensions().x, h));
	}
	int GetWidth() const { return mWidth;  }
	int GetHeight() const { return mHeight;  }
	virtual void UpdateDimensions(const int w, const int h) { SetWidth(w); SetHeight(h); }

	virtual void UpdateContentScale(const float xScale, const float yScale) {
		mContentXScale = xScale;
		mContentYScale = yScale;
	}

	float GetContentXScale() const {
		return mContentXScale;
	}

	float GetContentYScale() const {
		return mContentYScale;
	}

	std::shared_ptr<ScreenBox> GetScreenBox() {
		auto box = std::make_shared<ScreenBox>();
		box->SetDimensions(glm::vec2(static_cast<float>(mWidth), static_cast<float>(mHeight)));
		mBoxes.push_back(box);
		return box;
	}

private:
	float mContentXScale;
	float mContentYScale;
	int mWidth;
	int mHeight;

	std::vector<std::weak_ptr<ScreenBox>> mBoxes;
};
}
}