#pragma once
#include <iostream>
#include <string>
#include <algorithm>
#include <chrono>
#include <bcppul/timer.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "window.h"
#include "input.h"
#include "settings.h"
#include "graphics/mesh/textured_mesh.h"
#include "graphics/shader_manager.h"
#include "graphics/renderer.h"
#include "graphics/texture_manager.h"

namespace bulka {
	class Engine {
	private:
		static bool running;
		static int exitCode;
		static long long fps;
		static double deltaTime;
		static long long fpsLimit;
		static double fpsLimitDelta;
	protected:
	public:
		static int run();
		static void init();
		static void preInit();
		static void postInit();
		static void preUpdate();
		static void inputUpdate();
		static void update();
		static void postUpdate();
		static void preRender();
		static void render();
		static void postRender();
		static void stop(int statusCode = 0);
		static void onExit();
		static int getExitCode();

		static long long unixTime();
		static double unixTimeDouble();
		static long long getFPS();
		static double getDeltaTime();
		static long long getFPSLimit();
		static void setFPSLimit(long long fpsLimit);
	};
}