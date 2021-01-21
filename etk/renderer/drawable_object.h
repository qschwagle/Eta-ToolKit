#pragma once

#include <glm/glm.hpp>

#include "drawable_context.h"

#include <memory>

namespace etk {
namespace renderer {
class DrawableObject {
public:
	DrawableObject(std::weak_ptr<DrawableContext> context) : mContext{ context } {}
	virtual void Draw() = 0;
	const glm::vec2& GetPos(void) const { return mPos; }
	void SetPos(float x, float y) { mPos = glm::vec2(x, y);  }
protected:
	std::weak_ptr<DrawableContext> GetContext() const { return mContext; }

private:
	std::weak_ptr<DrawableContext> mContext;
	glm::vec2 mPos;
};
}
}