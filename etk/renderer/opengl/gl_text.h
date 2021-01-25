#pragma once

#include "../generic/text.h"

#include "gl_object.h"

#include <vector>

namespace etk {
namespace renderer {
namespace opengl {
class GLText : public etk::renderer::Text, public GLObject {
public:
	GLText(std::weak_ptr<GLDrawableContext> context) : GLObject(context) {}

	void SetText(std::wstring text) override;
	void Draw(glm::vec2 eye) override;

private:
	std::vector<std::shared_ptr<etk::renderer::opengl::GLCharacter>> mGLText;
	std::wstring mText;
};
}
}
}