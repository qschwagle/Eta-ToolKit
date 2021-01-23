#pragma once

#include <string>

#include <unordered_map>

namespace etk {
namespace renderer {
class DrawableContext {
public:
	virtual ~DrawableContext() {}
	virtual void WindowInit(int width, int height) = 0;
	virtual void Init() = 0;
	virtual void Clear() = 0;
	void SetWidth (const int w) { mWidth = w; }
	void SetHeight(const int h) { mHeight = h;  }
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

private:
	float mContentXScale;
	float mContentYScale;
	int mWidth;
	int mHeight;
};
}
}