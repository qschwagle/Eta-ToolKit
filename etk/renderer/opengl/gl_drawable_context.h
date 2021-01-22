#pragma once

#include "../drawable_context.h"

#include "gl_program_holder.h"


#include<memory>

namespace etk {
namespace renderer {
namespace opengl {
class GLDrawableContext : public etk::renderer::DrawableContext {
public:
	GLDrawableContext();
	void WindowInit(int width, int height) override;
	void Init() override;
	void Clear() override;

	void SetProgram(std::wstring id, std::shared_ptr<GLProgramHolder> program)
	{
		mGLProgramHolders.insert_or_assign(id, program);
	}

	std::weak_ptr<GLProgramHolder> GetProgramHolder(std::wstring id)
	{
		auto program = mGLProgramHolders.find(id);
		if (program != mGLProgramHolders.end()) {
			return program->second;
		}
		else {
			return std::weak_ptr<GLProgramHolder>();
		}
	}

	void UpdateDimensions(const int width, const int height) override;

private:
	std::unordered_map <std::wstring, std::shared_ptr<GLProgramHolder>> mGLProgramHolders;
};
}
}
}
