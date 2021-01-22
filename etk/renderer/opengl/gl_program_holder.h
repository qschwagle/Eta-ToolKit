#pragma once

#include "gl_shader_program.h"

namespace etk {
namespace renderer {
namespace opengl {
class GLProgramHolder {
public:
	GLProgramHolder() {};
	virtual GLShaderProgram* GetProgram() = 0;
private:
};
}
}
}
