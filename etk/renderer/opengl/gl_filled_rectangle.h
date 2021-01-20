#pragma once

#include "../filled_rectangle.h"

namespace etk {
namespace renderer {
namespace opengl {
class GLFilledRectangle : public etk::renderer::FilledRectangle {
public:
	GLFilledRectangle();
	~GLFilledRectangle();
	void Draw() override;
private:
	unsigned int mVAO;
	unsigned int mVBO;
};

}
}
}