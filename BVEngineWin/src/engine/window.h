#pragma once

#include <iostream>
#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "camera.h"
#include "engine.h"


namespace bulka {
	class Hero;
	class Window {
	private:
		static int memWidth;
		static int memHeight;
		static int xPos;
		static int yPos;
		static int memXPos;
		static int memYPos;
		static int screenWidth;
		static int screenHeight;
		static int realWidth;
		static int realHeight;
		static float aspect;
		static bool fullscreen;
		static bool inWindow;
		static bool cursorHided;
		static bool cursorJustHided;
		static std::string title;

		static void windowSizeCallback(GLFWwindow* window, int width, int height);
		static void windowPosCallback(GLFWwindow* window, int xpos, int ypos);
		static void windowFocusedCallback(GLFWwindow* window, int entered);
	protected:
	public:
		static GLFWwindow* window;
		static void create();
		static void resize();
		static void onResize();
		static void resize(int width, int height);
		static bool isShouldClose();
		static void preUpdate();
		static void inputUpdate();
		static void update();
		static void postUpdate();
		static void preRender();
		static void render();
		static void postRender();
		static void setCursorInCenter();
		static void finalization();
		static void hideCursor();
		static void showCursor();
		static int getXPos();
		static int getYPos();
		static int getScreenWidth();
		static int getScreenHeight();
		static int getRealWidth();
		static int getRealHeight();
		static float getAspect();
		static bool isFullScreen();
		static bool isInWindow();
		static bool isCursorHided();
		static bool isCursorJustHided();
		static std::string getTitle();
		static void setRealWidth(int width);
		static void setRealHeight(int height);
		static void setTitle(std::string title);
		static void enableFullScreen();
		static void disableFullScreen();
	};
}
