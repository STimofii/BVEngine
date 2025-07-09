#include "input.h"



namespace bulka {
	std::array<bool, KEYS_ALL> Input::keys;
	std::array<bool, KEYS_ALL> Input::keys_typed;
	std::array<bool, KEYS_ALL> Input::keys_released;

	int Input::key_repeat = 0;
	int Input::key_repeat_scancode = 0;
	double Input::mouseX = 0;
	double Input::mouseY = 0;
	double Input::previousMouseX = 0;
	double Input::previousMouseY = 0;
	double Input::mouseDeltaX = 0;
	double Input::mouseDeltaY = 0;
	double Input::scrollX = 0;
	double Input::scrollY = 0;

	void Input::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		switch (action) {
		case GLFW_PRESS: {
			keys[key] = true;
			keys_typed[key] = true;
			break;
		}
		case GLFW_REPEAT:{
			key_repeat = key;
			break;
		}
		case GLFW_RELEASE: {
			keys[key] = false;
			keys_released[key] = true;
			break;
		}
		default: {

		}
		}
		
	}

	void Input::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
	{
		int key = GLFW_KEY_LAST + button + 1;
		switch (action) {
		case GLFW_PRESS: {
			keys[key] = true;
			keys_typed[key] = true;
			break;
		}
		case GLFW_REPEAT: {
			key_repeat = key;
			break;
		}
		case GLFW_RELEASE: {
			keys[key] = false;
			keys_released[key] = true;
			break;
		}
		default: {

		}
		}
	}

	void Input::cursorPosCallback(GLFWwindow* window, double xpos, double ypos)
	{
		mouseX = xpos;
		mouseY = ypos;
	}

	void Input::scrollCallback(GLFWwindow* window, double xoffset, double yoffset)
	{
		scrollX = xoffset;
		scrollY = yoffset;
	}

	void Input::init() {
		std::fill(keys.begin(), keys.end(), 0);
		std::fill(keys_typed.begin(), keys_typed.end(), 0);
		std::fill(keys_released.begin(), keys_released.end(), 0);

		glfwSetKeyCallback(Window::window, keyCallback);
		glfwSetMouseButtonCallback(Window::window, mouseButtonCallback);
		glfwSetCursorPosCallback(Window::window, cursorPosCallback);
		glfwSetScrollCallback(Window::window, scrollCallback);
	}
	void Input::preUpdate()
	{

	}
	void Input::update()
	{

	}
	void Input::postUpdate()
	{

	}
	void Input::pollEvents()
	{
		key_repeat = 0;
		for (size_t i = 0; i <= GLFW_KEY_LAST; i++)
		{
			if (keys_typed[i]) {
				keys_typed[i] = false;
			}
			if (keys_released[i]) {
				keys_released[i] = false;
			}
		}
	}

	void Input::postPollEvents()
	{
		if (Window::isCursorHided()) {
			mouseDeltaX = previousMouseX - mouseX;
			mouseDeltaY = previousMouseY - mouseY;
			Window::setCursorInCenter();
			previousMouseX = mouseX;
			previousMouseY = mouseY;
		}
		else {
			previousMouseX = mouseX;
			previousMouseY = mouseY;
			mouseDeltaX = 0;
			mouseDeltaY = 0;
		}

	}


	void Input::finalization() {

	}
	bool Input::isKeyPressed(int key)
	{
		return keys[key];
	}
	bool Input::isKeyTyped(int key)
	{
		return keys_typed[key];
	}
	bool Input::isKeyReleased(int key)
	{
		return keys_released[key];
	}
	bool Input::isKeyRepeated(int key)
	{
		return key_repeat == key;
	}

	bool Input::isMouseButtonPressed(int key)
	{
		return keys[GLFW_KEY_LAST + key + 1];
	}
	bool Input::isMouseButtonTyped(int key)
	{
		return keys_typed[GLFW_KEY_LAST + key + 1];
	}
	bool Input::isMouseButtonReleased(int key)
	{
		return keys_released[GLFW_KEY_LAST + key + 1];
	}
	bool Input::isMouseButtonRepeated(int key)
	{
		return key_repeat == GLFW_KEY_LAST + key + 1;
	}

	int Input::getKeyRepeat()
	{
		return key_repeat;
	}
	int Input::getKeyRepeatScancode()
	{
		return key_repeat_scancode;
	}
	double Input::getMouseX()
	{
		return mouseX;
	}
	double Input::getMouseY()
	{
		return mouseY;
	}
	void Input::setMouseX(double mouseX)
	{
		Input::mouseX = mouseX;
	}
	void Input::setMouseY(double mouseY)
	{
		Input::mouseY = mouseY;
	}
	void Input::setPreviousMouseX(double mouseX)
	{
		previousMouseX = mouseX;
	}
	void Input::setPreviousMouseY(double mouseY)
	{
		previousMouseY = mouseY;
	}
	double Input::getMouseDeltaX()
	{
		return mouseDeltaX;
	}
	double Input::getMouseDeltaY()
	{
		return mouseDeltaY;
	}
	double Input::getScrollX()
	{
		return scrollX;
	}
	double Input::getScrollY()
	{
		return scrollY;
	}
}