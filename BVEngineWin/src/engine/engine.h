#pragma once

#define BVENGINE_VERSION_MAJOR 0
#define BVENGINE_VERSION_MINOR 0
#define BVENGINE_VERSION_REVISION 1

#include <string>
#include <ft2build.h>
#include FT_FREETYPE_H

#include <bcppul/logging.h>



namespace bulka {
	const std::string BVENGINE_VERSION = "BVEngine v" +
		std::to_string(BVENGINE_VERSION_MAJOR) + "." +
		std::to_string(BVENGINE_VERSION_MINOR) + "." +
		std::to_string(BVENGINE_VERSION_REVISION);
	class Hero;
	class TexturedMesh;
	class Engine {
	private:
		static bcppul::Logger* logger;
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