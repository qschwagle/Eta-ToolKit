#pragma once

#include "ft2build.h"
#include FT_FREETYPE_H

#include "../renderer/generic/character.h"

namespace etk {
namespace font_rendering {
class FontRendering {
public:
	FontRendering(std::wstring fontPath);
	~FontRendering();

	void SetCharacter(std::weak_ptr<etk::renderer::Character> character, unsigned int c);

	unsigned int GetHeight() {
		unsigned int temp = mHeight + mShift;
		mShift = 0;
		mHeight = 0;
		return temp;
	}

	unsigned int GetWidth() {
		unsigned int temp = mWidth;
		mWidth = 0;
		return temp;
	}

private:
	unsigned int mHeight{ 0 };
	unsigned int mWidth{ 0 };
	unsigned int mShift{ 0 };
	FT_Library* mLibrary;
	FT_Face mFace;
};
}
}