#include "engine.h"

namespace bulka {
	bool Engine::running = false;
	int Engine::exitCode = 0;
	long long Engine::fps = 0;
	double Engine::deltaTime = 0;
	long long Engine::fpsLimit = 0;
	double Engine::fpsLimitDelta = 0;

	TexturedMesh simpleMesh;

	int Engine::run() {
		bcppul::Timer timer("engine", false);
		timer.start();
		std::cout << "Initializing!" << std::endl;
		running = false;
		preInit();
		init();
		postInit();

		simpleMesh.setVertices(new Vertex5f[4]{
			Vertex5f(-1, -1, 0, 0, 1),
			Vertex5f(1, -1, 0, 1, 1),
			Vertex5f(1, 1, 0, 1, 0),
			Vertex5f(-1, 1, 0, 0, 0)
		}, 4);
		simpleMesh.setIndices(new GLuint[6]{
			0, 1, 2,
			2, 3, 0
		}, 6);
		simpleMesh.update();
		Texture bulka = Texture("res/textures/bulka.png");
		simpleMesh.setTexture(&bulka);

		std::cout << "Initialized! Time for initializing - " << timer.getTimeSeconds() << std::endl;
		
		running = true;
		std::cout << "Running!!!" << std::endl;
		long long timeFrameStart;
		long long timeFrameElapsed;
		long long timeFPS = unixTime();
		long long frames = 0;
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
			glClear(GL_COLOR_BUFFER_BIT);
			preRender();

			render();

			glfwSwapBuffers(Window::window);
			Input::pollEvents();
			glfwPollEvents();

			postRender();

			if (glGetError() != GL_NO_ERROR) {
				std::cerr << "GL_ERROR: " << glGetError() << std::endl;
			}
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
		std::cout << "Don't Running!" << std::endl;

		onExit();
		glfwTerminate();
		return exitCode;
	}

	void Engine::preInit()
	{
		Settings::init();
	}
	void Engine::init()
	{
		if (!glfwInit()) {
			std::cerr << "GLFW CAN'T INIT!!!" << std::endl;
			throw new std::exception("GLFW CAN'T INIT!!!");
		}


		Window::setRealWidth(1280);
		Window::setRealHeight(720);
		Window::setTitle(new char[10] {"BVEngine!"});
		Window::create();

		if (glewInit() != GLEW_OK) {
			std::cerr << "GLEW CAN'T INIT!!!" << std::endl;
			throw new std::exception("GLEW CAN'T INIT!!!");
		}

		Input::init();
		ShaderManager::init();
		Renderer::init();
	}
	void Engine::postInit()
	{
		glEnable(GL_CULL_FACE);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
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
				Window::disableFullScrean();
			}
			else {
				Window::enableFullScrean();
			}
		}
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
		ShaderManager::finalization();
		Input::finalization();
		Window::finalization();
		Settings::finalization();
	}
	int Engine::getExitCode()
	{
		return exitCode;
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
}