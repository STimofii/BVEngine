#pragma once

#include <array>
#include <algorithm>
#include <GL/glew.h>
#include <GLFW/glfw3.h>


#include "window.h"

#define KEYS_ALL (GLFW_KEY_LAST + GLFW_MOUSE_BUTTON_LAST)

namespace bulka {
	class Input {
	private:
		static std::array<bool, KEYS_ALL> keys;
		static std::array<bool, KEYS_ALL> keys_typed;
		static std::array<bool, KEYS_ALL> keys_released;
		static int key_repeat;
		static int key_repeat_scancode;
		static double mouseX;
		static double mouseY;
		static double previousMouseX;
		static double previousMouseY;
		static double mouseDeltaX;
		static double mouseDeltaY;
		static double scrollX;
		static double scrollY;

		static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
		static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
		static void cursorPosCallback(GLFWwindow* window, double xpos, double ypos);
		static void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);
	protected:
	public:
		static void init();
		static void preUpdate();
		static void update();
		static void postUpdate();
		static void pollEvents();
		static void finalization();
		static bool isKeyPressed(int key);
		static bool isKeyTyped(int key);
		static bool isKeyReleased(int key);
		static bool isKeyRepeated(int key);
		static int getKeyRepeat();
		static int getKeyRepeatScancode();
		static double getMouseX();
		static double getMouseY();
		static double getMouseDeltaX();
		static double getMouseDeltaY();
		static double getScrollX();
		static double getScrollY();
	};
}