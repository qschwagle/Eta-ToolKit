#pragma once

#include "../rectangle.h"

#include "gl_object.h"

namespace etk {
namespace renderer {
namespace opengl {
class GLRectangle : public etk::renderer::Rectangle, public GLObject {
public:
	GLRectangle(std::weak_ptr<GLDrawableContext> context) : GLObject(context) {}
	void Draw() override;
};
}
}
}