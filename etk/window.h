#pragma once

#include <string>
#include <vector>
#include <memory>

#include "widgets/scene.h"
#include "renderer/generic/drawable_factory.h"
#include "renderer/opengl/gl_factory.h"

#include "renderer/generic/window_background.h"

#include "renderer/generic/screen_box.h"

struct GLFWwindow;

namespace etk {
class Window : public std::enable_shared_from_this<Window> {
public:
	Window(int id, std::string title = "", long width = 1920, long height = 1080, std::shared_ptr<etk::renderer::DrawableFactory> factory = std::shared_ptr<etk::renderer::opengl::GLFactory>());
	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;
	~Window();
	void Init();
	long GetHeight() const { return mHeight;  }
	void SetHeight(const long height) { mHeight = height;  }
	long GetWidth() const { return mWidth;  }
	void SetWidth(const long width) { mWidth = width;  }
	void SetColor(etk::Color color);
	void PollEvents();
	void WaitEvents();
	void WaitEventsTimeout(double timeout);
	void PostEmptyEvent();
	const std::string& GetTitle() const { return mTitle;  }
	void SetTitle(const std::string title) { mTitle = title; }
	bool Run();
	void MarkToClose();

	void SetScene(std::shared_ptr<Scene> scene) {
		scene->SetDrawableFactory(mDrawableFactory);
		scene->SetWindow(shared_from_this());
		mScene = scene;
	}

	void ScheduleFunc(std::function<bool()> func) {
		mScheduler->Schedule(func);
	}

	void FrameBufferChanged(int width, int height);

	void ContentScaleChanged(float xScale, float yScale);

	void ScrollCallback(glm::vec2 point, float xOffset, float yOffset) {
		const auto height = mDrawableFactory->GetContext().lock()->GetHeight();
		if (mScene) mScene->OnScroll(glm::vec2(point.x, height+point.y), xOffset, yOffset);
	}

	void LeftMouseButtonClicked(float x, float y) {
		if(mScene) mScene->OnLeftClick(x, y);
	}

	void RightMouseButtonClicked(float x, float y) {
		if (mScene) mScene->OnRightClick(x, y);
	}

	const std::weak_ptr<etk::renderer::ScreenBox> GetBox() const {
		return mBox;
	}

	Color GetColor(void) const {
		return mBackgroundColor;

	}

private:
	const int mId;
	GLFWwindow* mWin{ nullptr };
	long mHeight;
	long mWidth;
	std::shared_ptr<etk::renderer::ScreenBox> mBox;
	std::string mTitle;
	std::shared_ptr<renderer::DrawableFactory> mDrawableFactory{ nullptr };
	std::shared_ptr<etk::Scene> mScene;
	std::unique_ptr<etk::renderer::WindowBackground> mBackground;
	std::shared_ptr<etk::renderer::UIThreadScheduler> mScheduler;

	bool mInitialized{ false };
	Color mBackgroundColor;
};

}