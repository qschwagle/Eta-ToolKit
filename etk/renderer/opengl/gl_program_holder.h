#pragma once

#include "gl_shader_program.h"

namespace etk {
namespace renderer {
namespace opengl {
class GLProgramHolder {
public:
	GLProgramHolder() {};
	virtual GLShaderProgram* GetProgram() = 0;

	virtual GLint GetProjId() {
		if (mProjId == -1) {
			mProjId = GetProgram()->GetUniformLoc(std::string("proj"));
		}
		return mProjId;
	}
private:
	GLint mProjId{ -1 };
};
}
}
}
