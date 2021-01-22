#pragma once

#include "../image.h"

#include "gl_object.h"

namespace etk {
namespace renderer {
namespace opengl {
class GLImage : public etk::renderer::Image, public GLObject {
public:
	GLImage(std::weak_ptr<GLDrawableContext> context) : GLObject(context) {}
	void Draw() override;

};
}
}
}