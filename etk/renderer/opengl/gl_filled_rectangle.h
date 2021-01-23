#pragma once

#include "../generic/filled_rectangle.h"

#include "gl_object.h"

namespace etk {
namespace renderer {
namespace opengl {
class GLFilledRectangle : public etk::renderer::FilledRectangle, public  GLObject {
public:
	GLFilledRectangle(std::weak_ptr<GLDrawableContext> context);
	virtual ~GLFilledRectangle();
	void Draw() override;
private:
	unsigned int mVAO;
	unsigned int mVBO;
};

}
}
}