#pragma once

#include "../generic/character.h"
#include "gl_object.h"
#include <array>

namespace etk {
namespace renderer {
namespace opengl {
/// <summary>
/// A GLCharacter drawable object which draws the provided character using the static position and dynamic eye
/// </summary>
class GLCharacter : public etk::renderer::Character, public GLObject {
public:
	GLCharacter(std::weak_ptr<GLDrawableContext> context);
	virtual ~GLCharacter();
	void Draw(std::weak_ptr<ScreenBox> box) override;

	void LoadGlyph(unsigned int adv, unsigned int width, unsigned int height, int bearingX, int bearingY, unsigned char* data) override;

	/// <summary>
	/// Sets the character c
	/// </summary>
	/// <param name="c">character shown by GLCharacter</param>
	void SetCharacter(wchar_t c) {
		mCharacter = c;
	}

	/// <summary>
	/// Sets the Position and Generates the Vertices for the given position
	/// </summary>
	/// <param name="x">x position</param>
	/// <param name="y">y position</param>
	void SetPos(float x, float y) override {
		DrawableObject::SetPos(x, y);
		GenerateVertices();
	}

private:
	void GenerateVertices();

	/// <summary>
	/// character being drawn
	/// </summary>
	wchar_t mCharacter{ 0 };

	/// <summary>
	/// vertices drawn
	/// </summary>
	std::array<float, 24> mVertices;

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
};
}
}
}