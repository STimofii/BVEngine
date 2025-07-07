#pragma once

#include <iostream>
#include <string>
#include <GLFW/glfw3.h>

namespace bulka {
	class Window {
	private:
		static int width;
		static int height;
		static int screenWidth;
		static int screenHeight;
		static int realWidth;
		static int realHeight;
		static float aspect;
		static bool fullscrean;
		static bool inWindow;
		static bool cursorHided;
		static std::string title;

		static void windowSizeCallback(GLFWwindow* window, int width, int height);
		static void windowFocusedCallback(GLFWwindow* window, int entered);
	protected:
	public:
		static GLFWwindow* window;
		static void create();
		static void resize();
		static void resize(int width, int height);
		static bool isShouldClose();
		static void preUpdate();
		static void inputUpdate();
		static void update();
		static void postUpdate();
		static void preRender();
		static void render();
		static void postRender();
		static void finalization();
		static void setVSync(bool vsync);
		static void hideCursor();
		static void showCursor();
		static int getWidth();
		static int getHeight();
		static int getScreenWidth();
		static int getScreenHeight();
		static int getRealWidth();
		static int getRealHeight();
		static float getAspect();
		static bool isFullScrean();
		static bool isInWindow();
		static bool isCursorHided();
		static std::string getTitle();
		static void setWidth(int width);
		static void setHeight(int height);
		static void setTitle(std::string title);
		static void setFullScrean(bool fullscrean);
	};
}
