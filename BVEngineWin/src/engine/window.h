#pragma once

#include <iostream>
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
		static const char* title;
	protected:
	public:
		static GLFWwindow* window;
		static int create();
		static void destroy();
		static int getWidth();
		static int getHeight();
		static int getScreenWidth();
		static int getScreenHeight();
		static int getRealWidth();
		static int getRealHeight();
		static const char* getTitle();
		static void setWidth(int width);
		static void setHeight(int height);
		static void setRealWidth(int width);
		static void setRealHeight(int height);
		static void setTitle(const char* title);
	};
}
