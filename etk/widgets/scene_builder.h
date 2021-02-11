#pragma once

#include "scene.h"

namespace etk {
class SceneBuilder {
public:
	SceneBuilder() = default;

	virtual std::shared_ptr<Scene> CreateScene() { return nullptr;  }
private:
};
}