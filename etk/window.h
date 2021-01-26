#pragma once

#include <string>
#include <vector>
#include <memory>

#include "widgets/scene.h"
#include "renderer/generic/drawable_factory.h"
#include "renderer/opengl/gl_factory.h"

#include "renderer/generic/window_background.h"

struct GLFWwindow;

namespace etk {
class Window {
public:
	Window(int id, std::string title = "", long width = 1920, long height = 1080, std::shared_ptr<etk::renderer::DrawableFactory> factory = std::make_shared<etk::renderer::opengl::GLFactory>());
	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;
	~Window();
	void Init();
	long GetHeight() const { return mHeight;  }
	void SetHeight(const long height) { mHeight = height;  }
	long GetWidth() const { return mWidth;  }
	void SetWidth(const long width) { mWidth = width;  }
	void SetColor(etk::Color color);
	const std::string& GetTitle() const { return mTitle;  }
	void SetTitle(const std::string title) { mTitle = title; }
	bool Run();
	void MarkToClose();

	void SetScene(std::shared_ptr<Scene> scene) {
		mScene = scene;
		scene->SetDrawableFactory(mDrawableFactory);
		if (mInitialized) scene->Init();
	}

	void ScheduleFunc(std::function<bool()> func) {
		auto sched = mDrawableFactory->GetUIScheduler();
		sched.lock()->Schedule(func);
	}

	void FrameBufferChanged(int width, int height);

	void ContentScaleChanged(float xScale, float yScale);

	void ScrollCallback(glm::vec2 point, float xOffset, float yOffset) {
		const auto height = mDrawableFactory->GetContext().lock()->GetHeight();
		if (mScene) mScene->OnScroll(glm::vec2(point.x, height+point.y), xOffset, yOffset);
	}

	const glm::vec2& GetEye() const {
		return mEye;
	}

	void LeftMouseButtonClicked(float x, float y) {
		if(mScene) mScene->OnLeftClick(x, y);
	}

	void RightMouseButtonClicked(float x, float y) {
		if (mScene) mScene->OnRightClick(x, y);
	}

private:
	const int mId;
	GLFWwindow* mWin{ nullptr };
	long mHeight;
	long mWidth;
	std::string mTitle;
	std::shared_ptr<renderer::DrawableFactory> mDrawableFactory{ nullptr };
	std::shared_ptr<etk::Scene> mScene;
	std::unique_ptr<etk::renderer::WindowBackground> mBackground;

	bool mInitialized{ false };
	glm::vec2 mEye{ 0.0f,0.0f };
};

}