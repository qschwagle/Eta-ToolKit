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
	virtual std::unique_ptr<Character> CreateCharacter() = 0;
	virtual std::unique_ptr<FilledRectangle> CreateFilledRectangle() = 0;
	virtual std::unique_ptr<Image> CreateImage() = 0;
	virtual std::unique_ptr<Rectangle> CreateRectangle() = 0;
	virtual std::unique_ptr<Text> CreateText() = 0;
	virtual std::unique_ptr<WindowBackground> CreateBackground() = 0;
};
}
}