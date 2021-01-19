#include "window.h"

#include <GLFW/glfw3.h>

#include <exception>

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

bool etk::Window::Run()
{
	glfwMakeContextCurrent(mWin);
	if (glfwWindowShouldClose(mWin)) {
		return false;
	}
	glClear(GL_COLOR_BUFFER_BIT);
	glfwSwapBuffers(mWin);
	glfwPollEvents();
	return true;
}
