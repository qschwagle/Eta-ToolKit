#include "window.h"

#include "GLFW/glfw3.h"

#include <exception>

etk::Window::Window(int id,  std::string title, long width, long height, std::shared_ptr<etk::renderer::DrawableFactory> factory) : 
	mId{ id }, 
	mWidth{ width }, 
	mHeight{ height }, 
	mTitle{ title },
	mDrawableFactory{ factory } 
{
	mBackground = mDrawableFactory->CreateBackground();
}

void etk::Window::Init() 
{
	auto context = mDrawableFactory->GetContext().lock();
	context->WindowInit(GetWidth(), GetHeight());
	mWin = glfwCreateWindow(GetWidth(), GetHeight(), mTitle.c_str(), nullptr, nullptr);
	if (!mWin) {
		throw std::exception("Could not create window");
	}
	glfwMakeContextCurrent(mWin);
	context->Init();
}

void etk::Window::MarkToClose()
{
	glfwSetWindowShouldClose(mWin, true);
}


etk::Window::~Window()
{
	if (!mWin) glfwDestroyWindow(mWin);
}

void etk::Window::SetColor(etk::Color color)
{
	mBackground->SetColor(color);
}

bool etk::Window::Run()
{
	glfwMakeContextCurrent(mWin);
	auto sched = mDrawableFactory->GetUIScheduler();
	sched.lock()->Execute();
	if (glfwWindowShouldClose(mWin)) {
		return false;
	}
	auto context = mDrawableFactory->GetContext().lock();
	context->Clear();
	mBackground->Draw();
	if (mScene) mScene->Draw();
	glfwSwapBuffers(mWin);
	glfwPollEvents();
	return true;
}
