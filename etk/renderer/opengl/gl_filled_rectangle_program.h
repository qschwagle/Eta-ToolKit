#pragma once

#include <memory>
#include <string>

#include "gl_shader_program.h"

#include "gl_program_holder.h"

#include "gl_object.h"

namespace etk {
namespace renderer {
namespace opengl {
class GLFilledRectangleProgram : public etk::renderer::opengl::GLProgramHolder, public GLObject {
public:
	GLFilledRectangleProgram(std::weak_ptr<GLDrawableContext> context);
	~GLFilledRectangleProgram();

	inline static std::wstring GetId() {
		return L"GL_FILLED_RECTANGLE_PROGRAM";
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