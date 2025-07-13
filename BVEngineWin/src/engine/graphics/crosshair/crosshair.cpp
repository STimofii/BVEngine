#include "crosshair.h"
#include "../shader_manager.h"
#include "../../window.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
namespace bulka {
	Crosshair::Crosshair()
	{

	}
	Crosshair::~Crosshair()
	{
		if (VBO != 0) {
			glDeleteBuffers(1, &VBO);
			VBO = 0;
		}
		if (VAO != 0) {
			glDeleteVertexArrays(1, &VAO);
			VAO = 0;
		}
	}
	void Crosshair::init() {
		if (VBO != 0) {
			glDeleteBuffers(1, &VBO);
			VBO = 0;
		}
		if (VAO != 0) {
			glDeleteVertexArrays(1, &VAO);
			VAO = 0;
		}
		float size = 20.0f;
		float screenWidth = Window::getRealWidth();
		float screenHeight = Window::getRealHeight();
		float right = (screenWidth - size)/ 2.0f;
		float left = (screenWidth + size) / 2.0f;
		float bottom = (screenHeight - size) / 2.0f;
		float top = (screenHeight + size) / 2.0f;
		float centerX = (screenWidth) / 2.0f;
		float centerY = (screenHeight) / 2.0f;
		float vertices[] = {
			left, centerY, 1.0f / left, 1.0f / centerY,
			right, centerY, 1.0f / right, 1.0f / centerY,
			centerX, bottom, 1.0f / top, 1.0f / centerX,
			centerX, top, 1.0f / bottom, 1.0f / centerX
		};
		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);
		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(float) * 4, vertices, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (GLvoid*)(0 * sizeof(float)));
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}
	void Crosshair::render() {
		ShaderManager::crosshairShader.bind();
		//glActiveTexture(GL_TEXTURE0);
		glBindVertexArray(VAO);
		//glBindTexture(GL_TEXTURE_2D, singleSizeFont->getTexture());
		glDrawArrays(GL_LINES, 0, 4);
		//glBindTexture(GL_TEXTURE_2D, 0);
		glBindVertexArray(0);
		ShaderManager::crosshairShader.unbind();
	}
}