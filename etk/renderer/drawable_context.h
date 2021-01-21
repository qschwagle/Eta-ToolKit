#pragma once

namespace etk {
namespace renderer {
class DrawableContext {
public:
	virtual void WindowInit(int width, int height) = 0;
	virtual void Init() = 0;
	virtual void Clear() = 0;
	void SetWidth (const int w) { mWidth = w; }
	void SetHeight(const int h) { mHeight = h;  }
	int GetWidth() const { return mWidth;  }
	int GetHeight() const { return mHeight;  }
	void UpdateDimensions(const int w, const int h) { SetWidth(w); SetHeight(h); }
private:
	int mWidth;
	int mHeight;
};
}
}