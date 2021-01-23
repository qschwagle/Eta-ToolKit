#pragma once

#include "../character.h"

#include "gl_object.h"

namespace etk {
namespace renderer {
namespace opengl {
class GLCharacter : public etk::renderer::Character, public GLObject {
public:
	GLCharacter(std::weak_ptr<GLDrawableContext> context);
	~GLCharacter();
	void Draw() override;

	void SetCharacter(wchar_t c) {
		mCharacter = c;
	}
private:
	wchar_t mCharacter{ 0 };
};
}
}
}