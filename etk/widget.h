#pragma once

#include <glm/glm.hpp>

namespace etk {
class Widget {
public:
	Widget() = default;
	Widget(const Widget&) = delete;
	Widget& operator=(const Widget&) = delete;

	virtual void Draw() {}

private:
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
};
}