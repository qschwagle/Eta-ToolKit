#include "application.h"

#include <GLFW/glfw3.h>

#include <exception>
#include <iostream>
#include <chrono>

void etk::Application::Init(int argc, char** argv)
{
	if (!glfwInit())
		throw std::exception("Could not init glfw");
	for (auto& i : mWindows) {
		i->Init();
	}
	mInitialized = true;

}

int etk::Application::Run(void)
{
	while (true) {
		std::vector<int> toBeRemoved;
		int counter = 0;
		for (auto& i : mWindows) {
			if (!i->Run()) {
				toBeRemoved.push_back(counter);
			}
			counter++;
		}
		counter = 0;
		for (auto i : toBeRemoved) {
			mWindows.erase(mWindows.begin() + (i-counter));
			counter++;
		}
		if (!mWindows.size()) {
			return 0;
		}

	}
	return 0;
}


std::weak_ptr<etk::Window> etk::Application::CreateAppWindow(const std::string title, long width, long height)
{
	std::shared_ptr<Window> win = std::make_shared<Window>(mFreeId, title, width, height);
	mWindows.push_back(win);
	return win;
}

etk::Application::~Application()
{
	if (mInitialized) glfwTerminate();
}
