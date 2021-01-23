#pragma once

#include "widget.h"

#include "../renderer/generic/rectangle.h"

namespace etk {
class Button : public Widget {
public:
	void Draw() override;

	void Invalidate() override {
		mBackgroundRenderer = nullptr;
	}
private:
	std::unique_ptr<etk::renderer::FilledRectangle> mBackgroundRenderer{ nullptr };
};
}