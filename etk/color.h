#pragma once

#include <array>

namespace etk {
class Color {
public:
	Color(unsigned char r, unsigned char g, unsigned char b) {
		mColor[0] = r/255.0f;
		mColor[1] = g/255.0f;
		mColor[2] = b/255.0f;
		mColor[3] = 1.0f;
	}
	
	Color(float r, float g, float b) {
		mColor[0] = r;
		mColor[1] = g;
		mColor[2] = b;
		mColor[3] = 1.0f;
	}


	Color(float r, float g, float b, float a) {
		mColor[0] = r;
		mColor[1] = g;
		mColor[2] = b;
		mColor[3] = a;
	}
	Color(const Color& color) {
		*this = color;
	}

	Color& operator=(const Color& c) {
		std::copy(c.mColor.cbegin(), c.mColor.cend(), mColor.begin());
		return *this;
	}

	const float* GetFloatPtr() const {
		return mColor.data();
	}

	unsigned int GetColorSize(void) const {
		return mColor.size();
	}
private:
	std::array<float, 4> mColor;
};

namespace 
colors {
	const etk::Color BLUE(0.0f, 0.0f, 1.0f);
	const etk::Color RED(1.0f, 0.0f, 0.0f);
	const etk::Color Green(0.0f, 1.0f, 0.0f);
	const etk::Color ORANGE((unsigned char) 0xFF, 0xAF, 0);
	const etk::Color PURPLE((unsigned char)0x80, 0x00, 80);
}


}


