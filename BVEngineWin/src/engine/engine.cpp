#include "engine.h"

#include "hero.h"
#include "graphics/mesh/textured_mesh.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <codecvt>
#include <string>
#include <algorithm>
#include <chrono>
#include <bcppul/timer.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "graphics/mesh/vertex/vertex5f.h"

#include "graphics/text/dynamic_text.h"



namespace bulka {
	bcppul::Logger* logger = bcppul::getLogger("Engine");
	bool Engine::running = false;
	int Engine::exitCode = 0;
	long long Engine::fps = 0;
	double Engine::deltaTime = 0;
	long long Engine::fpsLimit = 0;
	double Engine::fpsLimitDelta = 0;
	bool Engine::v_sync = false;
	bool Engine::isGLInitialized = false;;
	FT_Library Engine::ft_library;
	FT_Face Engine::main_font;
	Hero Engine::hero;
	TexturedMesh Engine::simpleMesh;

	DynamicText* texts;



	int Engine::run() {
		logger->info("Running!!!");
		bcppul::Timer timer("engine", false);
		timer.start();

		setlocale(LC_TIME, "uk_UA");
		setlocale(LC_MONETARY, "uk_UA");
		setlocale(LC_NUMERIC, "C");

		logger->info("Initializing");
		running = false;
		preInit();
		init();
		postInit();
		logger->info("Initialized");

		setVSync(v_sync);

		hero.setPosition(0, 0, 10);

		float z = 0.0f;
		float size = 1.0f;
		simpleMesh.setVertices(new Vertex5f[4]{
			Vertex5f(-size, -size, z, 0, 1),
			Vertex5f(size, -size, z, 1, 1),
			Vertex5f(size, size, z, 1, 0),
			Vertex5f(-size, size, z, 0, 0)
			}, 4);
		simpleMesh.setIndices(new GLuint[6]{
			0, 1, 2,
			2, 3, 0
			}, 6);
		simpleMesh.update();
		simpleMesh.setTexture(TextureManager::getTexture("res/textures/bulka.png"));

		*logger << bcppul::INFO << "Initialized! Time for initializing - " << timer.getTimeSeconds();
		
		running = true;
		std::cout << "Running!!!" << std::endl;
		long long timeFrameStart;
		long long timeFrameElapsed;
		long long timeFPS = unixTime();
		long long frames = 0;


		texts = new DynamicText(
			BVENGINE_VERSION, 16, glm::vec3(0, 0, 0), 255, 255, 255, 255, 1,
			LEFT_BOTTOM_CORNER
		);
		//std::wifstream wif("res/text.txt");
		//wif.imbue(std::locale(std::locale(), new std::codecvt_utf8<wchar_t>));
		//std::wstringstream wss;
		//wss << wif.rdbuf();
		//wif.close();
		//std::wcout << wss.str();
		texts->setProjection(&hero.getCamera().getOrthoMatrix());
		texts->init();

		logger->info("Starting game loop");
		while (running) {
			timeFrameStart = unixTime();
			preUpdate();
			if (Window::isShouldClose() || Input::isKeyPressed(GLFW_KEY_ESCAPE)) {
				std::cout << "Window should close... Or ESC is pressed" << std::endl;
				exitCode = 0;
				running = false;
			}


			inputUpdate();
			update();
			postUpdate();
			glClearColor(135.0f / 256, 206.0f / 256, 235.0f / 256, 1);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			preRender();

			render();

			glfwSwapBuffers(Window::window);
			Input::pollEvents();
			glfwPollEvents();
			Input::postPollEvents();

			postRender();

			checkGLErrors();
			do {
				timeFrameElapsed = unixTime() - timeFrameStart;
				deltaTime = timeFrameElapsed / 1000000000.0;
			} while (fpsLimit != 0 && deltaTime < fpsLimitDelta);
			if (unixTime() - timeFPS >= 500000000) {
				fps = frames / 0.5;
				timeFPS = unixTime();
				frames = 0;
				std::cout << "FPS: " << fps << std::endl;
				Window::setTitle(Settings::GAME_NAME + "! FPS: " + std::to_string(fps));
			}
			++frames;
		}
		logger->info("Don't Running!");

		logger->info("onExit()");
		onExit();
		logger->info("finalized");
		glfwTerminate();
		logger->info("Bye!");
		return exitCode;
	}

	void Engine::preInit()
	{
		logger->info("Pre init");
	}
	void Engine::init()
	{
		logger->info("Init");
		logger->debug("Initializing GLFW");
		if (!glfwInit()) {
			logger->fatal("GLFW CAN'T INIT!!!");
			throw new std::exception("GLFW CAN'T INIT!!!");
		}
		logger->debug("Initialized GLFW");
		logger->debug("Initializing Settings");
		Settings::init();
		logger->debug("Initialized Settings");

		logger->debug("Initializing FreeType");
		FT_Error error = FT_Init_FreeType(&ft_library);
		if (error) {
			*logger << bcppul::ERROR << "FreeType FT_Init_FreeType error: " << error;
		}
		*logger << bcppul::DEBUG << "Loading font: " << Settings::FONT;
		error = FT_New_Face(ft_library, Settings::FONT.c_str(), 0, &main_font);
		if (error) {
			logger->error("GLFW CAN'T INIT!!!");
			*logger << bcppul::ERROR << "FreeType font " << Settings::FONT.c_str() << " loading error: " << error;
		}
		error = FT_Set_Pixel_Sizes(main_font, 0, 16);
		if (error) {
			logger->error("GLFW CAN'T INIT!!!");
			*logger << bcppul::ERROR << "FreeType FT_Set_Pixel_Sizes error: " << error;
		}
		logger->debug("Initialized FreeType");


		logger->debug("Creating Window");
		Window::setRealWidth(1280);
		Window::setRealHeight(720);
		Window::setTitle(new char[10] {"BVEngine!"});
		Window::create();
		logger->debug("Created Window");
		logger->debug("Initializing GLEW");
		if (glewInit() != GLEW_OK) {
			logger->fatal("GLEW CAN'T INIT!!!");
			throw new std::exception("GLEW CAN'T INIT!!!");
		}
		isGLInitialized = true;
		logger->debug("Initialized GLEW");

		logger->debug("Initializing ShaderManager");
		ShaderManager::init();
		logger->debug("Initializing Input");
		Input::init();
		logger->debug("Initializing TextManager");
		TextManager::init();
		logger->debug("Initializing TextureManager");
		TextureManager::init();
		logger->debug("Initializing Hero");
		hero.init();
		logger->debug("Initializing Renderer");
		Renderer::init();
	}
	void Engine::postInit()
	{
		logger->info("Post init");
		glEnable(GL_CULL_FACE);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		hero.postInit();
	}

	void Engine::preUpdate()
	{
		Input::preUpdate();
		Window::preUpdate();
	}
	void Engine::inputUpdate()
	{
		if (Input::isKeyTyped(GLFW_KEY_TAB)) {
			if (Window::isCursorHided()) {
				Window::showCursor();
			}
			else {
				Window::hideCursor();
			}
		}
		if (Input::isKeyTyped(GLFW_KEY_F11)) {
			if (Window::isFullScreen()) {
				Window::disableFullScreen();
			}
			else {
				Window::enableFullScreen();
			}
		}

		hero.inputUpdate();
	}
	void Engine::update()
	{
		Input::update();
		Window::update();
	}
	void Engine::postUpdate()
	{
		Input::postUpdate();
		Window::postUpdate();
	}
	void Engine::preRender()
	{
		Window::preRender();
	}
	void Engine::render()
	{
		ShaderManager::mainShader.bind();
		Renderer::render(simpleMesh);
		ShaderManager::mainShader.unbind();
		texts->render();
		//for (size_t i = 0; i < 1; i++)
		//{
		//	texts[i].render();
		//}
		
		Window::render();
	}
	void Engine::postRender()
	{
		Window::postRender();
	}

	void Engine::stop(int statusCode)
	{
		exitCode = statusCode;
		running = false;
	}
	void Engine::onExit()
	{
		Renderer::finalization();
		hero.finalization();
		TextureManager::finalization();
		TextManager::finalization();
		ShaderManager::finalization();
		Input::finalization();
		Window::finalization();
		FT_Done_Face(main_font);
		FT_Done_FreeType(ft_library);
		Settings::finalization();
	}
	void Engine::checkGLErrors()
	{
		unsigned int gl_error = glGetError();
		if (gl_error != GL_NO_ERROR) {
			std::cerr << "GL_ERROR: " << gl_error << std::endl;
		}
	}
	int Engine::getExitCode()
	{
		return exitCode;
	}
	FT_Library& Engine::getFT_Library()
	{
		return ft_library;
	}
	FT_Face& Engine::getMainFont()
	{
		return main_font;
	}
	Hero& Engine::getHero()
	{
		return hero;
	}
	long long Engine::unixTime()
	{
		return std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	}
	double Engine::unixTimeDouble()
	{
		return static_cast<double>(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count())/1000000000;
	}
	long long Engine::getFPS()
	{
		return fps;
	}
	double Engine::getDeltaTime()
	{
		return deltaTime;
	}
	long long Engine::getFPSLimit()
	{
		return fpsLimit;
	}
	void Engine::setFPSLimit(long long fpsLimit) {
		Engine::fpsLimit = fpsLimit;
		if(fpsLimit != 0){
			fpsLimitDelta = 1.0 / static_cast<double>(fpsLimit);
		}
		else {
			fpsLimitDelta = 0;
		}
	}
	bool Engine::isVSync()
	{
		return v_sync;
	}
	void Engine::setVSync(bool v_sync) {
		Engine::v_sync = v_sync;
		if (v_sync) {
			glfwSwapInterval(1);
		}
		else {
			glfwSwapInterval(0);
		}
	}
	bool Engine::getIsGLInitialized()
	{
		return isGLInitialized;
	}
}