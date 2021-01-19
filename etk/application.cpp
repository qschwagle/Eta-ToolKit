#include "application.h"

#include <GLFW/glfw3.h>

#include <exception>

#include "RunOnUIThread.h"

void etk::Application::Init(int argc, char** argv)
{
	if (!glfwInit())
		throw std::exception("Could not init glfw");
	for (auto& i : mWindows) {
		i.second->Init();
	}
	mInitialized = true;
}

int etk::Application::Run(void)
{
	while (true) {
		RunOnUIThread* thread = RunOnUIThread::GetInstance();
		thread->Execute();
		std::vector<int> toBeRemoved;
		for (auto& i : mWindows) {
			if (!i.second->Run()) {
				toBeRemoved.push_back(i.first);
			}
		}
		for (auto i : toBeRemoved) {
			auto found = mWindows.find(i);
			if (found != mWindows.end()) {
				mWindows.erase(found);
			}
		}
		if (!mWindows.size()) {
			return 0;
		}
	}
	return 0;
}


int etk::Application::CreateWindow(const std::string title, long width, long height)
{
	auto win = std::make_unique<Window>(mFreeId, title, width, height);
	mWindows.insert(std::pair(mFreeId, std::move(win)));
	int used = mFreeId;
	mFreeId++;
	return used;
}

etk::Window* etk::Application::GetWindow(int id) {
	auto found = mWindows.find(id);
	if (found != mWindows.end()) {
		return found->second.get();
	}
	return nullptr;
}

etk::Application::~Application()
{
	if (mInitialized) glfwTerminate();
}
