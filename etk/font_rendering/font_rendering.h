#pragma once

#include "ft2build.h"
#include FT_FREETYPE_H

#include "../renderer/generic/character.h"

namespace etk {
/// <summary>
/// Manages Font management and glyph allocation. Depends heavily on freetype
/// </summary>
namespace font_rendering {
class FontRendering {
public:
	FontRendering(std::string fontPath);

	/// <summary>
	/// Copy Constructor not needed. Deleted.
	/// </summary>
	FontRendering(const FontRendering&) = delete;

	/// <summary>
	/// Assignment operator not needed. Deleted.
	/// </summary>
	FontRendering& operator=(const FontRendering&) = delete;

	~FontRendering();

	void SetCharacter(std::weak_ptr<etk::renderer::Character> character, unsigned int c);

	/// <summary>
	/// Gets the total required height for the text. Resets to zero once retrieved
	/// </summary>
	/// <returns>total height</returns>
	unsigned int GetHeight() {
		unsigned int temp = mHeight + mShift;
		mShift = 0;
		mHeight = 0;
		return temp;
	}

	/// <summary>
	/// Retreives the total width required by the text. resets to zero once retrieved
	/// </summary>
	/// <returns>width of thet text</returns>
	unsigned int GetWidth() {
		unsigned int temp = mWidth;
		mWidth = 0;
		return temp;
	}

	void SetDpi(float hor, float vert);

	void SetPt(unsigned int pt);

private:
	/// <summary>
	/// pt height of the allocated glyphs
	/// </summary>
	unsigned int mPtHeight{ 24 };

	/// <summary>
	/// horizontal dpi used by freetype
	/// </summary>
	float mHor{ 200 };

	/// <summary>
	/// vertical dpi used by freetype
	/// </summary>
	float mVert{ 200 };
	/// <summary>
	/// current Height of the field
	/// </summary>
	unsigned int mHeight{ 0 };

	/// <summary>
	/// Current Width of the field
	/// </summary>
	unsigned int mWidth{ 0 };

	/// <summary>
	/// Shift required by text when placement. used to adjust height
	/// </summary>
	unsigned int mShift{ 0 };

	/// <summary>
	/// freetype library
	/// </summary>
	FT_Library* mLibrary;

	/// <summary>
	/// Freetype face
	/// </summary>
	FT_Face mFace;
};
}
}