#pragma once

#include <functional>

#include "ui_action.h"

namespace etk {
namespace renderer {
class UIActionFunc : public UIAction {
public:
	UIActionFunc(std::function<bool()> action) {
		mFunc = action;
	}

	bool Run(void) override {
		return mFunc();
	}
private:
	std::function<bool()> mFunc;
};
}
}