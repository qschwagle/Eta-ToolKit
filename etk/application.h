#pragma once

#include <string>
#include <unordered_map>
#include <memory>

#include "window.h"

namespace etk {

class Application {
public:
	Application() = default;
	Application(const Application&) = delete;
	Application& operator=(const Application&) = delete;
	~Application();
	void Init(int argc, char** argv);
	int Run(void);


	int CreateAppWindow(const std::string title="", long width = 1920, long height = 1080);

	Window* GetWindow(int id);
private:
	std::unordered_map<int, std::unique_ptr<Window>> mWindows;
	int mFreeId{ 0 };
	bool mInitialized{ false };
};
}

// vim:set sw=4 ts=4 et: