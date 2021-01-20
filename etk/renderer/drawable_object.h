#pragma once

#include <glm/glm.hpp>

namespace etk {
namespace renderer {
class DrawableObject {
public:
	DrawableObject() = default;
	virtual void Draw() = 0;
	const glm::vec2& GetPos(void) const { return mPos; }
	void SetPos(float x, float y) { mPos = glm::vec2(x, y);  }
private:
	glm::vec2 mPos;
};
}
}