#ifndef _ETK_FONT_ATLAS_H_
#define _ETK_FONT_ATLAS_H_

#include <unordered_map>

#include "font_rendering.h"
#include "glyph.h"

namespace etk {
namespace font_rendering {

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

	/// <summary>
	/// freetype library
	/// </summary>
	FT_Library* mLibrary;

	/// <summary>
	/// Freetype face
	/// </summary>
	FT_Face mFace;

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


#endif