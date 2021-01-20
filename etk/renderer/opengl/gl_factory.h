#pragma once

#include "../drawable_factory.h"

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
};
}
}
}