#pragma once

#include "dimensional_unit.h"
#include "../color.h"

#include <array>

namespace etk {
/// <summary>
/// A Style for a widget.
/// 
/// Contains all styling information required for a widget
/// </summary>
class Style {
public:
	Style(void) {}
	struct BorderEdge {
		BorderEdge() : width{ 0 }, color{ colors::BLUE } {}
		const DimensionalUnit width;
		const Color color;
	};

	const Color& GetBackgroundColor(void) const {
		return mBackgroundColor;
	}

	glm::vec2 GetPixelDimensions() {
		glm::vec2 dims{ mDimensions[0].GetPixels(0, 0,0,0), mDimensions[1].GetPixels(0,0,0,0) };
		return dims;
	}
	glm::vec2 GetPixelPos() {
		glm::vec2 dims{ mPos[0].GetPixels(0, 0,0,0), mPos[1].GetPixels(0,0,0,0) };
		return dims;
	}

	void SetPos(DimensionalUnit x, DimensionalUnit y) {
		mPos[0] = x;
		mPos[1] = y;
	}

	glm::vec4 GetPixelMargin() {
		glm::vec4 dims{ mMargin[0].GetPixels(0, 0,0,0), mMargin[1].GetPixels(0,0,0,0), mMargin[2].GetPixels(0, 0,0,0), mMargin[3].GetPixels(0, 0,0,0) };
		return dims;
	}

	void SetMargin(DimensionalUnit top, DimensionalUnit right, DimensionalUnit bottom, DimensionalUnit left) {
		mMargin[0] = top;
		mMargin[1] = right;
		mMargin[2] = bottom;
		mMargin[3] = left;
	}

	glm::vec4 GetPixelPadding() {
		glm::vec4 dims{ mPadding[0].GetPixels(0, 0,0,0), mPadding[1].GetPixels(0,0,0,0), mPadding[2].GetPixels(0, 0,0,0), mPadding[3].GetPixels(0, 0,0,0) };
		return dims;
	}

	void SetPadding(DimensionalUnit top, DimensionalUnit right, DimensionalUnit bottom, DimensionalUnit left) {
		mPadding[0] = top;
		mPadding[1] = right;
		mPadding[2] = bottom;
		mPadding[3] = left;
	}
private:

	/// <summary>
	/// background color
	/// </summary>
	Color mBackgroundColor{ colors::BLUE };

	/// <summary>
	/// The width and height of the widget
	/// </summary>
	std::array<DimensionalUnit, 2> mDimensions;

	/// <summary>
	/// The max width and height of the widget
	/// </summary>
	std::array<DimensionalUnit, 2> mMaxDimensions;

	/// <summary>
	/// The min width and height of the widget
	/// </summary>
	std::array<DimensionalUnit, 2> mMinDimensions;

	/// <summary>
	/// the x and y position (top left corner) of the widget
	/// </summary>
	std::array<DimensionalUnit, 2> mPos{ PixelUnit(0), PixelUnit(0) };

	/// <summary>
	/// margin in the box
	/// </summary>
	std::array<DimensionalUnit, 4> mMargin{ PixelUnit(0), PixelUnit(0), PixelUnit(0), PixelUnit(0) };

	/// <summary>
	/// Padding around the box 
	/// </summary>
	std::array<DimensionalUnit, 4> mPadding{PixelUnit(0), PixelUnit(0), PixelUnit(0), PixelUnit(0) };

	/// <summary>
	/// 
	/// </summary>
	std::array<BorderEdge, 4> mBorder;

	/// <summary>
	/// Parent style used by this Style. Needs to have co-ownership with the possible widget which owns the parent it
	/// </summary>
	std::shared_ptr<Style> mParent;
};
}