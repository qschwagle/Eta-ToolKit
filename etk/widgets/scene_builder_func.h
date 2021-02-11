#pragma once

#include "scene_builder.h"

#include <functional>

namespace etk {
class SceneBuilderFunction : public SceneBuilder {
public:
	void SetFunction(std::function <std::shared_ptr<Scene>()> f) {
		mFunc = f;
	}

	std::shared_ptr<Scene> CreateScene() override {
		return mFunc();
	}

private:
	std::function <std::shared_ptr<Scene>()> mFunc;
};
}