#pragma once

#include "../generic/drawable_factory.h"

#include "gl_drawable_context.h"

#include "etk/font_rendering/book.h"

namespace etk {
namespace renderer {
namespace opengl {
class GLFactory : public etk::renderer::DrawableFactory {
public:
	GLFactory();
	void Init() override;
	std::unique_ptr<Character> CreateCharacter() override;
	std::unique_ptr<FilledRectangle> CreateFilledRectangle() override;
	std::unique_ptr<Image> CreateImage() override;
	std::unique_ptr<Rectangle> CreateRectangle() override;
	std::unique_ptr<Text> CreateText() override;
	std::unique_ptr<WindowBackground> CreateBackground() override;
	std::weak_ptr<DrawableContext> GetContext() override;

protected:
	std::weak_ptr<GLDrawableContext> GetGLDrawableContext() const {
		return mContext;
	}

	void SetContext(std::shared_ptr<GLDrawableContext> context) {
		mContext = context;
	}

private:
	std::shared_ptr<GLDrawableContext> mContext;


};
}
}
}