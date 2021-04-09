#pragma once

#include "../generic/image.h"

#include "gl_object.h"

#include "gl_image_program.h"

namespace etk {
namespace renderer {
namespace opengl {
class GLImage : public etk::renderer::Image, public GLObject {
public:
	GLImage(std::weak_ptr<GLDrawableContext> context);
	virtual ~GLImage();
	void Draw(std::weak_ptr<ScreenBox> box) override;

	void LoadImage(unsigned char* data, int width, int height, int channels) override;

	void SetWidth(int w) override {
		mExWidth = w;
	}

	void SetHeight(int h) override {
		mExHeight = h;
	}
private:
	int mExWidth{ -1 };
	int mExHeight{ -1 };
	int mWidth{ -1 };
	int mHeight{ -1 };
	int mChannels{ -1 };
	unsigned int mTexture;
	unsigned int mVAO;
	unsigned int mVBO;

	GLImageProgram* mProgramCache;
};
}
}
}