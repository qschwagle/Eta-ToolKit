#pragma once

#include <unordered_map>

#include "glyph.h"

#include <etk/style/dimensional_unit.h>

namespace etk {
namespace font_rendering {

struct FreeFont;

/// <summary>
/// A font atlas
/// </summary>
class FontAtlas {
public:
	FontAtlas(int width, int height, std::string fontPath, DimensionalUnit pt);
	~FontAtlas();

	FontAtlas(const FontAtlas&) = delete;
	FontAtlas(const FontAtlas&&) = delete;
	FontAtlas& operator=(const FontAtlas&) = delete;

	FontGlyph* GetGlyph(unsigned int character);

private:
	/// <summary>
	/// The raw block of the atlas
	/// </summary>
	unsigned char* mAtlas;

	/// <summary>
	// mapping from unicode to glyph
	/// </summary>
	std::unordered_map<unsigned int, FontGlyph> mMap;

	/// <summary>
	/// width of the atlas
	/// </summary>
	int mWidth;

	/// <summary>
	/// height of the atlas
	/// </summary>
	int mHeight;

	FreeFont* mFreeFont;


	/// <summary>
	/// pt size of the font
	/// </summary>
	DimensionalUnit mPt;

	int mPositionX{ 0 };
	int mPositionY{ 0 };
	int mCharacterHeight{ 0 };

	int mHorizontalDensity{ 200 };
	int mVerticalDensity{ 200 };
};
}
}
