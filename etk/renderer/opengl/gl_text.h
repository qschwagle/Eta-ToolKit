#pragma once

#include "../text.h"

namespace etk {
namespace renderer {
namespace opengl {
class GLText : public etk::renderer::Text {
public:
	GLText(std::weak_ptr<DrawableContext> context) : Text(context) {}
	void Draw() override;

};
}
}
}