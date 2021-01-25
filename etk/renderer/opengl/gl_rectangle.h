#pragma once

#include <memory>

#include "../generic/rectangle.h"

#include "gl_object.h"

namespace etk {
namespace renderer {
namespace opengl {
class GLRectangle : public etk::renderer::Rectangle, public GLObject {
public:
	GLRectangle(std::weak_ptr<GLDrawableContext> context) : GLObject(context) {}
	void Draw(glm::vec2 eye) override;
};
}
}
}