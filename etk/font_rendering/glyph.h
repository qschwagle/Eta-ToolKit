#pragma once

#include <vector>

namespace etk {
namespace font_rendering {
class FontAtlas;

/// <summary>
/// Holds font atlas and glyph information for a given character. 
/// All data is filled in by Font Atlas and is meant to be used through Font Atlas
/// </summary>
class FontGlyph {
public:
	FontGlyph() = default;

	void SetGlyph(int width, int height, int aX, int aY, FontAtlas* atlas, int bX, int bY, int advance) noexcept {
		mWidth = width;
		mHeight = height;
		mAtlasX = aX;
		mAtlasY = aY;
		mAtlas = atlas;
		mBearingX = bX;
		mBearingY = bY;
		mAdvance = advance;
	}

	/// <summary>
	/// retrieves glyph width
	/// </summary>
	/// <returns>glyph width</returns>
	int GetWidth() const noexcept { return mWidth;  }

	/// <summary>
	/// retrieves glyph height
	/// </summary>
	/// <returns>glyph height</returns>
	int GetHeight() const noexcept { return mHeight;  }

	/// <summary>
	/// retreives the x bearing
	/// </summary>
	/// <returns>x bearing</returns>
	int GetBearingX() const noexcept { return mBearingX; }

	/// <summary>
	/// retrieves the y bearing
	/// </summary>
	/// <returns>y bearing</returns>
	int GetBearingY() const noexcept { return mBearingY; }

	/// <summary>
	/// retrieves the x advance
	/// </summary>
	/// <returns>x advance </returns>
	int GetAdvance() const noexcept { return mAdvance;  }

	void LoadVertices(std::vector<float>::iterator& begin, float& x) noexcept;

	/// <summary>
	/// retrieves the font atlas associated with this glyph
	/// </summary>
	/// <returns>font atlas</returns>
	etk::font_rendering::FontAtlas* GetFontAtlas() noexcept { return mAtlas; }

private:
	/// <summary>
	/// pointer to the atlas which contains the glyph
	/// </summary>
	FontAtlas* mAtlas;

	/// <summary>
	/// integer width within the atlas
	/// </summary>
	int mWidth{ 0 };

	/// <summary>
	/// integer height within the atlas
	/// </summary>
	int mHeight{ 0 };

	/// <summary>
	/// top left x position
	/// </summary>
	int mAtlasX{ 0 };

	/// <summary>
	/// top left y position
	/// </summary>
	int mAtlasY{ 0 };

	/// <summary>
	/// glyph bearing x
	/// </summary>
	int mBearingX{ 0 };

	/// <summary>
	/// glyph bearing y
	/// </summary>
	int mBearingY{ 0 };

	/// <summary>
	/// x advance amount
	/// </summary>
	int mAdvance{ 0 };
};
}
}