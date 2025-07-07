#include "window.h"

namespace bulka {
	int Window::width = 1280;
	int Window::height = 720;
	int Window::realWidth = width;
	int Window::realHeight = height;
	int Window::screenWidth = 0;
	int Window::screenHeight = 0;
	const char* Window::title = new char[9] {"BVEngine"};
	GLFWwindow* Window::window = nullptr;

	int Window::create()
	{
		const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
		screenWidth = mode->width;
		screenHeight = mode->height;
		if (width > screenWidth) {
			width = screenWidth;
		}
		if (height > screenHeight) {
			height = screenHeight;
		}
		Window::realWidth = width;
		Window::realHeight = height;
		window = glfwCreateWindow(width, height, title, nullptr, nullptr);

		if (window == nullptr)
		{
			std::cerr << "FAILED TO CREATE WINDOW!!!" << std::endl;
			return -1;
		}

		glfwWindowHint(GLFW_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
		glfwSetWindowPos(window, screenWidth / 2 - realWidth / 2, screenHeight / 2 - realHeight / 2);

		glfwMakeContextCurrent(window);
		
		glfwWindowHint(GLFW_VISIBLE, GLFW_TRUE);

		return 0;
	}
	void Window::destroy()
	{
		delete[] title;
	}

	int Window::getWidth() {
		return width;
	}
	int Window::getHeight() {
		return height;
	}
	int Window::getScreenWidth() {
		return screenWidth;
	}
	int Window::getScreenHeight() {
		return screenHeight;
	}
	int Window::getRealWidth() {
		return realWidth;
	}
	int Window::getRealHeight() {
		return realHeight;
	}
	const char* Window::getTitle() {
		return title;
	}
	void Window::setWidth(int width) {
		Window::width = width;
	}
	void Window::setHeight(int height) {
		Window::height = height;
	}
	void Window::setRealWidth(int width) {
		Window::realWidth = width;
	}
	void Window::setRealHeight(int height) {
		Window::realHeight = height;
	}
	void Window::setTitle(const char* title) {
		Window::title = title;
	}
}