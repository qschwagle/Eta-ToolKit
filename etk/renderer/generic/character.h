#pragma once 
#include "drawable_object.h"

#include <etk/style/dimensional_unit.h>
#include <etk/color.h>

namespace etk {
namespace renderer {
class Character : public etk::renderer::DrawableObject {
public:
	Character() = default;
	virtual ~Character() {}
	virtual void LoadGlyph(unsigned int adv, unsigned int width, unsigned int height, int bearingX, int bearingY, unsigned char* data) = 0;


	unsigned int GetAdvance(void) const { return mAdvance; }
	unsigned int GetGlyphWidth(void) const { return mGlyphWidth; }
	unsigned int GetGlyphHeight(void) const { return mGlyphHeight; }
	int GetBearingX(void) const { return mBearingX; }
	int GetBearingY(void) const { return mBearingY; }

	void SetSize(etk::DimensionalUnit u) { mSize = u; } 
	DimensionalUnit GetSize(void) const { return mSize; }

	void SetColor(etk::Color c) { mColor = c; }

	etk::Color GetColor(void) const { return mColor; }


protected:
	void SetAdvance(unsigned int adv) { mAdvance = adv; }
	void SetGlyphWidth(unsigned  w) { mGlyphWidth = w; }
	void SetGlyphHeight(unsigned int h) { mGlyphHeight = h; }
	void SetBearingX(int x) { mBearingX = x;  }
	void SetBearingY(int y) { mBearingY = y; }

private:
	unsigned int mAdvance{ 0 };
	unsigned int mGlyphWidth{ 0 };
	unsigned int mGlyphHeight{ 0 };
	int mBearingX{ 0 };
	int mBearingY{ 0 };

	Color mColor{ etk::colors::BLACK };
	DimensionalUnit mSize;
};
}
}