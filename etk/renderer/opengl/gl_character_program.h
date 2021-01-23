#pragma once

#include <memory>
#include <string>

#include "gl_shader_program.h"

#include "gl_program_holder.h"

#include "gl_object.h"

namespace etk {
namespace renderer {
namespace opengl {
class GLCharacterProgram: public etk::renderer::opengl::GLProgramHolder, public GLObject {
public:
	GLCharacterProgram(std::weak_ptr<GLDrawableContext> context);
	~GLCharacterProgram();
	inline static std::wstring GetId() {
		return L"GL_CHARACTER_PROGRAM";
	}

	GLShaderProgram* GetProgram() override {
		return &mProgram;
	}

private:
	GLShaderProgram mProgram;
};
}
}
}