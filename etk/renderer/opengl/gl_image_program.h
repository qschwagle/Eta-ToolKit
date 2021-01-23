#pragma once

#include "gl_object.h"

#include "gl_shader_program.h"

namespace etk {
namespace renderer {
namespace opengl {
class GLImageProgram : public etk::renderer::opengl::GLProgramHolder, public GLObject {
public:
	GLImageProgram(std::weak_ptr<GLDrawableContext> context);
	virtual ~GLImageProgram() = default;

	inline static std::wstring GetId() {
		return L"GL_IMAGE_PROGRAM";
	}

	GLShaderProgram* GetProgram() override {
		return &mProgram;
	}

private:
	GLShaderProgram mProgram;
private:
};
}
}
}