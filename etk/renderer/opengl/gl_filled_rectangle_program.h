#pragma once

#include <mutex>

#include "gl_shader_program.h"

namespace etk {
namespace renderer {
namespace opengl {
class GLFilledRectangleProgram {
public:
	static GLFilledRectangleProgram* GetInstance();

	GLShaderProgram& GetProgram() { return mProgram;  }
protected:
	GLFilledRectangleProgram();
	~GLFilledRectangleProgram();
private:
	GLShaderProgram mProgram;


	static GLFilledRectangleProgram* mSelf;
	static std::mutex mLock;
};
}
}
}