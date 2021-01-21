#pragma once

#include "../rectangle.h"

namespace etk {
namespace renderer {
namespace opengl {
class GLRectangle : public etk::renderer::Rectangle {
public:
	GLRectangle(std::weak_ptr<DrawableContext> context) : Rectangle(context) {}
	void Draw() override;
};
}
}
}