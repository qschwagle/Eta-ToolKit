#pragma once

#include <string>
#include <vector>
#include <memory>

#include "scene.h"
#include "renderer/drawable_factory.h"
#include "renderer/opengl/gl_factory.h"

struct GLFWwindow;

namespace etk {
class Window {
public:
	Window(int id,  std::string title="", long width = 1920, long height = 1080, std::shared_ptr<etk::renderer::DrawableFactory> factory=std::make_shared<etk::renderer::opengl::GLFactory>()) : 
		mId{ id }, 
		mWidth{ width }, 
		mHeight{ height }, 
		mTitle{ title },
		mDrawableFactory{ factory } {}
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

	void SetScene(std::shared_ptr<Scene> scene) {
		mScene = scene;
	}

private:
	const int mId;
	GLFWwindow* mWin{ nullptr };
	long mHeight;
	long mWidth;
	std::string mTitle;
	std::shared_ptr<renderer::DrawableFactory> mDrawableFactory{ nullptr };
	std::shared_ptr<etk::Scene> mScene;
};
}