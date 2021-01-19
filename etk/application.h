#pragma once

#include <glm/glm.hpp>

namespace etk {
class Application {
public:
	Application() = default;
	Application(const Application&) = delete;
	Application& operator=(const Application&) = delete;

	void Init(int argc, char** argv);

	int Run(void);


private:
};
}

// vim:set sw=4 ts=4 et: