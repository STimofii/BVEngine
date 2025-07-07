#pragma once
#include <iostream>
#include <GLFW/glfw3.h>
#include "window.h"

namespace bulka {
	class Engine {
	private:
		static bool running;
		static int exitCode;
	protected:
	public:
		static int run();
		static int init();
		static int preInit();
		static int postInit();
		static void stop(int statusCode = 0);
		static void onExit();
	};
}