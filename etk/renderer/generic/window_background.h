#pragma once

#include "../../color.h"

namespace etk {
namespace renderer {
class WindowBackground {
public:
	WindowBackground() : mColor(1.0f, 1.0f, 1.0f) { }
	virtual ~WindowBackground() {}
	void SetColor(const etk::Color color) {
		mColor = color;
	}
	const etk::Color& GetColor(void) const {
		return mColor;
	}
	virtual void Draw() = 0;
private:
	etk::Color mColor;
};
}
}
