#pragma once

#include <string>
#include <vector>

#include "renderer/drawable_factory.h"

struct GLFWwindow;

namespace etk {
class Window {
public:
	Window(int id, std::string title="", long width = 1920, long height = 1080) : mId{ id }, mWidth{ width }, mHeight{ height }, mTitle{ title } {}
	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;
	~Window();
	void Init();
	long GetHeight() const { return mHeight;  }
	void SetHeight(const long height) { mHeight = height;  }
	long GetWidth() const { return mWidth;  }
	void SetWidth(const long width) { mWidth = width;  }
	const std::string& GetTitle() const { return mTitle;  }
	void SetTitle(const std::string title) { mTitle = title; }
	bool Run();
	void MarkToClose();

private:
	const int mId;
	GLFWwindow* mWin{ nullptr };
	long mHeight;
	long mWidth;
	std::string mTitle;
	std::unique_ptr<renderer::DrawableFactory> mDrawableFactory{ nullptr };
};
}