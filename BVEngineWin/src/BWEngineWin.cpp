// src/BWEngineWin.cpp
#include <iostream>

#include <bcppul/timer.h>
#include <GLFW/glfw3.h>

int main()
{
	bcppul::SimpleTimer timer;
	if (!glfwInit()) {
		std::cerr << "GLFW CAN'T INIT!!!" << std::endl;
		return -1;
	}

	//glfwWindowHint(GLFW_VERSION_MAJOR, 3);
	//glfwWindowHint(GLFW_VERSION_MINOR, 3);
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(640, 480, "Hello World", nullptr, nullptr);
	if (window == nullptr)
	{
		std::cerr << "FAILED TO CREATE WINDOW!!!" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}