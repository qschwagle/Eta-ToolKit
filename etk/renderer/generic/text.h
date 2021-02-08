#pragma once
#include "drawable_object.h"

namespace etk {
namespace renderer {
class Text : public DrawableObject {
public:
	Text() = default;
	virtual ~Text() {}

	virtual void UpdateText(const std::wstring& text)=0;

	float GetWidth() const { return mWidth;  }
	float GetHeight() const { return mHeight;  }

protected:
	void SetWidth(float w) {
		mWidth = w;
	}
	void SetHeight(float h) {
		mHeight = h;
	}

private:
	float mWidth{ 0.0f };
	float mHeight{ 0.0f };

};
}
}