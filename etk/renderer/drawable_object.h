#pragma once

#include <glm/glm.hpp>

namespace etk {
namespace renderer {
class DrawableObject {
public:
	virtual void Draw() = 0;
	const glm::vec2& GetPos(void) const { return mPos; }
	void SetPos(const glm::vec2& pos) { mPos = pos; }
private:
	glm::vec2 mPos;
};
}
}