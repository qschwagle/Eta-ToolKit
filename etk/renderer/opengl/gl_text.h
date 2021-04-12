#pragma once

#include "../generic/text.h"

#include "gl_object.h"

#include <vector>

#include "etk/font_rendering/glyph.h"

#include "etk/renderer/opengl/gl_character_program.h"

namespace etk {
namespace renderer {
namespace opengl {
class GLText : public etk::renderer::Text, public GLObject {
public:
	GLText(std::weak_ptr<GLDrawableContext> context) : GLObject(context) {}
	~GLText();

	void UpdateText(const std::wstring& text) override;
	void UpdateColor() override;
	void UpdatePosition() override;
	void Draw(std::weak_ptr<ScreenBox> box) noexcept override;

private:
	std::vector<std::shared_ptr<etk::renderer::opengl::GLCharacter>> mGLText;
	std::vector<etk::font_rendering::FontGlyph*> mGlyphs;

	/// <summary>
	/// Vertex Buffer Object
	/// </summary>
	unsigned int mVBO{ 0 };

	/// <summary>
	/// Vertex Array Object
	/// </summary>
	unsigned int mVAO{ 0 };

	/// <summary>
	/// Texture
	/// </summary>
	unsigned int mTexture{ 0 };

	etk::renderer::opengl::GLCharacterProgram* mProgramCache{ nullptr };

	std::vector<float> mBlockCache;
};
}
}
}