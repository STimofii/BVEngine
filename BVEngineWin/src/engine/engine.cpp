#include "engine.h"

namespace bulka {
	bool Engine::running = false;
	int Engine::exitCode = 0;
	int Engine::run() {
		running = false;
		exitCode = 0;
		preInit();
		init();
		postInit();
		if (exitCode != 0) {
			
		}
		else {
			running = true;
			glClearColor(1.0, 0.0, 0.0, 1.0);

			while (running) {
				glfwPollEvents();
				if (glfwWindowShouldClose(Window::window)) {
					running = false;
				}

				glClear(GL_COLOR_BUFFER_BIT);

				glfwSwapBuffers(Window::window);
			}
		}


		onExit();
		glfwTerminate();
		return exitCode;
	}

	int Engine::preInit()
	{
		return 0;
	}
	int Engine::init()
	{
		if (!glfwInit()) {
			std::cerr << "GLFW CAN'T INIT!!!" << std::endl;
			return -1;
		}

		Window::setWidth(1280);
		Window::setHeight(720);
		Window::setTitle(new char[10] {"BVEngine!"});
		Window::create();


		return 0;
	}
	int Engine::postInit()
	{
		return 0;
	}

	void Engine::stop(int statusCode)
	{
		exitCode = statusCode;
		running = false;
	}
	void Engine::onExit()
	{
		Window::destroy();
	}
}