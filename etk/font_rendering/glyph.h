#pragma once

#include <vector>


namespace etk {
namespace font_rendering {
class FontAtlas;

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

	int GetWidth() const noexcept { return mWidth;  }

	int GetHeight() const noexcept { return mHeight;  }

	int GetBearingX() const noexcept { return mBearingX; }

	int GetBearingY() const noexcept { return mBearingY; }

	int GetAdvance() const noexcept { return mAdvance;  }


	void LoadVertices(std::vector<float>::iterator& begin, float& x) noexcept;

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

	int mBearingX{ 0 };

	int mBearingY{ 0 };

	int mAdvance{ 0 };
};
}
}