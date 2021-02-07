#pragma once

#include <glm/glm.hpp>

#include "drawable_context.h"

#include "screen_box.h"

#include <memory>

namespace etk {
namespace renderer {
class DrawableObject {
public:
	DrawableObject()=default;
	virtual ~DrawableObject() {}
	virtual void Draw(std::weak_ptr<ScreenBox> box) {}
	const glm::vec2& GetPos(void) const { return mPos; }
	virtual void SetPos(float x, float y) { mPos = glm::vec2(x, y);  }
private:
	glm::vec2 mPos{ 0.0f,0.0f };
};
}
}