#include "loading_screen.h"
#include "../window.h"
#include "../engine.h"
#include "texture_manager.h"
#include "shader_manager.h"

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>


namespace bulka {

	LoadingScreen::LoadingScreen(bool visible) : visible(visible)
	{
	}

	LoadingScreen::~LoadingScreen()
	{
		glDeleteBuffers(1, &VBO);
		glDeleteVertexArrays(1, &VAO);
	}
	void LoadingScreen::init() {
		float sizeX = 0.2f;
		float sizeY = 0.2f * Window::getAspect();
		float vertices[]{
			-sizeX, -sizeY, 0.0f, 1.0f,
			sizeX, -sizeY, 1.0f, 1.0f,
			sizeX, sizeY, 1.0f, 0.0f,

			sizeX, sizeY, 1.0f, 0.0f,
			-sizeX, sizeY, 0.0f, 0.0f,
			-sizeX, -sizeY, 0.0f, 1.0f,
		};
		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);
		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(float) * 6, vertices, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (GLvoid*)(0 * sizeof(float)));
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}
	void LoadingScreen::render() {
		if (!visible) {
			return;
		}
		glClearColor(1, 1, 1, 1);
		glClear(GL_COLOR_BUFFER_BIT);
		ShaderManager::loadingScreenShader.bind();
		ShaderManager::loadingScreenShader.uniformMat4f("rotation", rotation);
		rotation = glm::rotate(rotation, static_cast<float>(3.0f * Engine::getDeltaTime()), glm::vec3(0, 0, 1));
		glActiveTexture(GL_TEXTURE0);
		TextureManager::bindTexture("res/textures/bulka.png");
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);
		TextureManager::unbindTexture();
		ShaderManager::loadingScreenShader.unbind();
	}


	bool LoadingScreen::isVisible() {
		return visible;
	}
	void LoadingScreen::setVisible(bool val) {
		visible = val;
	}
}