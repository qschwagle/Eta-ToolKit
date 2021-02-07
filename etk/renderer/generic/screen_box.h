#pragma once

#include <glm/glm.hpp>

namespace etk {
namespace renderer {
class ScreenBox {
public:
	/// <summary>
	/// Set the position anchor of the box
	/// </summary>
	/// <param name="a"></param>
	void SetPosAnchor(const glm::vec2 a) {
		mPosAnchor = a;
	}

	/// <summary>
	/// Sets the width and height
	/// </summary>
	/// <param name="dim">[width, height]</param>
	void SetDimensions(const glm::vec2 dim) {
		mDimensions = dim;
	}

	/// <summary>
	/// Sets the shift from anchor (down and right)
	/// </summary>
	/// <param name="shift">shift from anchor</param>
	void SetShift(const glm::vec2 shift) {
		mShift = shift;
	}

	void AdjustShift(float x, float y) {
		mShift.x += x;
		mShift.y += y;
	}

	/// <summary>
	/// retrieves the top right left which is the anchor to container screen coordinates (0,0) if at origin
	/// </summary>
	/// <returns>top left corner</returns>
	const glm::vec2& GetPosAnchor(void) const {
		return mPosAnchor;
	}

	/// <summary>
	/// retrieves the dimensions, [width, height]
	/// </summary>
	/// <returns>[width, height]</returns>
	const glm::vec2& GetDimensions(void) const {
		return mDimensions;
	}

	/// <summary>
	/// retrieves the shift of the internal items of the box
	/// </summary>
	/// <returns>the shift</returns>
	const glm::vec2& GetShift(void) const {
		return mShift;
	}

	ScreenBox AmendBox(const ScreenBox& local, const float screenWidth, const float screenHeight) const {
		ScreenBox out;
		out.mPosAnchor = local.mPosAnchor;

		// max width the item can have
		const float maxW = screenWidth - out.mPosAnchor.x;
		// max height the item can have
		const float maxH = screenHeight - out.mPosAnchor.y;

		const float w = maxW > local.mDimensions.x ? local.mDimensions.x : maxW;
		const float h = maxH > local.mDimensions.y ? local.mDimensions.y : maxH;

		out.mDimensions = local.mDimensions;
		out.mShift = this->mShift + local.mShift;
		return out;
	}

private:
	/// <summary>
	/// the position anchor (top left corner)
	/// </summary>
	glm::vec2 mPosAnchor{ 0.0f,0.0f };

	/// <summary>
	/// The width and height of the box.
	/// These measurements are used from the position anchor down and right and must not reach off screen 
	/// </summary>
	glm::vec2 mDimensions{ 0.0f, 0.0f };


	/// <summary>
	/// the shift from the position anchor. down and right
	/// </summary>
	glm::vec2 mShift{ 0.0f, 0.0f };
};
}
}