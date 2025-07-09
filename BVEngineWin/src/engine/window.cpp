#include "window.h"

#include <iostream>
#include "camera.h"
#include "hero.h"
#include "engine.h"


namespace bulka {
	int Window::realWidth = 1280;
	int Window::realHeight = 720;
	int Window::memWidth = realWidth;
	int Window::memHeight = realHeight;
	int Window::screenWidth = 0;
	int Window::screenHeight = 0;
	int Window::xPos = 0;
	int Window::yPos = 0;
	int Window::memXPos = 0;
	int Window::memYPos = 0;
	float Window::aspect = 0.0;
	bool Window::fullscreen = false;
	bool Window::inWindow = false;
	bool Window::cursorHided = false;
	bool Window::cursorJustHided = false;
	std::string Window::title = "BVEngine";
	GLFWwindow* Window::window = nullptr;

	void Window::windowSizeCallback(GLFWwindow* window, int width, int height) {
		Window::realWidth = width;
		Window::realHeight = height;
		onResize();
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
		const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
		screenWidth = mode->width;
		screenHeight = mode->height;
		if (realWidth > screenWidth) {
			realWidth = screenWidth;
		}
		if (realHeight > screenHeight) {
			realHeight = screenHeight;
		}
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
		xPos = screenWidth / 2 - realWidth / 2;
		yPos = screenHeight / 2 - realHeight / 2;
		glfwSetWindowPos(window, xPos, yPos);

		glfwMakeContextCurrent(window);
		onResize();
		
		glfwShowWindow(window);
	}
	void Window::onResize() {
		aspect = static_cast<float>(realWidth) / static_cast<float>(realHeight);
		glViewport(0, 0, realWidth, realHeight);
		Engine::getHero().getCamera().updateOrthoMatrix();
		Engine::getHero().getCamera().updateProjectionMatrix();
		Engine::getHero().getCamera().updateProjViewMatrix();
	}
	void Window::resize()
	{
		aspect = static_cast<float>(realWidth) / static_cast<float>(realHeight);
		glfwSetWindowSize(window, realWidth, realHeight);
		glViewport(0, 0, realWidth, realHeight);
	}
	void Window::resize(int width, int height)
	{
		Window::realWidth = width;
		Window::realHeight = height;
		resize();
	}

	void Window::enableFullScreen() {
		Window::fullscreen = true;
		memWidth = realWidth;
		memHeight = realHeight;
		realWidth = screenWidth;
		realHeight = screenHeight;
		memXPos = xPos;
		memYPos = yPos;
		glfwSetWindowMonitor(window, glfwGetPrimaryMonitor(), 0, 0, screenWidth, screenHeight, GLFW_DONT_CARE);
		glViewport(0, 0, realWidth, realHeight);
	}
	void Window::disableFullScreen() {
		Window::fullscreen = false;
		realWidth = memWidth;
		realHeight = memHeight;
		glfwSetWindowMonitor(window, nullptr, memXPos, memYPos, memWidth, memHeight, GLFW_DONT_CARE);
		glViewport(0, 0, realWidth, realHeight);
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

	}
	void Window::postUpdate()
	{
		cursorJustHided = false;
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

	void Window::setCursorInCenter()
	{
		glfwSetCursorPos(window, realWidth / 2, realHeight / 2);
		Input::setMouseX(realWidth / 2);
		Input::setMouseY(realHeight / 2);
		Input::setPreviousMouseX(realWidth / 2);
		Input::setPreviousMouseY(realHeight / 2);
	}

	void Window::finalization()
	{

	}

	void Window::hideCursor()
	{
		cursorHided = true;
		cursorJustHided = true;
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	}
	void Window::showCursor()
	{
		cursorHided = false;
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
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
	bool Window::isCursorHided()
	{
		return cursorHided;
	}
	bool Window::isCursorJustHided()
	{
		return cursorJustHided;
	}
	std::string Window::getTitle() {
		return title;
	}
	void Window::setRealWidth(int width) {
		Window::realWidth = width;
	}
	void Window::setRealHeight(int height) {
		Window::realHeight = height;
	}
	void Window::setTitle(std::string title) {
		Window::title = title;
		if(window != nullptr){
			glfwSetWindowTitle(window, title.c_str());
		}
	}
}