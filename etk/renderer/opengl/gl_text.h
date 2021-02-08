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

	void UpdateText(const std::wstring& text) override;
	void Draw(std::weak_ptr<ScreenBox> box) override;

private:
	std::vector<std::shared_ptr<etk::renderer::opengl::GLCharacter>> mGLText;
};
}
}
}