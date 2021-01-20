#pragma once

#include <glm/glm.hpp>

namespace etk {
class Widget {
public:
	Widget() = default;
	Widget(const Widget&) = delete;
	Widget& operator=(const Widget&) = delete;

	virtual void Draw() {}

	void SetPosition(const glm::vec2 pos)
	{
		mPos = pos;
	}

	const glm::vec2& GetPosition(void) const
	{
		return mPos;
	}

	void SetMargin(const glm::vec4 margin) 
	{
		mMargin = margin;
	}

	const glm::vec4& GetMargin() const
	{
		return mMargin;
	}

	void SetPadding(const glm::vec4 padding)
	{
		mPadding = padding;
	}

	const glm::vec4& GetPadding() const 
	{
		return mMargin;
	}

	/// <summary>
	/// Internal Width + border + margin + padding
	/// </summary>
	/// <returns></returns>
	float GetExternalWidth() const {
		float width = mPadding[3] + mPadding[1] + mMargin[1] + mMargin[3] + mInternalWidth;
		// branchless version: does not use mBorder->GetWidth() if mBorder is nullptr
		mBorder && (width += mBorder->GetWidth());
		return width;
	}

	/// <summary>
	/// Internal Height + border + margin + padding
	/// </summary>
	/// <returns></returns>
	float GetExternalHeight() const {
		float height = mPadding[0] + mPadding[2] + mMargin[0] + mMargin[2] + mInternalHeight;
		// branchless version: does not use mBorder->GetWidth() if mBorder is nullptr
		mBorder && (height += mBorder->GetWidth());
		return height;
	}

	class Border {
	public:
		float GetWidth() const {
			return 0;
		}
	private:
	};

protected:
	/// <summary>
	/// The internal width of the object
	/// </summary>
	/// <param name="width"></param>
	void SetInternalWidth(float width) {
		mInternalWidth = width;
	}

	/// <summary>
	/// the internal height of the object
	/// </summary>
	/// <param name="height"></param>
	void SetInternalHeight(float height) {
		mInternalHeight = height;
	}

private:
	float mInternalWidth{ 0.0f };
	float mInternalHeight{ 0.0f };
	/// <summary>
	/// position of the box
	/// </summary>
	glm::vec2 mPos{ 0.0f, 0.0f };

	/// <summary>
	/// margin in the box
	/// </summary>
	glm::vec4 mMargin{ 0.0f, 0.0f, 0.0f, 0.0f };

	/// <summary>
	/// Padding around the box 
	/// </summary>
	glm::vec4 mPadding{ 0.0f, 0.0f, 0.0f, 0.0f };

	/// <summary>
	/// border
	/// </summary>
	std::unique_ptr<Border> mBorder{ nullptr };
};
}