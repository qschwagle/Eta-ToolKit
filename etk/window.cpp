#include "window.h"

#include "GLFW/glfw3.h"

#include <exception>
#include <iostream>

static void glfw_on_scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	etk::Window* win = static_cast<etk::Window*>(glfwGetWindowUserPointer(window));
	double x;
	double y;
	glfwGetCursorPos(window, &x, &y);
	win->ScrollCallback(glm::vec2(static_cast<float>(x), static_cast<float>(y)), xoffset, yoffset);

}

static void glfw_mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	etk::Window* win = static_cast<etk::Window*>(glfwGetWindowUserPointer(window));
	double x;
	double y;
	glfwGetCursorPos(window, &x, &y);

	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) {
		win->RightMouseButtonClicked(x, y);
	} if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
		win->LeftMouseButtonClicked(x, y);
	}
}


static void glfw_framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	etk::Window* win = static_cast<etk::Window*>(glfwGetWindowUserPointer(window));
	win->FrameBufferChanged(width, height);
}

static void glfw_content_scale_changed_callback(GLFWwindow* window, float xScale, float yScale)
{
	etk::Window* win = static_cast<etk::Window*>(glfwGetWindowUserPointer(window));
	win->ContentScaleChanged(xScale, yScale);
}

etk::Window::Window(int id, std::string title, long width, long height, std::shared_ptr<etk::renderer::DrawableFactory> factory) :
	mId{ id },
	mWidth{ width },
	mHeight{ height },
	mTitle{ title },
	mDrawableFactory{ factory },
	mBackgroundColor{colors::WHITE},
	mScheduler{ std::make_shared<etk::renderer::UIThreadScheduler>()}
{
	mBox = nullptr;
	mBackground = nullptr;
}

void etk::Window::Init() 
{
	mDrawableFactory = std::make_shared<etk::renderer::opengl::GLFactory>();
	mBox = mDrawableFactory->GetContext().lock()->GetScreenBox();
	mBackground = mDrawableFactory->CreateBackground();
	mBackground->SetColor(mBackgroundColor);
	auto context = mDrawableFactory->GetContext().lock();
	context->WindowInit(GetWidth(), GetHeight());
	mWin = glfwCreateWindow(GetWidth(), GetHeight(), mTitle.c_str(), nullptr, nullptr);
	if (!mWin) {
		throw std::exception("Could not create window");
	}
	glfwMakeContextCurrent(mWin);
	glfwSetWindowUserPointer(mWin, this);
	glfwSetFramebufferSizeCallback(mWin, glfw_framebuffer_size_callback);
	glfwSetScrollCallback(mWin, glfw_on_scroll_callback);
	glfwSetMouseButtonCallback(mWin, glfw_mouse_button_callback);

	float xScale;
	float yScale;
	glfwGetWindowContentScale(mWin, &xScale, &yScale);
	context->UpdateContentScale(xScale, yScale);
	context->Init();
	if (mScene) mScene->SetDrawableFactory(mDrawableFactory);
	mInitialized = true;
}

void etk::Window::MarkToClose()
{
	glfwSetWindowShouldClose(mWin, true);
}

void etk::Window::FrameBufferChanged(int width, int height)
{
	mDrawableFactory->GetContext().lock()->UpdateDimensions(width, height);
}

void etk::Window::ContentScaleChanged(float xScale, float yScale)
{
	mDrawableFactory->GetContext().lock()->UpdateContentScale(xScale, yScale);
	mDrawableFactory->Invalidate();
}


etk::Window::~Window()
{
	if (!mWin) glfwDestroyWindow(mWin);
}

void etk::Window::SetColor(etk::Color color)
{
	mBackgroundColor = color;
	if(mBackground) mBackground->SetColor(color);
}

void etk::Window::PollEvents()
{
	glfwPollEvents();
}

void etk::Window::WaitEvents()
{
	glfwWaitEvents();
}

void etk::Window::WaitEventsTimeout(double timeout)
{
	glfwWaitEventsTimeout(timeout);
}

void etk::Window::PostEmptyEvent()
{
	glfwPostEmptyEvent();

}

bool etk::Window::Run()
{

	auto start = std::chrono::system_clock::now();
	glfwMakeContextCurrent(mWin);
	mScheduler->Execute();
	if (glfwWindowShouldClose(mWin)) {
		return false;
	}
	auto context = mDrawableFactory->GetContext().lock();
	context->Clear();
	if (mDrawableFactory->IsInvalidated()) {
		if (mScene) mScene->Update();
		mDrawableFactory->ClearInvalidated();
	}
	mBackground->Draw();
	if (mScene) mScene->Draw();
	glfwSwapBuffers(mWin);

	auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> duration = end - start;
	std::cout << "draw duration: " << duration.count() << "s" << std::endl;
	std::cout << "draw fps: " << 1.0 / duration.count() << "fps" << std::endl;
	if (mDrawableFactory->IsInvalidated())
		glfwPostEmptyEvent();
	if (!mScheduler->AnimationQueued() && mScheduler->UIActionQueued()) WaitEventsTimeout(100);
	else if (mScheduler->AnimationQueued()) PollEvents();
	else WaitEvents();
	return true;
}
