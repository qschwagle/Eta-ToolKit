#pragma once 
#include "drawable_object.h"

#include <etk/style/dimensional_unit.h>
#include <etk/color.h>

namespace etk {
namespace renderer {

/// <summary>
/// An individual drawable character.
/// 
/// Meant to be configured by FontRendering::SetCharacter
/// </summary>
class Character : public etk::renderer::DrawableObject {
public:
	/// <summary>
	/// Default constructor used for allocation
	/// </summary>
	Character() = default;

	/// <summary>
	/// Copy Constructor deleted
	/// </summary>
	Character(const Character&) = delete;

	/// <summary>
	/// Assignment Operator deleted
	/// </summary>
	Character& operator=(const Character&) = delete;

	/// <summary>
	/// Deconstructor
	/// </summary>
	virtual ~Character() {}

	/// <summary>
	/// Used by FontRendering to set the provided values
	/// </summary>
	/// <param name="adv">advance to next character</param>
	/// <param name="width">width of character(glyph)</param>
	/// <param name="height">height of character(glyph)</param>
	/// <param name="bearingX">x bearing</param>
	/// <param name="bearingY">y bearing</param>
	/// <param name="data">glyph</param>
	virtual void LoadGlyph(unsigned int adv, unsigned int width, unsigned int height, int bearingX, int bearingY, unsigned char* data) = 0;


	/// <summary>
	/// Get the Advance to next glyph
	/// </summary>
	/// <returns>advance</returns>
	unsigned int GetAdvance(void) const { return mAdvance; }

	/// <summary>
	/// Get the Glyph Width
	/// </summary>
	/// <returns>width</returns>
	unsigned int GetGlyphWidth(void) const { return mGlyphWidth; }

	/// <summary>
	/// Get the Glyph Height
	/// </summary>
	/// <returns>height</returns>
	unsigned int GetGlyphHeight(void) const { return mGlyphHeight; }
	
	/// <summary>
	/// Get the Bearing X (distance from x = 0 to start of glyph)
	/// </summary>
	/// <returns>bearing x</returns>
	int GetBearingX(void) const { return mBearingX; }

	/// <summary>
	/// Get the Bearing Y (distance from y=0 to top of glyph)
	/// </summary>
	/// <returns></returns>
	int GetBearingY(void) const { return mBearingY; }

	/// <summary>
	/// The dimension size (will be converted to Pt) of the glyph
	/// </summary>
	/// <param name="u">pt convertable dimension</param>
	void SetSize(etk::DimensionalUnit u) { mSize = u; } 

	/// <summary>
	/// Get the Dimensional Unit
	/// </summary>
	/// <returns>font size</returns>
	DimensionalUnit GetSize(void) const { return mSize; }

	/// <summary>
	/// Font Color used when drawing
	/// </summary>
	/// <param name="c">new font color</param>
	void SetColor(etk::Color c) { mColor = c; }

	/// <summary>
	/// Retrieve the font color
	/// </summary>
	/// <returns>color</returns>
	etk::Color GetColor(void) const { return mColor; }

protected:
	/// <summary>
	/// Set the advance 
	/// </summary>
	/// <param name="adv">advance</param>
	void SetAdvance(unsigned int adv) { mAdvance = adv; }

	/// <summary>
	/// Set the Glyph width
	/// </summary>
	/// <param name="w">width</param>
	void SetGlyphWidth(unsigned  w) { mGlyphWidth = w; }

	/// <summary>
	/// Set the Glyph height
	/// </summary>
	/// <param name="h">height</param>
	void SetGlyphHeight(unsigned int h) { mGlyphHeight = h; }

	/// <summary>
	/// Set the X Bearing
	/// </summary>
	/// <param name="x">x bearing</param>
	void SetBearingX(int x) { mBearingX = x;  }


	/// <summary>
	/// Set the Y bearing
	/// </summary>
	/// <param name="y">y bearing</param>
	void SetBearingY(int y) { mBearingY = y; }

private:
	/// <summary>
	/// advance to next character
	/// </summary>
	unsigned int mAdvance{ 0 };

	/// <summary>
	/// glyph(character) height
	/// </summary>
	unsigned int mGlyphWidth{ 0 };

	/// <summary>
	/// glyph(character) width
	/// </summary>
	unsigned int mGlyphHeight{ 0 };

	/// <summary>
	/// x bearing 
	/// </summary>
	int mBearingX{ 0 };

	/// <summary>
	/// y bearing
	/// </summary>
	int mBearingY{ 0 };

	/// <summary>
	/// font color
	/// </summary>
	Color mColor{ etk::colors::BLACK };

	/// <summary>
	/// font size
	/// </summary>
	DimensionalUnit mSize;
};
}
}