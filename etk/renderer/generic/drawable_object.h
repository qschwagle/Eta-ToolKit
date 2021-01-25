#pragma once

#include <glm/glm.hpp>

#include "drawable_context.h"

#include <memory>

namespace etk {
namespace renderer {
class DrawableObject {
public:
	DrawableObject()=default;
	virtual ~DrawableObject() {}
	virtual void Draw(glm::vec2 eye) = 0;
	const glm::vec2& GetPos(void) const { return mPos; }
	void SetPos(float x, float y) { mPos = glm::vec2(x, y);  }
private:
	glm::vec2 mPos{ 0.0f,0.0f };
};
}
}