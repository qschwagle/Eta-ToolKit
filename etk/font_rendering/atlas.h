#pragma once

#include <unordered_map>
#include <memory>

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


	/// <summary>
	/// Retrieves the texture atlas
	/// </summary>
	/// <returns>texture atlas</returns>
	unsigned char* GetAtlas() {
		return mAtlas;
	}

	/// <summary>
	/// Width of the texture atlas in pixels
	/// </summary>
	/// <returns>width of atlas</returns>
	int GetWidth() {
		return mWidth;
	}

	/// <summary>
	/// height of the texture atlas in pixels
	/// </summary>
	/// <returns>height in pixels</returns>
	int GetHeight() {
		return mHeight;
	}

private:
	/// <summary>
	/// The raw block of the atlas
	/// </summary>
	unsigned char* mAtlas;

	/// <summary>
	// mapping from unicode to glyph
	/// </summary>
	std::unordered_map<unsigned int, std::unique_ptr<FontGlyph>> mMap;

	/// <summary>
	/// width of the atlas
	/// </summary>
	int mWidth;

	/// <summary>
	/// height of the atlas
	/// </summary>
	int mHeight;

	/// <summary>
	/// Pointer to container holding Freefont data strctures
	/// </summary>
	FreeFont* mFreeFont;

	/// <summary>
	/// pt size of the font
	/// </summary>
	DimensionalUnit mPt;

	/// <summary>
	/// Next point for character in texture atlas in the x direction
	/// </summary>
	int mPositionX{ 0 };

	/// <summary>
	/// Next point in top corner for character in the texture atlas in the y direction
	/// </summary>
	int mPositionY{ 0 };

	/// <summary>
	/// horizontal screen pixel density
	/// </summary>
	int mHorizontalDensity{ 200 };

	/// <summary>
	/// vertical screen pixel density
	/// </summary>
	int mVerticalDensity{ 200 };
};
}
}
