#include "window.h"

#include <GLFW/glfw3.h>

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
	mWin = glfwCreateWindow(GetWidth(), GetHeight(), mTitle.c_str(), nullptr, nullptr);
	if (!mWin) {
		throw std::exception("Could not create window");
	}
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
	if (glfwWindowShouldClose(mWin)) {
		return false;
	}
	glClear(GL_COLOR_BUFFER_BIT);
	mBackground->Draw();

	glfwSwapBuffers(mWin);
	glfwPollEvents();
	return true;
}
