#pragma once

#include "../text.h"

#include "gl_object.h"

namespace etk {
namespace renderer {
namespace opengl {
class GLText : public etk::renderer::Text, public GLObject {
public:
	GLText(std::weak_ptr<GLDrawableContext> context) : GLObject(context) {}
	void Draw() override;

};
}
}
}