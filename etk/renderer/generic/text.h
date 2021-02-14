#pragma once
#include "drawable_object.h"
#include <etk/style/dimensional_unit.h>
#include <etk/color.h>

namespace etk {
namespace renderer {
class Text : public DrawableObject {
public:
	Text() = default;
	virtual ~Text() {}

	virtual void UpdateText(const std::wstring& text)=0;

	float GetWidth() const { return mWidth;  }
	float GetHeight() const { return mHeight;  }

	void SetSize(etk::DimensionalUnit u) {
		mSize = u;
	}

	etk::DimensionalUnit GetSize(void) const {
		return mSize;
	}

	void SetColor(etk::Color c) {
		mColor = c;
	}

	etk::Color GetColor(void) const {
		return mColor;
	}

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

	etk::DimensionalUnit mSize;
	etk::Color mColor{ etk::colors::BLACK };


};
}
}