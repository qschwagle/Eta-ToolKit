#pragma once

#include "../generic/image.h"

#include "gl_object.h"

namespace etk {
namespace renderer {
namespace opengl {
class GLImage : public etk::renderer::Image, public GLObject {
public:
	GLImage(std::weak_ptr<GLDrawableContext> context);
	virtual ~GLImage();
	void Draw(glm::vec2 eye) override;

	void LoadImage(unsigned char* data, int width, int height, int channels) override;
private:
	int mWidth{ -1 };
	int mHeight{ -1 };
	int mChannels{ -1 };
	unsigned int mTexture;
	unsigned int mVAO;
	unsigned int mVBO;
};
}
}
}