#pragma once

#include "../generic/drawable_context.h"

#include "gl_program_holder.h"

#include<memory>

#include "etk/font_rendering/book.h"


namespace etk {
namespace renderer {
namespace opengl {
class GLCharacter;
class GLDrawableContext : public etk::renderer::DrawableContext, public std::enable_shared_from_this<GLDrawableContext> {
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

	std::shared_ptr<etk::renderer::opengl::GLCharacter> GetCharacter();

	etk::font_rendering::FontBook* GetFontBook() {
		return mFontBook.get();
	}

private:
	std::unordered_map <std::wstring, std::shared_ptr<GLProgramHolder>> mGLProgramHolders;

	std::unique_ptr<etk::font_rendering::FontBook> mFontBook;
};
}
}
}
