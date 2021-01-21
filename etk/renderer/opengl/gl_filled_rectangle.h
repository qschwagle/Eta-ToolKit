#pragma once

#include "../filled_rectangle.h"

namespace etk {
namespace renderer {
namespace opengl {
class GLFilledRectangle : public etk::renderer::FilledRectangle {
public:
	GLFilledRectangle(std::weak_ptr<DrawableContext> context);
	~GLFilledRectangle();
	void Draw() override;
private:
	unsigned int mVAO;
	unsigned int mVBO;
};

}
}
}