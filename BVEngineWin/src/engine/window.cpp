#include "window.h"

namespace bulka {
	int Window::width = 1280;
	int Window::height = 720;
	int Window::realWidth = width;
	int Window::realHeight = height;
	int Window::screenWidth = 0;
	int Window::screenHeight = 0;
	float Window::aspect = 0.0;
	bool Window::fullscrean = false;
	bool Window::inWindow = false;
	bool Window::cursorHided = false;
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
	void Window::windowFocusedCallback(GLFWwindow* window, int focused)
	{
		inWindow = focused;
	}

	void Window::create()
	{
		inWindow = false;
		fullscrean = false;
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
	bool Window::isShouldClose()
	{
		return glfwWindowShouldClose(Window::window);
	}

	void Window::preUpdate()
	{

	}
	void Window::update()
	{
		if (cursorHided) {
			glfwSetCursorPos(window, realWidth / 2, realHeight / 2);
		}
	}
	void Window::postUpdate()
	{

	}
	void Window::preRender()
	{

	}
	void Window::render()
	{

	}
	void Window::postRender()
	{

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

	void Window::hideCursor()
	{
		cursorHided = true;
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	}
	void Window::showCursor()
	{
		cursorHided = false;
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
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
	float Window::getAspect()
	{
		return aspect;
	}
	bool Window::isFullScrean()
	{
		return fullscrean;
	}
	bool Window::isInWindow()
	{
		return inWindow;
	}
	bool Window::isCursorHided()
	{
		return cursorHided;
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
	void Window::setFullScrean(bool fullscrean) {
		Window::fullscrean = fullscrean;

	}
}