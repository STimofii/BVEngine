#include "postprocessing.h"

#include "shader_manager.h"
#include "../window.h"

#include <iostream>
namespace bulka {
	Postprocessing::Postprocessing()
	{
	}

	Postprocessing::~Postprocessing()
	{
		if (VBO != 0) {
			glDeleteBuffers(1, &VBO);
			VBO = 0;
		}
		if (VAO != 0) {
			glDeleteVertexArrays(1, &VAO);
			VAO = 0;
		}
		if (FBO != 0) {
			glDeleteFramebuffers(1, &FBO);
			FBO = 0;
		}
		if (FBO_Texture != 0) {
			glDeleteTextures(1, &FBO_Texture);
			FBO_Texture = 0;
		}
		if (RBO != 0) {
			glDeleteRenderbuffers(1, &RBO);
			RBO = 0;
		}
	}

	void Postprocessing::init() {
		initFBO();
		if (VBO != 0) {
			glDeleteBuffers(1, &VBO);
			VBO = 0;
		}
		if (VAO != 0) {
			glDeleteVertexArrays(1, &VAO);
			VAO = 0;
		}

		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);
		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (GLvoid*)(0 * sizeof(float)));
		glBindVertexArray(0);

	}
	void Postprocessing::initFBO()
	{
		if (FBO != 0) {
			glDeleteFramebuffers(1, &FBO);
			FBO = 0;
		}
		if (FBO_Texture != 0) {
			glDeleteTextures(1, &FBO_Texture);
			FBO_Texture = 0;
		}
		if (RBO != 0) {
			glDeleteRenderbuffers(1, &RBO);
			RBO = 0;
		}
		glGenFramebuffers(1, &FBO);
		glBindFramebuffer(GL_FRAMEBUFFER, FBO);

		glGenTextures(1, &FBO_Texture);
		glBindTexture(GL_TEXTURE_2D, FBO_Texture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Window::getRealWidth(), Window::getRealHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glBindTexture(GL_TEXTURE_2D, 0);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, FBO_Texture, 0);

		glGenRenderbuffers(1, &RBO);
		glBindRenderbuffer(GL_RENDERBUFFER, RBO);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, Window::getRealWidth(), Window::getRealHeight());
		glBindRenderbuffer(GL_RENDERBUFFER, 0);

		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, RBO);

		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			std::cerr << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
	void Postprocessing::render() {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		ShaderManager::postprocessingShader.bind();
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, FBO_Texture);
		ShaderManager::postprocessingShader.uniform1i("screenTexture", 0);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);
		ShaderManager::postprocessingShader.unbind();
	}
	void Postprocessing::bindFBO()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, FBO);
	}
	void Postprocessing::unbindFBO()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
}