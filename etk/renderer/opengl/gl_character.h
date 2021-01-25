#pragma once

#include "../generic/character.h"

#include "gl_object.h"

namespace etk {
namespace renderer {
namespace opengl {
class GLCharacter : public etk::renderer::Character, public GLObject {
public:
	GLCharacter(std::weak_ptr<GLDrawableContext> context);
	virtual ~GLCharacter();
	void Draw(glm::vec2 eye) override;

	void LoadGlyph(unsigned int adv, unsigned int width, unsigned int height, int bearingX, int bearingY, unsigned char* data) override;

	void SetCharacter(wchar_t c) {
		mCharacter = c;
	}
private:
	wchar_t mCharacter{ 0 };

	unsigned int mVBO{ 0 };
	unsigned int mVAO{ 0 };
	unsigned int mTexture{ 0 };
};
}
}
}