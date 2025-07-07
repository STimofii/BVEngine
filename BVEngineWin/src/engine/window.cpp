#include "window.h"

namespace bulka {
	int Window::width = 1280;
	int Window::height = 720;
	int Window::realWidth = width;
	int Window::realHeight = height;
	int Window::screenWidth = 0;
	int Window::screenHeight = 0;
	float Window::aspect = 0.0;
	bool Window::fullscreen = false;
	bool Window::inWindow = false;
	std::string Window::title = "BVEngine";
	GLFWwindow* Window::window = nullptr;

	void Window::windowSizeCallback(GLFWwindow* window, int width, int height) {
		Window::width = width;
		Window::height = height;
		Window::realWidth = width;
		Window::realHeight = height;
		aspect = static_cast<float>(realWidth) / static_cast<float>(realHeight);
		glViewport(0, 0, width, height);
	}
	void Window::windowPosCallback(GLFWwindow* window, int xpos, int ypos)
	{
		xPos = xpos;
		yPos = ypos;
	}
	void Window::windowFocusedCallback(GLFWwindow* window, int focused)
	{
		inWindow = focused;
	}

	void Window::create()
	{
		inWindow = false;
		fullscreen = false;
		const GLFWvidmode* mode = glfwGetVideoMode(glfwGetWindowMonitor(window));
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
		aspect = static_cast<float>(realWidth) / static_cast<float>(realHeight);
		glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
		glfwWindowHint(GLFW_FOCUSED, GLFW_TRUE);
		window = glfwCreateWindow(realWidth, realHeight, title.c_str(), nullptr, nullptr);

		if (window == nullptr)
		{
			std::cerr << "FAILED TO CREATE WINDOW!!!" << std::endl;
			throw new std::exception("FAILED TO CREATE WINDOW!!!");
		}

		glfwWindowHint(GLFW_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwSetWindowSizeCallback(window, windowSizeCallback);
		glfwSetWindowPosCallback(window, windowPosCallback);
		glfwSetWindowFocusCallback(window, windowFocusedCallback);
		glfwSetWindowPos(window, screenWidth / 2 - realWidth / 2, screenHeight / 2 - realHeight / 2);

		glfwMakeContextCurrent(window);
		setVSync(false);
		glViewport(0, 0, realWidth, realHeight);
		
		glfwShowWindow(window);
	}
	void Window::resize()
	{
		realWidth = width;
		realHeight = height;
		aspect = static_cast<float>(realWidth) / static_cast<float>(realHeight);
		glfwSetWindowSize(window, width, height);
		glViewport(0, 0, width, height);
	}
	void Window::resize(int width, int height)
	{
		Window::width = width;
		Window::height = height;
		resize();
	}

	void Window::enableFullScrean() {
		Window::fullscreen = true;
		realWidth = screenWidth;
		realHeight = screenHeight;
		glfwSetWindowMonitor(window, glfwGetWindowMonitor(window), 0, 0, screenWidth, screenHeight, GLFW_DONT_CARE);
	}
	void Window::disableFullScrean() {
		Window::fullscreen = false;
		realWidth = width;
		realHeight = height;
		glfwSetWindowMonitor(window, glfwGetWindowMonitor(window), xPos, yPos, width, height, GLFW_DONT_CARE);
	}

	bool Window::isShouldClose()
	{
		return glfwWindowShouldClose(Window::window);
	}
	void Window::finalization()
	{

	}

	void Window::setVSync(bool vsync)
	{
		if(vsync){
			glfwSwapInterval(1);
		}
		else {
			glfwSwapInterval(0);
		}
	}

	int Window::getWidth() {
		return width;
	}
	int Window::getHeight() {
		return height;
	}
	int Window::getXPos() {
		return xPos;
	}
	int Window::getYPos() {
		return yPos;
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
	float Window::getAspect()
	{
		return aspect;
	}
	bool Window::isFullScreen()
	{
		return fullscreen;
	}
	bool Window::isInWindow()
	{
		return inWindow;
	}
	std::string Window::getTitle() {
		return title;
	}
	void Window::setWidth(int width) {
		Window::width = width;
	}
	void Window::setHeight(int height) {
		Window::height = height;
	}
	void Window::setTitle(std::string title) {
		Window::title = title;
		if(window != nullptr){
			glfwSetWindowTitle(window, title.c_str());
		}
	}
}