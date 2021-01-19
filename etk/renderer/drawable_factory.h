#pragma once

#include <memory>

#include "character.h"
#include "filled_rectangle.h"
#include "image.h"
#include "rectangle.h"
#include "text.h"

#include "window_background.h"

namespace etk {
namespace renderer {
class DrawableFactory {
public:
	DrawableFactory() {};
	DrawableFactory(const DrawableFactory&) = delete;
	DrawableFactory& operator=(const DrawableFactory&) = delete;

	virtual void Init() = 0;
	virtual std::unique_ptr<Character> createCharacter() = 0;
	virtual std::unique_ptr<FilledRectangle> createFilledRectangle() = 0;
	virtual std::unique_ptr<Image> createImage() = 0;
	virtual std::unique_ptr<Rectangle> createRectangle() = 0;
	virtual std::unique_ptr<Text> createText() = 0;
	virtual std::unique_ptr<WindowBackground> createBackground() = 0;
};
}
}