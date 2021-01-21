#pragma once

#include "../image.h"

namespace etk {
namespace renderer {
namespace opengl {
class GLImage : public etk::renderer::Image {
public:
	GLImage(std::weak_ptr<DrawableContext> context) : etk::renderer::Image(context) {}
	void Draw() override;

};
}
}
}