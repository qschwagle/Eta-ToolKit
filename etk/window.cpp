#include "window.h"

#include <Gl/glew.h>
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
    glewExperimental = true;

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SRGB_CAPABLE, GLFW_TRUE);
	glEnable(GL_MULTISAMPLE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	mWin = glfwCreateWindow(GetWidth(), GetHeight(), mTitle.c_str(), nullptr, nullptr);
	if (!mWin) {
		throw std::exception("Could not create window");
	}
	glfwMakeContextCurrent(mWin);
	if (glewInit() != GLEW_OK)
	{
		throw std::exception("failed to initialize glew");
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
	if (mScene) mScene->Draw();
	glfwSwapBuffers(mWin);
	glfwPollEvents();
	return true;
}
