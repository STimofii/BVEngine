#pragma once

#include "window.h"
#include "input.h"
#include "settings.h"
#include "graphics/shader_manager.h"
#include "graphics/renderer.h"
#include "graphics/texture_manager.h"

#include <ft2build.h>
#include FT_FREETYPE_H

namespace bulka {
	class Hero;
	class TexturedMesh;
	class Engine {
	private:
		static bool running;
		static int exitCode;
		static long long fps;
		static double deltaTime;
		static long long fpsLimit;
		static double fpsLimitDelta;
		static bool v_sync;
		static bool isGLInitialized;
		static FT_Library ft_library;
		static FT_Face main_font;
		static Hero hero;
		static TexturedMesh simpleMesh;

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

		static void checkGLErrors();
		
		static int getExitCode();
		static long long unixTime();
		static double unixTimeDouble();
		static long long getFPS();
		static double getDeltaTime();
		static long long getFPSLimit();
		static void setFPSLimit(long long fpsLimit);
		static bool isVSync();
		static void setVSync(bool v_sync);
		static bool getIsGLInitialized();

		static FT_Library& getFT_Library();
		static FT_Face& getMainFont();
		static Hero& getHero();
		
	};
}