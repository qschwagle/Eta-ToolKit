#pragma once

#include "drawable_object.h"
#include "../../color.h"

namespace etk {
namespace renderer {
class FilledRectangle : public etk::renderer::DrawableObject {
public:
	FilledRectangle() : mColor(1.0f, 1.0f, 1.0f) {}
	virtual ~FilledRectangle() {}
	void SetWidth(const float w) {
		mWidth = w;
	}

	void SetHeight(const float h) {
		mHeight = h;
	}

	const float& GetWidth() {
		return mWidth;
	}

	const float& GetHeight() {
		return mHeight;
	}

	void SetColor(etk::Color color) {
		mColor = color;
	}

	const Color& GetColor() const {
		return mColor;
	}
private:
	float mWidth{ 0.0f };
	float mHeight{ 0.0f };

	Color mColor;
};
}
}